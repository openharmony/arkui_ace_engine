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

#include "core/components/common/properties/color.h"

namespace OHOS::Ace {
const Color Color::TRANSPARENT = Color(0x00000000);
const Color Color::WHITE = Color(0xffffffff);
const Color Color::BLACK = Color(0xff000000);
const Color Color::RED = Color(0xffff0000);
const Color Color::GREEN = Color(0xff00ff00);
const Color Color::BLUE = Color(0xff0000ff);
const Color Color::GRAY = Color(0xffc0c0c0);
const Color Color::FOREGROUND = Color(0x00000001);

Color Color::FromString(std::string colorStr, uint32_t maskAlpha, Color defaultColor)
{
    (void)maskAlpha;
    if (colorStr.empty()) {
        return defaultColor;
    }
    if (colorStr == "#ffffffff" || colorStr == "#FFFFFFFF" || colorStr == "white") {
        return Color::WHITE;
    }
    if (colorStr == "#00000000") {
        return Color::TRANSPARENT;
    }
    return defaultColor;
}

std::string Color::ColorToString() const
{
    return "#00000000";
}

std::string Color::ToString() const
{
    return ColorToString();
}

Color Color::ChangeAlpha(uint8_t alpha) const
{
    uint32_t value = (GetValue() & 0x00ffffff) | (static_cast<uint32_t>(alpha) << 24);
    return Color(value, GetColorSpace());
}

std::string Color::ToSvgFillColorKey() const
{
    std::ostringstream oss;
    oss << ColorToString() << "_cs" << static_cast<int32_t>(colorSpace_);
    return oss.str();
}

Color Color::FromARGB(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
{
    return Color();
}

Color Color::ColorFromString(const std::string& str)
{
    (void)str;
    return Color();
}
} // namespace OHOS::Ace
