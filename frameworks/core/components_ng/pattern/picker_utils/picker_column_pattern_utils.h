/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_COLUMN_PATTERN_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_COLUMN_PATTERN_UTILS_H

#include <utility>
#include <string>

#include "core/components/picker/picker_theme.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace::NG {

template<class T>
class PickerColumnPatternUtils {
public:
    PickerColumnPatternUtils(const T& init)
    {
        selectedColumnId_ = init;
    }

    virtual ~PickerColumnPatternUtils()
    {
    }

    void SetSelectedMark(bool focus, bool notify = true, bool reRender = true)
    {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        auto pickerTheme = pipeline->GetTheme<PickerTheme>();
        CHECK_NULL_VOID(pickerTheme);
        SetSelectedMark(pickerTheme, focus, notify, reRender);
    }

    void SetSelectedMark(RefPtr<PickerTheme>& pickerTheme, bool focus, bool notify = true, bool reRender = true)
    {
        CHECK_NULL_VOID(pickerTheme);
        if (selectedMark_ == focus) {
            return;
        }
        selectedMark_ = focus;
        bool IsCircleDial = pickerTheme->IsCircleDial();
        if (IsCircleDial) {
            selectedMarkPaint_ = selectedMark_;
        }
        if (reRender && IsCircleDial) {
            ToUpdateSelectedTextProperties(pickerTheme);
        }

        if (focus && notify && (nullptr != focusedListerner_)) {
            focusedListerner_(selectedColumnId_);
        }
    }

    void SetSelectedMarkId(const T& strColumnId)
    {
        selectedColumnId_ = strColumnId;
    }

    void SetSelectedMarkListener(const std::function<void(T&)>& listener)
    {
        focusedListerner_ = listener;
    }

    T& GetselectedColumnId() const
    {
        return const_cast<T&>(selectedColumnId_);
    }

    int32_t GetDigitalCrownSensitivity()
    {
        if (crownSensitivity_ == INVALID_CROWNSENSITIVITY) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_RETURN(pipeline, DEFAULT_CROWNSENSITIVITY);
            auto pickerTheme = pipeline->GetTheme<PickerTheme>();
            CHECK_NULL_RETURN(pickerTheme, DEFAULT_CROWNSENSITIVITY);
            crownSensitivity_ = pickerTheme->GetDigitalCrownSensitivity();
        }

        return crownSensitivity_;
    }

    void SetDigitalCrownSensitivity(int32_t crownSensitivity)
    {
        crownSensitivity_ = crownSensitivity;
    }

#ifdef SUPPORT_DIGITAL_CROWN
    bool IsCrownEventEnded() const
    {
        return isCrownEventEnded_;
    }

    double GetCrownRotatePx(const CrownEvent& event)
    {
        double velocity = std::abs(event.angularVelocity * PICKER_ANGULAR_VELOCITY_FACTOR);
        double px = 0.0;
        if (LessOrEqualCustomPrecision(velocity, PICKER_ANGULAR_VELOCITY_SLOW, 0.01f)) {
            px = (Dimension(PICKER_DISPLAY_CONTROL_RATIO_VERY_SLOW, DimensionUnit::VP) * event.degree).ConvertToPx();
        } else if (LessOrEqualCustomPrecision(velocity, PICKER_ANGULAR_VELOCITY_MEDIUM, 0.01f)) {
            px = (Dimension(PICKER_DISPLAY_CONTROL_RATIO_SLOW, DimensionUnit::VP) * event.degree).ConvertToPx();
        } else if (LessOrEqualCustomPrecision(velocity, PICKER_ANGULAR_VELOCITY_FAST, 0.01f)) {
            px = (Dimension(PICKER_DISPLAY_CONTROL_RATIO_MEDIUM, DimensionUnit::VP) * event.degree).ConvertToPx();
        } else {
            px = (Dimension(PICKER_DISPLAY_CONTROL_RATIO_FAST, DimensionUnit::VP) * event.degree).ConvertToPx();
        }

        int32_t crownSensitivity = GetDigitalCrownSensitivity();
        LOGD("timepicker crownSensitivity=%{public}d", crownSensitivity);
        switch (crownSensitivity) {
            case static_cast<int32_t>(OHOS::Ace::CrownSensitivity::LOW):
                px *= PICKER_CROWN_SENSITIVITY_LOW;
                break;
            case static_cast<int32_t>(OHOS::Ace::CrownSensitivity::MEDIUM):
                px *= PICKER_CROWN_SENSITIVITY_MEDIUM;
                break;
            case static_cast<int32_t>(OHOS::Ace::CrownSensitivity::HIGH):
                px *= PICKER_CROWN_SENSITIVITY_HIGH;
                break;
            default:
                break;
        }

        return px;
    }

    bool OnCrownEvent(const CrownEvent& event)
    {
        if (event.action == OHOS::Ace::CrownAction::BEGIN) {
            HandleCrownBeginEvent(event);
            isCrownEventEnded_ = false;
        } else if (event.action == OHOS::Ace::CrownAction::UPDATE) {
            HandleCrownMoveEvent(event);
            isCrownEventEnded_ = false;
        } else if (event.action == OHOS::Ace::CrownAction::END) {
            HandleCrownEndEvent();
            isCrownEventEnded_ = true;
        } else {
            return false;
        }

        return true;
    }
#endif

private:
    virtual void ToUpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme) = 0;
#ifdef SUPPORT_DIGITAL_CROWN
    virtual void HandleCrownBeginEvent(const CrownEvent& event)= 0;
    virtual void HandleCrownMoveEvent(const CrownEvent& event) = 0;
    virtual void HandleCrownEndEvent() = 0;
#endif

protected:
#ifdef SUPPORT_DIGITAL_CROWN
    bool isCrownEventEnded_ = true;
#endif
    bool selectedMark_ = false;
    bool selectedMarkPaint_ = false;
    T selectedColumnId_;
    std::function<void(T&)> focusedListerner_ = nullptr;
    int32_t crownSensitivity_ = INVALID_CROWNSENSITIVITY;
};

}

#endif