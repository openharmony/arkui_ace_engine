/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/components/common/properties/color.h"
#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
// #include "arkoala_api_generated.h"
//#include "base/log/log_wrapper.h"

namespace {

template <typename T>
T toAceEnum(Ark_Int32 val, T min, T max)
{
    static const Ark_Int32 limitMin = static_cast<Ark_Int32>(min);
    static const Ark_Int32 limitMax = static_cast<Ark_Int32>(max);
    return (val >= limitMin && val <= limitMax) ? static_cast<T>(val) : min;
}

template <typename T>
T toAceEnum(Ark_Int32 val, T min, T max, T dflt)
{
    static const Ark_Int32 limitMin = static_cast<Ark_Int32>(min);
    static const Ark_Int32 limitMax = static_cast<Ark_Int32>(max);
    return (val >= limitMin && val <= limitMax) ? static_cast<T>(val) : dflt;
}

template <typename T>
Ark_Int32 trimToAceRange(Ark_Int32 val, T min, T max)
{
    static const Ark_Int32 limitMin = static_cast<Ark_Int32>(min);
    static const Ark_Int32 limitMax = static_cast<Ark_Int32>(max);
    return (val >= limitMin && val <= limitMax) ? val : limitMin;
}

std::optional<OHOS::Ace::Dimension> &checkDimValid(std::optional<OHOS::Ace::Dimension> &dim) {
    if (dim && dim->IsNegative()) {
        dim->SetValue(0);
        dim->SetUnit(OHOS::Ace::DimensionUnit::VP);
    }
    return dim;
}

constexpr int32_t DEFAULT_INTERVAL = static_cast<int32_t>(OHOS::Ace::DEFAULT_SWIPER_AUTOPLAY_INTERVAL);
constexpr int32_t DEFAULT_DURATION = static_cast<int32_t>(OHOS::Ace::DEFAULT_SWIPER_ANIMATION_DURATION);
constexpr int32_t DEFAULT_CACHED_COUNT = OHOS::Ace::DEFAULT_SWIPER_CACHED_SIZE;
constexpr int32_t DEFAULT_DISPLAY_COUNT = OHOS::Ace::DEFAULT_SWIPER_DISPLAY_COUNT;
} // namespace

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwiperInterfaceModifier {
void SetSwiperOptionsImpl(Ark_NativePointer node,
                          const Opt_SwiperController* controller)
{
    // TODO
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
    auto aceVal = Converter::Convert<int32_t>(*value);
    SwiperModelNG::SetAutoPlayInterval(frameNode, aceVal < 0 ? ::DEFAULT_INTERVAL: aceVal);
}

namespace {
bool checkDimCustom(std::optional<Dimension> &dim, const Dimension &defultVal) {
    bool isCustom = dim && dim->Unit() != DimensionUnit::PERCENT;
    if (isCustom && dim->IsNegative()) {
        *dim = defultVal;
    }
    return isCustom;
}
std::tuple<SwiperParameters, bool> ParseDotIndicator(const Ark_DotIndicator& src) {
    SwiperParameters p;
    bool isCustom;
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

    if (!p.dimStart) {
        p.dimStart = Dimension(0, DimensionUnit::VP);
    }
    if (!p.dimEnd) {
        p.dimEnd = Dimension(0, DimensionUnit::VP);
    }

    checkDimValid(p.dimLeft);
    checkDimValid(p.dimTop);
    checkDimValid(p.dimRight);
    checkDimValid(p.dimBottom);
    checkDimValid(p.dimStart);
    checkDimValid(p.dimEnd);

    Dimension defaultSize(0, DimensionUnit::VP);     // TODO
    isCustom = checkDimCustom(p.itemWidth, defaultSize);
    isCustom = checkDimCustom(p.itemHeight, defaultSize) || isCustom;
    isCustom = checkDimCustom(p.selectedItemWidth, defaultSize) || isCustom;
    isCustom = checkDimCustom(p.selectedItemHeight, defaultSize) || isCustom;

    if (p.maxDisplayCountVal && *p.maxDisplayCountVal < 0) {
        *p.maxDisplayCountVal = 0;
    }
    return {p, isCustom};
}

SwiperDigitalParameters ParseDigitIndicator(const Ark_DigitIndicator& src) {
    SwiperDigitalParameters p;
    // TODO
    return p;
}
} // namespace

void IndicatorImpl(Ark_NativePointer node,
                   const Type_SwiperAttribute_indicator_Arg0* value)
{
    constexpr int SELECTOR_DOT =  SELECTOR_ID_0;
    constexpr int SELECTOR_DIGIT = SELECTOR_ID_1;
    constexpr int SELECTOR_BOOL = SELECTOR_ID_2;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->selector == SELECTOR_DIGIT) {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, ParseDigitIndicator(value->value1));
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else {
        static Ark_DotIndicator defaultArkDot;
        const Ark_DotIndicator *arkDot = &defaultArkDot;
        if (value->selector == SELECTOR_DOT ) {
            arkDot = &(value->value0);
            SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        }
        auto [params, isCustomSize] = ParseDotIndicator(*arkDot);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, params);
        SwiperModelNG::SetIsIndicatorCustomSize(frameNode, isCustomSize);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }

    auto showIndicator = value->selector != SELECTOR_BOOL || Converter::Convert<bool>(value->value2);
    SwiperModelNG::SetShowIndicator(frameNode, showIndicator);
}
void DisplayArrowImpl(Ark_NativePointer node,
                      const Type_SwiperAttribute_displayArrow_Arg0* value,
                      const Opt_Boolean* isHoverShow)
{
    // TODO
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
    auto aceVal = Converter::Convert<int32_t>(*value);
    SwiperModelNG::SetDuration(frameNode, aceVal < 0 ? ::DEFAULT_DURATION : aceVal);
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
                   const Type_SwiperAttribute_itemSpace_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto aceOptVal = Converter::OptConvert<Dimension>(*value);
    CHECK_NULL_VOID(aceOptVal);
    SwiperModelNG::SetItemSpace(frameNode, *checkDimValid(aceOptVal));
}
void DisplayModeImpl(Ark_NativePointer node,
                     Ark_Int32 value)
{
    using namespace OHOS::Ace;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = toAceEnum<SwiperDisplayMode>(value, SwiperDisplayMode::STRETCH, SwiperDisplayMode::AUTO_LINEAR);
    SwiperModelNG::SetDisplayMode(frameNode, aceVal);
}
void CachedCountImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto aceVal = Converter::Convert<int32_t>(*value);
    SwiperModelNG::SetCachedCount(frameNode, aceVal < 0 ? ::DEFAULT_CACHED_COUNT : aceVal);
}
void DisplayCountImpl(Ark_NativePointer node,
                      const Type_SwiperAttribute_displayCount_Arg0* value,
                      const Opt_Boolean* swipeByGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    switch (value->selector) {
        case SELECTOR_ID_0: { // Ark_Number
            int32_t val = Converter::Convert<int32_t>(value->value0);
            SwiperModelNG::SetDisplayCount(frameNode, val < DEFAULT_DISPLAY_COUNT ? DEFAULT_DISPLAY_COUNT : val);
            break;
        }
        case SELECTOR_ID_1: { // Ark_String
            std::string aceVal(value->value1.chars);
            if (aceVal == "auto") {
                SwiperModelNG::SetDisplayMode(frameNode, OHOS::Ace::SwiperDisplayMode::AUTO_LINEAR);
                SwiperModelNG::ResetDisplayCount(frameNode);
                break;
            }
            int32_t val = StringUtils::StringToInt(aceVal);
            SwiperModelNG::SetDisplayCount(frameNode, val < DEFAULT_DISPLAY_COUNT ? DEFAULT_DISPLAY_COUNT : val);
            break;
        }
        case SELECTOR_ID_2: { // struct Ark_SwiperAutoFill
            if (auto aceOptVal = Converter::OptConvert<Dimension>(value->value2.minSize); aceOptVal) {
                SwiperModelNG::SetMinSize(frameNode, *checkDimValid(aceOptVal));
            }
            break;
        }
    }

    if (swipeByGroup) {
        auto aceOptVal = Converter::OptConvert<bool>(*swipeByGroup);
        SwiperModelNG::SetSwipeByGroup(frameNode, aceOptVal && *aceOptVal);
    }
}
void EffectModeImpl(Ark_NativePointer node,
                    Ark_Int32 value)
{
    using namespace OHOS::Ace;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = toAceEnum<EdgeEffect>(value, EdgeEffect::SPRING, EdgeEffect::NONE);
    SwiperModelNG::SetEdgeEffect(frameNode, aceVal);
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
               const Type_SwiperAttribute_curve_Arg0* value)
{
    // TODO
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    // TODO
}
void IndicatorStyleImpl(Ark_NativePointer node,
                        const Opt_IndicatorStyle* value)
{
    // TODO
}
void PrevMarginImpl(Ark_NativePointer node,
                    const Ark_Length* value,
                    const Opt_Boolean* ignoreBlank)
{
    // TODO
}
void NextMarginImpl(Ark_NativePointer node,
                    const Ark_Length* value,
                    const Opt_Boolean* ignoreBlank)
{
    // TODO
}
void OnAnimationStartImpl(Ark_NativePointer node,
                          Ark_Function event)
{
    // TODO
}
void OnAnimationEndImpl(Ark_NativePointer node,
                        Ark_Function event)
{
    // TODO
}
void OnGestureSwipeImpl(Ark_NativePointer node,
                        Ark_Function event)
{
    // TODO
}

void NestedScrollImpl(Ark_NativePointer node,
                      Ark_Int32 value)
{
    using namespace OHOS::Ace;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    value = ::trimToAceRange(value, NestedScrollMode::SELF_ONLY, NestedScrollMode::PARALLEL);
    SwiperModelNG::SetNestedScroll(frameNode, value);

}
void CustomContentTransitionImpl(Ark_NativePointer node,
                                 const Ark_SwiperContentAnimatedTransition* transition)
{
    // TODO
}
void OnContentDidScrollImpl(Ark_NativePointer node,
                            Ark_Function handler)
{
    // TODO
}
void IndicatorInteractiveImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceVal = Converter::Convert<bool>(value);
    SwiperModelNG::SetIndicatorInteractive(frameNode, aceVal);
}
} // SwiperAttributeModifier

const GENERATED_ArkUISwiperModifier* GetSwiperModifier()
{
    static const GENERATED_ArkUISwiperModifier ArkUISwiperModifierImpl {
        SwiperInterfaceModifier::SetSwiperOptionsImpl,
        SwiperAttributeModifier::IndexImpl,
        SwiperAttributeModifier::AutoPlayImpl,
        SwiperAttributeModifier::IntervalImpl,
        SwiperAttributeModifier::IndicatorImpl,
        SwiperAttributeModifier::DisplayArrowImpl,
        SwiperAttributeModifier::LoopImpl,
        SwiperAttributeModifier::DurationImpl,
        SwiperAttributeModifier::VerticalImpl,
        SwiperAttributeModifier::ItemSpaceImpl,
        SwiperAttributeModifier::DisplayModeImpl,
        SwiperAttributeModifier::CachedCountImpl,
        SwiperAttributeModifier::DisplayCountImpl,
        SwiperAttributeModifier::EffectModeImpl,
        SwiperAttributeModifier::DisableSwipeImpl,
        SwiperAttributeModifier::CurveImpl,
        SwiperAttributeModifier::OnChangeImpl,
        SwiperAttributeModifier::IndicatorStyleImpl,
        SwiperAttributeModifier::PrevMarginImpl,
        SwiperAttributeModifier::NextMarginImpl,
        SwiperAttributeModifier::OnAnimationStartImpl,
        SwiperAttributeModifier::OnAnimationEndImpl,
        SwiperAttributeModifier::OnGestureSwipeImpl,
        SwiperAttributeModifier::NestedScrollImpl,
        SwiperAttributeModifier::CustomContentTransitionImpl,
        SwiperAttributeModifier::OnContentDidScrollImpl,
        SwiperAttributeModifier::IndicatorInteractiveImpl,
    };
    return &ArkUISwiperModifierImpl;
}

}
