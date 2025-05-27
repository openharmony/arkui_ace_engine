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

import { Edge, Axis, ScrollSource, BarState, Color, EdgeEffect, Curve } from "./enums"
import { Length, VoidCallback, Dimension } from "./units"
import { RectResult, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, EdgeEffectOptions, ICurve, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, UIScrollableCommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, UICommonMethod } from "./common"
import { Resource } from "./resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Callback_Number_Number_Void } from "./grid"
import { ScrollState, ScrollSnapAlign } from "./list"
import { Callback_Void } from "./ability_component"
import { LengthMetrics } from "./arkui-graphics"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    public scrollTo(options: ScrollOptions): void {
        const options_casted = options as (ScrollOptions)
        this.scrollTo_serialize(options_casted)
        return
    }
    public scrollEdge(value: Edge, options?: ScrollEdgeOptions): void {
        const value_casted = value as (Edge)
        const options_casted = options as (ScrollEdgeOptions | undefined)
        this.scrollEdge_serialize(value_casted, options_casted)
        return
    }
    public fling(velocity: number): void {
        const velocity_casted = velocity as (number)
        this.fling_serialize(velocity_casted)
        return
    }
    public scrollPage(value: ScrollPageOptions | Literal_Boolean_next_Axis_direction): void {
        const value_type = runtimeType(value)
        if (TypeChecker.isScrollPageOptions(value, true, false)) {
            const value_casted = value as (ScrollPageOptions)
            this.scrollPage0_serialize(value_casted)
            return
        }
        if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isLiteral_Boolean_next_Axis_direction(value, true, false))) {
            const value_casted = value as (Literal_Boolean_next_Axis_direction)
            this.scrollPage1_serialize(value_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public currentOffset(): OffsetResult {
        return this.currentOffset_serialize()
    }
    public scrollToIndex(value: number, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): void {
        const value_casted = value as (number)
        const smooth_casted = smooth as (boolean | undefined)
        const align_casted = align as (ScrollAlign | undefined)
        const options_casted = options as (ScrollToIndexOptions | undefined)
        this.scrollToIndex_serialize(value_casted, smooth_casted, align_casted, options_casted)
        return
    }
    public scrollBy(dx: Length, dy: Length): void {
        const dx_casted = dx as (Length)
        const dy_casted = dy as (Length)
        this.scrollBy_serialize(dx_casted, dy_casted)
        return
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
    private scrollTo_serialize(options: ScrollOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScrollOptions(options)
        ArkUIGeneratedNativeModule._Scroller_scrollTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private scrollEdge_serialize(value: Edge, options?: ScrollEdgeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeScrollEdgeOptions(options_value)
        }
        ArkUIGeneratedNativeModule._Scroller_scrollEdge(this.peer!.ptr, TypeChecker.Edge_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private fling_serialize(velocity: number): void {
        ArkUIGeneratedNativeModule._Scroller_fling(this.peer!.ptr, velocity)
    }
    private scrollPage0_serialize(value: ScrollPageOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScrollPageOptions(value)
        ArkUIGeneratedNativeModule._Scroller_scrollPage0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private scrollPage1_serialize(value: Literal_Boolean_next_Axis_direction): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_next  = value.next
        thisSerializer.writeBoolean(value_next)
        const value_direction  = value.direction
        let value_direction_type : int32 = RuntimeType.UNDEFINED
        value_direction_type = runtimeType(value_direction)
        thisSerializer.writeInt8(value_direction_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_direction_type)) {
            const value_direction_value  = (value_direction as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_direction_value))
        }
        ArkUIGeneratedNativeModule._Scroller_scrollPage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private currentOffset_serialize(): OffsetResult {
        const retval  = ArkUIGeneratedNativeModule._Scroller_currentOffset(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const returnResult : OffsetResult = retvalDeserializer.readOffsetResult()
        return returnResult
    }
    private scrollToIndex_serialize(value: number, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): void {
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
            thisSerializer.writeInt32(TypeChecker.ScrollAlign_ToNumeric(align_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeScrollToIndexOptions(options_value)
        }
        ArkUIGeneratedNativeModule._Scroller_scrollToIndex(this.peer!.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private scrollBy_serialize(dx: Length, dy: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let dx_type : int32 = RuntimeType.UNDEFINED
        dx_type = runtimeType(dx)
        if (RuntimeType.STRING == dx_type) {
            thisSerializer.writeInt8(0 as int32)
            const dx_0  = dx as string
            thisSerializer.writeString(dx_0)
        }
        else if (RuntimeType.NUMBER == dx_type) {
            thisSerializer.writeInt8(1 as int32)
            const dx_1  = dx as number
            thisSerializer.writeNumber(dx_1)
        }
        else if (RuntimeType.OBJECT == dx_type) {
            thisSerializer.writeInt8(2 as int32)
            const dx_2  = dx as Resource
            thisSerializer.writeResource(dx_2)
        }
        let dy_type : int32 = RuntimeType.UNDEFINED
        dy_type = runtimeType(dy)
        if (RuntimeType.STRING == dy_type) {
            thisSerializer.writeInt8(0 as int32)
            const dy_0  = dy as string
            thisSerializer.writeString(dy_0)
        }
        else if (RuntimeType.NUMBER == dy_type) {
            thisSerializer.writeInt8(1 as int32)
            const dy_1  = dy as number
            thisSerializer.writeNumber(dy_1)
        }
        else if (RuntimeType.OBJECT == dy_type) {
            thisSerializer.writeInt8(2 as int32)
            const dy_2  = dy as Resource
            thisSerializer.writeResource(dy_2)
        }
        ArkUIGeneratedNativeModule._Scroller_scrollBy(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
export class ArkScrollPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScrollPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Scroll_construct(peerId, flags)
        const _peer  = new ArkScrollPeer(_peerPtr, peerId, "Scroll", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setScrollOptionsAttribute(scroller?: Scroller): void {
        const thisSerializer : Serializer = Serializer.hold()
        let scroller_type : int32 = RuntimeType.UNDEFINED
        scroller_type = runtimeType(scroller)
        thisSerializer.writeInt8(scroller_type as int32)
        if ((RuntimeType.UNDEFINED) != (scroller_type)) {
            const scroller_value  = scroller!
            thisSerializer.writeScroller(scroller_value)
        }
        ArkUIGeneratedNativeModule._ScrollInterface_setScrollOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollableAttribute(value: ScrollDirection): void {
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollable(this.peer.ptr, TypeChecker.ScrollDirection_ToNumeric(value))
    }
    onScrollAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillScrollAttribute(value: ScrollOnWillScrollCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: ScrollOnScrollCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollEdgeAttribute(value: OnScrollEdgeCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollEndAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: VoidCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarAttribute(value: BarState): void {
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBar(this.peer.ptr, TypeChecker.BarState_ToNumeric(value))
    }
    scrollBarColorAttribute(value: Color | number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarWidthAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ScrollAttribute_enableScrollInteraction(this.peer.ptr, value ? 1 : 0)
    }
    frictionAttribute(value: number | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollSnapAttribute(value: ScrollSnapOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeScrollSnapOptions(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollSnap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePagingAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._ScrollAttribute_enablePaging(this.peer.ptr, value ? 1 : 0)
    }
    initialOffsetAttribute(value: OffsetOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeOffsetOptions(value)
        ArkUIGeneratedNativeModule._ScrollAttribute_initialOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_edgeEffect(this.peer.ptr, TypeChecker.EdgeEffect_ToNumeric(edgeEffect), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
export interface ScrollAttribute extends ScrollableCommonMethod {
    scrollable(value: ScrollDirection): this
    onScroll(value: ((first: number,last: number) => void)): this
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this
    onDidScroll(value: ScrollOnScrollCallback): this
    onScrollEdge(value: OnScrollEdgeCallback): this
    onScrollStart(value: VoidCallback): this
    onScrollEnd(value: (() => void)): this
    onScrollStop(value: VoidCallback): this
    scrollBar(value: BarState): this
    scrollBarColor(value: Color | number | string): this
    scrollBarWidth(value: number | string): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback): this
    nestedScroll(value: NestedScrollOptions): this
    enableScrollInteraction(value: boolean): this
    friction(value: number | Resource): this
    scrollSnap(value: ScrollSnapOptions): this
    enablePaging(value: boolean): this
    initialOffset(value: OffsetOptions): this
    edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this
    attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIScrollAttribute extends UIScrollableCommonMethod {
    /** @memo */
    scrollable(value: ScrollDirection): this
    /** @memo */
    onScroll(value: ((first: number,last: number) => void)): this
    /** @memo */
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this
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
    /** @memo */
    attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkScrollStyle extends ArkScrollableCommonMethodStyle implements ScrollAttribute {
    scrollable_value?: ScrollDirection
    onScroll_value?: ((first: number,last: number) => void)
    onWillScroll_value?: ScrollOnWillScrollCallback | undefined
    onDidScroll_value?: ScrollOnScrollCallback
    onScrollEdge_value?: OnScrollEdgeCallback
    onScrollStart_value?: VoidCallback
    onScrollEnd_value?: (() => void)
    onScrollStop_value?: VoidCallback
    scrollBar_value?: BarState
    scrollBarColor_value?: Color | number | string
    scrollBarWidth_value?: number | string
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    scrollSnap_value?: ScrollSnapOptions
    enablePaging_value?: boolean
    initialOffset_value?: OffsetOptions
    public scrollable(value: ScrollDirection): this {
        return this
    }
    public onScroll(value: ((first: number,last: number) => void)): this {
        return this
    }
    public onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        return this
    }
    public onDidScroll(value: ScrollOnScrollCallback): this {
        return this
    }
    public onScrollEdge(value: OnScrollEdgeCallback): this {
        return this
    }
    public onScrollStart(value: VoidCallback): this {
        return this
    }
    public onScrollEnd(value: (() => void)): this {
        return this
    }
    public onScrollStop(value: VoidCallback): this {
        return this
    }
    public scrollBar(value: BarState): this {
        return this
    }
    public scrollBarColor(value: Color | number | string): this {
        return this
    }
    public scrollBarWidth(value: number | string): this {
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback): this {
        return this
    }
    public nestedScroll(value: NestedScrollOptions): this {
        return this
    }
    public enableScrollInteraction(value: boolean): this {
        return this
    }
    public friction(value: number | Resource): this {
        return this
    }
    public scrollSnap(value: ScrollSnapOptions): this {
        return this
    }
    public enablePaging(value: boolean): this {
        return this
    }
    public initialOffset(value: OffsetOptions): this {
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export type ScrollOnScrollCallback = (xOffset: number, yOffset: number, scrollState: ScrollState) => void;
export type ScrollOnWillScrollCallback = (xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => OffsetResult;
/** @memo:stable */
export class ArkScrollComponent extends ArkScrollableCommonMethodComponent implements UIScrollAttribute {
    getPeer(): ArkScrollPeer {
        return (this.peer as ArkScrollPeer)
    }
    /** @memo */
    public setScrollOptions(scroller?: Scroller): this {
        if (this.checkPriority("setScrollOptions")) {
            const scroller_casted = scroller as (Scroller | undefined)
            this.getPeer()?.setScrollOptionsAttribute(scroller_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollable(value: ScrollDirection): this {
        if (this.checkPriority("scrollable")) {
            const value_casted = value as (ScrollDirection)
            this.getPeer()?.scrollableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScroll(value: ((first: number,last: number) => void)): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number,last: number) => void))
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (ScrollOnWillScrollCallback | undefined)
            this.getPeer()?.onWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDidScroll(value: ScrollOnScrollCallback): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (ScrollOnScrollCallback)
            this.getPeer()?.onDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollEdge(value: OnScrollEdgeCallback): this {
        if (this.checkPriority("onScrollEdge")) {
            const value_casted = value as (OnScrollEdgeCallback)
            this.getPeer()?.onScrollEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStart(value: VoidCallback): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollEnd(value: (() => void)): this {
        if (this.checkPriority("onScrollEnd")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onScrollEndAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollStop(value: VoidCallback): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as (VoidCallback)
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBar(value: BarState): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarColor(value: Color | number | string): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string)
            this.getPeer()?.scrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollBarWidth(value: number | string): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.scrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (OnScrollFrameBeginCallback)
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nestedScroll(value: NestedScrollOptions): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enableScrollInteraction(value: boolean): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public friction(value: number | Resource): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public scrollSnap(value: ScrollSnapOptions): this {
        if (this.checkPriority("scrollSnap")) {
            const value_casted = value as (ScrollSnapOptions)
            this.getPeer()?.scrollSnapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public enablePaging(value: boolean): this {
        if (this.checkPriority("enablePaging")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enablePagingAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public initialOffset(value: OffsetOptions): this {
        if (this.checkPriority("initialOffset")) {
            const value_casted = value as (OffsetOptions)
            this.getPeer()?.initialOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public edgeEffect(edgeEffect: EdgeEffect, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const edgeEffect_casted = edgeEffect as (EdgeEffect)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkScroll(
    /** @memo */
    style: ((attributes: UIScrollAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    scroller?: Scroller,
): void {
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
