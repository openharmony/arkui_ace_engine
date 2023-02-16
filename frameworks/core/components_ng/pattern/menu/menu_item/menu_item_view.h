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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_VIEW_H

#include <functional>
#include <optional>

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
struct MenuItemProperties {
    std::string content;
    std::optional<std::string> startIcon;
    std::optional<std::string> endIcon;
    std::optional<std::string> labelInfo;
    std::optional<std::function<void()>> buildFunc;
};

class ACE_EXPORT MenuItemView {
public:
    // createMenuItem with custom
    static void Create(const RefPtr<UINode>& customNode);

    // createMenuItem with startIcon, content, endIcon, labelInfo
    static void Create(const MenuItemProperties& props);

    static void SetSelected(bool isSelected = false);
    static void SetSelectIcon(bool isShow = false);
    static void SetOnChange(std::function<void(bool)>&& onChange);

private:
    static void AddIcon(const std::optional<std::string>& startIcon, const RefPtr<FrameNode>& row);
    static void AddContent(const std::string& content, const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& menuItem);
    static void AddLabelInfo(
        const std::optional<std::string>& labelInfo, const RefPtr<FrameNode>& row, const RefPtr<FrameNode>& menuItem);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_MENU_MENU_ITEM_VIEW_H
