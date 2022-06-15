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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
void LayoutWrapper::Reset()
{
    children_.clear();
    geometryNode_.Reset();
    layoutProperty_.Reset();
    layoutAlgorithm_.Reset();
}

void LayoutWrapper::AddChild(const RefPtr<LayoutWrapper>& child, int32_t slot)
{
    if (!child) {
        LOGW("Child MUST NOT be nullptr");
        return;
    }

    auto it = std::find(children_.begin(), children_.end(), child);
    if (it != children_.end()) {
        LOGW("frame node exist AddChild failed");
        return;
    }

    auto pos = children_.begin();
    std::advance(pos, slot);
    children_.insert(pos, child);
}

void LayoutWrapper::RemoveChild(const RefPtr<LayoutWrapper>& child)
{
    if (!child) {
        LOGW("Child MUST NOT be nullptr");
        return;
    }

    // ClearChildren() before RemoveChild() also need to NotifyTransition().
    if (!children_.empty()) {
        auto it = std::find(children_.begin(), children_.end(), child);
        if (it == children_.end()) {
            LOGW("Child is not in  render node");
            return;
        }
        children_.erase(it);
    }
}

void LayoutWrapper::ClearChildren()
{
    children_.clear();
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
    if (!layoutAlgorithm_ || layoutAlgorithm_->SkipMeasure()) {
        LOGD("the layoutAlgorithm skip measure");
        return;
    }
    if (!layoutProperty_ || !geometryNode_) {
        LOGE("Measure failed: the layoutAlgorithm_ or layoutProperty_ or geometryNode_ is nullptr");
        return;
    }
    layoutProperty_->UpdateLayoutConstraint(parentConstraint.value_or(LayoutConstraintF()));
    layoutProperty_->UpdateContentConstraint();
    LOGD("Measure: %{public}s, Constraint: %{public}s", GetHostTag().c_str(),
        layoutProperty_->GetLayoutConstraint()->ToString().c_str());
    auto size = layoutAlgorithm_->MeasureContent(layoutProperty_->GetContentLayoutConstraint().value(), this);
    if (size.has_value()) {
        geometryNode_->SetContentSize(size.value());
    }
    layoutAlgorithm_->Measure(this);
    LOGD("on Measure Done: %{public}s, Size: %{public}s", GetHostTag().c_str(),
        geometryNode_->GetFrameSize().ToString().c_str());
}

// Called to perform layout children.
void LayoutWrapper::Layout(const std::optional<OffsetF>& parentGlobalOffset)
{
    if (!layoutAlgorithm_ || layoutAlgorithm_->SkipLayout()) {
        LOGD("the layoutAlgorithm skip layout");
        return;
    }
    if (!layoutProperty_ || !geometryNode_) {
        LOGE("Layout failed: the layoutAlgorithm_ or layoutProperty_ or geometryNode_ or frameNode is nullptr");
        return;
    }
    geometryNode_->SetParentGlobalOffset(parentGlobalOffset.value_or(OffsetF(0, 0)));
    layoutAlgorithm_->Layout(this);
    LOGD("On Layout Done: %{public}s, Offset: %{public}s", GetHostTag().c_str(),
        geometryNode_->GetFrameOffset().ToString().c_str());
}

void LayoutWrapper::MountToHostOnUiThread()
{
    SwapDirtyLayoutWrapperFromUiThread();
    UiTaskScheduler::GetInstance()->FlushRenderTaskInUiThread();
}

void LayoutWrapper::SwapDirtyLayoutWrapperFromUiThread()
{
    auto host = hostNode_.Upgrade();
    if (!host) {
        LOGE("the host is nullptr");
        return;
    }
    host->SwapDirtyLayoutWrapperFromUiThread(Claim(this));

    for (const auto& child : children_) {
        child->SwapDirtyLayoutWrapperFromUiThread();
    }
}
} // namespace OHOS::Ace::NG
