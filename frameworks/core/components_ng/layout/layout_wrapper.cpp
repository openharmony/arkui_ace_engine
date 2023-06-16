/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/layout/layout_wrapper.h"

#include <algorithm>

#include "base/log/ace_trace.h"
#include "base/utils/system_properties.h"
#include "base/utils/time_util.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void LayoutWrapper::Update(
    WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty)
{
    hostNode_ = std::move(hostNode);
    geometryNode_ = std::move(geometryNode);
    layoutProperty_ = std::move(layoutProperty);
    auto host = hostNode_.Upgrade();
    CHECK_NULL_VOID(host);
    host->RecordLayoutWrapper(WeakClaim(this));
}

LayoutWrapper::LayoutWrapper(
    WeakPtr<FrameNode> hostNode, RefPtr<GeometryNode> geometryNode, RefPtr<LayoutProperty> layoutProperty)
    : hostNode_(std::move(hostNode)), geometryNode_(std::move(geometryNode)), layoutProperty_(std::move(layoutProperty))
{
    auto host = hostNode_.Upgrade();
    CHECK_NULL_VOID(host);
    host->RecordLayoutWrapper(WeakClaim(this));
}

RefPtr<LayoutWrapper> LayoutWrapper::GetOrCreateChildByIndex(int32_t index, bool addToRenderTree)
{
    if ((index >= currentChildCount_) || (index < 0)) {
        LOGD("index is of out boundary, total count: %{public}d, target index: %{public}d", currentChildCount_, index);
        return nullptr;
    }
    auto iter = childrenMap_.find(index);
    if (iter != childrenMap_.end()) {
        if (addToRenderTree) {
            iter->second->BuildLazyItem();
            iter->second->isActive_ = true;
        }
        return iter->second;
    }
    CHECK_NULL_RETURN(layoutWrapperBuilder_, nullptr);
    auto wrapper = layoutWrapperBuilder_->GetOrCreateWrapperByIndex(index);
    CHECK_NULL_RETURN(wrapper, nullptr);
    if (addToRenderTree) {
        wrapper->isActive_ = true;
    }
    return wrapper;
}

void LayoutWrapper::SetCacheCount(int32_t cacheCount)
{
    CHECK_NULL_VOID_NOLOG(layoutWrapperBuilder_);
    layoutWrapperBuilder_->SetCacheCount(cacheCount);
}

const std::list<RefPtr<LayoutWrapper>>& LayoutWrapper::GetAllChildrenWithBuild(bool addToRenderTree)
{
    if (!cachedList_.empty()) {
        return cachedList_;
    }
    cachedList_ = children_;
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
            if (!child->isActive_) {
                child->isActive_ = true;
            }
        }
    }
    return cachedList_;
}

void LayoutWrapper::RemoveChildInRenderTree(const RefPtr<LayoutWrapper>& wrapper)
{
    CHECK_NULL_VOID(wrapper);
    wrapper->isActive_ = false;
}

void LayoutWrapper::RemoveChildInRenderTree(int32_t index)
{
    auto wrapper = GetOrCreateChildByIndex(index, false);
    CHECK_NULL_VOID(wrapper);
    wrapper->isActive_ = false;
}

void LayoutWrapper::RemoveAllChildInRenderTree()
{
    for (auto& child : childrenMap_) {
        child.second->isActive_ = false;
    }
    CHECK_NULL_VOID_NOLOG(layoutWrapperBuilder_);
    layoutWrapperBuilder_->RemoveAllChildInRenderTree();
}

void LayoutWrapper::ResetHostNode()
{
    hostNode_.Reset();
}

RefPtr<FrameNode> LayoutWrapper::GetHostNode() const
{
    return hostNode_.Upgrade();
}

WeakPtr<FrameNode> LayoutWrapper::GetWeakHostNode() const
{
    return hostNode_;
}

std::string LayoutWrapper::GetHostTag() const
{
    auto host = GetHostNode();
    CHECK_NULL_RETURN_NOLOG(host, "");
    return host->GetTag();
}

int32_t LayoutWrapper::GetHostDepth() const
{
    auto host = GetHostNode();
    CHECK_NULL_RETURN_NOLOG(host, -1);
    return host->GetDepth();
}

void LayoutWrapper::CreateRootConstraint()
{
    LayoutConstraintF layoutConstraint;
    layoutConstraint.percentReference.SetWidth(PipelineContext::GetCurrentRootWidth());
    const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
    auto hasAspectRatio = magicItemProperty && magicItemProperty->HasAspectRatio();
    if (hasAspectRatio) {
        auto aspectRatio = magicItemProperty->GetAspectRatioValue();
        if (Positive(aspectRatio)) {
            auto height = PipelineContext::GetCurrentRootHeight() / aspectRatio;
            layoutConstraint.percentReference.SetHeight(height);
        }
    } else {
        layoutConstraint.percentReference.SetHeight(PipelineContext::GetCurrentRootHeight());
    }
    layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
}

void LayoutWrapper::ApplyConstraint(LayoutConstraintF constraint)
{
    const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
    if (magicItemProperty && magicItemProperty->HasAspectRatio()) {
        std::optional<CalcSize> idealSize = std::nullopt;
        if (layoutProperty_->GetCalcLayoutConstraint()) {
            idealSize = layoutProperty_->GetCalcLayoutConstraint()->selfIdealSize;
        }
        constraint.ApplyAspectRatio(magicItemProperty->GetAspectRatioValue(), idealSize);
    }

    auto&& insets = layoutProperty_->GetSafeAreaInsets();
    if (insets) {
        ApplySafeArea(*insets, constraint);
    }
    geometryNode_->SetParentLayoutConstraint(constraint);
    layoutProperty_->UpdateLayoutConstraint(constraint);
}

void LayoutWrapper::ApplySafeArea(const SafeAreaInsets& insets, LayoutConstraintF& constraint)
{
    constraint.MinusPadding(
        insets.left_.Length(), insets.right_.Length(), insets.top_.Length(), insets.bottom_.Length());
}

// This will call child and self measure process.
void LayoutWrapper::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
    auto host = GetHostNode();
    CHECK_NULL_VOID(layoutProperty_);
    CHECK_NULL_VOID(geometryNode_);
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(layoutAlgorithm_);
    if (layoutAlgorithm_->SkipMeasure()) {
        LOGD("%{public}s, depth: %{public}d: the layoutAlgorithm skip measure", host->GetTag().c_str(),
            host->GetDepth());
        return;
    }

    const auto& geometryTransition = layoutProperty_->GetGeometryTransition();
    if (geometryTransition != nullptr && geometryTransition->IsRunning()) {
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

    LOGD("Measure: %{public}s, depth: %{public}d, Constraint: %{public}s", host->GetTag().c_str(), host->GetDepth(),
        layoutProperty_->GetLayoutConstraint()->ToString().c_str());

    if (isConstraintNotChanged_ && !skipMeasureContent_) {
        if (!CheckNeedForceMeasureAndLayout()) {
            LOGD("%{public}s (depth: %{public}d) skip measure content", host->GetTag().c_str(), host->GetDepth());
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

        // check aspect radio.
        auto pattern = host->GetPattern();
        if (pattern && pattern->IsNeedAdjustByAspectRatio()) {
            const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
            auto aspectRatio = magicItemProperty->GetAspectRatioValue();
            // Adjust by aspect ratio, firstly pick height based on width. It means that when width, height and
            // aspectRatio are all set, the height is not used.
            auto width = geometryNode_->GetFrameSize().Width();
            LOGD("aspect ratio affects, origin width: %{public}f, height: %{public}f", width,
                geometryNode_->GetFrameSize().Height());
            auto height = width / aspectRatio;
            LOGD("aspect ratio affects, new width: %{public}f, height: %{public}f", width, height);
            geometryNode_->SetFrameSize(SizeF({ width, height }));
        }
    }

    LOGD("on Measure Done: type: %{public}s, depth: %{public}d, Size: %{public}s", host->GetTag().c_str(),
        host->GetDepth(), geometryNode_->GetFrameSize().ToString().c_str());
}

// Called to perform layout children.
void LayoutWrapper::Layout()
{
    int64_t time = GetSysTimestamp();
    auto host = GetHostNode();
    CHECK_NULL_VOID(layoutProperty_);
    CHECK_NULL_VOID(geometryNode_);
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(layoutAlgorithm_);

    auto&& expandOpts = layoutProperty_->GetSafeAreaExpandOpts();
    if ((expandOpts && expandOpts->Expansive()) || host->IsContentRoot()) {
        // record expansive wrappers during Layout traversal to speed up SafeArea expansion
        auto pipeline = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->GetSafeAreaManager()->AddWrapper(WeakClaim(this));
    }

    if (layoutAlgorithm_->SkipLayout()) {
        LOGD(
            "%{public}s, depth: %{public}d: the layoutAlgorithm skip layout", host->GetTag().c_str(), host->GetDepth());
        return;
    }

    LOGD("On Layout begin: type: %{public}s, depth: %{public}d", host->GetTag().c_str(), host->GetDepth());

    if ((skipMeasureContent_ == true)) {
        LOGD(
            "%{public}s (depth: %{public}d) skip measure content and layout", host->GetTag().c_str(), host->GetDepth());
        LOGD("On Layout Done: type: %{public}s, depth: %{public}d, Offset: %{public}s", host->GetTag().c_str(),
            host->GetDepth(), geometryNode_->GetFrameOffset().ToString().c_str());
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
    time = GetSysTimestamp() - time;
    AddNodeFlexLayouts();
    AddNodeLayoutTime(time);
    LOGD("On Layout Done: type: %{public}s, depth: %{public}d, Offset: %{public}s", host->GetTag().c_str(),
        host->GetDepth(), geometryNode_->GetFrameOffset().ToString().c_str());
}

void LayoutWrapper::RestoreGeoState(int32_t rootDepth)
{
    std::vector<WeakPtr<FrameNode>> untraversedNodes;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    auto&& restoreNodes = manager->GetGeoRestoreNodes();

    for (auto&& nodeWk : restoreNodes) {
        auto node = nodeWk.Upgrade();
        if (!node) {
            continue;
        }
        // only restore nodes that are involved in this LayoutTask
        if (node->GetDepth() >= rootDepth) {
            auto wrapper = node->GetLayoutWrapper().Upgrade();
            if (wrapper) {
                wrapper->RestoreSelfGeoState();
            }
        } else {
            untraversedNodes.emplace_back(nodeWk);
        }
    }
    manager->SwapGeoRestoreNodes(untraversedNodes);

    manager->ResetLastKeyboardOffset();
}

void LayoutWrapper::RestoreSelfGeoState()
{
    CHECK_NULL_VOID(geometryNode_->GetPreviousState());

    auto expanded = geometryNode_->GetFrameOffset();
    geometryNode_->Restore();

    // reverse offset for children, so that they stay in the same position. But for keyboard offset, children move with
    // the parent node; that portion of the offset needs to be negated
    auto offset = geometryNode_->GetFrameOffset() - expanded;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    // parent subtracted LastKeyboardOffset in Restore(), so in reverse, children add it back
    offset.AddY(pipeline->GetSafeAreaManager()->GetLastKeyboardOffset());
    for (auto&& child : children_) {
        child->geometryNode_->SetFrameOffset(child->geometryNode_->GetFrameOffset() - offset);
    }
}

void LayoutWrapper::AvoidKeyboard()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();

    for (auto&& wrapperWk : manager->GetWrappers()) {
        auto wrapper = wrapperWk.Upgrade();
        if (!wrapper) {
            continue;
        }
        auto host = wrapper->GetHostNode();
        // apply keyboard avoidance on content rootNodes
        if (host && host->IsContentRoot()) {
            wrapper->geometryNode_->SetFrameOffset(
                wrapper->geometryNode_->GetFrameOffset() + OffsetF(0, manager->GetKeyboardOffset()));
        }
    }
    manager->SaveLastKeyboardOffset();
}

void LayoutWrapper::ExpandSafeArea()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();

    for (auto&& wrapperWk : manager->GetWrappers()) {
        auto wrapper = wrapperWk.Upgrade();
        if (wrapper && wrapper->layoutProperty_->GetSafeAreaExpandOpts()) {
            wrapper->ExpandSafeAreaInner();
        }
    }

    manager->ResetWrappers();
}

void LayoutWrapper::SaveGeoState()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto manager = pipeline->GetSafeAreaManager();
    // save geometry state before SafeArea expansion / keyboard avoidance.
    for (auto&& wrapperWk : manager->GetWrappers()) {
        auto wrapper = wrapperWk.Upgrade();
        if (wrapper) {
            wrapper->geometryNode_->Save();

            // record nodes whose geometry states need to be restored, to speed up RestoreGeoState
            auto pipeline = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            manager->AddGeoRestoreNode(wrapper->hostNode_);
        }
    }
}

void LayoutWrapper::SaveSelfGeoState() {}

void LayoutWrapper::ExpandSafeAreaInner()
{
    auto&& opts = layoutProperty_->GetSafeAreaExpandOpts();
    CHECK_NULL_VOID_NOLOG(opts->Expansive());

    // get frame in global offset
    auto frame = geometryNode_->GetFrameRect() + geometryNode_->GetParentGlobalOffset();
    LOGD("initial frame = %{public}s", frame.ToString().c_str());
    auto safeArea = opts->GetCombinedSafeArea();
    if ((opts->edges & SAFE_AREA_EDGE_START) && safeArea.left_.IsValid() && frame.Left() <= safeArea.left_.end) {
        frame.SetWidth(frame.Width() + frame.Left() - safeArea.left_.start);
        frame.SetLeft(safeArea.left_.start);
    }
    if ((opts->edges & SAFE_AREA_EDGE_TOP) && safeArea.top_.IsValid() && frame.Top() <= safeArea.top_.end) {
        frame.SetHeight(frame.Height() + frame.Top() - safeArea.top_.start);
        frame.SetTop(safeArea.top_.start);
    }

    if ((opts->edges & SAFE_AREA_EDGE_END) && safeArea.right_.IsValid() && frame.Right() >= safeArea.right_.start) {
        frame.SetWidth(frame.Width() + (safeArea.right_.end - frame.Right()));
    }
    if ((opts->edges & SAFE_AREA_EDGE_BOTTOM) && safeArea.bottom_.IsValid() &&
        frame.Bottom() >= safeArea.bottom_.start) {
        frame.SetHeight(frame.Height() + (safeArea.bottom_.end - frame.Bottom()));
    }
    LOGD("expanded frame to %{public}s", frame.ToString().c_str());

    // restore to local offset
    frame -= geometryNode_->GetParentGlobalOffset();
    if (frame != geometryNode_->GetFrameRect()) {
        auto topLeftExpansion = frame.GetOffset() - geometryNode_->GetFrameOffset();
        geometryNode_->SetFrameSize(frame.GetSize());
        geometryNode_->SetFrameOffset(frame.GetOffset());

        // adjust child offset in the opposite direction so that its absolute position remains unchanged
        for (auto&& child : GetAllChildrenWithBuild()) {
            auto geo = child->GetGeometryNode();
            geo->SetFrameOffset(geo->GetFrameOffset() - topLeftExpansion);
            geo->SetParentGlobalOffset(geo->GetParentGlobalOffset() + topLeftExpansion);
        }
    }

    if (opts->edges & SAFE_AREA_EDGE_BOTTOM && opts->type & SAFE_AREA_TYPE_KEYBOARD) {
        ExpandIntoKeyboard();
    }
}

void LayoutWrapper::ExpandIntoKeyboard()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    geometryNode_->SetFrameOffset(
        geometryNode_->GetFrameOffset() - OffsetF(0, pipeline->GetSafeAreaManager()->GetKeyboardOffset()));
    for (auto&& child : GetAllChildrenWithBuild()) {
        auto geo = child->GetGeometryNode();
        geo->SetFrameOffset(geo->GetFrameOffset() + OffsetF(0, pipeline->GetSafeAreaManager()->GetKeyboardOffset()));
        geo->SetParentGlobalOffset(
            geo->GetParentGlobalOffset() - OffsetF(0, pipeline->GetSafeAreaManager()->GetKeyboardOffset()));
    }
}

bool LayoutWrapper::SkipMeasureContent() const
{
    return (skipMeasureContent_ == true) || layoutAlgorithm_->SkipMeasure();
}

bool LayoutWrapper::CheckNeedForceMeasureAndLayout()
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

bool LayoutWrapper::CheckChildNeedForceMeasureAndLayout()
{
    return std::any_of(
        children_.begin(), children_.end(), [](const auto& item) { return item->CheckNeedForceMeasureAndLayout(); });
}

void LayoutWrapper::MountToHostOnMainThread()
{
    SwapDirtyLayoutWrapperOnMainThread();
}

void LayoutWrapper::SwapDirtyLayoutWrapperOnMainThread()
{
    if (GetHostTag() != V2::TAB_CONTENT_ITEM_ETS_TAG || isActive_) {
        for (const auto& child : children_) {
            if (!child) {
                continue;
            }
            auto node = child->GetHostNode();
            if (node && node->GetLayoutProperty()) {
                const auto& geometryTransition = node->GetLayoutProperty()->GetGeometryTransition();
                if (geometryTransition != nullptr && geometryTransition->IsNodeInAndActive(node)) {
                    continue;
                }
            }
            child->SwapDirtyLayoutWrapperOnMainThread();
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
    CHECK_NULL_VOID_NOLOG(layoutWrapperBuilder_);
    layoutWrapperBuilder_->AdjustGridOffset();
}

void LayoutWrapper::BuildLazyItem()
{
    if (!lazyBuildFunction_) {
        return;
    }
    ACE_FUNCTION_TRACE();
    lazyBuildFunction_(Claim(this));
    lazyBuildFunction_ = nullptr;
}

std::pair<int32_t, int32_t> LayoutWrapper::GetLazyBuildRange()
{
    if (layoutWrapperBuilder_) {
        auto start = layoutWrapperBuilder_->GetStartIndex();
        auto end = start + layoutWrapperBuilder_->GetTotalCount();
        return { start, end };
    }
    return { -1, 0 };
}

void LayoutWrapper::AddNodeFlexLayouts()
{
    if (!SystemProperties::IsPerformanceCheckEnabled()) {
        return;
    }
    auto host = GetHostNode();
    CHECK_NULL_VOID(host);
    auto frameNodeParent = host->GetAncestorNodeOfFrame();
    CHECK_NULL_VOID(frameNodeParent);
    if (frameNodeParent->GetTag() == V2::FLEX_ETS_TAG) {
        auto parent = host->GetParent();
        CHECK_NULL_VOID(parent);
        if (parent->GetTag() == V2::JS_VIEW_ETS_TAG) {
            parent->AddFlexLayouts();
        } else if (host->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
            auto children = host->GetChildren();
            if (!children.empty()) {
                auto begin = children.begin();
                (*begin)->AddFlexLayouts();
            }
        } else {
            host->AddFlexLayouts();
        }
    }
}

void LayoutWrapper::AddNodeLayoutTime(int64_t time)
{
    if (!SystemProperties::IsPerformanceCheckEnabled()) {
        return;
    }
    auto host = GetHostNode();
    CHECK_NULL_VOID(host);
    host->SetLayoutTime(time);
}
} // namespace OHOS::Ace::NG
