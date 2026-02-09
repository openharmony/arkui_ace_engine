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

#include "core/components_ng/pattern/menu/bridge/menu_item_group/menu_item_group_dynamic_module.h"

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_item_group_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/menu/arkts_native_menu_bridge.h"
#include "core/components_ng/pattern/menu/bridge/menu_item_group/arkts_native_menu_item_group_bridge.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view.h"
#include "core/interfaces/ani/ani_api.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view_static.h"
#endif
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_MenuItemGroup()
{
    return new OHOS::Ace::MenuItemGroupDynamicModule();
}

namespace OHOS::Ace {
typedef void (*ComponentAsyncEventHandler)(ArkUINodeHandle node, void* extraParam);
typedef void (*ResetComponentAsyncEventHandler)(ArkUINodeHandle node);

namespace NG {
const ArkUIMenuItemGroupModifier* GetMenuItemGroupDynamicModifier();
const CJUIMenuItemGroupModifier* GetCJUIMenuItemGroupModifier();
namespace InnerModifier {
constexpr const char* MENU_ITEM_GROUP_INNER_MODIFIER = "menuItemGroupInnerModifier";
const ArkUIMenuItemGroupInnerModifier* GetMenuItemGroupInnerModifier();
} // namespace InnerModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
const GENERATED_ArkUIMenuItemGroupModifier* GetMenuItemGroupStaticModifier();
}
#endif
} // namespace NG

void MenuItemGroupDynamicModule::RegisterAttributes(
    panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::MenuItemGroupBridge::RegisterMenuItemGroupAttributes(object, vm);
}

const void* MenuItemGroupDynamicModule::GetDynamicModifier()
{
    return NG::GetMenuItemGroupDynamicModifier();
}

const void* MenuItemGroupDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetMenuItemGroupStaticModifier();
#else
    return nullptr;
#endif
}

const void* MenuItemGroupDynamicModule::GetCjModifier()
{
    return NG::GetCJUIMenuItemGroupModifier();
}

void* MenuItemGroupDynamicModule::GetModel()
{
    static NG::MenuItemGroupView model;
    return &model;
}

const void* MenuItemGroupDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::InnerModifier::MENU_ITEM_GROUP_INNER_MODIFIER) {
        return NG::InnerModifier::GetMenuItemGroupInnerModifier();
    }
    return nullptr;
}
} // namespace OHOS::Ace