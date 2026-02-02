/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/calendar_picker_modifier.h"

#include "ui/base/utils/utils.h"
#include "frameworks/core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"
#include "core/common/dynamic_module_helper.h"
namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUICalendarPickerModifier* GetCalendarPickerModifier()
{
    static const ArkUICalendarPickerModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("CalendarPicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const ArkUICalendarPickerModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

const CJUICalendarPickerModifier* GetCJUICalendarPickerModifier()
{
    static const CJUICalendarPickerModifier* cachedModifier = nullptr;
    if (!cachedModifier) {
        auto* module = DynamicModuleHelper::GetInstance().GetDynamicModule("CalendarPicker");
        CHECK_NULL_RETURN(module, nullptr);
        cachedModifier = reinterpret_cast<const CJUICalendarPickerModifier*>(module->GetDynamicModifier());
    }
    return cachedModifier;
}

void SetCalendarPickerOnChange(ArkUINodeHandle node, void* extraParam)
{
    auto* modifier = GetCalendarPickerModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setCalendarPickerOnChangeExtraParam(node, extraParam);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG