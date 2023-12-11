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

#include "arkts_native_api.h"

#include "core/components/common/layout/constants.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

constexpr uint32_t DEFAULT_SCROLLABLE_VALUE = (uint32_t)Axis::FREE;

void SetScrollScrollable(NodeHandle node, uint32_t scrollDirection)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetScrollable(frameNode, scrollDirection);
}

void ResetScrollScrollable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ScrollModelNG::SetScrollable(frameNode, DEFAULT_SCROLLABLE_VALUE);
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

void SetScrollScrollBarWidth(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto scrollBarTheme = pipeline->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(scrollBarTheme);

    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (value < 0 || unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC ||
        unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
        ScrollModelNG::SetScrollBarWidth(frameNode, scrollBarTheme->GetNormalWidth());
    } else {
        ScrollModelNG::SetScrollBarWidth(frameNode, Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    }
}

void ResetScrollScrollBarWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto scrollBarTheme = pipeline->GetTheme<ScrollBarTheme>();
    CHECK_NULL_VOID(scrollBarTheme);
    CalcDimension dimension = scrollBarTheme->GetNormalWidth();
    ScrollModelNG::SetScrollBarWidth(frameNode, dimension);
}

void SetScrollEdgeEffect(NodeHandle node, uint32_t edgeEffect, bool alwaysEnabled)
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
    static const ArkUIScrollModifierAPI modifier = { SetScrollScrollable, ResetScrollScrollable,
        SetScrollScrollBarColor, ResetScrollScrollBarColor, SetScrollScrollBarWidth, ResetScrollScrollBarWidth,
        SetScrollEdgeEffect, ResetScrollEdgeEffect };

    return modifier;
}
} // namespace OHOS::Ace::NG