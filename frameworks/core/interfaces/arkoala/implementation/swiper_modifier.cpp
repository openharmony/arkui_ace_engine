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

std::optional<OHOS::Ace::Dimension> &checkDimValid(std::optional<OHOS::Ace::Dimension> &dim)
{
    if (!dim || dim->IsNegative()) {
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
bool checkDimCustom(std::optional<Dimension> &dim, const Dimension &defaultDim)
{
    bool isCustom = dim && dim->Unit() != DimensionUnit::PERCENT;
    if (!dim || (isCustom && dim->IsNegative())) {
        *dim = defaultDim;
    }
    return isCustom;
}
SwiperParameters ParseDotIndicator(const Ark_DotIndicator& src)
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

bool CheckSwiperParameters(SwiperParameters& p, const RefPtr<SwiperIndicatorTheme> &theme)
{
    checkDimValid(p.dimLeft);
    checkDimValid(p.dimTop);
    checkDimValid(p.dimRight);
    checkDimValid(p.dimBottom);
    checkDimValid(p.dimStart);
    checkDimValid(p.dimEnd);

    Dimension defaultSize(0, DimensionUnit::VP);
    if (theme) {
        defaultSize = theme->GetSize();

        // the next should be removed for support of the dynamic Theme changes
        if (!p.colorVal) {
            p.colorVal = theme->GetColor();
        }
        if (!p.selectedColorVal) {
            p.selectedColorVal = theme->GetSelectedColor();
        }
    }

    bool isCustom = checkDimCustom(p.itemWidth, defaultSize);
    isCustom = checkDimCustom(p.itemHeight, defaultSize) || isCustom;
    isCustom = checkDimCustom(p.selectedItemWidth, defaultSize) || isCustom;
    isCustom = checkDimCustom(p.selectedItemHeight, defaultSize) || isCustom;

    if (p.maxDisplayCountVal && *p.maxDisplayCountVal < 0) {
        *p.maxDisplayCountVal = 0;
    }
    return isCustom;
}

SwiperDigitalParameters ParseDigitIndicator(const Ark_DigitIndicator& src,
    const RefPtr<SwiperIndicatorTheme> &theme)
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

    checkDimValid(p.dimLeft);
    checkDimValid(p.dimTop);
    checkDimValid(p.dimRight);
    checkDimValid(p.dimBottom);
    checkDimValid(p.dimStart);
    checkDimValid(p.dimEnd);

    if (p.fontSize && p.fontSize->IsNegative()) {
        p.fontSize.reset();
    }
    if (p.selectedFontSize && p.selectedFontSize->IsNegative()) {
        p.selectedFontSize.reset();
    }
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
    RefPtr<SwiperIndicatorTheme> swiperIndicatorTheme = nullptr;
    if (auto pipelineContext = frameNode->GetContext(); pipelineContext) {
        swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    }
    auto showIndicator = true;
    if (value->selector == SELECTOR_DIGIT) {
        SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        SwiperModelNG::SetDigitIndicatorStyle(frameNode, ParseDigitIndicator(value->value1, swiperIndicatorTheme));
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DIGIT);
    } else {
        static Ark_DotIndicator defaultArkDot;
        const Ark_DotIndicator *arkDot = &defaultArkDot;
        if (value->selector == SELECTOR_DOT) {
            arkDot = &(value->value0);
            SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
        } else if (value->selector == SELECTOR_BOOL) {
            showIndicator = Converter::Convert<bool>(value->value2);
        }
        auto params = ParseDotIndicator(*arkDot);
        auto isCustomSize = CheckSwiperParameters(params, swiperIndicatorTheme);
        SwiperModelNG::SetDotIndicatorStyle(frameNode, params);
        SwiperModelNG::SetIsIndicatorCustomSize(frameNode, isCustomSize);
        SwiperModelNG::SetIndicatorType(frameNode, SwiperIndicatorType::DOT);
    }

    SwiperModelNG::SetShowIndicator(frameNode, showIndicator);
}

namespace {
SwiperArrowParameters ParseArrowStyle(const Ark_ArrowStyle& src,
    const RefPtr<SwiperIndicatorTheme> &theme)
{
    SwiperArrowParameters p;
    p.isShowBackground = Converter::OptConvert<bool>(src.showBackground);
    p.isSidebarMiddle = Converter::OptConvert<bool>(src.isSidebarMiddle);
    p.backgroundSize = Converter::OptConvert<Dimension>(src.backgroundSize);
    p.arrowSize = Converter::OptConvert<Dimension>(src.arrowSize);
    p.backgroundColor = Converter::OptConvert<Color>(src.backgroundColor);
    p.arrowColor = Converter::OptConvert<Color>(src.arrowColor);
    CHECK_NULL_RETURN(theme, p);

    if (!p.isShowBackground) {
        p.isShowBackground = theme->GetIsShowArrowBackground();
    }
    if (!p.isSidebarMiddle) {
        p.isSidebarMiddle = theme->GetIsSidebarMiddle();
    }
    bool isBigArrow = p.isSidebarMiddle.value();
    if (!p.backgroundSize || (p.backgroundSize->Unit() != DimensionUnit::PERCENT && p.backgroundSize->IsNegative())) {
        p.backgroundSize = isBigArrow ? theme->GetBigArrowBackgroundSize() : theme->GetSmallArrowBackgroundSize();
    }
    if (!p.arrowSize || (p.arrowSize->Unit() != DimensionUnit::PERCENT && p.arrowSize->IsNegative())) {
        p.arrowSize = isBigArrow ? theme->GetBigArrowSize() : theme->GetSmallArrowSize();
    }
    // the next should be removed for support of the dynamic Theme changes
    if (!p.backgroundColor) {
        p.backgroundColor =
            isBigArrow ? theme->GetBigArrowBackgroundColor() : theme->GetSmallArrowBackgroundColor();
    }
    if (!p.arrowColor) {
        p.arrowColor = isBigArrow ? theme->GetBigArrowColor() : theme->GetSmallArrowColor();
    }
    return p;
}
} // namespace
void DisplayArrowImpl(Ark_NativePointer node,
                      const Type_SwiperAttribute_displayArrow_Arg0* value,
                      const Opt_Boolean* isHoverShow)
{
    constexpr int SELECTOR_STYLE =  SELECTOR_ID_0;
    constexpr int SELECTOR_BOOL = SELECTOR_ID_1;
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    RefPtr<SwiperIndicatorTheme> swiperIndicatorTheme = nullptr;
    if (auto pipelineContext = frameNode->GetContext(); pipelineContext) {
        swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    }

    static Ark_ArrowStyle defaultArkArrow;
    const Ark_ArrowStyle *arkArrow = &defaultArkArrow;
    if (value->selector == SELECTOR_STYLE) {
        arkArrow = &(value->value0);
    } else {
        if (!swiperIndicatorTheme || !(value->selector == SELECTOR_BOOL) || !value->value1) {
            SwiperModelNG::SetDisplayArrow(frameNode, false);
            return;
        }
    }
    auto params = ParseArrowStyle(*arkArrow, swiperIndicatorTheme);
    SwiperModelNG::SetArrowStyle(frameNode, params);
    SwiperModelNG::SetDisplayArrow(frameNode, true);

    CHECK_NULL_VOID(isHoverShow);
    if (auto showHover = Converter::OptConvert<bool>(*isHoverShow); showHover) {
        SwiperModelNG::SetHoverShow(frameNode, showHover && *showHover);
    }
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SwiperParameters params;
    if (value && value->tag != ARK_TAG_UNDEFINED) {
        const Ark_IndicatorStyle &dotStyle = value->value;
        Ark_DotIndicator arkDot = {
            ._left = dotStyle.left,
            ._top = dotStyle.top,
            ._right = dotStyle.right,
            ._bottom = dotStyle.bottom,
            ._itemWidth = dotStyle.size,
            ._itemHeight = dotStyle.size,
            ._selectedItemWidth = dotStyle.size,
            ._selectedItemHeight = dotStyle.size,
            ._mask = dotStyle.mask,
            ._color = dotStyle.color,
            ._selectedColor = dotStyle.selectedColor,
        };
        params = ParseDotIndicator(arkDot);
    }
    RefPtr<SwiperIndicatorTheme> swiperIndicatorTheme = nullptr;
    if (auto pipelineContext = frameNode->GetContext(); pipelineContext) {
        swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    }
    CheckSwiperParameters(params, swiperIndicatorTheme);
    SwiperModelNG::SetIndicatorIsBoolean(frameNode, false);
    SwiperModelNG::SetDotIndicatorStyle(frameNode, params);
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
