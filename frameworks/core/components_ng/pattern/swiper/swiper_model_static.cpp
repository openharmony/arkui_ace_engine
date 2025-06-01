/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/swiper_model_static.h"

#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_node.h"

namespace {
constexpr float ARROW_SIZE_COEFFICIENT = 0.75f;
} // namespace

namespace OHOS::Ace::NG {
namespace {
static const Dimension& TrimToPositive(const Dimension& val)
{
    static Dimension zeroVp(0, DimensionUnit::VP);
    return val.IsNegative() ? zeroVp : val;
}
} // namespace

void SwiperModelStatic::ParseAndSetArrowStyle(FrameNode* frameNode, const SwiperArrowParameters& swiperArrowParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    SwiperArrowParameters arrowParameters;
    arrowParameters.isShowBackground =
        swiperArrowParameters.isShowBackground.value_or(swiperIndicatorTheme->GetIsShowArrowBackground());
    arrowParameters.isSidebarMiddle =
        swiperArrowParameters.isSidebarMiddle.value_or(swiperIndicatorTheme->GetIsSidebarMiddle());
    auto isSidebarMiddle = swiperArrowParameters.isSidebarMiddle;
    if (isSidebarMiddle && isSidebarMiddle.value()) {
        arrowParameters.backgroundColor =
            swiperArrowParameters.backgroundColor.value_or(swiperIndicatorTheme->GetBigArrowBackgroundColor());
        arrowParameters.arrowColor =
            swiperArrowParameters.arrowColor.value_or(swiperIndicatorTheme->GetBigArrowColor());
        auto backgroundSize = swiperArrowParameters.backgroundSize;
        arrowParameters.backgroundSize = backgroundSize && GreatNotEqual(backgroundSize.value().ConvertToVp(), 0.0) &&
                                                 !(backgroundSize.value().Unit() == DimensionUnit::PERCENT)
                                             ? backgroundSize.value()
                                             : swiperIndicatorTheme->GetBigArrowBackgroundSize();
        if (arrowParameters.isShowBackground.value()) {
            arrowParameters.arrowSize = arrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            auto arrowSize = swiperArrowParameters.arrowSize;
            arrowParameters.arrowSize = arrowSize && GreatNotEqual(arrowSize.value().ConvertToVp(), 0.0) &&
                                                !(arrowSize.value().Unit() == DimensionUnit::PERCENT)
                                            ? arrowSize.value()
                                            : swiperIndicatorTheme->GetBigArrowSize();
            arrowParameters.backgroundSize = arrowParameters.arrowSize;
        }
    } else {
        arrowParameters.backgroundColor =
            swiperArrowParameters.backgroundColor.value_or(swiperIndicatorTheme->GetSmallArrowBackgroundColor());
        arrowParameters.arrowColor =
            swiperArrowParameters.arrowColor.value_or(swiperIndicatorTheme->GetSmallArrowColor());

        auto backgroundSize = swiperArrowParameters.backgroundSize;
        arrowParameters.backgroundSize = backgroundSize && GreatNotEqual(backgroundSize.value().ConvertToVp(), 0.0) &&
                                                 !(backgroundSize.value().Unit() == DimensionUnit::PERCENT)
                                             ? backgroundSize.value()
                                             : swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        if (arrowParameters.isShowBackground.value()) {
            arrowParameters.arrowSize = arrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            auto arrowSize = swiperArrowParameters.arrowSize;
            arrowParameters.arrowSize = arrowSize && GreatNotEqual(arrowSize.value().ConvertToVp(), 0.0) &&
                                                !(arrowSize.value().Unit() == DimensionUnit::PERCENT)
                                            ? arrowSize.value()
                                            : swiperIndicatorTheme->GetSmallArrowSize();
            arrowParameters.backgroundSize = arrowParameters.arrowSize;
        }
    }
    SetArrowStyle(frameNode, arrowParameters);
    SetDisplayArrow(frameNode, true);
}

void SwiperModelStatic::SetDefaultArrowStyle(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    SwiperArrowParameters swiperArrowParameters;
    swiperArrowParameters.isShowBackground = swiperIndicatorTheme->GetIsShowArrowBackground();
    swiperArrowParameters.isSidebarMiddle = swiperIndicatorTheme->GetIsSidebarMiddle();
    swiperArrowParameters.backgroundSize = swiperIndicatorTheme->GetSmallArrowBackgroundSize();
    swiperArrowParameters.backgroundColor = swiperIndicatorTheme->GetSmallArrowBackgroundColor();
    swiperArrowParameters.arrowSize = swiperIndicatorTheme->GetSmallArrowSize();
    swiperArrowParameters.arrowColor = swiperIndicatorTheme->GetSmallArrowColor();
    SetArrowStyle(frameNode, swiperArrowParameters);
    SetDisplayArrow(frameNode, true);
}

void SwiperModelStatic::SetArrowStyle(FrameNode* frameNode, const SwiperArrowParameters& swiperArrowParameters)
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

RefPtr<FrameNode> SwiperModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto swiperNode = ElementRegister::GetInstance()->GetSpecificItemById<SwiperNode>(nodeId);
    if (swiperNode) {
        if (swiperNode->GetTag() == V2::SWIPER_ETS_TAG) {
            return swiperNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = swiperNode->GetParent();
        if (parent) {
            parent->RemoveChild(swiperNode);
        }
    }
    // adapt for capi
    swiperNode = AceType::MakeRefPtr<SwiperNode>(V2::SWIPER_ETS_TAG, nodeId, AceType::MakeRefPtr<SwiperPattern>());
    swiperNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(swiperNode);
    return swiperNode;
}

RefPtr<SwiperController> SwiperModelStatic::GetSwiperController(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    return pattern->GetSwiperController();
}

void SwiperModelStatic::SetIndex(FrameNode* frameNode, uint32_t index)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, Index, index, frameNode);
}

void SwiperModelStatic::SetAutoPlay(FrameNode* frameNode, bool autoPlay)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, AutoPlay, autoPlay, frameNode);
}

void SwiperModelStatic::SetAutoPlayOptions(FrameNode* frameNode, const SwiperAutoPlayOptions& swiperAutoPlayOptions)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetStopWhenTouched(swiperAutoPlayOptions.stopWhenTouched);
}

void SwiperModelStatic::SetAutoPlayInterval(FrameNode* frameNode, uint32_t interval)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, AutoPlayInterval, interval, frameNode);
}

void SwiperModelStatic::SetDigitIndicatorStyle(FrameNode* frameNode,
    const SwiperDigitalParameters& swiperDigitalParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperDigitalParameters(swiperDigitalParameters);
}

void SwiperModelStatic::SetIndicatorType(FrameNode* frameNode, SwiperIndicatorType indicatorType)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, IndicatorType, indicatorType, frameNode);
}

void SwiperModelStatic::SetDotIndicatorStyle(FrameNode* frameNode, const SwiperParameters& swiperParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperParameters(swiperParameters);
}

void SwiperModelStatic::SetIsIndicatorCustomSize(FrameNode* frameNode, bool isCustomSize)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsIndicatorCustomSize(isCustomSize);
}

void SwiperModelStatic::SetShowIndicator(FrameNode* frameNode, bool showIndicator)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, ShowIndicator, showIndicator, frameNode);
}

void SwiperModelStatic::SetLoop(FrameNode* frameNode, bool loop)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, Loop, loop, frameNode);
}

void SwiperModelStatic::SetDuration(FrameNode* frameNode, uint32_t duration)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, Duration, duration, frameNode);
}

void SwiperModelStatic::SetDirection(FrameNode* frameNode, Axis axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, Direction, axis, frameNode);
}

void SwiperModelStatic::SetItemSpace(FrameNode* frameNode, const Dimension& itemSpace)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, ItemSpace, itemSpace, frameNode);
}

void SwiperModelStatic::SetDisplayMode(FrameNode* frameNode, SwiperDisplayMode displayMode)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayMode, displayMode, frameNode);
}

void SwiperModelStatic::SetCachedCount(FrameNode* frameNode, int32_t cachedCount)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCachedCount(cachedCount);

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, CachedCount, cachedCount, frameNode);
}

void SwiperModelStatic::SetCachedIsShown(FrameNode* frameNode, bool isShown)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, CachedIsShown, isShown, frameNode);
}

void SwiperModelStatic::SetEdgeEffect(FrameNode* frameNode, EdgeEffect edgeEffect)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, EdgeEffect, edgeEffect, frameNode);
}

void SwiperModelStatic::SetDisableSwipe(FrameNode* frameNode, bool disableSwipe)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisableSwipe, disableSwipe, frameNode);
}

void SwiperModelStatic::SetCurve(FrameNode* frameNode, const RefPtr<Curve>& curve)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwiperPaintProperty, Curve, curve, frameNode);
}

void SwiperModelStatic::SetOnChange(FrameNode* frameNode, ChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateChangeEvent(std::move(onChange));
}

void SwiperModelStatic::SetIndicatorIsBoolean(FrameNode* frameNode, bool isBoolean)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIndicatorIsBoolean(isBoolean);
}

void SwiperModelStatic::SetOnAnimationStart(FrameNode* frameNode, AnimationStartEvent&& onAnimationStart)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateAnimationStartEvent(
        [event = std::move(onAnimationStart)](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
            CHECK_NULL_VOID(event);
            event(index, targetIndex, info);
        }
    );
}

void SwiperModelStatic::SetOnAnimationEnd(FrameNode* frameNode, AnimationEndEvent&& onAnimationEnd)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateAnimationEndEvent(
        [event = std::move(onAnimationEnd)](int32_t index, const AnimationCallbackInfo& info) {
            CHECK_NULL_VOID(event);
            event(index, info);
        }
    );
}

void SwiperModelStatic::SetOnGestureSwipe(FrameNode* frameNode, GestureSwipeEvent&& onGestureSwipe)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetGestureSwipeEvent(
        [event = std::move(onGestureSwipe)](int32_t index, const AnimationCallbackInfo& info) {
            CHECK_NULL_VOID(event);
            event(index, info);
        }
    );
}

void SwiperModelStatic::SetNestedScroll(FrameNode* frameNode, const int32_t nestedOpt)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    NestedScrollOptions option;
    option.forward = static_cast<NestedScrollMode>(nestedOpt);
    option.backward = static_cast<NestedScrollMode>(nestedOpt);
    pattern->SetNestedScroll(option);
}

void SwiperModelStatic::SetCustomContentTransition(FrameNode* frameNode, SwiperContentAnimatedTransition& transition)
{
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperCustomContentTransition(transition);
}

void SwiperModelStatic::SetOnContentDidScroll(FrameNode* frameNode, ContentDidScrollEvent&& onContentDidScroll)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetOnContentDidScroll(std::move(onContentDidScroll));
}

void SwiperModelStatic::SetIndicatorInteractive(FrameNode* frameNode, bool interactive)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIndicatorInteractive(interactive);
}

void SwiperModelStatic::SetPageFlipMode(FrameNode* frameNode, int32_t options)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPageFlipMode(options);
}

void SwiperModelStatic::SetHoverShow(FrameNode* frameNode, bool hoverShow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, HoverShow, hoverShow, frameNode);
}

void SwiperModelStatic::SetDisplayArrow(FrameNode* frameNode, bool displayArrow)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayArrow, displayArrow, frameNode);
}

void SwiperModelStatic::SetSwipeByGroup(FrameNode* frameNode, bool swipeByGroup)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, SwipeByGroup, swipeByGroup, frameNode);
}

void SwiperModelStatic::SetDisplayCount(FrameNode* frameNode, int32_t displayCount)
{
    if (displayCount <= 0) {
        return;
    }

    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayCount, displayCount, frameNode);
}

void SwiperModelStatic::ResetDisplayCount(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, DisplayCount, frameNode);
}

void SwiperModelStatic::SetMinSize(FrameNode* frameNode, const Dimension& minSize)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, MinSize, minSize, frameNode);
}

void SwiperModelStatic::SetPreviousMargin(FrameNode* frameNode, const Dimension& prevMargin,
    const std::optional<bool> &ignoreBlank)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, PrevMargin, TrimToPositive(prevMargin), frameNode);
    CHECK_NULL_VOID(ignoreBlank);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, PrevMarginIgnoreBlank, *ignoreBlank, frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetPrevMarginIgnoreBlank(*ignoreBlank);
}

void SwiperModelStatic::SetNextMargin(FrameNode* frameNode, const Dimension& nextMargin,
    const std::optional<bool> &ignoreBlank)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, NextMargin, TrimToPositive(nextMargin), frameNode);
    CHECK_NULL_VOID(ignoreBlank);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperLayoutProperty, NextMarginIgnoreBlank, *ignoreBlank, frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetNextMarginIgnoreBlank(*ignoreBlank);
}

void SwiperModelStatic::SetOnChangeEvent(FrameNode* frameNode,
    std::function<void(const BaseEventInfo* info)>&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);

    pattern->UpdateOnChangeEvent([event = std::move(onChangeEvent)](int32_t index) {
        CHECK_NULL_VOID(event);
        SwiperChangeEvent eventInfo(index);
        event(&eventInfo);
    });
}
} // namespace OHOS::Ace::NG
