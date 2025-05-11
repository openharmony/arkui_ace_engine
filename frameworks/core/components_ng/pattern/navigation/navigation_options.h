/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_OPTIONS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_OPTIONS_H

#include <optional>

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"

namespace OHOS::Ace::NG {
struct NavigationBackgroundOptions {
    std::optional<Color> color;
    std::optional<BlurStyleOption> blurStyleOption;
    std::optional<EffectOption> effectOption;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, NavigationBackgroundOptions&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;

    bool operator== (const NavigationBackgroundOptions& other) const
    {
        return color == other.color && blurStyleOption == other.blurStyleOption && effectOption == other.effectOption;
    }

    bool operator!= (const NavigationBackgroundOptions& other) const
    {
        return !(*this == other);
    }

    void AddResource(const std::string& key, const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, NavigationBackgroundOptions&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = { resObj, std::move(updateFunc) };
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }
};

struct NavigationBarOptions {
    std::optional<BarStyle> barStyle;
    std::optional<CalcDimension> paddingStart;
    std::optional<CalcDimension> paddingEnd;
    bool textHideOptions = false;

    bool operator== (const NavigationBarOptions& other) const
    {
        return barStyle == other.barStyle && paddingStart == other.paddingStart
            && paddingEnd == other.paddingEnd;
    }

    bool operator!= (const NavigationBarOptions& other) const
    {
        return !(*this == other);
    }
};

struct MoreButtonOptions {
    NavigationBackgroundOptions bgOptions;

    bool operator== (const MoreButtonOptions& other) const
    {
        return bgOptions == other.bgOptions;
    }

    bool operator!= (const MoreButtonOptions& other) const
    {
        return !(*this == other);
    }
};

using TextStyleApplyFunc = std::function<void(WeakPtr<FrameNode>)>;
struct NavigationTextOptions {
    TextStyleApplyFunc mainTitleApplyFunc;
    TextStyleApplyFunc subTitleApplyFunc;

    void Reset()
    {
        mainTitleApplyFunc = nullptr;
        subTitleApplyFunc = nullptr;
    }
};

struct NavigationTitlebarOptions {
    NavigationBackgroundOptions bgOptions;
    NavigationBarOptions brOptions;
    NavigationTextOptions textOptions;
    bool enableHoverMode = false;

    bool operator== (const NavigationTitlebarOptions& other) const
    {
        return bgOptions == other.bgOptions && brOptions == other.brOptions
            && enableHoverMode == other.enableHoverMode;
    }

    bool operator!= (const NavigationTitlebarOptions& other) const
    {
        return !(*this == other);
    }
};

struct NavigationToolbarOptions {
    NavigationBackgroundOptions bgOptions;
    // toolBar not support paddingStart and paddingEnd of NavigationBarOptions now
    NavigationBarOptions brOptions;
    MoreButtonOptions mbOptions;

    bool operator== (const NavigationToolbarOptions& other) const
    {
        return bgOptions == other.bgOptions && brOptions == other.brOptions && mbOptions == other.mbOptions;
    }

    bool operator!= (const NavigationToolbarOptions& other) const
    {
        return !(*this == other);
    }
};

struct ImageOption {
    bool noPixMap;
    bool isValidImage;
};

struct NavigationMenuOptions {
    MoreButtonOptions mbOptions;

    bool operator== (const NavigationMenuOptions& other) const
    {
        return mbOptions == other.mbOptions;
    }

    bool operator!= (const NavigationMenuOptions& other) const
    {
        return !(*this == other);
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_OPTIONS_H
