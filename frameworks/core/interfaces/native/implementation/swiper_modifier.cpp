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
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/swiper_content_transition_proxy_peer.h"
#include "core/interfaces/native/implementation/swiper_controller_modifier_peer_impl.h"

namespace OHOS::Ace::NG {
using IndicatorVariantType = std::variant<SwiperParameters, SwiperDigitalParameters, bool>;
using ArrowStyleVariantType = std::variant<SwiperArrowParameters, bool>;
using DisplayCountVariantType = std::variant<int32_t, std::string, Ark_SwiperAutoFill>;
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
IndicatorVariantType Convert(const Ark_DotIndicator& src)
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
IndicatorVariantType Convert(const Ark_DigitIndicator& src)
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
IndicatorVariantType Convert(const Ark_Boolean& src)
{
    return Convert<bool>(src);
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
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG {
namespace {
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
    ResetIfInvalid(p.itemHeight);
    ResetIfInvalid(p.selectedItemWidth);
    ResetIfInvalid(p.selectedItemHeight);

    if (p.maxDisplayCountVal && *(p.maxDisplayCountVal) < 0) {
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
    ResetIfInvalid(p.selectedFontSize);
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwiperModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SwiperModelNG::CreateFrameNode(id);
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
    CHECK_NULL_VOID(controller);

    // obtain the internal SwiperController
    auto internalSwiperController = SwiperModelNG::GetSwiperController(frameNode);

    // obtain the external SwiperController peer
    auto abstPeerPtrOpt = Converter::OptConvert<Ark_SwiperController>(*controller);
    CHECK_NULL_VOID(abstPeerPtrOpt);
    auto peerImplPtr = reinterpret_cast<GeneratedModifier::SwiperControllerPeerImpl *>(*abstPeerPtrOpt);
    CHECK_NULL_VOID(peerImplPtr);

    // pass the internal controller to external management
    peerImplPtr->AddTargetController(internalSwiperController);
}
} // SwiperInterfaceModifier
namespace SwiperAttributeModifier {
void IndexImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto aceVal = Converter::Convert<int32_t>(*value);
    SwiperModelNG::SetIndex(frameNode, aceVal < 0 ? OHOS::Ace::DEFAULT_SWIPER_CURRENT_INDEX : aceVal);
}
void AutoPlayImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::Convert<bool>(value);
    SwiperModelNG::SetAutoPlay(frameNode, aceVal);
}
void IntervalImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SwiperModelNG::SetAutoPlayInterval(frameNode, Converter::Convert<int32_t>(*value));
}
void Indicator0Impl(Ark_NativePointer node,
                    const Ark_Union_DotIndicator_DigitIndicator_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optIndicator = Converter::OptConvert<IndicatorVariantType>(*value);
    CHECK_NULL_VOID(optIndicator);
    auto showIndicator = true;
    if (auto digitParamPtr = std::get_if<SwiperDigitalParameters>(&(*optIndicator)); digitParamPtr) {
        CheckSwiperDigitalParameters(*digitParamPtr);
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, *digitParamPtr);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else {
        if (auto dotParamPtr = std::get_if<SwiperParameters>(&(*optIndicator)); dotParamPtr) {
            auto isCustomSize = CheckSwiperParameters(*dotParamPtr);
            SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
            SwiperModelNG::SetDotIndicatorStyle(frameNode, *dotParamPtr);
            SwiperModelNG::SetIsIndicatorCustomSize(frameNode, isCustomSize);
        }
        if (auto booleanPtr = std::get_if<bool>(&(*optIndicator)); booleanPtr) {
            SwiperModelNG::SetIndicatorIsBoolean(frameNode, true);
            SwiperModelNG::SetDotIndicatorStyle(frameNode, SwiperParameters());
            SwiperModelNG::SetIsIndicatorCustomSize(frameNode, false);
            showIndicator = *booleanPtr;
        }
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }
    SwiperModelNG::SetShowIndicator(frameNode, showIndicator);
}
void Indicator1Impl(Ark_NativePointer node,
                    Ark_IndicatorComponentController value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SwiperModelNG::SetIndicator1(frameNode, convValue);
}
void LoopImpl(Ark_NativePointer node,
              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::Convert<bool>(value);
    SwiperModelNG::SetLoop(frameNode, aceVal);
}
void DurationImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SwiperModelNG::SetDuration(frameNode, Converter::Convert<int32_t>(*value));
}
void VerticalImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::Convert<bool>(value) ? Axis::VERTICAL : Axis::HORIZONTAL;
    SwiperModelNG::SetDirection(frameNode, aceVal);
}
void ItemSpaceImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto aceOptVal = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(aceOptVal);
    SwiperModelNG::SetItemSpace(frameNode, *aceOptVal);
}
void DisplayModeImpl(Ark_NativePointer node,
                     Ark_SwiperDisplayMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto dispModeOpt = Converter::OptConvert<SwiperDisplayMode>(value);
    CHECK_NULL_VOID(dispModeOpt);
    SwiperModelNG::SetDisplayMode(frameNode, *dispModeOpt);
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SwiperModelNG::SetCachedCount(frameNode, Converter::Convert<int32_t>(*value));
}
void EffectModeImpl(Ark_NativePointer node,
                    Ark_EdgeEffect value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto edgeEffOpt = Converter::OptConvert<EdgeEffect>(value);
    CHECK_NULL_VOID(edgeEffOpt);
    SwiperModelNG::SetEdgeEffect(frameNode, *edgeEffOpt);
}
void DisableSwipeImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::Convert<bool>(value);
    SwiperModelNG::SetDisableSwipe(frameNode, aceVal);
}
void CurveImpl(Ark_NativePointer node,
               const Ark_Union_Curve_String_ICurve* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    RefPtr<Curve> curve = nullptr;
    if (value) {
        if (auto curveOpt = Converter::OptConvert<RefPtr<Curve>>(*value); curveOpt) {
            curve = *curveOpt;
        }
    }
    if (!curve) {
        curve = Framework::CreateCurve(std::string(), true); // the default Framework Curve
    }
    SwiperModelNG::SetCurve(frameNode, curve);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)](int32_t index) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(index));
    };
    SwiperModelNG::SetOnChange(frameNode, onEvent);
}
void IndicatorStyleImpl(Ark_NativePointer node,
                        const Opt_IndicatorStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperParameters params;
    if (value) {
        if (auto paramsOpt = Converter::OptConvert<SwiperParameters>(*value); paramsOpt) {
            params = *paramsOpt;
            CheckSwiperParameters(params);
        }
    }
    SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
    SwiperModelNG::SetDotIndicatorStyle(frameNode, params);
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          const OnSwiperAnimationStartCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*value)](
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
    SwiperModelNG::SetOnAnimationStart(frameNode, onEvent);
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        const OnSwiperAnimationEndCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*value)](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.0f)),
        };
        arkCallback.Invoke(arkIndex, arkExtraInfo);
    };
    SwiperModelNG::SetOnAnimationEnd(frameNode, onEvent);
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        const OnSwiperGestureSwipeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*value)](int32_t index, const AnimationCallbackInfo& info) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        Ark_SwiperAnimationEvent arkExtraInfo = {
            .currentOffset = Converter::ArkValue<Ark_Number>(info.currentOffset.value_or(0.0f)),
            .targetOffset = Converter::ArkValue<Ark_Number>(info.targetOffset.value_or(0.0f)),
            .velocity = Converter::ArkValue<Ark_Number>(info.velocity.value_or(0.0f)),
        };
        arkCallback.Invoke(arkIndex, arkExtraInfo);
    };
    SwiperModelNG::SetOnGestureSwipe(frameNode, onEvent);
}
void NestedScrollImpl(Ark_NativePointer node,
                      Ark_SwiperNestedScrollMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto nestedModeOpt = Converter::OptConvert<NestedScrollMode>(value);
    CHECK_NULL_VOID(nestedModeOpt);
    SwiperModelNG::SetNestedScroll(frameNode, static_cast<int>(*nestedModeOpt));
}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const Ark_SwiperContentAnimatedTransition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SwiperContentAnimatedTransition transitionInfo;

    auto optTimeout = Converter::OptConvert<Ark_Int32>(value->timeout);
    if (optTimeout) {
        transitionInfo.timeout = *optTimeout;
    }

    transitionInfo.transition =
        [arkCallback = CallbackHelper(value->transition)](const RefPtr<SwiperContentTransitionProxy>& proxy) {
        auto peer = new SwiperContentTransitionProxyPeer();
        CHECK_NULL_VOID(peer);
        peer->SetHandler(proxy);
        arkCallback.Invoke(peer);
    };
    SwiperModelNG::SetCustomContentTransition(frameNode, transitionInfo);
}
void OnContentDidScrollImpl(Ark_NativePointer node,
                            const ContentDidScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEvent = [arkCallback = CallbackHelper(*value)](
        int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
        auto arkSelectedIndex = Converter::ArkValue<Ark_Number>(selectedIndex);
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkPosition = Converter::ArkValue<Ark_Number>(position);
        auto arkMainAxisLength = Converter::ArkValue<Ark_Number>(mainAxisLength);
        arkCallback.Invoke(arkSelectedIndex, arkIndex, arkPosition, arkMainAxisLength);
    };
    SwiperModelNG::SetOnContentDidScroll(frameNode, onEvent);
}
void IndicatorInteractiveImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::Convert<bool>(value);
    SwiperModelNG::SetIndicatorInteractive(frameNode, aceVal);
}
void DisplayArrowImpl(Ark_NativePointer node,
                      const Ark_Union_ArrowStyle_Boolean* value,
                      const Opt_Boolean* isHoverShow)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optArrow = Converter::OptConvert<ArrowStyleVariantType>(*value);
    CHECK_NULL_VOID(optArrow);

    if (isHoverShow) {
        if (auto show = Converter::OptConvert<bool>(*isHoverShow); show) {
            SwiperModelNG::SetHoverShow(frameNode, *show);
        }
    }

    bool *arrowBoolPtr = std::get_if<bool>(&(*optArrow));
    if (arrowBoolPtr && !*arrowBoolPtr) {
        SwiperModelNG::SetDisplayArrow(frameNode, false);
        return;
    }

    if (auto arrowStylePtr = std::get_if<SwiperArrowParameters>(&(*optArrow)); arrowStylePtr) {
        ResetIfInvalid(arrowStylePtr->backgroundSize);
        ResetIfInvalid(arrowStylePtr->arrowSize);
        SwiperModelNG::SetArrowStyle(frameNode, *arrowStylePtr);
    } else {
        SwiperModelNG::SetArrowStyle(frameNode, SwiperArrowParameters());
    }
    SwiperModelNG::SetDisplayArrow(frameNode, true);
}
void DisplayCountImpl(Ark_NativePointer node,
                      const Ark_Union_Number_String_SwiperAutoFill* value,
                      const Opt_Boolean* swipeByGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto optDispCount = Converter::OptConvert<DisplayCountVariantType>(*value);
    CHECK_NULL_VOID(optDispCount);

    if (swipeByGroup) {
        if (auto bygroupOpt = Converter::OptConvert<bool>(*swipeByGroup); bygroupOpt) {
            SwiperModelNG::SetSwipeByGroup(frameNode, *bygroupOpt);
        }
    }

    if (auto countPtr = std::get_if<int32_t>(&(*optDispCount)); countPtr) {
        int32_t val = *countPtr;
        SwiperModelNG::SetDisplayCount(frameNode, val);
    } else if (auto descPtr = std::get_if<std::string>(&(*optDispCount)); descPtr) {
        if (descPtr->compare("auto") == 0) {
            SwiperModelNG::SetDisplayMode(frameNode, OHOS::Ace::SwiperDisplayMode::AUTO_LINEAR);
            SwiperModelNG::ResetDisplayCount(frameNode);
            return;
        }
        int32_t val = StringUtils::StringToInt(*descPtr);
        SwiperModelNG::SetDisplayCount(frameNode, val);
    } else if (auto autofillPtr = std::get_if<Ark_SwiperAutoFill>(&(*optDispCount)); autofillPtr) {
        if (auto minsizeOpt = Converter::OptConvert<Dimension>(autofillPtr->minSize); minsizeOpt) {
            SwiperModelNG::SetMinSize(frameNode, *minsizeOpt);
        }
    } else {
        LOGW("SwiperAttributeModifier::DisplayCountImpl, unknown data, nothing do");
    }
}
void PrevMarginImpl(Ark_NativePointer node,
                    const Ark_Length* value,
                    const Opt_Boolean* ignoreBlank)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optMargin = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(optMargin);
    auto optIgnore = ignoreBlank ? Converter::OptConvert<bool>(*ignoreBlank) : std::nullopt;
    SwiperModelNG::SetPreviousMargin(frameNode, *optMargin, optIgnore);
}
void NextMarginImpl(Ark_NativePointer node,
                    const Ark_Length* value,
                    const Opt_Boolean* ignoreBlank)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optMargin = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(optMargin);
    auto optIgnore = ignoreBlank ? Converter::OptConvert<bool>(*ignoreBlank) : std::nullopt;
    SwiperModelNG::SetNextMargin(frameNode, *optMargin, optIgnore);
}
void _onChangeEvent_indexImpl(Ark_NativePointer node,
                              const Callback_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        CHECK_NULL_VOID(swiperInfo);
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(swiperInfo->GetIndex()));
    };
    SwiperModelNG::SetOnChangeEvent(frameNode, std::move(onEvent));
}
} // SwiperAttributeModifier
const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
{
    static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
        SwiperModifier::ConstructImpl,
        SwiperInterfaceModifier::SetSwiperOptionsImpl,
        SwiperAttributeModifier::IndexImpl,
        SwiperAttributeModifier::AutoPlayImpl,
        SwiperAttributeModifier::IntervalImpl,
        SwiperAttributeModifier::Indicator0Impl,
        SwiperAttributeModifier::Indicator1Impl,
        SwiperAttributeModifier::LoopImpl,
        SwiperAttributeModifier::DurationImpl,
        SwiperAttributeModifier::VerticalImpl,
        SwiperAttributeModifier::ItemSpaceImpl,
        SwiperAttributeModifier::DisplayModeImpl,
        SwiperAttributeModifier::CachedCountImpl,
        SwiperAttributeModifier::EffectModeImpl,
        SwiperAttributeModifier::DisableSwipeImpl,
        SwiperAttributeModifier::CurveImpl,
        SwiperAttributeModifier::OnChangeImpl,
        SwiperAttributeModifier::IndicatorStyleImpl,
        SwiperAttributeModifier::OnAnimationStartImpl,
        SwiperAttributeModifier::OnAnimationEndImpl,
        SwiperAttributeModifier::OnGestureSwipeImpl,
        SwiperAttributeModifier::NestedScrollImpl,
        SwiperAttributeModifier::CustomContentTransitionImpl,
        SwiperAttributeModifier::OnContentDidScrollImpl,
        SwiperAttributeModifier::IndicatorInteractiveImpl,
        SwiperAttributeModifier::DisplayArrowImpl,
        SwiperAttributeModifier::DisplayCountImpl,
        SwiperAttributeModifier::PrevMarginImpl,
        SwiperAttributeModifier::NextMarginImpl,
        SwiperAttributeModifier::_onChangeEvent_indexImpl,
    };
    return &ArkUISwiperModifierImpl;
}

}
