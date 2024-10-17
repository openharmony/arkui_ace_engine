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

namespace OHOS::Ace::NG {
struct EdgesParamOptions {
    EdgesParam value;
    bool isLocalized;
};

using ColorOrStrategy = std::variant<std::monostate, std::optional<Color>, std::optional<ForegroundColorStrategy>>;
using OffsetOrEdgesParam = std::variant<
    std::monostate,
    std::optional<OffsetT<Dimension>>,
    std::optional<EdgesParamOptions>
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
GradientColor Convert(const Ark_Tuple_ResourceColor_Number& src)
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
Gradient Convert(const Ark_Type_CommonMethod_radialGradient_value& src)
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
                      const Ark_Union_DrawModifier_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetDrawModifier(frameNode, convValue);
}
void ResponseRegionImpl(Ark_NativePointer node,
                        const Ark_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetResponseRegion(frameNode, convValue);
}
void MouseResponseRegionImpl(Ark_NativePointer node,
                             const Ark_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMouseResponseRegion(frameNode, convValue);
}
void SizeImpl(Ark_NativePointer node,
              const Ark_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
    CHECK_NULL_VOID(value);
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
                         Ark_HitTestMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetHitTestBehavior(frameNode, convValue);
}
void OnChildTouchTestImpl(Ark_NativePointer node,
                          Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnChildTouchTest(frameNode, convValue);
}
void LayoutWeightImpl(Ark_NativePointer node,
                      const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetLayoutWeight(frameNode, convValue);
}
void PaddingImpl(Ark_NativePointer node,
                 const Ark_Union_Padding_Length_LocalizedPadding* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA CommonMethod::PaddingImpl: LocalizedPadding is not supported yet!");
    ViewAbstract::SetPadding(frameNode, Converter::OptConvert<PaddingProperty>(*value));
}
void MarginImpl(Ark_NativePointer node,
                const Ark_Union_Margin_Length_LocalizedMargin* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA CommonMethod::MarginImpl: LocalizedMargin is not supported yet!");
    ViewAbstract::SetMargin(frameNode, Converter::OptConvert<PaddingProperty>(*value));
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetPixelRound(frameNode, convValue);
}
void BackgroundImageSizeImpl(Ark_NativePointer node,
                             const Ark_Union_SizeOptions_ImageSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundImageSize(frameNode, convValue);
}
void BackgroundImagePositionImpl(Ark_NativePointer node,
                                 const Ark_Union_Position_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundImagePosition(frameNode, convValue);
}
void BackgroundEffectImpl(Ark_NativePointer node,
                          const Ark_BackgroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundEffect(frameNode, convValue);
}
void BackgroundImageResizableImpl(Ark_NativePointer node,
                                  const Ark_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundImageResizable(frameNode, convValue);
}
void ForegroundEffectImpl(Ark_NativePointer node,
                          const Ark_ForegroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetForegroundEffect(frameNode, convValue);
}
void VisualEffectImpl(Ark_NativePointer node,
                      const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetVisualEffect(frameNode, convValue);
}
void BackgroundFilterImpl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundFilter(frameNode, convValue);
}
void ForegroundFilterImpl(Ark_NativePointer node,
                          const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetForegroundFilter(frameNode, convValue);
}
void CompositingFilterImpl(Ark_NativePointer node,
                           const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetCompositingFilter(frameNode, convValue);
}
void OpacityImpl(Ark_NativePointer node,
                 const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOpacity(frameNode, convValue);
}
void BorderImpl(Ark_NativePointer node,
                const Ark_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBorder(frameNode, convValue);
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Ark_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBorderStyle(frameNode, convValue);
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Ark_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBorderWidth(frameNode, convValue);
}
void BorderColorImpl(Ark_NativePointer node,
                     const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBorderColor(frameNode, convValue);
}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Ark_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBorderRadius(frameNode, convValue);
}
void BorderImageImpl(Ark_NativePointer node,
                     const Ark_BorderImageOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBorderImage(frameNode, convValue);
}
void OutlineImpl(Ark_NativePointer node,
                 const Ark_OutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOutline(frameNode, convValue);
}
void OutlineStyleImpl(Ark_NativePointer node,
                      const Ark_Union_OutlineStyle_EdgeOutlineStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOutlineStyle(frameNode, convValue);
}
void OutlineWidthImpl(Ark_NativePointer node,
                      const Ark_Union_Dimension_EdgeOutlineWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOutlineWidth(frameNode, convValue);
}
void OutlineColorImpl(Ark_NativePointer node,
                      const Ark_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOutlineColor(frameNode, convValue);
}
void OutlineRadiusImpl(Ark_NativePointer node,
                       const Ark_Union_Dimension_OutlineRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOutlineRadius(frameNode, convValue);
}

void ForegroundColorImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceColor_ColoringStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
void OnClickImpl(Ark_NativePointer node,
                 Ark_Function event,
                 const Opt_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode](GestureEvent& info) {
        Ark_ClickEvent onClick = Converter::ArkValue<Ark_ClickEvent>(info);
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onClick(frameNode->GetId(), onClick);
    };

    if (frameNode->GetTag() == "Span") {
        SpanModelNG::SetOnClick(reinterpret_cast<UINode *>(node), std::move(onEvent));
    } else {
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
    }
}
void OnHoverImpl(Ark_NativePointer node,
                 Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnHover(frameNode, convValue);
}
void OnAccessibilityHoverImpl(Ark_NativePointer node,
                              Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnAccessibilityHover(frameNode, convValue);
}
void HoverEffectImpl(Ark_NativePointer node,
                     Ark_HoverEffect value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetHoverEffect(frameNode, convValue);
}
void OnMouseImpl(Ark_NativePointer node,
                 Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnMouse(frameNode, convValue);
}
void OnTouchImpl(Ark_NativePointer node,
                 Ark_Function value)
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
                    Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnKeyEvent(frameNode, convValue);
}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnKeyPreIme(frameNode, convValue);
}
void FocusableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetFocusable(frameNode, static_cast<bool>(value));
}
void OnFocusImpl(Ark_NativePointer node,
                 Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onFocus(frameNode->GetId());
    };
    ViewAbstract::SetOnFocus(frameNode, std::move(onEvent));
}
void OnBlurImpl(Ark_NativePointer node,
                Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnBlur(frameNode, convValue);
}
void TabIndexImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetTabIndex(frameNode, convValue);
}
void DefaultFocusImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetDefaultFocus(frameNode, convValue);
}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetGroupDefaultFocus(frameNode, convValue);
}
void FocusOnTouchImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetFocusOnTouch(frameNode, convValue);
}
void FocusBoxImpl(Ark_NativePointer node,
                  const Ark_FocusBoxStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetFocusBox(frameNode, convValue);
}
void AnimationImpl(Ark_NativePointer node,
                   const Ark_AnimateParam* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAnimation(frameNode, convValue);
}
void Transition0Impl(Ark_NativePointer node,
                     const Ark_Union_TransitionOptions_TransitionEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetTransition0(frameNode, convValue);
}
void Transition1Impl(Ark_NativePointer node,
                     const Ark_TransitionEffect* effect,
                     const Opt_Function* onFinish)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(effect);
    //auto convValue = Converter::OptConvert<type>(effect); // for enums
    //CommonMethodModelNG::SetTransition1(frameNode, convValue);
}
void MotionBlurImpl(Ark_NativePointer node,
                    const Ark_MotionBlurOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMotionBlur(frameNode, convValue);
}
void BrightnessImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBrightness(frameNode, convValue);
}
void ContrastImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetContrast(frameNode, convValue);
}
void GrayscaleImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetGrayscale(frameNode, convValue);
}
void ColorBlendImpl(Ark_NativePointer node,
                    const Ark_Union_Color_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetColorBlend(frameNode, convValue);
}
void SaturateImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetSaturate(frameNode, convValue);
}
void SepiaImpl(Ark_NativePointer node,
               const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetSepia(frameNode, convValue);
}
void InvertImpl(Ark_NativePointer node,
                const Ark_Union_Number_InvertOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetInvert(frameNode, convValue);
}
void HueRotateImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetHueRotate(frameNode, convValue);
}
void UseShadowBatchingImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetUseShadowBatching(frameNode, convValue);
}
void UseEffectImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetUseEffect(frameNode, convValue);
}
void RenderGroupImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetRenderGroup(frameNode, convValue);
}
void FreezeImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetFreeze(frameNode, convValue);
}
void TranslateImpl(Ark_NativePointer node,
                   const Ark_TranslateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetTranslate(frameNode, convValue);
}
void ScaleImpl(Ark_NativePointer node,
               const Ark_ScaleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetScale(frameNode, convValue);
}
void GridSpanImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetGridSpan(frameNode, convValue);
}
void GridOffsetImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetGridOffset(frameNode, convValue);
}
void RotateImpl(Ark_NativePointer node,
                const Ark_RotateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetRotate(frameNode, convValue);
}
void TransformImpl(Ark_NativePointer node,
                   const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetTransform(frameNode, convValue);
}
void OnAppearImpl(Ark_NativePointer node,
                  Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onAppear(frameNode->GetId());
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onEvent));
}
void OnDisAppearImpl(Ark_NativePointer node,
                     Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [frameNode]() {
        GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onDisAppear(frameNode->GetId());
    };
    ViewAbstract::SetOnDisappear(frameNode, std::move(onEvent));
}
void OnAttachImpl(Ark_NativePointer node,
                  Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnAttach(frameNode, convValue);
}
void OnDetachImpl(Ark_NativePointer node,
                  Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnDetach(frameNode, convValue);
}
void OnAreaChangeImpl(Ark_NativePointer node,
                      Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnAreaChange(frameNode, convValue);
}
void VisibilityImpl(Ark_NativePointer node,
                    Ark_Visibility value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetVisibility(frameNode, static_cast<VisibleType>(value));
}
void FlexGrowImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetFlexGrow(frameNode, convValue);
}
void FlexShrinkImpl(Ark_NativePointer node,
                    const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetFlexShrink(frameNode, convValue);
}
void FlexBasisImpl(Ark_NativePointer node,
                   const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetFlexBasis(frameNode, convValue);
}
void AlignSelfImpl(Ark_NativePointer node,
                   Ark_ItemAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetAlignSelf(frameNode, convValue);
}
void DisplayPriorityImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetDisplayPriority(frameNode, convValue);
}
void ZIndexImpl(Ark_NativePointer node,
                const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetZIndex(frameNode, convValue);
}
void DirectionImpl(Ark_NativePointer node,
                   Ark_Direction value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetDirection(frameNode, convValue);
}
void AlignImpl(Ark_NativePointer node,
               Ark_Alignment value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetAlign(frameNode, convValue);
}
void PositionImpl(Ark_NativePointer node,
                  const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
                    const Ark_Union_Position_LocalizedPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMarkAnchor(frameNode, convValue);
}
void OffsetImpl(Ark_NativePointer node,
                const Ark_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
                     const Ark_Literal_Union_Number_Literal_Number_span_offset_xs_sm_md_lg* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetUseSizeType(frameNode, convValue);
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Ark_AlignRuleOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAlignRules0(frameNode, convValue);
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Ark_LocalizedAlignRuleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAlignRules1(frameNode, convValue);
}
void AspectRatioImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAspectRatio(frameNode, convValue);
}
void ClickEffectImpl(Ark_NativePointer node,
                     const Ark_Union_ClickEffect_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetClickEffect(frameNode, convValue);
}
void OnDragStartImpl(Ark_NativePointer node,
                     Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnDragStart(frameNode, convValue);
}
void OnDragEnterImpl(Ark_NativePointer node,
                     Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnDragEnter(frameNode, convValue);
}
void OnDragMoveImpl(Ark_NativePointer node,
                    Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnDragMove(frameNode, convValue);
}
void OnDragLeaveImpl(Ark_NativePointer node,
                     Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnDragLeave(frameNode, convValue);
}
void OnDropImpl(Ark_NativePointer node,
                Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnDrop(frameNode, convValue);
}
void OnDragEndImpl(Ark_NativePointer node,
                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnDragEnd(frameNode, convValue);
}
void AllowDropImpl(Ark_NativePointer node,
                   const Ark_Union_Array_UniformDataType_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAllowDrop(frameNode, convValue);
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetDraggable(frameNode, convValue);
}
void DragPreviewImpl(Ark_NativePointer node,
                     const Ark_Union_CustomBuilder_DragItemInfo_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetDragPreview(frameNode, convValue);
}
void OnPreDragImpl(Ark_NativePointer node,
                   Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnPreDrag(frameNode, convValue);
}
void LinearGradientImpl(Ark_NativePointer node,
                        const Ark_Type_CommonMethod_linearGradient_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetLinearGradient(frameNode, convValue);
}
void SweepGradientImpl(Ark_NativePointer node,
                       const Ark_Type_CommonMethod_sweepGradient_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetSweepGradient(frameNode, convValue);
}
void RadialGradientImpl(Ark_NativePointer node,
                        const Ark_Type_CommonMethod_radialGradient_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Gradient gradient = Converter::Convert<Gradient>(*value);
    ViewAbstract::SetRadialGradient(frameNode, gradient);
}
void MotionPathImpl(Ark_NativePointer node,
                    const Ark_MotionPathOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMotionPath(frameNode, convValue);
}
void ShadowImpl(Ark_NativePointer node,
                const Ark_Union_ShadowOptions_ShadowStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetShadow(frameNode, convValue);
}
void Clip0Impl(Ark_NativePointer node,
               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetClip0(frameNode, convValue);
}
void Clip1Impl(Ark_NativePointer node,
               const Ark_Type_CommonMethod_clip_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetClip1(frameNode, convValue);
}
void ClipShapeImpl(Ark_NativePointer node,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetClipShape(frameNode, convValue);
}
void Mask0Impl(Ark_NativePointer node,
               const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMask0(frameNode, convValue);
}
void Mask1Impl(Ark_NativePointer node,
               const Ark_Type_CommonMethod_mask_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMask1(frameNode, convValue);
}
void MaskShapeImpl(Ark_NativePointer node,
                   const Ark_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMaskShape(frameNode, convValue);
}
void KeyImpl(Ark_NativePointer node,
             const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetKey(frameNode, convValue);
}
void IdImpl(Ark_NativePointer node,
            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetId(frameNode, convValue);
}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetGeometryTransition0(frameNode, convValue);
}
void GeometryTransition1Impl(Ark_NativePointer node,
                             const Ark_String* id,
                             const Opt_GeometryTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetGeometryTransition1(frameNode, convValue);
}
void StateStylesImpl(Ark_NativePointer node,
                     const Ark_StateStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetStateStyles(frameNode, convValue);
}
void RestoreIdImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetRestoreId(frameNode, convValue);
}
void SphericalEffectImpl(Ark_NativePointer node,
                         const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetSphericalEffect(frameNode, convValue);
}
void LightUpEffectImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetLightUpEffect(frameNode, convValue);
}
void PixelStretchEffectImpl(Ark_NativePointer node,
                            const Ark_PixelStretchEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetPixelStretchEffect(frameNode, convValue);
}
void AccessibilityGroupImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetAccessibilityGroup(frameNode, convValue);
}
void AccessibilityText0Impl(Ark_NativePointer node,
                            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityText0(frameNode, convValue);
}
void AccessibilityText1Impl(Ark_NativePointer node,
                            const Ark_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAccessibilityText1(frameNode, convValue);
}
void AccessibilityTextHintImpl(Ark_NativePointer node,
                               const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityTextHint(frameNode, convValue);
}
void AccessibilityDescription0Impl(Ark_NativePointer node,
                                   const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityDescription0(frameNode, convValue);
}
void AccessibilityDescription1Impl(Ark_NativePointer node,
                                   const Ark_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAccessibilityDescription1(frameNode, convValue);
}
void AccessibilityLevelImpl(Ark_NativePointer node,
                            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityLevel(frameNode, convValue);
}
void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                  const Ark_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAccessibilityVirtualNode(frameNode, convValue);
}
void ObscuredImpl(Ark_NativePointer node,
                  const Array_ObscuredReasons* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetObscured(frameNode, convValue);
}
void ReuseIdImpl(Ark_NativePointer node,
                 const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    [[maybe_unused]]
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetReuseId(frameNode, convValue);
}
void RenderFitImpl(Ark_NativePointer node,
                   Ark_RenderFit value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetRenderFit(frameNode, convValue);
}
void GestureModifierImpl(Ark_NativePointer node,
                         const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetGestureModifier(frameNode, convValue);
}
void BackgroundBrightnessImpl(Ark_NativePointer node,
                              const Ark_BackgroundBrightnessOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundBrightness(frameNode, convValue);
}
void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                             Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnGestureJudgeBegin(frameNode, convValue);
}
void OnGestureRecognizerJudgeBeginImpl(Ark_NativePointer node,
                                       Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnGestureRecognizerJudgeBegin(frameNode, convValue);
}
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                             Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetShouldBuiltInRecognizerParallelWith(frameNode, convValue);
}
void MonopolizeEventsImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    [[maybe_unused]]
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetMonopolizeEvents(frameNode, convValue);
}
void OnTouchInterceptImpl(Ark_NativePointer node,
                          Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnTouchIntercept(frameNode, convValue);
}
void OnSizeChangeImpl(Ark_NativePointer node,
                      Ark_Function value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = [frameNode](input values) { code }
    //CommonMethodModelNG::SetOnSizeChange(frameNode, convValue);
}
void CustomPropertyImpl(Ark_NativePointer node,
                        const Ark_String* name,
                        const Opt_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(name);
    //auto convValue = Converter::OptConvert<type>(name); // for enums
    //CommonMethodModelNG::SetCustomProperty(frameNode, convValue);
}
void ExpandSafeAreaImpl(Ark_NativePointer node,
                        const Opt_Array_SafeAreaType* types,
                        const Opt_Array_SafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(types);
    //auto convValue = Converter::OptConvert<type>(types); // for enums
    //CommonMethodModelNG::SetExpandSafeArea(frameNode, convValue);
}
void BackgroundImpl(Ark_NativePointer node,
                    const Ark_CustomBuilder* builder,
                    const Opt_Literal_Alignment_align* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(builder);
    //auto convValue = Converter::OptConvert<type>(builder); // for enums
    //CommonMethodModelNG::SetBackground(frameNode, convValue);
}
void BackgroundImageImpl(Ark_NativePointer node,
                         const Ark_Union_ResourceStr_PixelMap* src,
                         const Opt_ImageRepeat* repeat)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(src);
    //auto convValue = Converter::OptConvert<type>(src); // for enums
    //CommonMethodModelNG::SetBackgroundImage(frameNode, convValue);
}
void BackgroundBlurStyleImpl(Ark_NativePointer node,
                             Ark_BlurStyle value,
                             const Opt_BackgroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetBackgroundBlurStyle(frameNode, convValue);
}
void ForegroundBlurStyleImpl(Ark_NativePointer node,
                             Ark_BlurStyle value,
                             const Opt_ForegroundBlurStyleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetForegroundBlurStyle(frameNode, convValue);
}
void FocusScopeIdImpl(Ark_NativePointer node,
                      const Ark_String* id,
                      const Opt_Boolean* isGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetFocusScopeId(frameNode, convValue);
}
void FocusScopePriorityImpl(Ark_NativePointer node,
                            const Ark_String* scopeId,
                            const Opt_FocusPriority* priority)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(scopeId);
    //auto convValue = Converter::OptConvert<type>(scopeId); // for enums
    //CommonMethodModelNG::SetFocusScopePriority(frameNode, convValue);
}
void GestureImpl(Ark_NativePointer node,
                 Ark_GestureControl_GestureType gesture,
                 const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetGesture(frameNode, convValue);
}
void PriorityGestureImpl(Ark_NativePointer node,
                         Ark_GestureControl_GestureType gesture,
                         const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetPriorityGesture(frameNode, convValue);
}
void ParallelGestureImpl(Ark_NativePointer node,
                         Ark_GestureControl_GestureType gesture,
                         const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetParallelGesture(frameNode, convValue);
}
void BlurImpl(Ark_NativePointer node,
              const Ark_Number* value,
              const Opt_BlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetBlur(frameNode, convValue);
}
void LinearGradientBlurImpl(Ark_NativePointer node,
                            const Ark_Number* value,
                            const Ark_LinearGradientBlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetLinearGradientBlur(frameNode, convValue);
}
void SystemBarEffectImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //CommonMethodModelNG::SetSystemBarEffect(frameNode, convValue);
}
void BackdropBlurImpl(Ark_NativePointer node,
                      const Ark_Number* value,
                      const Opt_BlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetBackdropBlur(frameNode, convValue);
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
void ChainModeImpl(Ark_NativePointer node,
                   Ark_Axis direction,
                   Ark_ChainStyle style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(direction);
    //auto convValue = Converter::OptConvert<type>(direction); // for enums
    //CommonMethodModelNG::SetChainMode(frameNode, convValue);
}
void DragPreviewOptionsImpl(Ark_NativePointer node,
                            const Ark_DragPreviewOptions* value,
                            const Opt_DragInteractionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetDragPreviewOptions(frameNode, convValue);
}
void OverlayImpl(Ark_NativePointer node,
                 const Ark_Union_String_CustomBuilder_ComponentContent* value,
                 const Opt_OverlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetOverlay(frameNode, convValue);
}
void BlendModeImpl(Ark_NativePointer node,
                   Ark_BlendMode value,
                   const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetBlendMode(frameNode, convValue);
}
void AdvancedBlendModeImpl(Ark_NativePointer node,
                           const Ark_Union_BlendMode_Blender* effect,
                           const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(effect);
    //auto convValue = Converter::OptConvert<type>(effect); // for enums
    //CommonMethodModelNG::SetAdvancedBlendMode(frameNode, convValue);
}
void BindPopupImpl(Ark_NativePointer node,
                   Ark_Boolean show,
                   const Ark_Union_PopupOptions_CustomPopupOptions* popup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(show);
    //auto convValue = Converter::OptConvert<type>(show); // for enums
    //CommonMethodModelNG::SetBindPopup(frameNode, convValue);
}
void BindMenu0Impl(Ark_NativePointer node,
                   const Ark_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //CommonMethodModelNG::SetBindMenu0(frameNode, convValue);
}
void BindMenu1Impl(Ark_NativePointer node,
                   Ark_Boolean isShow,
                   const Ark_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetBindMenu1(frameNode, convValue);
}
void BindContextMenu0Impl(Ark_NativePointer node,
                          const Ark_CustomBuilder* content,
                          Ark_ResponseType responseType,
                          const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //CommonMethodModelNG::SetBindContextMenu0(frameNode, convValue);
}
void BindContextMenu1Impl(Ark_NativePointer node,
                          Ark_Boolean isShown,
                          const Ark_CustomBuilder* content,
                          const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShown);
    //auto convValue = Converter::OptConvert<type>(isShown); // for enums
    //CommonMethodModelNG::SetBindContextMenu1(frameNode, convValue);
}
void BindContentCover0Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const Ark_CustomBuilder* builder,
                           const Opt_ModalTransition* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetBindContentCover0(frameNode, convValue);
}
void BindContentCover1Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const Ark_CustomBuilder* builder,
                           const Opt_ContentCoverOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetBindContentCover1(frameNode, convValue);
}
void BindSheetImpl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const Ark_CustomBuilder* builder,
                   const Opt_SheetOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetBindSheet(frameNode, convValue);
}
void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                             const Array_Number* ratios,
                             Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(ratios);
    //auto convValue = Converter::OptConvert<type>(ratios); // for enums
    //CommonMethodModelNG::SetOnVisibleAreaChange(frameNode, convValue);
}
void KeyboardShortcutImpl(Ark_NativePointer node,
                          const Ark_Union_String_FunctionKey* value,
                          const Array_ModifierKey* keys,
                          const Opt_Function* action)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetKeyboardShortcut(frameNode, convValue);
}
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::WidthImpl,
        CommonMethodModifier::HeightImpl,
        CommonMethodModifier::DrawModifierImpl,
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
        CommonMethodModifier::BackgroundColorImpl,
        CommonMethodModifier::PixelRoundImpl,
        CommonMethodModifier::BackgroundImageSizeImpl,
        CommonMethodModifier::BackgroundImagePositionImpl,
        CommonMethodModifier::BackgroundEffectImpl,
        CommonMethodModifier::BackgroundImageResizableImpl,
        CommonMethodModifier::ForegroundEffectImpl,
        CommonMethodModifier::VisualEffectImpl,
        CommonMethodModifier::BackgroundFilterImpl,
        CommonMethodModifier::ForegroundFilterImpl,
        CommonMethodModifier::CompositingFilterImpl,
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
        CommonMethodModifier::OnClickImpl,
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
        CommonMethodModifier::AnimationImpl,
        CommonMethodModifier::Transition0Impl,
        CommonMethodModifier::Transition1Impl,
        CommonMethodModifier::MotionBlurImpl,
        CommonMethodModifier::BrightnessImpl,
        CommonMethodModifier::ContrastImpl,
        CommonMethodModifier::GrayscaleImpl,
        CommonMethodModifier::ColorBlendImpl,
        CommonMethodModifier::SaturateImpl,
        CommonMethodModifier::SepiaImpl,
        CommonMethodModifier::InvertImpl,
        CommonMethodModifier::HueRotateImpl,
        CommonMethodModifier::UseShadowBatchingImpl,
        CommonMethodModifier::UseEffectImpl,
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
        CommonMethodModifier::DirectionImpl,
        CommonMethodModifier::AlignImpl,
        CommonMethodModifier::PositionImpl,
        CommonMethodModifier::MarkAnchorImpl,
        CommonMethodModifier::OffsetImpl,
        CommonMethodModifier::EnabledImpl,
        CommonMethodModifier::UseSizeTypeImpl,
        CommonMethodModifier::AlignRules0Impl,
        CommonMethodModifier::AlignRules1Impl,
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
        CommonMethodModifier::OnPreDragImpl,
        CommonMethodModifier::LinearGradientImpl,
        CommonMethodModifier::SweepGradientImpl,
        CommonMethodModifier::RadialGradientImpl,
        CommonMethodModifier::MotionPathImpl,
        CommonMethodModifier::ShadowImpl,
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
        CommonMethodModifier::StateStylesImpl,
        CommonMethodModifier::RestoreIdImpl,
        CommonMethodModifier::SphericalEffectImpl,
        CommonMethodModifier::LightUpEffectImpl,
        CommonMethodModifier::PixelStretchEffectImpl,
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
        CommonMethodModifier::CustomPropertyImpl,
        CommonMethodModifier::ExpandSafeAreaImpl,
        CommonMethodModifier::BackgroundImpl,
        CommonMethodModifier::BackgroundImageImpl,
        CommonMethodModifier::BackgroundBlurStyleImpl,
        CommonMethodModifier::ForegroundBlurStyleImpl,
        CommonMethodModifier::FocusScopeIdImpl,
        CommonMethodModifier::FocusScopePriorityImpl,
        CommonMethodModifier::GestureImpl,
        CommonMethodModifier::PriorityGestureImpl,
        CommonMethodModifier::ParallelGestureImpl,
        CommonMethodModifier::BlurImpl,
        CommonMethodModifier::LinearGradientBlurImpl,
        CommonMethodModifier::SystemBarEffectImpl,
        CommonMethodModifier::BackdropBlurImpl,
        CommonMethodModifier::SharedTransitionImpl,
        CommonMethodModifier::ChainModeImpl,
        CommonMethodModifier::DragPreviewOptionsImpl,
        CommonMethodModifier::OverlayImpl,
        CommonMethodModifier::BlendModeImpl,
        CommonMethodModifier::AdvancedBlendModeImpl,
        CommonMethodModifier::BindPopupImpl,
        CommonMethodModifier::BindMenu0Impl,
        CommonMethodModifier::BindMenu1Impl,
        CommonMethodModifier::BindContextMenu0Impl,
        CommonMethodModifier::BindContextMenu1Impl,
        CommonMethodModifier::BindContentCover0Impl,
        CommonMethodModifier::BindContentCover1Impl,
        CommonMethodModifier::BindSheetImpl,
        CommonMethodModifier::OnVisibleAreaChangeImpl,
        CommonMethodModifier::KeyboardShortcutImpl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
