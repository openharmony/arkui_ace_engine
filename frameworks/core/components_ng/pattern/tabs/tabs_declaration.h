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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_DECLARATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_DECLARATION_H

#include <cstdint>
#include <string>
#include <functional>
#include <optional>
#include "core/common/resource/resource_object.h"

namespace OHOS::Ace::NG {

enum class TabBarLayoutStyle {
    BOTTOM = 0,
    SIDEBAR,
    SIDEBAR_ADAPTABLE,
};

enum class TabBarDisplayMode {
    BOTTOMTABBAR = 0,
    SIDEBAR,
};

enum class TabVisibility {
    VISIBLE = 0,
    HIDDEN,
};

struct TabContentDefaultVisibility {
    TabVisibility visibility = TabVisibility::VISIBLE;
    std::optional<TabBarDisplayMode> displayMode;
    bool isNull = true;

    bool operator==(const TabContentDefaultVisibility& other) const
    {
        if (isNull != other.isNull) {
            return false;
        }
        if (isNull) {
            return true;
        }
        return visibility == other.visibility && displayMode == other.displayMode;
    }

    bool operator!=(const TabContentDefaultVisibility& other) const
    {
        return !(*this == other);
    }
};

struct TabBarDisplayModeBreakpoint {
    TabBarDisplayMode sm = TabBarDisplayMode::BOTTOMTABBAR;
    TabBarDisplayMode md = TabBarDisplayMode::BOTTOMTABBAR;
    TabBarDisplayMode lg = TabBarDisplayMode::SIDEBAR;
    bool isNull = false;

    bool operator==(const TabBarDisplayModeBreakpoint& other) const
    {
        if (isNull != other.isNull) {
            return false;
        }
        if (isNull) {
            return true;
        }
        return sm == other.sm && md == other.md && lg == other.lg;
    }

    bool operator!=(const TabBarDisplayModeBreakpoint& other) const
    {
        return !(*this == other);
    }
};

struct TabsSidebarSearchableOptions {
    std::optional<std::string> searchText;
    std::optional<std::string> placeholder;
    std::function<void(const std::string& text)> searchCallback;
    std::function<bool(int32_t tabIndex, const std::string& text)> searchFilter;
    RefPtr<ResourceObject> searchTextResObj;
    RefPtr<ResourceObject> placeholderResObj;
    bool isNull = true;

    bool operator==(const TabsSidebarSearchableOptions& other) const
    {
        if (isNull != other.isNull) {
            return false;
        }
        if (isNull) {
            return true;
        }
        return searchText == other.searchText && placeholder == other.placeholder &&
            searchTextResObj == other.searchTextResObj && placeholderResObj == other.placeholderResObj;
    }

    bool operator!=(const TabsSidebarSearchableOptions& other) const
    {
        return !(*this == other);
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_TABS_TABS_DECLARATION_H
