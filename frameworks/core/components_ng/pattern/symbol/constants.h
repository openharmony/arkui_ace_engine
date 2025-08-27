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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_SYMBOL_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TEXT_SYMBOL_CONSTANTS_H

#include <cstdint>
#include "core/components/common/properties/color.h"

namespace OHOS::Ace {

enum class SymbolEffectType {
    NONE = 0,
    SCALE,
    HIERARCHICAL,
    APPEAR,
    DISAPPEAR,
    BOUNCE,
    PULSE,
    REPLACE,
    DISABLE,
    QUICK_REPLACE,
};

enum class CommonSubType {
    DOWN = 0,
    UP,
};

enum class ScopeType {
    LAYER = 0,
    WHOLE,
};

enum class FillStyle {
    CUMULATIVE = 0,
    ITERATIVE,
};

enum class SymbolType {
    SYSTEM = 0,
    CUSTOM,
};

enum class SymbolGradientType {
    NONE = 0,
    COLOR_SHADER,
    RADIAL_GRADIENT,
    LINEAR_GRADIENT,
};

enum class GradientDefinedStatus {
    GRADIENT_TYPE = 1,
    GRADIENT_DEFAULT_COLOR = 2
};

enum class SDKGradientDirection {
    Left,
    Top,
    Right,
    Bottom,
    LeftTop,
    LeftBottom,
    RightTop,
    RightBottom,
    None
};

static const std::unordered_map<SDKGradientDirection, float> GRADIENT_DIRECTION_TO_ANGLE = {
    {SDKGradientDirection::Left,        270.0f},
    {SDKGradientDirection::Top,           0.0f},
    {SDKGradientDirection::Right,        90.0f},
    {SDKGradientDirection::Bottom,      180.0f},
    {SDKGradientDirection::LeftTop,     315.0f},
    {SDKGradientDirection::LeftBottom,  225.0f},
    {SDKGradientDirection::RightTop,     45.0f},
    {SDKGradientDirection::RightBottom, 135.0f},
    {SDKGradientDirection::None,        180.0f}
};

struct SymbolGradient {
    SymbolGradientType type = SymbolGradientType::NONE;
    GradientDefinedStatus gradientType = GradientDefinedStatus::GRADIENT_DEFAULT_COLOR;
    std::vector<Color> symbolColor;
    std::vector<float> symbolOpacities;
    bool repeating = false;
    std::optional<float> angle;
    std::optional<Dimension> radius;
    std::optional<Dimension> radialCenterX;
    std::optional<Dimension> radialCenterY;

    bool operator==(const SymbolGradient& other) const
    {
    return type == other.type &&
           radialCenterX == other.radialCenterX &&
           radialCenterY == other.radialCenterY &&
           symbolColor == other.symbolColor &&
           symbolOpacities.size() == other.symbolOpacities.size() &&
           std::equal(symbolOpacities.begin(), symbolOpacities.end(), other.symbolOpacities.begin(),
                     [](float a, float b) { return NearZero(a - b); }) &&
           repeating == other.repeating &&
           gradientType == other.gradientType &&
           ((!angle && !other.angle) || (angle && other.angle && NearZero(*angle - *other.angle))) &&
           radius == other.radius;
    }
};

struct SymbolShadow {
    Color color = Color::BLACK;
    std::pair<float, float> offset{0.0f, 0.0f};
    float radius = 0.0f;
    bool operator==(const SymbolShadow& other) const
    {
        return color == other.color &&
               NearZero(offset.first - other.offset.first) &&
               NearZero(offset.second - other.offset.second) &&
               NearZero(radius - other.radius);
    }

    bool IsDefault() const
    {
        return color == Color::BLACK &&
               NearZero(offset.first) &&
               NearZero(offset.second) &&
               NearZero(radius);
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_H
