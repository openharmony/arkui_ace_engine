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
import { Resource_serializer, Resource } from "./../generated/resource"
import { LinearGradient_serializer, LinearGradient } from "./dataPanel"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor, Length, ResourceStr, Dimension } from "./units"
import { Color } from "./enums"
import { CustomBuilder } from "./builder"
import { ContentModifier, AttributeModifier, hookGaugeContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
    setValueAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setValue(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStartAngleAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setStartAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEndAngleAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setEndAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorsAttribute(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8((3).toChar())
                    const value_value_0_3  = value_value_0 as Resource
                    Resource_serializer.write(thisSerializer, value_value_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as LinearGradient
                LinearGradient_serializer.write(thisSerializer, value_value_1)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value_value))) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Array<[ ResourceColor | LinearGradient, number ]>
                thisSerializer.writeInt32((value_value_2.length).toInt())
                for (let value_value_2_counter_i = 0; value_value_2_counter_i < value_value_2.length; value_value_2_counter_i++) {
                    const value_value_2_element : [ ResourceColor | LinearGradient, number ] = value_value_2[value_value_2_counter_i]
                    const value_value_2_element_0  = value_value_2_element[0]
                    let value_value_2_element_0_type : int32 = RuntimeType.UNDEFINED
                    value_value_2_element_0_type = runtimeType(value_value_2_element_0)
                    if ((TypeChecker.isColor(value_value_2_element_0)) || (RuntimeType.NUMBER == value_value_2_element_0_type) || (RuntimeType.STRING == value_value_2_element_0_type) || (RuntimeType.OBJECT == value_value_2_element_0_type)) {
                        thisSerializer.writeInt8((0).toChar())
                        const value_value_2_element_0_0  = value_value_2_element_0 as ResourceColor
                        let value_value_2_element_0_0_type : int32 = RuntimeType.UNDEFINED
                        value_value_2_element_0_0_type = runtimeType(value_value_2_element_0_0)
                        if (TypeChecker.isColor(value_value_2_element_0_0)) {
                            thisSerializer.writeInt8((0).toChar())
                            const value_value_2_element_0_0_0  = value_value_2_element_0_0 as Color
                            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_2_element_0_0_0))
                        }
                        else if (RuntimeType.NUMBER == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8((1).toChar())
                            const value_value_2_element_0_0_1  = value_value_2_element_0_0 as number
                            thisSerializer.writeNumber(value_value_2_element_0_0_1)
                        }
                        else if (RuntimeType.STRING == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8((2).toChar())
                            const value_value_2_element_0_0_2  = value_value_2_element_0_0 as string
                            thisSerializer.writeString(value_value_2_element_0_0_2)
                        }
                        else if (RuntimeType.OBJECT == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8((3).toChar())
                            const value_value_2_element_0_0_3  = value_value_2_element_0_0 as Resource
                            Resource_serializer.write(thisSerializer, value_value_2_element_0_0_3)
                        }
                    }
                    else if (TypeChecker.isLinearGradient(value_value_2_element_0)) {
                        thisSerializer.writeInt8((1).toChar())
                        const value_value_2_element_0_1  = value_value_2_element_0 as LinearGradient
                        LinearGradient_serializer.write(thisSerializer, value_value_2_element_0_1)
                    }
                    const value_value_2_element_1  = value_value_2_element[1]
                    thisSerializer.writeNumber(value_value_2_element_1)
                }
            }
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setColors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._GaugeAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDescriptionAttribute(value: CustomBuilder | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value))
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setDescription(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackShadowAttribute(value: GaugeShadowOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            GaugeShadowOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setTrackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorAttribute(value: GaugeIndicatorOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            GaugeIndicatorOptions_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrivacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentModifierAttribute(value: ContentModifier<GaugeConfiguration> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteObject(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setContentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    value(value: number | undefined): this {
        throw new Error("Unimplemented method value")
    }
    startAngle(value: number | undefined): this {
        throw new Error("Unimplemented method startAngle")
    }
    endAngle(value: number | undefined): this {
        throw new Error("Unimplemented method endAngle")
    }
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): this {
        throw new Error("Unimplemented method colors")
    }
    strokeWidth(value: Length | undefined): this {
        throw new Error("Unimplemented method strokeWidth")
    }
    description(value: CustomBuilder | undefined): this {
        throw new Error("Unimplemented method description")
    }
    trackShadow(value: GaugeShadowOptions | undefined): this {
        throw new Error("Unimplemented method trackShadow")
    }
    indicator(value: GaugeIndicatorOptions | undefined): this {
        throw new Error("Unimplemented method indicator")
    }
    privacySensitive(value: boolean | undefined): this {
        throw new Error("Unimplemented method privacySensitive")
    }
    contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
        throw new Error("Unimplemented method contentModifier")
    }
    attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
            this.getPeer()?.setValueAttribute(value_casted)
            return this
        }
        return this
    }
    public startAngle(value: number | undefined): this {
        if (this.checkPriority("startAngle")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setStartAngleAttribute(value_casted)
            return this
        }
        return this
    }
    public endAngle(value: number | undefined): this {
        if (this.checkPriority("endAngle")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setEndAngleAttribute(value_casted)
            return this
        }
        return this
    }
    public colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): this {
        if (this.checkPriority("colors")) {
            const value_casted = value as (ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined)
            this.getPeer()?.setColorsAttribute(value_casted)
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
    public description(value: CustomBuilder | undefined): this {
        if (this.checkPriority("description")) {
            const value_casted = value as (CustomBuilder | undefined)
            this.getPeer()?.setDescriptionAttribute(value_casted)
            return this
        }
        return this
    }
    public trackShadow(value: GaugeShadowOptions | undefined): this {
        if (this.checkPriority("trackShadow")) {
            const value_casted = value as (GaugeShadowOptions | undefined)
            this.getPeer()?.setTrackShadowAttribute(value_casted)
            return this
        }
        return this
    }
    public indicator(value: GaugeIndicatorOptions | undefined): this {
        if (this.checkPriority("indicator")) {
            const value_casted = value as (GaugeIndicatorOptions | undefined)
            this.getPeer()?.setIndicatorAttribute(value_casted)
            return this
        }
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setPrivacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    public contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier<GaugeConfiguration> | undefined)
            this.getPeer()?.setContentModifierAttribute(value_casted)
            return this
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Gauge")
// export function Gauge(
//     options: GaugeOptions,
//     @memo
//     content_?: () => void,
// ): GaugeAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Gauge(
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

export class ArkGaugeSet extends ArkCommonMethodSet implements GaugeAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _value_flag?: boolean
    _value0_value?: number | undefined
    _startAngle_flag?: boolean
    _startAngle0_value?: number | undefined
    _endAngle_flag?: boolean
    _endAngle0_value?: number | undefined
    _colors_flag?: boolean
    _colors0_value?: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined
    _strokeWidth_flag?: boolean
    _strokeWidth0_value?: Length | undefined
    _description_flag?: boolean
    _description0_value?: CustomBuilder | undefined
    _trackShadow_flag?: boolean
    _trackShadow0_value?: GaugeShadowOptions | undefined
    _indicator_flag?: boolean
    _indicator0_value?: GaugeIndicatorOptions | undefined
    _privacySensitive_flag?: boolean
    _privacySensitive0_value?: boolean | undefined
    _contentModifier_flag?: boolean
    _contentModifier0_value?: ContentModifier<GaugeConfiguration> | undefined
    applyModifierPatch(component: GaugeAttribute): void {
        if (this._value_flag)
            component.value((this._value0_value as number | undefined))
        if (this._startAngle_flag)
            component.startAngle((this._startAngle0_value as number | undefined))
        if (this._endAngle_flag)
            component.endAngle((this._endAngle0_value as number | undefined))
        if (this._colors_flag)
            component.colors((this._colors0_value as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined))
        if (this._strokeWidth_flag)
            component.strokeWidth((this._strokeWidth0_value as Length | undefined))
        if (this._description_flag)
            component.description((this._description0_value as CustomBuilder | undefined))
        if (this._trackShadow_flag)
            component.trackShadow((this._trackShadow0_value as GaugeShadowOptions | undefined))
        if (this._indicator_flag)
            component.indicator((this._indicator0_value as GaugeIndicatorOptions | undefined))
        if (this._privacySensitive_flag)
            component.privacySensitive((this._privacySensitive0_value as boolean | undefined))
        if (this._contentModifier_flag)
            component.contentModifier((this._contentModifier0_value as ContentModifier<GaugeConfiguration> | undefined))
    }
    public value(value: number | undefined): this {
        this._value_flag = true
        this._value0_value = value
        return this
    }
    public startAngle(value: number | undefined): this {
        this._startAngle_flag = true
        this._startAngle0_value = value
        return this
    }
    public endAngle(value: number | undefined): this {
        this._endAngle_flag = true
        this._endAngle0_value = value
        return this
    }
    public colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): this {
        this._colors_flag = true
        this._colors0_value = value
        return this
    }
    public strokeWidth(value: Length | undefined): this {
        this._strokeWidth_flag = true
        this._strokeWidth0_value = value
        return this
    }
    public description(value: CustomBuilder | undefined): this {
        this._description_flag = true
        this._description0_value = value
        return this
    }
    public trackShadow(value: GaugeShadowOptions | undefined): this {
        this._trackShadow_flag = true
        this._trackShadow0_value = value
        return this
    }
    public indicator(value: GaugeIndicatorOptions | undefined): this {
        this._indicator_flag = true
        this._indicator0_value = value
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        this._privacySensitive_flag = true
        this._privacySensitive0_value = value
        return this
    }
    public contentModifier(value: ContentModifier<GaugeConfiguration> | undefined): this {
        this._contentModifier_flag = true
        this._contentModifier0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
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
        valueSerializer.writeInt8((value_min_type).toChar())
        if ((value_min_type) != (RuntimeType.UNDEFINED)) {
            const value_min_value  = value_min!
            valueSerializer.writeNumber(value_min_value)
        }
        const value_max  = value.max
        let value_max_type : int32 = RuntimeType.UNDEFINED
        value_max_type = runtimeType(value_max)
        valueSerializer.writeInt8((value_max_type).toChar())
        if ((value_max_type) != (RuntimeType.UNDEFINED)) {
            const value_max_value  = value_max!
            valueSerializer.writeNumber(value_max_value)
        }
    }
    public static read(buffer: DeserializerBase): GaugeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const value_result : number = (valueDeserializer.readNumber() as number)
        const min_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let min_buf : number | undefined
        if ((min_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            min_buf = (valueDeserializer.readNumber() as number)
        }
        const min_result : number | undefined = min_buf
        const max_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let max_buf : number | undefined
        if ((max_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
    }
    public static read(buffer: DeserializerBase): GaugeShadowOptions {
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
        valueSerializer.writeInt8((value_icon_type).toChar())
        if ((value_icon_type) != (RuntimeType.UNDEFINED)) {
            const value_icon_value  = value_icon!
            let value_icon_value_type : int32 = RuntimeType.UNDEFINED
            value_icon_value_type = runtimeType(value_icon_value)
            if (RuntimeType.STRING == value_icon_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_icon_value_0  = value_icon_value as string
                valueSerializer.writeString(value_icon_value_0)
            }
            else if (RuntimeType.OBJECT == value_icon_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_icon_value_1  = value_icon_value as Resource
                Resource_serializer.write(valueSerializer, value_icon_value_1)
            }
        }
        const value_space  = value.space
        let value_space_type : int32 = RuntimeType.UNDEFINED
        value_space_type = runtimeType(value_space)
        valueSerializer.writeInt8((value_space_type).toChar())
        if ((value_space_type) != (RuntimeType.UNDEFINED)) {
            const value_space_value  = value_space!
            let value_space_value_type : int32 = RuntimeType.UNDEFINED
            value_space_value_type = runtimeType(value_space_value)
            if (RuntimeType.STRING == value_space_value_type) {
                valueSerializer.writeInt8((0).toChar())
                const value_space_value_0  = value_space_value as string
                valueSerializer.writeString(value_space_value_0)
            }
            else if (RuntimeType.NUMBER == value_space_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_space_value_1  = value_space_value as number
                valueSerializer.writeNumber(value_space_value_1)
            }
            else if (RuntimeType.OBJECT == value_space_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_space_value_2  = value_space_value as Resource
                Resource_serializer.write(valueSerializer, value_space_value_2)
            }
        }
    }
    public static read(buffer: DeserializerBase): GaugeIndicatorOptions {
        let valueDeserializer : DeserializerBase = buffer
        const icon_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let icon_buf : ResourceStr | undefined
        if ((icon_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const icon_buf__selector : int32 = valueDeserializer.readInt8()
            let icon_buf_ : string | Resource | undefined
            if (icon_buf__selector == (0).toChar()) {
                icon_buf_ = (valueDeserializer.readString() as string)
            }
            else if (icon_buf__selector == (1).toChar()) {
                icon_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for icon_buf_ has to be chosen through deserialisation.")
            }
            icon_buf = (icon_buf_ as string | Resource)
        }
        const icon_result : ResourceStr | undefined = icon_buf
        const space_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let space_buf : Dimension | undefined
        if ((space_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const space_buf__selector : int32 = valueDeserializer.readInt8()
            let space_buf_ : string | number | Resource | undefined
            if (space_buf__selector == (0).toChar()) {
                space_buf_ = (valueDeserializer.readString() as string)
            }
            else if (space_buf__selector == (1).toChar()) {
                space_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (space_buf__selector == (2).toChar()) {
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
