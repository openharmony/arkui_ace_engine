/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/swiper/swiper_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/swiper_content_transition_proxy_peer.h"
#include "core/interfaces/native/implementation/arc_swiper_controller_peer.h"

namespace OHOS::Ace::NG {
const static int32_t DEFAULT_DURATION = 400;
const static uint32_t DEFAULT_ARC_SWIPER_CURRENT_INDEX = 0;
}

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<SwiperArcDirection>& dst, const Ark_ArcDirectionInner& src)
{
    switch (src) {
        case ARK_ARC_DIRECTION_INNER_THREE_CLOCK_DIRECTION: dst = SwiperArcDirection::THREE_CLOCK_DIRECTION; break;
        case ARK_ARC_DIRECTION_INNER_SIX_CLOCK_DIRECTION: dst = SwiperArcDirection::SIX_CLOCK_DIRECTION; break;
        case ARK_ARC_DIRECTION_INNER_NINE_CLOCK_DIRECTION: dst = SwiperArcDirection::NINE_CLOCK_DIRECTION; break;
        default: TAG_LOGE(AceLogTag::ACE_SWIPER, "Unexpected enum value in Ark_ArcDirection: %{public}d", src);
    }
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
SwiperArcDotParameters ProcessDotParameters(FrameNode* frameNode, const Ark_ArcDotIndicatorInner& src)
{
    SwiperArcDotParameters arcDotParam;
    auto pipeline = frameNode->GetContext()->GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, arcDotParam);
    auto swiperIndicatorTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, arcDotParam);

    arcDotParam.arcDirection = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    auto arcDirectionOpt = Converter::OptConvert<SwiperArcDirection>(src._arcDirection);
    if (arcDirectionOpt) {
        arcDotParam.arcDirection = arcDirectionOpt;
    }
    arcDotParam.itemColor = swiperIndicatorTheme->GetArcItemColor();
    auto itemColorOpt = Converter::OptConvert<Color>(src._itemColor);
    if (itemColorOpt) {
        arcDotParam.itemColor = itemColorOpt;
    }
    arcDotParam.selectedItemColor = swiperIndicatorTheme->GetArcSelectedItemColor();
    auto selectedItemColorOpt = Converter::OptConvert<Color>(src._selectedItemColor);
    if (selectedItemColorOpt) {
        arcDotParam.selectedItemColor = selectedItemColorOpt;
    }
    arcDotParam.containerColor = swiperIndicatorTheme->GetArcContainerColor();
    auto containerColorOpt = Converter::OptConvert<Color>(src._backgroundColor);
    if (containerColorOpt) {
        arcDotParam.containerColor = containerColorOpt;
    }
    arcDotParam.maskColor = swiperIndicatorTheme->GetArcMaskColor();
    auto maskColorOpt = Converter::OptConvert<NG::Gradient>(src._maskColor);
    if (maskColorOpt) {
        arcDotParam.maskColor = maskColorOpt;
    }
    return arcDotParam;
}

SwiperArcDotParameters ProcessDefaultDotParameters(FrameNode* frameNode)
{
    SwiperArcDotParameters arcDotParam;
    auto pipeline = frameNode->GetContext()->GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, arcDotParam);
    auto swiperIndicatorTheme = pipeline->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, arcDotParam);
    arcDotParam.arcDirection = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    arcDotParam.itemColor = swiperIndicatorTheme->GetArcItemColor();
    arcDotParam.selectedItemColor = swiperIndicatorTheme->GetArcSelectedItemColor();
    arcDotParam.containerColor = swiperIndicatorTheme->GetArcContainerColor();
    arcDotParam.maskColor = swiperIndicatorTheme->GetArcMaskColor();
    return arcDotParam;
}
} // namespace

namespace ArcSwiperExtenderAccessor {
Ark_NativePointer ArcSwiperConstructImpl(Ark_Int32 id,
                                         Ark_Int32 flags)
{
    auto frameNode = SwiperModelStatic::CreateArcFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void SetConstructInfoImpl(Ark_NativePointer node,
                          const Opt_ArcSwiperControllerHelper* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::ARC_DOT);
    CHECK_NULL_VOID(controller);

    // obtain the internal ArcSwiperController
    auto internalSwiperController = SwiperModelStatic::GetSwiperController(frameNode);

    // obtain the external ArcSwiperController peer
    auto abstPeerPtrOpt = Converter::OptConvert<Ark_ArcSwiperControllerHelper>(*controller);
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::ArcSwiperControllerHelperPeerImpl *>(*abstPeerPtrOpt);
    CHECK_NULL_VOID(peerImplPtr);

    // pass the internal controller to external management
    peerImplPtr->UpdateTargetController(internalSwiperController);
}
void IndexImpl(Ark_NativePointer node,
               const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        SwiperModelStatic::SetIndex(frameNode, DEFAULT_ARC_SWIPER_CURRENT_INDEX);
        return;
    }
    SwiperModelStatic::SetIndex(frameNode, *convValue < 0 ? DEFAULT_ARC_SWIPER_CURRENT_INDEX : *convValue);
}
void IndicatorImpl(Ark_NativePointer node,
                   const Opt_Union_ArcDotIndicatorInner_Boolean* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(style);
    bool showIndicator = true;
    Converter::VisitUnion(*style,
        [frameNode](const Ark_ArcDotIndicatorInner& style) {
            SwiperModelStatic::SetIndicatorIsBoolean(frameNode, false);
            auto arcDotParam = ProcessDotParameters(frameNode, style);
            SwiperModelStatic::SetArcDotIndicatorStyle(frameNode, arcDotParam);
        },
        [&showIndicator](const Ark_Boolean& style) {
            showIndicator = Converter::Convert<bool>(style);
        },
        [frameNode]() {
            SwiperModelStatic::SetIndicatorIsBoolean(frameNode, true);
            auto arcDotParam = ProcessDefaultDotParameters(frameNode);
            SwiperModelStatic::SetArcDotIndicatorStyle(frameNode, arcDotParam);
        }
    );
    SwiperModelStatic::SetShowIndicator(frameNode, showIndicator);
    SwiperModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::ARC_DOT);
}
void DurationImpl(Ark_NativePointer node,
                  const Opt_Int32* duration)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*duration);
    if (!convValue) {
        SwiperModelStatic::SetDuration(frameNode, DEFAULT_DURATION);
        return;
    }
    SwiperModelStatic::SetDuration(frameNode, *convValue < 0 ? DEFAULT_DURATION : *convValue);
}
void VerticalImpl(Ark_NativePointer node,
                  const Opt_Boolean* isVertical)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::OptConvert<bool>(*isVertical);
    if (!aceVal) {
        SwiperModelStatic::SetDirection(frameNode, Axis::HORIZONTAL);
        return;
    }
    SwiperModelStatic::SetDirection(frameNode, *aceVal ? Axis::VERTICAL : Axis::HORIZONTAL);
}
void DisableSwipeImpl(Ark_NativePointer node,
                      const Opt_Boolean* disabled)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*disabled);
    if (!convValue) {
        SwiperModelStatic::SetDisableSwipe(frameNode, false);
        return;
    }
    SwiperModelStatic::SetDisableSwipe(frameNode, *convValue);
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* sensitivity)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<CrownSensitivity>(*sensitivity);
    if (!convValue) {
        SwiperModelStatic::SetDigitalCrownSensitivity(frameNode, 1);
        return;
    }
    SwiperModelStatic::SetDigitalCrownSensitivity(frameNode, static_cast<int32_t>(*convValue));
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_arkui_component_idlize_Callback_I32_Void* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        SwiperModelStatic::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](int32_t index) {
        arkCallback.InvokeSync(Converter::ArkValue<Ark_Int32>(index));
    };
    SwiperModelStatic::SetOnChange(frameNode, onEvent);
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          const Opt_AnimationStartHandler* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        SwiperModelStatic::SetOnAnimationStart(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](
        int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
        auto arkTargetIndex = Converter::ArkValue<Ark_Int32>(targetIndex);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Float64>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Float64>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Float64>(info.velocity.value_or(0.0f)),
        };
        arkCallback.InvokeSync(arkIndex, arkTargetIndex, arkExtraInfo);
    };
    SwiperModelStatic::SetOnAnimationStart(frameNode, onEvent);
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        const Opt_AnimationEndHandler* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        SwiperModelStatic::SetOnAnimationEnd(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Float64>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Float64>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Float64>(info.velocity.value_or(0.0f)),
        };
        arkCallback.InvokeSync(arkIndex, arkExtraInfo);
    };
    SwiperModelStatic::SetOnAnimationEnd(frameNode, onEvent);
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        const Opt_GestureSwipeHandler* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        SwiperModelStatic::SetOnGestureSwipe(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Float64>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Float64>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Float64>(info.velocity.value_or(0.0f)),
        };
        arkCallback.InvokeSync(arkIndex, arkExtraInfo);
    };
    SwiperModelStatic::SetOnGestureSwipe(frameNode, onEvent);
}
void EffectModeImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* edgeEffect)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto edgeEffOpt = Converter::OptConvert<EdgeEffect>(*edgeEffect);
    if (!edgeEffOpt) {
        SwiperModelStatic::SetEdgeEffect(frameNode, EdgeEffect::SPRING);
        return;
    }
    SwiperModelStatic::SetEdgeEffect(frameNode, *edgeEffOpt);
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const Opt_SwiperContentAnimatedTransition* transition)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperContentAnimatedTransition transitionInfo;
    auto optValue = Converter::GetOptPtr(transition);
    CHECK_NULL_VOID(optValue);
    auto optTimeout = Converter::OptConvert<Ark_Int32>(optValue->timeout);
    if (optTimeout) {
        transitionInfo.timeout = *optTimeout;
    }

    transitionInfo.transition =
        [arkCallback = CallbackHelper(optValue->transition)](const RefPtr<SwiperContentTransitionProxy>& proxy) {
        auto peer = new SwiperContentTransitionProxyPeer();
        CHECK_NULL_VOID(peer);
        peer->SetHandler(proxy);
        arkCallback.InvokeSync(peer);
    };
    SwiperModelStatic::SetCustomContentTransition(frameNode, transitionInfo);
}
void DisableTransitionAnimationImpl(Ark_NativePointer node,
                                    const Opt_Boolean* disabled)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*disabled);
    if (!convValue) {
        SwiperModelStatic::SetDisableTransitionAnimation(frameNode, false);
        return;
    }
    SwiperModelStatic::SetDisableTransitionAnimation(frameNode, *convValue);
}
} // ArcSwiperExtenderAccessor
const GENERATED_ArkUIArcSwiperExtenderAccessor* GetArcSwiperExtenderAccessor()
{
    static const GENERATED_ArkUIArcSwiperExtenderAccessor ArcSwiperExtenderAccessorImpl {
        ArcSwiperExtenderAccessor::ArcSwiperConstructImpl,
        ArcSwiperExtenderAccessor::SetConstructInfoImpl,
        ArcSwiperExtenderAccessor::IndexImpl,
        ArcSwiperExtenderAccessor::IndicatorImpl,
        ArcSwiperExtenderAccessor::DurationImpl,
        ArcSwiperExtenderAccessor::VerticalImpl,
        ArcSwiperExtenderAccessor::DisableSwipeImpl,
        ArcSwiperExtenderAccessor::DigitalCrownSensitivityImpl,
        ArcSwiperExtenderAccessor::OnChangeImpl,
        ArcSwiperExtenderAccessor::OnAnimationStartImpl,
        ArcSwiperExtenderAccessor::OnAnimationEndImpl,
        ArcSwiperExtenderAccessor::OnGestureSwipeImpl,
        ArcSwiperExtenderAccessor::EffectModeImpl,
        ArcSwiperExtenderAccessor::CustomContentTransitionImpl,
        ArcSwiperExtenderAccessor::DisableTransitionAnimationImpl,
    };
    return &ArcSwiperExtenderAccessorImpl;
}

}
