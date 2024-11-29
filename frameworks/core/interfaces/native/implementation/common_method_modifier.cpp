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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonMethodModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
void WidthImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetWidth(frameNode, convValue);
}
void HeightImpl(Ark_NativePointer node,
                const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetHeight(frameNode, convValue);
}
void DrawModifierImpl(Ark_NativePointer node,
                      const Opt_DrawModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
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
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetSize(frameNode, convValue);
}
void ConstraintSizeImpl(Ark_NativePointer node,
                        const Ark_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetConstraintSize(frameNode, convValue);
}
void TouchableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetTouchable(frameNode, convValue);
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
                          const Callback_Array_TouchTestInfo_TouchResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
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
void ChainWeightImpl(Ark_NativePointer node,
                     const Ark_ChainWeightOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetChainWeight(frameNode, convValue);
}
void PaddingImpl(Ark_NativePointer node,
                 const Ark_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetPadding(frameNode, convValue);
}
void SafeAreaPaddingImpl(Ark_NativePointer node,
                         const Ark_Union_Padding_LengthMetrics_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetSafeAreaPadding(frameNode, convValue);
}
void MarginImpl(Ark_NativePointer node,
                const Ark_Union_Margin_Length_LocalizedMargin* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetMargin(frameNode, convValue);
}
void BackgroundColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetBackgroundColor(frameNode, convValue);
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
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetForegroundColor(frameNode, convValue);
}
void OnClick0Impl(Ark_NativePointer node,
                  const Callback_ClickEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnClick0(frameNode, convValue);
}
void OnClick1Impl(Ark_NativePointer node,
                  const Callback_ClickEvent_Void* event,
                  const Ark_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(event);
    //auto convValue = Converter::OptConvert<type>(event); // for enums
    //CommonMethodModelNG::SetOnClick1(frameNode, convValue);
}
void OnHoverImpl(Ark_NativePointer node,
                 const Callback_Boolean_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnHover(frameNode, convValue);
}
void OnAccessibilityHoverImpl(Ark_NativePointer node,
                              const AccessibilityCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
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
                 const Callback_MouseEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnMouse(frameNode, convValue);
}
void OnTouchImpl(Ark_NativePointer node,
                 const Callback_TouchEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnTouch(frameNode, convValue);
}
void OnKeyEventImpl(Ark_NativePointer node,
                    const Callback_KeyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnKeyEvent(frameNode, convValue);
}
void OnKeyPreImeImpl(Ark_NativePointer node,
                     const Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnKeyPreIme(frameNode, convValue);
}
void FocusableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetFocusable(frameNode, convValue);
}
void TabStopImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetTabStop(frameNode, convValue);
}
void OnFocusImpl(Ark_NativePointer node,
                 const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnFocus(frameNode, convValue);
}
void OnBlurImpl(Ark_NativePointer node,
                const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
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
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetDefaultFocus(frameNode, convValue);
}
void GroupDefaultFocusImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetGroupDefaultFocus(frameNode, convValue);
}
void FocusOnTouchImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
                     const Opt_TransitionFinishCallback* onFinish)
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
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetUseShadowBatching(frameNode, convValue);
}
void UseEffect0Impl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetUseEffect0(frameNode, convValue);
}
void UseEffect1Impl(Ark_NativePointer node,
                    Ark_Boolean useEffect,
                    Ark_EffectType effectType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(useEffect);
    //auto convValue = Converter::OptConvert<type>(useEffect); // for enums
    //CommonMethodModelNG::SetUseEffect1(frameNode, convValue);
}
void RenderGroupImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetRenderGroup(frameNode, convValue);
}
void FreezeImpl(Ark_NativePointer node,
                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnAppear(frameNode, convValue);
}
void OnDisAppearImpl(Ark_NativePointer node,
                     const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDisAppear(frameNode, convValue);
}
void OnAttachImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnAttach(frameNode, convValue);
}
void OnDetachImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDetach(frameNode, convValue);
}
void OnAreaChangeImpl(Ark_NativePointer node,
                      const Callback_Area_Area_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnAreaChange(frameNode, convValue);
}
void VisibilityImpl(Ark_NativePointer node,
                    Ark_Visibility value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetVisibility(frameNode, convValue);
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
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetPosition(frameNode, convValue);
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
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOffset(frameNode, convValue);
}
void EnabledImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetEnabled(frameNode, convValue);
}
void UseSizeTypeImpl(Ark_NativePointer node,
                     const Ark_Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs* value)
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
                     const Ark_Union_ClickEffect_Null* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetClickEffect(frameNode, convValue);
}
void OnDragStartImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragStart(frameNode, convValue);
}
void OnDragEnterImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragEnter(frameNode, convValue);
}
void OnDragMoveImpl(Ark_NativePointer node,
                    const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragMove(frameNode, convValue);
}
void OnDragLeaveImpl(Ark_NativePointer node,
                     const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragLeave(frameNode, convValue);
}
void OnDropImpl(Ark_NativePointer node,
                const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDrop(frameNode, convValue);
}
void OnDragEndImpl(Ark_NativePointer node,
                   const Callback_DragEvent_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnDragEnd(frameNode, convValue);
}
void AllowDropImpl(Ark_NativePointer node,
                   const Ark_Union_Array_UniformDataType_Null* value)
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
                   const Callback_PreDragStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
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
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetRadialGradient(frameNode, convValue);
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
               const Ark_ProgressMask* value)
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
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetKey(frameNode, convValue);
}
void IdImpl(Ark_NativePointer node,
            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetId(frameNode, convValue);
}
void GeometryTransition0Impl(Ark_NativePointer node,
                             const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
void AccessibilityGroup0Impl(Ark_NativePointer node,
                             Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetAccessibilityGroup0(frameNode, convValue);
}
void AccessibilityGroup1Impl(Ark_NativePointer node,
                             Ark_Boolean isGroup,
                             const Ark_AccessibilityOptions* accessibilityOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isGroup);
    //auto convValue = Converter::OptConvert<type>(isGroup); // for enums
    //CommonMethodModelNG::SetAccessibilityGroup1(frameNode, convValue);
}
void AccessibilityText0Impl(Ark_NativePointer node,
                            const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityTextHint(frameNode, convValue);
}
void AccessibilityDescription0Impl(Ark_NativePointer node,
                                   const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
    auto convValue = Converter::Convert<std::string>(*value);
    //CommonMethodModelNG::SetAccessibilityLevel(frameNode, convValue);
}
void AccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                  const Callback_Any* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetAccessibilityVirtualNode(frameNode, convValue);
}
void AccessibilityCheckedImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetAccessibilityChecked(frameNode, convValue);
}
void AccessibilitySelectedImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetAccessibilitySelected(frameNode, convValue);
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
                         const Ark_GestureModifier* value)
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
                             const Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnGestureJudgeBegin(frameNode, convValue);
}
void OnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                        const GestureRecognizerJudgeBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnGestureRecognizerJudgeBegin0(frameNode, convValue);
}
void OnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                        const GestureRecognizerJudgeBeginCallback* callback,
                                        Ark_Boolean exposeInnerGesture)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(callback);
    //auto convValue = Converter::OptConvert<type>(callback); // for enums
    //CommonMethodModelNG::SetOnGestureRecognizerJudgeBegin1(frameNode, convValue);
}
void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                             const ShouldBuiltInRecognizerParallelWithCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetShouldBuiltInRecognizerParallelWith(frameNode, convValue);
}
void MonopolizeEventsImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CommonMethodModelNG::SetMonopolizeEvents(frameNode, convValue);
}
void OnTouchInterceptImpl(Ark_NativePointer node,
                          const Callback_TouchEvent_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CommonMethodModelNG::SetOnTouchIntercept(frameNode, convValue);
}
void OnSizeChangeImpl(Ark_NativePointer node,
                      const SizeChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
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
                    const Callback_Any* builder,
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
void FocusScopeId0Impl(Ark_NativePointer node,
                       const Ark_String* id,
                       const Opt_Boolean* isGroup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetFocusScopeId0(frameNode, convValue);
}
void FocusScopeId1Impl(Ark_NativePointer node,
                       const Ark_String* id,
                       const Opt_Boolean* isGroup,
                       const Opt_Boolean* arrowStepOut)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetFocusScopeId1(frameNode, convValue);
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
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetSharedTransition(frameNode, convValue);
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
                          const Callback_Any* content,
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
                          const Callback_Any* content,
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
                           const Callback_Any* builder,
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
                           const Callback_Any* builder,
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
                   const Callback_Any* builder,
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
                             const VisibleAreaChangeCallback* event)
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
                          const Opt_Callback_Void* action)
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
        CommonMethodModifier::ConstructImpl,
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
        CommonMethodModifier::ChainWeightImpl,
        CommonMethodModifier::PaddingImpl,
        CommonMethodModifier::SafeAreaPaddingImpl,
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
        CommonMethodModifier::UseEffect0Impl,
        CommonMethodModifier::UseEffect1Impl,
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
        CommonMethodModifier::AccessibilityGroup0Impl,
        CommonMethodModifier::AccessibilityGroup1Impl,
        CommonMethodModifier::AccessibilityText0Impl,
        CommonMethodModifier::AccessibilityText1Impl,
        CommonMethodModifier::AccessibilityTextHintImpl,
        CommonMethodModifier::AccessibilityDescription0Impl,
        CommonMethodModifier::AccessibilityDescription1Impl,
        CommonMethodModifier::AccessibilityLevelImpl,
        CommonMethodModifier::AccessibilityVirtualNodeImpl,
        CommonMethodModifier::AccessibilityCheckedImpl,
        CommonMethodModifier::AccessibilitySelectedImpl,
        CommonMethodModifier::ObscuredImpl,
        CommonMethodModifier::ReuseIdImpl,
        CommonMethodModifier::RenderFitImpl,
        CommonMethodModifier::GestureModifierImpl,
        CommonMethodModifier::BackgroundBrightnessImpl,
        CommonMethodModifier::OnGestureJudgeBeginImpl,
        CommonMethodModifier::OnGestureRecognizerJudgeBegin0Impl,
        CommonMethodModifier::OnGestureRecognizerJudgeBegin1Impl,
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
        CommonMethodModifier::FocusScopeId0Impl,
        CommonMethodModifier::FocusScopeId1Impl,
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
