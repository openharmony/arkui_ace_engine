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
#include "calendar_picker_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/picker/picker_data.h"

namespace OHOS::Ace::NG {
PickerDate CalendarPickerUtils::ParseDate(
    EcmaVM* vm, const panda::Local<panda::JSValueRef>& dateVal, bool useCurrentDate)
{
    auto pickerDate = useCurrentDate ? PickerDate::Current() : PickerDate();

    if (!dateVal->IsObject(vm)) {
        return pickerDate;
    }

    auto dateObj = dateVal->ToObject(vm);
    CHECK_NULL_RETURN(dateObj->IsObject(vm), pickerDate);

    panda::Local<panda::JSValueRef> yearFuncVal = dateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getFullYear"));
    panda::Local<panda::JSValueRef> monthFuncVal = dateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getMonth"));
    panda::Local<panda::JSValueRef> dateFuncVal = dateObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "getDate"));

    if (!(yearFuncVal->IsFunction(vm) && monthFuncVal->IsFunction(vm) && dateFuncVal->IsFunction(vm))) {
        return pickerDate;
    }

    panda::Local<panda::FunctionRef> yearFunc = yearFuncVal->ToObject(vm);
    panda::Local<panda::FunctionRef> monthFunc = monthFuncVal->ToObject(vm);
    panda::Local<panda::FunctionRef> dateFunc = dateFuncVal->ToObject(vm);

    panda::Local<panda::JSValueRef> yearResult = yearFunc->Call(vm, dateObj, nullptr, 0);
    panda::Local<panda::JSValueRef> monthResult = monthFunc->Call(vm, dateObj, nullptr, 0);
    panda::Local<panda::JSValueRef> dateResult = dateFunc->Call(vm, dateObj, nullptr, 0);

    if (yearResult->IsNumber() && monthResult->IsNumber() && dateResult->IsNumber()) {
        pickerDate.SetYear(yearResult->ToNumber(vm)->Int32Value(vm));
        pickerDate.SetMonth(monthResult->ToNumber(vm)->Int32Value(vm) + 1); // 0-11 转换为 1-12
        pickerDate.SetDay(dateResult->ToNumber(vm)->Int32Value(vm));
    }

    return pickerDate;
}

void CalendarPickerUtils::ParseDisabledDateRange(
    EcmaVM* vm, const panda::Local<panda::JSValueRef>& disabledDateRangeVal, NG::CalendarSettingData& settingData)
{
    if (disabledDateRangeVal->IsUndefined() || disabledDateRangeVal->IsNull() || !disabledDateRangeVal->IsArray(vm)) {
        return;
    }
    panda::Local<panda::ArrayRef> array = panda::Local<panda::ArrayRef>(disabledDateRangeVal);
    auto length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, array));
    for (uint32_t i = 0; i < length; i++) {
        panda::Local<panda::JSValueRef> dateRangeValue = array->Get(vm, i);
        if (!dateRangeValue->IsObject(vm)) {
            continue;
        }
        panda::Local<panda::ObjectRef> dateRangeObj = dateRangeValue->ToObject(vm);
        panda::Local<panda::JSValueRef> startValue = dateRangeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "start"));
        panda::Local<panda::JSValueRef> endValue = dateRangeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "end"));
        if (startValue->IsObject(vm) && endValue->IsObject(vm)) {
            auto startDate = ParseDate(vm, startValue, false);
            auto endDate = ParseDate(vm, endValue, false);
            if (startDate.GetYear() == 0 || endDate.GetYear() == 0 || endDate < startDate) {
                continue;
            }
            std::pair<PickerDate, PickerDate> pickerDateRange;
            pickerDateRange.first = startDate;
            pickerDateRange.second = endDate;
            settingData.disabledDateRange.emplace_back(pickerDateRange);
        }
    }
}
} // namespace OHOS::Ace::NG