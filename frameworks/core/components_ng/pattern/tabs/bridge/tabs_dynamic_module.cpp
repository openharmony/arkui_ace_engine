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

#include "core/components_ng/pattern/tabs/bridge/tabs_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/tabs/bridge/arkts_native_tabcontent_bridge.h"
#include "core/components_ng/pattern/tabs/bridge/arkts_native_tabs_bridge.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_custom_modifier.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_controller_modifier_api.h"
#include "core/components_ng/pattern/tabs/bridge/tabs_transition_proxy_modifier_api.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Tabs()
{
    return new OHOS::Ace::TabsDynamicModule();
}

namespace OHOS::Ace {
namespace NG {
namespace NodeModifier {
const ArkUITabsModifier* GetTabsModifier();
const CJUITabsModifier* GetCJUITabsModifier();
const ArkUITabsCustomModifier* GetTabsCustomModifier();
} // namespace NodeModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUITabsModifier* GetTabsModifier();
const GENERATED_ArkUITabsExtenderAccessor* GetTabsExtenderAccessor();
const GENERATED_ArkUITabsControllerAccessor* GetTabsControllerAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void TabsDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::TabsBridge::RegisterTabsAttributes(object, vm);
    NG::TabContentBridge::RegisterTabContentAttributes(object, vm);
}

const void* TabsDynamicModule::GetDynamicModifier()
{
    return NG::NodeModifier::GetTabsModifier();
}

const void* TabsDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetTabsModifier();
#else
    return nullptr;
#endif
}

const void* TabsDynamicModule::GetCjModifier()
{
    return NG::NodeModifier::GetCJUITabsModifier();
}

void* TabsDynamicModule::GetModel()
{
    static NG::TabsModelNG model;
    return &model;
}

const void* TabsDynamicModule::GetCustomModifier(const std::string& name)
{
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == "tabsModifier") {
        return NG::GeneratedModifier::GetTabsModifier();
    }
    if (name == "tabsExtenderAccessor") {
        return NG::GeneratedModifier::GetTabsExtenderAccessor();
    }
    if (name == "tabsControllerAccessor") {
        return NG::GeneratedModifier::GetTabsControllerAccessor();
    }
#endif
    if (name == "tabsCustomModifier") {
        return NG::NodeModifier::GetTabsCustomModifier();
    }
    if (name == "tabsController") {
        return NG::NodeModifier::GetTabsControllerModifier();
    }
    if (name == "tabsTransitionProxy") {
        return NG::NodeModifier::GetTabsTransitionProxyModifier();
    }
    return nullptr;
}
} // namespace OHOS::Ace
