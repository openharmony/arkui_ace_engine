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
import { Resource_serializer } from "./../framework/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length } from "./units"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { ContentModifier, AttributeModifier, hookDataPanelContentModifier, hookDataPanelAttributeModifier, AttributeUpdater } from "#handwritten"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { DataPanelModifier } from "./../DataPanelModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
export class LinearGradientInternal {
    public static fromPtr(ptr: KPointer): LinearGradient {
        return new LinearGradient(false, ptr)
    }
}
export class LinearGradient implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(_0: boolean, peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, LinearGradient.getFinalizer())
    }
    constructor(colorStops: Array<ColorStop>) {
        this(false, LinearGradient.construct(colorStops))
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
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
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
                    if (valueTmpValueTmpElementForIdx0 instanceof Color) {
                        thisSerializer.writeInt8((0).toByte())
                        const valueTmpValueTmpElementForIdx0ForIdx0  = valueTmpValueTmpElementForIdx0 as Color
                        thisSerializer.writeInt32(valueTmpValueTmpElementForIdx0ForIdx0.getOrdinal())
                    } else if (valueTmpValueTmpElementForIdx0 instanceof number) {
                        thisSerializer.writeInt8((1).toByte())
                        const valueTmpValueTmpElementForIdx0ForIdx1  = valueTmpValueTmpElementForIdx0 as number
                        thisSerializer.writeNumber(valueTmpValueTmpElementForIdx0ForIdx1)
                    } else if (valueTmpValueTmpElementForIdx0 instanceof string) {
                        thisSerializer.writeInt8((2).toByte())
                        const valueTmpValueTmpElementForIdx0ForIdx2  = valueTmpValueTmpElementForIdx0 as string
                        thisSerializer.writeString(valueTmpValueTmpElementForIdx0ForIdx2)
                    } else if (valueTmpValueTmpElementForIdx0 instanceof Resource) {
                        thisSerializer.writeInt8((3).toByte())
                        const valueTmpValueTmpElementForIdx0ForIdx3  = valueTmpValueTmpElementForIdx0 as Resource
                        Resource_serializer.write(thisSerializer, valueTmpValueTmpElementForIdx0ForIdx3)
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
            if (valueTmpValue instanceof Color) {
                thisSerializer.writeInt8((0).toByte())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toByte())
                const valueTmpValueForIdx3  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx3)
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
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toByte())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toByte())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackShadowAttribute(value: DataPanelShadowOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
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
    LINE = 0,
    Line = 0,
    CIRCLE = 1,
    Circle = 1
}
export interface ColorStop {
    color: ResourceColor;
    offset: Length;
}
export interface DataPanelShadowOptions extends MultiShadowOptions {
    colors?: Array<ResourceColor | LinearGradient>;
}
export interface DataPanelOptions {
    values: Array<number>;
    max?: number;
    type?: DataPanelType;
}
export interface DataPanelConfiguration extends CommonConfiguration<DataPanelConfiguration> {
    values: Array<number>;
    maxValue: number;
}
export interface DataPanelAttribute extends CommonMethod {
    setDataPanelOptions(options: DataPanelOptions): this {
        throw new Error("Unimplemented method setDataPanelOptions")
    }
    closeEffect(value: boolean | undefined): this {
        throw new Error("Unimplemented method closeEffect")
    }
    valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        throw new Error("Unimplemented method valueColors")
    }
    trackBackgroundColor(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method trackBackgroundColor")
    }
    strokeWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method strokeWidth")
    }
    trackShadow(value: DataPanelShadowOptions | undefined): this {
        throw new Error("Unimplemented method trackShadow")
    }
    contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkDataPanelStyle extends ArkCommonMethodStyle implements DataPanelAttribute {
    closeEffect_value?: boolean | undefined
    valueColors_value?: Array<ResourceColor | LinearGradient> | undefined
    trackBackgroundColor_value?: ResourceColor | undefined
    strokeWidth_value?: Length | undefined
    trackShadow_value?: DataPanelShadowOptions | undefined
    contentModifier_value?: ContentModifier<DataPanelConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined
    setDataPanelOptions(options: DataPanelOptions): this {
        return this
    }
    closeEffect(value: boolean | undefined): this {
        return this
    }
    valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        return this
    }
    trackBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    strokeWidth(value: Length | undefined): this {
        return this
    }
    trackShadow(value: DataPanelShadowOptions | undefined): this {
        return this
    }
    contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkDataPanelComponent extends ArkCommonMethodComponent implements DataPanelAttribute {
    getPeer(): ArkDataPanelPeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkDataPanelPeer)
    }
    public setDataPanelOptions(options: DataPanelOptions): this {
        if (this.checkPriority("setDataPanelOptions")) {
            const options_casted = options as (DataPanelOptions)
            this.getPeer()?.setDataPanelOptionsAttribute(options_casted)
            this.applyOptionsFinish('DataPanelAttribute');
            return this
        }
        return this
    }
    public closeEffect(value: boolean | undefined): this {
        if (this.checkPriority("closeEffect")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setCloseEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        if (this.checkPriority("valueColors")) {
            const value_casted = value as (Array<ResourceColor | LinearGradient> | undefined)
            this.getPeer()?.setValueColorsAttribute(value_casted)
            return this
        }
        return this
    }
    public trackBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("trackBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setTrackBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.setStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public trackShadow(value: DataPanelShadowOptions | undefined): this {
        if (this.checkPriority("trackShadow")) {
            const value_casted = value as (DataPanelShadowOptions | undefined)
            this.getPeer()?.setTrackShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            hookDataPanelContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        hookDataPanelAttributeModifier(this, value);
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
    @memo
    style: ((attributes: DataPanelAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkDataPanelComponent>((): ArkDataPanelComponent => {
        return new ArkDataPanelComponent()
    })
    NodeAttach<ArkDataPanelPeer>((): ArkDataPanelPeer => ArkDataPanelPeer.create(receiver), (peer: ArkDataPanelPeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
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
            const valueHolderForValuesTmpElement : number = valueHolderForValues[valueHolderForValuesCounterI]
            valueSerializer.writeNumber(valueHolderForValuesTmpElement)
        }
        const valueHolderForMaxValue  = value.maxValue
        valueSerializer.writeNumber(valueHolderForMaxValue)
    }
    public static read(buffer: DeserializerBase): DataPanelConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<DataPanelConfiguration> = (valueDeserializer.readObject() as ContentModifier<DataPanelConfiguration>)
        const valuesTmpBufLength : int32 = valueDeserializer.readInt32()
        let valuesTmpBuf : Array<number> = new Array<number>(valuesTmpBufLength)
        for (let valuesTmpBufBufCounterI = 0; valuesTmpBufBufCounterI < valuesTmpBufLength; valuesTmpBufBufCounterI++) {
            valuesTmpBuf[valuesTmpBufBufCounterI] = (valueDeserializer.readNumber() as number)
        }
        const valuesTmpResult : Array<number> = valuesTmpBuf
        const maxValueTmpResult : number = (valueDeserializer.readNumber() as number)
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
            const valueHolderForValuesTmpElement : number = valueHolderForValues[valueHolderForValuesCounterI]
            valueSerializer.writeNumber(valueHolderForValuesTmpElement)
        }
        const valueHolderForMax  = value.max
        if (valueHolderForMax !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxTmpValue  = valueHolderForMax!
            valueSerializer.writeNumber(valueHolderForMaxTmpValue)
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
        let valuesTmpBuf : Array<number> = new Array<number>(valuesTmpBufLength)
        for (let valuesTmpBufBufCounterI = 0; valuesTmpBufBufCounterI < valuesTmpBufLength; valuesTmpBufBufCounterI++) {
            valuesTmpBuf[valuesTmpBufBufCounterI] = (valueDeserializer.readNumber() as number)
        }
        const valuesTmpResult : Array<number> = valuesTmpBuf
        const maxTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxTmpBuf : number | undefined = undefined
        if ((maxTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const maxTmpResult : number | undefined = maxTmpBuf
        const typeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
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
            if (valueHolderForRadiusTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toByte())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as number
                valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx0)
            } else if (valueHolderForRadiusTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForRadiusTmpValueForIdx1  = valueHolderForRadiusTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForRadiusTmpValueForIdx1)
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
            } else if (valueHolderForOffsetXTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOffsetXTmpValueForIdx1  = valueHolderForOffsetXTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForOffsetXTmpValueForIdx1)
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
            } else if (valueHolderForOffsetYTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toByte())
                const valueHolderForOffsetYTmpValueForIdx1  = valueHolderForOffsetYTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForOffsetYTmpValueForIdx1)
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
                    if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof Color) {
                        valueSerializer.writeInt8((0).toByte())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx0  = valueHolderForColorsTmpValueTmpElementForIdx0 as Color
                        valueSerializer.writeInt32(valueHolderForColorsTmpValueTmpElementForIdx0ForIdx0.getOrdinal())
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof number) {
                        valueSerializer.writeInt8((1).toByte())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx1  = valueHolderForColorsTmpValueTmpElementForIdx0 as number
                        valueSerializer.writeNumber(valueHolderForColorsTmpValueTmpElementForIdx0ForIdx1)
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof string) {
                        valueSerializer.writeInt8((2).toByte())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx2  = valueHolderForColorsTmpValueTmpElementForIdx0 as string
                        valueSerializer.writeString(valueHolderForColorsTmpValueTmpElementForIdx0ForIdx2)
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof Resource) {
                        valueSerializer.writeInt8((3).toByte())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx3  = valueHolderForColorsTmpValueTmpElementForIdx0 as Resource
                        Resource_serializer.write(valueSerializer, valueHolderForColorsTmpValueTmpElementForIdx0ForIdx3)
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
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : number | Resource | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBuf_ : number | Resource | undefined
            if (radiusTmpBuf_UnionSelector == (0).toChar()) {
                radiusTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (radiusTmpBuf_UnionSelector == (1).toChar()) {
                radiusTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for radiusTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusTmpBuf = (radiusTmpBuf_ as number | Resource)
        }
        const radiusTmpResult : number | Resource | undefined = radiusTmpBuf
        const offsetXTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetXTmpBuf : double | Resource | undefined = undefined
        if ((offsetXTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetXTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let offsetXTmpBuf_ : double | Resource | undefined
            if (offsetXTmpBuf_UnionSelector == (0).toChar()) {
                offsetXTmpBuf_ = valueDeserializer.readFloat64()
            } else if (offsetXTmpBuf_UnionSelector == (1).toChar()) {
                offsetXTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for offsetXTmpBuf_ has to be chosen through deserialisation.")
            }
            offsetXTmpBuf = (offsetXTmpBuf_ as double | Resource)
        }
        const offsetXTmpResult : double | Resource | undefined = offsetXTmpBuf
        const offsetYTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetYTmpBuf : double | Resource | undefined = undefined
        if ((offsetYTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetYTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let offsetYTmpBuf_ : double | Resource | undefined
            if (offsetYTmpBuf_UnionSelector == (0).toChar()) {
                offsetYTmpBuf_ = valueDeserializer.readFloat64()
            } else if (offsetYTmpBuf_UnionSelector == (1).toChar()) {
                offsetYTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for offsetYTmpBuf_ has to be chosen through deserialisation.")
            }
            offsetYTmpBuf = (offsetYTmpBuf_ as double | Resource)
        }
        const offsetYTmpResult : double | Resource | undefined = offsetYTmpBuf
        const colorsTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorsTmpBuf : Array<ResourceColor | LinearGradient> | undefined = undefined
        if ((colorsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorsTmpBuf_Length : int32 = valueDeserializer.readInt32()
            let colorsTmpBuf_ : Array<ResourceColor | LinearGradient> = new Array<ResourceColor | LinearGradient>(colorsTmpBuf_Length)
            for (let colorsTmpBuf_BufCounterI = 0; colorsTmpBuf_BufCounterI < colorsTmpBuf_Length; colorsTmpBuf_BufCounterI++) {
                const colorsTmpBuf_TempBufUnionSelector : int32 = valueDeserializer.readInt8()
                let colorsTmpBuf_TempBuf : ResourceColor | LinearGradient | undefined
                if (colorsTmpBuf_TempBufUnionSelector == (0).toChar()) {
                    const colorsTmpBuf_TempBufBufUUnionSelector : int32 = valueDeserializer.readInt8()
                    let colorsTmpBuf_TempBufBufU : Color | number | string | Resource | undefined
                    if (colorsTmpBuf_TempBufBufUUnionSelector == (0).toChar()) {
                        colorsTmpBuf_TempBufBufU = Color.values()[valueDeserializer.readInt32()]
                    } else if (colorsTmpBuf_TempBufBufUUnionSelector == (1).toChar()) {
                        colorsTmpBuf_TempBufBufU = (valueDeserializer.readNumber() as number)
                    } else if (colorsTmpBuf_TempBufBufUUnionSelector == (2).toChar()) {
                        colorsTmpBuf_TempBufBufU = (valueDeserializer.readString() as string)
                    } else if (colorsTmpBuf_TempBufBufUUnionSelector == (3).toChar()) {
                        colorsTmpBuf_TempBufBufU = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for colorsTmpBuf_TempBufBufU has to be chosen through deserialisation.")
                    }
                    colorsTmpBuf_TempBuf = (colorsTmpBuf_TempBufBufU as Color | number | string | Resource)
                } else if (colorsTmpBuf_TempBufUnionSelector == (1).toChar()) {
                    colorsTmpBuf_TempBuf = (LinearGradient_serializer.read(valueDeserializer) as LinearGradient)
                } else {
                    throw new Error("One of the branches for colorsTmpBuf_TempBuf has to be chosen through deserialisation.")
                }
                colorsTmpBuf_[colorsTmpBuf_BufCounterI] = (colorsTmpBuf_TempBuf as ResourceColor | LinearGradient)
            }
            colorsTmpBuf = colorsTmpBuf_
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
        if (valueHolderForColor instanceof Color) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForColorForIdx0  = valueHolderForColor as Color
            valueSerializer.writeInt32(valueHolderForColorForIdx0.getOrdinal())
        } else if (valueHolderForColor instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForColorForIdx1  = valueHolderForColor as number
            valueSerializer.writeNumber(valueHolderForColorForIdx1)
        } else if (valueHolderForColor instanceof string) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForColorForIdx2  = valueHolderForColor as string
            valueSerializer.writeString(valueHolderForColorForIdx2)
        } else if (valueHolderForColor instanceof Resource) {
            valueSerializer.writeInt8((3).toByte())
            const valueHolderForColorForIdx3  = valueHolderForColor as Resource
            Resource_serializer.write(valueSerializer, valueHolderForColorForIdx3)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForOffsetForIdx0  = valueHolderForOffset as string
            valueSerializer.writeString(valueHolderForOffsetForIdx0)
        } else if (valueHolderForOffset instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForOffsetForIdx1  = valueHolderForOffset as number
            valueSerializer.writeNumber(valueHolderForOffsetForIdx1)
        } else if (valueHolderForOffset instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForOffsetForIdx2  = valueHolderForOffset as Resource
            Resource_serializer.write(valueSerializer, valueHolderForOffsetForIdx2)
        }
    }
    public static read(buffer: DeserializerBase): ColorStop {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let colorTmpBuf : Color | number | string | Resource | undefined
        if (colorTmpBufUnionSelector == (0).toChar()) {
            colorTmpBuf = Color.values()[valueDeserializer.readInt32()]
        } else if (colorTmpBufUnionSelector == (1).toChar()) {
            colorTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (colorTmpBufUnionSelector == (2).toChar()) {
            colorTmpBuf = (valueDeserializer.readString() as string)
        } else if (colorTmpBufUnionSelector == (3).toChar()) {
            colorTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for colorTmpBuf has to be chosen through deserialisation.")
        }
        const colorTmpResult : ResourceColor = (colorTmpBuf as Color | number | string | Resource)
        const offsetTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let offsetTmpBuf : string | number | Resource | undefined
        if (offsetTmpBufUnionSelector == (0).toChar()) {
            offsetTmpBuf = (valueDeserializer.readString() as string)
        } else if (offsetTmpBufUnionSelector == (1).toChar()) {
            offsetTmpBuf = (valueDeserializer.readNumber() as number)
        } else if (offsetTmpBufUnionSelector == (2).toChar()) {
            offsetTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for offsetTmpBuf has to be chosen through deserialisation.")
        }
        const offsetTmpResult : Length = (offsetTmpBuf as string | number | Resource)
        let value : ColorStop = ({color: colorTmpResult, offset: offsetTmpResult} as ColorStop)
        return value
    }
}
