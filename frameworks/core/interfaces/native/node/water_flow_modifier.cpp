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
#include "core/interfaces/native/node/water_flow_modifier.h"

#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double FRICTION_DEFAULT = -1.0;
constexpr double DIMENSION_DEFAULT = 0.0;
}

void ResetColumnsTemplate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsTemplate(frameNode, "");
}

void SetColumnsTemplate(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsTemplate(frameNode, value);
}

void ResetRowsTemplate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsTemplate(frameNode, "");
}

void SetRowsTemplate(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsTemplate(frameNode, value);
}

void ResetWaterFlowEnableScrollInteraction(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollEnabled(frameNode, true);
}

void SetWaterFlowEnableScrollInteraction(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetScrollEnabled(frameNode, value);
}

void SetColumnsGap(NodeHandle node, double value, int32_t unit, const char* calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension columnsGapDimension;
    if (unitEnum == DimensionUnit::CALC) {
        columnsGapDimension = Dimension::FromString(std::string(calcValue));
    } else {
        columnsGapDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetColumnsGap(frameNode, columnsGapDimension);
}

void ResetColumnsGap(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetColumnsGap(frameNode, CalcDimension(DIMENSION_DEFAULT));
}

void SetRowsGap(NodeHandle node, double value, int32_t unit, const char* calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension rowsGapDimension;
    if (unitEnum == DimensionUnit::CALC) {
        rowsGapDimension = Dimension::FromString(std::string(calcValue));
    } else {
        rowsGapDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetRowsGap(frameNode, rowsGapDimension);
}

void ResetRowsGap(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetRowsGap(frameNode, CalcDimension(DIMENSION_DEFAULT));
}

void SetItemMinWidth(NodeHandle node, double value, int32_t unit, const char* calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension minWidthDimension;
    if (unitEnum == DimensionUnit::CALC) {
        minWidthDimension = Dimension::FromString(std::string(calcValue));
    } else {
        minWidthDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMinWidth(frameNode, minWidthDimension);
}

void ResetItemMinWidth(NodeHandle node) {}

void SetItemMinHeight(NodeHandle node, double value, int32_t unit, const char* calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension minHeightDimension;
    if (unitEnum == DimensionUnit::CALC) {
        minHeightDimension = Dimension::FromString(std::string(calcValue));
    } else {
        minHeightDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMinHeight(frameNode, minHeightDimension);
}

void ResetItemMinHeight(NodeHandle node) {}

void SetItemMaxWidth(NodeHandle node, double value, int32_t unit, const char* calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension maxWidthDimension;
    if (unitEnum == DimensionUnit::CALC) {
        maxWidthDimension = Dimension::FromString(std::string(calcValue));
    } else {
        maxWidthDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMaxWidth(frameNode, maxWidthDimension);
}

void ResetItemMaxWidth(NodeHandle node) {}

void SetItemMaxHeight(NodeHandle node, double value, int32_t unit, const char* calcValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    CalcDimension maxHeightDimension;
    if (unitEnum == DimensionUnit::CALC) {
        maxHeightDimension = Dimension::FromString(std::string(calcValue));
    } else {
        maxHeightDimension = Dimension(value, unitEnum);
    }
    WaterFlowModelNG::SetItemMaxHeight(frameNode, maxHeightDimension);
}

void ResetItemMaxHeight(NodeHandle node) {}

void SetLayoutDirection(NodeHandle node, int32_t direction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetLayoutDirection(frameNode, static_cast<FlexDirection>(direction));
}

void ResetLayoutDirection(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetLayoutDirection(frameNode, FlexDirection::COLUMN);
}

void SetWaterFlowNestedScroll(NodeHandle node, int32_t scrollForward, int32_t scrollBackward)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    nestedOpt.forward = static_cast<NestedScrollMode>(scrollForward);
    nestedOpt.backward = static_cast<NestedScrollMode>(scrollBackward);
    WaterFlowModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void ResetWaterFlowNestedScroll(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    WaterFlowModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void SetWaterFlowFriction(NodeHandle node, double friction)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFriction(frameNode, friction);
}

void ResetWaterFlowFriction(NodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    WaterFlowModelNG::SetFriction(frameNode, FRICTION_DEFAULT);
}

ArkUIWaterFlowModifierAPI GetWaterFlowModifier()
{
    static const ArkUIWaterFlowModifierAPI modifier = {
        ResetColumnsTemplate,
        SetColumnsTemplate,
        ResetRowsTemplate,
        SetRowsTemplate,
        ResetWaterFlowEnableScrollInteraction,
        SetWaterFlowEnableScrollInteraction,
        SetColumnsGap,
        ResetColumnsGap,
        SetRowsGap,
        ResetRowsGap,
        SetItemMinWidth,
        ResetItemMinWidth,
        SetItemMaxWidth,
        ResetItemMaxWidth,
        SetItemMinHeight,
        ResetItemMinHeight,
        SetItemMaxHeight,
        ResetItemMaxHeight,
        SetLayoutDirection,
        ResetLayoutDirection,
        SetWaterFlowNestedScroll,
        ResetWaterFlowNestedScroll,
        SetWaterFlowFriction,
        ResetWaterFlowFriction,
    };
    return modifier;
}
} // namespace OHOS::Ace::NG