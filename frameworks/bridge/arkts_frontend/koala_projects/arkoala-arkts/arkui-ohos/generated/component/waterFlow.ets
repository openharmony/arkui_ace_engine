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

import { ArkThemeScopeManager } from '#arktheme'
import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, resourceFinalizerRegister, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { ConstraintSizeOptions_serializer, ConstraintSizeOptions, Length, Resource as arkui_component_units_Resource, Dimension, Margin, Padding } from './units'
import { global_resource_Resource_serializer } from './../framework/resource'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkUIGeneratedNativeModule } from '#components'
import { ArkScrollableCommonMethodPeer, ScrollableCommonMethod, OnWillScrollCallback, OnScrollCallback, CommonMethod, ArkScrollableCommonMethodComponent, ArkCommonMethodComponent } from './common'
import { Resource as global_resource_Resource } from 'global.resource'
import { FlexDirection, ScrollSource } from './enums'
import { OnScrollFrameBeginCallback, Scroller, Scroller_serializer } from './scroll'
import { ScrollState } from './list'
import { AttributeModifier, initializers, WaterFlowSections, hookWaterFlowAttributeModifier, AttributeUpdater, extractors } from '#handwritten'
// instructive change start
import { hookWaterFlowOptionsImpl } from '#handwritten'
// instructive change end
import { CallbackKind } from './../framework/peers/CallbackKind'
import { CallbackTransformer } from './../CallbackTransformer'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { CustomBuilder } from './builder'
import { ComponentContentBase } from '@arkui.ComponentContent'
import { WaterFlowModifier } from './../WaterFlowModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
import { WaterFlowSectionsInterface, WaterFlowSectionsInterface_serializer } from './idlize'
export class ArkWaterFlowPeer extends ArkScrollableCommonMethodPeer {
    attributeSet?: WaterFlowModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
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
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
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
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
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
    itemsCount: int32 = initializers.arkui.component.waterFlow.SectionOptionsNS.itemsCount;
    crossCount?: int32 | undefined;
    onGetItemMainSizeByIndex?: GetItemMainSizeByIndex | undefined;
    columnsGap?: Dimension | undefined;
    rowsGap?: Dimension | undefined;
    margin?: Margin | Dimension | undefined;
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
        throw new Error('Unimplemented method setWaterFlowOptions')
    }
    columnsTemplate(value: string | undefined): this {
        throw new Error('Unimplemented method columnsTemplate')
    }
    itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        throw new Error('Unimplemented method itemConstraintSize')
    }
    rowsTemplate(value: string | undefined): this {
        throw new Error('Unimplemented method rowsTemplate')
    }
    columnsGap(value: Length | undefined): this {
        throw new Error('Unimplemented method columnsGap')
    }
    rowsGap(value: Length | undefined): this {
        throw new Error('Unimplemented method rowsGap')
    }
    layoutDirection(value: FlexDirection | undefined): this {
        throw new Error('Unimplemented method layoutDirection')
    }
    cachedCount(value: int32 | undefined): this {
        throw new Error('Unimplemented method cachedCount')
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        throw new Error('Unimplemented method onScrollFrameBegin')
    }
    onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        throw new Error('Unimplemented method onScrollIndex')
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        throw new Error('Unimplemented method onWillScroll')
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        throw new Error('Unimplemented method onDidScroll')
    }
    cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        throw new Error('Unimplemented method cachedCount')
    }
    attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkWaterFlowComponent extends ArkScrollableCommonMethodComponent implements WaterFlowAttribute {
    getPeer(): ArkWaterFlowPeer {
        return (this.peer as ArkWaterFlowPeer)
    }
    public setWaterFlowOptions(options?: WaterFlowOptions): this {
        if (this.checkPriority('setWaterFlowOptions')) {
            // instructive change start
            hookWaterFlowOptionsImpl(this, options);
            // instructive change end
            this.applyOptionsFinish('WaterFlowAttribute');
            return this
        }
        return this
    }
    public columnsTemplate(value: string | undefined): this {
        if (this.checkPriority('columnsTemplate')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setColumnsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        if (this.checkPriority('itemConstraintSize')) {
            const value_casted = value as (ConstraintSizeOptions | undefined)
            this.getPeer()?.setItemConstraintSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsTemplate(value: string | undefined): this {
        if (this.checkPriority('rowsTemplate')) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.setRowsTemplateAttribute(value_casted)
            return this
        }
        return this
    }
    public columnsGap(value: Length | undefined): this {
        if (this.checkPriority('columnsGap')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setColumnsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public rowsGap(value: Length | undefined): this {
        if (this.checkPriority('rowsGap')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setRowsGapAttribute(value_casted)
            return this
        }
        return this
    }
    public layoutDirection(value: FlexDirection | undefined): this {
        if (this.checkPriority('layoutDirection')) {
            const value_casted = value as (FlexDirection | undefined)
            this.getPeer()?.setLayoutDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(value: int32 | undefined): this {
        if (this.checkPriority('cachedCount')) {
            const value_casted = value as (int32 | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
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
    public onScrollIndex(value: ((first: int32,last: int32) => void) | undefined): this {
        if (this.checkPriority('onScrollIndex')) {
            const value_casted = value as (((first: int32,last: int32) => void) | undefined)
            this.getPeer()?.setOnScrollIndexAttribute(value_casted)
            return this
        }
        return this
    }
    public onWillScroll(value: OnWillScrollCallback | undefined): this {
        if (this.checkPriority('onWillScroll')) {
            const value_casted = value as (OnWillScrollCallback | undefined)
            this.getPeer()?.setOnWillScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public onDidScroll(value: OnScrollCallback | undefined): this {
        if (this.checkPriority('onDidScroll')) {
            const value_casted = value as (OnScrollCallback | undefined)
            this.getPeer()?.setOnDidScrollAttribute(value_casted)
            return this
        }
        return this
    }
    public cachedCount(count: int32 | undefined, show: boolean | undefined): this {
        if (this.checkPriority('cachedCount')) {
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
    @memo @memo_skip
    style: ((attributes: WaterFlowAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkWaterFlowComponent>((): ArkWaterFlowComponent => {
        return new ArkWaterFlowComponent()
    })
    NodeAttach<ArkWaterFlowPeer>((): ArkWaterFlowPeer => ArkWaterFlowPeer.create(receiver), (_: ArkWaterFlowPeer): void => {
        style?.(receiver)
        content_?.()
    })
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
            const valueHolderForSectionsTmpValueTransformed : WaterFlowSectionsInterface = extractors.transform_Ark_WaterFlowSections_to_Ark_WaterFlowSectionsInterface(valueHolderForSectionsTmpValue)
            WaterFlowSectionsInterface_serializer.write(valueSerializer, valueHolderForSectionsTmpValueTransformed)
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
        const footerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let footerTmpBuf : CustomBuilder | undefined = undefined
        if ((footerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const footerTmpBufOptBufResource : CallbackResource = valueDeserializer.readCallbackResource()
            const footerTmpBufOptBufCall : KPointer = valueDeserializer.readPointer()
            const footerTmpBufOptBufCallSync : KPointer = valueDeserializer.readPointer()
            const footerTmpBufOptClosure  = ():void => {
                const footerTmpBufOptBufArgsSerializer : SerializerBase = SerializerBase.hold();
                footerTmpBufOptBufArgsSerializer.writeInt32(footerTmpBufOptBufResource.resourceId);
                footerTmpBufOptBufArgsSerializer.writePointer(footerTmpBufOptBufCall);
                footerTmpBufOptBufArgsSerializer.writePointer(footerTmpBufOptBufCallSync);
                InteropNativeModule._CallCallbackSync(10, -1834072896, footerTmpBufOptBufArgsSerializer.asBuffer(), footerTmpBufOptBufArgsSerializer.length());
                footerTmpBufOptBufArgsSerializer.release();
                return;
            }
            resourceFinalizerRegister(footerTmpBufOptClosure, footerTmpBufOptBufResource)
            footerTmpBuf = footerTmpBufOptClosure
        }
        const footerTmpResult : CustomBuilder | undefined = footerTmpBuf
        const footerContentTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let footerContentTmpBuf : ComponentContentBase | undefined = undefined
        if ((footerContentTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            footerContentTmpBuf = (valueDeserializer.readObject() as ComponentContentBase)
        }
        const footerContentTmpResult : ComponentContentBase | undefined = footerContentTmpBuf
        const scrollerTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let scrollerTmpBuf : Scroller | undefined = undefined
        if ((scrollerTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            scrollerTmpBuf = (Scroller_serializer.read(valueDeserializer) as Scroller)
        }
        const scrollerTmpResult : Scroller | undefined = scrollerTmpBuf
        const sectionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let sectionsTmpBuf : WaterFlowSections | undefined = undefined
        if ((sectionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const sectionsTmpBufOptDeserialized : WaterFlowSectionsInterface = WaterFlowSectionsInterface_serializer.read(valueDeserializer)
            sectionsTmpBuf = extractors.transform_Ark_WaterFlowSectionsInterface_to_Ark_WaterFlowSections(sectionsTmpBufOptDeserialized)
        }
        const sectionsTmpResult : WaterFlowSections | undefined = sectionsTmpBuf
        const layoutModeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let layoutModeTmpBuf : WaterFlowLayoutMode | undefined = undefined
        if ((layoutModeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            layoutModeTmpBuf = WaterFlowLayoutMode.fromValue(valueDeserializer.readInt32())
        }
        const layoutModeTmpResult : WaterFlowLayoutMode | undefined = layoutModeTmpBuf
        let value : WaterFlowOptions = ({footer: footerTmpResult, footerContent: footerContentTmpResult, scroller: scrollerTmpResult, sections: sectionsTmpResult, layoutMode: layoutModeTmpResult} as WaterFlowOptions)
        return value
    }
}
