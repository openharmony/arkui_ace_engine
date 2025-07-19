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
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ConstraintSizeOptions_serializer, ConstraintSizeOptions, Length, Dimension, Padding, Padding_serializer } from "./units"
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkScrollableCommonMethodSet, ArkCommonMethodSet } from "./common"
import { FlexDirection, ScrollSource } from "./enums"
import { OnScrollFrameBeginCallback, Scroller, Scroller_serializer } from "./scroll"
import { ScrollState } from "./list"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { CustomBuilder } from "./builder"
import { ComponentContent, ComponentContent_serializer } from "./../generated/arkui.ComponentContent"
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
    constructor() {
        this(WaterFlowSections.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_construct()
        return retval
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
        thisSerializer.writeInt8((deleteCount_type).toChar())
        if ((deleteCount_type) != (RuntimeType.UNDEFINED)) {
            const deleteCount_value  = deleteCount!
            thisSerializer.writeNumber(deleteCount_value)
        }
        let sections_type : int32 = RuntimeType.UNDEFINED
        sections_type = runtimeType(sections)
        thisSerializer.writeInt8((sections_type).toChar())
        if ((sections_type) != (RuntimeType.UNDEFINED)) {
            const sections_value  = sections!
            thisSerializer.writeInt32((sections_value.length).toInt())
            for (let sections_value_counter_i = 0; sections_value_counter_i < sections_value.length; sections_value_counter_i++) {
                const sections_value_element : SectionOptions = sections_value[sections_value_counter_i]
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
        thisSerializer.writeInt8((options_type).toChar())
        if ((options_type) != (RuntimeType.UNDEFINED)) {
            const options_value  = options!
            WaterFlowOptions_serializer.write(thisSerializer, options_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowInterface_setWaterFlowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setColumnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemConstraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            ConstraintSizeOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setItemConstraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setRowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setColumnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setRowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutDirectionAttribute(value: FlexDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as FlexDirection)
            thisSerializer.writeInt32(TypeChecker.FlexDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setLayoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollIndexAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setOnScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount1Attribute(count: number | undefined, show: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8((count_type).toChar())
        if ((count_type) != (RuntimeType.UNDEFINED)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let show_type : int32 = RuntimeType.UNDEFINED
        show_type = runtimeType(show)
        thisSerializer.writeInt8((show_type).toChar())
        if ((show_type) != (RuntimeType.UNDEFINED)) {
            const show_value  = show!
            thisSerializer.writeBoolean(show_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setCachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    columnsTemplate(value: string | undefined): this {
        throw new Error("Unimplemented method columnsTemplate")
    }
    itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        throw new Error("Unimplemented method itemConstraintSize")
    }
    rowsTemplate(value: string | undefined): this {
        throw new Error("Unimplemented method rowsTemplate")
    }
    columnsGap(value: Length | undefined): this {
        throw new Error("Unimplemented method columnsGap")
    }
    rowsGap(value: Length | undefined): this {
        throw new Error("Unimplemented method rowsGap")
    }
    layoutDirection(value: FlexDirection | undefined): this {
        throw new Error("Unimplemented method layoutDirection")
    }
    cachedCount(value: number | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        throw new Error("Unimplemented method onScrollFrameBegin")
    }
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        throw new Error("Unimplemented method onScrollIndex")
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        throw new Error("Unimplemented method onWillScroll")
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        throw new Error("Unimplemented method onDidScroll")
    }
    cachedCount(count: number | undefined, show: boolean | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
    public cachedCount(value: number | undefined): this {
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
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
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
            this.getPeer()?.setColumnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        if (this.checkPriority("itemConstraintSize")) {
            const value_casted = value as (ConstraintSizeOptions | undefined)
            this.getPeer()?.setItemConstraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        if (this.checkPriority("rowsTemplate")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setRowsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public columnsGap(value: Length | undefined): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setColumnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsGap(value: Length | undefined): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setRowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutDirection(value: FlexDirection | undefined): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (FlexDirection | undefined)
            this.getPeer()?.setLayoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(value: number | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
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
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.setOnScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (OnWillScrollCallback | undefined)
            this.getPeer()?.setOnWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (OnScrollCallback | undefined)
            this.getPeer()?.setOnDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const count_casted = count as (number | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("WaterFlow")
// export function WaterFlow(
//     options?: WaterFlowOptions,
//     @memo
//     content_?: () => void,
// ): WaterFlowAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function WaterFlow(
    @memo
    style: ((attributes: WaterFlowAttribute) => void) | undefined,
    options?: WaterFlowOptions,
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

export class ArkWaterFlowSet extends ArkScrollableCommonMethodSet implements WaterFlowAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _columnsTemplate_flag?: boolean
    _columnsTemplate0_value?: string | undefined
    _itemConstraintSize_flag?: boolean
    _itemConstraintSize0_value?: ConstraintSizeOptions | undefined
    _rowsTemplate_flag?: boolean
    _rowsTemplate0_value?: string | undefined
    _columnsGap_flag?: boolean
    _columnsGap0_value?: Length | undefined
    _rowsGap_flag?: boolean
    _rowsGap0_value?: Length | undefined
    _layoutDirection_flag?: boolean
    _layoutDirection0_value?: FlexDirection | undefined
    _cachedCount_flag?: boolean
    _cachedCount0_value?: number | undefined
    _cachedCount1_value?: boolean | undefined
    _onScrollFrameBegin_flag?: boolean
    _onScrollFrameBegin0_value?: OnScrollFrameBeginCallback | undefined
    _onScrollIndex_flag?: boolean
    _onScrollIndex0_value?: ((first: number,last: number) => void) | undefined
    _onWillScroll_flag?: boolean
    _onWillScroll0_value?: OnWillScrollCallback | undefined
    _onDidScroll_flag?: boolean
    _onDidScroll0_value?: OnScrollCallback | undefined
    applyModifierPatch(component: WaterFlowAttribute): void {
        if (this._columnsTemplate_flag)
            component.columnsTemplate((this._columnsTemplate0_value as string | undefined))
        if (this._itemConstraintSize_flag)
            component.itemConstraintSize((this._itemConstraintSize0_value as ConstraintSizeOptions | undefined))
        if (this._rowsTemplate_flag)
            component.rowsTemplate((this._rowsTemplate0_value as string | undefined))
        if (this._columnsGap_flag)
            component.columnsGap((this._columnsGap0_value as Length | undefined))
        if (this._rowsGap_flag)
            component.rowsGap((this._rowsGap0_value as Length | undefined))
        if (this._layoutDirection_flag)
            component.layoutDirection((this._layoutDirection0_value as FlexDirection | undefined))
        if (this._cachedCount_flag)
            component.cachedCount((this._cachedCount0_value as number | undefined), (this._cachedCount1_value as boolean | undefined))
        if (this._onScrollFrameBegin_flag)
            component.onScrollFrameBegin((this._onScrollFrameBegin0_value as OnScrollFrameBeginCallback | undefined))
        if (this._onScrollIndex_flag)
            component.onScrollIndex((this._onScrollIndex0_value as ((first: number,last: number) => void) | undefined))
        if (this._onWillScroll_flag)
            component.onWillScroll((this._onWillScroll0_value as OnWillScrollCallback | undefined))
        if (this._onDidScroll_flag)
            component.onDidScroll((this._onDidScroll0_value as OnScrollCallback | undefined))
    }
    public columnsTemplate(value: string | undefined): this {
        this._columnsTemplate_flag = true
        this._columnsTemplate0_value = value
        return this
    }
    public itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        this._itemConstraintSize_flag = true
        this._itemConstraintSize0_value = value
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        this._rowsTemplate_flag = true
        this._rowsTemplate0_value = value
        return this
    }
    public columnsGap(value: Length | undefined): this {
        this._columnsGap_flag = true
        this._columnsGap0_value = value
        return this
    }
    public rowsGap(value: Length | undefined): this {
        this._rowsGap_flag = true
        this._rowsGap0_value = value
        return this
    }
    public layoutDirection(value: FlexDirection | undefined): this {
        this._layoutDirection_flag = true
        this._layoutDirection0_value = value
        return this
    }
    public cachedCount(count: number | undefined, show: boolean | undefined): this {
        this._cachedCount_flag = true
        this._cachedCount0_value = count
        this._cachedCount1_value = show
        return this
    }
    public onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        this._onScrollFrameBegin_flag = true
        this._onScrollFrameBegin0_value = value
        return this
    }
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        this._onScrollIndex_flag = true
        this._onScrollIndex0_value = value
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        this._onWillScroll_flag = true
        this._onWillScroll0_value = value
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        this._onDidScroll_flag = true
        this._onDidScroll0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        valueSerializer.writeInt8((value_footer_type).toChar())
        if ((value_footer_type) != (RuntimeType.UNDEFINED)) {
            const value_footer_value  = value_footer!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_footer_value))
        }
        const value_footerContent  = value.footerContent
        let value_footerContent_type : int32 = RuntimeType.UNDEFINED
        value_footerContent_type = runtimeType(value_footerContent)
        valueSerializer.writeInt8((value_footerContent_type).toChar())
        if ((value_footerContent_type) != (RuntimeType.UNDEFINED)) {
            const value_footerContent_value  = value_footerContent!
            ComponentContent_serializer.write(valueSerializer, value_footerContent_value)
        }
        const value_scroller  = value.scroller
        let value_scroller_type : int32 = RuntimeType.UNDEFINED
        value_scroller_type = runtimeType(value_scroller)
        valueSerializer.writeInt8((value_scroller_type).toChar())
        if ((value_scroller_type) != (RuntimeType.UNDEFINED)) {
            const value_scroller_value  = value_scroller!
            Scroller_serializer.write(valueSerializer, value_scroller_value)
        }
        const value_sections  = value.sections
        let value_sections_type : int32 = RuntimeType.UNDEFINED
        value_sections_type = runtimeType(value_sections)
        valueSerializer.writeInt8((value_sections_type).toChar())
        if ((value_sections_type) != (RuntimeType.UNDEFINED)) {
            const value_sections_value  = value_sections!
            WaterFlowSections_serializer.write(valueSerializer, value_sections_value)
        }
        const value_layoutMode  = value.layoutMode
        let value_layoutMode_type : int32 = RuntimeType.UNDEFINED
        value_layoutMode_type = runtimeType(value_layoutMode)
        valueSerializer.writeInt8((value_layoutMode_type).toChar())
        if ((value_layoutMode_type) != (RuntimeType.UNDEFINED)) {
            const value_layoutMode_value  = (value_layoutMode as WaterFlowLayoutMode)
            valueSerializer.writeInt32(TypeChecker.WaterFlowLayoutMode_ToNumeric(value_layoutMode_value))
        }
    }
    public static read(buffer: DeserializerBase): WaterFlowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const footer_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let footer_buf : CustomBuilder | undefined
        if ((footer_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        const footerContent_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let footerContent_buf : ComponentContent | undefined
        if ((footerContent_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            footerContent_buf = (ComponentContent_serializer.read(valueDeserializer) as ComponentContent)
        }
        const footerContent_result : ComponentContent | undefined = footerContent_buf
        const scroller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scroller_buf : Scroller | undefined
        if ((scroller_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scroller_buf = (Scroller_serializer.read(valueDeserializer) as Scroller)
        }
        const scroller_result : Scroller | undefined = scroller_buf
        const sections_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sections_buf : WaterFlowSections | undefined
        if ((sections_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            sections_buf = (WaterFlowSections_serializer.read(valueDeserializer) as WaterFlowSections)
        }
        const sections_result : WaterFlowSections | undefined = sections_buf
        const layoutMode_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let layoutMode_buf : WaterFlowLayoutMode | undefined
        if ((layoutMode_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_crossCount_type).toChar())
        if ((value_crossCount_type) != (RuntimeType.UNDEFINED)) {
            const value_crossCount_value  = value_crossCount!
            valueSerializer.writeNumber(value_crossCount_value)
        }
        const value_onGetItemMainSizeByIndex  = value.onGetItemMainSizeByIndex
        let value_onGetItemMainSizeByIndex_type : int32 = RuntimeType.UNDEFINED
        value_onGetItemMainSizeByIndex_type = runtimeType(value_onGetItemMainSizeByIndex)
        valueSerializer.writeInt8((value_onGetItemMainSizeByIndex_type).toChar())
        if ((value_onGetItemMainSizeByIndex_type) != (RuntimeType.UNDEFINED)) {
            const value_onGetItemMainSizeByIndex_value  = value_onGetItemMainSizeByIndex!
            valueSerializer.holdAndWriteCallback(value_onGetItemMainSizeByIndex_value)
        }
        const value_columnsGap  = value.columnsGap
        let value_columnsGap_type : int32 = RuntimeType.UNDEFINED
        value_columnsGap_type = runtimeType(value_columnsGap)
        valueSerializer.writeInt8((value_columnsGap_type).toChar())
        if ((value_columnsGap_type) != (RuntimeType.UNDEFINED)) {
            const value_columnsGap_value  = value_columnsGap!
            let value_columnsGap_value_type : int32 = RuntimeType.UNDEFINED
            value_columnsGap_value_type = runtimeType(value_columnsGap_value)
            if (RuntimeType.STRING == value_columnsGap_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_columnsGap_value_0  = value_columnsGap_value as string
                valueSerializer.writeString(value_columnsGap_value_0)
            }
            else if (RuntimeType.NUMBER == value_columnsGap_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_columnsGap_value_1  = value_columnsGap_value as number
                valueSerializer.writeNumber(value_columnsGap_value_1)
            }
            else if (RuntimeType.OBJECT == value_columnsGap_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_columnsGap_value_2  = value_columnsGap_value as Resource
                Resource_serializer.write(valueSerializer, value_columnsGap_value_2)
            }
        }
        const value_rowsGap  = value.rowsGap
        let value_rowsGap_type : int32 = RuntimeType.UNDEFINED
        value_rowsGap_type = runtimeType(value_rowsGap)
        valueSerializer.writeInt8((value_rowsGap_type).toChar())
        if ((value_rowsGap_type) != (RuntimeType.UNDEFINED)) {
            const value_rowsGap_value  = value_rowsGap!
            let value_rowsGap_value_type : int32 = RuntimeType.UNDEFINED
            value_rowsGap_value_type = runtimeType(value_rowsGap_value)
            if (RuntimeType.STRING == value_rowsGap_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_rowsGap_value_0  = value_rowsGap_value as string
                valueSerializer.writeString(value_rowsGap_value_0)
            }
            else if (RuntimeType.NUMBER == value_rowsGap_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_rowsGap_value_1  = value_rowsGap_value as number
                valueSerializer.writeNumber(value_rowsGap_value_1)
            }
            else if (RuntimeType.OBJECT == value_rowsGap_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_rowsGap_value_2  = value_rowsGap_value as Resource
                Resource_serializer.write(valueSerializer, value_rowsGap_value_2)
            }
        }
        const value_margin  = value.margin
        let value_margin_type : int32 = RuntimeType.UNDEFINED
        value_margin_type = runtimeType(value_margin)
        valueSerializer.writeInt8((value_margin_type).toChar())
        if ((value_margin_type) != (RuntimeType.UNDEFINED)) {
            const value_margin_value  = value_margin!
            let value_margin_value_type : int32 = RuntimeType.UNDEFINED
            value_margin_value_type = runtimeType(value_margin_value)
            if (TypeChecker.isPadding(value_margin_value, false, false, false, false)) {
                valueSerializer.writeInt8((0).toChar())
                const value_margin_value_0  = value_margin_value as Padding
                Padding_serializer.write(valueSerializer, value_margin_value_0)
            }
            else if ((RuntimeType.STRING == value_margin_value_type) || (RuntimeType.NUMBER == value_margin_value_type) || (RuntimeType.OBJECT == value_margin_value_type)) {
                valueSerializer.writeInt8((1).toChar())
                const value_margin_value_1  = value_margin_value as Dimension
                let value_margin_value_1_type : int32 = RuntimeType.UNDEFINED
                value_margin_value_1_type = runtimeType(value_margin_value_1)
                if (RuntimeType.STRING == value_margin_value_1_type) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_margin_value_1_0  = value_margin_value_1 as string
                    valueSerializer.writeString(value_margin_value_1_0)
                }
                else if (RuntimeType.NUMBER == value_margin_value_1_type) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_margin_value_1_1  = value_margin_value_1 as number
                    valueSerializer.writeNumber(value_margin_value_1_1)
                }
                else if (RuntimeType.OBJECT == value_margin_value_1_type) {
                    valueSerializer.writeInt8((2).toChar())
                    const value_margin_value_1_2  = value_margin_value_1 as Resource
                    Resource_serializer.write(valueSerializer, value_margin_value_1_2)
                }
            }
        }
    }
    public static read(buffer: DeserializerBase): SectionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const itemsCount_result : number = (valueDeserializer.readNumber() as number)
        const crossCount_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let crossCount_buf : number | undefined
        if ((crossCount_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            crossCount_buf = (valueDeserializer.readNumber() as number)
        }
        const crossCount_result : number | undefined = crossCount_buf
        const onGetItemMainSizeByIndex_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onGetItemMainSizeByIndex_buf : GetItemMainSizeByIndex | undefined
        if ((onGetItemMainSizeByIndex_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        const columnsGap_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let columnsGap_buf : Dimension | undefined
        if ((columnsGap_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const columnsGap_buf__selector : int32 = valueDeserializer.readInt8()
            let columnsGap_buf_ : string | number | Resource | undefined
            if (columnsGap_buf__selector == (0).toChar()) {
                columnsGap_buf_ = (valueDeserializer.readString() as string)
            }
            else if (columnsGap_buf__selector == (1).toChar()) {
                columnsGap_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (columnsGap_buf__selector == (2).toChar()) {
                columnsGap_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for columnsGap_buf_ has to be chosen through deserialisation.")
            }
            columnsGap_buf = (columnsGap_buf_ as string | number | Resource)
        }
        const columnsGap_result : Dimension | undefined = columnsGap_buf
        const rowsGap_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rowsGap_buf : Dimension | undefined
        if ((rowsGap_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const rowsGap_buf__selector : int32 = valueDeserializer.readInt8()
            let rowsGap_buf_ : string | number | Resource | undefined
            if (rowsGap_buf__selector == (0).toChar()) {
                rowsGap_buf_ = (valueDeserializer.readString() as string)
            }
            else if (rowsGap_buf__selector == (1).toChar()) {
                rowsGap_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (rowsGap_buf__selector == (2).toChar()) {
                rowsGap_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for rowsGap_buf_ has to be chosen through deserialisation.")
            }
            rowsGap_buf = (rowsGap_buf_ as string | number | Resource)
        }
        const rowsGap_result : Dimension | undefined = rowsGap_buf
        const margin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let margin_buf : Padding | Dimension | undefined
        if ((margin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const margin_buf__selector : int32 = valueDeserializer.readInt8()
            let margin_buf_ : Padding | Dimension | undefined
            if (margin_buf__selector == (0).toChar()) {
                margin_buf_ = Padding_serializer.read(valueDeserializer)
            }
            else if (margin_buf__selector == (1).toChar()) {
                const margin_buf__u_selector : int32 = valueDeserializer.readInt8()
                let margin_buf__u : string | number | Resource | undefined
                if (margin_buf__u_selector == (0).toChar()) {
                    margin_buf__u = (valueDeserializer.readString() as string)
                }
                else if (margin_buf__u_selector == (1).toChar()) {
                    margin_buf__u = (valueDeserializer.readNumber() as number)
                }
                else if (margin_buf__u_selector == (2).toChar()) {
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
