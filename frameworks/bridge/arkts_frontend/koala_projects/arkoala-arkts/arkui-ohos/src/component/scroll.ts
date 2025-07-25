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
import { RectResult, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, EdgeEffectOptions, ICurve, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod } from "./common"
import { Resource } from "global/resource"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Callback_Number_Number_Void } from "./grid"
import { ScrollState, ScrollSnapAlign } from "./list"
import { NodeAttach, remember } from "@koalaui/runtime"
import { LengthMetrics } from "../Graphics"

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
    public scrollPage(value: ScrollPageOptions): void {
        const value_type = runtimeType(value)
        if (TypeChecker.isScrollPageOptions(value, true, false)) {
            const value_casted = value as (ScrollPageOptions)
            this.scrollPage0_serialize(value_casted)
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
    public scrollBy(dx: Length | undefined, dy: Length | undefined): void {
        const dx_casted = dx as (Length | undefined)
        const dy_casted = dy as (Length | undefined)
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
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollEdge(this.peer!.ptr, TypeChecker.Edge_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
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
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_direction_value))
        }
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollPage1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private currentOffset_serialize(): OffsetResult {
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._Scroller_currentOffset(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
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
            thisSerializer.writeInt32(TypeChecker.ScrollAlign_ToNumeric(align_value))
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
    private scrollBy_serialize(dx: Length | undefined, dy: Length | undefined): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let dx_type : int32 = RuntimeType.UNDEFINED
        dx_type = runtimeType(dx)
        thisSerializer.writeInt8(dx_type as int32)
        if ((RuntimeType.UNDEFINED) != (dx_type)) {
            const dx_value  = dx!
            thisSerializer.writeLength(dx_value)
        }

        let dy_type : int32 = RuntimeType.UNDEFINED
        dy_type = runtimeType(dy)
        thisSerializer.writeInt8(dy_type as int32)
        if ((RuntimeType.UNDEFINED) != (dy_type)) {
            const dy_value  = dy!
            thisSerializer.writeLength(dy_value)
        }
        const retval  = ArkUIGeneratedNativeModule._Scroller_scrollBy(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private isAtEnd_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._Scroller_isAtEnd(this.peer!.ptr)
        return retval
    }
    private getItemRect_serialize(index: number): RectResult {
        // @ts-ignore
        const retval = ArkUIGeneratedNativeModule._Scroller_getItemRect(this.peer!.ptr, index) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkScrollPeer {
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
    scrollableAttribute(value: ScrollDirection | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ScrollDirection)
            thisSerializer.writeInt32(TypeChecker.ScrollDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
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
    onDidScrollAttribute(value: ScrollOnScrollCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollEdgeAttribute(value: OnScrollEdgeCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollEndAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarAttribute(value: BarState | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarState)
            thisSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarColorAttribute(value: Color | number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNestedScrollOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_enableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    frictionAttribute(value: number | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as Resource
                thisSerializer.writeResource(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollSnapAttribute(value: ScrollSnapOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeScrollSnapOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollSnap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePagingAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_enablePaging(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    initialOffsetAttribute(value: OffsetOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeOffsetOptions(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_initialOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let edgeEffect_type : int32 = RuntimeType.UNDEFINED
        edgeEffect_type = runtimeType(edgeEffect)
        thisSerializer.writeInt8(edgeEffect_type as int32)
        if ((RuntimeType.UNDEFINED) != (edgeEffect_type)) {
            const edgeEffect_value  = (edgeEffect as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(edgeEffect_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeEdgeEffectOptions(options_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_edgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export type ScrollInterface = (scroller?: Scroller) => ScrollAttribute;
export type OnScrollEdgeCallback = (side: Edge) => void;
export interface OnScrollFrameBeginHandlerResult {
    offsetRemain: number;
}
export type OnScrollFrameBeginCallback = (offset: number, state: ScrollState) => OnScrollFrameBeginHandlerResult;
export interface ScrollAttribute extends ScrollableCommonMethod {
    scrollable(value: ScrollDirection | undefined): this
    onScroll(value: ((first: number,last: number) => void) | undefined): this
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this
    onDidScroll(value: ScrollOnScrollCallback | undefined): this
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this
    onScrollStart(value: VoidCallback | undefined): this
    onScrollEnd(value: (() => void) | undefined): this
    onScrollStop(value: VoidCallback | undefined): this
    scrollBar(value: BarState | undefined): this
    scrollBarColor(value: Color | number | string | undefined): this
    scrollBarWidth(value: number | string | undefined): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: number | Resource | undefined): this
    scrollSnap(value: ScrollSnapOptions | undefined): this
    enablePaging(value: boolean | undefined): this
    initialOffset(value: OffsetOptions | undefined): this
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this
}
export class ArkScrollStyle extends ArkScrollableCommonMethodStyle implements ScrollAttribute {
    scrollable_value?: ScrollDirection | undefined
    onScroll_value?: ((first: number,last: number) => void) | undefined
    onWillScroll_value?: ScrollOnWillScrollCallback | undefined
    onDidScroll_value?: ScrollOnScrollCallback | undefined
    onScrollEdge_value?: OnScrollEdgeCallback | undefined
    onScrollStart_value?: VoidCallback | undefined
    onScrollEnd_value?: (() => void) | undefined
    onScrollStop_value?: VoidCallback | undefined
    scrollBar_value?: BarState | undefined
    scrollBarColor_value?: Color | number | string | undefined
    scrollBarWidth_value?: number | string | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    nestedScroll_value?: NestedScrollOptions | undefined
    enableScrollInteraction_value?: boolean | undefined
    friction_value?: number | Resource | undefined
    scrollSnap_value?: ScrollSnapOptions | undefined
    enablePaging_value?: boolean | undefined
    initialOffset_value?: OffsetOptions | undefined
    public scrollable(value: ScrollDirection | undefined): this {
        return this
    }
    public onScroll(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        return this
    }
    public onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        return this
    }
    public onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        return this
    }
    public onScrollStart(value: VoidCallback | undefined): this {
        return this
    }
    public onScrollEnd(value: (() => void) | undefined): this {
        return this
    }
    public onScrollStop(value: VoidCallback | undefined): this {
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        return this
    }
    public scrollBarWidth(value: number | string | undefined): this {
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        return this
    }
    public friction(value: number | Resource | undefined): this {
        return this
    }
    public scrollSnap(value: ScrollSnapOptions | undefined): this {
        return this
    }
    public enablePaging(value: boolean | undefined): this {
        return this
    }
    public initialOffset(value: OffsetOptions | undefined): this {
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        return this
        }
}
export type ScrollOnScrollCallback = (xOffset: number, yOffset: number, scrollState: ScrollState) => void;
export type ScrollOnWillScrollCallback = (xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => OffsetResult;
export class ArkScrollComponent extends ArkScrollableCommonMethodComponent implements ScrollAttribute {
    getPeer(): ArkScrollPeer {
        return (this.peer as ArkScrollPeer)
    }
    public setScrollOptions(scroller?: Scroller): this {
        if (this.checkPriority("setScrollOptions")) {
            const scroller_casted = scroller as (Scroller | undefined)
            this.getPeer()?.setScrollOptionsAttribute(scroller_casted)
            return this
        }
        return this
    }
    public scrollable(value: ScrollDirection | undefined): this {
        if (this.checkPriority("scrollable")) {
            const value_casted = value as (ScrollDirection | undefined)
            this.getPeer()?.scrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public onScroll(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onScroll")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (ScrollOnWillScrollCallback | undefined)
            this.getPeer()?.onWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (ScrollOnScrollCallback | undefined)
            this.getPeer()?.onDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        if (this.checkPriority("onScrollEdge")) {
            const value_casted = value as (OnScrollEdgeCallback | undefined)
            this.getPeer()?.onScrollEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStart(value: VoidCallback | undefined): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollEnd(value: (() => void) | undefined): this {
        if (this.checkPriority("onScrollEnd")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onScrollEndAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: VoidCallback | undefined): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.onScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.scrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string | undefined)
            this.getPeer()?.scrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarWidth(value: number | string | undefined): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.scrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (OnScrollFrameBeginCallback | undefined)
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | undefined)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    public friction(value: number | Resource | undefined): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollSnap(value: ScrollSnapOptions | undefined): this {
        if (this.checkPriority("scrollSnap")) {
            const value_casted = value as (ScrollSnapOptions | undefined)
            this.getPeer()?.scrollSnapAttribute(value_casted)
            return this
        }
        return this
    }
    public enablePaging(value: boolean | undefined): this {
        if (this.checkPriority("enablePaging")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enablePagingAttribute(value_casted)
            return this
        }
        return this
    }
    public initialOffset(value: OffsetOptions | undefined): this {
        if (this.checkPriority("initialOffset")) {
            const value_casted = value as (OffsetOptions | undefined)
            this.getPeer()?.initialOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const edgeEffect_casted = edgeEffect as (EdgeEffect | undefined)
            const options_casted = options as (EdgeEffectOptions)
            this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Scroll(
    /** @memo */
    style: ((attributes: ScrollAttribute) => void) | undefined,
    scroller?: Scroller,
    /** @memo */
    content_?: (() => void) | undefined,
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
