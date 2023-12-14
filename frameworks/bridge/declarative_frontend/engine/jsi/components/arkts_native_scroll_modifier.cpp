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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_scroll_modifier.h"

#include "base/log/log.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
constexpr int32_t SNAP_START_INDEX = 0;
constexpr int32_t DEFAULT_SNAP_ALIGN_VALUE = 0;
constexpr int32_t DEFAULT_SCROLLABLE_AXIS_VALUE = 0;
constexpr double FRICTION_DEFAULT = 0.6;
constexpr double DEFAULT_DIMENSION_VALUE = 0.0;
constexpr double DEFAULT_SCROLLBARWIDTH_VALUE = 4.0;
constexpr int32_t PARAM_SIZE = 4;
bool CheckSnapPaginations(std::vector<Dimension> snapPaginations)
{
    CHECK_NULL_RETURN(!snapPaginations.empty(), false);
    float preValue = (*snapPaginations.begin()).Value();
    CHECK_NULL_RETURN(!Negative(preValue), false);
    auto unit = (*snapPaginations.begin()).Unit();
    for (auto iter = snapPaginations.begin() + 1; iter < snapPaginations.end(); ++iter) {
        if (Negative((*iter).Value()) || (*iter).Unit() != unit || LessOrEqual((*iter).Value(), preValue)) {
            return false;
        }
        preValue = (*iter).Value();
    }
    return true;
}
void SetScrollNestedScroll(NodeHandle node, int32_t scrollForward, int32_t scrollBackward)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    nestedOpt.forward = static_cast<NestedScrollMode>(scrollForward);
    nestedOpt.backward = static_cast<NestedScrollMode>(scrollBackward);
    ScrollModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void ResetScrollNestedScroll(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    ScrollModelNG::SetNestedScroll(frameNode, nestedOpt);
}

void SetScrollEnableScroll(NodeHandle node, bool isEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetScrollEnabled(frameNode, isEnabled);
}

void ResetScrollEnableScroll(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetScrollEnabled(frameNode, false);
}

void SetScrollFriction(NodeHandle node, double friction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetFriction(frameNode, friction);
}

void ResetScrollFriction(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetFriction(frameNode, FRICTION_DEFAULT);
}

void SetScrollScrollSnap(NodeHandle node, const double* paginationValue, int32_t paginationSize,
    const int32_t* paginationParam, int32_t paramSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    int32_t snapAlign = 0;
    auto snapToStart = false;
    auto snapToEnd = false;
    auto isArray = false;
    auto snapAlignIndex = paginationSize;
    auto snapToStartIndex = paginationSize + 1;
    auto snapToEndIndex = paginationSize + 2;
    auto isArrayIndex = paginationSize + 3;
    if (paramSize - paginationSize == PARAM_SIZE) {
        snapAlign = paginationParam[snapAlignIndex];
        snapToStart = static_cast<bool>(paginationParam[snapToStartIndex]);
        snapToEnd = static_cast<bool>(paginationParam[snapToEndIndex]);
        isArray = static_cast<bool>(paginationParam[isArrayIndex]);
    }
    std::pair<bool, bool> enableSnapToSide = { snapToStart, snapToEnd };

    std::vector<Dimension> snapPaginations;
    CalcDimension intervalSize;
    if (isArray) {
        for (auto i = 0; i < paginationSize; i++) {
            auto pValue = paginationValue[i];
            auto pUnit = static_cast<DimensionUnit>(paginationParam[i]);
            CalcDimension dms = Dimension(pValue, pUnit);
            snapPaginations.push_back(dms);
        }
        intervalSize = CalcDimension(DEFAULT_DIMENSION_VALUE);
    } else {
        auto pValue = paginationValue[SNAP_START_INDEX];
        auto pUnit = static_cast<DimensionUnit>(paginationParam[SNAP_START_INDEX]);
        intervalSize = Dimension(pValue, pUnit);
    }

    if (!CheckSnapPaginations(snapPaginations)) {
        std::vector<Dimension>().swap(snapPaginations);
    }

    ScrollModelNG::SetScrollSnap(
        frameNode, static_cast<ScrollSnapAlign>(snapAlign), intervalSize, snapPaginations, enableSnapToSide);
}

void ResetScrollScrollSnap(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    int32_t snapAlign = DEFAULT_SNAP_ALIGN_VALUE;
    CalcDimension intervalSize = CalcDimension(DEFAULT_DIMENSION_VALUE);
    std::vector<Dimension> snapPaginations;
    std::pair<bool, bool> enableSnapToSide = {true, true};
    ScrollModelNG::SetScrollSnap(
        frameNode, static_cast<ScrollSnapAlign>(snapAlign), intervalSize, snapPaginations, enableSnapToSide);
}

void SetScrollScrollBar(NodeHandle node, int32_t direction)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetScrollBar(frameNode, static_cast<DisplayMode>(direction));
}

void ResetScrollScrollBar(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetScrollBar(frameNode, DisplayMode::AUTO);
}

void SetScrollScrollable(NodeHandle node, int32_t scrollDirection)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetAxis(frameNode, static_cast<Axis>(scrollDirection));
}

void ResetScrollScrollable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetAxis(frameNode, static_cast<Axis>(DEFAULT_SCROLLABLE_AXIS_VALUE));
}

void SetScrollScrollBarColor(NodeHandle node, uint32_t scrollBarColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetScrollBarColor(frameNode, Color(scrollBarColor));
}

void ResetScrollScrollBarColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto scrollBarTheme = pipeline->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(scrollBarTheme);
    Color foregroundColor = scrollBarTheme->GetForegroundColor();
    ScrollModelNG::SetScrollBarColor(frameNode, foregroundColor);
}

void SetScrollScrollBarWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    ScrollModelNG::SetScrollBarWidth(frameNode, width);
}

void ResetScrollScrollBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension width = CalcDimension(DEFAULT_SCROLLBARWIDTH_VALUE, DimensionUnit::VP);
    ScrollModelNG::SetScrollBarWidth(frameNode, width);
}

void SetScrollEdgeEffect(NodeHandle node, int32_t edgeEffect, bool alwaysEnabled)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetEdgeEffect(frameNode, static_cast<EdgeEffect>(edgeEffect), alwaysEnabled);
}

void ResetScrollEdgeEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetEdgeEffect(frameNode, EdgeEffect::NONE, true);
}

ArkUIScrollModifierAPI GetScrollModifier()
{
    static const ArkUIScrollModifierAPI modifier = { SetScrollNestedScroll, ResetScrollNestedScroll,
        SetScrollEnableScroll, ResetScrollEnableScroll, SetScrollFriction, ResetScrollFriction, SetScrollScrollSnap,
        ResetScrollScrollSnap, SetScrollScrollBar, ResetScrollScrollBar, SetScrollScrollable, ResetScrollScrollable,
        SetScrollScrollBarColor, ResetScrollScrollBarColor, SetScrollScrollBarWidth, ResetScrollScrollBarWidth,
        SetScrollEdgeEffect, ResetScrollEdgeEffect };

    return modifier;
}
} // namespace OHOS::Ace::NG