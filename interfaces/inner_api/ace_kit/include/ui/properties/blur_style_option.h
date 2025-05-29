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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_BLUR_STYLE_OPTION_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_BLUR_STYLE_OPTION_H

#include "json/json_util.h"
#include "ui/properties/color.h"
#include "ui/base/geometry/dimension.h"
#include "ui/base/inspector_filter.h"
#include "ui/base/utils/utils.h"
#include "ui/resource/resource_object.h"
#include <functional>

namespace OHOS::Ace {
enum class BlurStyle {
    NO_MATERIAL = 0,
    THIN,
    REGULAR,
    THICK,
    BACKGROUND_THIN,
    BACKGROUND_REGULAR,
    BACKGROUND_THICK,
    BACKGROUND_ULTRA_THICK,
    COMPONENT_ULTRA_THIN,
    COMPONENT_THIN,
    COMPONENT_REGULAR,
    COMPONENT_THICK,
    COMPONENT_ULTRA_THICK,
    COMPONENT_ULTRA_THICK_WINDOW
};

enum class AdaptiveColor {
    DEFAULT = 0,
    AVERAGE,
};

enum class TransitionHierarchyStrategy {
    NONE = 0,
    ADAPTIVE,
};

struct BlurOption {
    std::vector<float> grayscale;
    bool operator==(const BlurOption& other) const
    {
        if (grayscale.size() != other.grayscale.size()) {
            return false;
        }
        return std::equal(grayscale.begin(), grayscale.end(), other.grayscale.begin());
    }

    bool operator!= (const BlurOption& other) const
    {
        return !(*this == other);
    }
};

enum class BlurStyleActivePolicy {
    FOLLOWS_WINDOW_ACTIVE_STATE = 0,
    ALWAYS_ACTIVE = 1,
    ALWAYS_INACTIVE = 2,
};

enum class BlurType {
    WITHIN_WINDOW = 0,
    BEHIND_WINDOW = 1
};

enum class EffectType {
    DEFAULT = 0,
    WINDOW_EFFECT = 1
};

struct EffectOption {
    Dimension radius;
    double saturation { 1.0f };
    double brightness { 1.0f };
    Color color { Color::TRANSPARENT };
    AdaptiveColor adaptiveColor = AdaptiveColor::DEFAULT;
    BlurOption blurOption = { std::vector<float>() };
    BlurType blurType = BlurType::WITHIN_WINDOW;
    BlurStyleActivePolicy policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    Color inactiveColor { Color::TRANSPARENT };
    bool isValidColor = false;
    bool isWindowFocused = true;
    bool operator == (const EffectOption &other) const
    {
        return radius == other.radius && NearEqual(saturation, other.saturation) &&
            NearEqual(brightness, other.brightness) && color == other.color && adaptiveColor == other.adaptiveColor &&
            policy == other.policy && blurType == other.blurType &&
            inactiveColor == other.inactiveColor && isValidColor == other.isValidColor &&
            isWindowFocused == other.isWindowFocused;
    }
    
    void ToJsonValue(std::unique_ptr<JsonValue> &json, const NG::InspectorFilter &filter) const
    {
        json->PutExtAttr("backgroundEffect", ToJsonValue(), filter);
    }

    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, EffectOption&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;

    std::unique_ptr<JsonValue> ToJsonValue() const
    {
        static const char* ADAPTIVE_COLOR[] = { "AdaptiveColor.Default", "AdaptiveColor.Average" };
        static const char* POLICY[] = { "BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE",
            "BlurStyleActivePolicy.ALWAYS_ACTIVE", "BlurStyleActivePolicy.ALWAYS_INACTIVE" };
        static const char* BLUR_TYPE[] = { "WITHIN_WINDOW", "BEHIND_WINDOW" };
        auto jsonEffect = JsonUtil::Create(true);
        auto jsonBrightnessOption = JsonUtil::Create(true);
        jsonBrightnessOption->Put("radius", radius.Value());
        jsonBrightnessOption->Put("saturation", saturation);
        jsonBrightnessOption->Put("brightness", brightness);
        jsonBrightnessOption->Put("color", color.ColorToString().c_str());
        jsonBrightnessOption->Put("adaptiveColor", ADAPTIVE_COLOR[static_cast<int32_t>(adaptiveColor)]);
        jsonBrightnessOption->Put("policy", POLICY[static_cast<int>(policy)]);
        jsonBrightnessOption->Put("type", BLUR_TYPE[static_cast<int>(blurType)]);
        jsonBrightnessOption->Put("inactiveColor", inactiveColor.ColorToString().c_str());
        auto grayscale = "[0,0]";
        if (blurOption.grayscale.size() > 1) {
            grayscale =
                ("[" + std::to_string(blurOption.grayscale[0]) + "," + std::to_string(blurOption.grayscale[1]) + "]")
                    .c_str();
        }
        jsonBrightnessOption->Put("blurOption", grayscale);
        jsonEffect->Put("options", jsonBrightnessOption);
        return jsonEffect;
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, EffectOption&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = {resObj, std::move(updateFunc)};
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }
};

struct MotionBlurAnchor {
    float x = 0.0f;
    float y = 0.0f;
    bool operator==(const MotionBlurAnchor& other) const
    {
        return NearEqual(x, other.x) && NearEqual(y, other.y);
    }
    bool operator!=(const MotionBlurAnchor& other) const
    {
        return !operator==(other);
    }
};

struct MotionBlurOption {
    float radius = 0.0f;
    MotionBlurAnchor anchor;
    bool operator==(const MotionBlurOption& other) const
    {
        return NearEqual(radius, other.radius) && anchor == other.anchor;
    }
    bool operator!=(const MotionBlurOption& other) const
    {
        return !operator==(other);
    }
};

enum class ThemeColorMode {
    SYSTEM = 0,
    LIGHT,
    DARK,
};

struct BlurStyleOption {
    BlurStyle blurStyle = BlurStyle::NO_MATERIAL;
    ThemeColorMode colorMode = ThemeColorMode::SYSTEM;
    AdaptiveColor adaptiveColor = AdaptiveColor::DEFAULT;
    double scale = 1.0;
    BlurOption blurOption;
    BlurStyleActivePolicy policy = BlurStyleActivePolicy::ALWAYS_ACTIVE;
    BlurType blurType = BlurType::WITHIN_WINDOW;
    Color inactiveColor { Color::TRANSPARENT };
    bool isValidColor = false;
    bool isWindowFocused = true;
    struct resourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, BlurStyleOption&)> updateFunc;
    };
    std::unordered_map<std::string, resourceUpdater> resMap_;
    bool operator==(const BlurStyleOption& other) const
    {
        return blurStyle == other.blurStyle && colorMode == other.colorMode && adaptiveColor == other.adaptiveColor &&
               NearEqual(scale, other.scale) && policy == other.policy && blurType == other.blurType &&
               inactiveColor == other.inactiveColor && isValidColor == other.isValidColor &&
               isWindowFocused == other.isWindowFocused;
    }
    void ToJsonValue(std::unique_ptr<JsonValue>& json, const NG::InspectorFilter& filter) const
    {
        /* no fixed attr below, just return */
        if (filter.IsFastFilter()) {
            return;
        }
        static const char* STYLE[] = { "BlurStyle.NONE", "BlurStyle.Thin", "BlurStyle.Regular", "BlurStyle.Thick",
            "BlurStyle.BACKGROUND_THIN", "BlurStyle.BACKGROUND_REGULAR", "BlurStyle.BACKGROUND_THICK",
            "BlurStyle.BACKGROUND_ULTRA_THICK", "BlurStyle.COMPONENT_ULTRA_THIN", "BlurStyle.COMPONENT_THIN",
            "BlurStyle.COMPONENT_REGULAR", "BlurStyle.COMPONENT_THICK", "BlurStyle.COMPONENT_ULTRA_THICK" };
        static const char* COLOR_MODE[] = { "ThemeColorMode.System", "ThemeColorMode.Light", "ThemeColorMode.Dark" };
        static const char* ADAPTIVE_COLOR[] = { "AdaptiveColor.Default", "AdaptiveColor.Average" };
        static const char* POLICY[] = { "BlurStyleActivePolicy.FOLLOWS_WINDOW_ACTIVE_STATE",
            "BlurStyleActivePolicy.ALWAYS_ACTIVE", "BlurStyleActivePolicy.ALWAYS_INACTIVE" };
        static const char* BLUR_TYPE[] = { "BlurType.WITHIN_WINDOW", "BlurType.BEHIND_WINDOW" };
        auto jsonBlurStyle = JsonUtil::Create(true);
        jsonBlurStyle->Put("value", STYLE[static_cast<int>(blurStyle)]);
        auto jsonBlurStyleOption = JsonUtil::Create(true);
        jsonBlurStyleOption->Put("colorMode", COLOR_MODE[static_cast<int>(colorMode)]);
        jsonBlurStyleOption->Put("adaptiveColor", ADAPTIVE_COLOR[static_cast<int>(adaptiveColor)]);
        jsonBlurStyleOption->Put("policy", POLICY[static_cast<int>(policy)]);
        jsonBlurStyleOption->Put("type", BLUR_TYPE[static_cast<int>(blurType)]);
        jsonBlurStyleOption->Put("inactiveColor", inactiveColor.ColorToString().c_str());
        jsonBlurStyleOption->Put("scale", scale);
        jsonBlurStyle->Put("options", jsonBlurStyleOption);

        json->PutExtAttr("backgroundBlurStyle", jsonBlurStyle, filter);
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, BlurStyleOption&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = {resObj, std::move(updateFunc)};
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_BLUR_STYLE_OPTION_H
