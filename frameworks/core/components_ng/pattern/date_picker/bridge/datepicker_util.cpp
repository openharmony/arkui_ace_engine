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

#include "core/interfaces/native/node/node_api.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/date_picker/bridge/datepicker_util.h"
#include "core/components_ng/pattern/date_picker/datepicker_dialog_view.h"
#include "core/components_ng/pattern/date_picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/date_picker/datepicker_pattern.h"

namespace OHOS::Ace::NG::DatePickerUtil {
namespace {
#define MODIFIER_COUNTS 1

#ifndef ARKUI_WEARABLE
void SetDatePickerDialogViewShow(DatePickerDialogInfo& info,
    std::map<std::string, std::function<void(const std::string&)>> dialogEvent,
    std::map<std::string, std::function<void(const GestureEvent& info)>> dialogCancelEvent)
{
    info.datePickerNode = DatePickerDialogView::Show(info.dialogProperties, info.settingData, info.buttonInfos,
        std::move(dialogEvent), std::move(dialogCancelEvent));
}
#endif

std::string GetFormatString(PickerDateF date)
{
    return DatePickerPattern::GetFormatString(date);
}
} // namespace

const DatepickerCustomModifier* GetDatePickerCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const DatepickerCustomModifier modifier = {
#ifndef ARKUI_WEARABLE
        .setDatePickerDialogViewShow = SetDatePickerDialogViewShow,
#else
        .setDatePickerDialogViewShow = nullptr,
#endif
        .getFormatString = GetFormatString,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, MODIFIER_COUNTS, 0, 0); // don't move this line
    return &modifier;
}

const NG::TimePickerUtil::TimepickerCustomModifier* GetTimepickerCustomModifier()
{
    static const NG::TimePickerUtil::TimepickerCustomModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
#ifdef ACE_UNITTEST
        cachedModifier = NG::TimePickerUtil::GetTimePickerCustomModifier();
#else
        // Dynamically load the independently compiled so library
        // from frameworks/core/components_ng/pattern/time_picker directory
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("TimePicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const NG::TimePickerUtil::TimepickerCustomModifier*>(
            module->GetCustomModifier("customModifier"));
#endif
    }
    return cachedModifier;
}
} // namespace OHOS::Ace::NG::DatePickerUtil
