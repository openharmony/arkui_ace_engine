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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_MENU_VIEW_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_MENU_VIEW_H

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "ui/base/geometry/dimension.h"
#include "ui/base/macros.h"
#include "ui/base/referenced.h"
#include "ui/view/frame_node.h"

namespace OHOS::Ace::Kit {

enum class MenuType {
    MENU,
    CONTEXT_MENU,

    NAVIGATION_MENU = 5,
};

struct OptionParam {
    std::string value;
    std::string icon;
    std::string labelInfo;
    bool enabled = true;
    std::function<void()> action;
    std::function<void(void*)> symbol = nullptr;
    std::optional<Dimension> symbolUserDefinedIdealFontSize = std::nullopt;
    bool disableSystemClick = false;
    bool isPasteOption = false;
};

struct MenuParam {
    bool isShowInSubWindow = false;
    int32_t placement;
    int32_t targetId;
    std::string targetTag;
};

class ACE_FORCE_EXPORT MenuView {
public:
    // create menu with menuItems
    static RefPtr<FrameNode> Create(std::vector<OptionParam>&& params, MenuType type, const MenuParam& menuParam);
};
} // OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_COMPONENTS_MENU_VIEW_H
