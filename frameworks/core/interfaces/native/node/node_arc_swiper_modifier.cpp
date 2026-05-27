/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_arc_swiper_modifier.h"

#include "node_model.h"

#include "base/error/error_code.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/swiper/arc_swiper_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_change_event.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const std::vector<EdgeEffect> EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
constexpr int32_t NUM_0 = 0;
constexpr int32_t NUM_1 = 1;
constexpr int32_t NUM_2 = 2;
constexpr int32_t NUM_3 = 3;
constexpr int32_t NUM_4 = 4;
constexpr float ANIMATION_INFO_DEFAULT = 0.0f;
constexpr int32_t DEFAULT_DURATION = 400;
constexpr int32_t DEFAULT_EDGE_EFFECT_INDEX = 0;

bool GetArcSwiperTheme(FrameNode* frameNode, RefPtr<SwiperIndicatorTheme>& swiperIndicatorTheme)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, false);
    return true;
}

SwiperArcDotParameters GetDefaultArcSwiperIndicator(FrameNode* frameNode)
{
    SwiperArcDotParameters params;
    params.arcDirection = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    RefPtr<SwiperIndicatorTheme> swiperIndicatorTheme;
    if (!GetArcSwiperTheme(frameNode, swiperIndicatorTheme)) {
        return params;
    }
    params.itemColor = swiperIndicatorTheme->GetArcItemColor();
    params.selectedItemColor = swiperIndicatorTheme->GetArcSelectedItemColor();
    params.containerColor = swiperIndicatorTheme->GetArcContainerColor();
    params.maskColor = swiperIndicatorTheme->GetArcMaskColor();
    return params;
}

void SetArcSwiperIndex(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    index = index < 0 ? 0 : index;
    SwiperModelNG::SetIndex(frameNode, index);
}

void ResetArcSwiperIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetIndex(frameNode, 0);
}

void SetArcSwiperDuration(ArkUINodeHandle node, ArkUI_Float32 duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDuration(frameNode, static_cast<uint32_t>(duration));
}

void ResetArcSwiperDuration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDuration(frameNode, DEFAULT_DURATION);
}

void SetArcSwiperVertical(ArkUINodeHandle node, ArkUI_Bool isVertical)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDirection(frameNode, isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void ResetArcSwiperVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDirection(frameNode, Axis::HORIZONTAL);
}

void SetArcSwiperDisableSwipe(ArkUINodeHandle node, ArkUI_Bool disableSwipe)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisableSwipe(frameNode, disableSwipe);
}

void ResetArcSwiperDisableSwipe(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetDisableSwipe(frameNode, false);
}

void SetArcSwiperEffectMode(ArkUINodeHandle node, ArkUI_Int32 edgeEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (edgeEffect < 0 || edgeEffect >= static_cast<int32_t>(EDGE_EFFECT.size())) {
        edgeEffect = DEFAULT_EDGE_EFFECT_INDEX;
    }
    SwiperModelNG::SetEdgeEffect(frameNode, EDGE_EFFECT[edgeEffect]);
}

void ResetArcSwiperEffectMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetEdgeEffect(frameNode, EdgeEffect::SPRING);
}

void SetArcSwiperIndicator(ArkUINodeHandle node, ArkUI_Int32 show,
    ArkUI_Int32 arcDirection, ArkUI_Uint32 unselectedColor,
    ArkUI_Uint32 selectedColor, ArkUI_Uint32 backgroundColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!show) {
        SwiperModelNG::SetShowIndicator(frameNode, false);
        return;
    }
    SwiperModelNG::SetShowIndicator(frameNode, true);
    SwiperArcDotParameters params;
    if (arcDirection < 0 || arcDirection > static_cast<ArkUI_Int32>(SwiperArcDirection::NINE_CLOCK_DIRECTION)) {
        TAG_LOGW(AceLogTag::ACE_SWIPER,
            "ArcSwiper indicator arcDirection %{public}d is invalid, fallback to SIX_CLOCK_DIRECTION", arcDirection);
        params.arcDirection = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    } else {
        params.arcDirection = static_cast<SwiperArcDirection>(arcDirection);
    }
    params.itemColor = Color(unselectedColor);
    params.selectedItemColor = Color(selectedColor);
    params.containerColor = Color(backgroundColor);
    SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::ARC_DOT);
    SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
    SwiperModelNG::SetArcDotIndicatorStyle(frameNode, params);
}

void ResetArcSwiperIndicator(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto params = GetDefaultArcSwiperIndicator(frameNode);
    SwiperModelNG::SetShowIndicator(frameNode, true);
    SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::ARC_DOT);
    SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
    SwiperModelNG::SetArcDotIndicatorStyle(frameNode, params);
}

void SetArcSwiperDigitalCrownSensitivity(ArkUINodeHandle node, ArkUI_Int32 sensitivity)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDigitalCrownSensitivity(static_cast<CrownSensitivity>(sensitivity));
#endif
}

void ResetArcSwiperDigitalCrownSensitivity(ArkUINodeHandle node)
{
#ifdef SUPPORT_DIGITAL_CROWN
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDigitalCrownSensitivity(CrownSensitivity::MEDIUM);
#endif
}

void SetArcSwiperDisableTransitionAnimation(ArkUINodeHandle node, ArkUI_Bool disable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDisableTransitionAnimation(disable);
}

void ResetArcSwiperDisableTransitionAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetDisableTransitionAnimation(false);
}

ArkUI_Int32 GetArcSwiperIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return SwiperModelNG::GetIndex(frameNode);
}

ArkUI_Float32 GetArcSwiperDuration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return static_cast<ArkUI_Float32>(SwiperModelNG::GetDuration(frameNode));
}

ArkUI_Int32 GetArcSwiperVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return SwiperModelNG::GetDirection(frameNode) == Axis::VERTICAL ? 1 : 0;
}

ArkUI_Int32 GetArcSwiperDisableSwipe(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    return SwiperModelNG::GetDisableSwipe(frameNode) ? 1 : 0;
}

ArkUI_Int32 GetArcSwiperEffectMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto edgeEffect = SwiperModelNG::GetEffectMode(frameNode);
    for (int32_t i = 0; i < static_cast<int32_t>(EDGE_EFFECT.size()); i++) {
        if (EDGE_EFFECT[i] == edgeEffect) {
            return i;
        }
    }
    return DEFAULT_EDGE_EFFECT_INDEX;
}

void GetArcSwiperIndicator(ArkUINodeHandle node, ArkUIArcSwiperIndicatorOptions* options)
{
    CHECK_NULL_VOID(options);
    options->show = 0;
    options->arcDirection = static_cast<ArkUI_Int32>(SwiperArcDirection::SIX_CLOCK_DIRECTION);
    options->unselectedColor = Color::TRANSPARENT.GetValue();
    options->selectedColor = Color::TRANSPARENT.GetValue();
    options->backgroundColor = Color::TRANSPARENT.GetValue();

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    options->show = static_cast<ArkUI_Int32>(SwiperModelNG::GetShowIndicator(frameNode));
    RefPtr<SwiperIndicatorTheme> swiperIndicatorTheme;
    GetArcSwiperTheme(frameNode, swiperIndicatorTheme);
    if (swiperIndicatorTheme) {
        options->unselectedColor = swiperIndicatorTheme->GetArcItemColor().GetValue();
        options->selectedColor = swiperIndicatorTheme->GetArcSelectedItemColor().GetValue();
        options->backgroundColor = swiperIndicatorTheme->GetArcContainerColor().GetValue();
    }

    auto pattern = frameNode->GetPattern<ArcSwiperPattern>();
    CHECK_NULL_VOID(pattern);
    auto params = pattern->GetSwiperArcDotParameters();
    CHECK_NULL_VOID(params);
    options->arcDirection =
        static_cast<ArkUI_Int32>(params->arcDirection.value_or(SwiperArcDirection::SIX_CLOCK_DIRECTION));
    options->unselectedColor =
        params->itemColor.value_or(swiperIndicatorTheme ? swiperIndicatorTheme->GetArcItemColor() : Color::TRANSPARENT)
            .GetValue();
    options->selectedColor =
        params->selectedItemColor
            .value_or(swiperIndicatorTheme ? swiperIndicatorTheme->GetArcSelectedItemColor() : Color::TRANSPARENT)
            .GetValue();
    options->backgroundColor =
        params->containerColor
            .value_or(swiperIndicatorTheme ? swiperIndicatorTheme->GetArcContainerColor() : Color::TRANSPARENT)
            .GetValue();
}

ArkUI_Int32 GetArcSwiperDigitalCrownSensitivity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, static_cast<ArkUI_Int32>(CrownSensitivity::MEDIUM));
    auto pattern = frameNode->GetPattern<ArcSwiperPattern>();
    CHECK_NULL_RETURN(pattern, static_cast<ArkUI_Int32>(CrownSensitivity::MEDIUM));
    return static_cast<ArkUI_Int32>(pattern->GetDigitalCrownSensitivity());
}

ArkUI_Int32 GetArcSwiperDisableTransitionAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto pattern = frameNode->GetPattern<ArcSwiperPattern>();
    CHECK_NULL_RETURN(pattern, 0);
    return static_cast<ArkUI_Int32>(pattern->IsDisableTransitionAnimation());
}

void SetArcSwiperOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
        SwiperModelNG::SetOnChange(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetArcSwiperOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnChange(frameNode, nullptr);
}

void SetArcSwiperOnAnimationStart(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<AnimationStartEvent*>(callback);
        SwiperModelNG::SetOnAnimationStart(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnAnimationStart(frameNode, nullptr);
    }
}

void ResetArcSwiperOnAnimationStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnAnimationStart(frameNode, nullptr);
}

void SetArcSwiperOnAnimationEnd(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<AnimationEndEvent*>(callback);
        SwiperModelNG::SetOnAnimationEnd(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnAnimationEnd(frameNode, nullptr);
    }
}

void ResetArcSwiperOnAnimationEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnAnimationEnd(frameNode, nullptr);
}

void SetArcSwiperOnGestureSwipe(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onEvent = reinterpret_cast<GestureSwipeEvent*>(callback);
        SwiperModelNG::SetOnGestureSwipe(frameNode, std::move(*onEvent));
    } else {
        SwiperModelNG::SetOnGestureSwipe(frameNode, nullptr);
    }
}

void ResetArcSwiperOnGestureSwipe(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetOnGestureSwipe(frameNode, nullptr);
}

void CallArcSwiperShowNext(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::CallSwiperShowNext(frameNode);
}

void CallArcSwiperShowPrevious(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::CallSwiperShowPrevious(frameNode);
}

void CallArcSwiperFinishAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelNG::SetSwiperFinishAnimation(frameNode);
}
} // namespace

namespace NodeModifier {
const ArkUIArcSwiperModifier* GetArcSwiperModifier()
{
    static const ArkUIArcSwiperModifier modifier = {
        .setArcSwiperIndex = SetArcSwiperIndex,
        .resetArcSwiperIndex = ResetArcSwiperIndex,
        .setArcSwiperDuration = SetArcSwiperDuration,
        .resetArcSwiperDuration = ResetArcSwiperDuration,
        .setArcSwiperVertical = SetArcSwiperVertical,
        .resetArcSwiperVertical = ResetArcSwiperVertical,
        .setArcSwiperDisableSwipe = SetArcSwiperDisableSwipe,
        .resetArcSwiperDisableSwipe = ResetArcSwiperDisableSwipe,
        .setArcSwiperEffectMode = SetArcSwiperEffectMode,
        .resetArcSwiperEffectMode = ResetArcSwiperEffectMode,
        .setArcSwiperIndicator = SetArcSwiperIndicator,
        .resetArcSwiperIndicator = ResetArcSwiperIndicator,
        .setArcSwiperDigitalCrownSensitivity = SetArcSwiperDigitalCrownSensitivity,
        .resetArcSwiperDigitalCrownSensitivity = ResetArcSwiperDigitalCrownSensitivity,
        .setArcSwiperDisableTransitionAnimation = SetArcSwiperDisableTransitionAnimation,
        .resetArcSwiperDisableTransitionAnimation = ResetArcSwiperDisableTransitionAnimation,
        .getArcSwiperIndex = GetArcSwiperIndex,
        .getArcSwiperDuration = GetArcSwiperDuration,
        .getArcSwiperVertical = GetArcSwiperVertical,
        .getArcSwiperDisableSwipe = GetArcSwiperDisableSwipe,
        .getArcSwiperEffectMode = GetArcSwiperEffectMode,
        .getArcSwiperIndicator = GetArcSwiperIndicator,
        .getArcSwiperDigitalCrownSensitivity = GetArcSwiperDigitalCrownSensitivity,
        .getArcSwiperDisableTransitionAnimation = GetArcSwiperDisableTransitionAnimation,
        .setArcSwiperOnChange = SetArcSwiperOnChange,
        .resetArcSwiperOnChange = ResetArcSwiperOnChange,
        .setArcSwiperOnAnimationStart = SetArcSwiperOnAnimationStart,
        .resetArcSwiperOnAnimationStart = ResetArcSwiperOnAnimationStart,
        .setArcSwiperOnAnimationEnd = SetArcSwiperOnAnimationEnd,
        .resetArcSwiperOnAnimationEnd = ResetArcSwiperOnAnimationEnd,
        .setArcSwiperOnGestureSwipe = SetArcSwiperOnGestureSwipe,
        .resetArcSwiperOnGestureSwipe = ResetArcSwiperOnGestureSwipe,
        .callArcSwiperShowNext = CallArcSwiperShowNext,
        .callArcSwiperShowPrevious = CallArcSwiperShowPrevious,
        .callArcSwiperFinishAnimation = CallArcSwiperFinishAnimation,
    };
    return &modifier;
}

void SetArcSwiperChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [weak = AceType::WeakClaim(frameNode), extraParam](const BaseEventInfo* info) {
        CHECK_NULL_VOID(weak.Upgrade());
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            LOGE("ArcSwiper onChange callback execute failed.");
            return;
        }
        int32_t index = swiperInfo->GetIndex();
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ARC_SWIPER_CHANGE;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnChange(frameNode, std::move(onEvent));
}

void SetArcSwiperAnimationStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [weak = AceType::WeakClaim(frameNode), extraParam](
                       int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        CHECK_NULL_VOID(weak.Upgrade());
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ARC_SWIPER_ANIMATION_START;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        event.componentAsyncEvent.data[NUM_1].i32 = targetIndex;
        event.componentAsyncEvent.data[NUM_2].f32 = info.currentOffset.value_or(ANIMATION_INFO_DEFAULT);
        event.componentAsyncEvent.data[NUM_3].f32 = info.targetOffset.value_or(ANIMATION_INFO_DEFAULT);
        event.componentAsyncEvent.data[NUM_4].f32 = info.velocity.value_or(ANIMATION_INFO_DEFAULT);
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnAnimationStart(frameNode, std::move(onEvent));
}

void SetArcSwiperAnimationEnd(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [weak = AceType::WeakClaim(frameNode), extraParam](
                       int32_t index, const AnimationCallbackInfo& info) {
        CHECK_NULL_VOID(weak.Upgrade());
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ARC_SWIPER_ANIMATION_END;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        event.componentAsyncEvent.data[NUM_1].f32 = info.currentOffset.value_or(ANIMATION_INFO_DEFAULT);
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnAnimationEnd(frameNode, std::move(onEvent));
}

void SetArcSwiperGestureSwipe(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [weak = AceType::WeakClaim(frameNode), extraParam](
                       int32_t index, const AnimationCallbackInfo& info) {
        CHECK_NULL_VOID(weak.Upgrade());
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_ARC_SWIPER_GESTURE_SWIPE;
        event.componentAsyncEvent.data[NUM_0].i32 = index;
        event.componentAsyncEvent.data[NUM_1].f32 = info.currentOffset.value_or(ANIMATION_INFO_DEFAULT);
        SendArkUISyncEvent(&event);
    };
    SwiperModelNG::SetOnGestureSwipe(frameNode, std::move(onEvent));
}
} // namespace OHOS::Ace::NG::NodeModifier
} // namespace OHOS::Ace::NG
