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
#include <utility>
#include <vector>
#include "ui/base/geometry/calc_dimension.h"
#include "ui/base/geometry/dimension.h"
#include "ui/properties/color.h"
#include "ui/properties/gradient_property.h"

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/blur_style_option.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "interfaces/inner_api/ace_kit/include/ui/properties/ui_material.h"

namespace OHOS::Ace::NG {
constexpr double DEFAULT_BLUR_RADIUS = 40;

enum class ScrollEffectType {
    COMMON_BLUR = 0,
    GRADUAL_BLUR
};

struct ScrollEffectOptions {
    ScrollEffectType scrollEffectType = ScrollEffectType::COMMON_BLUR;
    std::optional<CalcDimension> blurEffectiveStartOffset;
    std::optional<CalcDimension> blurEffectiveEndOffset;

    bool operator==(const ScrollEffectOptions& other) const
    {
        return scrollEffectType == other.scrollEffectType &&
               blurEffectiveStartOffset == other.blurEffectiveStartOffset &&
               blurEffectiveEndOffset == other.blurEffectiveEndOffset;
    }

    bool operator!=(const ScrollEffectOptions& other) const
    {
        return !(*this == other);
    }
};

struct NavigationBackgroundOptions {
    std::optional<Color> color;
    std::optional<BlurStyleOption> blurStyleOption;
    std::optional<EffectOption> effectOption;
    std::optional<ScrollEffectOptions> scrollEffectOptions;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, NavigationBackgroundOptions&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;

    bool operator== (const NavigationBackgroundOptions& other) const
    {
        return color == other.color && blurStyleOption == other.blurStyleOption &&
            effectOption == other.effectOption && scrollEffectOptions == other.scrollEffectOptions;
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

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const NG::InspectorFilter& filter) const
    {
        // add backgroundBlurStyleOptions
        if (bgOptions.blurStyleOption.has_value()) {
            bgOptions.blurStyleOption.value().ToJsonValue(json, filter);
        } else {
            json->PutExtAttr("backgroundBlurStyle", JsonUtil::Create(true), filter);
        }
        // add backgroundEffect
        if (bgOptions.effectOption.has_value()) {
            bgOptions.effectOption.value().ToJsonValue(json, filter);
        } else {
            json->PutExtAttr("backgroundEffect", JsonUtil::Create(true), filter);
        }
        // add backgroundBlurStyle
        if (bgOptions.blurStyleOption.has_value()) {
            const char* STYLE[] = { "BlurStyle.NONE", "BlurStyle.Thin", "BlurStyle.Regular", "BlurStyle.Thick",
                "BlurStyle.BACKGROUND_THIN", "BlurStyle.BACKGROUND_REGULAR", "BlurStyle.BACKGROUND_THICK",
                "BlurStyle.BACKGROUND_ULTRA_THICK", "BlurStyle.COMPONENT_ULTRA_THIN", "BlurStyle.COMPONENT_THIN",
                "BlurStyle.COMPONENT_REGULAR", "BlurStyle.COMPONENT_THICK", "BlurStyle.COMPONENT_ULTRA_THICK" };
            int32_t styleEnum = static_cast<int32_t>(bgOptions.blurStyleOption.value().blurStyle);
            json->PutExtAttr("backgroundBlurStyleValue", STYLE[styleEnum], filter);
        } else {
            json->PutExtAttr("backgroundBlurStyleValue", "undefined", filter);
        }
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
    bool enableCustomTitlePaddingCheck = false;
    RefPtr<UiMaterial> material = nullptr;

    bool operator== (const NavigationTitlebarOptions& other) const
    {
        return bgOptions == other.bgOptions && brOptions == other.brOptions &&
               enableHoverMode == other.enableHoverMode &&
               enableCustomTitlePaddingCheck == other.enableCustomTitlePaddingCheck;
    }

    bool operator!= (const NavigationTitlebarOptions& other) const
    {
        return !(*this == other);
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const NG::InspectorFilter& filter) const
    {
        // add backgroundBlurStyleOptions
        if (bgOptions.blurStyleOption.has_value()) {
            bgOptions.blurStyleOption.value().ToJsonValue(json, filter);
        } else {
            json->PutExtAttr("backgroundBlurStyle", JsonUtil::Create(true), filter);
        }
        // add backgroundEffect
        if (bgOptions.effectOption.has_value()) {
            bgOptions.effectOption.value().ToJsonValue(json, filter);
        } else {
            json->PutExtAttr("backgroundEffect", JsonUtil::Create(true), filter);
        }
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

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const NG::InspectorFilter& filter) const
    {
        // add backgroundBlurStyleOptions
        if (bgOptions.blurStyleOption.has_value()) {
            bgOptions.blurStyleOption.value().ToJsonValue(json, filter);
        } else {
            json->PutExtAttr("backgroundBlurStyle", JsonUtil::Create(true), filter);
        }
        // add backgroundEffect
        if (bgOptions.effectOption.has_value()) {
            bgOptions.effectOption.value().ToJsonValue(json, filter);
        } else {
            json->PutExtAttr("backgroundEffect", JsonUtil::Create(true), filter);
        }
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

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const NG::InspectorFilter& filter) const
    {
        mbOptions.ToJsonValue(json, filter);
    }
};

struct NavigationTitleBarBackgroundStyle {
    Color backgroundColor;
    double opacity = 1.0f;
    Dimension blurRadius;
    int32_t brightness = 0;
    CalcDimension offset;
    std::optional<LinearGradientBlurPara> linearGradientBlur;

    bool operator==(const NavigationTitleBarBackgroundStyle& other) const
    {
        return backgroundColor == other.backgroundColor && opacity == other.opacity &&
            blurRadius == other.blurRadius && brightness == other.brightness && offset == other.offset &&
            linearGradientBlur == other.linearGradientBlur;
    }

    bool operator!=(const NavigationTitleBarBackgroundStyle& other) const
    {
        return !(*this == other);
    }
};

struct NavigationTitleBarDividerStyle {
    Color color;
    double opacity = 1.0f;

    bool operator==(const NavigationTitleBarDividerStyle& other) const
    {
        return color == other.color && opacity == other.opacity;
    }

    bool operator!=(const NavigationTitleBarDividerStyle& other) const
    {
        return !(*this == other);
    }
};

struct NavigationTitleBarStyle {
    Color titleColor;
    Color buttonTextColor;
    Color subTitleColor;
    Color iconColor;
    NavigationTitleBarBackgroundStyle iconBackgroundStyle;
    NavigationTitleBarBackgroundStyle backgroundStyle;
    NavigationTitleBarDividerStyle dividerStyle;
    std::optional<std::vector<Shadow>> titleShadow;
    std::optional<std::vector<Shadow>> subTitleShadow;

    bool operator==(const NavigationTitleBarStyle& other) const
    {
        return titleColor == other.titleColor && buttonTextColor == other.buttonTextColor &&
            subTitleColor == other.subTitleColor && iconColor == other.iconColor &&
            iconBackgroundStyle == other.iconBackgroundStyle &&
            backgroundStyle == other.backgroundStyle && dividerStyle == other.dividerStyle &&
            titleShadow == other.titleShadow && subTitleShadow == other.subTitleShadow;
    }

    bool operator!=(const NavigationTitleBarStyle& other) const
    {
        return !(*this == other);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_NAVIGATION_OPTIONS_H
