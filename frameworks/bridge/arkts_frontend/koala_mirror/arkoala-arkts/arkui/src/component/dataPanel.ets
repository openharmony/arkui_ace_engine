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
import { Resource_serializer, Resource } from "./../generated/resource"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor, Length } from "./units"
import { Color } from "./enums"
import { ContentModifier, AttributeModifier, hookDataPanelContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        for (let colorStops_counter_i = 0; colorStops_counter_i < colorStops.length; colorStops_counter_i++) {
            const colorStops_element : ColorStop = colorStops[colorStops_counter_i]
            ColorStop_serializer.write(thisSerializer, colorStops_element)
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
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkDataPanelPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._DataPanel_construct(peerId, flags)
        const _peer  = new ArkDataPanelPeer(_peerPtr, peerId, "DataPanel", flags)
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
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setCloseEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setValueColorsAttribute(value: Array<ResourceColor | LinearGradient> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ResourceColor | LinearGradient = value_value[value_value_counter_i]
                let value_value_element_type : int32 = RuntimeType.UNDEFINED
                value_value_element_type = runtimeType(value_value_element)
                if ((TypeChecker.isColor(value_value_element)) || (RuntimeType.NUMBER == value_value_element_type) || (RuntimeType.STRING == value_value_element_type) || (RuntimeType.OBJECT == value_value_element_type)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_element_0  = value_value_element as ResourceColor
                    let value_value_element_0_type : int32 = RuntimeType.UNDEFINED
                    value_value_element_0_type = runtimeType(value_value_element_0)
                    if (TypeChecker.isColor(value_value_element_0)) {
                        thisSerializer.writeInt8((0).toChar())
                        const value_value_element_0_0  = value_value_element_0 as Color
                        thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_element_0_0))
                    }
                    else if (RuntimeType.NUMBER == value_value_element_0_type) {
                        thisSerializer.writeInt8((1).toChar())
                        const value_value_element_0_1  = value_value_element_0 as number
                        thisSerializer.writeNumber(value_value_element_0_1)
                    }
                    else if (RuntimeType.STRING == value_value_element_0_type) {
                        thisSerializer.writeInt8((2).toChar())
                        const value_value_element_0_2  = value_value_element_0 as string
                        thisSerializer.writeString(value_value_element_0_2)
                    }
                    else if (RuntimeType.OBJECT == value_value_element_0_type) {
                        thisSerializer.writeInt8((3).toChar())
                        const value_value_element_0_3  = value_value_element_0 as Resource
                        Resource_serializer.write(thisSerializer, value_value_element_0_3)
                    }
                }
                else if (TypeChecker.isLinearGradient(value_value_element)) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_element_1  = value_value_element as LinearGradient
                    LinearGradient_serializer.write(thisSerializer, value_value_element_1)
                }
            }
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setValueColors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setTrackBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeWidthAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._DataPanelAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackShadowAttribute(value: DataPanelShadowOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            DataPanelShadowOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setTrackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<DataPanelConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    public closeEffect(value: boolean | undefined): this {
        return this
    }
    public valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        return this
    }
    public trackBackgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        return this
    }
    public trackShadow(value: DataPanelShadowOptions | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: DataPanelAttribute): void {
        super.apply(target)
        if (this.closeEffect_value !== undefined)
            target.closeEffect(this.closeEffect_value!)
        if (this.valueColors_value !== undefined)
            target.valueColors(this.valueColors_value!)
        if (this.trackBackgroundColor_value !== undefined)
            target.trackBackgroundColor(this.trackBackgroundColor_value!)
        if (this.strokeWidth_value !== undefined)
            target.strokeWidth(this.strokeWidth_value!)
        if (this.trackShadow_value !== undefined)
            target.trackShadow(this.trackShadow_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
    }
}

export class ArkDataPanelComponent extends ArkCommonMethodComponent implements DataPanelAttribute {
    getPeer(): ArkDataPanelPeer {
        return (this.peer as ArkDataPanelPeer)
    }
    public setDataPanelOptions(options: DataPanelOptions): this {
        if (this.checkPriority("setDataPanelOptions")) {
            const options_casted = options as (DataPanelOptions)
            this.getPeer()?.setDataPanelOptionsAttribute(options_casted)
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
            const value_casted = value as (ContentModifier<DataPanelConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withDataPanelStyle(receiver: DataPanelAttribute, modifier: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkDataPanelStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("DataPanel")
// export function DataPanel(
//     options: DataPanelOptions,
//     @memo
//     content_?: () => void,
// ): DataPanelAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function DataPanel(
    @memo
    style: ((attributes: DataPanelAttribute) => void) | undefined,
    options: DataPanelOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkDataPanelComponent>((): ArkDataPanelComponent => {
        return new ArkDataPanelComponent()
    })
    NodeAttach<ArkDataPanelPeer>((): ArkDataPanelPeer => ArkDataPanelPeer.create(receiver), (_: ArkDataPanelPeer): void => {
        receiver.setDataPanelOptions(options)
        style?.(receiver)
        withDataPanelStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkDataPanelSet extends ArkCommonMethodSet implements DataPanelAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _closeEffect_flag?: boolean
    _closeEffect0_value?: boolean | undefined
    _valueColors_flag?: boolean
    _valueColors0_value?: Array<ResourceColor | LinearGradient> | undefined
    _trackBackgroundColor_flag?: boolean
    _trackBackgroundColor0_value?: ResourceColor | undefined
    _strokeWidth_flag?: boolean
    _strokeWidth0_value?: Length | undefined
    _trackShadow_flag?: boolean
    _trackShadow0_value?: DataPanelShadowOptions | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<DataPanelConfiguration> | undefined
    applyModifierPatch(component: DataPanelAttribute): void {
        if (this._closeEffect_flag)
            component.closeEffect((this._closeEffect0_value as boolean | undefined))
        if (this._valueColors_flag)
            component.valueColors((this._valueColors0_value as Array<ResourceColor | LinearGradient> | undefined))
        if (this._trackBackgroundColor_flag)
            component.trackBackgroundColor((this._trackBackgroundColor0_value as ResourceColor | undefined))
        if (this._strokeWidth_flag)
            component.strokeWidth((this._strokeWidth0_value as Length | undefined))
        if (this._trackShadow_flag)
            component.trackShadow((this._trackShadow0_value as DataPanelShadowOptions | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<DataPanelConfiguration> | undefined))
    }
    public closeEffect(value: boolean | undefined): this {
        this._closeEffect_flag = true
        this._closeEffect0_value = value
        return this
    }
    public valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        this._valueColors_flag = true
        this._valueColors0_value = value
        return this
    }
    public trackBackgroundColor(value: ResourceColor | undefined): this {
        this._trackBackgroundColor_flag = true
        this._trackBackgroundColor0_value = value
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        this._strokeWidth_flag = true
        this._strokeWidth0_value = value
        return this
    }
    public trackShadow(value: DataPanelShadowOptions | undefined): this {
        this._trackShadow_flag = true
        this._trackShadow0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<DataPanelConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_values  = value.values
        valueSerializer.writeInt32((value_values.length).toInt())
        for (let value_values_counter_i = 0; value_values_counter_i < value_values.length; value_values_counter_i++) {
            const value_values_element : number = value_values[value_values_counter_i]
            valueSerializer.writeNumber(value_values_element)
        }
        const value_maxValue  = value.maxValue
        valueSerializer.writeNumber(value_maxValue)
    }
    public static read(buffer: DeserializerBase): DataPanelConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<DataPanelConfiguration> = (valueDeserializer.readObject() as ContentModifier<DataPanelConfiguration>)
        const values_buf_length : int32 = valueDeserializer.readInt32()
        let values_buf : Array<number> = new Array<number>(values_buf_length)
        for (let values_buf_i = 0; values_buf_i < values_buf_length; values_buf_i++) {
            values_buf[values_buf_i] = (valueDeserializer.readNumber() as number)
        }
        const values_result : Array<number> = values_buf
        const maxValue_result : number = (valueDeserializer.readNumber() as number)
        let value : DataPanelConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, values: values_result, maxValue: maxValue_result} as DataPanelConfiguration)
        return value
    }
}
export class DataPanelOptions_serializer {
    public static write(buffer: SerializerBase, value: DataPanelOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_values  = value.values
        valueSerializer.writeInt32((value_values.length).toInt())
        for (let value_values_counter_i = 0; value_values_counter_i < value_values.length; value_values_counter_i++) {
            const value_values_element : number = value_values[value_values_counter_i]
            valueSerializer.writeNumber(value_values_element)
        }
        const value_max  = value.max
        let value_max_type : int32 = RuntimeType.UNDEFINED
        value_max_type = runtimeType(value_max)
        valueSerializer.writeInt8((value_max_type).toChar())
        if ((value_max_type) != (RuntimeType.UNDEFINED)) {
            const value_max_value  = value_max!
            valueSerializer.writeNumber(value_max_value)
        }
        const value_type  = value.type
        let value_type_type : int32 = RuntimeType.UNDEFINED
        value_type_type = runtimeType(value_type)
        valueSerializer.writeInt8((value_type_type).toChar())
        if ((value_type_type) != (RuntimeType.UNDEFINED)) {
            const value_type_value  = (value_type as DataPanelType)
            valueSerializer.writeInt32(TypeChecker.DataPanelType_ToNumeric(value_type_value))
        }
    }
    public static read(buffer: DeserializerBase): DataPanelOptions {
        let valueDeserializer : DeserializerBase = buffer
        const values_buf_length : int32 = valueDeserializer.readInt32()
        let values_buf : Array<number> = new Array<number>(values_buf_length)
        for (let values_buf_i = 0; values_buf_i < values_buf_length; values_buf_i++) {
            values_buf[values_buf_i] = (valueDeserializer.readNumber() as number)
        }
        const values_result : Array<number> = values_buf
        const max_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let max_buf : number | undefined
        if ((max_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            max_buf = (valueDeserializer.readNumber() as number)
        }
        const max_result : number | undefined = max_buf
        const type_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let type_buf : DataPanelType | undefined
        if ((type_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            type_buf = TypeChecker.DataPanelType_FromNumeric(valueDeserializer.readInt32())
        }
        const type_result : DataPanelType | undefined = type_buf
        let value : DataPanelOptions = ({values: values_result, max: max_result, type: type_result} as DataPanelOptions)
        return value
    }
}
export class DataPanelShadowOptions_serializer {
    public static write(buffer: SerializerBase, value: DataPanelShadowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        valueSerializer.writeInt8((value_radius_type).toChar())
        if ((value_radius_type) != (RuntimeType.UNDEFINED)) {
            const value_radius_value  = value_radius!
            let value_radius_value_type : int32 = RuntimeType.UNDEFINED
            value_radius_value_type = runtimeType(value_radius_value)
            if (RuntimeType.NUMBER == value_radius_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_radius_value_0  = value_radius_value as number
                valueSerializer.writeNumber(value_radius_value_0)
            }
            else if (RuntimeType.OBJECT == value_radius_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_radius_value_1  = value_radius_value as Resource
                Resource_serializer.write(valueSerializer, value_radius_value_1)
            }
        }
        const value_offsetX  = value.offsetX
        let value_offsetX_type : int32 = RuntimeType.UNDEFINED
        value_offsetX_type = runtimeType(value_offsetX)
        valueSerializer.writeInt8((value_offsetX_type).toChar())
        if ((value_offsetX_type) != (RuntimeType.UNDEFINED)) {
            const value_offsetX_value  = value_offsetX!
            let value_offsetX_value_type : int32 = RuntimeType.UNDEFINED
            value_offsetX_value_type = runtimeType(value_offsetX_value)
            if (RuntimeType.NUMBER == value_offsetX_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_offsetX_value_0  = value_offsetX_value as number
                valueSerializer.writeNumber(value_offsetX_value_0)
            }
            else if (RuntimeType.OBJECT == value_offsetX_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_offsetX_value_1  = value_offsetX_value as Resource
                Resource_serializer.write(valueSerializer, value_offsetX_value_1)
            }
        }
        const value_offsetY  = value.offsetY
        let value_offsetY_type : int32 = RuntimeType.UNDEFINED
        value_offsetY_type = runtimeType(value_offsetY)
        valueSerializer.writeInt8((value_offsetY_type).toChar())
        if ((value_offsetY_type) != (RuntimeType.UNDEFINED)) {
            const value_offsetY_value  = value_offsetY!
            let value_offsetY_value_type : int32 = RuntimeType.UNDEFINED
            value_offsetY_value_type = runtimeType(value_offsetY_value)
            if (RuntimeType.NUMBER == value_offsetY_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_offsetY_value_0  = value_offsetY_value as number
                valueSerializer.writeNumber(value_offsetY_value_0)
            }
            else if (RuntimeType.OBJECT == value_offsetY_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_offsetY_value_1  = value_offsetY_value as Resource
                Resource_serializer.write(valueSerializer, value_offsetY_value_1)
            }
        }
        const value_colors  = value.colors
        let value_colors_type : int32 = RuntimeType.UNDEFINED
        value_colors_type = runtimeType(value_colors)
        valueSerializer.writeInt8((value_colors_type).toChar())
        if ((value_colors_type) != (RuntimeType.UNDEFINED)) {
            const value_colors_value  = value_colors!
            valueSerializer.writeInt32((value_colors_value.length).toInt())
            for (let value_colors_value_counter_i = 0; value_colors_value_counter_i < value_colors_value.length; value_colors_value_counter_i++) {
                const value_colors_value_element : ResourceColor | LinearGradient = value_colors_value[value_colors_value_counter_i]
                let value_colors_value_element_type : int32 = RuntimeType.UNDEFINED
                value_colors_value_element_type = runtimeType(value_colors_value_element)
                if ((TypeChecker.isColor(value_colors_value_element)) || (RuntimeType.NUMBER == value_colors_value_element_type) || (RuntimeType.STRING == value_colors_value_element_type) || (RuntimeType.OBJECT == value_colors_value_element_type)) {
                    valueSerializer.writeInt8((0).toChar())
                    const value_colors_value_element_0  = value_colors_value_element as ResourceColor
                    let value_colors_value_element_0_type : int32 = RuntimeType.UNDEFINED
                    value_colors_value_element_0_type = runtimeType(value_colors_value_element_0)
                    if (TypeChecker.isColor(value_colors_value_element_0)) {
                        valueSerializer.writeInt8((0).toChar())
                        const value_colors_value_element_0_0  = value_colors_value_element_0 as Color
                        valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_colors_value_element_0_0))
                    }
                    else if (RuntimeType.NUMBER == value_colors_value_element_0_type) {
                        valueSerializer.writeInt8((1).toChar())
                        const value_colors_value_element_0_1  = value_colors_value_element_0 as number
                        valueSerializer.writeNumber(value_colors_value_element_0_1)
                    }
                    else if (RuntimeType.STRING == value_colors_value_element_0_type) {
                        valueSerializer.writeInt8((2).toChar())
                        const value_colors_value_element_0_2  = value_colors_value_element_0 as string
                        valueSerializer.writeString(value_colors_value_element_0_2)
                    }
                    else if (RuntimeType.OBJECT == value_colors_value_element_0_type) {
                        valueSerializer.writeInt8((3).toChar())
                        const value_colors_value_element_0_3  = value_colors_value_element_0 as Resource
                        Resource_serializer.write(valueSerializer, value_colors_value_element_0_3)
                    }
                }
                else if (TypeChecker.isLinearGradient(value_colors_value_element)) {
                    valueSerializer.writeInt8((1).toChar())
                    const value_colors_value_element_1  = value_colors_value_element as LinearGradient
                    LinearGradient_serializer.write(valueSerializer, value_colors_value_element_1)
                }
            }
        }
    }
    public static read(buffer: DeserializerBase): DataPanelShadowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const radius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radius_buf : number | Resource | undefined
        if ((radius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const radius_buf__selector : int32 = valueDeserializer.readInt8()
            let radius_buf_ : number | Resource | undefined
            if (radius_buf__selector == (0).toChar()) {
                radius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (radius_buf__selector == (1).toChar()) {
                radius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for radius_buf_ has to be chosen through deserialisation.")
            }
            radius_buf = (radius_buf_ as number | Resource)
        }
        const radius_result : number | Resource | undefined = radius_buf
        const offsetX_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetX_buf : number | Resource | undefined
        if ((offsetX_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const offsetX_buf__selector : int32 = valueDeserializer.readInt8()
            let offsetX_buf_ : number | Resource | undefined
            if (offsetX_buf__selector == (0).toChar()) {
                offsetX_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (offsetX_buf__selector == (1).toChar()) {
                offsetX_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for offsetX_buf_ has to be chosen through deserialisation.")
            }
            offsetX_buf = (offsetX_buf_ as number | Resource)
        }
        const offsetX_result : number | Resource | undefined = offsetX_buf
        const offsetY_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetY_buf : number | Resource | undefined
        if ((offsetY_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const offsetY_buf__selector : int32 = valueDeserializer.readInt8()
            let offsetY_buf_ : number | Resource | undefined
            if (offsetY_buf__selector == (0).toChar()) {
                offsetY_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (offsetY_buf__selector == (1).toChar()) {
                offsetY_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for offsetY_buf_ has to be chosen through deserialisation.")
            }
            offsetY_buf = (offsetY_buf_ as number | Resource)
        }
        const offsetY_result : number | Resource | undefined = offsetY_buf
        const colors_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colors_buf : Array<ResourceColor | LinearGradient> | undefined
        if ((colors_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const colors_buf__length : int32 = valueDeserializer.readInt32()
            let colors_buf_ : Array<ResourceColor | LinearGradient> = new Array<ResourceColor | LinearGradient>(colors_buf__length)
            for (let colors_buf__i = 0; colors_buf__i < colors_buf__length; colors_buf__i++) {
                const colors_buf__buf_selector : int32 = valueDeserializer.readInt8()
                let colors_buf__buf : ResourceColor | LinearGradient | undefined
                if (colors_buf__buf_selector == (0).toChar()) {
                    const colors_buf__buf_u_selector : int32 = valueDeserializer.readInt8()
                    let colors_buf__buf_u : Color | number | string | Resource | undefined
                    if (colors_buf__buf_u_selector == (0).toChar()) {
                        colors_buf__buf_u = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
                    }
                    else if (colors_buf__buf_u_selector == (1).toChar()) {
                        colors_buf__buf_u = (valueDeserializer.readNumber() as number)
                    }
                    else if (colors_buf__buf_u_selector == (2).toChar()) {
                        colors_buf__buf_u = (valueDeserializer.readString() as string)
                    }
                    else if (colors_buf__buf_u_selector == (3).toChar()) {
                        colors_buf__buf_u = Resource_serializer.read(valueDeserializer)
                    }
                    else {
                        throw new Error("One of the branches for colors_buf__buf_u has to be chosen through deserialisation.")
                    }
                    colors_buf__buf = (colors_buf__buf_u as Color | number | string | Resource)
                }
                else if (colors_buf__buf_selector == (1).toChar()) {
                    colors_buf__buf = (LinearGradient_serializer.read(valueDeserializer) as LinearGradient)
                }
                else {
                    throw new Error("One of the branches for colors_buf__buf has to be chosen through deserialisation.")
                }
                colors_buf_[colors_buf__i] = (colors_buf__buf as ResourceColor | LinearGradient)
            }
            colors_buf = colors_buf_
        }
        const colors_result : Array<ResourceColor | LinearGradient> | undefined = colors_buf
        let value : DataPanelShadowOptions = ({radius: radius_result, offsetX: offsetX_result, offsetY: offsetY_result, colors: colors_result} as DataPanelShadowOptions)
        return value
    }
}
export class ColorStop_serializer {
    public static write(buffer: SerializerBase, value: ColorStop): void {
        let valueSerializer : SerializerBase = buffer
        const value_color  = value.color
        let value_color_type : int32 = RuntimeType.UNDEFINED
        value_color_type = runtimeType(value_color)
        if (TypeChecker.isColor(value_color)) {
            valueSerializer.writeInt8((0).toChar())
            const value_color_0  = value_color as Color
            valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_color_0))
        }
        else if (RuntimeType.NUMBER == value_color_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_color_1  = value_color as number
            valueSerializer.writeNumber(value_color_1)
        }
        else if (RuntimeType.STRING == value_color_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_color_2  = value_color as string
            valueSerializer.writeString(value_color_2)
        }
        else if (RuntimeType.OBJECT == value_color_type) {
            valueSerializer.writeInt8((3).toChar())
            const value_color_3  = value_color as Resource
            Resource_serializer.write(valueSerializer, value_color_3)
        }
        const value_offset  = value.offset
        let value_offset_type : int32 = RuntimeType.UNDEFINED
        value_offset_type = runtimeType(value_offset)
        if (RuntimeType.STRING == value_offset_type) {
            valueSerializer.writeInt8((0).toChar())
            const value_offset_0  = value_offset as string
            valueSerializer.writeString(value_offset_0)
        }
        else if (RuntimeType.NUMBER == value_offset_type) {
            valueSerializer.writeInt8((1).toChar())
            const value_offset_1  = value_offset as number
            valueSerializer.writeNumber(value_offset_1)
        }
        else if (RuntimeType.OBJECT == value_offset_type) {
            valueSerializer.writeInt8((2).toChar())
            const value_offset_2  = value_offset as Resource
            Resource_serializer.write(valueSerializer, value_offset_2)
        }
    }
    public static read(buffer: DeserializerBase): ColorStop {
        let valueDeserializer : DeserializerBase = buffer
        const color_buf_selector : int32 = valueDeserializer.readInt8()
        let color_buf : Color | number | string | Resource | undefined
        if (color_buf_selector == (0).toChar()) {
            color_buf = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
        }
        else if (color_buf_selector == (1).toChar()) {
            color_buf = (valueDeserializer.readNumber() as number)
        }
        else if (color_buf_selector == (2).toChar()) {
            color_buf = (valueDeserializer.readString() as string)
        }
        else if (color_buf_selector == (3).toChar()) {
            color_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for color_buf has to be chosen through deserialisation.")
        }
        const color_result : ResourceColor = (color_buf as Color | number | string | Resource)
        const offset_buf_selector : int32 = valueDeserializer.readInt8()
        let offset_buf : string | number | Resource | undefined
        if (offset_buf_selector == (0).toChar()) {
            offset_buf = (valueDeserializer.readString() as string)
        }
        else if (offset_buf_selector == (1).toChar()) {
            offset_buf = (valueDeserializer.readNumber() as number)
        }
        else if (offset_buf_selector == (2).toChar()) {
            offset_buf = Resource_serializer.read(valueDeserializer)
        }
        else {
            throw new Error("One of the branches for offset_buf has to be chosen through deserialisation.")
        }
        const offset_result : Length = (offset_buf as string | number | Resource)
        let value : ColorStop = ({color: color_result, offset: offset_result} as ColorStop)
        return value
    }
}
