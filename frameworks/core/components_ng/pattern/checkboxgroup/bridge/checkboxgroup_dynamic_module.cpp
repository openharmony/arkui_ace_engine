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

#include "core/components_ng/pattern/checkboxgroup/bridge/checkboxgroup_custom_modifier.h"
#include "core/components_ng/pattern/checkboxgroup/bridge/checkboxgroup_dynamic_module.h"
#include "core/components_ng/pattern/checkboxgroup/bridge/arkts_native_checkboxgroup_bridge.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/checkboxgroup/bridge/checkboxgroup_content_modifier_helper.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_static.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_CheckboxGroup()
{
    return new OHOS::Ace::CheckBoxGroupDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUICheckboxGroupModifier* GetCheckboxGroupDynamicModifier();
const CJUICheckboxGroupModifier* GetCJUICheckboxGroupModifier();
const ArkUICheckboxGroupCustomModifier* GetCheckboxGroupDynamicCustomModifier();
constexpr const char* CUSTOM_MODIFIER = "customModifier";
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONTENT_MODIFIER = "contentModifier";
constexpr const char* CONFIGURATION_ACCESSOR = "configurationAccessor";
const GENERATED_ArkUICheckboxGroupModifier* GetCheckboxGroupStaticModifier();
const GENERATED_ArkUICheckboxGroupContentModifier* GetCheckboxGroupStaticContentModifier();
const GENERATED_ArkUICheckBoxGroupConfigurationAccessor* GetCheckboxGroupStaticConfigurationAccessor();
}
#endif
} // namespace NG

void CheckBoxGroupDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::CheckboxGroupBridge::RegisterCheckboxGroupAttributes(object, vm);
}

const void* CheckBoxGroupDynamicModule::GetDynamicModifier()
{
    return NG::GetCheckboxGroupDynamicModifier();
}

const void* CheckBoxGroupDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetCheckboxGroupStaticModifier();
#else
    return nullptr;
#endif
}

const void* CheckBoxGroupDynamicModule::GetCjModifier()
{
    return NG::GetCJUICheckboxGroupModifier();
}

void* CheckBoxGroupDynamicModule::GetModel()
{
    static NG::CheckBoxGroupModelNG model;
    return &model;
}

const void* CheckBoxGroupDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::CUSTOM_MODIFIER) {
        return NG::GetCheckboxGroupDynamicCustomModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetCheckboxGroupStaticContentModifier();
    }
    if (name == NG::GeneratedModifier::CONFIGURATION_ACCESSOR) {
        return NG::GeneratedModifier::GetCheckboxGroupStaticConfigurationAccessor();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace
