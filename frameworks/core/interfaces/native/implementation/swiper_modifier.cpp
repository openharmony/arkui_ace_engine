/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "base/utils/string_utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/pattern/swiper/swiper_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/implementation/swiper_content_transition_proxy_peer.h"
#include "core/interfaces/native/implementation/swiper_controller_modifier_peer_impl.h"
#include "core/interfaces/native/implementation/indicator_component_controller_peer.h"
#include "core/interfaces/native/implementation/dot_indicator_peer_impl.h"
#include "core/interfaces/native/implementation/digit_indicator_peer_impl.h"

namespace OHOS::Ace::NG {
using ArrowStyleVariantType = std::variant<SwiperArrowParameters, bool>;
using DisplayCountVariantType = std::variant<int32_t, std::string, Ark_SwiperAutoFill>;
const static int32_t DEFAULT_DURATION = 400;
const static int32_t DEFAULT_DISPLAY_COUNT = 1;
const static int32_t DEFAULT_CACHED_COUNT = 1;
const auto DEFAULT_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(-1, 1, 328, 34);

namespace {
std::optional<int32_t> ProcessBindableIndex(FrameNode* frameNode, const Opt_Union_I32_Bindable *value)
{
    std::optional<int32_t> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Int32& src) {
            result = Converter::OptConvert<int32_t>(src);
        },
        [&result, frameNode](const Ark_Bindable_I32& src) {
            result = Converter::OptConvert<int32_t>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const BaseEventInfo* info) {
                const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
                CHECK_NULL_VOID(swiperInfo);
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(swiperInfo->GetIndex()));
            };
            SwiperModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
}

namespace OHOS::Ace::NG::Converter {

template<>
ArrowStyleVariantType Convert(const Ark_ArrowStyle& src)
{
    SwiperArrowParameters p;
    p.isShowBackground = Converter::OptConvert<bool>(src.showBackground);
    p.isSidebarMiddle = Converter::OptConvert<bool>(src.isSidebarMiddle);
    p.backgroundSize = Converter::OptConvert<Dimension>(src.backgroundSize);
    p.arrowSize = Converter::OptConvert<Dimension>(src.arrowSize);
    p.backgroundColor = Converter::OptConvert<Color>(src.backgroundColor);
    p.arrowColor = Converter::OptConvert<Color>(src.arrowColor);
    return p;
}

template<>
ArrowStyleVariantType Convert(const Ark_Boolean& src)
{
    return Convert<bool>(src);
}

template<>
DisplayCountVariantType Convert(const Ark_Int32& src)
{
    return Converter::Convert<int32_t>(src);
}

template<>
DisplayCountVariantType Convert(const Ark_String& src)
{
    return Converter::Convert<std::string>(src);
}

template<>
DisplayCountVariantType Convert(const Ark_SwiperAutoFill& src)
{
    return src;
}

template<>
Ark_Function Convert(const Ark_Function& src)
{
    return src;
}

template<>
inline void AssignCast(std::optional<SwiperDisplayMode>& dst, const Ark_SwiperDisplayMode& src)
{
    switch (src) {
        case ARK_SWIPER_DISPLAY_MODE_STRETCH: dst = SwiperDisplayMode::STRETCH; break;
        default: LOGE("Unexpected enum value in Ark_SwiperDisplayMode: %{public}d", src);
    }
}

template<>
inline void AssignCast(std::optional<NestedScrollMode>& dst, const Ark_SwiperNestedScrollMode& src)
{
    switch (src) {
        case ARK_SWIPER_NESTED_SCROLL_MODE_SELF_ONLY:
            dst = NestedScrollMode::SELF_ONLY;
            break;
        case ARK_SWIPER_NESTED_SCROLL_MODE_SELF_FIRST:
            dst = NestedScrollMode::SELF_FIRST;
            break;
        default: LOGE("Unexpected enum value in Ark_SwiperNestedScrollMode: %{public}d", src);
    }
}

template<>
SwiperAutoPlayOptions Convert(const Ark_AutoPlayOptions& src)
{
    return {
        .stopWhenTouched = src.stopWhenTouched
    };
}

void AssignArkValue(Ark_SwiperContentWillScrollResult &dst, const SwiperContentWillScrollResult& src, ConvContext *ctx)
{
    dst.currentIndex = Converter::ArkValue<Ark_Int32>(src.currentIndex, ctx);
    dst.comingIndex = Converter::ArkValue<Ark_Int32>(src.comingIndex, ctx);
    dst.offset = Converter::ArkValue<Ark_Float64>(src.offset, ctx);
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG {
namespace SwiperAttributeModifierInternal {
std::optional<OHOS::Ace::Dimension> &ResetIfInvalid(std::optional<OHOS::Ace::Dimension> &dimOpt)
{
    if (dimOpt && dimOpt->IsNegative()) {
        dimOpt.reset();
    }
    return dimOpt;
}

bool IsCustom(std::optional<Dimension> &dimOpt)
{
    return dimOpt && dimOpt->Unit() != DimensionUnit::PERCENT && !dimOpt->IsNegative();
}

bool CheckSwiperParameters(SwiperParameters& p)
{
    ResetIfInvalid(p.dimLeft);
    ResetIfInvalid(p.dimTop);
    ResetIfInvalid(p.dimRight);
    ResetIfInvalid(p.dimBottom);
    ResetIfInvalid(p.dimStart);
    ResetIfInvalid(p.dimEnd);

    ResetIfInvalid(p.itemWidth);
    p.itemWidth = p.itemWidth ? p.itemWidth : 6.0_vp;
    ResetIfInvalid(p.itemHeight);
    p.itemHeight = p.itemHeight ? p.itemHeight : 6.0_vp;
    ResetIfInvalid(p.selectedItemWidth);
    p.selectedItemWidth = p.selectedItemWidth ? p.selectedItemWidth : 6.0_vp;
    ResetIfInvalid(p.selectedItemHeight);
    p.selectedItemHeight = p.selectedItemHeight ? p.selectedItemHeight : 6.0_vp;

    if (p.maxDisplayCountVal && (*(p.maxDisplayCountVal) < 6 || *(p.maxDisplayCountVal) > 9)) {
        p.maxDisplayCountVal.reset();
    }

    return IsCustom(p.itemWidth) || IsCustom(p.itemHeight) ||
        IsCustom(p.selectedItemWidth) || IsCustom(p.selectedItemHeight);
}

void CheckSwiperDigitalParameters(SwiperDigitalParameters& p)
{
    ResetIfInvalid(p.dimLeft);
    ResetIfInvalid(p.dimTop);
    ResetIfInvalid(p.dimRight);
    ResetIfInvalid(p.dimBottom);
    ResetIfInvalid(p.dimStart);
    ResetIfInvalid(p.dimEnd);

    ResetIfInvalid(p.fontSize);
    p.fontSize = p.fontSize ? p.fontSize : 14.0_vp;
    ResetIfInvalid(p.selectedFontSize);
    p.selectedFontSize = p.selectedFontSize ? p.selectedFontSize : 14.0_vp;
}
} // namespace SwiperAttributeModifierInternal
} // namespace OHOS::Ace::NG
using namespace OHOS::Ace::NG::SwiperAttributeModifierInternal;

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr uint32_t DEFAULT_INTERVAL_VALUE = 3000;
constexpr int32_t INVALID_VALUE = 0;
constexpr int32_t DEFAULT_VALUE = 6;

namespace SwiperModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SwiperModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SwiperModifier
namespace SwiperInterfaceModifier {
void SetSwiperOptionsImpl(Ark_NativePointer node,
                          const Opt_SwiperController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    // obtain the internal SwiperController
    auto internalSwiperController = SwiperModelStatic::GetSwiperController(frameNode);

    // obtain the external SwiperController peer
    auto abstPeerPtrOpt = Converter::OptConvertPtr<Ark_SwiperController>(controller);
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::SwiperControllerPeerImpl *>(*abstPeerPtrOpt);
    CHECK_NULL_VOID(peerImplPtr);

    // pass the internal controller to external management
    peerImplPtr->AddTargetController(internalSwiperController);
}
} // SwiperInterfaceModifier
namespace SwiperAttributeModifier {
void SetIndexImpl(Ark_NativePointer node,
                  const Opt_Union_I32_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = ProcessBindableIndex(frameNode, value);
    Validator::ValidateNonNegative(convValue);
    SwiperModelStatic::SetIndex(frameNode, convValue.value_or(OHOS::Ace::DEFAULT_SWIPER_CURRENT_INDEX));
}
void SetAutoPlay0Impl(Ark_NativePointer node,
                     const Opt_Boolean* autoPlay)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto autoPlayConv = Converter::OptConvertPtr<bool>(autoPlay);
    if (!autoPlayConv) {
        SwiperModelStatic::SetAutoPlay(frameNode, false);
        return;
    }
    SwiperModelStatic::SetAutoPlay(frameNode, *autoPlayConv);
}
void SetIntervalImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        SwiperModelStatic::SetAutoPlayInterval(frameNode, DEFAULT_INTERVAL_VALUE);
        return;
    }
    auto convValue2 = Converter::Convert<int32_t>(value->value);
    if (convValue2 < INVALID_VALUE) {
        SwiperModelStatic::SetAutoPlayInterval(frameNode, DEFAULT_INTERVAL_VALUE);
        return;
    }
    SwiperModelStatic::SetAutoPlayInterval(frameNode, convValue2);
}
namespace {
void SetIndicator(FrameNode* frameNode, const Ark_DigitIndicator& src)
{
    CHECK_NULL_VOID(frameNode);
    auto peerDigitIndicator = src;
    CHECK_NULL_VOID(peerDigitIndicator);
    auto digitParam = peerDigitIndicator->GetDigitParameters();
    CheckSwiperDigitalParameters(digitParam);
    SwiperModelStatic::SetIndicatorIsBoolean(frameNode, false);
    SwiperModelStatic::SetDigitIndicatorStyle(frameNode, digitParam);
    SwiperModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    SwiperModelStatic::SetShowIndicator(frameNode, true);
}
void SetIndicator(FrameNode* frameNode, const Ark_DotIndicator& src)
{
    CHECK_NULL_VOID(frameNode);
    auto peerDotIndicator = src;
    CHECK_NULL_VOID(peerDotIndicator);
    auto dotParam = peerDotIndicator->GetDotParameters();
    auto isCustomSize = CheckSwiperParameters(dotParam);
    SwiperModelStatic::SetIndicatorIsBoolean(frameNode, false);
    SwiperModelStatic::SetDotIndicatorStyle(frameNode, dotParam);
    SwiperModelStatic::SetIsIndicatorCustomSize(frameNode, isCustomSize);
    SwiperModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    SwiperModelStatic::SetShowIndicator(frameNode, true);
}
void SetIndicator(FrameNode* frameNode, const Ark_Boolean& src)
{
    auto boolParam = Converter::Convert<bool>(src);
    SwiperModelStatic::SetIndicatorIsBoolean(frameNode, true);
    SwiperModelStatic::SetDotIndicatorStyle(frameNode, SwiperParameters());
    SwiperModelStatic::SetIsIndicatorCustomSize(frameNode, false);
    SwiperModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    SwiperModelStatic::SetShowIndicator(frameNode, boolParam);
}
void SetIndicator(FrameNode* frameNode, const Ark_IndicatorComponentController& src)
{
    CHECK_NULL_VOID(frameNode);
    auto controller = src;
    CHECK_NULL_VOID(controller);
    controller->SetSwiperNodeBySwiper(OHOS::Ace::AceType::Claim(frameNode));
    SwiperModelStatic::SetBindIndicator(frameNode, true);
}
} // namespace
void SetIndicatorImpl(Ark_NativePointer node,
                      const Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnion(*value, [frameNode](const auto& value) { SetIndicator(frameNode, value); },
        [frameNode]() {
            SwiperModelStatic::SetIndicatorIsBoolean(frameNode, true);
            SwiperModelStatic::SetDotIndicatorStyle(frameNode, SwiperParameters());
            SwiperModelStatic::SetIsIndicatorCustomSize(frameNode, false);
            SwiperModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
            SwiperModelStatic::SetShowIndicator(frameNode, true);
        });
}
void SetLoopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        SwiperModelStatic::SetLoop(frameNode, true);
        return;
    }
    SwiperModelStatic::SetLoop(frameNode, *convValue);
}
void SetDurationImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        SwiperModelStatic::SetDuration(frameNode, DEFAULT_DURATION);
        return;
    }
    SwiperModelStatic::SetDuration(frameNode, *convValue < 0 ? DEFAULT_DURATION : *convValue);
}
void SetVerticalImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::OptConvertPtr<bool>(value);
    if (!aceVal) {
        SwiperModelStatic::SetDirection(frameNode, Axis::HORIZONTAL);
        return;
    }
    SwiperModelStatic::SetDirection(frameNode, *aceVal ? Axis::VERTICAL : Axis::HORIZONTAL);
}
void SetItemSpaceImpl(Ark_NativePointer node,
                      const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperModelStatic::SetItemSpace(frameNode, Converter::OptConvertPtr<Dimension>(value));
}
void SetDisplayModeImpl(Ark_NativePointer node,
                        const Opt_SwiperDisplayMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto dispModeOpt = Converter::OptConvertPtr<SwiperDisplayMode>(value);
    if (!dispModeOpt) {
        SwiperModelStatic::SetDisplayMode(frameNode, SwiperDisplayMode::STRETCH);
        return;
    }
    SwiperModelStatic::SetDisplayMode(frameNode, *dispModeOpt);
}
void SetCachedCount0Impl(Ark_NativePointer node,
                         const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        SwiperModelStatic::SetCachedCount(frameNode, DEFAULT_CACHED_COUNT);
        return;
    }
    SwiperModelStatic::SetCachedCount(frameNode, *convValue);
}
void SetEffectModeImpl(Ark_NativePointer node,
                       const Opt_EdgeEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto edgeEffOpt = Converter::OptConvertPtr<EdgeEffect>(value);
    if (!edgeEffOpt) {
        SwiperModelStatic::SetEdgeEffect(frameNode, EdgeEffect::SPRING);
        return;
    }
    SwiperModelStatic::SetEdgeEffect(frameNode, *edgeEffOpt);
}
void SetDisableSwipeImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        SwiperModelStatic::SetDisableSwipe(frameNode, false);
        return;
    }
    SwiperModelStatic::SetDisableSwipe(frameNode, *convValue);
}
void SetCurveImpl(Ark_NativePointer node,
                  const Opt_Union_Curve_String_ICurve* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto curveVal = Converter::OptConvert<RefPtr<Curve>>(*value);
    if (!curveVal) {
        SwiperModelStatic::SetCurve(frameNode, DEFAULT_CURVE);
        return;
    }
    SwiperModelStatic::SetCurve(frameNode, *curveVal);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SwiperModelStatic::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](int32_t index) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(index));
    };
    SwiperModelStatic::SetOnChange(frameNode, onEvent);
}
void SetOnSelectedImpl(Ark_NativePointer node,
                       const Opt_Callback_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SwiperModelStatic::SetOnSelected(frameNode, nullptr);
        return;
    }
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onSelected = [weakNode, arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        CHECK_NULL_VOID(swiperInfo);
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(swiperInfo->GetIndex()));
    };
    SwiperModelStatic::SetOnSelected(frameNode, onSelected);
}
void SetOnUnselectedImpl(Ark_NativePointer node,
                         const Opt_Callback_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SwiperModelStatic::SetOnUnselected(frameNode, nullptr);
        return;
    }
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onUnselected = [weakNode, arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        CHECK_NULL_VOID(swiperInfo);
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(swiperInfo->GetIndex()));
    };
    SwiperModelStatic::SetOnUnselected(frameNode, onUnselected);
}
void SetOnAnimationStartImpl(Ark_NativePointer node,
                             const Opt_OnSwiperAnimationStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
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
        arkCallback.Invoke(arkIndex, arkTargetIndex, arkExtraInfo);
    };
    SwiperModelStatic::SetOnAnimationStart(frameNode, onEvent);
}
void SetOnAnimationEndImpl(Ark_NativePointer node,
                           const Opt_OnSwiperAnimationEndCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
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
        arkCallback.Invoke(arkIndex, arkExtraInfo);
    };
    SwiperModelStatic::SetOnAnimationEnd(frameNode, onEvent);
}
void SetOnGestureSwipeImpl(Ark_NativePointer node,
                           const Opt_OnSwiperGestureSwipeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
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
        arkCallback.Invoke(arkIndex, arkExtraInfo);
    };
    SwiperModelStatic::SetOnGestureSwipe(frameNode, onEvent);
}
void SetNestedScrollImpl(Ark_NativePointer node,
                         const Opt_SwiperNestedScrollMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto nestedModeOpt = Converter::OptConvertPtr<NestedScrollMode>(value);
    if (!nestedModeOpt) {
        SwiperModelStatic::SetNestedScroll(frameNode, static_cast<int>(NestedScrollMode::SELF_ONLY));
        return;
    }
    SwiperModelStatic::SetNestedScroll(frameNode, static_cast<int>(*nestedModeOpt));
}
void SetCustomContentTransitionImpl(Ark_NativePointer node,
                                    const Opt_SwiperContentAnimatedTransition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperContentAnimatedTransition transitionInfo;
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SwiperModelStatic::SetCustomContentTransition(frameNode, transitionInfo);
        return;
    }
    auto optTimeout = Converter::OptConvert<Ark_Int32>(optValue->timeout);
    if (optTimeout) {
        transitionInfo.timeout = *optTimeout;
    }

    transitionInfo.transition =
        [arkCallback = CallbackHelper(optValue->transition)](const RefPtr<SwiperContentTransitionProxy>& proxy) {
        auto peer = new SwiperContentTransitionProxyPeer();
        CHECK_NULL_VOID(peer);
        peer->SetHandler(proxy);
        arkCallback.Invoke(peer);
    };
    SwiperModelStatic::SetCustomContentTransition(frameNode, transitionInfo);
}
void SetOnContentDidScrollImpl(Ark_NativePointer node,
                               const Opt_ContentDidScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SwiperModelStatic::SetOnContentDidScroll(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](
        int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
        auto arkSelectedIndex = Converter::ArkValue<Ark_Int32>(selectedIndex);
        auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
        auto arkPosition = Converter::ArkValue<Ark_Float64>(position);
        auto arkMainAxisLength = Converter::ArkValue<Ark_Float64>(mainAxisLength);
        arkCallback.Invoke(arkSelectedIndex, arkIndex, arkPosition, arkMainAxisLength);
    };
    SwiperModelStatic::SetOnContentDidScroll(frameNode, onEvent);
}
void SetIndicatorInteractiveImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        SwiperModelStatic::SetIndicatorInteractive(frameNode, true);
        return;
    }
    SwiperModelStatic::SetIndicatorInteractive(frameNode, *convValue);
}
void SetPageFlipModeImpl(Ark_NativePointer node,
                         const Opt_PageFlipMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    int32_t defaultValue = static_cast<int32_t>(PageFlipMode::CONTINUOUS);
    SwiperModelStatic::SetPageFlipMode(frameNode, convValue.value_or(defaultValue));
}
void SetOnContentWillScrollImpl(Ark_NativePointer node,
                                const Opt_ContentWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SwiperModelStatic::SetOnContentWillScroll(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](
        const SwiperContentWillScrollResult& resultIn) -> bool {
        auto arkResult = Converter::ArkValue<Ark_SwiperContentWillScrollResult>(resultIn, Converter::FC);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(arkResult);
        return Converter::Convert<bool>(result);
    };
    SwiperModelStatic::SetOnContentWillScroll(frameNode, std::move(onEvent));
}
void SetAutoPlay1Impl(Ark_NativePointer node,
                     const Opt_Boolean* autoPlay,
                     const Opt_AutoPlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto autoPlayConv = Converter::OptConvertPtr<bool>(autoPlay);
    if (!autoPlayConv) {
        SwiperModelStatic::SetAutoPlay(frameNode, false);
    } else {
        SwiperModelStatic::SetAutoPlay(frameNode, *autoPlayConv);
    }
    auto optionsConv = Converter::OptConvertPtr<SwiperAutoPlayOptions>(options);
    if (!optionsConv) {
        SwiperAutoPlayOptions swiperAutoPlayOptions;
        SwiperModelStatic::SetAutoPlayOptions(frameNode, swiperAutoPlayOptions);
        return;
    }
    SwiperModelStatic::SetAutoPlayOptions(frameNode, *optionsConv);
}
void SetDisplayArrowImpl(Ark_NativePointer node,
                         const Opt_Union_ArrowStyle_Boolean* value,
                         const Opt_Boolean* isHoverShow)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optArrow = Converter::OptConvertPtr<ArrowStyleVariantType>(value);
    if (auto show = Converter::OptConvertPtr<bool>(isHoverShow); show) {
        SwiperModelStatic::SetHoverShow(frameNode, *show);
    }
    if (!optArrow) {
        SwiperModelStatic::SetDisplayArrow(frameNode, false);
        return;
    }
    bool *arrowBoolPtr = std::get_if<bool>(&(*optArrow));
    if (arrowBoolPtr && !*arrowBoolPtr) {
        SwiperModelStatic::SetDisplayArrow(frameNode, false);
        return;
    }

    if (auto arrowStylePtr = std::get_if<SwiperArrowParameters>(&(*optArrow)); arrowStylePtr) {
        SwiperModelStatic::ParseAndSetArrowStyle(frameNode, *arrowStylePtr);
        return;
    }

    SwiperModelStatic::SetDefaultArrowStyle(frameNode);
}
void SetCachedCount1Impl(Ark_NativePointer node,
                         const Opt_Int32* count,
                         const Opt_Boolean* isShown)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convCount = Converter::OptConvertPtr<int32_t>(count);
    SwiperModelStatic::SetCachedCount(frameNode, convCount.value_or(DEFAULT_CACHED_COUNT));
    auto convIsShown = Converter::OptConvertPtr<bool>(isShown);
    if (!convIsShown) {
        SwiperModelStatic::SetCachedIsShown(frameNode, false);
        return;
    }
    SwiperModelStatic::SetCachedIsShown(frameNode, *convIsShown);
}
void SetDisplayCountImpl(Ark_NativePointer node,
                         const Opt_Union_I32_String_SwiperAutoFill* value,
                         const Opt_Boolean* swipeByGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto optDispCount = Converter::OptConvertPtr<DisplayCountVariantType>(value);

    if (auto bygroupOpt = Converter::OptConvertPtr<bool>(swipeByGroup); bygroupOpt) {
        SwiperModelStatic::SetSwipeByGroup(frameNode, *bygroupOpt);
    }

    if (!optDispCount) {
        SwiperModelStatic::SetDisplayCount(frameNode, DEFAULT_DISPLAY_COUNT);
        return;
    }

    if (auto countPtr = std::get_if<int32_t>(&(*optDispCount)); countPtr) {
        int32_t val = *countPtr;
        SwiperModelStatic::SetDisplayCount(frameNode, val);
    } else if (auto descPtr = std::get_if<std::string>(&(*optDispCount)); descPtr) {
        if (descPtr->compare("auto") == 0) {
            SwiperModelStatic::SetDisplayMode(frameNode, OHOS::Ace::SwiperDisplayMode::AUTO_LINEAR);
            SwiperModelStatic::ResetDisplayCount(frameNode);
            return;
        }
        int32_t val = StringUtils::StringToInt(*descPtr);
        SwiperModelStatic::SetDisplayCount(frameNode, val);
    } else if (auto autofillPtr = std::get_if<Ark_SwiperAutoFill>(&(*optDispCount)); autofillPtr) {
        if (auto minsizeOpt = Converter::OptConvert<Dimension>(autofillPtr->minSize); minsizeOpt) {
            SwiperModelStatic::SetMinSize(frameNode, *minsizeOpt);
        }
    } else {
        SwiperModelStatic::SetDisplayCount(frameNode, DEFAULT_DISPLAY_COUNT);
    }
}
void SetPrevMarginImpl(Ark_NativePointer node,
                       const Opt_Length* value,
                       const Opt_Boolean* ignoreBlank)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optMargin = Converter::OptConvert<Dimension>(*value);
    auto optIgnore = Converter::OptConvertPtr<bool>(ignoreBlank);
    SwiperModelStatic::SetPreviousMargin(frameNode, optMargin, optIgnore);
}
void SetNextMarginImpl(Ark_NativePointer node,
                       const Opt_Length* value,
                       const Opt_Boolean* ignoreBlank)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optMargin = Converter::OptConvertPtr<Dimension>(value);
    auto optIgnore = Converter::OptConvertPtr<bool>(ignoreBlank);
    SwiperModelStatic::SetNextMargin(frameNode, optMargin, optIgnore);
}
} // SwiperAttributeModifier
const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
{
    static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
        SwiperModifier::ConstructImpl,
        SwiperInterfaceModifier::SetSwiperOptionsImpl,
        SwiperAttributeModifier::SetIndexImpl,
        SwiperAttributeModifier::SetAutoPlay0Impl,
        SwiperAttributeModifier::SetIntervalImpl,
        SwiperAttributeModifier::SetIndicatorImpl,
        SwiperAttributeModifier::SetLoopImpl,
        SwiperAttributeModifier::SetDurationImpl,
        SwiperAttributeModifier::SetVerticalImpl,
        SwiperAttributeModifier::SetItemSpaceImpl,
        SwiperAttributeModifier::SetDisplayModeImpl,
        SwiperAttributeModifier::SetCachedCount0Impl,
        SwiperAttributeModifier::SetEffectModeImpl,
        SwiperAttributeModifier::SetDisableSwipeImpl,
        SwiperAttributeModifier::SetCurveImpl,
        SwiperAttributeModifier::SetOnChangeImpl,
        SwiperAttributeModifier::SetOnSelectedImpl,
        SwiperAttributeModifier::SetOnUnselectedImpl,
        SwiperAttributeModifier::SetOnAnimationStartImpl,
        SwiperAttributeModifier::SetOnAnimationEndImpl,
        SwiperAttributeModifier::SetOnGestureSwipeImpl,
        SwiperAttributeModifier::SetNestedScrollImpl,
        SwiperAttributeModifier::SetCustomContentTransitionImpl,
        SwiperAttributeModifier::SetOnContentDidScrollImpl,
        SwiperAttributeModifier::SetIndicatorInteractiveImpl,
        SwiperAttributeModifier::SetPageFlipModeImpl,
        SwiperAttributeModifier::SetOnContentWillScrollImpl,
        SwiperAttributeModifier::SetAutoPlay1Impl,
        SwiperAttributeModifier::SetDisplayArrowImpl,
        SwiperAttributeModifier::SetCachedCount1Impl,
        SwiperAttributeModifier::SetDisplayCountImpl,
        SwiperAttributeModifier::SetPrevMarginImpl,
        SwiperAttributeModifier::SetNextMarginImpl,
    };
    return &ArkUISwiperModifierImpl;
}

}
