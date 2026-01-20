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

#include "core/components_ng/pattern/time_picker/bridge/timepicker_dynamic_module.h"

#include "compatible/components/picker/timepicker_model_impl.h"

#include "core/common/dynamic_module.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/time_picker/bridge/arkts_native_timepicker_bridge.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/time_picker/timepicker_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_TimePicker()
{
    return new OHOS::Ace::TimePickerDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUITimepickerModifier* GetTimePickerDynamicModifier();
const CJUITimepickerModifier* GetCJUITimePickerModifier();
} // namespace NodeModifier
namespace GeneratedModifier {
#ifdef INCLUDE_GENERATED_SOURCES
const GENERATED_ArkUITimePickerModifier* GetTimePickerStaticModifier();
#endif
} // namespace GeneratedModifier
} // namespace NG

void TimePickerDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::TimePickerBridge::RegisterTimePickerAttributes(object, vm);
}

const void* TimePickerDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetTimePickerDynamicModifier();
}

const void* TimePickerDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetTimePickerStaticModifier();
#else
    return nullptr;
#endif
}

const void* TimePickerDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUITimePickerModifier();
}

void* TimePickerDynamicModule::GetModel()
{
    static NG::TimePickerModelNG model;
    return &model;
}

const void* TimePickerDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == "customModifier") {
        return NG::TimePickerUtil::GetTimePickerCustomModifier();
    }
    return nullptr;
}

} // namespace OHOS::Ace
