/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "frameworks/core/components_ng/pattern/smart_layout/smart_layout_algorithm.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/smart_layout/smart_layout_engine_loader.h"

namespace OHOS::Ace::NG {

namespace {
/**
 * @brief Convert FlexAlign to SmartLayoutAlign for decoupling
 */
SmartLayoutAlign ConvertFlexAlignToSmartLayoutAlign(FlexAlign flexAlign)
{
    switch (flexAlign) {
        case FlexAlign::FLEX_START:
            return SmartLayoutAlign::FLEX_START;
        case FlexAlign::CENTER:
            return SmartLayoutAlign::CENTER;
        case FlexAlign::FLEX_END:
            return SmartLayoutAlign::FLEX_END;
        default:
            return SmartLayoutAlign::FLEX_START;
    }
}

} // namespace


SmartLayoutType SmartLayoutAlgorithm::GetLayoutTypeFromWrapper(LayoutWrapper* layoutWrapper)
{
    if (layoutWrapper == nullptr) {
        return SmartLayoutType::UNKNOWN;
    }
    const auto& hostTag = layoutWrapper->GetHostTag();
    if (hostTag == V2::COLUMN_ETS_TAG) {
        return SmartLayoutType::COLUMN;
    }
    if (hostTag == V2::ROW_ETS_TAG) {
        return SmartLayoutType::ROW;
    }
    if (hostTag == V2::FLEX_ETS_TAG) {
        auto layoutProp = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
        if (layoutProp) {
            auto direction = layoutProp->GetFlexDirection().value_or(FlexDirection::ROW);
            if (direction == FlexDirection::COLUMN || direction == FlexDirection::COLUMN_REVERSE) {
                return SmartLayoutType::COLUMN;
            }
        }
        return SmartLayoutType::ROW;
    }
    return SmartLayoutType::UNKNOWN;
}

void SmartLayoutAlgorithm::PerformSmartLayout(LayoutWrapper* layoutWrapper)
{
    AceTraceBegin("PerformSmartLayout");
    auto layoutType = GetLayoutTypeFromWrapper(layoutWrapper);
    LOGD("SmartLayout: Detected layout %{public}s content overflow!!",
        layoutWrapper ? layoutWrapper->GetHostTag().c_str() : "UNKNOWN");
    ExecuteLayout(layoutWrapper, layoutType);
    AceTraceEnd();
}

void SmartLayoutAlgorithm::ExecuteLayout(LayoutWrapper* layoutWrapper, SmartLayoutType layoutType)
{
    if (layoutWrapper == nullptr || layoutType == SmartLayoutType::UNKNOWN) {
        return;
    }

    auto* engine = SmartLayoutEngineLoader::GetInstance().GetEngine();
    if (engine == nullptr) {
        return;
    }

    rootNode_ = engine->CreateRootNode();
    CHECK_NULL_VOID(rootNode_);
    rootNode_->SetLayoutType(layoutType);

    if (!InitializeLayoutContext(layoutWrapper)) {
        return;
    }
    ProcessLayoutChildren(layoutWrapper);

    auto currentLayoutType = rootNode_->GetLayoutType();
    if (currentLayoutType == SmartLayoutType::COLUMN) {
        rootNode_->ApplyColumnConstraints();
    } else {
        rootNode_->ApplyRowConstraints();
    }

    if (!rootNode_->SolveLayout()) {
        return;
    }
    ApplyLayoutResults(layoutWrapper);
}

std::vector<ChildLayoutInfo> SmartLayoutAlgorithm::CollectChildInfo(LayoutWrapper* layoutWrapper)
{
    std::vector<ChildLayoutInfo> childInfos;
    if (layoutWrapper == nullptr) {
        return childInfos;
    }

    const auto& children = layoutWrapper->GetAllChildrenWithBuild(false);
    for (const auto& child : children) {
        if (child == nullptr || child->GetHostNode() == nullptr) {
            continue;
        }

        ChildLayoutInfo info;
        info.id = child->GetHostNode()->GetId();

        auto geo = child->GetGeometryNode();
        if (geo) {
            auto frameSize = geo->GetFrameSize();
            info.width = static_cast<double>(frameSize.Width());
            info.height = static_cast<double>(frameSize.Height());

            auto offset = geo->GetFrameOffset();
            info.offsetX = static_cast<double>(offset.GetX());
            info.offsetY = static_cast<double>(offset.GetY());
        }

        info.isBlank = (child->GetHostTag() == V2::BLANK_ETS_TAG);
        childInfos.push_back(info);
    }

    return childInfos;
}

void SmartLayoutAlgorithm::ProcessLayoutChildren(LayoutWrapper* layoutWrapper)
{
    auto childInfos = CollectChildInfo(layoutWrapper);
    if (childInfos.empty()) {
        return;
    }

    rootNode_->CreateChildrenFromInfos(childInfos);
}

std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>> SmartLayoutAlgorithm::BuildNodeIdMap(
    const std::vector<std::shared_ptr<ISmartLayoutNode>>& children)
{
    std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>> nodeMap;
    for (const auto& child : children) {
        if (child != nullptr) {
            nodeMap[child->GetNodeId()] = child;
        }
    }
    return nodeMap;
}

OffsetF SmartLayoutAlgorithm::CalculateOffsetWithMargin(
    const ISmartLayoutNode& layoutNode,
    const RefPtr<GeometryNode> geoNode,
    double boundingBoxOffsetX,
    double boundingBoxOffsetY)
{
    double offsetX = layoutNode.GetPosition().offsetX.value;
    double offsetY = layoutNode.GetPosition().offsetY.value;

    if (rootNode_->GetLayoutType() == SmartLayoutType::ROW) {
        return OffsetF(static_cast<float>(offsetX), static_cast<float>(offsetY + boundingBoxOffsetY));
    } else if (rootNode_->GetLayoutType() == SmartLayoutType::COLUMN) {
        return OffsetF(static_cast<float>(offsetX + boundingBoxOffsetX), static_cast<float>(offsetY));
    }
    return OffsetF(static_cast<float>(offsetX), static_cast<float>(offsetY));
}

void SmartLayoutAlgorithm::ApplyChildLayout(
    const RefPtr<LayoutWrapper>& childWrapper,
    const std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>>& nodeMap,
    double sizeScale,
    double boundingBoxOffsetX,
    double boundingBoxOffsetY)
{
    CHECK_NULL_VOID(childWrapper);
    auto hostNode = childWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);

    int64_t nodeId = hostNode->GetId();
    auto it = nodeMap.find(nodeId);
    if (it == nodeMap.end()) {
        return;
    }

    auto& layoutNode = it->second;

    auto geoNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geoNode);
    OffsetF offset = CalculateOffsetWithMargin(*layoutNode, geoNode, boundingBoxOffsetX, boundingBoxOffsetY);
    geoNode->SetFrameOffset(offset);

    auto renderContext = hostNode->GetRenderContext();
    if (renderContext != nullptr) {
        renderContext->SetRenderPivot(0.0f, 0.0f);
        renderContext->SetScale(static_cast<float>(sizeScale), static_cast<float>(sizeScale));
    }

    hostNode->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
    childWrapper->Layout();

    LOGD("SmartLayout: Applied layout for child %{public}s: \
        offset=(%{public}f, %{public}f), size=(%{public}f, %{public}f)",
        layoutNode->GetName().c_str(),
        layoutNode->GetPosition().offsetX.value,
        layoutNode->GetPosition().offsetY.value,
        layoutNode->GetSize().width.value,
        layoutNode->GetSize().height.value);
}

void SmartLayoutAlgorithm::ApplyLayoutResults(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    CHECK_NULL_VOID(rootNode_);

    const auto& children = rootNode_->GetChildren();
    if (children.empty()) {
        return;
    }

    // Pre-sync all data once to avoid O(N²) SyncData calls
    rootNode_->SyncData();
    for (const auto& child : children) {
        if (child != nullptr) {
            child->SyncData();
        }
    }

    // Pre-calculate bounding box offsets once
    auto [boundingBoxOffsetX, boundingBoxOffsetY] = CalculateBoundingBoxOffsets();

    auto nodeMap = BuildNodeIdMap(children);
    double sizeScale = rootNode_->GetScaleInfo().sizeScale.value;

    for (const auto& childWrapper : layoutWrapper->GetAllChildrenWithBuild(false)) {
        ApplyChildLayout(childWrapper, nodeMap, sizeScale, boundingBoxOffsetX, boundingBoxOffsetY);
    }
}

std::pair<double, double> SmartLayoutAlgorithm::CalculateBoundingBoxOffsets()
{
    if (rootNode_ == nullptr) {
        return {0.0, 0.0};
    }

    auto rect = rootNode_->GetChildrenBoundingBox();
    double offsetOfBoundingBoxX = (rootNode_->GetSize().width.value - rect.width) / 2 - rect.Left();
    double offsetOfBoundingBoxY = (rootNode_->GetSize().height.value - rect.height) / 2 - rect.Top();

    return {offsetOfBoundingBoxX, offsetOfBoundingBoxY};
}

bool SmartLayoutAlgorithm::InitializeLayoutContext(LayoutWrapper* layoutWrapper)
{
    if (layoutWrapper == nullptr) {
        return false;
    }
    const auto& children = layoutWrapper->GetAllChildrenWithBuild(false);
    if (children.empty()) {
        return false;
    }

    auto& context = rootNode_->GetContext();

    auto geo = layoutWrapper->GetGeometryNode();
    if (geo) {
        auto frameSize = geo->GetFrameSize();
        context.size.SetWidth(static_cast<double>(frameSize.Width()));
        context.size.SetHeight(static_cast<double>(frameSize.Height()));
    } else {
        context.size = SmartLayoutSize(0.0, 0.0);
    }

    auto layoutProp = layoutWrapper->GetLayoutProperty();
    if (layoutProp) {
        auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(layoutProp);
        if (flexProp) {
            auto mainAlign = flexProp->GetMainAxisAlign().value_or(FlexAlign::FLEX_START);
            auto crossAlign = flexProp->GetCrossAxisAlign().value_or(FlexAlign::CENTER);
            context.mainAxisAlign = ConvertFlexAlignToSmartLayoutAlign(mainAlign);
            context.crossAxisAlign = ConvertFlexAlignToSmartLayoutAlign(crossAlign);
        }
    }

    rootNode_->SetFixedSizeConstraints(context.size.Width(), context.size.Height());

    auto hostNode = layoutWrapper->GetHostNode();
    if (hostNode) {
        OffsetF absoluteOffset = hostNode->GetTransformRelativeOffset();
        if (NearZero(absoluteOffset.GetY())) {
            rootNode_->SetAvoidSafeArea(true);
        }
    }
    return true;
}

} // namespace OHOS::Ace::NG
