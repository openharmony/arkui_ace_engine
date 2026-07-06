/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper/bridge/swiper_custom_modifier.h"

#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_model_static.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_change_event.h"

namespace OHOS::Ace::NG {
namespace {
ArkUINodeHandle CreateSwiperFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = SwiperModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUINodeHandle CreateArcSwiperFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = SwiperModelStatic::CreateArcFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->SetIsPureSwiper(true);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUINodeHandle CreateArcSwiperFrameNodeNG(ArkUI_Int32 nodeId)
{
    auto frameNode = SwiperModelNG::CreateArcSwiperFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    SwiperModelNG::SetIndicatorType(AceType::RawPtr(frameNode), SwiperIndicatorType::ARC_DOT);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUINodeHandle GetSwiperControllerCustom(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto controller = SwiperModelNG::GetOrCreateSwiperController(frameNode);
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(controller));
}

ArkUI_Int32 GetSwiperCurrentIndexCustom(ArkUINodeHandle node, ArkUI_Bool original)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return pattern->GetCurrentIndex(original);
}

ArkUI_Int32 GetSwiperTotalCountCustom(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return pattern->TotalCount();
}

ArkUI_Int32 GetSwiperDirectionCustom(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, static_cast<ArkUI_Int32>(Axis::NONE));
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, static_cast<ArkUI_Int32>(Axis::NONE));
    return static_cast<ArkUI_Int32>(pattern->GetDirection());
}

ArkUI_Bool IsSwiperAtStartCustom(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsAtStart();
}

ArkUI_Bool IsSwiperAtEndCustom(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsAtEnd();
}

void SetSwiperIndexCustom(ArkUINodeHandle node, ArkUI_Uint32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetIndex(frameNode, index);
}

void SetSwiperIndexCustomNG(ArkUINodeHandle node, ArkUI_Uint32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIndex(frameNode, index);
}

void SetSwiperDurationCustom(ArkUINodeHandle node, ArkUI_Uint32 duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetDuration(frameNode, duration);
}

void SetSwiperDurationCustomNG(ArkUINodeHandle node, ArkUI_Uint32 duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDuration(frameNode, duration);
}

void SetSwiperDirectionCustom(ArkUINodeHandle node, ArkUI_Int32 axis)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetDirection(frameNode, static_cast<Axis>(axis));
}

void SetSwiperDirectionCustomNG(ArkUINodeHandle node, ArkUI_Int32 axis)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDirection(frameNode, static_cast<Axis>(axis));
}

void SetSwiperDisableSwipeCustom(ArkUINodeHandle node, ArkUI_Bool disableSwipe)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetDisableSwipe(frameNode, disableSwipe);
}

void SetSwiperDisableSwipeCustomNG(ArkUINodeHandle node, ArkUI_Bool disableSwipe)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisableSwipe(frameNode, disableSwipe);
}

void SetSwiperDigitalCrownSensitivityCustom(ArkUINodeHandle node, ArkUI_Int32 sensitivity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetDigitalCrownSensitivity(frameNode, sensitivity);
}

void SetSwiperDigitalCrownSensitivityCustomNG(ArkUINodeHandle node, ArkUI_Int32 sensitivity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDigitalCrownSensitivity(frameNode, sensitivity);
}

void SetSwiperOnChangeCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<std::function<void(int32_t)>*>(callback);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetOnChange(frameNode, event ? std::move(*event) : nullptr);
}

void SetSwiperOnChangeCustomNG(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnChange(frameNode, event ? std::move(*event) : nullptr);
}

void SetSwiperOnAnimationStartCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<AnimationStartEvent*>(callback);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetOnAnimationStart(frameNode, event ? std::move(*event) : nullptr);
}

void SetSwiperOnAnimationStartCustomNG(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<AnimationStartEvent*>(callback);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnAnimationStart(frameNode, event ? std::move(*event) : nullptr);
}

void SetSwiperOnAnimationEndCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<AnimationEndEvent*>(callback);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetOnAnimationEnd(frameNode, event ? std::move(*event) : nullptr);
}

void SetSwiperOnAnimationEndCustomNG(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<AnimationEndEvent*>(callback);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnAnimationEnd(frameNode, event ? std::move(*event) : nullptr);
}

void SetSwiperOnGestureSwipeCustom(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<GestureSwipeEvent*>(callback);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetOnGestureSwipe(frameNode, event ? std::move(*event) : nullptr);
}

void SetSwiperOnGestureSwipeCustomNG(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* event = reinterpret_cast<GestureSwipeEvent*>(callback);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnGestureSwipe(frameNode, event ? std::move(*event) : nullptr);
}

void SetSwiperEdgeEffectCustom(ArkUINodeHandle node, ArkUI_Int32 edgeEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetEdgeEffect(frameNode, static_cast<EdgeEffect>(edgeEffect));
}

void SetSwiperEdgeEffectCustomNG(ArkUINodeHandle node, ArkUI_Int32 edgeEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetEdgeEffect(frameNode, static_cast<EdgeEffect>(edgeEffect));
}

void SetSwiperCustomContentTransitionCustom(ArkUINodeHandle node, void* transition)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* transitionInfo = reinterpret_cast<SwiperContentAnimatedTransition*>(transition);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(transitionInfo);
    SwiperModelStatic::SetCustomContentTransition(frameNode, *transitionInfo);
}

void SetSwiperCustomContentTransitionCustomNG(ArkUINodeHandle node, void* transition)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* transitionInfo = reinterpret_cast<SwiperContentAnimatedTransition*>(transition);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(transitionInfo);
    SwiperModelNG::SetCustomContentTransition(frameNode, *transitionInfo);
}

void SetSwiperDisableTransitionAnimationCustom(ArkUINodeHandle node, ArkUI_Bool isDisable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetDisableTransitionAnimation(frameNode, isDisable);
}

void SetSwiperDisableTransitionAnimationCustomNG(ArkUINodeHandle node, ArkUI_Bool isDisable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisableTransitionAnimation(frameNode, isDisable);
}

void SetSwiperIndicatorTypeCustom(ArkUINodeHandle node, ArkUI_Int32 indicatorType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetIndicatorType(frameNode, static_cast<SwiperIndicatorType>(indicatorType));
}

void SetSwiperIndicatorTypeCustomNG(ArkUINodeHandle node, ArkUI_Int32 indicatorType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIndicatorType(frameNode, static_cast<SwiperIndicatorType>(indicatorType));
}

void SetSwiperIndicatorIsBooleanCustom(ArkUINodeHandle node, ArkUI_Bool isBoolean)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetIndicatorIsBoolean(frameNode, isBoolean);
}

void SetSwiperIndicatorIsBooleanCustomNG(ArkUINodeHandle node, ArkUI_Bool isBoolean)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIndicatorIsBoolean(frameNode, isBoolean);
}

void SetSwiperShowIndicatorCustom(ArkUINodeHandle node, ArkUI_Bool showIndicator)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetShowIndicator(frameNode, showIndicator);
}

void SetSwiperShowIndicatorCustomNG(ArkUINodeHandle node, ArkUI_Bool showIndicator)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetShowIndicator(frameNode, showIndicator);
}

void SetSwiperArcDotIndicatorStyleCustom(ArkUINodeHandle node, void* swiperArcDotParameters)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* arcDotParameters = reinterpret_cast<SwiperArcDotParameters*>(swiperArcDotParameters);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(arcDotParameters);
    SwiperModelStatic::SetArcDotIndicatorStyle(frameNode, *arcDotParameters);
}

void SetSwiperArcDotIndicatorStyleCustomNG(ArkUINodeHandle node, void* swiperArcDotParameters)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    auto* arcDotParameters = reinterpret_cast<SwiperArcDotParameters*>(swiperArcDotParameters);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(arcDotParameters);
    SwiperModelNG::SetArcDotIndicatorStyle(frameNode, *arcDotParameters);
}

ArkUINodeHandle CreateCalendarSwiperNodeCustom(ArkUI_Int32 nodeId)
{
    auto swiperNode = FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG,
        nodeId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(1);
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperLayoutProperty->UpdateMeasureType(MeasureType::MATCH_PARENT);
    swiperLayoutProperty->UpdateLoop(true);
    swiperLayoutProperty->UpdateDisableSwipe(false);
    swiperNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(swiperNode));
}

ArkUINodeHandle CreateStepperSwiperNodeCustom(ArkUI_Int32 nodeId, ArkUI_Uint32 index)
{
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::NONE);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateDisableSwipe(true);
    swiperLayoutProperty->UpdateLoop(false);
    swiperLayoutProperty->UpdateCachedCount(0);
    swiperLayoutProperty->UpdateIndex(static_cast<int32_t>(index));
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperNode->MarkModifyDone();
    swiperNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(swiperNode));
}

void SwipeToCustom(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    auto swiperController = pattern->GetSwiperController();
    CHECK_NULL_VOID(swiperController);
    swiperController->SwipeTo(index);
}

ArkUI_Bool IsAnimationStoppedCustom(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(pattern, true);
    auto swiperAnimationController = pattern->GetController();
    return swiperAnimationController ? swiperAnimationController->IsStopped() : true;
}

void SetCurveLinearCustom(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto swiperPaintProperty = frameNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_VOID(swiperPaintProperty);
    swiperPaintProperty->UpdateCurve(Curves::LINEAR);
}

} // namespace

namespace NodeModifier {
const ArkUISwiperCustomModifier* GetSwiperCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISwiperCustomModifier modifier = {
        .createFrameNode = CreateSwiperFrameNode,
        .createArcFrameNode = CreateArcSwiperFrameNode,
        .createArcFrameNodeNG = CreateArcSwiperFrameNodeNG,
        .getSwiperController = GetSwiperControllerCustom,
        .getCurrentIndex = GetSwiperCurrentIndexCustom,
        .getTotalCount = GetSwiperTotalCountCustom,
        .getDirection = GetSwiperDirectionCustom,
        .isAtStart = IsSwiperAtStartCustom,
        .isAtEnd = IsSwiperAtEndCustom,
        .setIndex = SetSwiperIndexCustom,
        .setIndexNG = SetSwiperIndexCustomNG,
        .setDuration = SetSwiperDurationCustom,
        .setDurationNG = SetSwiperDurationCustomNG,
        .setDirection = SetSwiperDirectionCustom,
        .setDirectionNG = SetSwiperDirectionCustomNG,
        .setDisableSwipe = SetSwiperDisableSwipeCustom,
        .setDisableSwipeNG = SetSwiperDisableSwipeCustomNG,
        .setDigitalCrownSensitivity = SetSwiperDigitalCrownSensitivityCustom,
        .setDigitalCrownSensitivityNG = SetSwiperDigitalCrownSensitivityCustomNG,
        .setOnChange = SetSwiperOnChangeCustom,
        .setOnChangeNG = SetSwiperOnChangeCustomNG,
        .setOnAnimationStart = SetSwiperOnAnimationStartCustom,
        .setOnAnimationStartNG = SetSwiperOnAnimationStartCustomNG,
        .setOnAnimationEnd = SetSwiperOnAnimationEndCustom,
        .setOnAnimationEndNG = SetSwiperOnAnimationEndCustomNG,
        .setOnGestureSwipe = SetSwiperOnGestureSwipeCustom,
        .setOnGestureSwipeNG = SetSwiperOnGestureSwipeCustomNG,
        .setEdgeEffect = SetSwiperEdgeEffectCustom,
        .setEdgeEffectNG = SetSwiperEdgeEffectCustomNG,
        .setCustomContentTransition = SetSwiperCustomContentTransitionCustom,
        .setCustomContentTransitionNG = SetSwiperCustomContentTransitionCustomNG,
        .setDisableTransitionAnimation = SetSwiperDisableTransitionAnimationCustom,
        .setDisableTransitionAnimationNG = SetSwiperDisableTransitionAnimationCustomNG,
        .setIndicatorType = SetSwiperIndicatorTypeCustom,
        .setIndicatorTypeNG = SetSwiperIndicatorTypeCustomNG,
        .setIndicatorIsBoolean = SetSwiperIndicatorIsBooleanCustom,
        .setIndicatorIsBooleanNG = SetSwiperIndicatorIsBooleanCustomNG,
        .setShowIndicator = SetSwiperShowIndicatorCustom,
        .setShowIndicatorNG = SetSwiperShowIndicatorCustomNG,
        .setArcDotIndicatorStyle = SetSwiperArcDotIndicatorStyleCustom,
        .setArcDotIndicatorStyleNG = SetSwiperArcDotIndicatorStyleCustomNG,
        .createCalendarSwiperNode = CreateCalendarSwiperNodeCustom,
        .createStepperSwiperNode = CreateStepperSwiperNodeCustom,
        .swipeTo = SwipeToCustom,
        .isAnimationStopped = IsAnimationStoppedCustom,
        .setCurveLinear = SetCurveLinearCustom,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
