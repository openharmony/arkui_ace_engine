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

#include "base/log/ace_trace.h"
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

void LayoutWrapper::ResetHostNode()
{
    hostNode_.Reset();
}

RefPtr<FrameNode> LayoutWrapper::GetHostNode() const
{
    return hostNode_.Upgrade();
}

std::string LayoutWrapper::GetHostTag() const
{
    auto host = GetHostNode();
    if (host) {
        return host->GetTag();
    }
    return "";
}

// This will call child and self measure process.
void LayoutWrapper::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
    LOGD("%s, do Measure, child size: %d", OHOS::Ace::DEVTAG.c_str(), childrenMap_.size());
    if (!layoutAlgorithm_ || layoutAlgorithm_->SkipMeasure()) {
        LOGD("the layoutAlgorithm skip measure");
        return;
    }
    auto host = GetHostNode();
    if (!layoutProperty_ || !geometryNode_ || !host) {
        LOGE("Measure failed: the layoutProperty_ or geometryNode_ or host is nullptr");
        return;
    }

    if (parentConstraint == geometryNode_->GetParentLayoutConstraint()) {
        isContraintNoChanged_ = true;
    }

    if (parentConstraint) {
        geometryNode_->SetParentLayoutConstraint(parentConstraint.value());
        layoutProperty_->UpdateGridConstraint(GetHostNode());
        layoutProperty_->UpdateLayoutConstraint(parentConstraint.value());
    } else {
        LayoutConstraintF layoutConstraint;
        layoutConstraint.percentReference.SetWidth(PipelineContext::GetCurrentRootWidth());
        layoutConstraint.percentReference.SetHeight(PipelineContext::GetCurrentRootHeight());
        layoutProperty_->UpdateGridConstraint(GetHostNode());
        layoutProperty_->UpdateLayoutConstraint(layoutConstraint);
    }
    layoutProperty_->UpdateContentConstraint();
    geometryNode_->UpdateMargin(layoutProperty_->CreateMargin());

    LOGD("Measure: %{public}s, Constraint: %{public}s", GetHostTag().c_str(),
        layoutProperty_->GetLayoutConstraint()->ToString().c_str());

    if (isContraintNoChanged_ && !CheckNeedMeasure(layoutProperty_->GetPropertyChangeFlag())) {
        LOGD("%{public}s skip measure content, constrain flag: %{public}d, measure flag: %{public}d",
            host->GetTag().c_str(), isContraintNoChanged_, layoutProperty_->GetPropertyChangeFlag());
    } else {
        auto size = layoutAlgorithm_->MeasureContent(layoutProperty_->CreateContentConstraint(), this);
        measureContent_ = true;
        if (size.has_value()) {
            geometryNode_->SetContentSize(size.value());
        }
    }

    layoutAlgorithm_->Measure(this);

    // check aspect radio.
    const auto& magicItemProperty = layoutProperty_->GetMagicItemProperty();
    auto hasAspectRatio = magicItemProperty ? magicItemProperty->HasAspectRatio() : false;
    if (hasAspectRatio) {
        auto aspectRatio = magicItemProperty->GetAspectRatioValue();
        // Adjust by aspect ratio, firstly pick height based on width. It means that when width, height and aspectRatio
        // are all set, the height is not used.
        auto width = geometryNode_->GetFrameSize().Width();
        LOGD("aspect ratio affects, origin width: %{public}f, height: %{public}f", width,
            geometryNode_->GetFrameSize().Height());
        auto height = width / aspectRatio;
        LOGD("aspect ratio affects, new width: %{public}f, height: %{public}f", width, height);
        geometryNode_->SetFrameSize(SizeF({ width, height }));
    }

    LOGD("on Measure Done: %{public}s, Size: %{public}s", GetHostTag().c_str(),
        geometryNode_->GetFrameSize().ToString().c_str());
}

// Called to perform layout children.
void LayoutWrapper::Layout()
{
    LOGD("%s, do Layout", OHOS::Ace::DEVTAG.c_str());
    if (!layoutAlgorithm_ || layoutAlgorithm_->SkipLayout()) {
        LOGD("the layoutAlgorithm skip layout");
        return;
    }
    auto host = GetHostNode();
    if (!layoutProperty_ || !geometryNode_ || !host) {
        LOGE("Layout failed: the layoutProperty_ or geometryNode_ or host or frameNode is nullptr");
        return;
    }

    LOGD("On Layout begin: %{public}s", GetHostTag().c_str());
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

    // TODO: add grid container offset prop.

    layoutAlgorithm_->Layout(this);
    LOGD("On Layout Done: %{public}s, Offset: %{public}s", GetHostTag().c_str(),
        geometryNode_->GetFrameOffset().ToString().c_str());
}

bool LayoutWrapper::SkipMeasureContent() const
{
    return !measureContent_;
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
    if (!host) {
        LOGE("the host is nullptr");
        return;
    }
    host->SwapDirtyLayoutWrapperOnMainThread(Claim(this));
}
} // namespace OHOS::Ace::NG
