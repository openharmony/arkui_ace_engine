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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, CustomBuilder, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, OnWillScrollCallback, OnScrollCallback } from "./common"
import { ConstraintSizeOptions, Length, Dimension, Padding } from "./units"
import { FlexDirection } from "./enums"
import { Resource } from "global/resource"
import { Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain, Callback_Number_Number_Void } from "./grid"
import { ScrollState } from "./list"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentContent } from "./arkui-custom"
import { Scroller, OnScrollFrameBeginCallback } from "./scroll"

export class WaterFlowSectionsInternal {
    public static fromPtr(ptr: KPointer): WaterFlowSections {
        const obj : WaterFlowSections = new WaterFlowSections()
        obj.peer = new Finalizable(ptr, WaterFlowSections.getFinalizer())
        return obj
    }
}
export class WaterFlowSections implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_waterflowsections(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = WaterFlowSections.ctor_waterflowsections()
        this.peer = new Finalizable(ctorPtr, WaterFlowSections.getFinalizer())
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
        const thisSerializer : Serializer = Serializer.hold()
        let deleteCount_type : int32 = RuntimeType.UNDEFINED
        deleteCount_type = runtimeType(deleteCount)
        thisSerializer.writeInt8(deleteCount_type as int32)
        if ((RuntimeType.UNDEFINED) != (deleteCount_type)) {
            const deleteCount_value  = deleteCount!
            thisSerializer.writeNumber(deleteCount_value)
        }
        let sections_type : int32 = RuntimeType.UNDEFINED
        sections_type = runtimeType(sections)
        thisSerializer.writeInt8(sections_type as int32)
        if ((RuntimeType.UNDEFINED) != (sections_type)) {
            const sections_value  = sections!
            thisSerializer.writeInt32(sections_value.length as int32)
            for (let i = 0; i < sections_value.length; i++) {
                const sections_value_element : SectionOptions = sections_value[i]
                thisSerializer.writeSectionOptions(sections_value_element)
            }
        }
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_splice(this.peer!.ptr, start, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private push_serialize(section: SectionOptions): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSectionOptions(section)
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_push(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private update_serialize(sectionIndex: number, section: SectionOptions): boolean {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeSectionOptions(section)
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_update(this.peer!.ptr, sectionIndex, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private values_serialize(): Array<SectionOptions> {
        const retval  = ArkUIGeneratedNativeModule._WaterFlowSections_values(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<SectionOptions> = new Array<SectionOptions>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = retvalDeserializer.readSectionOptions()
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkWaterFlowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WaterFlow_construct(peerId, flags)
        const _peer  = new ArkWaterFlowPeer(_peerPtr, peerId, "WaterFlow", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWaterFlowOptionsAttribute(options?: WaterFlowOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeWaterFlowOptions(options_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowInterface_setWaterFlowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_columnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    itemConstraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeConstraintSizeOptions(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_itemConstraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_rowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsGapAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_columnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsGapAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_rowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutDirectionAttribute(value: FlexDirection | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as FlexDirection)
            thisSerializer.writeInt32(TypeChecker.FlexDirection_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_layoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._WaterFlowAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._WaterFlowAttribute_enableScrollInteraction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._WaterFlowAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount0Attribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_cachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount1Attribute(count: number | undefined, show: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let count_type : int32 = RuntimeType.UNDEFINED
        count_type = runtimeType(count)
        thisSerializer.writeInt8(count_type as int32)
        if ((RuntimeType.UNDEFINED) != (count_type)) {
            const count_value  = count!
            thisSerializer.writeNumber(count_value)
        }
        let show_type : int32 = RuntimeType.UNDEFINED
        show_type = runtimeType(show)
        thisSerializer.writeInt8(show_type as int32)
        if ((RuntimeType.UNDEFINED) != (show_type)) {
            const show_value  = show!
            thisSerializer.writeBoolean(show_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_cachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachStartAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((first: number,last: number) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._GridAttribute_onWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer: Serializer = Serializer.hold();
        let value_type: int32 = RuntimeType.UNDEFINED;
        value_type = runtimeType(value);
        thisSerializer.writeInt8(value_type as int32);
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value = value!;
            thisSerializer.holdAndWriteCallback(value_value);
        }
        ArkUIGeneratedNativeModule._GridAttribute_onDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length());
        thisSerializer.release();
    }
}
export type GetItemMainSizeByIndex = (index: number) => number;
export interface SectionOptions {
    itemsCount: number;
    crossCount?: number;
    onGetItemMainSizeByIndex?: GetItemMainSizeByIndex;
    columnsGap?: Dimension;
    rowsGap?: Dimension;
    margin?: Padding | Dimension;
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
export type WaterFlowInterface = (options?: WaterFlowOptions) => WaterFlowAttribute;
export interface WaterFlowAttribute extends ScrollableCommonMethod {
    columnsTemplate(value: string | undefined): this
    itemConstraintSize(value: ConstraintSizeOptions | undefined): this
    rowsTemplate(value: string | undefined): this
    columnsGap(value: Length | undefined): this
    rowsGap(value: Length | undefined): this
    layoutDirection(value: FlexDirection | undefined): this
    nestedScroll(value: NestedScrollOptions | undefined): this
    enableScrollInteraction(value: boolean | undefined): this
    friction(value: number | Resource | undefined): this
    cachedCount(count: number | undefined, show?: boolean): this
    onReachStart(value: (() => void) | undefined): this
    onReachEnd(value: (() => void) | undefined): this
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this
    onScrollIndex(value: ((first: number,last: number) => void) | undefined): this
    onWillScroll(value: OnWillScrollCallback | undefined): this
    onDidScroll(value: OnScrollCallback | undefined): this
}
export class ArkWaterFlowStyle extends ArkScrollableCommonMethodStyle implements WaterFlowAttribute {
    columnsTemplate_value?: string | undefined
    itemConstraintSize_value?: ConstraintSizeOptions | undefined
    rowsTemplate_value?: string | undefined
    columnsGap_value?: Length | undefined
    rowsGap_value?: Length | undefined
    layoutDirection_value?: FlexDirection | undefined
    nestedScroll_value?: NestedScrollOptions | undefined
    enableScrollInteraction_value?: boolean | undefined
    friction_value?: number | Resource | undefined
    cachedCount_value?: number | undefined
    onReachStart_value?: (() => void) | undefined
    onReachEnd_value?: (() => void) | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onScrollIndex_value?: ((first: number,last: number) => void) | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
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
    public nestedScroll(value: NestedScrollOptions | undefined): this {
        return this
    }
    public enableScrollInteraction(value: boolean | undefined): this {
        return this
    }
    public friction(value: number | Resource | undefined): this {
        return this
    }
    public cachedCount(count: number | undefined, show?: boolean): this {
        return this
    }
    public onReachStart(value: (() => void) | undefined): this {
        return this
    }
    public onReachEnd(value: (() => void) | undefined): this {
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
    public onReachStart(value: (() => void) | undefined): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    public onReachEnd(value: (() => void) | undefined): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onReachEndAttribute(value_casted)
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
    public onScrollIndex(value: ((first: number,last: number) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: number,last: number) => void) | undefined)
            this.getPeer()?.onScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value?: OnWillScrollCallback | undefined): this {
        if (this.checkPriority("onWillScroll")) {
            const value_casted = value as (OnWillScrollCallback | undefined)
            this.getPeer()?.onWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value?: OnScrollCallback | undefined): this {
        if (this.checkPriority("onDidScroll")) {
            const value_casted = value as (OnScrollCallback | undefined)
            this.getPeer()?.onDidScrollAttribute(value_casted)
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
export function WaterFlow(
    /** @memo */
    style: ((attributes: WaterFlowAttribute) => void) | undefined,
    options?: WaterFlowOptions,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkWaterFlowComponent()
    })
    NodeAttach<ArkWaterFlowPeer>((): ArkWaterFlowPeer => ArkWaterFlowPeer.create(receiver), (_: ArkWaterFlowPeer) => {
        receiver.setWaterFlowOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
