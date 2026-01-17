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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_UTILS_H
#include "ecmascript/napi/include/jsnapi.h"

#include "core/components_ng/pattern/calendar_picker/calendar_type_define.h"
#include "core/components_ng/pattern/picker/picker_data.h"
namespace OHOS::Ace::NG {
using panda::JSValueRef;
using panda::Local;
using panda::ecmascript::EcmaVM;
class CalendarPickerUtils {
public:
    static PickerDate ParseDate(
        EcmaVM* vm, const panda::Local<panda::JSValueRef>& dateVal, bool useCurrentDate = false);
    static void ParseDisabledDateRange(
        EcmaVM* vm, const panda::Local<panda::JSValueRef>& disabledDateRangeVal, NG::CalendarSettingData& settingData);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_CALENDAR_PICKER_UTILS_H