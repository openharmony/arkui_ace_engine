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

#include "core/components_ng/pattern/stepper/bridge/arkts_native_stepper_bridge.h"
#include "core/components_ng/pattern/stepper/bridge/stepper_dynamic_module.h"
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Stepper()
{
    return new OHOS::Ace::StepperDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIStepperModifier* GetStepperDynamicModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
#ifdef WRONG_GEN_v140
const GENERATED_ArkUIStepperModifier* GetStepperStaticModifier();
#endif // WRONG_GEN_v140
} // namespace GeneratedModifier
#endif
} // namespace NG

void StepperDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::StepperBridge::RegisterStepperAttributes(object, vm);
}

const void* StepperDynamicModule::GetDynamicModifier()
{
    return NG::GetStepperDynamicModifier();
}

const void* StepperDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
#ifdef WRONG_GEN_v140
    return NG::GeneratedModifier::GetStepperStaticModifier();
#else // WRONG_GEN_v140
    return nullptr;
#endif // WRONG_GEN_v140
#else
    return nullptr;
#endif
}

const void* StepperDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* StepperDynamicModule::GetModel()
{
    static NG::StepperModelNG model;
    return &model;
}

} // namespace OHOS::Ace
