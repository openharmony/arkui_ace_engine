/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_MENU_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_MENU_MODIFIER_H

#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_view_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_inner_modifier.h"
#include "core/components_ng/pattern/menu/bridge/inner_modifier/menu_manager_inner_modifier.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUIMenuModifier* GetMenuModifier();
const CJUIMenuModifier* GetCJUIMenuModifier();
const ArkUIMenuInnerModifier* GetMenuInnerModifier();
const ArkUIMenuViewInnerModifier* GetMenuViewInnerModifier();
const ArkUIMenuManagerInnerModifier* GetMenuManagerInnerModifier();
}

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_MENU_MODIFIER_H