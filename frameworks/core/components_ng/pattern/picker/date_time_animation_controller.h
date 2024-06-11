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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_TIME_ANIMATION_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_TIME_ANIMATION_CONTROLLER_H

#include "core/animation/animator.h"
#include "core/components/display/render_display.h"
#include "core/components/picker/picker_animation.h"
#include "core/components/picker/render_picker_column.h"
#include "core/components/triangle/render_triangle.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace::NG {
class DateTimeAnimationController : public virtual AceType {
    DECLARE_ACE_TYPE(DateTimeAnimationController, AceType);

public:
    ~DateTimeAnimationController() = default;

    void SetButtonIcon(const RefPtr<FrameNode>& value)
    {
        buttonIcon_ = value;
    }

    void SetMonthDays(const RefPtr<FrameNode>& value)
    {
        monthDays_ = value;
    }

    void SetTimePicker(const RefPtr<FrameNode>& value)
    {
        timePicker_ = value;
    }

    void SetDatePicker(const RefPtr<FrameNode>& value);

    void SetButtonRow(const RefPtr<FrameNode>& value)
    {
        buttonRow_ = value;
    }

    void SetDatePickerButtonHide(bool value)
    {
        isDatePickerButtonHade_ = value;
    }

    void Play(bool isIn);

private:
    // triangle animation
    void PlayTitleInAnimation();
    void PlayTitleOutAnimation();
    // opacity animation
    void PlayOldColumnOpacityInAnimation();
    void PlayOldColumnOpacityOutAnimation();
    void PlayNewColumnOpacityInAnimation();
    void PlayYearColumnOpacityInAnimation();
    void PlayButtonOpacityInAnimation();
    void PlayNewColumnOpacityOutAnimation();
    void PlayYearColumnOpacityOutAnimation();
    void PlayButtonOpacityOutAnimation();
    // moving animation
    void PlayMovingInAnimation();
    void PlayMovingOutAnimation();
    void InitMoveRange();
    // play or stop animation

    void StopOldColumnOpacityInAnimation();
    void StopOldColumnOpacityOutAnimation();

    void PlayInAnimation();
    void PlayOutAnimation();

    WeakPtr<FrameNode> buttonIcon_;
    WeakPtr<FrameNode> datePicker_;
    WeakPtr<FrameNode> monthDays_;
    WeakPtr<FrameNode> timePicker_;
    WeakPtr<FrameNode> year_;
    WeakPtr<FrameNode> month_;
    WeakPtr<FrameNode> day_;
    WeakPtr<FrameNode> buttonRow_;
    // move range of date
    double yearStart_ = 0.0;
    double yearEnd_ = 0.0;
    double monthStart_ = 0.0;
    double monthEnd_ = 0.0;
    double dayStart_ = 0.0;
    double dayEnd_ = 0.0;
    // others
    std::shared_ptr<AnimationUtils::Animation> oldColumnOpacityInAnimation_;
    std::shared_ptr<AnimationUtils::Animation> oldColumnOpacityOutAnimation_;
    bool created_ = false;
    bool isInAnimationPlaying_ = false;
    bool isOutAnimationPlaying_ = false;
    bool isDatePickerButtonHade_ = false;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_DATE_TIME_ANIMATION_CONTROLLER_H
