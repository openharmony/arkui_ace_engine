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

#include "core/components_ng/pattern/time_picker/bridge/timepickerdialog_dynamic_module.h"

#include "compatible/components/picker/timepicker_model_impl.h"

#include "bridge/arkts_frontend/koala_projects/arkoala-arkts/framework/native/src/generated/arkoala_api_generated.h"
#include "core/common/dynamic_module.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/time_picker/bridge/arkts_native_timepickerdialog_bridge.h"
#include "core/components_ng/pattern/time_picker/bridge/timepicker_dynamic_module.h"
#include "core/components_ng/pattern/time_picker/bridge/timepicker_util.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/time_picker/timepicker_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_TimePickerDialog()
{
    return new OHOS::Ace::TimePickerDialogDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace TimePickerUtil {
const ArkUITimePickerDialogModifier* GetTimePickerDialogStaticModifier();
} // namespace TimePickerUtil
namespace GeneratedModifier {
#ifdef INCLUDE_GENERATED_SOURCES
GENERATED_ArkUITimePickerDialogAccessor* GetTimePickerDialogStaticAccessor();
#endif
} // namespace GeneratedModifier
} // namespace NG

void TimePickerDialogDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::TimePickerDialogBridge::RegisterTimePickerDialogAttributes(object, vm);
}

const void* TimePickerDialogDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetTimePickerDynamicModifier();
}

const void* TimePickerDialogDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::TimePickerUtil::GetTimePickerDialogStaticModifier();
#else
    return nullptr;
#endif
}

void* TimePickerDialogDynamicModule::GetModel()
{
    static NG::TimePickerDialogModelNG model;
    return &model;
}

const void* TimePickerDialogDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == "customModifier") {
        return NG::TimePickerUtil::GetTimePickerCustomModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == "configurationAccessor") {
        return NG::GeneratedModifier::GetTimePickerDialogStaticAccessor();
    }
#else
    return nullptr;
#endif
    return nullptr;
}

} // namespace OHOS::Ace
