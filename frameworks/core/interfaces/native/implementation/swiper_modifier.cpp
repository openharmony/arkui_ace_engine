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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/swiper_content_transition_proxy_peer.h"
#include "core/interfaces/native/implementation/swiper_controller_modifier_peer_impl.h"
#include "core/interfaces/native/implementation/indicator_component_controller_peer.h"

namespace OHOS::Ace::NG {
using ArrowStyleVariantType = std::variant<SwiperArrowParameters, bool>;
using DisplayCountVariantType = std::variant<int32_t, std::string, Ark_SwiperAutoFill>;
const static int32_t DEFAULT_DURATION = 400;
const static int32_t DEFAULT_DISPLAY_COUNT = 1;
const static int32_t DEFAULT_CACHED_COUNT = 1;
}

namespace OHOS::Ace::NG::Converter {
template<>
SwiperParameters Convert(const Ark_IndicatorStyle& src)
{
    SwiperParameters p;
    p.dimLeft = Converter::OptConvert<Dimension>(src.left);
    p.dimTop = Converter::OptConvert<Dimension>(src.top);
    p.dimRight = Converter::OptConvert<Dimension>(src.right);
    p.dimBottom = Converter::OptConvert<Dimension>(src.bottom);

    p.itemWidth = p.itemHeight = p.selectedItemWidth = p.selectedItemHeight =
        Converter::OptConvert<Dimension>(src.size);

    p.maskValue = Converter::OptConvert<bool>(src.mask);
    p.colorVal = Converter::OptConvert<Color>(src.color);
    p.selectedColorVal = Converter::OptConvert<Color>(src.selectedColor);
    return p;
}

template<>
SwiperParameters Convert(const Ark_DotIndicator& src)
{
    SwiperParameters p;
    p.dimLeft = Converter::OptConvert<Dimension>(src._left);
    p.dimTop = Converter::OptConvert<Dimension>(src._top);
    p.dimRight = Converter::OptConvert<Dimension>(src._right);
    p.dimBottom = Converter::OptConvert<Dimension>(src._bottom);

    p.dimStart = Converter::OptConvert<Dimension>(src._start);
    p.dimEnd = Converter::OptConvert<Dimension>(src._end);

    p.itemWidth = Converter::OptConvert<Dimension>(src._itemWidth);
    p.itemHeight = Converter::OptConvert<Dimension>(src._itemHeight);
    p.selectedItemWidth = Converter::OptConvert<Dimension>(src._selectedItemWidth);
    p.selectedItemHeight = Converter::OptConvert<Dimension>(src._selectedItemHeight);

    p.maskValue = Converter::OptConvert<bool>(src._mask);
    p.colorVal = Converter::OptConvert<Color>(src._color);
    p.selectedColorVal = Converter::OptConvert<Color>(src._selectedColor);
    p.maxDisplayCountVal = Converter::OptConvert<int32_t>(src._maxDisplayCount);
    return p;
}

template<>
SwiperDigitalParameters Convert(const Ark_DigitIndicator& src)
{
    SwiperDigitalParameters p;
    p.dimLeft = Converter::OptConvert<Dimension>(src._left);
    p.dimTop = Converter::OptConvert<Dimension>(src._top);
    p.dimRight = Converter::OptConvert<Dimension>(src._right);
    p.dimBottom = Converter::OptConvert<Dimension>(src._bottom);

    p.dimStart = Converter::OptConvert<Dimension>(src._start);
    p.dimEnd = Converter::OptConvert<Dimension>(src._end);

    if (auto font = Converter::OptConvert<Converter::FontMetaData>(src._digitFont); font) {
        std::tie(p.fontSize, p.fontWeight) = *font;
    }
    if (auto font = Converter::OptConvert<Converter::FontMetaData>(src._selectedDigitFont); font) {
        std::tie(p.selectedFontSize, p.selectedFontWeight) = *font;
    }

    p.fontColor = Converter::OptConvert<Color>(src._fontColor);
    p.selectedFontColor = Converter::OptConvert<Color>(src._selectedFontColor);
    return p;
}

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
DisplayCountVariantType Convert(const Ark_Number& src)
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
    bool newSdk = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN);
    switch (src) {
        case SELECTOR_ID_0: dst = SwiperDisplayMode::STRETCH; break;
        case SELECTOR_ID_1: dst = SwiperDisplayMode::AUTO_LINEAR; break;
        case SELECTOR_ID_2: newSdk ? dst = SwiperDisplayMode::STRETCH : dst = std::nullopt; break;
        case SELECTOR_ID_3: newSdk ? dst = SwiperDisplayMode::AUTO_LINEAR : dst = std::nullopt; break;
        default: LOGE("Unexpected enum value in Ark_SwiperDisplayMode: %{public}d", src);
    }
}

template<>
inline void AssignCast(std::optional<NestedScrollMode>& dst, const Ark_SwiperNestedScrollMode& src)
{
    switch (src) {
        case static_cast<Ark_SwiperNestedScrollMode>(NestedScrollMode::SELF_ONLY):
            dst = NestedScrollMode::SELF_ONLY;
            break;
        case static_cast<Ark_SwiperNestedScrollMode>(NestedScrollMode::SELF_FIRST):
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
    dst.currentIndex = Converter::ArkValue<Ark_Number>(src.currentIndex, ctx);
    dst.comingIndex = Converter::ArkValue<Ark_Number>(src.comingIndex, ctx);
    dst.offset = Converter::ArkValue<Ark_Number>(src.offset, ctx);
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
    p.itemWidth = p.itemWidth ? std::max(6.0_vp, *p.itemWidth) : 6.0_vp;
    ResetIfInvalid(p.itemHeight);
    p.itemHeight = p.itemHeight ? std::max(6.0_vp, *p.itemHeight) : 6.0_vp;
    ResetIfInvalid(p.selectedItemWidth);
    p.selectedItemWidth = p.selectedItemWidth ? std::max(6.0_vp, *p.selectedItemWidth) : 6.0_vp;
    ResetIfInvalid(p.selectedItemHeight);
    p.selectedItemHeight = p.selectedItemHeight ? std::max(6.0_vp, *p.itemWidth) : 6.0_vp;

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
    p.fontSize = p.fontSize ? std::max(14.0_vp, *p.fontSize) : 14.0_vp;
    ResetIfInvalid(p.selectedFontSize);
    p.selectedFontSize = p.selectedFontSize ? std::max(14.0_vp, *p.selectedFontSize) : 14.0_vp;
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
    return {};
}
} // SwiperModifier
namespace SwiperInterfaceModifier {
void SetSwiperOptionsImpl(Ark_NativePointer node,
                          const Opt_SwiperController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = controller ? Converter::OptConvert<type>(*controller) : std::nullopt;
    //SwiperModelNG::SetSetSwiperOptions(frameNode, convValue);
}
} // SwiperInterfaceModifier
namespace SwiperAttributeModifier {
void SetIndexImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        SwiperModelStatic::SetIndex(frameNode, OHOS::Ace::DEFAULT_SWIPER_CURRENT_INDEX);
        return;
    }
    SwiperModelStatic::SetIndex(frameNode, *convValue < 0 ? OHOS::Ace::DEFAULT_SWIPER_CURRENT_INDEX : *convValue);
}
void AutoPlay0Impl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        SwiperModelStatic::SetAutoPlay(frameNode, false);
        return;
    }
    SwiperModelStatic::SetAutoPlay(frameNode, *convValue);
}
void AutoPlay1Impl(Ark_NativePointer node,
                   const Opt_Boolean* autoPlay,
                   const Opt_AutoPlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto autoPlayConv = Converter::OptConvert<bool>(*autoPlay);
    if (!autoPlayConv) {
        SwiperModelStatic::SetAutoPlay(frameNode, false);
        return;
    }
    auto optionsConv = Converter::OptConvert<SwiperAutoPlayOptions>(*options);
    if (!optionsConv) {
        SwiperModelStatic::SetAutoPlayOptions(frameNode, SwiperAutoPlayOptions());
        return;
    }
    SwiperModelStatic::SetAutoPlay(frameNode, *autoPlayConv);
    SwiperModelStatic::SetAutoPlayOptions(frameNode, *optionsConv);
}
void SetIntervalImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        SwiperModelStatic::SetAutoPlayInterval(frameNode, DEFAULT_INTERVAL_VALUE);
        return;
    }
    auto convValue = Converter::Convert<int32_t>(value->value);
    if (convValue < INVALID_VALUE) {
        SwiperModelStatic::SetAutoPlayInterval(frameNode, DEFAULT_INTERVAL_VALUE);
        return;
    }
    SwiperModelStatic::SetAutoPlayInterval(frameNode, convValue);
}
namespace {
void SetIndicator(FrameNode* frameNode, const Ark_DigitIndicator& src)
{
    auto digitParam = Converter::Convert<SwiperDigitalParameters>(src);
    CheckSwiperDigitalParameters(digitParam);
    SwiperModelStatic::SetIndicatorIsBoolean(frameNode, false);
    SwiperModelStatic::SetDigitIndicatorStyle(frameNode, digitParam);
    SwiperModelStatic::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    SwiperModelStatic::SetShowIndicator(frameNode, true);
}
void SetIndicatorImpl(Ark_NativePointer node,
                      const Opt_Union_IndicatorComponentController_DotIndicator_DigitIndicator_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetIndicator(frameNode, convValue);
}
void SetLoopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        SwiperModelStatic::SetLoop(frameNode, true);
        return;
    }
    SwiperModelStatic::SetLoop(frameNode, *convValue);
}
void SetDurationImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        SwiperModelStatic::SetDuration(frameNode, DEFAULT_DURATION);
        return;
    }
    SwiperModelStatic::SetDuration(frameNode, *convValue);
}
void SetVerticalImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::OptConvert<bool>(*value);
    if (!aceVal) {
        SwiperModelStatic::SetDirection(frameNode, Axis::HORIZONTAL);
        return;
    }
    SwiperModelStatic::SetDirection(frameNode, *aceVal ? Axis::VERTICAL : Axis::HORIZONTAL);
}
void SetItemSpaceImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceOptVal = Converter::OptConvert<Dimension>(*value);
    if (!aceOptVal) {
        CalcDimension value;
        value.SetValue(0.0);
        SwiperModelStatic::SetItemSpace(frameNode, value);
        return;
    }
    SwiperModelStatic::SetItemSpace(frameNode, *aceOptVal);
}
void SetDisplayModeImpl(Ark_NativePointer node,
                        const Opt_SwiperDisplayMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto dispModeOpt = Converter::OptConvert<SwiperDisplayMode>(*value);
    if (!dispModeOpt) {
        SwiperModelStatic::SetDisplayMode(frameNode, SwiperDisplayMode::STRETCH);
        return;
    }
    SwiperModelStatic::SetDisplayMode(frameNode, *dispModeOpt);
}
void SetCachedCount0Impl(Ark_NativePointer node,
                         const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue) {
        SwiperModelStatic::SetCachedCount(frameNode, DEFAULT_CACHED_COUNT);
        return;
    }
    SwiperModelStatic::SetCachedCount(frameNode, *convValue);
}
void CachedCount1Impl(Ark_NativePointer node,
                      const Opt_Number* count,
                      const Opt_Boolean* isShown)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convCount = Converter::OptConvert<int32_t>(*count);
    if (!convCount) {
        SwiperModelStatic::SetCachedCount(frameNode, DEFAULT_CACHED_COUNT);
        return;
    }
    SwiperModelStatic::SetCachedCount(frameNode, *convCount);
    auto convIsShown = Converter::OptConvert<bool>(*isShown);
    if (!convIsShown) {
        SwiperModelStatic::SetCachedIsShown(frameNode, false);
        return;
    }
    SwiperModelStatic::SetCachedIsShown(frameNode, *convIsShown);
}
void SetEffectModeImpl(Ark_NativePointer node,
                       const Opt_EdgeEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto edgeEffOpt = Converter::OptConvert<EdgeEffect>(*value);
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
    auto convValue = Converter::OptConvert<bool>(*value);
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
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetCurve(frameNode, convValue);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SwiperModelStatic::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](int32_t index) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(index));
    };
    SwiperModelStatic::SetOnChange(frameNode, onEvent);
}
void SetOnSelectedImpl(Ark_NativePointer node,
                       const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnSelected(frameNode, convValue);
}
void SetOnUnselectedImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnUnselected(frameNode, convValue);
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
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkTargetIndex = Converter::ArkValue<Ark_Number>(targetIndex);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.0f)),
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
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.0f)),
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
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.0f)),
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
    auto nestedModeOpt = Converter::OptConvert<NestedScrollMode>(*value);
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
        auto arkSelectedIndex = Converter::ArkValue<Ark_Number>(selectedIndex);
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkPosition = Converter::ArkValue<Ark_Number>(position);
        auto arkMainAxisLength = Converter::ArkValue<Ark_Number>(mainAxisLength);
        arkCallback.Invoke(arkSelectedIndex, arkIndex, arkPosition, arkMainAxisLength);
    };
    SwiperModelStatic::SetOnContentDidScroll(frameNode, onEvent);
}
void SetIndicatorInteractiveImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
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
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetPageFlipMode(frameNode, convValue);
}
void SetOnContentWillScrollImpl(Ark_NativePointer node,
                                const Opt_ContentWillScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SwiperModelNG::SetSetOnContentWillScroll(frameNode, convValue);
}
void SetAutoPlayImpl(Ark_NativePointer node,
                     const Opt_Boolean* autoPlay,
                     const Opt_AutoPlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(autoPlay);
    //auto convValue = Converter::OptConvert<type>(autoPlay); // for enums
    //SwiperModelNG::SetSetAutoPlay(frameNode, convValue);
}
void SetDisplayArrowImpl(Ark_NativePointer node,
                         const Opt_Union_ArrowStyle_Boolean* value,
                         const Opt_Boolean* isHoverShow)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SwiperModelNG::SetSetDisplayArrow(frameNode, convValue);
}
void SetCachedCount1Impl(Ark_NativePointer node,
                         const Opt_Number* count,
                         const Opt_Boolean* isShown)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(count);
    //auto convValue = Converter::OptConvert<type>(count); // for enums
    //SwiperModelNG::SetSetCachedCount1(frameNode, convValue);
}
void SetDisplayCountImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String_SwiperAutoFill* value,
                         const Opt_Boolean* swipeByGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto optDispCount = Converter::OptConvert<DisplayCountVariantType>(*value);
    CHECK_NULL_VOID(optDispCount);

    if (swipeByGroup) {
        if (auto bygroupOpt = Converter::OptConvert<bool>(*swipeByGroup); bygroupOpt) {
            SwiperModelStatic::SetSwipeByGroup(frameNode, *bygroupOpt);
        }
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
    CHECK_NULL_VOID(value);
    auto optMargin = Converter::OptConvert<Dimension>(*value);
    CalcDimension margin;
    if (!optMargin) {
        margin.SetValue(0.0);
    }
    bool ignoreResult = false;
    if (ignoreBlank->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        SwiperModelStatic::SetPreviousMargin(frameNode, margin, false);
        return;
    }
    ignoreResult = Converter::Convert<bool>(ignoreBlank->value);
    SwiperModelStatic::SetPreviousMargin(frameNode, margin, ignoreResult);
}
void SetNextMarginImpl(Ark_NativePointer node,
                       const Opt_Length* value,
                       const Opt_Boolean* ignoreBlank)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optMargin = Converter::OptConvert<Dimension>(*value);
    CalcDimension margin;
    if (!optMargin) {
        margin.SetValue(0.0);
    }
    bool ignoreResult = false;
    if (ignoreBlank->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        SwiperModelStatic::SetPreviousMargin(frameNode, margin, false);
        return;
    }
    SwiperModelStatic::SetNextMargin(frameNode, margin, ignoreResult);
}
void _onChangeEvent_indexImpl(Ark_NativePointer node,
                              const Callback_Opt_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        CHECK_NULL_VOID(swiperInfo);
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Opt_Number>(swiperInfo->GetIndex()));
    };
    SwiperModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
}
} // SwiperAttributeModifier
const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
{
    static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
        SwiperModifier::ConstructImpl,
        SwiperInterfaceModifier::SetSwiperOptionsImpl,
        SwiperAttributeModifier::SetIndexImpl,
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
        SwiperAttributeModifier::SetAutoPlayImpl,
        SwiperAttributeModifier::SetDisplayArrowImpl,
        SwiperAttributeModifier::SetCachedCount1Impl,
        SwiperAttributeModifier::SetDisplayCountImpl,
        SwiperAttributeModifier::SetPrevMarginImpl,
        SwiperAttributeModifier::SetNextMarginImpl,
    };
    return &ArkUISwiperModifierImpl;
}

}
