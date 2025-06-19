/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"

#include <sys/time.h>

#include "core/components_ng/pattern/picker_utils/picker_column_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double MIN_TIME = 1.0;
constexpr int32_t DISMIN = 0;
constexpr double VMIN = 0;
constexpr double PICKER_SPEED_TH = 0.25;
constexpr int32_t VELOCTY_TRANS = 1000;
constexpr float PICKER_SPRING_MASS = 1.f;
constexpr float PICKER_SPRING_STIFFNESS = 20.f;
constexpr float PICKER_SPRING_DAMPING = 10.f;
constexpr int32_t DISMAX = 30;
constexpr double VMAX = 5.0;
} // namespace

void TossAnimationController::SetStart(double y)
{
    auto weak = AceType::WeakClaim(this);
    auto ref = weak.Upgrade();
    CHECK_NULL_VOID(ref);
    auto column = AceType::DynamicCast<PickerColumnPattern>(ref->column_.Upgrade());
    CHECK_NULL_VOID(column);
    auto isTouchBreak = column->GetTouchBreakStatus();
    if (isTouchBreak == false) {
        column->SetYOffset(0.0);
    }
    if (property_) {
        StopTossAnimation();
    }
    yStart_ = y;
    timeStart_ = GetCurrentTime();
}

void TossAnimationController::SetEnd(double y)
{
    if (property_) {
        StopTossAnimation();
    }

    yEnd_ = y;
    timeEnd_ = GetCurrentTime();
}

bool TossAnimationController::Play()
{
    auto weak = AceType::WeakClaim(this);
    auto ref = weak.Upgrade();
    CHECK_NULL_RETURN(ref, false);
    auto column = AceType::DynamicCast<PickerColumnPattern>(ref->column_.Upgrade());
    CHECK_NULL_RETURN(column, false);
    auto timeDiff = timeEnd_ - timeStart_;
    if (timeDiff < MIN_TIME) {
        return false;
    }
    speed_ = column->GetMainVelocity() / VELOCTY_TRANS;
    if (std::abs(speed_) < PICKER_SPEED_TH) {
        return false;
    }
    StartSpringMotion();
    return true;
}

void TossAnimationController::StartSpringMotion()
{
    auto weak = AceType::WeakClaim(this);
    auto ref = weak.Upgrade();
    CHECK_NULL_VOID(ref);
    auto column = AceType::DynamicCast<PickerColumnPattern>(ref->column_.Upgrade());
    CHECK_NULL_VOID(column);
    auto columnNode = column->GetHost();
    CHECK_NULL_VOID(columnNode);
    auto offset = column->GetOffset();
    auto speed = column->GetMainVelocity() / VELOCTY_TRANS;
    auto renderContext = columnNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto springCurve = UpdatePlayAnimationValue();
    CHECK_NULL_VOID(springCurve);
    double midIndex = column->GetShowCount() / 2;
    auto optionProperties = column->GetMidShiftDistance();
    auto midShiftDistance =
        (speed) < 0.0 ? optionProperties[midIndex].prevDistance : optionProperties[midIndex].nextDistance;
    column->SetYLast(0.0);
    end_ = midShiftDistance * showCount_ - offset;
    AnimationOption option = AnimationOption();
    option.SetCurve(springCurve);
    CreatePropertyCallback();
    CHECK_NULL_VOID(property_);
    renderContext->AttachNodeAnimatableProperty(property_);
    property_->SetPropertyUnit(PropertyUnit::PIXEL_POSITION);
    auto finishCallback = [weak, column]() {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        column->UpdateToss(static_cast<int>(ref->end_));
        column->TossAnimationStoped();
        auto isTouchBreak = column->GetTouchBreakStatus();
        if (isTouchBreak == false) {
            column->SetTossStatus(false);
            column->SetYOffset(0.0);
            if (!NearZero(column->GetOffset()) && column->IsTossNeedToStop()) {
                column->TossStoped();
            }
        }
    };
    AnimationUtils::Animate(
        option,
        [weak]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            ref->property_->Set(ref->end_);
        },
        finishCallback);
}

void TossAnimationController::StopTossAnimation()
{
    auto weak = AceType::WeakClaim(this);
    auto ref = weak.Upgrade();
    CHECK_NULL_VOID(ref);
    CHECK_NULL_VOID(ref->property_);
    auto column = AceType::DynamicCast<PickerColumnPattern>(ref->column_.Upgrade());
    CHECK_NULL_VOID(column);
    column->SetTossStatus(false);
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(0);
    option.SetDelay(0);
    AnimationUtils::Animate(option, [weak]() {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        ref->property_->Set(0.0);
    });
}
RefPtr<Curve> TossAnimationController::UpdatePlayAnimationValue()
{
    double mass = PICKER_SPRING_MASS;
    double stiffness = PICKER_SPRING_STIFFNESS;
    double damping = PICKER_SPRING_DAMPING;
    double showCountMax = DISMAX;
    double velocityMax = VMAX;
    speed_ = std::abs(speed_) >= std::abs(velocityMax) ? std::abs(velocityMax) : std::abs(speed_);
    showCount_ = static_cast<int>(DISMIN + (showCountMax - DISMIN) * (std::abs(speed_) - VMIN) / (velocityMax - VMIN));
    return AceType::MakeRefPtr<InterpolatingSpring>(speed_, mass, stiffness, damping);
}
double TossAnimationController::GetCurrentTime() const
{
    struct timeval tv {};
    int result = gettimeofday(&tv, nullptr);
    if (result != 0) {
        return 0.0;
    }

    double sec = static_cast<double>(tv.tv_sec);
    double msec = static_cast<double>(tv.tv_usec / 1000.0); // usec / 1000 is msec
    return (sec * 1000 + msec);                             // sec * 1000 is msec
}

void TossAnimationController::CreatePropertyCallback()
{
    if (property_) {
        return;
    }
    auto weak = AceType::WeakClaim(this);
    auto ref = weak.Upgrade();
    CHECK_NULL_VOID(ref);
    auto column = AceType::DynamicCast<PickerColumnPattern>(ref->column_.Upgrade());
    CHECK_NULL_VOID(column);
    auto propertyCallback = [weak, column](float position) {
        auto isTouchBreak = column->GetTouchBreakStatus();
        if ((isTouchBreak) || (static_cast<int32_t>(position) == DISMIN)) {
            return;
        }
        column->UpdateToss(static_cast<int>(position));
        column->SetTossStatus(true);
    };
    property_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
}
} // namespace OHOS::Ace::NG
