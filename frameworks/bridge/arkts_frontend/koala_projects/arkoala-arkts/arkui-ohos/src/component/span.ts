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
import { ResourceColor, Dimension, BorderRadiuses, Length, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, Font } from "./units"
import { CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback } from "./common"
import { HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, Axis, ResponseType, FunctionKey, ModifierKey, FontStyle, FontWeight, TextCase } from "./enums"
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
import { DecorationStyleInterface } from "./styledString"
import { ArkSpanComponent } from "./../generated/ArkSpan"
import { ArkSpanPeer } from "./../generated/peers/ArkSpanPeer"
export interface TextBackgroundStyle {
    color?: ResourceColor;
    radius?: Dimension | BorderRadiuses;
}
/** @memo:stable */
export interface BaseSpan extends CommonMethod {
    /** @memo */
    textBackgroundStyle(value: TextBackgroundStyle): this
    /** @memo */
    baselineOffset(value: LengthMetrics): this
}
/** @memo:stable */
export interface SpanAttribute extends BaseSpan {
    /** @memo */
    setSpanOptions(value: string | Resource): this
    /** @memo */
    font(value: Font): this
    /** @memo */
    fontColor(value: ResourceColor): this
    /** @memo */
    fontSize(value: number | string | Resource): this
    /** @memo */
    fontStyle(value: FontStyle): this
    /** @memo */
    fontWeight(value: number | FontWeight | string): this
    /** @memo */
    fontFamily(value: string | Resource): this
    /** @memo */
    decoration(value: DecorationStyleInterface): this
    /** @memo */
    letterSpacing(value: number | string): this
    /** @memo */
    textCase(value: TextCase): this
    /** @memo */
    lineHeight(value: Length): this
    /** @memo */
    textShadow(value: ShadowOptions | Array<ShadowOptions>): this
}
// /** @memo */
// export function BaseSpan(
//   /** @memo */
//   style: ((attributes: BaseSpanAttribute) => void) | undefined,
  
//   /** @memo */
//   content_?: () => void,
// ) {
//     const receiver = remember(() => {
//         return new ArkBaseSpanComponent()
//     })
//     NodeAttach<ArkBaseSpanPeer>((): ArkBaseSpanPeer => ArkBaseSpanPeer.create(receiver), (_: ArkBaseSpanPeer) => {
        
//         style?.(receiver)
//         content_?.()
//         receiver.applyAttributesFinish()
//     })
// }
/** @memo */
export function Span(
  /** @memo */
  style: ((attributes: SpanAttribute) => void) | undefined,
  value: string | Resource, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkSpanComponent()
    })
    NodeAttach<ArkSpanPeer>((): ArkSpanPeer => ArkSpanPeer.create(receiver), (_: ArkSpanPeer) => {
        receiver.setSpanOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
