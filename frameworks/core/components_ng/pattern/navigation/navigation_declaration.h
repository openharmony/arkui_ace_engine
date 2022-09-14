/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_NAVIGATION_NAVIGATION_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_NAVIGATION_NAVIGATION_DECLARATION_H

#include <string>

#include "base/geometry/dimension.h"
#include "core/components/declaration/common/declaration.h"

namespace OHOS::Ace::NG {
// TODO：move some items to theme
// title bar back button
const std::string BACK_BUTTON = "Back";
constexpr InternalResource::ResourceId BACK_ICON = InternalResource::ResourceId::IC_BACK;
constexpr InternalResource::ResourceId MORE_ICON = InternalResource::ResourceId::IC_MORE;
constexpr float BACK_BUTTON_WIDTH = 100.0f;
// title bar and tool bar, bar item
constexpr float BAR_ITEM_WIDTH = 40.0f;
constexpr float BAR_ITEM_HEIGHT = 60.0f;
constexpr float ICON_SIZE = 40.0f;
constexpr float ICON_PADDING = 10.0f;
constexpr float TEXT_TOP_PADDING = 2.0f;
constexpr float BAR_TEXT_FONT_SIZE = 18.0f;
// title bar title and subtitle
constexpr float TITLE_WIDTH = 100.0f;
constexpr float TITLE_HEIGHT = 40.0f;
constexpr float SUBTITLE_HEIGHT = 40.0f;
constexpr Dimension TITLE_FONT_SIZE = 20.0_vp;
constexpr Dimension SUBTITLE_FONT_SIZE = 14.0_vp;
constexpr float TITLEBAR_HEIGHT = 120.0f;
// toolbar
constexpr float TOOLBAR_HEIGHT = 60.0f;
// single page maximum width
constexpr float SINGLE_PAGE_MAXIMUM_WIDTH = 720.0f;

struct BarItem {
    std::optional<std::string> text;
    std::optional<std::string> icon;
    std::function<void()> action;
    std::string ToString() const
    {
        std::string result;
        result.append("text: ");
        result.append(text.value_or("na"));
        result.append(", icon: ");
        result.append(icon.value_or("na"));
        return result;
    }
};

enum class TitleBarChildType {
    TITLE = 0,
    SUBTITLE,
    MENU,
};

enum class NavigationTitleMode {
    FREE = 0,
    FULL,
    MINI,
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_DECLARATION_NAVIGATION_NAVIGATION_DECLARATION_H