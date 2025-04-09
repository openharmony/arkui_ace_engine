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

import { Edge, Axis, Curve, HitTestMode, ImageSize, Alignment, BorderStyle, ColoringStrategy, HoverEffect, Color, Visibility, ItemAlign, Direction, GradientDirection, ObscuredReasons, RenderFit, ImageRepeat, ResponseType, FunctionKey, ModifierKey, BarState, EdgeEffect, ScrollSource } from "./enums"
import { Length, Dimension, SizeOptions, ConstraintSizeOptions, ChainWeightOptions, Padding, LocalizedPadding, Margin, LocalizedMargin, ResourceColor, Position, BorderOptions, EdgeStyles, EdgeWidths, LocalizedEdgeWidths, EdgeColors, LocalizedEdgeColors, BorderRadiuses, LocalizedBorderRadiuses, OutlineOptions, EdgeOutlineStyles, EdgeOutlineWidths, OutlineRadiuses, Area, Edges, LocalizedEdges, LocalizedPosition, ResourceStr, AccessibilityOptions, VoidCallback } from "./units"
import { RectResult, ICurve, ScrollableCommonMethod, CommonMethod, DrawModifier, Rectangle, Callback_Array_TouchTestInfo_TouchResult, TouchTestInfo, TouchResult, PixelRoundPolicy, BackgroundEffectOptions, ForegroundEffectOptions, VisualEffect, Filter, BorderImageOption, OutlineStyle, Callback_ClickEvent_Void, ClickEvent, Callback_Boolean_HoverEvent_Void, HoverEvent, AccessibilityCallback, Callback_MouseEvent_Void, MouseEvent, Callback_TouchEvent_Void, TouchEvent, Callback_KeyEvent_Void, KeyEvent, Callback_KeyEvent_Boolean, AnimateParam, TransitionOptions, TransitionEffect, MotionBlurOptions, InvertOptions, TranslateOptions, ScaleOptions, RotateOptions, Callback_Area_Area_Void, Literal_Union_Number_Literal_Number_offset_span_lg_md_sm_xs, Literal_Number_offset_span, AlignRuleOption, LocalizedAlignRuleOptions, ClickEffect, Callback_DragEvent_String_Union_CustomBuilder_DragItemInfo, DragEvent, CustomBuilder, DragItemInfo, Callback_DragEvent_String_Void, UniformDataType, Callback_PreDragStatus_Void, PreDragStatus, Type_CommonMethod_linearGradient_value, Tuple_ResourceColor_Number, Type_CommonMethod_sweepGradient_value, Tuple_Length_Length, Type_CommonMethod_radialGradient_value, MotionPathOptions, ShadowOptions, ShadowStyle, ProgressMask, StateStyles, PixelStretchEffectOptions, GestureModifier, BackgroundBrightnessOptions, Callback_GestureInfo_BaseGestureEvent_GestureJudgeResult, GestureRecognizerJudgeBeginCallback, ShouldBuiltInRecognizerParallelWithCallback, Callback_TouchEvent_HitTestMode, SizeChangeCallback, SafeAreaType, SafeAreaEdge, Literal_Alignment_align, BlurStyle, BackgroundBlurStyleOptions, ForegroundBlurStyleOptions, TransitionFinishCallback, BlurOptions, LinearGradientBlurOptions, EffectType, sharedTransitionOptions, ChainStyle, DragPreviewOptions, DragInteractionOptions, ComponentContent, OverlayOptions, BlendMode, BlendApplyType, Blender, GeometryTransitionOptions, PopupOptions, CustomPopupOptions, MenuElement, MenuOptions, ContextMenuOptions, ModalTransition, ContentCoverOptions, SheetOptions, VisibleAreaChangeCallback, NestedScrollOptions, ContentClipMode, EdgeEffectOptions, FadingEdgeOptions } from "./common"
import { Resource } from "global/resource";
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics } from "../Graphics"
import { ScrollSnapAlign, ScrollState } from "./list"
import { ResizableOptions } from "./image"
import { Callback_Void } from "./abilityComponent"
import { FocusBoxStyle, FocusPriority } from "./focus"
import { CircleShape } from "./../generated/ArkCircleShapeMaterialized"
import { EllipseShape } from "./../generated/ArkEllipseShapeMaterialized"
import { PathShape } from "./../generated/ArkPathShapeMaterialized"
import { RectShape } from "./../generated/ArkRectShapeMaterialized"
import { AttributeModifier } from "./../component/common" 
import { GestureInfo, BaseGestureEvent, GestureJudgeResult, GestureType, GestureMask } from "./gesture"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"
import { Callback_Number_Number_Void } from "./grid"
import { ArkScrollComponent } from "./../generated/ArkScroll"
import { ArkScrollPeer } from "./../generated/peers/ArkScrollPeer"
export class ScrollerInternal {
    public static fromPtr(ptr: KPointer): Scroller {
        const obj : Scroller = new Scroller()
        obj.peer = new Finalizable(ptr, Scroller.getFinalizer())
        return obj
    }
}
export class Scroller implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_scroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Scroller_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = Scroller.ctor_scroller()
        this.peer = new Finalizable(ctorPtr, Scroller.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._Scroller_getFinalizer()
    }
    public scrollTo(options: ScrollOptions): undefined {
        const options_casted = options as (ScrollOptions)
        return this.scrollTo_serialize(options_casted)
    }
    public scrollEdge(value: Edge, options?: ScrollEdgeOptions): undefined {
        const value_casted = value as (Edge)
        const options_casted = options as (ScrollEdgeOptions | undefined)
        return this.scrollEdge_serialize(value_casted, options_casted)
    }
    public fling(velocity: number): void {
        const velocity_casted = velocity as (number)
        this.fling_serialize(velocity_casted)
        return
    }
    public scrollPage(value: ScrollPageOptions | Literal_Boolean_next_Axis_direction): undefined {
        const value_type = runtimeType(value)
        if (TypeChecker.isScrollPageOptions(value, true, false)) {
            const value_casted = value as (ScrollPageOptions)
            return this.scrollPage0_serialize(value_casted)
        }
        if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isLiteral_Boolean_next_Axis_direction(value, true, false))) {
            const value_casted = value as (Literal_Boolean_next_Axis_direction)
            return this.scrollPage1_serialize(value_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public currentOffset(): OffsetResult {
        return this.currentOffset_serialize()
    }
    public scrollToIndex(value: number, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): undefined {
        const value_casted = value as (number)
        const smooth_casted = smooth as (boolean | undefined)
        const align_casted = align as (ScrollAlign | undefined)
        const options_casted = options as (ScrollToIndexOptions | undefined)
        return this.scrollToIndex_serialize(value_casted, smooth_casted, align_casted, options_casted)
    }
    public scrollBy(dx: Length, dy: Length): undefined {
        const dx_casted = dx as (Length)
        const dy_casted = dy as (Length)
        return this.scrollBy_serialize(dx_casted, dy_casted)
    }
    public isAtEnd(): boolean {
        return this.isAtEnd_serialize()
    }
    public getItemRect(index: number): RectResult {
        const index_casted = index as (number)
        return this.getItemRect_serialize(index_casted)
    }
    public getItemIndex(x: number, y: number): number {
        const x_casted = x as (number)
        const y_casted = y as (number)
        return this.getItemIndex_serialize(x_casted, y_casted)
    }
    private scrollTo_serialize(options: ScrollOptions): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScrollOptions(options)
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private scrollEdge_serialize(value: Edge, options?: ScrollEdgeOptions): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeScrollEdgeOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollEdge(this.peer!.ptr, value.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private fling_serialize(velocity: number): void {
        ArkUIGeneratedNativeModule._Scroller_fling(this.peer!.ptr, velocity)
    }
    private scrollPage0_serialize(value: ScrollPageOptions): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScrollPageOptions(value)
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollPage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private scrollPage1_serialize(value: Literal_Boolean_next_Axis_direction): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        const value_next  = value.next
        thisSerializer.writeBoolean(value_next)
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        thisSerializer.writeInt8(value_direction_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_direction_type)) {
            const value_direction_value  = (value_direction as Axis)
            thisSerializer.writeInt32(value_direction_value.valueOf())
        }
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollPage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private currentOffset_serialize(): OffsetResult {
        const retval  = ArkUIGeneratedNativeModule._Scroller_currentOffset(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : OffsetResult = retvalDeserializer.readOffsetResult()
        return returnResult
    }
    private scrollToIndex_serialize(value: number, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let smooth_type : int32 = RuntimeType.UNDEFINED
        smooth_type = runtimeType(smooth)
        thisSerializer.writeInt8(smooth_type as int32)
        if ((RuntimeType.UNDEFINED) != (smooth_type)) {
            const smooth_value  = smooth!
            thisSerializer.writeBoolean(smooth_value)
        }
        let align_type : int32 = RuntimeType.UNDEFINED
        align_type = runtimeType(align)
        thisSerializer.writeInt8(align_type as int32)
        if ((RuntimeType.UNDEFINED) != (align_type)) {
            const align_value  = (align as ScrollAlign)
            thisSerializer.writeInt32(align_value.valueOf())
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeScrollToIndexOptions(options_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollToIndex(this.peer!.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private scrollBy_serialize(dx: Length, dy: Length): undefined {
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollBy(this.peer!.ptr, dx, dy)
        return retval
    }
    private isAtEnd_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._Scroller_isAtEnd(this.peer!.ptr)
        return retval
    }
    private getItemRect_serialize(index: number): RectResult {
        const retval  = ArkUIGeneratedNativeModule._Scroller_getItemRect(this.peer!.ptr, index)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : RectResult = retvalDeserializer.readRectResult()
        return returnResult
    }
    private getItemIndex_serialize(x: number, y: number): number {
        const retval  = ArkUIGeneratedNativeModule._Scroller_getItemIndex(this.peer!.ptr, x, y)
        return retval
    }
}
export enum ScrollDirection {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    FREE = 2,
    Free = 2,
    NONE = 3,
    None = 3
}
export enum ScrollAlign {
    START = 0,
    CENTER = 1,
    END = 2,
    AUTO = 3
}
export interface OffsetResult {
    xOffset: number;
    yOffset: number;
}
export interface ScrollEdgeOptions {
    velocity?: number;
}
export interface ScrollToIndexOptions {
    extraOffset?: LengthMetrics;
}
export interface ScrollAnimationOptions {
    duration?: number;
    curve?: Curve | ICurve;
    canOverScroll?: boolean;
}
export interface OffsetOptions {
    xOffset?: Dimension;
    yOffset?: Dimension;
}
export interface Literal_Boolean_next_Axis_direction {
    next: boolean;
    direction?: Axis;
}
export interface ScrollOptions {
    xOffset: number | string;
    yOffset: number | string;
    animation?: ScrollAnimationOptions | boolean;
}
export interface ScrollPageOptions {
    next: boolean;
    animation?: boolean;
}
export interface ScrollSnapOptions {
    snapAlign: ScrollSnapAlign;
    snapPagination?: Dimension | Array<Dimension>;
    enableSnapToStart?: boolean;
    enableSnapToEnd?: boolean;
}
export type OnScrollEdgeCallback = (side: Edge) => void;
export interface OnScrollFrameBeginHandlerResult {
    offsetRemain: number;
}
export type OnScrollFrameBeginCallback = (offset: number, state: ScrollState) => OnScrollFrameBeginHandlerResult;
export type ScrollOnScrollCallback = (xOffset: number, yOffset: number, scrollState: ScrollState) => void;
export type ScrollOnWillScrollCallback = (xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => OffsetResult;
/** @memo:stable */
export interface ScrollAttribute extends ScrollableCommonMethod {
    /** @memo */
    setScrollOptions(scroller?: Scroller): this
    /** @memo */
    scrollable(value: ScrollDirection): this
    /** @memo */
    onScroll(value: ((first: number,last: number) => void)): this
    /** @memo */
    onWillScroll(value?: ScrollOnWillScrollCallback): this
    /** @memo */
    onDidScroll(value: ScrollOnScrollCallback): this
    /** @memo */
    onScrollEdge(value: OnScrollEdgeCallback): this
    /** @memo */
    onScrollStart(value: VoidCallback): this
    /** @memo */
    onScrollEnd(value: (() => void)): this
    /** @memo */
    onScrollStop(value: VoidCallback): this
    /** @memo */
    scrollBar(value: BarState): this
    /** @memo */
    scrollBarColor(value: Color | number | string): this
    /** @memo */
    scrollBarWidth(value: number | string): this
    /** @memo */
    onScrollFrameBegin(value: OnScrollFrameBeginCallback): this
    /** @memo */
    nestedScroll(value: NestedScrollOptions): this
    /** @memo */
    enableScrollInteraction(value: boolean): this
    /** @memo */
    friction(value: number | Resource): this
    /** @memo */
    scrollSnap(value: ScrollSnapOptions): this
    /** @memo */
    enablePaging(value: boolean): this
    /** @memo */
    initialOffset(value: OffsetOptions): this
    /** @memo */
    edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this
}
/** @memo */
export function Scroll(
  /** @memo */
  style: ((attributes: ScrollAttribute) => void) | undefined,
  scroller?: Scroller | undefined, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkScrollComponent()
    })
    NodeAttach<ArkScrollPeer>((): ArkScrollPeer => ArkScrollPeer.create(receiver), (_: ArkScrollPeer) => {
        receiver.setScrollOptions(scroller)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
