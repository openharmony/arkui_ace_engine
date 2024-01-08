/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

#include <functional>
#include <memory>

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_arrow_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_utils.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<SwiperController> SwiperModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SWIPER_ETS_TAG, nodeId);
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });

    stack->Push(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetSwiperController();
}

RefPtr<FrameNode> SwiperModelNG::CreateFrameNode(int32_t nodeId)
{
    auto swiperNode = FrameNode::CreateFrameNode(V2::SWIPER_ETS_TAG, nodeId, AceType::MakeRefPtr<SwiperPattern>());
    return swiperNode;
}

void SwiperModelNG::SetDirection(Axis axis)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, Direction, axis);
}

void SwiperModelNG::SetIndex(uint32_t index)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, Index, index);
}

void SwiperModelNG::SetDisplayMode(SwiperDisplayMode displayMode)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayMode, displayMode);
}

void SwiperModelNG::SetDisplayCount(int32_t displayCount)
{
    if (displayCount <= 0) {
        return;
    }

    ResetDisplayMode();
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayCount, displayCount);
}

void SwiperModelNG::ResetDisplayCount()
{
    ACE_RESET_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayCount);
}

void SwiperModelNG::ResetDisplayMode()
{
    ACE_RESET_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayMode);
}

void SwiperModelNG::SetMinSize(const Dimension& minSize)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, MinSize, minSize);
}

void SwiperModelNG::SetShowIndicator(bool showIndicator)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, ShowIndicator, showIndicator);
}

void SwiperModelNG::SetIndicatorType(SwiperIndicatorType indicatorType)
{
    SwiperIndicatorUtils::SetSwiperIndicatorType(indicatorType);
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, IndicatorType, indicatorType);
}

void SwiperModelNG::SetItemSpace(const Dimension& itemSpace)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, ItemSpace, itemSpace);
}

void SwiperModelNG::SetCachedCount(int32_t cachedCount)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCachedCount(cachedCount);

    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, CachedCount, cachedCount);
}

void SwiperModelNG::SetIsIndicatorCustomSize(bool isCustomSize)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsIndicatorCustomSize(isCustomSize);
}

void SwiperModelNG::SetAutoPlay(bool autoPlay)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, AutoPlay, autoPlay);
}

void SwiperModelNG::SetAutoPlayInterval(uint32_t interval)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, AutoPlayInterval, interval);
}

void SwiperModelNG::SetDuration(uint32_t duration)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, Duration, duration);
}

void SwiperModelNG::SetLoop(bool loop)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, Loop, loop);
}

void SwiperModelNG::SetEnabled(bool enabled)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, Enabled, enabled);
}

void SwiperModelNG::SetDisableSwipe(bool disableSwipe)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, DisableSwipe, disableSwipe);
}

void SwiperModelNG::SetEdgeEffect(EdgeEffect edgeEffect)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, EdgeEffect, edgeEffect);
}

void SwiperModelNG::SetCurve(const RefPtr<Curve>& curve)
{
    ACE_UPDATE_PAINT_PROPERTY(SwiperPaintProperty, Curve, curve);
}

void SwiperModelNG::SetOnChange(std::function<void(const BaseEventInfo* info)>&& onChange)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);

    pattern->UpdateChangeEvent([event = std::move(onChange)](int32_t index) {
        SwiperChangeEvent eventInfo(index);
        event(&eventInfo);
    });
}

void SwiperModelNG::SetOnAnimationStart(AnimationStartEvent&& onAnimationStart)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);

    pattern->UpdateAnimationStartEvent([event = std::move(onAnimationStart)](int32_t index, int32_t targetIndex,
        const AnimationCallbackInfo& info) { event(index, targetIndex, info); });
}

void SwiperModelNG::SetOnAnimationEnd(AnimationEndEvent&& onAnimationEnd)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);

    pattern->UpdateAnimationEndEvent(
        [event = std::move(onAnimationEnd)](int32_t index, const AnimationCallbackInfo& info) { event(index, info); });
}

void SwiperModelNG::SetOnGestureSwipe(GestureSwipeEvent&& onGestureSwipe)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(eventHub);

    eventHub->SetGestureSwipeEvent(
        [event = std::move(onGestureSwipe)](int32_t index, const AnimationCallbackInfo& info) { event(index, info); });
}

void SwiperModelNG::SetRemoteMessageEventId(RemoteCallback&& remoteCallback) {}

void SwiperModelNG::SetIndicatorStyle(const SwiperParameters& swiperParameters)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperParameters(swiperParameters);
};

void SwiperModelNG::SetDotIndicatorStyle(const SwiperParameters& swiperParameters)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperParameters(swiperParameters);
};

void SwiperModelNG::SetDigitIndicatorStyle(const SwiperDigitalParameters& swiperDigitalParameters)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperDigitalParameters(swiperDigitalParameters);
};

void SwiperModelNG::SetOnClick(
    std::function<void(const BaseEventInfo* info, const RefPtr<V2::InspectorFunctionImpl>& impl)>&& value)
{}

void SwiperModelNG::SetMainSwiperSizeWidth() {}

void SwiperModelNG::SetMainSwiperSizeHeight() {}

void SwiperModelNG::SetPreviousMargin(const Dimension& prevMargin)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, PrevMargin, prevMargin);
}

void SwiperModelNG::SetNextMargin(const Dimension& nextMargin)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, NextMargin, nextMargin);
}

void SwiperModelNG::SetOnChangeEvent(std::function<void(const BaseEventInfo* info)>&& onChangeEvent)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);

    pattern->UpdateOnChangeEvent([event = std::move(onChangeEvent)](int32_t index) {
        SwiperChangeEvent eventInfo(index);
        event(&eventInfo);
    });
}

void SwiperModelNG::SetIndicatorIsBoolean(bool isBoolean)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIndicatorIsBoolean(isBoolean);
}

void SwiperModelNG::SetArrowStyle(const SwiperArrowParameters& swiperArrowParameters)
{
    if (swiperArrowParameters.isShowBackground.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, IsShowBackground, swiperArrowParameters.isShowBackground.value());
    }
    if (swiperArrowParameters.backgroundSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, BackgroundSize, swiperArrowParameters.backgroundSize.value());
    }
    if (swiperArrowParameters.backgroundColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, BackgroundColor, swiperArrowParameters.backgroundColor.value());
    }
    if (swiperArrowParameters.arrowSize.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, ArrowSize, swiperArrowParameters.arrowSize.value());
    }
    if (swiperArrowParameters.arrowColor.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, ArrowColor, swiperArrowParameters.arrowColor.value());
    }
    if (swiperArrowParameters.isSidebarMiddle.has_value()) {
        ACE_UPDATE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, IsSidebarMiddle, swiperArrowParameters.isSidebarMiddle.value());
    }
}

void SwiperModelNG::SetDisplayArrow(bool displayArrow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayArrow, displayArrow);
}

void SwiperModelNG::SetHoverShow(bool hoverShow)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperLayoutProperty, HoverShow, hoverShow);
}

void SwiperModelNG::SetNestedScroll(const NestedScrollOptions& nestedOpt)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNestedScroll(nestedOpt);
}

void SwiperModelNG::SetNextMargin(FrameNode* frameNode, const Dimension& nextMargin)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, NextMargin, nextMargin, frameNode);
}

void SwiperModelNG::SetPreviousMargin(FrameNode* frameNode, const Dimension& prevMargin)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, PrevMargin, prevMargin, frameNode);
}

void SwiperModelNG::SetIndex(FrameNode* frameNode, uint32_t index)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, Index, index, frameNode);
}

void SwiperModelNG::SetAutoPlayInterval(FrameNode* frameNode, uint32_t interval)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, AutoPlayInterval, interval, frameNode);
}

void SwiperModelNG::SetDuration(FrameNode* frameNode, uint32_t duration)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, Duration, duration, frameNode);
}

void SwiperModelNG::SetCachedCount(FrameNode* frameNode, int32_t cachedCount)
{
    auto swiperNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(swiperNode);
    auto pattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCachedCount(cachedCount);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, CachedCount, cachedCount, frameNode);
}

void SwiperModelNG::SetAutoPlay(FrameNode* frameNode, bool autoPlay)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, AutoPlay, autoPlay, frameNode);
}

void SwiperModelNG::SetLoop(FrameNode* frameNode, bool loop)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, Loop, loop, frameNode);
}

void SwiperModelNG::SetDirection(FrameNode* frameNode, Axis axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, Direction, axis, frameNode);
}

void SwiperModelNG::SetDisableSwipe(FrameNode* frameNode, bool disableSwipe)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, DisableSwipe, disableSwipe, frameNode);
}

void SwiperModelNG::SetItemSpace(FrameNode* frameNode, const Dimension& itemSpace)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, ItemSpace, itemSpace, frameNode);
}

void SwiperModelNG::SetDisplayMode(FrameNode* frameNode, SwiperDisplayMode displayMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayMode, displayMode, frameNode);
}

void SwiperModelNG::ResetDisplayMode(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayMode, frameNode);
}

void SwiperModelNG::SetEdgeEffect(FrameNode* frameNode, EdgeEffect edgeEffect)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, EdgeEffect, edgeEffect, frameNode);
}

void SwiperModelNG::SetMinSize(FrameNode* frameNode, const Dimension& minSize)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, MinSize, minSize, frameNode);
}

void SwiperModelNG::SetDisplayCount(FrameNode* frameNode, int32_t displayCount)
{
    if (displayCount <= 0) {
        return;
    }

    ResetDisplayMode(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayCount, displayCount, frameNode);
}

void SwiperModelNG::ResetDisplayCount(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayCount, frameNode);
}

void SwiperModelNG::SetCurve(FrameNode* frameNode, const RefPtr<Curve>& curve)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, Curve, curve, frameNode);
}

void SwiperModelNG::SetArrowStyle(FrameNode* frameNode, const SwiperArrowParameters& swiperArrowParameters)
{
    if (swiperArrowParameters.isShowBackground.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, IsShowBackground, swiperArrowParameters.isShowBackground.value(), frameNode);
    }
    if (swiperArrowParameters.backgroundSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, BackgroundSize, swiperArrowParameters.backgroundSize.value(), frameNode);
    }
    if (swiperArrowParameters.backgroundColor.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, BackgroundColor, swiperArrowParameters.backgroundColor.value(), frameNode);
    }
    if (swiperArrowParameters.arrowSize.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, ArrowSize, swiperArrowParameters.arrowSize.value(), frameNode);
    }
    if (swiperArrowParameters.arrowColor.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, ArrowColor, swiperArrowParameters.arrowColor.value(), frameNode);
    }
    if (swiperArrowParameters.isSidebarMiddle.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(
            SwiperLayoutProperty, IsSidebarMiddle, swiperArrowParameters.isSidebarMiddle.value(), frameNode);
    }
}

void SwiperModelNG::SetDisplayArrow(FrameNode* frameNode, bool displayArrow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayArrow, displayArrow, frameNode);
}

void SwiperModelNG::SetHoverShow(FrameNode* frameNode, bool hoverShow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, HoverShow, hoverShow, frameNode);
}

void SwiperModelNG::SetShowIndicator(FrameNode* frameNode, bool showIndicator)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, ShowIndicator, showIndicator, frameNode);
}

void SwiperModelNG::SetIndicatorIsBoolean(FrameNode* frameNode, bool isBoolean)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIndicatorIsBoolean(isBoolean);
}

void SwiperModelNG::SetDigitIndicatorStyle(FrameNode* frameNode, const SwiperDigitalParameters& swiperDigitalParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperDigitalParameters(swiperDigitalParameters);
}

void SwiperModelNG::SetIndicatorType(FrameNode* frameNode, SwiperIndicatorType indicatorType)
{
    SwiperIndicatorUtils::SetSwiperIndicatorType(indicatorType);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, IndicatorType, indicatorType, frameNode);
}

void SwiperModelNG::SetIsIndicatorCustomSize(FrameNode* frameNode, bool isCustomSize)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsIndicatorCustomSize(isCustomSize);
}

void SwiperModelNG::SetDotIndicatorStyle(FrameNode* frameNode, const SwiperParameters& swiperParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperParameters(swiperParameters);
}
} // namespace OHOS::Ace::NG
