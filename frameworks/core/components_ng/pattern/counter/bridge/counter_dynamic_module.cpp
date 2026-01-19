/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/counter/bridge/counter_dynamic_module.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "core/components_ng/pattern/counter/bridge/arkts_native_counter_bridge.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/counter/counter_model_static.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Counter()
{
    return new OHOS::Ace::CounterDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUICounterModifier* GetCounterDynamicModifier();
const CJUICounterModifier* GetCJUICounterModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUICounterModifier* GetCounterStaticModifier();
}
#endif
} // namespace NG

void CounterDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::CounterBridge::RegisterCounterAttributes(object, vm);
}

const void* CounterDynamicModule::GetDynamicModifier()
{
    return NG::GetCounterDynamicModifier();
}

const void* CounterDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetCounterStaticModifier();
#else
    return nullptr;
#endif
}

const void* CounterDynamicModule::GetCjModifier()
{
    return NG::GetCJUICounterModifier();
}

void* CounterDynamicModule::GetModel()
{
    static NG::CounterModelNG model;
    return &model;
}

} // namespace OHOS::Ace
