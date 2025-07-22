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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { RectResult_serializer, RectResult, NestedScrollOptions_serializer, EdgeEffectOptions_serializer, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, CommonMethod, EdgeEffectOptions, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkScrollableCommonMethodSet, ArkCommonMethodSet } from "./common"
import { Edge, ScrollSource, BarState, Color, EdgeEffect } from "./enums"
import { Length, VoidCallback, Dimension } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ScrollState, ScrollSnapAlign } from "./list"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { LengthMetrics, LengthMetrics_serializer } from "./../generated/arkui.Graphics"
import { curves, curves_ICurve_serializer } from "./../generated/ohos.curves"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ScrollerInternal {
    public static fromPtr(ptr: KPointer): Scroller {
        return new Scroller(ptr)
    }
}
export class Scroller implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, Scroller.getFinalizer())
    }
    constructor() {
        this(Scroller.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Scroller_construct()
        return retval
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
        const value_casted = value as (ScrollPageOptions)
        this.scrollPage_serialize(value_casted)
        return
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ScrollOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._Scroller_scrollTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private scrollEdge_serialize(value: Edge, options?: ScrollEdgeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            ScrollEdgeOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._Scroller_scrollEdge(this.peer!.ptr, TypeChecker.Edge_ToNumeric(value), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private fling_serialize(velocity: number): void {
        ArkUIGeneratedNativeModule._Scroller_fling(this.peer!.ptr, velocity)
    }
    private scrollPage_serialize(value: ScrollPageOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ScrollPageOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._Scroller_scrollPage(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private currentOffset_serialize(): OffsetResult {
        const retval  = ArkUIGeneratedNativeModule._Scroller_currentOffset(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : OffsetResult = OffsetResult_serializer.read(retvalDeserializer)
        return returnResult
    }
    private scrollToIndex_serialize(value: number, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let smooth_type : int32 = RuntimeType.UNDEFINED
        smooth_type = runtimeType(smooth)
        thisSerializer.writeInt8((smooth_type).toChar())
        if ((smooth_type) != (RuntimeType.UNDEFINED)) {
            const smooth_value  = smooth!
            thisSerializer.writeBoolean(smooth_value)
        }
        let align_type : int32 = RuntimeType.UNDEFINED
        align_type = runtimeType(align)
        thisSerializer.writeInt8((align_type).toChar())
        if ((align_type) != (RuntimeType.UNDEFINED)) {
            const align_value  = (align as ScrollAlign)
            thisSerializer.writeInt32(TypeChecker.ScrollAlign_ToNumeric(align_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            ScrollToIndexOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._Scroller_scrollToIndex(this.peer!.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private scrollBy_serialize(dx: Length, dy: Length): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let dx_type : int32 = RuntimeType.UNDEFINED
        dx_type = runtimeType(dx)
        if (RuntimeType.STRING == dx_type) {
            thisSerializer.writeInt8((0).toChar())
            const dx_0  = dx as string
            thisSerializer.writeString(dx_0)
        }
        else if (RuntimeType.NUMBER == dx_type) {
            thisSerializer.writeInt8((1).toChar())
            const dx_1  = dx as number
            thisSerializer.writeNumber(dx_1)
        }
        else if (RuntimeType.OBJECT == dx_type) {
            thisSerializer.writeInt8((2).toChar())
            const dx_2  = dx as Resource
            Resource_serializer.write(thisSerializer, dx_2)
        }
        let dy_type : int32 = RuntimeType.UNDEFINED
        dy_type = runtimeType(dy)
        if (RuntimeType.STRING == dy_type) {
            thisSerializer.writeInt8((0).toChar())
            const dy_0  = dy as string
            thisSerializer.writeString(dy_0)
        }
        else if (RuntimeType.NUMBER == dy_type) {
            thisSerializer.writeInt8((1).toChar())
            const dy_1  = dy as number
            thisSerializer.writeNumber(dy_1)
        }
        else if (RuntimeType.OBJECT == dy_type) {
            thisSerializer.writeInt8((2).toChar())
            const dy_2  = dy as Resource
            Resource_serializer.write(thisSerializer, dy_2)
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
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : RectResult = RectResult_serializer.read(retvalDeserializer)
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let scroller_type : int32 = RuntimeType.UNDEFINED
        scroller_type = runtimeType(scroller)
        thisSerializer.writeInt8((scroller_type).toChar())
        if ((scroller_type) != (RuntimeType.UNDEFINED)) {
            const scroller_value  = scroller!
            Scroller_serializer.write(thisSerializer, scroller_value)
        }
        ArkUIGeneratedNativeModule._ScrollInterface_setScrollOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollableAttribute(value: ScrollDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as ScrollDirection)
            thisSerializer.writeInt32(TypeChecker.ScrollDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillScrollAttribute(value: ScrollOnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidScrollAttribute(value: ScrollOnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollEdgeAttribute(value: OnScrollEdgeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnScrollEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollStartAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollStopAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarAttribute(value: BarState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as BarState)
            thisSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarColorAttribute(value: Color | number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNestedScrollAttribute(value: NestedScrollOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            NestedScrollOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableScrollInteractionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setEnableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFrictionAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setFriction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollSnapAttribute(value: ScrollSnapOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ScrollSnapOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollSnap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnablePagingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setEnablePaging(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInitialOffsetAttribute(value: OffsetOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            OffsetOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setInitialOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeEffectAttribute(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let edgeEffect_type : int32 = RuntimeType.UNDEFINED
        edgeEffect_type = runtimeType(edgeEffect)
        thisSerializer.writeInt8((edgeEffect_type).toChar())
        if ((edgeEffect_type) != (RuntimeType.UNDEFINED)) {
            const edgeEffect_value  = (edgeEffect as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(edgeEffect_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            EdgeEffectOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setEdgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ScrollDirection {
    VERTICAL = 0,
    Vertical = 0,
    HORIZONTAL = 1,
    Horizontal = 1,
    NONE = 2,
    None = 2
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
    curve?: curves.Curve | curves.ICurve;
    canOverScroll?: boolean;
}
export interface OffsetOptions {
    xOffset?: Dimension;
    yOffset?: Dimension;
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
    scrollable(value: ScrollDirection | undefined): this {
        throw new Error("Unimplemented method scrollable")
    }
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        throw new Error("Unimplemented method onWillScroll")
    }
    onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        throw new Error("Unimplemented method onDidScroll")
    }
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        throw new Error("Unimplemented method onScrollEdge")
    }
    onScrollStart(value: VoidCallback | undefined): this
    onScrollStop(value: VoidCallback | undefined): this
    scrollBar(value: BarState | undefined): this
    scrollBarColor(value: Color | number | string | undefined): this
    scrollBarWidth(value: number | string | undefined): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        throw new Error("Unimplemented method onScrollFrameBegin")
    }
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: number | Resource | undefined): this
    scrollSnap(value: ScrollSnapOptions | undefined): this {
        throw new Error("Unimplemented method scrollSnap")
    }
    enablePaging(value: boolean | undefined): this {
        throw new Error("Unimplemented method enablePaging")
    }
    initialOffset(value: OffsetOptions | undefined): this {
        throw new Error("Unimplemented method initialOffset")
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        throw new Error("Unimplemented method edgeEffect")
    }
    attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkScrollStyle extends ArkScrollableCommonMethodStyle implements ScrollAttribute {
    scrollable_value?: ScrollDirection | undefined
    onWillScroll_value?: ScrollOnWillScrollCallback | undefined
    onDidScroll_value?: ScrollOnScrollCallback | undefined
    onScrollEdge_value?: OnScrollEdgeCallback | undefined
    onScrollStart_value?: VoidCallback | undefined
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
    attributeModifier_value?: AttributeModifier<ScrollAttribute> | AttributeModifier<CommonMethod> | undefined
    public scrollable(value: ScrollDirection | undefined): this {
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
    public attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: ScrollAttribute): void {
        super.apply(target)
        if (this.scrollable_value !== undefined)
            target.scrollable(this.scrollable_value!)
        if (this.onWillScroll_value !== undefined)
            target.onWillScroll(this.onWillScroll_value!)
        if (this.onDidScroll_value !== undefined)
            target.onDidScroll(this.onDidScroll_value!)
        if (this.onScrollEdge_value !== undefined)
            target.onScrollEdge(this.onScrollEdge_value!)
        if (this.onScrollStart_value !== undefined)
            target.onScrollStart(this.onScrollStart_value!)
        if (this.onScrollStop_value !== undefined)
            target.onScrollStop(this.onScrollStop_value!)
        if (this.scrollBar_value !== undefined)
            target.scrollBar(this.scrollBar_value!)
        if (this.scrollBarColor_value !== undefined)
            target.scrollBarColor(this.scrollBarColor_value!)
        if (this.scrollBarWidth_value !== undefined)
            target.scrollBarWidth(this.scrollBarWidth_value!)
        if (this.onScrollFrameBegin_value !== undefined)
            target.onScrollFrameBegin(this.onScrollFrameBegin_value!)
        if (this.nestedScroll_value !== undefined)
            target.nestedScroll(this.nestedScroll_value!)
        if (this.enableScrollInteraction_value !== undefined)
            target.enableScrollInteraction(this.enableScrollInteraction_value!)
        if (this.friction_value !== undefined)
            target.friction(this.friction_value!)
        if (this.scrollSnap_value !== undefined)
            target.scrollSnap(this.scrollSnap_value!)
        if (this.enablePaging_value !== undefined)
            target.enablePaging(this.enablePaging_value!)
        if (this.initialOffset_value !== undefined)
            target.initialOffset(this.initialOffset_value!)
    }
}
export type ScrollOnScrollCallback = (xOffset: number, yOffset: number, scrollState: ScrollState) => void;
export type ScrollOnWillScrollCallback = (xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => OffsetResult | undefined;

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
            this.getPeer()?.setScrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (ScrollOnWillScrollCallback | undefined)
            this.getPeer()?.setOnWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (ScrollOnScrollCallback | undefined)
            this.getPeer()?.setOnDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        if (this.checkPriority("onScrollEdge")) {
            const value_casted = value as (OnScrollEdgeCallback | undefined)
            this.getPeer()?.setOnScrollEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStart(value: VoidCallback | undefined): this {
        if (this.checkPriority("onScrollStart")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: VoidCallback | undefined): this {
        if (this.checkPriority("onScrollStop")) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        if (this.checkPriority("scrollBar")) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.setScrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        if (this.checkPriority("scrollBarColor")) {
            const value_casted = value as (Color | number | string | undefined)
            this.getPeer()?.setScrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarWidth(value: number | string | undefined): this {
        if (this.checkPriority("scrollBarWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.setScrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (OnScrollFrameBeginCallback | undefined)
            this.getPeer()?.setOnScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions | undefined)
            this.getPeer()?.setNestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    public friction(value: number | Resource | undefined): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setFrictionAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollSnap(value: ScrollSnapOptions | undefined): this {
        if (this.checkPriority("scrollSnap")) {
            const value_casted = value as (ScrollSnapOptions | undefined)
            this.getPeer()?.setScrollSnapAttribute(value_casted)
            return this
        }
        return this
    }
    public enablePaging(value: boolean | undefined): this {
        if (this.checkPriority("enablePaging")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnablePagingAttribute(value_casted)
            return this
        }
        return this
    }
    public initialOffset(value: OffsetOptions | undefined): this {
        if (this.checkPriority("initialOffset")) {
            const value_casted = value as (OffsetOptions | undefined)
            this.getPeer()?.setInitialOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (this.checkPriority("edgeEffect")) {
            const edgeEffect_casted = edgeEffect as (EdgeEffect | undefined)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.setEdgeEffectAttribute(edgeEffect_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withScrollStyle(receiver: ScrollAttribute, modifier: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkScrollStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Scroll")
// export function Scroll(
//     scroller?: Scroller,
//     @memo
//     content_?: () => void,
// ): ScrollAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Scroll(
    @memo
    style: ((attributes: ScrollAttribute) => void) | undefined,
    scroller?: Scroller,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkScrollComponent>((): ArkScrollComponent => {
        return new ArkScrollComponent()
    })
    NodeAttach<ArkScrollPeer>((): ArkScrollPeer => ArkScrollPeer.create(receiver), (_: ArkScrollPeer): void => {
        receiver.setScrollOptions(scroller)
        style?.(receiver)
        withScrollStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkScrollSet extends ArkScrollableCommonMethodSet implements ScrollAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _scrollable_flag?: boolean
    _scrollable0_value?: ScrollDirection | undefined
    _onWillScroll_flag?: boolean
    _onWillScroll0_value?: ScrollOnWillScrollCallback | undefined
    _onDidScroll_flag?: boolean
    _onDidScroll0_value?: ScrollOnScrollCallback | undefined
    _onScrollEdge_flag?: boolean
    _onScrollEdge0_value?: OnScrollEdgeCallback | undefined
    _onScrollStart_flag?: boolean
    _onScrollStart0_value?: VoidCallback | undefined
    _onScrollStop_flag?: boolean
    _onScrollStop0_value?: VoidCallback | undefined
    _scrollBar_flag?: boolean
    _scrollBar0_value?: BarState | undefined
    _scrollBarColor_flag?: boolean
    _scrollBarColor0_value?: Color | number | string | undefined
    _scrollBarWidth_flag?: boolean
    _scrollBarWidth0_value?: number | string | undefined
    _onScrollFrameBegin_flag?: boolean
    _onScrollFrameBegin0_value?: OnScrollFrameBeginCallback | undefined
    _nestedScroll_flag?: boolean
    _nestedScroll0_value?: NestedScrollOptions | undefined
    _enableScrollInteraction_flag?: boolean
    _enableScrollInteraction0_value?: boolean | undefined
    _friction_flag?: boolean
    _friction0_value?: number | Resource | undefined
    _scrollSnap_flag?: boolean
    _scrollSnap0_value?: ScrollSnapOptions | undefined
    _enablePaging_flag?: boolean
    _enablePaging0_value?: boolean | undefined
    _initialOffset_flag?: boolean
    _initialOffset0_value?: OffsetOptions | undefined
    _edgeEffect_flag?: boolean
    _edgeEffect0_value?: EdgeEffect | undefined
    _edgeEffect1_value?: EdgeEffectOptions | undefined
    applyModifierPatch(component: ScrollAttribute): void {
        if (this._scrollable_flag)
            component.scrollable((this._scrollable0_value as ScrollDirection | undefined))
        if (this._onWillScroll_flag)
            component.onWillScroll((this._onWillScroll0_value as ScrollOnWillScrollCallback | undefined))
        if (this._onDidScroll_flag)
            component.onDidScroll((this._onDidScroll0_value as ScrollOnScrollCallback | undefined))
        if (this._onScrollEdge_flag)
            component.onScrollEdge((this._onScrollEdge0_value as OnScrollEdgeCallback | undefined))
        if (this._onScrollStart_flag)
            component.onScrollStart((this._onScrollStart0_value as VoidCallback | undefined))
        if (this._onScrollStop_flag)
            component.onScrollStop((this._onScrollStop0_value as VoidCallback | undefined))
        if (this._scrollBar_flag)
            component.scrollBar((this._scrollBar0_value as BarState | undefined))
        if (this._scrollBarColor_flag)
            component.scrollBarColor((this._scrollBarColor0_value as Color | number | string | undefined))
        if (this._scrollBarWidth_flag)
            component.scrollBarWidth((this._scrollBarWidth0_value as number | string | undefined))
        if (this._onScrollFrameBegin_flag)
            component.onScrollFrameBegin((this._onScrollFrameBegin0_value as OnScrollFrameBeginCallback | undefined))
        if (this._nestedScroll_flag)
            component.nestedScroll((this._nestedScroll0_value as NestedScrollOptions | undefined))
        if (this._enableScrollInteraction_flag)
            component.enableScrollInteraction((this._enableScrollInteraction0_value as boolean | undefined))
        if (this._friction_flag)
            component.friction((this._friction0_value as number | Resource | undefined))
        if (this._scrollSnap_flag)
            component.scrollSnap((this._scrollSnap0_value as ScrollSnapOptions | undefined))
        if (this._enablePaging_flag)
            component.enablePaging((this._enablePaging0_value as boolean | undefined))
        if (this._initialOffset_flag)
            component.initialOffset((this._initialOffset0_value as OffsetOptions | undefined))
        if (this._edgeEffect_flag)
            component.edgeEffect((this._edgeEffect0_value as EdgeEffect | undefined), (this._edgeEffect1_value as EdgeEffectOptions | undefined))
    }
    public scrollable(value: ScrollDirection | undefined): this {
        this._scrollable_flag = true
        this._scrollable0_value = value
        return this
    }
    public onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        this._onWillScroll_flag = true
        this._onWillScroll0_value = value
        return this
    }
    public onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        this._onDidScroll_flag = true
        this._onDidScroll0_value = value
        return this
    }
    public onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        this._onScrollEdge_flag = true
        this._onScrollEdge0_value = value
        return this
    }
    public onScrollStart(value: VoidCallback | undefined): this {
        this._onScrollStart_flag = true
        this._onScrollStart0_value = value
        return this
    }
    public onScrollStop(value: VoidCallback | undefined): this {
        this._onScrollStop_flag = true
        this._onScrollStop0_value = value
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        this._scrollBar_flag = true
        this._scrollBar0_value = value
        return this
    }
    public scrollBarColor(value: Color | number | string | undefined): this {
        this._scrollBarColor_flag = true
        this._scrollBarColor0_value = value
        return this
    }
    public scrollBarWidth(value: number | string | undefined): this {
        this._scrollBarWidth_flag = true
        this._scrollBarWidth0_value = value
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        this._onScrollFrameBegin_flag = true
        this._onScrollFrameBegin0_value = value
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        this._nestedScroll_flag = true
        this._nestedScroll0_value = value
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        this._enableScrollInteraction_flag = true
        this._enableScrollInteraction0_value = value
        return this
    }
    public friction(value: number | Resource | undefined): this {
        this._friction_flag = true
        this._friction0_value = value
        return this
    }
    public scrollSnap(value: ScrollSnapOptions | undefined): this {
        this._scrollSnap_flag = true
        this._scrollSnap0_value = value
        return this
    }
    public enablePaging(value: boolean | undefined): this {
        this._enablePaging_flag = true
        this._enablePaging0_value = value
        return this
    }
    public initialOffset(value: OffsetOptions | undefined): this {
        this._initialOffset_flag = true
        this._initialOffset0_value = value
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        this._edgeEffect_flag = true
        this._edgeEffect0_value = edgeEffect
        this._edgeEffect1_value = options
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class OffsetResult_serializer {
    public static write(buffer: SerializerBase, value: OffsetResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_xOffset  = value.xOffset
        valueSerializer.writeNumber(value_xOffset)
        const value_yOffset  = value.yOffset
        valueSerializer.writeNumber(value_yOffset)
    }
    public static read(buffer: DeserializerBase): OffsetResult {
        let valueDeserializer : DeserializerBase = buffer
        const xOffset_result : number = (valueDeserializer.readNumber() as number)
        const yOffset_result : number = (valueDeserializer.readNumber() as number)
        let value : OffsetResult = ({xOffset: xOffset_result, yOffset: yOffset_result} as OffsetResult)
        return value
    }
}
export class OnScrollFrameBeginHandlerResult_serializer {
    public static write(buffer: SerializerBase, value: OnScrollFrameBeginHandlerResult): void {
        let valueSerializer : SerializerBase = buffer
        const value_offsetRemain  = value.offsetRemain
        valueSerializer.writeNumber(value_offsetRemain)
    }
    public static read(buffer: DeserializerBase): OnScrollFrameBeginHandlerResult {
        let valueDeserializer : DeserializerBase = buffer
        const offsetRemain_result : number = (valueDeserializer.readNumber() as number)
        let value : OnScrollFrameBeginHandlerResult = ({offsetRemain: offsetRemain_result} as OnScrollFrameBeginHandlerResult)
        return value
    }
}
export class Scroller_serializer {
    public static write(buffer: SerializerBase, value: Scroller): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): Scroller {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return ScrollerInternal.fromPtr(ptr)
    }
}
export class ScrollAnimationOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollAnimationOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_duration  = value.duration
        let value_duration_type : int32 = RuntimeType.UNDEFINED
        value_duration_type = runtimeType(value_duration)
        valueSerializer.writeInt8((value_duration_type).toChar())
        if ((value_duration_type) != (RuntimeType.UNDEFINED)) {
            const value_duration_value  = value_duration!
            valueSerializer.writeNumber(value_duration_value)
        }
        const value_curve  = value.curve
        let value_curve_type : int32 = RuntimeType.UNDEFINED
        value_curve_type = runtimeType(value_curve)
        valueSerializer.writeInt8((value_curve_type).toChar())
        if ((value_curve_type) != (RuntimeType.UNDEFINED)) {
            const value_curve_value  = value_curve!
            let value_curve_value_type : int32 = RuntimeType.UNDEFINED
            value_curve_value_type = runtimeType(value_curve_value)
            if (TypeChecker.iscurves_Curve(value_curve_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_curve_value_0  = value_curve_value as curves.Curve
                valueSerializer.writeInt32(TypeChecker.curves_Curve_ToNumeric(value_curve_value_0))
            }
            else if (RuntimeType.OBJECT == value_curve_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_curve_value_1  = value_curve_value as curves.ICurve
                curves_ICurve_serializer.write(valueSerializer, value_curve_value_1)
            }
        }
        const value_canOverScroll  = value.canOverScroll
        let value_canOverScroll_type : int32 = RuntimeType.UNDEFINED
        value_canOverScroll_type = runtimeType(value_canOverScroll)
        valueSerializer.writeInt8((value_canOverScroll_type).toChar())
        if ((value_canOverScroll_type) != (RuntimeType.UNDEFINED)) {
            const value_canOverScroll_value  = value_canOverScroll!
            valueSerializer.writeBoolean(value_canOverScroll_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollAnimationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const duration_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let duration_buf : number | undefined
        if ((duration_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            duration_buf = (valueDeserializer.readNumber() as number)
        }
        const duration_result : number | undefined = duration_buf
        const curve_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let curve_buf : curves.Curve | curves.ICurve | undefined
        if ((curve_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const curve_buf__selector : int32 = valueDeserializer.readInt8()
            let curve_buf_ : curves.Curve | curves.ICurve | undefined
            if (curve_buf__selector == (0).toChar()) {
                curve_buf_ = TypeChecker.curves_Curve_FromNumeric(valueDeserializer.readInt32())
            }
            else if (curve_buf__selector == (1).toChar()) {
                curve_buf_ = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
            }
            else {
                throw new Error("One of the branches for curve_buf_ has to be chosen through deserialisation.")
            }
            curve_buf = (curve_buf_ as curves.Curve | curves.ICurve)
        }
        const curve_result : curves.Curve | curves.ICurve | undefined = curve_buf
        const canOverScroll_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let canOverScroll_buf : boolean | undefined
        if ((canOverScroll_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            canOverScroll_buf = valueDeserializer.readBoolean()
        }
        const canOverScroll_result : boolean | undefined = canOverScroll_buf
        let value : ScrollAnimationOptions = ({duration: duration_result, curve: curve_result, canOverScroll: canOverScroll_result} as ScrollAnimationOptions)
        return value
    }
}
export class ScrollEdgeOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollEdgeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_velocity  = value.velocity
        let value_velocity_type : int32 = RuntimeType.UNDEFINED
        value_velocity_type = runtimeType(value_velocity)
        valueSerializer.writeInt8((value_velocity_type).toChar())
        if ((value_velocity_type) != (RuntimeType.UNDEFINED)) {
            const value_velocity_value  = value_velocity!
            valueSerializer.writeNumber(value_velocity_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollEdgeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const velocity_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let velocity_buf : number | undefined
        if ((velocity_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            velocity_buf = (valueDeserializer.readNumber() as number)
        }
        const velocity_result : number | undefined = velocity_buf
        let value : ScrollEdgeOptions = ({velocity: velocity_result} as ScrollEdgeOptions)
        return value
    }
}
export class ScrollPageOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollPageOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_next  = value.next
        valueSerializer.writeBoolean(value_next)
        const value_animation  = value.animation
        let value_animation_type : int32 = RuntimeType.UNDEFINED
        value_animation_type = runtimeType(value_animation)
        valueSerializer.writeInt8((value_animation_type).toChar())
        if ((value_animation_type) != (RuntimeType.UNDEFINED)) {
            const value_animation_value  = value_animation!
            valueSerializer.writeBoolean(value_animation_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollPageOptions {
        let valueDeserializer : DeserializerBase = buffer
        const next_result : boolean = valueDeserializer.readBoolean()
        const animation_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let animation_buf : boolean | undefined
        if ((animation_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            animation_buf = valueDeserializer.readBoolean()
        }
        const animation_result : boolean | undefined = animation_buf
        let value : ScrollPageOptions = ({next: next_result, animation: animation_result} as ScrollPageOptions)
        return value
    }
}
export class ScrollOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_xOffset  = value.xOffset
        let value_xOffset_type : int32 = RuntimeType.UNDEFINED
        value_xOffset_type = runtimeType(value_xOffset)
        if (RuntimeType.NUMBER == value_xOffset_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_xOffset_0  = value_xOffset as number
            valueSerializer.writeNumber(value_xOffset_0)
        }
        else if (RuntimeType.STRING == value_xOffset_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_xOffset_1  = value_xOffset as string
            valueSerializer.writeString(value_xOffset_1)
        }
        const value_yOffset  = value.yOffset
        let value_yOffset_type : int32 = RuntimeType.UNDEFINED
        value_yOffset_type = runtimeType(value_yOffset)
        if (RuntimeType.NUMBER == value_yOffset_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_yOffset_0  = value_yOffset as number
            valueSerializer.writeNumber(value_yOffset_0)
        }
        else if (RuntimeType.STRING == value_yOffset_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_yOffset_1  = value_yOffset as string
            valueSerializer.writeString(value_yOffset_1)
        }
        const value_animation  = value.animation
        let value_animation_type : int32 = RuntimeType.UNDEFINED
        value_animation_type = runtimeType(value_animation)
        valueSerializer.writeInt8((value_animation_type).toChar())
        if ((value_animation_type) != (RuntimeType.UNDEFINED)) {
            const value_animation_value  = value_animation!
            let value_animation_value_type : int32 = RuntimeType.UNDEFINED
            value_animation_value_type = runtimeType(value_animation_value)
            if (RuntimeType.OBJECT == value_animation_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_animation_value_0  = value_animation_value as ScrollAnimationOptions
                ScrollAnimationOptions_serializer.write(valueSerializer, value_animation_value_0)
            }
            else if (RuntimeType.BOOLEAN == value_animation_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_animation_value_1  = value_animation_value as boolean
                valueSerializer.writeBoolean(value_animation_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): ScrollOptions {
        let valueDeserializer : DeserializerBase = buffer
        const xOffset_buf_selector : int32 = valueDeserializer.readInt8()
        let xOffset_buf : number | string | undefined
        if (xOffset_buf_selector == (0).toChar()) {
            xOffset_buf = (valueDeserializer.readNumber() as number)
        }
        else if (xOffset_buf_selector == (1).toChar()) {
            xOffset_buf = (valueDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for xOffset_buf has to be chosen through deserialisation.")
        }
        const xOffset_result : number | string = (xOffset_buf as number | string)
        const yOffset_buf_selector : int32 = valueDeserializer.readInt8()
        let yOffset_buf : number | string | undefined
        if (yOffset_buf_selector == (0).toChar()) {
            yOffset_buf = (valueDeserializer.readNumber() as number)
        }
        else if (yOffset_buf_selector == (1).toChar()) {
            yOffset_buf = (valueDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for yOffset_buf has to be chosen through deserialisation.")
        }
        const yOffset_result : number | string = (yOffset_buf as number | string)
        const animation_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let animation_buf : ScrollAnimationOptions | boolean | undefined
        if ((animation_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const animation_buf__selector : int32 = valueDeserializer.readInt8()
            let animation_buf_ : ScrollAnimationOptions | boolean | undefined
            if (animation_buf__selector == (0).toChar()) {
                animation_buf_ = ScrollAnimationOptions_serializer.read(valueDeserializer)
            }
            else if (animation_buf__selector == (1).toChar()) {
                animation_buf_ = valueDeserializer.readBoolean()
            }
            else {
                throw new Error("One of the branches for animation_buf_ has to be chosen through deserialisation.")
            }
            animation_buf = (animation_buf_ as ScrollAnimationOptions | boolean)
        }
        const animation_result : ScrollAnimationOptions | boolean | undefined = animation_buf
        let value : ScrollOptions = ({xOffset: xOffset_result, yOffset: yOffset_result, animation: animation_result} as ScrollOptions)
        return value
    }
}
export class ScrollToIndexOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollToIndexOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_extraOffset  = value.extraOffset
        let value_extraOffset_type : int32 = RuntimeType.UNDEFINED
        value_extraOffset_type = runtimeType(value_extraOffset)
        valueSerializer.writeInt8((value_extraOffset_type).toChar())
        if ((value_extraOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_extraOffset_value  = value_extraOffset!
            LengthMetrics_serializer.write(valueSerializer, value_extraOffset_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollToIndexOptions {
        let valueDeserializer : DeserializerBase = buffer
        const extraOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let extraOffset_buf : LengthMetrics | undefined
        if ((extraOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            extraOffset_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const extraOffset_result : LengthMetrics | undefined = extraOffset_buf
        let value : ScrollToIndexOptions = ({extraOffset: extraOffset_result} as ScrollToIndexOptions)
        return value
    }
}
export class OffsetOptions_serializer {
    public static write(buffer: SerializerBase, value: OffsetOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_xOffset  = value.xOffset
        let value_xOffset_type : int32 = RuntimeType.UNDEFINED
        value_xOffset_type = runtimeType(value_xOffset)
        valueSerializer.writeInt8((value_xOffset_type).toChar())
        if ((value_xOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_xOffset_value  = value_xOffset!
            let value_xOffset_value_type : int32 = RuntimeType.UNDEFINED
            value_xOffset_value_type = runtimeType(value_xOffset_value)
            if (RuntimeType.STRING == value_xOffset_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_xOffset_value_0  = value_xOffset_value as string
                valueSerializer.writeString(value_xOffset_value_0)
            }
            else if (RuntimeType.NUMBER == value_xOffset_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_xOffset_value_1  = value_xOffset_value as number
                valueSerializer.writeNumber(value_xOffset_value_1)
            }
            else if (RuntimeType.OBJECT == value_xOffset_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_xOffset_value_2  = value_xOffset_value as Resource
                Resource_serializer.write(valueSerializer, value_xOffset_value_2)
            }
        }
        const value_yOffset  = value.yOffset
        let value_yOffset_type : int32 = RuntimeType.UNDEFINED
        value_yOffset_type = runtimeType(value_yOffset)
        valueSerializer.writeInt8((value_yOffset_type).toChar())
        if ((value_yOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_yOffset_value  = value_yOffset!
            let value_yOffset_value_type : int32 = RuntimeType.UNDEFINED
            value_yOffset_value_type = runtimeType(value_yOffset_value)
            if (RuntimeType.STRING == value_yOffset_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_yOffset_value_0  = value_yOffset_value as string
                valueSerializer.writeString(value_yOffset_value_0)
            }
            else if (RuntimeType.NUMBER == value_yOffset_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_yOffset_value_1  = value_yOffset_value as number
                valueSerializer.writeNumber(value_yOffset_value_1)
            }
            else if (RuntimeType.OBJECT == value_yOffset_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_yOffset_value_2  = value_yOffset_value as Resource
                Resource_serializer.write(valueSerializer, value_yOffset_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): OffsetOptions {
        let valueDeserializer : DeserializerBase = buffer
        const xOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let xOffset_buf : Dimension | undefined
        if ((xOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const xOffset_buf__selector : int32 = valueDeserializer.readInt8()
            let xOffset_buf_ : string | number | Resource | undefined
            if (xOffset_buf__selector == (0).toChar()) {
                xOffset_buf_ = (valueDeserializer.readString() as string)
            }
            else if (xOffset_buf__selector == (1).toChar()) {
                xOffset_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (xOffset_buf__selector == (2).toChar()) {
                xOffset_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for xOffset_buf_ has to be chosen through deserialisation.")
            }
            xOffset_buf = (xOffset_buf_ as string | number | Resource)
        }
        const xOffset_result : Dimension | undefined = xOffset_buf
        const yOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let yOffset_buf : Dimension | undefined
        if ((yOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const yOffset_buf__selector : int32 = valueDeserializer.readInt8()
            let yOffset_buf_ : string | number | Resource | undefined
            if (yOffset_buf__selector == (0).toChar()) {
                yOffset_buf_ = (valueDeserializer.readString() as string)
            }
            else if (yOffset_buf__selector == (1).toChar()) {
                yOffset_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (yOffset_buf__selector == (2).toChar()) {
                yOffset_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for yOffset_buf_ has to be chosen through deserialisation.")
            }
            yOffset_buf = (yOffset_buf_ as string | number | Resource)
        }
        const yOffset_result : Dimension | undefined = yOffset_buf
        let value : OffsetOptions = ({xOffset: xOffset_result, yOffset: yOffset_result} as OffsetOptions)
        return value
    }
}
export class ScrollSnapOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollSnapOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_snapAlign  = value.snapAlign
        valueSerializer.writeInt32(TypeChecker.ScrollSnapAlign_ToNumeric(value_snapAlign))
        const value_snapPagination  = value.snapPagination
        let value_snapPagination_type : int32 = RuntimeType.UNDEFINED
        value_snapPagination_type = runtimeType(value_snapPagination)
        valueSerializer.writeInt8((value_snapPagination_type).toChar())
        if ((value_snapPagination_type) != (RuntimeType.UNDEFINED)) {
            const value_snapPagination_value  = value_snapPagination!
            let value_snapPagination_value_type : int32 = RuntimeType.UNDEFINED
            value_snapPagination_value_type = runtimeType(value_snapPagination_value)
            if ((RuntimeType.STRING == value_snapPagination_value_type) || (RuntimeType.NUMBER == value_snapPagination_value_type) || (RuntimeType.OBJECT == value_snapPagination_value_type)) {
                valueSerializer.writeInt8((0).toChar())
                const value_snapPagination_value_0  = value_snapPagination_value as Dimension
                let value_snapPagination_value_0_type : int32 = RuntimeType.UNDEFINED
                value_snapPagination_value_0_type = runtimeType(value_snapPagination_value_0)
                if (RuntimeType.STRING == value_snapPagination_value_0_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_snapPagination_value_0_0  = value_snapPagination_value_0 as string
                    valueSerializer.writeString(value_snapPagination_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_snapPagination_value_0_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_snapPagination_value_0_1  = value_snapPagination_value_0 as number
                    valueSerializer.writeNumber(value_snapPagination_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_snapPagination_value_0_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_snapPagination_value_0_2  = value_snapPagination_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_snapPagination_value_0_2)
                }
            }
            else if (((RuntimeType.OBJECT) == (value_snapPagination_value_type)) && (TypeChecker.isArray_Dimension(value_snapPagination_value))) {
                valueSerializer.writeInt8((1).toChar())
                const value_snapPagination_value_1  = value_snapPagination_value as Array<Dimension>
                valueSerializer.writeInt32((value_snapPagination_value_1.length).toInt())
                for (let value_snapPagination_value_1_counter_i = 0; value_snapPagination_value_1_counter_i < value_snapPagination_value_1.length; value_snapPagination_value_1_counter_i++) {
                    const value_snapPagination_value_1_element : Dimension = value_snapPagination_value_1[value_snapPagination_value_1_counter_i]
                    let value_snapPagination_value_1_element_type : int32 = RuntimeType.UNDEFINED
                    value_snapPagination_value_1_element_type = runtimeType(value_snapPagination_value_1_element)
                    if (RuntimeType.STRING == value_snapPagination_value_1_element_type) {
                        valueSerializer.writeInt8((0).toChar())
                        const value_snapPagination_value_1_element_0  = value_snapPagination_value_1_element as string
                        valueSerializer.writeString(value_snapPagination_value_1_element_0)
                    }
                    else if (RuntimeType.NUMBER == value_snapPagination_value_1_element_type) {
                        valueSerializer.writeInt8((1).toChar())
                        const value_snapPagination_value_1_element_1  = value_snapPagination_value_1_element as number
                        valueSerializer.writeNumber(value_snapPagination_value_1_element_1)
                    }
                    else if (RuntimeType.OBJECT == value_snapPagination_value_1_element_type) {
                        valueSerializer.writeInt8((2).toChar())
                        const value_snapPagination_value_1_element_2  = value_snapPagination_value_1_element as Resource
                        Resource_serializer.write(valueSerializer, value_snapPagination_value_1_element_2)
                    }
                }
            }
        }
        const value_enableSnapToStart  = value.enableSnapToStart
        let value_enableSnapToStart_type : int32 = RuntimeType.UNDEFINED
        value_enableSnapToStart_type = runtimeType(value_enableSnapToStart)
        valueSerializer.writeInt8((value_enableSnapToStart_type).toChar())
        if ((value_enableSnapToStart_type) != (RuntimeType.UNDEFINED)) {
            const value_enableSnapToStart_value  = value_enableSnapToStart!
            valueSerializer.writeBoolean(value_enableSnapToStart_value)
        }
        const value_enableSnapToEnd  = value.enableSnapToEnd
        let value_enableSnapToEnd_type : int32 = RuntimeType.UNDEFINED
        value_enableSnapToEnd_type = runtimeType(value_enableSnapToEnd)
        valueSerializer.writeInt8((value_enableSnapToEnd_type).toChar())
        if ((value_enableSnapToEnd_type) != (RuntimeType.UNDEFINED)) {
            const value_enableSnapToEnd_value  = value_enableSnapToEnd!
            valueSerializer.writeBoolean(value_enableSnapToEnd_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollSnapOptions {
        let valueDeserializer : DeserializerBase = buffer
        const snapAlign_result : ScrollSnapAlign = TypeChecker.ScrollSnapAlign_FromNumeric(valueDeserializer.readInt32())
        const snapPagination_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let snapPagination_buf : Dimension | Array<Dimension> | undefined
        if ((snapPagination_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const snapPagination_buf__selector : int32 = valueDeserializer.readInt8()
            let snapPagination_buf_ : Dimension | Array<Dimension> | undefined
            if (snapPagination_buf__selector == (0).toChar()) {
                const snapPagination_buf__u_selector : int32 = valueDeserializer.readInt8()
                let snapPagination_buf__u : string | number | Resource | undefined
                if (snapPagination_buf__u_selector == (0).toChar()) {
                    snapPagination_buf__u = (valueDeserializer.readString() as string)
                }
                else if (snapPagination_buf__u_selector == (1).toChar()) {
                    snapPagination_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (snapPagination_buf__u_selector == (2).toChar()) {
                    snapPagination_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for snapPagination_buf__u has to be chosen through deserialisation.")
                }
                snapPagination_buf_ = (snapPagination_buf__u as string | number | Resource)
            }
            else if (snapPagination_buf__selector == (1).toChar()) {
                const snapPagination_buf__u_length : int32 = valueDeserializer.readInt32()
                let snapPagination_buf__u : Array<Dimension> = new Array<Dimension>(snapPagination_buf__u_length)
                for (let snapPagination_buf__u_i = 0; snapPagination_buf__u_i < snapPagination_buf__u_length; snapPagination_buf__u_i++) {
                    const snapPagination_buf__u_buf_selector : int32 = valueDeserializer.readInt8()
                    let snapPagination_buf__u_buf : string | number | Resource | undefined
                    if (snapPagination_buf__u_buf_selector == (0).toChar()) {
                        snapPagination_buf__u_buf = (valueDeserializer.readString() as string)
                    }
                    else if (snapPagination_buf__u_buf_selector == (1).toChar()) {
                        snapPagination_buf__u_buf = (valueDeserializer.readNumber() as number)
                    }
                    else if (snapPagination_buf__u_buf_selector == (2).toChar()) {
                        snapPagination_buf__u_buf = Resource_serializer.read(valueDeserializer)
                    }
                    else {
                        throw new Error("One of the branches for snapPagination_buf__u_buf has to be chosen through deserialisation.")
                    }
                    snapPagination_buf__u[snapPagination_buf__u_i] = (snapPagination_buf__u_buf as string | number | Resource)
                }
                snapPagination_buf_ = snapPagination_buf__u
            }
            else {
                throw new Error("One of the branches for snapPagination_buf_ has to be chosen through deserialisation.")
            }
            snapPagination_buf = (snapPagination_buf_ as Dimension | Array<Dimension>)
        }
        const snapPagination_result : Dimension | Array<Dimension> | undefined = snapPagination_buf
        const enableSnapToStart_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableSnapToStart_buf : boolean | undefined
        if ((enableSnapToStart_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableSnapToStart_buf = valueDeserializer.readBoolean()
        }
        const enableSnapToStart_result : boolean | undefined = enableSnapToStart_buf
        const enableSnapToEnd_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let enableSnapToEnd_buf : boolean | undefined
        if ((enableSnapToEnd_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            enableSnapToEnd_buf = valueDeserializer.readBoolean()
        }
        const enableSnapToEnd_result : boolean | undefined = enableSnapToEnd_buf
        let value : ScrollSnapOptions = ({snapAlign: snapAlign_result, snapPagination: snapPagination_result, enableSnapToStart: enableSnapToStart_result, enableSnapToEnd: enableSnapToEnd_result} as ScrollSnapOptions)
        return value
    }
}
