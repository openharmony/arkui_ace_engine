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

#include "core/components_ng/pattern/menu/bridge/menu/menu_dynamic_module.h"

#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_manager_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_view_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/menu/arkts_native_menu_bridge.h"
#include "core/components_ng/pattern/menu/bridge/menu_item/arkts_native_menu_item_bridge.h"
#include "core/components_ng/pattern/menu/menu_model_ng.h"
#include "core/interfaces/ani/ani_api.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/menu/menu_model_static.h"
#endif
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_DynamicModule_Create_Menu()
{
    return new OHOS::Ace::MenuDynamicModule();
}

namespace OHOS::Ace {

namespace NG {
const ArkUIMenuModifier* GetMenuDynamicModifier();
const CJUIMenuModifier* GetCJUIMenuModifier();
namespace InnerModifier {
constexpr const char* MENU_INNER_MODIFIER = "menuInnerModifier";
const ArkUIMenuInnerModifier* GetMenuInnerModifier();
constexpr const char* MENU_VIEW_INNER_MODIFIER = "menuViewInnerModifier";
const ArkUIMenuViewInnerModifier* GetMenuViewInnerModifier();
constexpr const char* MENU_MANAGER_INNER_MODIFIER = "menuManagerInnerModifier";
const ArkUIMenuManagerInnerModifier* GetMenuManagerInnerModifier();
} // namespace InnerModifier
#ifdef INCLUDE_GENERATED_SOURCES
namespace GeneratedModifier {
constexpr const char* CONTEXT_MENU_ACCESSOR = "contextMenuAccessor";
const GENERATED_ArkUIMenuModifier* GetMenuStaticModifier();
const GENERATED_ArkUIContextMenuAccessor* GetContextMenuAccessor();
} // namespace GeneratedModifier
#endif
} // namespace NG

void MenuDynamicModule::RegisterAttributes(panda::Local<panda::ObjectRef> object, panda::ecmascript::EcmaVM* vm)
{
    NG::MenuBridge::RegisterMenuAttributes(object, vm);
}

const void* MenuDynamicModule::GetDynamicModifier()
{
    return NG::GetMenuDynamicModifier();
}

const void* MenuDynamicModule::GetStaticModifier()
{
#ifdef INCLUDE_GENERATED_SOURCES
    return NG::GeneratedModifier::GetMenuStaticModifier();
#else
    return nullptr;
#endif
}

const void* MenuDynamicModule::GetCjModifier()
{
    return NG::GetCJUIMenuModifier();
}

void* MenuDynamicModule::GetModel()
{
    static NG::MenuModelNG menuModel;
    return &menuModel;
}

const void* MenuDynamicModule::GetCustomModifier(const std::string& name)
{
    if (name == NG::InnerModifier::MENU_INNER_MODIFIER) {
        return NG::InnerModifier::GetMenuInnerModifier();
    }
    if (name == NG::InnerModifier::MENU_VIEW_INNER_MODIFIER) {
        return NG::InnerModifier::GetMenuViewInnerModifier();
    }
    if (name == NG::InnerModifier::MENU_MANAGER_INNER_MODIFIER) {
        return NG::InnerModifier::GetMenuManagerInnerModifier();
    }
#ifdef INCLUDE_GENERATED_SOURCES
    if (name == NG::GeneratedModifier::CONTEXT_MENU_ACCESSOR) {
        return NG::GeneratedModifier::GetContextMenuAccessor();
    }
#endif
    return nullptr;
}

} // namespace OHOS::Ace