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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_COLUMN_PATTERN_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_COLUMN_PATTERN_UTILS_H

#include <utility>
#include <string>

#include "core/components/picker/picker_theme.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace::NG {

template<class T>
class PickerColumnPatternCircleUtils {
public:
    PickerColumnPatternCircleUtils() {}

    virtual ~PickerColumnPatternCircleUtils() {}

    void SetSelectedMark(
        T* pickerColumn, RefPtr<PickerTheme>& pickerTheme, bool focus, bool notify = true, bool reRender = true)
    {
        CHECK_NULL_VOID(pickerTheme);
        CHECK_NULL_VOID(pickerColumn);
        if (selectedMark_ == focus) {
            return;
        }
        selectedMark_ = focus;
        pickerColumn->SetSelectedMarkPaint(selectedMark_);
        if (reRender) {
            pickerColumn->UpdateSelectedTextColor(pickerTheme);
        }

        if (focus && notify && pickerColumn->focusedListerner_) {
            pickerColumn->focusedListerner_(pickerColumn->selectedColumnId_);
        }
    }

#ifdef SUPPORT_DIGITAL_CROWN
    double GetCrownRotatePx(const CrownEvent& event, int32_t crownSensitivity)
    {
        float ration[][2] = {
            {PICKER_ANGULAR_VELOCITY_SLOW, PICKER_DISPLAY_CONTROL_RATIO_VERY_SLOW},
            {PICKER_ANGULAR_VELOCITY_MEDIUM, PICKER_DISPLAY_CONTROL_RATIO_SLOW},
            {PICKER_ANGULAR_VELOCITY_FAST, PICKER_DISPLAY_CONTROL_RATIO_MEDIUM}};
        double velocity = std::abs(event.angularVelocity * PICKER_ANGULAR_VELOCITY_FACTOR);
        double px = (Dimension(PICKER_DISPLAY_CONTROL_RATIO_FAST, DimensionUnit::VP) * event.degree).ConvertToPx();
        // Calculate the offset based on the angle of rotation of the crown
        for (size_t i = 0; i < sizeof(ration) / sizeof(ration[0]); i++) {
            if (LessOrEqualCustomPrecision(velocity, ration[i][0], 0.01f)) {
                px = (Dimension(ration[i][1], DimensionUnit::VP) * event.degree).ConvertToPx();
                break;
            }
        }

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
                px *= PICKER_CROWN_SENSITIVITY_MEDIUM;
                break;
        }

        return px;
    }

    bool OnCrownEvent(T* pickerColumn, const CrownEvent& event)
    {
        CHECK_NULL_RETURN(pickerColumn, false);
        switch (event.action) {
            case OHOS::Ace::CrownAction::BEGIN:
                pickerColumn->HandleCrownBeginEvent(event);
                break;
            case OHOS::Ace::CrownAction::UPDATE:
                pickerColumn->HandleCrownMoveEvent(event);
                break;
            case OHOS::Ace::CrownAction::END:
                pickerColumn->HandleCrownEndEvent(event);
                break;
            default:
                return false;
                break;
        }

        return true;
    }
#endif

private:
    bool selectedMark_ = false;
};

}

#endif
