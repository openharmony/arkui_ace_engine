/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "base/log/log_wrapper.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_view_static.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef ACE_UNITTEST
const GENERATED_ArkUIMenuItemGroupModifier* GetMenuItemGroupStaticModifier();
#endif

const GENERATED_ArkUIMenuItemGroupModifier* GetMenuItemGroupModifier()
{
#ifdef ACE_UNITTEST
    return GetMenuItemGroupStaticModifier();
#else
    static const GENERATED_ArkUIMenuItemGroupModifier* modifier = nullptr;
    if (modifier == nullptr) {
        auto module = DynamicModuleHelper::GetInstance().GetDynamicModule("MenuItemGroup");
        if (module == nullptr) {
            LOGF("Can't find MenuItemGroup dynamic module");
            abort();
        }
        modifier = reinterpret_cast<const GENERATED_ArkUIMenuItemGroupModifier*>(module->GetStaticModifier());
    }
    return modifier;
#endif
}
} // namespace OHOS::Ace::NG::GeneratedModifier
