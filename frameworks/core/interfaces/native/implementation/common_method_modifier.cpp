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

#include "arkoala_api_generated.h"

#include "base/log/log_wrapper.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/components_ng/pattern/counter/counter_node.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/view_context/view_context_model_ng.h"
#include "core/components_ng/property/flex_property.h"
#include "core/components_ng/property/safe_area_insets.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/components/common/properties/color.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace {
constexpr double VISIBLE_RATIO_MIN = 0.0;
constexpr double VISIBLE_RATIO_MAX = 1.0;
}

namespace CommonMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void Width0Impl(Ark_NativePointer node,
                const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::Convert<CalcLength>(value->value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        // if (result.GetDimensionContainsNegative().IsNegative()) {
        //     return;
        // }
        // CounterModelNG::SetWidth(frameNode, result);
    } else {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, true);
            return;
        }
        ViewAbstract::SetWidth(frameNode, result);
    }
}
void Width1Impl(Ark_NativePointer node,
                const Opt_Union_Length_LayoutPolicy* value)
{
}
void Height0Impl(Ark_NativePointer node,
                 const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto result = Converter::Convert<CalcLength>(value->value);
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        // if (result.GetDimensionContainsNegative().IsNegative()) {
        //     return;
        // }
        // CounterModelNG::SetHeight(frameNode, result);
    } else {
        if (result.GetDimensionContainsNegative().IsNegative()) {
            ViewAbstract::ClearWidthOrHeight(frameNode, false);
            return;
        }
        ViewAbstract::SetHeight(frameNode, result);
    }
}
void Height1Impl(Ark_NativePointer node,
                 const Opt_Union_Length_LayoutPolicy* value)
{
}
void DrawModifierImpl(Ark_NativePointer node,
                      const Opt_DrawModifier* value)
{
}
void ResponseRegionImpl(Ark_NativePointer node,
                        const Opt_Union_Array_Rectangle_Rectangle* value)
{
}
void MouseResponseRegionImpl(Ark_NativePointer node,
                             const Opt_Union_Array_Rectangle_Rectangle* value)
{
}
void SizeImpl(Ark_NativePointer node,
              const Opt_SizeOptions* value)
{
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Opt_ConstraintSizeOptions* value)
{
}
void TouchableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void HitTestBehaviorImpl(Ark_NativePointer node,
                         const Opt_HitTestMode* value)
{
}
void OnChildTouchTestImpl(Ark_NativePointer node,
                          const Opt_Callback_Array_TouchTestInfo_TouchResult* value)
{
}
void LayoutWeightImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
}
void ChainWeightImpl(Ark_NativePointer node,
                     const Opt_ChainWeightOptions* value)
{
}
void PaddingImpl(Ark_NativePointer node,
                 const Opt_Union_Padding_Length_LocalizedPadding* value)
{
}
void SafeAreaPaddingImpl(Ark_NativePointer node,
                         const Opt_Union_Padding_LengthMetrics_LocalizedPadding* value)
{
}
void MarginImpl(Ark_NativePointer node,
                const Opt_Union_Margin_Length_LocalizedMargin* value)
{
}
void BackgroundColor0Impl(Ark_NativePointer node, const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = std::make_optional<Color>(Color::FromString((value->value).value2.chars));
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        CounterModelNG::SetBackgroundColor(frameNode, color);
    } else {
        ViewAbstract::SetBackgroundColor(frameNode, color);
    }
}
void BackgroundColor1Impl(Ark_NativePointer node, const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = std::make_optional<Color>(Color::FromString((value->value).value2.chars));
    if (AceType::TypeId(frameNode) == CounterNode::TypeId()) {
        CounterModelNG::SetBackgroundColor(frameNode, color);
    } else {
        ViewAbstract::SetBackgroundColor(frameNode, color);
    }
}
void PixelRoundImpl(Ark_NativePointer node,
                    const Opt_PixelRoundPolicy* value)
{
}
void BackgroundImageSizeImpl(Ark_NativePointer node,
                             const Opt_Union_SizeOptions_ImageSize* value)
{
}
void BackgroundImagePositionImpl(Ark_NativePointer node,
                                 const Opt_Union_Position_Alignment* value)
{
}
void BackgroundEffect0Impl(Ark_NativePointer node,
                           const Opt_BackgroundEffectOptions* value)
{
}
void BackgroundEffect1Impl(Ark_NativePointer node,
                           const Opt_BackgroundEffectOptions* options,
                           const Opt_SystemAdaptiveOptions* sysOptions)
{
}
void BackgroundImageResizableImpl(Ark_NativePointer node,
                                  const Opt_ResizableOptions* value)
{
}
void ForegroundEffectImpl(Ark_NativePointer node,
                          const Opt_ForegroundEffectOptions* value)
{
}
void VisualEffectImpl(Ark_NativePointer node,
                      const Opt_VisualEffect* value)
{
}
void BackgroundFilterImpl(Ark_NativePointer node,
                          const Opt_Filter* value)
{
}
void ForegroundFilterImpl(Ark_NativePointer node,
                          const Opt_Filter* value)
{
}
void CompositingFilterImpl(Ark_NativePointer node,
                           const Opt_Filter* value)
{
}
void Opacity0Impl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
}
void Opacity1Impl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
}
void BorderImpl(Ark_NativePointer node,
                const Opt_BorderOptions* value)
{
}
void BorderStyleImpl(Ark_NativePointer node,
                     const Opt_Union_BorderStyle_EdgeStyles* value)
{
}
void BorderWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
}
void BorderColorImpl(Ark_NativePointer node,
                     const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
}
void BorderRadiusImpl(Ark_NativePointer node,
                      const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
}
void BorderImageImpl(Ark_NativePointer node,
                     const Opt_BorderImageOption* value)
{
}
void Outline0Impl(Ark_NativePointer node,
                  const Opt_OutlineOptions* value)
{
}
void Outline1Impl(Ark_NativePointer node,
                  const Opt_OutlineOptions* value)
{
}
void OutlineStyle0Impl(Ark_NativePointer node,
                       const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
{
}
void OutlineStyle1Impl(Ark_NativePointer node,
                       const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
{
}
void OutlineWidth0Impl(Ark_NativePointer node,
                       const Opt_Union_Dimension_EdgeOutlineWidths* value)
{
}
void OutlineWidth1Impl(Ark_NativePointer node,
                       const Opt_Union_Dimension_EdgeOutlineWidths* value)
{
}
void OutlineColor0Impl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
}
void OutlineColor1Impl(Ark_NativePointer node,
                       const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
}
void OutlineRadius0Impl(Ark_NativePointer node,
                        const Opt_Union_Dimension_OutlineRadiuses* value)
{
}
void OutlineRadius1Impl(Ark_NativePointer node,
                        const Opt_Union_Dimension_OutlineRadiuses* value)
{
}
void ForegroundColor0Impl(Ark_NativePointer node,
                          const Opt_Union_ResourceColor_ColoringStrategy* value)
{
}
void ForegroundColor1Impl(Ark_NativePointer node,
                          const Opt_Union_ResourceColor_ColoringStrategy* value)
{
}
void OnClick0Impl(Ark_NativePointer node,
                  const Opt_Callback_ClickEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::DisableOnClick(frameNode);
        return;
    }
    auto onClick = [callback = CallbackHelper(value->value)](GestureEvent& info) {
        const auto event = Converter::ArkClickEventSync(info);
        callback.Invoke(event.ArkValue());
    };
    NG::ViewAbstract::SetOnClick(frameNode, std::move(onClick));
}
void OnClick1Impl(Ark_NativePointer node,
                  const Opt_Callback_ClickEvent_Void* event,
                  const Opt_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(event);
    CHECK_NULL_VOID(distanceThreshold);
    if (event->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::DisableOnClick(frameNode);
        return;
    }
    auto onEvent = [callback = CallbackHelper(event->value)](GestureEvent& info) {
        const auto event = Converter::ArkClickEventSync(info);
        callback.Invoke(event.ArkValue());
    };
    if (distanceThreshold->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
        return;
    }
    auto convValue = Converter::Convert<float>(distanceThreshold->value);

    if (frameNode->GetTag() == "Span") {
        SpanModelNG::SetOnClick(reinterpret_cast<UINode *>(node), std::move(onEvent));
    } else {
        ViewAbstract::SetOnClick(frameNode, std::move(onEvent), convValue);
    }
}
void OnHoverImpl(Ark_NativePointer node,
                 const Opt_Callback_Boolean_HoverEvent_Void* value)
{
}
void OnHoverMoveImpl(Ark_NativePointer node,
                     const Opt_Callback_HoverEvent_Void* value)
{
}
void OnAccessibilityHoverImpl(Ark_NativePointer node,
                              const Opt_AccessibilityCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (!value) {
        ViewAbstract::DisableOnAccessibilityHover(frameNode);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onAccessibilityHover = [arkCallback = CallbackHelper(value->value), node = weakNode](
        bool isHover, AccessibilityHoverInfo& hoverInfo) {
        PipelineContext::SetCallBackNode(node);
        Ark_Boolean arkIsHover = Converter::ArkValue<Ark_Boolean>(isHover);
        auto event = Converter::ArkAccessibilityHoverEventSync(hoverInfo);
        arkCallback.InvokeSync(arkIsHover, event.ArkValue());
    };
    ViewAbstract::SetOnAccessibilityHover(frameNode, std::move(onAccessibilityHover));
}
void HoverEffectImpl(Ark_NativePointer node,
                     const Opt_HoverEffect* value)
{
}
void OnMouseImpl(Ark_NativePointer node,
                 const Opt_Callback_MouseEvent_Void* value)
{
}
void OnTouchImpl(Ark_NativePointer node,
                 const Opt_Callback_TouchEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::DisableOnTouch(frameNode);
        return;
    }
    auto onEvent = [callback = CallbackHelper(value->value)](TouchEventInfo& info) {
        const auto event = Converter::ArkTouchEventSync(info);
        callback.Invoke(event.ArkValue());
    };
    ViewAbstract::SetOnTouch(frameNode, std::move(onEvent));
}
void OnKeyEvent0Impl(Ark_NativePointer node,
                     const Opt_Callback_KeyEvent_Void* value)
{
}
void OnKeyEvent1Impl(Ark_NativePointer node,
                     const Opt_Callback_KeyEvent_Boolean* value)
{
}
void OnDigitalCrownImpl(Ark_NativePointer node,
                        const Opt_Callback_CrownEvent_Void* value)
{
}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     const Opt_Callback_KeyEvent_Boolean* value)
{
}
void OnKeyEventDispatchImpl(Ark_NativePointer node,
                            const Opt_Callback_KeyEvent_Boolean* value)
{
}
void OnFocusAxisEventImpl(Ark_NativePointer node,
                          const Opt_Callback_FocusAxisEvent_Void* value)
{
}
void OnAxisEventImpl(Ark_NativePointer node,
                     const Opt_Callback_AxisEvent_Void* value)
{
}
void FocusableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto arkBoolean = Converter::OptConvert<bool>(*value);
    if (!arkBoolean.has_value()) {
        return;
    }
    ViewAbstract::SetFocusable(frameNode, arkBoolean.value());
}
void NextFocusImpl(Ark_NativePointer node,
                   const Opt_FocusMovement* value)
{
}
void TabStopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
}
void OnFocusImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::DisableOnFocus(frameNode);
    }
    auto callBack = Converter::OptConvert<Callback_Void>(*value);
    if (!callBack.has_value()) {
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(callBack.value())]() {
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnFocus(frameNode, std::move(onEvent));
}
void OnBlurImpl(Ark_NativePointer node,
                const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::DisableOnBlur(frameNode);
    }
    auto callBack = Converter::OptConvert<Callback_Void>(*value);
    if (!callBack.has_value()) {
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(callBack.value())]() {
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnBlur(frameNode, std::move(onEvent));
}
void TabIndexImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<int32_t>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstract::SetTabIndex(frameNode, convValue.value());
}
void DefaultFocusImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstract::SetDefaultFocus(frameNode, convValue.value());
}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstract::SetGroupDefaultFocus(frameNode, convValue.value());
}
void FocusOnTouchImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstract::SetFocusOnTouch(frameNode, convValue.value());
}
void FocusBoxImpl(Ark_NativePointer node,
                  const Opt_FocusBoxStyle* value)
{
}
void AnimationImpl(Ark_NativePointer node,
                   const Opt_AnimateParam* value)
{
}
void Transition0Impl(Ark_NativePointer node,
                     const Opt_Union_TransitionOptions_TransitionEffect* value)
{
}
void Transition1Impl(Ark_NativePointer node,
                     const Opt_TransitionEffect* effect,
                     const Opt_TransitionFinishCallback* onFinish)
{
}
void MotionBlur0Impl(Ark_NativePointer node,
                     const Opt_MotionBlurOptions* value)
{
}
void MotionBlur1Impl(Ark_NativePointer node,
                     const Opt_MotionBlurOptions* value)
{
}
void Brightness0Impl(Ark_NativePointer node,
                     const Opt_Number* value)
{
}
void Brightness1Impl(Ark_NativePointer node,
                     const Opt_Number* value)
{
}
void Contrast0Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void Contrast1Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void Grayscale0Impl(Ark_NativePointer node,
                    const Opt_Number* value)
{
}
void Grayscale1Impl(Ark_NativePointer node,
                    const Opt_Number* value)
{
}
void ColorBlend0Impl(Ark_NativePointer node,
                     const Opt_Union_Color_String_Resource* value)
{
}
void ColorBlend1Impl(Ark_NativePointer node,
                     const Opt_Union_Color_String_Resource* value)
{
}
void Saturate0Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void Saturate1Impl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void Sepia0Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
}
void Sepia1Impl(Ark_NativePointer node,
                const Opt_Number* value)
{
}
void Invert0Impl(Ark_NativePointer node,
                 const Opt_Union_Number_InvertOptions* value)
{
}
void Invert1Impl(Ark_NativePointer node,
                 const Opt_Union_Number_InvertOptions* value)
{
}
void HueRotate0Impl(Ark_NativePointer node,
                    const Opt_Union_Number_String* value)
{
}
void HueRotate1Impl(Ark_NativePointer node,
                    const Opt_Union_Number_String* value)
{
}
void UseShadowBatching0Impl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
}
void UseShadowBatching1Impl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
}
void UseEffect0Impl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void UseEffect1Impl(Ark_NativePointer node,
                    const Opt_Boolean* useEffect,
                    const Opt_EffectType* effectType)
{
}
void UseEffect2Impl(Ark_NativePointer node,
                    const Opt_Boolean* useEffect,
                    const Opt_EffectType* effectType)
{
}
void RenderGroup0Impl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void RenderGroup1Impl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void Freeze0Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
}
void Freeze1Impl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
}
void Translate0Impl(Ark_NativePointer node,
                    const Opt_TranslateOptions* value)
{
}
void Translate1Impl(Ark_NativePointer node,
                    const Opt_TranslateOptions* value)
{
}
void Scale0Impl(Ark_NativePointer node,
                const Opt_ScaleOptions* value)
{
}
void Scale1Impl(Ark_NativePointer node,
                const Opt_ScaleOptions* value)
{
}
void GridSpanImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void GridOffsetImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
}
void Rotate0Impl(Ark_NativePointer node,
                 const Opt_RotateOptions* value)
{
}
void Rotate1Impl(Ark_NativePointer node,
                 const Opt_RotateOptions* value)
{
}
void Transform0Impl(Ark_NativePointer node,
                    const Opt_TransformationMatrix* value)
{
}
void Transform1Impl(Ark_NativePointer node,
                    const Opt_Object* value)
{
}
void OnAppearImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::DisableOnAppear(frameNode);
    }
    auto callBack = Converter::OptConvert<Callback_Void>(*value);
    if (!callBack.has_value()) {
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(callBack.value())]() {
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnAppear(frameNode, std::move(onEvent));
}
void OnDisAppearImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::DisableOnDisappear(frameNode);
    }
    auto callBack = Converter::OptConvert<Callback_Void>(*value);
    if (!callBack.has_value()) {
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(callBack.value())]() {
        arkCallback.Invoke();
    };
    ViewAbstract::SetOnDisappear(frameNode, std::move(onEvent));
}
void OnAttachImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void OnDetachImpl(Ark_NativePointer node,
                  const Opt_Callback_Void* value)
{
}
void OnAreaChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Area_Area_Void* value)
{
}
void VisibilityImpl(Ark_NativePointer node,
                    const Opt_Visibility* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::SetVisibility(frameNode, static_cast<VisibleType>(0));
        return;
    }
    auto arkVisibility = Converter::OptConvert<Ark_Visibility>(*value);
    if (!arkVisibility.has_value()) {
        ViewAbstract::SetVisibility(frameNode, static_cast<VisibleType>(0));
        return;
    }
    ViewAbstract::SetVisibility(frameNode, static_cast<VisibleType>(arkVisibility.value()));
}
void FlexGrowImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void FlexShrinkImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
}
void FlexBasisImpl(Ark_NativePointer node,
                   const Opt_Union_Number_String* value)
{
}
void AlignSelfImpl(Ark_NativePointer node,
                   const Opt_ItemAlign* value)
{
}
void DisplayPriorityImpl(Ark_NativePointer node,
                         const Opt_Number* value)
{
}
void ZIndexImpl(Ark_NativePointer node,
                const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::SetZIndex(frameNode, 0);
        return;
    }
    auto arkNumber = Converter::OptConvert<Ark_Number>(*value);
    if (!arkNumber.has_value()) {
        ViewAbstract::SetZIndex(frameNode, 0);
        return;
    }
    auto result = Converter::OptConvert<int>(arkNumber.value());
    if (result.has_value()) {
        ViewAbstract::SetZIndex(frameNode, result.value());
    }
}
void DirectionImpl(Ark_NativePointer node,
                   const Opt_Direction* value)
{
}
void AlignImpl(Ark_NativePointer node,
               const Opt_Alignment* value)
{
}
void PositionImpl(Ark_NativePointer node,
                  const Opt_Union_Position_Edges_LocalizedEdges* value)
{
}
void MarkAnchorImpl(Ark_NativePointer node,
                    const Opt_Union_Position_LocalizedPosition* value)
{
}
void OffsetImpl(Ark_NativePointer node,
                const Opt_Union_Position_Edges_LocalizedEdges* value)
{
}
void EnabledImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        ViewAbstract::SetEnabled(frameNode, true);
        return;
    }
    auto arkBoolean = Converter::OptConvert<bool>(*value);
    if (!arkBoolean.has_value()) {
        ViewAbstract::SetEnabled(frameNode, true);
        return;
    }
    ViewAbstract::SetEnabled(frameNode, arkBoolean.value());
}
void UseSizeTypeImpl(Ark_NativePointer node,
                     const Opt_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs* value)
{
}
void AlignRules0Impl(Ark_NativePointer node,
                     const Opt_AlignRuleOption* value)
{
}
void AlignRules1Impl(Ark_NativePointer node,
                     const Opt_LocalizedAlignRuleOptions* value)
{
}
void AspectRatioImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
}
void ClickEffect0Impl(Ark_NativePointer node,
                      const Opt_ClickEffect* value)
{
}
void ClickEffect1Impl(Ark_NativePointer node,
                      const Opt_ClickEffect* value)
{
}
void OnDragStartImpl(Ark_NativePointer node,
                     const Opt_Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo* value)
{
}
void OnDragEnterImpl(Ark_NativePointer node,
                     const Opt_Callback_DragEvent_String_Void* value)
{
}
void OnDragMoveImpl(Ark_NativePointer node,
                    const Opt_Callback_DragEvent_String_Void* value)
{
}
void OnDragLeaveImpl(Ark_NativePointer node,
                     const Opt_Callback_DragEvent_String_Void* value)
{
}
void OnDrop0Impl(Ark_NativePointer node,
                 const Opt_Callback_DragEvent_String_Void* value)
{
}
void OnDrop1Impl(Ark_NativePointer node,
                 const Opt_OnDragEventCallback* eventCallback,
                 const Opt_DropOptions* dropOptions)
{
}
void OnDragEndImpl(Ark_NativePointer node,
                   const Opt_Callback_DragEvent_String_Void* value)
{
}
void AllowDropImpl(Ark_NativePointer node,
                   const Opt_Array_UniformDataType* value)
{
}
void DraggableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void DragPreview0Impl(Ark_NativePointer node,
                      const Opt_Union_CustomBuilder_DragItemInfo_String* value)
{
}
void DragPreview1Impl(Ark_NativePointer node,
                      const Opt_Union_CustomBuilder_DragItemInfo_String* preview,
                      const Opt_PreviewConfiguration* config)
{
}
void OnPreDragImpl(Ark_NativePointer node,
                   const Opt_Callback_PreDragStatus_Void* value)
{
}
void LinearGradient0Impl(Ark_NativePointer node,
                         const Opt_LinearGradientOptions* value)
{
}
void LinearGradient1Impl(Ark_NativePointer node,
                         const Opt_LinearGradientOptions* value)
{
}
void SweepGradient0Impl(Ark_NativePointer node,
                        const Opt_SweepGradientOptions* value)
{
}
void SweepGradient1Impl(Ark_NativePointer node,
                        const Opt_SweepGradientOptions* value)
{
}
void RadialGradient0Impl(Ark_NativePointer node,
                         const Opt_RadialGradientOptions* value)
{
}
void RadialGradient1Impl(Ark_NativePointer node,
                         const Opt_RadialGradientOptions* value)
{
}
void MotionPathImpl(Ark_NativePointer node,
                    const Opt_MotionPathOptions* value)
{
}
void Shadow0Impl(Ark_NativePointer node,
                 const Opt_Union_ShadowOptions_ShadowStyle* value)
{
}
void Shadow1Impl(Ark_NativePointer node,
                 const Opt_Union_ShadowOptions_ShadowStyle* value)
{
}
void Clip0Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetClipEdge(frameNode, Converter::OptConvert<bool>(*value).value_or(false));
}
void Clip1Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
}
void Clip2Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
}
void ClipShape0Impl(Ark_NativePointer node,
                    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
}
void ClipShape1Impl(Ark_NativePointer node,
                    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
}
void Mask0Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
}
void Mask1Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
}
void Mask2Impl(Ark_NativePointer node,
               const Opt_ProgressMask* value)
{
}
void MaskShape0Impl(Ark_NativePointer node,
                    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
}
void MaskShape1Impl(Ark_NativePointer node,
                    const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
}
void KeyImpl(Ark_NativePointer node,
             const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstract::SetInspectorId(frameNode, convValue.value());
}
void IdImpl(Ark_NativePointer node,
            const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto id = Converter::OptConvert<std::string>(*value);
    if (!id.has_value()) {
        return;
    }
    if (id.value().empty()) {
        return;
    }
    ViewAbstract::SetInspectorId(frameNode, id.value());
}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Opt_String* value)
{
}
void GeometryTransition1Impl(Ark_NativePointer node,
                             const Opt_String* id,
                             const Opt_GeometryTransitionOptions* options)
{
}
void StateStylesImpl(Ark_NativePointer node,
                     const Opt_StateStyles* value)
{
}
void RestoreIdImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void SphericalEffect0Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
}
void SphericalEffect1Impl(Ark_NativePointer node,
                          const Opt_Number* value)
{
}
void LightUpEffect0Impl(Ark_NativePointer node,
                        const Opt_Number* value)
{
}
void LightUpEffect1Impl(Ark_NativePointer node,
                        const Opt_Number* value)
{
}
void PixelStretchEffect0Impl(Ark_NativePointer node,
                             const Opt_PixelStretchEffectOptions* value)
{
}
void PixelStretchEffect1Impl(Ark_NativePointer node,
                             const Opt_PixelStretchEffectOptions* value)
{
}
void AccessibilityGroup0Impl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto accessible = Converter::OptConvert<bool>(*value);
    if (!accessible.has_value()) {
        return;
    }
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, accessible.value());
}
void AccessibilityGroup1Impl(Ark_NativePointer node,
                             const Opt_Boolean* isGroup,
                             const Opt_AccessibilityOptions* accessibilityOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (isGroup->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto isGroupValue = Converter::OptConvert<bool>(*isGroup);
    if (!isGroupValue.has_value()) {
        return;
    }
    auto accessibilityPreferred = accessibilityOptions
        ? Converter::OptConvert<bool>(accessibilityOptions->value.accessibilityPreferred) : std::nullopt;
    ViewAbstractModelNG::SetAccessibilityGroup(frameNode, isGroupValue.value());
    ViewAbstractModelNG::SetAccessibilityTextPreferred(frameNode, accessibilityPreferred.value_or(false));
}
void AccessibilityText0Impl(Ark_NativePointer node,
                            const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstractModelNG::SetAccessibilityText(frameNode, convValue.value());
}
void AccessibilityText1Impl(Ark_NativePointer node,
                            const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto optValue = Converter::OptConvert<std::string>(*value);
    if (optValue.has_value()) {
        ViewAbstractModelNG::SetAccessibilityText(frameNode, optValue.value());
    }
}
void AccessibilityNextFocusIdImpl(Ark_NativePointer node,
                                  const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag != InteropTag::INTEROP_TAG_STRING) {
        return;
    }
    auto nextFocusId = Converter::OptConvert<std::string>(*value);
    if (!nextFocusId.has_value()) {
        return;
    }
    ViewAbstractModelNG::SetAccessibilityNextFocusId(frameNode, nextFocusId.value());
}
void AccessibilityDefaultFocusImpl(Ark_NativePointer node,
                                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    bool isFocus = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        isFocus = Converter::Convert<bool>(value->value);
    }
    ViewAbstractModelNG::SetAccessibilityDefaultFocus(frameNode, isFocus);
}
void AccessibilityUseSamePageImpl(Ark_NativePointer node,
                                  const Opt_AccessibilitySamePageMode* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto pageMode = AccessibilityUtils::GetPageModeType(static_cast<int32_t>(value->value));
    // ViewAbstractModelNG::SetAccessibilityUseSamePage(pageMode);
}
void AccessibilityScrollTriggerableImpl(Ark_NativePointer node,
                                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    bool scrollTriggerable = false;
    bool resetValue = false;
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        resetValue = true;
    } else  {
        scrollTriggerable = Converter::Convert<bool>(value->value);
    }
    ViewAbstractModelNG::SetAccessibilityScrollTriggerable(frameNode, scrollTriggerable, resetValue);
}
void AccessibilityRoleImpl(Ark_NativePointer node,
                           const Opt_AccessibilityRoleType* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // bool resetValue = false;
    // auto roleType = static_cast<AccessibilityRoleType>(value->value);
    // auto role = AccessibilityUtils::GetRoleType(roleType);
    // if (role.empty()) {
    //     resetValue = true;
    // }
    // ViewAbstractModelNG::SetAccessibilityRole(role, resetValue);
}
void OnAccessibilityFocusImpl(Ark_NativePointer node,
                              const Opt_AccessibilityFocusCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if ((!value) || (value->tag == InteropTag::INTEROP_TAG_UNDEFINED)) {
        ViewAbstractModelNG::ResetOnAccessibilityFocus(frameNode);
        return;
    }

    auto weakNode = AceType::WeakClaim(frameNode);
    auto onAccessibilityFocus = [arkCallback = CallbackHelper(value->value), node = weakNode](
        bool isFocus) {
        PipelineContext::SetCallBackNode(node);
        Ark_Boolean arkIsFocus = Converter::ArkValue<Ark_Boolean>(isFocus);
        arkCallback.InvokeSync(arkIsFocus);
    };
    ViewAbstractModelNG::SetOnAccessibilityFocus(frameNode, std::move(onAccessibilityFocus));
}
void AccessibilityTextHintImpl(Ark_NativePointer node,
                               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstractModelNG::SetAccessibilityTextHint(frameNode, convValue.value());
}
void AccessibilityDescription0Impl(Ark_NativePointer node,
                                   const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstractModelNG::SetAccessibilityDescription(frameNode, convValue.value());
}
void AccessibilityDescription1Impl(Ark_NativePointer node,
                                   const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<std::string>(*value);
    if (optValue.has_value()) {
        ViewAbstractModelNG::SetAccessibilityDescription(frameNode, optValue.value());
    }
}
void AccessibilityLevelImpl(Ark_NativePointer node,
                            const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue.has_value()) {
        return;
    }
    ViewAbstractModelNG::SetAccessibilityImportance(frameNode, convValue.value());
}
void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                  const Opt_CustomNodeBuilder* value)
{
    CHECK_NULL_VOID(value);
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto builder = [callback = CallbackHelper(value->value), node]() -> RefPtr<UINode> {
        return callback.BuildSync(node);
    };
    ViewAbstractModelNG::SetAccessibilityVirtualNode(frameNode, std::move(builder));
}
void AccessibilityCheckedImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    bool checked = false;
    bool resetValue = false;
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        resetValue = true;
    }
    checked = Converter::Convert<bool>(value->value);
    ViewAbstractModelNG::SetAccessibilityChecked(frameNode, checked, resetValue);
}
void AccessibilitySelectedImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    bool selected = false;
    bool resetValue = false;
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        resetValue = true;
    }
    selected = Converter::Convert<bool>(value->value);
    ViewAbstractModelNG::SetAccessibilitySelected(frameNode, selected, resetValue);
}
void ObscuredImpl(Ark_NativePointer node,
                  const Opt_Array_ObscuredReasons* value)
{
}
void ReuseIdImpl(Ark_NativePointer node,
                 const Opt_String* value)
{
}
void ReuseImpl(Ark_NativePointer node,
               const Opt_ReuseOptions* value)
{
}
void RenderFit0Impl(Ark_NativePointer node,
                    const Opt_RenderFit* value)
{
}
void RenderFit1Impl(Ark_NativePointer node,
                    const Opt_RenderFit* value)
{
}
void GestureModifierImpl(Ark_NativePointer node,
                         const Opt_GestureModifier* value)
{
}
void BackgroundBrightness0Impl(Ark_NativePointer node,
                               const Opt_BackgroundBrightnessOptions* value)
{
}
void BackgroundBrightness1Impl(Ark_NativePointer node,
                               const Opt_BackgroundBrightnessOptions* value)
{
}
void OnGestureJudgeBeginImpl(Ark_NativePointer node,
                             const Opt_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
{
}
void OnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                        const Opt_GestureRecognizerJudgeBeginCallback* value)
{
}
void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                        const Opt_GestureRecognizerJudgeBeginCallback* callback_,
                                        const Opt_Boolean* exposeInnerGesture)
{
}
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                             const Opt_ShouldBuiltInRecognizerParallelWithCallback* value)
{
}
void MonopolizeEventsImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
}
void OnTouchInterceptImpl(Ark_NativePointer node,
                          const Opt_Callback_TouchEvent_HitTestMode* value)
{
}
void OnSizeChangeImpl(Ark_NativePointer node,
                      const Opt_SizeChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto callBack = Converter::OptConvert<SizeChangeCallback>(*value);
    if (!callBack.has_value()) {
        return;
    }
    auto onSizeChange = [callback = CallbackHelper(callBack.value())](const RectF &oldRect, const RectF &newRect) {
        Ark_SizeOptions oldSize;
        oldSize.width = Converter::ArkValue<Opt_Length>(oldRect.Width());
        oldSize.height = Converter::ArkValue<Opt_Length>(oldRect.Height());
        Ark_SizeOptions newSize;
        newSize.width = Converter::ArkValue<Opt_Length>(newRect.Width());
        newSize.height = Converter::ArkValue<Opt_Length>(newRect.Height());
        callback.Invoke(oldSize, newSize);
    };
    ViewAbstract::SetOnSizeChanged(frameNode, std::move(onSizeChange));
}
void AccessibilityFocusDrawLevelImpl(Ark_NativePointer node,
                                     const Opt_FocusDrawLevel* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // auto drawLevel = AccessibilityUtils::GetFocusDrawLevel(static_cast<int32_t>(value->value));
    // if (drawLevel == -1) {
    //     drawLevel = 0;
    // }
    // ViewAbstractModelNG::SetAccessibilityFocusDrawLevel(frameNode, drawLevel);
}
void CustomPropertyImpl(Ark_NativePointer node,
                        const Opt_String* name,
                        const Opt_Object* value)
{
}
void ExpandSafeAreaImpl(Ark_NativePointer node,
                        const Opt_Array_SafeAreaType* types,
                        const Opt_Array_SafeAreaEdge* edges)
{
}
void BackgroundImpl(Ark_NativePointer node,
                    const Opt_CustomNodeBuilder* builder,
                    const Opt_Literal_Alignment_align* options)
{
}
void BackgroundImage0Impl(Ark_NativePointer node,
                          const Opt_Union_ResourceStr_PixelMap* src,
                          const Opt_ImageRepeat* repeat)
{
}
void BackgroundImage1Impl(Ark_NativePointer node,
                          const Opt_Union_ResourceStr_PixelMap* src,
                          const Opt_BackgroundImageOptions* options)
{
}
void BackgroundBlurStyle0Impl(Ark_NativePointer node,
                              const Opt_BlurStyle* value,
                              const Opt_BackgroundBlurStyleOptions* options)
{
}
void BackgroundBlurStyle1Impl(Ark_NativePointer node,
                              const Opt_BlurStyle* style,
                              const Opt_BackgroundBlurStyleOptions* options,
                              const Opt_SystemAdaptiveOptions* sysOptions)
{
}
void ForegroundBlurStyle0Impl(Ark_NativePointer node,
                              const Opt_BlurStyle* value,
                              const Opt_ForegroundBlurStyleOptions* options)
{
}
void ForegroundBlurStyle1Impl(Ark_NativePointer node,
                              const Opt_BlurStyle* style,
                              const Opt_ForegroundBlurStyleOptions* options,
                              const Opt_SystemAdaptiveOptions* sysOptions)
{
}
void FocusScopeId0Impl(Ark_NativePointer node,
                       const Opt_String* id,
                       const Opt_Boolean* isGroup)
{
}
void FocusScopeId1Impl(Ark_NativePointer node,
                       const Opt_String* id,
                       const Opt_Boolean* isGroup,
                       const Opt_Boolean* arrowStepOut)
{
}
void FocusScopePriorityImpl(Ark_NativePointer node,
                            const Opt_String* scopeId,
                            const Opt_FocusPriority* priority)
{
}
void GestureImpl(Ark_NativePointer node,
                 const Opt_GestureType* gesture,
                 const Opt_GestureMask* mask)
{
}
void PriorityGestureImpl(Ark_NativePointer node,
                         const Opt_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
}
void ParallelGestureImpl(Ark_NativePointer node,
                         const Opt_GestureType* gesture,
                         const Opt_GestureMask* mask)
{
}
void Blur0Impl(Ark_NativePointer node,
               const Opt_Number* value,
               const Opt_BlurOptions* options)
{
}
void Blur1Impl(Ark_NativePointer node,
               const Opt_Number* blurRadius,
               const Opt_BlurOptions* options,
               const Opt_SystemAdaptiveOptions* sysOptions)
{
}
void LinearGradientBlur0Impl(Ark_NativePointer node,
                             const Opt_Number* value,
                             const Opt_LinearGradientBlurOptions* options)
{
}
void LinearGradientBlur1Impl(Ark_NativePointer node,
                             const Opt_Number* blurRadius,
                             const Opt_LinearGradientBlurOptions* options)
{
}
void SystemBarEffectImpl(Ark_NativePointer node)
{
}
void BackdropBlur0Impl(Ark_NativePointer node,
                       const Opt_Number* value,
                       const Opt_BlurOptions* options)
{
}
void BackdropBlur1Impl(Ark_NativePointer node,
                       const Opt_Number* radius,
                       const Opt_BlurOptions* options,
                       const Opt_SystemAdaptiveOptions* sysOptions)
{
}
void SharedTransitionImpl(Ark_NativePointer node,
                          const Opt_String* id,
                          const Opt_sharedTransitionOptions* options)
{
}
void ChainModeImpl(Ark_NativePointer node,
                   const Opt_Axis* direction,
                   const Opt_ChainStyle* style)
{
}
void DragPreviewOptionsImpl(Ark_NativePointer node,
                            const Opt_DragPreviewOptions* value,
                            const Opt_DragInteractionOptions* options)
{
}
void OverlayImpl(Ark_NativePointer node,
                 const Opt_Union_String_CustomBuilder_ComponentContent* value,
                 const Opt_OverlayOptions* options)
{
}
void BlendMode0Impl(Ark_NativePointer node,
                    const Opt_BlendMode* value,
                    const Opt_BlendApplyType* type)
{
}
void BlendMode1Impl(Ark_NativePointer node,
                    const Opt_BlendMode* mode,
                    const Opt_BlendApplyType* type)
{
}
void AdvancedBlendModeImpl(Ark_NativePointer node,
                           const Opt_Union_BlendMode_Blender* effect,
                           const Opt_BlendApplyType* type)
{
}
void BindTipsImpl(Ark_NativePointer node,
                  const Opt_TipsMessageType* message,
                  const Opt_TipsOptions* options)
{
}
void BindPopupImpl(Ark_NativePointer node,
                   const Opt_Boolean* show,
                   const Opt_Union_PopupOptions_CustomPopupOptions* popup)
{
}
void BindMenu0Impl(Ark_NativePointer node,
                   const Opt_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
}
void BindMenu1Impl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const Opt_Union_Array_MenuElement_CustomBuilder* content,
                   const Opt_MenuOptions* options)
{
}
void BindContextMenu0Impl(Ark_NativePointer node,
                          const Opt_CustomNodeBuilder* content,
                          const Opt_ResponseType* responseType,
                          const Opt_ContextMenuOptions* options)
{
}
void BindContextMenu1Impl(Ark_NativePointer node,
                          const Opt_Boolean* isShown,
                          const Opt_CustomNodeBuilder* content,
                          const Opt_ContextMenuOptions* options)
{
}
void BindContentCover0Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const Opt_CustomNodeBuilder* builder,
                           const Opt_ModalTransition* type)
{
}
void BindContentCover1Impl(Ark_NativePointer node,
                           const Opt_Boolean* isShow,
                           const Opt_CustomNodeBuilder* builder,
                           const Opt_ContentCoverOptions* options)
{
}
void BindSheetImpl(Ark_NativePointer node,
                   const Opt_Boolean* isShow,
                   const Opt_CustomNodeBuilder* builder,
                   const Opt_SheetOptions* options)
{
}
void OnVisibleAreaChangeImpl(Ark_NativePointer node,
                             const Opt_Array_Number* ratios,
                             const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(ratios);
    CHECK_NULL_VOID(event);
    if (ratios->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    if (event->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto rawRatioVec = Converter::OptConvert<std::vector<float>>(*ratios);
    if (!rawRatioVec.has_value()) {
        return;
    }
    auto callBack = Converter::OptConvert<VisibleAreaChangeCallback>(*event);
    if (!callBack.has_value()) {
        return;
    }
    if (!callBack.has_value()) {
        return;
    }
    std::vector<float> floatArray = rawRatioVec.value();;
    size_t size = floatArray.size();
    std::vector<double> ratioVec;
    for (size_t i = 0; i < size; i++) {
        double ratio = static_cast<double>(floatArray[i]);
        if (LessOrEqual(ratio, VISIBLE_RATIO_MIN)) {
            ratio = VISIBLE_RATIO_MIN;
        }

        if (GreatOrEqual(ratio, VISIBLE_RATIO_MAX)) {
            ratio = VISIBLE_RATIO_MAX;
        }
        ratioVec.push_back(ratio);
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onVisibleAreaChange =
        [arkCallback = CallbackHelper(callBack.value()), node = weakNode](bool visible, double ratio) {
            Ark_Boolean isExpanding = Converter::ArkValue<Ark_Boolean>(visible);
            Ark_Number currentRatio = Converter::ArkValue<Ark_Number>(static_cast<float>(ratio));
            PipelineContext::SetCallBackNode(node);
            arkCallback.Invoke(isExpanding, currentRatio);
        };
    ViewAbstract::SetOnVisibleChange(frameNode, std::move(onVisibleAreaChange), ratioVec);
}
void OnVisibleAreaApproximateChangeImpl(Ark_NativePointer node,
                                        const Opt_VisibleAreaEventOptions* options,
                                        const Opt_VisibleAreaChangeCallback* event)
{
}
void KeyboardShortcutImpl(Ark_NativePointer node,
                          const Opt_Union_String_FunctionKey* value,
                          const Opt_Array_ModifierKey* keys,
                          const Opt_Callback_Void* action)
{
}
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::ConstructImpl,
        CommonMethodModifier::Width0Impl,
        CommonMethodModifier::Width1Impl,
        CommonMethodModifier::Height0Impl,
        CommonMethodModifier::Height1Impl,
        CommonMethodModifier::DrawModifierImpl,
        CommonMethodModifier::ResponseRegionImpl,
        CommonMethodModifier::MouseResponseRegionImpl,
        CommonMethodModifier::SizeImpl,
        CommonMethodModifier::ConstraintSizeImpl,
        CommonMethodModifier::TouchableImpl,
        CommonMethodModifier::HitTestBehaviorImpl,
        CommonMethodModifier::OnChildTouchTestImpl,
        CommonMethodModifier::LayoutWeightImpl,
        CommonMethodModifier::ChainWeightImpl,
        CommonMethodModifier::PaddingImpl,
        CommonMethodModifier::SafeAreaPaddingImpl,
        CommonMethodModifier::MarginImpl,
        CommonMethodModifier::BackgroundColor0Impl,
        CommonMethodModifier::BackgroundColor1Impl,
        CommonMethodModifier::PixelRoundImpl,
        CommonMethodModifier::BackgroundImageSizeImpl,
        CommonMethodModifier::BackgroundImagePositionImpl,
        CommonMethodModifier::BackgroundEffect0Impl,
        CommonMethodModifier::BackgroundEffect1Impl,
        CommonMethodModifier::BackgroundImageResizableImpl,
        CommonMethodModifier::ForegroundEffectImpl,
        CommonMethodModifier::VisualEffectImpl,
        CommonMethodModifier::BackgroundFilterImpl,
        CommonMethodModifier::ForegroundFilterImpl,
        CommonMethodModifier::CompositingFilterImpl,
        CommonMethodModifier::Opacity0Impl,
        CommonMethodModifier::Opacity1Impl,
        CommonMethodModifier::BorderImpl,
        CommonMethodModifier::BorderStyleImpl,
        CommonMethodModifier::BorderWidthImpl,
        CommonMethodModifier::BorderColorImpl,
        CommonMethodModifier::BorderRadiusImpl,
        CommonMethodModifier::BorderImageImpl,
        CommonMethodModifier::Outline0Impl,
        CommonMethodModifier::Outline1Impl,
        CommonMethodModifier::OutlineStyle0Impl,
        CommonMethodModifier::OutlineStyle1Impl,
        CommonMethodModifier::OutlineWidth0Impl,
        CommonMethodModifier::OutlineWidth1Impl,
        CommonMethodModifier::OutlineColor0Impl,
        CommonMethodModifier::OutlineColor1Impl,
        CommonMethodModifier::OutlineRadius0Impl,
        CommonMethodModifier::OutlineRadius1Impl,
        CommonMethodModifier::ForegroundColor0Impl,
        CommonMethodModifier::ForegroundColor1Impl,
        CommonMethodModifier::OnClick0Impl,
        CommonMethodModifier::OnClick1Impl,
        CommonMethodModifier::OnHoverImpl,
        CommonMethodModifier::OnHoverMoveImpl,
        CommonMethodModifier::OnAccessibilityHoverImpl,
        CommonMethodModifier::HoverEffectImpl,
        CommonMethodModifier::OnMouseImpl,
        CommonMethodModifier::OnTouchImpl,
        CommonMethodModifier::OnKeyEvent0Impl,
        CommonMethodModifier::OnKeyEvent1Impl,
        CommonMethodModifier::OnDigitalCrownImpl,
        CommonMethodModifier::OnKeyPreImeImpl,
        CommonMethodModifier::OnKeyEventDispatchImpl,
        CommonMethodModifier::OnFocusAxisEventImpl,
        CommonMethodModifier::OnAxisEventImpl,
        CommonMethodModifier::FocusableImpl,
        CommonMethodModifier::NextFocusImpl,
        CommonMethodModifier::TabStopImpl,
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
        CommonMethodModifier::MotionBlur0Impl,
        CommonMethodModifier::MotionBlur1Impl,
        CommonMethodModifier::Brightness0Impl,
        CommonMethodModifier::Brightness1Impl,
        CommonMethodModifier::Contrast0Impl,
        CommonMethodModifier::Contrast1Impl,
        CommonMethodModifier::Grayscale0Impl,
        CommonMethodModifier::Grayscale1Impl,
        CommonMethodModifier::ColorBlend0Impl,
        CommonMethodModifier::ColorBlend1Impl,
        CommonMethodModifier::Saturate0Impl,
        CommonMethodModifier::Saturate1Impl,
        CommonMethodModifier::Sepia0Impl,
        CommonMethodModifier::Sepia1Impl,
        CommonMethodModifier::Invert0Impl,
        CommonMethodModifier::Invert1Impl,
        CommonMethodModifier::HueRotate0Impl,
        CommonMethodModifier::HueRotate1Impl,
        CommonMethodModifier::UseShadowBatching0Impl,
        CommonMethodModifier::UseShadowBatching1Impl,
        CommonMethodModifier::UseEffect0Impl,
        CommonMethodModifier::UseEffect1Impl,
        CommonMethodModifier::UseEffect2Impl,
        CommonMethodModifier::RenderGroup0Impl,
        CommonMethodModifier::RenderGroup1Impl,
        CommonMethodModifier::Freeze0Impl,
        CommonMethodModifier::Freeze1Impl,
        CommonMethodModifier::Translate0Impl,
        CommonMethodModifier::Translate1Impl,
        CommonMethodModifier::Scale0Impl,
        CommonMethodModifier::Scale1Impl,
        CommonMethodModifier::GridSpanImpl,
        CommonMethodModifier::GridOffsetImpl,
        CommonMethodModifier::Rotate0Impl,
        CommonMethodModifier::Rotate1Impl,
        CommonMethodModifier::Transform0Impl,
        CommonMethodModifier::Transform1Impl,
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
        CommonMethodModifier::ClickEffect0Impl,
        CommonMethodModifier::ClickEffect1Impl,
        CommonMethodModifier::OnDragStartImpl,
        CommonMethodModifier::OnDragEnterImpl,
        CommonMethodModifier::OnDragMoveImpl,
        CommonMethodModifier::OnDragLeaveImpl,
        CommonMethodModifier::OnDrop0Impl,
        CommonMethodModifier::OnDrop1Impl,
        CommonMethodModifier::OnDragEndImpl,
        CommonMethodModifier::AllowDropImpl,
        CommonMethodModifier::DraggableImpl,
        CommonMethodModifier::DragPreview0Impl,
        CommonMethodModifier::DragPreview1Impl,
        CommonMethodModifier::OnPreDragImpl,
        CommonMethodModifier::LinearGradient0Impl,
        CommonMethodModifier::LinearGradient1Impl,
        CommonMethodModifier::SweepGradient0Impl,
        CommonMethodModifier::SweepGradient1Impl,
        CommonMethodModifier::RadialGradient0Impl,
        CommonMethodModifier::RadialGradient1Impl,
        CommonMethodModifier::MotionPathImpl,
        CommonMethodModifier::Shadow0Impl,
        CommonMethodModifier::Shadow1Impl,
        CommonMethodModifier::Clip0Impl,
        CommonMethodModifier::Clip1Impl,
        CommonMethodModifier::Clip2Impl,
        CommonMethodModifier::ClipShape0Impl,
        CommonMethodModifier::ClipShape1Impl,
        CommonMethodModifier::Mask0Impl,
        CommonMethodModifier::Mask1Impl,
        CommonMethodModifier::Mask2Impl,
        CommonMethodModifier::MaskShape0Impl,
        CommonMethodModifier::MaskShape1Impl,
        CommonMethodModifier::KeyImpl,
        CommonMethodModifier::IdImpl,
        CommonMethodModifier::GeometryTransition0Impl,
        CommonMethodModifier::GeometryTransition1Impl,
        CommonMethodModifier::StateStylesImpl,
        CommonMethodModifier::RestoreIdImpl,
        CommonMethodModifier::SphericalEffect0Impl,
        CommonMethodModifier::SphericalEffect1Impl,
        CommonMethodModifier::LightUpEffect0Impl,
        CommonMethodModifier::LightUpEffect1Impl,
        CommonMethodModifier::PixelStretchEffect0Impl,
        CommonMethodModifier::PixelStretchEffect1Impl,
        CommonMethodModifier::AccessibilityGroup0Impl,
        CommonMethodModifier::AccessibilityGroup1Impl,
        CommonMethodModifier::AccessibilityText0Impl,
        CommonMethodModifier::AccessibilityText1Impl,
        CommonMethodModifier::AccessibilityNextFocusIdImpl,
        CommonMethodModifier::AccessibilityDefaultFocusImpl,
        CommonMethodModifier::AccessibilityUseSamePageImpl,
        CommonMethodModifier::AccessibilityScrollTriggerableImpl,
        CommonMethodModifier::AccessibilityRoleImpl,
        CommonMethodModifier::OnAccessibilityFocusImpl,
        CommonMethodModifier::AccessibilityTextHintImpl,
        CommonMethodModifier::AccessibilityDescription0Impl,
        CommonMethodModifier::AccessibilityDescription1Impl,
        CommonMethodModifier::AccessibilityLevelImpl,
        CommonMethodModifier::AccessibilityVirtualNodeImpl,
        CommonMethodModifier::AccessibilityCheckedImpl,
        CommonMethodModifier::AccessibilitySelectedImpl,
        CommonMethodModifier::ObscuredImpl,
        CommonMethodModifier::ReuseIdImpl,
        CommonMethodModifier::ReuseImpl,
        CommonMethodModifier::RenderFit0Impl,
        CommonMethodModifier::RenderFit1Impl,
        CommonMethodModifier::GestureModifierImpl,
        CommonMethodModifier::BackgroundBrightness0Impl,
        CommonMethodModifier::BackgroundBrightness1Impl,
        CommonMethodModifier::OnGestureJudgeBeginImpl,
        CommonMethodModifier::OnGestureRecognizerJudgeBegin0Impl,
        CommonMethodModifier::OnGestureRecognizerJudgeBegin1Impl,
        CommonMethodModifier::ShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::MonopolizeEventsImpl,
        CommonMethodModifier::OnTouchInterceptImpl,
        CommonMethodModifier::OnSizeChangeImpl,
        CommonMethodModifier::AccessibilityFocusDrawLevelImpl,
        CommonMethodModifier::CustomPropertyImpl,
        CommonMethodModifier::ExpandSafeAreaImpl,
        CommonMethodModifier::BackgroundImpl,
        CommonMethodModifier::BackgroundImage0Impl,
        CommonMethodModifier::BackgroundImage1Impl,
        CommonMethodModifier::BackgroundBlurStyle0Impl,
        CommonMethodModifier::BackgroundBlurStyle1Impl,
        CommonMethodModifier::ForegroundBlurStyle0Impl,
        CommonMethodModifier::ForegroundBlurStyle1Impl,
        CommonMethodModifier::FocusScopeId0Impl,
        CommonMethodModifier::FocusScopeId1Impl,
        CommonMethodModifier::FocusScopePriorityImpl,
        CommonMethodModifier::GestureImpl,
        CommonMethodModifier::PriorityGestureImpl,
        CommonMethodModifier::ParallelGestureImpl,
        CommonMethodModifier::Blur0Impl,
        CommonMethodModifier::Blur1Impl,
        CommonMethodModifier::LinearGradientBlur0Impl,
        CommonMethodModifier::LinearGradientBlur1Impl,
        CommonMethodModifier::SystemBarEffectImpl,
        CommonMethodModifier::BackdropBlur0Impl,
        CommonMethodModifier::BackdropBlur1Impl,
        CommonMethodModifier::SharedTransitionImpl,
        CommonMethodModifier::ChainModeImpl,
        CommonMethodModifier::DragPreviewOptionsImpl,
        CommonMethodModifier::OverlayImpl,
        CommonMethodModifier::BlendMode0Impl,
        CommonMethodModifier::BlendMode1Impl,
        CommonMethodModifier::AdvancedBlendModeImpl,
        CommonMethodModifier::BindTipsImpl,
        CommonMethodModifier::BindPopupImpl,
        CommonMethodModifier::BindMenu0Impl,
        CommonMethodModifier::BindMenu1Impl,
        CommonMethodModifier::BindContextMenu0Impl,
        CommonMethodModifier::BindContextMenu1Impl,
        CommonMethodModifier::BindContentCover0Impl,
        CommonMethodModifier::BindContentCover1Impl,
        CommonMethodModifier::BindSheetImpl,
        CommonMethodModifier::OnVisibleAreaChangeImpl,
        CommonMethodModifier::OnVisibleAreaApproximateChangeImpl,
        CommonMethodModifier::KeyboardShortcutImpl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
