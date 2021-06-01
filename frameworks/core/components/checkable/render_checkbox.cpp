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

#include "core/components/checkable/render_checkbox.h"

#include "base/log/event_report.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t DEFUALT_CHECKBOX_ANIMATION_DURATION = 150;
constexpr double DEFAULT_MAX_CHECKBOX_SHAPE_SCALE = 1.0;
constexpr double DEFAULT_MIN_CHECKBOX_SHAPE_SCALE = 0.0;

} // namespace

void RenderCheckbox::Update(const RefPtr<Component>& component)
{
    LOGD("update");
    RenderCheckable::Update(component);
    const auto& checkbox = AceType::DynamicCast<CheckboxComponent>(component);
    if (!checkbox) {
        LOGE("cast to checkbox component failed");
        EventReport::SendRenderException(RenderExcepType::RENDER_COMPONENT_ERR);
        return;
    }

    if (!controller_) {
        controller_ = AceType::MakeRefPtr<Animator>(GetContext());
        auto weak = AceType::WeakClaim(this);
        controller_->AddStopListener(Animator::StatusCallback([weak]() {
            auto checkBox = weak.Upgrade();
            if (checkBox) {
                checkBox->OnAnimationStop();
            }
        }));
    }

    auto theme = GetTheme<CheckboxTheme>();
    if (theme) {
        borderWidth_ = theme->GetBorderWidth();
        borderRadius_ = theme->GetBorderRadius();
        checkStroke_ = theme->GetCheckStroke();
    }
    if (checkbox->GetUpdateType() == UpdateType::ALL) {
        checked_ = checkbox->GetValue();
    }
    UpdateUIStatus();
    UpdateAccessibilityAttr();
}

void RenderCheckbox::UpdateAccessibilityAttr()
{
    auto accessibilityNode = GetAccessibilityNode().Upgrade();
    if (!accessibilityNode) {
        return;
    }
    accessibilityNode->SetCheckedState(checked_);
    if (accessibilityNode->GetClicked()) {
        accessibilityNode->SetClicked(false);
        auto context = context_.Upgrade();
        if (context) {
            AccessibilityEvent checkboxEvent;
            checkboxEvent.nodeId = accessibilityNode->GetNodeId();
            checkboxEvent.eventType = "click";
            context->SendEventToAccessibility(checkboxEvent);
        }
    }
}

void RenderCheckbox::HandleClick()
{
    UpdateAnimation();
    if (controller_) {
        controller_->Play();
    }
    if (clickEvent_) {
        clickEvent_();
    }
}

void RenderCheckbox::UpdateAnimation()
{
    if (!controller_) {
        LOGE("the controller is nullptr");
        return;
    }
    double from = 0.0;
    double to = 0.0;
    if (checked_) {
        from = DEFAULT_MAX_CHECKBOX_SHAPE_SCALE;
        to = DEFAULT_MIN_CHECKBOX_SHAPE_SCALE;
    } else {
        from = DEFAULT_MIN_CHECKBOX_SHAPE_SCALE;
        to = DEFAULT_MAX_CHECKBOX_SHAPE_SCALE;
    }

    if (translate_) {
        controller_->RemoveInterpolator(translate_);
    }
    translate_ = AceType::MakeRefPtr<CurveAnimation<double>>(from, to, Curves::FRICTION);
    auto weak = AceType::WeakClaim(this);
    translate_->AddListener(Animation<double>::ValueCallback([weak](double value) {
        auto checkBox = weak.Upgrade();
        if (checkBox) {
            checkBox->UpdateCheckBoxShape(value);
        }
    }));
    controller_->SetDuration(DEFUALT_CHECKBOX_ANIMATION_DURATION);
    controller_->AddInterpolator(translate_);
}

void RenderCheckbox::UpdateCheckBoxShape(const double value)
{
    if (value < DEFAULT_MIN_CHECKBOX_SHAPE_SCALE || value > DEFAULT_MAX_CHECKBOX_SHAPE_SCALE) {
        return;
    }
    shapeScale_ = value;
    if (!checked_) {
        uiStatus_ = UIStatus::OFF_TO_ON;
    } else {
        uiStatus_ = UIStatus::ON_TO_OFF;
    }
    MarkNeedRender();
}

void RenderCheckbox::OnAnimationStop()
{
    // after the animation stopped,we need to update the check status
    RenderCheckable::HandleClick();
    UpdateAccessibilityAttr();
}

} // namespace OHOS::Ace
