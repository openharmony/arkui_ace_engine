/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/bridge/tab_content_dynamic_module.h"

#include "core/components_ng/pattern/tabs/bridge/arkts_native_tabcontent_bridge.h"
#include "core/components_ng/pattern/tabs/bridge/tab_content_custom_modifier.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_transition_proxy_modifier_api.h"
#endif

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_TabContent()
{
    return new OHOS::Ace::TabContentDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
namespace NodeModifier {
const ArkUITabContentModifier* GetTabContentDynamicModifier();
const ArkUITabContentCustomModifier* GetTabContentCustomModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUITabContentModifier* GetTabContentModifier();
const GENERATED_ArkUITabContentTransitionProxyAccessor* GetTabContentTransitionProxyAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void TabContentDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::TabContentBridge::RegisterTabContentAttributes(object, vm);
}

const void* TabContentDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetTabContentDynamicModifier();
}

const void* TabContentDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetTabContentModifier();
#else
    return nullptr;
#endif
}

const void* TabContentDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == "tabContentModifier") {
        return NG::GeneratedModifier::GetTabContentModifier();
    }
    if (name == "tabContentTransitionProxyAccessor") {
        return NG::GeneratedModifier::GetTabContentTransitionProxyAccessor();
    }
#endif
    if (name == "customModifier") {
        return NG::NodeModifier::GetTabContentCustomModifier();
    }
    return nullptr;
}

const void* TabContentDynamicModule::GetCjModifier()
{
    return nullptr;
}

void* TabContentDynamicModule::GetModel()
{
    static NG::TabContentModelNG model;
    return &model;
}

} // namespace OHOS::Ace
