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

#include "core/components_ng/pattern/blank/bridge/blank_dynamic_module.h"

#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/blank/bridge/arkts_native_blank_bridge.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Blank()
{
    return new OHOS::Ace::BlankDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIBlankModifier* GetBlankDynamicModifier();
const CJUIBlankModifier* GetCJUIBlankDynamicModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIBlankModifier* GetBlankStaticModifier();
}
#endif
} // namespace NG

void BlankDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::BlankBridge::RegisterBlankAttributes(object, vm);
}

const void* BlankDynamicModule::GetDynamicModifier()
{
    return NG::GetBlankDynamicModifier();
}

const void* BlankDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetBlankStaticModifier();
#else
    return nullptr;
#endif
}

const void* BlankDynamicModule::GetCjModifier()
{
    return NG::GetCJUIBlankDynamicModifier();
}

void* BlankDynamicModule::GetModel()
{
    static NG::BlankModelNG model;
    return &model;
}

} // namespace OHOS::Ace
