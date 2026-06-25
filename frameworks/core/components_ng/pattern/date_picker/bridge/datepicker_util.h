/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_BRIDGE_DATE_PICKER_UTIL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_BRIDGE_DATE_PICKER_UTIL_H

#include <functional>
#include <map>
#include <string>

#include "ui/base/referenced.h"
#include "core/interfaces/native/node/node_api.h"

#include "core/components_ng/pattern/date_picker/picker_data.h"
#include "core/components_ng/pattern/date_picker/picker_date_f.h"
#include "core/components_ng/pattern/date_picker/picker_type_define.h"
#include "core/components_ng/pattern/time_picker/bridge/timepicker_util.h"
#include "core/components/dialog/dialog_properties.h"

struct Ark_DatePickerDialogOptions;
namespace OHOS::Ace {
struct ButtonInfo;
class GestureEvent;

namespace NG {
class FrameNode;

namespace DatePickerUtil {
const char DATE_PICKER_ETS_TAG[] = "DatePicker";

struct DatePickerDialogInfo {
    const DialogProperties& dialogProperties;
    const DatePickerSettingData& settingData;
    const std::vector<ButtonInfo>& buttonInfos;
    RefPtr<FrameNode> datePickerNode;
};

struct DatepickerCustomModifier {
    void (*setDatePickerDialogViewShow)(DatePickerDialogInfo& info,
        std::map<std::string, std::function<void(const std::string&)>> dialogEvent,
        std::map<std::string, std::function<void(const GestureEvent& info)>> dialogCancelEvent);
    std::string (*getFormatString)(PickerDateF date);
};

struct ArkUIDatePickerDialogModifier {
    void (*showDatePickerDialog)(const Ark_DatePickerDialogOptions* options);
};

const ArkUIDatePickerDialogModifier* GetDatePickerDialogStaticModifier();
const DatepickerCustomModifier* GetDatePickerCustomModifier();
const NG::TimePickerUtil::TimepickerCustomModifier* GetTimepickerCustomModifier();

} // namespace DatePickerUtil
} // namespace NG
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_DATE_PICKER_BRIDGE_DATE_PICKER_UTIL_H
