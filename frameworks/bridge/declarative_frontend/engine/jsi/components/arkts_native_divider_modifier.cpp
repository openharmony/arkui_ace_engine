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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_divider_modifier.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr uint32_t DEFAULT_DIVIDER_COLOR = 0x33182431;
constexpr bool DEFAULT_DIVIDER_VERTICAL = false;
const Dimension DEFAULT_DIVIDER_STROKE_WIDTH(1, DimensionUnit::PX);
const LineCap DEFAULT_DIVIDER_LINE_CAP = LineCap::BUTT;

void SetDividerStrokeWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension strokeWidthDimension(value, static_cast<DimensionUnit>(unit));
    DividerModelNG::StrokeWidth(frameNode, strokeWidthDimension);
}

void ResetDividerStrokeWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::StrokeWidth(frameNode, DEFAULT_DIVIDER_STROKE_WIDTH);
}

void SetDividerLineCap(NodeHandle node, int32_t lineCap)
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

void ResetDividerLineCap(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::LineCap(frameNode, DEFAULT_DIVIDER_LINE_CAP);
}

void SetDividerColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetDividerColor(frameNode, Color(color));
}

void ResetDividerColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetDividerColor(frameNode, Color(DEFAULT_DIVIDER_COLOR));
}

void SetDividerVertical(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetVertical(frameNode, value);
}

void ResetDividerVertical(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetVertical(frameNode, DEFAULT_DIVIDER_VERTICAL);
}

ArkUIDividerModifierAPI GetDividerModifier()
{
    static const ArkUIDividerModifierAPI modifier = { SetDividerStrokeWidth, ResetDividerStrokeWidth, SetDividerLineCap,
        ResetDividerLineCap, SetDividerColor, ResetDividerColor, SetDividerVertical, ResetDividerVertical };
    return modifier;
}
} // namespace OHOS::Ace::NG