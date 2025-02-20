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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BLUR_STYLE_OPTION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BLUR_STYLE_OPTION_H

#include "base/json/json_util.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/common_decoration.h"
#include "core/components_ng/base/inspector_filter.h"

namespace OHOS::Ace {
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
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BLUR_STYLE_OPTION_H
