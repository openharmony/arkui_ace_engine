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

#include "core/components_ng/pattern/radio/bridge/arkts_native_radio_bridge.h"
#include "core/components_ng/pattern/radio/bridge/radio_dynamic_module.h"
#include "core/components_ng/pattern/radio/radio_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/radio/bridge/radio_content_modifier_helper.h"
#include "core/components_ng/pattern/radio/radio_model_static.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Radio()
{
    return new OHOS::Ace::RadioDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIRadioModifier* GetRadioDynamicModifier();
const CJUIRadioModifier* GetCJUIRadioModifier();
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONTENT_MODIFIER = "contentModifier";
const GENERATED_ArkUIRadioModifier* GetRadioStaticModifier();
const GENERATED_ArkUIRadioContentModifier* GetRadioStaticContentModifier();
}
#endif
} // namespace NG

void RadioDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::RadioBridge::RegisterRadioAttributes(object, vm);
}

const void* RadioDynamicModule::GetDynamicModifier()
{
    return NG::GetRadioDynamicModifier();
}

const void* RadioDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetRadioStaticModifier();
#else
    return nullptr;
#endif
}

const void* RadioDynamicModule::GetCjModifier()
{
    return NG::GetCJUIRadioModifier();
}

void* RadioDynamicModule::GetModel()
{
    static NG::RadioModelNG model;
    return &model;
}

const void* RadioDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetRadioStaticContentModifier();
    }
#endif
    return nullptr;
}
} // namespace OHOS::Ace