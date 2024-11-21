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

struct EffectOption {
    Dimension radius;
    double saturation { 1.0f };
    double brightness { 1.0f };
    Color color { Color::TRANSPARENT };
    AdaptiveColor adaptiveColor = AdaptiveColor::DEFAULT;
    BlurOption blurOption;
    bool operator == (const EffectOption &other) const
    {
        return radius == other.radius && NearEqual(saturation, other.saturation) &&
            NearEqual(brightness, other.brightness) && color == other.color && adaptiveColor == other.adaptiveColor;
    }
    
    void ToJsonValue(std::unique_ptr<JsonValue> &json, const NG::InspectorFilter &filter) const
    {
        json->PutExtAttr("backgroundEffect", ToJsonValue(), filter);
    }

    std::unique_ptr<JsonValue> ToJsonValue() const
    {
        static const char* ADAPTIVE_COLOR[] = { "AdaptiveColor.Default", "AdaptiveColor.Average" };
        auto jsonEffect = JsonUtil::Create(true);
        auto jsonBrightnessOption = JsonUtil::Create(true);
        jsonBrightnessOption->Put("radius", radius.Value());
        jsonBrightnessOption->Put("saturation", saturation);
        jsonBrightnessOption->Put("brightness", brightness);
        jsonBrightnessOption->Put("color", color.ColorToString().c_str());
        jsonBrightnessOption->Put("adaptiveColor", ADAPTIVE_COLOR[static_cast<int32_t>(adaptiveColor)]);
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