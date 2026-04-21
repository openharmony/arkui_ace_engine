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

#include "core/components_ng/pattern/text/text_free_scroll_controller.h"

#include "core/components_ng/pattern/scrollable/scrollable_animation_consts.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "core/components_ng/pattern/scrollable/scrollable.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float START_FRICTION_VELOCITY_THRESHOLD = 240.0f;
constexpr float FRICTION_VELOCITY_THRESHOLD = 120.0f;
constexpr uint32_t MAX_VSYNC_DIFF_TIME = 100 * 1000 * 1000; // 100ms
constexpr uint32_t MIN_VSYNC_DIFF_TIME = 1000 * 1000;       // 1ms
constexpr uint64_t MILLOS_PER_NANO_SECONDS = 1000 * 1000 * 1000;

float GetFriction(const WeakPtr<ScrollablePattern>& pattern)
{
    auto scrollablePattern = pattern.Upgrade();
    CHECK_NULL_RETURN(scrollablePattern, 0.0f);
    auto friction = static_cast<float>(scrollablePattern->GetFriction());
    if (NonPositive(friction)) {
        auto* ctx = scrollablePattern->GetContext();
        CHECK_NULL_RETURN(ctx, 0.0f);
        auto theme = ctx->GetTheme<ScrollableTheme>();
        CHECK_NULL_RETURN(theme, 0.0f);
        friction = theme->GetFriction();
    }
    return friction * -FRICTION_SCALE;
}

AnimationOption CreateSpringOption(float friction)
{
    if (NearZero(friction)) {
        return {};
    }
    const auto curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(fabs(2 * ACE_PI / friction), 1.0f, 0.0f);
    AnimationOption option(curve, CUSTOM_SPRING_ANIMATION_DURATION);
    option.SetFinishCallbackType(FinishCallbackType::LOGICALLY);
    return option;
}
} // namespace

TextFreeScrollController::TextFreeScrollController(const WeakPtr<ScrollablePattern>& hostPattern)
    : pattern_(hostPattern)
{
    offsetX_ = MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [weak = WeakClaim(this)](const float& newOffsetX) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandleOffsetUpdate(newOffsetX, false);
        }
    });
    offsetY_ = MakeRefPtr<NodeAnimatablePropertyFloat>(0.0f, [weak = WeakClaim(this)](const float& newOffsetY) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandleOffsetUpdate(newOffsetY, true);
        }
    });
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    weakHost_ = host;
    context_ = host->GetContextRefPtr();
    auto renderCtx = host->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    renderCtx->AttachNodeAnimatableProperty(offsetX_);
    renderCtx->AttachNodeAnimatableProperty(offsetY_);

    InitializePanRecognizer();
    InitializeTouchEvent();
}

TextFreeScrollController::~TextFreeScrollController()
{
    auto host = weakHost_.Upgrade();
    CHECK_NULL_VOID(host);
    if (freeTouch_) {
        auto hub = host->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(hub);
        hub->RemoveTouchEvent(freeTouch_);
    }
    auto renderCtx = host->GetRenderContext();
    CHECK_NULL_VOID(renderCtx);
    if (offsetX_) {
        renderCtx->DetachNodeAnimatableProperty(offsetX_);
    }
    if (offsetY_) {
        renderCtx->DetachNodeAnimatableProperty(offsetY_);
    }
}

void TextFreeScrollController::InitializePanRecognizer()
{
    auto verticalPanRecognizer = CreatePanRecognizer(PanDirection::VERTICAL);
    auto horizontalPanRecognizer = CreatePanRecognizer(PanDirection::HORIZONTAL);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers;
    recognizers.emplace_back(verticalPanRecognizer);
    recognizers.emplace_back(horizontalPanRecognizer);
    auto groupRecognizer = MakeRefPtr<ExclusiveRecognizer>(recognizers);
    groupRecognizer->RemainChildOnResetStatus();
    recognizer_ = groupRecognizer;
}

RefPtr<PanRecognizer> TextFreeScrollController::CreatePanRecognizer(uint32_t direction)
{
    const double distance = SystemProperties::GetScrollableDistance();
    PanDistanceMap distanceMap;
    if (Positive(distance)) {
        distanceMap[SourceTool::UNKNOWN] = distance;
    } else {
        distanceMap[SourceTool::UNKNOWN] = DEFAULT_PAN_DISTANCE.ConvertToPx();
        distanceMap[SourceTool::PEN] = DEFAULT_PEN_PAN_DISTANCE.ConvertToPx();
    }
    PanDirection panDirection { .type = direction };
    auto panRecognizer = MakeRefPtr<PanRecognizer>(DEFAULT_PAN_FINGER, panDirection, distanceMap);
    bool isVertical = direction == PanDirection::VERTICAL;
    panRecognizer->SetOnActionStart([weak = WeakClaim(this), isVertical](const GestureEvent& event) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandlePanStart(event, isVertical);
        }
    });
    panRecognizer->SetOnActionUpdate([weak = WeakClaim(this), isVertical](const GestureEvent& event) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandlePanUpdate(event, isVertical);
        }
    });
    const auto endCallback = [weak = WeakClaim(this), isVertical](const GestureEvent& event) {
        auto controller = weak.Upgrade();
        if (controller) {
            controller->HandlePanEndOrCancel(event, isVertical);
        }
    };
    panRecognizer->SetOnActionEnd(endCallback);
    panRecognizer->SetOnActionCancel(endCallback);
    panRecognizer->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    panRecognizer->SetIsSystemGesture(true);
    panRecognizer->SetIsAllowMouse(false);
    panRecognizer->SetSysGestureJudge(
        [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
            if (gestureInfo->GetInputEventType() == InputEventType::AXIS &&
                (info->IsKeyPressed(KeyCode::KEY_CTRL_LEFT) || info->IsKeyPressed(KeyCode::KEY_CTRL_RIGHT))) {
                return GestureJudgeResult::REJECT;
            }
            return GestureJudgeResult::CONTINUE;
        });
    return panRecognizer;
}

void TextFreeScrollController::HandlePanStart(const GestureEvent& event, bool isVertical)
{
    StopScrollAnimation(!isVertical);
    UpdateState(isVertical, State::DRAG);
    FireOnScrollUpdate(0, SCROLL_FROM_START, isVertical);
    if (wheelAnimator_ && !Scrollable::IsMouseWheelScroll(event)) {
        wheelAnimator_->StopAxisAnimation();
    }
}

void TextFreeScrollController::HandlePanUpdate(const GestureEvent& event, bool isVertical)
{
    float delta =
        isVertical ? static_cast<float>(event.GetDelta().GetY()) : static_cast<float>(event.GetDelta().GetX());
    if (Scrollable::IsMouseWheelScroll(event)) {
        TriggerMouseAnimation(delta, isVertical);
        return;
    }
    size_t fingers = event.GetFingerList().size();
    if (fingers > 1) {
        delta /= fingers;
    }
    FireOnScrollUpdate(delta, 0, isVertical);
}

void TextFreeScrollController::HandlePanEndOrCancel(const GestureEvent& event, bool isVertical)
{
    UpdateState(isVertical, State::IDLE);
    if (Scrollable::IsMouseWheelScroll(event)) {
        FireOnScrollEnd(isVertical);
        return;
    }
    const auto& src = event.GetVelocity();
    Fling(isVertical ? static_cast<float>(src.GetVelocityY()) : static_cast<float>(src.GetVelocityX()), isVertical);
    if (IsEqualState(isVertical, State::IDLE)) {
        FireOnScrollEnd(isVertical);
    }
}

void TextFreeScrollController::Fling(float velocity, bool isVertical)
{
    if (NearZero(velocity, START_FRICTION_VELOCITY_THRESHOLD)) {
        return;
    }
    const float friction = GetFriction(pattern_);
    if (NearZero(friction)) {
        return;
    }
    auto offset = isVertical ? offsetY_ : offsetX_;
    float mainPos = isVertical ? currentOffset_.GetY() : currentOffset_.GetX();
    float finalPos = mainPos + velocity * FLING_SCALE_K / friction;
    if (finalPos == offset->Get()) {
        return;
    }
    offset->Set(mainPos);
    lastPosition_ = mainPos;
    flingFinalPos_ = finalPos;
    offset->SetThresholdType(ThresholdType::LAYOUT);
    offset->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    offset->AnimateWithVelocity(CreateSpringOption(friction), finalPos, velocity,
        [weak = WeakClaim(this), isVertical, id = Container::CurrentId()]() {
            ContainerScope scope(id);
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            self->HandleAnimationEnd(isVertical);
        });
    UpdateState(isVertical, State::FLING);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    context->RequestFrame();
    lastVsyncTime_ = context->GetVsyncTime();
}

void TextFreeScrollController::HandleOffsetUpdate(float newValue, bool isVertical)
{
    if (IsEqualState(isVertical, State::FLING)) {
        if (NearEqual(flingFinalPos_, newValue, 1.0f)) {
            StopScrollAnimation(isVertical);
        }
        auto context = context_.Upgrade();
        CHECK_NULL_VOID(context);
        uint64_t currentVsync = context->GetVsyncTime();
        uint64_t diff = currentVsync - lastVsyncTime_;
        if (diff < MAX_VSYNC_DIFF_TIME && diff > MIN_VSYNC_DIFF_TIME) {
            auto velocity = (newValue - lastPosition_) / diff * MILLOS_PER_NANO_SECONDS;
            if (NearZero(velocity, FRICTION_VELOCITY_THRESHOLD)) {
                StopScrollAnimation(isVertical);
            }
        }
        lastVsyncTime_ = currentVsync;
        lastPosition_ = newValue;
    }
    if (IsEqualState(isVertical, State::FLING) || IsEqualState(isVertical, State::WHEEL)) {
        float current = isVertical ? currentOffset_.GetY() : currentOffset_.GetX();
        FireOnScrollUpdate(newValue - current, 0, isVertical);
    }
}

void TextFreeScrollController::HandleAnimationEnd(bool isVertical)
{
    UpdateState(isVertical, State::IDLE);
    FireOnScrollEnd(isVertical);
}

void TextFreeScrollController::InitializeTouchEvent()
{
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto controller = weak.Upgrade();
        CHECK_NULL_VOID(controller);
        switch (info.GetTouches().front().GetTouchType()) {
            case TouchType::DOWN:
                controller->HandleTouchDown();
                break;
            default:
                break;
        }
    };
    freeTouch_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    auto host = weakHost_.Upgrade();
    CHECK_NULL_VOID(host);
    auto hub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(hub);
    hub->AddTouchEvent(freeTouch_);
}

void TextFreeScrollController::HandleTouchDown()
{
    if (IsEqualState(true, State::DRAG) || IsEqualState(false, State::DRAG)) {
        return;
    }
    StopAllScrollAnimation();
}

void TextFreeScrollController::StopAllScrollAnimation()
{
    StopScrollAnimation(true);
    StopScrollAnimation(false);
}

void TextFreeScrollController::StopScrollAnimation(bool isVertical)
{
    if (IsEqualState(isVertical, State::FLING)) {
        UpdateState(isVertical, State::IDLE);
        AnimationOption option;
        option.SetCurve(Curves::EASE);
        option.SetDuration(0);
        AnimationUtils::StartAnimation(
            option,
            [weak = WeakClaim(this), isVertical]() {
                auto controller = weak.Upgrade();
                CHECK_NULL_VOID(controller);
                if (isVertical) {
                    controller->offsetY_->Set(controller->offsetY_->Get());
                } else {
                    controller->offsetX_->Set(controller->offsetX_->Get());
                }
            },
            nullptr);
    }
}

void TextFreeScrollController::HandleMouseAnimationFrame(float newOffset)
{
    if (mouseWheelScrollIsVertical_) {
        offsetY_->Set(newOffset);
    } else {
        offsetX_->Set(newOffset);
    }
}

void TextFreeScrollController::TriggerMouseAnimation(float delta, bool isVertical)
{
    mouseWheelScrollIsVertical_ = isVertical;
    if (!wheelAnimator_) {
        wheelAnimator_ = MakeRefPtr<AxisAnimator>(
            [weak = WeakClaim(this)](float newOffset) {
                auto controller = weak.Upgrade();
                CHECK_NULL_VOID(controller);
                controller->HandleMouseAnimationFrame(newOffset);
            },
            nullptr, nullptr);
        auto pipelineBase = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipelineBase);
        wheelAnimator_->Initialize(WeakClaim(AceType::RawPtr(pipelineBase)));
    }
    wheelAnimator_->OnAxis(delta, isVertical ? currentOffset_.GetY() : currentOffset_.GetX());
    UpdateState(isVertical, State::WHEEL);
}

void TextFreeScrollController::FireOnScrollUpdate(float offset, int32_t source, bool isVertical)
{
    if (freeScrollCallback_) {
        freeScrollCallback_(offset, source, isVertical);
    }
}

void TextFreeScrollController::FireOnScrollEnd(bool isVertical) const
{
    if (freeEndScrollCallback_) {
        freeEndScrollCallback_(isVertical);
    }
}
} // namespace OHOS::Ace::NG
