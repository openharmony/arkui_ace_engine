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

#include "core/components_ng/pattern/divider/bridge/divider_dynamic_module.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "core/components_ng/pattern/divider/bridge/arkts_native_divider_bridge.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Divider()
{
    return new OHOS::Ace::DividerDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIDividerModifier* GetDividerDynamicModifier();
const CJUIDividerModifier* GetCJUIDividerDynamicModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIDividerModifier* GetDividerStaticModifier();
}
#endif
} // namespace NG

void DividerDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::DividerBridge::RegisterDividerAttributes(object, vm);
}

const void* DividerDynamicModule::GetDynamicModifier()
{
    return NG::GetDividerDynamicModifier();
}

const void* DividerDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetDividerStaticModifier();
#else
    return nullptr;
#endif
}

const void* DividerDynamicModule::GetCjModifier()
{
    return NG::GetCJUIDividerDynamicModifier();
}

void* DividerDynamicModule::GetModel()
{
    static NG::DividerModelNG model;
    return &model;
}

} // namespace OHOS::Ace
