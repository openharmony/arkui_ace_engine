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
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
    namespace CommonMethodModifier {
        void WidthImpl(Ark_NativePointer node, const Ark_Length* value) {
            auto* frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            auto result = Converter::ConvertOrDefault(*value, CalcLength());
            ViewAbstract::SetWidth(frameNode, result);
        }
        void HeightImpl(Ark_NativePointer node, const Ark_Length* value) {
            auto* frameNode = reinterpret_cast<FrameNode*>(node);
            CHECK_NULL_VOID(frameNode);
            auto result = Converter::ConvertOrDefault(*value, CalcLength());
            ViewAbstract::SetHeight(frameNode, result);
        }
        void DrawModifierImpl(Ark_NativePointer node, const Type_CommonMethod_drawModifier_Arg0* modifier) {
        }
        void CustomPropertyImpl(Ark_NativePointer node, const Ark_String* name, const Opt_Object* value) {
        }
        void ExpandSafeAreaImpl(Ark_NativePointer node, const Opt_Array_SafeAreaType* types, const Opt_Array_SafeAreaEdge* edges) {
        }
        void ResponseRegionImpl(Ark_NativePointer node, const Type_CommonMethod_responseRegion_Arg0* value) {
        }
        void MouseResponseRegionImpl(Ark_NativePointer node, const Type_CommonMethod_mouseResponseRegion_Arg0* value) {
        }
        void SizeImpl(Ark_NativePointer node, const Ark_SizeOptions* value) {
        }
        void ConstraintSizeImpl(Ark_NativePointer node, const Ark_ConstraintSizeOptions* value) {
        }
        void TouchableImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void HitTestBehaviorImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void OnChildTouchTestImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void LayoutWeightImpl(Ark_NativePointer node, const Type_CommonMethod_layoutWeight_Arg0* value) {
        }
        void PaddingImpl(Ark_NativePointer node, const Type_CommonMethod_padding_Arg0* value) {
        }
        void MarginImpl(Ark_NativePointer node, const Type_CommonMethod_margin_Arg0* value) {
        }
        void BackgroundImpl(Ark_NativePointer node, const CustomBuilder* builder, const Opt_Type_CommonMethod_background_Arg1* options) {
        }
        void BackgroundColorImpl(Ark_NativePointer node, const ResourceColor* value) {
            auto frameNode = reinterpret_cast<FrameNode *>(node);
            auto color = Converter::OptConvert<Color>(*value);
            if (color) {
                ViewAbstract::SetBackgroundColor(frameNode, color.value());
            } else {
                LOGI("#### CommonMethod::BackgroundColor impl: color is empty");
            }
        }
        void PixelRoundImpl(Ark_NativePointer node, const Ark_PixelRoundPolicy* value) {
        }
        void BackgroundImageImpl(Ark_NativePointer node, const Type_CommonMethod_backgroundImage_Arg0* src, const Opt_ImageRepeat* repeat) {
        }
        void BackgroundImageSizeImpl(Ark_NativePointer node, const Type_CommonMethod_backgroundImageSize_Arg0* value) {
        }
        void BackgroundImagePositionImpl(Ark_NativePointer node, const Type_CommonMethod_backgroundImagePosition_Arg0* value) {
        }
        void BackgroundBlurStyleImpl(Ark_NativePointer node, Ark_Int32 value, const Opt_BackgroundBlurStyleOptions* options) {
        }
        void BackgroundEffectImpl(Ark_NativePointer node, const Ark_BackgroundEffectOptions* options) {
        }
        void BackgroundImageResizableImpl(Ark_NativePointer node, const Ark_ResizableOptions* value) {
        }
        void ForegroundEffectImpl(Ark_NativePointer node, const Ark_ForegroundEffectOptions* options) {
        }
        void VisualEffectImpl(Ark_NativePointer node, const Ark_CustomObject* effect) {
        }
        void BackgroundFilterImpl(Ark_NativePointer node, const Ark_CustomObject* filter) {
        }
        void ForegroundFilterImpl(Ark_NativePointer node, const Ark_CustomObject* filter) {
        }
        void CompositingFilterImpl(Ark_NativePointer node, const Ark_CustomObject* filter) {
        }
        void ForegroundBlurStyleImpl(Ark_NativePointer node, Ark_Int32 value, const Opt_ForegroundBlurStyleOptions* options) {
        }
        void OpacityImpl(Ark_NativePointer node, const Type_CommonMethod_opacity_Arg0* value) {
        }
        void BorderImpl(Ark_NativePointer node, const Ark_BorderOptions* value) {
        }
        void BorderStyleImpl(Ark_NativePointer node, const Type_CommonMethod_borderStyle_Arg0* value) {
        }
        void BorderWidthImpl(Ark_NativePointer node, const Type_CommonMethod_borderWidth_Arg0* value) {
        }
        void BorderColorImpl(Ark_NativePointer node, const Type_CommonMethod_borderColor_Arg0* value) {
        }
        void BorderRadiusImpl(Ark_NativePointer node, const Type_CommonMethod_borderRadius_Arg0* value) {
        }
        void BorderImageImpl(Ark_NativePointer node, const Ark_BorderImageOption* value) {
        }
        void OutlineImpl(Ark_NativePointer node, const Ark_OutlineOptions* value) {
        }
        void OutlineStyleImpl(Ark_NativePointer node, const Type_CommonMethod_outlineStyle_Arg0* value) {
        }
        void OutlineWidthImpl(Ark_NativePointer node, const Type_CommonMethod_outlineWidth_Arg0* value) {
        }
        void OutlineColorImpl(Ark_NativePointer node, const Type_CommonMethod_outlineColor_Arg0* value) {
        }
        void OutlineRadiusImpl(Ark_NativePointer node, const Type_CommonMethod_outlineRadius_Arg0* value) {
        }
        void ForegroundColorImpl(Ark_NativePointer node, const Type_CommonMethod_foregroundColor_Arg0* value) {
        }
        void OnClickImpl(Ark_NativePointer node, Ark_Function callback) {
            auto frameNode = reinterpret_cast<FrameNode *>(node);
            CHECK_NULL_VOID(frameNode);
            auto onEvent = [frameNode](GestureEvent& info) {
                Ark_ClickEvent onClick;

                Offset globalOffset = info.GetGlobalLocation();
                Offset localOffset = info.GetLocalLocation();
                Offset screenOffset = info.GetScreenLocation();

                onClick.axisHorizontal.tag = Ark_Tag::ARK_TAG_UNDEFINED;
                onClick.axisVertical.tag = Ark_Tag::ARK_TAG_UNDEFINED;
                onClick.displayX.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.displayX.f32 = static_cast<float>(
                        PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetX()));

                onClick.displayY.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.displayY.f32 = static_cast<float>(
                        PipelineBase::Px2VpWithCurrentDensity(screenOffset.GetY()));

                onClick.pressure.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.pressure.f32 = 0.0f;
                onClick.preventDefault.id = 0;

                onClick.screenX.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.screenX.f32 = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));

                onClick.screenY.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.screenY.f32 = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

                onClick.source = static_cast<int32_t>(info.GetSourceDevice());

                onClick.sourceTool = 0;
                onClick.target.area.globalPosition.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
                onClick.target.area.globalPosition.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;
                onClick.target.area.height.type = 0;
                onClick.target.area.height.unit = 1;
                onClick.target.area.height.value = 0;
                onClick.target.area.width.type = 0;
                onClick.target.area.width.unit = 1;
                onClick.target.area.width.value = 0;
                onClick.target.area.position.x.tag = Ark_Tag::ARK_TAG_UNDEFINED;
                onClick.target.area.position.y.tag = Ark_Tag::ARK_TAG_UNDEFINED;

                onClick.tiltX.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.tiltX.f32 = 0;
                onClick.tiltY.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.tiltY.f32 = 0;
                
                onClick.timestamp.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.timestamp.f32 = static_cast<float>(info.GetTimeStamp().time_since_epoch().count());

                onClick.windowX.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.windowX.f32 = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetX()));

                onClick.windowY.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.windowY.f32 = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(globalOffset.GetY()));

                onClick.x.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.x.f32 = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetX()));

                onClick.y.tag = Ark_Tag::ARK_TAG_FLOAT32;
                onClick.y.f32 = static_cast<float>(PipelineBase::Px2VpWithCurrentDensity(localOffset.GetY()));

                GetFullAPI()->getEventsAPI()->getCommonMethodEventsReceiver()->onClick(frameNode->GetId(), onClick);
            };

            if (frameNode->GetTag() == "Span") {
                SpanModelNG::SetOnClick(reinterpret_cast<UINode *>(node), std::move(onEvent));
            } else {
                ViewAbstract::SetOnClick(frameNode, std::move(onEvent));
            }
        }
        void OnHoverImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnAccessibilityHoverImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void HoverEffectImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void OnMouseImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnTouchImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnKeyEventImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnKeyPreImeImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void FocusableImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void OnFocusImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnBlurImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void TabIndexImpl(Ark_NativePointer node, const Ark_Number* index) {
        }
        void DefaultFocusImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void GroupDefaultFocusImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void FocusOnTouchImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void FocusBoxImpl(Ark_NativePointer node, const Ark_FocusBoxStyle* style) {
        }
        void FocusScopeIdImpl(Ark_NativePointer node, const Ark_String* id, const Opt_Boolean* isGroup) {
        }
        void FocusScopePriorityImpl(Ark_NativePointer node, const Ark_String* scopeId, const Opt_FocusPriority* priority) {
        }
        void AnimationImpl(Ark_NativePointer node, const Ark_AnimateParam* value) {
        }
        void Transition_TransitionOptionsTransitionEffectImpl(Ark_NativePointer node, const Type_CommonMethod_transition_Arg0* value) {
        }
        void Transition_TransitionEffect_TransitionFinishCallbackundefinedImpl(Ark_NativePointer node, const Ark_TransitionEffect* effect, const Opt_Function* onFinish) {
        }
        void GestureImpl(Ark_NativePointer node, const Ark_GestureType* gesture, const Opt_GestureMask* mask) {
        }
        void PriorityGestureImpl(Ark_NativePointer node, const Ark_GestureType* gesture, const Opt_GestureMask* mask) {
        }
        void ParallelGestureImpl(Ark_NativePointer node, const Ark_GestureType* gesture, const Opt_GestureMask* mask) {
        }
        void BlurImpl(Ark_NativePointer node, const Ark_Number* value, const Opt_BlurOptions* options) {
        }
        void LinearGradientBlurImpl(Ark_NativePointer node, const Ark_Number* value, const Ark_LinearGradientBlurOptions* options) {
        }
        void MotionBlurImpl(Ark_NativePointer node, const Ark_MotionBlurOptions* value) {
        }
        void BrightnessImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void ContrastImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void GrayscaleImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void ColorBlendImpl(Ark_NativePointer node, const Type_CommonMethod_colorBlend_Arg0* value) {
        }
        void SaturateImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void SepiaImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void InvertImpl(Ark_NativePointer node, const Type_CommonMethod_invert_Arg0* value) {
        }
        void SystemBarEffectImpl(Ark_NativePointer node) {
        }
        void HueRotateImpl(Ark_NativePointer node, const Type_CommonMethod_hueRotate_Arg0* value) {
        }
        void UseShadowBatchingImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void UseEffectImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void BackdropBlurImpl(Ark_NativePointer node, const Ark_Number* value, const Opt_BlurOptions* options) {
        }
        void RenderGroupImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void FreezeImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void TranslateImpl(Ark_NativePointer node, const Ark_TranslateOptions* value) {
        }
        void ScaleImpl(Ark_NativePointer node, const Ark_ScaleOptions* value) {
        }
        void GridSpanImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void GridOffsetImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void RotateImpl(Ark_NativePointer node, const Ark_RotateOptions* value) {
        }
        void TransformImpl(Ark_NativePointer node, const Ark_CustomObject* value) {
        }
        void OnAppearImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnDisAppearImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnAttachImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnDetachImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnAreaChangeImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void VisibilityImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void FlexGrowImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void FlexShrinkImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void FlexBasisImpl(Ark_NativePointer node, const Type_CommonMethod_flexBasis_Arg0* value) {
        }
        void AlignSelfImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void DisplayPriorityImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void ZIndexImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void SharedTransitionImpl(Ark_NativePointer node, const Ark_String* id, const Opt_sharedTransitionOptions* options) {
        }
        void DirectionImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void AlignImpl(Ark_NativePointer node, Ark_Int32 value) {
        }
        void PositionImpl(Ark_NativePointer node, const Type_CommonMethod_position_Arg0* value) {
        }
        void MarkAnchorImpl(Ark_NativePointer node, const Type_CommonMethod_markAnchor_Arg0* value) {
        }
        void OffsetImpl(Ark_NativePointer node, const Type_CommonMethod_offset_Arg0* value) {
        }
        void EnabledImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void UseSizeTypeImpl(Ark_NativePointer node, const Type_CommonMethod_useSizeType_Arg0* value) {
        }
        void AlignRules_AlignRuleOptionImpl(Ark_NativePointer node, const Ark_AlignRuleOption* value) {
        }
        void AlignRules_LocalizedAlignRuleOptionsImpl(Ark_NativePointer node, const Ark_LocalizedAlignRuleOptions* alignRule) {
        }
        void ChainModeImpl(Ark_NativePointer node, Ark_Int32 direction, Ark_Int32 style) {
        }
        void AspectRatioImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void ClickEffectImpl(Ark_NativePointer node, const Type_CommonMethod_clickEffect_Arg0* value) {
        }
        void OnDragStartImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnDragEnterImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnDragMoveImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnDragLeaveImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnDropImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void OnDragEndImpl(Ark_NativePointer node, Ark_Function event) {
        }
        void AllowDropImpl(Ark_NativePointer node, const Type_CommonMethod_allowDrop_Arg0* value) {
        }
        void DraggableImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void DragPreviewImpl(Ark_NativePointer node, const Type_CommonMethod_dragPreview_Arg0* value) {
        }
        void DragPreviewOptionsImpl(Ark_NativePointer node, const Ark_DragPreviewOptions* value, const Opt_DragInteractionOptions* options) {
        }
        void OnPreDragImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OverlayImpl(Ark_NativePointer node, const Type_CommonMethod_overlay_Arg0* value, const Opt_OverlayOptions* options) {
        }
        void LinearGradientImpl(Ark_NativePointer node, const Type_CommonMethod_linearGradient_Arg0* value) {
        }
        void SweepGradientImpl(Ark_NativePointer node, const Type_CommonMethod_sweepGradient_Arg0* value) {
        }
        void RadialGradientImpl(Ark_NativePointer node, const Type_CommonMethod_radialGradient_Arg0* value) {
        }
        void MotionPathImpl(Ark_NativePointer node, const Ark_MotionPathOptions* value) {
        }
        void ShadowImpl(Ark_NativePointer node, const Type_CommonMethod_shadow_Arg0* value) {
        }
        void BlendModeImpl(Ark_NativePointer node, Ark_Int32 value, const Opt_BlendApplyType* type) {
        }
        void Clip_booleanImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void Clip_booleanCircleAttributeEllipseAttributePathAttributeRectAttributeImpl(Ark_NativePointer node, const Type_CommonMethod_clip1_Arg0* value) {
        }
        void ClipShapeImpl(Ark_NativePointer node, const Type_CommonMethod_clipShape_Arg0* value) {
        }
        void Mask_ProgressMaskImpl(Ark_NativePointer node, const Ark_Materialized* value) {
        }
        void Mask_CircleAttributeEllipseAttributePathAttributeRectAttributeProgressMaskImpl(Ark_NativePointer node, const Type_CommonMethod_mask1_Arg0* value) {
        }
        void MaskShapeImpl(Ark_NativePointer node, const Type_CommonMethod_maskShape_Arg0* value) {
        }
        void KeyImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void IdImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void GeometryTransition_stringImpl(Ark_NativePointer node, const Ark_String* id) {
        }
        void GeometryTransition_string_GeometryTransitionOptionsImpl(Ark_NativePointer node, const Ark_String* id, const Opt_GeometryTransitionOptions* options) {
        }
        void BindPopupImpl(Ark_NativePointer node, Ark_Boolean show, const Type_CommonMethod_bindPopup_Arg1* popup) {
        }
        void BindMenu_ArrayMenuElementCustomBuilder_MenuOptionsImpl(Ark_NativePointer node, const Type_CommonMethod_bindMenu_Arg0* content, const Opt_MenuOptions* options) {
        }
        void BindMenu_boolean_ArrayMenuElementCustomBuilder_MenuOptionsImpl(Ark_NativePointer node, Ark_Boolean isShow, const Type_CommonMethod_bindMenu1_Arg1* content, const Opt_MenuOptions* options) {
        }
        void BindContextMenu_CustomBuilder_ResponseType_ContextMenuOptionsImpl(Ark_NativePointer node, const CustomBuilder* content, Ark_Int32 responseType, const Opt_ContextMenuOptions* options) {
        }
        void BindContextMenu_boolean_CustomBuilder_ContextMenuOptionsImpl(Ark_NativePointer node, Ark_Boolean isShown, const CustomBuilder* content, const Opt_ContextMenuOptions* options) {
        }
        void BindContentCover_booleanundefined_CustomBuilder_ModalTransitionImpl(Ark_NativePointer node, const Opt_Boolean* isShow, const CustomBuilder* builder, const Opt_ModalTransition* type) {
        }
        void BindContentCover_booleanundefined_CustomBuilder_ContentCoverOptionsImpl(Ark_NativePointer node, const Opt_Boolean* isShow, const CustomBuilder* builder, const Opt_ContentCoverOptions* options) {
        }
        void BindSheetImpl(Ark_NativePointer node, const Opt_Boolean* isShow, const CustomBuilder* builder, const Opt_SheetOptions* options) {
        }
        void StateStylesImpl(Ark_NativePointer node, const Ark_StateStyles* value) {
        }
        void RestoreIdImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void OnVisibleAreaChangeImpl(Ark_NativePointer node, const Array_Number* ratios, Ark_Function event) {
        }
        void SphericalEffectImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void LightUpEffectImpl(Ark_NativePointer node, const Ark_Number* value) {
        }
        void PixelStretchEffectImpl(Ark_NativePointer node, const Ark_PixelStretchEffectOptions* options) {
        }
        void KeyboardShortcutImpl(Ark_NativePointer node, const Type_CommonMethod_keyboardShortcut_Arg0* value, const Array_ModifierKey* keys, const Opt_Function* action) {
        }
        void AccessibilityGroupImpl(Ark_NativePointer node, Ark_Boolean value) {
        }
        void AccessibilityText_stringImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void AccessibilityText_ResourceImpl(Ark_NativePointer node, const Ark_Resource* text) {
        }
        void AccessibilityTextHintImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void AccessibilityDescription_stringImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void AccessibilityDescription_ResourceImpl(Ark_NativePointer node, const Ark_Resource* description) {
        }
        void AccessibilityLevelImpl(Ark_NativePointer node, const Ark_String* value) {
        }
        void AccessibilityVirtualNodeImpl(Ark_NativePointer node, const CustomBuilder* builder) {
        }
        void ObscuredImpl(Ark_NativePointer node, const Array_ObscuredReasons* reasons) {
        }
        void ReuseIdImpl(Ark_NativePointer node, const Ark_String* id) {
        }
        void RenderFitImpl(Ark_NativePointer node, Ark_Int32 fitMode) {
        }
        void GestureModifierImpl(Ark_NativePointer node, const Ark_Materialized* modifier) {
        }
        void BackgroundBrightnessImpl(Ark_NativePointer node, const Ark_BackgroundBrightnessOptions* params) {
        }
        void OnGestureJudgeBeginImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnGestureRecognizerJudgeBeginImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void ShouldBuiltInRecognizerParallelWithImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void MonopolizeEventsImpl(Ark_NativePointer node, Ark_Boolean monopolize) {
        }
        void OnTouchInterceptImpl(Ark_NativePointer node, Ark_Function callback) {
        }
        void OnSizeChangeImpl(Ark_NativePointer node, Ark_Function event) {
        }
    } // CommonMethodModifier
    const GENERATED_ArkUICommonMethodModifier* GetCommonMethodModifier() {
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
            CommonMethodModifier::FocusScopeIdImpl,
            CommonMethodModifier::FocusScopePriorityImpl,
            CommonMethodModifier::AnimationImpl,
            CommonMethodModifier::Transition_TransitionOptionsTransitionEffectImpl,
            CommonMethodModifier::Transition_TransitionEffect_TransitionFinishCallbackundefinedImpl,
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
            CommonMethodModifier::AlignRules_AlignRuleOptionImpl,
            CommonMethodModifier::AlignRules_LocalizedAlignRuleOptionsImpl,
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
            CommonMethodModifier::Clip_booleanImpl,
            CommonMethodModifier::Clip_booleanCircleAttributeEllipseAttributePathAttributeRectAttributeImpl,
            CommonMethodModifier::ClipShapeImpl,
            CommonMethodModifier::Mask_ProgressMaskImpl,
            CommonMethodModifier::Mask_CircleAttributeEllipseAttributePathAttributeRectAttributeProgressMaskImpl,
            CommonMethodModifier::MaskShapeImpl,
            CommonMethodModifier::KeyImpl,
            CommonMethodModifier::IdImpl,
            CommonMethodModifier::GeometryTransition_stringImpl,
            CommonMethodModifier::GeometryTransition_string_GeometryTransitionOptionsImpl,
            CommonMethodModifier::BindPopupImpl,
            CommonMethodModifier::BindMenu_ArrayMenuElementCustomBuilder_MenuOptionsImpl,
            CommonMethodModifier::BindMenu_boolean_ArrayMenuElementCustomBuilder_MenuOptionsImpl,
            CommonMethodModifier::BindContextMenu_CustomBuilder_ResponseType_ContextMenuOptionsImpl,
            CommonMethodModifier::BindContextMenu_boolean_CustomBuilder_ContextMenuOptionsImpl,
            CommonMethodModifier::BindContentCover_booleanundefined_CustomBuilder_ModalTransitionImpl,
            CommonMethodModifier::BindContentCover_booleanundefined_CustomBuilder_ContentCoverOptionsImpl,
            CommonMethodModifier::BindSheetImpl,
            CommonMethodModifier::StateStylesImpl,
            CommonMethodModifier::RestoreIdImpl,
            CommonMethodModifier::OnVisibleAreaChangeImpl,
            CommonMethodModifier::SphericalEffectImpl,
            CommonMethodModifier::LightUpEffectImpl,
            CommonMethodModifier::PixelStretchEffectImpl,
            CommonMethodModifier::KeyboardShortcutImpl,
            CommonMethodModifier::AccessibilityGroupImpl,
            CommonMethodModifier::AccessibilityText_stringImpl,
            CommonMethodModifier::AccessibilityText_ResourceImpl,
            CommonMethodModifier::AccessibilityTextHintImpl,
            CommonMethodModifier::AccessibilityDescription_stringImpl,
            CommonMethodModifier::AccessibilityDescription_ResourceImpl,
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
