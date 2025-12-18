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

import { SerializerBase, DeserializerBase, Finalizable, RuntimeType, toPeerPtr, KPointer, MaterializedBase, MaterializedBaseTag, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { global_resource_Resource_serializer } from './../framework/resource'
import { RectResult_serializer, RectResult, NestedScrollOptions_serializer, EdgeEffectOptions_serializer, ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, CommonMethod, EdgeEffectOptions, ICurve, ArkScrollableCommonMethodComponent, ArkCommonMethodComponent } from './common'
import { Edge, ScrollSource, BarState, Color as arkui_component_enums_Color, EdgeEffect, Curve } from './enums'
import { Length, Resource as arkui_component_units_Resource, VoidCallback, LengthMetrics as arkui_component_units_LengthMetrics, Dimension } from './units'
import { Resource as global_resource_Resource } from 'global.resource'
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ScrollState, ScrollSnapAlign } from './list'
import { AttributeModifier, extractors, hookScrollAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from '@arkui.Graphics'
import { default as curves } from '@ohos.curves'
import { ScrollModifier } from './../ScrollModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { curves_ICurve_serializer } from './../framework/ohos.curves'
import { arkui_Graphics_LengthMetrics_serializer } from './../framework/Graphics'
export class ScrollerInternal {
    public static fromPtr(ptr: KPointer): Scroller {
        return new Scroller(MaterializedBaseTag.NOP, ptr)
    }
}
export class Scroller implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, Scroller.getFinalizer())
    }
    constructor() {
        this(MaterializedBaseTag.NOP, Scroller.construct())
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
    public fling(velocity: double): void {
        const velocity_casted = velocity as (double)
        this.fling_serialize(velocity_casted)
        return
    }
    public scrollPage(value: ScrollPageOptions): void {
        const value_casted = value as (ScrollPageOptions)
        this.scrollPage_serialize(value_casted)
        return
    }
    public currentOffset(): OffsetResult | undefined {
        return this.currentOffset_serialize()
    }
    public scrollToIndex(value: int32, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): void {
        const value_casted = value as (int32)
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
    public getItemRect(index: int32): RectResult {
        const index_casted = index as (int32)
        return this.getItemRect_serialize(index_casted)
    }
    public getItemIndex(x: double, y: double): int32 {
        const x_casted = x as (double)
        const y_casted = y as (double)
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
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ScrollEdgeOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Scroller_scrollEdge(this.peer!.ptr, value.valueOf(), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private fling_serialize(velocity: double): void {
        ArkUIGeneratedNativeModule._Scroller_fling(this.peer!.ptr, velocity)
    }
    private scrollPage_serialize(value: ScrollPageOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        ScrollPageOptions_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._Scroller_scrollPage(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private currentOffset_serialize(): OffsetResult | undefined {
        const retval  = ArkUIGeneratedNativeModule._Scroller_currentOffset(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_runtimeType  = retvalDeserializer.readInt8()!.toInt()
        let buffer : OffsetResult | undefined = undefined
        if ((buffer_runtimeType) != (RuntimeType.UNDEFINED)) {
            buffer = OffsetResult_serializer.read(retvalDeserializer)
        }
        const returnResult : OffsetResult | undefined = buffer
        return returnResult
    }
    private scrollToIndex_serialize(value: int32, smooth?: boolean, align?: ScrollAlign, options?: ScrollToIndexOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (smooth !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const smoothTmpValue  = smooth!
            thisSerializer.writeBoolean(smoothTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (align !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const alignTmpValue  = (align as ScrollAlign)
            thisSerializer.writeInt32(alignTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            ScrollToIndexOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._Scroller_scrollToIndex(this.peer!.ptr, value, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private scrollBy_serialize(dx: Length, dy: Length): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (dx instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const dxForIdx0  = dx as string
            thisSerializer.writeString(dxForIdx0)
        } else if (dx instanceof double) {
            thisSerializer.writeInt8((1).toByte())
            const dxForIdx1  = dx as double
            thisSerializer.writeFloat64(dxForIdx1)
        } else if (dx instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((2).toByte())
            const dxForIdx2  = dx as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, dxForIdx2)
        }
        if (dy instanceof string) {
            thisSerializer.writeInt8((0).toByte())
            const dyForIdx0  = dy as string
            thisSerializer.writeString(dyForIdx0)
        } else if (dy instanceof double) {
            thisSerializer.writeInt8((1).toByte())
            const dyForIdx1  = dy as double
            thisSerializer.writeFloat64(dyForIdx1)
        } else if (dy instanceof arkui_component_units_Resource) {
            thisSerializer.writeInt8((2).toByte())
            const dyForIdx2  = dy as arkui_component_units_Resource
            global_resource_Resource_serializer.write(thisSerializer, dyForIdx2)
        }
        ArkUIGeneratedNativeModule._Scroller_scrollBy(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private isAtEnd_serialize(): boolean {
        const retval  = ArkUIGeneratedNativeModule._Scroller_isAtEnd(this.peer!.ptr)
        return retval
    }
    private getItemRect_serialize(index: int32): RectResult {
        const retval  = ArkUIGeneratedNativeModule._Scroller_getItemRect(this.peer!.ptr, index)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const returnResult : RectResult = RectResult_serializer.read(retvalDeserializer)
        return returnResult
    }
    private getItemIndex_serialize(x: double, y: double): int32 {
        const retval  = ArkUIGeneratedNativeModule._Scroller_getItemIndex(this.peer!.ptr, x, y)
        return retval
    }
}
export class ArkScrollPeer extends ArkScrollableCommonMethodPeer {
    attributeSet?: ScrollModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkScrollPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Scroll_construct(peerId, flags)
        const _peer  = new ArkScrollPeer(_peerPtr, peerId, 'Scroll', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setScrollOptionsAttribute(scroller?: Scroller): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (scroller !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const scrollerTmpValue  = scroller!
            Scroller_serializer.write(thisSerializer, scrollerTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollInterface_setScrollOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollableAttribute(value: ScrollDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as ScrollDirection)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillScrollAttribute(value: ScrollOnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidScrollAttribute(value: ScrollOnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollEdgeAttribute(value: OnScrollEdgeCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnScrollEdge(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollStartAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnScrollStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollStopAttribute(value: VoidCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnScrollStop(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarAttribute(value: BarState | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as BarState)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarColorAttribute(value: arkui_component_enums_Color | int32 | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof arkui_component_enums_Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as arkui_component_enums_Color
                thisSerializer.writeInt32((valueTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollBarColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollBarWidthAttribute(value: double | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollFrameBeginAttribute(value: OnScrollFrameBeginCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNestedScrollAttribute(value: NestedScrollOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            NestedScrollOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setNestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnableScrollInteractionAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setEnableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFrictionAttribute(value: double | arkui_component_units_Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx1)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setFriction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setScrollSnapAttribute(value: ScrollSnapOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ScrollSnapOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setScrollSnap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEnablePagingAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setEnablePaging(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setInitialOffsetAttribute(value: OffsetOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            OffsetOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setInitialOffset(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEdgeEffectAttribute(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (edgeEffect !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const edgeEffectTmpValue  = (edgeEffect as EdgeEffect)
            thisSerializer.writeInt32(edgeEffectTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            EdgeEffectOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._ScrollAttribute_setEdgeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum ScrollDirection {
    Vertical = 0,
    Horizontal = 1,
    None = 2,
    VERTICAL = 0,
    HORIZONTAL = 1,
    NONE = 2
}
export enum ScrollAlign {
    START = 0,
    CENTER = 1,
    END = 2,
    AUTO = 3
}
export interface OffsetResult {
    xOffset: double;
    yOffset: double;
}
export interface ScrollEdgeOptions {
    velocity?: double;
}
export interface ScrollToIndexOptions {
    extraOffset?: arkui_component_units_LengthMetrics;
}
export interface ScrollAnimationOptions {
    duration?: int32;
    curve?: Curve | ICurve;
    canOverScroll?: boolean;
}
export interface OffsetOptions {
    xOffset?: Dimension;
    yOffset?: Dimension;
}
export interface ScrollOptions {
    xOffset: double | string;
    yOffset: double | string;
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
    offsetRemain: double;
}
export type OnScrollFrameBeginCallback = (offset: double, state: ScrollState) => OnScrollFrameBeginHandlerResult;
export interface ScrollAttribute extends ScrollableCommonMethod {
    setScrollOptions(scroller?: Scroller): this {
        throw new Error('Unimplemented method setScrollOptions')
    }
    scrollable(value: ScrollDirection | undefined): this {
        throw new Error('Unimplemented method scrollable')
    }
    onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        throw new Error('Unimplemented method onWillScroll')
    }
    onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        throw new Error('Unimplemented method onDidScroll')
    }
    onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        throw new Error('Unimplemented method onScrollEdge')
    }
    onScrollStart(value: VoidCallback | undefined): this
    onScrollStop(value: VoidCallback | undefined): this
    scrollBar(value: BarState | undefined): this
    scrollBarColor(value: arkui_component_enums_Color | int32 | string | undefined): this
    scrollBarWidth(value: double | string | undefined): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        throw new Error('Unimplemented method onScrollFrameBegin')
    }
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: double | arkui_component_units_Resource | undefined): this
    scrollSnap(value: ScrollSnapOptions | undefined): this {
        throw new Error('Unimplemented method scrollSnap')
    }
    enablePaging(value: boolean | undefined): this {
        throw new Error('Unimplemented method enablePaging')
    }
    initialOffset(value: OffsetOptions | undefined): this {
        throw new Error('Unimplemented method initialOffset')
    }
    edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        throw new Error('Unimplemented method edgeEffect')
    }
    attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
export type ScrollOnScrollCallback = (xOffset: double, yOffset: double, scrollState: ScrollState) => void;
export type ScrollOnWillScrollCallback = (xOffset: double, yOffset: double, scrollState: ScrollState, scrollSource: ScrollSource) => OffsetResult | undefined;

export class ArkScrollComponent extends ArkScrollableCommonMethodComponent implements ScrollAttribute {
    getPeer(): ArkScrollPeer {
        return (this.peer as ArkScrollPeer)
    }
    public setScrollOptions(scroller?: Scroller): this {
        if (this.checkPriority('setScrollOptions')) {
            const scroller_casted = scroller as (Scroller | undefined)
            this.getPeer()?.setScrollOptionsAttribute(scroller_casted)
            this.applyOptionsFinish('ScrollAttribute');
            return this
        }
        return this
    }
    public scrollable(value: ScrollDirection | undefined): this {
        if (this.checkPriority('scrollable')) {
            const value_casted = value as (ScrollDirection | undefined)
            this.getPeer()?.setScrollableAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value: ScrollOnWillScrollCallback | undefined): this {
        if (this.checkPriority('onWillScroll')) {
            const value_casted = value as (ScrollOnWillScrollCallback | undefined)
            this.getPeer()?.setOnWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: ScrollOnScrollCallback | undefined): this {
        if (this.checkPriority('onDidScroll')) {
            const value_casted = value as (ScrollOnScrollCallback | undefined)
            this.getPeer()?.setOnDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollEdge(value: OnScrollEdgeCallback | undefined): this {
        if (this.checkPriority('onScrollEdge')) {
            const value_casted = value as (OnScrollEdgeCallback | undefined)
            this.getPeer()?.setOnScrollEdgeAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStart(value: VoidCallback | undefined): this {
        if (this.checkPriority('onScrollStart')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnScrollStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollStop(value: VoidCallback | undefined): this {
        if (this.checkPriority('onScrollStop')) {
            const value_casted = value as (VoidCallback | undefined)
            this.getPeer()?.setOnScrollStopAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBar(value: BarState | undefined): this {
        if (this.checkPriority('scrollBar')) {
            const value_casted = value as (BarState | undefined)
            this.getPeer()?.setScrollBarAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarColor(value: arkui_component_enums_Color | int32 | string | undefined): this {
        if (this.checkPriority('scrollBarColor')) {
            const value_casted = value as (arkui_component_enums_Color | int32 | string | undefined)
            this.getPeer()?.setScrollBarColorAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollBarWidth(value: double | string | undefined): this {
        if (this.checkPriority('scrollBarWidth')) {
            const value_casted = value as (double | string | undefined)
            this.getPeer()?.setScrollBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        if (this.checkPriority('onScrollFrameBegin')) {
            const value_casted = value as (OnScrollFrameBeginCallback | undefined)
            this.getPeer()?.setOnScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        if (this.checkPriority('nestedScroll')) {
            const value_casted = value as (NestedScrollOptions | undefined)
            this.getPeer()?.setNestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        if (this.checkPriority('enableScrollInteraction')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    public friction(value: double | arkui_component_units_Resource | undefined): this {
        if (this.checkPriority('friction')) {
            const value_casted = value as (double | arkui_component_units_Resource | undefined)
            this.getPeer()?.setFrictionAttribute(value_casted)
            return this
        }
        return this
    }
    public scrollSnap(value: ScrollSnapOptions | undefined): this {
        if (this.checkPriority('scrollSnap')) {
            const value_casted = value as (ScrollSnapOptions | undefined)
            this.getPeer()?.setScrollSnapAttribute(value_casted)
            return this
        }
        return this
    }
    public enablePaging(value: boolean | undefined): this {
        if (this.checkPriority('enablePaging')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setEnablePagingAttribute(value_casted)
            return this
        }
        return this
    }
    public initialOffset(value: OffsetOptions | undefined): this {
        if (this.checkPriority('initialOffset')) {
            const value_casted = value as (OffsetOptions | undefined)
            this.getPeer()?.setInitialOffsetAttribute(value_casted)
            return this
        }
        return this
    }
    public edgeEffect(edgeEffect: EdgeEffect | undefined, options?: EdgeEffectOptions): this {
        if (this.checkPriority('edgeEffect')) {
            const edgeEffect_casted = edgeEffect as (EdgeEffect | undefined)
            const options_casted = options as (EdgeEffectOptions | undefined)
            this.getPeer()?.setEdgeEffectAttribute(edgeEffect_casted, options_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ScrollAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookScrollAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function ScrollImpl(
    @memo @memo_skip
    style: ((attributes: ScrollAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkScrollComponent>((): ArkScrollComponent => {
        return new ArkScrollComponent()
    })
    NodeAttach<ArkScrollPeer>((): ArkScrollPeer => ArkScrollPeer.create(receiver), (_: ArkScrollPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class OffsetResult_serializer {
    public static write(buffer: SerializerBase, value: OffsetResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForXOffset  = value.xOffset
        valueSerializer.writeFloat64(valueHolderForXOffset)
        const valueHolderForYOffset  = value.yOffset
        valueSerializer.writeFloat64(valueHolderForYOffset)
    }
    public static read(buffer: DeserializerBase): OffsetResult {
        let valueDeserializer : DeserializerBase = buffer
        const xOffsetTmpResult : double = valueDeserializer.readFloat64()
        const yOffsetTmpResult : double = valueDeserializer.readFloat64()
        let value : OffsetResult = ({xOffset: xOffsetTmpResult, yOffset: yOffsetTmpResult} as OffsetResult)
        return value
    }
}
export class OnScrollFrameBeginHandlerResult_serializer {
    public static write(buffer: SerializerBase, value: OnScrollFrameBeginHandlerResult): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForOffsetRemain  = value.offsetRemain
        valueSerializer.writeFloat64(valueHolderForOffsetRemain)
    }
    public static read(buffer: DeserializerBase): OnScrollFrameBeginHandlerResult {
        let valueDeserializer : DeserializerBase = buffer
        const offsetRemainTmpResult : double = valueDeserializer.readFloat64()
        let value : OnScrollFrameBeginHandlerResult = ({offsetRemain: offsetRemainTmpResult} as OnScrollFrameBeginHandlerResult)
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
        const valueHolderForDuration  = value.duration
        if (valueHolderForDuration !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDurationTmpValue  = valueHolderForDuration!
            valueSerializer.writeInt32(valueHolderForDurationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCurve  = value.curve
        if (valueHolderForCurve !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCurveTmpValue  = valueHolderForCurve!
            if (valueHolderForCurveTmpValue instanceof Curve) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForCurveTmpValueForIdx0  = valueHolderForCurveTmpValue as Curve
                valueSerializer.writeInt32(valueHolderForCurveTmpValueForIdx0.valueOf())
            } else if (valueHolderForCurveTmpValue instanceof ICurve) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForCurveTmpValueForIdx1  = valueHolderForCurveTmpValue as ICurve
                curves_ICurve_serializer.write(valueSerializer, valueHolderForCurveTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForCanOverScroll  = value.canOverScroll
        if (valueHolderForCanOverScroll !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCanOverScrollTmpValue  = valueHolderForCanOverScroll!
            valueSerializer.writeBoolean(valueHolderForCanOverScrollTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollAnimationOptions {
        let valueDeserializer : DeserializerBase = buffer
        const durationTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let durationTmpBuf : int32 | undefined = undefined
        if ((durationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            durationTmpBuf = valueDeserializer.readInt32()
        }
        const durationTmpResult : int32 | undefined = durationTmpBuf
        const curveTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let curveTmpBuf : Curve | ICurve | undefined = undefined
        if ((curveTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const curveTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let curveTmpBufOpt : Curve | ICurve | undefined
            if (curveTmpBufOptUnionSelector == (0).toByte()) {
                curveTmpBufOpt = curves.Curve.fromValue(valueDeserializer.readInt32())
            } else if (curveTmpBufOptUnionSelector == (1).toByte()) {
                curveTmpBufOpt = (curves_ICurve_serializer.read(valueDeserializer) as curves.ICurve)
            } else {
                throw new Error('One of the branches for curveTmpBufOpt has to be chosen through deserialisation.')
            }
            curveTmpBuf = (curveTmpBufOpt as Curve | ICurve)
        }
        const curveTmpResult : Curve | ICurve | undefined = curveTmpBuf
        const canOverScrollTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let canOverScrollTmpBuf : boolean | undefined = undefined
        if ((canOverScrollTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            canOverScrollTmpBuf = valueDeserializer.readBoolean()
        }
        const canOverScrollTmpResult : boolean | undefined = canOverScrollTmpBuf
        let value : ScrollAnimationOptions = ({duration: durationTmpResult, curve: curveTmpResult, canOverScroll: canOverScrollTmpResult} as ScrollAnimationOptions)
        return value
    }
}
export class ScrollEdgeOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollEdgeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForVelocity  = value.velocity
        if (valueHolderForVelocity !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForVelocityTmpValue  = valueHolderForVelocity!
            valueSerializer.writeFloat64(valueHolderForVelocityTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollEdgeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const velocityTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let velocityTmpBuf : double | undefined = undefined
        if ((velocityTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            velocityTmpBuf = valueDeserializer.readFloat64()
        }
        const velocityTmpResult : double | undefined = velocityTmpBuf
        let value : ScrollEdgeOptions = ({velocity: velocityTmpResult} as ScrollEdgeOptions)
        return value
    }
}
export class ScrollPageOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollPageOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNext  = value.next
        valueSerializer.writeBoolean(valueHolderForNext)
        const valueHolderForAnimation  = value.animation
        if (valueHolderForAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAnimationTmpValue  = valueHolderForAnimation!
            valueSerializer.writeBoolean(valueHolderForAnimationTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollPageOptions {
        let valueDeserializer : DeserializerBase = buffer
        const nextTmpResult : boolean = valueDeserializer.readBoolean()
        const animationTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let animationTmpBuf : boolean | undefined = undefined
        if ((animationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            animationTmpBuf = valueDeserializer.readBoolean()
        }
        const animationTmpResult : boolean | undefined = animationTmpBuf
        let value : ScrollPageOptions = ({next: nextTmpResult, animation: animationTmpResult} as ScrollPageOptions)
        return value
    }
}
export class ScrollOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForXOffset  = value.xOffset
        if (valueHolderForXOffset instanceof double) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForXOffsetForIdx0  = valueHolderForXOffset as double
            valueSerializer.writeFloat64(valueHolderForXOffsetForIdx0)
        } else if (valueHolderForXOffset instanceof string) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForXOffsetForIdx1  = valueHolderForXOffset as string
            valueSerializer.writeString(valueHolderForXOffsetForIdx1)
        }
        const valueHolderForYOffset  = value.yOffset
        if (valueHolderForYOffset instanceof double) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForYOffsetForIdx0  = valueHolderForYOffset as double
            valueSerializer.writeFloat64(valueHolderForYOffsetForIdx0)
        } else if (valueHolderForYOffset instanceof string) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForYOffsetForIdx1  = valueHolderForYOffset as string
            valueSerializer.writeString(valueHolderForYOffsetForIdx1)
        }
        const valueHolderForAnimation  = value.animation
        if (valueHolderForAnimation !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForAnimationTmpValue  = valueHolderForAnimation!
            if (valueHolderForAnimationTmpValue instanceof ScrollAnimationOptions) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForAnimationTmpValueForIdx0  = valueHolderForAnimationTmpValue as ScrollAnimationOptions
                ScrollAnimationOptions_serializer.write(valueSerializer, valueHolderForAnimationTmpValueForIdx0)
            } else if (valueHolderForAnimationTmpValue instanceof boolean) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForAnimationTmpValueForIdx1  = valueHolderForAnimationTmpValue as boolean
                valueSerializer.writeBoolean(valueHolderForAnimationTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollOptions {
        let valueDeserializer : DeserializerBase = buffer
        const xOffsetTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let xOffsetTmpBuf : double | string | undefined
        if (xOffsetTmpBufUnionSelector == (0).toByte()) {
            xOffsetTmpBuf = valueDeserializer.readFloat64()
        } else if (xOffsetTmpBufUnionSelector == (1).toByte()) {
            xOffsetTmpBuf = (valueDeserializer.readString() as string)
        } else {
            throw new Error('One of the branches for xOffsetTmpBuf has to be chosen through deserialisation.')
        }
        const xOffsetTmpResult : double | string = (xOffsetTmpBuf as double | string)
        const yOffsetTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let yOffsetTmpBuf : double | string | undefined
        if (yOffsetTmpBufUnionSelector == (0).toByte()) {
            yOffsetTmpBuf = valueDeserializer.readFloat64()
        } else if (yOffsetTmpBufUnionSelector == (1).toByte()) {
            yOffsetTmpBuf = (valueDeserializer.readString() as string)
        } else {
            throw new Error('One of the branches for yOffsetTmpBuf has to be chosen through deserialisation.')
        }
        const yOffsetTmpResult : double | string = (yOffsetTmpBuf as double | string)
        const animationTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let animationTmpBuf : ScrollAnimationOptions | boolean | undefined = undefined
        if ((animationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const animationTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let animationTmpBufOpt : ScrollAnimationOptions | boolean | undefined
            if (animationTmpBufOptUnionSelector == (0).toByte()) {
                animationTmpBufOpt = ScrollAnimationOptions_serializer.read(valueDeserializer)
            } else if (animationTmpBufOptUnionSelector == (1).toByte()) {
                animationTmpBufOpt = valueDeserializer.readBoolean()
            } else {
                throw new Error('One of the branches for animationTmpBufOpt has to be chosen through deserialisation.')
            }
            animationTmpBuf = (animationTmpBufOpt as ScrollAnimationOptions | boolean)
        }
        const animationTmpResult : ScrollAnimationOptions | boolean | undefined = animationTmpBuf
        let value : ScrollOptions = ({xOffset: xOffsetTmpResult, yOffset: yOffsetTmpResult, animation: animationTmpResult} as ScrollOptions)
        return value
    }
}
export class ScrollToIndexOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollToIndexOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForExtraOffset  = value.extraOffset
        if (valueHolderForExtraOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForExtraOffsetTmpValue  = valueHolderForExtraOffset!
            arkui_Graphics_LengthMetrics_serializer.write(valueSerializer, valueHolderForExtraOffsetTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollToIndexOptions {
        let valueDeserializer : DeserializerBase = buffer
        const extraOffsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let extraOffsetTmpBuf : arkui_component_units_LengthMetrics | undefined = undefined
        if ((extraOffsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            extraOffsetTmpBuf = arkui_Graphics_LengthMetrics_serializer.read(valueDeserializer)
        }
        const extraOffsetTmpResult : arkui_component_units_LengthMetrics | undefined = extraOffsetTmpBuf
        let value : ScrollToIndexOptions = ({extraOffset: extraOffsetTmpResult} as ScrollToIndexOptions)
        return value
    }
}
export class OffsetOptions_serializer {
    public static write(buffer: SerializerBase, value: OffsetOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForXOffset  = value.xOffset
        if (valueHolderForXOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForXOffsetTmpValue  = valueHolderForXOffset!
            if (valueHolderForXOffsetTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForXOffsetTmpValueForIdx0  = valueHolderForXOffsetTmpValue as string
                valueSerializer.writeString(valueHolderForXOffsetTmpValueForIdx0)
            } else if (valueHolderForXOffsetTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForXOffsetTmpValueForIdx1  = valueHolderForXOffsetTmpValue as number
                valueSerializer.writeNumber(valueHolderForXOffsetTmpValueForIdx1)
            } else if (valueHolderForXOffsetTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForXOffsetTmpValueForIdx2  = valueHolderForXOffsetTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForXOffsetTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForYOffset  = value.yOffset
        if (valueHolderForYOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForYOffsetTmpValue  = valueHolderForYOffset!
            if (valueHolderForYOffsetTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForYOffsetTmpValueForIdx0  = valueHolderForYOffsetTmpValue as string
                valueSerializer.writeString(valueHolderForYOffsetTmpValueForIdx0)
            } else if (valueHolderForYOffsetTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForYOffsetTmpValueForIdx1  = valueHolderForYOffsetTmpValue as number
                valueSerializer.writeNumber(valueHolderForYOffsetTmpValueForIdx1)
            } else if (valueHolderForYOffsetTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForYOffsetTmpValueForIdx2  = valueHolderForYOffsetTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForYOffsetTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): OffsetOptions {
        let valueDeserializer : DeserializerBase = buffer
        const xOffsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let xOffsetTmpBuf : Dimension | undefined = undefined
        if ((xOffsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const xOffsetTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let xOffsetTmpBufOpt : string | number | global_resource_Resource | undefined
            if (xOffsetTmpBufOptUnionSelector == (0).toByte()) {
                xOffsetTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (xOffsetTmpBufOptUnionSelector == (1).toByte()) {
                xOffsetTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (xOffsetTmpBufOptUnionSelector == (2).toByte()) {
                xOffsetTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for xOffsetTmpBufOpt has to be chosen through deserialisation.')
            }
            xOffsetTmpBuf = (xOffsetTmpBufOpt as string | number | global_resource_Resource)
        }
        const xOffsetTmpResult : Dimension | undefined = xOffsetTmpBuf
        const yOffsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let yOffsetTmpBuf : Dimension | undefined = undefined
        if ((yOffsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const yOffsetTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let yOffsetTmpBufOpt : string | number | global_resource_Resource | undefined
            if (yOffsetTmpBufOptUnionSelector == (0).toByte()) {
                yOffsetTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (yOffsetTmpBufOptUnionSelector == (1).toByte()) {
                yOffsetTmpBufOpt = (valueDeserializer.readNumber() as number)
            } else if (yOffsetTmpBufOptUnionSelector == (2).toByte()) {
                yOffsetTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for yOffsetTmpBufOpt has to be chosen through deserialisation.')
            }
            yOffsetTmpBuf = (yOffsetTmpBufOpt as string | number | global_resource_Resource)
        }
        const yOffsetTmpResult : Dimension | undefined = yOffsetTmpBuf
        let value : OffsetOptions = ({xOffset: xOffsetTmpResult, yOffset: yOffsetTmpResult} as OffsetOptions)
        return value
    }
}
export class ScrollSnapOptions_serializer {
    public static write(buffer: SerializerBase, value: ScrollSnapOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSnapAlign  = value.snapAlign
        valueSerializer.writeInt32(valueHolderForSnapAlign.valueOf())
        const valueHolderForSnapPagination  = value.snapPagination
        if (valueHolderForSnapPagination !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSnapPaginationTmpValue  = valueHolderForSnapPagination!
            if (valueHolderForSnapPaginationTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForSnapPaginationTmpValueForIdx0  = valueHolderForSnapPaginationTmpValue as Dimension
                if (valueHolderForSnapPaginationTmpValueForIdx0 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForSnapPaginationTmpValueForIdx0ForIdx0  = valueHolderForSnapPaginationTmpValueForIdx0 as string
                    valueSerializer.writeString(valueHolderForSnapPaginationTmpValueForIdx0ForIdx0)
                } else if (valueHolderForSnapPaginationTmpValueForIdx0 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForSnapPaginationTmpValueForIdx0ForIdx1  = valueHolderForSnapPaginationTmpValueForIdx0 as number
                    valueSerializer.writeNumber(valueHolderForSnapPaginationTmpValueForIdx0ForIdx1)
                } else if (valueHolderForSnapPaginationTmpValueForIdx0 instanceof global_resource_Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForSnapPaginationTmpValueForIdx0ForIdx2  = valueHolderForSnapPaginationTmpValueForIdx0 as global_resource_Resource
                    global_resource_Resource_serializer.write(valueSerializer, valueHolderForSnapPaginationTmpValueForIdx0ForIdx2)
                }
            } else if (valueHolderForSnapPaginationTmpValue instanceof Array) {
                if (valueHolderForSnapPaginationTmpValue.length == 0) {
                    valueSerializer.writeInt8((1).toByte())
                    valueSerializer.writeInt32(0)
                } else {
                    const valueHolderForSnapPaginationTmpValueElem  = valueHolderForSnapPaginationTmpValue[0]
                    if (valueHolderForSnapPaginationTmpValueElem instanceof Dimension) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForSnapPaginationTmpValueForIdx1  = valueHolderForSnapPaginationTmpValue as Array<Dimension>
                        valueSerializer.writeInt32((valueHolderForSnapPaginationTmpValueForIdx1.length).toInt())
                        for (let valueHolderForSnapPaginationTmpValueForIdx1CounterI = 0; valueHolderForSnapPaginationTmpValueForIdx1CounterI < valueHolderForSnapPaginationTmpValueForIdx1.length; valueHolderForSnapPaginationTmpValueForIdx1CounterI++) {
                            const valueHolderForSnapPaginationTmpValueForIdx1TmpElement : Dimension = valueHolderForSnapPaginationTmpValueForIdx1[valueHolderForSnapPaginationTmpValueForIdx1CounterI]
                            if (valueHolderForSnapPaginationTmpValueForIdx1TmpElement instanceof string) {
                                valueSerializer.writeInt8((0).toByte())
                                const valueHolderForSnapPaginationTmpValueForIdx1TmpElementForIdx0  = valueHolderForSnapPaginationTmpValueForIdx1TmpElement as string
                                valueSerializer.writeString(valueHolderForSnapPaginationTmpValueForIdx1TmpElementForIdx0)
                            } else if (valueHolderForSnapPaginationTmpValueForIdx1TmpElement instanceof number) {
                                valueSerializer.writeInt8((1).toByte())
                                const valueHolderForSnapPaginationTmpValueForIdx1TmpElementForIdx1  = valueHolderForSnapPaginationTmpValueForIdx1TmpElement as number
                                valueSerializer.writeNumber(valueHolderForSnapPaginationTmpValueForIdx1TmpElementForIdx1)
                            } else if (valueHolderForSnapPaginationTmpValueForIdx1TmpElement instanceof global_resource_Resource) {
                                valueSerializer.writeInt8((2).toByte())
                                const valueHolderForSnapPaginationTmpValueForIdx1TmpElementForIdx2  = valueHolderForSnapPaginationTmpValueForIdx1TmpElement as global_resource_Resource
                                global_resource_Resource_serializer.write(valueSerializer, valueHolderForSnapPaginationTmpValueForIdx1TmpElementForIdx2)
                            }
                        }
                    }
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableSnapToStart  = value.enableSnapToStart
        if (valueHolderForEnableSnapToStart !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableSnapToStartTmpValue  = valueHolderForEnableSnapToStart!
            valueSerializer.writeBoolean(valueHolderForEnableSnapToStartTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEnableSnapToEnd  = value.enableSnapToEnd
        if (valueHolderForEnableSnapToEnd !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEnableSnapToEndTmpValue  = valueHolderForEnableSnapToEnd!
            valueSerializer.writeBoolean(valueHolderForEnableSnapToEndTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ScrollSnapOptions {
        let valueDeserializer : DeserializerBase = buffer
        const snapAlignTmpResult : ScrollSnapAlign = ScrollSnapAlign.fromValue(valueDeserializer.readInt32())
        const snapPaginationTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let snapPaginationTmpBuf : Dimension | Array<Dimension> | undefined = undefined
        if ((snapPaginationTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const snapPaginationTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let snapPaginationTmpBufOpt : Dimension | Array<Dimension> | undefined
            if (snapPaginationTmpBufOptUnionSelector == (0).toByte()) {
                const snapPaginationTmpBufOptBufUUnionSelector : int32 = valueDeserializer.readInt8()
                let snapPaginationTmpBufOptBufU : string | number | global_resource_Resource | undefined
                if (snapPaginationTmpBufOptBufUUnionSelector == (0).toByte()) {
                    snapPaginationTmpBufOptBufU = (valueDeserializer.readString() as string)
                } else if (snapPaginationTmpBufOptBufUUnionSelector == (1).toByte()) {
                    snapPaginationTmpBufOptBufU = (valueDeserializer.readNumber() as number)
                } else if (snapPaginationTmpBufOptBufUUnionSelector == (2).toByte()) {
                    snapPaginationTmpBufOptBufU = global_resource_Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error('One of the branches for snapPaginationTmpBufOptBufU has to be chosen through deserialisation.')
                }
                snapPaginationTmpBufOpt = (snapPaginationTmpBufOptBufU as string | number | global_resource_Resource)
            } else if (snapPaginationTmpBufOptUnionSelector == (1).toByte()) {
                const snapPaginationTmpBufOptBufULength : int32 = valueDeserializer.readInt32()
                let snapPaginationTmpBufOptBufU : Array<Dimension> = new Array<Dimension>(snapPaginationTmpBufOptBufULength)
                for (let snapPaginationTmpBufOptBufUBufCounterI = 0; snapPaginationTmpBufOptBufUBufCounterI < snapPaginationTmpBufOptBufULength; snapPaginationTmpBufOptBufUBufCounterI++) {
                    const snapPaginationTmpBufOptBufUTempBufUnionSelector : int32 = valueDeserializer.readInt8()
                    let snapPaginationTmpBufOptBufUTempBuf : string | number | global_resource_Resource | undefined
                    if (snapPaginationTmpBufOptBufUTempBufUnionSelector == (0).toByte()) {
                        snapPaginationTmpBufOptBufUTempBuf = (valueDeserializer.readString() as string)
                    } else if (snapPaginationTmpBufOptBufUTempBufUnionSelector == (1).toByte()) {
                        snapPaginationTmpBufOptBufUTempBuf = (valueDeserializer.readNumber() as number)
                    } else if (snapPaginationTmpBufOptBufUTempBufUnionSelector == (2).toByte()) {
                        snapPaginationTmpBufOptBufUTempBuf = global_resource_Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error('One of the branches for snapPaginationTmpBufOptBufUTempBuf has to be chosen through deserialisation.')
                    }
                    snapPaginationTmpBufOptBufU[snapPaginationTmpBufOptBufUBufCounterI] = (snapPaginationTmpBufOptBufUTempBuf as string | number | global_resource_Resource)
                }
                snapPaginationTmpBufOpt = snapPaginationTmpBufOptBufU
            } else {
                throw new Error('One of the branches for snapPaginationTmpBufOpt has to be chosen through deserialisation.')
            }
            snapPaginationTmpBuf = (snapPaginationTmpBufOpt as Dimension | Array<Dimension>)
        }
        const snapPaginationTmpResult : Dimension | Array<Dimension> | undefined = snapPaginationTmpBuf
        const enableSnapToStartTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableSnapToStartTmpBuf : boolean | undefined = undefined
        if ((enableSnapToStartTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableSnapToStartTmpBuf = valueDeserializer.readBoolean()
        }
        const enableSnapToStartTmpResult : boolean | undefined = enableSnapToStartTmpBuf
        const enableSnapToEndTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let enableSnapToEndTmpBuf : boolean | undefined = undefined
        if ((enableSnapToEndTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            enableSnapToEndTmpBuf = valueDeserializer.readBoolean()
        }
        const enableSnapToEndTmpResult : boolean | undefined = enableSnapToEndTmpBuf
        let value : ScrollSnapOptions = ({snapAlign: snapAlignTmpResult, snapPagination: snapPaginationTmpResult, enableSnapToStart: enableSnapToStartTmpResult, enableSnapToEnd: enableSnapToEndTmpResult} as ScrollSnapOptions)
        return value
    }
}
