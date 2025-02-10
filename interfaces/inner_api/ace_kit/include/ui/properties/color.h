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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_COLOR_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_COLOR_H

#include <cstdint>
#include <string>
#include <vector>

#include "ui/base/macros.h"

namespace OHOS::Ace {

constexpr uint32_t COLOR_ALPHA_MASK = 0xff000000;

union ColorParam {
#if BIG_ENDIANNESS
    struct {
        uint8_t alpha;
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    } argb;
#else
    struct {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t alpha;
    } argb;
#endif
    uint32_t value;
};

// A color value present by 32 bit.
class ACE_FORCE_EXPORT Color {
public:
    Color() = default;
    constexpr explicit Color(uint32_t value) : colorValue_(ColorParam { .value = value }) {}
    constexpr explicit Color(uint32_t value, uint32_t resId)
        : colorValue_(ColorParam { .value = value }), resourceId_(resId) {}
    ~Color() = default;

    static Color FromARGB(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue);
    static Color FromRGBO(uint8_t red, uint8_t green, uint8_t blue, double opacity);
    static Color FromRGB(uint8_t red, uint8_t green, uint8_t blue);
    // Need to change the input parameters, it is more appropriate to use the passed value here.
    static Color FromString(std::string colorStr, uint32_t maskAlpha = COLOR_ALPHA_MASK,
        Color defaultColor = Color::BLACK);
    static bool ParseColorString(std::string colorStr, Color& color, uint32_t maskAlpha = COLOR_ALPHA_MASK);
    static bool ParseColorString(const std::string& colorStr, Color& color, const Color& defaultColor,
        uint32_t maskAlpha = COLOR_ALPHA_MASK);
    // Return the linear transition color from startColor to endColor.
    static const Color LineColorTransition(const Color& startColor, const Color& endColor, double percent);

    static const Color TRANSPARENT;
    static const Color WHITE;
    static const Color BLACK;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color GRAY;
    static const Color FOREGROUND;

    Color BlendColor(const Color& overlayColor) const;

    Color BlendColorWithAlpha(const Color& overlayColor) const;
    Color BlendOpacity(double opacityRatio) const;
    Color ChangeOpacity(double opacity) const;
    Color ChangeAlpha(uint8_t alpha) const;

    void SetValue(uint32_t value)
    {
        colorValue_.value = value;
    }

    uint32_t GetValue() const
    {
        return colorValue_.value;
    }

    void SetResourceId(uint32_t id)
    {
        resourceId_ = id;
    }

    uint32_t GetResourceId() const
    {
        return resourceId_;
    }

    uint8_t GetAlpha() const
    {
        return colorValue_.argb.alpha;
    }

    uint8_t GetRed() const
    {
        return colorValue_.argb.red;
    }

    uint8_t GetGreen() const
    {
        return colorValue_.argb.green;
    }

    uint8_t GetBlue() const
    {
        return colorValue_.argb.blue;
    }

    void UpdateColorByResourceId();

    bool operator==(const Color& color) const
    {
        return colorValue_.value == color.GetValue();
    }

    bool operator!=(const Color& color) const
    {
        return !operator==(color);
    }

    Color operator+(const Color& color) const;

    Color operator-(const Color& color) const;

    Color operator*(double value) const;

    Color operator/(double value) const;

    std::string ColorToString() const;

    static Color ColorFromString(const std::string& str);
    static bool MatchColorHexString(const std::string& colorStr);
    static bool MatchColorWithMagic(std::string& colorStr, uint32_t maskAlpha, Color& color);
    static bool MatchColorWithMagicMini(std::string& colorStr, uint32_t maskAlpha, Color& color);
    static bool MatchColorSpecialString(const std::string& colorStr, Color& color);

    std::string ToString() const;

private:
    constexpr explicit Color(ColorParam colorValue) : colorValue_(colorValue) {}

    static double ConvertGammaToLinear(uint8_t value);
    static void ConvertGammaToLinear(
        const Color& gammaColor, double& linearRed, double& linearGreen, double& linearBlue);
    static uint8_t ConvertLinearToGamma(double value);
    static Color ConvertLinearToGamma(double alpha, double linearRed, double linearGreen, double linearBlue);
    static bool MatchColorWithRGB(const std::string& colorStr, Color& color);
    static bool MatchColorWithRGBA(const std::string& colorStr, Color& color);
    static bool ParseUintColorString(const std::string& colorStr, Color& color);
    static bool ParseUintColorString(const std::string& colorStr, Color& color, const Color& defaultColor);
    static bool IsRGBValid(int value);
    static bool IsOpacityValid(double value);
    static bool FastCheckColorType(const std::string& colorStr, const std::string& expectPrefix,
        const std::vector<size_t>& expectLengths);
    static bool IsHexNumber(std::string& colorStr);

    float CalculateBlend(float alphaLeft, float alphaRight, float valueLeft, float valueRight) const;
    ColorParam colorValue_ { .value = 0xff000000 };
    uint32_t resourceId_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_COLOR_H
