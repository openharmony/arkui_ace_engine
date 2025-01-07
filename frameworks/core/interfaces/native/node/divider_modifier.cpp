/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/divider_modifier.h"

#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"

namespace OHOS::Ace::NG {
constexpr bool DEFAULT_DIVIDER_VERTICAL = false;
const Dimension DEFAULT_DIVIDER_STROKE_WIDTH(1, DimensionUnit::PX);
const LineCap DEFAULT_DIVIDER_LINE_CAP = LineCap::BUTT;

void SetDividerStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension strokeWidthDimension(value, static_cast<DimensionUnit>(unit));
    DividerModelNG::StrokeWidth(frameNode, strokeWidthDimension);
}

void ResetDividerStrokeWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::StrokeWidth(frameNode, DEFAULT_DIVIDER_STROKE_WIDTH);
}

void SetDividerLineCap(ArkUINodeHandle node, int32_t lineCap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto lineCapStyle = DEFAULT_DIVIDER_LINE_CAP;
    if (static_cast<int>(LineCap::SQUARE) == lineCap) {
        lineCapStyle = LineCap::SQUARE;
    } else if (static_cast<int>(LineCap::ROUND) == lineCap) {
        lineCapStyle = LineCap::ROUND;
    } else {
        lineCapStyle = DEFAULT_DIVIDER_LINE_CAP;
    }
    DividerModelNG::LineCap(frameNode, lineCapStyle);
}

void ResetDividerLineCap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::LineCap(frameNode, DEFAULT_DIVIDER_LINE_CAP);
}

void SetDividerColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetDividerColor(frameNode, Color(color));
}

void ResetDividerColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto theme = GetTheme<DividerTheme>();
    CHECK_NULL_VOID(theme);
    Color dividerColor = theme->GetColor();
    DividerModelNG::SetDividerColor(frameNode, dividerColor);
}

void SetDividerVertical(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetVertical(frameNode, value);
}

void ResetDividerVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetVertical(frameNode, DEFAULT_DIVIDER_VERTICAL);
}

namespace NodeModifier {
const ArkUIDividerModifier* GetDividerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDividerModifier modifier = {
        .setDividerStrokeWidth = SetDividerStrokeWidth,
        .resetDividerStrokeWidth = ResetDividerStrokeWidth,
        .setDividerLineCap = SetDividerLineCap,
        .resetDividerLineCap = ResetDividerLineCap,
        .setDividerColor = SetDividerColor,
        .resetDividerColor = ResetDividerColor,
        .setDividerVertical = SetDividerVertical,
        .resetDividerVertical = ResetDividerVertical,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIDividerModifier* GetCJUIDividerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIDividerModifier modifier = {
        .setDividerStrokeWidth = SetDividerStrokeWidth,
        .resetDividerStrokeWidth = ResetDividerStrokeWidth,
        .setDividerLineCap = SetDividerLineCap,
        .resetDividerLineCap = ResetDividerLineCap,
        .setDividerColor = SetDividerColor,
        .resetDividerColor = ResetDividerColor,
        .setDividerVertical = SetDividerVertical,
        .resetDividerVertical = ResetDividerVertical,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG
