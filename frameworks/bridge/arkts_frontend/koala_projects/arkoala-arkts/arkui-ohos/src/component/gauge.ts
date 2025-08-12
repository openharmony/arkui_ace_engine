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
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, MultiShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length, ResourceStr, Dimension } from "./units"
import { LinearGradient } from "./dataPanel"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Color } from "./enums"
import { Resource } from "global.resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkGaugePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkGaugePeer {
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
    valueAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_value(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    startAngleAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_startAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    endAngleAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_endAngle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorsAttribute(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if ((TypeChecker.isColor(value_value)) || (RuntimeType.NUMBER == value_value_type) || (RuntimeType.STRING == value_value_type) || (RuntimeType.OBJECT == value_value_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceColor
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (TypeChecker.isColor(value_value_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0_0))
                }
                else if (RuntimeType.NUMBER == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as number
                    thisSerializer.writeNumber(value_value_0_1)
                }
                else if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_0_2  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_2)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_0_3  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as LinearGradient
                thisSerializer.writeLinearGradient(value_value_1)
            }
            else if (((RuntimeType.OBJECT) == (value_value_type)) && (TypeChecker.isArray_Tuple_Union_ResourceColor_LinearGradient_Number(value_value))) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Array<[ ResourceColor | LinearGradient, number ]>
                thisSerializer.writeInt32(value_value_2.length as int32)
                for (let i = 0; i < value_value_2.length; i++) {
                    const value_value_2_element : [ ResourceColor | LinearGradient, number ] = value_value_2[i]
                    const value_value_2_element_0  = value_value_2_element[0]
                    let value_value_2_element_0_type : int32 = RuntimeType.UNDEFINED
                    value_value_2_element_0_type = runtimeType(value_value_2_element_0)
                    if ((TypeChecker.isColor(value_value_2_element_0)) || (RuntimeType.NUMBER == value_value_2_element_0_type) || (RuntimeType.STRING == value_value_2_element_0_type) || (RuntimeType.OBJECT == value_value_2_element_0_type)) {
                        thisSerializer.writeInt8(0 as int32)
                        const value_value_2_element_0_0  = value_value_2_element_0 as ResourceColor
                        let value_value_2_element_0_0_type : int32 = RuntimeType.UNDEFINED
                        value_value_2_element_0_0_type = runtimeType(value_value_2_element_0_0)
                        if (TypeChecker.isColor(value_value_2_element_0_0)) {
                            thisSerializer.writeInt8(0 as int32)
                            const value_value_2_element_0_0_0  = value_value_2_element_0_0 as Color
                            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_2_element_0_0_0))
                        }
                        else if (RuntimeType.NUMBER == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8(1 as int32)
                            const value_value_2_element_0_0_1  = value_value_2_element_0_0 as number
                            thisSerializer.writeNumber(value_value_2_element_0_0_1)
                        }
                        else if (RuntimeType.STRING == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8(2 as int32)
                            const value_value_2_element_0_0_2  = value_value_2_element_0_0 as string
                            thisSerializer.writeString(value_value_2_element_0_0_2)
                        }
                        else if (RuntimeType.OBJECT == value_value_2_element_0_0_type) {
                            thisSerializer.writeInt8(3 as int32)
                            const value_value_2_element_0_0_3  = value_value_2_element_0_0 as Resource
                            thisSerializer.writeResource(value_value_2_element_0_0_3)
                        }
                    }
                    else if (TypeChecker.isLinearGradient(value_value_2_element_0)) {
                        thisSerializer.writeInt8(1 as int32)
                        const value_value_2_element_0_1  = value_value_2_element_0 as LinearGradient
                        thisSerializer.writeLinearGradient(value_value_2_element_0_1)
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
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    descriptionAttribute(value: CustomBuilder | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value))
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_description(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackShadowAttribute(value: GaugeShadowOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeGaugeShadowOptions(value_value)
        }
        ArkUIGeneratedNativeModule._GaugeAttribute_trackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    indicatorAttribute(value: GaugeIndicatorOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeGaugeIndicatorOptions(value_value)
        }
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
    contentModifierAttribute(value: ContentModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
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
export type GaugeInterface = (options: GaugeOptions) => GaugeAttribute;
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
    value(value: number | undefined): this
    startAngle(value: number | undefined): this
    endAngle(value: number | undefined): this
    colors(value: ResourceColor | LinearGradient | Array<[ ResourceColor | LinearGradient, number ]> | undefined): this
    strokeWidth(value: Length | undefined): this
    description(value: CustomBuilder | undefined): this
    trackShadow(value: GaugeShadowOptions | undefined): this
    indicator(value: GaugeIndicatorOptions | undefined): this
    privacySensitive(value: boolean | undefined): this
    contentModifier(value: ContentModifier | undefined): this
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
    contentModifier_value?: ContentModifier | undefined
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
    public contentModifier(value: ContentModifier | undefined): this {
        return this
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
    public contentModifier(value: ContentModifier | undefined): this {
        if (this.checkPriority("contentModifier")) {
            const value_casted = value as (ContentModifier | undefined)
            this.getPeer()?.contentModifierAttribute(value_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Gauge(
    /** @memo */
    style: ((attributes: GaugeAttribute) => void) | undefined,
    options: GaugeOptions,
    /** @memo */
    content_?: (() => void) | undefined,
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
