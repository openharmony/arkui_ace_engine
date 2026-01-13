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

#include "core/components_ng/pattern/checkbox/bridge/arkts_native_checkbox_bridge.h"
#include "core/components_ng/pattern/checkbox/bridge/checkbox_custom_modifier.h"
#include "core/components_ng/pattern/checkbox/bridge/checkbox_dynamic_module.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"

#ifndef ARKUI_WEARABLE
#include "core/components_ng/pattern/checkbox/bridge/checkbox_content_modifier_helper.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_static.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Checkbox()
{
    return new OHOS::Ace::CheckboxDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUICheckboxModifier* GetCheckboxDynamicModifier();
const CJUICheckboxModifier* GetCJUICheckboxModifier();
const ArkUICheckboxCustomModifier* GetCheckboxCustomModifier();
constexpr const char* CUSTOM_MODIFIER = "customModifier";
#ifndef ARKUI_WEARABLE
namespace GeneratedModifier {
constexpr const char* CONTENT_MODIFIER = "contentModifier";
const GENERATED_ArkUICheckboxModifier* GetCheckboxStaticModifier();
const GENERATED_ArkUICheckboxContentModifier* GetCheckboxStaticContentModifier();
}
#endif
} // namespace NG

void CheckboxDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::CheckboxBridge::RegisterCheckboxAttributes(object, vm);
}

const void* CheckboxDynamicModule::GetDynamicModifier()
{
    return NG::GetCheckboxDynamicModifier();
}

const void* CheckboxDynamicModule::GetStaticModifier()
{
#ifndef ARKUI_WEARABLE
    return NG::GeneratedModifier::GetCheckboxStaticModifier();
#else
    return nullptr;
#endif
}

const void* CheckboxDynamicModule::GetCjModifier()
{
    return NG::GetCJUICheckboxModifier();
}

void* CheckboxDynamicModule::GetModel()
{
    static NG::CheckBoxModelNG model;
    return &model;
}

const void* CheckboxDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::CUSTOM_MODIFIER) {
        return NG::GetCheckboxCustomModifier();
    }
#ifndef ARKUI_WEARABLE
    if (name == NG::GeneratedModifier::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetCheckboxStaticContentModifier();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace
