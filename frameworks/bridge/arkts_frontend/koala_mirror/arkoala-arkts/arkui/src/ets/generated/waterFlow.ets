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
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ConstraintSizeOptions_serializer, ConstraintSizeOptions, Length, Dimension, Padding, Padding_serializer } from "./units"
import { Resource_serializer, Resource } from "./resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { FlexDirection, ScrollSource } from "./enums"
import { OnScrollFrameBeginCallback, Scroller, Scroller_serializer } from "./scroll"
import { ScrollState } from "./list"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { CustomBuilder } from "./builder"
import { ComponentContent, ComponentContent_serializer } from "./ark.ComponentContent"
import { NodeAttach, remember } from "@koalaui/runtime"
export class WaterFlowSectionsInternal {
    public static fromPtr(ptr: KPointer): WaterFlowSections {
        return new WaterFlowSections(ptr)
    }
}
export class WaterFlowSections implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, WaterFlowSections.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_ctor()
        return retval
    }
    constructor() {
        this(WaterFlowSections.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._WaterFlowSections_getFinalizer()
    }
    public splice(start: number, deleteCount?: number, sections?: Array<SectionOptions>): boolean {
        const start_casted = start as (number)
        const deleteCount_casted = deleteCount as (number | undefined)
        const sections_casted = sections as (Array<SectionOptions> | undefined)
        return this.splice_serialize(start_casted, deleteCount_casted, sections_casted)
    }
    public push(section: SectionOptions): boolean {
        const section_casted = section as (SectionOptions)
        return this.push_serialize(section_casted)
    }
    public update(sectionIndex: number, section: SectionOptions): boolean {
        const sectionIndex_casted = sectionIndex as (number)
        const section_casted = section as (SectionOptions)
        return this.update_serialize(sectionIndex_casted, section_casted)
    }
    public values(): Array<SectionOptions> {
        return this.values_serialize()
    }
    public length(): number {
        return this.length_serialize()
    }
    private splice_serialize(start: number, deleteCount?: number, sections?: Array<SectionOptions>): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let deleteCount_type : int32 = RuntimeType.UNDEFINED
        deleteCount_type = runtimeType(deleteCount)
        thisSerializer.writeInt8(deleteCount_type)
        if ((RuntimeType.UNDEFINED) != (deleteCount_type)) {
            const deleteCount_value  = deleteCount!
            thisSerializer.writeNumber(deleteCount_value)
        }
        let sections_type : int32 = RuntimeType.UNDEFINED
        sections_type = runtimeType(sections)
        thisSerializer.writeInt8(sections_type)
        if ((RuntimeType.UNDEFINED) != (sections_type)) {
            const sections_value  = sections!
            thisSerializer.writeInt32(sections_value.length as int32)
            for (let i = 0; i < sections_value.length; i++) {
                const sections_value_element : SectionOptions = sections_value[i]
                SectionOptions_serializer.write(thisSerializer, sections_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_splice(this.peer!.ptr, start, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private push_serialize(section: SectionOptions): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SectionOptions_serializer.write(thisSerializer, section)
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_push(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private update_serialize(sectionIndex: number, section: SectionOptions): boolean {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        SectionOptions_serializer.write(thisSerializer, section)
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_update(this.peer!.ptr, sectionIndex, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private values_serialize(): Array<SectionOptions> {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_values(this.peer!.ptr)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<SectionOptions> = new Array<SectionOptions>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = SectionOptions_serializer.read(retvalDeserializer)
        }
        const returnResult : Array<SectionOptions> = buffer
        return returnResult
    }
    private length_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_length(this.peer!.ptr)
        return retval
    }
}
export class ArkWaterFlowPeer extends ArkScrollableCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWaterFlowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WaterFlow_construct(peerId, flags)
        const _peer  = new ArkWaterFlowPeer(_peerPtr, peerId, "WaterFlow", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWaterFlowOptionsAttribute(options?: WaterFlowOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            WaterFlowOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowInterface_setWaterFlowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_columnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    itemConstraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            ConstraintSizeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_itemConstraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_rowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_columnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_rowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutDirectionAttribute(value: FlexDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FlexDirection)
            thisSerializer.writeInt32(TypeChecker.FlexDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_layoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_cachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount1Attribute(count: number | undefined, show: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8(count_type)
        if ((RuntimeType.UNDEFINED) != (count_type)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let show_type : int32 = RuntimeType.UNDEFINED
        show_type = runtimeType(show)
        thisSerializer.writeInt8(show_type)
        if ((RuntimeType.UNDEFINED) != (show_type)) {
            const show_value  = show!
            thisSerializer.writeBoolean(show_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_cachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type GetItemMainSizeByIndex = (index: number) => number;
export interface SectionOptions {
    itemsCount: number;
    crossCount?: number | undefined;
    onGetItemMainSizeByIndex?: GetItemMainSizeByIndex | undefined;
    columnsGap?: Dimension | undefined;
    rowsGap?: Dimension | undefined;
    margin?: Padding | Dimension | undefined;
}
export enum WaterFlowLayoutMode {
    ALWAYS_TOP_DOWN = 0,
    SLIDING_WINDOW = 1
}
export interface WaterFlowOptions {
    footer?: CustomBuilder;
    footerContent?: ComponentContent;
    scroller?: Scroller;
    sections?: WaterFlowSections;
    layoutMode?: WaterFlowLayoutMode;
}
export interface WaterFlowAttribute extends ScrollableCommonMethod {
    columnsTemplate(value: string | undefined): this
    itemConstraintSize(value: ConstraintSizeOptions | undefined): this
    rowsTemplate(value: string | undefined): this
    columnsGap(value: Length | undefined): this
    rowsGap(value: Length | undefined): this
    layoutDirection(value: FlexDirection | undefined): this
    cachedCount(count: number | undefined, show?: boolean): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this
    onWillScroll(value: OnWillScrollCallback | undefined): this
    onDidScroll(value: OnScrollCallback | undefined): this
    attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkWaterFlowStyle extends ArkScrollableCommonMethodStyle implements WaterFlowAttribute {
    columnsTemplate_value?: string | undefined
    itemConstraintSize_value?: ConstraintSizeOptions | undefined
    rowsTemplate_value?: string | undefined
    columnsGap_value?: Length | undefined
    rowsGap_value?: Length | undefined
    layoutDirection_value?: FlexDirection | undefined
    cachedCount_value?: number | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onScrollIndex_value?: ((first: number,last: number) => void) | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
    attributeModifier_value?: AttributeModifier<WaterFlowAttribute> | AttributeModifier<CommonMethod> | undefined
    public columnsTemplate(value: string | undefined): this {
        return this
    }
    public itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        return this
    }
    public columnsGap(value: Length | undefined): this {
        return this
    }
    public rowsGap(value: Length | undefined): this {
        return this
    }
    public layoutDirection(value: FlexDirection | undefined): this {
        return this
    }
    public cachedCount(count: number | undefined, show?: boolean): this {
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        return this
    }
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: WaterFlowAttribute): void {
        super.apply(target)
        if (this.columnsTemplate_value !== undefined)
            target.columnsTemplate(this.columnsTemplate_value!)
        if (this.itemConstraintSize_value !== undefined)
            target.itemConstraintSize(this.itemConstraintSize_value!)
        if (this.rowsTemplate_value !== undefined)
            target.rowsTemplate(this.rowsTemplate_value!)
        if (this.columnsGap_value !== undefined)
            target.columnsGap(this.columnsGap_value!)
        if (this.rowsGap_value !== undefined)
            target.rowsGap(this.rowsGap_value!)
        if (this.layoutDirection_value !== undefined)
            target.layoutDirection(this.layoutDirection_value!)
        if (this.cachedCount_value !== undefined)
            target.cachedCount(this.cachedCount_value!)
        if (this.onScrollFrameBegin_value !== undefined)
            target.onScrollFrameBegin(this.onScrollFrameBegin_value!)
        if (this.onScrollIndex_value !== undefined)
            target.onScrollIndex(this.onScrollIndex_value!)
        if (this.onWillScroll_value !== undefined)
            target.onWillScroll(this.onWillScroll_value!)
        if (this.onDidScroll_value !== undefined)
            target.onDidScroll(this.onDidScroll_value!)
    }
}

export class ArkWaterFlowComponent extends ArkScrollableCommonMethodComponent implements WaterFlowAttribute {
    getPeer(): ArkWaterFlowPeer {
        return (this.peer as ArkWaterFlowPeer)
    }
    public setWaterFlowOptions(options?: WaterFlowOptions): this {
        if (this.checkPriority("setWaterFlowOptions")) {
            const options_casted = options as (WaterFlowOptions | undefined)
            this.getPeer()?.setWaterFlowOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public columnsTemplate(value: string | undefined): this {
        if (this.checkPriority("columnsTemplate")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.columnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        if (this.checkPriority("itemConstraintSize")) {
            const value_casted = value as (ConstraintSizeOptions | undefined)
            this.getPeer()?.itemConstraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        if (this.checkPriority("rowsTemplate")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.rowsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public columnsGap(value: Length | undefined): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.columnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsGap(value: Length | undefined): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.rowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutDirection(value: FlexDirection | undefined): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (FlexDirection | undefined)
            this.getPeer()?.layoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(count: number | undefined, show?: boolean): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(count)
            const show_type = runtimeType(show)
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) && (RuntimeType.UNDEFINED == show_type)) {
                const value_casted = count as (number | undefined)
                this.getPeer()?.cachedCount0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) && ((RuntimeType.BOOLEAN == show_type) || (RuntimeType.UNDEFINED == show_type))) {
                const count_casted = count as (number | undefined)
                const show_casted = show as (boolean | undefined)
                this.getPeer()?.cachedCount1Attribute(count_casted, show_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
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
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (OnWillScrollCallback | undefined)
            this.getPeer()?.onWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (OnScrollCallback | undefined)
            this.getPeer()?.onDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withWaterFlowStyle(receiver: WaterFlowAttribute, modifier: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkWaterFlowStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("WaterFlowImpl")
export function WaterFlow(
    options?: WaterFlowOptions | undefined,
    @memo
    content_?: () => void,
): WaterFlowAttribute {
    throw new Error("Not implemented")
}

@memo
export function WaterFlowImpl(
    @memo
    style: ((attributes: WaterFlowAttribute) => void) | undefined,
    options?: WaterFlowOptions | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkWaterFlowComponent>((): ArkWaterFlowComponent => {
        return new ArkWaterFlowComponent()
    })
    NodeAttach<ArkWaterFlowPeer>((): ArkWaterFlowPeer => ArkWaterFlowPeer.create(receiver), (_: ArkWaterFlowPeer): void => {
        receiver.setWaterFlowOptions(options)
        style?.(receiver)
        withWaterFlowStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class WaterFlowSections_serializer {
    public static write(buffer: SerializerBase, value: WaterFlowSections): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): WaterFlowSections {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return WaterFlowSectionsInternal.fromPtr(ptr)
    }
}
export class WaterFlowOptions_serializer {
    public static write(buffer: SerializerBase, value: WaterFlowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_footer  = value.footer
        let value_footer_type : int32 = RuntimeType.UNDEFINED
        value_footer_type = runtimeType(value_footer)
        valueSerializer.writeInt8(value_footer_type)
        if ((RuntimeType.UNDEFINED) != (value_footer_type)) {
            const value_footer_value  = value_footer!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_footer_value))
        }
        const value_footerContent  = value.footerContent
        let value_footerContent_type : int32 = RuntimeType.UNDEFINED
        value_footerContent_type = runtimeType(value_footerContent)
        valueSerializer.writeInt8(value_footerContent_type)
        if ((RuntimeType.UNDEFINED) != (value_footerContent_type)) {
            const value_footerContent_value  = value_footerContent!
            ComponentContent_serializer.write(valueSerializer, value_footerContent_value)
        }
        const value_scroller  = value.scroller
        let value_scroller_type : int32 = RuntimeType.UNDEFINED
        value_scroller_type = runtimeType(value_scroller)
        valueSerializer.writeInt8(value_scroller_type)
        if ((RuntimeType.UNDEFINED) != (value_scroller_type)) {
            const value_scroller_value  = value_scroller!
            Scroller_serializer.write(valueSerializer, value_scroller_value)
        }
        const value_sections  = value.sections
        let value_sections_type : int32 = RuntimeType.UNDEFINED
        value_sections_type = runtimeType(value_sections)
        valueSerializer.writeInt8(value_sections_type)
        if ((RuntimeType.UNDEFINED) != (value_sections_type)) {
            const value_sections_value  = value_sections!
            WaterFlowSections_serializer.write(valueSerializer, value_sections_value)
        }
        const value_layoutMode  = value.layoutMode
        let value_layoutMode_type : int32 = RuntimeType.UNDEFINED
        value_layoutMode_type = runtimeType(value_layoutMode)
        valueSerializer.writeInt8(value_layoutMode_type)
        if ((RuntimeType.UNDEFINED) != (value_layoutMode_type)) {
            const value_layoutMode_value  = (value_layoutMode as WaterFlowLayoutMode)
            valueSerializer.writeInt32(TypeChecker.WaterFlowLayoutMode_ToNumeric(value_layoutMode_value))
        }
    }
    public static read(buffer: DeserializerBase): WaterFlowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const footer_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let footer_buf : CustomBuilder | undefined
        if ((RuntimeType.UNDEFINED) != (footer_buf_runtimeType))
        {
            const footer_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const footer_buf__call : KPointer = valueDeserializer.readPointer()
            const footer_buf__callSync : KPointer = valueDeserializer.readPointer()
            footer_buf = ():void => { 
    const footer_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    footer_buf__argsSerializer.writeInt32(footer_buf__resource.resourceId);
    footer_buf__argsSerializer.writePointer(footer_buf__call);
    footer_buf__argsSerializer.writePointer(footer_buf__callSync);
    InteropNativeModule._CallCallback(737226752, footer_buf__argsSerializer.asBuffer(), footer_buf__argsSerializer.length());
    footer_buf__argsSerializer.release();
    return; }
        }
        const footer_result : CustomBuilder | undefined = footer_buf
        const footerContent_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let footerContent_buf : ComponentContent | undefined
        if ((RuntimeType.UNDEFINED) != (footerContent_buf_runtimeType))
        {
            footerContent_buf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const footerContent_result : ComponentContent | undefined = footerContent_buf
        const scroller_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let scroller_buf : Scroller | undefined
        if ((RuntimeType.UNDEFINED) != (scroller_buf_runtimeType))
        {
            scroller_buf = (Scroller_serializer.read(valueDeserializer) as Scroller)
        }
        const scroller_result : Scroller | undefined = scroller_buf
        const sections_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let sections_buf : WaterFlowSections | undefined
        if ((RuntimeType.UNDEFINED) != (sections_buf_runtimeType))
        {
            sections_buf = (WaterFlowSections_serializer.read(valueDeserializer) as WaterFlowSections)
        }
        const sections_result : WaterFlowSections | undefined = sections_buf
        const layoutMode_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let layoutMode_buf : WaterFlowLayoutMode | undefined
        if ((RuntimeType.UNDEFINED) != (layoutMode_buf_runtimeType))
        {
            layoutMode_buf = TypeChecker.WaterFlowLayoutMode_FromNumeric(valueDeserializer.readInt32())
        }
        const layoutMode_result : WaterFlowLayoutMode | undefined = layoutMode_buf
        let value : WaterFlowOptions = ({footer: footer_result, footerContent: footerContent_result, scroller: scroller_result, sections: sections_result, layoutMode: layoutMode_result} as WaterFlowOptions)
        return value
    }
}
export class SectionOptions_serializer {
    public static write(buffer: SerializerBase, value: SectionOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_itemsCount  = value.itemsCount
        valueSerializer.writeNumber(value_itemsCount)
        const value_crossCount  = value.crossCount
        let value_crossCount_type : int32 = RuntimeType.UNDEFINED
        value_crossCount_type = runtimeType(value_crossCount)
        valueSerializer.writeInt8(value_crossCount_type)
        if ((RuntimeType.UNDEFINED) != (value_crossCount_type)) {
            const value_crossCount_value  = value_crossCount!
            valueSerializer.writeNumber(value_crossCount_value)
        }
        const value_onGetItemMainSizeByIndex  = value.onGetItemMainSizeByIndex
        let value_onGetItemMainSizeByIndex_type : int32 = RuntimeType.UNDEFINED
        value_onGetItemMainSizeByIndex_type = runtimeType(value_onGetItemMainSizeByIndex)
        valueSerializer.writeInt8(value_onGetItemMainSizeByIndex_type)
        if ((RuntimeType.UNDEFINED) != (value_onGetItemMainSizeByIndex_type)) {
            const value_onGetItemMainSizeByIndex_value  = value_onGetItemMainSizeByIndex!
            valueSerializer.holdAndWriteCallback(value_onGetItemMainSizeByIndex_value)
        }
        const value_columnsGap  = value.columnsGap
        let value_columnsGap_type : int32 = RuntimeType.UNDEFINED
        value_columnsGap_type = runtimeType(value_columnsGap)
        valueSerializer.writeInt8(value_columnsGap_type)
        if ((RuntimeType.UNDEFINED) != (value_columnsGap_type)) {
            const value_columnsGap_value  = value_columnsGap!
            let value_columnsGap_value_type : int32 = RuntimeType.UNDEFINED
            value_columnsGap_value_type = runtimeType(value_columnsGap_value)
            if (RuntimeType.STRING == value_columnsGap_value_type) {
                valueSerializer.writeInt8(0)
                const value_columnsGap_value_0  = value_columnsGap_value as string
                valueSerializer.writeString(value_columnsGap_value_0)
            }
            else if (RuntimeType.NUMBER == value_columnsGap_value_type) {
                valueSerializer.writeInt8(1)
                const value_columnsGap_value_1  = value_columnsGap_value as number
                valueSerializer.writeNumber(value_columnsGap_value_1)
            }
            else if (RuntimeType.OBJECT == value_columnsGap_value_type) {
                valueSerializer.writeInt8(2)
                const value_columnsGap_value_2  = value_columnsGap_value as Resource
                Resource_serializer.write(valueSerializer, value_columnsGap_value_2)
            }
        }
        const value_rowsGap  = value.rowsGap
        let value_rowsGap_type : int32 = RuntimeType.UNDEFINED
        value_rowsGap_type = runtimeType(value_rowsGap)
        valueSerializer.writeInt8(value_rowsGap_type)
        if ((RuntimeType.UNDEFINED) != (value_rowsGap_type)) {
            const value_rowsGap_value  = value_rowsGap!
            let value_rowsGap_value_type : int32 = RuntimeType.UNDEFINED
            value_rowsGap_value_type = runtimeType(value_rowsGap_value)
            if (RuntimeType.STRING == value_rowsGap_value_type) {
                valueSerializer.writeInt8(0)
                const value_rowsGap_value_0  = value_rowsGap_value as string
                valueSerializer.writeString(value_rowsGap_value_0)
            }
            else if (RuntimeType.NUMBER == value_rowsGap_value_type) {
                valueSerializer.writeInt8(1)
                const value_rowsGap_value_1  = value_rowsGap_value as number
                valueSerializer.writeNumber(value_rowsGap_value_1)
            }
            else if (RuntimeType.OBJECT == value_rowsGap_value_type) {
                valueSerializer.writeInt8(2)
                const value_rowsGap_value_2  = value_rowsGap_value as Resource
                Resource_serializer.write(valueSerializer, value_rowsGap_value_2)
            }
        }
        const value_margin  = value.margin
        let value_margin_type : int32 = RuntimeType.UNDEFINED
        value_margin_type = runtimeType(value_margin)
        valueSerializer.writeInt8(value_margin_type)
        if ((RuntimeType.UNDEFINED) != (value_margin_type)) {
            const value_margin_value  = value_margin!
            let value_margin_value_type : int32 = RuntimeType.UNDEFINED
            value_margin_value_type = runtimeType(value_margin_value)
            if (TypeChecker.isPadding(value_margin_value, false, false, false, false)) {
                valueSerializer.writeInt8(0)
                const value_margin_value_0  = value_margin_value as Padding
                Padding_serializer.write(valueSerializer, value_margin_value_0)
            }
            else if ((RuntimeType.STRING == value_margin_value_type) || (RuntimeType.NUMBER == value_margin_value_type) || (RuntimeType.OBJECT == value_margin_value_type)) {
                valueSerializer.writeInt8(1)
                const value_margin_value_1  = value_margin_value as Dimension
                let value_margin_value_1_type : int32 = RuntimeType.UNDEFINED
                value_margin_value_1_type = runtimeType(value_margin_value_1)
                if (RuntimeType.STRING == value_margin_value_1_type) {
                    valueSerializer.writeInt8(0)
                    const value_margin_value_1_0  = value_margin_value_1 as string
                    valueSerializer.writeString(value_margin_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_margin_value_1_type) {
                    valueSerializer.writeInt8(1)
                    const value_margin_value_1_1  = value_margin_value_1 as number
                    valueSerializer.writeNumber(value_margin_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_margin_value_1_type) {
                    valueSerializer.writeInt8(2)
                    const value_margin_value_1_2  = value_margin_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_margin_value_1_2)
                }
            }
        }
    }
    public static read(buffer: DeserializerBase): SectionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const itemsCount_result : number = (valueDeserializer.readNumber() as number)
        const crossCount_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let crossCount_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (crossCount_buf_runtimeType))
        {
            crossCount_buf = (valueDeserializer.readNumber() as number)
        }
        const crossCount_result : number | undefined = crossCount_buf
        const onGetItemMainSizeByIndex_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let onGetItemMainSizeByIndex_buf : GetItemMainSizeByIndex | undefined
        if ((RuntimeType.UNDEFINED) != (onGetItemMainSizeByIndex_buf_runtimeType))
        {
            const onGetItemMainSizeByIndex_buf__resource : CallbackResource = valueDeserializer.readCallbackResource()
            const onGetItemMainSizeByIndex_buf__call : KPointer = valueDeserializer.readPointer()
            const onGetItemMainSizeByIndex_buf__callSync : KPointer = valueDeserializer.readPointer()
            onGetItemMainSizeByIndex_buf = (index: number):number => { 
    const onGetItemMainSizeByIndex_buf__argsSerializer : SerializerBase = SerializerBase.hold();
    onGetItemMainSizeByIndex_buf__argsSerializer.writeInt32(onGetItemMainSizeByIndex_buf__resource.resourceId);
    onGetItemMainSizeByIndex_buf__argsSerializer.writePointer(onGetItemMainSizeByIndex_buf__call);
    onGetItemMainSizeByIndex_buf__argsSerializer.writePointer(onGetItemMainSizeByIndex_buf__callSync);
    onGetItemMainSizeByIndex_buf__argsSerializer.writeNumber(index);
    let onGetItemMainSizeByIndex_buf__continuationValue : number | undefined;
    const onGetItemMainSizeByIndex_buf__continuationCallback : ((value: number) => void) = (value: number):void => {     onGetItemMainSizeByIndex_buf__continuationValue = value; }
    onGetItemMainSizeByIndex_buf__argsSerializer.holdAndWriteCallback(onGetItemMainSizeByIndex_buf__continuationCallback);
    InteropNativeModule._CallCallback(-2076995110, onGetItemMainSizeByIndex_buf__argsSerializer.asBuffer(), onGetItemMainSizeByIndex_buf__argsSerializer.length());
    onGetItemMainSizeByIndex_buf__argsSerializer.release();
    return (onGetItemMainSizeByIndex_buf__continuationValue as number); }
        }
        const onGetItemMainSizeByIndex_result : GetItemMainSizeByIndex | undefined = onGetItemMainSizeByIndex_buf
        const columnsGap_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let columnsGap_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (columnsGap_buf_runtimeType))
        {
            const columnsGap_buf__selector : int32 = valueDeserializer.readInt8()
            let columnsGap_buf_ : string | number | Resource | undefined
            if (columnsGap_buf__selector == 0) {
                columnsGap_buf_ = (valueDeserializer.readString() as string)
            }
            else if (columnsGap_buf__selector == 1) {
                columnsGap_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (columnsGap_buf__selector == 2) {
                columnsGap_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for columnsGap_buf_ has to be chosen through deserialisation.")
            }
            columnsGap_buf = (columnsGap_buf_ as string | number | Resource)
        }
        const columnsGap_result : Dimension | undefined = columnsGap_buf
        const rowsGap_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let rowsGap_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (rowsGap_buf_runtimeType))
        {
            const rowsGap_buf__selector : int32 = valueDeserializer.readInt8()
            let rowsGap_buf_ : string | number | Resource | undefined
            if (rowsGap_buf__selector == 0) {
                rowsGap_buf_ = (valueDeserializer.readString() as string)
            }
            else if (rowsGap_buf__selector == 1) {
                rowsGap_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (rowsGap_buf__selector == 2) {
                rowsGap_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for rowsGap_buf_ has to be chosen through deserialisation.")
            }
            rowsGap_buf = (rowsGap_buf_ as string | number | Resource)
        }
        const rowsGap_result : Dimension | undefined = rowsGap_buf
        const margin_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let margin_buf : Padding | Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (margin_buf_runtimeType))
        {
            const margin_buf__selector : int32 = valueDeserializer.readInt8()
            let margin_buf_ : Padding | Dimension | undefined
            if (margin_buf__selector == 0) {
                margin_buf_ = Padding_serializer.read(valueDeserializer)
            }
            else if (margin_buf__selector == 1) {
                const margin_buf__u_selector : int32 = valueDeserializer.readInt8()
                let margin_buf__u : string | number | Resource | undefined
                if (margin_buf__u_selector == 0) {
                    margin_buf__u = (valueDeserializer.readString() as string)
                }
                else if (margin_buf__u_selector == 1) {
                    margin_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (margin_buf__u_selector == 2) {
                    margin_buf__u = Resource_serializer.read(valueDeserializer)
                }
                else {
                    throw new Error("One of the branches for margin_buf__u has to be chosen through deserialisation.")
                }
                margin_buf_ = (margin_buf__u as string | number | Resource)
            }
            else {
                throw new Error("One of the branches for margin_buf_ has to be chosen through deserialisation.")
            }
            margin_buf = (margin_buf_ as Padding | Dimension)
        }
        const margin_result : Padding | Dimension | undefined = margin_buf
        let value : SectionOptions = ({itemsCount: itemsCount_result, crossCount: crossCount_result, onGetItemMainSizeByIndex: onGetItemMainSizeByIndex_result, columnsGap: columnsGap_result, rowsGap: rowsGap_result, margin: margin_result} as SectionOptions)
        return value
    }
}
