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
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper_builder.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
RefPtr<LayoutWrapper> LayoutWrapper::GetOrCreateChildByIndex(int32_t index, bool addToRenderTree)
{
    if ((index >= currentChildCount_) || (index < 0)) {
        LOGI("index is of out boundary, total count: %{public}d, target index: %{public}d", currentChildCount_, index);
        return nullptr;
    }
    auto iter = childrenMap_.find(index);
    if (iter != childrenMap_.end()) {
        if (addToRenderTree) {
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

    auto preConstraint = layoutProperty_->GetLayoutConstraint();
    auto contentConstraint = layoutProperty_->GetContentLayoutConstraint();
    layoutProperty_->BuildGridProperty(host);
    if (parentConstraint) {
        geometryNode_->SetParentLayoutConstraint(parentConstraint.value());
        layoutProperty_->UpdateLayoutConstraint(parentConstraint.value());
    } else {
        LayoutConstraintF layoutConstraint;
        layoutConstraint.percentReference.SetWidth(PipelineContext::GetCurrentRootWidth());
        layoutConstraint.percentReference.SetHeight(PipelineContext::GetCurrentRootHeight());
        layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
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
        const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
        auto hasAspectRatio = magicItemProperty ? magicItemProperty->HasAspectRatio() : false;
        if (hasAspectRatio) {
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
    auto host = GetHostNode();
    CHECK_NULL_VOID(layoutProperty_);
    CHECK_NULL_VOID(geometryNode_);
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(layoutAlgorithm_);

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
    LOGD("On Layout Done: type: %{public}s, depth: %{public}d, Offset: %{public}s", host->GetTag().c_str(),
        host->GetDepth(), geometryNode_->GetFrameOffset().ToString().c_str());
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
    for (const auto& child : children_) {
        if (child) {
            child->SwapDirtyLayoutWrapperOnMainThread();
        }
    }

    if (layoutWrapperBuilder_) {
        layoutWrapperBuilder_->SwapDirtyAndUpdateBuildCache();
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

std::pair<int32_t, int32_t> LayoutWrapper::GetLazyBuildRange()
{
    if (layoutWrapperBuilder_) {
        auto start = layoutWrapperBuilder_->GetStartIndex();
        auto end = start + layoutWrapperBuilder_->GetTotalCount();
        return { start, end };
    }
    return { -1, 0 };
}
} // namespace OHOS::Ace::NG
