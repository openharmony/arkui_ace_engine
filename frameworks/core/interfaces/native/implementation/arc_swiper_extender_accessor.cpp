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
#include "core/interfaces/native/node/node_swiper_modifier.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/arc_swiper_content_transition_proxy_peer.h"
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
    CHECK_NULL_RETURN(frameNode, arcDotParam);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, arcDotParam);
    auto pipeline = context->GetCurrentContextSafelyWithCheck();
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
    CHECK_NULL_RETURN(frameNode, arcDotParam);
    auto context = frameNode->GetContext();
    CHECK_NULL_RETURN(context, arcDotParam);
    auto pipeline = context->GetCurrentContextSafelyWithCheck();
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
    auto swiperModifier = NodeModifier::GetSwiperCustomModifier();
    CHECK_NULL_RETURN(swiperModifier, nullptr);
    auto frameNode = reinterpret_cast<FrameNode*>(swiperModifier->createArcFrameNode(id));
    CHECK_NULL_RETURN(frameNode, nullptr);
    return reinterpret_cast<Ark_NativePointer>(frameNode);
}
void SetConstructInfoImpl(Ark_NativePointer node,
                          const Opt_ArcSwiperControllerHelper* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto swiperModifier = NodeModifier::GetSwiperCustomModifier();
    CHECK_NULL_VOID(swiperModifier);
    swiperModifier->setIndicatorType(
        reinterpret_cast<ArkUINodeHandle>(frameNode), static_cast<ArkUI_Int32>(SwiperIndicatorType::ARC_DOT));
    CHECK_NULL_VOID(controller);

    // obtain the internal ArcSwiperController
    auto internalSwiperController =
        AceType::Claim(reinterpret_cast<SwiperController*>(swiperModifier->getSwiperController(
            reinterpret_cast<ArkUINodeHandle>(frameNode))));

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
        auto swiperModifier = NodeModifier::GetSwiperCustomModifier();
        CHECK_NULL_VOID(swiperModifier);
        swiperModifier->setIndex(reinterpret_cast<ArkUINodeHandle>(frameNode), DEFAULT_ARC_SWIPER_CURRENT_INDEX);
        return;
    }
    auto swiperModifier = NodeModifier::GetSwiperCustomModifier();
    CHECK_NULL_VOID(swiperModifier);
    swiperModifier->setIndex(reinterpret_cast<ArkUINodeHandle>(frameNode),
        *convValue < 0 ? DEFAULT_ARC_SWIPER_CURRENT_INDEX : static_cast<ArkUI_Uint32>(*convValue));
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
        auto swiperModifier = NodeModifier::GetSwiperCustomModifier();
        CHECK_NULL_VOID(swiperModifier);
        swiperModifier->setIndicatorIsBoolean(reinterpret_cast<ArkUINodeHandle>(frameNode), false);
        auto arcDotParam = ProcessDotParameters(frameNode, style);
        swiperModifier->setArcDotIndicatorStyle(reinterpret_cast<ArkUINodeHandle>(frameNode), &arcDotParam);
        },
        [&showIndicator](const Ark_Boolean& style) {
        showIndicator = Converter::Convert<bool>(style);
    },
[frameNode]() {
        auto swiperModifier = NodeModifier::GetSwiperCustomModifier();
        CHECK_NULL_VOID(swiperModifier);
        swiperModifier->setIndicatorIsBoolean(reinterpret_cast<ArkUINodeHandle>(frameNode), true);
        auto arcDotParam = ProcessDefaultDotParameters(frameNode);
        swiperModifier->setArcDotIndicatorStyle(reinterpret_cast<ArkUINodeHandle>(frameNode), &arcDotParam);
        }
    );
    auto swiperModifier = NodeModifier::GetSwiperCustomModifier();
    CHECK_NULL_VOID(swiperModifier);
    swiperModifier->setShowIndicator(reinterpret_cast<ArkUINodeHandle>(frameNode), showIndicator);
    swiperModifier->setIndicatorType(
        reinterpret_cast<ArkUINodeHandle>(frameNode), static_cast<ArkUI_Int32>(SwiperIndicatorType::ARC_DOT));
}
void DurationImpl(Ark_NativePointer node,
                  const Opt_Int32* duration)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*duration);
    if (!convValue) {
        NodeModifier::GetSwiperCustomModifier()->setDuration(
            reinterpret_cast<ArkUINodeHandle>(frameNode), DEFAULT_DURATION);
        return;
    }
    NodeModifier::GetSwiperCustomModifier()->setDuration(reinterpret_cast<ArkUINodeHandle>(frameNode),
        *convValue < 0 ? DEFAULT_DURATION : static_cast<ArkUI_Uint32>(*convValue));
}
void VerticalImpl(Ark_NativePointer node, const Opt_Boolean* isVertical)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::OptConvert<bool>(*isVertical);
    if (!aceVal) {
        NodeModifier::GetSwiperCustomModifier()->setDirection(
            reinterpret_cast<ArkUINodeHandle>(frameNode), static_cast<ArkUI_Int32>(Axis::HORIZONTAL));
        return;
    }
    NodeModifier::GetSwiperCustomModifier()->setDirection(reinterpret_cast<ArkUINodeHandle>(frameNode),
        static_cast<ArkUI_Int32>(*aceVal ? Axis::VERTICAL : Axis::HORIZONTAL));
}
void DisableSwipeImpl(Ark_NativePointer node,
                      const Opt_Boolean* disabled)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*disabled);
    if (!convValue) {
        NodeModifier::GetSwiperCustomModifier()->setDisableSwipe(reinterpret_cast<ArkUINodeHandle>(frameNode), false);
        return;
    }
    NodeModifier::GetSwiperCustomModifier()->setDisableSwipe(reinterpret_cast<ArkUINodeHandle>(frameNode), *convValue);
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* sensitivity)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<CrownSensitivity>(*sensitivity);
    if (!convValue) {
        NodeModifier::GetSwiperCustomModifier()->setDigitalCrownSensitivity(
            reinterpret_cast<ArkUINodeHandle>(frameNode), 1);
        return;
    }
    NodeModifier::GetSwiperCustomModifier()->setDigitalCrownSensitivity(
        reinterpret_cast<ArkUINodeHandle>(frameNode), static_cast<ArkUI_Int32>(*convValue));
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_arkui_component_idlize_Callback_I32_Void* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        NodeModifier::GetSwiperCustomModifier()->setOnChange(reinterpret_cast<ArkUINodeHandle>(frameNode), nullptr);
        return;
    }
    std::function<void(int32_t)> onEvent = [arkCallback = CallbackHelper(*optValue)](int32_t index) {
        arkCallback.InvokeSync(Converter::ArkValue<Ark_Int32>(index));
    };
    NodeModifier::GetSwiperCustomModifier()->setOnChange(reinterpret_cast<ArkUINodeHandle>(frameNode), &onEvent);
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          const Opt_AnimationStartHandler* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        NodeModifier::GetSwiperCustomModifier()->setOnAnimationStart(
            reinterpret_cast<ArkUINodeHandle>(frameNode), nullptr);
        return;
    }
    AnimationStartEvent onEvent = [arkCallback = CallbackHelper(*optValue)](
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
    NodeModifier::GetSwiperCustomModifier()->setOnAnimationStart(
        reinterpret_cast<ArkUINodeHandle>(frameNode), &onEvent);
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        const Opt_AnimationEndHandler* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        NodeModifier::GetSwiperCustomModifier()->setOnAnimationEnd(
            reinterpret_cast<ArkUINodeHandle>(frameNode), nullptr);
        return;
    }
    AnimationEndEvent onEvent = [arkCallback = CallbackHelper(*optValue)](
                                    int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Float64>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Float64>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Float64>(info.velocity.value_or(0.0f)),
        };
        arkCallback.InvokeSync(arkIndex, arkExtraInfo);
    };
    NodeModifier::GetSwiperCustomModifier()->setOnAnimationEnd(reinterpret_cast<ArkUINodeHandle>(frameNode), &onEvent);
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        const Opt_GestureSwipeHandler* handler)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(handler);
    if (!optValue) {
        NodeModifier::GetSwiperCustomModifier()->setOnGestureSwipe(
            reinterpret_cast<ArkUINodeHandle>(frameNode), nullptr);
        return;
    }
    GestureSwipeEvent onEvent = [arkCallback = CallbackHelper(*optValue)](
                                    int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Float64>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Float64>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Float64>(info.velocity.value_or(0.0f)),
        };
        arkCallback.InvokeSync(arkIndex, arkExtraInfo);
    };
    NodeModifier::GetSwiperCustomModifier()->setOnGestureSwipe(reinterpret_cast<ArkUINodeHandle>(frameNode), &onEvent);
}
void EffectModeImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* edgeEffect)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto edgeEffOpt = Converter::OptConvert<EdgeEffect>(*edgeEffect);
    if (!edgeEffOpt) {
        NodeModifier::GetSwiperCustomModifier()->setEdgeEffect(reinterpret_cast<ArkUINodeHandle>(frameNode), static_cast<ArkUI_Int32>(EdgeEffect::SPRING));
        return;
    }
    NodeModifier::GetSwiperCustomModifier()->setEdgeEffect(
        reinterpret_cast<ArkUINodeHandle>(frameNode), static_cast<ArkUI_Int32>(*edgeEffOpt));
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const Opt_ArcSwiperContentAnimatedTransition* transition)
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
        auto peer = PeerUtils::CreatePeer<ArcSwiperContentTransitionProxyInnerPeer>();
        CHECK_NULL_VOID(peer);
        peer->SetHandler(proxy);
        arkCallback.InvokeSync(peer);
    };
    NodeModifier::GetSwiperCustomModifier()->setCustomContentTransition(
        reinterpret_cast<ArkUINodeHandle>(frameNode), &transitionInfo);
}
void DisableTransitionAnimationImpl(Ark_NativePointer node,
                                    const Opt_Boolean* disabled)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*disabled);
    if (!convValue) {
        NodeModifier::GetSwiperCustomModifier()->setDisableTransitionAnimation(
            reinterpret_cast<ArkUINodeHandle>(frameNode), false);
        return;
    }
    NodeModifier::GetSwiperCustomModifier()->setDisableTransitionAnimation(
        reinterpret_cast<ArkUINodeHandle>(frameNode), *convValue);
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
