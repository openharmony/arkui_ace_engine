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

#include "core/interfaces/native/node/menu_modifier.h"
#include "core/interfaces/native/node/menu_item_modifier.h"
#include "core/interfaces/native/node/menu_item_group_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_view_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_manager_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_item_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_item_group_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/menu/menu_dynamic_module.h"
#include "core/components_ng/pattern/menu/bridge/menu_item/menu_item_dynamic_module.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
namespace OHOS::Ace::NG {
namespace NodeModifier {
const ArkUIMenuViewInnerModifier* GetMenuViewInnerModifier()
{
    return InnerModifier::GetMenuViewInnerModifier();
}

const ArkUIMenuManagerInnerModifier* GetMenuManagerInnerModifier()
{
    return InnerModifier::GetMenuManagerInnerModifier();
}

const ArkUIMenuItemInnerModifier* GetMenuItemInnerModifier()
{
    return InnerModifier::GetMenuItemInnerModifier();
}

const ArkUIMenuItemGroupInnerModifier* GetMenuItemGroupInnerModifier()
{
    return InnerModifier::GetMenuItemGroupInnerModifier();
}

const ArkUIMenuInnerModifier* GetMenuInnerModifier()
{
    return InnerModifier::GetMenuInnerModifier();
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG