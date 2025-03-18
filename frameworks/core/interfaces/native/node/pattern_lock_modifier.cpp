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
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
namespace OHOS::Ace::NG {
void SetPatternLockActiveColor(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveColor(frameNode, Color(value));
}

void ResetPatternLockActiveColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color activeColor = patternLockTheme->GetActiveColor();
    PatternLockModelNG::SetActiveColor(frameNode, activeColor);
}

void ResetPatternLockCircleRadius(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension radius = patternLockTheme->GetCircleRadius();
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(radius.Value(), radius.Unit()));
}

void SetPatternLockCircleRadius(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void SetPatternLockSelectedColor(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSelectedColor(frameNode, Color(value));
}

void ResetPatternLockSelectedColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color selectedColor = patternLockTheme->GetSelectedColor();
    PatternLockModelNG::SetSelectedColor(frameNode, selectedColor);
}

void SetPatternLockSideLength(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSideLength(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetPatternLockSideLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension sideLength = patternLockTheme->GetSideLength();
    PatternLockModelNG::SetSideLength(frameNode, Dimension(sideLength.Value(), sideLength.Unit()));
}

void SetPatternLockAutoReset(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetAutoReset(frameNode, static_cast<bool>(value));
}

void ResetPatternLockAutoReset(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetAutoReset(frameNode, true);
}

void SetPatternLockPathStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetStrokeWidth(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetPatternLockPathStrokeWidth(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension lineWidth = patternLockTheme->GetPathStrokeWidth();
    PatternLockModelNG::SetStrokeWidth(frameNode, lineWidth);
}

void SetPatternLockRegularColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetRegularColor(frameNode, Color(color));
}

void ResetPatternLockRegularColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color regularColor = patternLockTheme->GetRegularColor();
    PatternLockModelNG::SetRegularColor(frameNode, regularColor);
}

void SetPatternLockPathColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPathColor(frameNode, Color(color));
}

void ResetPatternLockPathColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color pathColor = patternLockTheme->GetPathColor();
    PatternLockModelNG::SetPathColor(frameNode, pathColor);
}

void SetPatternLockActiveCircleColor(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleColor(frameNode, Color(value));
}

void ResetPatternLockActiveCircleColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleColor(frameNode, Color::TRANSPARENT);
}

void SetPatternLockActiveCircleRadius(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleRadius(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void ResetPatternLockActiveCircleRadius(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension radius = patternLockTheme->GetCircleRadius();
    PatternLockModelNG::SetActiveCircleRadius(frameNode, Dimension(0.0f, DimensionUnit::VP));
}

void SetPatternLockEnableWaveEffect(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetEnableWaveEffect(frameNode, static_cast<bool>(value));
}

void ResetPatternLockEnableWaveEffect(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetEnableWaveEffect(frameNode, true);
}

void SetPatternLockEnableForeground(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetEnableForeground(frameNode, static_cast<bool>(value));
}

void ResetPatternLockEnableForeground(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetEnableForeground(frameNode, false);
}

void SetPatternLockSkipUnselectedPoint(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSkipUnselectedPoint(frameNode, static_cast<bool>(value));
}

void ResetPatternLockSkipUnselectedPoint(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSkipUnselectedPoint(frameNode, false);
}

void SetPatternLockOnPatternComplete(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPatternComplete = reinterpret_cast<NG::PatternLockCompleteEvent*>(callback);
        PatternLockModelNG::SetPatternComplete(frameNode, std::move(*onPatternComplete));
    } else {
        PatternLockModelNG::SetPatternComplete(frameNode, nullptr);
    }
}

void ResetPatternLockOnPatternComplete(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPatternComplete(frameNode, nullptr);
}

void SetPatternLockOnDotConnect(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDotConnect = reinterpret_cast<std::function<void(int32_t)>*>(callback);
        PatternLockModelNG::SetDotConnect(frameNode, std::move(*onDotConnect));
    } else {
        PatternLockModelNG::SetDotConnect(frameNode, nullptr);
    }
}

void ResetPatternLockOnDotConnect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetDotConnect(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUIPatternLockModifier* GetPatternLockModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIPatternLockModifier modifier = {
        .setPatternLockActiveColor = SetPatternLockActiveColor,
        .resetPatternLockActiveColor = ResetPatternLockActiveColor,
        .setPatternLockCircleRadius = SetPatternLockCircleRadius,
        .resetPatternLockCircleRadius = ResetPatternLockCircleRadius,
        .setPatternLockSelectedColor = SetPatternLockSelectedColor,
        .resetPatternLockSelectedColor = ResetPatternLockSelectedColor,
        .setPatternLockSideLength = SetPatternLockSideLength,
        .resetPatternLockSideLength = ResetPatternLockSideLength,
        .setPatternLockAutoReset = SetPatternLockAutoReset,
        .resetPatternLockAutoReset = ResetPatternLockAutoReset,
        .setPatternLockPathStrokeWidth = SetPatternLockPathStrokeWidth,
        .resetPatternLockPathStrokeWidth = ResetPatternLockPathStrokeWidth,
        .setPatternLockRegularColor = SetPatternLockRegularColor,
        .resetPatternLockRegularColor = ResetPatternLockRegularColor,
        .setPatternLockPathColor = SetPatternLockPathColor,
        .resetPatternLockPathColor = ResetPatternLockPathColor,
        .setPatternLockActiveCircleColor = SetPatternLockActiveCircleColor,
        .resetPatternLockActiveCircleColor = ResetPatternLockActiveCircleColor,
        .setPatternLockActiveCircleRadius = SetPatternLockActiveCircleRadius,
        .resetPatternLockActiveCircleRadius = ResetPatternLockActiveCircleRadius,
        .setPatternLockEnableWaveEffect = SetPatternLockEnableWaveEffect,
        .resetPatternLockEnableWaveEffect = ResetPatternLockEnableWaveEffect,
        .setPatternLockEnableForeground = SetPatternLockEnableForeground,
        .resetPatternLockEnableForeground = ResetPatternLockEnableForeground,
        .setPatternLockSkipUnselectedPoint = SetPatternLockSkipUnselectedPoint,
        .resetPatternLockSkipUnselectedPoint = ResetPatternLockSkipUnselectedPoint,
        .setPatternLockOnPatternComplete = SetPatternLockOnPatternComplete,
        .resetPatternLockOnPatternComplete = ResetPatternLockOnPatternComplete,
        .setPatternLockOnDotConnect = SetPatternLockOnDotConnect,
        .resetPatternLockOnDotConnect = ResetPatternLockOnDotConnect,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIPatternLockModifier* GetCJUIPatternLockModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIPatternLockModifier modifier = {
        .setPatternLockActiveColor = SetPatternLockActiveColor,
        .resetPatternLockActiveColor = ResetPatternLockActiveColor,
        .setPatternLockCircleRadius = SetPatternLockCircleRadius,
        .resetPatternLockCircleRadius = ResetPatternLockCircleRadius,
        .setPatternLockSelectedColor = SetPatternLockSelectedColor,
        .resetPatternLockSelectedColor = ResetPatternLockSelectedColor,
        .setPatternLockSideLength = SetPatternLockSideLength,
        .resetPatternLockSideLength = ResetPatternLockSideLength,
        .setPatternLockAutoReset = SetPatternLockAutoReset,
        .resetPatternLockAutoReset = ResetPatternLockAutoReset,
        .setPatternLockPathStrokeWidth = SetPatternLockPathStrokeWidth,
        .resetPatternLockPathStrokeWidth = ResetPatternLockPathStrokeWidth,
        .setPatternLockRegularColor = SetPatternLockRegularColor,
        .resetPatternLockRegularColor = ResetPatternLockRegularColor,
        .setPatternLockPathColor = SetPatternLockPathColor,
        .resetPatternLockPathColor = ResetPatternLockPathColor,
        .setPatternLockActiveCircleColor = SetPatternLockActiveCircleColor,
        .resetPatternLockActiveCircleColor = ResetPatternLockActiveCircleColor,
        .setPatternLockActiveCircleRadius = SetPatternLockActiveCircleRadius,
        .resetPatternLockActiveCircleRadius = ResetPatternLockActiveCircleRadius,
        .setPatternLockEnableWaveEffect = SetPatternLockEnableWaveEffect,
        .resetPatternLockEnableWaveEffect = ResetPatternLockEnableWaveEffect,
        .setPatternLockEnableForeground = SetPatternLockEnableForeground,
        .resetPatternLockEnableForeground = ResetPatternLockEnableForeground,
        .setPatternLockSkipUnselectedPoint = SetPatternLockSkipUnselectedPoint,
        .resetPatternLockSkipUnselectedPoint = ResetPatternLockSkipUnselectedPoint,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
