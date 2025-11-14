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
import { ModifierStateManager } from '../CommonModifier';
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
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueTmpElementForIdx0  = valueTmpValueTmpElement as ResourceColor
                    if (valueTmpValueTmpElementForIdx0 instanceof Color) {
                        thisSerializer.writeInt8((0).toChar())
                        const valueTmpValueTmpElementForIdx0ForIdx0  = valueTmpValueTmpElementForIdx0 as Color
                        thisSerializer.writeInt32(valueTmpValueTmpElementForIdx0ForIdx0.getOrdinal())
                    } else if (valueTmpValueTmpElementForIdx0 instanceof int32) {
                        thisSerializer.writeInt8((1).toChar())
                        const valueTmpValueTmpElementForIdx0ForIdx1  = valueTmpValueTmpElementForIdx0 as int32
                        thisSerializer.writeInt32(valueTmpValueTmpElementForIdx0ForIdx1)
                    } else if (valueTmpValueTmpElementForIdx0 instanceof string) {
                        thisSerializer.writeInt8((2).toChar())
                        const valueTmpValueTmpElementForIdx0ForIdx2  = valueTmpValueTmpElementForIdx0 as string
                        thisSerializer.writeString(valueTmpValueTmpElementForIdx0ForIdx2)
                    } else if (valueTmpValueTmpElementForIdx0 instanceof Resource) {
                        thisSerializer.writeInt8((3).toChar())
                        const valueTmpValueTmpElementForIdx0ForIdx3  = valueTmpValueTmpElementForIdx0 as Resource
                        Resource_serializer.write(thisSerializer, valueTmpValueTmpElementForIdx0ForIdx3)
                    }
                } else if (valueTmpValueTmpElement instanceof LinearGradient) {
                    thisSerializer.writeInt8((1).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as Color
                thisSerializer.writeInt32(valueTmpValueForIdx0.getOrdinal())
            } else if (valueTmpValue instanceof int32) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as int32
                thisSerializer.writeInt32(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof string) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx2)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((3).toChar())
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
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as string
                thisSerializer.writeString(valueTmpValueForIdx0)
            } else if (valueTmpValue instanceof double) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as double
                thisSerializer.writeFloat64(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
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
        const maxTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxTmpBuf : double | undefined = undefined
        if ((maxTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxTmpBuf = valueDeserializer.readFloat64()
        }
        const maxTmpResult : double | undefined = maxTmpBuf
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
            if (valueHolderForRadiusTmpValue instanceof double) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as double
                valueSerializer.writeFloat64(valueHolderForRadiusTmpValueForIdx0)
            } else if (valueHolderForRadiusTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
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
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForOffsetXTmpValueForIdx0  = valueHolderForOffsetXTmpValue as double
                valueSerializer.writeFloat64(valueHolderForOffsetXTmpValueForIdx0)
            } else if (valueHolderForOffsetXTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
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
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForOffsetYTmpValueForIdx0  = valueHolderForOffsetYTmpValue as double
                valueSerializer.writeFloat64(valueHolderForOffsetYTmpValueForIdx0)
            } else if (valueHolderForOffsetYTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
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
                    valueSerializer.writeInt8((0).toChar())
                    const valueHolderForColorsTmpValueTmpElementForIdx0  = valueHolderForColorsTmpValueTmpElement as ResourceColor
                    if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof Color) {
                        valueSerializer.writeInt8((0).toChar())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx0  = valueHolderForColorsTmpValueTmpElementForIdx0 as Color
                        valueSerializer.writeInt32(valueHolderForColorsTmpValueTmpElementForIdx0ForIdx0.getOrdinal())
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof int32) {
                        valueSerializer.writeInt8((1).toChar())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx1  = valueHolderForColorsTmpValueTmpElementForIdx0 as int32
                        valueSerializer.writeInt32(valueHolderForColorsTmpValueTmpElementForIdx0ForIdx1)
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof string) {
                        valueSerializer.writeInt8((2).toChar())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx2  = valueHolderForColorsTmpValueTmpElementForIdx0 as string
                        valueSerializer.writeString(valueHolderForColorsTmpValueTmpElementForIdx0ForIdx2)
                    } else if (valueHolderForColorsTmpValueTmpElementForIdx0 instanceof Resource) {
                        valueSerializer.writeInt8((3).toChar())
                        const valueHolderForColorsTmpValueTmpElementForIdx0ForIdx3  = valueHolderForColorsTmpValueTmpElementForIdx0 as Resource
                        Resource_serializer.write(valueSerializer, valueHolderForColorsTmpValueTmpElementForIdx0ForIdx3)
                    }
                } else if (valueHolderForColorsTmpValueTmpElement instanceof LinearGradient) {
                    valueSerializer.writeInt8((1).toChar())
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
        let radiusTmpBuf : double | Resource | undefined = undefined
        if ((radiusTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const radiusTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let radiusTmpBuf_ : double | Resource | undefined
            if (radiusTmpBuf_UnionSelector == (0).toChar()) {
                radiusTmpBuf_ = valueDeserializer.readFloat64()
            } else if (radiusTmpBuf_UnionSelector == (1).toChar()) {
                radiusTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for radiusTmpBuf_ has to be chosen through deserialisation.")
            }
            radiusTmpBuf = (radiusTmpBuf_ as double | Resource)
        }
        const radiusTmpResult : double | Resource | undefined = radiusTmpBuf
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
                    let colorsTmpBuf_TempBufBufU : Color | int32 | string | Resource | undefined
                    if (colorsTmpBuf_TempBufBufUUnionSelector == (0).toChar()) {
                        colorsTmpBuf_TempBufBufU = Color.values()[valueDeserializer.readInt32()]
                    } else if (colorsTmpBuf_TempBufBufUUnionSelector == (1).toChar()) {
                        colorsTmpBuf_TempBufBufU = (valueDeserializer.readInt32())
                    } else if (colorsTmpBuf_TempBufBufUUnionSelector == (2).toChar()) {
                        colorsTmpBuf_TempBufBufU = (valueDeserializer.readString() as string)
                    } else if (colorsTmpBuf_TempBufBufUUnionSelector == (3).toChar()) {
                        colorsTmpBuf_TempBufBufU = Resource_serializer.read(valueDeserializer)
                    } else {
                        throw new Error("One of the branches for colorsTmpBuf_TempBufBufU has to be chosen through deserialisation.")
                    }
                    colorsTmpBuf_TempBuf = (colorsTmpBuf_TempBufBufU as Color | int32 | string | Resource)
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
        if (valueHolderForColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForColorTmpValue  = valueHolderForColor!
            if (valueHolderForColorTmpValue instanceof Color) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForColorTmpValueForIdx0  = valueHolderForColorTmpValue as Color
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx0.getOrdinal())
            } else if (valueHolderForColorTmpValue instanceof int32) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForColorTmpValueForIdx1  = valueHolderForColorTmpValue as int32
                valueSerializer.writeInt32(valueHolderForColorTmpValueForIdx1)
            } else if (valueHolderForColorTmpValue instanceof string) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForColorTmpValueForIdx2  = valueHolderForColorTmpValue as string
                valueSerializer.writeString(valueHolderForColorTmpValueForIdx2)
            } else if (valueHolderForColorTmpValue instanceof Resource) {
                valueSerializer.writeInt8((3).toChar())
                const valueHolderForColorTmpValueForIdx3  = valueHolderForColorTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForColorTmpValueForIdx3)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForOffset  = value.offset
        if (valueHolderForOffset !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForOffsetTmpValue  = valueHolderForOffset!
            if (valueHolderForOffsetTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForOffsetTmpValueForIdx0  = valueHolderForOffsetTmpValue as string
                valueSerializer.writeString(valueHolderForOffsetTmpValueForIdx0)
            } else if (valueHolderForOffsetTmpValue instanceof double) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForOffsetTmpValueForIdx1  = valueHolderForOffsetTmpValue as double
                valueSerializer.writeFloat64(valueHolderForOffsetTmpValueForIdx1)
            } else if (valueHolderForOffsetTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForOffsetTmpValueForIdx2  = valueHolderForOffsetTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForOffsetTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ColorStop {
        let valueDeserializer : DeserializerBase = buffer
        const colorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colorTmpBuf : ResourceColor | undefined = undefined
        if ((colorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const colorTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let colorTmpBuf_ : Color | int32 | string | Resource | undefined
            if (colorTmpBuf_UnionSelector == (0).toChar()) {
                colorTmpBuf_ = Color.values()[valueDeserializer.readInt32()]
            } else if (colorTmpBuf_UnionSelector == (1).toChar()) {
                colorTmpBuf_ = valueDeserializer.readInt32()
            } else if (colorTmpBuf_UnionSelector == (2).toChar()) {
                colorTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (colorTmpBuf_UnionSelector == (3).toChar()) {
                colorTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for colorTmpBuf_ has to be chosen through deserialisation.")
            }
            colorTmpBuf = (colorTmpBuf_ as Color | int32 | string | Resource)
        }
        const colorTmpResult : ResourceColor | undefined = colorTmpBuf
        const offsetTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetTmpBuf : Length | undefined = undefined
        if ((offsetTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let offsetTmpBuf_ : string | double | Resource | undefined
            if (offsetTmpBuf_UnionSelector == (0).toChar()) {
                offsetTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (offsetTmpBuf_UnionSelector == (1).toChar()) {
                offsetTmpBuf_ = valueDeserializer.readFloat64()
            } else if (offsetTmpBuf_UnionSelector == (2).toChar()) {
                offsetTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for offsetTmpBuf_ has to be chosen through deserialisation.")
            }
            offsetTmpBuf = (offsetTmpBuf_ as string | double | Resource)
        }
        const offsetTmpResult : Length | undefined = offsetTmpBuf
        let value : ColorStop = ({color: colorTmpResult, offset: offsetTmpResult} as ColorStop)
        return value
    }
}
