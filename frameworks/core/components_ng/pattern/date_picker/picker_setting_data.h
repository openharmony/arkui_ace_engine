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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_SETTING_DATA_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_SETTING_DATA_H

#include <map>
#include <string>

#include "core/components_ng/pattern/date_picker/picker_checkbox_setting.h"
#include "core/components_ng/pattern/date_picker/picker_date.h"
#include "core/components_ng/pattern/date_picker/picker_time.h"
#include "core/components_ng/pattern/date_picker/picker_types.h"
#include "core/components_ng/pattern/date_picker/picker_text_style.h"
#include "base/i18n/time_format.h"

namespace OHOS::Ace::NG {

struct DatePickerSettingData {
    bool isLunar;
    bool lunarswitch;
    bool canLoop = true;
    CheckboxSettingData checkboxSettingData;
    bool showTime;
    bool useMilitary;
    DatePickerMode mode;
    std::map<std::string, PickerDate> datePickerProperty;
    std::map<std::string, PickerTime> timePickerProperty;
    PickerTextProperties properties;
    DateTimeType dateTimeOptions;
    bool isEnableHapticFeedback = true;
    int32_t crownSensitivity;
};

struct TimePickerSettingData {
    bool isUseMilitaryTime = false;
    PickerDate dialogTitleDate;
    PickerTextProperties properties;
    DateTimeType dateTimeOptions;
    bool isEnableHapticFeedback;
    bool showSecond;
    bool isEnableCascade;
    int32_t crownSensitivity;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_DATE_PICKER_PICKER_SETTING_DATA_H
