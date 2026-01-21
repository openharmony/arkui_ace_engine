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

#include "core/components_ng/pattern/calendar_picker/bridge/calendar_picker_dynamic_module.h"

#include "core/components_ng/pattern/calendar_picker/bridge/arkts_native_calendar_picker_bridge.h"
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/calendar_picker/calendar_picker_model_static.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_CalendarPicker()
{
    return new OHOS::Ace::CalendarPickerDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUICalendarPickerModifier* GetCalendarPickerDynamicModifier();
const CJUICalendarPickerModifier* GetCJUICalendarPickerModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUICalendarPickerModifier* GetCalendarPickerStaticModifier();
}
#endif
} // namespace NG

void CalendarPickerDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::CalendarPickerBridge::RegisterCalendarPickerAttributes(object, vm);
}

const void* CalendarPickerDynamicModule::GetDynamicModifier()
{
    return NG::GetCalendarPickerDynamicModifier();
}

const void* CalendarPickerDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetCalendarPickerStaticModifier();
#else
    return nullptr;
#endif
}

const void* CalendarPickerDynamicModule::GetCjModifier()
{
    return NG::GetCJUICalendarPickerModifier();
}

void* CalendarPickerDynamicModule::GetModel()
{
    static NG::CalendarPickerModelNG model;
    return &model;
}
} // namespace OHOS::Ace