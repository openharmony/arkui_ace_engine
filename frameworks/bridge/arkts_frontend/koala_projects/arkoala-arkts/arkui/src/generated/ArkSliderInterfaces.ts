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
import { Axis, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, ResponseType, FunctionKey, ModifierKey } from "./ArkEnumsInterfaces"
import { ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions } from "./ArkUnitsInterfaces"
import { CommonConfiguration, ContentModifier, CommonMethod, Rectangle, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, AccessibilityCallback, AnimateParam, TransitionOptions, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, CustomBuilder, DragItemInfo, UniformDataType, PreDragStatus, MotionPathOptions, ShadowOptions, ShadowStyle, StateStyles, PixelStretchEffectOptions, BackgroundBrightnessOptions, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, SizeChangeCallback, SafeAreaType, SafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./ArkCommonInterfaces"
import { DrawModifier } from "./ArkDrawModifierMaterialized"
import { Callback_Array_TouchTestInfo_TouchResult, Callback_ClickEvent_Void, Callback_Boolean_HoverEvent_Void, Callback_MouseEvent_Void, Callback_TouchEvent_Void, Callback_KeyEvent_Void, Callback_KeyEvent_Boolean, Callback_Void, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, Callback_DragEvent_String_Void, Callback_PreDragStatus_Void, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, Callback_TouchEvent_HitTestMode, Literal_Alignment_align, Callback_Number_SliderChangeMode_Void, Callback_Number_Void } from "./SyntheticDeclarations"
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
import { LinearGradient } from "./ArkLinearGradientMaterialized"
export enum SliderStyle {
    OUT_SET = 0,
    OutSet = 0,
    IN_SET = 1,
    InSet = 1,
    NONE = 2
}
export enum SliderChangeMode {
    BEGIN = 0,
    Begin = 0,
    MOVING = 1,
    Moving = 1,
    END = 2,
    End = 2,
    CLICK = 3,
    Click = 3
}
export enum SliderInteraction {
    SLIDE_AND_CLICK = 0,
    SLIDE_ONLY = 1,
    SLIDE_AND_CLICK_UP = 2
}
export interface SlideRange {
    from?: number;
    to?: number;
}
export interface SliderOptions {
    value?: number;
    min?: number;
    max?: number;
    step?: number;
    style?: SliderStyle;
    direction?: Axis;
    reverse?: boolean;
}
export enum SliderBlockType {
    DEFAULT = 0,
    IMAGE = 1,
    SHAPE = 2
}
export interface SliderBlockStyle {
    type: SliderBlockType;
    image?: ResourceStr;
    shape?: string;
}
export type SliderTriggerChangeCallback = (value: number, mode: SliderChangeMode) => void;
export interface SliderConfiguration extends CommonConfiguration<SliderConfiguration> {
    value: number;
    min: number;
    max: number;
    step: number;
    triggerChange: SliderTriggerChangeCallback;
}
export type SliderInterface = (options?: SliderOptions) => SliderAttribute;
export interface SliderAttribute extends CommonMethod<SliderAttribute> {
    blockColor: ResourceColor;
    trackColor: ResourceColor | LinearGradient;
    selectedColor: ResourceColor;
    minLabel: string;
    maxLabel: string;
    showSteps: boolean;
    trackThickness: Length;
    onChange: ((value: number,mode: SliderChangeMode) => void);
    blockBorderColor: ResourceColor;
    blockBorderWidth: Length;
    stepColor: ResourceColor;
    trackBorderRadius: Length;
    selectedBorderRadius: Dimension;
    blockSize: SizeOptions;
    blockStyle: SliderBlockStyle;
    stepSize: Length;
    sliderInteractionMode: SliderInteraction;
    minResponsiveDistance: number;
    contentModifier: ContentModifier<SliderConfiguration>;
    slideRange: SlideRange;
}
