/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/bridge/menu_item/menu_item_dynamic_module.h"

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_item_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/menu/arkts_native_menu_bridge.h"
#include "core/components_ng/pattern/menu/bridge/menu_item/arkts_native_menu_item_bridge.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/interfaces/ani/ani_api.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_static.h"
#endif
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_MenuItem()
{
    return new OHOS::Ace::MenuItemDynamicModule();
}

namespace OHOS::Ace {
typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
typedef void (*ResetComponentAsyncEventHandler)(ArkUINodeHandle node);

namespace NG {
const ArkUIMenuItemModifier* GetMenuItemDynamicModifier();
const CJUIMenuItemModifier* GetCJUIMenuItemModifier();
namespace InnerModifier {
constexpr const char* MENU_ITEM_INNER_MODIFIER = "menuItemInnerModifier";
const ArkUIMenuItemInnerModifier* GetMenuItemInnerModifier();
} // namespace InnerModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONFIGURATION_ACCESSOR = "configurationAccessor";
const GENERATED_ArkUIMenuItemModifier* GetMenuItemStaticModifier();
const GENERATED_ArkUIMenuItemConfigurationAccessor* GetMenuItemStaticConfigurationAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void MenuItemDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::MenuItemBridge::RegisterMenuItemAttributes(object, vm);
}

const void* MenuItemDynamicModule::GetDynamicModifier()
{
    return NG::GetMenuItemDynamicModifier();
}

const void* MenuItemDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetMenuItemStaticModifier();
#else
    return nullptr;
#endif
}

const void* MenuItemDynamicModule::GetCjModifier()
{
    return NG::GetCJUIMenuItemModifier();
}

void* MenuItemDynamicModule::GetModel()
{
    static NG::MenuItemModelNG menuModel;
    return &menuModel;
}

const void* MenuItemDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::InnerModifier::MENU_ITEM_INNER_MODIFIER) {
        return NG::InnerModifier::GetMenuItemInnerModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONFIGURATION_ACCESSOR) {
        return NG::GeneratedModifier::GetMenuItemStaticConfigurationAccessor();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace