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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { AttributeModifier, DrawModifier, extractors, GestureModifier, hookAllowDrop, hookDragPreviewOptions } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkCommonMethodPeer, LayoutPolicy, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, BorderImageOption, OutlineStyle, ClickEvent, HoverEvent, AccessibilityCallback, AccessibilityHoverEvent, MouseEvent, TouchEvent, KeyEvent, CrownEvent, FocusAxisEvent, AxisEvent, FocusMovement, AnimateParam, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, RotateAngleOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, DragEvent, DragItemInfo, PreDragStatus, LinearGradientOptions, SweepGradientOptions, RadialGradientOptions, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, AccessibilitySamePageMode, AccessibilityRoleType, AccessibilityFocusCallback, AccessibilityActionInterceptCallback, AccessibilityAction, ReuseOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, CustomProperty, SafeAreaType, SafeAreaEdge, BackgroundOptions, BackgroundImageOptions, BlurStyle, BackgroundBlurStyleOptions, SystemAdaptiveOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, OnDragEventCallback, DropOptions, PreviewConfiguration, DragPreviewOptions, DragInteractionOptions, OverlayOptions, BlendMode, BlendApplyType, GeometryTransitionOptions, TipsMessageType, TipsOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, Bindable, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, VisibleAreaEventOptions, CommonMethod } from "./component/common"
import { int32 } from "@koalaui/common"
import { Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, VoidCallback, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./component/units"
import { Resource } from "global.resource"
import { HitTestMode, Color, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Visibility, ItemAlign, Direction, ObscuredReasons, RenderFit, FocusDrawLevel, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey } from "./component/enums"
import { LengthMetrics, ColorMetrics} from "arkui.Graphics"
import { ResizableOptions } from "./component/image"
import { default as uiEffect } from "@ohos.graphics.uiEffect"
import { FocusBoxStyle, FocusPriority } from "./component/focus"
import { default as matrix4 } from "@ohos.matrix4"
import { CustomBuilder } from "./component/builder"
import { default as uniformTypeDescriptor } from "@ohos.data.uniformTypeDescriptor"
import { CircleShape, EllipseShape, PathShape, RectShape } from "@ohos.arkui.shape"
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureRecognizer, GestureType, Gesture, GestureGroup, GestureMask } from "./component/gesture"
import { default as image } from "@ohos.multimedia.image"
import { ComponentContent } from "arkui.ComponentContent"
import { StyledString } from "./component/styledString"
export class CommonMethodModifier implements CommonMethod {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    _width_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _width_0_0value?: Length | LayoutPolicy | undefined
    _height_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _height_0_0value?: Length | LayoutPolicy | undefined
    _responseRegion_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _responseRegion_0_0value?: Array<Rectangle> | Rectangle | undefined
    _mouseResponseRegion_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mouseResponseRegion_0_0value?: Array<Rectangle> | Rectangle | undefined
    _size_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _size_0_0value?: SizeOptions | undefined
    _constraintSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _constraintSize_0_0value?: ConstraintSizeOptions | undefined
    _hitTestBehavior_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hitTestBehavior_0_0value?: HitTestMode | undefined
    _onChildTouchTest_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onChildTouchTest_0_0value?: ((value: Array<TouchTestInfo>) => TouchResult) | undefined
    _layoutWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _layoutWeight_0_0value?: number | string | undefined
    _chainWeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _chainWeight_0_0value?: ChainWeightOptions | undefined
    _padding_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _padding_0_0value?: Padding | Length | LocalizedPadding | undefined
    _safeAreaPadding_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _safeAreaPadding_0_0value?: Padding | LengthMetrics | LocalizedPadding | undefined
    _margin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _margin_0_0value?: Padding | Length | LocalizedPadding | undefined
    _backgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundColor_0_0value?: ResourceColor | ColorMetrics | undefined
    _pixelRound_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pixelRound_0_0value?: PixelRoundPolicy | undefined
    _backgroundImageSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundImageSize_0_0value?: SizeOptions | ImageSize | undefined
    _backgroundImagePosition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundImagePosition_0_0value?: Position | Alignment | undefined
    _backgroundEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundEffect_0_0value?: BackgroundEffectOptions | undefined
    _backgroundImageResizable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundImageResizable_0_0value?: ResizableOptions | undefined
    _foregroundEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _foregroundEffect_0_0value?: ForegroundEffectOptions | undefined
    _visualEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _visualEffect_0_0value?: uiEffect.VisualEffect | undefined
    _backgroundFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundFilter_0_0value?: uiEffect.Filter | undefined
    _foregroundFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _foregroundFilter_0_0value?: uiEffect.Filter | undefined
    _compositingFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _compositingFilter_0_0value?: uiEffect.Filter | undefined
    _opacity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _opacity_0_0value?: number | Resource | undefined
    _border_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _border_0_0value?: BorderOptions | undefined
    _borderStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderStyle_0_0value?: BorderStyle | EdgeStyles | undefined
    _borderWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderWidth_0_0value?: Length | EdgeWidths | LocalizedEdgeWidths | undefined
    _borderColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderColor_0_0value?: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
    _borderRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderRadius_0_0value?: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined
    _borderImage_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _borderImage_0_0value?: BorderImageOption | undefined
    _outline_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _outline_0_0value?: OutlineOptions | undefined
    _outlineStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _outlineStyle_0_0value?: OutlineStyle | EdgeOutlineStyles | undefined
    _outlineWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _outlineWidth_0_0value?: Dimension | EdgeOutlineWidths | undefined
    _outlineColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _outlineColor_0_0value?: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined
    _outlineRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _outlineRadius_0_0value?: Dimension | OutlineRadiuses | undefined
    _foregroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _foregroundColor_0_0value?: ResourceColor | ColoringStrategy | undefined
    _onClick_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onClick_0_0value?: ((event: ClickEvent) => void) | undefined
    _onHover_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHover_0_0value?: ((isHover: boolean,event: HoverEvent) => void) | undefined
    _onHoverMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHoverMove_0_0value?: ((value0: HoverEvent) => void) | undefined
    _onAccessibilityHover_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAccessibilityHover_0_0value?: AccessibilityCallback | undefined
    _hoverEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hoverEffect_0_0value?: HoverEffect | undefined
    _onMouse_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onMouse_0_0value?: ((event: MouseEvent) => void) | undefined
    _onTouch_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTouch_0_0value?: ((event: TouchEvent) => void) | undefined
    _onKeyEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onKeyEvent_0_0value?: ((event: KeyEvent) => void) | undefined
    _onDigitalCrown_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDigitalCrown_0_0value?: ((value0: CrownEvent) => void) | undefined
    _onKeyPreIme_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onKeyPreIme_0_0value?: ((value0: KeyEvent) => boolean) | undefined
    _onKeyEventDispatch_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onKeyEventDispatch_0_0value?: ((value0: KeyEvent) => boolean) | undefined
    _onFocusAxisEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFocusAxisEvent_0_0value?: ((value0: FocusAxisEvent) => void) | undefined
    _onAxisEvent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAxisEvent_0_0value?: ((value0: AxisEvent) => void) | undefined
    _focusable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _focusable_0_0value?: boolean | undefined
    _nextFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _nextFocus_0_0value?: FocusMovement | undefined
    _tabStop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _tabStop_0_0value?: boolean | undefined
    _onFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFocus_0_0value?: (() => void) | undefined
    _onBlur_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onBlur_0_0value?: (() => void) | undefined
    _tabIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _tabIndex_0_0value?: number | undefined
    _defaultFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _defaultFocus_0_0value?: boolean | undefined
    _groupDefaultFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _groupDefaultFocus_0_0value?: boolean | undefined
    _focusOnTouch_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _focusOnTouch_0_0value?: boolean | undefined
    _focusBox_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _focusBox_0_0value?: FocusBoxStyle | undefined
    _animation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _animation_0_0value?: AnimateParam | undefined
    _transition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _transition_0_0value?: TransitionEffect | undefined
    _motionBlur_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _motionBlur_0_0value?: MotionBlurOptions | undefined
    _brightness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _brightness_0_0value?: number | undefined
    _contrast_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _contrast_0_0value?: number | undefined
    _grayscale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _grayscale_0_0value?: number | undefined
    _colorBlend_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _colorBlend_0_0value?: Color | string | Resource | undefined
    _saturate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _saturate_0_0value?: number | undefined
    _sepia_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sepia_0_0value?: number | undefined
    _invert_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _invert_0_0value?: number | InvertOptions | undefined
    _hueRotate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _hueRotate_0_0value?: number | string | undefined
    _useShadowBatching_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _useShadowBatching_0_0value?: boolean | undefined
    _useEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _useEffect_0_0value?: boolean | undefined
    _renderGroup_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderGroup_0_0value?: boolean | undefined
    _freeze_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _freeze_0_0value?: boolean | undefined
    _translate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _translate_0_0value?: TranslateOptions | undefined
    _scale_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _scale_0_0value?: ScaleOptions | undefined
    _rotate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rotate_0_0value?: RotateOptions | RotateAngleOptions | undefined
    _transform_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _transform_0_0value?: matrix4.Matrix4Transit | undefined
    _transform3D_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _transform3D_0_0value?: matrix4.Matrix4Transit | undefined
    _onAppear_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAppear_0_0value?: (() => void) | undefined
    _onDisAppear_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDisAppear_0_0value?: (() => void) | undefined
    _onAttach_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAttach_0_0value?: VoidCallback | undefined
    _onDetach_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDetach_0_0value?: VoidCallback | undefined
    _onAreaChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAreaChange_0_0value?: ((oldValue: Area,newValue: Area) => void) | undefined
    _visibility_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _visibility_0_0value?: Visibility | undefined
    _flexGrow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _flexGrow_0_0value?: number | undefined
    _flexShrink_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _flexShrink_0_0value?: number | undefined
    _flexBasis_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _flexBasis_0_0value?: number | string | undefined
    _alignSelf_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignSelf_0_0value?: ItemAlign | undefined
    _displayPriority_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _displayPriority_0_0value?: number | undefined
    _zIndex_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _zIndex_0_0value?: number | undefined
    _direction_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _direction_0_0value?: Direction | undefined
    _align_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _align_0_0value?: Alignment | undefined
    _position_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _position_0_0value?: Position | Edges | LocalizedEdges | undefined
    _markAnchor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _markAnchor_0_0value?: Position | LocalizedPosition | undefined
    _offset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _offset_0_0value?: Position | Edges | LocalizedEdges | undefined
    _enabled_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enabled_0_0value?: boolean | undefined
    _alignRules_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignRules_0_0value?: AlignRuleOption | LocalizedAlignRuleOptions | undefined
    _aspectRatio_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _aspectRatio_0_0value?: number | undefined
    _clickEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _clickEffect_0_0value?: ClickEffect | null | undefined
    _onDragStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDragStart_0_0value?: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined
    _onDragEnter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDragEnter_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _onDragMove_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDragMove_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _onDragLeave_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDragLeave_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _onDrop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDrop_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _onDragEnd_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDragEnd_0_0value?: ((event: DragEvent,extraParams?: string) => void) | undefined
    _allowDrop_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _allowDrop_0_0value?: Array<uniformTypeDescriptor.UniformDataType> | null | undefined
    _draggable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _draggable_0_0value?: boolean | undefined
    _dragPreview_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dragPreview_0_0value?: CustomBuilder | DragItemInfo | string | undefined
    _onPreDrag_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPreDrag_0_0value?: ((value0: PreDragStatus) => void) | undefined
    _linearGradient_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _linearGradient_0_0value?: LinearGradientOptions | undefined
    _sweepGradient_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sweepGradient_0_0value?: SweepGradientOptions | undefined
    _radialGradient_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _radialGradient_0_0value?: RadialGradientOptions | undefined
    _motionPath_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _motionPath_0_0value?: MotionPathOptions | undefined
    _shadow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _shadow_0_0value?: ShadowOptions | ShadowStyle | undefined
    _clip_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _clip_0_0value?: boolean | undefined
    _clipShape_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _clipShape_0_0value?: CircleShape | EllipseShape | PathShape | RectShape | undefined
    _mask_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _mask_0_0value?: ProgressMask | undefined
    _maskShape_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _maskShape_0_0value?: CircleShape | EllipseShape | PathShape | RectShape | undefined
    _key_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _key_0_0value?: string | undefined
    _id_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _id_0_0value?: string | undefined
    _geometryTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _geometryTransition_0_0value?: string | undefined
    _restoreId_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _restoreId_0_0value?: number | undefined
    _sphericalEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sphericalEffect_0_0value?: number | undefined
    _lightUpEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _lightUpEffect_0_0value?: number | undefined
    _pixelStretchEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pixelStretchEffect_0_0value?: PixelStretchEffectOptions | undefined
    _accessibilityGroup_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityGroup_0_0value?: boolean | undefined
    _accessibilityText_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityText_0_0value?: string | undefined
    _accessibilityNextFocusId_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityNextFocusId_0_0value?: string | undefined
    _accessibilityDefaultFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityDefaultFocus_0_0value?: boolean | undefined
    _accessibilityUseSamePage_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityUseSamePage_0_0value?: AccessibilitySamePageMode | undefined
    _accessibilityScrollTriggerable_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityScrollTriggerable_0_0value?: boolean | undefined
    _accessibilityText_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityText_1_0value?: Resource | undefined
    _accessibilityRole_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityRole_0_0value?: AccessibilityRoleType | undefined
    _onAccessibilityFocus_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAccessibilityFocus_0_0value?: AccessibilityFocusCallback | undefined
    _onAccessibilityActionIntercept_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAccessibilityActionIntercept_0_0value?: AccessibilityActionInterceptCallback | undefined
    _accessibilityTextHint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityTextHint_0_0value?: string | undefined
    _accessibilityDescription_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityDescription_0_0value?: string | undefined
    _accessibilityDescription_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityDescription_1_0value?: Resource | undefined
    _accessibilityLevel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityLevel_0_0value?: string | undefined
    _accessibilityVirtualNode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityVirtualNode_0_0value?: CustomBuilder | undefined
    _accessibilityChecked_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityChecked_0_0value?: boolean | undefined
    _accessibilitySelected_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilitySelected_0_0value?: boolean | undefined
    _obscured_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _obscured_0_0value?: Array<ObscuredReasons> | undefined
    _reuseId_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _reuseId_0_0value?: string | undefined
    _reuse_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _reuse_0_0value?: ReuseOptions | undefined
    _renderFit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderFit_0_0value?: RenderFit | undefined
    _backgroundBrightness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundBrightness_0_0value?: BackgroundBrightnessOptions | undefined
    _onGestureJudgeBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGestureJudgeBegin_0_0value?: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined
    _onGestureRecognizerJudgeBegin_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGestureRecognizerJudgeBegin_0_0value?: GestureRecognizerJudgeBeginCallback | undefined
    _shouldBuiltInRecognizerParallelWith_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _shouldBuiltInRecognizerParallelWith_0_0value?: ShouldBuiltInRecognizerParallelWithCallback | undefined
    _monopolizeEvents_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _monopolizeEvents_0_0value?: boolean | undefined
    _onTouchIntercept_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onTouchIntercept_0_0value?: ((value0: TouchEvent) => HitTestMode) | undefined
    _onSizeChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onSizeChange_0_0value?: SizeChangeCallback | undefined
    _accessibilityFocusDrawLevel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityFocusDrawLevel_0_0value?: FocusDrawLevel | undefined
    _expandSafeArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _expandSafeArea_0_0value?: Array<SafeAreaType> | undefined
    _expandSafeArea_0_1value?: Array<SafeAreaEdge> | undefined
    _background_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _background_0_0value?: CustomBuilder | undefined
    _background_0_1value?: BackgroundOptions | undefined
    _backgroundImage_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundImage_0_0value?: ResourceStr | image.PixelMap | undefined
    _backgroundImage_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundImage_1_0value?: ResourceStr | image.PixelMap | undefined
    _backgroundImage_1_1value?: BackgroundImageOptions
    _backgroundImage_2_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundImage_2_0value?: ResourceStr | image.PixelMap | undefined
    _backgroundImage_2_1value?: ImageRepeat
    _backgroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundBlurStyle_0_0value?: BlurStyle | undefined
    _backgroundBlurStyle_0_1value?: BackgroundBlurStyleOptions | undefined
    _backgroundBlurStyle_0_2value?: SystemAdaptiveOptions | undefined
    _backgroundEffect_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundEffect_1_0value?: BackgroundEffectOptions | undefined
    _backgroundEffect_1_1value?: SystemAdaptiveOptions | undefined
    _foregroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _foregroundBlurStyle_0_0value?: BlurStyle | undefined
    _foregroundBlurStyle_0_1value?: ForegroundBlurStyleOptions | undefined
    _foregroundBlurStyle_0_2value?: SystemAdaptiveOptions | undefined
    _onClick_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onClick_1_0value?: ((event: ClickEvent) => void) | undefined
    _onClick_1_1value?: number | undefined
    _focusScopeId_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _focusScopeId_0_0value?: string | undefined
    _focusScopeId_0_1value?: boolean | undefined
    _focusScopeId_0_2value?: boolean | undefined
    _focusScopePriority_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _focusScopePriority_0_0value?: string | undefined
    _focusScopePriority_0_1value?: FocusPriority | undefined
    _transition_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _transition_1_0value?: TransitionEffect | undefined
    _transition_1_1value?: TransitionFinishCallback | undefined
    _blur_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blur_0_0value?: number | undefined
    _blur_0_1value?: BlurOptions | undefined
    _blur_0_2value?: SystemAdaptiveOptions | undefined
    _linearGradientBlur_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _linearGradientBlur_0_0value?: number | undefined
    _linearGradientBlur_0_1value?: LinearGradientBlurOptions | undefined
    _systemBarEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _useEffect_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _useEffect_1_0value?: boolean | undefined
    _useEffect_1_1value?: EffectType | undefined
    _backdropBlur_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backdropBlur_0_0value?: number | undefined
    _backdropBlur_0_1value?: BlurOptions | undefined
    _backdropBlur_0_2value?: SystemAdaptiveOptions | undefined
    _sharedTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sharedTransition_0_0value?: string | undefined
    _sharedTransition_0_1value?: sharedTransitionOptions | undefined
    _chainMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _chainMode_0_0value?: Axis | undefined
    _chainMode_0_1value?: ChainStyle | undefined
    _onDrop_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDrop_1_0value?: OnDragEventCallback | undefined
    _onDrop_1_1value?: DropOptions | undefined
    _dragPreview_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dragPreview_1_0value?: CustomBuilder | DragItemInfo | string | undefined
    _dragPreview_1_1value?: PreviewConfiguration | undefined
    _dragPreviewOptions_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dragPreviewOptions_0_0value?: DragPreviewOptions | undefined
    _dragPreviewOptions_0_1value?: DragInteractionOptions | undefined
    _overlay_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _overlay_0_0value?: string | CustomBuilder | ComponentContent | undefined
    _overlay_0_1value?: OverlayOptions | undefined
    _blendMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _blendMode_0_0value?: BlendMode | undefined
    _blendMode_0_1value?: BlendApplyType | undefined
    _advancedBlendMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _advancedBlendMode_0_0value?: BlendMode | uiEffect.Blender
    _advancedBlendMode_0_1value?: BlendApplyType | undefined
    _geometryTransition_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _geometryTransition_1_0value?: string | undefined
    _geometryTransition_1_1value?: GeometryTransitionOptions | undefined
    _bindTips_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindTips_0_0value?: TipsMessageType | undefined
    _bindTips_0_1value?: TipsOptions | undefined
    _bindPopup_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindPopup_0_0value?: boolean | undefined
    _bindPopup_0_1value?: PopupOptions | CustomPopupOptions | undefined
    _bindMenu_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindMenu_0_0value?: Array<MenuElement> | CustomBuilder | undefined
    _bindMenu_0_1value?: MenuOptions | undefined
    _bindMenu_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindMenu_1_0value?: boolean | undefined
    _bindMenu_1_1value?: Array<MenuElement> | CustomBuilder | undefined
    _bindMenu_1_2value?: MenuOptions | undefined
    _bindContextMenu_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindContextMenu_0_0value?: CustomBuilder | undefined
    _bindContextMenu_0_1value?: ResponseType | undefined
    _bindContextMenu_0_2value?: ContextMenuOptions | undefined
    _bindContextMenu_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindContextMenu_1_0value?: boolean | undefined
    _bindContextMenu_1_1value?: CustomBuilder | undefined
    _bindContextMenu_1_2value?: ContextMenuOptions | undefined
    _bindContentCover_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindContentCover_0_0value?: boolean | Bindable<boolean> | undefined
    _bindContentCover_0_1value?: CustomBuilder | undefined
    _bindContentCover_0_2value?: ModalTransition | undefined
    _bindContentCover_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindContentCover_1_0value?: boolean | Bindable<boolean> | undefined
    _bindContentCover_1_1value?: CustomBuilder | undefined
    _bindContentCover_1_2value?: ContentCoverOptions | undefined
    _bindSheet_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _bindSheet_0_0value?: boolean | Bindable<boolean> | undefined
    _bindSheet_0_1value?: CustomBuilder | undefined
    _bindSheet_0_2value?: SheetOptions | undefined
    _onVisibleAreaChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onVisibleAreaChange_0_0value?: Array<number> | undefined
    _onVisibleAreaChange_0_1value?: VisibleAreaChangeCallback | undefined
    _onVisibleAreaApproximateChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onVisibleAreaApproximateChange_0_0value?: VisibleAreaEventOptions | undefined
    _onVisibleAreaApproximateChange_0_1value?: VisibleAreaChangeCallback | undefined
    _keyboardShortcut_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _keyboardShortcut_0_0value?: string | FunctionKey | undefined
    _keyboardShortcut_0_1value?: Array<ModifierKey> | undefined
    _keyboardShortcut_0_2value?: (() => void) | undefined
    _accessibilityGroup_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _accessibilityGroup_1_0value?: boolean | undefined
    _accessibilityGroup_1_1value?: AccessibilityOptions | undefined
    _onGestureRecognizerJudgeBegin_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onGestureRecognizerJudgeBegin_1_0value?: GestureRecognizerJudgeBeginCallback | undefined
    _onGestureRecognizerJudgeBegin_1_1value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        const peer = node as ArkCommonMethodPeer;
        if (this._width_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._width_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setWidthAttribute((this._width_0_0value as Length | LayoutPolicy | undefined));
                    this._width_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._width_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._width_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setWidthAttribute((undefined as Length | LayoutPolicy | undefined));
                }
            }
        }
        if (this._height_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._height_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHeightAttribute((this._height_0_0value as Length | LayoutPolicy | undefined));
                    this._height_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._height_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._height_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHeightAttribute((undefined as Length | LayoutPolicy | undefined));
                }
            }
        }
        if (this._responseRegion_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._responseRegion_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setResponseRegionAttribute((this._responseRegion_0_0value as Array<Rectangle> | Rectangle | undefined));
                    this._responseRegion_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._responseRegion_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._responseRegion_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setResponseRegionAttribute((undefined as Array<Rectangle> | Rectangle | undefined));
                }
            }
        }
        if (this._mouseResponseRegion_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mouseResponseRegion_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMouseResponseRegionAttribute((this._mouseResponseRegion_0_0value as Array<Rectangle> | Rectangle | undefined));
                    this._mouseResponseRegion_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mouseResponseRegion_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mouseResponseRegion_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMouseResponseRegionAttribute((undefined as Array<Rectangle> | Rectangle | undefined));
                }
            }
        }
        if (this._size_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._size_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSizeAttribute((this._size_0_0value as SizeOptions | undefined));
                    this._size_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._size_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._size_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSizeAttribute((undefined as SizeOptions | undefined));
                }
            }
        }
        if (this._constraintSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._constraintSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setConstraintSizeAttribute((this._constraintSize_0_0value as ConstraintSizeOptions | undefined));
                    this._constraintSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._constraintSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._constraintSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setConstraintSizeAttribute((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (this._hitTestBehavior_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hitTestBehavior_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHitTestBehaviorAttribute((this._hitTestBehavior_0_0value as HitTestMode | undefined));
                    this._hitTestBehavior_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hitTestBehavior_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hitTestBehavior_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHitTestBehaviorAttribute((undefined as HitTestMode | undefined));
                }
            }
        }
        if (this._onChildTouchTest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onChildTouchTest_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnChildTouchTestAttribute((this._onChildTouchTest_0_0value as ((value: Array<TouchTestInfo>) => TouchResult) | undefined));
                    this._onChildTouchTest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onChildTouchTest_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onChildTouchTest_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnChildTouchTestAttribute((undefined as ((value: Array<TouchTestInfo>) => TouchResult) | undefined));
                }
            }
        }
        if (this._layoutWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._layoutWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLayoutWeightAttribute((this._layoutWeight_0_0value as number | string | undefined));
                    this._layoutWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._layoutWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._layoutWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLayoutWeightAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._chainWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._chainWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChainWeightAttribute((this._chainWeight_0_0value as ChainWeightOptions | undefined));
                    this._chainWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainWeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainWeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChainWeightAttribute((undefined as ChainWeightOptions | undefined));
                }
            }
        }
        if (this._padding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._padding_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPaddingAttribute((this._padding_0_0value as Padding | Length | LocalizedPadding | undefined));
                    this._padding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._padding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._padding_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPaddingAttribute((undefined as Padding | Length | LocalizedPadding | undefined));
                }
            }
        }
        if (this._safeAreaPadding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._safeAreaPadding_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSafeAreaPaddingAttribute((this._safeAreaPadding_0_0value as Padding | LengthMetrics | LocalizedPadding | undefined));
                    this._safeAreaPadding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._safeAreaPadding_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._safeAreaPadding_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSafeAreaPaddingAttribute((undefined as Padding | LengthMetrics | LocalizedPadding | undefined));
                }
            }
        }
        if (this._margin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._margin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMarginAttribute((this._margin_0_0value as Padding | Length | LocalizedPadding | undefined));
                    this._margin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._margin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._margin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMarginAttribute((undefined as Padding | Length | LocalizedPadding | undefined));
                }
            }
        }
        if (this._backgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundColorAttribute((this._backgroundColor_0_0value as ResourceColor | ColorMetrics | undefined));
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundColorAttribute((undefined as ResourceColor | ColorMetrics | undefined));
                }
            }
        }
        if (this._pixelRound_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pixelRound_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPixelRoundAttribute((this._pixelRound_0_0value as PixelRoundPolicy | undefined));
                    this._pixelRound_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pixelRound_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pixelRound_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPixelRoundAttribute((undefined as PixelRoundPolicy | undefined));
                }
            }
        }
        if (this._backgroundImageSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundImageSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundImageSizeAttribute((this._backgroundImageSize_0_0value as SizeOptions | ImageSize | undefined));
                    this._backgroundImageSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundImageSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundImageSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundImageSizeAttribute((undefined as SizeOptions | ImageSize | undefined));
                }
            }
        }
        if (this._backgroundImagePosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundImagePosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundImagePositionAttribute((this._backgroundImagePosition_0_0value as Position | Alignment | undefined));
                    this._backgroundImagePosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundImagePosition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundImagePosition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundImagePositionAttribute((undefined as Position | Alignment | undefined));
                }
            }
        }
        if (this._backgroundEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundEffect0Attribute((this._backgroundEffect_0_0value as BackgroundEffectOptions | undefined));
                    this._backgroundEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundEffect0Attribute((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
        if (this._backgroundImageResizable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundImageResizable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundImageResizableAttribute((this._backgroundImageResizable_0_0value as ResizableOptions | undefined));
                    this._backgroundImageResizable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundImageResizable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundImageResizable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundImageResizableAttribute((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (this._foregroundEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._foregroundEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setForegroundEffectAttribute((this._foregroundEffect_0_0value as ForegroundEffectOptions | undefined));
                    this._foregroundEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._foregroundEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._foregroundEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setForegroundEffectAttribute((undefined as ForegroundEffectOptions | undefined));
                }
            }
        }
        if (this._visualEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._visualEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVisualEffectAttribute((this._visualEffect_0_0value as uiEffect.VisualEffect | undefined));
                    this._visualEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._visualEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._visualEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVisualEffectAttribute((undefined as uiEffect.VisualEffect | undefined));
                }
            }
        }
        if (this._backgroundFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundFilterAttribute((this._backgroundFilter_0_0value as uiEffect.Filter | undefined));
                    this._backgroundFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundFilterAttribute((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (this._foregroundFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._foregroundFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setForegroundFilterAttribute((this._foregroundFilter_0_0value as uiEffect.Filter | undefined));
                    this._foregroundFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._foregroundFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._foregroundFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setForegroundFilterAttribute((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (this._compositingFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._compositingFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCompositingFilterAttribute((this._compositingFilter_0_0value as uiEffect.Filter | undefined));
                    this._compositingFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._compositingFilter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._compositingFilter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCompositingFilterAttribute((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (this._opacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._opacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOpacityAttribute((this._opacity_0_0value as number | Resource | undefined));
                    this._opacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._opacity_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._opacity_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOpacityAttribute((undefined as number | Resource | undefined));
                }
            }
        }
        if (this._border_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._border_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderAttribute((this._border_0_0value as BorderOptions | undefined));
                    this._border_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._border_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._border_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderAttribute((undefined as BorderOptions | undefined));
                }
            }
        }
        if (this._borderStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderStyleAttribute((this._borderStyle_0_0value as BorderStyle | EdgeStyles | undefined));
                    this._borderStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderStyleAttribute((undefined as BorderStyle | EdgeStyles | undefined));
                }
            }
        }
        if (this._borderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderWidthAttribute((this._borderWidth_0_0value as Length | EdgeWidths | LocalizedEdgeWidths | undefined));
                    this._borderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderWidthAttribute((undefined as Length | EdgeWidths | LocalizedEdgeWidths | undefined));
                }
            }
        }
        if (this._borderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderColorAttribute((this._borderColor_0_0value as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                    this._borderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderColorAttribute((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                }
            }
        }
        if (this._borderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderRadiusAttribute((this._borderRadius_0_0value as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined));
                    this._borderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderRadiusAttribute((undefined as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined));
                }
            }
        }
        if (this._borderImage_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._borderImage_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBorderImageAttribute((this._borderImage_0_0value as BorderImageOption | undefined));
                    this._borderImage_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._borderImage_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._borderImage_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBorderImageAttribute((undefined as BorderImageOption | undefined));
                }
            }
        }
        if (this._outline_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._outline_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOutlineAttribute((this._outline_0_0value as OutlineOptions | undefined));
                    this._outline_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._outline_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._outline_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOutlineAttribute((undefined as OutlineOptions | undefined));
                }
            }
        }
        if (this._outlineStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._outlineStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOutlineStyleAttribute((this._outlineStyle_0_0value as OutlineStyle | EdgeOutlineStyles | undefined));
                    this._outlineStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._outlineStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._outlineStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOutlineStyleAttribute((undefined as OutlineStyle | EdgeOutlineStyles | undefined));
                }
            }
        }
        if (this._outlineWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._outlineWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOutlineWidthAttribute((this._outlineWidth_0_0value as Dimension | EdgeOutlineWidths | undefined));
                    this._outlineWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._outlineWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._outlineWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOutlineWidthAttribute((undefined as Dimension | EdgeOutlineWidths | undefined));
                }
            }
        }
        if (this._outlineColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._outlineColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOutlineColorAttribute((this._outlineColor_0_0value as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                    this._outlineColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._outlineColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._outlineColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOutlineColorAttribute((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                }
            }
        }
        if (this._outlineRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._outlineRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOutlineRadiusAttribute((this._outlineRadius_0_0value as Dimension | OutlineRadiuses | undefined));
                    this._outlineRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._outlineRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._outlineRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOutlineRadiusAttribute((undefined as Dimension | OutlineRadiuses | undefined));
                }
            }
        }
        if (this._foregroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._foregroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setForegroundColorAttribute((this._foregroundColor_0_0value as ResourceColor | ColoringStrategy | undefined));
                    this._foregroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._foregroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._foregroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setForegroundColorAttribute((undefined as ResourceColor | ColoringStrategy | undefined));
                }
            }
        }
        if (this._onClick_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnClick0Attribute((this._onClick_0_0value as ((event: ClickEvent) => void) | undefined));
                    this._onClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onClick_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onClick_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnClick0Attribute((undefined as ((event: ClickEvent) => void) | undefined));
                }
            }
        }
        if (this._onHover_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHover_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHoverAttribute((this._onHover_0_0value as ((isHover: boolean,event: HoverEvent) => void) | undefined));
                    this._onHover_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHover_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHover_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHoverAttribute((undefined as ((isHover: boolean,event: HoverEvent) => void) | undefined));
                }
            }
        }
        if (this._onHoverMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHoverMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHoverMoveAttribute((this._onHoverMove_0_0value as ((value0: HoverEvent) => void) | undefined));
                    this._onHoverMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHoverMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHoverMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHoverMoveAttribute((undefined as ((value0: HoverEvent) => void) | undefined));
                }
            }
        }
        if (this._onAccessibilityHover_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAccessibilityHover_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAccessibilityHoverAttribute((this._onAccessibilityHover_0_0value as AccessibilityCallback | undefined));
                    this._onAccessibilityHover_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAccessibilityHover_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAccessibilityHover_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAccessibilityHoverAttribute((undefined as AccessibilityCallback | undefined));
                }
            }
        }
        if (this._hoverEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hoverEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHoverEffectAttribute((this._hoverEffect_0_0value as HoverEffect | undefined));
                    this._hoverEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hoverEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hoverEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHoverEffectAttribute((undefined as HoverEffect | undefined));
                }
            }
        }
        if (this._onMouse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onMouse_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnMouseAttribute((this._onMouse_0_0value as ((event: MouseEvent) => void) | undefined));
                    this._onMouse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onMouse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onMouse_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnMouseAttribute((undefined as ((event: MouseEvent) => void) | undefined));
                }
            }
        }
        if (this._onTouch_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTouch_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTouchAttribute((this._onTouch_0_0value as ((event: TouchEvent) => void) | undefined));
                    this._onTouch_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTouch_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTouch_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTouchAttribute((undefined as ((event: TouchEvent) => void) | undefined));
                }
            }
        }
        if (this._onKeyEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onKeyEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnKeyEventAttribute((this._onKeyEvent_0_0value as ((event: KeyEvent) => void) | undefined));
                    this._onKeyEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onKeyEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onKeyEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnKeyEventAttribute((undefined as ((event: KeyEvent) => void) | undefined));
                }
            }
        }
        if (this._onDigitalCrown_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDigitalCrown_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDigitalCrownAttribute((this._onDigitalCrown_0_0value as ((value0: CrownEvent) => void) | undefined));
                    this._onDigitalCrown_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDigitalCrown_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDigitalCrown_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDigitalCrownAttribute((undefined as ((value0: CrownEvent) => void) | undefined));
                }
            }
        }
        if (this._onKeyPreIme_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onKeyPreIme_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnKeyPreImeAttribute((this._onKeyPreIme_0_0value as ((value0: KeyEvent) => boolean) | undefined));
                    this._onKeyPreIme_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onKeyPreIme_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onKeyPreIme_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnKeyPreImeAttribute((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onKeyEventDispatch_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onKeyEventDispatch_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnKeyEventDispatchAttribute((this._onKeyEventDispatch_0_0value as ((value0: KeyEvent) => boolean) | undefined));
                    this._onKeyEventDispatch_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onKeyEventDispatch_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onKeyEventDispatch_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnKeyEventDispatchAttribute((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (this._onFocusAxisEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFocusAxisEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFocusAxisEventAttribute((this._onFocusAxisEvent_0_0value as ((value0: FocusAxisEvent) => void) | undefined));
                    this._onFocusAxisEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFocusAxisEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFocusAxisEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFocusAxisEventAttribute((undefined as ((value0: FocusAxisEvent) => void) | undefined));
                }
            }
        }
        if (this._onAxisEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAxisEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAxisEventAttribute((this._onAxisEvent_0_0value as ((value0: AxisEvent) => void) | undefined));
                    this._onAxisEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAxisEvent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAxisEvent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAxisEventAttribute((undefined as ((value0: AxisEvent) => void) | undefined));
                }
            }
        }
        if (this._focusable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._focusable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFocusableAttribute((this._focusable_0_0value as boolean | undefined));
                    this._focusable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._focusable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._focusable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFocusableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._nextFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._nextFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setNextFocusAttribute((this._nextFocus_0_0value as FocusMovement | undefined));
                    this._nextFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._nextFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._nextFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setNextFocusAttribute((undefined as FocusMovement | undefined));
                }
            }
        }
        if (this._tabStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._tabStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTabStopAttribute((this._tabStop_0_0value as boolean | undefined));
                    this._tabStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._tabStop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._tabStop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTabStopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFocusAttribute((this._onFocus_0_0value as (() => void) | undefined));
                    this._onFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFocusAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onBlur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onBlur_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnBlurAttribute((this._onBlur_0_0value as (() => void) | undefined));
                    this._onBlur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onBlur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onBlur_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnBlurAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._tabIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._tabIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTabIndexAttribute((this._tabIndex_0_0value as number | undefined));
                    this._tabIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._tabIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._tabIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTabIndexAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._defaultFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._defaultFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDefaultFocusAttribute((this._defaultFocus_0_0value as boolean | undefined));
                    this._defaultFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._defaultFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._defaultFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDefaultFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._groupDefaultFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._groupDefaultFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGroupDefaultFocusAttribute((this._groupDefaultFocus_0_0value as boolean | undefined));
                    this._groupDefaultFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._groupDefaultFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._groupDefaultFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGroupDefaultFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._focusOnTouch_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._focusOnTouch_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFocusOnTouchAttribute((this._focusOnTouch_0_0value as boolean | undefined));
                    this._focusOnTouch_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._focusOnTouch_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._focusOnTouch_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFocusOnTouchAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._focusBox_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._focusBox_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFocusBoxAttribute((this._focusBox_0_0value as FocusBoxStyle | undefined));
                    this._focusBox_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._focusBox_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._focusBox_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFocusBoxAttribute((undefined as FocusBoxStyle | undefined));
                }
            }
        }
        if (this._animation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._animation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAnimationAttribute((this._animation_0_0value as AnimateParam | undefined));
                    this._animation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._animation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._animation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAnimationAttribute((undefined as AnimateParam | undefined));
                }
            }
        }
        if (this._transition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._transition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTransition0Attribute((this._transition_0_0value as TransitionEffect | undefined));
                    this._transition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._transition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._transition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTransition0Attribute((undefined as TransitionEffect | undefined));
                }
            }
        }
        if (this._motionBlur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._motionBlur_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMotionBlurAttribute((this._motionBlur_0_0value as MotionBlurOptions | undefined));
                    this._motionBlur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._motionBlur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._motionBlur_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMotionBlurAttribute((undefined as MotionBlurOptions | undefined));
                }
            }
        }
        if (this._brightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._brightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBrightnessAttribute((this._brightness_0_0value as number | undefined));
                    this._brightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._brightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._brightness_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBrightnessAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._contrast_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._contrast_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setContrastAttribute((this._contrast_0_0value as number | undefined));
                    this._contrast_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._contrast_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._contrast_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setContrastAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._grayscale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._grayscale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGrayscaleAttribute((this._grayscale_0_0value as number | undefined));
                    this._grayscale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._grayscale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._grayscale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGrayscaleAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._colorBlend_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._colorBlend_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorBlendAttribute((this._colorBlend_0_0value as Color | string | Resource | undefined));
                    this._colorBlend_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._colorBlend_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._colorBlend_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorBlendAttribute((undefined as Color | string | Resource | undefined));
                }
            }
        }
        if (this._saturate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._saturate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSaturateAttribute((this._saturate_0_0value as number | undefined));
                    this._saturate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._saturate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._saturate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSaturateAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._sepia_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sepia_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSepiaAttribute((this._sepia_0_0value as number | undefined));
                    this._sepia_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sepia_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sepia_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSepiaAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._invert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._invert_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setInvertAttribute((this._invert_0_0value as number | InvertOptions | undefined));
                    this._invert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._invert_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._invert_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setInvertAttribute((undefined as number | InvertOptions | undefined));
                }
            }
        }
        if (this._hueRotate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._hueRotate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setHueRotateAttribute((this._hueRotate_0_0value as number | string | undefined));
                    this._hueRotate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._hueRotate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._hueRotate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setHueRotateAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._useShadowBatching_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._useShadowBatching_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setUseShadowBatchingAttribute((this._useShadowBatching_0_0value as boolean | undefined));
                    this._useShadowBatching_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._useShadowBatching_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._useShadowBatching_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setUseShadowBatchingAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._useEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._useEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setUseEffect0Attribute((this._useEffect_0_0value as boolean | undefined));
                    this._useEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._useEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._useEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setUseEffect0Attribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._renderGroup_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderGroup_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRenderGroupAttribute((this._renderGroup_0_0value as boolean | undefined));
                    this._renderGroup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderGroup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderGroup_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRenderGroupAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._freeze_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._freeze_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFreezeAttribute((this._freeze_0_0value as boolean | undefined));
                    this._freeze_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._freeze_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._freeze_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFreezeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._translate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._translate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTranslateAttribute((this._translate_0_0value as TranslateOptions | undefined));
                    this._translate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._translate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._translate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTranslateAttribute((undefined as TranslateOptions | undefined));
                }
            }
        }
        if (this._scale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._scale_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setScaleAttribute((this._scale_0_0value as ScaleOptions | undefined));
                    this._scale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._scale_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._scale_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setScaleAttribute((undefined as ScaleOptions | undefined));
                }
            }
        }
        if (this._rotate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._rotate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRotateAttribute((this._rotate_0_0value as RotateOptions | RotateAngleOptions | undefined));
                    this._rotate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rotate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rotate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRotateAttribute((undefined as RotateOptions | RotateAngleOptions | undefined));
                }
            }
        }
        if (this._transform_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._transform_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTransformAttribute((this._transform_0_0value as matrix4.Matrix4Transit | undefined));
                    this._transform_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._transform_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._transform_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTransformAttribute((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (this._transform3D_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._transform3D_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTransform3DAttribute((this._transform3D_0_0value as matrix4.Matrix4Transit | undefined));
                    this._transform3D_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._transform3D_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._transform3D_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTransform3DAttribute((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (this._onAppear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAppear_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAppearAttribute((this._onAppear_0_0value as (() => void) | undefined));
                    this._onAppear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAppear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAppear_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAppearAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onDisAppear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDisAppear_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDisAppearAttribute((this._onDisAppear_0_0value as (() => void) | undefined));
                    this._onDisAppear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDisAppear_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDisAppear_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDisAppearAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onAttach_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAttach_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAttachAttribute((this._onAttach_0_0value as VoidCallback | undefined));
                    this._onAttach_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAttach_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAttach_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAttachAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onDetach_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDetach_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDetachAttribute((this._onDetach_0_0value as VoidCallback | undefined));
                    this._onDetach_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDetach_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDetach_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDetachAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onAreaChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAreaChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAreaChangeAttribute((this._onAreaChange_0_0value as ((oldValue: Area,newValue: Area) => void) | undefined));
                    this._onAreaChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAreaChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAreaChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAreaChangeAttribute((undefined as ((oldValue: Area,newValue: Area) => void) | undefined));
                }
            }
        }
        if (this._visibility_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._visibility_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVisibilityAttribute((this._visibility_0_0value as Visibility | undefined));
                    this._visibility_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._visibility_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._visibility_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVisibilityAttribute((undefined as Visibility | undefined));
                }
            }
        }
        if (this._flexGrow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._flexGrow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFlexGrowAttribute((this._flexGrow_0_0value as number | undefined));
                    this._flexGrow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._flexGrow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._flexGrow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFlexGrowAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._flexShrink_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._flexShrink_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFlexShrinkAttribute((this._flexShrink_0_0value as number | undefined));
                    this._flexShrink_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._flexShrink_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._flexShrink_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFlexShrinkAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._flexBasis_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._flexBasis_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFlexBasisAttribute((this._flexBasis_0_0value as number | string | undefined));
                    this._flexBasis_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._flexBasis_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._flexBasis_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFlexBasisAttribute((undefined as number | string | undefined));
                }
            }
        }
        if (this._alignSelf_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignSelf_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignSelfAttribute((this._alignSelf_0_0value as ItemAlign | undefined));
                    this._alignSelf_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignSelf_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignSelf_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignSelfAttribute((undefined as ItemAlign | undefined));
                }
            }
        }
        if (this._displayPriority_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._displayPriority_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDisplayPriorityAttribute((this._displayPriority_0_0value as number | undefined));
                    this._displayPriority_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._displayPriority_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._displayPriority_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDisplayPriorityAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._zIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._zIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setZIndexAttribute((this._zIndex_0_0value as number | undefined));
                    this._zIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._zIndex_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._zIndex_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setZIndexAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._direction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._direction_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDirectionAttribute((this._direction_0_0value as Direction | undefined));
                    this._direction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._direction_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._direction_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDirectionAttribute((undefined as Direction | undefined));
                }
            }
        }
        if (this._align_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._align_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignAttribute((this._align_0_0value as Alignment | undefined));
                    this._align_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._align_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._align_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignAttribute((undefined as Alignment | undefined));
                }
            }
        }
        if (this._position_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._position_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPositionAttribute((this._position_0_0value as Position | Edges | LocalizedEdges | undefined));
                    this._position_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._position_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._position_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPositionAttribute((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (this._markAnchor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._markAnchor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMarkAnchorAttribute((this._markAnchor_0_0value as Position | LocalizedPosition | undefined));
                    this._markAnchor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._markAnchor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._markAnchor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMarkAnchorAttribute((undefined as Position | LocalizedPosition | undefined));
                }
            }
        }
        if (this._offset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._offset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOffsetAttribute((this._offset_0_0value as Position | Edges | LocalizedEdges | undefined));
                    this._offset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._offset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._offset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOffsetAttribute((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (this._enabled_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enabled_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnabledAttribute((this._enabled_0_0value as boolean | undefined));
                    this._enabled_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enabled_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enabled_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnabledAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._alignRules_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignRules_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignRulesAttribute((this._alignRules_0_0value as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                    this._alignRules_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignRules_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignRules_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignRulesAttribute((undefined as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                }
            }
        }
        if (this._aspectRatio_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._aspectRatio_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAspectRatioAttribute((this._aspectRatio_0_0value as number | undefined));
                    this._aspectRatio_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._aspectRatio_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._aspectRatio_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAspectRatioAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._clickEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._clickEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setClickEffectAttribute((this._clickEffect_0_0value as ClickEffect | null | undefined));
                    this._clickEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._clickEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._clickEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setClickEffectAttribute((undefined as ClickEffect | null | undefined));
                }
            }
        }
        if (this._onDragStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDragStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDragStartAttribute((this._onDragStart_0_0value as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined));
                    this._onDragStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDragStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDragStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDragStartAttribute((undefined as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined));
                }
            }
        }
        if (this._onDragEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDragEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDragEnterAttribute((this._onDragEnter_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    this._onDragEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDragEnter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDragEnter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDragEnterAttribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (this._onDragMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDragMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDragMoveAttribute((this._onDragMove_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    this._onDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDragMove_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDragMove_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDragMoveAttribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (this._onDragLeave_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDragLeaveAttribute((this._onDragLeave_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    this._onDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDragLeave_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDragLeave_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDragLeaveAttribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (this._onDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDrop0Attribute((this._onDrop_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    this._onDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDrop_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDrop0Attribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (this._onDragEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDragEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDragEndAttribute((this._onDragEnd_0_0value as ((event: DragEvent,extraParams?: string) => void) | undefined));
                    this._onDragEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDragEnd_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDragEnd_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDragEndAttribute((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (this._allowDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._allowDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookAllowDrop(peer, (this._allowDrop_0_0value as Array<uniformTypeDescriptor.UniformDataType> | null | undefined));
                    this._allowDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._allowDrop_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._allowDrop_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookAllowDrop(peer, (undefined as Array<uniformTypeDescriptor.UniformDataType> | null | undefined));
                }
            }
        }
        if (this._draggable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._draggable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDraggableAttribute((this._draggable_0_0value as boolean | undefined));
                    this._draggable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._draggable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._draggable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDraggableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._dragPreview_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dragPreview_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDragPreview0Attribute((this._dragPreview_0_0value as CustomBuilder | DragItemInfo | string | undefined));
                    this._dragPreview_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dragPreview_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dragPreview_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDragPreview0Attribute((undefined as CustomBuilder | DragItemInfo | string | undefined));
                }
            }
        }
        if (this._onPreDrag_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPreDrag_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPreDragAttribute((this._onPreDrag_0_0value as ((value0: PreDragStatus) => void) | undefined));
                    this._onPreDrag_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPreDrag_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPreDrag_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPreDragAttribute((undefined as ((value0: PreDragStatus) => void) | undefined));
                }
            }
        }
        if (this._linearGradient_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._linearGradient_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLinearGradientAttribute((this._linearGradient_0_0value as LinearGradientOptions | undefined));
                    this._linearGradient_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._linearGradient_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._linearGradient_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLinearGradientAttribute((undefined as LinearGradientOptions | undefined));
                }
            }
        }
        if (this._sweepGradient_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sweepGradient_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSweepGradientAttribute((this._sweepGradient_0_0value as SweepGradientOptions | undefined));
                    this._sweepGradient_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sweepGradient_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sweepGradient_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSweepGradientAttribute((undefined as SweepGradientOptions | undefined));
                }
            }
        }
        if (this._radialGradient_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._radialGradient_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRadialGradientAttribute((this._radialGradient_0_0value as RadialGradientOptions | undefined));
                    this._radialGradient_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._radialGradient_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._radialGradient_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRadialGradientAttribute((undefined as RadialGradientOptions | undefined));
                }
            }
        }
        if (this._motionPath_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._motionPath_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMotionPathAttribute((this._motionPath_0_0value as MotionPathOptions | undefined));
                    this._motionPath_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._motionPath_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._motionPath_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMotionPathAttribute((undefined as MotionPathOptions | undefined));
                }
            }
        }
        if (this._shadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._shadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShadowAttribute((this._shadow_0_0value as ShadowOptions | ShadowStyle | undefined));
                    this._shadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._shadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._shadow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShadowAttribute((undefined as ShadowOptions | ShadowStyle | undefined));
                }
            }
        }
        if (this._clip_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._clip_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setClipAttribute((this._clip_0_0value as boolean | undefined));
                    this._clip_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._clip_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._clip_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setClipAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._clipShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._clipShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setClipShapeAttribute((this._clipShape_0_0value as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                    this._clipShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._clipShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._clipShape_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setClipShapeAttribute((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                }
            }
        }
        if (this._mask_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._mask_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaskAttribute((this._mask_0_0value as ProgressMask | undefined));
                    this._mask_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._mask_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._mask_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaskAttribute((undefined as ProgressMask | undefined));
                }
            }
        }
        if (this._maskShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._maskShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMaskShapeAttribute((this._maskShape_0_0value as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                    this._maskShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._maskShape_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._maskShape_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMaskShapeAttribute((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                }
            }
        }
        if (this._key_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._key_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setKeyAttribute((this._key_0_0value as string | undefined));
                    this._key_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._key_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._key_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setKeyAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._id_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._id_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIdAttribute((this._id_0_0value as string | undefined));
                    this._id_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._id_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._id_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIdAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._geometryTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._geometryTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGeometryTransition0Attribute((this._geometryTransition_0_0value as string | undefined));
                    this._geometryTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._geometryTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._geometryTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGeometryTransition0Attribute((undefined as string | undefined));
                }
            }
        }
        if (this._restoreId_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._restoreId_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRestoreIdAttribute((this._restoreId_0_0value as number | undefined));
                    this._restoreId_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._restoreId_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._restoreId_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRestoreIdAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._sphericalEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sphericalEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSphericalEffectAttribute((this._sphericalEffect_0_0value as number | undefined));
                    this._sphericalEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sphericalEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sphericalEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSphericalEffectAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._lightUpEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._lightUpEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLightUpEffectAttribute((this._lightUpEffect_0_0value as number | undefined));
                    this._lightUpEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._lightUpEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._lightUpEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLightUpEffectAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._pixelStretchEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pixelStretchEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPixelStretchEffectAttribute((this._pixelStretchEffect_0_0value as PixelStretchEffectOptions | undefined));
                    this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPixelStretchEffectAttribute((undefined as PixelStretchEffectOptions | undefined));
                }
            }
        }
        if (this._accessibilityGroup_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityGroup_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityGroupWithValueAttribute((this._accessibilityGroup_0_0value as boolean | undefined));
                    this._accessibilityGroup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityGroup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityGroup_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityGroupWithValueAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._accessibilityText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityText_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityTextOfStringTypeAttribute((this._accessibilityText_0_0value as string | undefined));
                    this._accessibilityText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityText_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityText_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityTextOfStringTypeAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._accessibilityNextFocusId_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityNextFocusId_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityNextFocusIdAttribute((this._accessibilityNextFocusId_0_0value as string | undefined));
                    this._accessibilityNextFocusId_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityNextFocusId_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityNextFocusId_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityNextFocusIdAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._accessibilityDefaultFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityDefaultFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityDefaultFocusAttribute((this._accessibilityDefaultFocus_0_0value as boolean | undefined));
                    this._accessibilityDefaultFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityDefaultFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityDefaultFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityDefaultFocusAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._accessibilityUseSamePage_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityUseSamePage_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityUseSamePageAttribute((this._accessibilityUseSamePage_0_0value as AccessibilitySamePageMode | undefined));
                    this._accessibilityUseSamePage_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityUseSamePage_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityUseSamePage_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityUseSamePageAttribute((undefined as AccessibilitySamePageMode | undefined));
                }
            }
        }
        if (this._accessibilityScrollTriggerable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityScrollTriggerable_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityScrollTriggerableAttribute((this._accessibilityScrollTriggerable_0_0value as boolean | undefined));
                    this._accessibilityScrollTriggerable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityScrollTriggerable_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityScrollTriggerable_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityScrollTriggerableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._accessibilityText_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityText_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityTextOfResourceTypeAttribute((this._accessibilityText_1_0value as Resource | undefined));
                    this._accessibilityText_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityText_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityText_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityTextOfResourceTypeAttribute((undefined as Resource | undefined));
                }
            }
        }
        if (this._accessibilityRole_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityRole_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityRoleAttribute((this._accessibilityRole_0_0value as AccessibilityRoleType | undefined));
                    this._accessibilityRole_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityRole_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityRole_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityRoleAttribute((undefined as AccessibilityRoleType | undefined));
                }
            }
        }
        if (this._onAccessibilityFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAccessibilityFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAccessibilityFocusAttribute((this._onAccessibilityFocus_0_0value as AccessibilityFocusCallback | undefined));
                    this._onAccessibilityFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAccessibilityFocus_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAccessibilityFocus_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAccessibilityFocusAttribute((undefined as AccessibilityFocusCallback | undefined));
                }
            }
        }
        if (this._onAccessibilityActionIntercept_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAccessibilityActionIntercept_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAccessibilityActionInterceptAttribute((this._onAccessibilityActionIntercept_0_0value as AccessibilityActionInterceptCallback | undefined));
                    this._onAccessibilityActionIntercept_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAccessibilityActionIntercept_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAccessibilityActionIntercept_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAccessibilityActionInterceptAttribute((undefined as AccessibilityActionInterceptCallback | undefined));
                }
            }
        }
        if (this._accessibilityTextHint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityTextHint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityTextHintAttribute((this._accessibilityTextHint_0_0value as string | undefined));
                    this._accessibilityTextHint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityTextHint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityTextHint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityTextHintAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._accessibilityDescription_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityDescription_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityDescriptionOfStringTypeAttribute((this._accessibilityDescription_0_0value as string | undefined));
                    this._accessibilityDescription_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityDescription_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityDescription_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityDescriptionOfStringTypeAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._accessibilityDescription_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityDescription_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityDescriptionOfResourceTypeAttribute((this._accessibilityDescription_1_0value as Resource | undefined));
                    this._accessibilityDescription_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityDescription_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityDescription_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityDescriptionOfResourceTypeAttribute((undefined as Resource | undefined));
                }
            }
        }
        if (this._accessibilityLevel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityLevel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityLevelAttribute((this._accessibilityLevel_0_0value as string | undefined));
                    this._accessibilityLevel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityLevel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityLevel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityLevelAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._accessibilityVirtualNode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityVirtualNode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityVirtualNodeAttribute((this._accessibilityVirtualNode_0_0value as CustomBuilder | undefined));
                    this._accessibilityVirtualNode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityVirtualNode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityVirtualNode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityVirtualNodeAttribute((undefined as CustomBuilder | undefined));
                }
            }
        }
        if (this._accessibilityChecked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityChecked_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityCheckedAttribute((this._accessibilityChecked_0_0value as boolean | undefined));
                    this._accessibilityChecked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityChecked_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityChecked_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityCheckedAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._accessibilitySelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilitySelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilitySelectedAttribute((this._accessibilitySelected_0_0value as boolean | undefined));
                    this._accessibilitySelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilitySelected_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilitySelected_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilitySelectedAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._obscured_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._obscured_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setObscuredAttribute((this._obscured_0_0value as Array<ObscuredReasons> | undefined));
                    this._obscured_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._obscured_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._obscured_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setObscuredAttribute((undefined as Array<ObscuredReasons> | undefined));
                }
            }
        }
        if (this._reuseId_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._reuseId_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setReuseIdAttribute((this._reuseId_0_0value as string | undefined));
                    this._reuseId_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._reuseId_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._reuseId_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setReuseIdAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._reuse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._reuse_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setReuseAttribute((this._reuse_0_0value as ReuseOptions | undefined));
                    this._reuse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._reuse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._reuse_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setReuseAttribute((undefined as ReuseOptions | undefined));
                }
            }
        }
        if (this._renderFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRenderFitAttribute((this._renderFit_0_0value as RenderFit | undefined));
                    this._renderFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderFit_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderFit_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRenderFitAttribute((undefined as RenderFit | undefined));
                }
            }
        }
        if (this._backgroundBrightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundBrightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundBrightnessAttribute((this._backgroundBrightness_0_0value as BackgroundBrightnessOptions | undefined));
                    this._backgroundBrightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundBrightness_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundBrightness_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundBrightnessAttribute((undefined as BackgroundBrightnessOptions | undefined));
                }
            }
        }
        if (this._onGestureJudgeBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGestureJudgeBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGestureJudgeBeginAttribute((this._onGestureJudgeBegin_0_0value as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined));
                    this._onGestureJudgeBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGestureJudgeBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGestureJudgeBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGestureJudgeBeginAttribute((undefined as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined));
                }
            }
        }
        if (this._onGestureRecognizerJudgeBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGestureRecognizerJudgeBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGestureRecognizerJudgeBegin0Attribute((this._onGestureRecognizerJudgeBegin_0_0value as GestureRecognizerJudgeBeginCallback | undefined));
                    this._onGestureRecognizerJudgeBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGestureRecognizerJudgeBegin_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGestureRecognizerJudgeBegin_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGestureRecognizerJudgeBegin0Attribute((undefined as GestureRecognizerJudgeBeginCallback | undefined));
                }
            }
        }
        if (this._shouldBuiltInRecognizerParallelWith_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._shouldBuiltInRecognizerParallelWith_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShouldBuiltInRecognizerParallelWithAttribute((this._shouldBuiltInRecognizerParallelWith_0_0value as ShouldBuiltInRecognizerParallelWithCallback | undefined));
                    this._shouldBuiltInRecognizerParallelWith_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._shouldBuiltInRecognizerParallelWith_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._shouldBuiltInRecognizerParallelWith_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShouldBuiltInRecognizerParallelWithAttribute((undefined as ShouldBuiltInRecognizerParallelWithCallback | undefined));
                }
            }
        }
        if (this._monopolizeEvents_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._monopolizeEvents_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMonopolizeEventsAttribute((this._monopolizeEvents_0_0value as boolean | undefined));
                    this._monopolizeEvents_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._monopolizeEvents_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._monopolizeEvents_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMonopolizeEventsAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onTouchIntercept_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onTouchIntercept_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnTouchInterceptAttribute((this._onTouchIntercept_0_0value as ((value0: TouchEvent) => HitTestMode) | undefined));
                    this._onTouchIntercept_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onTouchIntercept_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onTouchIntercept_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnTouchInterceptAttribute((undefined as ((value0: TouchEvent) => HitTestMode) | undefined));
                }
            }
        }
        if (this._onSizeChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onSizeChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnSizeChangeAttribute((this._onSizeChange_0_0value as SizeChangeCallback | undefined));
                    this._onSizeChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onSizeChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onSizeChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnSizeChangeAttribute((undefined as SizeChangeCallback | undefined));
                }
            }
        }
        if (this._accessibilityFocusDrawLevel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityFocusDrawLevel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityFocusDrawLevelAttribute((this._accessibilityFocusDrawLevel_0_0value as FocusDrawLevel | undefined));
                    this._accessibilityFocusDrawLevel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityFocusDrawLevel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityFocusDrawLevel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityFocusDrawLevelAttribute((undefined as FocusDrawLevel | undefined));
                }
            }
        }
        if (this._expandSafeArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._expandSafeArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setExpandSafeAreaAttribute((this._expandSafeArea_0_0value as Array<SafeAreaType> | undefined | undefined), (this._expandSafeArea_0_1value as Array<SafeAreaEdge> | undefined | undefined));
                    this._expandSafeArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._expandSafeArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._expandSafeArea_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setExpandSafeAreaAttribute((undefined as Array<SafeAreaType> | undefined | undefined), (undefined as Array<SafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (this._background_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._background_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundAttribute((this._background_0_0value as CustomBuilder | undefined), (this._background_0_1value as BackgroundOptions | undefined | undefined));
                    this._background_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._background_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._background_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundAttribute((undefined as CustomBuilder | undefined), (undefined as BackgroundOptions | undefined | undefined));
                }
            }
        }
        if (this._backgroundImage_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundImage_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundImage0Attribute((this._backgroundImage_0_0value as ResourceStr | image.PixelMap | undefined));
                    this._backgroundImage_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundImage_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundImage_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundImage0Attribute((undefined as ResourceStr | image.PixelMap | undefined));
                }
            }
        }
        if (this._backgroundImage_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundImage_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundImage1Attribute((this._backgroundImage_1_0value as ResourceStr | image.PixelMap | undefined), (this._backgroundImage_1_1value as BackgroundImageOptions | undefined | undefined));
                    this._backgroundImage_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundImage_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundImage_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundImage1Attribute((undefined as ResourceStr | image.PixelMap | undefined), (undefined as BackgroundImageOptions | undefined | undefined));
                }
            }
        }
        if (this._backgroundImage_2_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundImage_2_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundImage2Attribute((this._backgroundImage_2_0value as ResourceStr | image.PixelMap | undefined), (this._backgroundImage_2_1value as ImageRepeat | undefined | undefined));
                    this._backgroundImage_2_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundImage_2_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundImage_2_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundImage2Attribute((undefined as ResourceStr | image.PixelMap | undefined), (undefined as ImageRepeat | undefined | undefined));
                }
            }
        }
        if (this._backgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundBlurStyleAttribute((this._backgroundBlurStyle_0_0value as BlurStyle | undefined), (this._backgroundBlurStyle_0_1value as BackgroundBlurStyleOptions | undefined | undefined), (this._backgroundBlurStyle_0_2value as SystemAdaptiveOptions | undefined | undefined));
                    this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundBlurStyleAttribute((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (this._backgroundEffect_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundEffect_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundEffect1Attribute((this._backgroundEffect_1_0value as BackgroundEffectOptions | undefined), (this._backgroundEffect_1_1value as SystemAdaptiveOptions | undefined | undefined));
                    this._backgroundEffect_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundEffect_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundEffect_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundEffect1Attribute((undefined as BackgroundEffectOptions | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (this._foregroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._foregroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setForegroundBlurStyleAttribute((this._foregroundBlurStyle_0_0value as BlurStyle | undefined), (this._foregroundBlurStyle_0_1value as ForegroundBlurStyleOptions | undefined | undefined), (this._foregroundBlurStyle_0_2value as SystemAdaptiveOptions | undefined | undefined));
                    this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setForegroundBlurStyleAttribute((undefined as BlurStyle | undefined), (undefined as ForegroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (this._onClick_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onClick_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnClick1Attribute((this._onClick_1_0value as ((event: ClickEvent) => void) | undefined), (this._onClick_1_1value as number | undefined));
                    this._onClick_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onClick_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onClick_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnClick1Attribute((undefined as ((event: ClickEvent) => void) | undefined), (undefined as number | undefined));
                }
            }
        }
        if (this._focusScopeId_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._focusScopeId_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFocusScopeIdAttribute((this._focusScopeId_0_0value as string | undefined), (this._focusScopeId_0_1value as boolean | undefined | undefined), (this._focusScopeId_0_2value as boolean | undefined | undefined));
                    this._focusScopeId_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._focusScopeId_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._focusScopeId_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFocusScopeIdAttribute((undefined as string | undefined), (undefined as boolean | undefined | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (this._focusScopePriority_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._focusScopePriority_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFocusScopePriorityAttribute((this._focusScopePriority_0_0value as string | undefined), (this._focusScopePriority_0_1value as FocusPriority | undefined | undefined));
                    this._focusScopePriority_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._focusScopePriority_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._focusScopePriority_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFocusScopePriorityAttribute((undefined as string | undefined), (undefined as FocusPriority | undefined | undefined));
                }
            }
        }
        if (this._transition_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._transition_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTransition1Attribute((this._transition_1_0value as TransitionEffect | undefined), (this._transition_1_1value as TransitionFinishCallback | undefined));
                    this._transition_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._transition_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._transition_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTransition1Attribute((undefined as TransitionEffect | undefined), (undefined as TransitionFinishCallback | undefined));
                }
            }
        }
        if (this._blur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blur_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlurAttribute((this._blur_0_0value as number | undefined), (this._blur_0_1value as BlurOptions | undefined | undefined), (this._blur_0_2value as SystemAdaptiveOptions | undefined | undefined));
                    this._blur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blur_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlurAttribute((undefined as number | undefined), (undefined as BlurOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (this._linearGradientBlur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._linearGradientBlur_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setLinearGradientBlurAttribute((this._linearGradientBlur_0_0value as number | undefined), (this._linearGradientBlur_0_1value as LinearGradientBlurOptions | undefined));
                    this._linearGradientBlur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._linearGradientBlur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._linearGradientBlur_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setLinearGradientBlurAttribute((undefined as number | undefined), (undefined as LinearGradientBlurOptions | undefined));
                }
            }
        }
        if (this._systemBarEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._systemBarEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSystemBarEffectAttribute();
                    this._systemBarEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._systemBarEffect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._systemBarEffect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSystemBarEffectAttribute();
                }
            }
        }
        if (this._useEffect_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._useEffect_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setUseEffect1Attribute((this._useEffect_1_0value as boolean | undefined), (this._useEffect_1_1value as EffectType | undefined));
                    this._useEffect_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._useEffect_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._useEffect_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setUseEffect1Attribute((undefined as boolean | undefined), (undefined as EffectType | undefined));
                }
            }
        }
        if (this._backdropBlur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backdropBlur_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackdropBlurAttribute((this._backdropBlur_0_0value as number | undefined), (this._backdropBlur_0_1value as BlurOptions | undefined | undefined), (this._backdropBlur_0_2value as SystemAdaptiveOptions | undefined | undefined));
                    this._backdropBlur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backdropBlur_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backdropBlur_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackdropBlurAttribute((undefined as number | undefined), (undefined as BlurOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (this._sharedTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sharedTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSharedTransitionAttribute((this._sharedTransition_0_0value as string | undefined), (this._sharedTransition_0_1value as sharedTransitionOptions | undefined | undefined));
                    this._sharedTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sharedTransition_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sharedTransition_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSharedTransitionAttribute((undefined as string | undefined), (undefined as sharedTransitionOptions | undefined | undefined));
                }
            }
        }
        if (this._chainMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._chainMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setChainModeAttribute((this._chainMode_0_0value as Axis | undefined), (this._chainMode_0_1value as ChainStyle | undefined));
                    this._chainMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._chainMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._chainMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setChainModeAttribute((undefined as Axis | undefined), (undefined as ChainStyle | undefined));
                }
            }
        }
        if (this._onDrop_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDrop_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDrop1Attribute((this._onDrop_1_0value as OnDragEventCallback | undefined), (this._onDrop_1_1value as DropOptions | undefined | undefined));
                    this._onDrop_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDrop_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDrop_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDrop1Attribute((undefined as OnDragEventCallback | undefined), (undefined as DropOptions | undefined | undefined));
                }
            }
        }
        if (this._dragPreview_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dragPreview_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDragPreview1Attribute((this._dragPreview_1_0value as CustomBuilder | DragItemInfo | string | undefined), (this._dragPreview_1_1value as PreviewConfiguration | undefined | undefined));
                    this._dragPreview_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dragPreview_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dragPreview_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDragPreview1Attribute((undefined as CustomBuilder | DragItemInfo | string | undefined), (undefined as PreviewConfiguration | undefined | undefined));
                }
            }
        }
        if (this._dragPreviewOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dragPreviewOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    hookDragPreviewOptions(peer, (this._dragPreviewOptions_0_0value as DragPreviewOptions | undefined), (this._dragPreviewOptions_0_1value as DragInteractionOptions | undefined | undefined));
                    this._dragPreviewOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dragPreviewOptions_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dragPreviewOptions_0_flag = AttributeUpdaterFlag.INITIAL;
                    hookDragPreviewOptions(peer, (undefined as DragPreviewOptions | undefined), (undefined as DragInteractionOptions | undefined | undefined));
                }
            }
        }
        if (this._overlay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._overlay_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOverlayAttribute((this._overlay_0_0value as string | CustomBuilder | ComponentContent | undefined), (this._overlay_0_1value as OverlayOptions | undefined | undefined));
                    this._overlay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._overlay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._overlay_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOverlayAttribute((undefined as string | CustomBuilder | ComponentContent | undefined), (undefined as OverlayOptions | undefined | undefined));
                }
            }
        }
        if (this._blendMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._blendMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBlendModeAttribute((this._blendMode_0_0value as BlendMode | undefined), (this._blendMode_0_1value as BlendApplyType | undefined | undefined));
                    this._blendMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._blendMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._blendMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBlendModeAttribute((undefined as BlendMode | undefined), (undefined as BlendApplyType | undefined | undefined));
                }
            }
        }
        if (this._geometryTransition_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._geometryTransition_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setGeometryTransition1Attribute((this._geometryTransition_1_0value as string | undefined), (this._geometryTransition_1_1value as GeometryTransitionOptions | undefined | undefined));
                    this._geometryTransition_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._geometryTransition_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._geometryTransition_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setGeometryTransition1Attribute((undefined as string | undefined), (undefined as GeometryTransitionOptions | undefined | undefined));
                }
            }
        }
        if (this._bindTips_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindTips_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindTipsAttribute((this._bindTips_0_0value as TipsMessageType | undefined), (this._bindTips_0_1value as TipsOptions | undefined | undefined));
                    this._bindTips_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindTips_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindTips_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindTipsAttribute((undefined as TipsMessageType | undefined), (undefined as TipsOptions | undefined | undefined));
                }
            }
        }
        if (this._bindPopup_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindPopup_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindPopupAttribute((this._bindPopup_0_0value as boolean | undefined), (this._bindPopup_0_1value as PopupOptions | CustomPopupOptions | undefined));
                    this._bindPopup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindPopup_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindPopup_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindPopupAttribute((undefined as boolean | undefined), (undefined as PopupOptions | CustomPopupOptions | undefined));
                }
            }
        }
        if (this._bindMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindMenu0Attribute((this._bindMenu_0_0value as Array<MenuElement> | CustomBuilder | undefined), (this._bindMenu_0_1value as MenuOptions | undefined | undefined));
                    this._bindMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindMenu_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindMenu0Attribute((undefined as Array<MenuElement> | CustomBuilder | undefined), (undefined as MenuOptions | undefined | undefined));
                }
            }
        }
        if (this._bindMenu_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindMenu_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindMenu1Attribute((this._bindMenu_1_0value as boolean | undefined), (this._bindMenu_1_1value as Array<MenuElement> | CustomBuilder | undefined), (this._bindMenu_1_2value as MenuOptions | undefined | undefined));
                    this._bindMenu_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindMenu_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindMenu_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindMenu1Attribute((undefined as boolean | undefined), (undefined as Array<MenuElement> | CustomBuilder | undefined), (undefined as MenuOptions | undefined | undefined));
                }
            }
        }
        if (this._bindContextMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindContextMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindContextMenu0Attribute((this._bindContextMenu_0_0value as CustomBuilder | undefined), (this._bindContextMenu_0_1value as ResponseType | undefined), (this._bindContextMenu_0_2value as ContextMenuOptions | undefined | undefined));
                    this._bindContextMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindContextMenu_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindContextMenu_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindContextMenu0Attribute((undefined as CustomBuilder | undefined), (undefined as ResponseType | undefined), (undefined as ContextMenuOptions | undefined | undefined));
                }
            }
        }
        if (this._bindContextMenu_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindContextMenu_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindContextMenu1Attribute((this._bindContextMenu_1_0value as boolean | undefined), (this._bindContextMenu_1_1value as CustomBuilder | undefined), (this._bindContextMenu_1_2value as ContextMenuOptions | undefined | undefined));
                    this._bindContextMenu_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindContextMenu_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindContextMenu_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindContextMenu1Attribute((undefined as boolean | undefined), (undefined as CustomBuilder | undefined), (undefined as ContextMenuOptions | undefined | undefined));
                }
            }
        }
        if (this._bindContentCover_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindContentCover_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindContentCover0Attribute((this._bindContentCover_0_0value as boolean | Bindable<boolean> | undefined), (this._bindContentCover_0_1value as CustomBuilder | undefined), (this._bindContentCover_0_2value as ModalTransition | undefined | undefined));
                    this._bindContentCover_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindContentCover_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindContentCover_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindContentCover0Attribute((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as ModalTransition | undefined | undefined));
                }
            }
        }
        if (this._bindContentCover_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindContentCover_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindContentCover1Attribute((this._bindContentCover_1_0value as boolean | Bindable<boolean> | undefined), (this._bindContentCover_1_1value as CustomBuilder | undefined), (this._bindContentCover_1_2value as ContentCoverOptions | undefined | undefined));
                    this._bindContentCover_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindContentCover_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindContentCover_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindContentCover1Attribute((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as ContentCoverOptions | undefined | undefined));
                }
            }
        }
        if (this._bindSheet_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._bindSheet_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBindSheetAttribute((this._bindSheet_0_0value as boolean | Bindable<boolean> | undefined), (this._bindSheet_0_1value as CustomBuilder | undefined), (this._bindSheet_0_2value as SheetOptions | undefined | undefined));
                    this._bindSheet_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._bindSheet_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._bindSheet_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBindSheetAttribute((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as SheetOptions | undefined | undefined));
                }
            }
        }
        if (this._onVisibleAreaChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onVisibleAreaChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnVisibleAreaChangeAttribute((this._onVisibleAreaChange_0_0value as Array<number> | undefined), (this._onVisibleAreaChange_0_1value as VisibleAreaChangeCallback | undefined));
                    this._onVisibleAreaChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onVisibleAreaChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onVisibleAreaChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnVisibleAreaChangeAttribute((undefined as Array<number> | undefined), (undefined as VisibleAreaChangeCallback | undefined));
                }
            }
        }
        if (this._onVisibleAreaApproximateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onVisibleAreaApproximateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnVisibleAreaApproximateChangeAttribute((this._onVisibleAreaApproximateChange_0_0value as VisibleAreaEventOptions | undefined), (this._onVisibleAreaApproximateChange_0_1value as VisibleAreaChangeCallback | undefined));
                    this._onVisibleAreaApproximateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onVisibleAreaApproximateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onVisibleAreaApproximateChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnVisibleAreaApproximateChangeAttribute((undefined as VisibleAreaEventOptions | undefined), (undefined as VisibleAreaChangeCallback | undefined));
                }
            }
        }
        if (this._keyboardShortcut_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._keyboardShortcut_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setKeyboardShortcutAttribute((this._keyboardShortcut_0_0value as string | FunctionKey | undefined), (this._keyboardShortcut_0_1value as Array<ModifierKey> | undefined), (this._keyboardShortcut_0_2value as (() => void) | undefined | undefined));
                    this._keyboardShortcut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._keyboardShortcut_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._keyboardShortcut_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setKeyboardShortcutAttribute((undefined as string | FunctionKey | undefined), (undefined as Array<ModifierKey> | undefined), (undefined as (() => void) | undefined | undefined));
                }
            }
        }
        if (this._accessibilityGroup_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._accessibilityGroup_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAccessibilityGroupWithConfigAttribute((this._accessibilityGroup_1_0value as boolean | undefined), (this._accessibilityGroup_1_1value as AccessibilityOptions | undefined));
                    this._accessibilityGroup_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._accessibilityGroup_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._accessibilityGroup_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAccessibilityGroupWithConfigAttribute((undefined as boolean | undefined), (undefined as AccessibilityOptions | undefined));
                }
            }
        }
        if (this._onGestureRecognizerJudgeBegin_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onGestureRecognizerJudgeBegin_1_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnGestureRecognizerJudgeBegin1Attribute((this._onGestureRecognizerJudgeBegin_1_0value as GestureRecognizerJudgeBeginCallback | undefined), (this._onGestureRecognizerJudgeBegin_1_1value as boolean | undefined));
                    this._onGestureRecognizerJudgeBegin_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onGestureRecognizerJudgeBegin_1_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onGestureRecognizerJudgeBegin_1_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnGestureRecognizerJudgeBegin1Attribute((undefined as GestureRecognizerJudgeBeginCallback | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CommonMethodModifier): void {
        if (modifier._width_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._width_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.width(modifier._width_0_0value);
                    break;
                }
                default: {
                    this.width((undefined as Length | LayoutPolicy | undefined));
                }
            }
        }
        if (modifier._height_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._height_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.height(modifier._height_0_0value);
                    break;
                }
                default: {
                    this.height((undefined as Length | LayoutPolicy | undefined));
                }
            }
        }
        if (modifier._responseRegion_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._responseRegion_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.responseRegion(modifier._responseRegion_0_0value);
                    break;
                }
                default: {
                    this.responseRegion((undefined as Array<Rectangle> | Rectangle | undefined));
                }
            }
        }
        if (modifier._mouseResponseRegion_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mouseResponseRegion_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mouseResponseRegion(modifier._mouseResponseRegion_0_0value);
                    break;
                }
                default: {
                    this.mouseResponseRegion((undefined as Array<Rectangle> | Rectangle | undefined));
                }
            }
        }
        if (modifier._size_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._size_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.size(modifier._size_0_0value);
                    break;
                }
                default: {
                    this.size((undefined as SizeOptions | undefined));
                }
            }
        }
        if (modifier._constraintSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._constraintSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.constraintSize(modifier._constraintSize_0_0value);
                    break;
                }
                default: {
                    this.constraintSize((undefined as ConstraintSizeOptions | undefined));
                }
            }
        }
        if (modifier._hitTestBehavior_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hitTestBehavior_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hitTestBehavior(modifier._hitTestBehavior_0_0value);
                    break;
                }
                default: {
                    this.hitTestBehavior((undefined as HitTestMode | undefined));
                }
            }
        }
        if (modifier._onChildTouchTest_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onChildTouchTest_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onChildTouchTest(modifier._onChildTouchTest_0_0value);
                    break;
                }
                default: {
                    this.onChildTouchTest((undefined as ((value: Array<TouchTestInfo>) => TouchResult) | undefined));
                }
            }
        }
        if (modifier._layoutWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._layoutWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.layoutWeight(modifier._layoutWeight_0_0value);
                    break;
                }
                default: {
                    this.layoutWeight((undefined as number | string | undefined));
                }
            }
        }
        if (modifier._chainWeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._chainWeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainWeight(modifier._chainWeight_0_0value);
                    break;
                }
                default: {
                    this.chainWeight((undefined as ChainWeightOptions | undefined));
                }
            }
        }
        if (modifier._padding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._padding_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.padding(modifier._padding_0_0value);
                    break;
                }
                default: {
                    this.padding((undefined as Padding | Length | LocalizedPadding | undefined));
                }
            }
        }
        if (modifier._safeAreaPadding_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._safeAreaPadding_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.safeAreaPadding(modifier._safeAreaPadding_0_0value);
                    break;
                }
                default: {
                    this.safeAreaPadding((undefined as Padding | LengthMetrics | LocalizedPadding | undefined));
                }
            }
        }
        if (modifier._margin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._margin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.margin(modifier._margin_0_0value);
                    break;
                }
                default: {
                    this.margin((undefined as Padding | Length | LocalizedPadding | undefined));
                }
            }
        }
        if (modifier._backgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundColor(modifier._backgroundColor_0_0value);
                    break;
                }
                default: {
                    this.backgroundColor((undefined as ResourceColor | ColorMetrics | undefined));
                }
            }
        }
        if (modifier._pixelRound_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pixelRound_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pixelRound(modifier._pixelRound_0_0value);
                    break;
                }
                default: {
                    this.pixelRound((undefined as PixelRoundPolicy | undefined));
                }
            }
        }
        if (modifier._backgroundImageSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundImageSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundImageSize(modifier._backgroundImageSize_0_0value);
                    break;
                }
                default: {
                    this.backgroundImageSize((undefined as SizeOptions | ImageSize | undefined));
                }
            }
        }
        if (modifier._backgroundImagePosition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundImagePosition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundImagePosition(modifier._backgroundImagePosition_0_0value);
                    break;
                }
                default: {
                    this.backgroundImagePosition((undefined as Position | Alignment | undefined));
                }
            }
        }
        if (modifier._backgroundEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundEffect(modifier._backgroundEffect_0_0value);
                    break;
                }
                default: {
                    this.backgroundEffect((undefined as BackgroundEffectOptions | undefined));
                }
            }
        }
        if (modifier._backgroundImageResizable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundImageResizable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundImageResizable(modifier._backgroundImageResizable_0_0value);
                    break;
                }
                default: {
                    this.backgroundImageResizable((undefined as ResizableOptions | undefined));
                }
            }
        }
        if (modifier._foregroundEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._foregroundEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.foregroundEffect(modifier._foregroundEffect_0_0value);
                    break;
                }
                default: {
                    this.foregroundEffect((undefined as ForegroundEffectOptions | undefined));
                }
            }
        }
        if (modifier._visualEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._visualEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.visualEffect(modifier._visualEffect_0_0value);
                    break;
                }
                default: {
                    this.visualEffect((undefined as uiEffect.VisualEffect | undefined));
                }
            }
        }
        if (modifier._backgroundFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundFilter(modifier._backgroundFilter_0_0value);
                    break;
                }
                default: {
                    this.backgroundFilter((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (modifier._foregroundFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._foregroundFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.foregroundFilter(modifier._foregroundFilter_0_0value);
                    break;
                }
                default: {
                    this.foregroundFilter((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (modifier._compositingFilter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._compositingFilter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.compositingFilter(modifier._compositingFilter_0_0value);
                    break;
                }
                default: {
                    this.compositingFilter((undefined as uiEffect.Filter | undefined));
                }
            }
        }
        if (modifier._opacity_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._opacity_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.opacity(modifier._opacity_0_0value);
                    break;
                }
                default: {
                    this.opacity((undefined as number | Resource | undefined));
                }
            }
        }
        if (modifier._border_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._border_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.border(modifier._border_0_0value);
                    break;
                }
                default: {
                    this.border((undefined as BorderOptions | undefined));
                }
            }
        }
        if (modifier._borderStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderStyle(modifier._borderStyle_0_0value);
                    break;
                }
                default: {
                    this.borderStyle((undefined as BorderStyle | EdgeStyles | undefined));
                }
            }
        }
        if (modifier._borderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderWidth(modifier._borderWidth_0_0value);
                    break;
                }
                default: {
                    this.borderWidth((undefined as Length | EdgeWidths | LocalizedEdgeWidths | undefined));
                }
            }
        }
        if (modifier._borderColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderColor(modifier._borderColor_0_0value);
                    break;
                }
                default: {
                    this.borderColor((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                }
            }
        }
        if (modifier._borderRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderRadius(modifier._borderRadius_0_0value);
                    break;
                }
                default: {
                    this.borderRadius((undefined as Length | BorderRadiuses | LocalizedBorderRadiuses | undefined));
                }
            }
        }
        if (modifier._borderImage_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._borderImage_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.borderImage(modifier._borderImage_0_0value);
                    break;
                }
                default: {
                    this.borderImage((undefined as BorderImageOption | undefined));
                }
            }
        }
        if (modifier._outline_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._outline_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.outline(modifier._outline_0_0value);
                    break;
                }
                default: {
                    this.outline((undefined as OutlineOptions | undefined));
                }
            }
        }
        if (modifier._outlineStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._outlineStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.outlineStyle(modifier._outlineStyle_0_0value);
                    break;
                }
                default: {
                    this.outlineStyle((undefined as OutlineStyle | EdgeOutlineStyles | undefined));
                }
            }
        }
        if (modifier._outlineWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._outlineWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.outlineWidth(modifier._outlineWidth_0_0value);
                    break;
                }
                default: {
                    this.outlineWidth((undefined as Dimension | EdgeOutlineWidths | undefined));
                }
            }
        }
        if (modifier._outlineColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._outlineColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.outlineColor(modifier._outlineColor_0_0value);
                    break;
                }
                default: {
                    this.outlineColor((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
                }
            }
        }
        if (modifier._outlineRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._outlineRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.outlineRadius(modifier._outlineRadius_0_0value);
                    break;
                }
                default: {
                    this.outlineRadius((undefined as Dimension | OutlineRadiuses | undefined));
                }
            }
        }
        if (modifier._foregroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._foregroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.foregroundColor(modifier._foregroundColor_0_0value);
                    break;
                }
                default: {
                    this.foregroundColor((undefined as ResourceColor | ColoringStrategy | undefined));
                }
            }
        }
        if (modifier._onClick_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onClick_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onClick(modifier._onClick_0_0value);
                    break;
                }
                default: {
                    this.onClick((undefined as ((event: ClickEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onHover_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHover_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHover(modifier._onHover_0_0value);
                    break;
                }
                default: {
                    this.onHover((undefined as ((isHover: boolean,event: HoverEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onHoverMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHoverMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHoverMove(modifier._onHoverMove_0_0value);
                    break;
                }
                default: {
                    this.onHoverMove((undefined as ((value0: HoverEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onAccessibilityHover_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAccessibilityHover_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAccessibilityHover(modifier._onAccessibilityHover_0_0value);
                    break;
                }
                default: {
                    this.onAccessibilityHover((undefined as AccessibilityCallback | undefined));
                }
            }
        }
        if (modifier._hoverEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hoverEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hoverEffect(modifier._hoverEffect_0_0value);
                    break;
                }
                default: {
                    this.hoverEffect((undefined as HoverEffect | undefined));
                }
            }
        }
        if (modifier._onMouse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onMouse_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onMouse(modifier._onMouse_0_0value);
                    break;
                }
                default: {
                    this.onMouse((undefined as ((event: MouseEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onTouch_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTouch_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTouch(modifier._onTouch_0_0value);
                    break;
                }
                default: {
                    this.onTouch((undefined as ((event: TouchEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onKeyEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onKeyEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onKeyEvent(modifier._onKeyEvent_0_0value);
                    break;
                }
                default: {
                    this.onKeyEvent((undefined as ((event: KeyEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onDigitalCrown_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDigitalCrown_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDigitalCrown(modifier._onDigitalCrown_0_0value);
                    break;
                }
                default: {
                    this.onDigitalCrown((undefined as ((value0: CrownEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onKeyPreIme_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onKeyPreIme_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onKeyPreIme(modifier._onKeyPreIme_0_0value);
                    break;
                }
                default: {
                    this.onKeyPreIme((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onKeyEventDispatch_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onKeyEventDispatch_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onKeyEventDispatch(modifier._onKeyEventDispatch_0_0value);
                    break;
                }
                default: {
                    this.onKeyEventDispatch((undefined as ((value0: KeyEvent) => boolean) | undefined));
                }
            }
        }
        if (modifier._onFocusAxisEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFocusAxisEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFocusAxisEvent(modifier._onFocusAxisEvent_0_0value);
                    break;
                }
                default: {
                    this.onFocusAxisEvent((undefined as ((value0: FocusAxisEvent) => void) | undefined));
                }
            }
        }
        if (modifier._onAxisEvent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAxisEvent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAxisEvent(modifier._onAxisEvent_0_0value);
                    break;
                }
                default: {
                    this.onAxisEvent((undefined as ((value0: AxisEvent) => void) | undefined));
                }
            }
        }
        if (modifier._focusable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._focusable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.focusable(modifier._focusable_0_0value);
                    break;
                }
                default: {
                    this.focusable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._nextFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._nextFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.nextFocus(modifier._nextFocus_0_0value);
                    break;
                }
                default: {
                    this.nextFocus((undefined as FocusMovement | undefined));
                }
            }
        }
        if (modifier._tabStop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._tabStop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.tabStop(modifier._tabStop_0_0value);
                    break;
                }
                default: {
                    this.tabStop((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFocus(modifier._onFocus_0_0value);
                    break;
                }
                default: {
                    this.onFocus((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onBlur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onBlur_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onBlur(modifier._onBlur_0_0value);
                    break;
                }
                default: {
                    this.onBlur((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._tabIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._tabIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.tabIndex(modifier._tabIndex_0_0value);
                    break;
                }
                default: {
                    this.tabIndex((undefined as number | undefined));
                }
            }
        }
        if (modifier._defaultFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._defaultFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.defaultFocus(modifier._defaultFocus_0_0value);
                    break;
                }
                default: {
                    this.defaultFocus((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._groupDefaultFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._groupDefaultFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.groupDefaultFocus(modifier._groupDefaultFocus_0_0value);
                    break;
                }
                default: {
                    this.groupDefaultFocus((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._focusOnTouch_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._focusOnTouch_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.focusOnTouch(modifier._focusOnTouch_0_0value);
                    break;
                }
                default: {
                    this.focusOnTouch((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._focusBox_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._focusBox_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.focusBox(modifier._focusBox_0_0value);
                    break;
                }
                default: {
                    this.focusBox((undefined as FocusBoxStyle | undefined));
                }
            }
        }
        if (modifier._animation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._animation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.animation(modifier._animation_0_0value);
                    break;
                }
                default: {
                    this.animation((undefined as AnimateParam | undefined));
                }
            }
        }
        if (modifier._transition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._transition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.transition(modifier._transition_0_0value);
                    break;
                }
                default: {
                    this.transition((undefined as TransitionEffect | undefined));
                }
            }
        }
        if (modifier._motionBlur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._motionBlur_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.motionBlur(modifier._motionBlur_0_0value);
                    break;
                }
                default: {
                    this.motionBlur((undefined as MotionBlurOptions | undefined));
                }
            }
        }
        if (modifier._brightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._brightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.brightness(modifier._brightness_0_0value);
                    break;
                }
                default: {
                    this.brightness((undefined as number | undefined));
                }
            }
        }
        if (modifier._contrast_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._contrast_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.contrast(modifier._contrast_0_0value);
                    break;
                }
                default: {
                    this.contrast((undefined as number | undefined));
                }
            }
        }
        if (modifier._grayscale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._grayscale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.grayscale(modifier._grayscale_0_0value);
                    break;
                }
                default: {
                    this.grayscale((undefined as number | undefined));
                }
            }
        }
        if (modifier._colorBlend_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._colorBlend_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.colorBlend(modifier._colorBlend_0_0value);
                    break;
                }
                default: {
                    this.colorBlend((undefined as Color | string | Resource | undefined));
                }
            }
        }
        if (modifier._saturate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._saturate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.saturate(modifier._saturate_0_0value);
                    break;
                }
                default: {
                    this.saturate((undefined as number | undefined));
                }
            }
        }
        if (modifier._sepia_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sepia_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sepia(modifier._sepia_0_0value);
                    break;
                }
                default: {
                    this.sepia((undefined as number | undefined));
                }
            }
        }
        if (modifier._invert_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._invert_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.invert(modifier._invert_0_0value);
                    break;
                }
                default: {
                    this.invert((undefined as number | InvertOptions | undefined));
                }
            }
        }
        if (modifier._hueRotate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._hueRotate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.hueRotate(modifier._hueRotate_0_0value);
                    break;
                }
                default: {
                    this.hueRotate((undefined as number | string | undefined));
                }
            }
        }
        if (modifier._useShadowBatching_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._useShadowBatching_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.useShadowBatching(modifier._useShadowBatching_0_0value);
                    break;
                }
                default: {
                    this.useShadowBatching((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._useEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._useEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.useEffect(modifier._useEffect_0_0value);
                    break;
                }
                default: {
                    this.useEffect((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._renderGroup_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._renderGroup_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.renderGroup(modifier._renderGroup_0_0value);
                    break;
                }
                default: {
                    this.renderGroup((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._freeze_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._freeze_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.freeze(modifier._freeze_0_0value);
                    break;
                }
                default: {
                    this.freeze((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._translate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._translate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.translate(modifier._translate_0_0value);
                    break;
                }
                default: {
                    this.translate((undefined as TranslateOptions | undefined));
                }
            }
        }
        if (modifier._scale_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._scale_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.scale(modifier._scale_0_0value);
                    break;
                }
                default: {
                    this.scale((undefined as ScaleOptions | undefined));
                }
            }
        }
        if (modifier._rotate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._rotate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rotate(modifier._rotate_0_0value);
                    break;
                }
                default: {
                    this.rotate((undefined as RotateOptions | undefined));
                }
            }
        }
        if (modifier._transform_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._transform_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.transform(modifier._transform_0_0value);
                    break;
                }
                default: {
                    this.transform((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (modifier._transform3D_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._transform3D_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.transform3D(modifier._transform3D_0_0value);
                    break;
                }
                default: {
                    this.transform3D((undefined as matrix4.Matrix4Transit | undefined));
                }
            }
        }
        if (modifier._onAppear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAppear_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAppear(modifier._onAppear_0_0value);
                    break;
                }
                default: {
                    this.onAppear((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onDisAppear_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDisAppear_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDisAppear(modifier._onDisAppear_0_0value);
                    break;
                }
                default: {
                    this.onDisAppear((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onAttach_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAttach_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAttach(modifier._onAttach_0_0value);
                    break;
                }
                default: {
                    this.onAttach((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onDetach_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDetach_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDetach(modifier._onDetach_0_0value);
                    break;
                }
                default: {
                    this.onDetach((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onAreaChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAreaChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAreaChange(modifier._onAreaChange_0_0value);
                    break;
                }
                default: {
                    this.onAreaChange((undefined as ((oldValue: Area,newValue: Area) => void) | undefined));
                }
            }
        }
        if (modifier._visibility_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._visibility_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.visibility(modifier._visibility_0_0value);
                    break;
                }
                default: {
                    this.visibility((undefined as Visibility | undefined));
                }
            }
        }
        if (modifier._flexGrow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._flexGrow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.flexGrow(modifier._flexGrow_0_0value);
                    break;
                }
                default: {
                    this.flexGrow((undefined as number | undefined));
                }
            }
        }
        if (modifier._flexShrink_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._flexShrink_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.flexShrink(modifier._flexShrink_0_0value);
                    break;
                }
                default: {
                    this.flexShrink((undefined as number | undefined));
                }
            }
        }
        if (modifier._flexBasis_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._flexBasis_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.flexBasis(modifier._flexBasis_0_0value);
                    break;
                }
                default: {
                    this.flexBasis((undefined as number | string | undefined));
                }
            }
        }
        if (modifier._alignSelf_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignSelf_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignSelf(modifier._alignSelf_0_0value);
                    break;
                }
                default: {
                    this.alignSelf((undefined as ItemAlign | undefined));
                }
            }
        }
        if (modifier._displayPriority_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._displayPriority_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.displayPriority(modifier._displayPriority_0_0value);
                    break;
                }
                default: {
                    this.displayPriority((undefined as number | undefined));
                }
            }
        }
        if (modifier._zIndex_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._zIndex_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.zIndex(modifier._zIndex_0_0value);
                    break;
                }
                default: {
                    this.zIndex((undefined as number | undefined));
                }
            }
        }
        if (modifier._direction_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._direction_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.direction(modifier._direction_0_0value);
                    break;
                }
                default: {
                    this.direction((undefined as Direction | undefined));
                }
            }
        }
        if (modifier._align_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._align_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.align(modifier._align_0_0value);
                    break;
                }
                default: {
                    this.align((undefined as Alignment | undefined));
                }
            }
        }
        if (modifier._position_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._position_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.position(modifier._position_0_0value);
                    break;
                }
                default: {
                    this.position((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (modifier._markAnchor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._markAnchor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.markAnchor(modifier._markAnchor_0_0value);
                    break;
                }
                default: {
                    this.markAnchor((undefined as Position | LocalizedPosition | undefined));
                }
            }
        }
        if (modifier._offset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._offset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.offset(modifier._offset_0_0value);
                    break;
                }
                default: {
                    this.offset((undefined as Position | Edges | LocalizedEdges | undefined));
                }
            }
        }
        if (modifier._enabled_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enabled_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enabled(modifier._enabled_0_0value);
                    break;
                }
                default: {
                    this.enabled((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._alignRules_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignRules_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignRules(modifier._alignRules_0_0value);
                    break;
                }
                default: {
                    this.alignRules((undefined as AlignRuleOption | LocalizedAlignRuleOptions | undefined));
                }
            }
        }
        if (modifier._aspectRatio_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._aspectRatio_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.aspectRatio(modifier._aspectRatio_0_0value);
                    break;
                }
                default: {
                    this.aspectRatio((undefined as number | undefined));
                }
            }
        }
        if (modifier._clickEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._clickEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.clickEffect(modifier._clickEffect_0_0value);
                    break;
                }
                default: {
                    this.clickEffect((undefined as ClickEffect | null | undefined));
                }
            }
        }
        if (modifier._onDragStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDragStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDragStart(modifier._onDragStart_0_0value);
                    break;
                }
                default: {
                    this.onDragStart((undefined as ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined));
                }
            }
        }
        if (modifier._onDragEnter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDragEnter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDragEnter(modifier._onDragEnter_0_0value);
                    break;
                }
                default: {
                    this.onDragEnter((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (modifier._onDragMove_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDragMove_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDragMove(modifier._onDragMove_0_0value);
                    break;
                }
                default: {
                    this.onDragMove((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (modifier._onDragLeave_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDragLeave_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDragLeave(modifier._onDragLeave_0_0value);
                    break;
                }
                default: {
                    this.onDragLeave((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (modifier._onDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDrop(modifier._onDrop_0_0value);
                    break;
                }
                default: {
                    this.onDrop((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (modifier._onDragEnd_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDragEnd_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDragEnd(modifier._onDragEnd_0_0value);
                    break;
                }
                default: {
                    this.onDragEnd((undefined as ((event: DragEvent,extraParams?: string) => void) | undefined));
                }
            }
        }
        if (modifier._allowDrop_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._allowDrop_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.allowDrop(modifier._allowDrop_0_0value);
                    break;
                }
                default: {
                    this.allowDrop((undefined as Array<uniformTypeDescriptor.UniformDataType> | null | undefined));
                }
            }
        }
        if (modifier._draggable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._draggable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.draggable(modifier._draggable_0_0value);
                    break;
                }
                default: {
                    this.draggable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._dragPreview_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dragPreview_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dragPreview(modifier._dragPreview_0_0value);
                    break;
                }
                default: {
                    this.dragPreview((undefined as CustomBuilder | DragItemInfo | string | undefined));
                }
            }
        }
        if (modifier._dragPreviewOptions_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dragPreviewOptions_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dragPreviewOptions(modifier._dragPreviewOptions_0_0value, modifier._dragPreviewOptions_0_1value);
                    break;
                }
                default: {
                    this.dragPreviewOptions((undefined as DragPreviewOptions | undefined), (undefined as DragInteractionOptions | undefined | undefined));
                }
            }
        }
        if (modifier._onPreDrag_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPreDrag_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPreDrag(modifier._onPreDrag_0_0value);
                    break;
                }
                default: {
                    this.onPreDrag((undefined as ((value0: PreDragStatus) => void) | undefined));
                }
            }
        }
        if (modifier._linearGradient_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._linearGradient_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.linearGradient(modifier._linearGradient_0_0value);
                    break;
                }
                default: {
                    this.linearGradient((undefined as LinearGradientOptions | undefined));
                }
            }
        }
        if (modifier._sweepGradient_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sweepGradient_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sweepGradient(modifier._sweepGradient_0_0value);
                    break;
                }
                default: {
                    this.sweepGradient((undefined as SweepGradientOptions | undefined));
                }
            }
        }
        if (modifier._radialGradient_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._radialGradient_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.radialGradient(modifier._radialGradient_0_0value);
                    break;
                }
                default: {
                    this.radialGradient((undefined as RadialGradientOptions | undefined));
                }
            }
        }
        if (modifier._motionPath_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._motionPath_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.motionPath(modifier._motionPath_0_0value);
                    break;
                }
                default: {
                    this.motionPath((undefined as MotionPathOptions | undefined));
                }
            }
        }
        if (modifier._shadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._shadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.shadow(modifier._shadow_0_0value);
                    break;
                }
                default: {
                    this.shadow((undefined as ShadowOptions | ShadowStyle | undefined));
                }
            }
        }
        if (modifier._clip_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._clip_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.clip(modifier._clip_0_0value);
                    break;
                }
                default: {
                    this.clip((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._clipShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._clipShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.clipShape(modifier._clipShape_0_0value);
                    break;
                }
                default: {
                    this.clipShape((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                }
            }
        }
        if (modifier._mask_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._mask_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.mask(modifier._mask_0_0value);
                    break;
                }
                default: {
                    this.mask((undefined as ProgressMask | undefined));
                }
            }
        }
        if (modifier._maskShape_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._maskShape_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.maskShape(modifier._maskShape_0_0value);
                    break;
                }
                default: {
                    this.maskShape((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
                }
            }
        }
        if (modifier._key_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._key_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.key(modifier._key_0_0value);
                    break;
                }
                default: {
                    this.key((undefined as string | undefined));
                }
            }
        }
        if (modifier._id_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._id_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.id(modifier._id_0_0value);
                    break;
                }
                default: {
                    this.id((undefined as string | undefined));
                }
            }
        }
        if (modifier._geometryTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._geometryTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.geometryTransition(modifier._geometryTransition_0_0value);
                    break;
                }
                default: {
                    this.geometryTransition((undefined as string | undefined));
                }
            }
        }
        if (modifier._restoreId_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._restoreId_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.restoreId(modifier._restoreId_0_0value);
                    break;
                }
                default: {
                    this.restoreId((undefined as number | undefined));
                }
            }
        }
        if (modifier._sphericalEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sphericalEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sphericalEffect(modifier._sphericalEffect_0_0value);
                    break;
                }
                default: {
                    this.sphericalEffect((undefined as number | undefined));
                }
            }
        }
        if (modifier._lightUpEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._lightUpEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.lightUpEffect(modifier._lightUpEffect_0_0value);
                    break;
                }
                default: {
                    this.lightUpEffect((undefined as number | undefined));
                }
            }
        }
        if (modifier._pixelStretchEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pixelStretchEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pixelStretchEffect(modifier._pixelStretchEffect_0_0value);
                    break;
                }
                default: {
                    this.pixelStretchEffect((undefined as PixelStretchEffectOptions | undefined));
                }
            }
        }
        if (modifier._accessibilityGroup_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityGroup_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityGroup(modifier._accessibilityGroup_0_0value);
                    break;
                }
                default: {
                    this.accessibilityGroup((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._accessibilityText_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityText_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityText(modifier._accessibilityText_0_0value);
                    break;
                }
                default: {
                    this.accessibilityText((undefined as string | undefined));
                }
            }
        }
        if (modifier._accessibilityNextFocusId_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityNextFocusId_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityNextFocusId(modifier._accessibilityNextFocusId_0_0value);
                    break;
                }
                default: {
                    this.accessibilityNextFocusId((undefined as string | undefined));
                }
            }
        }
        if (modifier._accessibilityDefaultFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityDefaultFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityDefaultFocus(modifier._accessibilityDefaultFocus_0_0value);
                    break;
                }
                default: {
                    this.accessibilityDefaultFocus((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._accessibilityUseSamePage_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityUseSamePage_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityUseSamePage(modifier._accessibilityUseSamePage_0_0value);
                    break;
                }
                default: {
                    this.accessibilityUseSamePage((undefined as AccessibilitySamePageMode | undefined));
                }
            }
        }
        if (modifier._accessibilityScrollTriggerable_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityScrollTriggerable_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityScrollTriggerable(modifier._accessibilityScrollTriggerable_0_0value);
                    break;
                }
                default: {
                    this.accessibilityScrollTriggerable((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._accessibilityText_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityText_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityText(modifier._accessibilityText_1_0value);
                    break;
                }
                default: {
                    this.accessibilityText((undefined as Resource | undefined));
                }
            }
        }
        if (modifier._accessibilityRole_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityRole_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityRole(modifier._accessibilityRole_0_0value);
                    break;
                }
                default: {
                    this.accessibilityRole((undefined as AccessibilityRoleType | undefined));
                }
            }
        }
        if (modifier._onAccessibilityFocus_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAccessibilityFocus_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAccessibilityFocus(modifier._onAccessibilityFocus_0_0value);
                    break;
                }
                default: {
                    this.onAccessibilityFocus((undefined as AccessibilityFocusCallback | undefined));
                }
            }
        }
        if (modifier._onAccessibilityActionIntercept_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAccessibilityActionIntercept_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAccessibilityActionIntercept(modifier._onAccessibilityActionIntercept_0_0value);
                    break;
                }
                default: {
                    this.onAccessibilityActionIntercept((undefined as AccessibilityActionInterceptCallback | undefined));
                }
            }
        }
        if (modifier._accessibilityTextHint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityTextHint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityTextHint(modifier._accessibilityTextHint_0_0value);
                    break;
                }
                default: {
                    this.accessibilityTextHint((undefined as string | undefined));
                }
            }
        }
        if (modifier._accessibilityDescription_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityDescription_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityDescription(modifier._accessibilityDescription_0_0value);
                    break;
                }
                default: {
                    this.accessibilityDescription((undefined as string | undefined));
                }
            }
        }
        if (modifier._accessibilityDescription_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityDescription_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityDescription(modifier._accessibilityDescription_1_0value);
                    break;
                }
                default: {
                    this.accessibilityDescription((undefined as Resource | undefined));
                }
            }
        }
        if (modifier._accessibilityLevel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityLevel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityLevel(modifier._accessibilityLevel_0_0value);
                    break;
                }
                default: {
                    this.accessibilityLevel((undefined as string | undefined));
                }
            }
        }
        if (modifier._accessibilityVirtualNode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityVirtualNode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityVirtualNode(modifier._accessibilityVirtualNode_0_0value);
                    break;
                }
                default: {
                    this.accessibilityVirtualNode((undefined as CustomBuilder | undefined));
                }
            }
        }
        if (modifier._accessibilityChecked_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityChecked_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityChecked(modifier._accessibilityChecked_0_0value);
                    break;
                }
                default: {
                    this.accessibilityChecked((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._accessibilitySelected_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilitySelected_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilitySelected(modifier._accessibilitySelected_0_0value);
                    break;
                }
                default: {
                    this.accessibilitySelected((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._obscured_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._obscured_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.obscured(modifier._obscured_0_0value);
                    break;
                }
                default: {
                    this.obscured((undefined as Array<ObscuredReasons> | undefined));
                }
            }
        }
        if (modifier._reuseId_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._reuseId_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.reuseId(modifier._reuseId_0_0value);
                    break;
                }
                default: {
                    this.reuseId((undefined as string | undefined));
                }
            }
        }
        if (modifier._reuse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._reuse_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.reuse(modifier._reuse_0_0value);
                    break;
                }
                default: {
                    this.reuse((undefined as ReuseOptions | undefined));
                }
            }
        }
        if (modifier._renderFit_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._renderFit_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.renderFit(modifier._renderFit_0_0value);
                    break;
                }
                default: {
                    this.renderFit((undefined as RenderFit | undefined));
                }
            }
        }
        if (modifier._backgroundBrightness_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundBrightness_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundBrightness(modifier._backgroundBrightness_0_0value);
                    break;
                }
                default: {
                    this.backgroundBrightness((undefined as BackgroundBrightnessOptions | undefined));
                }
            }
        }
        if (modifier._onGestureJudgeBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGestureJudgeBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGestureJudgeBegin(modifier._onGestureJudgeBegin_0_0value);
                    break;
                }
                default: {
                    this.onGestureJudgeBegin((undefined as ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined));
                }
            }
        }
        if (modifier._onGestureRecognizerJudgeBegin_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGestureRecognizerJudgeBegin_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGestureRecognizerJudgeBegin(modifier._onGestureRecognizerJudgeBegin_0_0value);
                    break;
                }
                default: {
                    this.onGestureRecognizerJudgeBegin((undefined as GestureRecognizerJudgeBeginCallback | undefined));
                }
            }
        }
        if (modifier._shouldBuiltInRecognizerParallelWith_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._shouldBuiltInRecognizerParallelWith_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.shouldBuiltInRecognizerParallelWith(modifier._shouldBuiltInRecognizerParallelWith_0_0value);
                    break;
                }
                default: {
                    this.shouldBuiltInRecognizerParallelWith((undefined as ShouldBuiltInRecognizerParallelWithCallback | undefined));
                }
            }
        }
        if (modifier._monopolizeEvents_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._monopolizeEvents_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.monopolizeEvents(modifier._monopolizeEvents_0_0value);
                    break;
                }
                default: {
                    this.monopolizeEvents((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onTouchIntercept_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onTouchIntercept_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onTouchIntercept(modifier._onTouchIntercept_0_0value);
                    break;
                }
                default: {
                    this.onTouchIntercept((undefined as ((value0: TouchEvent) => HitTestMode) | undefined));
                }
            }
        }
        if (modifier._onSizeChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onSizeChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onSizeChange(modifier._onSizeChange_0_0value);
                    break;
                }
                default: {
                    this.onSizeChange((undefined as SizeChangeCallback | undefined));
                }
            }
        }
        if (modifier._accessibilityFocusDrawLevel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityFocusDrawLevel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityFocusDrawLevel(modifier._accessibilityFocusDrawLevel_0_0value);
                    break;
                }
                default: {
                    this.accessibilityFocusDrawLevel((undefined as FocusDrawLevel | undefined));
                }
            }
        }
        if (modifier._expandSafeArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._expandSafeArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.expandSafeArea(modifier._expandSafeArea_0_0value, modifier._expandSafeArea_0_1value);
                    break;
                }
                default: {
                    this.expandSafeArea((undefined as Array<SafeAreaType> | undefined | undefined), (undefined as Array<SafeAreaEdge> | undefined | undefined));
                }
            }
        }
        if (modifier._background_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._background_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.background(modifier._background_0_0value, modifier._background_0_1value);
                    break;
                }
                default: {
                    this.background((undefined as CustomBuilder | undefined), (undefined as BackgroundOptions | undefined | undefined));
                }
            }
        }
        if (modifier._backgroundImage_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundImage_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundImage(modifier._backgroundImage_0_0value);
                    break;
                }
                default: {
                    this.backgroundImage((undefined as ResourceStr | image.PixelMap | undefined));
                }
            }
        }
        if (modifier._backgroundImage_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundImage_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundImage(modifier._backgroundImage_1_0value, modifier._backgroundImage_1_1value);
                    break;
                }
                default: {
                    this.backgroundImage((undefined as ResourceStr | image.PixelMap | undefined), (undefined as BackgroundImageOptions | undefined | undefined));
                }
            }
        }
        if (modifier._backgroundImage_2_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundImage_2_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundImage(modifier._backgroundImage_2_0value, modifier._backgroundImage_2_1value);
                    break;
                }
                default: {
                    this.backgroundImage((undefined as ResourceStr | image.PixelMap | undefined), (undefined as ImageRepeat | undefined | undefined));
                }
            }
        }
        if (modifier._backgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundBlurStyle(modifier._backgroundBlurStyle_0_0value, modifier._backgroundBlurStyle_0_1value, modifier._backgroundBlurStyle_0_2value);
                    break;
                }
                default: {
                    this.backgroundBlurStyle((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (modifier._backgroundEffect_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundEffect_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundEffect(modifier._backgroundEffect_1_0value, modifier._backgroundEffect_1_1value);
                    break;
                }
                default: {
                    this.backgroundEffect((undefined as BackgroundEffectOptions | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (modifier._foregroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._foregroundBlurStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.foregroundBlurStyle(modifier._foregroundBlurStyle_0_0value, modifier._foregroundBlurStyle_0_1value, modifier._foregroundBlurStyle_0_2value);
                    break;
                }
                default: {
                    this.foregroundBlurStyle((undefined as BlurStyle | undefined), (undefined as ForegroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (modifier._onClick_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onClick_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onClick(modifier._onClick_1_0value, modifier._onClick_1_1value);
                    break;
                }
                default: {
                    this.onClick((undefined as ((event: ClickEvent) => void) | undefined), (undefined as number | undefined));
                }
            }
        }
        if (modifier._focusScopeId_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._focusScopeId_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.focusScopeId(modifier._focusScopeId_0_0value, modifier._focusScopeId_0_1value, modifier._focusScopeId_0_2value);
                    break;
                }
                default: {
                    this.focusScopeId((undefined as string | undefined), (undefined as boolean | undefined | undefined), (undefined as boolean | undefined | undefined));
                }
            }
        }
        if (modifier._focusScopePriority_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._focusScopePriority_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.focusScopePriority(modifier._focusScopePriority_0_0value, modifier._focusScopePriority_0_1value);
                    break;
                }
                default: {
                    this.focusScopePriority((undefined as string | undefined), (undefined as FocusPriority | undefined | undefined));
                }
            }
        }
        if (modifier._transition_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._transition_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.transition(modifier._transition_1_0value, modifier._transition_1_1value);
                    break;
                }
                default: {
                    this.transition((undefined as TransitionEffect | undefined), (undefined as TransitionFinishCallback | undefined));
                }
            }
        }
        if (modifier._blur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blur_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blur(modifier._blur_0_0value, modifier._blur_0_1value, modifier._blur_0_2value);
                    break;
                }
                default: {
                    this.blur((undefined as number | undefined), (undefined as BlurOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (modifier._linearGradientBlur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._linearGradientBlur_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.linearGradientBlur(modifier._linearGradientBlur_0_0value, modifier._linearGradientBlur_0_1value);
                    break;
                }
                default: {
                    this.linearGradientBlur((undefined as number | undefined), (undefined as LinearGradientBlurOptions | undefined));
                }
            }
        }
        if (modifier._systemBarEffect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._systemBarEffect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.systemBarEffect();
                    break;
                }
                default: {
                    this.systemBarEffect();
                }
            }
        }
        if (modifier._useEffect_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._useEffect_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.useEffect(modifier._useEffect_1_0value, modifier._useEffect_1_1value);
                    break;
                }
                default: {
                    this.useEffect((undefined as boolean | undefined), (undefined as EffectType | undefined));
                }
            }
        }
        if (modifier._backdropBlur_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backdropBlur_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backdropBlur(modifier._backdropBlur_0_0value, modifier._backdropBlur_0_1value, modifier._backdropBlur_0_2value);
                    break;
                }
                default: {
                    this.backdropBlur((undefined as number | undefined), (undefined as BlurOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
                }
            }
        }
        if (modifier._sharedTransition_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sharedTransition_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sharedTransition(modifier._sharedTransition_0_0value, modifier._sharedTransition_0_1value);
                    break;
                }
                default: {
                    this.sharedTransition((undefined as string | undefined), (undefined as sharedTransitionOptions | undefined | undefined));
                }
            }
        }
        if (modifier._chainMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._chainMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.chainMode(modifier._chainMode_0_0value, modifier._chainMode_0_1value);
                    break;
                }
                default: {
                    this.chainMode((undefined as Axis | undefined), (undefined as ChainStyle | undefined));
                }
            }
        }
        if (modifier._onDrop_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDrop_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDrop(modifier._onDrop_1_0value, modifier._onDrop_1_1value);
                    break;
                }
                default: {
                    this.onDrop((undefined as OnDragEventCallback | undefined), (undefined as DropOptions | undefined | undefined));
                }
            }
        }
        if (modifier._dragPreview_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dragPreview_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dragPreview(modifier._dragPreview_1_0value, modifier._dragPreview_1_1value);
                    break;
                }
                default: {
                    this.dragPreview((undefined as CustomBuilder | DragItemInfo | string | undefined), (undefined as PreviewConfiguration | undefined | undefined));
                }
            }
        }
        if (modifier._overlay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._overlay_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.overlay(modifier._overlay_0_0value, modifier._overlay_0_1value);
                    break;
                }
                default: {
                    this.overlay((undefined as string | CustomBuilder | ComponentContent | undefined), (undefined as OverlayOptions | undefined | undefined));
                }
            }
        }
        if (modifier._blendMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._blendMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.blendMode(modifier._blendMode_0_0value, modifier._blendMode_0_1value);
                    break;
                }
                default: {
                    this.blendMode((undefined as BlendMode | undefined), (undefined as BlendApplyType | undefined | undefined));
                }
            }
        }
        if (modifier._geometryTransition_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._geometryTransition_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.geometryTransition(modifier._geometryTransition_1_0value, modifier._geometryTransition_1_1value);
                    break;
                }
                default: {
                    this.geometryTransition((undefined as string | undefined), (undefined as GeometryTransitionOptions | undefined | undefined));
                }
            }
        }
        if (modifier._bindTips_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindTips_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindTips(modifier._bindTips_0_0value, modifier._bindTips_0_1value);
                    break;
                }
                default: {
                    this.bindTips((undefined as TipsMessageType | undefined), (undefined as TipsOptions | undefined | undefined));
                }
            }
        }
        if (modifier._bindPopup_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindPopup_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindPopup(modifier._bindPopup_0_0value, modifier._bindPopup_0_1value);
                    break;
                }
                default: {
                    this.bindPopup((undefined as boolean | undefined), (undefined as PopupOptions | CustomPopupOptions | undefined));
                }
            }
        }
        if (modifier._bindMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindMenu(modifier._bindMenu_0_0value, modifier._bindMenu_0_1value);
                    break;
                }
                default: {
                    this.bindMenu((undefined as Array<MenuElement> | CustomBuilder | undefined), (undefined as MenuOptions | undefined | undefined));
                }
            }
        }
        if (modifier._bindMenu_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindMenu_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindMenu(modifier._bindMenu_1_0value, modifier._bindMenu_1_1value, modifier._bindMenu_1_2value);
                    break;
                }
                default: {
                    this.bindMenu((undefined as boolean | undefined), (undefined as Array<MenuElement> | CustomBuilder | undefined), (undefined as MenuOptions | undefined | undefined));
                }
            }
        }
        if (modifier._bindContextMenu_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindContextMenu_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindContextMenu(modifier._bindContextMenu_0_0value, modifier._bindContextMenu_0_1value, modifier._bindContextMenu_0_2value);
                    break;
                }
                default: {
                    this.bindContextMenu((undefined as CustomBuilder | undefined), (undefined as ResponseType | undefined), (undefined as ContextMenuOptions | undefined | undefined));
                }
            }
        }
        if (modifier._bindContextMenu_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindContextMenu_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindContextMenu(modifier._bindContextMenu_1_0value, modifier._bindContextMenu_1_1value, modifier._bindContextMenu_1_2value);
                    break;
                }
                default: {
                    this.bindContextMenu((undefined as boolean | undefined), (undefined as CustomBuilder | undefined), (undefined as ContextMenuOptions | undefined | undefined));
                }
            }
        }
        if (modifier._bindContentCover_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindContentCover_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindContentCover(modifier._bindContentCover_0_0value, modifier._bindContentCover_0_1value, modifier._bindContentCover_0_2value);
                    break;
                }
                default: {
                    this.bindContentCover((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as ModalTransition | undefined | undefined));
                }
            }
        }
        if (modifier._bindContentCover_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindContentCover_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindContentCover(modifier._bindContentCover_1_0value, modifier._bindContentCover_1_1value, modifier._bindContentCover_1_2value);
                    break;
                }
                default: {
                    this.bindContentCover((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as ContentCoverOptions | undefined | undefined));
                }
            }
        }
        if (modifier._bindSheet_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._bindSheet_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.bindSheet(modifier._bindSheet_0_0value, modifier._bindSheet_0_1value, modifier._bindSheet_0_2value);
                    break;
                }
                default: {
                    this.bindSheet((undefined as boolean | Bindable<boolean> | undefined), (undefined as CustomBuilder | undefined), (undefined as SheetOptions | undefined | undefined));
                }
            }
        }
        if (modifier._onVisibleAreaChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onVisibleAreaChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onVisibleAreaChange(modifier._onVisibleAreaChange_0_0value, modifier._onVisibleAreaChange_0_1value);
                    break;
                }
                default: {
                    this.onVisibleAreaChange((undefined as Array<number> | undefined), (undefined as VisibleAreaChangeCallback | undefined));
                }
            }
        }
        if (modifier._onVisibleAreaApproximateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onVisibleAreaApproximateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onVisibleAreaApproximateChange(modifier._onVisibleAreaApproximateChange_0_0value, modifier._onVisibleAreaApproximateChange_0_1value);
                    break;
                }
                default: {
                    this.onVisibleAreaApproximateChange((undefined as VisibleAreaEventOptions | undefined), (undefined as VisibleAreaChangeCallback | undefined));
                }
            }
        }
        if (modifier._keyboardShortcut_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._keyboardShortcut_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.keyboardShortcut(modifier._keyboardShortcut_0_0value, modifier._keyboardShortcut_0_1value, modifier._keyboardShortcut_0_2value);
                    break;
                }
                default: {
                    this.keyboardShortcut((undefined as string | FunctionKey | undefined), (undefined as Array<ModifierKey> | undefined), (undefined as (() => void) | undefined | undefined));
                }
            }
        }
        if (modifier._accessibilityGroup_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._accessibilityGroup_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.accessibilityGroup(modifier._accessibilityGroup_1_0value, modifier._accessibilityGroup_1_1value);
                    break;
                }
                default: {
                    this.accessibilityGroup((undefined as boolean | undefined), (undefined as AccessibilityOptions | undefined));
                }
            }
        }
        if (modifier._onGestureRecognizerJudgeBegin_1_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onGestureRecognizerJudgeBegin_1_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onGestureRecognizerJudgeBegin(modifier._onGestureRecognizerJudgeBegin_1_0value, modifier._onGestureRecognizerJudgeBegin_1_1value);
                    break;
                }
                default: {
                    this.onGestureRecognizerJudgeBegin((undefined as GestureRecognizerJudgeBeginCallback | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    width(value: Length | LayoutPolicy | undefined): this {
        if (((this._width_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._width_0_flag = AttributeUpdaterFlag.UPDATE
            this._width_0_0value = value
        } else
        {
            this._width_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    height(value: Length | LayoutPolicy | undefined): this {
        if (((this._height_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._height_0_flag = AttributeUpdaterFlag.UPDATE
            this._height_0_0value = value
        } else
        {
            this._height_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    responseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        if (((this._responseRegion_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._responseRegion_0_flag = AttributeUpdaterFlag.UPDATE
            this._responseRegion_0_0value = value
        } else
        {
            this._responseRegion_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mouseResponseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
        if (((this._mouseResponseRegion_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mouseResponseRegion_0_flag = AttributeUpdaterFlag.UPDATE
            this._mouseResponseRegion_0_0value = value
        } else
        {
            this._mouseResponseRegion_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    size(value: SizeOptions | undefined): this {
        if (((this._size_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._size_0_flag = AttributeUpdaterFlag.UPDATE
            this._size_0_0value = value
        } else
        {
            this._size_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    constraintSize(value: ConstraintSizeOptions | undefined): this {
        if (((this._constraintSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._constraintSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._constraintSize_0_0value = value
        } else
        {
            this._constraintSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hitTestBehavior(value: HitTestMode | undefined): this {
        if (((this._hitTestBehavior_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._hitTestBehavior_0_flag = AttributeUpdaterFlag.UPDATE
            this._hitTestBehavior_0_0value = value
        } else
        {
            this._hitTestBehavior_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onChildTouchTest(value: ((value: Array<TouchTestInfo>) => TouchResult) | undefined): this {
        if (((this._onChildTouchTest_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onChildTouchTest_0_flag = AttributeUpdaterFlag.UPDATE
            this._onChildTouchTest_0_0value = value
        } else
        {
            this._onChildTouchTest_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    layoutWeight(value: number | string | undefined): this {
        if (((this._layoutWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._layoutWeight_0_0value) !== (value)))
        {
            this._layoutWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._layoutWeight_0_0value = value
        } else
        {
            this._layoutWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    chainWeight(value: ChainWeightOptions | undefined): this {
        if (((this._chainWeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._chainWeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._chainWeight_0_0value = value
        } else
        {
            this._chainWeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    padding(value: Padding | Length | LocalizedPadding | undefined): this {
        if (((this._padding_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._padding_0_flag = AttributeUpdaterFlag.UPDATE
            this._padding_0_0value = value
        } else
        {
            this._padding_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this {
        if (((this._safeAreaPadding_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._safeAreaPadding_0_flag = AttributeUpdaterFlag.UPDATE
            this._safeAreaPadding_0_0value = value
        } else
        {
            this._safeAreaPadding_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    margin(value: Padding | Length | LocalizedPadding | undefined): this {
        if (((this._margin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._margin_0_flag = AttributeUpdaterFlag.UPDATE
            this._margin_0_0value = value
        } else
        {
            this._margin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundColor(value: ResourceColor | ColorMetrics | undefined): this {
        if (((this._backgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundColor_0_0value = value
        } else
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pixelRound(value: PixelRoundPolicy | undefined): this {
        if (((this._pixelRound_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pixelRound_0_flag = AttributeUpdaterFlag.UPDATE
            this._pixelRound_0_0value = value
        } else
        {
            this._pixelRound_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundImageSize(value: SizeOptions | ImageSize | undefined): this {
        if (((this._backgroundImageSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundImageSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundImageSize_0_0value = value
        } else
        {
            this._backgroundImageSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundImagePosition(value: Position | Alignment | undefined): this {
        if (((this._backgroundImagePosition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundImagePosition_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundImagePosition_0_0value = value
        } else
        {
            this._backgroundImagePosition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundEffect(value: BackgroundEffectOptions | undefined): this {
        if (((this._backgroundEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundEffect_0_0value = value
        } else
        {
            this._backgroundEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundImageResizable(value: ResizableOptions | undefined): this {
        if (((this._backgroundImageResizable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundImageResizable_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundImageResizable_0_0value = value
        } else
        {
            this._backgroundImageResizable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    foregroundEffect(value: ForegroundEffectOptions | undefined): this {
        if (((this._foregroundEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._foregroundEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._foregroundEffect_0_0value = value
        } else
        {
            this._foregroundEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    visualEffect(value: uiEffect.VisualEffect | undefined): this {
        if (((this._visualEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._visualEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._visualEffect_0_0value = value
        } else
        {
            this._visualEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundFilter(value: uiEffect.Filter | undefined): this {
        if (((this._backgroundFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundFilter_0_0value = value
        } else
        {
            this._backgroundFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    foregroundFilter(value: uiEffect.Filter | undefined): this {
        if (((this._foregroundFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._foregroundFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._foregroundFilter_0_0value = value
        } else
        {
            this._foregroundFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    compositingFilter(value: uiEffect.Filter | undefined): this {
        if (((this._compositingFilter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._compositingFilter_0_flag = AttributeUpdaterFlag.UPDATE
            this._compositingFilter_0_0value = value
        } else
        {
            this._compositingFilter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    opacity(value: number | Resource | undefined): this {
        if (((this._opacity_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._opacity_0_flag = AttributeUpdaterFlag.UPDATE
            this._opacity_0_0value = value
        } else
        {
            this._opacity_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    border(value: BorderOptions | undefined): this {
        if (((this._border_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._border_0_flag = AttributeUpdaterFlag.UPDATE
            this._border_0_0value = value
        } else
        {
            this._border_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderStyle(value: BorderStyle | EdgeStyles | undefined): this {
        if (((this._borderStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderStyle_0_0value = value
        } else
        {
            this._borderStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderWidth(value: Length | EdgeWidths | LocalizedEdgeWidths | undefined): this {
        if (((this._borderWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderWidth_0_0value = value
        } else
        {
            this._borderWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        if (((this._borderColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderColor_0_0value = value
        } else
        {
            this._borderColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderRadius(value: Length | BorderRadiuses | LocalizedBorderRadiuses | undefined): this {
        if (((this._borderRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderRadius_0_0value = value
        } else
        {
            this._borderRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    borderImage(value: BorderImageOption | undefined): this {
        if (((this._borderImage_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._borderImage_0_flag = AttributeUpdaterFlag.UPDATE
            this._borderImage_0_0value = value
        } else
        {
            this._borderImage_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    outline(value: OutlineOptions | undefined): this {
        if (((this._outline_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._outline_0_flag = AttributeUpdaterFlag.UPDATE
            this._outline_0_0value = value
        } else
        {
            this._outline_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this {
        if (((this._outlineStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._outlineStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._outlineStyle_0_0value = value
        } else
        {
            this._outlineStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this {
        if (((this._outlineWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._outlineWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._outlineWidth_0_0value = value
        } else
        {
            this._outlineWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
        if (((this._outlineColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._outlineColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._outlineColor_0_0value = value
        } else
        {
            this._outlineColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    outlineRadius(value: Dimension | OutlineRadiuses | undefined): this {
        if (((this._outlineRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._outlineRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._outlineRadius_0_0value = value
        } else
        {
            this._outlineRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this {
        if (((this._foregroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._foregroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._foregroundColor_0_0value = value
        } else
        {
            this._foregroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onClick(value: ((event: ClickEvent) => void) | undefined): this {
        if (((this._onClick_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onClick_0_flag = AttributeUpdaterFlag.UPDATE
            this._onClick_0_0value = value
        } else
        {
            this._onClick_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHover(value: ((isHover: boolean,event: HoverEvent) => void) | undefined): this {
        if (((this._onHover_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHover_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHover_0_0value = value
        } else
        {
            this._onHover_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHoverMove(value: ((value0: HoverEvent) => void) | undefined): this {
        if (((this._onHoverMove_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHoverMove_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHoverMove_0_0value = value
        } else
        {
            this._onHoverMove_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAccessibilityHover(value: AccessibilityCallback | undefined): this {
        if (((this._onAccessibilityHover_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAccessibilityHover_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAccessibilityHover_0_0value = value
        } else
        {
            this._onAccessibilityHover_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hoverEffect(value: HoverEffect | undefined): this {
        if (((this._hoverEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._hoverEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._hoverEffect_0_0value = value
        } else
        {
            this._hoverEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onMouse(value: ((event: MouseEvent) => void) | undefined): this {
        if (((this._onMouse_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onMouse_0_flag = AttributeUpdaterFlag.UPDATE
            this._onMouse_0_0value = value
        } else
        {
            this._onMouse_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTouch(value: ((event: TouchEvent) => void) | undefined): this {
        if (((this._onTouch_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTouch_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTouch_0_0value = value
        } else
        {
            this._onTouch_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onKeyEvent(value: ((event: KeyEvent) => void) | undefined): this {
        if (((this._onKeyEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onKeyEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onKeyEvent_0_0value = value
        } else
        {
            this._onKeyEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDigitalCrown(value: ((value0: CrownEvent) => void) | undefined): this {
        if (((this._onDigitalCrown_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDigitalCrown_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDigitalCrown_0_0value = value
        } else
        {
            this._onDigitalCrown_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onKeyPreIme(value: ((value0: KeyEvent) => boolean) | undefined): this {
        if (((this._onKeyPreIme_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onKeyPreIme_0_flag = AttributeUpdaterFlag.UPDATE
            this._onKeyPreIme_0_0value = value
        } else
        {
            this._onKeyPreIme_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onKeyEventDispatch(value: ((value0: KeyEvent) => boolean) | undefined): this {
        if (((this._onKeyEventDispatch_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onKeyEventDispatch_0_flag = AttributeUpdaterFlag.UPDATE
            this._onKeyEventDispatch_0_0value = value
        } else
        {
            this._onKeyEventDispatch_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFocusAxisEvent(value: ((value0: FocusAxisEvent) => void) | undefined): this {
        if (((this._onFocusAxisEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFocusAxisEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFocusAxisEvent_0_0value = value
        } else
        {
            this._onFocusAxisEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAxisEvent(value: ((value0: AxisEvent) => void) | undefined): this {
        if (((this._onAxisEvent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAxisEvent_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAxisEvent_0_0value = value
        } else
        {
            this._onAxisEvent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    focusable(value: boolean | undefined): this {
        if (((this._focusable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._focusable_0_0value) !== (value)))
        {
            this._focusable_0_flag = AttributeUpdaterFlag.UPDATE
            this._focusable_0_0value = value
        } else
        {
            this._focusable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    nextFocus(value: FocusMovement | undefined): this {
        if (((this._nextFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._nextFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._nextFocus_0_0value = value
        } else
        {
            this._nextFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    tabStop(value: boolean | undefined): this {
        if (((this._tabStop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._tabStop_0_0value) !== (value)))
        {
            this._tabStop_0_flag = AttributeUpdaterFlag.UPDATE
            this._tabStop_0_0value = value
        } else
        {
            this._tabStop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFocus(value: (() => void) | undefined): this {
        if (((this._onFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFocus_0_0value = value
        } else
        {
            this._onFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onBlur(value: (() => void) | undefined): this {
        if (((this._onBlur_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onBlur_0_flag = AttributeUpdaterFlag.UPDATE
            this._onBlur_0_0value = value
        } else
        {
            this._onBlur_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    tabIndex(value: number | undefined): this {
        if (((this._tabIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._tabIndex_0_0value) !== (value)))
        {
            this._tabIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._tabIndex_0_0value = value
        } else
        {
            this._tabIndex_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    defaultFocus(value: boolean | undefined): this {
        if (((this._defaultFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._defaultFocus_0_0value) !== (value)))
        {
            this._defaultFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._defaultFocus_0_0value = value
        } else
        {
            this._defaultFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    groupDefaultFocus(value: boolean | undefined): this {
        if (((this._groupDefaultFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._groupDefaultFocus_0_0value) !== (value)))
        {
            this._groupDefaultFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._groupDefaultFocus_0_0value = value
        } else
        {
            this._groupDefaultFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    focusOnTouch(value: boolean | undefined): this {
        if (((this._focusOnTouch_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._focusOnTouch_0_0value) !== (value)))
        {
            this._focusOnTouch_0_flag = AttributeUpdaterFlag.UPDATE
            this._focusOnTouch_0_0value = value
        } else
        {
            this._focusOnTouch_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    focusBox(value: FocusBoxStyle | undefined): this {
        if (((this._focusBox_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._focusBox_0_flag = AttributeUpdaterFlag.UPDATE
            this._focusBox_0_0value = value
        } else
        {
            this._focusBox_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    animation(value: AnimateParam | undefined): this {
        if (((this._animation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._animation_0_flag = AttributeUpdaterFlag.UPDATE
            this._animation_0_0value = value
        } else
        {
            this._animation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    transition(value: TransitionEffect | undefined): this {
        if (((this._transition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._transition_0_flag = AttributeUpdaterFlag.UPDATE
            this._transition_0_0value = value
        } else
        {
            this._transition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    motionBlur(value: MotionBlurOptions | undefined): this {
        if (((this._motionBlur_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._motionBlur_0_flag = AttributeUpdaterFlag.UPDATE
            this._motionBlur_0_0value = value
        } else
        {
            this._motionBlur_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    brightness(value: number | undefined): this {
        if (((this._brightness_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._brightness_0_0value) !== (value)))
        {
            this._brightness_0_flag = AttributeUpdaterFlag.UPDATE
            this._brightness_0_0value = value
        } else
        {
            this._brightness_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    contrast(value: number | undefined): this {
        if (((this._contrast_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contrast_0_0value) !== (value)))
        {
            this._contrast_0_flag = AttributeUpdaterFlag.UPDATE
            this._contrast_0_0value = value
        } else
        {
            this._contrast_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    grayscale(value: number | undefined): this {
        if (((this._grayscale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._grayscale_0_0value) !== (value)))
        {
            this._grayscale_0_flag = AttributeUpdaterFlag.UPDATE
            this._grayscale_0_0value = value
        } else
        {
            this._grayscale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    colorBlend(value: Color | string | Resource | undefined): this {
        if (((this._colorBlend_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._colorBlend_0_flag = AttributeUpdaterFlag.UPDATE
            this._colorBlend_0_0value = value
        } else
        {
            this._colorBlend_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    saturate(value: number | undefined): this {
        if (((this._saturate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._saturate_0_0value) !== (value)))
        {
            this._saturate_0_flag = AttributeUpdaterFlag.UPDATE
            this._saturate_0_0value = value
        } else
        {
            this._saturate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sepia(value: number | undefined): this {
        if (((this._sepia_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._sepia_0_0value) !== (value)))
        {
            this._sepia_0_flag = AttributeUpdaterFlag.UPDATE
            this._sepia_0_0value = value
        } else
        {
            this._sepia_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    invert(value: number | InvertOptions | undefined): this {
        if (((this._invert_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._invert_0_flag = AttributeUpdaterFlag.UPDATE
            this._invert_0_0value = value
        } else
        {
            this._invert_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    hueRotate(value: number | string | undefined): this {
        if (((this._hueRotate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hueRotate_0_0value) !== (value)))
        {
            this._hueRotate_0_flag = AttributeUpdaterFlag.UPDATE
            this._hueRotate_0_0value = value
        } else
        {
            this._hueRotate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    useShadowBatching(value: boolean | undefined): this {
        if (((this._useShadowBatching_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._useShadowBatching_0_0value) !== (value)))
        {
            this._useShadowBatching_0_flag = AttributeUpdaterFlag.UPDATE
            this._useShadowBatching_0_0value = value
        } else
        {
            this._useShadowBatching_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    useEffect(value: boolean | undefined): this {
        if (((this._useEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._useEffect_0_0value) !== (value)))
        {
            this._useEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._useEffect_0_0value = value
        } else
        {
            this._useEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderGroup(value: boolean | undefined): this {
        if (((this._renderGroup_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._renderGroup_0_0value) !== (value)))
        {
            this._renderGroup_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderGroup_0_0value = value
        } else
        {
            this._renderGroup_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    freeze(value: boolean | undefined): this {
        if (((this._freeze_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._freeze_0_0value) !== (value)))
        {
            this._freeze_0_flag = AttributeUpdaterFlag.UPDATE
            this._freeze_0_0value = value
        } else
        {
            this._freeze_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    translate(value: TranslateOptions | undefined): this {
        if (((this._translate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._translate_0_flag = AttributeUpdaterFlag.UPDATE
            this._translate_0_0value = value
        } else
        {
            this._translate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    scale(value: ScaleOptions | undefined): this {
        if (((this._scale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._scale_0_flag = AttributeUpdaterFlag.UPDATE
            this._scale_0_0value = value
        } else
        {
            this._scale_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rotate(value: RotateOptions | RotateAngleOptions | undefined): this {
        if (((this._rotate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._rotate_0_flag = AttributeUpdaterFlag.UPDATE
            this._rotate_0_0value = value
        } else
        {
            this._rotate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    transform(value: matrix4.Matrix4Transit | undefined): this {
        if (((this._transform_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._transform_0_flag = AttributeUpdaterFlag.UPDATE
            this._transform_0_0value = value
        } else
        {
            this._transform_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    transform3D(value: matrix4.Matrix4Transit | undefined): this {
        if (((this._transform3D_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._transform3D_0_flag = AttributeUpdaterFlag.UPDATE
            this._transform3D_0_0value = value
        } else
        {
            this._transform3D_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAppear(value: (() => void) | undefined): this {
        if (((this._onAppear_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAppear_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAppear_0_0value = value
        } else
        {
            this._onAppear_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDisAppear(value: (() => void) | undefined): this {
        if (((this._onDisAppear_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDisAppear_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDisAppear_0_0value = value
        } else
        {
            this._onDisAppear_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAttach(value: VoidCallback | undefined): this {
        if (((this._onAttach_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAttach_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAttach_0_0value = value
        } else
        {
            this._onAttach_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDetach(value: VoidCallback | undefined): this {
        if (((this._onDetach_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDetach_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDetach_0_0value = value
        } else
        {
            this._onDetach_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAreaChange(value: ((oldValue: Area,newValue: Area) => void) | undefined): this {
        if (((this._onAreaChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAreaChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAreaChange_0_0value = value
        } else
        {
            this._onAreaChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    visibility(value: Visibility | undefined): this {
        if (((this._visibility_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._visibility_0_flag = AttributeUpdaterFlag.UPDATE
            this._visibility_0_0value = value
        } else
        {
            this._visibility_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    flexGrow(value: number | undefined): this {
        if (((this._flexGrow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._flexGrow_0_0value) !== (value)))
        {
            this._flexGrow_0_flag = AttributeUpdaterFlag.UPDATE
            this._flexGrow_0_0value = value
        } else
        {
            this._flexGrow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    flexShrink(value: number | undefined): this {
        if (((this._flexShrink_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._flexShrink_0_0value) !== (value)))
        {
            this._flexShrink_0_flag = AttributeUpdaterFlag.UPDATE
            this._flexShrink_0_0value = value
        } else
        {
            this._flexShrink_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    flexBasis(value: number | string | undefined): this {
        if (((this._flexBasis_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._flexBasis_0_0value) !== (value)))
        {
            this._flexBasis_0_flag = AttributeUpdaterFlag.UPDATE
            this._flexBasis_0_0value = value
        } else
        {
            this._flexBasis_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    alignSelf(value: ItemAlign | undefined): this {
        if (((this._alignSelf_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignSelf_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignSelf_0_0value = value
        } else
        {
            this._alignSelf_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    displayPriority(value: number | undefined): this {
        if (((this._displayPriority_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._displayPriority_0_0value) !== (value)))
        {
            this._displayPriority_0_flag = AttributeUpdaterFlag.UPDATE
            this._displayPriority_0_0value = value
        } else
        {
            this._displayPriority_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    zIndex(value: number | undefined): this {
        if (((this._zIndex_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._zIndex_0_0value) !== (value)))
        {
            this._zIndex_0_flag = AttributeUpdaterFlag.UPDATE
            this._zIndex_0_0value = value
        } else
        {
            this._zIndex_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    direction(value: Direction | undefined): this {
        if (((this._direction_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._direction_0_flag = AttributeUpdaterFlag.UPDATE
            this._direction_0_0value = value
        } else
        {
            this._direction_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    align(value: Alignment | undefined): this {
        if (((this._align_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._align_0_flag = AttributeUpdaterFlag.UPDATE
            this._align_0_0value = value
        } else
        {
            this._align_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    position(value: Position | Edges | LocalizedEdges | undefined): this {
        if (((this._position_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._position_0_flag = AttributeUpdaterFlag.UPDATE
            this._position_0_0value = value
        } else
        {
            this._position_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    markAnchor(value: Position | LocalizedPosition | undefined): this {
        if (((this._markAnchor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._markAnchor_0_flag = AttributeUpdaterFlag.UPDATE
            this._markAnchor_0_0value = value
        } else
        {
            this._markAnchor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    offset(value: Position | Edges | LocalizedEdges | undefined): this {
        if (((this._offset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._offset_0_flag = AttributeUpdaterFlag.UPDATE
            this._offset_0_0value = value
        } else
        {
            this._offset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enabled(value: boolean | undefined): this {
        if (((this._enabled_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enabled_0_0value) !== (value)))
        {
            this._enabled_0_flag = AttributeUpdaterFlag.UPDATE
            this._enabled_0_0value = value
        } else
        {
            this._enabled_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    alignRules(value: AlignRuleOption | LocalizedAlignRuleOptions | undefined): this {
        if (((this._alignRules_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignRules_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignRules_0_0value = value
        } else
        {
            this._alignRules_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    aspectRatio(value: number | undefined): this {
        if (((this._aspectRatio_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._aspectRatio_0_0value) !== (value)))
        {
            this._aspectRatio_0_flag = AttributeUpdaterFlag.UPDATE
            this._aspectRatio_0_0value = value
        } else
        {
            this._aspectRatio_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    clickEffect(value: ClickEffect | null | undefined): this {
        if (((this._clickEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._clickEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._clickEffect_0_0value = value
        } else
        {
            this._clickEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDragStart(value: ((event: DragEvent,extraParams?: string) => CustomBuilder | DragItemInfo) | undefined): this {
        if (((this._onDragStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDragStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDragStart_0_0value = value
        } else
        {
            this._onDragStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDragEnter(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._onDragEnter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDragEnter_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDragEnter_0_0value = value
        } else
        {
            this._onDragEnter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDragMove(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._onDragMove_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDragMove_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDragMove_0_0value = value
        } else
        {
            this._onDragMove_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDragLeave(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._onDragLeave_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDragLeave_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDragLeave_0_0value = value
        } else
        {
            this._onDragLeave_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDrop(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._onDrop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDrop_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDrop_0_0value = value
        } else
        {
            this._onDrop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDragEnd(value: ((event: DragEvent,extraParams?: string) => void) | undefined): this {
        if (((this._onDragEnd_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDragEnd_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDragEnd_0_0value = value
        } else
        {
            this._onDragEnd_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    allowDrop(value: Array<uniformTypeDescriptor.UniformDataType> | null | undefined): this {
        if (((this._allowDrop_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._allowDrop_0_flag = AttributeUpdaterFlag.UPDATE
            this._allowDrop_0_0value = value
        } else
        {
            this._allowDrop_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    draggable(value: boolean | undefined): this {
        if (((this._draggable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._draggable_0_0value) !== (value)))
        {
            this._draggable_0_flag = AttributeUpdaterFlag.UPDATE
            this._draggable_0_0value = value
        } else
        {
            this._draggable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dragPreview(value: CustomBuilder | DragItemInfo | string | undefined): this {
        if (((this._dragPreview_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dragPreview_0_flag = AttributeUpdaterFlag.UPDATE
            this._dragPreview_0_0value = value
        } else
        {
            this._dragPreview_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPreDrag(value: ((value0: PreDragStatus) => void) | undefined): this {
        if (((this._onPreDrag_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPreDrag_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPreDrag_0_0value = value
        } else
        {
            this._onPreDrag_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    linearGradient(value: LinearGradientOptions | undefined): this {
        if (((this._linearGradient_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._linearGradient_0_flag = AttributeUpdaterFlag.UPDATE
            this._linearGradient_0_0value = value
        } else
        {
            this._linearGradient_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sweepGradient(value: SweepGradientOptions | undefined): this {
        if (((this._sweepGradient_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sweepGradient_0_flag = AttributeUpdaterFlag.UPDATE
            this._sweepGradient_0_0value = value
        } else
        {
            this._sweepGradient_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    radialGradient(value: RadialGradientOptions | undefined): this {
        if (((this._radialGradient_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._radialGradient_0_flag = AttributeUpdaterFlag.UPDATE
            this._radialGradient_0_0value = value
        } else
        {
            this._radialGradient_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    motionPath(value: MotionPathOptions | undefined): this {
        if (((this._motionPath_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._motionPath_0_flag = AttributeUpdaterFlag.UPDATE
            this._motionPath_0_0value = value
        } else
        {
            this._motionPath_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    shadow(value: ShadowOptions | ShadowStyle | undefined): this {
        if (((this._shadow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._shadow_0_flag = AttributeUpdaterFlag.UPDATE
            this._shadow_0_0value = value
        } else
        {
            this._shadow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    clip(value: boolean | undefined): this {
        if (((this._clip_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._clip_0_0value) !== (value)))
        {
            this._clip_0_flag = AttributeUpdaterFlag.UPDATE
            this._clip_0_0value = value
        } else
        {
            this._clip_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        if (((this._clipShape_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._clipShape_0_flag = AttributeUpdaterFlag.UPDATE
            this._clipShape_0_0value = value
        } else
        {
            this._clipShape_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    mask(value: ProgressMask | undefined): this {
        if (((this._mask_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._mask_0_flag = AttributeUpdaterFlag.UPDATE
            this._mask_0_0value = value
        } else
        {
            this._mask_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
        if (((this._maskShape_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._maskShape_0_flag = AttributeUpdaterFlag.UPDATE
            this._maskShape_0_0value = value
        } else
        {
            this._maskShape_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    key(value: string | undefined): this {
        if (((this._key_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._key_0_0value) !== (value)))
        {
            this._key_0_flag = AttributeUpdaterFlag.UPDATE
            this._key_0_0value = value
        } else
        {
            this._key_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    id(value: string | undefined): this {
        if (((this._id_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._id_0_0value) !== (value)))
        {
            this._id_0_flag = AttributeUpdaterFlag.UPDATE
            this._id_0_0value = value
        } else
        {
            this._id_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    geometryTransition(value: string | undefined): this {
        if (((this._geometryTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._geometryTransition_0_0value) !== (value)))
        {
            this._geometryTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._geometryTransition_0_0value = value
        } else
        {
            this._geometryTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    restoreId(value: number | undefined): this {
        if (((this._restoreId_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._restoreId_0_0value) !== (value)))
        {
            this._restoreId_0_flag = AttributeUpdaterFlag.UPDATE
            this._restoreId_0_0value = value
        } else
        {
            this._restoreId_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sphericalEffect(value: number | undefined): this {
        if (((this._sphericalEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._sphericalEffect_0_0value) !== (value)))
        {
            this._sphericalEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._sphericalEffect_0_0value = value
        } else
        {
            this._sphericalEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    lightUpEffect(value: number | undefined): this {
        if (((this._lightUpEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._lightUpEffect_0_0value) !== (value)))
        {
            this._lightUpEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._lightUpEffect_0_0value = value
        } else
        {
            this._lightUpEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this {
        if (((this._pixelStretchEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.UPDATE
            this._pixelStretchEffect_0_0value = value
        } else
        {
            this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityGroup(value: boolean | undefined): this {
        if (((this._accessibilityGroup_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityGroup_0_0value) !== (value)))
        {
            this._accessibilityGroup_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityGroup_0_0value = value
        } else
        {
            this._accessibilityGroup_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityText(value: string | undefined): this {
        if (((this._accessibilityText_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityText_0_0value) !== (value)))
        {
            this._accessibilityText_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityText_0_0value = value
        } else
        {
            this._accessibilityText_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityNextFocusId(value: string | undefined): this {
        if (((this._accessibilityNextFocusId_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityNextFocusId_0_0value) !== (value)))
        {
            this._accessibilityNextFocusId_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityNextFocusId_0_0value = value
        } else
        {
            this._accessibilityNextFocusId_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityDefaultFocus(value: boolean | undefined): this {
        if (((this._accessibilityDefaultFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityDefaultFocus_0_0value) !== (value)))
        {
            this._accessibilityDefaultFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityDefaultFocus_0_0value = value
        } else
        {
            this._accessibilityDefaultFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityUseSamePage(value: AccessibilitySamePageMode | undefined): this {
        if (((this._accessibilityUseSamePage_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._accessibilityUseSamePage_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityUseSamePage_0_0value = value
        } else
        {
            this._accessibilityUseSamePage_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityScrollTriggerable(value: boolean | undefined): this {
        if (((this._accessibilityScrollTriggerable_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityScrollTriggerable_0_0value) !== (value)))
        {
            this._accessibilityScrollTriggerable_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityScrollTriggerable_0_0value = value
        } else
        {
            this._accessibilityScrollTriggerable_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityText(value: Resource | undefined): this {
        if (((this._accessibilityText_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._accessibilityText_1_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityText_1_0value = value
        } else
        {
            this._accessibilityText_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityRole(value: AccessibilityRoleType | undefined): this {
        if (((this._accessibilityRole_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._accessibilityRole_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityRole_0_0value = value
        } else
        {
            this._accessibilityRole_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAccessibilityFocus(value: AccessibilityFocusCallback | undefined): this {
        if (((this._onAccessibilityFocus_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAccessibilityFocus_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAccessibilityFocus_0_0value = value
        } else
        {
            this._onAccessibilityFocus_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAccessibilityActionIntercept(value: AccessibilityActionInterceptCallback | undefined): this {
        if (((this._onAccessibilityActionIntercept_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAccessibilityActionIntercept_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAccessibilityActionIntercept_0_0value = value
        } else
        {
            this._onAccessibilityActionIntercept_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityTextHint(value: string | undefined): this {
        if (((this._accessibilityTextHint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityTextHint_0_0value) !== (value)))
        {
            this._accessibilityTextHint_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityTextHint_0_0value = value
        } else
        {
            this._accessibilityTextHint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityDescription(value: string | undefined): this {
        if (((this._accessibilityDescription_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityDescription_0_0value) !== (value)))
        {
            this._accessibilityDescription_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityDescription_0_0value = value
        } else
        {
            this._accessibilityDescription_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityDescription(value: Resource | undefined): this {
        if (((this._accessibilityDescription_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._accessibilityDescription_1_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityDescription_1_0value = value
        } else
        {
            this._accessibilityDescription_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityLevel(value: string | undefined): this {
        if (((this._accessibilityLevel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityLevel_0_0value) !== (value)))
        {
            this._accessibilityLevel_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityLevel_0_0value = value
        } else
        {
            this._accessibilityLevel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityVirtualNode(value: CustomBuilder | undefined): this {
        if (((this._accessibilityVirtualNode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._accessibilityVirtualNode_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityVirtualNode_0_0value = value
        } else
        {
            this._accessibilityVirtualNode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityChecked(value: boolean | undefined): this {
        if (((this._accessibilityChecked_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityChecked_0_0value) !== (value)))
        {
            this._accessibilityChecked_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityChecked_0_0value = value
        } else
        {
            this._accessibilityChecked_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilitySelected(value: boolean | undefined): this {
        if (((this._accessibilitySelected_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilitySelected_0_0value) !== (value)))
        {
            this._accessibilitySelected_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilitySelected_0_0value = value
        } else
        {
            this._accessibilitySelected_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    obscured(value: Array<ObscuredReasons> | undefined): this {
        if (((this._obscured_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._obscured_0_flag = AttributeUpdaterFlag.UPDATE
            this._obscured_0_0value = value
        } else
        {
            this._obscured_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    reuseId(value: string | undefined): this {
        if (((this._reuseId_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._reuseId_0_0value) !== (value)))
        {
            this._reuseId_0_flag = AttributeUpdaterFlag.UPDATE
            this._reuseId_0_0value = value
        } else
        {
            this._reuseId_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    reuse(value: ReuseOptions | undefined): this {
        if (((this._reuse_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._reuse_0_flag = AttributeUpdaterFlag.UPDATE
            this._reuse_0_0value = value
        } else
        {
            this._reuse_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderFit(value: RenderFit | undefined): this {
        if (((this._renderFit_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._renderFit_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderFit_0_0value = value
        } else
        {
            this._renderFit_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this {
        if (((this._backgroundBrightness_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundBrightness_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundBrightness_0_0value = value
        } else
        {
            this._backgroundBrightness_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGestureJudgeBegin(value: ((gestureInfo: GestureInfo,event: BaseGestureEvent) => GestureJudgeResult) | undefined): this {
        if (((this._onGestureJudgeBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGestureJudgeBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGestureJudgeBegin_0_0value = value
        } else
        {
            this._onGestureJudgeBegin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGestureRecognizerJudgeBegin(value: GestureRecognizerJudgeBeginCallback | undefined): this {
        if (((this._onGestureRecognizerJudgeBegin_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onGestureRecognizerJudgeBegin_0_flag = AttributeUpdaterFlag.UPDATE
            this._onGestureRecognizerJudgeBegin_0_0value = value
        } else
        {
            this._onGestureRecognizerJudgeBegin_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
        if (((this._shouldBuiltInRecognizerParallelWith_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._shouldBuiltInRecognizerParallelWith_0_flag = AttributeUpdaterFlag.UPDATE
            this._shouldBuiltInRecognizerParallelWith_0_0value = value
        } else
        {
            this._shouldBuiltInRecognizerParallelWith_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    monopolizeEvents(value: boolean | undefined): this {
        if (((this._monopolizeEvents_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._monopolizeEvents_0_0value) !== (value)))
        {
            this._monopolizeEvents_0_flag = AttributeUpdaterFlag.UPDATE
            this._monopolizeEvents_0_0value = value
        } else
        {
            this._monopolizeEvents_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onTouchIntercept(value: ((value0: TouchEvent) => HitTestMode) | undefined): this {
        if (((this._onTouchIntercept_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onTouchIntercept_0_flag = AttributeUpdaterFlag.UPDATE
            this._onTouchIntercept_0_0value = value
        } else
        {
            this._onTouchIntercept_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onSizeChange(value: SizeChangeCallback | undefined): this {
        if (((this._onSizeChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onSizeChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onSizeChange_0_0value = value
        } else
        {
            this._onSizeChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityFocusDrawLevel(value: FocusDrawLevel | undefined): this {
        if (((this._accessibilityFocusDrawLevel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._accessibilityFocusDrawLevel_0_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityFocusDrawLevel_0_0value = value
        } else
        {
            this._accessibilityFocusDrawLevel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    expandSafeArea(types?: Array<SafeAreaType>, edges?: Array<SafeAreaEdge>): this {
        if (((this._expandSafeArea_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._expandSafeArea_0_flag = AttributeUpdaterFlag.UPDATE
            this._expandSafeArea_0_0value = types
            this._expandSafeArea_0_1value = edges
        } else
        {
            this._expandSafeArea_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    background(builder: CustomBuilder | undefined, options?: BackgroundOptions): this {
        if (((this._background_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._background_0_flag = AttributeUpdaterFlag.UPDATE
            this._background_0_0value = builder
            this._background_0_1value = options
        } else
        {
            this._background_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundImage(value: ResourceStr | image.PixelMap | undefined): this {
        if (((this._backgroundImage_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundImage_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundImage_0_0value = value
        } else
        {
            this._backgroundImage_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundImage(src: ResourceStr | image.PixelMap | undefined, options: BackgroundImageOptions): this {
        if (((this._backgroundImage_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._backgroundImage_1_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundImage_1_0value = src
            this._backgroundImage_1_1value = options
        } else
        {
            this._backgroundImage_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundImage(src: ResourceStr | image.PixelMap | undefined, repeat: ImageRepeat): this {
        if (((this._backgroundImage_2_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._backgroundImage_2_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundImage_2_0value = src
            this._backgroundImage_2_1value = repeat
        } else
        {
            this._backgroundImage_2_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (((this._backgroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true))
        {
            this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundBlurStyle_0_0value = style
            this._backgroundBlurStyle_0_1value = options
            this._backgroundBlurStyle_0_2value = sysOptions
        } else
        {
            this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this {
        if (((this._backgroundEffect_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._backgroundEffect_1_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundEffect_1_0value = options
            this._backgroundEffect_1_1value = sysOptions
        } else
        {
            this._backgroundEffect_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (((this._foregroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true))
        {
            this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._foregroundBlurStyle_0_0value = style
            this._foregroundBlurStyle_0_1value = options
            this._foregroundBlurStyle_0_2value = sysOptions
        } else
        {
            this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onClick(event: ((event: ClickEvent) => void) | undefined, distanceThreshold: number | undefined): this {
        if (((this._onClick_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._onClick_1_1value) !== (distanceThreshold)))
        {
            this._onClick_1_flag = AttributeUpdaterFlag.UPDATE
            this._onClick_1_0value = event
            this._onClick_1_1value = distanceThreshold
        } else
        {
            this._onClick_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
        if (((this._focusScopeId_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._focusScopeId_0_0value) !== (id)) || ((this._focusScopeId_0_1value) !== (isGroup)) || ((this._focusScopeId_0_2value) !== (arrowStepOut)))
        {
            this._focusScopeId_0_flag = AttributeUpdaterFlag.UPDATE
            this._focusScopeId_0_0value = id
            this._focusScopeId_0_1value = isGroup
            this._focusScopeId_0_2value = arrowStepOut
        } else
        {
            this._focusScopeId_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
        if (((this._focusScopePriority_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._focusScopePriority_0_0value) !== (scopeId)) || (true))
        {
            this._focusScopePriority_0_flag = AttributeUpdaterFlag.UPDATE
            this._focusScopePriority_0_0value = scopeId
            this._focusScopePriority_0_1value = priority
        } else
        {
            this._focusScopePriority_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    transition(effect: TransitionEffect | undefined, onFinish: TransitionFinishCallback | undefined): this {
        if (((this._transition_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._transition_1_flag = AttributeUpdaterFlag.UPDATE
            this._transition_1_0value = effect
            this._transition_1_1value = onFinish
        } else
        {
            this._transition_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (((this._blur_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._blur_0_0value) !== (blurRadius)) || (true) || (true))
        {
            this._blur_0_flag = AttributeUpdaterFlag.UPDATE
            this._blur_0_0value = blurRadius
            this._blur_0_1value = options
            this._blur_0_2value = sysOptions
        } else
        {
            this._blur_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this {
        if (((this._linearGradientBlur_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._linearGradientBlur_0_0value) !== (value)) || (true))
        {
            this._linearGradientBlur_0_flag = AttributeUpdaterFlag.UPDATE
            this._linearGradientBlur_0_0value = value
            this._linearGradientBlur_0_1value = options
        } else
        {
            this._linearGradientBlur_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    systemBarEffect(): this {
        if ((this._systemBarEffect_0_flag) == (AttributeUpdaterFlag.INITIAL))
        {
            this._systemBarEffect_0_flag = AttributeUpdaterFlag.UPDATE
        } else
        {
            this._systemBarEffect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    useEffect(useEffect: boolean | undefined, effectType: EffectType | undefined): this {
        if (((this._useEffect_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._useEffect_1_0value) !== (useEffect)) || (true))
        {
            this._useEffect_1_flag = AttributeUpdaterFlag.UPDATE
            this._useEffect_1_0value = useEffect
            this._useEffect_1_1value = effectType
        } else
        {
            this._useEffect_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
        if (((this._backdropBlur_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._backdropBlur_0_0value) !== (radius)) || (true) || (true))
        {
            this._backdropBlur_0_flag = AttributeUpdaterFlag.UPDATE
            this._backdropBlur_0_0value = radius
            this._backdropBlur_0_1value = options
            this._backdropBlur_0_2value = sysOptions
        } else
        {
            this._backdropBlur_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this {
        if (((this._sharedTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._sharedTransition_0_0value) !== (id)) || (true))
        {
            this._sharedTransition_0_flag = AttributeUpdaterFlag.UPDATE
            this._sharedTransition_0_0value = id
            this._sharedTransition_0_1value = options
        } else
        {
            this._sharedTransition_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
        if (((this._chainMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._chainMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._chainMode_0_0value = direction
            this._chainMode_0_1value = style
        } else
        {
            this._chainMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDrop(eventCallback: OnDragEventCallback | undefined, dropOptions?: DropOptions): this {
        if (((this._onDrop_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._onDrop_1_flag = AttributeUpdaterFlag.UPDATE
            this._onDrop_1_0value = eventCallback
            this._onDrop_1_1value = dropOptions
        } else
        {
            this._onDrop_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dragPreview(preview: CustomBuilder | DragItemInfo | string | undefined, config?: PreviewConfiguration): this {
        if (((this._dragPreview_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._dragPreview_1_flag = AttributeUpdaterFlag.UPDATE
            this._dragPreview_1_0value = preview
            this._dragPreview_1_1value = config
        } else
        {
            this._dragPreview_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dragPreviewOptions(value: DragPreviewOptions | undefined, options?: DragInteractionOptions): this {
        if (((this._dragPreviewOptions_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._dragPreviewOptions_0_flag = AttributeUpdaterFlag.UPDATE
            this._dragPreviewOptions_0_0value = value
            this._dragPreviewOptions_0_1value = options
        } else
        {
            this._dragPreviewOptions_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    overlay(value: string | CustomBuilder | ComponentContent | undefined, options?: OverlayOptions): this {
        if (((this._overlay_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._overlay_0_flag = AttributeUpdaterFlag.UPDATE
            this._overlay_0_0value = value
            this._overlay_0_1value = options
        } else
        {
            this._overlay_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    blendMode(value: BlendMode | undefined, type?: BlendApplyType): this {
        if (((this._blendMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._blendMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._blendMode_0_0value = value
            this._blendMode_0_1value = type
        } else
        {
            this._blendMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    advancedBlendMode(effect: BlendMode | uiEffect.Blender, type?: BlendApplyType): this {
        throw new Error("Not implemented")
    }
    geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this {
        if (((this._geometryTransition_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._geometryTransition_1_0value) !== (id)) || (true))
        {
            this._geometryTransition_1_flag = AttributeUpdaterFlag.UPDATE
            this._geometryTransition_1_0value = id
            this._geometryTransition_1_1value = options
        } else
        {
            this._geometryTransition_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindTips(message: TipsMessageType | undefined, options?: TipsOptions): this {
        if (((this._bindTips_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._bindTips_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindTips_0_0value = message
            this._bindTips_0_1value = options
        } else
        {
            this._bindTips_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindPopup(show: boolean | undefined, popup: PopupOptions | CustomPopupOptions | undefined): this {
        if (((this._bindPopup_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._bindPopup_0_0value) !== (show)) || (true))
        {
            this._bindPopup_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindPopup_0_0value = show
            this._bindPopup_0_1value = popup
        } else
        {
            this._bindPopup_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindMenu(content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): this {
        if (((this._bindMenu_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._bindMenu_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindMenu_0_0value = content
            this._bindMenu_0_1value = options
        } else
        {
            this._bindMenu_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindMenu(isShow: boolean | undefined, content: Array<MenuElement> | CustomBuilder | undefined, options?: MenuOptions): this {
        if (((this._bindMenu_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._bindMenu_1_0value) !== (isShow)) || (true) || (true))
        {
            this._bindMenu_1_flag = AttributeUpdaterFlag.UPDATE
            this._bindMenu_1_0value = isShow
            this._bindMenu_1_1value = content
            this._bindMenu_1_2value = options
        } else
        {
            this._bindMenu_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindContextMenu(content: CustomBuilder | undefined, responseType: ResponseType | undefined, options?: ContextMenuOptions): this {
        if (((this._bindContextMenu_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true))
        {
            this._bindContextMenu_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindContextMenu_0_0value = content
            this._bindContextMenu_0_1value = responseType
            this._bindContextMenu_0_2value = options
        } else
        {
            this._bindContextMenu_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindContextMenu(isShown: boolean | undefined, content: CustomBuilder | undefined, options?: ContextMenuOptions): this {
        if (((this._bindContextMenu_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._bindContextMenu_1_0value) !== (isShown)) || (true) || (true))
        {
            this._bindContextMenu_1_flag = AttributeUpdaterFlag.UPDATE
            this._bindContextMenu_1_0value = isShown
            this._bindContextMenu_1_1value = content
            this._bindContextMenu_1_2value = options
        } else
        {
            this._bindContextMenu_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindContentCover(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, type?: ModalTransition): this {
        if (((this._bindContentCover_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true))
        {
            this._bindContentCover_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindContentCover_0_0value = isShow
            this._bindContentCover_0_1value = builder
            this._bindContentCover_0_2value = type
        } else
        {
            this._bindContentCover_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindContentCover(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, options?: ContentCoverOptions): this {
        if (((this._bindContentCover_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true))
        {
            this._bindContentCover_1_flag = AttributeUpdaterFlag.UPDATE
            this._bindContentCover_1_0value = isShow
            this._bindContentCover_1_1value = builder
            this._bindContentCover_1_2value = options
        } else
        {
            this._bindContentCover_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    bindSheet(isShow: boolean | Bindable<boolean> | undefined, builder: CustomBuilder | undefined, options?: SheetOptions): this {
        if (((this._bindSheet_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true))
        {
            this._bindSheet_0_flag = AttributeUpdaterFlag.UPDATE
            this._bindSheet_0_0value = isShow
            this._bindSheet_0_1value = builder
            this._bindSheet_0_2value = options
        } else
        {
            this._bindSheet_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onVisibleAreaChange(ratios: Array<number> | undefined, event: VisibleAreaChangeCallback | undefined): this {
        if (((this._onVisibleAreaChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._onVisibleAreaChange_0_0value) !== (ratios)) || (true))
        {
            this._onVisibleAreaChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onVisibleAreaChange_0_0value = ratios
            this._onVisibleAreaChange_0_1value = event
        } else
        {
            this._onVisibleAreaChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onVisibleAreaApproximateChange(options: VisibleAreaEventOptions | undefined, event: VisibleAreaChangeCallback | undefined): this {
        if (((this._onVisibleAreaApproximateChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true))
        {
            this._onVisibleAreaApproximateChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onVisibleAreaApproximateChange_0_0value = options
            this._onVisibleAreaApproximateChange_0_1value = event
        } else
        {
            this._onVisibleAreaApproximateChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
        if (((this._keyboardShortcut_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || (true) || (true))
        {
            this._keyboardShortcut_0_flag = AttributeUpdaterFlag.UPDATE
            this._keyboardShortcut_0_0value = value
            this._keyboardShortcut_0_1value = keys
            this._keyboardShortcut_0_2value = action
        } else
        {
            this._keyboardShortcut_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    accessibilityGroup(isGroup: boolean | undefined, config: AccessibilityOptions | undefined): this {
        if (((this._accessibilityGroup_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._accessibilityGroup_1_0value) !== (isGroup)) || (true))
        {
            this._accessibilityGroup_1_flag = AttributeUpdaterFlag.UPDATE
            this._accessibilityGroup_1_0value = isGroup
            this._accessibilityGroup_1_1value = config
        } else
        {
            this._accessibilityGroup_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture: boolean | undefined): this {
        if (((this._onGestureRecognizerJudgeBegin_1_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._onGestureRecognizerJudgeBegin_1_1value) !== (exposeInnerGesture)))
        {
            this._onGestureRecognizerJudgeBegin_1_flag = AttributeUpdaterFlag.UPDATE
            this._onGestureRecognizerJudgeBegin_1_0value = callback_
            this._onGestureRecognizerJudgeBegin_1_1value = exposeInnerGesture
        } else
        {
            this._onGestureRecognizerJudgeBegin_1_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
