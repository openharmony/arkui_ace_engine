/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/layout/layout_wrapper_node.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void LayoutWrapperNode::Update(
    WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty)
{
    hostNode_ = std::move(hostNode);
    geometryNode_ = std::move(geometryNode);
    layoutProperty_ = std::move(layoutProperty);
}

LayoutWrapperNode::LayoutWrapperNode(
    WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty)
    : LayoutWrapper(std::move(hostNode)), geometryNode_(std::move(geometryNode)),
      layoutProperty_(std::move(layoutProperty))
{}

void LayoutWrapperNode::AppendChild(const RefPtr<LayoutWrapperNode>& child, bool isOverlayNode)
{
    CHECK_NULL_VOID(child);
    if (!isOverlayNode) {
        children_.emplace_back(child);
        childrenMap_.try_emplace(currentChildCount_, child);
        ++currentChildCount_;
    } else {
        overlayChild_ = child;
    }
}
RefPtr<LayoutWrapper> LayoutWrapperNode::GetOrCreateChildByIndex(uint32_t index, bool addToRenderTree, bool isCache)
{
    if ((index >= static_cast<uint32_t>(currentChildCount_)) || (index < 0)) {
        return nullptr;
    }
    auto iter = childrenMap_.find(index);
    if (iter != childrenMap_.end()) {
        if (addToRenderTree) {
            iter->second->BuildLazyItem();
            iter->second->SetActive(true);
        }
        return iter->second;
    }
    CHECK_NULL_RETURN(layoutWrapperBuilder_, nullptr);
    auto wrapper = layoutWrapperBuilder_->GetOrCreateWrapperByIndex(index);
    CHECK_NULL_RETURN(wrapper, nullptr);
    if (addToRenderTree) {
        wrapper->SetActive(true);
    }
    return wrapper;
}

void LayoutWrapperNode::SetCacheCount(int32_t cacheCount, const std::optional<LayoutConstraintF>& itemConstraint)
{
    CHECK_NULL_VOID(layoutWrapperBuilder_);
    layoutWrapperBuilder_->SetCacheCount(cacheCount, itemConstraint);
}

void LayoutWrapperNode::Build(bool addToRenderTree)
{
    for (const auto& child : children_) {
        cachedList_.push_back(child);
    }
    if (layoutWrapperBuilder_) {
        auto buildItems = layoutWrapperBuilder_->ExpandAllChildWrappers();
        auto index = layoutWrapperBuilder_->GetStartIndex();
        auto insertIter = cachedList_.begin();
        std::advance(insertIter, index);
        cachedList_.splice(insertIter, buildItems);
    }
    if (addToRenderTree) {
        for (const auto& child : cachedList_) {
            child->BuildLazyItem();
            if (!child->IsActive()) {
                child->SetActive(true);
            }
        }
        if (overlayChild_) {
            overlayChild_->BuildLazyItem();
            if (!overlayChild_->IsActive()) {
                overlayChild_->SetActive(true);
            }
        }
    }
}

ChildrenListWithGuard LayoutWrapperNode::GetAllChildrenWithBuild(bool addToRenderTree)
{
    if (cachedList_.empty()) {
        Build(addToRenderTree);
    }
    static RecursiveLock dummyLock;
    return ChildrenListWithGuard(cachedList_, dummyLock);
}

void LayoutWrapperNode::RemoveChildInRenderTree(uint32_t index)
{
    auto wrapper = GetOrCreateChildByIndex(index, false);
    CHECK_NULL_VOID(wrapper);
    wrapper->SetActive(false);
}

void LayoutWrapperNode::RemoveAllChildInRenderTree()
{
    for (auto& child : childrenMap_) {
        child.second->SetActive(false);
    }
    CHECK_NULL_VOID(layoutWrapperBuilder_);
    layoutWrapperBuilder_->RemoveAllChildInRenderTree();
}

void LayoutWrapperNode::ResetHostNode()
{
    hostNode_.Reset();
}

const std::string& LayoutWrapperNode::GetHostTag() const
{
    auto host = GetHostNode();
    if (!host) {
        static std::string retFailed;
        return retFailed;
    }
    return host->GetTag();
}

int32_t LayoutWrapperNode::GetHostDepth() const
{
    auto host = GetHostNode();
    CHECK_NULL_RETURN(host, -1);
    return host->GetDepth();
}

// This will call child and self measure process.
void LayoutWrapperNode::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
    auto host = GetHostNode();
    CHECK_NULL_VOID(layoutProperty_);
    CHECK_NULL_VOID(geometryNode_);
    CHECK_NULL_VOID(host);

    CHECK_NULL_VOID(layoutAlgorithm_);
    if (layoutAlgorithm_->SkipMeasure()) {
        return;
    }

    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr && geometryTransition->IsRunning(GetHostNode())) {
        geometryTransition->WillLayout(Claim(this));
    }

    auto preConstraint = layoutProperty_->GetLayoutConstraint();
    auto contentConstraint = layoutProperty_->GetContentLayoutConstraint();
    layoutProperty_->BuildGridProperty(host);
    if (parentConstraint) {
        ApplyConstraint(*parentConstraint);
    } else {
        CreateRootConstraint();
    }
    layoutProperty_->UpdateContentConstraint();
    geometryNode_->UpdateMargin(layoutProperty_->CreateMargin());
    geometryNode_->UpdatePaddingWithBorder(layoutProperty_->CreatePaddingAndBorder());

    isConstraintNotChanged_ = preConstraint ? preConstraint == layoutProperty_->GetLayoutConstraint() : false;
    if (!isConstraintNotChanged_) {
        isConstraintNotChanged_ =
            contentConstraint ? contentConstraint == layoutProperty_->GetContentLayoutConstraint() : false;
    }

    if (isConstraintNotChanged_ && !skipMeasureContent_) {
        if (!CheckNeedForceMeasureAndLayout()) {
            skipMeasureContent_ = true;
        }
    }

    if (!skipMeasureContent_.value_or(false)) {
        skipMeasureContent_ = false;
        auto size = layoutAlgorithm_->MeasureContent(layoutProperty_->CreateContentConstraint(), this);
        if (size.has_value()) {
            geometryNode_->SetContentSize(size.value());
        }
        layoutAlgorithm_->Measure(this);

        if (overlayChild_) {
            overlayChild_->Measure(GetLayoutProperty()->CreateChildConstraint());
        }

        // check aspect radio.
        auto pattern = host->GetPattern();
        if (pattern && pattern->IsNeedAdjustByAspectRatio()) {
            const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
            auto aspectRatio = magicItemProperty.GetAspectRatioValue();
            // Adjust by aspect ratio, firstly pick height based on width. It means that when width, height and
            // aspectRatio are all set, the height is not used.
            auto width = geometryNode_->GetFrameSize().Width();
            auto height = width / aspectRatio;
            geometryNode_->SetFrameSize(SizeF({ width, height }));
        }
    }
}

// Called to perform layout children.
void LayoutWrapperNode::Layout()
{
    int64_t time = GetSysTimestamp();
    auto host = GetHostNode();
    CHECK_NULL_VOID(layoutProperty_);
    CHECK_NULL_VOID(geometryNode_);
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(layoutAlgorithm_);

    OffsetNodeToSafeArea();

    if (layoutAlgorithm_->SkipLayout()) {
        return;
    }

    if ((skipMeasureContent_ == true)) {
        return;
    }

    if (!layoutProperty_->GetLayoutConstraint()) {
        const auto& parentLayoutConstraint = geometryNode_->GetParentLayoutConstraint();
        if (parentLayoutConstraint) {
            layoutProperty_->UpdateLayoutConstraint(parentLayoutConstraint.value());
        } else {
            LayoutConstraintF layoutConstraint;
            layoutConstraint.percentReference.SetWidth(PipelineContext::GetCurrentRootWidth());
            layoutConstraint.percentReference.SetHeight(PipelineContext::GetCurrentRootHeight());
            layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
        }
        layoutProperty_->UpdateContentConstraint();
    }
    layoutAlgorithm_->Layout(this);
    LayoutOverlay();

    time = GetSysTimestamp() - time;
    AddNodeFlexLayouts();
    AddNodeLayoutTime(time);
}

bool LayoutWrapperNode::SkipMeasureContent() const
{
    return (skipMeasureContent_ == true) || layoutAlgorithm_->SkipMeasure();
}

bool LayoutWrapperNode::CheckNeedForceMeasureAndLayout()
{
    if (needForceMeasureAndLayout_) {
        return needForceMeasureAndLayout_.value();
    }
    PropertyChangeFlag flag = layoutProperty_->GetPropertyChangeFlag();
    // Need to remove layout flag when measure and layout make independent in each pattern layoutAlgorithm like
    // flex.
    bool needForceMeasureAndLayout = CheckNeedMeasure(flag) || CheckNeedLayout(flag);
    if (needForceMeasureAndLayout) {
        needForceMeasureAndLayout_ = true;
        return true;
    }
    // check child flag.
    needForceMeasureAndLayout_ = std::any_of(
        children_.begin(), children_.end(), [](const auto& item) { return item->CheckNeedForceMeasureAndLayout(); });
    return needForceMeasureAndLayout_.value();
}

bool LayoutWrapperNode::CheckChildNeedForceMeasureAndLayout()
{
    return std::any_of(
        children_.begin(), children_.end(), [](const auto& item) { return item->CheckNeedForceMeasureAndLayout(); });
}

void LayoutWrapperNode::MountToHostOnMainThread()
{
    SwapDirtyLayoutWrapperOnMainThread();
}

void LayoutWrapperNode::SwapDirtyLayoutWrapperOnMainThreadForChild(RefPtr<LayoutWrapperNode> child)
{
    if (!child) {
        return;
    }
    auto node = child->GetHostNode();
    if (node && node->GetLayoutProperty()) {
        const auto& geometryTransition = node->GetLayoutProperty()->GetGeometryTransition();
        if (geometryTransition != nullptr && geometryTransition->IsNodeInAndActive(node)) {
            return;
        }
    }
    child->SwapDirtyLayoutWrapperOnMainThread();
}

void LayoutWrapperNode::SwapDirtyLayoutWrapperOnMainThread()
{
    if (IsActive()) {
        for (const auto& child : children_) {
            SwapDirtyLayoutWrapperOnMainThreadForChild(child);
        }

        if (overlayChild_) {
            SwapDirtyLayoutWrapperOnMainThreadForChild(overlayChild_);
        }

        if (layoutWrapperBuilder_) {
            layoutWrapperBuilder_->SwapDirtyAndUpdateBuildCache();
        }
    }

    auto host = hostNode_.Upgrade();
    CHECK_NULL_VOID(host);
    host->SwapDirtyLayoutWrapperOnMainThread(Claim(this));

    /* Adjust components' position which have been set grid properties */
    for (const auto& child : children_) {
        if (child && child->GetHostNode()) {
            child->GetHostNode()->AdjustGridOffset();
        }
    }
    CHECK_NULL_VOID(layoutWrapperBuilder_);
    layoutWrapperBuilder_->AdjustGridOffset();
}

void LayoutWrapperNode::BuildLazyItem()
{
    if (!lazyBuildFunction_) {
        return;
    }
    ACE_FUNCTION_TRACE();
    lazyBuildFunction_(Claim(this));
    lazyBuildFunction_ = nullptr;
}

std::pair<int32_t, int32_t> LayoutWrapperNode::GetLazyBuildRange()
{
    if (layoutWrapperBuilder_) {
        auto start = layoutWrapperBuilder_->GetStartIndex();
        auto end = start + layoutWrapperBuilder_->GetTotalCount();
        return { start, end };
    }
    return { -1, 0 };
}

void LayoutWrapperNode::SetLongPredictTask()
{
    CHECK_NULL_VOID(layoutWrapperBuilder_);
    layoutWrapperBuilder_->SetLongPredictTask();
}

void LayoutWrapperNode::LayoutOverlay()
{
    if (!overlayChild_) {
        return;
    }
    overlayChild_->Layout();
    auto size = GetGeometryNode()->GetFrameSize();
    auto align = Alignment::TOP_LEFT;
    Dimension offsetX, offsetY;
    auto childLayoutProperty = overlayChild_->GetLayoutProperty();
    childLayoutProperty->GetOverlayOffset(offsetX, offsetY);
    auto offset = OffsetF(offsetX.ConvertToPx(), offsetY.ConvertToPx());
    if (childLayoutProperty->GetPositionProperty()) {
        align = childLayoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }

    auto childSize = overlayChild_->GetGeometryNode()->GetMarginFrameSize();
    auto translate = Alignment::GetAlignPosition(size, childSize, align) + offset;
    overlayChild_->GetGeometryNode()->SetMarginFrameOffset(translate);
}

} // namespace OHOS::Ace::NG
