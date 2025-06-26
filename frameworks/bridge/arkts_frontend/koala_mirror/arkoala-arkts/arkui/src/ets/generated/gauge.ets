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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./resource"
import { LinearGradient_serializer, LinearGradient } from "./dataPanel"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length, ResourceStr, Dimension } from "./units"
import { Color } from "./enums"
import { CustomBuilder } from "./builder"
import { ContentModifier, AttributeModifier, hookGaugeContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkGaugePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGaugePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Gauge_construct(peerId, flags)
        const _peer  = new ArkGaugePeer(_peerPtr, peerId, "Gauge", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setGaugeOptionsAttribute(options: GaugeOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        GaugeOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._GaugeInterface_setGaugeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    valueAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    startAngleAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_startAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    endAngleAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_endAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorsAttribute(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3)
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8(1)
                const value_value_1  = value_value as LinearGradient
                LinearGradient_serializer.write(thisSerializer, value_value_1)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value_value))) {
                thisSerializer.writeInt8(2)
                const value_value_2  = value_value as Array<[ ResourceColor | LinearGradient, number ]>
                thisSerializer.writeInt32(value_value_2.length as int32)
                for (let i = 0; i < value_value_2.length; i++) {
                    const value_value_2_element : [ ResourceColor | LinearGradient, number ] = value_value_2[i]
                    const value_value_2_element_0  = value_value_2_element[0]
                    let value_value_2_element_0_type : int32 = RuntimeType.UNDEFINED
                    value_value_2_element_0_type = runtimeType(value_value_2_element_0)
                    if ((TypeChecker.isColor(value_value_2_element_0)) || (RuntimeType.NUMBER == value_value_2_element_0_type) || (RuntimeType.STRING == value_value_2_element_0_type) || (RuntimeType.OBJECT == value_value_2_element_0_type)) {
                        thisSerializer.writeInt8(0)
                        const value_value_2_element_0_0  = value_value_2_element_0 as ResourceColor
                        let value_value_2_element_0_0_type : int32 = RuntimeType.UNDEFINED
                        value_value_2_element_0_0_type = runtimeType(value_value_2_element_0_0)
                        if (TypeChecker.isColor(value_value_2_element_0_0)) {
                            thisSerializer.writeInt8(0)
                            const value_value_2_element_0_0_0  = value_value_2_element_0_0 as Color
                            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_2_element_0_0_0))
                        }
                        else if (RuntimeType.NUMBER == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8(1)
                            const value_value_2_element_0_0_1  = value_value_2_element_0_0 as number
                            thisSerializer.writeNumber(value_value_2_element_0_0_1)
                        }
                        else if (RuntimeType.STRING == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8(2)
                            const value_value_2_element_0_0_2  = value_value_2_element_0_0 as string
                            thisSerializer.writeString(value_value_2_element_0_0_2)
                        }
                        else if (RuntimeType.OBJECT == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8(3)
                            const value_value_2_element_0_0_3  = value_value_2_element_0_0 as Resource
                            Resource_serializer.write(thisSerializer, value_value_2_element_0_0_3)
                        }
                    }
                    else if (TypeChecker.isLinearGradient(value_value_2_element_0)) {
                        thisSerializer.writeInt8(1)
                        const value_value_2_element_0_1  = value_value_2_element_0 as LinearGradient
                        LinearGradient_serializer.write(thisSerializer, value_value_2_element_0_1)
                    }
                    const value_value_2_element_1  = value_value_2_element[1]
                    thisSerializer.writeNumber(value_value_2_element_1)
                }
            }
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_colors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: Length | undefined): void {
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
        ArkUIGeneratedNativeModule._GaugeAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    descriptionAttribute(value: CustomBuilder | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value))
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_description(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackShadowAttribute(value: GaugeShadowOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            GaugeShadowOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_trackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorAttribute(value: GaugeIndicatorOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            GaugeIndicatorOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_indicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_privacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier<GaugeConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface GaugeOptions {
    value: number;
    min?: number;
    max?: number;
}
export interface GaugeShadowOptions extends MultiShadowOptions {
}
export interface GaugeIndicatorOptions {
    icon?: ResourceStr;
    space?: Dimension;
}
export interface GaugeConfiguration extends CommonConfiguration<GaugeConfiguration> {
    value: number;
    min: number;
    max: number;
}
export interface GaugeAttribute extends CommonMethod {
    value(value: number | undefined): this
    startAngle(value: number | undefined): this
    endAngle(value: number | undefined): this
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): this
    strokeWidth(value: Length | undefined): this
    description(value: CustomBuilder | undefined): this
    trackShadow(value: GaugeShadowOptions | undefined): this
    indicator(value: GaugeIndicatorOptions | undefined): this
    privacySensitive(value: boolean | undefined): this
    contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this
    attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkGaugeStyle extends ArkCommonMethodStyle implements GaugeAttribute {
    value_value?: number | undefined
    startAngle_value?: number | undefined
    endAngle_value?: number | undefined
    colors_value?: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined
    strokeWidth_value?: Length | undefined
    description_value?: CustomBuilder | undefined
    trackShadow_value?: GaugeShadowOptions | undefined
    indicator_value?: GaugeIndicatorOptions | undefined
    privacySensitive_value?: boolean | undefined
    contentModifier_value?: ContentModifier<GaugeConfiguration> | undefined
    attributeModifier_value?: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined
    public value(value: number | undefined): this {
        return this
    }
    public startAngle(value: number | undefined): this {
        return this
    }
    public endAngle(value: number | undefined): this {
        return this
    }
    public colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): this {
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        return this
    }
    public description(value: CustomBuilder | undefined): this {
        return this
    }
    public trackShadow(value: GaugeShadowOptions | undefined): this {
        return this
    }
    public indicator(value: GaugeIndicatorOptions | undefined): this {
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: GaugeAttribute): void {
        super.apply(target)
        if (this.value_value !== undefined)
            target.value(this.value_value!)
        if (this.startAngle_value !== undefined)
            target.startAngle(this.startAngle_value!)
        if (this.endAngle_value !== undefined)
            target.endAngle(this.endAngle_value!)
        if (this.colors_value !== undefined)
            target.colors(this.colors_value!)
        if (this.strokeWidth_value !== undefined)
            target.strokeWidth(this.strokeWidth_value!)
        if (this.description_value !== undefined)
            target.description(this.description_value!)
        if (this.trackShadow_value !== undefined)
            target.trackShadow(this.trackShadow_value!)
        if (this.indicator_value !== undefined)
            target.indicator(this.indicator_value!)
        if (this.privacySensitive_value !== undefined)
            target.privacySensitive(this.privacySensitive_value!)
        if (this.contentModifier_value !== undefined)
            target.contentModifier(this.contentModifier_value!)
    }
}

export class ArkGaugeComponent extends ArkCommonMethodComponent implements GaugeAttribute {
    getPeer(): ArkGaugePeer {
        return (this.peer as ArkGaugePeer)
    }
    public setGaugeOptions(options: GaugeOptions): this {
        if (this.checkPriority("setGaugeOptions")) {
            const options_casted = options as (GaugeOptions)
            this.getPeer()?.setGaugeOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    public value(value: number | undefined): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.valueAttribute(value_casted)
            return this
        }
        return this
    }
    public startAngle(value: number | undefined): this {
        if (this.checkPriority("startAngle")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.startAngleAttribute(value_casted)
            return this
        }
        return this
    }
    public endAngle(value: number | undefined): this {
        if (this.checkPriority("endAngle")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.endAngleAttribute(value_casted)
            return this
        }
        return this
    }
    public colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): this {
        if (this.checkPriority("colors")) {
            const value_casted = value as (ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined)
            this.getPeer()?.colorsAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.strokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public description(value: CustomBuilder | undefined): this {
        if (this.checkPriority("description")) {
            const value_casted = value as (CustomBuilder | undefined)
            this.getPeer()?.descriptionAttribute(value_casted)
            return this
        }
        return this
    }
    public trackShadow(value: GaugeShadowOptions | undefined): this {
        if (this.checkPriority("trackShadow")) {
            const value_casted = value as (GaugeShadowOptions | undefined)
            this.getPeer()?.trackShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public indicator(value: GaugeIndicatorOptions | undefined): this {
        if (this.checkPriority("indicator")) {
            const value_casted = value as (GaugeIndicatorOptions | undefined)
            this.getPeer()?.indicatorAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            hookGaugeContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withGaugeStyle(receiver: GaugeAttribute, modifier: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkGaugeStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("GaugeImpl")
export function Gauge(
    options: GaugeOptions,
    @memo
    content_?: () => void,
): GaugeAttribute {
    throw new Error("Not implemented")
}

@memo
export function GaugeImpl(
    @memo
    style: ((attributes: GaugeAttribute) => void) | undefined,
    options: GaugeOptions,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkGaugeComponent>((): ArkGaugeComponent => {
        return new ArkGaugeComponent()
    })
    NodeAttach<ArkGaugePeer>((): ArkGaugePeer => ArkGaugePeer.create(receiver), (_: ArkGaugePeer): void => {
        receiver.setGaugeOptions(options)
        style?.(receiver)
        withGaugeStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class GaugeConfiguration_serializer {
    public static write(buffer: SerializerBase, value: GaugeConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const value_enabled  = value.enabled
        valueSerializer.writeBoolean(value_enabled)
        const value_contentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(value_contentModifier)
        const value_value  = value.value
        valueSerializer.writeNumber(value_value)
        const value_min  = value.min
        valueSerializer.writeNumber(value_min)
        const value_max  = value.max
        valueSerializer.writeNumber(value_max)
    }
    public static read(buffer: DeserializerBase): GaugeConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabled_result : boolean = valueDeserializer.readBoolean()
        const contentModifier_result : ContentModifier<GaugeConfiguration> = (valueDeserializer.readObject() as ContentModifier<GaugeConfiguration>)
        const value_result : number = (valueDeserializer.readNumber() as number)
        const min_result : number = (valueDeserializer.readNumber() as number)
        const max_result : number = (valueDeserializer.readNumber() as number)
        let value : GaugeConfiguration = ({enabled: enabled_result, contentModifier: contentModifier_result, value: value_result, min: min_result, max: max_result} as GaugeConfiguration)
        return value
    }
}
export class GaugeOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_value  = value.value
        valueSerializer.writeNumber(value_value)
        const value_min  = value.min
        let value_min_type : int32 = RuntimeType.UNDEFINED
        value_min_type = runtimeType(value_min)
        valueSerializer.writeInt8(value_min_type)
        if ((RuntimeType.UNDEFINED) != (value_min_type)) {
            const value_min_value  = value_min!
            valueSerializer.writeNumber(value_min_value)
        }
        const value_max  = value.max
        let value_max_type : int32 = RuntimeType.UNDEFINED
        value_max_type = runtimeType(value_max)
        valueSerializer.writeInt8(value_max_type)
        if ((RuntimeType.UNDEFINED) != (value_max_type)) {
            const value_max_value  = value_max!
            valueSerializer.writeNumber(value_max_value)
        }
    }
    public static read(buffer: DeserializerBase): GaugeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const value_result : number = (valueDeserializer.readNumber() as number)
        const min_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let min_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (min_buf_runtimeType))
        {
            min_buf = (valueDeserializer.readNumber() as number)
        }
        const min_result : number | undefined = min_buf
        const max_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let max_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (max_buf_runtimeType))
        {
            max_buf = (valueDeserializer.readNumber() as number)
        }
        const max_result : number | undefined = max_buf
        let value : GaugeOptions = ({value: value_result, min: min_result, max: max_result} as GaugeOptions)
        return value
    }
}
export class GaugeShadowOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeShadowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_radius  = value.radius
        let value_radius_type : int32 = RuntimeType.UNDEFINED
        value_radius_type = runtimeType(value_radius)
        valueSerializer.writeInt8(value_radius_type)
        if ((RuntimeType.UNDEFINED) != (value_radius_type)) {
            const value_radius_value  = value_radius!
            let value_radius_value_type : int32 = RuntimeType.UNDEFINED
            value_radius_value_type = runtimeType(value_radius_value)
            if (RuntimeType.NUMBER == value_radius_value_type) {
                valueSerializer.writeInt8(0)
                const value_radius_value_0  = value_radius_value as number
                valueSerializer.writeNumber(value_radius_value_0)
            }
            else if (RuntimeType.OBJECT == value_radius_value_type) {
                valueSerializer.writeInt8(1)
                const value_radius_value_1  = value_radius_value as Resource
                Resource_serializer.write(valueSerializer, value_radius_value_1)
            }
        }
        const value_offsetX  = value.offsetX
        let value_offsetX_type : int32 = RuntimeType.UNDEFINED
        value_offsetX_type = runtimeType(value_offsetX)
        valueSerializer.writeInt8(value_offsetX_type)
        if ((RuntimeType.UNDEFINED) != (value_offsetX_type)) {
            const value_offsetX_value  = value_offsetX!
            let value_offsetX_value_type : int32 = RuntimeType.UNDEFINED
            value_offsetX_value_type = runtimeType(value_offsetX_value)
            if (RuntimeType.NUMBER == value_offsetX_value_type) {
                valueSerializer.writeInt8(0)
                const value_offsetX_value_0  = value_offsetX_value as number
                valueSerializer.writeNumber(value_offsetX_value_0)
            }
            else if (RuntimeType.OBJECT == value_offsetX_value_type) {
                valueSerializer.writeInt8(1)
                const value_offsetX_value_1  = value_offsetX_value as Resource
                Resource_serializer.write(valueSerializer, value_offsetX_value_1)
            }
        }
        const value_offsetY  = value.offsetY
        let value_offsetY_type : int32 = RuntimeType.UNDEFINED
        value_offsetY_type = runtimeType(value_offsetY)
        valueSerializer.writeInt8(value_offsetY_type)
        if ((RuntimeType.UNDEFINED) != (value_offsetY_type)) {
            const value_offsetY_value  = value_offsetY!
            let value_offsetY_value_type : int32 = RuntimeType.UNDEFINED
            value_offsetY_value_type = runtimeType(value_offsetY_value)
            if (RuntimeType.NUMBER == value_offsetY_value_type) {
                valueSerializer.writeInt8(0)
                const value_offsetY_value_0  = value_offsetY_value as number
                valueSerializer.writeNumber(value_offsetY_value_0)
            }
            else if (RuntimeType.OBJECT == value_offsetY_value_type) {
                valueSerializer.writeInt8(1)
                const value_offsetY_value_1  = value_offsetY_value as Resource
                Resource_serializer.write(valueSerializer, value_offsetY_value_1)
            }
        }
    }
    public static read(buffer: DeserializerBase): GaugeShadowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const radius_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let radius_buf : number | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (radius_buf_runtimeType))
        {
            const radius_buf__selector : int32 = valueDeserializer.readInt8()
            let radius_buf_ : number | Resource | undefined
            if (radius_buf__selector == 0) {
                radius_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (radius_buf__selector == 1) {
                radius_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for radius_buf_ has to be chosen through deserialisation.")
            }
            radius_buf = (radius_buf_ as number | Resource)
        }
        const radius_result : number | Resource | undefined = radius_buf
        const offsetX_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let offsetX_buf : number | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (offsetX_buf_runtimeType))
        {
            const offsetX_buf__selector : int32 = valueDeserializer.readInt8()
            let offsetX_buf_ : number | Resource | undefined
            if (offsetX_buf__selector == 0) {
                offsetX_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (offsetX_buf__selector == 1) {
                offsetX_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for offsetX_buf_ has to be chosen through deserialisation.")
            }
            offsetX_buf = (offsetX_buf_ as number | Resource)
        }
        const offsetX_result : number | Resource | undefined = offsetX_buf
        const offsetY_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let offsetY_buf : number | Resource | undefined
        if ((RuntimeType.UNDEFINED) != (offsetY_buf_runtimeType))
        {
            const offsetY_buf__selector : int32 = valueDeserializer.readInt8()
            let offsetY_buf_ : number | Resource | undefined
            if (offsetY_buf__selector == 0) {
                offsetY_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (offsetY_buf__selector == 1) {
                offsetY_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for offsetY_buf_ has to be chosen through deserialisation.")
            }
            offsetY_buf = (offsetY_buf_ as number | Resource)
        }
        const offsetY_result : number | Resource | undefined = offsetY_buf
        let value : GaugeShadowOptions = ({radius: radius_result, offsetX: offsetX_result, offsetY: offsetY_result} as GaugeShadowOptions)
        return value
    }
}
export class GaugeIndicatorOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeIndicatorOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_icon  = value.icon
        let value_icon_type : int32 = RuntimeType.UNDEFINED
        value_icon_type = runtimeType(value_icon)
        valueSerializer.writeInt8(value_icon_type)
        if ((RuntimeType.UNDEFINED) != (value_icon_type)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8(0)
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8(1)
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_space  = value.space
        let value_space_type : int32 = RuntimeType.UNDEFINED
        value_space_type = runtimeType(value_space)
        valueSerializer.writeInt8(value_space_type)
        if ((RuntimeType.UNDEFINED) != (value_space_type)) {
            const value_space_value  = value_space!
            let value_space_value_type : int32 = RuntimeType.UNDEFINED
            value_space_value_type = runtimeType(value_space_value)
            if (RuntimeType.STRING == value_space_value_type) {
                valueSerializer.writeInt8(0)
                const value_space_value_0  = value_space_value as string
                valueSerializer.writeString(value_space_value_0)
            }
            else if (RuntimeType.NUMBER == value_space_value_type) {
                valueSerializer.writeInt8(1)
                const value_space_value_1  = value_space_value as number
                valueSerializer.writeNumber(value_space_value_1)
            }
            else if (RuntimeType.OBJECT == value_space_value_type) {
                valueSerializer.writeInt8(2)
                const value_space_value_2  = value_space_value as Resource
                Resource_serializer.write(valueSerializer, value_space_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): GaugeIndicatorOptions {
        let valueDeserializer : DeserializerBase = buffer
        const icon_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let icon_buf : ResourceStr | undefined
        if ((RuntimeType.UNDEFINED) != (icon_buf_runtimeType))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == 0) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == 1) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const space_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let space_buf : Dimension | undefined
        if ((RuntimeType.UNDEFINED) != (space_buf_runtimeType))
        {
            const space_buf__selector : int32 = valueDeserializer.readInt8()
            let space_buf_ : string | number | Resource | undefined
            if (space_buf__selector == 0) {
                space_buf_ = (valueDeserializer.readString() as string)
            }
            else if (space_buf__selector == 1) {
                space_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (space_buf__selector == 2) {
                space_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for space_buf_ has to be chosen through deserialisation.")
            }
            space_buf = (space_buf_ as string | number | Resource)
        }
        const space_result : Dimension | undefined = space_buf
        let value : GaugeIndicatorOptions = ({icon: icon_result, space: space_result} as GaugeIndicatorOptions)
        return value
    }
}
