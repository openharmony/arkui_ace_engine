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

void SetPatternLockActiveColorRes(ArkUINodeHandle node, uint32_t value, void* activeColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveColor(frameNode, Color(value));
    if (SystemProperties::ConfigChangePerform()) {
        auto* activeColor = reinterpret_cast<ResourceObject*>(activeColorRawPtr);
        auto activeColorResObj = AceType::Claim(activeColor);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::ACTIVECOLOR, activeColorResObj);
    }
}

void ResetPatternLockActiveColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color activeColor = patternLockTheme->GetActiveColor();
    PatternLockModelNG::SetActiveColor(frameNode, activeColor);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetActiveColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::ACTIVECOLOR, nullptr);
    }
}

void ResetPatternLockCircleRadius(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension radius = patternLockTheme->GetCircleRadius();
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(radius.Value(), radius.Unit()));
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::CIRCLERADIUS, nullptr);
    }
}

void SetPatternLockCircleRadius(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void SetPatternLockCircleRadiusRes(
    ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* circleRadiusRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetCircleRadius(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    if (SystemProperties::ConfigChangePerform()) {
        auto* circleRadius = reinterpret_cast<ResourceObject*>(circleRadiusRawPtr);
        auto circleRadiusResObj = AceType::Claim(circleRadius);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::CIRCLERADIUS, circleRadiusResObj);
    }
}

void SetPatternLockSelectedColor(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSelectedColor(frameNode, Color(value));
}

void SetPatternLockSelectedColorRes(ArkUINodeHandle node, uint32_t value, void* selectedColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSelectedColor(frameNode, Color(value));
    if (SystemProperties::ConfigChangePerform()) {
        auto* selectedColor = reinterpret_cast<ResourceObject*>(selectedColorRawPtr);
        auto selectedColorResObj = AceType::Claim(selectedColor);
        PatternLockModelNG::CreateWithResourceObj(
            frameNode, PatternLockResourceType::SELECTEDCOLOR, selectedColorResObj);
    }
}

void ResetPatternLockSelectedColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color selectedColor = patternLockTheme->GetSelectedColor();
    PatternLockModelNG::SetSelectedColor(frameNode, selectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetSelectedColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::SELECTEDCOLOR, nullptr);
    }
}

void SetPatternLockSideLength(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSideLength(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
}

void SetPatternLockSideLengthRes(ArkUINodeHandle node, ArkUI_Float32 number, ArkUI_Int32 unit, void* sideLengthRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetSideLength(frameNode, Dimension(number, static_cast<DimensionUnit>(unit)));
    if (SystemProperties::ConfigChangePerform()) {
        auto* sideLength = reinterpret_cast<ResourceObject*>(sideLengthRawPtr);
        auto sideLengthResObj = AceType::Claim(sideLength);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::SIDELENGTH, sideLengthResObj);
    }
}

void ResetPatternLockSideLength(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    CalcDimension sideLength = patternLockTheme->GetSideLength();
    PatternLockModelNG::SetSideLength(frameNode, Dimension(sideLength.Value(), sideLength.Unit()));
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::SIDELENGTH, nullptr);
    }
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

void SetPatternLockRegularColorRes(ArkUINodeHandle node, uint32_t color, void* regularColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetRegularColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform()) {
        auto* regularColor = reinterpret_cast<ResourceObject*>(regularColorRawPtr);
        auto regularColorResObj = AceType::Claim(regularColor);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::REGULARCOLOR, regularColorResObj);
    }
}

void ResetPatternLockRegularColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color regularColor = patternLockTheme->GetRegularColor();
    PatternLockModelNG::SetRegularColor(frameNode, regularColor);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetRegularColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::REGULARCOLOR, nullptr);
    }
}

void SetPatternLockPathColor(ArkUINodeHandle node, uint32_t color)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPathColor(frameNode, Color(color));
}

void SetPatternLockPathColorRes(ArkUINodeHandle node, uint32_t color, void* pathColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetPathColor(frameNode, Color(color));
    if (SystemProperties::ConfigChangePerform()) {
        auto* pathColor = reinterpret_cast<ResourceObject*>(pathColorRawPtr);
        auto pathColorResObj = AceType::Claim(pathColor);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::PATHCOLOR, pathColorResObj);
    }
}

void ResetPatternLockPathColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto patternLockTheme = GetTheme<V2::PatternLockTheme>();
    CHECK_NULL_VOID(patternLockTheme);
    Color pathColor = patternLockTheme->GetPathColor();
    PatternLockModelNG::SetPathColor(frameNode, pathColor);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetPathColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::PATHCOLOR, nullptr);
    }
}

void SetPatternLockActiveCircleColor(ArkUINodeHandle node, uint32_t value)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleColor(frameNode, Color(value));
}

void SetPatternLockActiveCircleColorRes(ArkUINodeHandle node, uint32_t value, void* activeCircleColorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleColor(frameNode, Color(value));
    if (SystemProperties::ConfigChangePerform()) {
        auto* activeCircleColor = reinterpret_cast<ResourceObject*>(activeCircleColorRawPtr);
        auto activeCircleColorResObj = AceType::Claim(activeCircleColor);
        PatternLockModelNG::CreateWithResourceObj(
            frameNode, PatternLockResourceType::ACTIVECIRCLECOLOR, activeCircleColorResObj);
    }
}

void ResetPatternLockActiveCircleColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PatternLockModelNG::SetActiveCircleColor(frameNode, Color::TRANSPARENT);
    if (SystemProperties::ConfigChangePerform()) {
        PatternLockModelNG::SetActiveCircleColorByUser(frameNode, false);
        PatternLockModelNG::CreateWithResourceObj(frameNode, PatternLockResourceType::ACTIVECIRCLECOLOR, nullptr);
    }
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
        .setPatternLockActiveColorRes = SetPatternLockActiveColorRes,
        .resetPatternLockActiveColor = ResetPatternLockActiveColor,
        .setPatternLockCircleRadius = SetPatternLockCircleRadius,
        .setPatternLockCircleRadiusRes = SetPatternLockCircleRadiusRes,
        .resetPatternLockCircleRadius = ResetPatternLockCircleRadius,
        .setPatternLockSelectedColor = SetPatternLockSelectedColor,
        .setPatternLockSelectedColorRes = SetPatternLockSelectedColorRes,
        .resetPatternLockSelectedColor = ResetPatternLockSelectedColor,
        .setPatternLockSideLength = SetPatternLockSideLength,
        .setPatternLockSideLengthRes = SetPatternLockSideLengthRes,
        .resetPatternLockSideLength = ResetPatternLockSideLength,
        .setPatternLockAutoReset = SetPatternLockAutoReset,
        .resetPatternLockAutoReset = ResetPatternLockAutoReset,
        .setPatternLockPathStrokeWidth = SetPatternLockPathStrokeWidth,
        .resetPatternLockPathStrokeWidth = ResetPatternLockPathStrokeWidth,
        .setPatternLockRegularColor = SetPatternLockRegularColor,
        .setPatternLockRegularColorRes = SetPatternLockRegularColorRes,
        .resetPatternLockRegularColor = ResetPatternLockRegularColor,
        .setPatternLockPathColor = SetPatternLockPathColor,
        .setPatternLockPathColorRes = SetPatternLockPathColorRes,
        .resetPatternLockPathColor = ResetPatternLockPathColor,
        .setPatternLockActiveCircleColor = SetPatternLockActiveCircleColor,
        .setPatternLockActiveCircleColorRes = SetPatternLockActiveCircleColorRes,
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
        .setPatternLockActiveColorRes = SetPatternLockActiveColorRes,
        .resetPatternLockActiveColor = ResetPatternLockActiveColor,
        .setPatternLockCircleRadius = SetPatternLockCircleRadius,
        .setPatternLockCircleRadiusRes = SetPatternLockCircleRadiusRes,
        .resetPatternLockCircleRadius = ResetPatternLockCircleRadius,
        .setPatternLockSelectedColor = SetPatternLockSelectedColor,
        .setPatternLockSelectedColorRes = SetPatternLockSelectedColorRes,
        .resetPatternLockSelectedColor = ResetPatternLockSelectedColor,
        .setPatternLockSideLength = SetPatternLockSideLength,
        .setPatternLockSideLengthRes = SetPatternLockSideLengthRes,
        .resetPatternLockSideLength = ResetPatternLockSideLength,
        .setPatternLockAutoReset = SetPatternLockAutoReset,
        .resetPatternLockAutoReset = ResetPatternLockAutoReset,
        .setPatternLockPathStrokeWidth = SetPatternLockPathStrokeWidth,
        .resetPatternLockPathStrokeWidth = ResetPatternLockPathStrokeWidth,
        .setPatternLockRegularColor = SetPatternLockRegularColor,
        .setPatternLockRegularColorRes = SetPatternLockRegularColorRes,
        .resetPatternLockRegularColor = ResetPatternLockRegularColor,
        .setPatternLockPathColor = SetPatternLockPathColor,
        .setPatternLockPathColorRes = SetPatternLockPathColorRes,
        .resetPatternLockPathColor = ResetPatternLockPathColor,
        .setPatternLockActiveCircleColor = SetPatternLockActiveCircleColor,
        .setPatternLockActiveCircleColorRes = SetPatternLockActiveCircleColorRes,
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
