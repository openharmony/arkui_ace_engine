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

#include "core/components_ng/pattern/toggle/bridge/toggle_dynamic_module.h"

#include "core/components_ng/pattern/toggle/bridge/arkts_native_toggle_bridge.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/toggle/bridge/toggle_content_modifier_helper.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Toggle()
{
    return new OHOS::Ace::ToggleDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIToggleModifier* GetToggleDynamicModifier();
const CJUIToggleModifier* GetCJUIToggleDynamicModifier();

#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONTENT_MODIFIER = "contentModifier";
constexpr const char* EXTENDER_ACCESSOR = "extenderAccessor";
const GENERATED_ArkUIToggleModifier* GetToggleStaticModifier();
const ArkUIToggleStaticContentModifier* GetToggleStaticContentModifier();
const GENERATED_ArkUIToggleExtenderAccessor* GetToggleStaticExtenderAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void ToggleDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::ToggleBridge::RegisterToggleAttributes(object, vm);
}

const void* ToggleDynamicModule::GetDynamicModifier()
{
    return NG::GetToggleDynamicModifier();
}

const void* ToggleDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetToggleStaticModifier();
#else
    return nullptr;
#endif
}

const void* ToggleDynamicModule::GetCjModifier()
{
    return NG::GetCJUIToggleDynamicModifier();
}

void* ToggleDynamicModule::GetModel()
{
    static NG::ToggleModelNG model;
    return &model;
}

const void* ToggleDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONTENT_MODIFIER) {
        return NG::GeneratedModifier::GetToggleStaticContentModifier();
    }
    if (name == NG::GeneratedModifier::EXTENDER_ACCESSOR) {
        return NG::GeneratedModifier::GetToggleStaticExtenderAccessor();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace
