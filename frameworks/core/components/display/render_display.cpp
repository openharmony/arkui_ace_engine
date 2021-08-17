/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/display/render_display.h"

#include "base/log/dump_log.h"
#include "base/log/event_report.h"
#include "core/animation/curve_animation.h"

namespace OHOS::Ace {

void RenderDisplay::Update(const RefPtr<Component>& component)
{
    const RefPtr<DisplayComponent> display = AceType::DynamicCast<DisplayComponent>(component);
    if (!display) {
        LOGE("RenderDisplay update with nullptr");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }
    displayComponent_ = display;
    UpdateVisibleType(display->GetVisible());
    transitionOpacity_ = display->GetOpacity();
    disappearingOpacity_ = display->GetDisappearingOpacity();
    appearingOpacity_ = display->GetAppearingOpacity();
    hasDisappearTransition_ = display->HasDisappearTransition();
    if (pendingAppearing_) {
        animatableOpacity_.MoveTo(appearingOpacity_);
        // appearing transition do not need stop callback anymore.
        animatableOpacity_.SetAnimationStopCallback(nullptr);
        animatableOpacity_ = AnimatableDouble(display->GetOpacity());
        pendingAppearing_ = false;
        inTransition_ = true;
    } else {
        animatableOpacity_ = AnimatableDouble(display->GetOpacity(), display->GetOpacityAnimationOption());
        inTransition_ = false;
    }
    double opacity = std::min(std::max(animatableOpacity_.GetValue(), 0.0), 1.0);
    if (disableLayer_ != display->IsDisableLayer()) {
        // recover opacity in child
        UpdateOpacity(UINT8_MAX);
        disableLayer_ = display->IsDisableLayer();
    }
    opacity_ = static_cast<uint8_t>(round(opacity * UINT8_MAX));

    SetShadow(display->GetShadow());
    MarkNeedLayout();
}

void RenderDisplay::PerformLayout()
{
    pendingAppearing_ = false;
    LayoutParam layoutParam = GetLayoutParam();
    if (visible_ == VisibleType::GONE) {
        layoutParam.SetMinSize(Size());
        layoutParam.SetMaxSize(Size());
        SetVisible(false);
    }
    Size childSize;
    if (!GetChildren().empty()) {
        GetChildren().front()->Layout(layoutParam);
        childSize = GetChildren().front()->GetLayoutSize();
    }
    SetLayoutSize(childSize);
}

void RenderDisplay::GetOpacityCallbacks()
{
    opacityCallbacks_.clear();
    if (!disableLayer_) {
        return;
    }
    GetDomOpacityCallbacks(GetNodeId(), opacityCallbacks_);
}

void RenderDisplay::Dump()
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        DumpLog::GetInstance().AddDesc(std::string("Display: ").append(visible_ == VisibleType::VISIBLE ? "visible" :
            visible_ == VisibleType::INVISIBLE ? "invisible" : "gone"));
        DumpLog::GetInstance().AddDesc(std::string("Opacity: ").append(std::to_string(animatableOpacity_.GetValue())));
    }
}

bool RenderDisplay::GetVisible() const
{
    return RenderNode::GetVisible() && visible_ == VisibleType::VISIBLE;
}

void RenderDisplay::OnOpacityDisappearingCallback()
{
    LOGD("OnOpacityDisappearingCallback");
    RefPtr<RenderNode> child = AceType::Claim(this);
    while (child && !child->IsDisappearing()) {
        child = child->GetParent().Upgrade();
    }
    if (!child) {
        return;
    }
    auto parent = child->GetParent().Upgrade();
    if (parent) {
        parent->ClearDisappearingNode(child);
    }
}

void RenderDisplay::OnOpacityAnimationCallback()
{
    double value = animatableOpacity_.GetValue();
    opacity_ = static_cast<uint8_t>(round(value * UINT8_MAX));
    MarkNeedLayout();
    if (inTransition_) {
        MarkNeedRender();
    }
}

bool RenderDisplay::HasDisappearingTransition(int32_t nodeId)
{
    return hasDisappearTransition_ || RenderNode::HasDisappearingTransition(nodeId);
}

void RenderDisplay::OnTransition(TransitionType type, int32_t id)
{
    LOGD("OnTransition. type: %{public}d, id: %{public}d", type, id);
    if (type == TransitionType::APPEARING) {
        pendingAppearing_ = true;
    } else if (type == TransitionType::DISAPPEARING) {
        animatableOpacity_.SetAnimationStopCallback(std::bind(&RenderDisplay::OnOpacityDisappearingCallback, this));
        animatableOpacity_ = AnimatableDouble(disappearingOpacity_);
        inTransition_ = true;
    }
}

void RenderDisplay::ClearRenderObject()
{
    RenderNode::ClearRenderObject();
    animatableOpacity_ = 1.0;
    appearingOpacity_ = 0.0;
    disappearingOpacity_ = 0.0;
    inTransition_ = false;
}

} // namespace OHOS::Ace
