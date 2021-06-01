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

#include "core/components/toggle/render_toggle.h"

#include "base/log/log.h"
#include "core/components/common/properties/alignment.h"
#include "core/event/ace_event_helper.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t HOVER_ANIMATION_DURATION = 250;

} // namespace

RenderToggle::RenderToggle()
{
    clickRecognizer_ = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer_->SetOnClick([wp = AceType::WeakClaim(this)](const ClickInfo&) {
        auto toggle = wp.Upgrade();
        if (toggle) {
            toggle->HandleClickEvent();
        }
    });

    auto wp = AceType::WeakClaim(this);
    touchRecognizer_ = AceType::MakeRefPtr<RawRecognizer>();
    touchRecognizer_->SetOnTouchDown([wp](const TouchEventInfo&) {
        auto toggle = wp.Upgrade();
        if (toggle) {
            toggle->HandleTouchEvent(true);
        }
    });
    touchRecognizer_->SetOnTouchUp([wp](const TouchEventInfo&) {
        auto toggle = wp.Upgrade();
        if (toggle) {
            toggle->HandleTouchEvent(false);
        }
    });
    touchRecognizer_->SetOnTouchMove([wp](const TouchEventInfo& info) {
        auto toggle = wp.Upgrade();
        if (toggle) {
            toggle->HandleMoveEvent(info);
        }
    });
}

void RenderToggle::HandleClickEvent()
{
    auto toggle = toggleComponent_.Upgrade();
    if (!toggle) {
        LOGE("fail to perform click due to toggle is null");
        return;
    }
    if (onClick_) {
        onClick_();
    }
    auto checkValue = toggle->GetCheckedState();
    toggle->SetCheckedState(!checkValue);
    MarkNeedRender();
    std::string checked = (!checkValue) ? "true" : "false";
    std::string result = std::string(R"("change",{"checked":)").append(checked.append("},null"));
    if (onChange_) {
        onChange_(result);
    }
}

void RenderToggle::HandleTouchEvent(bool touched)
{
    isPressed_ = touched;
    if (isPressed_) {
        isMoveEventValid_ = true;
    }
    if (isMoveEventValid_) {
        MarkNeedRender();
    }
}

void RenderToggle::HandleMoveEvent(const TouchEventInfo& info)
{
    if (!isMoveEventValid_ || info.GetTouches().empty()) {
        return;
    }
    const auto& locationInfo = info.GetTouches().front();
    double moveX = locationInfo.GetLocalLocation().GetX();
    double moveY = locationInfo.GetLocalLocation().GetY();
    if ((LessNotEqual(moveX, 0.0) || GreatNotEqual(moveX, toggleSize_.Width()))
        || (LessNotEqual(moveY, 0.0) || GreatNotEqual(moveY, toggleSize_.Height()))) {
        isPressed_ = false;
        isMoveEventValid_ = false;
        MarkNeedRender();
    }
}

void RenderToggle::OnTouchTestHit(
    const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result)
{
    if ((!touchRecognizer_) || (!clickRecognizer_)) {
        return;
    }
    touchRecognizer_->SetCoordinateOffset(coordinateOffset);
    result.emplace_back(touchRecognizer_);
    result.emplace_back(clickRecognizer_);
}

void RenderToggle::UpdateFocusAnimation()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    double radius = toggleSize_.Height() / 2.0;
    context->ShowFocusAnimation(RRect::MakeRRect(Rect(Offset(0, 0), toggleSize_), Radius(radius)),
        Color(), GetGlobalOffset());
    context->ShowShadow( RRect::MakeRRect(Rect(Offset(0, 0), toggleSize_), Radius(radius)), GetGlobalOffset());
}

void RenderToggle::OnMouseHoverEnterTest()
{
    ResetController(hoverControllerExit_);
    if (!hoverControllerEnter_) {
        hoverControllerEnter_ = AceType::MakeRefPtr<Animator>(context_);
    }
    scaleAnimationEnter_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    CreateFloatAnimation(scaleAnimationEnter_, 1.0, 1.05);
    hoverControllerEnter_->AddInterpolator(scaleAnimationEnter_);
    hoverControllerEnter_->SetDuration(HOVER_ANIMATION_DURATION);
    hoverControllerEnter_->Play();
    hoverControllerEnter_->SetFillMode(FillMode::FORWARDS);
}

void RenderToggle::OnMouseHoverExitTest()
{
    ResetController(hoverControllerEnter_);
    if (!hoverControllerExit_) {
        hoverControllerExit_ = AceType::MakeRefPtr<Animator>(context_);
    }
    scaleAnimationExit_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    auto begin = scale_;
    CreateFloatAnimation(scaleAnimationExit_, begin, 1.0);
    hoverControllerExit_->AddInterpolator(scaleAnimationExit_);
    hoverControllerExit_->SetDuration(HOVER_ANIMATION_DURATION);
    hoverControllerExit_->Play();
    hoverControllerExit_->SetFillMode(FillMode::FORWARDS);
}

void RenderToggle::OnMouseClickDownAnimation()
{
    ResetController(clickControllerUp_);
    if (!clickControllerDown_) {
        clickControllerDown_ = AceType::MakeRefPtr<Animator>(context_);
    }
    scaleAnimationDown_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    auto begin = scale_;
    CreateFloatAnimation(scaleAnimationDown_, begin, 1.0);
    clickControllerDown_->AddInterpolator(scaleAnimationDown_);
    clickControllerDown_->SetDuration(HOVER_ANIMATION_DURATION);
    clickControllerDown_->Play();
    clickControllerDown_->SetFillMode(FillMode::FORWARDS);
}

void RenderToggle::OnMouseClickUpAnimation()
{
    ResetController(clickControllerDown_);
    if (!clickControllerUp_) {
        clickControllerUp_ = AceType::MakeRefPtr<Animator>(context_);
    }
    scaleAnimationUp_ = AceType::MakeRefPtr<KeyframeAnimation<float>>();
    auto begin = scale_;
    CreateFloatAnimation(scaleAnimationUp_, begin, 1.05);
    clickControllerUp_->AddInterpolator(scaleAnimationUp_);
    clickControllerUp_->SetDuration(HOVER_ANIMATION_DURATION);
    clickControllerUp_->Play();
    clickControllerUp_->SetFillMode(FillMode::FORWARDS);
}

void RenderToggle::CreateFloatAnimation(RefPtr<KeyframeAnimation<float>>& floatAnimation, float beginValue,
    float endValue)
{
    if (!floatAnimation) {
        return;
    }
    auto keyframeBegin = AceType::MakeRefPtr<Keyframe<float>>(0.0, beginValue);
    auto keyframeEnd = AceType::MakeRefPtr<Keyframe<float>>(1.0, endValue);
    floatAnimation->AddKeyframe(keyframeBegin);
    floatAnimation->AddKeyframe(keyframeEnd);
    floatAnimation->AddListener([weakToggle = AceType::WeakClaim(this)](float value) {
        auto toggle = weakToggle.Upgrade();
        if (toggle) {
            toggle->scale_ = value;
            toggle->MarkNeedRender();
        }
    });
}

void RenderToggle::ResetController(RefPtr<Animator>& controller)
{
    if (controller) {
        if (!controller->IsStopped()) {
            controller->Stop();
        }
        controller->ClearInterpolators();
    }
}

void RenderToggle::Update(const RefPtr<Component>& component)
{
    auto toggle = AceType::DynamicCast<ToggleComponent>(component);
    if (!toggle) {
        LOGE("Update error, toggle component is null");
        return;
    }
    toggleComponent_ = toggle;
    widthDefined_ = !NearZero(toggle->GetWidth().Value());
    onClick_ = AceAsyncEvent<void()>::Create(toggle->GetClickEvent(), context_);
    onChange_ = AceAsyncEvent<void(const std::string)>::Create(toggle->GetChangeEvent(), context_);
    MarkNeedLayout();
}

void RenderToggle::PerformLayout()
{
    auto toggle = toggleComponent_.Upgrade();
    if (!toggle) {
        LOGE("fail to perform layout due to toggle is null");
        return;
    }
    toggleSize_ = Size(NormalizeToPx(toggle->GetWidth()), NormalizeToPx(toggle->GetHeight()));
    Measure();
    LayoutParam innerLayoutParam;
    double maxWidth = widthDefined_ ? toggleSize_.Width() : GetLayoutParam().GetMaxSize().Width();
    innerLayoutParam.SetMaxSize(Size(maxWidth, toggleSize_.Height()));
    RefPtr<RenderNode> child;
    Size childrenSize;
    if (!GetChildren().empty()) {
        child = GetChildren().front();
        child->Layout(innerLayoutParam);
        childrenSize.SetWidth(child->GetLayoutSize().Width());
        childrenSize.SetHeight(child->GetLayoutSize().Height());
    }
    Size layoutSize = widthDefined_ ? toggleSize_ : Size(childrenSize.Width(), toggleSize_.Height());
    layoutSize = GetLayoutParam().Constrain(layoutSize);
    SetLayoutSize(layoutSize);
    toggleSize_ = GetLayoutSize();
    if (child) {
        child->SetPosition(Alignment::GetAlignPosition(GetLayoutSize(), child->GetLayoutSize(), Alignment::CENTER));
    }
}

} // namespace OHOS::Ace
