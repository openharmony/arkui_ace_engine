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
import { Resource_serializer, Resource } from "./resource"
import { RectResult_serializer, RectResult, NestedScrollOptions_serializer, EdgeEffectOptions_serializer, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, CommonMethod, EdgeEffectOptions, ICurve, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ICurve_serializer } from "./common"
import { Edge, ScrollSource, BarState, Color, EdgeEffect, Curve } from "./enums"
import { Length, VoidCallback, Dimension } from "./units"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ScrollState, ScrollSnapAlign } from "./list"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { LengthMetrics, LengthMetrics_serializer } from "./arkui.Graphics"
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
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._Scroller_ctor()
        return retval
    }
    constructor() {
        this(Scroller.ctor())
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
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
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
        thisSerializer.writeInt8(smooth_type)
        if ((RuntimeType.UNDEFINED) != (smooth_type)) {
            const smooth_value  = smooth!
            thisSerializer.writeBoolean(smooth_value)
        }
        let align_type : int32 = RuntimeType.UNDEFINED
        align_type = runtimeType(align)
        thisSerializer.writeInt8(align_type)
        if ((RuntimeType.UNDEFINED) != (align_type)) {
            const align_value  = (align as ScrollAlign)
            thisSerializer.writeInt32(TypeChecker.ScrollAlign_ToNumeric(align_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
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
            thisSerializer.writeInt8(0)
            const dx_0  = dx as string
            thisSerializer.writeString(dx_0)
        }
        else if (RuntimeType.NUMBER == dx_type) {
            thisSerializer.writeInt8(1)
            const dx_1  = dx as number
            thisSerializer.writeNumber(dx_1)
        }
        else if (RuntimeType.OBJECT == dx_type) {
            thisSerializer.writeInt8(2)
            const dx_2  = dx as Resource
            Resource_serializer.write(thisSerializer, dx_2)
        }
        let dy_type : int32 = RuntimeType.UNDEFINED
        dy_type = runtimeType(dy)
        if (RuntimeType.STRING == dy_type) {
            thisSerializer.writeInt8(0)
            const dy_0  = dy as string
            thisSerializer.writeString(dy_0)
        }
        else if (RuntimeType.NUMBER == dy_type) {
            thisSerializer.writeInt8(1)
            const dy_1  = dy as number
            thisSerializer.writeNumber(dy_1)
        }
        else if (RuntimeType.OBJECT == dy_type) {
            thisSerializer.writeInt8(2)
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
        thisSerializer.writeInt8(scroller_type)
        if ((RuntimeType.UNDEFINED) != (scroller_type)) {
            const scroller_value  = scroller!
            Scroller_serializer.write(thisSerializer, scroller_value)
        }
        ArkUIGeneratedNativeModule._ScrollInterface_setScrollOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollableAttribute(value: ScrollDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as ScrollDirection)
            thisSerializer.writeInt32(TypeChecker.ScrollDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillScrollAttribute(value: ScrollOnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: ScrollOnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollEdgeAttribute(value: OnScrollEdgeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStartAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollStopAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarAttribute(value: BarState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as BarState)
            thisSerializer.writeInt32(TypeChecker.BarState_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarColorAttribute(value: Color | number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollBarWidthAttribute(value: number | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nestedScrollAttribute(value: NestedScrollOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            NestedScrollOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_enableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    frictionAttribute(value: number | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    scrollSnapAttribute(value: ScrollSnapOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            ScrollSnapOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_scrollSnap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enablePagingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_enablePaging(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    initialOffsetAttribute(value: OffsetOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            OffsetOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_initialOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    edgeEffectAttribute(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let edgeEffect_type : int32 = RuntimeType.UNDEFINED
        edgeEffect_type = runtimeType(edgeEffect)
        thisSerializer.writeInt8(edgeEffect_type)
        if ((RuntimeType.UNDEFINED) != (edgeEffect_type)) {
            const edgeEffect_value  = (edgeEffect as EdgeEffect)
            thisSerializer.writeInt32(TypeChecker.EdgeEffect_ToNumeric(edgeEffect_value))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            EdgeEffectOptions_serializer.write(thisSerializer, options_value)
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
    curve?: Curve | ICurve;
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
    scrollable(value: ScrollDirection | undefined): this
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this
    onDidScroll(value: ScrollOnScrollCallback | undefined): this
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this
    onScrollStart(value: VoidCallback | undefined): this
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
    attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
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
            this.getPeer()?.scrollableAttribute(value_casted)
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
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.edgeEffectAttribute(edgeEffect_casted, options_casted)
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
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("ScrollImpl")
export function Scroll(
    scroller?: Scroller | undefined,
    @memo
    content_?: () => void,
): ScrollAttribute {
    throw new Error("Not implemented")
}

@memo
export function ScrollImpl(
    @memo
    style: ((attributes: ScrollAttribute) => void) | undefined,
    scroller?: Scroller | undefined,
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
        valueSerializer.writeInt8(value_duration_type)
        if ((RuntimeType.UNDEFINED) != (value_duration_type)) {
            const value_duration_value  = value_duration!
            valueSerializer.writeNumber(value_duration_value)
        }
        const value_curve  = value.curve
        let value_curve_type : int32 = RuntimeType.UNDEFINED
        value_curve_type = runtimeType(value_curve)
        valueSerializer.writeInt8(value_curve_type)
        if ((RuntimeType.UNDEFINED) != (value_curve_type)) {
            const value_curve_value  = value_curve!
            let value_curve_value_type : int32 = RuntimeType.UNDEFINED
            value_curve_value_type = runtimeType(value_curve_value)
            if (TypeChecker.isCurve(value_curve_value)) {
                valueSerializer.writeInt8(0)
                const value_curve_value_0  = value_curve_value as Curve
                valueSerializer.writeInt32(TypeChecker.Curve_ToNumeric(value_curve_value_0))
            }
            else if (RuntimeType.OBJECT == value_curve_value_type) {
                valueSerializer.writeInt8(1)
                const value_curve_value_1  = value_curve_value as ICurve
                ICurve_serializer.write(valueSerializer, value_curve_value_1)
            }
        }
        const value_canOverScroll  = value.canOverScroll
        let value_canOverScroll_type : int32 = RuntimeType.UNDEFINED
        value_canOverScroll_type = runtimeType(value_canOverScroll)
        valueSerializer.writeInt8(value_canOverScroll_type)
        if ((RuntimeType.UNDEFINED) != (value_canOverScroll_type)) {
            const value_canOverScroll_value  = value_canOverScroll!
            valueSerializer.writeBoolean(value_canOverScroll_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollAnimationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const duration_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let duration_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (duration_buf_runtimeType))
        {
            duration_buf = (valueDeserializer.readNumber() as number)
        }
        const duration_result : number | undefined = duration_buf
        const curve_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let curve_buf : Curve | ICurve | undefined
        if ((RuntimeType.UNDEFINED) != (curve_buf_runtimeType))
        {
            const curve_buf__selector : int32 = valueDeserializer.readInt8()
            let curve_buf_ : Curve | ICurve | undefined
            if (curve_buf__selector == 0) {
                curve_buf_ = TypeChecker.Curve_FromNumeric(valueDeserializer.readInt32())
            }
            else if (curve_buf__selector == 1) {
                curve_buf_ = (ICurve_serializer.read(valueDeserializer) as ICurve)
            }
            else {
                throw new Error("One of the branches for curve_buf_ has to be chosen through deserialisation.")
            }
            curve_buf = (curve_buf_ as Curve | ICurve)
        }
        const curve_result : Curve | ICurve | undefined = curve_buf
        const canOverScroll_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let canOverScroll_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (canOverScroll_buf_runtimeType))
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
        valueSerializer.writeInt8(value_velocity_type)
        if ((RuntimeType.UNDEFINED) != (value_velocity_type)) {
            const value_velocity_value  = value_velocity!
            valueSerializer.writeNumber(value_velocity_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollEdgeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const velocity_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let velocity_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (velocity_buf_runtimeType))
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
        valueSerializer.writeInt8(value_animation_type)
        if ((RuntimeType.UNDEFINED) != (value_animation_type)) {
            const value_animation_value  = value_animation!
            valueSerializer.writeBoolean(value_animation_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollPageOptions {
        let valueDeserializer : DeserializerBase = buffer
        const next_result : boolean = valueDeserializer.readBoolean()
        const animation_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let animation_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (animation_buf_runtimeType))
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
            valueSerializer.writeInt8(0)
            const value_xOffset_0  = value_xOffset as number
            valueSerializer.writeNumber(value_xOffset_0)
        }
        else if (RuntimeType.STRING == value_xOffset_type) {
            valueSerializer.writeInt8(1)
            const value_xOffset_1  = value_xOffset as string
            valueSerializer.writeString(value_xOffset_1)
        }
        const value_yOffset  = value.yOffset
        let value_yOffset_type : int32 = RuntimeType.UNDEFINED
        value_yOffset_type = runtimeType(value_yOffset)
        if (RuntimeType.NUMBER == value_yOffset_type) {
            valueSerializer.writeInt8(0)
            const value_yOffset_0  = value_yOffset as number
            valueSerializer.writeNumber(value_yOffset_0)
        }
        else if (RuntimeType.STRING == value_yOffset_type) {
            valueSerializer.writeInt8(1)
            const value_yOffset_1  = value_yOffset as string
            valueSerializer.writeString(value_yOffset_1)
        }
        const value_animation  = value.animation
        let value_animation_type : int32 = RuntimeType.UNDEFINED
        value_animation_type = runtimeType(value_animation)
        valueSerializer.writeInt8(value_animation_type)
        if ((RuntimeType.UNDEFINED) != (value_animation_type)) {
            const value_animation_value  = value_animation!
            let value_animation_value_type : int32 = RuntimeType.UNDEFINED
            value_animation_value_type = runtimeType(value_animation_value)
            if (RuntimeType.OBJECT == value_animation_value_type) {
                valueSerializer.writeInt8(0)
                const value_animation_value_0  = value_animation_value as ScrollAnimationOptions
                ScrollAnimationOptions_serializer.write(valueSerializer, value_animation_value_0)
            }
            else if (RuntimeType.BOOLEAN == value_animation_value_type) {
                valueSerializer.writeInt8(1)
                const value_animation_value_1  = value_animation_value as boolean
                valueSerializer.writeBoolean(value_animation_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): ScrollOptions {
        let valueDeserializer : DeserializerBase = buffer
        const xOffset_buf_selector : int32 = valueDeserializer.readInt8()
        let xOffset_buf : number | string | undefined
        if (xOffset_buf_selector == 0) {
            xOffset_buf = (valueDeserializer.readNumber() as number)
        }
        else if (xOffset_buf_selector == 1) {
            xOffset_buf = (valueDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for xOffset_buf has to be chosen through deserialisation.")
        }
        const xOffset_result : number | string = (xOffset_buf as number | string)
        const yOffset_buf_selector : int32 = valueDeserializer.readInt8()
        let yOffset_buf : number | string | undefined
        if (yOffset_buf_selector == 0) {
            yOffset_buf = (valueDeserializer.readNumber() as number)
        }
        else if (yOffset_buf_selector == 1) {
            yOffset_buf = (valueDeserializer.readString() as string)
        }
        else {
            throw new Error("One of the branches for yOffset_buf has to be chosen through deserialisation.")
        }
        const yOffset_result : number | string = (yOffset_buf as number | string)
        const animation_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let animation_buf : ScrollAnimationOptions | boolean | undefined
        if ((RuntimeType.UNDEFINED) != (animation_buf_runtimeType))
        {
            const animation_buf__selector : int32 = valueDeserializer.readInt8()
            let animation_buf_ : ScrollAnimationOptions | boolean | undefined
            if (animation_buf__selector == 0) {
                animation_buf_ = ScrollAnimationOptions_serializer.read(valueDeserializer)
            }
            else if (animation_buf__selector == 1) {
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
        valueSerializer.writeInt8(value_extraOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_extraOffset_type)) {
            const value_extraOffset_value  = value_extraOffset!
            LengthMetrics_serializer.write(valueSerializer, value_extraOffset_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollToIndexOptions {
        let valueDeserializer : DeserializerBase = buffer
        const extraOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let extraOffset_buf : LengthMetrics | undefined
        if ((RuntimeType.UNDEFINED) != (extraOffset_buf_runtimeType))
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
        valueSerializer.writeInt8(value_xOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_xOffset_type)) {
            const value_xOffset_value  = value_xOffset!
            let value_xOffset_value_type : int32 = RuntimeType.UNDEFINED
            value_xOffset_value_type = runtimeType(value_xOffset_value)
            if (RuntimeType.STRING == value_xOffset_value_type) {
                valueSerializer.writeInt8(0)
                const value_xOffset_value_0  = value_xOffset_value as string
                valueSerializer.writeString(value_xOffset_value_0)
            }
            else if (RuntimeType.NUMBER == value_xOffset_value_type) {
                valueSerializer.writeInt8(1)
                const value_xOffset_value_1  = value_xOffset_value as number
                valueSerializer.writeNumber(value_xOffset_value_1)
            }
            else if (RuntimeType.OBJECT == value_xOffset_value_type) {
                valueSerializer.writeInt8(2)
                const value_xOffset_value_2  = value_xOffset_value as Resource
                Resource_serializer.write(valueSerializer, value_xOffset_value_2)
            }
        }
        const value_yOffset  = value.yOffset
        let value_yOffset_type : int32 = RuntimeType.UNDEFINED
        value_yOffset_type = runtimeType(value_yOffset)
        valueSerializer.writeInt8(value_yOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_yOffset_type)) {
            const value_yOffset_value  = value_yOffset!
            let value_yOffset_value_type : int32 = RuntimeType.UNDEFINED
            value_yOffset_value_type = runtimeType(value_yOffset_value)
            if (RuntimeType.STRING == value_yOffset_value_type) {
                valueSerializer.writeInt8(0)
                const value_yOffset_value_0  = value_yOffset_value as string
                valueSerializer.writeString(value_yOffset_value_0)
            }
            else if (RuntimeType.NUMBER == value_yOffset_value_type) {
                valueSerializer.writeInt8(1)
                const value_yOffset_value_1  = value_yOffset_value as number
                valueSerializer.writeNumber(value_yOffset_value_1)
            }
            else if (RuntimeType.OBJECT == value_yOffset_value_type) {
                valueSerializer.writeInt8(2)
                const value_yOffset_value_2  = value_yOffset_value as Resource
                Resource_serializer.write(valueSerializer, value_yOffset_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): OffsetOptions {
        let valueDeserializer : DeserializerBase = buffer
        const xOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let xOffset_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (xOffset_buf_runtimeType))
        {
            const xOffset_buf__selector : int32 = valueDeserializer.readInt8()
            let xOffset_buf_ : string | number | Resource | undefined
            if (xOffset_buf__selector == 0) {
                xOffset_buf_ = (valueDeserializer.readString() as string)
            }
            else if (xOffset_buf__selector == 1) {
                xOffset_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (xOffset_buf__selector == 2) {
                xOffset_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for xOffset_buf_ has to be chosen through deserialisation.")
            }
            xOffset_buf = (xOffset_buf_ as string | number | Resource)
        }
        const xOffset_result : Dimension | undefined = xOffset_buf
        const yOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let yOffset_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (yOffset_buf_runtimeType))
        {
            const yOffset_buf__selector : int32 = valueDeserializer.readInt8()
            let yOffset_buf_ : string | number | Resource | undefined
            if (yOffset_buf__selector == 0) {
                yOffset_buf_ = (valueDeserializer.readString() as string)
            }
            else if (yOffset_buf__selector == 1) {
                yOffset_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (yOffset_buf__selector == 2) {
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
        valueSerializer.writeInt8(value_snapPagination_type)
        if ((RuntimeType.UNDEFINED) != (value_snapPagination_type)) {
            const value_snapPagination_value  = value_snapPagination!
            let value_snapPagination_value_type : int32 = RuntimeType.UNDEFINED
            value_snapPagination_value_type = runtimeType(value_snapPagination_value)
            if ((RuntimeType.STRING == value_snapPagination_value_type) || (RuntimeType.NUMBER == value_snapPagination_value_type) || (RuntimeType.OBJECT == value_snapPagination_value_type)) {
                valueSerializer.writeInt8(0)
                const value_snapPagination_value_0  = value_snapPagination_value as Dimension
                let value_snapPagination_value_0_type : int32 = RuntimeType.UNDEFINED
                value_snapPagination_value_0_type = runtimeType(value_snapPagination_value_0)
                if (RuntimeType.STRING == value_snapPagination_value_0_type) {
                    valueSerializer.writeInt8(0)
                    const value_snapPagination_value_0_0  = value_snapPagination_value_0 as string
                    valueSerializer.writeString(value_snapPagination_value_0_0)
                }
                else if (RuntimeType.NUMBER == value_snapPagination_value_0_type) {
                    valueSerializer.writeInt8(1)
                    const value_snapPagination_value_0_1  = value_snapPagination_value_0 as number
                    valueSerializer.writeNumber(value_snapPagination_value_0_1)
                }
                else if (RuntimeType.OBJECT == value_snapPagination_value_0_type) {
                    valueSerializer.writeInt8(2)
                    const value_snapPagination_value_0_2  = value_snapPagination_value_0 as Resource
                    Resource_serializer.write(valueSerializer, value_snapPagination_value_0_2)
                }
            }
            else if (((RuntimeType.OBJECT) == (value_snapPagination_value_type)) && (TypeChecker.isArray_Dimension(value_snapPagination_value))) {
                valueSerializer.writeInt8(1)
                const value_snapPagination_value_1  = value_snapPagination_value as Array<Dimension>
                valueSerializer.writeInt32(value_snapPagination_value_1.length as int32)
                for (let i = 0; i < value_snapPagination_value_1.length; i++) {
                    const value_snapPagination_value_1_element : Dimension = value_snapPagination_value_1[i]
                    let value_snapPagination_value_1_element_type : int32 = RuntimeType.UNDEFINED
                    value_snapPagination_value_1_element_type = runtimeType(value_snapPagination_value_1_element)
                    if (RuntimeType.STRING == value_snapPagination_value_1_element_type) {
                        valueSerializer.writeInt8(0)
                        const value_snapPagination_value_1_element_0  = value_snapPagination_value_1_element as string
                        valueSerializer.writeString(value_snapPagination_value_1_element_0)
                    }
                    else if (RuntimeType.NUMBER == value_snapPagination_value_1_element_type) {
                        valueSerializer.writeInt8(1)
                        const value_snapPagination_value_1_element_1  = value_snapPagination_value_1_element as number
                        valueSerializer.writeNumber(value_snapPagination_value_1_element_1)
                    }
                    else if (RuntimeType.OBJECT == value_snapPagination_value_1_element_type) {
                        valueSerializer.writeInt8(2)
                        const value_snapPagination_value_1_element_2  = value_snapPagination_value_1_element as Resource
                        Resource_serializer.write(valueSerializer, value_snapPagination_value_1_element_2)
                    }
                }
            }
        }
        const value_enableSnapToStart  = value.enableSnapToStart
        let value_enableSnapToStart_type : int32 = RuntimeType.UNDEFINED
        value_enableSnapToStart_type = runtimeType(value_enableSnapToStart)
        valueSerializer.writeInt8(value_enableSnapToStart_type)
        if ((RuntimeType.UNDEFINED) != (value_enableSnapToStart_type)) {
            const value_enableSnapToStart_value  = value_enableSnapToStart!
            valueSerializer.writeBoolean(value_enableSnapToStart_value)
        }
        const value_enableSnapToEnd  = value.enableSnapToEnd
        let value_enableSnapToEnd_type : int32 = RuntimeType.UNDEFINED
        value_enableSnapToEnd_type = runtimeType(value_enableSnapToEnd)
        valueSerializer.writeInt8(value_enableSnapToEnd_type)
        if ((RuntimeType.UNDEFINED) != (value_enableSnapToEnd_type)) {
            const value_enableSnapToEnd_value  = value_enableSnapToEnd!
            valueSerializer.writeBoolean(value_enableSnapToEnd_value)
        }
    }
    public static read(buffer: DeserializerBase): ScrollSnapOptions {
        let valueDeserializer : DeserializerBase = buffer
        const snapAlign_result : ScrollSnapAlign = TypeChecker.ScrollSnapAlign_FromNumeric(valueDeserializer.readInt32())
        const snapPagination_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let snapPagination_buf : Dimension | Array<Dimension> | undefined
        if ((RuntimeType.UNDEFINED) != (snapPagination_buf_runtimeType))
        {
            const snapPagination_buf__selector : int32 = valueDeserializer.readInt8()
            let snapPagination_buf_ : Dimension | Array<Dimension> | undefined
            if (snapPagination_buf__selector == 0) {
                const snapPagination_buf__u_selector : int32 = valueDeserializer.readInt8()
                let snapPagination_buf__u : string | number | Resource | undefined
                if (snapPagination_buf__u_selector == 0) {
                    snapPagination_buf__u = (valueDeserializer.readString() as string)
                }
                else if (snapPagination_buf__u_selector == 1) {
                    snapPagination_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (snapPagination_buf__u_selector == 2) {
                    snapPagination_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for snapPagination_buf__u has to be chosen through deserialisation.")
                }
                snapPagination_buf_ = (snapPagination_buf__u as string | number | Resource)
            }
            else if (snapPagination_buf__selector == 1) {
                const snapPagination_buf__u_length : int32 = valueDeserializer.readInt32()
                let snapPagination_buf__u : Array<Dimension> = new Array<Dimension>(snapPagination_buf__u_length)
                for (let snapPagination_buf__u_i = 0; snapPagination_buf__u_i < snapPagination_buf__u_length; snapPagination_buf__u_i++) {
                    const snapPagination_buf__u_buf_selector : int32 = valueDeserializer.readInt8()
                    let snapPagination_buf__u_buf : string | number | Resource | undefined
                    if (snapPagination_buf__u_buf_selector == 0) {
                        snapPagination_buf__u_buf = (valueDeserializer.readString() as string)
                    }
                    else if (snapPagination_buf__u_buf_selector == 1) {
                        snapPagination_buf__u_buf = (valueDeserializer.readNumber() as number)
                    }
                    else if (snapPagination_buf__u_buf_selector == 2) {
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
        const enableSnapToStart_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let enableSnapToStart_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (enableSnapToStart_buf_runtimeType))
        {
            enableSnapToStart_buf = valueDeserializer.readBoolean()
        }
        const enableSnapToStart_result : boolean | undefined = enableSnapToStart_buf
        const enableSnapToEnd_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let enableSnapToEnd_buf : boolean | undefined
        if ((RuntimeType.UNDEFINED) != (enableSnapToEnd_buf_runtimeType))
        {
            enableSnapToEnd_buf = valueDeserializer.readBoolean()
        }
        const enableSnapToEnd_result : boolean | undefined = enableSnapToEnd_buf
        let value : ScrollSnapOptions = ({snapAlign: snapAlign_result, snapPagination: snapPagination_result, enableSnapToStart: enableSnapToStart_result, enableSnapToEnd: enableSnapToEnd_result} as ScrollSnapOptions)
        return value
    }
}
