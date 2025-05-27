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
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, NestedScrollOptions, CustomBuilder, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, UIScrollableCommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethod, UICommonMethod } from "./common"
import { ConstraintSizeOptions, Length, Dimension, Padding } from "./units"
import { FlexDirection } from "./enums"
import { Resource } from "./resource"
import { Callback_Void } from "./ability_component"
import { Callback_Number_ScrollState_Literal_Number_offsetRemain, Literal_Number_offsetRemain, Callback_Number_Number_Void } from "./grid"
import { ScrollState } from "./list"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { Scroller } from "./scroll"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWaterFlowPeer {
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
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeWaterFlowOptions(options_value)
        }
        ArkUIGeneratedNativeModule._WaterFlowInterface_setWaterFlowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    columnsTemplateAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WaterFlowAttribute_columnsTemplate(this.peer.ptr, value)
    }
    itemConstraintSizeAttribute(value: ConstraintSizeOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeConstraintSizeOptions(value)
        ArkUIGeneratedNativeModule._WaterFlowAttribute_itemConstraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsTemplateAttribute(value: string): void {
        ArkUIGeneratedNativeModule._WaterFlowAttribute_rowsTemplate(this.peer.ptr, value)
    }
    columnsGapAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_columnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    rowsGapAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_rowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    layoutDirectionAttribute(value: FlexDirection): void {
        ArkUIGeneratedNativeModule._WaterFlowAttribute_layoutDirection(this.peer.ptr, TypeChecker.FlexDirection_ToNumeric(value))
    }
    nestedScrollAttribute(value: NestedScrollOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNestedScrollOptions(value)
        ArkUIGeneratedNativeModule._WaterFlowAttribute_nestedScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableScrollInteractionAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._WaterFlowAttribute_enableScrollInteraction(this.peer.ptr, value ? 1 : 0)
    }
    frictionAttribute(value: number | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as Resource
            thisSerializer.writeResource(value_1)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_friction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    cachedCount0Attribute(value: number): void {
        ArkUIGeneratedNativeModule._WaterFlowAttribute_cachedCount0(this.peer.ptr, value)
    }
    cachedCount1Attribute(count: number, show: boolean): void {
        ArkUIGeneratedNativeModule._WaterFlowAttribute_cachedCount1(this.peer.ptr, count, show ? 1 : 0)
    }
    onReachStartAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onReachStart(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReachEndAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onReachEnd(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollFrameBeginAttribute(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onScrollIndexAttribute(value: ((first: number,last: number) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._WaterFlowAttribute_onScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    scroller?: Scroller;
    sections?: WaterFlowSections;
    layoutMode?: WaterFlowLayoutMode;
}

export interface WaterFlowAttribute extends ScrollableCommonMethod {
    columnsTemplate(value: string): this
    itemConstraintSize(value: ConstraintSizeOptions): this
    rowsTemplate(value: string): this
    columnsGap(value: Length): this
    rowsGap(value: Length): this
    layoutDirection(value: FlexDirection): this
    nestedScroll(value: NestedScrollOptions): this
    enableScrollInteraction(value: boolean): this
    friction(value: number | Resource): this
    cachedCount(count: number, show?: boolean): this
    onReachStart(value: (() => void)): this
    onReachEnd(value: (() => void)): this
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this
    onScrollIndex(value: ((first: number,last: number) => void)): this
    attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIWaterFlowAttribute extends UIScrollableCommonMethod {
    @memo
    columnsTemplate(value: string): this
    @memo
    itemConstraintSize(value: ConstraintSizeOptions): this
    @memo
    rowsTemplate(value: string): this
    @memo
    columnsGap(value: Length): this
    @memo
    rowsGap(value: Length): this
    @memo
    layoutDirection(value: FlexDirection): this
    @memo
    nestedScroll(value: NestedScrollOptions): this
    @memo
    enableScrollInteraction(value: boolean): this
    @memo
    friction(value: number | Resource): this
    @memo
    cachedCount(count: number, show?: boolean): this
    @memo
    onReachStart(value: (() => void)): this
    @memo
    onReachEnd(value: (() => void)): this
    @memo
    onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this
    @memo
    onScrollIndex(value: ((first: number,last: number) => void)): this
    @memo
    attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkWaterFlowStyle extends ArkScrollableCommonMethodStyle implements WaterFlowAttribute {
    columnsTemplate_value?: string
    itemConstraintSize_value?: ConstraintSizeOptions
    rowsTemplate_value?: string
    columnsGap_value?: Length
    rowsGap_value?: Length
    layoutDirection_value?: FlexDirection
    nestedScroll_value?: NestedScrollOptions
    enableScrollInteraction_value?: boolean
    friction_value?: number | Resource
    cachedCount_value?: number
    onReachStart_value?: (() => void)
    onReachEnd_value?: (() => void)
    onScrollFrameBegin_value?: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)
    onScrollIndex_value?: ((first: number,last: number) => void)
    public columnsTemplate(value: string): this {
        return this
    }
    public itemConstraintSize(value: ConstraintSizeOptions): this {
        return this
    }
    public rowsTemplate(value: string): this {
        return this
    }
    public columnsGap(value: Length): this {
        return this
    }
    public rowsGap(value: Length): this {
        return this
    }
    public layoutDirection(value: FlexDirection): this {
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
    public cachedCount(count: number, show?: boolean): this {
        return this
    }
    public onReachStart(value: (() => void)): this {
        return this
    }
    public onReachEnd(value: (() => void)): this {
        return this
    }
    public onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this {
        return this
    }
    public onScrollIndex(value: ((first: number,last: number) => void)): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkWaterFlowComponent extends ArkScrollableCommonMethodComponent implements UIWaterFlowAttribute {
    getPeer(): ArkWaterFlowPeer {
        return (this.peer as ArkWaterFlowPeer)
    }
    @memo
    public setWaterFlowOptions(options?: WaterFlowOptions): this {
        if (this.checkPriority("setWaterFlowOptions")) {
            const options_casted = options as (WaterFlowOptions | undefined)
            this.getPeer()?.setWaterFlowOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    @memo
    public columnsTemplate(value: string): this {
        if (this.checkPriority("columnsTemplate")) {
            const value_casted = value as (string)
            this.getPeer()?.columnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public itemConstraintSize(value: ConstraintSizeOptions): this {
        if (this.checkPriority("itemConstraintSize")) {
            const value_casted = value as (ConstraintSizeOptions)
            this.getPeer()?.itemConstraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public rowsTemplate(value: string): this {
        if (this.checkPriority("rowsTemplate")) {
            const value_casted = value as (string)
            this.getPeer()?.rowsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public columnsGap(value: Length): this {
        if (this.checkPriority("columnsGap")) {
            const value_casted = value as (Length)
            this.getPeer()?.columnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public rowsGap(value: Length): this {
        if (this.checkPriority("rowsGap")) {
            const value_casted = value as (Length)
            this.getPeer()?.rowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public layoutDirection(value: FlexDirection): this {
        if (this.checkPriority("layoutDirection")) {
            const value_casted = value as (FlexDirection)
            this.getPeer()?.layoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public nestedScroll(value: NestedScrollOptions): this {
        if (this.checkPriority("nestedScroll")) {
            const value_casted = value as (NestedScrollOptions)
            this.getPeer()?.nestedScrollAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public enableScrollInteraction(value: boolean): this {
        if (this.checkPriority("enableScrollInteraction")) {
            const value_casted = value as (boolean)
            this.getPeer()?.enableScrollInteractionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public friction(value: number | Resource): this {
        if (this.checkPriority("friction")) {
            const value_casted = value as (number | Resource)
            this.getPeer()?.frictionAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public cachedCount(count: number, show?: boolean): this {
        if (this.checkPriority("cachedCount")) {
            const count_type = runtimeType(count)
            const show_type = runtimeType(show)
            const value_casted = count as (number)
            this.getPeer()?.cachedCount0Attribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onReachStart(value: (() => void)): this {
        if (this.checkPriority("onReachStart")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachStartAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onReachEnd(value: (() => void)): this {
        if (this.checkPriority("onReachEnd")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onReachEndAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onScrollFrameBegin(value: ((offset: number,state: ScrollState) => Literal_Number_offsetRemain)): this {
        if (this.checkPriority("onScrollFrameBegin")) {
            const value_casted = value as (((offset: number,state: ScrollState) => Literal_Number_offsetRemain))
            this.getPeer()?.onScrollFrameBeginAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onScrollIndex(value: ((first: number,last: number) => void)): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: number,last: number) => void))
            this.getPeer()?.onScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("WaterFlow")
export function WaterFlow(
    options?: WaterFlowOptions,
    @memo
    content_?: () => void,
): WaterFlowAttribute {
    throw new Error("Not implemented")
}

@memo
export function WaterFlow(
    @memo
    style: ((attributes: UIWaterFlowAttribute) => void) | undefined,
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
        content_?.()
        receiver.applyAttributesFinish()
    })
}
