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

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { VP, Length, ResourceColor, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { SwiperController } from "./ArkSwiperControllerMaterialized"
import { CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, EdgeEffect, Curve } from "./ArkEnumsInterfaces"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Number_Void, Callback_SwiperContentTransitionProxy_Void } from "./SyntheticDeclarations"
import { LengthMetrics } from "./ArkLengthMetricsMaterialized"
import { ResizableOptions } from "./ArkImageInterfaces"
import { Resource } from "./ArkResourceInterfaces"
import { ClickEvent } from "./ArkClickEventMaterialized"
import { HoverEvent } from "./ArkHoverEventMaterialized"
import { MouseEvent } from "./ArkMouseEventMaterialized"
import { TouchEvent } from "./ArkTouchEventMaterialized"
import { KeyEvent } from "./ArkKeyEventMaterialized"
import { FocusBoxStyle, FocusPriority } from "./ArkFocusInterfaces"
import { TransitionEffect } from "./ArkTransitionEffectMaterialized"
import { DragEvent } from "./ArkDragEventMaterialized"
import { CircleShape } from "./ArkCircleShapeMaterialized"
import { EllipseShape } from "./ArkEllipseShapeMaterialized"
import { PathShape } from "./ArkPathShapeMaterialized"
import { RectShape } from "./ArkRectShapeMaterialized"
import { ProgressMask } from "./ArkProgressMaskMaterialized"
import { AttributeModifier } from "./../handwritten"
import { GestureModifier } from "./ArkGestureModifierMaterialized"
import { GestureInfo, GestureJudgeResult, GestureType, GestureMask } from "./ArkGestureInterfaces"
import { BaseGestureEvent } from "./ArkBaseGestureEventMaterialized"
import { PixelMap } from "./ArkPixelMapMaterialized"
import { DotIndicator } from "./ArkDotIndicatorBuilder"
import { DigitIndicator } from "./ArkDigitIndicatorBuilder"
import { IndicatorComponentController } from "./ArkIndicatorComponentControllerMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { SwiperContentTransitionProxy } from "./ArkSwiperContentTransitionProxyMaterialized"
export interface SwiperAutoFill {
    minSize: VP;
}
export interface ArrowStyle {
    showBackground?: boolean;
    isSidebarMiddle?: boolean;
    backgroundSize?: Length;
    backgroundColor?: ResourceColor;
    arrowSize?: Length;
    arrowColor?: ResourceColor;
}
export enum SwiperDisplayMode {
    LEGACY_STRETCH = 0,
    Stretch = 0,
    LEGACY_AUTO_LINEAR = 1,
    AutoLinear = 1,
    STRETCH = 2,
    AUTO_LINEAR = 3
}
export type SwiperInterface = (controller?: SwiperController) => SwiperAttribute;
export interface IndicatorStyle {
    left?: Length;
    top?: Length;
    right?: Length;
    bottom?: Length;
    size?: Length;
    mask?: boolean;
    color?: ResourceColor;
    selectedColor?: ResourceColor;
}
export interface SwiperAnimationEvent {
    currentOffset: number;
    targetOffset: number;
    velocity: number;
}
export enum SwiperNestedScrollMode {
    SELF_ONLY = 0,
    SELF_FIRST = 1
}
export type OnSwiperAnimationStartCallback = (index: number, targetIndex: number, extraInfo: SwiperAnimationEvent) => void;
export type OnSwiperAnimationEndCallback = (index: number, extraInfo: SwiperAnimationEvent) => void;
export type OnSwiperGestureSwipeCallback = (index: number, extraInfo: SwiperAnimationEvent) => void;
export interface SwiperAttribute extends CommonMethod<SwiperAttribute> {
    index: number;
    autoPlay: boolean;
    interval: number;
    indicator: DotIndicator | DigitIndicator | boolean;

    loop: boolean;
    duration: number;
    vertical: boolean;
    itemSpace: number | string;
    displayMode: SwiperDisplayMode;
    cachedCount: number;
    effectMode: EdgeEffect;
    disableSwipe: boolean;
    curve: Curve | string | ICurve;
    onChange: ((index: number) => void);
    indicatorStyle?: IndicatorStyle;
    onAnimationStart: OnSwiperAnimationStartCallback;
    onAnimationEnd: OnSwiperAnimationEndCallback;
    onGestureSwipe: OnSwiperGestureSwipeCallback;
    nestedScroll: SwiperNestedScrollMode;
    customContentTransition: SwiperContentAnimatedTransition;
    onContentDidScroll: ContentDidScrollCallback;
    indicatorInteractive: boolean;
}
export interface SwiperContentAnimatedTransition {
    timeout?: number;
    transition: ((parameter: SwiperContentTransitionProxy) => void);
}
export type ContentDidScrollCallback = (selectedIndex: number, index: number, position: number, mainAxisLength: number) => void;
