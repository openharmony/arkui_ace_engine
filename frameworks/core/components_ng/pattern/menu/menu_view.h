/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_VIEW_H

#include <string>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/select/select_model.h"
#include "core/components_ng/pattern/text/text_styles.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT MenuView {
public:
    // create menu with menuItems
    static RefPtr<FrameNode> Create(std::vector<OptionParam>&& params, int32_t targetId,
        const std::string& targetTag = "", MenuType type = MenuType::MENU, const MenuParam& menuParam = MenuParam());

    // create menu with custom node from a builder
    static RefPtr<FrameNode> Create(const RefPtr<UINode>& customNode, int32_t targetId,
        const std::string& targetTag = "", MenuType type = MenuType::MENU, const MenuParam& menuParam = MenuParam(),
        bool withWrapper = true);

    // create select's popup menu
    static RefPtr<FrameNode> Create(const std::vector<SelectParam>& params, int32_t targetId);

private:
    static void UpdateMenuPaintProperty(
        const RefPtr<FrameNode>& menuNode, const MenuParam& menuParam, const MenuType& isContextMenu);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_VIEW_H
