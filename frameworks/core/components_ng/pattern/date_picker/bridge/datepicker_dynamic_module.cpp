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

#include "frameworks/core/components_ng/pattern/date_picker/bridge/datepicker_dynamic_module.h"

#include "core/common/dynamic_module.h"
#include "core/components_ng/pattern/date_picker/bridge/arkts_native_date_picker_bridge.h"
#include "core/components_ng/pattern/date_picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/date_picker/picker_model.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/date_picker/datepicker_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_DatePicker()
{
    return new OHOS::Ace::DatePickerDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUIDatePickerModifier* GetDatePickerDynamicModifier();
const CJUIDatePickerModifier* GetCJUIDatepickerModifier();
} // namespace NodeModifier
namespace DatePickerUtil {
const DatepickerCustomModifier* GetDatePickerCustomModifier();
} // namespace DatePickerUtil
namespace GeneratedModifier {
#ifdef INCLUDE_GENERATED_SOURCES
const GENERATED_ArkUIDatePickerModifier* GetDatePickerStaticModifier();
#endif
} // namespace GeneratedModifier
} // namespace NG
void DatePickerDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::DatePickerBridge::RegisterDatePickerAttributes(object, vm);
}

const void* DatePickerDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetDatePickerDynamicModifier();
}

const void* DatePickerDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetDatePickerStaticModifier();
#else
    return nullptr;
#endif
}

const void* DatePickerDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUIDatepickerModifier();
}

void* DatePickerDynamicModule::GetModel()
{
    static NG::DatePickerModelNG model;
    return &model;
}

const void* DatePickerDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == "customModifier") {
        return NG::DatePickerUtil::GetDatePickerCustomModifier();
    }
    return nullptr;
}
} // namespace OHOS::Ace
