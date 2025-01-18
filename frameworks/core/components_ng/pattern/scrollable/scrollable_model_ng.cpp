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

#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"

#include "core/components_ng/pattern/scrollable/scrollable_event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {
void ScrollableModelNG::SetEdgeEffect(EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEdgeEffect(edgeEffect, alwaysEnabled, effectEdge);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ScrollableModelNG::SetScrollBarMode(DisplayMode value)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarMode, value);
}

void ScrollableModelNG::SetScrollBarMode(FrameNode* frameNode, const std::optional<DisplayMode>& value)
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

void ScrollableModelNG::SetScrollBarColor(const std::string& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, Color::FromString(value));
}

void ScrollableModelNG::ResetScrollBarColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, frameNode);
}

void ScrollableModelNG::SetScrollBarColor(FrameNode* frameNode, const std::optional<Color>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, frameNode);
    }
}

void ScrollableModelNG::SetScrollBarWidth(const std::string& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, StringUtils::StringToDimensionWithUnit(value));
}

void ScrollableModelNG::ResetScrollBarWidth(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, frameNode);
}

void ScrollableModelNG::SetScrollBarWidth(FrameNode* frameNode, const std::optional<Dimension>& value)
{
    if (value) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, value.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarWidth, frameNode);
    }
}

void ScrollableModelNG::SetOnScroll(OnScrollEvent&& onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(onScroll));
}

void ScrollableModelNG::SetOnScroll(FrameNode* frameNode, OnScrollEvent&& onScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScroll(std::move(onScroll));
}

void ScrollableModelNG::SetOnWillScroll(OnWillScrollEvent&& onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillScroll(std::move(onScroll));
}

void ScrollableModelNG::SetOnWillScroll(FrameNode* frameNode, OnWillScrollEvent&& event)
{
    CHECK_NULL_VOID(frameNode);
    const auto& eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillScroll(std::move(event));
}

void ScrollableModelNG::SetOnDidScroll(OnScrollEvent&& onScroll)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidScroll(std::move(onScroll));
}

void ScrollableModelNG::SetOnDidScroll(FrameNode* frameNode, OnScrollEvent&& onScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDidScroll(std::move(onScroll));
}

void ScrollableModelNG::SetOnScrollStart(OnScrollStartEvent&& onScrollStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void ScrollableModelNG::SetOnScrollStart(FrameNode* frameNode, OnScrollStartEvent&& onScrollStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStart(std::move(onScrollStart));
}

void ScrollableModelNG::SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void ScrollableModelNG::SetOnScrollStop(FrameNode* frameNode, OnScrollStopEvent&& onScrollStop)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollStop(std::move(onScrollStop));
}

void ScrollableModelNG::SetOnReachStart(OnReachEvent&& onReachStart)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void ScrollableModelNG::SetOnReachStart(FrameNode* frameNode, OnReachEvent&& onReachStart)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachStart(std::move(onReachStart));
}

void ScrollableModelNG::SetOnReachEnd(OnReachEvent&& onReachEnd)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

void ScrollableModelNG::SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& ScrollFrameBegin)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(ScrollFrameBegin));
}

void ScrollableModelNG::SetOnScrollFrameBegin(FrameNode* frameNode, OnScrollFrameBeginEvent&& ScrollFrameBegin)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnScrollFrameBegin(std::move(ScrollFrameBegin));
}

void ScrollableModelNG::SetFadingEdge(bool fadingEdge, const Dimension& fadingEdgeLength)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, FadingEdge, fadingEdge);
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, FadingEdgeLength, fadingEdgeLength);
}

void ScrollableModelNG::SetFadingEdge(FrameNode* frameNode, bool fadingEdge, const Dimension& fadingEdgeLength)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, FadingEdge, fadingEdge, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, FadingEdgeLength, fadingEdgeLength, frameNode);
}

void ScrollableModelNG::SetEdgeEffect(
    FrameNode* frameNode, EdgeEffect edgeEffect, bool alwaysEnabled, EffectEdge effectEdge)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEdgeEffect(edgeEffect, alwaysEnabled, effectEdge);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ScrollableModelNG::SetScrollBarMode(FrameNode* frameNode, int32_t displayNumber)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(
        ScrollablePaintProperty, ScrollBarMode, static_cast<DisplayMode>(displayNumber), frameNode);
}

void ScrollableModelNG::SetScrollBarWidth(FrameNode* frameNode, const std::string& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(
        ScrollablePaintProperty, ScrollBarWidth, StringUtils::StringToDimensionWithUnit(value), frameNode);
}

void ScrollableModelNG::SetScrollBarColor(FrameNode* frameNode, const std::string& value)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ScrollBarColor, Color::FromString(value), frameNode);
}

void ScrollableModelNG::SetMaxFlingSpeed(double max)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaxFlingVelocity(max);
}

int32_t ScrollableModelNG::GetEdgeEffect(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    const auto& pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return static_cast<int32_t>(pattern->GetEdgeEffect());
}

int32_t ScrollableModelNG::GetAlwaysEnabled(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0);
    const auto& pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return pattern->GetAlwaysEnabled();
}

void ScrollableModelNG::SetOnReachEnd(FrameNode* frameNode, OnReachEvent&& onReachEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ScrollableEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnReachEnd(std::move(onReachEnd));
}

void ScrollableModelNG::SetMaxFlingSpeed(FrameNode* frameNode, double max)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetMaxFlingVelocity(max);
}

float ScrollableModelNG::GetMaxFlingSpeed(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, 0.0f);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, 0.0f);
    return static_cast<float>(pattern->GetMaxFlingVelocity() / PipelineBase::GetCurrentDensity());
}

void ScrollableModelNG::SetContentClip(ContentClipMode mode, const RefPtr<ShapeRect>& shape)
{
    ACE_UPDATE_PAINT_PROPERTY(ScrollablePaintProperty, ContentClip, std::make_pair(mode, shape));
}

ContentClipMode ScrollableModelNG::GetContentClip(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, ContentClipMode::CONTENT_ONLY);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, ContentClipMode::CONTENT_ONLY);
    const auto& clip = paintProperty->GetContentClip();
    const auto mode = clip ? clip->first : ContentClipMode::DEFAULT;
    if (mode >= ContentClipMode::CUSTOM) {
        return paintProperty->GetDefaultContentClip();
    }
    return mode;
}

void ScrollableModelNG::SetContentClip(FrameNode* frameNode, ContentClipMode mode, const RefPtr<ShapeRect>& rect)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ScrollablePaintProperty, ContentClip, std::make_pair(mode, rect), frameNode);
}

void ScrollableModelNG::ResetContentClip(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateContentClip({ paintProperty->GetDefaultContentClip(), nullptr });
}

bool ScrollableModelNG::GetFadingEdge(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    return paintProperty->GetFadingEdge().value_or(false);
}

float ScrollableModelNG::GetFadingEdgeLength(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, DEFAULT_FADING_EDGE_LENGTH_SCROLLABLE.Value());
    auto paintProperty = frameNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_RETURN(paintProperty, DEFAULT_FADING_EDGE_LENGTH_SCROLLABLE.Value());
    return paintProperty->GetFadingEdgeLength().value_or(DEFAULT_FADING_EDGE_LENGTH_SCROLLABLE).Value();
}

#ifdef SUPPORT_DIGITAL_CROWN
void ScrollableModelNG::SetDigitalCrownSensitivity(CrownSensitivity sensitivity)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDigitalCrownSensitivity(sensitivity);
}
#endif

void ScrollableModelNG::SetNestedScroll(FrameNode* frameNode, const NestedScrollOptions& nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void ScrollableModelNG::SetFriction(FrameNode* frameNode, const std::optional<double>& value)
{
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(pattern);
    const double invalidValue = -1.; // allow pattern to set proper default value
    pattern->SetFriction(value.value_or(invalidValue));
}
} // namespace OHOS::Ace::NG
