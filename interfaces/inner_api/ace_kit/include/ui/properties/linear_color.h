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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_LINEAR_COLOR_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_LINEAR_COLOR_H

#include "ui/properties/color.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT LinearColor {
public:
    LinearColor() = default;
    explicit LinearColor(uint32_t argb)
    {
        alpha_ = static_cast<int16_t>((argb & 0xFF000000) >> 24);
        red_ = static_cast<int16_t>((argb & 0x00FF0000) >> 16);
        green_ = static_cast<int16_t>((argb & 0x0000FF00) >> 8);
        blue_ = static_cast<int16_t>(argb & 0xFF);
    }
    explicit LinearColor(const Color& color)
        : alpha_(color.GetAlpha()), red_(color.GetRed()), green_(color.GetGreen()), blue_(color.GetBlue())
    {}
    LinearColor(int16_t alpha, int16_t red, int16_t green, int16_t blue)
        : alpha_(alpha), red_(red), green_(green), blue_(blue)
    {}
    ~LinearColor() = default;

    ACE_FORCE_EXPORT static const LinearColor TRANSPARENT;
    static const LinearColor WHITE;
    static const LinearColor BLACK;
    static const LinearColor RED;
    static const LinearColor GREEN;
    static const LinearColor BLUE;
    static const LinearColor GRAY;

    LinearColor operator+(const LinearColor& color) const
    {
        return LinearColor(GetAlpha() + color.GetAlpha(), GetRed() + color.GetRed(), GetGreen() + color.GetGreen(),
            GetBlue() + color.GetBlue());
    }

    LinearColor operator-(const LinearColor& color) const
    {
        return LinearColor(GetAlpha() - color.GetAlpha(), GetRed() - color.GetRed(), GetGreen() - color.GetGreen(),
            GetBlue() - color.GetBlue());
    }

    LinearColor operator*(double value) const
    {
        return LinearColor(static_cast<int16_t>(round(GetAlpha() * value)),
            static_cast<int16_t>(round(GetRed() * value)), static_cast<int16_t>(round(GetGreen() * value)),
            static_cast<int16_t>(round(GetBlue() * value)));
    }

    bool operator==(const LinearColor& color) const
    {
        return alpha_ == color.GetAlpha() && red_ == color.GetRed() && green_ == color.GetGreen() &&
               blue_ == color.GetBlue();
    }

    LinearColor& operator+=(const LinearColor& color) {
        alpha_ = alpha_ + color.GetAlpha();
        red_ = red_ + color.GetRed();
        green_ = green_ + color.GetGreen();
        blue_ = blue_ + color.GetBlue();
        return *this;
    }

    LinearColor& operator*=(float scale) {
        alpha_ = alpha_ * scale;
        red_ = red_ * scale;
        green_ = green_ * scale;
        blue_ = blue_ * scale;
        return *this;
    }

    LinearColor& operator-=(const LinearColor& color) {
        alpha_ = alpha_ - color.GetAlpha();
        red_ = red_ - color.GetRed();
        green_ = green_ - color.GetGreen();
        blue_ = blue_ - color.GetBlue();
        return *this;
    }

    int16_t GetRed() const
    {
        return red_;
    }

    int16_t GetGreen() const
    {
        return green_;
    }

    int16_t GetBlue() const
    {
        return blue_;
    }

    int16_t GetAlpha() const
    {
        return alpha_;
    }

    uint32_t GetValue() const
    {
        return (static_cast<uint32_t>(std::clamp<uint16_t>(blue_, 0, UINT8_MAX))) |
               (static_cast<uint32_t>((std::clamp<uint16_t>(green_, 0, UINT8_MAX)) << 8)) |
               (static_cast<uint32_t>((std::clamp<uint16_t>(red_, 0, UINT8_MAX)) << 16)) |
               (static_cast<uint32_t>((std::clamp<uint16_t>(alpha_, 0, UINT8_MAX)) << 24));
    }

    Color BlendOpacity(double opacityRatio) const
    {
        auto alpha = static_cast<int16_t>(GetAlpha() * opacityRatio);
        return Color::FromARGB(static_cast<uint8_t>(std::clamp<int16_t>(alpha, 0, UINT8_MAX)),
            static_cast<uint8_t>(std::clamp<int16_t>(red_, 0, UINT8_MAX)),
            static_cast<uint8_t>(std::clamp<int16_t>(green_, 0, UINT8_MAX)),
            static_cast<uint8_t>(std::clamp<int16_t>(blue_, 0, UINT8_MAX)));
    }

    Color ToColor() const
    {
        return Color::FromARGB(static_cast<uint8_t>(std::clamp<int16_t>(alpha_, 0, UINT8_MAX)),
            static_cast<uint8_t>(std::clamp<int16_t>(red_, 0, UINT8_MAX)),
            static_cast<uint8_t>(std::clamp<int16_t>(green_, 0, UINT8_MAX)),
            static_cast<uint8_t>(std::clamp<int16_t>(blue_, 0, UINT8_MAX)));
    }

private:
    int16_t alpha_;
    int16_t red_;
    int16_t green_;
    int16_t blue_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_BASE_PROPERTIES_LINEAR_COLOR_H
