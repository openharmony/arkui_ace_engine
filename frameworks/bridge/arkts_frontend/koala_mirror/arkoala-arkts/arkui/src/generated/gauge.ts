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

import { int32, int64, float32 } from "@koalaui/common"
import { nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Serializer } from "./peers/Serializer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, MultiShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor, Length, ResourceStr, Dimension } from "./units"
import { LinearGradient } from "./data_panel"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Color } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeGaugeOptions(options)
        ArkUIGeneratedNativeModule._GaugeInterface_setGaugeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    valueAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_value(this.peer.ptr, value)
    }
    startAngleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_startAngle(this.peer.ptr, value)
    }
    endAngleAttribute(value: number): void {
        ArkUIGeneratedNativeModule._GaugeAttribute_endAngle(this.peer.ptr, value)
    }
    colorsAttribute(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((TypeChecker.isColor(value)) || (RuntimeType.NUMBER == value_type) || (RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ResourceColor
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (TypeChecker.isColor(value_0)) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0_0))
            }
            else if (RuntimeType.NUMBER == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as number
                thisSerializer.writeNumber(value_0_1)
            }
            else if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_0_2  = value_0 as string
                thisSerializer.writeString(value_0_2)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_0_3  = value_0 as Resource
                thisSerializer.writeResource(value_0_3)
            }
        }
        else if (TypeChecker.isLinearGradient(value)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as LinearGradient
            thisSerializer.writeLinearGradient(value_1)
        }
        else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value))) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Array<[ ResourceColor | LinearGradient, number ]>
            thisSerializer.writeInt32(value_2.length as int32)
            for (let i = 0; i < value_2.length; i++) {
                const value_2_element : [ ResourceColor | LinearGradient, number ] = value_2[i]
                const value_2_element_0  = value_2_element[0]
                let value_2_element_0_type : int32 = RuntimeType.UNDEFINED
                value_2_element_0_type = runtimeType(value_2_element_0)
                if ((TypeChecker.isColor(value_2_element_0)) || (RuntimeType.NUMBER == value_2_element_0_type) || (RuntimeType.STRING == value_2_element_0_type) || (RuntimeType.OBJECT == value_2_element_0_type)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_2_element_0_0  = value_2_element_0 as ResourceColor
                    let value_2_element_0_0_type : int32 = RuntimeType.UNDEFINED
                    value_2_element_0_0_type = runtimeType(value_2_element_0_0)
                    if (TypeChecker.isColor(value_2_element_0_0)) {
                        thisSerializer.writeInt8(0 as int32)
                        const value_2_element_0_0_0  = value_2_element_0_0 as Color
                        thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_2_element_0_0_0))
                    }
                    else if (RuntimeType.NUMBER == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(1 as int32)
                        const value_2_element_0_0_1  = value_2_element_0_0 as number
                        thisSerializer.writeNumber(value_2_element_0_0_1)
                    }
                    else if (RuntimeType.STRING == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(2 as int32)
                        const value_2_element_0_0_2  = value_2_element_0_0 as string
                        thisSerializer.writeString(value_2_element_0_0_2)
                    }
                    else if (RuntimeType.OBJECT == value_2_element_0_0_type) {
                        thisSerializer.writeInt8(3 as int32)
                        const value_2_element_0_0_3  = value_2_element_0_0 as Resource
                        thisSerializer.writeResource(value_2_element_0_0_3)
                    }
                }
                else if (TypeChecker.isLinearGradient(value_2_element_0)) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_2_element_0_1  = value_2_element_0 as LinearGradient
                    thisSerializer.writeLinearGradient(value_2_element_0_1)
                }
                const value_2_element_1  = value_2_element[1]
                thisSerializer.writeNumber(value_2_element_1)
            }
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_colors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    descriptionAttribute(value: CustomBuilder): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        ArkUIGeneratedNativeModule._GaugeAttribute_description(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackShadowAttribute(value: GaugeShadowOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeGaugeShadowOptions(value)
        ArkUIGeneratedNativeModule._GaugeAttribute_trackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorAttribute(value: GaugeIndicatorOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeGaugeIndicatorOptions(value)
        ArkUIGeneratedNativeModule._GaugeAttribute_indicator(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    privacySensitiveAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_privacySensitive(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
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
export interface GaugeConfiguration extends CommonConfiguration {
    value: number;
    min: number;
    max: number;
}
export type Tuple_Union_ResourceColor_LinearGradient_Number = [
    ResourceColor | LinearGradient,
    number
]
export interface GaugeAttribute extends CommonMethod {
    value(value: number): this
    startAngle(value: number): this
    endAngle(value: number): this
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>): this
    strokeWidth(value: Length): this
    description(value: CustomBuilder): this
    trackShadow(value: GaugeShadowOptions): this
    indicator(value: GaugeIndicatorOptions): this
    privacySensitive(value: boolean | undefined): this
    contentModifier(value: ContentModifier): this
    attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIGaugeAttribute extends UICommonMethod {
    /** @memo */
    value(value: number): this
    /** @memo */
    startAngle(value: number): this
    /** @memo */
    endAngle(value: number): this
    /** @memo */
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>): this
    /** @memo */
    strokeWidth(value: Length): this
    /** @memo */
    description(value: CustomBuilder): this
    /** @memo */
    trackShadow(value: GaugeShadowOptions): this
    /** @memo */
    indicator(value: GaugeIndicatorOptions): this
    /** @memo */
    privacySensitive(value: boolean | undefined): this
    /** @memo */
    contentModifier(value: ContentModifier): this
    /** @memo */
    attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkGaugeStyle extends ArkCommonMethodStyle implements GaugeAttribute {
    value_value?: number
    startAngle_value?: number
    endAngle_value?: number
    colors_value?: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>
    strokeWidth_value?: Length
    description_value?: CustomBuilder
    trackShadow_value?: GaugeShadowOptions
    indicator_value?: GaugeIndicatorOptions
    privacySensitive_value?: boolean | undefined
    contentModifier_value?: ContentModifier
    public value(value: number): this {
        return this
    }
    public startAngle(value: number): this {
        return this
    }
    public endAngle(value: number): this {
        return this
    }
    public colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>): this {
        return this
    }
    public strokeWidth(value: Length): this {
        return this
    }
    public description(value: CustomBuilder): this {
        return this
    }
    public trackShadow(value: GaugeShadowOptions): this {
        return this
    }
    public indicator(value: GaugeIndicatorOptions): this {
        return this
    }
    public privacySensitive(value: boolean | undefined): this {
        return this
    }
    public contentModifier(value: ContentModifier): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkGaugeComponent extends ArkCommonMethodComponent implements UIGaugeAttribute {
    getPeer(): ArkGaugePeer {
        return (this.peer as ArkGaugePeer)
    }
    /** @memo */
    public setGaugeOptions(options: GaugeOptions): this {
        if (this.checkPriority("setGaugeOptions")) {
            const options_casted = options as (GaugeOptions)
            this.getPeer()?.setGaugeOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public value(value: number): this {
        if (this.checkPriority("value")) {
            const value_casted = value as (number)
            this.getPeer()?.valueAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public startAngle(value: number): this {
        if (this.checkPriority("startAngle")) {
            const value_casted = value as (number)
            this.getPeer()?.startAngleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public endAngle(value: number): this {
        if (this.checkPriority("endAngle")) {
            const value_casted = value as (number)
            this.getPeer()?.endAngleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>): this {
        if (this.checkPriority("colors")) {
            const value_casted = value as (ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]>)
            this.getPeer()?.colorsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeWidth(value: Length): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (Length)
            this.getPeer()?.strokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public description(value: CustomBuilder): this {
        if (this.checkPriority("description")) {
            const value_casted = value as (CustomBuilder)
            this.getPeer()?.descriptionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public trackShadow(value: GaugeShadowOptions): this {
        if (this.checkPriority("trackShadow")) {
            const value_casted = value as (GaugeShadowOptions)
            this.getPeer()?.trackShadowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public indicator(value: GaugeIndicatorOptions): this {
        if (this.checkPriority("indicator")) {
            const value_casted = value as (GaugeIndicatorOptions)
            this.getPeer()?.indicatorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public privacySensitive(value: boolean | undefined): this {
        if (this.checkPriority("privacySensitive")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.privacySensitiveAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public contentModifier(value: ContentModifier): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<GaugeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkGauge(
    /** @memo */
    style: ((attributes: UIGaugeAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options: GaugeOptions,
): void {
    const receiver = remember(() => {
        return new ArkGaugeComponent()
    })
    NodeAttach<ArkGaugePeer>((): ArkGaugePeer => ArkGaugePeer.create(receiver), (_: ArkGaugePeer) => {
        receiver.setGaugeOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
