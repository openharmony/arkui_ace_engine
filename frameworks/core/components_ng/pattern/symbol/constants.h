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
    Disable,
    QuickReplace,
};

// need check
enum class RenderingStrategy {
    SINGLE = 0,
    MULTIPLE_COLOR,
    MULTIPLE_OPACITY
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
    COLOR_SHADER = 0,
    RADIAL_GRADIENT,
    LINEAR_GRADIENT,
};

struct Point2F {
    float x{0.0f};
    float y{0.0f};
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
    {SDKGradientDirection::Left,      270.0f},
    {SDKGradientDirection::Top,         0.0f},
    {SDKGradientDirection::Right,      90.0f},
    {SDKGradientDirection::Bottom,    180.0f},
    {SDKGradientDirection::LeftTop,   315.0f},
    {SDKGradientDirection::LeftBottom,225.0f},
    {SDKGradientDirection::RightTop,   45.0f},
    {SDKGradientDirection::RightBottom,135.0f},
    {SDKGradientDirection::None,        0.0f}
};

struct SymbolGradient {
    SymbolGradientType type = SymbolGradientType::COLOR_SHADER;
    Point2F center;
    std::vector<Color> symbolColor;
    std::vector<float> positions;
    bool repeating = false;
    float angle = 0.0f;
    float radius = 0.0f;

    bool operator==(const SymbolGradient& other) const {
        return type == other.type;
    }
};

struct SymbolShadow{
    Color color = Color::BLACK;
    std::pair<float, float> offset{0.0, 0.0};
    double radius = 0.0;
    bool operator==(const SymbolShadow& other) const {
        return color == other.color &&
               offset == other.offset &&
               std::abs(radius - other.radius) < 1e-6;
    }

    bool IsDefault() const {
        return color == Color::BLACK &&
               std::abs(offset.first) < 1e-6f &&
               std::abs(offset.second) < 1e-6f &&
               std::abs(radius) < 1e-6;
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_LAYOUT_CONSTANTS_H
