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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CommonMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void SetWidthImpl(Ark_NativePointer node,
                  const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetWidth(frameNode, convValue);
}
void SetHeightImpl(Ark_NativePointer node,
                   const Opt_Union_Length_LayoutPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetHeight(frameNode, convValue);
}
void SetDrawModifierImpl(Ark_NativePointer node,
                         const Opt_DrawModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDrawModifier(frameNode, convValue);
}
void SetResponseRegionImpl(Ark_NativePointer node,
                           const Opt_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetResponseRegion(frameNode, convValue);
}
void SetMouseResponseRegionImpl(Ark_NativePointer node,
                                const Opt_Union_Array_Rectangle_Rectangle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMouseResponseRegion(frameNode, convValue);
}
void SetSizeImpl(Ark_NativePointer node,
                 const Opt_SizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSize(frameNode, convValue);
}
void SetConstraintSizeImpl(Ark_NativePointer node,
                           const Opt_ConstraintSizeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetConstraintSize(frameNode, convValue);
}
void SetHitTestBehaviorImpl(Ark_NativePointer node,
                            const Opt_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetHitTestBehavior(frameNode, convValue);
}
void SetOnChildTouchTestImpl(Ark_NativePointer node,
                             const Opt_Callback_Array_TouchTestInfo_TouchResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnChildTouchTest(frameNode, convValue);
}
void SetLayoutWeightImpl(Ark_NativePointer node,
                         const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetLayoutWeight(frameNode, convValue);
}
void SetChainWeightImpl(Ark_NativePointer node,
                        const Opt_ChainWeightOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetChainWeight(frameNode, convValue);
}
void SetPaddingImpl(Ark_NativePointer node,
                    const Opt_Union_Padding_Length_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetPadding(frameNode, convValue);
}
void SetSafeAreaPaddingImpl(Ark_NativePointer node,
                            const Opt_Union_Padding_LengthMetrics_LocalizedPadding* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSafeAreaPadding(frameNode, convValue);
}
void SetMarginImpl(Ark_NativePointer node,
                   const Opt_Union_Margin_Length_LocalizedMargin* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMargin(frameNode, convValue);
}
void SetBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundColor(frameNode, convValue);
}
void SetPixelRoundImpl(Ark_NativePointer node,
                       const Opt_PixelRoundPolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetPixelRound(frameNode, convValue);
}
void SetBackgroundImageSizeImpl(Ark_NativePointer node,
                                const Opt_Union_SizeOptions_ImageSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundImageSize(frameNode, convValue);
}
void SetBackgroundImagePositionImpl(Ark_NativePointer node,
                                    const Opt_Union_Position_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundImagePosition(frameNode, convValue);
}
void SetBackgroundEffect0Impl(Ark_NativePointer node,
                              const Opt_BackgroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundEffect0(frameNode, convValue);
}
void SetBackgroundImageResizableImpl(Ark_NativePointer node,
                                     const Opt_ResizableOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundImageResizable(frameNode, convValue);
}
void SetForegroundEffectImpl(Ark_NativePointer node,
                             const Opt_ForegroundEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetForegroundEffect(frameNode, convValue);
}
void SetVisualEffectImpl(Ark_NativePointer node,
                         const Opt_uiEffect_VisualEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetVisualEffect(frameNode, convValue);
}
void SetBackgroundFilterImpl(Ark_NativePointer node,
                             const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundFilter(frameNode, convValue);
}
void SetForegroundFilterImpl(Ark_NativePointer node,
                             const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetForegroundFilter(frameNode, convValue);
}
void SetCompositingFilterImpl(Ark_NativePointer node,
                              const Opt_uiEffect_Filter* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetCompositingFilter(frameNode, convValue);
}
void SetOpacityImpl(Ark_NativePointer node,
                    const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOpacity(frameNode, convValue);
}
void SetBorderImpl(Ark_NativePointer node,
                   const Opt_BorderOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorder(frameNode, convValue);
}
void SetBorderStyleImpl(Ark_NativePointer node,
                        const Opt_Union_BorderStyle_EdgeStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorderStyle(frameNode, convValue);
}
void SetBorderWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Length_EdgeWidths_LocalizedEdgeWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorderWidth(frameNode, convValue);
}
void SetBorderColorImpl(Ark_NativePointer node,
                        const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorderColor(frameNode, convValue);
}
void SetBorderRadiusImpl(Ark_NativePointer node,
                         const Opt_Union_Length_BorderRadiuses_LocalizedBorderRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorderRadius(frameNode, convValue);
}
void SetBorderImageImpl(Ark_NativePointer node,
                        const Opt_BorderImageOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBorderImage(frameNode, convValue);
}
void SetOutlineImpl(Ark_NativePointer node,
                    const Opt_OutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutline(frameNode, convValue);
}
void SetOutlineStyleImpl(Ark_NativePointer node,
                         const Opt_Union_OutlineStyle_EdgeOutlineStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutlineStyle(frameNode, convValue);
}
void SetOutlineWidthImpl(Ark_NativePointer node,
                         const Opt_Union_Dimension_EdgeOutlineWidths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutlineWidth(frameNode, convValue);
}
void SetOutlineColorImpl(Ark_NativePointer node,
                         const Opt_Union_ResourceColor_EdgeColors_LocalizedEdgeColors* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutlineColor(frameNode, convValue);
}
void SetOutlineRadiusImpl(Ark_NativePointer node,
                          const Opt_Union_Dimension_OutlineRadiuses* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOutlineRadius(frameNode, convValue);
}
void SetForegroundColorImpl(Ark_NativePointer node,
                            const Opt_Union_ResourceColor_ColoringStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetForegroundColor(frameNode, convValue);
}
void SetOnClick0Impl(Ark_NativePointer node,
                     const Opt_Callback_ClickEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnClick0(frameNode, convValue);
}
void SetOnHoverImpl(Ark_NativePointer node,
                    const Opt_Callback_Boolean_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnHover(frameNode, convValue);
}
void SetOnHoverMoveImpl(Ark_NativePointer node,
                        const Opt_Callback_HoverEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnHoverMove(frameNode, convValue);
}
void SetOnAccessibilityHoverImpl(Ark_NativePointer node,
                                 const Opt_AccessibilityCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAccessibilityHover(frameNode, convValue);
}
void SetHoverEffectImpl(Ark_NativePointer node,
                        const Opt_HoverEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetHoverEffect(frameNode, convValue);
}
void SetOnMouseImpl(Ark_NativePointer node,
                    const Opt_Callback_MouseEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnMouse(frameNode, convValue);
}
void SetOnTouchImpl(Ark_NativePointer node,
                    const Opt_Callback_TouchEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnTouch(frameNode, convValue);
}
void SetOnKeyEventImpl(Ark_NativePointer node,
                       const Opt_Callback_KeyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnKeyEvent(frameNode, convValue);
}
void SetOnDigitalCrownImpl(Ark_NativePointer node,
                           const Opt_Callback_CrownEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDigitalCrown(frameNode, convValue);
}
void SetOnKeyPreImeImpl(Ark_NativePointer node,
                        const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnKeyPreIme(frameNode, convValue);
}
void SetOnKeyEventDispatchImpl(Ark_NativePointer node,
                               const Opt_Callback_KeyEvent_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnKeyEventDispatch(frameNode, convValue);
}
void SetOnFocusAxisEventImpl(Ark_NativePointer node,
                             const Opt_Callback_FocusAxisEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnFocusAxisEvent(frameNode, convValue);
}
void SetOnAxisEventImpl(Ark_NativePointer node,
                        const Opt_Callback_AxisEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAxisEvent(frameNode, convValue);
}
void SetFocusableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFocusable(frameNode, convValue);
}
void SetNextFocusImpl(Ark_NativePointer node,
                      const Opt_FocusMovement* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetNextFocus(frameNode, convValue);
}
void SetTabStopImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTabStop(frameNode, convValue);
}
void SetOnFocusImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnFocus(frameNode, convValue);
}
void SetOnBlurImpl(Ark_NativePointer node,
                   const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnBlur(frameNode, convValue);
}
void SetTabIndexImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTabIndex(frameNode, convValue);
}
void SetDefaultFocusImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDefaultFocus(frameNode, convValue);
}
void SetGroupDefaultFocusImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetGroupDefaultFocus(frameNode, convValue);
}
void SetFocusOnTouchImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFocusOnTouch(frameNode, convValue);
}
void SetFocusBoxImpl(Ark_NativePointer node,
                     const Opt_FocusBoxStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFocusBox(frameNode, convValue);
}
void SetAnimationImpl(Ark_NativePointer node,
                      const Opt_AnimateParam* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAnimation(frameNode, convValue);
}
void SetTransition0Impl(Ark_NativePointer node,
                        const Opt_TransitionEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTransition0(frameNode, convValue);
}
void SetMotionBlurImpl(Ark_NativePointer node,
                       const Opt_MotionBlurOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMotionBlur(frameNode, convValue);
}
void SetBrightnessImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBrightness(frameNode, convValue);
}
void SetContrastImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetContrast(frameNode, convValue);
}
void SetGrayscaleImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetGrayscale(frameNode, convValue);
}
void SetColorBlendImpl(Ark_NativePointer node,
                       const Opt_Union_Color_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetColorBlend(frameNode, convValue);
}
void SetSaturateImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSaturate(frameNode, convValue);
}
void SetSepiaImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSepia(frameNode, convValue);
}
void SetInvertImpl(Ark_NativePointer node,
                   const Opt_Union_Number_InvertOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetInvert(frameNode, convValue);
}
void SetHueRotateImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetHueRotate(frameNode, convValue);
}
void SetUseShadowBatchingImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetUseShadowBatching(frameNode, convValue);
}
void SetUseEffect0Impl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetUseEffect0(frameNode, convValue);
}
void SetRenderGroupImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRenderGroup(frameNode, convValue);
}
void SetFreezeImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFreeze(frameNode, convValue);
}
void SetTranslateImpl(Ark_NativePointer node,
                      const Opt_TranslateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTranslate(frameNode, convValue);
}
void SetScaleImpl(Ark_NativePointer node,
                  const Opt_ScaleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetScale(frameNode, convValue);
}
void SetRotateImpl(Ark_NativePointer node,
                   const Opt_RotateOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRotate(frameNode, convValue);
}
void SetTransformImpl(Ark_NativePointer node,
                      const Opt_Object* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetTransform(frameNode, convValue);
}
void SetOnAppearImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAppear(frameNode, convValue);
}
void SetOnDisAppearImpl(Ark_NativePointer node,
                        const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDisAppear(frameNode, convValue);
}
void SetOnAttachImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAttach(frameNode, convValue);
}
void SetOnDetachImpl(Ark_NativePointer node,
                     const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDetach(frameNode, convValue);
}
void SetOnAreaChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Area_Area_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAreaChange(frameNode, convValue);
}
void SetVisibilityImpl(Ark_NativePointer node,
                       const Opt_Visibility* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetVisibility(frameNode, convValue);
}
void SetFlexGrowImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFlexGrow(frameNode, convValue);
}
void SetFlexShrinkImpl(Ark_NativePointer node,
                       const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFlexShrink(frameNode, convValue);
}
void SetFlexBasisImpl(Ark_NativePointer node,
                      const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetFlexBasis(frameNode, convValue);
}
void SetAlignSelfImpl(Ark_NativePointer node,
                      const Opt_ItemAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAlignSelf(frameNode, convValue);
}
void SetDisplayPriorityImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDisplayPriority(frameNode, convValue);
}
void SetZIndexImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetZIndex(frameNode, convValue);
}
void SetDirectionImpl(Ark_NativePointer node,
                      const Opt_Direction* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDirection(frameNode, convValue);
}
void SetAlignImpl(Ark_NativePointer node,
                  const Opt_Alignment* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAlign(frameNode, convValue);
}
void SetPositionImpl(Ark_NativePointer node,
                     const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetPosition(frameNode, convValue);
}
void SetMarkAnchorImpl(Ark_NativePointer node,
                       const Opt_Union_Position_LocalizedPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMarkAnchor(frameNode, convValue);
}
void SetOffsetImpl(Ark_NativePointer node,
                   const Opt_Union_Position_Edges_LocalizedEdges* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOffset(frameNode, convValue);
}
void SetEnabledImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetEnabled(frameNode, convValue);
}
void SetAlignRules0Impl(Ark_NativePointer node,
                        const Opt_AlignRuleOption* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAlignRules0(frameNode, convValue);
}
void SetAlignRules1Impl(Ark_NativePointer node,
                        const Opt_LocalizedAlignRuleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAlignRules1(frameNode, convValue);
}
void SetAspectRatioImpl(Ark_NativePointer node,
                        const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAspectRatio(frameNode, convValue);
}
void SetClickEffectImpl(Ark_NativePointer node,
                        const Opt_ClickEffect* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetClickEffect(frameNode, convValue);
}
void SetOnDragStartImpl(Ark_NativePointer node,
                        const Opt_Type_CommonMethod_onDragStart* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragStart(frameNode, convValue);
}
void SetOnDragEnterImpl(Ark_NativePointer node,
                        const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragEnter(frameNode, convValue);
}
void SetOnDragMoveImpl(Ark_NativePointer node,
                       const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragMove(frameNode, convValue);
}
void SetOnDragLeaveImpl(Ark_NativePointer node,
                        const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragLeave(frameNode, convValue);
}
void SetOnDrop0Impl(Ark_NativePointer node,
                    const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDrop0(frameNode, convValue);
}
void SetOnDragEndImpl(Ark_NativePointer node,
                      const Opt_Callback_DragEvent_Opt_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnDragEnd(frameNode, convValue);
}
void SetAllowDropImpl(Ark_NativePointer node,
                      const Opt_Array_uniformTypeDescriptor_UniformDataType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAllowDrop(frameNode, convValue);
}
void SetDraggableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDraggable(frameNode, convValue);
}
void SetDragPreview0Impl(Ark_NativePointer node,
                         const Opt_Union_CustomBuilder_DragItemInfo_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetDragPreview0(frameNode, convValue);
}
void SetOnPreDragImpl(Ark_NativePointer node,
                      const Opt_Callback_PreDragStatus_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnPreDrag(frameNode, convValue);
}
void SetLinearGradientImpl(Ark_NativePointer node,
                           const Opt_LinearGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetLinearGradient(frameNode, convValue);
}
void SetSweepGradientImpl(Ark_NativePointer node,
                          const Opt_SweepGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSweepGradient(frameNode, convValue);
}
void SetRadialGradientImpl(Ark_NativePointer node,
                           const Opt_RadialGradientOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRadialGradient(frameNode, convValue);
}
void SetMotionPathImpl(Ark_NativePointer node,
                       const Opt_MotionPathOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMotionPath(frameNode, convValue);
}
void SetShadowImpl(Ark_NativePointer node,
                   const Opt_Union_ShadowOptions_ShadowStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetShadow(frameNode, convValue);
}
void SetClipImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetClip(frameNode, convValue);
}
void SetClipShapeImpl(Ark_NativePointer node,
                      const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetClipShape(frameNode, convValue);
}
void SetMaskImpl(Ark_NativePointer node,
                 const Opt_ProgressMask* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMask(frameNode, convValue);
}
void SetMaskShapeImpl(Ark_NativePointer node,
                      const Opt_Union_CircleShape_EllipseShape_PathShape_RectShape* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMaskShape(frameNode, convValue);
}
void SetKeyImpl(Ark_NativePointer node,
                const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetKey(frameNode, convValue);
}
void SetIdImpl(Ark_NativePointer node,
               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetId(frameNode, convValue);
}
void SetGeometryTransition0Impl(Ark_NativePointer node,
                                const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetGeometryTransition0(frameNode, convValue);
}
void SetStateStylesImpl(Ark_NativePointer node,
                        const Opt_StateStyles* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetStateStyles(frameNode, convValue);
}
void SetRestoreIdImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRestoreId(frameNode, convValue);
}
void SetSphericalEffectImpl(Ark_NativePointer node,
                            const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetSphericalEffect(frameNode, convValue);
}
void SetLightUpEffectImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetLightUpEffect(frameNode, convValue);
}
void SetPixelStretchEffectImpl(Ark_NativePointer node,
                               const Opt_PixelStretchEffectOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetPixelStretchEffect(frameNode, convValue);
}
void SetAccessibilityGroup0Impl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityGroup0(frameNode, convValue);
}
void SetAccessibilityText0Impl(Ark_NativePointer node,
                               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityText0(frameNode, convValue);
}
void SetAccessibilityNextFocusIdImpl(Ark_NativePointer node,
                                     const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityNextFocusId(frameNode, convValue);
}
void SetAccessibilityDefaultFocusImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityDefaultFocus(frameNode, convValue);
}
void SetAccessibilityUseSamePageImpl(Ark_NativePointer node,
                                     const Opt_AccessibilitySamePageMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityUseSamePage(frameNode, convValue);
}
void SetAccessibilityScrollTriggerableImpl(Ark_NativePointer node,
                                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityScrollTriggerable(frameNode, convValue);
}
void SetAccessibilityText1Impl(Ark_NativePointer node,
                               const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityText1(frameNode, convValue);
}
void SetAccessibilityRoleImpl(Ark_NativePointer node,
                              const Opt_AccessibilityRoleType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityRole(frameNode, convValue);
}
void SetOnAccessibilityFocusImpl(Ark_NativePointer node,
                                 const Opt_AccessibilityFocusCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnAccessibilityFocus(frameNode, convValue);
}
void SetAccessibilityTextHintImpl(Ark_NativePointer node,
                                  const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityTextHint(frameNode, convValue);
}
void SetAccessibilityDescription0Impl(Ark_NativePointer node,
                                      const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityDescription0(frameNode, convValue);
}
void SetAccessibilityDescription1Impl(Ark_NativePointer node,
                                      const Opt_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityDescription1(frameNode, convValue);
}
void SetAccessibilityLevelImpl(Ark_NativePointer node,
                               const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityLevel(frameNode, convValue);
}
void SetAccessibilityVirtualNodeImpl(Ark_NativePointer node,
                                     const Opt_CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityVirtualNode(frameNode, convValue);
}
void SetAccessibilityCheckedImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityChecked(frameNode, convValue);
}
void SetAccessibilitySelectedImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilitySelected(frameNode, convValue);
}
void SetObscuredImpl(Ark_NativePointer node,
                     const Opt_Array_ObscuredReasons* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetObscured(frameNode, convValue);
}
void SetReuseIdImpl(Ark_NativePointer node,
                    const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetReuseId(frameNode, convValue);
}
void SetReuseImpl(Ark_NativePointer node,
                  const Opt_ReuseOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetReuse(frameNode, convValue);
}
void SetRenderFitImpl(Ark_NativePointer node,
                      const Opt_RenderFit* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetRenderFit(frameNode, convValue);
}
void SetGestureModifierImpl(Ark_NativePointer node,
                            const Opt_GestureModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetGestureModifier(frameNode, convValue);
}
void SetBackgroundBrightnessImpl(Ark_NativePointer node,
                                 const Opt_BackgroundBrightnessOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetBackgroundBrightness(frameNode, convValue);
}
void SetOnGestureJudgeBeginImpl(Ark_NativePointer node,
                                const Opt_Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnGestureJudgeBegin(frameNode, convValue);
}
void SetOnGestureRecognizerJudgeBegin0Impl(Ark_NativePointer node,
                                           const Opt_GestureRecognizerJudgeBeginCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnGestureRecognizerJudgeBegin0(frameNode, convValue);
}
void SetShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node,
                                                const Opt_ShouldBuiltInRecognizerParallelWithCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetShouldBuiltInRecognizerParallelWith(frameNode, convValue);
}
void SetMonopolizeEventsImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetMonopolizeEvents(frameNode, convValue);
}
void SetOnTouchInterceptImpl(Ark_NativePointer node,
                             const Opt_Callback_TouchEvent_HitTestMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnTouchIntercept(frameNode, convValue);
}
void SetOnSizeChangeImpl(Ark_NativePointer node,
                         const Opt_SizeChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetOnSizeChange(frameNode, convValue);
}
void SetAccessibilityFocusDrawLevelImpl(Ark_NativePointer node,
                                        const Opt_FocusDrawLevel* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CommonMethodModelNG::SetSetAccessibilityFocusDrawLevel(frameNode, convValue);
}
void SetCustomPropertyImpl(Ark_NativePointer node,
                           const Opt_String* name,
                           const Opt_Object* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(name);
    //auto convValue = Converter::OptConvert<type>(name); // for enums
    //CommonMethodModelNG::SetSetCustomProperty(frameNode, convValue);
}
void SetExpandSafeAreaImpl(Ark_NativePointer node,
                           const Opt_Array_SafeAreaType* types,
                           const Opt_Array_SafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(types);
    //auto convValue = Converter::OptConvert<type>(types); // for enums
    //CommonMethodModelNG::SetSetExpandSafeArea(frameNode, convValue);
}
void SetBackgroundImpl(Ark_NativePointer node,
                       const Opt_CustomNodeBuilder* builder,
                       const Opt_BackgroundOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(builder);
    //auto convValue = Converter::OptConvert<type>(builder); // for enums
    //CommonMethodModelNG::SetSetBackground(frameNode, convValue);
}
void SetBackgroundImage0Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap* src,
                             const Opt_ImageRepeat* repeat)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(src);
    //auto convValue = Converter::OptConvert<type>(src); // for enums
    //CommonMethodModelNG::SetSetBackgroundImage0(frameNode, convValue);
}
void SetBackgroundImage1Impl(Ark_NativePointer node,
                             const Opt_Union_ResourceStr_PixelMap* src,
                             const Opt_BackgroundImageOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(src);
    //auto convValue = Converter::OptConvert<type>(src); // for enums
    //CommonMethodModelNG::SetSetBackgroundImage1(frameNode, convValue);
}
void SetBackgroundBlurStyleImpl(Ark_NativePointer node,
                                const Opt_BlurStyle* style,
                                const Opt_BackgroundBlurStyleOptions* options,
                                const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(style);
    //auto convValue = Converter::OptConvert<type>(style); // for enums
    //CommonMethodModelNG::SetSetBackgroundBlurStyle(frameNode, convValue);
}
void SetBackgroundEffect1Impl(Ark_NativePointer node,
                              const Opt_BackgroundEffectOptions* options,
                              const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(options);
    //auto convValue = Converter::OptConvert<type>(options); // for enums
    //CommonMethodModelNG::SetSetBackgroundEffect1(frameNode, convValue);
}
void SetForegroundBlurStyleImpl(Ark_NativePointer node,
                                const Opt_BlurStyle* style,
                                const Opt_ForegroundBlurStyleOptions* options,
                                const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(style);
    //auto convValue = Converter::OptConvert<type>(style); // for enums
    //CommonMethodModelNG::SetSetForegroundBlurStyle(frameNode, convValue);
}
void SetOnClick1Impl(Ark_NativePointer node,
                     const Opt_Callback_ClickEvent_Void* event,
                     const Opt_Number* distanceThreshold)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(event);
    //auto convValue = Converter::OptConvert<type>(event); // for enums
    //CommonMethodModelNG::SetSetOnClick1(frameNode, convValue);
}
void SetFocusScopeIdImpl(Ark_NativePointer node,
                         const Opt_String* id,
                         const Opt_Boolean* isGroup,
                         const Opt_Boolean* arrowStepOut)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetSetFocusScopeId(frameNode, convValue);
}
void SetFocusScopePriorityImpl(Ark_NativePointer node,
                               const Opt_String* scopeId,
                               const Opt_FocusPriority* priority)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(scopeId);
    //auto convValue = Converter::OptConvert<type>(scopeId); // for enums
    //CommonMethodModelNG::SetSetFocusScopePriority(frameNode, convValue);
}
void SetTransition1Impl(Ark_NativePointer node,
                        const Opt_TransitionEffect* effect,
                        const Opt_TransitionFinishCallback* onFinish)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(effect);
    //auto convValue = Converter::OptConvert<type>(effect); // for enums
    //CommonMethodModelNG::SetSetTransition1(frameNode, convValue);
}
void SetGestureImpl(Ark_NativePointer node,
                    const Opt_GestureType* gesture,
                    const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetSetGesture(frameNode, convValue);
}
void SetPriorityGestureImpl(Ark_NativePointer node,
                            const Opt_GestureType* gesture,
                            const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetSetPriorityGesture(frameNode, convValue);
}
void SetParallelGestureImpl(Ark_NativePointer node,
                            const Opt_GestureType* gesture,
                            const Opt_GestureMask* mask)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(gesture);
    //auto convValue = Converter::OptConvert<type>(gesture); // for enums
    //CommonMethodModelNG::SetSetParallelGesture(frameNode, convValue);
}
void SetBlurImpl(Ark_NativePointer node,
                 const Opt_Number* blurRadius,
                 const Opt_BlurOptions* options,
                 const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(blurRadius);
    //auto convValue = Converter::OptConvert<type>(blurRadius); // for enums
    //CommonMethodModelNG::SetSetBlur(frameNode, convValue);
}
void SetLinearGradientBlurImpl(Ark_NativePointer node,
                               const Opt_Number* value,
                               const Opt_LinearGradientBlurOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetSetLinearGradientBlur(frameNode, convValue);
}
void SetSystemBarEffectImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //CommonMethodModelNG::SetSetSystemBarEffect(frameNode, convValue);
}
void SetUseEffect1Impl(Ark_NativePointer node,
                       const Opt_Boolean* useEffect,
                       const Opt_EffectType* effectType)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(useEffect);
    //auto convValue = Converter::OptConvert<type>(useEffect); // for enums
    //CommonMethodModelNG::SetSetUseEffect1(frameNode, convValue);
}
void SetBackdropBlurImpl(Ark_NativePointer node,
                         const Opt_Number* radius,
                         const Opt_BlurOptions* options,
                         const Opt_SystemAdaptiveOptions* sysOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(radius);
    //auto convValue = Converter::OptConvert<type>(radius); // for enums
    //CommonMethodModelNG::SetSetBackdropBlur(frameNode, convValue);
}
void SetSharedTransitionImpl(Ark_NativePointer node,
                             const Opt_String* id,
                             const Opt_sharedTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetSetSharedTransition(frameNode, convValue);
}
void SetChainModeImpl(Ark_NativePointer node,
                      const Opt_Axis* direction,
                      const Opt_ChainStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(direction);
    //auto convValue = Converter::OptConvert<type>(direction); // for enums
    //CommonMethodModelNG::SetSetChainMode(frameNode, convValue);
}
void SetOnDrop1Impl(Ark_NativePointer node,
                    const Opt_OnDragEventCallback* eventCallback,
                    const Opt_DropOptions* dropOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(eventCallback);
    //auto convValue = Converter::OptConvert<type>(eventCallback); // for enums
    //CommonMethodModelNG::SetSetOnDrop1(frameNode, convValue);
}
void SetDragPreview1Impl(Ark_NativePointer node,
                         const Opt_Union_CustomBuilder_DragItemInfo_String* preview,
                         const Opt_PreviewConfiguration* config)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(preview);
    //auto convValue = Converter::OptConvert<type>(preview); // for enums
    //CommonMethodModelNG::SetSetDragPreview1(frameNode, convValue);
}
void SetDragPreviewOptionsImpl(Ark_NativePointer node,
                               const Opt_DragPreviewOptions* value,
                               const Opt_DragInteractionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetSetDragPreviewOptions(frameNode, convValue);
}
void SetOverlayImpl(Ark_NativePointer node,
                    const Opt_Union_String_CustomBuilder_ComponentContent* value,
                    const Opt_OverlayOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetSetOverlay(frameNode, convValue);
}
void SetBlendModeImpl(Ark_NativePointer node,
                      const Opt_BlendMode* value,
                      const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetSetBlendMode(frameNode, convValue);
}
void SetAdvancedBlendModeImpl(Ark_NativePointer node,
                              const Opt_Union_BlendMode_Blender* effect,
                              const Opt_BlendApplyType* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(effect);
    //auto convValue = Converter::OptConvert<type>(effect); // for enums
    //CommonMethodModelNG::SetSetAdvancedBlendMode(frameNode, convValue);
}
void SetGeometryTransition1Impl(Ark_NativePointer node,
                                const Opt_String* id,
                                const Opt_GeometryTransitionOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(id);
    //auto convValue = Converter::OptConvert<type>(id); // for enums
    //CommonMethodModelNG::SetSetGeometryTransition1(frameNode, convValue);
}
void SetBindTipsImpl(Ark_NativePointer node,
                     const Opt_TipsMessageType* message,
                     const Opt_TipsOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(message);
    //auto convValue = Converter::OptConvert<type>(message); // for enums
    //CommonMethodModelNG::SetSetBindTips(frameNode, convValue);
}
void SetBindPopupImpl(Ark_NativePointer node,
                      const Opt_Boolean* show,
                      const Opt_Union_PopupOptions_CustomPopupOptions* popup)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(show);
    //auto convValue = Converter::OptConvert<type>(show); // for enums
    //CommonMethodModelNG::SetSetBindPopup(frameNode, convValue);
}
void SetBindMenu0Impl(Ark_NativePointer node,
                      const Opt_Union_Array_MenuElement_CustomBuilder* content,
                      const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //CommonMethodModelNG::SetSetBindMenu0(frameNode, convValue);
}
void SetBindMenu1Impl(Ark_NativePointer node,
                      const Opt_Boolean* isShow,
                      const Opt_Union_Array_MenuElement_CustomBuilder* content,
                      const Opt_MenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetSetBindMenu1(frameNode, convValue);
}
void SetBindContextMenu0Impl(Ark_NativePointer node,
                             const Opt_CustomNodeBuilder* content,
                             const Opt_ResponseType* responseType,
                             const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(content);
    //auto convValue = Converter::OptConvert<type>(content); // for enums
    //CommonMethodModelNG::SetSetBindContextMenu0(frameNode, convValue);
}
void SetBindContextMenu1Impl(Ark_NativePointer node,
                             const Opt_Boolean* isShown,
                             const Opt_CustomNodeBuilder* content,
                             const Opt_ContextMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShown);
    //auto convValue = Converter::OptConvert<type>(isShown); // for enums
    //CommonMethodModelNG::SetSetBindContextMenu1(frameNode, convValue);
}
void SetBindContentCover0Impl(Ark_NativePointer node,
                              const Opt_Boolean* isShow,
                              const Opt_CustomNodeBuilder* builder,
                              const Opt_ModalTransition* type)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetSetBindContentCover0(frameNode, convValue);
}
void SetBindContentCover1Impl(Ark_NativePointer node,
                              const Opt_Boolean* isShow,
                              const Opt_CustomNodeBuilder* builder,
                              const Opt_ContentCoverOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetSetBindContentCover1(frameNode, convValue);
}
void SetBindSheetImpl(Ark_NativePointer node,
                      const Opt_Boolean* isShow,
                      const Opt_CustomNodeBuilder* builder,
                      const Opt_SheetOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isShow);
    //auto convValue = Converter::OptConvert<type>(isShow); // for enums
    //CommonMethodModelNG::SetSetBindSheet(frameNode, convValue);
}
void SetOnVisibleAreaChangeImpl(Ark_NativePointer node,
                                const Opt_Array_Number* ratios,
                                const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(ratios);
    //auto convValue = Converter::OptConvert<type>(ratios); // for enums
    //CommonMethodModelNG::SetSetOnVisibleAreaChange(frameNode, convValue);
}
void SetOnVisibleAreaApproximateChangeImpl(Ark_NativePointer node,
                                           const Opt_VisibleAreaEventOptions* options,
                                           const Opt_VisibleAreaChangeCallback* event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(options);
    //auto convValue = Converter::OptConvert<type>(options); // for enums
    //CommonMethodModelNG::SetSetOnVisibleAreaApproximateChange(frameNode, convValue);
}
void SetKeyboardShortcutImpl(Ark_NativePointer node,
                             const Opt_Union_String_FunctionKey* value,
                             const Opt_Array_ModifierKey* keys,
                             const Opt_Callback_Void* action)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CommonMethodModelNG::SetSetKeyboardShortcut(frameNode, convValue);
}
void SetAccessibilityGroup1Impl(Ark_NativePointer node,
                                const Opt_Boolean* isGroup,
                                const Opt_AccessibilityOptions* accessibilityOptions)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(isGroup);
    //auto convValue = Converter::OptConvert<type>(isGroup); // for enums
    //CommonMethodModelNG::SetSetAccessibilityGroup1(frameNode, convValue);
}
void SetOnGestureRecognizerJudgeBegin1Impl(Ark_NativePointer node,
                                           const Opt_GestureRecognizerJudgeBeginCallback* callback_,
                                           const Opt_Boolean* exposeInnerGesture)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(callback_);
    //auto convValue = Converter::OptConvert<type>(callback_); // for enums
    //CommonMethodModelNG::SetSetOnGestureRecognizerJudgeBegin1(frameNode, convValue);
}
} // CommonMethodModifier
const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier()
{
    static const GENERATED_ArkUICommonMethodModifier ArkUICommonMethodModifierImpl {
        CommonMethodModifier::ConstructImpl,
        CommonMethodModifier::SetWidthImpl,
        CommonMethodModifier::SetHeightImpl,
        CommonMethodModifier::SetDrawModifierImpl,
        CommonMethodModifier::SetResponseRegionImpl,
        CommonMethodModifier::SetMouseResponseRegionImpl,
        CommonMethodModifier::SetSizeImpl,
        CommonMethodModifier::SetConstraintSizeImpl,
        CommonMethodModifier::SetHitTestBehaviorImpl,
        CommonMethodModifier::SetOnChildTouchTestImpl,
        CommonMethodModifier::SetLayoutWeightImpl,
        CommonMethodModifier::SetChainWeightImpl,
        CommonMethodModifier::SetPaddingImpl,
        CommonMethodModifier::SetSafeAreaPaddingImpl,
        CommonMethodModifier::SetMarginImpl,
        CommonMethodModifier::SetBackgroundColorImpl,
        CommonMethodModifier::SetPixelRoundImpl,
        CommonMethodModifier::SetBackgroundImageSizeImpl,
        CommonMethodModifier::SetBackgroundImagePositionImpl,
        CommonMethodModifier::SetBackgroundEffect0Impl,
        CommonMethodModifier::SetBackgroundImageResizableImpl,
        CommonMethodModifier::SetForegroundEffectImpl,
        CommonMethodModifier::SetVisualEffectImpl,
        CommonMethodModifier::SetBackgroundFilterImpl,
        CommonMethodModifier::SetForegroundFilterImpl,
        CommonMethodModifier::SetCompositingFilterImpl,
        CommonMethodModifier::SetOpacityImpl,
        CommonMethodModifier::SetBorderImpl,
        CommonMethodModifier::SetBorderStyleImpl,
        CommonMethodModifier::SetBorderWidthImpl,
        CommonMethodModifier::SetBorderColorImpl,
        CommonMethodModifier::SetBorderRadiusImpl,
        CommonMethodModifier::SetBorderImageImpl,
        CommonMethodModifier::SetOutlineImpl,
        CommonMethodModifier::SetOutlineStyleImpl,
        CommonMethodModifier::SetOutlineWidthImpl,
        CommonMethodModifier::SetOutlineColorImpl,
        CommonMethodModifier::SetOutlineRadiusImpl,
        CommonMethodModifier::SetForegroundColorImpl,
        CommonMethodModifier::SetOnClick0Impl,
        CommonMethodModifier::SetOnHoverImpl,
        CommonMethodModifier::SetOnHoverMoveImpl,
        CommonMethodModifier::SetOnAccessibilityHoverImpl,
        CommonMethodModifier::SetHoverEffectImpl,
        CommonMethodModifier::SetOnMouseImpl,
        CommonMethodModifier::SetOnTouchImpl,
        CommonMethodModifier::SetOnKeyEventImpl,
        CommonMethodModifier::SetOnDigitalCrownImpl,
        CommonMethodModifier::SetOnKeyPreImeImpl,
        CommonMethodModifier::SetOnKeyEventDispatchImpl,
        CommonMethodModifier::SetOnFocusAxisEventImpl,
        CommonMethodModifier::SetOnAxisEventImpl,
        CommonMethodModifier::SetFocusableImpl,
        CommonMethodModifier::SetNextFocusImpl,
        CommonMethodModifier::SetTabStopImpl,
        CommonMethodModifier::SetOnFocusImpl,
        CommonMethodModifier::SetOnBlurImpl,
        CommonMethodModifier::SetTabIndexImpl,
        CommonMethodModifier::SetDefaultFocusImpl,
        CommonMethodModifier::SetGroupDefaultFocusImpl,
        CommonMethodModifier::SetFocusOnTouchImpl,
        CommonMethodModifier::SetFocusBoxImpl,
        CommonMethodModifier::SetAnimationImpl,
        CommonMethodModifier::SetTransition0Impl,
        CommonMethodModifier::SetMotionBlurImpl,
        CommonMethodModifier::SetBrightnessImpl,
        CommonMethodModifier::SetContrastImpl,
        CommonMethodModifier::SetGrayscaleImpl,
        CommonMethodModifier::SetColorBlendImpl,
        CommonMethodModifier::SetSaturateImpl,
        CommonMethodModifier::SetSepiaImpl,
        CommonMethodModifier::SetInvertImpl,
        CommonMethodModifier::SetHueRotateImpl,
        CommonMethodModifier::SetUseShadowBatchingImpl,
        CommonMethodModifier::SetUseEffect0Impl,
        CommonMethodModifier::SetRenderGroupImpl,
        CommonMethodModifier::SetFreezeImpl,
        CommonMethodModifier::SetTranslateImpl,
        CommonMethodModifier::SetScaleImpl,
        CommonMethodModifier::SetRotateImpl,
        CommonMethodModifier::SetTransformImpl,
        CommonMethodModifier::SetOnAppearImpl,
        CommonMethodModifier::SetOnDisAppearImpl,
        CommonMethodModifier::SetOnAttachImpl,
        CommonMethodModifier::SetOnDetachImpl,
        CommonMethodModifier::SetOnAreaChangeImpl,
        CommonMethodModifier::SetVisibilityImpl,
        CommonMethodModifier::SetFlexGrowImpl,
        CommonMethodModifier::SetFlexShrinkImpl,
        CommonMethodModifier::SetFlexBasisImpl,
        CommonMethodModifier::SetAlignSelfImpl,
        CommonMethodModifier::SetDisplayPriorityImpl,
        CommonMethodModifier::SetZIndexImpl,
        CommonMethodModifier::SetDirectionImpl,
        CommonMethodModifier::SetAlignImpl,
        CommonMethodModifier::SetPositionImpl,
        CommonMethodModifier::SetMarkAnchorImpl,
        CommonMethodModifier::SetOffsetImpl,
        CommonMethodModifier::SetEnabledImpl,
        CommonMethodModifier::SetAlignRules0Impl,
        CommonMethodModifier::SetAlignRules1Impl,
        CommonMethodModifier::SetAspectRatioImpl,
        CommonMethodModifier::SetClickEffectImpl,
        CommonMethodModifier::SetOnDragStartImpl,
        CommonMethodModifier::SetOnDragEnterImpl,
        CommonMethodModifier::SetOnDragMoveImpl,
        CommonMethodModifier::SetOnDragLeaveImpl,
        CommonMethodModifier::SetOnDrop0Impl,
        CommonMethodModifier::SetOnDragEndImpl,
        CommonMethodModifier::SetAllowDropImpl,
        CommonMethodModifier::SetDraggableImpl,
        CommonMethodModifier::SetDragPreview0Impl,
        CommonMethodModifier::SetOnPreDragImpl,
        CommonMethodModifier::SetLinearGradientImpl,
        CommonMethodModifier::SetSweepGradientImpl,
        CommonMethodModifier::SetRadialGradientImpl,
        CommonMethodModifier::SetMotionPathImpl,
        CommonMethodModifier::SetShadowImpl,
        CommonMethodModifier::SetClipImpl,
        CommonMethodModifier::SetClipShapeImpl,
        CommonMethodModifier::SetMaskImpl,
        CommonMethodModifier::SetMaskShapeImpl,
        CommonMethodModifier::SetKeyImpl,
        CommonMethodModifier::SetIdImpl,
        CommonMethodModifier::SetGeometryTransition0Impl,
        CommonMethodModifier::SetStateStylesImpl,
        CommonMethodModifier::SetRestoreIdImpl,
        CommonMethodModifier::SetSphericalEffectImpl,
        CommonMethodModifier::SetLightUpEffectImpl,
        CommonMethodModifier::SetPixelStretchEffectImpl,
        CommonMethodModifier::SetAccessibilityGroup0Impl,
        CommonMethodModifier::SetAccessibilityText0Impl,
        CommonMethodModifier::SetAccessibilityNextFocusIdImpl,
        CommonMethodModifier::SetAccessibilityDefaultFocusImpl,
        CommonMethodModifier::SetAccessibilityUseSamePageImpl,
        CommonMethodModifier::SetAccessibilityScrollTriggerableImpl,
        CommonMethodModifier::SetAccessibilityText1Impl,
        CommonMethodModifier::SetAccessibilityRoleImpl,
        CommonMethodModifier::SetOnAccessibilityFocusImpl,
        CommonMethodModifier::SetAccessibilityTextHintImpl,
        CommonMethodModifier::SetAccessibilityDescription0Impl,
        CommonMethodModifier::SetAccessibilityDescription1Impl,
        CommonMethodModifier::SetAccessibilityLevelImpl,
        CommonMethodModifier::SetAccessibilityVirtualNodeImpl,
        CommonMethodModifier::SetAccessibilityCheckedImpl,
        CommonMethodModifier::SetAccessibilitySelectedImpl,
        CommonMethodModifier::SetObscuredImpl,
        CommonMethodModifier::SetReuseIdImpl,
        CommonMethodModifier::SetReuseImpl,
        CommonMethodModifier::SetRenderFitImpl,
        CommonMethodModifier::SetGestureModifierImpl,
        CommonMethodModifier::SetBackgroundBrightnessImpl,
        CommonMethodModifier::SetOnGestureJudgeBeginImpl,
        CommonMethodModifier::SetOnGestureRecognizerJudgeBegin0Impl,
        CommonMethodModifier::SetShouldBuiltInRecognizerParallelWithImpl,
        CommonMethodModifier::SetMonopolizeEventsImpl,
        CommonMethodModifier::SetOnTouchInterceptImpl,
        CommonMethodModifier::SetOnSizeChangeImpl,
        CommonMethodModifier::SetAccessibilityFocusDrawLevelImpl,
        CommonMethodModifier::SetCustomPropertyImpl,
        CommonMethodModifier::SetExpandSafeAreaImpl,
        CommonMethodModifier::SetBackgroundImpl,
        CommonMethodModifier::SetBackgroundImage0Impl,
        CommonMethodModifier::SetBackgroundImage1Impl,
        CommonMethodModifier::SetBackgroundBlurStyleImpl,
        CommonMethodModifier::SetBackgroundEffect1Impl,
        CommonMethodModifier::SetForegroundBlurStyleImpl,
        CommonMethodModifier::SetOnClick1Impl,
        CommonMethodModifier::SetFocusScopeIdImpl,
        CommonMethodModifier::SetFocusScopePriorityImpl,
        CommonMethodModifier::SetTransition1Impl,
        CommonMethodModifier::SetGestureImpl,
        CommonMethodModifier::SetPriorityGestureImpl,
        CommonMethodModifier::SetParallelGestureImpl,
        CommonMethodModifier::SetBlurImpl,
        CommonMethodModifier::SetLinearGradientBlurImpl,
        CommonMethodModifier::SetSystemBarEffectImpl,
        CommonMethodModifier::SetUseEffect1Impl,
        CommonMethodModifier::SetBackdropBlurImpl,
        CommonMethodModifier::SetSharedTransitionImpl,
        CommonMethodModifier::SetChainModeImpl,
        CommonMethodModifier::SetOnDrop1Impl,
        CommonMethodModifier::SetDragPreview1Impl,
        CommonMethodModifier::SetDragPreviewOptionsImpl,
        CommonMethodModifier::SetOverlayImpl,
        CommonMethodModifier::SetBlendModeImpl,
        CommonMethodModifier::SetAdvancedBlendModeImpl,
        CommonMethodModifier::SetGeometryTransition1Impl,
        CommonMethodModifier::SetBindTipsImpl,
        CommonMethodModifier::SetBindPopupImpl,
        CommonMethodModifier::SetBindMenu0Impl,
        CommonMethodModifier::SetBindMenu1Impl,
        CommonMethodModifier::SetBindContextMenu0Impl,
        CommonMethodModifier::SetBindContextMenu1Impl,
        CommonMethodModifier::SetBindContentCover0Impl,
        CommonMethodModifier::SetBindContentCover1Impl,
        CommonMethodModifier::SetBindSheetImpl,
        CommonMethodModifier::SetOnVisibleAreaChangeImpl,
        CommonMethodModifier::SetOnVisibleAreaApproximateChangeImpl,
        CommonMethodModifier::SetKeyboardShortcutImpl,
        CommonMethodModifier::SetAccessibilityGroup1Impl,
        CommonMethodModifier::SetOnGestureRecognizerJudgeBegin1Impl,
    };
    return &ArkUICommonMethodModifierImpl;
}

}
