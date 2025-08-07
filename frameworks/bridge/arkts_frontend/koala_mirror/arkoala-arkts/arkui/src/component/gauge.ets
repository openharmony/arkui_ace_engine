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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { LinearGradient_serializer, LinearGradient } from "./dataPanel"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, CommonConfiguration, ArkCommonMethodComponent, ArkCommonMethodStyle, CommonMethodModifier } from "./common"
import { ResourceColor, Length, ResourceStr, Dimension } from "./units"
import { Color } from "./enums"
import { CustomBuilder } from "./builder"
import { ContentModifier, AttributeModifier, hookGaugeContentModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeUpdaterFlag } from "./../generated/AttributeUpdater"
export class ArkGaugePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkGaugePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Gauge_construct(peerId, flags)
        const _peer  = new ArkGaugePeer(_peerPtr, peerId, 'Gauge', flags)
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
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setValue(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStartAngleAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setStartAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEndAngleAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeNumber(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setEndAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorsAttribute(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            if (valueTmpValue instanceof ResourceColor) {
                thisSerializer.writeInt8((0).toChar())
                const valueTmpValueForIdx0  = valueTmpValue as ResourceColor
                if (valueTmpValueForIdx0 instanceof Color) {
                    thisSerializer.writeInt8((0).toChar())
                    const valueTmpValueForIdx0ForIdx0  = valueTmpValueForIdx0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx0ForIdx0))
                } else if (valueTmpValueForIdx0 instanceof number) {
                    thisSerializer.writeInt8((1).toChar())
                    const valueTmpValueForIdx0ForIdx1  = valueTmpValueForIdx0 as number
                    thisSerializer.writeNumber(valueTmpValueForIdx0ForIdx1)
                } else if (valueTmpValueForIdx0 instanceof string) {
                    thisSerializer.writeInt8((2).toChar())
                    const valueTmpValueForIdx0ForIdx2  = valueTmpValueForIdx0 as string
                    thisSerializer.writeString(valueTmpValueForIdx0ForIdx2)
                } else if (valueTmpValueForIdx0 instanceof Resource) {
                    thisSerializer.writeInt8((3).toChar())
                    const valueTmpValueForIdx0ForIdx3  = valueTmpValueForIdx0 as Resource
                    Resource_serializer.write(thisSerializer, valueTmpValueForIdx0ForIdx3)
                }
            } else if (valueTmpValue instanceof LinearGradient) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as LinearGradient
                LinearGradient_serializer.write(thisSerializer, valueTmpValueForIdx1)
            } else if (TypeChecker.isArray_Tuple_Union_ResourceColor_LinearGradient_Number(valueTmpValue)) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Array<[ ResourceColor | LinearGradient, number ]>
                thisSerializer.writeInt32((valueTmpValueForIdx2.length).toInt())
                for (let valueTmpValueForIdx2CounterI = 0; valueTmpValueForIdx2CounterI < valueTmpValueForIdx2.length; valueTmpValueForIdx2CounterI++) {
                    const valueTmpValueForIdx2TmpElement : [ ResourceColor | LinearGradient, number ] = valueTmpValueForIdx2[valueTmpValueForIdx2CounterI]
                    const valueTmpValueForIdx2TmpElement_0  = valueTmpValueForIdx2TmpElement[0]
                    if (valueTmpValueForIdx2TmpElement_0 instanceof ResourceColor) {
                        thisSerializer.writeInt8((0).toChar())
                        const valueTmpValueForIdx2TmpElement_0ForIdx0  = valueTmpValueForIdx2TmpElement_0 as ResourceColor
                        if (valueTmpValueForIdx2TmpElement_0ForIdx0 instanceof Color) {
                            thisSerializer.writeInt8((0).toChar())
                            const valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx0  = valueTmpValueForIdx2TmpElement_0ForIdx0 as Color
                            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx0))
                        } else if (valueTmpValueForIdx2TmpElement_0ForIdx0 instanceof number) {
                            thisSerializer.writeInt8((1).toChar())
                            const valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx1  = valueTmpValueForIdx2TmpElement_0ForIdx0 as number
                            thisSerializer.writeNumber(valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx1)
                        } else if (valueTmpValueForIdx2TmpElement_0ForIdx0 instanceof string) {
                            thisSerializer.writeInt8((2).toChar())
                            const valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx2  = valueTmpValueForIdx2TmpElement_0ForIdx0 as string
                            thisSerializer.writeString(valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx2)
                        } else if (valueTmpValueForIdx2TmpElement_0ForIdx0 instanceof Resource) {
                            thisSerializer.writeInt8((3).toChar())
                            const valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx3  = valueTmpValueForIdx2TmpElement_0ForIdx0 as Resource
                            Resource_serializer.write(thisSerializer, valueTmpValueForIdx2TmpElement_0ForIdx0ForIdx3)
                        }
                    } else if (valueTmpValueForIdx2TmpElement_0 instanceof LinearGradient) {
                        thisSerializer.writeInt8((1).toChar())
                        const valueTmpValueForIdx2TmpElement_0ForIdx1  = valueTmpValueForIdx2TmpElement_0 as LinearGradient
                        LinearGradient_serializer.write(thisSerializer, valueTmpValueForIdx2TmpElement_0ForIdx1)
                    }
                    const valueTmpValueForIdx2TmpElement_1  = valueTmpValueForIdx2TmpElement[1]
                    thisSerializer.writeNumber(valueTmpValueForIdx2TmpElement_1)
                }
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setColors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
            } else if (valueTmpValue instanceof number) {
                thisSerializer.writeInt8((1).toChar())
                const valueTmpValueForIdx1  = valueTmpValue as number
                thisSerializer.writeNumber(valueTmpValueForIdx1)
            } else if (valueTmpValue instanceof Resource) {
                thisSerializer.writeInt8((2).toChar())
                const valueTmpValueForIdx2  = valueTmpValue as Resource
                Resource_serializer.write(thisSerializer, valueTmpValueForIdx2)
            }
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDescriptionAttribute(value: CustomBuilder | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(valueTmpValue))
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setDescription(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTrackShadowAttribute(value: GaugeShadowOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            GaugeShadowOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setTrackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setIndicatorAttribute(value: GaugeIndicatorOptions | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            GaugeIndicatorOptions_serializer.write(thisSerializer, valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setIndicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setPrivacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue  = value!
            thisSerializer.writeBoolean(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_setPrivacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
            hookGaugeContentModifier(this, value)
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

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
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class GaugeModifier extends CommonMethodModifier implements GaugeAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _value_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _value_0_0value?: number | undefined
    _startAngle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _startAngle_0_0value?: number | undefined
    _endAngle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _endAngle_0_0value?: number | undefined
    _colors_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _colors_0_0value?: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined
    _strokeWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _strokeWidth_0_0value?: Length | undefined
    _description_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _description_0_0value?: CustomBuilder | undefined
    _trackShadow_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _trackShadow_0_0value?: GaugeShadowOptions | undefined
    _indicator_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _indicator_0_0value?: GaugeIndicatorOptions | undefined
    _privacySensitive_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _privacySensitive_0_0value?: boolean | undefined
    applyModifierPatch(peer: ArkGaugePeer): void {
        super.applyModifierPatch(peer)
        if (this._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setValueAttribute((this._value_0_0value as number | undefined));
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._value_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._value_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setValueAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._startAngle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._startAngle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStartAngleAttribute((this._startAngle_0_0value as number | undefined));
                    this._startAngle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._startAngle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._startAngle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStartAngleAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._endAngle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._endAngle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEndAngleAttribute((this._endAngle_0_0value as number | undefined));
                    this._endAngle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._endAngle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._endAngle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEndAngleAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._colors_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._colors_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setColorsAttribute((this._colors_0_0value as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined));
                    this._colors_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._colors_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._colors_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setColorsAttribute((undefined as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined));
                }
            }
        }
        if (this._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as Length | undefined));
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._strokeWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStrokeWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._description_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._description_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDescriptionAttribute((this._description_0_0value as CustomBuilder | undefined));
                    this._description_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._description_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._description_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDescriptionAttribute((undefined as CustomBuilder | undefined));
                }
            }
        }
        if (this._trackShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._trackShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setTrackShadowAttribute((this._trackShadow_0_0value as GaugeShadowOptions | undefined));
                    this._trackShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._trackShadow_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._trackShadow_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setTrackShadowAttribute((undefined as GaugeShadowOptions | undefined));
                }
            }
        }
        if (this._indicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._indicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIndicatorAttribute((this._indicator_0_0value as GaugeIndicatorOptions | undefined));
                    this._indicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._indicator_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._indicator_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIndicatorAttribute((undefined as GaugeIndicatorOptions | undefined));
                }
            }
        }
        if (this._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPrivacySensitiveAttribute((this._privacySensitive_0_0value as boolean | undefined));
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._privacySensitive_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPrivacySensitiveAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: GaugeModifier): void {
        super.mergeModifier(modifier)
        if (modifier._value_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._value_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.value(modifier._value_0_0value);
                    break;
                }
                default: {
                    this.value((undefined as number | undefined));
                }
            }
        }
        if (modifier._startAngle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._startAngle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.startAngle(modifier._startAngle_0_0value);
                    break;
                }
                default: {
                    this.startAngle((undefined as number | undefined));
                }
            }
        }
        if (modifier._endAngle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._endAngle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.endAngle(modifier._endAngle_0_0value);
                    break;
                }
                default: {
                    this.endAngle((undefined as number | undefined));
                }
            }
        }
        if (modifier._colors_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._colors_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.colors(modifier._colors_0_0value);
                    break;
                }
                default: {
                    this.colors((undefined as ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined));
                }
            }
        }
        if (modifier._strokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._strokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.strokeWidth(modifier._strokeWidth_0_0value);
                    break;
                }
                default: {
                    this.strokeWidth((undefined as Length | undefined));
                }
            }
        }
        if (modifier._description_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._description_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.description(modifier._description_0_0value);
                    break;
                }
                default: {
                    this.description((undefined as CustomBuilder | undefined));
                }
            }
        }
        if (modifier._trackShadow_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._trackShadow_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.trackShadow(modifier._trackShadow_0_0value);
                    break;
                }
                default: {
                    this.trackShadow((undefined as GaugeShadowOptions | undefined));
                }
            }
        }
        if (modifier._indicator_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._indicator_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.indicator(modifier._indicator_0_0value);
                    break;
                }
                default: {
                    this.indicator((undefined as GaugeIndicatorOptions | undefined));
                }
            }
        }
        if (modifier._privacySensitive_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._privacySensitive_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.privacySensitive(modifier._privacySensitive_0_0value);
                    break;
                }
                default: {
                    this.privacySensitive((undefined as boolean | undefined));
                }
            }
        }
    }
    value(value: number | undefined): this {
        if (((this._value_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._value_0_0value) !== (value)))
        {
            this._value_0_flag = AttributeUpdaterFlag.UPDATE
            this._value_0_0value = value
        } else
        {
            this._value_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    startAngle(value: number | undefined): this {
        if (((this._startAngle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._startAngle_0_0value) !== (value)))
        {
            this._startAngle_0_flag = AttributeUpdaterFlag.UPDATE
            this._startAngle_0_0value = value
        } else
        {
            this._startAngle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    endAngle(value: number | undefined): this {
        if (((this._endAngle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._endAngle_0_0value) !== (value)))
        {
            this._endAngle_0_flag = AttributeUpdaterFlag.UPDATE
            this._endAngle_0_0value = value
        } else
        {
            this._endAngle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): this {
        if (((this._colors_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._colors_0_flag = AttributeUpdaterFlag.UPDATE
            this._colors_0_0value = value
        } else
        {
            this._colors_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    strokeWidth(value: Length | undefined): this {
        if (((this._strokeWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._strokeWidth_0_0value = value
        } else
        {
            this._strokeWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    description(value: CustomBuilder | undefined): this {
        if (((this._description_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._description_0_flag = AttributeUpdaterFlag.UPDATE
            this._description_0_0value = value
        } else
        {
            this._description_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    trackShadow(value: GaugeShadowOptions | undefined): this {
        if (((this._trackShadow_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._trackShadow_0_flag = AttributeUpdaterFlag.UPDATE
            this._trackShadow_0_0value = value
        } else
        {
            this._trackShadow_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    indicator(value: GaugeIndicatorOptions | undefined): this {
        if (((this._indicator_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._indicator_0_flag = AttributeUpdaterFlag.UPDATE
            this._indicator_0_0value = value
        } else
        {
            this._indicator_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    privacySensitive(value: boolean | undefined): this {
        if (((this._privacySensitive_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._privacySensitive_0_0value) !== (value)))
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.UPDATE
            this._privacySensitive_0_0value = value
        } else
        {
            this._privacySensitive_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class GaugeConfiguration_serializer {
    public static write(buffer: SerializerBase, value: GaugeConfiguration): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForEnabled  = value.enabled
        valueSerializer.writeBoolean(valueHolderForEnabled)
        const valueHolderForContentModifier  = value.contentModifier
        valueSerializer.holdAndWriteObject(valueHolderForContentModifier)
        const valueHolderForValue  = value.value
        valueSerializer.writeNumber(valueHolderForValue)
        const valueHolderForMin  = value.min
        valueSerializer.writeNumber(valueHolderForMin)
        const valueHolderForMax  = value.max
        valueSerializer.writeNumber(valueHolderForMax)
    }
    public static read(buffer: DeserializerBase): GaugeConfiguration {
        let valueDeserializer : DeserializerBase = buffer
        const enabledTmpResult : boolean = valueDeserializer.readBoolean()
        const contentModifierTmpResult : ContentModifier<GaugeConfiguration> = (valueDeserializer.readObject() as ContentModifier<GaugeConfiguration>)
        const valueTmpResult : number = (valueDeserializer.readNumber() as number)
        const minTmpResult : number = (valueDeserializer.readNumber() as number)
        const maxTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : GaugeConfiguration = ({enabled: enabledTmpResult, contentModifier: contentModifierTmpResult, value: valueTmpResult, min: minTmpResult, max: maxTmpResult} as GaugeConfiguration)
        return value
    }
}
export class GaugeOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForValue  = value.value
        valueSerializer.writeNumber(valueHolderForValue)
        const valueHolderForMin  = value.min
        if (valueHolderForMin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinTmpValue  = valueHolderForMin!
            valueSerializer.writeNumber(valueHolderForMinTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMax  = value.max
        if (valueHolderForMax !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMaxTmpValue  = valueHolderForMax!
            valueSerializer.writeNumber(valueHolderForMaxTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GaugeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const valueTmpResult : number = (valueDeserializer.readNumber() as number)
        const minTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minTmpBuf : number | undefined
        if ((minTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            minTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const minTmpResult : number | undefined = minTmpBuf
        const maxTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let maxTmpBuf : number | undefined
        if ((maxTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            maxTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const maxTmpResult : number | undefined = maxTmpBuf
        let value : GaugeOptions = ({value: valueTmpResult, min: minTmpResult, max: maxTmpResult} as GaugeOptions)
        return value
    }
}
export class GaugeShadowOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeShadowOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForRadiusTmpValue  = valueHolderForRadius!
            if (valueHolderForRadiusTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForRadiusTmpValueForIdx0  = valueHolderForRadiusTmpValue as number
                valueSerializer.writeNumber(valueHolderForRadiusTmpValueForIdx0)
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
            if (valueHolderForOffsetXTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForOffsetXTmpValueForIdx0  = valueHolderForOffsetXTmpValue as number
                valueSerializer.writeNumber(valueHolderForOffsetXTmpValueForIdx0)
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
            if (valueHolderForOffsetYTmpValue instanceof number) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForOffsetYTmpValueForIdx0  = valueHolderForOffsetYTmpValue as number
                valueSerializer.writeNumber(valueHolderForOffsetYTmpValueForIdx0)
            } else if (valueHolderForOffsetYTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForOffsetYTmpValueForIdx1  = valueHolderForOffsetYTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForOffsetYTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GaugeShadowOptions {
        let valueDeserializer : DeserializerBase = buffer
        const radiusTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let radiusTmpBuf : number | Resource | undefined
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
        let offsetXTmpBuf : number | Resource | undefined
        if ((offsetXTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetXTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let offsetXTmpBuf_ : number | Resource | undefined
            if (offsetXTmpBuf_UnionSelector == (0).toChar()) {
                offsetXTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (offsetXTmpBuf_UnionSelector == (1).toChar()) {
                offsetXTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for offsetXTmpBuf_ has to be chosen through deserialisation.")
            }
            offsetXTmpBuf = (offsetXTmpBuf_ as number | Resource)
        }
        const offsetXTmpResult : number | Resource | undefined = offsetXTmpBuf
        const offsetYTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offsetYTmpBuf : number | Resource | undefined
        if ((offsetYTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const offsetYTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let offsetYTmpBuf_ : number | Resource | undefined
            if (offsetYTmpBuf_UnionSelector == (0).toChar()) {
                offsetYTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (offsetYTmpBuf_UnionSelector == (1).toChar()) {
                offsetYTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for offsetYTmpBuf_ has to be chosen through deserialisation.")
            }
            offsetYTmpBuf = (offsetYTmpBuf_ as number | Resource)
        }
        const offsetYTmpResult : number | Resource | undefined = offsetYTmpBuf
        let value : GaugeShadowOptions = ({radius: radiusTmpResult, offsetX: offsetXTmpResult, offsetY: offsetYTmpResult} as GaugeShadowOptions)
        return value
    }
}
export class GaugeIndicatorOptions_serializer {
    public static write(buffer: SerializerBase, value: GaugeIndicatorOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForIcon  = value.icon
        if (valueHolderForIcon !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIconTmpValue  = valueHolderForIcon!
            if (valueHolderForIconTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForIconTmpValueForIdx0  = valueHolderForIconTmpValue as string
                valueSerializer.writeString(valueHolderForIconTmpValueForIdx0)
            } else if (valueHolderForIconTmpValue instanceof Resource) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForIconTmpValueForIdx1  = valueHolderForIconTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForIconTmpValueForIdx1)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSpace  = value.space
        if (valueHolderForSpace !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSpaceTmpValue  = valueHolderForSpace!
            if (valueHolderForSpaceTmpValue instanceof string) {
                valueSerializer.writeInt8((0).toChar())
                const valueHolderForSpaceTmpValueForIdx0  = valueHolderForSpaceTmpValue as string
                valueSerializer.writeString(valueHolderForSpaceTmpValueForIdx0)
            } else if (valueHolderForSpaceTmpValue instanceof number) {
                valueSerializer.writeInt8((1).toChar())
                const valueHolderForSpaceTmpValueForIdx1  = valueHolderForSpaceTmpValue as number
                valueSerializer.writeNumber(valueHolderForSpaceTmpValueForIdx1)
            } else if (valueHolderForSpaceTmpValue instanceof Resource) {
                valueSerializer.writeInt8((2).toChar())
                const valueHolderForSpaceTmpValueForIdx2  = valueHolderForSpaceTmpValue as Resource
                Resource_serializer.write(valueSerializer, valueHolderForSpaceTmpValueForIdx2)
            }
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): GaugeIndicatorOptions {
        let valueDeserializer : DeserializerBase = buffer
        const iconTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let iconTmpBuf : ResourceStr | undefined
        if ((iconTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const iconTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let iconTmpBuf_ : string | Resource | undefined
            if (iconTmpBuf_UnionSelector == (0).toChar()) {
                iconTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (iconTmpBuf_UnionSelector == (1).toChar()) {
                iconTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for iconTmpBuf_ has to be chosen through deserialisation.")
            }
            iconTmpBuf = (iconTmpBuf_ as string | Resource)
        }
        const iconTmpResult : ResourceStr | undefined = iconTmpBuf
        const spaceTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let spaceTmpBuf : Dimension | undefined
        if ((spaceTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            const spaceTmpBuf_UnionSelector : int32 = valueDeserializer.readInt8()
            let spaceTmpBuf_ : string | number | Resource | undefined
            if (spaceTmpBuf_UnionSelector == (0).toChar()) {
                spaceTmpBuf_ = (valueDeserializer.readString() as string)
            } else if (spaceTmpBuf_UnionSelector == (1).toChar()) {
                spaceTmpBuf_ = (valueDeserializer.readNumber() as number)
            } else if (spaceTmpBuf_UnionSelector == (2).toChar()) {
                spaceTmpBuf_ = Resource_serializer.read(valueDeserializer)
            } else {
                throw new Error("One of the branches for spaceTmpBuf_ has to be chosen through deserialisation.")
            }
            spaceTmpBuf = (spaceTmpBuf_ as string | number | Resource)
        }
        const spaceTmpResult : Dimension | undefined = spaceTmpBuf
        let value : GaugeIndicatorOptions = ({icon: iconTmpResult, space: spaceTmpResult} as GaugeIndicatorOptions)
        return value
    }
}
