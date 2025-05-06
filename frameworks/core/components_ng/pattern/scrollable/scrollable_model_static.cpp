/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/scrollable/scrollable_model_static.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension DEFAULT_FADING_EDGE_LENGTH_SCROLLABLE = Dimension(32.0f, DimensionUnit::VP); // default value
}

void ScrollableModelStatic::SetScrollBarMode(FrameNode* frameNode, const std::optional<DisplayMode>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, value.value(), frameNode);
    } else {
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_VOID(pattern);
        auto defaultValue = pattern->GetDefaultScrollBarDisplayMode();
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, defaultValue, frameNode);
    }
}

void ScrollableModelStatic::SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, frameNode);
    }
}

void ScrollableModelStatic::SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, frameNode);
    }
}

void ScrollableModelStatic::SetNestedScroll(FrameNode* frameNode,
    const std::optional<NestedScrollMode>& forward, const std::optional<NestedScrollMode>& backward)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    NestedScrollOptions nestedOpt = {
        .forward = forward.value_or(NestedScrollMode::SELF_ONLY),
        .backward = backward.value_or(NestedScrollMode::SELF_ONLY)};
    pattern->SetNestedScroll(nestedOpt);
}

void ScrollableModelStatic::SetFriction(FrameNode* frameNode, const std::optional<double>& value)
{
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    const double invalidValue = -1.; // allow pattern to set proper default value
    pattern->SetFriction(value.value_or(invalidValue));
}

void ScrollableModelStatic::SetOnWillScroll(FrameNode* frameNode, OnWillScrollEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillScroll(std::move(event));
}

void ScrollableModelStatic::SetOnDidScroll(FrameNode* frameNode, OnScrollEvent&& onScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidScroll(std::move(onScroll));
}

void ScrollableModelStatic::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void ScrollableModelStatic::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

void ScrollableModelStatic::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void ScrollableModelStatic::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void ScrollableModelStatic::SetMaxFlingSpeed(FrameNode* frameNode, const std::optional<double>& max)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaxFlingVelocity(max.value_or(-1.0));
}

void ScrollableModelStatic::SetContentClip(FrameNode* frameNode, ContentClipMode mode, const RefPtr<ShapeRect>& rect)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ContentClip, std::make_pair(mode, rect), frameNode);
}

#ifdef SUPPORT_DIGITAL_CROWN
void ScrollableModelStatic::SetDigitalCrownSensitivity(FrameNode* frameNode,
    const std::optional<CrownSensitivity>& valueOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDigitalCrownSensitivity(valueOpt.value_or(CrownSensitivity::MEDIUM));
}
#endif

void ScrollableModelStatic::SetBackToTop(FrameNode* frameNode, bool backToTop)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBackToTop(backToTop);
    pattern->UseDefaultBackToTop(false);
}

void ScrollableModelStatic::SetEdgeEffect(
    FrameNode* frameNode, const std::optional<EdgeEffect>& edgeEffect, const std::optional<bool>& alwaysEnabled,
    EffectEdge effectEdge)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEdgeEffect(edgeEffect.value_or(EdgeEffect::NONE), alwaysEnabled.value_or(false), effectEdge);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ScrollableModelStatic::SetFadingEdge(FrameNode* frameNode, const std::optional<bool>& fadingEdge,
    const std::optional<Dimension>& fadingEdgeLength)
{
    if (fadingEdge) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, FadingEdge, fadingEdge.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, FadingEdge, frameNode);
    }
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, FadingEdgeLength,
        fadingEdgeLength.value_or(DEFAULT_FADING_EDGE_LENGTH_SCROLLABLE), frameNode);
}
} // namespace OHOS::Ace::NG
 