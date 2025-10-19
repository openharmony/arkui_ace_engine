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

#include "core/components_ng/pattern/menu/menu_item/menu_item_model_static.h"

namespace OHOS::Ace::NG {
void MenuItemModelStatic::AddRowChildMultiThread(
    const RefPtr<NG::FrameNode>& menuItem, const MenuItemProperties& menuItemProps)
{
    CHECK_NULL_VOID(menuItem);
    menuItem->PostAfterAttachMainTreeTask([weak = WeakPtr<NG::FrameNode>(menuItem), menuItemProps]() {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        AddRowChildBase(frameNode, menuItemProps);
    });
}
} // namespace OHOS::Ace::NG
