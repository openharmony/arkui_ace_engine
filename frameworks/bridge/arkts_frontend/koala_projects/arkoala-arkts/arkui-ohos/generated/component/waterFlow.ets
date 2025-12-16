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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ArkThemeScopeManager } from "#arktheme"
import { ConstraintSizeOptions_serializer, ConstraintSizeOptions, Length, Dimension, Padding, Padding_serializer } from "./units"
import { Resource_serializer } from "./../framework/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkScrollableCommonMethodStyle, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource } from "global.resource"
import { FlexDirection, ScrollSource } from "./enums"
import { OnScrollFrameBeginCallback, Scroller, Scroller_serializer } from "./scroll"
import { ScrollState } from "./list"
import { AttributeModifier, hookWaterFlowAttributeModifier, AttributeUpdater, hookWaterFlowOptionsImpl } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier';
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { CustomBuilder } from "./builder"
import { ComponentContentBase } from "arkui.ComponentContent"
import { WaterFlowModifier } from "./../WaterFlowModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkWaterFlowPeer extends ArkScrollableCommonMethodPeer {
    attributeSet?: WaterFlowModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWaterFlowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WaterFlow_construct(peerId, flags)
        const _peer  = new ArkWaterFlowPeer(_peerPtr, peerId, 'WaterFlow', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWaterFlowOptionsAttribute(options?: WaterFlowOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (options !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const optionsTmpValue  = options!
            WaterFlowOptions_serializer.write(thisSerializer, optionsTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowInterface_setWaterFlowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setColumnsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setItemConstraintSizeAttribute(value: ConstraintSizeOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            ConstraintSizeOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setItemConstraintSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsTemplateAttribute(value: string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeString(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setRowsTemplate(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColumnsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setColumnsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRowsGapAttribute(value: Length | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setRowsGap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLayoutDirectionAttribute(value: FlexDirection | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = (value as FlexDirection)
            thisSerializer.writeInt32(valueTmpValue.valueOf())
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setLayoutDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount0Attribute(value: int32 | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setCachedCount0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setOnScrollFrameBegin(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnScrollIndexAttribute(value: ((first: int32,last: int32) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setOnScrollIndex(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnWillScrollAttribute(value: OnWillScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setOnWillScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDidScrollAttribute(value: OnScrollCallback | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setOnDidScroll(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCachedCount1Attribute(count: int32 | undefined, show: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (count !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const countTmpValue  = count!
            thisSerializer.writeInt32(countTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (show !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const showTmpValue  = show!
            thisSerializer.writeBoolean(showTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WaterFlowAttribute_setCachedCount1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type GetItemMainSizeByIndex = (index: int32) => double;
export class SectionOptions {
    itemsCount: int32;
    crossCount?: int32 | undefined;
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
    footerContent?: ComponentContentBase;
    scroller?: Scroller;
    sections?: WaterFlowSections;
    layoutMode?: WaterFlowLayoutMode;
}
export interface WaterFlowAttribute extends ScrollableCommonMethod {
    setWaterFlowOptions(options?: WaterFlowOptions): this {
        throw new Error("Unimplemented method setWaterFlowOptions")
    }
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
    cachedCount(value: int32 | undefined): this {
        throw new Error("Unimplemented method cachedCount")
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        throw new Error("Unimplemented method onScrollFrameBegin")
    }
    onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        throw new Error("Unimplemented method onScrollIndex")
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        throw new Error("Unimplemented method onWillScroll")
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        throw new Error("Unimplemented method onDidScroll")
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
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
    cachedCount_value?: int32 | undefined
    onScrollFrameBegin_value?: OnScrollFrameBeginCallback | undefined
    onScrollIndex_value?: ((first: int32,last: int32) => void) | undefined
    onWillScroll_value?: OnWillScrollCallback | undefined
    onDidScroll_value?: OnScrollCallback | undefined
    attributeModifier_value?: AttributeModifier<WaterFlowAttribute> | AttributeModifier<CommonMethod> | undefined
    setWaterFlowOptions(options?: WaterFlowOptions): this {
        return this
    }
    columnsTemplate(value: string | undefined): this {
        return this
    }
    itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        return this
    }
    rowsTemplate(value: string | undefined): this {
        return this
    }
    columnsGap(value: Length | undefined): this {
        return this
    }
    rowsGap(value: Length | undefined): this {
        return this
    }
    layoutDirection(value: FlexDirection | undefined): this {
        return this
    }
    cachedCount(value: int32 | undefined): this {
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        return this
    }
    onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        return this
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkWaterFlowComponent extends ArkScrollableCommonMethodComponent implements WaterFlowAttribute {
    getPeer(): ArkWaterFlowPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkWaterFlowPeer)
    }
    public setWaterFlowOptions(options?: WaterFlowOptions): this {
        if (this.checkPriority("setWaterFlowOptions")) {
            const options_casted = options as (WaterFlowOptions | undefined)
            hookWaterFlowOptionsImpl(this, options);
            this.applyOptionsFinish('WaterFlowAttribute');
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
    public cachedCount(value: int32 | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const value_casted = value as (int32 | undefined)
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
    public onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        if (this.checkPriority("onScrollIndex")) {
            const value_casted = value as (((first: int32,last: int32) => void) | undefined)
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
    public cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        if (this.checkPriority("cachedCount")) {
            const count_casted = count as (int32 | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
          hookWaterFlowAttributeModifier(this, value);
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
export function WaterFlowImpl(
    @memo
    style: ((attributes: WaterFlowAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkWaterFlowComponent>((): ArkWaterFlowComponent => {
        return new ArkWaterFlowComponent()
    })
    NodeAttach<ArkWaterFlowPeer>((): ArkWaterFlowPeer => ArkWaterFlowPeer.create(receiver), (peer: ArkWaterFlowPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
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
        const valueHolderForFooter  = value.footer
        if (valueHolderForFooter !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFooterTmpValue  = valueHolderForFooter!
            valueSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueHolderForFooterTmpValue))
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFooterContent  = value.footerContent
        if (valueHolderForFooterContent !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFooterContentTmpValue  = valueHolderForFooterContent!
            valueSerializer.holdAndWriteObject(valueHolderForFooterContentTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForScroller  = value.scroller
        if (valueHolderForScroller !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForScrollerTmpValue  = valueHolderForScroller!
            Scroller_serializer.write(valueSerializer, valueHolderForScrollerTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSections  = value.sections
        if (valueHolderForSections !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSectionsTmpValue  = valueHolderForSections!
            WaterFlowSections_serializer.write(valueSerializer, valueHolderForSectionsTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLayoutMode  = value.layoutMode
        if (valueHolderForLayoutMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLayoutModeTmpValue  = (valueHolderForLayoutMode as WaterFlowLayoutMode)
            valueSerializer.writeInt32(valueHolderForLayoutModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): WaterFlowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const footerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let footerTmpBuf : CustomBuilder | undefined = undefined
        if ((footerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const footerTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const footerTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const footerTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            footerTmpBuf = ():void => {
                const footerTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                footerTmpBuf_BufArgsSerializer.writeInt32(footerTmpBuf_BufResource.resourceId);
                footerTmpBuf_BufArgsSerializer.writePointer(footerTmpBuf_BufCall);
                footerTmpBuf_BufArgsSerializer.writePointer(footerTmpBuf_BufCallSync);
                InteropNativeModule._CallCallbackSync(10, 737226752, footerTmpBuf_BufArgsSerializer.asBuffer(), footerTmpBuf_BufArgsSerializer.length());
                footerTmpBuf_BufArgsSerializer.release();
                return;
            }
        }
        const footerTmpResult : CustomBuilder | undefined = footerTmpBuf
        const footerContentTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let footerContentTmpBuf : ComponentContentBase | undefined = undefined
        if ((footerContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            footerContentTmpBuf = (valueDeserializer.readObject() as ComponentContentBase)
        }
        const footerContentTmpResult : ComponentContentBase | undefined = footerContentTmpBuf
        const scrollerTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scrollerTmpBuf : Scroller | undefined = undefined
        if ((scrollerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollerTmpBuf = (Scroller_serializer.read(valueDeserializer) as Scroller)
        }
        const scrollerTmpResult : Scroller | undefined = scrollerTmpBuf
        const sectionsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let sectionsTmpBuf : WaterFlowSections | undefined = undefined
        if ((sectionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            sectionsTmpBuf = (WaterFlowSections_serializer.read(valueDeserializer) as WaterFlowSections)
        }
        const sectionsTmpResult : WaterFlowSections | undefined = sectionsTmpBuf
        const layoutModeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let layoutModeTmpBuf : WaterFlowLayoutMode | undefined = undefined
        if ((layoutModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            layoutModeTmpBuf = WaterFlowLayoutMode.fromValue(valueDeserializer.readInt32())
        }
        const layoutModeTmpResult : WaterFlowLayoutMode | undefined = layoutModeTmpBuf
        let value : WaterFlowOptions = ({footer: footerTmpResult, footerContent: footerContentTmpResult, scroller: scrollerTmpResult, sections: sectionsTmpResult, layoutMode: layoutModeTmpResult} as WaterFlowOptions)
        return value
    }
}
export class SectionOptions_serializer {
    public static write(buffer: SerializerBase, value: SectionOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForItemsCount  = value.itemsCount
        valueSerializer.writeInt32(valueHolderForItemsCount)
        const valueHolderForCrossCount  = value.crossCount
        if (valueHolderForCrossCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForCrossCountTmpValue  = valueHolderForCrossCount!
            valueSerializer.writeInt32(valueHolderForCrossCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOnGetItemMainSizeByIndex  = value.onGetItemMainSizeByIndex
        if (valueHolderForOnGetItemMainSizeByIndex !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOnGetItemMainSizeByIndexTmpValue  = valueHolderForOnGetItemMainSizeByIndex!
            valueSerializer.holdAndWriteCallback(valueHolderForOnGetItemMainSizeByIndexTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColumnsGap  = value.columnsGap
        if (valueHolderForColumnsGap !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColumnsGapTmpValue  = valueHolderForColumnsGap!
            if (valueHolderForColumnsGapTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColumnsGapTmpValueForIdx0  = valueHolderForColumnsGapTmpValue as string
                valueSerializer.writeString(valueHolderForColumnsGapTmpValueForIdx0)
            } else if (valueHolderForColumnsGapTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColumnsGapTmpValueForIdx1  = valueHolderForColumnsGapTmpValue as number
                valueSerializer.writeNumber(valueHolderForColumnsGapTmpValueForIdx1)
            } else if (valueHolderForColumnsGapTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColumnsGapTmpValueForIdx2  = valueHolderForColumnsGapTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColumnsGapTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForRowsGap  = value.rowsGap
        if (valueHolderForRowsGap !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRowsGapTmpValue  = valueHolderForRowsGap!
            if (valueHolderForRowsGapTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRowsGapTmpValueForIdx0  = valueHolderForRowsGapTmpValue as string
                valueSerializer.writeString(valueHolderForRowsGapTmpValueForIdx0)
            } else if (valueHolderForRowsGapTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRowsGapTmpValueForIdx1  = valueHolderForRowsGapTmpValue as number
                valueSerializer.writeNumber(valueHolderForRowsGapTmpValueForIdx1)
            } else if (valueHolderForRowsGapTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForRowsGapTmpValueForIdx2  = valueHolderForRowsGapTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRowsGapTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMargin  = value.margin
        if (valueHolderForMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTmpValue  = valueHolderForMargin!
            if (valueHolderForMarginTmpValue instanceof Padding) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForMarginTmpValueForIdx0  = valueHolderForMarginTmpValue as Padding
                Padding_serializer.write(valueSerializer, valueHolderForMarginTmpValueForIdx0)
            } else if (valueHolderForMarginTmpValue instanceof Dimension) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForMarginTmpValueForIdx1  = valueHolderForMarginTmpValue as Dimension
                if (valueHolderForMarginTmpValueForIdx1 instanceof string) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForMarginTmpValueForIdx1ForIdx0  = valueHolderForMarginTmpValueForIdx1 as string
                    valueSerializer.writeString(valueHolderForMarginTmpValueForIdx1ForIdx0)
                } else if (valueHolderForMarginTmpValueForIdx1 instanceof number) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForMarginTmpValueForIdx1ForIdx1  = valueHolderForMarginTmpValueForIdx1 as number
                    valueSerializer.writeNumber(valueHolderForMarginTmpValueForIdx1ForIdx1)
                } else if (valueHolderForMarginTmpValueForIdx1 instanceof Resource) {
                    valueSerializer.writeInt8((2).toByte())
                    const valueHolderForMarginTmpValueForIdx1ForIdx2  = valueHolderForMarginTmpValueForIdx1 as Resource
                    Resource_serializer.write(valueSerializer, valueHolderForMarginTmpValueForIdx1ForIdx2)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): SectionOptions {
        let valueDeserializer : DeserializerBase = buffer
        const itemsCountTmpResult : int32 = valueDeserializer.readInt32()
        const crossCountTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let crossCountTmpBuf : int32 | undefined = undefined
        if ((crossCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            crossCountTmpBuf = valueDeserializer.readInt32()
        }
        const crossCountTmpResult : int32 | undefined = crossCountTmpBuf
        const onGetItemMainSizeByIndexTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let onGetItemMainSizeByIndexTmpBuf : GetItemMainSizeByIndex | undefined = undefined
        if ((onGetItemMainSizeByIndexTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const onGetItemMainSizeByIndexTmpBuf_BufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const onGetItemMainSizeByIndexTmpBuf_BufCall : KPointer = valueDeserializer.readPointer()
            const onGetItemMainSizeByIndexTmpBuf_BufCallSync : KPointer = valueDeserializer.readPointer()
            onGetItemMainSizeByIndexTmpBuf = (index: int32):double => {
                const onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer : SerializerBase = SerializerBase.hold();
                onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer.writeInt32(onGetItemMainSizeByIndexTmpBuf_BufResource.resourceId);
                onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer.writePointer(onGetItemMainSizeByIndexTmpBuf_BufCall);
                onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer.writePointer(onGetItemMainSizeByIndexTmpBuf_BufCallSync);
                onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer.writeInt32(index);
                let onGetItemMainSizeByIndexTmpBuf_BufContinuationValue : double | undefined;
                const onGetItemMainSizeByIndexTmpBuf_BufContinuationCallback : ((offset: double) => void) = (value: double):void => {
                onGetItemMainSizeByIndexTmpBuf_BufContinuationValue = value;
            }
                onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer.holdAndWriteCallback(onGetItemMainSizeByIndexTmpBuf_BufContinuationCallback);
                InteropNativeModule._CallCallbackSync(10, -2076995110, onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer.asBuffer(), onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer.length());
                onGetItemMainSizeByIndexTmpBuf_BufArgsSerializer.release();
                return onGetItemMainSizeByIndexTmpBuf_BufContinuationValue!.toDouble();
            }
        }
        const onGetItemMainSizeByIndexTmpResult : GetItemMainSizeByIndex | undefined = onGetItemMainSizeByIndexTmpBuf
        const columnsGapTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let columnsGapTmpBuf : Dimension | undefined = undefined
        if ((columnsGapTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const columnsGapTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let columnsGapTmpBuf_ : string | number | Resource | undefined
            if (columnsGapTmpBuf_UnionSelector == (0).toByte()) {
                columnsGapTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (columnsGapTmpBuf_UnionSelector == (1).toByte()) {
                columnsGapTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (columnsGapTmpBuf_UnionSelector == (2).toByte()) {
                columnsGapTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for columnsGapTmpBuf_ has to be chosen through deserialisation.")
            }
            columnsGapTmpBuf = (columnsGapTmpBuf_ as string | number | Resource)
        }
        const columnsGapTmpResult : Dimension | undefined = columnsGapTmpBuf
        const rowsGapTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let rowsGapTmpBuf : Dimension | undefined = undefined
        if ((rowsGapTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const rowsGapTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let rowsGapTmpBuf_ : string | number | Resource | undefined
            if (rowsGapTmpBuf_UnionSelector == (0).toByte()) {
                rowsGapTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (rowsGapTmpBuf_UnionSelector == (1).toByte()) {
                rowsGapTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (rowsGapTmpBuf_UnionSelector == (2).toByte()) {
                rowsGapTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for rowsGapTmpBuf_ has to be chosen through deserialisation.")
            }
            rowsGapTmpBuf = (rowsGapTmpBuf_ as string | number | Resource)
        }
        const rowsGapTmpResult : Dimension | undefined = rowsGapTmpBuf
        const marginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marginTmpBuf : Padding | Dimension | undefined = undefined
        if ((marginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const marginTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let marginTmpBuf_ : Padding | Dimension | undefined
            if (marginTmpBuf_UnionSelector == (0).toByte()) {
                marginTmpBuf_ = Padding_serializer.read(valueDeserializer)
            } else if (marginTmpBuf_UnionSelector == (1).toByte()) {
                const marginTmpBuf_BufUUnionSelector : int32 = valueDeserializer.readInt8()
                let marginTmpBuf_BufU : string | number | Resource | undefined
                if (marginTmpBuf_BufUUnionSelector == (0).toByte()) {
                    marginTmpBuf_BufU = (valueDeserializer.readString() as string)
                } else if (marginTmpBuf_BufUUnionSelector == (1).toByte()) {
                    marginTmpBuf_BufU = (valueDeserializer.readNumber() as number)
                } else if (marginTmpBuf_BufUUnionSelector == (2).toByte()) {
                    marginTmpBuf_BufU = Resource_serializer.read(valueDeserializer)
                } else {
                    throw new Error("One of the branches for marginTmpBuf_BufU has to be chosen through deserialisation.")
                }
                marginTmpBuf_ = (marginTmpBuf_BufU as string | number | Resource)
            } else {
                throw new Error("One of the branches for marginTmpBuf_ has to be chosen through deserialisation.")
            }
            marginTmpBuf = (marginTmpBuf_ as Padding | Dimension)
        }
        const marginTmpResult : Padding | Dimension | undefined = marginTmpBuf
        let value : SectionOptions = ({itemsCount: itemsCountTmpResult, crossCount: crossCountTmpResult, onGetItemMainSizeByIndex: onGetItemMainSizeByIndexTmpResult, columnsGap: columnsGapTmpResult, rowsGap: rowsGapTmpResult, margin: marginTmpResult} as SectionOptions)
        return value
    }
}
