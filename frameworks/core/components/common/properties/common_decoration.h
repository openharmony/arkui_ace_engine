/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_COMMON_DECORATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_COMMON_DECORATION_H

#include "core/components/common/properties/color.h"

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
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_COMMON_DECORATION_H