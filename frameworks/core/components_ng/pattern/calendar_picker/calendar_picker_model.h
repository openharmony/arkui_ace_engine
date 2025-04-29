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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_PICKER_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_PICKER_MODEL_H

#include <functional>
#include <mutex>

#include "base/utils/macros.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_event_hub.h"
#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"

namespace OHOS::Ace {
class ACE_FORCE_EXPORT CalendarPickerModel {
public:
    static CalendarPickerModel* GetInstance();
    virtual ~CalendarPickerModel() = default;

    virtual void Create(const NG::CalendarSettingData& settingData) = 0;
    virtual void SetEdgeAlign(const NG::CalendarEdgeAlign& alignType, const DimensionOffset& offset) = 0;
    virtual void SetTextStyle(const NG::PickerTextStyle& textStyle) = 0;
    virtual void SetOnChange(NG::SelectedChangeEvent&& onChange) = 0;
    virtual void SetChangeEvent(NG::SelectedChangeEvent&& onChange) = 0;
    virtual void SetPadding(const NG::PaddingProperty& padding) = 0;
    virtual void ClearBorderColor() = 0;
    virtual void ClearBorderRadius() = 0;
    virtual void ClearHeight() = 0;
    virtual void ClearBorder() = 0;
    virtual void ClearBorderWidth() = 0;
    virtual void ClearPadding() = 0;
    virtual void SetMarkToday(bool isMarkToday) = 0;

private:
    static std::unique_ptr<CalendarPickerModel> instance_;
    static std::once_flag onceFlag_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CALENDAR_PICKER_CALENDAR_PICKER_MODEL_H
