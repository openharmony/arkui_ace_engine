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

#include "core/components/display/rosen_render_display.h"

#include "render_service_client/core/animation/rs_transition.h"
#include "render_service_client/core/ui/rs_node.h"

namespace OHOS::Ace {

void RosenRenderDisplay::Update(const RefPtr<Component>& component)
{
    RenderDisplay::Update(component);
    if (auto rsNode = GetRSNode()) {
        rsNode->SetAlpha(opacity_ / 255.0);
        if (pendingTransitionAppearing_ && hasAppearTransition_) {
            OnRSTransition(TransitionType::APPEARING, rsNode->GetId());
        }
    }
}

void RosenRenderDisplay::OnVisibleChanged()
{
    if (auto rsNode = GetRSNode()) {
        rsNode->SetVisible(RenderDisplay::GetVisible());
    }
}

void RosenRenderDisplay::OnOpacityAnimationCallback()
{
    double value = animatableOpacity_.GetValue();
    opacity_ = static_cast<uint8_t>(round(value * UINT8_MAX));

    if (auto rsNode = GetRSNode()) {
        rsNode->SetAlpha(value);
    }
}

void RosenRenderDisplay::Paint(RenderContext& context, const Offset& offset)
{
    LOGD("Paint");
    if (visible_ == VisibleType::VISIBLE) {
        RenderNode::Paint(context, offset);
    }
}

void RosenRenderDisplay::OnRSTransition(TransitionType type, unsigned long long rsNodeId)
{
    if (type == TransitionType::APPEARING) {
        if (pendingTransitionAppearing_ && hasAppearTransition_) {
            pendingTransitionAppearing_ = false;
            Rosen::RSNode::NotifyTransition(
                { Rosen::RSTransitionEffect(Rosen::RSTransitionEffectType::FADE_IN) }, rsNodeId);
        } else {
            pendingTransitionAppearing_ = true;
        }
    } else if (type == TransitionType::DISAPPEARING && hasDisappearTransition_) {
        Rosen::RSNode::NotifyTransition(
            { Rosen::RSTransitionEffect(Rosen::RSTransitionEffectType::FADE_OUT) }, rsNodeId);
    }
}

void RosenRenderDisplay::ClearRenderObject()
{
    RenderDisplay::ClearRenderObject();
    pendingTransitionAppearing_ = false;
}
} // namespace OHOS::Ace