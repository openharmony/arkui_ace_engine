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

#include <algorithm>
#include <variant>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_node.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "base/log/log_wrapper.h"

namespace {
constexpr double FULL_DIMENSION = 100.0;
constexpr double HALF_DIMENSION = 50.0;
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
}

namespace OHOS::Ace::NG {
struct EdgesParamOptions {
    EdgesParam value;
    bool isLocalized;
};

struct ScaleOpt {
    std::optional<float> x;
    std::optional<float> y;
    std::optional<float> z;
    std::optional<Dimension> centerX;
    std::optional<Dimension> centerY;
};

struct TranslateOpt {
    std::optional<Dimension> x;
    std::optional<Dimension> y;
    std::optional<Dimension> z;
};

using ColorOrStrategy = std::variant<std::monostate, std::optional<Color>, std::optional<ForegroundColorStrategy>>;
using OffsetOrEdgesParam = std::variant<
    std::monostate,
    std::optional<OffsetT<Dimension>>,
    std::optional<EdgesParamOptions>
>;
using BackgroundImagePositionType = std::variant<
    Ark_Position,
    Ark_Alignment
>;
using ClipType = std::variant<
    Ark_Boolean,
    Ark_CircleAttribute,
    Ark_EllipseAttribute,
    Ark_PathAttribute,
    Ark_RectAttribute
>;

namespace Converter {
template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Color& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Resource& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_String& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_Number& src)
{
    dst = OptConvert<Color>(src);
}

template<>
void AssignCast(std::optional<ColorOrStrategy>& dst, const Ark_ColoringStrategy& src)
{
    dst = OptConvert<ForegroundColorStrategy>(src);
}

template<>
void AssignCast(std::optional<BackgroundImageSizeType>& dst, const Ark_ImageSize& src)
{
    switch (src) {
        case ARK_IMAGE_SIZE_AUTO: dst = BackgroundImageSizeType::AUTO; break;
        case ARK_IMAGE_SIZE_COVER: dst = BackgroundImageSizeType::COVER; break;
        case ARK_IMAGE_SIZE_CONTAIN: dst = BackgroundImageSizeType::CONTAIN; break;
        case ARK_IMAGE_SIZE_FILL: dst = BackgroundImageSizeType::FILL; break;
        default: LOGE("Unexpected enum value in Ark_ImageSize: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<std::pair<double, double>>& dst, const Ark_Alignment& src)
{
    switch (src) {
        case ARK_ALIGNMENT_TOP_START: dst = { 0.0, 0.0 }; break;
        case ARK_ALIGNMENT_TOP: dst = { HALF_DIMENSION, 0.0 }; break;
        case ARK_ALIGNMENT_TOP_END: dst = { FULL_DIMENSION, 0.0 }; break;
        case ARK_ALIGNMENT_START: dst = { 0.0, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_CENTER: dst = { HALF_DIMENSION, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_END: dst = { FULL_DIMENSION, HALF_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM_START: dst = { 0.0, FULL_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM: dst = { HALF_DIMENSION, FULL_DIMENSION }; break;
        case ARK_ALIGNMENT_BOTTOM_END: dst = { FULL_DIMENSION, FULL_DIMENSION }; break;
        default: LOGE("Unexpected enum value in Ark_Alignment: %{public}d", src);
    }
}

template<>
MotionPathOption Convert(const Ark_MotionPathOptions& src)
{
    MotionPathOption p;
    p.SetPath(Converter::Convert<std::string>(src.path));
    if (auto opt = Converter::OptConvert<float>(src.from); opt) {
        p.SetBegin(*opt);
    }
    if (auto opt = Converter::OptConvert<float>(src.to); opt) {
        p.SetEnd(*opt);
    }
    if (auto opt = Converter::OptConvert<bool>(src.rotatable); opt) {
        p.SetRotate(*opt);
    }
    return p;
}

template<>
OHOS::Ace::SharedTransitionOption Convert(const Ark_sharedTransitionOptions& src)
{
    OHOS::Ace::SharedTransitionOption o = { .duration = INT_MIN };
    if (auto opt = Converter::OptConvert<RefPtr<Curve>>(src.curve); opt) {
        o.curve = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.duration); opt) {
        o.duration = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.delay); opt) {
        o.delay = *opt;
    }
    if (auto opt = Converter::OptConvert<MotionPathOption>(src.motionPath); opt) {
        o.motionPathOption = *opt;
    }
    if (auto opt = Converter::OptConvert<int32_t>(src.zIndex); opt) {
        o.zIndex = *opt;
    }
    if (auto opt = Converter::OptConvert<SharedTransitionEffectType>(src.type); opt) {
        o.type = *opt;
    }
    return o;
}

template<>
OffsetOrEdgesParam Convert(const Ark_Position& src)
{
    OffsetT<Dimension> offset;
    std::optional<Dimension> x = Converter::OptConvert<Dimension>(src.x);
    if (x) {
        offset.SetX(x.value());
    }
    std::optional<Dimension> y = Converter::OptConvert<Dimension>(src.y);
    if (y) {
        offset.SetY(y.value());
    }
    return offset;
}

template<>
OffsetOrEdgesParam Convert(const Ark_Edges& src)
{
    EdgesParamOptions edgesParamOptions;
    edgesParamOptions.value = Converter::Convert<EdgesParam>(src);
    edgesParamOptions.isLocalized = false;
    return edgesParamOptions;
}

template<>
OffsetOrEdgesParam Convert(const Ark_LocalizedEdges& src)
{
    // Ark_LocalizedEdges conversion need to be supported
    EdgesParamOptions edgesParamOptions;
    edgesParamOptions.isLocalized = false;
    return edgesParamOptions;
}

template<>
GradientColor Convert(const Tuple_Ark_ResourceColor_Number& src)
{
    GradientColor gradientColor;
    gradientColor.SetHasValue(false);

    // color
    std::optional<Color> colorOpt = Converter::OptConvert<Color>(src.value0);
    if (colorOpt) {
        gradientColor.SetColor(colorOpt.value());
        gradientColor.SetHasValue(true);
    }

    // stop value
    float value = Converter::Convert<float>(src.value1);
    value = std::clamp(value, 0.0f, 1.0f);
    //  [0, 1] -> [0, 100.0];
    gradientColor.SetDimension(CalcDimension(value * 100.0, DimensionUnit::PERCENT));

    return gradientColor;
}

template<>
Gradient Convert(const Type_CommonMethod_radialGradient_Arg0& src)
{
    NG::Gradient gradient;
    gradient.CreateGradientWithType(NG::GradientType::RADIAL);

    // center
    gradient.GetRadialGradient()->radialCenterX = Converter::Convert<Dimension>(src.center.value0);
    gradient.GetRadialGradient()->radialCenterY = Converter::Convert<Dimension>(src.center.value1);

    // radius
    std::optional<Dimension> radiusOpt = Converter::OptConvert<Dimension>(src.radius);
    if (radiusOpt) {
        // radius should be positive [0, +∞)
        Dimension radius = radiusOpt.value().IsNonPositive() ? Dimension(0, DimensionUnit::VP) : radiusOpt.value();
        gradient.GetRadialGradient()->radialVerticalSize = radius;
        gradient.GetRadialGradient()->radialHorizontalSize = radius;
    }

    // repeating
    std::optional<bool> repeating = Converter::OptConvert<bool>(src.repeating);
    if (repeating) {
        gradient.SetRepeat(repeating.value());
    }

    // color stops
    std::vector<GradientColor> colorStops = Converter::Convert<std::vector<GradientColor>>(src.colors);
    for (GradientColor gradientColor : colorStops) {
        gradient.AddColor(gradientColor);
    }

    return gradient;
}

template<>
BackgroundImageSize Convert(const Ark_SizeOptions& src)
{
    BackgroundImageSize imageSize;
    CalcDimension width;
    CalcDimension height;
    auto widthOpt = Converter::OptConvert<Dimension>(src.width);
    if (widthOpt) {
        width = widthOpt.value();
    }
    auto heightOpt = Converter::OptConvert<Dimension>(src.height);
    if (heightOpt) {
        height = heightOpt.value();
    }
    double valueWidth = width.ConvertToPx();
    double valueHeight = height.ConvertToPx();
    BackgroundImageSizeType typeWidth = BackgroundImageSizeType::LENGTH;
    BackgroundImageSizeType typeHeight = BackgroundImageSizeType::LENGTH;
    if (width.Unit() == DimensionUnit::PERCENT) {
        typeWidth = BackgroundImageSizeType::PERCENT;
        valueWidth = width.Value();
    }
    if (height.Unit() == DimensionUnit::PERCENT) {
        typeHeight = BackgroundImageSizeType::PERCENT;
        valueHeight = height.Value();
    }
    imageSize.SetSizeTypeX(typeWidth);
    imageSize.SetSizeValueX(valueWidth);
    imageSize.SetSizeTypeY(typeHeight);
    imageSize.SetSizeValueY(valueHeight);
    return imageSize;
}

template<>
BackgroundImageSize Convert(const Ark_ImageSize& src)
{
    auto sizeType = OptConvert<BackgroundImageSizeType>(src).value_or(BackgroundImageSizeType::AUTO);
    BackgroundImageSize imageSize;
    imageSize.SetSizeTypeX(sizeType);
    imageSize.SetSizeTypeY(sizeType);
    return imageSize;
}

template<>
std::pair<std::optional<Dimension>, std::optional<Dimension>> Convert(const Ark_Position& src)
{
    auto x = OptConvert<Dimension>(src.x);
    auto y = OptConvert<Dimension>(src.y);
    return {x, y};
}

template<>
ScaleOpt Convert(const Ark_ScaleOptions& src)
{
    ScaleOpt scaleOptions;
    scaleOptions.x = OptConvert<float>(src.x);
    scaleOptions.y = OptConvert<float>(src.y);
    scaleOptions.z = OptConvert<float>(src.z);
    scaleOptions.centerX = OptConvert<Dimension>(src.centerX);
    scaleOptions.centerY = OptConvert<Dimension>(src.centerY);
    return scaleOptions;
}

template<>
TranslateOpt Convert(const Ark_TranslateOptions& src)
{
    TranslateOpt translateOptions;
    translateOptions.x = OptConvert<Dimension>(src.x);
    translateOptions.y = OptConvert<Dimension>(src.y);
    translateOptions.z = OptConvert<Dimension>(src.z);
    return translateOptions;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr int32_t CASE_0 = 0;
constexpr int32_t CASE_1 = 1;
constexpr int32_t CASE_2 = 2;

namespace CommonMethodModifier {
void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::Convert<CalcLength>(*value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            return;
        }
        CounterModelNG::SetWidth(frameNode, result);
    } else {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, true);
            return;
        }
        ViewAbstract::SetWidth(frameNode, result);
    }
}
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto result = Converter::Convert<CalcLength>(*value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            return;
        }
        CounterModelNG::SetHeight(frameNode, result);
    } else {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, false);
            return;
        }
        ViewAbstract::SetHeight(frameNode, result);
    }
}
void DrawModifierImpl(Ark_NativePointer node,
                      const Type_CommonMethod_drawModifier_Arg0* modifier)
{
}
void CustomPropertyImpl(Ark_NativePointer node,
                        const Ark_String* name,
                        const Opt_Object* value)
{
}
void ExpandSafeAreaImpl(Ark_NativePointer node,
                        const Opt_Array_SafeAreaType* types,
                        const Opt_Array_SafeAreaEdge* edges)
{
}
void ResponseRegionImpl(Ark_NativePointer node,
                        const Type_CommonMethod_responseRegion_Arg0* value)
{
}
void MouseResponseRegionImpl(Ark_NativePointer node,
                             const Type_CommonMethod_mouseResponseRegion_Arg0* value)
{
}
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value)
{
    CHECK_NULL_VOID(value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto width = Converter::OptConvert<Ark_Length>(value->width);
    if (width) {
        WidthImpl(node, &width.value());
    }
    auto height = Converter::OptConvert<Ark_Length>(value->height);
    if (height) {
        HeightImpl(node, &height.value());
    }
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto minWidth = Converter::OptConvert<CalcLength>(value->minWidth);
    if (minWidth) {
        ViewAbstract::SetMinWidth(frameNode, minWidth.value());
    }
    auto minHeight = Converter::OptConvert<CalcLength>(value->minHeight);
    if (minHeight) {
        ViewAbstract::SetMinHeight(frameNode, minHeight.value());
    }
    auto maxWidth = Converter::OptConvert<CalcLength>(value->maxWidth);
    if (maxWidth) {
        ViewAbstract::SetMaxWidth(frameNode, maxWidth.value());
    }
    auto maxHeight = Converter::OptConvert<CalcLength>(value->maxHeight);
    if (maxHeight) {
        ViewAbstract::SetMaxHeight(frameNode, maxHeight.value());
    }
}
void TouchableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetTouchable(frameNode, static_cast<bool>(value));
}
void HitTestBehaviorImpl(Ark_NativePointer node,
                         enum Ark_HitTestMode value)
{
}
void OnChildTouchTestImpl(Ark_NativePointer node,
                          Ark_Function event)
{
}
void LayoutWeightImpl(Ark_NativePointer node,
                      const Type_CommonMethod_layoutWeight_Arg0* value)
{
}
void PaddingImpl(Ark_NativePointer node,
                 const Type_CommonMethod_padding_Arg0* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA CommonMethod::PaddingImpl: LocalizedPadding is not supported yet!");
    ViewAbstract::SetPadding(frameNode, Converter::OptConvert<PaddingProperty>(*value));
}
void MarginImpl(Ark_NativePointer node,
                const Type_CommonMethod_margin_Arg0* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA CommonMethod::MarginImpl: LocalizedMargin is not supported yet!");
    ViewAbstract::SetMargin(frameNode, Converter::OptConvert<PaddingProperty>(*value));
}
void BackgroundImpl(Ark_NativePointer node,
                    const CustomBuilder* builder,
                    const Opt_Type_CommonMethod_background_Arg1* options)
{
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        CounterModelNG::SetBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
    } else {
        ViewAbstract::SetBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
    }
}
void PixelRoundImpl(Ark_NativePointer node,
                    const Ark_PixelRoundPolicy* value)
{
}
void BackgroundImageImpl(Ark_NativePointer node,
                         const Type_CommonMethod_backgroundImage_Arg0* src,
                         const Opt_ImageRepeat* repeat)
{
}
void BackgroundImageSizeImpl(Ark_NativePointer node,
                             const Type_CommonMethod_backgroundImageSize_Arg0* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBackgroundImageSize(frameNode, Converter::OptConvert<BackgroundImageSize>(*value));
}
void BackgroundImagePositionImpl(Ark_NativePointer node,
                                 const Type_CommonMethod_backgroundImagePosition_Arg0* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto varValue = Converter::OptConvert<BackgroundImagePositionType>(*value);
    BackgroundImagePosition bgImgPosition;
    AnimationOption option = ViewStackProcessor::GetInstance()->GetImplicitAnimationOption();
    double valueX = 0.0;
    double valueY = 0.0;
    DimensionUnit typeX = DimensionUnit::PX;
    DimensionUnit typeY = DimensionUnit::PX;
    if (varValue) {
        if (auto arkPosition = std::get_if<Ark_Position>(&varValue.value()); arkPosition) {
            auto position =
                Converter::Convert<std::pair<std::optional<Dimension>, std::optional<Dimension>>>(*arkPosition);
            CalcDimension x;
            CalcDimension y;
            if (position.first) {
                x = position.first.value();
            }
            if (position.second) {
                y = position.second.value();
            }
            valueX = x.ConvertToPx();
            valueY = y.ConvertToPx();
            if (x.Unit() == DimensionUnit::PERCENT) {
                valueX = x.Value();
                typeX = DimensionUnit::PERCENT;
            }
            if (y.Unit() == DimensionUnit::PERCENT) {
                valueY = y.Value();
                typeY = DimensionUnit::PERCENT;
            }
        } else if (auto arkAlign = std::get_if<Ark_Alignment>(&varValue.value()); arkAlign) {
            auto alignment = Converter::OptConvert<std::pair<double, double>>(*arkAlign);
            if (alignment) {
                bgImgPosition.SetIsAlign(true);
                typeX = DimensionUnit::PERCENT;
                typeY = DimensionUnit::PERCENT;
                valueX = alignment.value().first;
                valueY = alignment.value().second;
            }
        }
    }
    bgImgPosition.SetSizeX(AnimatableDimension(valueX, typeX, option));
    bgImgPosition.SetSizeY(AnimatableDimension(valueY, typeY, option));
    ViewAbstract::SetBackgroundImagePosition(frameNode, bgImgPosition);
}
void BackgroundBlurStyleImpl(Ark_NativePointer node,
                             enum Ark_BlurStyle value,
                             const Opt_BackgroundBlurStyleOptions* options)
{
}
void BackgroundEffectImpl(Ark_NativePointer node,
                          const Ark_BackgroundEffectOptions* options)
{
}
void BackgroundImageResizableImpl(Ark_NativePointer node,
                                  const Ark_ResizableOptions* value)
{
}
void ForegroundEffectImpl(Ark_NativePointer node,
                          const Ark_ForegroundEffectOptions* options)
{
}
void VisualEffectImpl(Ark_NativePointer node,
                      const Ark_CustomObject* effect)
{
}
void BackgroundFilterImpl(Ark_NativePointer node,
                          const Ark_CustomObject* filter)
{
}
void ForegroundFilterImpl(Ark_NativePointer node,
                          const Ark_CustomObject* filter)
{
}
void CompositingFilterImpl(Ark_NativePointer node,
                           const Ark_CustomObject* filter)
{
}
void ForegroundBlurStyleImpl(Ark_NativePointer node,
                             enum Ark_BlurStyle value,
                             const Opt_ForegroundBlurStyleOptions* options)
{
}
void OpacityImpl(Ark_NativePointer node,
                 const Type_CommonMethod_opacity_Arg0* value)
{
}
void BorderImpl(Ark_NativePointer node,
                const Ark_BorderOptions* value)
{
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Type_CommonMethod_borderStyle_Arg0* value)
{
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Type_CommonMethod_borderWidth_Arg0* value)
{
}
void BorderColorImpl(Ark_NativePointer node,
                     const Type_CommonMethod_borderColor_Arg0* value)
{
}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Type_CommonMethod_borderRadius_Arg0* value)
{
}
void BorderImageImpl(Ark_NativePointer node,
                     const Ark_BorderImageOption* value)
{
}
void OutlineImpl(Ark_NativePointer node,
                 const Ark_OutlineOptions* value)
{
}
void OutlineStyleImpl(Ark_NativePointer node,
                      const Type_CommonMethod_outlineStyle_Arg0* value)
{
}
void OutlineWidthImpl(Ark_NativePointer node,
                      const Type_CommonMethod_outlineWidth_Arg0* value)
{
}
void OutlineColorImpl(Ark_NativePointer node,
                      const Type_CommonMethod_outlineColor_Arg0* value)
{
}
void OutlineRadiusImpl(Ark_NativePointer node,
                       const Type_CommonMethod_outlineRadius_Arg0* value)
{
}

void ForegroundColorImpl(Ark_NativePointer node,
                         const Type_CommonMethod_foregroundColor_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    auto var = Converter::OptConvert<ColorOrStrategy>(*value);
    if (var && var->index() == 1) {
        const auto& color = std::get<1>(*var);
        if (color) {
            ViewAbstract::SetForegroundColor(frameNode, color.value());
        } else {
            LOGI("#### CommonMethod::ForegroundColorImpl: color is empty");
        }
    } else {
        LOGE("#### CommonMethod::ForegroundColorImpl: strategy handling is not implemented!");
    }
}

void OnClick0Impl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](GestureEvent& info) {
        Ark_ClickEvent onClick = Converter::ArkValue<Ark_ClickEvent>(info);
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onClick0(frameNode->GetId(), onClick);
    };

    if (frameNode->GetTag() == "Span") {
        SpanModelNG::SetOnClick(reinterpret_cast<UINode *>(node), std::move(onEvent));
    } else {
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
    }
}
void OnClick1Impl(Ark_NativePointer node,
                  Ark_Function event,
                  const Ark_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](GestureEvent& info) {
        Ark_ClickEvent onClick = Converter::ArkValue<Ark_ClickEvent>(info);
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onClick1(frameNode->GetId(), onClick);
    };

    if (frameNode->GetTag() == "Span") {
        SpanModelNG::SetOnClick(reinterpret_cast<UINode *>(node), std::move(onEvent));
    } else {
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
    }
}
void OnHoverImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnAccessibilityHoverImpl(Ark_NativePointer node,
                              Ark_Function callback)
{
}
void HoverEffectImpl(Ark_NativePointer node,
                     enum Ark_HoverEffect value)
{
}
void OnMouseImpl(Ark_NativePointer node,
                 Ark_Function event)
{
}
void OnTouchImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](TouchEventInfo& eventInfo) {
        Ark_TouchEvent onTouch;
        onTouch.axisHorizontal.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.axisVertical.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.changedTouches.array = nullptr;
        onTouch.changedTouches.length = 0;
        auto changedTouches = eventInfo.GetChangedTouches();
        if (!changedTouches.empty()) {
            std::vector<Ark_TouchObject> array;
            for (auto& info : changedTouches) {
                array.push_back(Converter::ArkValue<Ark_TouchObject>(info));
            }
            onTouch.changedTouches.array = &array[0];
            onTouch.changedTouches.length = changedTouches.size();
        }
        onTouch.pressure.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.pressure.f32 = 0.0f;
        onTouch.preventDefault.id = 0;
        onTouch.source = static_cast<Ark_SourceType>(eventInfo.GetSourceDevice());
        onTouch.sourceTool = static_cast<Ark_SourceTool>(0);
        onTouch.stopPropagation.id = 0;
        onTouch.target.area.globalPosition.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.globalPosition.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.height.type = 0;
        onTouch.target.area.height.unit = 1;
        onTouch.target.area.height.value = 0;
        onTouch.target.area.width.type = 0;
        onTouch.target.area.width.unit = 1;
        onTouch.target.area.width.value = 0;
        onTouch.target.area.position.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.target.area.position.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
        onTouch.tiltX.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.tiltX.f32 = 0;
        onTouch.tiltY.tag = Ark_Tag::ARK_TAG_FLOAT32;
        onTouch.tiltY.f32 = 0;
        onTouch.timestamp.tag = Ark_Tag::ARK_TAG_INT32;
        onTouch.timestamp.i32 = eventInfo.GetTimeStamp().time_since_epoch().count();
        onTouch.type = static_cast<Ark_TouchType>(0);
        onTouch.touches.array = nullptr;
        onTouch.touches.length = 0;
        auto touches = eventInfo.GetTouches();
        if (!touches.empty()) {
            std::vector<Ark_TouchObject> array;
            for (auto& info : touches) {
                array.push_back(Converter::ArkValue<Ark_TouchObject>(info));
            }
            onTouch.touches.array = &array[0];
            onTouch.touches.length = touches.size();
        }

        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onTouch(frameNode->GetId(), onTouch);
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
void OnKeyEventImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void FocusableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, static_cast<bool>(value));
}
void OnFocusImpl(Ark_NativePointer node,
                 Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onFocus(frameNode->GetId());
    };
    ViewAbstract::SetOnFocus(frameNode, std::move(onEvent));
}
void OnBlurImpl(Ark_NativePointer node,
                Ark_Function event)
{
}
void TabIndexImpl(Ark_NativePointer node,
                  const Ark_Number* index)
{
}
void DefaultFocusImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
}
void FocusOnTouchImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void FocusBoxImpl(Ark_NativePointer node,
                  const Ark_FocusBoxStyle* style)
{
}
void FocusScopeIdImpl(Ark_NativePointer node,
                      const Ark_String* id,
                      const Opt_Boolean* isGroup)
{
}
void FocusScopePriorityImpl(Ark_NativePointer node,
                            const Ark_String* scopeId,
                            const Opt_FocusPriority* priority)
{
}
void AnimationImpl(Ark_NativePointer node,
                   const Ark_AnimateParam* value)
{
}
void Transition0Impl(Ark_NativePointer node,
                     const Type_CommonMethod_transition_Arg0* value)
{
}
void Transition1Impl(Ark_NativePointer node,
                     const Ark_TransitionEffect* effect,
                     const Opt_Function* onFinish)
{
}
void GestureImpl(Ark_NativePointer node,
                 const Ark_GestureType* gesture,
                 const Opt_GestureMask* mask)
{
}
void PriorityGestureImpl(Ark_NativePointer node,
                         const Ark_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
}
void ParallelGestureImpl(Ark_NativePointer node,
                         const Ark_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
}
void BlurImpl(Ark_NativePointer node,
              const Ark_Number* value,
              const Opt_BlurOptions* options)
{
}
void LinearGradientBlurImpl(Ark_NativePointer node,
                            const Ark_Number* value,
                            const Ark_LinearGradientBlurOptions* options)
{
}
void MotionBlurImpl(Ark_NativePointer node,
                    const Ark_MotionBlurOptions* value)
{
}
void BrightnessImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
}
void ContrastImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void GrayscaleImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
}
void ColorBlendImpl(Ark_NativePointer node,
                    const Type_CommonMethod_colorBlend_Arg0* value)
{
}
void SaturateImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void SepiaImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
}
void InvertImpl(Ark_NativePointer node,
                const Type_CommonMethod_invert_Arg0* value)
{
}
void SystemBarEffectImpl(Ark_NativePointer node)
{
}
void HueRotateImpl(Ark_NativePointer node,
                   const Type_CommonMethod_hueRotate_Arg0* value)
{
}
void UseShadowBatchingImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
}
void UseEffectImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void BackdropBlurImpl(Ark_NativePointer node,
                      const Ark_Number* value,
                      const Opt_BlurOptions* options)
{
}
void RenderGroupImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
}
void FreezeImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
}
void TranslateImpl(Ark_NativePointer node,
                   const Ark_TranslateOptions* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    TranslateOpt options = Converter::Convert<TranslateOpt>(*value);

    CalcDimension x = options.x.value_or(CalcDimension(0.0));
    CalcDimension y = options.y.value_or(CalcDimension(0.0));
    CalcDimension z = options.z.value_or(CalcDimension(0.0));
    ViewAbstract::SetTranslate(frameNode, TranslateOptions(x, y, z));
}
void ScaleImpl(Ark_NativePointer node,
               const Ark_ScaleOptions* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    ScaleOpt scaleOptions = Converter::Convert<ScaleOpt>(*value);

    float scaleX = scaleOptions.x.value_or(1.0f);
    float scaleY = scaleOptions.y.value_or(1.0f);
    ViewAbstract::SetScale(frameNode, VectorF(scaleX, scaleY));

    CalcDimension centerX = scaleOptions.centerX.value_or(0.5_pct);
    CalcDimension centerY = scaleOptions.centerY.value_or(0.5_pct);
    ViewAbstract::SetPivot(frameNode, DimensionOffset(centerX, centerY));
}
void GridSpanImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void GridOffsetImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
}
void RotateImpl(Ark_NativePointer node,
                const Ark_RotateOptions* value)
{
}
void TransformImpl(Ark_NativePointer node,
                   const Ark_CustomObject* value)
{
}
void OnAppearImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onAppear(frameNode->GetId());
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onEvent));
}
void OnDisAppearImpl(Ark_NativePointer node,
                     Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onDisAppear(frameNode->GetId());
    };
    ViewAbstract::SetOnDisappear(frameNode, std::move(onEvent));
}
void OnAttachImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnDetachImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnAreaChangeImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
void VisibilityImpl(Ark_NativePointer node,
                    enum Ark_Visibility value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetVisibility(frameNode, static_cast<VisibleType>(value));
}
void FlexGrowImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
}
void FlexShrinkImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
}
void FlexBasisImpl(Ark_NativePointer node,
                   const Type_CommonMethod_flexBasis_Arg0* value)
{
}
void AlignSelfImpl(Ark_NativePointer node,
                   enum Ark_ItemAlign value)
{
}
void DisplayPriorityImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
}
void ZIndexImpl(Ark_NativePointer node,
                const Ark_Number* value)
{
}
void SharedTransitionImpl(Ark_NativePointer node,
                          const Ark_String* id,
                          const Opt_sharedTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(id);
    auto modelId = Converter::Convert<std::string>(*id);
    auto modelOptions = std::make_shared<SharedTransitionOption>();
    if (options) {
        if (auto transOpt = Converter::OptConvert<SharedTransitionOption>(*options); transOpt) {
            *modelOptions = std::move(*transOpt);
        }
    }
    ViewAbstract::SetSharedTransition(frameNode, modelId, modelOptions);
}
void DirectionImpl(Ark_NativePointer node,
                   enum Ark_Direction value)
{
}
void AlignImpl(Ark_NativePointer node,
               enum Ark_Alignment value)
{
}
void PositionImpl(Ark_NativePointer node,
                  const Type_CommonMethod_position_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    switch (value->selector) {
        case CASE_0: {
            auto x = Converter::ConvertOrDefault(value->value0.x, Dimension());
            auto y = Converter::ConvertOrDefault(value->value0.y, Dimension());
            ViewAbstract::SetPosition(frameNode, { x, y });
            break;
        }
        case CASE_1: {
            auto result = Converter::ConvertOrDefault(value->value1, EdgesParam());
            ViewAbstract::SetPositionEdges(frameNode, result);
            break;
        }
        case CASE_2:
            LOGE("ARKOALA: LocalizedEdges is not fully support.");
            ViewAbstract::SetPositionLocalizedEdges(frameNode, true);
            break;

        default:
            LOGE("ARKOALA:PositionImpl: Unexpected value->selector: %{public}d\n", value->selector);
            return;
    }
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Type_CommonMethod_markAnchor_Arg0* value)
{
}
void OffsetImpl(Ark_NativePointer node,
                const Type_CommonMethod_offset_Arg0* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto varOpt = Converter::OptConvert<OffsetOrEdgesParam>(*value);
    if (!varOpt.has_value()) {
        LOGE("ARKOALA CommonMethod::OffsetImpl: incorrect value");
        return;
    }
    if (auto offset = std::get_if<std::optional<OffsetT<Dimension>>>(&varOpt.value())) {
        if (offset) {
            ViewAbstract::SetOffset(frameNode, offset->value());
        } else {
            LOGE("ARKOALA CommonMethod::OffsetImpl: offset is empty");
        }
    } else if (auto edges = std::get_if<std::optional<EdgesParamOptions>>(&varOpt.value())) {
        if (edges) {
            LOGE("ARKOALA: LocalizedEdges is not fully support.");
            ViewAbstract::SetOffsetEdges(frameNode, edges->value().value);
            ViewAbstract::SetOffsetLocalizedEdges(frameNode, edges->value().isLocalized);
        } else {
            LOGE("ARKOALA CommonMethod::OffsetImpl: edgesParamOptions is empty");
        }
    } else {
        LOGE("ARKOALA CommonMethod::OffsetImpl: incorrect value");
    }
}
void EnabledImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetEnabled(frameNode, static_cast<bool>(value));
}
void UseSizeTypeImpl(Ark_NativePointer node,
                     const Type_CommonMethod_useSizeType_Arg0* value)
{
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Ark_AlignRuleOption* value)
{
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Ark_LocalizedAlignRuleOptions* alignRule)
{
}
void ChainModeImpl(Ark_NativePointer node,
                   enum Ark_Axis direction,
                   enum Ark_ChainStyle style)
{
}
void AspectRatioImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
}
void ClickEffectImpl(Ark_NativePointer node,
                     const Type_CommonMethod_clickEffect_Arg0* value)
{
}
void OnDragStartImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void OnDragEnterImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void OnDragMoveImpl(Ark_NativePointer node,
                    Ark_Function event)
{
}
void OnDragLeaveImpl(Ark_NativePointer node,
                     Ark_Function event)
{
}
void OnDropImpl(Ark_NativePointer node,
                Ark_Function event)
{
}
void OnDragEndImpl(Ark_NativePointer node,
                   Ark_Function event)
{
}
void AllowDropImpl(Ark_NativePointer node,
                   const Type_CommonMethod_allowDrop_Arg0* value)
{
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void DragPreviewImpl(Ark_NativePointer node,
                     const Type_CommonMethod_dragPreview_Arg0* value)
{
}
void DragPreviewOptionsImpl(Ark_NativePointer node,
                            const Ark_DragPreviewOptions* value,
                            const Opt_DragInteractionOptions* options)
{
}
void OnPreDragImpl(Ark_NativePointer node,
                   Ark_Function callback)
{
}
void OverlayImpl(Ark_NativePointer node,
                 const Type_CommonMethod_overlay_Arg0* value,
                 const Opt_OverlayOptions* options)
{
}
void LinearGradientImpl(Ark_NativePointer node,
                        const Type_CommonMethod_linearGradient_Arg0* value)
{
}
void SweepGradientImpl(Ark_NativePointer node,
                       const Type_CommonMethod_sweepGradient_Arg0* value)
{
}
void RadialGradientImpl(Ark_NativePointer node,
                        const Type_CommonMethod_radialGradient_Arg0* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Gradient gradient = Converter::Convert<Gradient>(*value);
    ViewAbstract::SetRadialGradient(frameNode, gradient);
}
void MotionPathImpl(Ark_NativePointer node,
                    const Ark_MotionPathOptions* value)
{
}
void ShadowImpl(Ark_NativePointer node,
                const Type_CommonMethod_shadow_Arg0* value)
{
}
void BlendModeImpl(Ark_NativePointer node,
                   enum Ark_BlendMode value,
                   const Opt_BlendApplyType* type)
{
}
void AdvancedBlendModeImpl(Ark_NativePointer node,
                           const Type_CommonMethod_advancedBlendMode_Arg0* effect,
                           const Opt_BlendApplyType* type)
{
}
void Clip0Impl(Ark_NativePointer node,
               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetClipEdge(frameNode, Converter::Convert<bool>(value));
}
void Clip1Impl(Ark_NativePointer node,
               const Type_CommonMethod_clip1_Arg0* value)
{
    LOGE("ARKOALA CommonMethod::Clip1Impl: Deprecated interface!");
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!value) {
        ViewAbstract::SetClipEdge(frameNode, false);
        return;
    }
    auto clipTypeOpt = Converter::OptConvert<ClipType>(*value);
    if (clipTypeOpt) {
        if (auto arkBool = std::get_if<Ark_Boolean>(&clipTypeOpt.value()); arkBool) {
            ViewAbstract::SetClipEdge(frameNode, Converter::Convert<bool>(*arkBool));
            return;
        } else if (auto arkCircle = std::get_if<Ark_CircleAttribute>(&clipTypeOpt.value()); arkCircle) {
            LOGE("ARKOALA CommonMethod::Clip1Impl: Ark_CircleAttribute is not supported yet!");
        } else if (auto arkEllipse = std::get_if<Ark_EllipseAttribute>(&clipTypeOpt.value()); arkEllipse) {
            LOGE("ARKOALA CommonMethod::Clip1Impl: Ark_EllipseAttribute is not supported yet!");
        } else if (auto arkPath = std::get_if<Ark_PathAttribute>(&clipTypeOpt.value()); arkPath) {
            LOGE("ARKOALA CommonMethod::Clip1Impl: Ark_PathAttribute is not supported yet!");
        } else if (auto arkRect = std::get_if<Ark_RectAttribute>(&clipTypeOpt.value()); arkRect) {
            LOGE("ARKOALA CommonMethod::Clip1Impl: Ark_RectAttribute is not supported yet!");
        }
    }
    ViewAbstract::SetClipEdge(frameNode, false);
}
void ClipShapeImpl(Ark_NativePointer node,
                   const Type_CommonMethod_clipShape_Arg0* value)
{
}
void Mask0Impl(Ark_NativePointer node,
               const Ark_Materialized* value)
{
}
void Mask1Impl(Ark_NativePointer node,
               const Type_CommonMethod_mask1_Arg0* value)
{
}
void MaskShapeImpl(Ark_NativePointer node,
                   const Type_CommonMethod_maskShape_Arg0* value)
{
}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{
}
void IdImpl(Ark_NativePointer node,
            const Ark_String* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::string id = Converter::Convert<std::string>(*value);
    if (id.empty()) {
        return;
    }
    ViewAbstract::SetInspectorId(frameNode, id);
}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Ark_String* id)
{
}
void GeometryTransition1Impl(Ark_NativePointer node,
                             const Ark_String* id,
                             const Opt_GeometryTransitionOptions* options)
{
}
void BindPopupImpl(Ark_NativePointer node,
                   Ark_Boolean show,
                   const Type_CommonMethod_bindPopup_Arg1* popup)
{
}
void BindMenu0Impl(Ark_NativePointer node,
                   const Type_CommonMethod_bindMenu_Arg0* content,
                   const Opt_MenuOptions* options)
{
}
void BindMenu1Impl(Ark_NativePointer node,
                   Ark_Boolean isShow,
                   const Type_CommonMethod_bindMenu1_Arg1* content,
                   const Opt_MenuOptions* options)
{
}
void BindContextMenu0Impl(Ark_NativePointer node,
                          const CustomBuilder* content,
                          enum Ark_ResponseType responseType,
                          const Opt_ContextMenuOptions* options)
{
}
void BindContextMenu1Impl(Ark_NativePointer node,
                          Ark_Boolean isShown,
                          const CustomBuilder* content,
                          const Opt_ContextMenuOptions* options)
{
}
void BindContentCover0Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const CustomBuilder* builder,
                           const Opt_ModalTransition* type)
{
}
void BindContentCover1Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const CustomBuilder* builder,
                           const Opt_ContentCoverOptions* options)
{
}
void BindSheetImpl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const CustomBuilder* builder,
                   const Opt_SheetOptions* options)
{
}
void StateStylesImpl(Ark_NativePointer node,
                     const Ark_StateStyles* value)
{
}
void RestoreIdImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
}
void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                             const Array_Number* ratios,
                             Ark_Function event)
{
    CHECK_NULL_VOID(ratios);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    std::vector<float> rawRatioVec = Converter::Convert<std::vector<float>>(*ratios);
    size_t size = rawRatioVec.size();
    std::vector<double> ratioVec;
    for (size_t i = 0; i < size; i++) {
        double ratio = static_cast<double>(rawRatioVec[i]);
        if (LessOrEqual(ratio, VISIBLE_RATIO_MIN)) {
            ratio = VISIBLE_RATIO_MIN;
        }

        if (GreatOrEqual(ratio, VISIBLE_RATIO_MAX)) {
            ratio = VISIBLE_RATIO_MAX;
        }
        ratioVec.push_back(ratio);
    }

    auto onVisibleAreaChange = [frameNode](bool visible, double ratio) {
        Ark_Boolean isExpanding = Converter::ArkValue<Ark_Boolean>(visible);
        Ark_Number currentRatio = Converter::ArkValue<Ark_Number>(static_cast<float>(ratio));
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onVisibleAreaChange(
            frameNode->GetId(), isExpanding, currentRatio);
    };

    ViewAbstract::SetOnVisibleChange(frameNode, std::move(onVisibleAreaChange), ratioVec);
}
void SphericalEffectImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
}
void LightUpEffectImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
}
void PixelStretchEffectImpl(Ark_NativePointer node,
                            const Ark_PixelStretchEffectOptions* options)
{
}
void KeyboardShortcutImpl(Ark_NativePointer node,
                          const Type_CommonMethod_keyboardShortcut_Arg0* value,
                          const Array_ModifierKey* keys,
                          const Opt_Function* action)
{
}
void AccessibilityGroupImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
}
void AccessibilityText0Impl(Ark_NativePointer node,
                            const Ark_String* value)
{
}
void AccessibilityText1Impl(Ark_NativePointer node,
                            const Ark_Resource* text)
{
}
void AccessibilityTextHintImpl(Ark_NativePointer node,
                               const Ark_String* value)
{
}
void AccessibilityDescription0Impl(Ark_NativePointer node,
                                   const Ark_String* value)
{
}
void AccessibilityDescription1Impl(Ark_NativePointer node,
                                   const Ark_Resource* description)
{
}
void AccessibilityLevelImpl(Ark_NativePointer node,
                            const Ark_String* value)
{
}
void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                  const CustomBuilder* builder)
{
}
void ObscuredImpl(Ark_NativePointer node,
                  const Array_ObscuredReasons* reasons)
{
}
void ReuseIdImpl(Ark_NativePointer node,
                 const Ark_String* id)
{
}
void RenderFitImpl(Ark_NativePointer node,
                   enum Ark_RenderFit fitMode)
{
}
void GestureModifierImpl(Ark_NativePointer node,
                         const Ark_Materialized* modifier)
{
}
void BackgroundBrightnessImpl(Ark_NativePointer node,
                              const Ark_BackgroundBrightnessOptions* params)
{
}
void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                             Ark_Function callback)
{
}
void OnGestureRecognizerJudgeBeginImpl(Ark_NativePointer node,
                                       Ark_Function callback)
{
}
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                             Ark_Function callback)
{
}
void MonopolizeEventsImpl(Ark_NativePointer node,
                          Ark_Boolean monopolize)
{
}
void OnTouchInterceptImpl(Ark_NativePointer node,
                          Ark_Function callback)
{
}
void OnSizeChangeImpl(Ark_NativePointer node,
                      Ark_Function event)
{
}
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::WidthImpl,
        CommonMethodModifier::HeightImpl,
        CommonMethodModifier::DrawModifierImpl,
        CommonMethodModifier::CustomPropertyImpl,
        CommonMethodModifier::ExpandSafeAreaImpl,
        CommonMethodModifier::ResponseRegionImpl,
        CommonMethodModifier::MouseResponseRegionImpl,
        CommonMethodModifier::SizeImpl,
        CommonMethodModifier::ConstraintSizeImpl,
        CommonMethodModifier::TouchableImpl,
        CommonMethodModifier::HitTestBehaviorImpl,
        CommonMethodModifier::OnChildTouchTestImpl,
        CommonMethodModifier::LayoutWeightImpl,
        CommonMethodModifier::PaddingImpl,
        CommonMethodModifier::MarginImpl,
        CommonMethodModifier::BackgroundImpl,
        CommonMethodModifier::BackgroundColorImpl,
        CommonMethodModifier::PixelRoundImpl,
        CommonMethodModifier::BackgroundImageImpl,
        CommonMethodModifier::BackgroundImageSizeImpl,
        CommonMethodModifier::BackgroundImagePositionImpl,
        CommonMethodModifier::BackgroundBlurStyleImpl,
        CommonMethodModifier::BackgroundEffectImpl,
        CommonMethodModifier::BackgroundImageResizableImpl,
        CommonMethodModifier::ForegroundEffectImpl,
        CommonMethodModifier::VisualEffectImpl,
        CommonMethodModifier::BackgroundFilterImpl,
        CommonMethodModifier::ForegroundFilterImpl,
        CommonMethodModifier::CompositingFilterImpl,
        CommonMethodModifier::ForegroundBlurStyleImpl,
        CommonMethodModifier::OpacityImpl,
        CommonMethodModifier::BorderImpl,
        CommonMethodModifier::BorderStyleImpl,
        CommonMethodModifier::BorderWidthImpl,
        CommonMethodModifier::BorderColorImpl,
        CommonMethodModifier::BorderRadiusImpl,
        CommonMethodModifier::BorderImageImpl,
        CommonMethodModifier::OutlineImpl,
        CommonMethodModifier::OutlineStyleImpl,
        CommonMethodModifier::OutlineWidthImpl,
        CommonMethodModifier::OutlineColorImpl,
        CommonMethodModifier::OutlineRadiusImpl,
        CommonMethodModifier::ForegroundColorImpl,
        CommonMethodModifier::OnClick0Impl,
        CommonMethodModifier::OnClick1Impl,
        CommonMethodModifier::OnHoverImpl,
        CommonMethodModifier::OnAccessibilityHoverImpl,
        CommonMethodModifier::HoverEffectImpl,
        CommonMethodModifier::OnMouseImpl,
        CommonMethodModifier::OnTouchImpl,
        CommonMethodModifier::OnKeyEventImpl,
        CommonMethodModifier::OnKeyPreImeImpl,
        CommonMethodModifier::FocusableImpl,
        CommonMethodModifier::OnFocusImpl,
        CommonMethodModifier::OnBlurImpl,
        CommonMethodModifier::TabIndexImpl,
        CommonMethodModifier::DefaultFocusImpl,
        CommonMethodModifier::GroupDefaultFocusImpl,
        CommonMethodModifier::FocusOnTouchImpl,
        CommonMethodModifier::FocusBoxImpl,
        CommonMethodModifier::FocusScopeIdImpl,
        CommonMethodModifier::FocusScopePriorityImpl,
        CommonMethodModifier::AnimationImpl,
        CommonMethodModifier::Transition0Impl,
        CommonMethodModifier::Transition1Impl,
        CommonMethodModifier::GestureImpl,
        CommonMethodModifier::PriorityGestureImpl,
        CommonMethodModifier::ParallelGestureImpl,
        CommonMethodModifier::BlurImpl,
        CommonMethodModifier::LinearGradientBlurImpl,
        CommonMethodModifier::MotionBlurImpl,
        CommonMethodModifier::BrightnessImpl,
        CommonMethodModifier::ContrastImpl,
        CommonMethodModifier::GrayscaleImpl,
        CommonMethodModifier::ColorBlendImpl,
        CommonMethodModifier::SaturateImpl,
        CommonMethodModifier::SepiaImpl,
        CommonMethodModifier::InvertImpl,
        CommonMethodModifier::SystemBarEffectImpl,
        CommonMethodModifier::HueRotateImpl,
        CommonMethodModifier::UseShadowBatchingImpl,
        CommonMethodModifier::UseEffectImpl,
        CommonMethodModifier::BackdropBlurImpl,
        CommonMethodModifier::RenderGroupImpl,
        CommonMethodModifier::FreezeImpl,
        CommonMethodModifier::TranslateImpl,
        CommonMethodModifier::ScaleImpl,
        CommonMethodModifier::GridSpanImpl,
        CommonMethodModifier::GridOffsetImpl,
        CommonMethodModifier::RotateImpl,
        CommonMethodModifier::TransformImpl,
        CommonMethodModifier::OnAppearImpl,
        CommonMethodModifier::OnDisAppearImpl,
        CommonMethodModifier::OnAttachImpl,
        CommonMethodModifier::OnDetachImpl,
        CommonMethodModifier::OnAreaChangeImpl,
        CommonMethodModifier::VisibilityImpl,
        CommonMethodModifier::FlexGrowImpl,
        CommonMethodModifier::FlexShrinkImpl,
        CommonMethodModifier::FlexBasisImpl,
        CommonMethodModifier::AlignSelfImpl,
        CommonMethodModifier::DisplayPriorityImpl,
        CommonMethodModifier::ZIndexImpl,
        CommonMethodModifier::SharedTransitionImpl,
        CommonMethodModifier::DirectionImpl,
        CommonMethodModifier::AlignImpl,
        CommonMethodModifier::PositionImpl,
        CommonMethodModifier::MarkAnchorImpl,
        CommonMethodModifier::OffsetImpl,
        CommonMethodModifier::EnabledImpl,
        CommonMethodModifier::UseSizeTypeImpl,
        CommonMethodModifier::AlignRules0Impl,
        CommonMethodModifier::AlignRules1Impl,
        CommonMethodModifier::ChainModeImpl,
        CommonMethodModifier::AspectRatioImpl,
        CommonMethodModifier::ClickEffectImpl,
        CommonMethodModifier::OnDragStartImpl,
        CommonMethodModifier::OnDragEnterImpl,
        CommonMethodModifier::OnDragMoveImpl,
        CommonMethodModifier::OnDragLeaveImpl,
        CommonMethodModifier::OnDropImpl,
        CommonMethodModifier::OnDragEndImpl,
        CommonMethodModifier::AllowDropImpl,
        CommonMethodModifier::DraggableImpl,
        CommonMethodModifier::DragPreviewImpl,
        CommonMethodModifier::DragPreviewOptionsImpl,
        CommonMethodModifier::OnPreDragImpl,
        CommonMethodModifier::OverlayImpl,
        CommonMethodModifier::LinearGradientImpl,
        CommonMethodModifier::SweepGradientImpl,
        CommonMethodModifier::RadialGradientImpl,
        CommonMethodModifier::MotionPathImpl,
        CommonMethodModifier::ShadowImpl,
        CommonMethodModifier::BlendModeImpl,
        CommonMethodModifier::AdvancedBlendModeImpl,
        CommonMethodModifier::Clip0Impl,
        CommonMethodModifier::Clip1Impl,
        CommonMethodModifier::ClipShapeImpl,
        CommonMethodModifier::Mask0Impl,
        CommonMethodModifier::Mask1Impl,
        CommonMethodModifier::MaskShapeImpl,
        CommonMethodModifier::KeyImpl,
        CommonMethodModifier::IdImpl,
        CommonMethodModifier::GeometryTransition0Impl,
        CommonMethodModifier::GeometryTransition1Impl,
        CommonMethodModifier::BindPopupImpl,
        CommonMethodModifier::BindMenu0Impl,
        CommonMethodModifier::BindMenu1Impl,
        CommonMethodModifier::BindContextMenu0Impl,
        CommonMethodModifier::BindContextMenu1Impl,
        CommonMethodModifier::BindContentCover0Impl,
        CommonMethodModifier::BindContentCover1Impl,
        CommonMethodModifier::BindSheetImpl,
        CommonMethodModifier::StateStylesImpl,
        CommonMethodModifier::RestoreIdImpl,
        CommonMethodModifier::OnVisibleAreaChangeImpl,
        CommonMethodModifier::SphericalEffectImpl,
        CommonMethodModifier::LightUpEffectImpl,
        CommonMethodModifier::PixelStretchEffectImpl,
        CommonMethodModifier::KeyboardShortcutImpl,
        CommonMethodModifier::AccessibilityGroupImpl,
        CommonMethodModifier::AccessibilityText0Impl,
        CommonMethodModifier::AccessibilityText1Impl,
        CommonMethodModifier::AccessibilityTextHintImpl,
        CommonMethodModifier::AccessibilityDescription0Impl,
        CommonMethodModifier::AccessibilityDescription1Impl,
        CommonMethodModifier::AccessibilityLevelImpl,
        CommonMethodModifier::AccessibilityVirtualNodeImpl,
        CommonMethodModifier::ObscuredImpl,
        CommonMethodModifier::ReuseIdImpl,
        CommonMethodModifier::RenderFitImpl,
        CommonMethodModifier::GestureModifierImpl,
        CommonMethodModifier::BackgroundBrightnessImpl,
        CommonMethodModifier::OnGestureJudgeBeginImpl,
        CommonMethodModifier::OnGestureRecognizerJudgeBeginImpl,
        CommonMethodModifier::ShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::MonopolizeEventsImpl,
        CommonMethodModifier::OnTouchInterceptImpl,
        CommonMethodModifier::OnSizeChangeImpl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
