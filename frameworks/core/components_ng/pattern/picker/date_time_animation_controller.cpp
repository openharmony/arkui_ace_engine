/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/layout/layout_property.h"
#include "date_time_animation_controller.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CHILD_SIZE = 3;
constexpr double SEMI_CIRCLE_ANGEL = 180;
constexpr double OPACITY_DELAY = 100;
constexpr double COLUMN_OPACITY_DELAY = 150;
constexpr double OPACITY_DURATION = 150;
constexpr double TRIANGLE_DURATION = 300;
constexpr double MOVE_DURATION = 500;
} // namespace
void DateTimeAnimationController::PlayTitleInAnimation()
{
    CHECK_NULL_VOID(buttonIcon_);
    auto renderContext = buttonIcon_->GetRenderContext();
    AnimationOption animationOption;
    animationOption.SetDuration(TRIANGLE_DURATION);
    animationOption.SetCurve(Curves::SHARP);

    renderContext->UpdateTransformRotate(Vector5F(0, 0, 1, 0, 0));
    AnimationUtils::Animate(animationOption,
        [renderContext]() {
            CHECK_NULL_VOID_NOLOG(renderContext);
            renderContext->UpdateTransformRotate(Vector5F(0, 0, 1, 0 - SEMI_CIRCLE_ANGEL, 0));
        });
}

void DateTimeAnimationController::PlayTitleOutAnimation()
{
    CHECK_NULL_VOID(buttonIcon_);
    auto renderContext = buttonIcon_->GetRenderContext();
    AnimationOption animationOption;
    animationOption.SetDuration(TRIANGLE_DURATION);
    animationOption.SetCurve(Curves::SHARP);

    renderContext->UpdateTransformRotate(Vector5F(0, 0, 1, 0 - SEMI_CIRCLE_ANGEL, 0));
    AnimationUtils::Animate(animationOption,
        [renderContext]() {
            CHECK_NULL_VOID_NOLOG(renderContext);
            renderContext->UpdateTransformRotate(Vector5F(0, 0, 1, 0, 0));
        });
}

void DateTimeAnimationController::PlayMovingInAnimation()
{
    CHECK_NULL_VOID(year_);
    CHECK_NULL_VOID(month_);
    CHECK_NULL_VOID(day_);
    auto yearRenderContext = year_->GetRenderContext();
    auto monthRenderContext = month_->GetRenderContext();
    auto dayRenderContext = day_->GetRenderContext();
    AnimationOption animationOption;
    animationOption.SetDuration(MOVE_DURATION);
    animationOption.SetCurve(Curves::FRICTION);

    yearRenderContext->UpdateTransformTranslate({ yearStart_, 0.0f, 0.0f });
    monthRenderContext->UpdateTransformTranslate({ monthStart_, 0.0f, 0.0f });
    dayRenderContext->UpdateTransformTranslate({ dayStart_, 0.0f, 0.0f });
    AnimationUtils::Animate(animationOption,
        [yearRenderContext, monthRenderContext, dayRenderContext, weak = AceType::WeakClaim(this)]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            CHECK_NULL_VOID_NOLOG(yearRenderContext);
            CHECK_NULL_VOID_NOLOG(monthRenderContext);
            CHECK_NULL_VOID_NOLOG(dayRenderContext);
            yearRenderContext->UpdateTransformTranslate({ ref->yearEnd_, 0.0f, 0.0f });
            monthRenderContext->UpdateTransformTranslate({ ref->monthEnd_, 0.0f, 0.0f });
            dayRenderContext->UpdateTransformTranslate({ ref->dayEnd_, 0.0f, 0.0f });
        });
}

void DateTimeAnimationController::PlayMovingOutAnimation()
{
    CHECK_NULL_VOID(year_);
    CHECK_NULL_VOID(month_);
    CHECK_NULL_VOID(day_);
    auto yearRenderContext = year_->GetRenderContext();
    auto monthRenderContext = month_->GetRenderContext();
    auto dayRenderContext = day_->GetRenderContext();
    AnimationOption animationOption;
    animationOption.SetDuration(MOVE_DURATION);
    animationOption.SetCurve(Curves::FRICTION);

    yearRenderContext->UpdateTransformTranslate({ yearEnd_, 0.0f, 0.0f });
    monthRenderContext->UpdateTransformTranslate({ monthEnd_, 0.0f, 0.0f });
    dayRenderContext->UpdateTransformTranslate({ dayEnd_, 0.0f, 0.0f });
    AnimationUtils::Animate(animationOption,
        [yearRenderContext, monthRenderContext, dayRenderContext, weak = AceType::WeakClaim(this)]() {
            auto ref = weak.Upgrade();
            CHECK_NULL_VOID(ref);
            CHECK_NULL_VOID_NOLOG(yearRenderContext);
            CHECK_NULL_VOID_NOLOG(monthRenderContext);
            CHECK_NULL_VOID_NOLOG(dayRenderContext);
            yearRenderContext->UpdateTransformTranslate({ ref->yearStart_, 0.0f, 0.0f });
            monthRenderContext->UpdateTransformTranslate({ ref->monthStart_, 0.0f, 0.0f });
            dayRenderContext->UpdateTransformTranslate({ ref->dayStart_, 0.0f, 0.0f });
        });
}

void DateTimeAnimationController::PlayOldColumnOpacityInAnimation()
{
    CHECK_NULL_VOID(monthDays_);
    CHECK_NULL_VOID(timePicker_);
    auto monthDaysRender = monthDays_->GetRenderContext();
    auto timePickerRender = timePicker_->GetRenderContext();
    CHECK_NULL_VOID(monthDaysRender);
    CHECK_NULL_VOID(timePickerRender);
    if (datePicker_) {
        auto layoutProperty = datePicker_->GetLayoutProperty<LayoutProperty>();
        if (layoutProperty) {
            layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        }
    }
    AnimationOption animationOption;
    animationOption.SetDuration(OPACITY_DURATION);
    animationOption.SetCurve(Curves::LINEAR);
    animationOption.SetOnFinishEvent([weak = AceType::WeakClaim(this)] {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        if (ref->isOutAnimationPlaying_) {
            ref->isInAnimationPlaying_ = false;
            return;
        }
        auto monthDaysNode = ref->monthDays_;
        CHECK_NULL_VOID(monthDaysNode);
        auto layoutProperty = monthDaysNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::GONE);

        auto timePickerNode = ref->timePicker_;
        CHECK_NULL_VOID(timePickerNode);
        layoutProperty = timePickerNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::GONE);
        ref->isInAnimationPlaying_ = false;
    });
    monthDaysRender->UpdateOpacity(1);
    timePickerRender->UpdateOpacity(1);
    oldColumnOpacityInAnimation_ = AnimationUtils::StartAnimation(animationOption,
        [monthDaysRender, timePickerRender]() {
            CHECK_NULL_VOID_NOLOG(monthDaysRender);
            CHECK_NULL_VOID_NOLOG(timePickerRender);
            monthDaysRender->UpdateOpacity(0);
            timePickerRender->UpdateOpacity(0);
        }, animationOption.GetOnFinishEvent());
}

void DateTimeAnimationController::PlayNewColumnOpacityInAnimation()
{
    CHECK_NULL_VOID(month_);
    CHECK_NULL_VOID(day_);
    auto monthRender = month_->GetRenderContext();
    auto dayRender = day_->GetRenderContext();
    CHECK_NULL_VOID(monthRender);
    CHECK_NULL_VOID(dayRender);

    AnimationOption animationOption;
    animationOption.SetDuration(OPACITY_DURATION);
    animationOption.SetCurve(Curves::LINEAR);

    monthRender->UpdateOpacity(0);
    dayRender->UpdateOpacity(0);
    AnimationUtils::Animate(animationOption,
        [monthRender, dayRender]() {
            CHECK_NULL_VOID_NOLOG(monthRender);
            CHECK_NULL_VOID_NOLOG(dayRender);
            monthRender->UpdateOpacity(1);
            dayRender->UpdateOpacity(1);
        });
}

void DateTimeAnimationController::PlayYearColumnOpacityInAnimation()
{
    CHECK_NULL_VOID(year_);
    auto yearRender = year_->GetRenderContext();
    CHECK_NULL_VOID(yearRender);

    AnimationOption animationOption;
    animationOption.SetDelay(OPACITY_DELAY);
    animationOption.SetDuration(OPACITY_DURATION);
    animationOption.SetCurve(Curves::LINEAR);

    yearRender->OpacityAnimation(animationOption, 0.0f, 1.0f);
}

void DateTimeAnimationController::PlayButtonOpacityInAnimation()
{
    CHECK_NULL_VOID(buttonRow_);
    auto buttonRender = buttonRow_->GetRenderContext();
    CHECK_NULL_VOID(buttonRender);

    AnimationOption animationOption;
    animationOption.SetDelay(OPACITY_DELAY);
    animationOption.SetDuration(OPACITY_DURATION);
    animationOption.SetCurve(Curves::LINEAR);
    animationOption.SetOnFinishEvent([weak = AceType::WeakClaim(this)] {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        auto buttonNode = ref->buttonRow_;
        CHECK_NULL_VOID(buttonNode);
        auto layoutProperty = buttonNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        auto focusHub = buttonNode->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetShow(false);
    });
    buttonRender->OpacityAnimation(animationOption, 1.0f, 0.0f);
}

void DateTimeAnimationController::PlayOldColumnOpacityOutAnimation()
{
    CHECK_NULL_VOID(monthDays_);
    auto monthDaysRender = monthDays_->GetRenderContext();
    CHECK_NULL_VOID(timePicker_);
    auto timePickerRender = timePicker_->GetRenderContext();

    auto layoutProperty = monthDays_->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
    layoutProperty = timePicker_->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateVisibility(VisibleType::VISIBLE);

    AnimationOption animationOption;
    animationOption.SetDelay(COLUMN_OPACITY_DELAY);
    animationOption.SetDuration(OPACITY_DURATION);
    animationOption.SetCurve(Curves::LINEAR);
    animationOption.SetOnFinishEvent([weak = AceType::WeakClaim(this)] {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        if (ref->isInAnimationPlaying_) {
            ref->isOutAnimationPlaying_ = false;
            return;
        }
        auto datePickerNode = ref->datePicker_;
        CHECK_NULL_VOID(datePickerNode);
        auto layoutProperty = datePickerNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::GONE);
        ref->isOutAnimationPlaying_ = false;
    });

    monthDaysRender->UpdateOpacity(0);
    timePickerRender->UpdateOpacity(0);
    oldColumnOpacityOutAnimation_ = AnimationUtils::StartAnimation(animationOption,
        [monthDaysRender, timePickerRender]() {
            CHECK_NULL_VOID_NOLOG(monthDaysRender);
            CHECK_NULL_VOID_NOLOG(timePickerRender);
            monthDaysRender->UpdateOpacity(1);
            timePickerRender->UpdateOpacity(1);
        }, animationOption.GetOnFinishEvent());
}

void DateTimeAnimationController::PlayNewColumnOpacityOutAnimation()
{
    CHECK_NULL_VOID(month_);
    CHECK_NULL_VOID(day_);
    auto monthRender = month_->GetRenderContext();
    auto dayRender = day_->GetRenderContext();
    CHECK_NULL_VOID(monthRender);
    CHECK_NULL_VOID(dayRender);

    AnimationOption animationOption;
    animationOption.SetDelay(OPACITY_DELAY);
    animationOption.SetDuration(OPACITY_DURATION);
    animationOption.SetCurve(Curves::LINEAR);

    monthRender->UpdateOpacity(1);
    dayRender->UpdateOpacity(1);
    AnimationUtils::Animate(animationOption,
        [monthRender, dayRender]() {
            CHECK_NULL_VOID_NOLOG(monthRender);
            CHECK_NULL_VOID_NOLOG(dayRender);
            monthRender->UpdateOpacity(0);
            dayRender->UpdateOpacity(0);
        });
}

void DateTimeAnimationController::PlayYearColumnOpacityOutAnimation()
{
    CHECK_NULL_VOID(year_);
    auto yearRender = year_->GetRenderContext();
    CHECK_NULL_VOID(yearRender);

    AnimationOption animationOption;
    animationOption.SetDuration(OPACITY_DURATION);
    animationOption.SetCurve(Curves::LINEAR);

    yearRender->OpacityAnimation(animationOption, 1.0f, 0.0f);
}

void DateTimeAnimationController::PlayButtonOpacityOutAnimation()
{
    CHECK_NULL_VOID(buttonRow_);
    auto buttonRender = buttonRow_->GetRenderContext();
    CHECK_NULL_VOID(buttonRender);

    AnimationOption animationOption;
    animationOption.SetDelay(OPACITY_DELAY);
    animationOption.SetDuration(OPACITY_DURATION);
    animationOption.SetCurve(Curves::LINEAR);
    animationOption.SetOnFinishEvent([weak = AceType::WeakClaim(this)] {
        auto ref = weak.Upgrade();
        CHECK_NULL_VOID(ref);
        auto buttonNode = ref->buttonRow_;
        CHECK_NULL_VOID(buttonNode);
        auto layoutProperty = buttonNode->GetLayoutProperty<LayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateVisibility(VisibleType::VISIBLE);
        auto focusHub = buttonNode->GetFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetShow(true);
    });
    buttonRender->OpacityAnimation(animationOption, 0.0f, 1.0f);
}

void DateTimeAnimationController::StopOldColumnOpacityInAnimation()
{
    if (oldColumnOpacityInAnimation_) {
        AnimationUtils::StopAnimation(oldColumnOpacityInAnimation_);
    }
}

void DateTimeAnimationController::StopOldColumnOpacityOutAnimation()
{
    if (oldColumnOpacityOutAnimation_) {
        AnimationUtils::StopAnimation(oldColumnOpacityOutAnimation_);
    }
}

void DateTimeAnimationController::PlayInAnimation()
{
    isInAnimationPlaying_ = true;
    PlayTitleInAnimation();
    PlayMovingInAnimation();

    StopOldColumnOpacityOutAnimation();
    PlayOldColumnOpacityInAnimation();
    PlayNewColumnOpacityInAnimation();
    PlayYearColumnOpacityInAnimation();
    PlayButtonOpacityInAnimation();
}

void DateTimeAnimationController::PlayOutAnimation()
{
    isOutAnimationPlaying_ = true;
    PlayTitleOutAnimation();
    PlayMovingOutAnimation();

    StopOldColumnOpacityInAnimation();
    PlayOldColumnOpacityOutAnimation();
    PlayNewColumnOpacityOutAnimation();
    PlayYearColumnOpacityOutAnimation();
    PlayButtonOpacityOutAnimation();
}


void DateTimeAnimationController::InitMoveRange()
{
    yearEnd_ = 0.0;
    monthEnd_ = 0.0;
    dayEnd_ = 0.0;

    auto yearGeometry = year_->GetGeometryNode();
    CHECK_NULL_VOID(yearGeometry);
    auto monthGeometry = month_->GetGeometryNode();
    CHECK_NULL_VOID(monthGeometry);
    yearStart_ = 0;
    monthStart_ = 0 - yearGeometry->GetFrameSize().Width();
    dayStart_ = monthStart_ - monthGeometry->GetFrameSize().Width();
}


void DateTimeAnimationController::SetDatePicker(const RefPtr<FrameNode>& value)
{
    datePicker_ = value;
    auto children = datePicker_->GetChildren();
    if (children.size() != CHILD_SIZE) {
        return;
    }
    auto iter = children.begin();
    auto year = (*iter);
    CHECK_NULL_VOID(year);
    iter++;
    auto month = *iter;
    CHECK_NULL_VOID(month);
    iter++;
    auto day = *iter;
    CHECK_NULL_VOID(day);
    year_ = DynamicCast<FrameNode>(year->GetChildAtIndex(1));
    month_ = DynamicCast<FrameNode>(month->GetChildAtIndex(1));
    day_ = DynamicCast<FrameNode>(day->GetChildAtIndex(1));
}

void DateTimeAnimationController::Play(bool isIn)
{
    if (!created_) {
        InitMoveRange();
        created_ = true;
    }

    if (isIn) {
        PlayInAnimation();
    } else {
        PlayOutAnimation();
    }
}
} // namespace OHOS::Ace
