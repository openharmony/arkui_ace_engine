/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/pattern_lock_modifier.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/pipeline/base/element_register.h"
namespace OHOS::Ace::NG {
void SetPatternLockActiveColor(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveColor(frameNode, Color(value));
}

void ResetPatternLockActiveColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color activeColor = patternLockTheme->GetActiveColor();
    PatternLockModelNG::SetActiveColor(frameNode, activeColor);
}

void ResetPatternLockCircleRadius(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension radius = patternLockTheme->GetCircleRadius();
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(radius.Value(), radius.Unit()));
}

void SetPatternLockCircleRadius(NodeHandle node, double number, int8_t unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void SetPatternLockSelectedColor(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSelectedColor(frameNode, Color(value));
}

void ResetPatternLockSelectedColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color selectedColor = patternLockTheme->GetSelectedColor();
    PatternLockModelNG::SetSelectedColor(frameNode, selectedColor);
}

void SetPatternLockSideLength(NodeHandle node, double number, int8_t unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSideLength(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetPatternLockSideLength(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension sideLength = patternLockTheme->GetSideLength();
    PatternLockModelNG::SetSideLength(frameNode, Dimension(sideLength.Value(), sideLength.Unit()));
}

void SetPatternLockAutoReset(NodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetAutoReset(frameNode, static_cast<bool>(value));
}

void ResetPatternLockAutoReset(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetAutoReset(frameNode, true);
}

void SetPatternLockPathStrokeWidth(NodeHandle node, double number, int8_t unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetStrokeWidth(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetPatternLockPathStrokeWidth(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension lineWidth = patternLockTheme->GetPathStrokeWidth();
    PatternLockModelNG::SetStrokeWidth(frameNode, lineWidth);
}

void SetPatternLockRegularColor(NodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetRegularColor(frameNode, Color(color));
}

void ResetPatternLockRegularColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color regularColor = patternLockTheme->GetRegularColor();
    PatternLockModelNG::SetRegularColor(frameNode, regularColor);
}

void SetPatternLockPathColor(NodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPathColor(frameNode, Color(color));
}

void ResetPatternLockPathColor(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color pathColor = patternLockTheme->GetPathColor();
    PatternLockModelNG::SetPathColor(frameNode, pathColor);
}

ArkUIPatternLockModifierAPI GetPatternLockModifier()
{
    static const ArkUIPatternLockModifierAPI modifier = {
        SetPatternLockActiveColor, ResetPatternLockActiveColor, SetPatternLockCircleRadius,
        ResetPatternLockCircleRadius, SetPatternLockSelectedColor, ResetPatternLockSelectedColor,
        SetPatternLockSideLength, ResetPatternLockSideLength, SetPatternLockAutoReset,
        ResetPatternLockAutoReset, SetPatternLockPathStrokeWidth, ResetPatternLockPathStrokeWidth,
        SetPatternLockRegularColor, ResetPatternLockRegularColor, SetPatternLockPathColor,
        ResetPatternLockPathColor
    };
    return modifier;
}
} // namespace OHOS::Ace::NG