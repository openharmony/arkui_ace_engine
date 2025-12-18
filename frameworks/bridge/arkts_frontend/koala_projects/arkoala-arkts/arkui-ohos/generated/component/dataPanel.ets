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
import { unsafeCast, int32, int64, float32 } from '@koalaui/common'
import { ArkUIGeneratedNativeModule } from '#components'
import { CallbackTransformer } from './../CallbackTransformer'
import { ArkThemeScopeManager } from '#arktheme'
import { global_resource_Resource_serializer } from './../framework/resource'
import { ComponentBase } from './../ComponentBase'
import { PeerNode } from './../PeerNode'
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, CommonConfiguration, ArkCommonMethodComponent } from './common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length } from './units'
import { Color as arkui_component_enums_Color } from './enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { ContentModifier, AttributeModifier, hookDataPanelContentModifier, hookDataPanelAttributeModifier, AttributeUpdater } from '#handwritten'
import { CallbackKind } from './../framework/peers/CallbackKind'
import { memo, memo_stable, memo_skip } from 'arkui.stateManagement.runtime'
import { ComponentBuilder, Builder } from '@koalaui/builderLambda'
import { DataPanelModifier } from './../DataPanelModifier'
import { NodeAttach, remember } from '@koalaui/runtime'
import { ModifierStateManager } from './../CommonModifier'
export class LinearGradientInternal {
    public static fromPtr(ptr: KPointer): LinearGradient {
        return new LinearGradient(MaterializedBaseTag.NOP, ptr)
    }
}
export class LinearGradient implements MaterializedBase {
    public peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(tag: MaterializedBaseTag, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LinearGradient.getFinalizer())
    }
    constructor(colorStops: Array<ColorStop>) {
        this(MaterializedBaseTag.NOP, LinearGradient.construct(colorStops))
    }
    static construct(colorStops: Array<ColorStop>): KPointer {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.writeInt32((colorStops.length).toInt())
        for (let colorStopsCounterI = 0; colorStopsCounterI < colorStops.length; colorStopsCounterI++) {
            const colorStopsTmpElement : ColorStop = colorStops[colorStopsCounterI]
            ColorStop_serializer.write(thisSerializer, colorStopsTmpElement)
        }
        const retval  = ArkUIGeneratedNativeModule._LinearGradient_construct(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._LinearGradient_getFinalizer()
    }
}
export class ArkDataPanelPeer extends ArkCommonMethodPeer {
    attributeSet?: DataPanelModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkDataPanelPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._DataPanel_construct(peerId, flags)
        const _peer  = new ArkDataPanelPeer(_peerPtr, peerId, 'DataPanel', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setDataPanelOptionsAttribute(options: DataPanelOptions): void {
        ArkThemeScopeManager.getInstance().applyThemeScopeIdToNode(this.peer.ptr);
        const thisSerializer : SerializerBase = SerializerBase.hold()
        DataPanelOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._DataPanelInterface_setDataPanelOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCloseEffectAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setCloseEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setValueColorsAttribute(value: Array<ResourceColor | LinearGradient> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeInt32((valueTmpValue.length).toInt())
            for (let valueTmpValueCounterI = 0; valueTmpValueCounterI < valueTmpValue.length; valueTmpValueCounterI++) {
                const valueTmpValueTmpElement : ResourceColor | LinearGradient = valueTmpValue[valueTmpValueCounterI]
                if (valueTmpValueTmpElement instanceof ResourceColor) {
                    thisSerializer.writeInt8((0).toByte())
                    const valueTmpValueTmpElementForIdx0  = valueTmpValueTmpElement as ResourceColor
                    if (valueTmpValueTmpElementForIdx0 instanceof arkui_component_enums_Color) {
                        thisSerializer.writeInt8((0).toByte())
                        const valueTmpValueTmpElementForIdx0ForIdx0  = valueTmpValueTmpElementForIdx0 as arkui_component_enums_Color
                        thisSerializer.writeInt32((valueTmpValueTmpElementForIdx0ForIdx0.getOrdinal()) % (12))
                    } else if (valueTmpValueTmpElementForIdx0 instanceof int32) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueTmpElementForIdx0ForIdx1  = valueTmpValueTmpElementForIdx0 as int32
                        thisSerializer.writeInt32(valueTmpValueTmpElementForIdx0ForIdx1)
                    } else if (valueTmpValueTmpElementForIdx0 instanceof string) {
                        thisSerializer.writeInt8((2).toByte())
                        const valueTmpValueTmpElementForIdx0ForIdx2  = valueTmpValueTmpElementForIdx0 as string
                        thisSerializer.writeString(valueTmpValueTmpElementForIdx0ForIdx2)
                    } else if (valueTmpValueTmpElementForIdx0 instanceof arkui_component_units_Resource) {
                        thisSerializer.writeInt8((3).toByte())
                        const valueTmpValueTmpElementForIdx0ForIdx3  = valueTmpValueTmpElementForIdx0 as arkui_component_units_Resource
                        global_resource_Resource_serializer.write(thisSerializer, valueTmpValueTmpElementForIdx0ForIdx3)
                    }
                } else if (valueTmpValueTmpElement instanceof LinearGradient) {
                    thisSerializer.writeInt8((1).toByte())
                    const valueTmpValueTmpElementForIdx1  = valueTmpValueTmpElement as LinearGradient
                    LinearGradient_serializer.write(thisSerializer, valueTmpValueTmpElementForIdx1)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setValueColors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
            } else if (valueTmpValue instanceof arkui_component_units_Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setTrackBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeWidthAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._DataPanelAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackShadowAttribute(value: DataPanelShadowOptions | null | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined && value !== null) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            DataPanelShadowOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setTrackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export enum DataPanelType {
    Line = 0,
    Circle = 1,
    LINE = 0,
    CIRCLE = 1
}
export interface ColorStop {
    color: ResourceColor | undefined;
    offset: Length | undefined;
}
export interface DataPanelShadowOptions extends MultiShadowOptions {
    colors?: Array<ResourceColor | LinearGradient>;
}
export interface DataPanelOptions {
    values: Array<double>;
    max?: double;
    type?: DataPanelType;
}
export interface DataPanelConfiguration extends CommonConfiguration<DataPanelConfiguration> {
    values: Array<double>;
    maxValue: double;
}
export interface DataPanelAttribute extends CommonMethod {
    setDataPanelOptions(options: DataPanelOptions): this {
        throw new Error('Unimplemented method setDataPanelOptions')
    }
    closeEffect(value: boolean | undefined): this {
        throw new Error('Unimplemented method closeEffect')
    }
    valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        throw new Error('Unimplemented method valueColors')
    }
    trackBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error('Unimplemented method trackBackgroundColor')
    }
    strokeWidth(value: Length | undefined): this {
        throw new Error('Unimplemented method strokeWidth')
    }
    trackShadow(value: DataPanelShadowOptions | null | undefined): this {
        throw new Error('Unimplemented method trackShadow')
    }
    contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): this {
        throw new Error('Unimplemented method contentModifier')
    }
    attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}

export class ArkDataPanelComponent extends ArkCommonMethodComponent implements DataPanelAttribute {
    getPeer(): ArkDataPanelPeer {
        return (this.peer as ArkDataPanelPeer)
    }
    public setDataPanelOptions(options: DataPanelOptions): this {
        if (this.checkPriority('setDataPanelOptions')) {
            const options_casted = options as (DataPanelOptions)
            this.getPeer()?.setDataPanelOptionsAttribute(options_casted)
            this.applyOptionsFinish('DataPanelAttribute');
            return this
        }
        return this
    }
    public closeEffect(value: boolean | undefined): this {
        if (this.checkPriority('closeEffect')) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setCloseEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        if (this.checkPriority('valueColors')) {
            const value_casted = value as (Array<ResourceColor | LinearGradient> | undefined)
            this.getPeer()?.setValueColorsAttribute(value_casted)
            return this
        }
        return this
    }
    public trackBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority('trackBackgroundColor')) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setTrackBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        if (this.checkPriority('strokeWidth')) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public trackShadow(value: DataPanelShadowOptions | null | undefined): this {
        if (this.checkPriority('trackShadow')) {
            const value_casted = value as (DataPanelShadowOptions | null | undefined)
            this.getPeer()?.setTrackShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): this {
        if (this.checkPriority('contentModifier')) {
            hookDataPanelContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookDataPanelAttributeModifier(this, value);
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
export function DataPanelImpl(
    @memo @memo_skip
    style: ((attributes: DataPanelAttribute) => void) | undefined,
    @memo @memo_skip
    content_?: () => void,
): void {
    const receiver = remember<ArkDataPanelComponent>((): ArkDataPanelComponent => {
        return new ArkDataPanelComponent()
    })
    NodeAttach<ArkDataPanelPeer>((): ArkDataPanelPeer => ArkDataPanelPeer.create(receiver), (_: ArkDataPanelPeer): void => {
        style?.(receiver)
        content_?.()
    })
}

export class LinearGradient_serializer {
    public static write(buffer: SerializerBase, value: LinearGradient): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): LinearGradient {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return LinearGradientInternal.fromPtr(ptr)
    }
}
export class DataPanelConfiguration_serializer {
    public static write(buffer: SerializerBase, value: DataPanelConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForValues  = value.values
        valueSerializer.writeInt32((valueHolderForValues.length).toInt())
        for (let valueHolderForValuesCounterI = 0; valueHolderForValuesCounterI < valueHolderForValues.length; valueHolderForValuesCounterI++) {
            const valueHolderForValuesTmpElement : double = valueHolderForValues[valueHolderForValuesCounterI]
            valueSerializer.writeFloat64(valueHolderForValuesTmpElement)
        }
        const valueHolderForMaxValue  = value.maxValue
        valueSerializer.writeFloat64(valueHolderForMaxValue)
    }
    public static read(buffer: DeserializerBase): DataPanelConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<DataPanelConfiguration> = (valueDeserializer.readObject() as ContentModifier<DataPanelConfiguration>)
        const valuesTmpBufLength : int32 = valueDeserializer.readInt32()
        let valuesTmpBuf : Array<double> = new Array<double>(valuesTmpBufLength)
        for (let valuesTmpBufBufCounterI = 0; valuesTmpBufBufCounterI < valuesTmpBufLength; valuesTmpBufBufCounterI++) {
            valuesTmpBuf[valuesTmpBufBufCounterI] = valueDeserializer.readFloat64()
        }
        const valuesTmpResult : Array<double> = valuesTmpBuf
        const maxValueTmpResult : double = valueDeserializer.readFloat64()
        let value : DataPanelConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, values: valuesTmpResult, maxValue: maxValueTmpResult} as DataPanelConfiguration)
        return value
    }
}
export class DataPanelOptions_serializer {
    public static write(buffer: SerializerBase, value: DataPanelOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValues  = value.values
        valueSerializer.writeInt32((valueHolderForValues.length).toInt())
        for (let valueHolderForValuesCounterI = 0; valueHolderForValuesCounterI < valueHolderForValues.length; valueHolderForValuesCounterI++) {
            const valueHolderForValuesTmpElement : double = valueHolderForValues[valueHolderForValuesCounterI]
            valueSerializer.writeFloat64(valueHolderForValuesTmpElement)
        }
        const valueHolderForMax  = value.max
        if (valueHolderForMax !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxTmpValue  = valueHolderForMax!
            valueSerializer.writeFloat64(valueHolderForMaxTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForType  = value.type
        if (valueHolderForType !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTypeTmpValue  = (valueHolderForType as DataPanelType)
            valueSerializer.writeInt32(valueHolderForTypeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DataPanelOptions {
        let valueDeserializer : DeserializerBase = buffer
        const valuesTmpBufLength : int32 = valueDeserializer.readInt32()
        let valuesTmpBuf : Array<double> = new Array<double>(valuesTmpBufLength)
        for (let valuesTmpBufBufCounterI = 0; valuesTmpBufBufCounterI < valuesTmpBufLength; valuesTmpBufBufCounterI++) {
            valuesTmpBuf[valuesTmpBufBufCounterI] = valueDeserializer.readFloat64()
        }
        const valuesTmpResult : Array<double> = valuesTmpBuf
        const maxTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let maxTmpBuf : double | undefined = undefined
        if ((maxTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxTmpBuf = valueDeserializer.readFloat64()
        }
        const maxTmpResult : double | undefined = maxTmpBuf
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let typeTmpBuf : DataPanelType | undefined = undefined
        if ((typeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            typeTmpBuf = DataPanelType.fromValue(valueDeserializer.readInt32())
        }
        const typeTmpResult : DataPanelType | undefined = typeTmpBuf
        let value : DataPanelOptions = ({values: valuesTmpResult, max: maxTmpResult, type: typeTmpResult} as DataPanelOptions)
        return value
    }
}
export class DataPanelShadowOptions_serializer {
    public static write(buffer: SerializerBase, value: DataPanelShadowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRadiusTmpValueForIdx0)
            } else if (valueHolderForRadiusTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffsetX  = value.offsetX
        if (valueHolderForOffsetX !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetXTmpValue  = valueHolderForOffsetX!
            if (valueHolderForOffsetXTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForOffsetXTmpValueForIdx0  = valueHolderForOffsetXTmpValue as double
                valueSerializer.writeFloat64(valueHolderForOffsetXTmpValueForIdx0)
            } else if (valueHolderForOffsetXTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOffsetXTmpValueForIdx1  = valueHolderForOffsetXTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForOffsetXTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffsetY  = value.offsetY
        if (valueHolderForOffsetY !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetYTmpValue  = valueHolderForOffsetY!
            if (valueHolderForOffsetYTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForOffsetYTmpValueForIdx0  = valueHolderForOffsetYTmpValue as double
                valueSerializer.writeFloat64(valueHolderForOffsetYTmpValueForIdx0)
            } else if (valueHolderForOffsetYTmpValue instanceof global_resource_Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOffsetYTmpValueForIdx1  = valueHolderForOffsetYTmpValue as global_resource_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForOffsetYTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForColors  = value.colors
        if (valueHolderForColors !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorsTmpValue  = valueHolderForColors!
            valueSerializer.writeInt32((valueHolderForColorsTmpValue.length).toInt())
            for (let valueHolderForColorsTmpValueCounterI = 0; valueHolderForColorsTmpValueCounterI < valueHolderForColorsTmpValue.length; valueHolderForColorsTmpValueCounterI++) {
                const valueHolderForColorsTmpValueTmpElement : ResourceColor | LinearGradient = valueHolderForColorsTmpValue[valueHolderForColorsTmpValueCounterI]
                if (valueHolderForColorsTmpValueTmpElement instanceof ResourceColor) {
                    valueSerializer.writeInt8((0).toByte())
                    const valueHolderForColorsTmpValueTmpElementForIdx0  = valueHolderForColorsTmpValueTmpElement as ResourceColor
                    if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof arkui_component_enums_Color) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx0  = valueHolderForColorsTmpValueTmpElementForIdx0 as arkui_component_enums_Color
                        valueSerializer.writeInt32((valueHolderForColorsTmpValueTmpElementForIdx0ForIdx0.getOrdinal()) % (12))
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof int32) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx1  = valueHolderForColorsTmpValueTmpElementForIdx0 as int32
                        valueSerializer.writeInt32(valueHolderForColorsTmpValueTmpElementForIdx0ForIdx1)
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof string) {
                        valueSerializer.writeInt8((2).toByte())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx2  = valueHolderForColorsTmpValueTmpElementForIdx0 as string
                        valueSerializer.writeString(valueHolderForColorsTmpValueTmpElementForIdx0ForIdx2)
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof arkui_component_units_Resource) {
                        valueSerializer.writeInt8((3).toByte())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx3  = valueHolderForColorsTmpValueTmpElementForIdx0 as arkui_component_units_Resource
                        global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorsTmpValueTmpElementForIdx0ForIdx3)
                    }
                } else if (valueHolderForColorsTmpValueTmpElement instanceof LinearGradient) {
                    valueSerializer.writeInt8((1).toByte())
                    const valueHolderForColorsTmpValueTmpElementForIdx1  = valueHolderForColorsTmpValueTmpElement as LinearGradient
                    LinearGradient_serializer.write(valueSerializer, valueHolderForColorsTmpValueTmpElementForIdx1)
                }
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): DataPanelShadowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let radiusTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBufOpt : double | global_resource_Resource | undefined
            if (radiusTmpBufOptUnionSelector == (0).toByte()) {
                radiusTmpBufOpt = valueDeserializer.readFloat64()
            } else if (radiusTmpBufOptUnionSelector == (1).toByte()) {
                radiusTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for radiusTmpBufOpt has to be chosen through deserialisation.')
            }
            radiusTmpBuf = (radiusTmpBufOpt as double | global_resource_Resource)
        }
        const radiusTmpResult : double | global_resource_Resource | undefined = radiusTmpBuf
        const offsetXTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetXTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((offsetXTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetXTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let offsetXTmpBufOpt : double | global_resource_Resource | undefined
            if (offsetXTmpBufOptUnionSelector == (0).toByte()) {
                offsetXTmpBufOpt = valueDeserializer.readFloat64()
            } else if (offsetXTmpBufOptUnionSelector == (1).toByte()) {
                offsetXTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for offsetXTmpBufOpt has to be chosen through deserialisation.')
            }
            offsetXTmpBuf = (offsetXTmpBufOpt as double | global_resource_Resource)
        }
        const offsetXTmpResult : double | global_resource_Resource | undefined = offsetXTmpBuf
        const offsetYTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetYTmpBuf : double | global_resource_Resource | undefined = undefined
        if ((offsetYTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetYTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let offsetYTmpBufOpt : double | global_resource_Resource | undefined
            if (offsetYTmpBufOptUnionSelector == (0).toByte()) {
                offsetYTmpBufOpt = valueDeserializer.readFloat64()
            } else if (offsetYTmpBufOptUnionSelector == (1).toByte()) {
                offsetYTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for offsetYTmpBufOpt has to be chosen through deserialisation.')
            }
            offsetYTmpBuf = (offsetYTmpBufOpt as double | global_resource_Resource)
        }
        const offsetYTmpResult : double | global_resource_Resource | undefined = offsetYTmpBuf
        const colorsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorsTmpBuf : Array<ResourceColor | LinearGradient> | undefined = undefined
        if ((colorsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorsTmpBufOptLength : int32 = valueDeserializer.readInt32()
            let colorsTmpBufOpt : Array<ResourceColor | LinearGradient> = new Array<ResourceColor | LinearGradient>(colorsTmpBufOptLength)
            for (let colorsTmpBufOptBufCounterI = 0; colorsTmpBufOptBufCounterI < colorsTmpBufOptLength; colorsTmpBufOptBufCounterI++) {
                const colorsTmpBufOptTempBufUnionSelector : int32 = valueDeserializer.readInt8()
                let colorsTmpBufOptTempBuf : ResourceColor | LinearGradient | undefined
                if (colorsTmpBufOptTempBufUnionSelector == (0).toByte()) {
                    const colorsTmpBufOptTempBufBufUUnionSelector : int32 = valueDeserializer.readInt8()
                    let colorsTmpBufOptTempBufBufU : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
                    if (colorsTmpBufOptTempBufBufUUnionSelector == (0).toByte()) {
                        colorsTmpBufOptTempBufBufU = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
                    } else if (colorsTmpBufOptTempBufBufUUnionSelector == (1).toByte()) {
                        colorsTmpBufOptTempBufBufU = valueDeserializer.readInt32()
                    } else if (colorsTmpBufOptTempBufBufUUnionSelector == (2).toByte()) {
                        colorsTmpBufOptTempBufBufU = (valueDeserializer.readString() as string)
                    } else if (colorsTmpBufOptTempBufBufUUnionSelector == (3).toByte()) {
                        colorsTmpBufOptTempBufBufU = global_resource_Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error('One of the branches for colorsTmpBufOptTempBufBufU has to be chosen through deserialisation.')
                    }
                    colorsTmpBufOptTempBuf = (colorsTmpBufOptTempBufBufU as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
                } else if (colorsTmpBufOptTempBufUnionSelector == (1).toByte()) {
                    colorsTmpBufOptTempBuf = (LinearGradient_serializer.read(valueDeserializer) as LinearGradient)
                } else {
                    throw new Error('One of the branches for colorsTmpBufOptTempBuf has to be chosen through deserialisation.')
                }
                colorsTmpBufOpt[colorsTmpBufOptBufCounterI] = (colorsTmpBufOptTempBuf as ResourceColor | LinearGradient)
            }
            colorsTmpBuf = colorsTmpBufOpt
        }
        const colorsTmpResult : Array<ResourceColor | LinearGradient> | undefined = colorsTmpBuf
        let value : DataPanelShadowOptions = ({radius: radiusTmpResult, offsetX: offsetXTmpResult, offsetY: offsetYTmpResult, colors: colorsTmpResult} as DataPanelShadowOptions)
        return value
    }
}
export class ColorStop_serializer {
    public static write(buffer: SerializerBase, value: ColorStop): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForColor  = value.color
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof arkui_component_enums_Color) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as arkui_component_enums_Color
                valueSerializer.writeInt32((valueHolderForColorTmpValueForIdx0.getOrdinal()) % (12))
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((3).toByte())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            if (valueHolderForOffsetTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForOffsetTmpValueForIdx0  = valueHolderForOffsetTmpValue as string
                valueSerializer.writeString(valueHolderForOffsetTmpValueForIdx0)
            } else if (valueHolderForOffsetTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOffsetTmpValueForIdx1  = valueHolderForOffsetTmpValue as double
                valueSerializer.writeFloat64(valueHolderForOffsetTmpValueForIdx1)
            } else if (valueHolderForOffsetTmpValue instanceof arkui_component_units_Resource) {
                valueSerializer.writeInt8((2).toByte())
                const valueHolderForOffsetTmpValueForIdx2  = valueHolderForOffsetTmpValue as arkui_component_units_Resource
                global_resource_Resource_serializer.write(valueSerializer, valueHolderForOffsetTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ColorStop {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBufOpt : arkui_component_enums_Color | int32 | string | arkui_component_units_Resource | undefined
            if (colorTmpBufOptUnionSelector == (0).toByte()) {
                colorTmpBufOpt = arkui_component_enums_Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBufOptUnionSelector == (1).toByte()) {
                colorTmpBufOpt = valueDeserializer.readInt32()
            } else if (colorTmpBufOptUnionSelector == (2).toByte()) {
                colorTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (colorTmpBufOptUnionSelector == (3).toByte()) {
                colorTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for colorTmpBufOpt has to be chosen through deserialisation.')
            }
            colorTmpBuf = (colorTmpBufOpt as arkui_component_enums_Color | int32 | string | arkui_component_units_Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let offsetTmpBuf : Length | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetTmpBufOptUnionSelector : int32 = valueDeserializer.readInt8()
            let offsetTmpBufOpt : string | double | arkui_component_units_Resource | undefined
            if (offsetTmpBufOptUnionSelector == (0).toByte()) {
                offsetTmpBufOpt = (valueDeserializer.readString() as string)
            } else if (offsetTmpBufOptUnionSelector == (1).toByte()) {
                offsetTmpBufOpt = valueDeserializer.readFloat64()
            } else if (offsetTmpBufOptUnionSelector == (2).toByte()) {
                offsetTmpBufOpt = global_resource_Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error('One of the branches for offsetTmpBufOpt has to be chosen through deserialisation.')
            }
            offsetTmpBuf = (offsetTmpBufOpt as string | double | arkui_component_units_Resource)
        }
        const offsetTmpResult : Length | undefined = offsetTmpBuf
        let value : ColorStop = ({color: colorTmpResult, offset: offsetTmpResult} as ColorStop)
        return value
    }
}
