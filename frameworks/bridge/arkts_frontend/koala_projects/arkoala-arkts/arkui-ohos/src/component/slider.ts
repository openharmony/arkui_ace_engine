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
import { Axis, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, ResponseType, FunctionKey, ModifierKey } from "./enums"
import { ResourceStr, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, Dimension, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, AccessibilityOptions } from "./units"
import { CommonConfiguration, ContentModifier, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { LengthMetrics } from "../Graphics"
import { ResizableOptions } from "./image"
import { Resource } from "global/resource";
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { LinearGradient } from "./dataPanel"
import { Callback_Number_Void } from "./alphabetIndexer"
import { ArkSliderComponent } from "./../generated/ArkSlider"
import { ArkSliderPeer } from "./../generated/peers/ArkSliderPeer"
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
export type Callback_Number_SliderChangeMode_Void = (value: number, mode: SliderChangeMode) => void;
/** @memo:stable */
export interface SliderAttribute extends CommonMethod {
    /** @memo */
    setSliderOptions(options?: SliderOptions): this
    /** @memo */
    blockColor(value: ResourceColor): this
    /** @memo */
    trackColor(value: ResourceColor | LinearGradient): this
    /** @memo */
    selectedColor(value: ResourceColor): this
    /** @memo */
    minLabel(value: string): this
    /** @memo */
    maxLabel(value: string): this
    /** @memo */
    showSteps(value: boolean): this
    /** @memo */
    trackThickness(value: Length): this
    /** @memo */
    onChange(value: ((value: number,mode: SliderChangeMode) => void)): this
    /** @memo */
    blockBorderColor(value: ResourceColor): this
    /** @memo */
    blockBorderWidth(value: Length): this
    /** @memo */
    stepColor(value: ResourceColor): this
    /** @memo */
    trackBorderRadius(value: Length): this
    /** @memo */
    selectedBorderRadius(value: Dimension): this
    /** @memo */
    blockSize(value: SizeOptions): this
    /** @memo */
    blockStyle(value: SliderBlockStyle): this
    /** @memo */
    stepSize(value: Length): this
    /** @memo */
    sliderInteractionMode(value: SliderInteraction): this
    /** @memo */
    minResponsiveDistance(value: number): this
    /** @memo */
    contentModifier(value: ContentModifier<object>): this
    /** @memo */
    slideRange(value: SlideRange): this
    /** @memo */
    showTips(value: boolean, content?: ResourceStr): this
    /** @memo */
    _onChangeEvent_value(callback: ((index: number) => void)): void
}
/** @memo */
export function Slider(
  /** @memo */
  style: ((attributes: SliderAttribute) => void) | undefined,
  options?: SliderOptions | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkSliderComponent()
    })
    NodeAttach<ArkSliderPeer>((): ArkSliderPeer => ArkSliderPeer.create(receiver), (_: ArkSliderPeer) => {
        receiver.setSliderOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
