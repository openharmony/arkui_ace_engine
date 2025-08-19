/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Length } from "arkui/component/units";
import {ArkCommonMethodPeer, LayoutPolicy, ClickEvent, CommonMethod, KeyEvent, Rectangle, SafeAreaType, SafeAreaEdge,
  FocusMovement, SizeChangeCallback, ShouldBuiltInRecognizerParallelWithCallback, AlignRuleOption, ChainStyle,
  GestureRecognizerJudgeBeginCallback, FocusAxisEvent, AxisEvent, HoverEvent, LocalizedAlignRuleOptions,
  TouchEvent, MouseEvent, CustomProperty, ArkCommonMethodComponent } from './component/common';
import { 
  AnimateParam, BackgroundEffectOptions, ForegroundEffectOptions, OutlineStyle, TransitionEffect, MotionBlurOptions,
   InvertOptions, TranslateOptions, sharedTransitionOptions,  BlendMode, BlendApplyType, EffectType, 
  ScaleOptions, RotateOptions, ClickEffect,  LinearGradientOptions, SweepGradientOptions, RadialGradientOptions,
  MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, PixelStretchEffectOptions, BackgroundBrightnessOptions,
  BlurStyle, BackgroundBlurStyleOptions, SystemAdaptiveOptions, ForegroundBlurStyleOptions, TransitionFinishCallback,
  BlurOptions, LinearGradientBlurOptions, GeometryTransitionOptions } from "./component/common";
import { PeerNode } from './PeerNode';
import { ResourceColor, ResourceStr, SizeOptions, Area, Position, Padding, LocalizedPadding, Edges, LocalizedEdges,
  LocalizedPosition, ConstraintSizeOptions, Dimension, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths,
  EdgeColors, LocalizedEdgeColors, OutlineRadiuses } from './component/units';
import { runtimeType, RuntimeType } from '@koalaui/interop';
import { Axis, FunctionKey, ModifierKey, ImageRepeat, ImageSize, HitTestMode, HoverEffect, Visibility, Alignment,
  ItemAlign, ColoringStrategy, Color, RenderFit } from './component/enums';
import { FocusBoxStyle, FocusPriority } from './component/focus';
import { GestureInfo, BaseGestureEvent, GestureJudgeResult } from './component/gesture';
import { ResizableOptions } from './component/image';
import { LengthMetrics } from "./Graphics"
import { PixelMap, Filter, VisualEffect, BrightnessBlender } from '#external';
import { Resource } from "global.resource";
import { hookModifierBackgroundImageImpl } from './handwritten/ArkBackgroundImageImpl';
import { hookCustomPropertyImpl } from "./handwritten/CommonHandWritten"
import { CircleShape, EllipseShape, PathShape, RectShape } from "@ohos/arkui/shape";

export enum AttributeUpdaterFlag {
  INITIAL = 0,
  UPDATE = 1,
  SKIP = 2,
  RESET = 3,
}
export class CommonMethodModifier implements CommonMethod {
  _width_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _width_value?: Length | LayoutPolicy | undefined

  _height_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _height_value?: Length | LayoutPolicy | undefined

  _backgroundColor_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundColor_value?: ResourceColor | undefined

  _backgroundEffect_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundEffect_1_0value?: BackgroundEffectOptions | undefined
  _backgroundEffect_1_1value?: SystemAdaptiveOptions | undefined
  _backgroundEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundEffect_0_0value?: BackgroundEffectOptions | undefined

  _foregroundEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _foregroundEffect_0_0value?: ForegroundEffectOptions | undefined

  _backgroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundBlurStyle_0_0value?: BlurStyle | undefined
  _backgroundBlurStyle_0_1value?: BackgroundBlurStyleOptions | undefined
  _backgroundBlurStyle_0_2value?: SystemAdaptiveOptions | undefined

  _foregroundBlurStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _foregroundBlurStyle_0_0value?: BlurStyle | undefined
  _foregroundBlurStyle_0_1value?: ForegroundBlurStyleOptions | undefined
  _foregroundBlurStyle_0_2value?: SystemAdaptiveOptions | undefined

  _visualEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _visualEffect_0_0value?: VisualEffect | undefined

  _backgroundFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundFilter_0_0value?: Filter | undefined

  _foregroundFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _foregroundFilter_0_0value?: Filter | undefined

  _compositingFilter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _compositingFilter_0_0value?: Filter | undefined

  _opacity_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _opacity_0_0value?: number | Resource | undefined

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
  _rotate_0_0value?: RotateOptions | undefined

  _transform_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _transform_0_0value?: Object | undefined

  _clickEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _clickEffect_0_0value?: ClickEffect | undefined

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

  _sphericalEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _sphericalEffect_0_0value?: number | undefined

  _lightUpEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _lightUpEffect_0_0value?: number | undefined

  _pixelStretchEffect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _pixelStretchEffect_0_0value?: PixelStretchEffectOptions | undefined

  _renderFit_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _renderFit_0_0value?: RenderFit | undefined

  _backgroundBrightness_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundBrightness_0_0value?: BackgroundBrightnessOptions | undefined

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

  _blendMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _blendMode_0_0value?: BlendMode | undefined
  _blendMode_0_1value?: BlendApplyType | undefined

  _advancedBlendMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _advancedBlendMode_0_0value?: BlendMode | BrightnessBlender
  _advancedBlendMode_0_1value?: BlendApplyType | undefined

  _animation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _animation_0_0value?: AnimateParam | undefined
  _transition_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _transition_1_0value?: TransitionEffect | undefined
  _transition_1_1value?: TransitionFinishCallback | undefined
  _sharedTransition_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _sharedTransition_0_0value?: string | undefined
  _sharedTransition_0_1value?: sharedTransitionOptions | undefined
  _geometryTransition_1_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _geometryTransition_1_0value?: string | undefined
  _geometryTransition_1_1value?: GeometryTransitionOptions | undefined

  _size_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _size_value?: SizeOptions | undefined

  _constraintSize_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _constraintSize_value?: ConstraintSizeOptions | undefined

  _layoutWeight_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _layoutWeight_value?: number | string | undefined

  _padding_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _padding_value?: Padding | Length | LocalizedPadding | undefined

  _safeAreaPadding_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _safeAreaPadding_value?: Padding | LengthMetrics | LocalizedPadding | undefined

  _margin_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _margin_value?: Padding | Length | LocalizedPadding | undefined

  _flexGrow_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _flexGrow_value?: number | undefined

  _flexShrink_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _flexShrink_value?: number | undefined

  _flexBasis_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _flexBasis_value?: number | string | undefined

  _alignSelf_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _alignSelf_value?: ItemAlign | undefined

  _align_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _align_value?: Alignment | undefined

  _position_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _position_value?: Position | Edges | LocalizedEdges | undefined

  _markAnchor_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _markAnchor_value?: Position | LocalizedPosition | undefined

  _offset_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _offset_value?: Position | Edges | LocalizedEdges | undefined

  _alignRules_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _alignRules_value?: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined

  _chainMode_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _chainMode_direction?: Axis | undefined
  _chainMode_style: ChainStyle | undefined

  _aspectRatio_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _aspectRatio_value?: number | undefined

  _expandSafeArea_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _expandSafeArea_types?: Array<SafeAreaType> | undefined
  _expandSafeArea_edges?: Array<SafeAreaEdge> | undefined

  _onClick_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onClick0_value?: ((event: ClickEvent) => void) | undefined

  _zIndex_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _zIndex0_value?: number | undefined

  _backgroundImage_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundImage_src?: ResourceStr | PixelMap | undefined
  _backgroundImage_repeat?: ImageRepeat | undefined

  _backgroundImageSize_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundImageSize_value?: SizeOptions | ImageSize | undefined

  _backgroundImagePosition_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundImagePosition_value?: Position | Alignment | undefined

  _backgroundImageResizable_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _backgroundImageResizable_value?: ResizableOptions | undefined

  _onHover_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onHover_value?: ((isHover: boolean, event: HoverEvent) => void) | undefined

  _onHoverMove_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onHoverMove_value?: ((parameter: HoverEvent) => void) | undefined

  _onMouse_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onMouse_value?: ((event: MouseEvent) => void) | undefined

  _onTouch_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onTouch_value?: ((event: TouchEvent) => void) | undefined

  _onFocusAxisEvent_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onFocusAxisEvent_value?: ((parameter: FocusAxisEvent) => void) | undefined

  _onAxisEvent_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onAxisEvent_value?: ((parameter: AxisEvent) => void) | undefined

  _onKeyEvent_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onKeyEvent1_value?: ((event: KeyEvent) => boolean) | undefined

  _onKeyPreIme_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onKeyPreIme_value?: ((event: KeyEvent) => boolean) | undefined

  _onKeyEventDispatch_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onKeyEventDispatch_value?: ((event: KeyEvent) => boolean) | undefined

  _keyboardShortcut_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _keyboardShortcut_value?: string | FunctionKey | undefined
  _keyboardShortcut_keys?: Array<ModifierKey> | undefined
  _keyboardShortcut_action?: (() => void)

  _focusable_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _focusable_value?: boolean | undefined

  _nextFocus_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _nextFocus_value?: FocusMovement | undefined

  _tabIndex_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _tabIndex_value?: number | undefined

  _defaultFocus_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _defaultFocus_value?: boolean | undefined

  _groupDefaultFocus_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _groupDefaultFocus_value?: boolean | undefined

  _focusOnTouch_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _focusOnTouch_value?: boolean | undefined

  _focusBox_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _focusBox_value?: FocusBoxStyle | undefined

  _focusScopeId_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _focusScopeId_id?: string | undefined
  _focusScopeId_isGroup?: boolean
  _focusScopeId_arrowStepOut?: boolean

  _focusScopePriority_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _focusScopePriority_scopeId?: string | undefined
  _focusScopePriority_priority?: FocusPriority

  _tabStop_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _tabStop_value?: boolean | undefined

  _onFocus_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onFocus_value?: (() => void) | undefined

  _onBlur_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onBlur_value?: (() => void) | undefined

  _onAppear_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onAppear_value?: (() => void) | undefined

  _onDisAppear_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onDisAppear_value?: (() => void) | undefined

  _onAttach_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onAttach_value?: (() => void) | undefined

  _onDetach_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onDetach_value?: (() => void) | undefined

  _onAreaChange_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onAreaChange_value?: ((oldValue: Area, newValue: Area) => void) | undefined

  _onSizeChange_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onSizeChange_value?: SizeChangeCallback | undefined

  _onGestureJudgeBegin_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onGestureJudgeBegin_value?: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined

  _shouldBuiltInRecognizerParallelWith_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _shouldBuiltInRecognizerParallelWith_value?: ShouldBuiltInRecognizerParallelWithCallback | undefined

  _onGestureRecognizerJudgeBegin_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _onGestureRecognizerJudgeBegin_callback?: GestureRecognizerJudgeBeginCallback | undefined
  _onGestureRecognizerJudgeBegin_exposeInnerGesture?: boolean

  _responseRegion_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _responseRegion_value?: Array<Rectangle> | Rectangle | undefined

  _hitTestBehavior_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _hitTestBehavior_value?: HitTestMode | undefined

  _monopolizeEvents_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _monopolizeEvents_value?: boolean | undefined

  _restoreId_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _restoreId_value?: number | undefined

  _hoverEffect_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _hoverEffect_value?: HoverEffect | undefined

  _enabled_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _enabled_value?: boolean | undefined

  _visibility_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _visibility_value?: Visibility | undefined

  _key_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _key_value?: string | undefined

  _id_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _id_value?: string | undefined

  _customProperty_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
  _customPropertyMap?: Map<string, CustomProperty>

  public width(value: Length | LayoutPolicy | undefined): this {
    if (this._width_flag === AttributeUpdaterFlag.INITIAL || this._width_value !== value || !Type.of(value).isPrimitive()) {
      this._width_value = value
      this._width_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._width_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public height(value: Length | LayoutPolicy | undefined): this {
    if (this._height_flag === AttributeUpdaterFlag.INITIAL || this._height_value !== value || !Type.of(value).isPrimitive()) {
      this._height_value = value
      this._height_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._height_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public backgroundColor(value: ResourceColor | undefined): this {
    if ((this._backgroundColor_flag) == (AttributeUpdaterFlag.INITIAL) ||
      this._backgroundColor_value !== value || !Type.of(value).isPrimitive()) {
        this._backgroundColor_flag = AttributeUpdaterFlag.UPDATE
        this._backgroundColor_value = value
    } else {
        this._backgroundColor_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }


  public backgroundEffect(value: BackgroundEffectOptions | undefined): this {
    if ((this._backgroundEffect_0_flag) == (AttributeUpdaterFlag.INITIAL) ||
      this._backgroundEffect_0_0value !== value || !Type.of(value).isPrimitive()) {
        this._backgroundEffect_0_flag = AttributeUpdaterFlag.UPDATE
        this._backgroundEffect_0_0value = value
    } else {
        this._backgroundEffect_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public backgroundEffect(options: BackgroundEffectOptions | undefined, sysOptions?: SystemAdaptiveOptions): this {
    if ((this._backgroundEffect_1_flag) == (AttributeUpdaterFlag.INITIAL) ||
      !Type.of(options).isPrimitive() || !Type.of(sysOptions).isPrimitive() ||
      this._backgroundEffect_1_0value !== options || this._backgroundEffect_1_1value !== sysOptions) {
        this._backgroundEffect_1_flag = AttributeUpdaterFlag.UPDATE
        this._backgroundEffect_1_0value = options
        this._backgroundEffect_1_1value = sysOptions
    } else {
      this._backgroundEffect_1_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public foregroundEffect(value: ForegroundEffectOptions | undefined): this {
    if (((this._foregroundEffect_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._foregroundEffect_0_flag = AttributeUpdaterFlag.UPDATE
      this._foregroundEffect_0_0value = value
    } else {
      this._foregroundEffect_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  visualEffect(value: VisualEffect | undefined): this {
    if (((this._visualEffect_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._visualEffect_0_flag = AttributeUpdaterFlag.UPDATE
      this._visualEffect_0_0value = value
    } else {
      this._visualEffect_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  backgroundFilter(value: Filter | undefined): this {
    if (((this._backgroundFilter_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._backgroundFilter_0_flag = AttributeUpdaterFlag.UPDATE
      this._backgroundFilter_0_0value = value
    } else {
      this._backgroundFilter_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  foregroundFilter(value: Filter | undefined): this {
    if (((this._foregroundFilter_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
        this._foregroundFilter_0_flag = AttributeUpdaterFlag.UPDATE
        this._foregroundFilter_0_0value = value
    } else {
        this._foregroundFilter_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  compositingFilter(value: Filter | undefined): this {
    if (((this._compositingFilter_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._compositingFilter_0_flag = AttributeUpdaterFlag.UPDATE
      this._compositingFilter_0_0value = value
    } else {
      this._compositingFilter_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  opacity(value: number | Resource | undefined): this {
    if (((this._opacity_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._opacity_0_flag = AttributeUpdaterFlag.UPDATE
      this._opacity_0_0value = value
    } else {
      this._opacity_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  outline(value: OutlineOptions | undefined): this {
    if (((this._outline_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
        this._outline_0_flag = AttributeUpdaterFlag.UPDATE
        this._outline_0_0value = value
    } else {
        this._outline_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  outlineStyle(value: OutlineStyle | EdgeOutlineStyles | undefined): this {
    if (((this._outlineStyle_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._outlineStyle_0_flag = AttributeUpdaterFlag.UPDATE
      this._outlineStyle_0_0value = value
    } else {
      this._outlineStyle_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  outlineWidth(value: Dimension | EdgeOutlineWidths | undefined): this {
    if (((this._outlineWidth_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
        this._outlineWidth_0_flag = AttributeUpdaterFlag.UPDATE
        this._outlineWidth_0_0value = value
    } else {
        this._outlineWidth_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  outlineColor(value: ResourceColor | EdgeColors | LocalizedEdgeColors | undefined): this {
    if (((this._outlineColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._outlineColor_0_flag = AttributeUpdaterFlag.UPDATE
      this._outlineColor_0_0value = value
    } else {
      this._outlineColor_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  outlineRadius(value: Dimension | OutlineRadiuses | undefined): this {
    if (((this._outlineRadius_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._outlineRadius_0_flag = AttributeUpdaterFlag.UPDATE
      this._outlineRadius_0_0value = value
    } else {
      this._outlineRadius_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  foregroundColor(value: ResourceColor | ColoringStrategy | undefined): this {
    if (((this._foregroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
        this._foregroundColor_0_flag = AttributeUpdaterFlag.UPDATE
        this._foregroundColor_0_0value = value
    } else {
        this._foregroundColor_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  transition(value: TransitionEffect | undefined): this {
    if (((this._transition_1_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._transition_1_flag = AttributeUpdaterFlag.UPDATE
      this._transition_1_0value = value
    } else {
      this._transition_1_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  motionBlur(value: MotionBlurOptions | undefined): this {
    if (((this._motionBlur_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._motionBlur_0_flag = AttributeUpdaterFlag.UPDATE
      this._motionBlur_0_0value = value
    } else {
      this._motionBlur_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  brightness(value: number | undefined): this {
    if (((this._brightness_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._brightness_0_0value) !== (value))) {
      this._brightness_0_flag = AttributeUpdaterFlag.UPDATE
      this._brightness_0_0value = value
    } else {
      this._brightness_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  contrast(value: number | undefined): this {
    if (((this._contrast_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._contrast_0_0value) !== (value))) {
      this._contrast_0_flag = AttributeUpdaterFlag.UPDATE
      this._contrast_0_0value = value
    } else {
      this._contrast_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  grayscale(value: number | undefined): this {
    if (((this._grayscale_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._grayscale_0_0value) !== (value))) {
      this._grayscale_0_flag = AttributeUpdaterFlag.UPDATE
      this._grayscale_0_0value = value
    } else {
      this._grayscale_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  colorBlend(value: Color | string | Resource | undefined): this {
    if (((this._colorBlend_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._colorBlend_0_flag = AttributeUpdaterFlag.UPDATE
      this._colorBlend_0_0value = value
    } else {
      this._colorBlend_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  saturate(value: number | undefined): this {
    if (((this._saturate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._saturate_0_0value) !== (value))) {
      this._saturate_0_flag = AttributeUpdaterFlag.UPDATE
      this._saturate_0_0value = value
    } else {
      this._saturate_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  sepia(value: number | undefined): this {
    if (((this._sepia_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._sepia_0_0value) !== (value))) {
      this._sepia_0_flag = AttributeUpdaterFlag.UPDATE
      this._sepia_0_0value = value
    } else {
      this._sepia_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  invert(value: number | InvertOptions | undefined): this {
    if (((this._invert_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._invert_0_flag = AttributeUpdaterFlag.UPDATE
      this._invert_0_0value = value
    } else {
      this._invert_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  hueRotate(value: number | string | undefined): this {
    if (((this._hueRotate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._hueRotate_0_0value) !== (value))) {
      this._hueRotate_0_flag = AttributeUpdaterFlag.UPDATE
      this._hueRotate_0_0value = value
    } else {
      this._hueRotate_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  useShadowBatching(value: boolean | undefined): this {
    if (((this._useShadowBatching_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._useShadowBatching_0_0value) !== (value))) {
      this._useShadowBatching_0_flag = AttributeUpdaterFlag.UPDATE
      this._useShadowBatching_0_0value = value
    } else {
      this._useShadowBatching_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  useEffect(value: boolean | undefined): this {
    if (((this._useEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._useEffect_0_0value) !== (value))) {
      this._useEffect_0_flag = AttributeUpdaterFlag.UPDATE
      this._useEffect_0_0value = value
    } else {
      this._useEffect_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  renderGroup(value: boolean | undefined): this {
    if (((this._renderGroup_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._renderGroup_0_0value) !== (value))) {
      this._renderGroup_0_flag = AttributeUpdaterFlag.UPDATE
      this._renderGroup_0_0value = value
    } else {
      this._renderGroup_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  freeze(value: boolean | undefined): this {
    if (((this._freeze_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._freeze_0_0value) !== (value))) {
      this._freeze_0_flag = AttributeUpdaterFlag.UPDATE
      this._freeze_0_0value = value
    } else {
      this._freeze_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  translate(value: TranslateOptions | undefined): this {
    if (((this._translate_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._translate_0_flag = AttributeUpdaterFlag.UPDATE
      this._translate_0_0value = value
    } else {
      this._translate_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  scale(value: ScaleOptions | undefined): this {
    if (((this._scale_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._scale_0_flag = AttributeUpdaterFlag.UPDATE
      this._scale_0_0value = value
    } else {
      this._scale_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  rotate(value: RotateOptions | undefined): this {
    if (((this._rotate_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._rotate_0_flag = AttributeUpdaterFlag.UPDATE
      this._rotate_0_0value = value
    } else {
      this._rotate_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  transform(value: Object | undefined): this {
    if (((this._transform_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._transform_0_0value) !== (value))) {
      this._transform_0_flag = AttributeUpdaterFlag.UPDATE
      this._transform_0_0value = value
    } else {
      this._transform_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  clickEffect(value: ClickEffect | undefined): this {
    if (((this._clickEffect_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._clickEffect_0_flag = AttributeUpdaterFlag.UPDATE
      this._clickEffect_0_0value = value
    } else {
      this._clickEffect_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  linearGradient(value: LinearGradientOptions | undefined): this {
    if (((this._linearGradient_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._linearGradient_0_flag = AttributeUpdaterFlag.UPDATE
      this._linearGradient_0_0value = value
    } else {
      this._linearGradient_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  sweepGradient(value: SweepGradientOptions | undefined): this {
    if (((this._sweepGradient_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._sweepGradient_0_flag = AttributeUpdaterFlag.UPDATE
      this._sweepGradient_0_0value = value
    } else {
      this._sweepGradient_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  radialGradient(value: RadialGradientOptions | undefined): this {
    if (((this._radialGradient_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._radialGradient_0_flag = AttributeUpdaterFlag.UPDATE
      this._radialGradient_0_0value = value
    } else {
      this._radialGradient_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  motionPath(value: MotionPathOptions | undefined): this {
    if (((this._motionPath_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._motionPath_0_flag = AttributeUpdaterFlag.UPDATE
      this._motionPath_0_0value = value
    } else {
      this._motionPath_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  shadow(value: ShadowOptions | ShadowStyle | undefined): this {
    if (((this._shadow_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._shadow_0_flag = AttributeUpdaterFlag.UPDATE
      this._shadow_0_0value = value
    } else {
      this._shadow_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  clip(value: boolean | undefined): this {
    if (((this._clip_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._clip_0_0value) !== (value))) {
      this._clip_0_flag = AttributeUpdaterFlag.UPDATE
      this._clip_0_0value = value
    } else {
      this._clip_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  clipShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
    if (((this._clipShape_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._clipShape_0_flag = AttributeUpdaterFlag.UPDATE
      this._clipShape_0_0value = value
    } else {
      this._clipShape_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  mask(value: ProgressMask | undefined): this {
    if (((this._mask_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._mask_0_flag = AttributeUpdaterFlag.UPDATE
      this._mask_0_0value = value
    } else {
      this._mask_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  maskShape(value: CircleShape | EllipseShape | PathShape | RectShape | undefined): this {
    if (((this._maskShape_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._maskShape_0_flag = AttributeUpdaterFlag.UPDATE
      this._maskShape_0_0value = value
    } else {
      this._maskShape_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  sphericalEffect(value: number | undefined): this {
    if (((this._sphericalEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._sphericalEffect_0_0value) !== (value))) {
      this._sphericalEffect_0_flag = AttributeUpdaterFlag.UPDATE
      this._sphericalEffect_0_0value = value
    } else {
      this._sphericalEffect_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  lightUpEffect(value: number | undefined): this {
    if (((this._lightUpEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._lightUpEffect_0_0value) !== (value))) {
      this._lightUpEffect_0_flag = AttributeUpdaterFlag.UPDATE
      this._lightUpEffect_0_0value = value
    } else {
      this._lightUpEffect_0_flag = AttributeUpdaterFlag.SKIP
         }
         return this
       }
  pixelStretchEffect(value: PixelStretchEffectOptions | undefined): this {
    if (((this._pixelStretchEffect_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.UPDATE
      this._pixelStretchEffect_0_0value = value
    } else {
      this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  renderFit(value: RenderFit | undefined): this {
    if (((this._renderFit_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._renderFit_0_flag = AttributeUpdaterFlag.UPDATE
      this._renderFit_0_0value = value
    } else {
      this._renderFit_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  backgroundBrightness(value: BackgroundBrightnessOptions | undefined): this {
    if (((this._backgroundBrightness_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._backgroundBrightness_0_flag = AttributeUpdaterFlag.UPDATE
      this._backgroundBrightness_0_0value = value
    } else {
      this._backgroundBrightness_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  backgroundBlurStyle(style: BlurStyle | undefined, options?: BackgroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
    if (((this._backgroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
      this._backgroundBlurStyle_0_0value = style
      this._backgroundBlurStyle_0_1value = options
      this._backgroundBlurStyle_0_2value = sysOptions
    } else {
      this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  foregroundBlurStyle(style: BlurStyle | undefined, options?: ForegroundBlurStyleOptions, sysOptions?: SystemAdaptiveOptions): this {
    if (((this._foregroundBlurStyle_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.UPDATE
      this._foregroundBlurStyle_0_0value = style
      this._foregroundBlurStyle_0_1value = options
      this._foregroundBlurStyle_0_2value = sysOptions
    } else {
      this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  blur(blurRadius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
    if (((this._blur_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._blur_0_0value) !== (blurRadius))) {
      this._blur_0_flag = AttributeUpdaterFlag.UPDATE
      this._blur_0_0value = blurRadius
      this._blur_0_1value = options
      this._blur_0_2value = sysOptions
    } else {
      this._blur_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  linearGradientBlur(value: number | undefined, options: LinearGradientBlurOptions | undefined): this {
    if (((this._linearGradientBlur_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._linearGradientBlur_0_0value) !== (value))) {
      this._linearGradientBlur_0_flag = AttributeUpdaterFlag.UPDATE
      this._linearGradientBlur_0_0value = value
      this._linearGradientBlur_0_1value = options
    } else {
      this._linearGradientBlur_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  systemBarEffect(): this {
    if ((this._systemBarEffect_0_flag) == (AttributeUpdaterFlag.INITIAL)) {
      this._systemBarEffect_0_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._systemBarEffect_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  useEffect(useEffect: boolean | undefined, effectType: EffectType | undefined): this {
    if (((this._useEffect_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._useEffect_1_0value) !== (useEffect))) {
      this._useEffect_1_flag = AttributeUpdaterFlag.UPDATE
      this._useEffect_1_0value = useEffect
      this._useEffect_1_1value = effectType
    } else {
      this._useEffect_1_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  backdropBlur(radius: number | undefined, options?: BlurOptions, sysOptions?: SystemAdaptiveOptions): this {
    if (((this._backdropBlur_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._backdropBlur_0_0value) !== (radius))) {
      this._backdropBlur_0_flag = AttributeUpdaterFlag.UPDATE
      this._backdropBlur_0_0value = radius
      this._backdropBlur_0_1value = options
      this._backdropBlur_0_2value = sysOptions
    } else {
      this._backdropBlur_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  sharedTransition(id: string | undefined, options?: sharedTransitionOptions): this {
    if (((this._sharedTransition_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._sharedTransition_0_0value) !== (id))) {
      this._sharedTransition_0_flag = AttributeUpdaterFlag.UPDATE
      this._sharedTransition_0_0value = id
      this._sharedTransition_0_1value = options
    } else {
      this._sharedTransition_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  blendMode(value: BlendMode | undefined, type?: BlendApplyType): this {
    if (((this._blendMode_0_flag) == (AttributeUpdaterFlag.INITIAL))) {
      this._blendMode_0_flag = AttributeUpdaterFlag.UPDATE
      this._blendMode_0_0value = value
      this._blendMode_0_1value = type
    } else {
      this._blendMode_0_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  advancedBlendMode(effect: BlendMode | BrightnessBlender, type?: BlendApplyType): this {
    throw new Error("Not implemented")
  }
  geometryTransition(id: string | undefined, options?: GeometryTransitionOptions): this {
    if (((this._geometryTransition_1_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._geometryTransition_1_0value) !== (id))) {
      this._geometryTransition_1_flag = AttributeUpdaterFlag.UPDATE
      this._geometryTransition_1_0value = id
      this._geometryTransition_1_1value = options
    } else {
      this._geometryTransition_1_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  animation(value: AnimateParam | undefined): this {
    throw new Error("Not implemented")
  }


  public onClick(value: ((event: ClickEvent) => void) | undefined): this {
    if (this._onClick_flag === AttributeUpdaterFlag.INITIAL || this._onClick0_value !== value || !Type.of(value).isPrimitive()) {
      this._onClick0_value = value
      this._onClick_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onClick_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public size(value: SizeOptions | undefined): this {
    if (this._size_flag === AttributeUpdaterFlag.INITIAL || this._size_value !== value || !Type.of(value).isPrimitive()) {
      this._size_value = value
      this._size_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._size_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public constraintSize(value: ConstraintSizeOptions | undefined): this {
    if (this._constraintSize_flag === AttributeUpdaterFlag.INITIAL || this._constraintSize_value !== value || !Type.of(value).isPrimitive()) {
      this._constraintSize_value = value
      this._constraintSize_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._constraintSize_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public layoutWeight(value: number | string | undefined): this {
    if (this._layoutWeight_flag === AttributeUpdaterFlag.INITIAL || this._layoutWeight_value !== value || !Type.of(value).isPrimitive()) {
      this._layoutWeight_value = value
      this._layoutWeight_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._layoutWeight_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public padding(value: Padding | Length | LocalizedPadding | undefined): this {
    if (this._padding_flag === AttributeUpdaterFlag.INITIAL || this._padding_value !== value || !Type.of(value).isPrimitive()) {
      this._padding_value = value
      this._padding_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._padding_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public safeAreaPadding(value: Padding | LengthMetrics | LocalizedPadding | undefined): this {
    if (this._safeAreaPadding_flag === AttributeUpdaterFlag.INITIAL || this._safeAreaPadding_value !== value || !Type.of(value).isPrimitive()) {
      this._safeAreaPadding_value = value
      this._safeAreaPadding_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._safeAreaPadding_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public margin(value: Padding | Length | LocalizedPadding | undefined): this {
    if (this._margin_flag === AttributeUpdaterFlag.INITIAL || this._margin_value !== value || !Type.of(value).isPrimitive()) {
      this._margin_value = value
      this._margin_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._margin_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public flexGrow(value: number | undefined): this {
    if (this._flexGrow_flag === AttributeUpdaterFlag.INITIAL || this._flexGrow_value !== value || !Type.of(value).isPrimitive()) {
      this._flexGrow_value = value
      this._flexGrow_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._flexGrow_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public flexShrink(value: number | undefined): this {
    if (this._flexShrink_flag === AttributeUpdaterFlag.INITIAL || this._flexShrink_value !== value || !Type.of(value).isPrimitive()) {
      this._flexShrink_value = value
      this._flexShrink_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._flexShrink_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public flexBasis(value: number | string | undefined): this {
    if (this._flexBasis_flag === AttributeUpdaterFlag.INITIAL || this._flexBasis_value !== value || !Type.of(value).isPrimitive()) {
      this._flexBasis_value = value
      this._flexBasis_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._flexBasis_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public alignSelf(value: ItemAlign | undefined): this {
    if (this._alignSelf_flag === AttributeUpdaterFlag.INITIAL || this._alignSelf_value !== value) {
      this._alignSelf_value = value
      this._alignSelf_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._alignSelf_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public align(value: Alignment | undefined): this {
    if (this._align_flag === AttributeUpdaterFlag.INITIAL || this._align_value !== value) {
      this._align_value = value
      this._align_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._align_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public position(value: Position | Edges | LocalizedEdges | undefined): this {
    if (this._position_flag === AttributeUpdaterFlag.INITIAL || this._position_value !== value || !Type.of(value).isPrimitive()) {
      this._position_value = value
      this._position_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._position_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public markAnchor(value: Position | LocalizedPosition | undefined): this {
    if (this._markAnchor_flag === AttributeUpdaterFlag.INITIAL || this._markAnchor_value !== value || !Type.of(value).isPrimitive()) {
      this._markAnchor_value = value
      this._markAnchor_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._markAnchor_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public offset(value: Position | Edges | LocalizedEdges | undefined): this {
    if (this._offset_flag === AttributeUpdaterFlag.INITIAL || this._offset_value !== value || !Type.of(value).isPrimitive()) {
      this._offset_value = value
      this._offset_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._offset_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public alignRules(value: AlignRuleOption | undefined | LocalizedAlignRuleOptions | undefined): this {
    if (this._alignRules_flag === AttributeUpdaterFlag.INITIAL || this._alignRules_value !== value || !Type.of(value).isPrimitive()) {
      this._alignRules_value = value
      this._alignRules_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._alignRules_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public chainMode(direction: Axis | undefined, style: ChainStyle | undefined): this {
    if (this._chainMode_flag === AttributeUpdaterFlag.INITIAL || this._chainMode_direction !== direction ||
        this._chainMode_style !== style) {
      this._chainMode_direction = direction
      this._chainMode_style = style
      this._chainMode_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._chainMode_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public aspectRatio(value: number | undefined): this {
    if (this._aspectRatio_flag === AttributeUpdaterFlag.INITIAL || this._aspectRatio_value !== value || !Type.of(value).isPrimitive()) {
      this._aspectRatio_value = value
      this._aspectRatio_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._aspectRatio_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public expandSafeArea(types?: Array<SafeAreaType> | undefined, edges?: Array<SafeAreaEdge> | undefined): this {
    if (this._expandSafeArea_flag === AttributeUpdaterFlag.INITIAL || this._expandSafeArea_types !== types ||
      this._expandSafeArea_edges !== edges || !Type.of(types).isPrimitive() || !Type.of(edges).isPrimitive()) {
      this._expandSafeArea_types = types
      this._expandSafeArea_edges = edges
      this._expandSafeArea_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._expandSafeArea_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public zIndex(value: number | undefined): this {
    if (this._zIndex_flag === AttributeUpdaterFlag.INITIAL || this._zIndex0_value !== value || !Type.of(value).isPrimitive()) {
      this._zIndex0_value = value
      this._zIndex_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._zIndex_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public backgroundImage(src: ResourceStr | PixelMap | undefined, repeat?: ImageRepeat | undefined): this {
    if (this._backgroundImage_flag === AttributeUpdaterFlag.INITIAL || this._backgroundImage_src !== src || this._backgroundImage_repeat !== repeat || runtimeType(src) === RuntimeType.OBJECT) {
      this._backgroundImage_src = src
      this._backgroundImage_repeat = repeat
      this._backgroundImage_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._backgroundImage_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public backgroundImageSize(value: SizeOptions | ImageSize | undefined): this {
    if (this._backgroundImageSize_flag === AttributeUpdaterFlag.INITIAL || this._backgroundImageSize_value !== value || !Type.of(value).isPrimitive()) {
      this._backgroundImageSize_value = value
      this._backgroundImageSize_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._backgroundImageSize_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public backgroundImagePosition(value: Position | Alignment | undefined): this {
    if (this._backgroundImagePosition_flag === AttributeUpdaterFlag.INITIAL || this._backgroundImagePosition_value !== value || !Type.of(value).isPrimitive()) {
      this._backgroundImagePosition_value = value
      this._backgroundImagePosition_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._backgroundImagePosition_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public backgroundImageResizable(value: ResizableOptions | undefined): this {
    if (this._backgroundImageResizable_flag === AttributeUpdaterFlag.INITIAL || this._backgroundImageResizable_value !== value || !Type.of(value).isPrimitive()) {
      this._backgroundImageResizable_value = value
      this._backgroundImageResizable_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._backgroundImageResizable_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onHover(value: ((isHover: boolean, event: HoverEvent) => void) | undefined): this {
    if (this._onHover_flag === AttributeUpdaterFlag.INITIAL || this._onHover_value !== value || !Type.of(value).isPrimitive()) {
      this._onHover_value = value
      this._onHover_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onHover_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onHoverMove(value: ((parameter: HoverEvent) => void) | undefined): this {
    if (this._onHoverMove_flag === AttributeUpdaterFlag.INITIAL || this._onHoverMove_value !== value || !Type.of(value).isPrimitive()) {
      this._onHoverMove_value = value
      this._onHoverMove_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onHoverMove_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onMouse(value: ((event: MouseEvent) => void) | undefined): this {
    if (this._onMouse_flag === AttributeUpdaterFlag.INITIAL || this._onMouse_value !== value || !Type.of(value).isPrimitive()) {
      this._onMouse_value = value
      this._onMouse_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onMouse_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onTouch(value: ((event: TouchEvent) => void) | undefined): this {
    if (this._onTouch_flag === AttributeUpdaterFlag.INITIAL || this._onTouch_value !== value || !Type.of(value).isPrimitive()) {
      this._onTouch_value = value
      this._onTouch_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onTouch_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onFocusAxisEvent(value: ((parameter: FocusAxisEvent) => void) | undefined): this {
    if (this._onFocusAxisEvent_flag === AttributeUpdaterFlag.INITIAL || this._onFocusAxisEvent_value !== value || !Type.of(value).isPrimitive()) {
      this._onFocusAxisEvent_value = value
      this._onFocusAxisEvent_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onFocusAxisEvent_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onAxisEvent(value: ((parameter: AxisEvent) => void) | undefined): this {
    if (this._onAxisEvent_flag === AttributeUpdaterFlag.INITIAL || this._onAxisEvent_value !== value || !Type.of(value).isPrimitive()) {
      this._onAxisEvent_value = value
      this._onAxisEvent_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onAxisEvent_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onKeyEvent(value: ((event: KeyEvent) => boolean) | undefined): this {
    if (this._onKeyEvent_flag === AttributeUpdaterFlag.INITIAL || this._onKeyEvent1_value !== value || !Type.of(value).isPrimitive()) {
      this._onKeyEvent1_value = value
      this._onKeyEvent_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onKeyEvent_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onKeyPreIme(value: ((event: KeyEvent) => boolean) | undefined): this {
    if (this._onKeyPreIme_flag === AttributeUpdaterFlag.INITIAL || this._onKeyPreIme_value !== value || !Type.of(value).isPrimitive()) {
      this._onKeyPreIme_value = value
      this._onKeyPreIme_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onKeyPreIme_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onKeyEventDispatch(value: ((event: KeyEvent) => boolean) | undefined): this {
    if (this._onKeyEventDispatch_flag === AttributeUpdaterFlag.INITIAL || this._onKeyEventDispatch_value !== value || !Type.of(value).isPrimitive()) {
      this._onKeyEventDispatch_value = value
      this._onKeyEventDispatch_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onKeyEventDispatch_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public keyboardShortcut(value: string | FunctionKey | undefined, keys: Array<ModifierKey> | undefined, action?: (() => void)): this {
    if (this._keyboardShortcut_flag === AttributeUpdaterFlag.INITIAL || this._keyboardShortcut_value !== value ||
      this._keyboardShortcut_keys !== keys || this._keyboardShortcut_action !== action ||
      !Type.of(value).isPrimitive()) {
      this._keyboardShortcut_value = value
      this._keyboardShortcut_keys = keys
      this._keyboardShortcut_action = action
      this._keyboardShortcut_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._keyboardShortcut_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public focusable(value: boolean | undefined): this {
    if (this._focusable_flag === AttributeUpdaterFlag.INITIAL || this._focusable_value !== value || !Type.of(value).isPrimitive()) {
      this._focusable_value = value
      this._focusable_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._focusable_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public nextFocus(value: FocusMovement | undefined): this {
    if (this._nextFocus_flag === AttributeUpdaterFlag.INITIAL || this._nextFocus_value !== value || !Type.of(value).isPrimitive()) {
      this._nextFocus_value = value
      this._nextFocus_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._nextFocus_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public tabIndex(value: number | undefined): this {
    if (this._tabIndex_flag === AttributeUpdaterFlag.INITIAL || this._tabIndex_value !== value || !Type.of(value).isPrimitive()) {
      this._tabIndex_value = value
      this._tabIndex_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._tabIndex_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public defaultFocus(value: boolean | undefined): this {
    if (this._defaultFocus_flag === AttributeUpdaterFlag.INITIAL || this._defaultFocus_value !== value || !Type.of(value).isPrimitive()) {
      this._defaultFocus_value = value
      this._defaultFocus_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._defaultFocus_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public groupDefaultFocus(value: boolean | undefined): this {
    if (this._groupDefaultFocus_flag === AttributeUpdaterFlag.INITIAL || this._groupDefaultFocus_value !== value || !Type.of(value).isPrimitive()) {
      this._groupDefaultFocus_value = value
      this._groupDefaultFocus_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._groupDefaultFocus_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public focusOnTouch(value: boolean | undefined): this {
    if (this._focusOnTouch_flag === AttributeUpdaterFlag.INITIAL || this._focusOnTouch_value !== value || !Type.of(value).isPrimitive()) {
      this._focusOnTouch_value = value
      this._focusOnTouch_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._focusOnTouch_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public focusBox(value: FocusBoxStyle | undefined): this {
    if (this._focusBox_flag === AttributeUpdaterFlag.INITIAL || this._focusBox_value !== value || !Type.of(value).isPrimitive()) {
      this._focusBox_value = value
      this._focusBox_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._focusBox_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public focusScopeId(id: string | undefined, isGroup?: boolean, arrowStepOut?: boolean): this {
    if (this._focusScopeId_flag === AttributeUpdaterFlag.INITIAL || this._focusScopeId_id !== id || this._focusScopeId_isGroup !== isGroup || this._focusScopeId_arrowStepOut !== arrowStepOut || !Type.of(id).isPrimitive()) {
      this._focusScopeId_id = id
      this._focusScopeId_isGroup = isGroup
      this._focusScopeId_arrowStepOut = arrowStepOut
      this._focusScopeId_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._focusScopeId_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public focusScopePriority(scopeId: string | undefined, priority?: FocusPriority): this {
    if (this._focusScopePriority_flag === AttributeUpdaterFlag.INITIAL || this._focusScopePriority_scopeId !== scopeId || this._focusScopePriority_priority !== priority || !Type.of(scopeId).isPrimitive()) {
      this._focusScopePriority_scopeId = scopeId
      this._focusScopePriority_priority = priority
      this._focusScopePriority_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._focusScopePriority_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public tabStop(value: boolean | undefined): this {
    if (this._tabStop_flag === AttributeUpdaterFlag.INITIAL || this._tabStop_value !== value || !Type.of(value).isPrimitive()) {
      this._tabStop_value = value
      this._tabStop_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._tabStop_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onFocus(value: (() => void) | undefined): this {
    if (this._onFocus_flag === AttributeUpdaterFlag.INITIAL || this._onFocus_value !== value || !Type.of(value).isPrimitive()) {
      this._onFocus_value = value
      this._onFocus_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onFocus_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onBlur(value: (() => void) | undefined): this {
    if (this._onBlur_flag === AttributeUpdaterFlag.INITIAL || this._onBlur_value !== value || !Type.of(value).isPrimitive()) {
      this._onBlur_value = value
      this._onBlur_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onBlur_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onAppear(value: (() => void) | undefined): this {
    if (this._onAppear_flag === AttributeUpdaterFlag.INITIAL || this._onAppear_value !== value || !Type.of(value).isPrimitive()) {
      this._onAppear_value = value
      this._onAppear_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onAppear_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onDisAppear(value: (() => void) | undefined): this {
    if (this._onDisAppear_flag === AttributeUpdaterFlag.INITIAL || this._onDisAppear_value !== value || !Type.of(value).isPrimitive()) {
      this._onDisAppear_value = value
      this._onDisAppear_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onDisAppear_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onAttach(value: (() => void) | undefined): this {
    if (this._onAttach_flag === AttributeUpdaterFlag.INITIAL || this._onAttach_value !== value || !Type.of(value).isPrimitive()) {
      this._onAttach_value = value
      this._onAttach_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onAttach_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onDetach(value: (() => void) | undefined): this {
    if (this._onDetach_flag === AttributeUpdaterFlag.INITIAL || this._onDetach_value !== value || !Type.of(value).isPrimitive()) {
      this._onDetach_value = value
      this._onDetach_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onDetach_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onAreaChange(value: ((oldValue: Area, newValue: Area) => void) | undefined): this {
    if (this._onAreaChange_flag === AttributeUpdaterFlag.INITIAL || this._onAreaChange_value !== value || !Type.of(value).isPrimitive()) {
      this._onAreaChange_value = value
      this._onAreaChange_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onAreaChange_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onSizeChange(value: SizeChangeCallback | undefined): this {
    if (this._onSizeChange_flag === AttributeUpdaterFlag.INITIAL || this._onSizeChange_value !== value || !Type.of(value).isPrimitive()) {
      this._onSizeChange_value = value
      this._onSizeChange_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onSizeChange_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onGestureJudgeBegin(value: ((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined): this {
    if (this._onGestureJudgeBegin_flag === AttributeUpdaterFlag.INITIAL || this._onGestureJudgeBegin_value !== value || !Type.of(value).isPrimitive()) {
      this._onGestureJudgeBegin_value = value
      this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public shouldBuiltInRecognizerParallelWith(value: ShouldBuiltInRecognizerParallelWithCallback | undefined): this {
    if (this._shouldBuiltInRecognizerParallelWith_flag === AttributeUpdaterFlag.INITIAL || this._shouldBuiltInRecognizerParallelWith_value !== value || !Type.of(value).isPrimitive()) {
      this._shouldBuiltInRecognizerParallelWith_value = value
      this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public onGestureRecognizerJudgeBegin(callback_: GestureRecognizerJudgeBeginCallback | undefined, exposeInnerGesture?: boolean): this {
    if (this._onGestureRecognizerJudgeBegin_flag === AttributeUpdaterFlag.INITIAL || this._onGestureRecognizerJudgeBegin_callback !== callback_ || this._onGestureRecognizerJudgeBegin_exposeInnerGesture !== exposeInnerGesture || !Type.of(callback_).isPrimitive()) {
      this._onGestureRecognizerJudgeBegin_callback = callback_
      this._onGestureRecognizerJudgeBegin_exposeInnerGesture = exposeInnerGesture
      this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public responseRegion(value: Array<Rectangle> | Rectangle | undefined): this {
    if (this._responseRegion_flag === AttributeUpdaterFlag.INITIAL || this._responseRegion_value !== value || !Type.of(value).isPrimitive()) {
      this._responseRegion_value = value
      this._responseRegion_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._responseRegion_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public hitTestBehavior(value: HitTestMode | undefined): this {
    if (this._hitTestBehavior_flag === AttributeUpdaterFlag.INITIAL || this._hitTestBehavior_value !== value) {
      this._hitTestBehavior_value = value
      this._hitTestBehavior_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._hitTestBehavior_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public monopolizeEvents(value: boolean | undefined): this {
    if (this._monopolizeEvents_flag === AttributeUpdaterFlag.INITIAL || this._monopolizeEvents_value !== value) {
      this._monopolizeEvents_value = value
      this._monopolizeEvents_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._monopolizeEvents_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public restoreId(value: number | undefined): this {
    if (this._restoreId_flag === AttributeUpdaterFlag.INITIAL || this._restoreId_value !== value || !Type.of(value).isPrimitive()) {
      this._restoreId_value = value
      this._restoreId_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._restoreId_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public hoverEffect(value: HoverEffect | undefined): this {
    if (this._hoverEffect_flag === AttributeUpdaterFlag.INITIAL || this._hoverEffect_value !== value) {
      this._hoverEffect_value = value
      this._hoverEffect_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._hoverEffect_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public enabled(value: boolean | undefined): this {
    if (this._enabled_flag === AttributeUpdaterFlag.INITIAL || this._enabled_value !== value) {
      this._enabled_value = value
      this._enabled_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._enabled_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public visibility(value: Visibility | undefined): this {
    if (this._visibility_flag === AttributeUpdaterFlag.INITIAL || this._visibility_value !== value) {
      this._visibility_value = value
      this._visibility_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._visibility_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public key(value: string | undefined): this {
    if (this._key_flag === AttributeUpdaterFlag.INITIAL || this._key_value !== value || !Type.of(value).isPrimitive()) {
      this._key_value = value
      this._key_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._key_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public id(value: string | undefined): this {
    if (this._id_flag === AttributeUpdaterFlag.INITIAL || this._id_value !== value || !Type.of(value).isPrimitive()) {
      this._id_value = value
      this._id_flag = AttributeUpdaterFlag.UPDATE
    } else {
      this._id_flag = AttributeUpdaterFlag.SKIP
    }
    return this
  }
  public customProperty(name: string, value: CustomProperty): this {
    if (this._customPropertyMap === undefined) {
      this._customPropertyMap = new Map<string, CustomProperty>();
    }
    this._customPropertyMap!.set(name, value);
    this._customProperty_flag = AttributeUpdaterFlag.UPDATE;
    return this;
  }
  applyModifierPatch(node: PeerNode): void {
    const peerNode: ArkCommonMethodPeer = node as ArkCommonMethodPeer
    if (this._width_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._width_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.width1Attribute((this._width_value as Length | LayoutPolicy | undefined))
          this._width_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._width_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._width_flag = AttributeUpdaterFlag.INITIAL
          peerNode.width1Attribute(undefined)
        }
      }
    }
    if (this._height_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._height_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.height1Attribute((this._height_value as Length | LayoutPolicy | undefined))
          this._height_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._height_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._height_flag = AttributeUpdaterFlag.INITIAL
          peerNode.height1Attribute(undefined)
        }
      }
    }
    if (this.  _backgroundColor_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this.  _backgroundColor_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundColor0Attribute((this._backgroundColor_value as ResourceColor | undefined))
          this.  _backgroundColor_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this.  _backgroundColor_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this.  _backgroundColor_flag = AttributeUpdaterFlag.INITIAL
          peerNode.backgroundColor0Attribute(undefined)
        }
      }
    }

    if (this._backgroundEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundEffect0Attribute((this._backgroundEffect_0_0value as BackgroundEffectOptions | undefined));
          this._backgroundEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
            }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
            }
        default: {
          this._backgroundEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.backgroundEffect0Attribute((undefined as BackgroundEffectOptions | undefined));
        }
      }
    }
    if (this._foregroundEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._foregroundEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.foregroundEffectAttribute((this._foregroundEffect_0_0value as ForegroundEffectOptions | undefined));
          this._foregroundEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._foregroundEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._foregroundEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.foregroundEffectAttribute((undefined as ForegroundEffectOptions | undefined));
        }
      }
    }
    if (this._visualEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._visualEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.visualEffectAttribute((this._visualEffect_0_0value as VisualEffect | undefined));
          this._visualEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._visualEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._visualEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.visualEffectAttribute((undefined as VisualEffect | undefined));
        }
      }
    }
    if (this._backgroundFilter_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundFilter_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundFilterAttribute((this._backgroundFilter_0_0value as Filter | undefined));
          this._backgroundFilter_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundFilter_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._backgroundFilter_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.backgroundFilterAttribute((undefined as Filter | undefined));
        }
      }
    }
    if (this._foregroundFilter_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._foregroundFilter_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.foregroundFilterAttribute((this._foregroundFilter_0_0value as Filter | undefined));
          this._foregroundFilter_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._foregroundFilter_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._foregroundFilter_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.foregroundFilterAttribute((undefined as Filter | undefined));
        }
      }
    }
    if (this._compositingFilter_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._compositingFilter_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.compositingFilterAttribute((this._compositingFilter_0_0value as Filter | undefined));
          this._compositingFilter_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._compositingFilter_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._compositingFilter_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.compositingFilterAttribute((undefined as Filter | undefined));
        }
      }
    }
    if (this._opacity_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._opacity_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.opacity0Attribute((this._opacity_0_0value as number | Resource | undefined));
          this._opacity_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._opacity_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._opacity_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.opacity0Attribute((undefined as number | Resource | undefined));
        }
      }
    }
    if (this._outline_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._outline_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.outline0Attribute((this._outline_0_0value as OutlineOptions | undefined));
          this._outline_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._outline_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._outline_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.outline0Attribute((undefined as OutlineOptions | undefined));
        }
      }
    }
    if (this._outlineStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._outlineStyle_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.outlineStyle0Attribute((this._outlineStyle_0_0value as OutlineStyle | EdgeOutlineStyles | undefined));
          this._outlineStyle_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._outlineStyle_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._outlineStyle_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.outlineStyle0Attribute((undefined as OutlineStyle | EdgeOutlineStyles | undefined));
        }
      }
    }
    if (this._outlineWidth_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._outlineWidth_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.outlineWidth0Attribute((this._outlineWidth_0_0value as Dimension | EdgeOutlineWidths | undefined));
          this._outlineWidth_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._outlineWidth_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._outlineWidth_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.outlineWidth0Attribute((undefined as Dimension | EdgeOutlineWidths | undefined));
        }
      }
    }
    if (this._outlineColor_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._outlineColor_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.outlineColor0Attribute((this._outlineColor_0_0value as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
          this._outlineColor_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._outlineColor_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._outlineColor_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.outlineColor0Attribute((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
        }
      }
    }
    if (this._outlineRadius_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._outlineRadius_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.outlineRadius0Attribute((this._outlineRadius_0_0value as Dimension | OutlineRadiuses | undefined));
          this._outlineRadius_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._outlineRadius_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._outlineRadius_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.outlineRadius0Attribute((undefined as Dimension | OutlineRadiuses | undefined));
        }
      }
    }
    if (this._foregroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._foregroundColor_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.foregroundColor0Attribute((this._foregroundColor_0_0value as ResourceColor | ColoringStrategy | undefined));
          this._foregroundColor_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._foregroundColor_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._foregroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.foregroundColor0Attribute((undefined as ResourceColor | ColoringStrategy | undefined));
        }
      }
    }
    if (this._animation_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._animation_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.animationAttribute((this._animation_0_0value as AnimateParam | undefined));
          this._animation_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._animation_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._animation_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.animationAttribute((undefined as AnimateParam | undefined));
        }
      }
    }
    if (this._transition_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._transition_1_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.transition0Attribute((this._transition_1_0value as TransitionEffect | undefined));
          this._transition_1_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._transition_1_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._transition_1_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.transition0Attribute((undefined as TransitionEffect | undefined));
        }
      }
    }
    if (this._motionBlur_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._motionBlur_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.motionBlur0Attribute((this._motionBlur_0_0value as MotionBlurOptions | undefined));
          this._motionBlur_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._motionBlur_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._motionBlur_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.motionBlur0Attribute((undefined as MotionBlurOptions | undefined));
        }
      }
    }
    if (this._brightness_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._brightness_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.brightness0Attribute((this._brightness_0_0value as number | undefined));
          this._brightness_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._brightness_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._brightness_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.brightness0Attribute((undefined as number | undefined));
        }
      }
    }
    if (this._contrast_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._contrast_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.contrast0Attribute((this._contrast_0_0value as number | undefined));
          this._contrast_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._contrast_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._contrast_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.contrast0Attribute((undefined as number | undefined));
        }
      }
    }
    if (this._grayscale_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._grayscale_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.grayscale0Attribute((this._grayscale_0_0value as number | undefined));
          this._grayscale_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._grayscale_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._grayscale_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.grayscale0Attribute((undefined as number | undefined));
        }
      }
    }
    if (this._colorBlend_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._colorBlend_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.colorBlend0Attribute((this._colorBlend_0_0value as Color | string | Resource | undefined));
          this._colorBlend_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._colorBlend_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._colorBlend_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.colorBlend0Attribute((undefined as Color | string | Resource | undefined));
        }
      }
    }
    if (this._saturate_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._saturate_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.saturate0Attribute((this._saturate_0_0value as number | undefined));
          this._saturate_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._saturate_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._saturate_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.saturate0Attribute((undefined as number | undefined));
        }
      }
    }
    if (this._sepia_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._sepia_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.sepia0Attribute((this._sepia_0_0value as number | undefined));
          this._sepia_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._sepia_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._sepia_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.sepia0Attribute((undefined as number | undefined));
        }
      }
    }
    if (this._invert_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._invert_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.invert0Attribute((this._invert_0_0value as number | InvertOptions | undefined));
          this._invert_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._invert_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._invert_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.invert0Attribute((undefined as number | InvertOptions | undefined));
        }
      }
    }
    if (this._hueRotate_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._hueRotate_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.hueRotate0Attribute((this._hueRotate_0_0value as number | string | undefined));
          this._hueRotate_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._hueRotate_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._hueRotate_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.hueRotate0Attribute((undefined as number | string | undefined));
        }
      }
    }
    if (this._useShadowBatching_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._useShadowBatching_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.useShadowBatching0Attribute((this._useShadowBatching_0_0value as boolean | undefined));
          this._useShadowBatching_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._useShadowBatching_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._useShadowBatching_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.useShadowBatching0Attribute((undefined as boolean | undefined));
        }
      }
    }
    if (this._useEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._useEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.useEffect0Attribute((this._useEffect_0_0value as boolean | undefined));
          this._useEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._useEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._useEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.useEffect0Attribute((undefined as boolean | undefined));
        }
      }
    }
    if (this._renderGroup_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._renderGroup_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.renderGroup0Attribute((this._renderGroup_0_0value as boolean | undefined));
          this._renderGroup_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._renderGroup_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._renderGroup_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.renderGroup0Attribute((undefined as boolean | undefined));
        }
      }
    }
    if (this._freeze_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._freeze_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.freeze0Attribute((this._freeze_0_0value as boolean | undefined));
          this._freeze_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._freeze_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._freeze_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.freeze0Attribute((undefined as boolean | undefined));
        }
      }
    }
    if (this._translate_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._translate_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.translate0Attribute((this._translate_0_0value as TranslateOptions | undefined));
          this._translate_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._translate_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._translate_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.translate0Attribute((undefined as TranslateOptions | undefined));
        }
      }
    }
    if (this._scale_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._scale_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.scale0Attribute((this._scale_0_0value as ScaleOptions | undefined));
          this._scale_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._scale_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._scale_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.scale0Attribute((undefined as ScaleOptions | undefined));
        }
      }
    }
    if (this._rotate_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._rotate_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.rotate0Attribute((this._rotate_0_0value as RotateOptions | undefined));
          this._rotate_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._rotate_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._rotate_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.rotate0Attribute((undefined as RotateOptions | undefined));
        }
      }
    }
    if (this._transform_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._transform_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.transform0Attribute((this._transform_0_0value as Object | undefined));
          this._transform_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._transform_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._transform_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.transform0Attribute((undefined as Object | undefined));
        }
      }
    }
    if (this._clickEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._clickEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.clickEffect0Attribute((this._clickEffect_0_0value as ClickEffect | undefined));
          this._clickEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._clickEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._clickEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.clickEffect0Attribute((undefined as ClickEffect | undefined));
        }
      }
    }
    if (this._linearGradient_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._linearGradient_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.linearGradient0Attribute((this._linearGradient_0_0value as LinearGradientOptions | undefined));
          this._linearGradient_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._linearGradient_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._linearGradient_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.linearGradient0Attribute((undefined as LinearGradientOptions | undefined));
        }
      }
    }
    if (this._sweepGradient_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._sweepGradient_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.sweepGradient0Attribute((this._sweepGradient_0_0value as SweepGradientOptions | undefined));
          this._sweepGradient_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._sweepGradient_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._sweepGradient_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.sweepGradient0Attribute((undefined as SweepGradientOptions | undefined));
        }
      }
    }
    if (this._radialGradient_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._radialGradient_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.radialGradient0Attribute((this._radialGradient_0_0value as RadialGradientOptions | undefined));
          this._radialGradient_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._radialGradient_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._radialGradient_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.radialGradient0Attribute((undefined as RadialGradientOptions | undefined));
        }
      }
    }
    if (this._motionPath_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._motionPath_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.motionPathAttribute((this._motionPath_0_0value as MotionPathOptions | undefined));
          this._motionPath_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._motionPath_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._motionPath_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.motionPathAttribute((undefined as MotionPathOptions | undefined));
        }
      }
    }
    if (this._shadow_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._shadow_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.shadow0Attribute((this._shadow_0_0value as ShadowOptions | ShadowStyle | undefined));
          this._shadow_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._shadow_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._shadow_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.shadow0Attribute((undefined as ShadowOptions | ShadowStyle | undefined));
        }
      }
    }
    if (this._clip_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._clip_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.clip0Attribute((this._clip_0_0value as boolean | undefined));
          this._clip_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._clip_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._clip_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.clip0Attribute((undefined as boolean | undefined));
        }
      }
    }
    if (this._clipShape_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._clipShape_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.clipShape0Attribute((this._clipShape_0_0value as CircleShape | EllipseShape | PathShape | RectShape | undefined));
          this._clipShape_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._clipShape_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._clipShape_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.clipShape0Attribute((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
        }
      }
    }
    if (this._mask_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._mask_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.mask0Attribute((this._mask_0_0value as ProgressMask | undefined));
          this._mask_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._mask_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._mask_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.mask0Attribute((undefined as ProgressMask | undefined));
        }
      }
    }
    if (this._maskShape_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._maskShape_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.maskShape0Attribute((this._maskShape_0_0value as CircleShape | EllipseShape | PathShape | RectShape | undefined));
          this._maskShape_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._maskShape_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._maskShape_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.maskShape0Attribute((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
        }
      }
    }
    if (this._sphericalEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._sphericalEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.sphericalEffect0Attribute((this._sphericalEffect_0_0value as number | undefined));
          this._sphericalEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._sphericalEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._sphericalEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.sphericalEffect0Attribute((undefined as number | undefined));
        }
      }
    }
    if (this._lightUpEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._lightUpEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.lightUpEffect0Attribute((this._lightUpEffect_0_0value as number | undefined));
          this._lightUpEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._lightUpEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._lightUpEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.lightUpEffect0Attribute((undefined as number | undefined));
        }
      }
    }
    if (this._pixelStretchEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._pixelStretchEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.pixelStretchEffect0Attribute((this._pixelStretchEffect_0_0value as PixelStretchEffectOptions | undefined));
          this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._pixelStretchEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.pixelStretchEffect0Attribute((undefined as PixelStretchEffectOptions | undefined));
        }
      }
    }
    if (this._renderFit_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._renderFit_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.renderFit0Attribute((this._renderFit_0_0value as RenderFit | undefined));
          this._renderFit_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._renderFit_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._renderFit_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.renderFit0Attribute((undefined as RenderFit | undefined));
        }
      }
    }
    if (this._backgroundBrightness_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundBrightness_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundBrightness0Attribute((this._backgroundBrightness_0_0value as BackgroundBrightnessOptions | undefined));
          this._backgroundBrightness_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundBrightness_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._backgroundBrightness_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.backgroundBrightness0Attribute((undefined as BackgroundBrightnessOptions | undefined));
        }
      }
    }
    if (this._backgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundBlurStyle_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundBlurStyle1Attribute((this._backgroundBlurStyle_0_0value as BlurStyle | undefined), (this._backgroundBlurStyle_0_1value as BackgroundBlurStyleOptions | undefined), (this._backgroundBlurStyle_0_2value as SystemAdaptiveOptions | undefined));
          this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._backgroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.backgroundBlurStyle1Attribute((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (this._backgroundEffect_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundEffect_1_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundEffect1Attribute((this._backgroundEffect_1_0value as BackgroundEffectOptions | undefined), (this._backgroundEffect_1_1value as SystemAdaptiveOptions | undefined));
          this._backgroundEffect_1_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundEffect_1_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._backgroundEffect_1_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.backgroundEffect1Attribute((undefined as BackgroundEffectOptions | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (this._foregroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._foregroundBlurStyle_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.foregroundBlurStyle1Attribute((this._foregroundBlurStyle_0_0value as BlurStyle | undefined), (this._foregroundBlurStyle_0_1value as ForegroundBlurStyleOptions | undefined), (this._foregroundBlurStyle_0_2value as SystemAdaptiveOptions | undefined));
          this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._foregroundBlurStyle_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.foregroundBlurStyle1Attribute((undefined as BlurStyle | undefined), (undefined as ForegroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (this._blur_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._blur_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.blur1Attribute((this._blur_0_0value as number | undefined), (this._blur_0_1value as BlurOptions | undefined), (this._blur_0_2value as SystemAdaptiveOptions | undefined));
          this._blur_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._blur_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._blur_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.blur1Attribute((undefined as number | undefined), (undefined as BlurOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (this._linearGradientBlur_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._linearGradientBlur_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.linearGradientBlur0Attribute((this._linearGradientBlur_0_0value as number | undefined), (this._linearGradientBlur_0_1value as LinearGradientBlurOptions | undefined));
          this._linearGradientBlur_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._linearGradientBlur_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._linearGradientBlur_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.linearGradientBlur0Attribute((undefined as number | undefined), (undefined as LinearGradientBlurOptions | undefined));
        }
      }
    }
    if (this._systemBarEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._systemBarEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.systemBarEffectAttribute();
          this._systemBarEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._systemBarEffect_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._systemBarEffect_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.systemBarEffectAttribute();
        }
      }
    }
    if (this._useEffect_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._useEffect_1_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.useEffect1Attribute((this._useEffect_1_0value as boolean | undefined), (this._useEffect_1_1value as EffectType | undefined));
          this._useEffect_1_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._useEffect_1_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._useEffect_1_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.useEffect1Attribute((undefined as boolean | undefined), (undefined as EffectType | undefined));
        }
      }
    }
    if (this._backdropBlur_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backdropBlur_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backdropBlur1Attribute((this._backdropBlur_0_0value as number | undefined), (this._backdropBlur_0_1value as BlurOptions | undefined), (this._backdropBlur_0_2value as SystemAdaptiveOptions | undefined));
          this._backdropBlur_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backdropBlur_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._backdropBlur_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.backdropBlur1Attribute((undefined as number | undefined), (undefined as BlurOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (this._sharedTransition_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._sharedTransition_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.sharedTransitionAttribute((this._sharedTransition_0_0value as string | undefined), (this._sharedTransition_0_1value as sharedTransitionOptions | undefined));
          this._sharedTransition_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._sharedTransition_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._sharedTransition_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.sharedTransitionAttribute((undefined as string | undefined), (undefined as sharedTransitionOptions | undefined | undefined));
        }
      }
    }
    if (this._blendMode_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._blendMode_0_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.blendMode1Attribute((this._blendMode_0_0value as BlendMode | undefined), (this._blendMode_0_1value as BlendApplyType | undefined));
          this._blendMode_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._blendMode_0_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._blendMode_0_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.blendMode1Attribute((undefined as BlendMode | undefined), (undefined as BlendApplyType | undefined | undefined));
        }
      }
    }
    if (this._geometryTransition_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._geometryTransition_1_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.geometryTransition1Attribute((this._geometryTransition_1_0value as string | undefined), (this._geometryTransition_1_1value as GeometryTransitionOptions | undefined));
          this._geometryTransition_1_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        case AttributeUpdaterFlag.SKIP: {
          this._geometryTransition_1_flag = AttributeUpdaterFlag.RESET;
          break;
        }
        default: {
          this._geometryTransition_1_flag = AttributeUpdaterFlag.INITIAL;
          peerNode.geometryTransition1Attribute((undefined as string | undefined), (undefined as GeometryTransitionOptions | undefined | undefined));
        }
      }
    }




    if (this._onClick_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._onClick_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onClick0Attribute((this._onClick0_value as ((event: ClickEvent) => void) | undefined))
          this._onClick_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onClick_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onClick_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onClick0Attribute(undefined)
        }
      }
    }
    if (this._size_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._size_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.sizeAttribute(this._size_value as (SizeOptions | undefined))
          this._size_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._size_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._size_flag = AttributeUpdaterFlag.INITIAL
          peerNode.sizeAttribute(undefined)
        }
      }
    }
    if (this._constraintSize_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._constraintSize_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.constraintSizeAttribute(this._constraintSize_value as (ConstraintSizeOptions | undefined))
          this._constraintSize_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._constraintSize_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._constraintSize_flag = AttributeUpdaterFlag.INITIAL
          peerNode.constraintSizeAttribute(undefined)
        }
      }
    }
    if (this._layoutWeight_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._layoutWeight_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.layoutWeightAttribute(this._layoutWeight_value as (number | string | undefined))
          this._layoutWeight_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._layoutWeight_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._layoutWeight_flag = AttributeUpdaterFlag.INITIAL
          peerNode.layoutWeightAttribute(undefined)
        }
      }
    }
    if (this._padding_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._padding_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.paddingAttribute(this._padding_value as (Padding | Length | LocalizedPadding | undefined))
          this._padding_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._padding_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._padding_flag = AttributeUpdaterFlag.INITIAL
          peerNode.paddingAttribute(undefined)
        }
      }
    }
    if (this._safeAreaPadding_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._safeAreaPadding_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.safeAreaPaddingAttribute(this._safeAreaPadding_value as (Padding | LengthMetrics | LocalizedPadding | undefined))
          this._safeAreaPadding_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._safeAreaPadding_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._safeAreaPadding_flag = AttributeUpdaterFlag.INITIAL
          peerNode.safeAreaPaddingAttribute(undefined)
        }
      }
    }
    if (this._margin_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._margin_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.marginAttribute(this._margin_value as (Padding | Length | LocalizedPadding | undefined))
          this._margin_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._margin_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._margin_flag = AttributeUpdaterFlag.INITIAL
          peerNode.marginAttribute(undefined)
        }
      }
    }
    if (this._flexGrow_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._flexGrow_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.flexGrowAttribute(this._flexGrow_value as (number | undefined))
          this._flexGrow_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._flexGrow_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._flexGrow_flag = AttributeUpdaterFlag.INITIAL
          peerNode.flexGrowAttribute(undefined)
        }
      }
    }
    if (this._flexShrink_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._flexShrink_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.flexShrinkAttribute(this._flexShrink_value as (number | undefined))
          this._flexShrink_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._flexShrink_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._flexShrink_flag = AttributeUpdaterFlag.INITIAL
          peerNode.flexShrinkAttribute(undefined)
        }
      }
    }
    if (this._flexBasis_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._flexBasis_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.flexBasisAttribute(this._flexBasis_value as (number | undefined))
          this._flexBasis_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._flexBasis_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._flexBasis_flag = AttributeUpdaterFlag.INITIAL
          peerNode.flexBasisAttribute(undefined)
        }
      }
    }
    if (this._alignSelf_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._alignSelf_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.alignSelfAttribute(this._alignSelf_value as (ItemAlign | undefined))
          this._alignSelf_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._alignSelf_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._alignSelf_flag = AttributeUpdaterFlag.INITIAL
          peerNode.alignSelfAttribute(undefined)
        }
      }
    }
    if (this._align_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._align_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.alignAttribute(this._align_value as (Alignment | undefined))
          this._align_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._align_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._align_flag = AttributeUpdaterFlag.INITIAL
          peerNode.alignAttribute(undefined)
        }
      }
    }
    if (this._position_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._position_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.positionAttribute(this._position_value as (Position | Edges | LocalizedEdges | undefined))
          this._position_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._position_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._position_flag = AttributeUpdaterFlag.INITIAL
          peerNode.positionAttribute(undefined)
        }
      }
    }
    if (this._markAnchor_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._markAnchor_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.markAnchorAttribute(this._markAnchor_value as (Position | LocalizedPosition | undefined))
          this._markAnchor_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._markAnchor_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._markAnchor_flag = AttributeUpdaterFlag.INITIAL
          peerNode.markAnchorAttribute(undefined)
        }
      }
    }
    if (this._offset_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._offset_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.offsetAttribute(this._offset_value as (Position | Edges | LocalizedEdges | undefined))
          this._offset_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._offset_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._offset_flag = AttributeUpdaterFlag.INITIAL
          peerNode.offsetAttribute(undefined)
        }
      }
    }
    if (this._alignRules_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._alignRules_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          if (TypeChecker.isAlignRuleOption(this._alignRules_value, false, false, false, false, false, false, false)) {
            peerNode.alignRules0Attribute(this._alignRules_value as (AlignRuleOption | undefined))
          } else if (TypeChecker.isLocalizedAlignRuleOptions(this._alignRules_value, false, false, false, false, false, false, false)) {
            peerNode.alignRules1Attribute(this._alignRules_value as (LocalizedAlignRuleOptions | undefined))
          }
          this._alignRules_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._alignRules_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._alignRules_flag = AttributeUpdaterFlag.INITIAL
          if (TypeChecker.isAlignRuleOption(this._alignRules_value, false, false, false, false, false, false, false)) {
            peerNode.alignRules0Attribute(undefined)
          } else if (TypeChecker.isLocalizedAlignRuleOptions(this._alignRules_value, false, false, false, false, false, false, false)) {
            peerNode.alignRules1Attribute(undefined)
          }
        }
      }
    }
    if (this._chainMode_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._chainMode_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.chainModeAttribute(this._chainMode_direction as (Axis | undefined), this._chainMode_style as (ChainStyle | undefined))
          this._chainMode_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._chainMode_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._chainMode_flag = AttributeUpdaterFlag.INITIAL
          peerNode.chainModeAttribute(undefined, undefined)
        }
      }
    }
    if (this._aspectRatio_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._aspectRatio_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.aspectRatioAttribute(this._aspectRatio_value as (number | undefined))
          this._aspectRatio_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._aspectRatio_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._aspectRatio_flag = AttributeUpdaterFlag.INITIAL
          peerNode.aspectRatioAttribute(undefined)
        }
      }
    }
    if (this._expandSafeArea_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._expandSafeArea_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.expandSafeAreaAttribute((this._expandSafeArea_types as Array<SafeAreaType> | undefined),
            (this._expandSafeArea_edges as Array<SafeAreaEdge> | undefined))
          this._expandSafeArea_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._expandSafeArea_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._expandSafeArea_flag = AttributeUpdaterFlag.INITIAL
          peerNode.expandSafeAreaAttribute(undefined, undefined)
        }
      }
    }
    if (this._zIndex_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (this._zIndex_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.zIndexAttribute(this._zIndex0_value as (number | undefined))
          this._zIndex_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._zIndex_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._zIndex_flag = AttributeUpdaterFlag.INITIAL
          peerNode.zIndexAttribute(undefined)
        }
      }
    }
    if (this._backgroundImage_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundImage_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          hookModifierBackgroundImageImpl(peerNode, (this._backgroundImage_src as ResourceStr | PixelMap | undefined), (this._backgroundImage_repeat as ImageRepeat | undefined))
          this._backgroundImage_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundImage_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._backgroundImage_flag = AttributeUpdaterFlag.INITIAL
          hookModifierBackgroundImageImpl(peerNode, undefined)
        }
      }
    }
    if (this._backgroundImageSize_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundImageSize_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundImageSizeAttribute((this._backgroundImageSize_value as SizeOptions | ImageSize | undefined))
          this._backgroundImageSize_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundImageSize_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._backgroundImageSize_flag = AttributeUpdaterFlag.INITIAL
          peerNode.backgroundImageSizeAttribute(undefined)
        }
      }
    }
    if (this._backgroundImagePosition_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundImagePosition_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundImagePositionAttribute((this._backgroundImagePosition_value as Position | Alignment | undefined))
          this._backgroundImagePosition_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundImagePosition_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._backgroundImagePosition_flag = AttributeUpdaterFlag.INITIAL
          peerNode.backgroundImagePositionAttribute(undefined)
        }
      }
    }
    if (this._backgroundImageResizable_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._backgroundImageResizable_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.backgroundImageResizableAttribute((this._backgroundImageResizable_value as ResizableOptions | undefined))
          this._backgroundImageResizable_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._backgroundImageResizable_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._backgroundImageResizable_flag = AttributeUpdaterFlag.INITIAL
          peerNode.backgroundImageResizableAttribute(undefined)
        }
      }
    }
    if (this._onHover_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onHover_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onHoverAttribute((this._onHover_value as ((isHover: boolean, event: HoverEvent) => void) | undefined))
          this._onHover_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onHover_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onHover_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onHoverAttribute(undefined)
        }
      }
    }
    if (this._onHoverMove_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onHoverMove_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onHoverMoveAttribute((this._onHoverMove_value as ((parameter: HoverEvent) => void) | undefined))
          this._onHoverMove_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onHoverMove_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onHoverMove_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onHoverMoveAttribute(undefined)
        }
      }
    }
    if (this._onMouse_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onMouse_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onMouseAttribute((this._onMouse_value as (((event: MouseEvent) => void) | undefined)))
          this._onMouse_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onMouse_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onMouse_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onMouseAttribute(undefined)
        }
      }
    }
    if (this._onTouch_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onTouch_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onTouchAttribute((this._onTouch_value as (((event: TouchEvent) => void) | undefined)))
          this._onTouch_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onTouch_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onTouch_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onTouchAttribute(undefined)
        }
      }
    }
    if (this._onFocusAxisEvent_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onFocusAxisEvent_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onFocusAxisEventAttribute((this._onFocusAxisEvent_value as (((parameter: FocusAxisEvent) => void) | undefined)))
          this._onFocusAxisEvent_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onFocusAxisEvent_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onFocusAxisEvent_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onFocusAxisEventAttribute(undefined)
        }
      }
    }
    if (this._onAxisEvent_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onAxisEvent_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onAxisEventAttribute((this._onAxisEvent_value as (((parameter: AxisEvent) => void) | undefined)))
          this._onAxisEvent_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onAxisEvent_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onAxisEvent_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onAxisEventAttribute(undefined)
        }
      }
    }
    if (this._onKeyEvent_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onKeyEvent_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onKeyEvent1Attribute((this._onKeyEvent1_value as ((event: KeyEvent) => boolean) | undefined))
          this._onKeyEvent_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onKeyEvent_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onKeyEvent_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onKeyEvent1Attribute(undefined)
        }
      }
    }
    if (this._onKeyPreIme_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onKeyPreIme_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onKeyPreImeAttribute((this._onKeyPreIme_value as ((event: KeyEvent) => boolean) | undefined))
          this._onKeyPreIme_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onKeyPreIme_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onKeyPreIme_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onKeyPreImeAttribute(undefined)
        }
      }
    }
    if (this._onKeyEventDispatch_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onKeyEventDispatch_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onKeyEventDispatchAttribute((this._onKeyEventDispatch_value as ((event: KeyEvent) => boolean) | undefined))
          this._onKeyEventDispatch_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onKeyEventDispatch_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onKeyEventDispatch_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onKeyEventDispatchAttribute(undefined)
        }
      }
    }
    if (this._keyboardShortcut_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._keyboardShortcut_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.keyboardShortcutAttribute((this._keyboardShortcut_value as string | FunctionKey | undefined), (this._keyboardShortcut_keys as Array<ModifierKey> | undefined), (this._keyboardShortcut_action as (() => void)))
          this._keyboardShortcut_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._keyboardShortcut_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._keyboardShortcut_flag = AttributeUpdaterFlag.INITIAL
          peerNode.keyboardShortcutAttribute(undefined, undefined)
        }
      }
    }
    if (this._focusable_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._focusable_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.focusableAttribute((this._focusable_value as boolean | undefined))
          this._focusable_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._focusable_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._focusable_flag = AttributeUpdaterFlag.INITIAL
          peerNode.focusableAttribute(undefined)
        }
      }
    }
    if (this._nextFocus_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._nextFocus_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.nextFocusAttribute((this._nextFocus_value as FocusMovement | undefined))
          this._nextFocus_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._nextFocus_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._nextFocus_flag = AttributeUpdaterFlag.INITIAL
          peerNode.nextFocusAttribute(undefined)
        }
      }
    }
    if (this._tabIndex_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._tabIndex_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.tabIndexAttribute((this._tabIndex_value as (number | undefined)))
          this._tabIndex_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._tabIndex_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._tabIndex_flag = AttributeUpdaterFlag.INITIAL
          peerNode.tabIndexAttribute(undefined)
        }
      }
    }
    if (this._defaultFocus_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._defaultFocus_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.defaultFocusAttribute((this._defaultFocus_value as (boolean | undefined)))
          this._defaultFocus_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._defaultFocus_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._defaultFocus_flag = AttributeUpdaterFlag.INITIAL
          peerNode.defaultFocusAttribute(undefined)
        }
      }
    }
    if (this._groupDefaultFocus_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._groupDefaultFocus_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.groupDefaultFocusAttribute((this._groupDefaultFocus_value as (boolean | undefined)))
          this._groupDefaultFocus_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._groupDefaultFocus_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._groupDefaultFocus_flag = AttributeUpdaterFlag.INITIAL
          peerNode.groupDefaultFocusAttribute(undefined)
        }
      }
    }
    if (this._focusOnTouch_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._focusOnTouch_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.focusOnTouchAttribute((this._focusOnTouch_value as (boolean | undefined)))
          this._focusOnTouch_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._focusOnTouch_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._focusOnTouch_flag = AttributeUpdaterFlag.INITIAL
          peerNode.focusOnTouchAttribute(undefined)
        }
      }
    }
    if (this._focusBox_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._focusBox_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.focusBoxAttribute((this._focusBox_value as (FocusBoxStyle | undefined)))
          this._focusBox_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._focusBox_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._focusBox_flag = AttributeUpdaterFlag.INITIAL
          peerNode.focusBoxAttribute(undefined)
        }
      }
    }
    if (this._focusScopeId_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._focusScopeId_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.focusScopeId1Attribute((this._focusScopeId_id as (string | undefined)), (this._focusScopeId_isGroup as boolean), (this._focusScopeId_arrowStepOut as boolean))
          this._focusScopeId_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._focusScopeId_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._focusScopeId_flag = AttributeUpdaterFlag.INITIAL
          peerNode.focusScopeId1Attribute(undefined)
        }
      }
    }
    if (this._focusScopePriority_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._focusScopePriority_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.focusScopePriorityAttribute((this._focusScopePriority_scopeId as (string | undefined)), (this._focusScopePriority_priority as FocusPriority))
          this._focusScopePriority_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._focusScopePriority_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._focusScopePriority_flag = AttributeUpdaterFlag.INITIAL
          peerNode.focusScopePriorityAttribute(undefined)
        }
      }
    }
    if (this._tabStop_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._tabStop_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.tabStopAttribute((this._tabStop_value as (boolean | undefined)))
          this._tabStop_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._tabStop_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._tabStop_flag = AttributeUpdaterFlag.INITIAL
          peerNode.tabStopAttribute(undefined)
        }
      }
    }
    if (this._onFocus_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onFocus_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onFocusAttribute((this._onFocus_value as ((() => void) | undefined)))
          this._onFocus_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onFocus_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onFocus_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onFocusAttribute(undefined)
        }
      }
    }
    if (this._onBlur_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onBlur_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onBlurAttribute((this._onBlur_value as ((() => void) | undefined)))
          this._onBlur_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onBlur_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onBlur_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onBlurAttribute(undefined)
        }
      }
    }
    if (this._onAppear_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onAppear_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onAppearAttribute((this._onAppear_value as ((() => void) | undefined)))
          this._onAppear_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onAppear_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onAppear_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onAppearAttribute(undefined)
        }
      }
    }
    if (this._onDisAppear_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onDisAppear_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onDisAppearAttribute((this._onDisAppear_value as ((() => void) | undefined)))
          this._onDisAppear_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onDisAppear_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onDisAppear_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onDisAppearAttribute(undefined)
        }
      }
    }
    if (this._onAttach_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onAttach_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onAttachAttribute((this._onAttach_value as ((() => void) | undefined)))
          this._onAttach_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onAttach_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onAttach_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onAttachAttribute(undefined)
        }
      }
    }
    if (this._onDetach_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onDetach_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onDetachAttribute((this._onDetach_value as ((() => void) | undefined)))
          this._onDetach_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onDetach_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onDetach_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onDetachAttribute(undefined)
        }
      }
    }
    if (this._onAreaChange_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onAreaChange_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onAreaChangeAttribute((this._onAreaChange_value as (((oldValue: Area, newValue: Area) => void) | undefined)))
          this._onAreaChange_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onAreaChange_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onAreaChange_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onAreaChangeAttribute(undefined)
        }
      }
    }
    if (this._onSizeChange_flag != AttributeUpdaterFlag.INITIAL) {
      switch (this._onSizeChange_flag) {
        case AttributeUpdaterFlag.UPDATE: {
          peerNode.onSizeChangeAttribute((this._onSizeChange_value as (SizeChangeCallback | undefined)))
          this._onSizeChange_flag = AttributeUpdaterFlag.RESET
          break
        }
        case AttributeUpdaterFlag.SKIP: {
          this._onSizeChange_flag = AttributeUpdaterFlag.RESET
          break
        }
        default: {
          this._onSizeChange_flag = AttributeUpdaterFlag.INITIAL
          peerNode.onSizeChangeAttribute(undefined)
        }
      }
    }
     if (this._onGestureJudgeBegin_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onGestureJudgeBegin_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.onGestureJudgeBeginAttribute((this._onGestureJudgeBegin_value as (((gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult) | undefined)))
           this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onGestureJudgeBegin_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onGestureJudgeBeginAttribute(undefined)
         }
       }
     }
     if (this._shouldBuiltInRecognizerParallelWith_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._shouldBuiltInRecognizerParallelWith_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.shouldBuiltInRecognizerParallelWithAttribute((this._shouldBuiltInRecognizerParallelWith_value as (ShouldBuiltInRecognizerParallelWithCallback | undefined)))
           this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._shouldBuiltInRecognizerParallelWith_flag = AttributeUpdaterFlag.INITIAL
           peerNode.shouldBuiltInRecognizerParallelWithAttribute(undefined)
         }
       }
     }
     if (this._onGestureRecognizerJudgeBegin_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._onGestureRecognizerJudgeBegin_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           if (runtimeType(this._onGestureRecognizerJudgeBegin_exposeInnerGesture) != (RuntimeType.BOOLEAN)) {
             peerNode.onGestureRecognizerJudgeBegin0Attribute((this._onGestureRecognizerJudgeBegin_callback as (GestureRecognizerJudgeBeginCallback | undefined)))
           } else {
             peerNode.onGestureRecognizerJudgeBegin1Attribute((this._onGestureRecognizerJudgeBegin_callback as (GestureRecognizerJudgeBeginCallback | undefined)), (this._onGestureRecognizerJudgeBegin_exposeInnerGesture as boolean))
           }
           this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._onGestureRecognizerJudgeBegin_flag = AttributeUpdaterFlag.INITIAL
           peerNode.onGestureRecognizerJudgeBegin0Attribute(undefined)
         }
       }
     }
     if (this._responseRegion_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._responseRegion_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.responseRegionAttribute((this._responseRegion_value as (Array<Rectangle> | Rectangle | undefined)))
           this._responseRegion_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._responseRegion_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._responseRegion_flag = AttributeUpdaterFlag.INITIAL
           peerNode.responseRegionAttribute(undefined)
         }
       }
     }
     if (this._hitTestBehavior_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._hitTestBehavior_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.hitTestBehaviorAttribute((this._hitTestBehavior_value as (HitTestMode | undefined)))
           this._hitTestBehavior_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._hitTestBehavior_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._hitTestBehavior_flag = AttributeUpdaterFlag.INITIAL
           peerNode.hitTestBehaviorAttribute(undefined)
         }
       }
     }
     if (this._monopolizeEvents_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._monopolizeEvents_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.monopolizeEventsAttribute((this._monopolizeEvents_value as (boolean | undefined)))
           this._monopolizeEvents_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._monopolizeEvents_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._monopolizeEvents_flag = AttributeUpdaterFlag.INITIAL
           peerNode.monopolizeEventsAttribute(undefined)
         }
       }
     }
     if (this._restoreId_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._restoreId_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.restoreIdAttribute(this._restoreId_value as (number | undefined))
           this._restoreId_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._restoreId_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._restoreId_flag = AttributeUpdaterFlag.INITIAL
           peerNode.restoreIdAttribute(undefined)
         }
       }
     }
     if (this._hoverEffect_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._hoverEffect_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.hoverEffectAttribute(this._hoverEffect_value as (HoverEffect | undefined))
           this._hoverEffect_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._hoverEffect_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._hoverEffect_flag = AttributeUpdaterFlag.INITIAL
           peerNode.hoverEffectAttribute(undefined)
         }
       }
     }
     if (this._enabled_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._enabled_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.enabledAttribute(this._enabled_value as (boolean | undefined))
           this._enabled_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._enabled_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._enabled_flag = AttributeUpdaterFlag.INITIAL
           peerNode.enabledAttribute(undefined)
         }
       }
     }
     if (this._visibility_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._visibility_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.visibilityAttribute(this._visibility_value as (Visibility | undefined))
           this._visibility_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._visibility_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._visibility_flag = AttributeUpdaterFlag.INITIAL
           peerNode.visibilityAttribute(undefined)
         }
       }
     }
     if (this._key_flag != AttributeUpdaterFlag.INITIAL) {
       switch (this._key_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.keyAttribute(this._key_value as (string | undefined))
           this._key_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._key_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._key_flag = AttributeUpdaterFlag.INITIAL
           peerNode.keyAttribute(undefined)
         }
       }
     }
     if (this._id_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (this._id_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           peerNode.idAttribute(this._id_value as (string | undefined))
           this._id_flag = AttributeUpdaterFlag.RESET
           break
         }
         case AttributeUpdaterFlag.SKIP: {
           this._id_flag = AttributeUpdaterFlag.RESET
           break
         }
         default: {
           this._id_flag = AttributeUpdaterFlag.INITIAL
           peerNode.idAttribute(undefined)
         }
       }
     }
     if (this._customProperty_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (this._customProperty_flag) {
         case AttributeUpdaterFlag.UPDATE: {
           const arkCommonMethodComponent: ArkCommonMethodComponent = new ArkCommonMethodComponent();
           arkCommonMethodComponent.setPeer(peerNode);
           if (this._customPropertyMap === undefined) {
             break;
           }
           this._customPropertyMap!.forEach((value, key) => {
             hookCustomPropertyImpl(arkCommonMethodComponent, key as (string), value as (CustomProperty));
           });
           this._customProperty_flag = AttributeUpdaterFlag.RESET;
           break;
         }
         case AttributeUpdaterFlag.SKIP: {
           this._customProperty_flag = AttributeUpdaterFlag.RESET;
           break;
         }
         default: {
           this._customProperty_flag = AttributeUpdaterFlag.INITIAL;
         }
       }
     }
   }
  mergeModifier(value: CommonMethodModifier): void {
    if(value._width_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._width_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.width(value._width_value)
          break
        }
        default: {
          this.width(undefined)
        }
      }
    }
    if(value._height_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._height_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.height(value._height_value)
          break
        }
        default: {
          this.height(undefined)
        }
      }
    }
    if (value._backgroundColor_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._backgroundColor_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.backgroundColor(value._backgroundColor_value);
          break;
        }
        default: {
          this.backgroundColor((undefined as ResourceColor | undefined));
        }
      }
    }
    if (value._backgroundEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._backgroundEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.backgroundEffect(value._backgroundEffect_0_0value);
          break;
        }
        default: {
          this.backgroundEffect((undefined as BackgroundEffectOptions | undefined));
        }
      }
    }
    if (value._backgroundEffect_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._backgroundEffect_1_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.backgroundEffect(value._backgroundEffect_1_0value, value._backgroundEffect_1_1value);
          break;
        }
        default: {
          this.backgroundEffect((undefined as BackgroundEffectOptions | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (value._foregroundEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._foregroundEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.foregroundEffect(value._foregroundEffect_0_0value);
          break;
        }
        default: {
          this.foregroundEffect((undefined as ForegroundEffectOptions | undefined));
        }
      }
    }
    if (value._visualEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._visualEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.visualEffect(value._visualEffect_0_0value);
          break;
        }
        default: {
          this.visualEffect((undefined as VisualEffect | undefined));
        }
      }
    }
    if (value._backgroundFilter_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._backgroundFilter_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.backgroundFilter(value._backgroundFilter_0_0value);
          break;
        }
        default: {
          this.backgroundFilter((undefined as Filter | undefined));
        }
      }
    }
    if (value._foregroundFilter_0_flag != AttributeUpdaterFlag.INITIAL) {
        switch (value._foregroundFilter_0_flag) {
            case AttributeUpdaterFlag.UPDATE:
            case AttributeUpdaterFlag.SKIP: {
                this.foregroundFilter(value._foregroundFilter_0_0value);
                break;
            }
            default: {
                this.foregroundFilter((undefined as Filter | undefined));
            }
        }
    }
    if (value._compositingFilter_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._compositingFilter_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.compositingFilter(value._compositingFilter_0_0value);
          break;
        }
        default: {
          this.compositingFilter((undefined as Filter | undefined));
        }
      }
    }
    if (value._opacity_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._opacity_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.opacity(value._opacity_0_0value);
          break;
        }
        default: {
          this.opacity((undefined as number | Resource | undefined));
        }
      }
    }
    if (value._outline_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._outline_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.outline(value._outline_0_0value);
          break;
        }
        default: {
          this.outline((undefined as OutlineOptions | undefined));
        }
      }
    }
    if (value._outlineStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._outlineStyle_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.outlineStyle(value._outlineStyle_0_0value);
          break;
        }
        default: {
          this.outlineStyle((undefined as OutlineStyle | EdgeOutlineStyles | undefined));
        }
      }
    }
    if (value._outlineWidth_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._outlineWidth_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.outlineWidth(value._outlineWidth_0_0value);
          break;
        }
        default: {
          this.outlineWidth((undefined as Dimension | EdgeOutlineWidths | undefined));
        }
      }
    }
    if (value._outlineColor_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._outlineColor_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.outlineColor(value._outlineColor_0_0value);
          break;
        }
        default: {
          this.outlineColor((undefined as ResourceColor | EdgeColors | LocalizedEdgeColors | undefined));
        }
      }
    }
    if (value._outlineRadius_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._outlineRadius_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.outlineRadius(value._outlineRadius_0_0value);
          break;
        }
        default: {
          this.outlineRadius((undefined as Dimension | OutlineRadiuses | undefined));
        }
      }
    }
    if (value._foregroundColor_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._foregroundColor_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.foregroundColor(value._foregroundColor_0_0value);
          break;
        }
        default: {
          this.foregroundColor((undefined as ResourceColor | ColoringStrategy | undefined));
        }
      }
    }
    if (value._transition_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._transition_1_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.transition(value._transition_1_0value);
          break;
        }
        default: {
          this.transition((undefined as TransitionEffect | undefined));
        }
      }
    }
    if (value._motionBlur_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._motionBlur_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.motionBlur(value._motionBlur_0_0value);
          break;
        }
        default: {
          this.motionBlur((undefined as MotionBlurOptions | undefined));
        }
      }
    }
    if (value._brightness_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._brightness_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.brightness(value._brightness_0_0value);
          break;
        }
        default: {
          this.brightness((undefined as number | undefined));
        }
      }
    }
    if (value._contrast_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._contrast_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.contrast(value._contrast_0_0value);
          break;
        }
        default: {
          this.contrast((undefined as number | undefined));
        }
      }
    }
    if (value._grayscale_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._grayscale_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.grayscale(value._grayscale_0_0value);
          break;
        }
        default: {
          this.grayscale((undefined as number | undefined));
        }
      }
    }
    if (value._colorBlend_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._colorBlend_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.colorBlend(value._colorBlend_0_0value);
          break;
        }
        default: {
          this.colorBlend((undefined as Color | string | Resource | undefined));
        }
      }
    }
    if (value._saturate_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._saturate_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.saturate(value._saturate_0_0value);
          break;
        }
        default: {
          this.saturate((undefined as number | undefined));
        }
      }
    }
    if (value._sepia_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._sepia_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.sepia(value._sepia_0_0value);
          break;
        }
        default: {
          this.sepia((undefined as number | undefined));
        }
      }
    }
    if (value._invert_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._invert_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.invert(value._invert_0_0value);
          break;
        }
        default: {
          this.invert((undefined as number | InvertOptions | undefined));
        }
      }
    }
    if (value._hueRotate_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._hueRotate_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.hueRotate(value._hueRotate_0_0value);
          break;
        }
        default: {
          this.hueRotate((undefined as number | string | undefined));
        }
      }
    }
    if (value._useShadowBatching_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._useShadowBatching_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.useShadowBatching(value._useShadowBatching_0_0value);
          break;
        }
        default: {
          this.useShadowBatching((undefined as boolean | undefined));
        }
      }
    }
    if (value._useEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._useEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.useEffect(value._useEffect_0_0value);
          break;
        }
        default: {
          this.useEffect((undefined as boolean | undefined));
        }
      }
    }
    if (value._renderGroup_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._renderGroup_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.renderGroup(value._renderGroup_0_0value);
          break;
        }
        default: {
          this.renderGroup((undefined as boolean | undefined));
        }
      }
    }
    if (value._freeze_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._freeze_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.freeze(value._freeze_0_0value);
          break;
        }
        default: {
          this.freeze((undefined as boolean | undefined));
        }
      }
    }
    if (value._translate_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._translate_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.translate(value._translate_0_0value);
          break;
        }
        default: {
          this.translate((undefined as TranslateOptions | undefined));
        }
      }
    }
    if (value._scale_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._scale_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.scale(value._scale_0_0value);
          break;
        }
        default: {
          this.scale((undefined as ScaleOptions | undefined));
        }
      }
    }
    if (value._rotate_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._rotate_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.rotate(value._rotate_0_0value);
          break;
        }
        default: {
          this.rotate((undefined as RotateOptions | undefined));
        }
      }
    }
    if (value._transform_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._transform_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.transform(value._transform_0_0value);
          break;
        }
        default: {
          this.transform((undefined as Object | undefined));
        }
      }
    }
    if (value._clickEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._clickEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.clickEffect(value._clickEffect_0_0value);
          break;
        }
        default: {
          this.clickEffect((undefined as ClickEffect | undefined));
        }
      }
    }
    if (value._linearGradient_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._linearGradient_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.linearGradient(value._linearGradient_0_0value);
          break;
        }
        default: {
          this.linearGradient((undefined as LinearGradientOptions | undefined));
        }
      }
    }
    if (value._sweepGradient_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._sweepGradient_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.sweepGradient(value._sweepGradient_0_0value);
          break;
        }
        default: {
          this.sweepGradient((undefined as SweepGradientOptions | undefined));
        }
      }
    }
    if (value._radialGradient_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._radialGradient_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.radialGradient(value._radialGradient_0_0value);
          break;
        }
        default: {
          this.radialGradient((undefined as RadialGradientOptions | undefined));
        }
      }
    }
    if (value._motionPath_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._motionPath_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.motionPath(value._motionPath_0_0value);
          break;
        }
        default: {
          this.motionPath((undefined as MotionPathOptions | undefined));
        }
      }
    }
    if (value._shadow_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._shadow_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.shadow(value._shadow_0_0value);
          break;
        }
        default: {
          this.shadow((undefined as ShadowOptions | ShadowStyle | undefined));
        }
      }
    }
    if (value._clip_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._clip_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.clip(value._clip_0_0value);
          break;
        }
        default: {
          this.clip((undefined as boolean | undefined));
        }
      }
    }
    if (value._clipShape_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._clipShape_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.clipShape(value._clipShape_0_0value);
          break;
        }
        default: {
          this.clipShape((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
        }
      }
    }
    if (value._mask_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._mask_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.mask(value._mask_0_0value);
          break;
        }
        default: {
          this.mask((undefined as ProgressMask | undefined));
        }
      }
    }
    if (value._maskShape_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._maskShape_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.maskShape(value._maskShape_0_0value);
          break;
        }
        default: {
          this.maskShape((undefined as CircleShape | EllipseShape | PathShape | RectShape | undefined));
        }
      }
    }
    if (value._geometryTransition_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._geometryTransition_1_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.geometryTransition(value._geometryTransition_1_0value);
          break;
        }
        default: {
          this.geometryTransition((undefined as string | undefined));
        }
      }
    }
    if (value._sphericalEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._sphericalEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.sphericalEffect(value._sphericalEffect_0_0value);
          break;
        }
        default: {
          this.sphericalEffect((undefined as number | undefined));
        }
      }
    }
    if (value._lightUpEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._lightUpEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.lightUpEffect(value._lightUpEffect_0_0value);
          break;
        }
        default: {
          this.lightUpEffect((undefined as number | undefined));
        }
      }
    }
    if (value._pixelStretchEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._pixelStretchEffect_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.pixelStretchEffect(value._pixelStretchEffect_0_0value);
          break;
        }
        default: {
          this.pixelStretchEffect((undefined as PixelStretchEffectOptions | undefined));
        }
      }
    }
    if (value._renderFit_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._renderFit_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.renderFit(value._renderFit_0_0value);
          break;
        }
        default: {
          this.renderFit((undefined as RenderFit | undefined));
        }
      }
    }
    if (value._backgroundBrightness_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._backgroundBrightness_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.backgroundBrightness(value._backgroundBrightness_0_0value);
          break;
        }
        default: {
          this.backgroundBrightness((undefined as BackgroundBrightnessOptions | undefined));
        }
      }
    }
    if (value._backgroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._backgroundBlurStyle_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.backgroundBlurStyle(value._backgroundBlurStyle_0_0value, value._backgroundBlurStyle_0_1value, value._backgroundBlurStyle_0_2value);
          break;
        }
        default: {
          this.backgroundBlurStyle((undefined as BlurStyle | undefined), (undefined as BackgroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (value._backgroundEffect_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._backgroundEffect_1_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.backgroundEffect(value._backgroundEffect_1_0value, value._backgroundEffect_1_1value);
          break;
        }
        default: {
          this.backgroundEffect((undefined as BackgroundEffectOptions | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (value._foregroundBlurStyle_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._foregroundBlurStyle_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.foregroundBlurStyle(value._foregroundBlurStyle_0_0value, value._foregroundBlurStyle_0_1value, value._foregroundBlurStyle_0_2value);
          break;
        }
        default: {
          this.foregroundBlurStyle((undefined as BlurStyle | undefined), (undefined as ForegroundBlurStyleOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (value._transition_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._transition_1_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.transition(value._transition_1_0value, value._transition_1_1value);
          break;
        }
        default: {
          this.transition((undefined as TransitionEffect | undefined), (undefined as TransitionFinishCallback | undefined));
        }
      }
    }
    if (value._blur_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._blur_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.blur(value._blur_0_0value, value._blur_0_1value, value._blur_0_2value);
          break;
        }
        default: {
          this.blur((undefined as number | undefined), (undefined as BlurOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (value._linearGradientBlur_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._linearGradientBlur_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.linearGradientBlur(value._linearGradientBlur_0_0value, value._linearGradientBlur_0_1value);
          break;
        }
        default: {
          this.linearGradientBlur((undefined as number | undefined), (undefined as LinearGradientBlurOptions | undefined));
        }
      }
    }
    if (value._systemBarEffect_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._systemBarEffect_0_flag) {
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
    if (value._useEffect_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._useEffect_1_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.useEffect(value._useEffect_1_0value, value._useEffect_1_1value);
          break;
        }
        default: {
          this.useEffect((undefined as boolean | undefined), (undefined as EffectType | undefined));
        }
      }
    }
    if (value._backdropBlur_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._backdropBlur_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.backdropBlur(value._backdropBlur_0_0value, value._backdropBlur_0_1value, value._backdropBlur_0_2value);
          break;
        }
        default: {
          this.backdropBlur((undefined as number | undefined), (undefined as BlurOptions | undefined | undefined), (undefined as SystemAdaptiveOptions | undefined | undefined));
        }
      }
    }
    if (value._sharedTransition_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._sharedTransition_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.sharedTransition(value._sharedTransition_0_0value, value._sharedTransition_0_1value);
          break;
        }
        default: {
          this.sharedTransition((undefined as string | undefined), (undefined as sharedTransitionOptions | undefined | undefined));
        }
      }
    }
    if (value._blendMode_0_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._blendMode_0_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.blendMode(value._blendMode_0_0value, value._blendMode_0_1value);
          break;
        }
        default: {
          this.blendMode((undefined as BlendMode | undefined), (undefined as BlendApplyType | undefined | undefined));
        }
      }
    }
    if (value._geometryTransition_1_flag != AttributeUpdaterFlag.INITIAL) {
      switch (value._geometryTransition_1_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.geometryTransition(value._geometryTransition_1_0value, value._geometryTransition_1_1value);
          break;
        }
        default: {
          this.geometryTransition((undefined as string | undefined), (undefined as GeometryTransitionOptions | undefined | undefined));
        }
      }
    }

    if (value._size_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._size_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.size(value._size_value)
          break
        }
        default: {
          this.size(undefined)
        }
      }
    }
    if (value._constraintSize_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._constraintSize_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.constraintSize(value._constraintSize_value)
          break
        }
        default: {
          this.constraintSize(undefined)
        }
      }
    }
    if (value._layoutWeight_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._layoutWeight_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.layoutWeight(value._layoutWeight_value)
          break
        }
        default: {
          this.layoutWeight(undefined)
        }
      }
    }
    if (value._padding_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._padding_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.padding(value._padding_value)
          break
        }
        default: {
          this.padding(undefined)
        }
      }
    }
    if (value._safeAreaPadding_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._safeAreaPadding_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.safeAreaPadding(value._safeAreaPadding_value)
          break
        }
        default: {
          this.safeAreaPadding(undefined)
        }
      }
    }
    if (value._margin_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._margin_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.margin(value._margin_value)
          break
        }
        default: {
          this.margin(undefined)
        }
      }
    }
    if (value._flexGrow_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._flexGrow_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.flexGrow(value._flexGrow_value)
          break
        }
        default: {
          this.flexGrow(undefined)
        }
      }
    }
    if (value._flexShrink_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._flexShrink_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.flexShrink(value._flexShrink_value)
          break
        }
        default: {
          this.flexShrink(undefined)
        }
      }
    }
    if (value._flexBasis_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._flexBasis_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.flexBasis(value._flexBasis_value)
          break
        }
        default: {
          this.flexBasis(undefined)
        }
      }
    }
    if (value._alignSelf_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._alignSelf_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.alignSelf(value._alignSelf_value)
          break
        }
        default: {
          this.alignSelf(undefined)
        }
      }
    }
    if (value._align_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._align_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.align(value._align_value)
          break
        }
        default: {
          this.align(undefined)
        }
      }
    }
    if (value._position_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._position_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.position(value._position_value)
          break
        }
        default: {
          this.position(undefined)
        }
      }
    }
    if (value._offset_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._offset_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.offset(value._offset_value)
          break
        }
        default: {
          this.offset(undefined)
        }
      }
    }
    if (value._alignRules_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._alignRules_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.alignRules(value._alignRules_value)
          break
        }
        default: {
          this.alignRules(undefined)
        }
      }
    }
    if (value._chainMode_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._chainMode_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.chainMode(value._chainMode_direction, value._chainMode_style)
          break
        }
        default: {
          this.chainMode(undefined, undefined)
        }
      }
    }
    if (value._aspectRatio_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._aspectRatio_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.aspectRatio(value._aspectRatio_value)
          break
        }
        default: {
          this.aspectRatio(undefined)
        }
      }
    }
    if (value._expandSafeArea_flag !== AttributeUpdaterFlag.INITIAL) {
      switch (value._expandSafeArea_flag) {
        case AttributeUpdaterFlag.UPDATE:
        case AttributeUpdaterFlag.SKIP: {
          this.expandSafeArea(value._expandSafeArea_types, value._expandSafeArea_edges)
          break
        }
        default: {
          this.expandSafeArea(undefined, undefined)
        }
      }
    }
     if (value._onClick_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (value._onClick_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onClick(value._onClick0_value)
           break
         }
         default: {
           this.onClick(undefined)
         }
       }
     }
     if (value._zIndex_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (value._zIndex_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.zIndex(value._zIndex0_value)
           break
         }
         default: {
           this.zIndex(undefined)
         }
       }
     }
     if (value._backgroundImage_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImage_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImage(value._backgroundImage_src, this._backgroundImage_repeat)
           break
         }
         default: {
           this.backgroundImage(undefined)
         }
       }
     }
     if (value._backgroundImagePosition_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImagePosition_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImagePosition(value._backgroundImagePosition_value)
           break
         }
         default: {
           this.backgroundImagePosition(undefined)
         }
       }
     }
     if (value._backgroundImageSize_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImageSize_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImageSize(value._backgroundImageSize_value)
           break
         }
         default: {
           this.backgroundImageSize(undefined)
         }
       }
     }
     if (value._backgroundImagePosition_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImagePosition_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImagePosition(value._backgroundImagePosition_value)
           break
         }
         default: {
           this.backgroundImagePosition(undefined)
         }
       }
     }
     if (value._backgroundImageResizable_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._backgroundImageResizable_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.backgroundImageResizable(value._backgroundImageResizable_value)
           break
         }
         default: {
           this.backgroundImageResizable(undefined)
         }
       }
     }
     if (value._onHover_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onHover_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onHover(value._onHover_value)
           break
         }
         default: {
           this.onHover(undefined)
         }
       }
     }
     if (value._onHoverMove_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onHoverMove_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onHoverMove(value._onHoverMove_value)
           break
         }
         default: {
           this.onHoverMove(undefined)
         }
       }
     }
     if (value._onMouse_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onMouse_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onMouse(value._onMouse_value)
           break
         }
         default: {
           this.onMouse(undefined)
         }
       }
     }
     if (value._onTouch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onTouch_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onTouch(value._onTouch_value)
           break
         }
         default: {
           this.onTouch(undefined)
         }
       }
     }
     if (value._onFocusAxisEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onFocusAxisEvent_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onFocusAxisEvent(value._onFocusAxisEvent_value)
           break
         }
         default: {
           this.onFocusAxisEvent(undefined)
         }
       }
     }
     if (value._onAxisEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onAxisEvent_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onAxisEvent(value._onAxisEvent_value)
           break
         }
         default: {
           this.onAxisEvent(undefined)
         }
       }
     }
     if (value._onKeyEvent_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onKeyEvent_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onKeyEvent(value._onKeyEvent1_value)
           break
         }
         default: {
           this.onKeyEvent(undefined)
         }
       }
     }
     if (value._onKeyPreIme_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onKeyPreIme_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onKeyPreIme(value._onKeyPreIme_value)
           break
         }
         default: {
           this.onKeyPreIme(undefined)
         }
       }
     }
     if (value._onKeyEventDispatch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onKeyEventDispatch_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onKeyEventDispatch(value._onKeyEventDispatch_value)
           break
         }
         default: {
           this.onKeyEventDispatch(undefined)
         }
       }
     }
     if (value._keyboardShortcut_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._keyboardShortcut_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.keyboardShortcut((this._keyboardShortcut_value as (string | FunctionKey | undefined)), (this._keyboardShortcut_keys as (Array<ModifierKey> | undefined)), (this._keyboardShortcut_action as (() => void)))
           break
         }
         default: {
           this.keyboardShortcut(undefined, undefined)
         }
       }
     }
     if (value._focusable_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusable_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusable(value._focusable_value)
           break
         }
         default: {
           this.focusable(undefined)
         }
       }
     }
     if (value._nextFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._nextFocus_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.nextFocus(value._nextFocus_value)
           break
         }
         default: {
           this.nextFocus(undefined)
         }
       }
     }
     if (value._tabIndex_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._tabIndex_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.tabIndex(value._tabIndex_value)
           break
         }
         default: {
           this.tabIndex(undefined)
         }
       }
     }
     if (value._defaultFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._defaultFocus_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.defaultFocus(value._defaultFocus_value)
           break
         }
         default: {
           this.defaultFocus(undefined)
         }
       }
     }
     if (value._groupDefaultFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._groupDefaultFocus_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.groupDefaultFocus(value._groupDefaultFocus_value)
           break
         }
         default: {
           this.groupDefaultFocus(undefined)
         }
       }
     }
     if (value._focusOnTouch_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusOnTouch_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusOnTouch(value._focusOnTouch_value)
           break
         }
         default: {
           this.focusOnTouch(undefined)
         }
       }
     }
     if (value._focusBox_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusBox_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusBox(value._focusBox_value)
           break
         }
         default: {
           this.focusBox(undefined)
         }
       }
     }
     if (value._focusScopeId_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusScopeId_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusScopeId(value._focusScopeId_id, value._focusScopeId_isGroup, value._focusScopeId_arrowStepOut)
           break
         }
         default: {
           this.focusScopeId(undefined)
         }
       }
     }
     if (value._focusScopePriority_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._focusScopePriority_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.focusScopePriority(value._focusScopePriority_scopeId, value._focusScopePriority_priority)
           break
         }
         default: {
           this.focusScopePriority(undefined)
         }
       }
     }
     if (value._tabStop_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._tabStop_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.tabStop(value._tabStop_value)
           break
         }
         default: {
           this.tabStop(undefined)
         }
       }
     }
     if (value._onFocus_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onFocus_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onFocus(value._onFocus_value)
           break
         }
         default: {
           this.onFocus(undefined)
         }
       }
     }
     if (value._onBlur_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onBlur_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onBlur(value._onBlur_value)
           break
         }
         default: {
           this.onBlur(undefined)
         }
       }
     }
     if (value._onAppear_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onAppear_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onAppear(value._onAppear_value)
           break
         }
         default: {
           this.onAppear(undefined)
         }
       }
     }
     if (value._onDisAppear_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onDisAppear_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onDisAppear(value._onDisAppear_value)
           break
         }
         default: {
           this.onDisAppear(undefined)
         }
       }
     }
     if (value._onAttach_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onAttach_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onAttach(value._onAttach_value)
           break
         }
         default: {
           this.onAttach(undefined)
         }
       }
     }
     if (value._onDetach_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onDetach_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onDetach(value._onDetach_value)
           break
         }
         default: {
           this.onDetach(undefined)
         }
       }
     }
     if (value._onAreaChange_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onAreaChange_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onAreaChange(value._onAreaChange_value)
           break
         }
         default: {
           this.onAreaChange(undefined)
         }
       }
     }
     if (value._onSizeChange_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onSizeChange_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onSizeChange(value._onSizeChange_value)
           break
         }
         default: {
           this.onSizeChange(undefined)
         }
       }
     }
     if (value._onGestureJudgeBegin_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onGestureJudgeBegin_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onGestureJudgeBegin(value._onGestureJudgeBegin_value)
           break
         }
         default: {
           this.onGestureJudgeBegin(undefined)
         }
       }
     }
     if (value._shouldBuiltInRecognizerParallelWith_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._shouldBuiltInRecognizerParallelWith_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.shouldBuiltInRecognizerParallelWith(value._shouldBuiltInRecognizerParallelWith_value)
           break
         }
         default: {
           this.shouldBuiltInRecognizerParallelWith(undefined)
         }
       }
     }
     if (value._onGestureRecognizerJudgeBegin_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._onGestureRecognizerJudgeBegin_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.onGestureRecognizerJudgeBegin(value._onGestureRecognizerJudgeBegin_callback, value._onGestureRecognizerJudgeBegin_exposeInnerGesture)
           break
         }
         default: {
           this.onGestureRecognizerJudgeBegin(undefined)
         }
       }
     }
     if (value._responseRegion_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._responseRegion_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.responseRegion(value._responseRegion_value)
           break
         }
         default: {
           this.responseRegion(undefined)
         }
       }
     }
     if (value._hitTestBehavior_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._hitTestBehavior_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.hitTestBehavior(value._hitTestBehavior_value)
           break
         }
         default: {
           this.hitTestBehavior(undefined)
         }
       }
     }
     if (value._monopolizeEvents_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._monopolizeEvents_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.monopolizeEvents(value._monopolizeEvents_value)
           break
         }
         default: {
           this.monopolizeEvents(undefined)
         }
       }
     }
     if (value._restoreId_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._restoreId_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.restoreId(value._restoreId_value)
           break
         }
         default: {
           this.restoreId(undefined)
         }
       }
     }
     if (value._hoverEffect_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._hoverEffect_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.hoverEffect(value._hoverEffect_value)
           break
         }
         default: {
           this.hoverEffect(undefined)
         }
       }
     }
     if (value._enabled_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._enabled_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.enabled(value._enabled_value)
           break
         }
         default: {
           this.enabled(undefined)
         }
       }
     }
     if (value._visibility_flag != AttributeUpdaterFlag.INITIAL) {
       switch (value._visibility_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.visibility(value._visibility_value)
           break
         }
         default: {
           this.visibility(undefined)
         }
       }
     }
     if (value._key_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (value._key_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.key(value._key_value)
           break
         }
         default: {
           this.key(undefined)
         }
       }
     }
     if (value._id_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (value._id_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           this.id(value._id_value)
           break
         }
         default: {
           this.id(undefined)
         }
       }
     }
     if (value._customProperty_flag !== AttributeUpdaterFlag.INITIAL) {
       switch (value._customProperty_flag) {
         case AttributeUpdaterFlag.UPDATE:
         case AttributeUpdaterFlag.SKIP: {
           if (this._customPropertyMap === undefined) {
             break;
           }
           this._customPropertyMap!.forEach((value, key) => {
             this.customProperty(key as (string), value);
           });
           break;
         }
         default: {
         }
       }
     }
   }
}