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

#include "core/components_ng/pattern/date_picker/bridge/datepickerdialog_dynamic_module.h"

#include "compatible/components/picker/picker_model_impl.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/common/dynamic_module.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/date_picker/bridge/arkts_native_datepickerdialog_bridge.h"
#include "core/components_ng/pattern/date_picker/bridge/datepicker_dynamic_module.h"
#include "core/components_ng/pattern/date_picker/bridge/datepicker_util.h"
#include "core/components_ng/pattern/date_picker/picker_model.h"
#include "core/components_ng/pattern/date_picker/datepicker_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/date_picker/datepicker_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_DatePickerDialog()
{
    return new OHOS::Ace::DatePickerDialogDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace DatePickerUtil {
const ArkUIDatePickerDialogModifier* GetDatePickerDialogStaticModifier();
} // namespace DatePickerUtil
namespace GeneratedModifier {
#ifdef INCLUDE_GENERATED_SOURCES
#ifdef WRONG_GEN_v140
GENERATED_ArkUIDatePickerDialogAccessor* GetDatePickerDialogStaticAccessor();
#endif // WRONG_GEN_v140
#endif
} // namespace GeneratedModifier
} // namespace NG

void DatePickerDialogDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::DatePickerDialogBridge::RegisterDatePickerDialogAttributes(object, vm);
}

const void* DatePickerDialogDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetDatePickerDynamicModifier();
}

const void* DatePickerDialogDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::DatePickerUtil::GetDatePickerDialogStaticModifier();
#else
    return nullptr;
#endif
}

void* DatePickerDialogDynamicModule::GetModel()
{
    static NG::DatePickerDialogModelNG model;
    return &model;
}

const void* DatePickerDialogDynamicModule::GetCustomModifier(const std::string& name)
{
    return nullptr;
}

} // namespace OHOS::Ace
