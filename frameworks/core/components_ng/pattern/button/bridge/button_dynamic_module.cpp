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

#include "core/components_ng/pattern/button/bridge/arkts_native_button_bridge.h"
#include "core/components_ng/pattern/button/bridge/button_custom_modifier.h"
#include "core/components_ng/pattern/button/bridge/button_dynamic_module.h"
#include "core/components_ng/pattern/button/button_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/button/bridge/button_content_modifier_helper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Button()
{
    return new OHOS::Ace::ButtonDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIButtonModifier* GetButtonDynamicModifier();
const CJUIButtonModifier* GetCJUIButtonModifier();
const ArkUIButtonCustomModifier* GetButtonCustomModifier();
constexpr const char* CUSTOM_MODIFIER = "customModifier";
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONTENT_MODIFIER = "contentModifier";
const GENERATED_ArkUIButtonModifier* GetButtonStaticModifier();
const GENERATED_ArkUIButtonContentModifier* GetButtonStaticContentModifier();
} // namespace GeneratedModifier
#endif
} // namespace NG

void ButtonDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::ButtonBridge::RegisterButtonAttributes(object, vm);
}

const void* ButtonDynamicModule::GetDynamicModifier()
{
    return NG::GetButtonDynamicModifier();
}

const void* ButtonDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetButtonStaticModifier();
#else
    return nullptr;
#endif
}

const void* ButtonDynamicModule::GetCjModifier()
{
    return NG::GetCJUIButtonModifier();
}

void* ButtonDynamicModule::GetModel()
{
    static NG::ButtonModelNG model;
    return &model;
}

const void* ButtonDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::CUSTOM_MODIFIER) {
        return NG::GetButtonCustomModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetButtonStaticContentModifier();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace