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
#include "base/utils/string_utils.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/flex/flex_layout_property.h"
#include "core/components_ng/pattern/flex/flex_layout_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/components_ng/pattern/smart_layout/smart_layout_engine_loader.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr double SMART_LAYOUT_TEXT_ADAPT_MIN_FONT_SIZE_LIMIT_RATIO = 0.6;

/**
 * @brief Fixed inspector id prefix marking smart layout enabled containers, matched by prefix.
 */
constexpr char GENUI_RENDER_COMPONENT_ID_NAME[] = "__genui_render_component__";

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

bool SmartLayoutAlgorithm::HasSmartLayoutIdName(const RefPtr<FrameNode>& node)
{
    CHECK_NULL_RETURN(node, false);
    const auto& idName = node->GetInspectorId();
    return idName.has_value() && StringUtils::StartWith(idName.value(), GENUI_RENDER_COMPONENT_ID_NAME);
}

RefPtr<FrameNode> SmartLayoutAlgorithm::FindGenUIRenderComp(const RefPtr<FrameNode>& hostNode)
{
    auto node = hostNode;
    while (node) {
        if (HasSmartLayoutIdName(node)) {
            return node;
        }
        node = node->GetAncestorNodeOfFrame(false);
    }
    return nullptr;
}

SmartLayoutType SmartLayoutAlgorithm::GetLayoutTypeFromWrapper(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, SmartLayoutType::UNKNOWN);
    const auto& hostTag = layoutWrapper->GetHostTag();
    if (hostTag == V2::COLUMN_ETS_TAG) {
        return SmartLayoutType::COLUMN;
    }
    if (hostTag == V2::ROW_ETS_TAG) {
        return SmartLayoutType::ROW;
    }
    if (hostTag == V2::TEXT_ETS_TAG) {
        return SmartLayoutType::TEXT;
    }
    if (hostTag == V2::FLEX_ETS_TAG) {
        auto hostNode = layoutWrapper->GetHostNode();
        if (hostNode) {
            auto flexPattern = hostNode->GetPattern<FlexLayoutPattern>();
            if (flexPattern && flexPattern->GetIsWrap()) {
                return SmartLayoutType::GENERAL;
            }
        }
        auto layoutProp = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
        if (layoutProp) {
            auto direction = layoutProp->GetFlexDirection().value_or(FlexDirection::ROW);
            if (direction == FlexDirection::COLUMN || direction == FlexDirection::COLUMN_REVERSE) {
                return SmartLayoutType::COLUMN;
            }
        }
        return SmartLayoutType::ROW;
    }
    return SmartLayoutType::GENERAL;
}

bool SmartLayoutAlgorithm::PerformSmartLayout(LayoutWrapper* layoutWrapper)
{
    ACE_SCOPED_TRACE("PerformSmartLayout");
    auto layoutType = GetLayoutTypeFromWrapper(layoutWrapper);
    CHECK_EQUAL_RETURN(layoutType, SmartLayoutType::UNKNOWN, false);
    if (layoutType == SmartLayoutType::TEXT) {
        return HandleTextContentOverflow(layoutWrapper);
    }
    LOGD("SmartLayout: Detected layout %{public}s content overflow!!",
        layoutWrapper->GetHostTag().c_str());
    return ExecuteLayout(layoutWrapper, layoutType);
}

bool SmartLayoutAlgorithm::ExecuteLayout(LayoutWrapper* layoutWrapper, SmartLayoutType layoutType)
{
    CHECK_NULL_RETURN(layoutWrapper, false);

    auto* engine = SmartLayoutEngineLoader::GetInstance().GetEngine();
    CHECK_NULL_RETURN(engine, false);

    rootNode_ = engine->CreateRootNode();
    CHECK_NULL_RETURN(rootNode_, false);
    rootNode_->SetLayoutType(layoutType);

    if (!InitializeLayoutContext(layoutWrapper)) {
        return false;
    }
    ProcessLayoutChildren(layoutWrapper);

    if (layoutType == SmartLayoutType::ROW) {
        rootNode_->ApplyRowConstraints();
    } else if (layoutType == SmartLayoutType::COLUMN) {
        rootNode_->ApplyColumnConstraints();
    } else {
        if (!rootNode_->GetBoundingBox().IsValid()) {
            return false;
        }
        rootNode_->ApplyGeneralConstraints();
    }

    if (!rootNode_->SolveLayout()) {
        return false;
    }
    return ApplyLayoutResults(layoutWrapper);
}

std::vector<ChildLayoutInfo> SmartLayoutAlgorithm::CollectChildInfo(LayoutWrapper* layoutWrapper)
{
    std::vector<ChildLayoutInfo> childInfos;
    CHECK_NULL_RETURN(layoutWrapper, childInfos);

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
        if (NearZero(info.width) || NearZero(info.height)) {
            continue;
        }
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

    // For flex wrap, compute and store bounding box
    if (rootNode_->GetLayoutType() == SmartLayoutType::GENERAL) {
        SmartLayoutRect boundingBox = rootNode_->GetChildrenBoundingBox();
        if (boundingBox.IsValid()) {
            rootNode_->SetBoundingBox(boundingBox);
        }
    }
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
    double boundingBoxOffsetY,
    bool isFormRender)
{
    double offsetX = layoutNode.GetPosition().offsetX.value;
    double offsetY = layoutNode.GetPosition().offsetY.value;

    if (isFormRender) {
        return OffsetF(static_cast<float>(offsetX + boundingBoxOffsetX),
            static_cast<float>(offsetY + boundingBoxOffsetY));
    }

    auto layoutType = rootNode_->GetLayoutType();
    if (layoutType != SmartLayoutType::ROW && layoutType != SmartLayoutType::COLUMN) {
        return OffsetF(static_cast<float>(offsetX), static_cast<float>(offsetY));
    }

    auto& context = rootNode_->GetContext();
    bool centerX = (layoutType == SmartLayoutType::ROW)
        ? (context.mainAxisAlign == SmartLayoutAlign::CENTER)
        : (context.crossAxisAlign == SmartLayoutAlign::CENTER);
    bool centerY = (layoutType == SmartLayoutType::ROW)
        ? (context.crossAxisAlign == SmartLayoutAlign::CENTER)
        : (context.mainAxisAlign == SmartLayoutAlign::CENTER);

    return OffsetF(static_cast<float>(centerX ? offsetX + boundingBoxOffsetX : offsetX),
        static_cast<float>(centerY ? offsetY + boundingBoxOffsetY : offsetY));
}

void SmartLayoutAlgorithm::ApplyChildLayout(
    const RefPtr<LayoutWrapper>& childWrapper,
    const std::unordered_map<int64_t, std::shared_ptr<ISmartLayoutNode>>& nodeMap,
    double sizeScale, double boundingBoxOffsetX, double boundingBoxOffsetY)
{
    CHECK_NULL_VOID(childWrapper);
    auto hostNode = childWrapper->GetHostNode();
    CHECK_NULL_VOID(hostNode);
    auto renderContext = hostNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto layoutProperty = childWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    if (renderContext->HasPosition() || (layoutPolicy.has_value() && layoutPolicy->IsMatch())) {
        return;
    }

    auto it = nodeMap.find(hostNode->GetId());
    if (it == nodeMap.end()) {
        return;
    }

    auto& layoutNode = it->second;

    auto geoNode = childWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geoNode);
    auto* context = hostNode->GetContext();
    bool isFormRender = false;
    // 1px tolerance for matching smart layout root size against form/page root size
    constexpr float FORM_SIZE_EPSILON = 1.0f;
    const auto& rootSize = rootNode_->GetContext().size;
    auto isRootSizeMatched = [&rootSize](float width, float height) {
        return NearEqual(width, rootSize.Width(), FORM_SIZE_EPSILON) &&
            NearEqual(height, rootSize.Height(), FORM_SIZE_EPSILON);
    };
    if (context != nullptr && context->IsFormRender()) {
        isFormRender = isRootSizeMatched(context->GetRootRect().Width(), context->GetRootRect().Height());
    } else {
        auto formNode = FindGenUIRenderComp(hostNode);
        if (formNode != nullptr) {
            auto formGeo = formNode->GetGeometryNode();
            CHECK_NULL_VOID(formGeo);
            isFormRender = isRootSizeMatched(formGeo->GetFrameSize().Width(), formGeo->GetFrameSize().Height());
        }
    }
    OffsetF offset =
        CalculateOffsetWithMargin(*layoutNode, geoNode, boundingBoxOffsetX, boundingBoxOffsetY, isFormRender);
    geoNode->SetFrameOffset(offset);
    renderContext->SetRenderPivot(0.0f, 0.0f);
    hostNode->ForceSyncGeometryNode();
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    renderContext->SetScale(static_cast<float>(sizeScale), static_cast<float>(sizeScale));

    LOGD("SmartLayout: Applied layout for child %{public}s [%{public}s]: \
        offset=(%{public}f, %{public}f), size=(%{public}f, %{public}f)",
        layoutNode->GetName().c_str(), hostNode->GetTag().c_str(),
        layoutNode->GetPosition().offsetX.value, layoutNode->GetPosition().offsetY.value,
        layoutNode->GetSize().width.value, layoutNode->GetSize().height.value);
}

bool SmartLayoutAlgorithm::ApplyLayoutResults(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    CHECK_NULL_RETURN(rootNode_, false);

    const auto& children = rootNode_->GetChildren();
    if (children.empty()) {
        return false;
    }

    // Pre-calculate bounding box offsets once
    auto [boundingBoxOffsetX, boundingBoxOffsetY] = CalculateBoundingBoxOffsets();
    auto nodeMap = BuildNodeIdMap(children);
    double sizeScale = rootNode_->GetScaleInfo().sizeScale.value;
    if (NearZero(sizeScale)) {
        return false;
    }
    for (const auto& childWrapper : layoutWrapper->GetAllChildrenWithBuild(false)) {
        ApplyChildLayout(childWrapper, nodeMap, sizeScale, boundingBoxOffsetX, boundingBoxOffsetY);
    }
    return true;
}

std::pair<double, double> SmartLayoutAlgorithm::CalculateBoundingBoxOffsets()
{
    CHECK_NULL_RETURN(rootNode_, (std::pair<double, double>{0.0, 0.0}));

    auto rect = rootNode_->GetChildrenBoundingBox();
    double offsetOfBoundingBoxX = (rootNode_->GetSize().width.value - rect.width) / 2 - rect.Left();
    double offsetOfBoundingBoxY = (rootNode_->GetSize().height.value - rect.height) / 2 - rect.Top();

    return {offsetOfBoundingBoxX, offsetOfBoundingBoxY};
}

bool SmartLayoutAlgorithm::InitializeLayoutContext(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
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

    auto hostNode = layoutWrapper->GetHostNode();
    auto pipeline = hostNode ? hostNode->GetContext() : nullptr;
    context.contentPadding = Dimension(SMART_LAYOUT_CONTENT_PADDING, DimensionUnit::VP).ConvertToPx();
    auto layoutProp = layoutWrapper->GetLayoutProperty();
    if (layoutProp) {
        if (pipeline) {
            auto padding = layoutProp->CreatePaddingWithoutBorder();
            context.padding.left = static_cast<double>(padding.left.value_or(0));
            context.padding.right = static_cast<double>(padding.right.value_or(0));
            context.padding.top = static_cast<double>(padding.top.value_or(0));
            context.padding.bottom = static_cast<double>(padding.bottom.value_or(0));
        }

        auto flexProp = AceType::DynamicCast<FlexLayoutProperty>(layoutProp);
        if (flexProp) {
            auto mainAlign = flexProp->GetMainAxisAlign().value_or(FlexAlign::FLEX_START);
            auto crossAlign = flexProp->GetCrossAxisAlign().value_or(FlexAlign::CENTER);
            context.mainAxisAlign = ConvertFlexAlignToSmartLayoutAlign(mainAlign);
            context.crossAxisAlign = ConvertFlexAlignToSmartLayoutAlign(crossAlign);
        }
    }

    rootNode_->SetFixedSizeConstraints(context.size.Width(), context.size.Height());

    if (hostNode) {
        OffsetF absoluteOffset = hostNode->GetTransformRelativeOffset();
        if (NearZero(absoluteOffset.GetY())) {
            rootNode_->SetAvoidSafeArea(true);
        }
    }
    return true;
}

bool SmartLayoutAlgorithm::HandleTextContentOverflow(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(hostNode, false);
    auto textPattern = hostNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    auto layoutProperty = AceType::DynamicCast<TextLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_RETURN(layoutProperty, false);
    auto spanItems = textPattern->GetSpanItemChildren();
    bool propertyChanged = false;
    std::optional<Dimension> explicitSpanFontSize;
    if (spanItems.size() == 1 && spanItems.front() && spanItems.front()->fontStyle &&
        spanItems.front()->fontStyle->HasFontSize()) {
        explicitSpanFontSize = spanItems.front()->fontStyle->GetFontSize();
        spanItems.front()->fontStyle->ResetFontSize();
        layoutProperty->UpdateFontSize(explicitSpanFontSize.value());
        propertyChanged = true;
    }
    auto currentFontSize = layoutProperty->GetFontSize().value_or(textPattern->GetTextStyle().GetFontSize());
    auto targetMinFontSize = currentFontSize * SMART_LAYOUT_TEXT_ADAPT_MIN_FONT_SIZE_LIMIT_RATIO;
    auto adaptMinFontSize = layoutProperty->GetAdaptMinFontSize();
    if (!adaptMinFontSize.has_value() || NearZero(adaptMinFontSize->ConvertToPx()) ||
        GreatNotEqual(adaptMinFontSize->ConvertToPx(), targetMinFontSize.ConvertToPx())) {
        layoutProperty->UpdateAdaptMinFontSize(targetMinFontSize);
        propertyChanged = true;
    }
    auto adaptMaxFontSize = layoutProperty->GetAdaptMaxFontSize();
    if (explicitSpanFontSize.has_value() || !adaptMaxFontSize.has_value() ||
        NearZero(adaptMaxFontSize->ConvertToPx())) {
        layoutProperty->UpdateAdaptMaxFontSize(explicitSpanFontSize.value_or(currentFontSize));
        propertyChanged = true;
    }
    if (!layoutProperty->HasHeightAdaptivePolicy() ||
        layoutProperty->GetHeightAdaptivePolicy() != TextHeightAdaptivePolicy::MAX_LINES_FIRST) {
        layoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MAX_LINES_FIRST);
        propertyChanged = true;
    }
    if (!propertyChanged) {
        return true;
    }
    layoutProperty->OnPropertyChangeMeasure();
    return RemeasureText(layoutWrapper);
}

bool SmartLayoutAlgorithm::RemeasureText(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_RETURN(layoutWrapper, false);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto hostNode = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(hostNode, false);
    auto layoutAlgorithmWrapper = layoutWrapper->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = layoutAlgorithmWrapper->GetLayoutAlgorithm();
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    auto textLayoutAlgorithm = AceType::DynamicCast<TextLayoutAlgorithm>(layoutAlgorithm);
    CHECK_NULL_RETURN(textLayoutAlgorithm, false);
    auto textPattern = hostNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(textPattern, false);
    auto content = UtfUtils::Str16DebugToStr8(textPattern->GetTextForDisplay());
    const auto& previousTextStyle = textLayoutAlgorithm->GetTextStyle();
    auto previousFontSize = Dimension(previousTextStyle.GetFontSize().ConvertToFpWithEnv(
        previousTextStyle.GetEnvFontScale()), DimensionUnit::FP);
    auto parentNode = hostNode->GetParentFrameNode();
    bool isButtonLabel = hostNode->IsInternal() && parentNode && parentNode->GetTag() == V2::BUTTON_ETS_TAG;
    OffsetF previousCenter;
    if (isButtonLabel) {
        previousCenter = geometryNode->GetMarginFrameRect().Center();
    }

    // Rebuild and lay out the adapted paragraph before the current FrameNode layout is committed.
    auto contentSize = layoutAlgorithm->MeasureContent(layoutProperty->CreateContentConstraint(), layoutWrapper);
    if (contentSize.has_value()) {
        geometryNode->SetContentSize(contentSize.value());
    }
    layoutAlgorithm->Measure(layoutWrapper);
    const auto& currentTextStyle = textLayoutAlgorithm->GetTextStyle();
    auto currentFontSize = Dimension(currentTextStyle.GetFontSize().ConvertToFpWithEnv(
        currentTextStyle.GetEnvFontScale()), DimensionUnit::FP);
    LOGD("SmartLayout: Applied layout for text [id:%{public}d]: content=%{public}s, "
         "fontSize=(%{public}s -> %{public}s)",
        hostNode->GetId(), content.c_str(), previousFontSize.ToString().c_str(),
        currentFontSize.ToString().c_str());
    if (isButtonLabel) {
        auto marginFrameSize = geometryNode->GetMarginFrameSize();
        geometryNode->SetMarginFrameOffset(OffsetF(previousCenter.GetX() - marginFrameSize.Width() / 2.0f,
            previousCenter.GetY() - marginFrameSize.Height() / 2.0f));
    }
    layoutAlgorithm->Layout(layoutWrapper);
    return true;
}

bool SmartLayoutAlgorithm::PerformSmartLayoutScaleUp(LayoutWrapper* layoutWrapper)
{
    ACE_SCOPED_TRACE("PerformSmartLayoutScaleUp");
    auto layoutType = GetLayoutTypeFromWrapper(layoutWrapper);
    CHECK_EQUAL_RETURN(layoutType, SmartLayoutType::UNKNOWN, false);
    LOGD("SmartLayout: Detected layout %{public}s content underutilized, scaling up",
        layoutWrapper->GetHostTag().c_str());

    CHECK_NULL_RETURN(layoutWrapper, false);
    auto* engine = SmartLayoutEngineLoader::GetInstance().GetEngine();
    CHECK_NULL_RETURN(engine, false);

    rootNode_ = engine->CreateRootNode();
    CHECK_NULL_RETURN(rootNode_, false);
    rootNode_->SetLayoutType(layoutType);

    if (!InitializeLayoutContext(layoutWrapper)) {
        return false;
    }
    ProcessLayoutChildren(layoutWrapper);

    // Calculate bounding box
    auto boundingBox = rootNode_->GetChildrenBoundingBox();
    if (!boundingBox.IsValid()) {
        return false;
    }
    rootNode_->SetBoundingBox(boundingBox);

    // Apply scale-up constraints
    rootNode_->ApplyScaleUpConstraints();

    if (!rootNode_->SolveLayout()) {
        return false;
    }
    return ApplyLayoutResults(layoutWrapper);
}

} // namespace OHOS::Ace::NG
