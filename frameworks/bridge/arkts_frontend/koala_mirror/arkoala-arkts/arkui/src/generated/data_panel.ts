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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor, Length } from "./units"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Color } from "./enums"
import { Resource } from "./resource"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class LinearGradientInternal {
    public static fromPtr(ptr: KPointer): LinearGradient {
        const obj : LinearGradient = new LinearGradient(undefined)
        obj.peer = new Finalizable(ptr, LinearGradient.getFinalizer())
        return obj
    }
}
export class LinearGradient implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_lineargradient(colorStops: Array<ColorStop>): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(colorStops.length as int32)
        for (let i = 0; i < colorStops.length; i++) {
            const colorStops_element : ColorStop = colorStops[i]
            thisSerializer.writeColorStop(colorStops_element)
        }
        const retval  = ArkUIGeneratedNativeModule._LinearGradient_ctor(thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(colorStops?: Array<ColorStop>) {
        if ((colorStops) !== (undefined))
        {
            const ctorPtr : KPointer = LinearGradient.ctor_lineargradient((colorStops)!)
            this.peer = new Finalizable(ctorPtr, LinearGradient.getFinalizer())
        }
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
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDataPanelOptions(options)
        ArkUIGeneratedNativeModule._DataPanelInterface_setDataPanelOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    closeEffectAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._DataPanelAttribute_closeEffect(this.peer.ptr, value ? 1 : 0)
    }
    valueColorsAttribute(value: Array<ResourceColor | LinearGradient>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ResourceColor | LinearGradient = value[i]
            let value_element_type : int32 = RuntimeType.UNDEFINED
            value_element_type = runtimeType(value_element)
            if ((TypeChecker.isColor(value_element)) || (RuntimeType.NUMBER == value_element_type) || (RuntimeType.STRING == value_element_type) || (RuntimeType.OBJECT == value_element_type)) {
                thisSerializer.writeInt8(0 as int32)
                const value_element_0  = value_element as ResourceColor
                let value_element_0_type : int32 = RuntimeType.UNDEFINED
                value_element_0_type = runtimeType(value_element_0)
                if (TypeChecker.isColor(value_element_0)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_element_0_0  = value_element_0 as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_element_0_0))
                }
                else if (RuntimeType.NUMBER == value_element_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_element_0_1  = value_element_0 as number
                    thisSerializer.writeNumber(value_element_0_1)
                }
                else if (RuntimeType.STRING == value_element_0_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_element_0_2  = value_element_0 as string
                    thisSerializer.writeString(value_element_0_2)
                }
                else if (RuntimeType.OBJECT == value_element_0_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_element_0_3  = value_element_0 as Resource
                    thisSerializer.writeResource(value_element_0_3)
                }
            }
            else if (TypeChecker.isLinearGradient(value_element)) {
                thisSerializer.writeInt8(1 as int32)
                const value_element_1  = value_element as LinearGradient
                thisSerializer.writeLinearGradient(value_element_1)
            }
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_valueColors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackBackgroundColorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_trackBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._DataPanelAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackShadowAttribute(value: DataPanelShadowOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeDataPanelShadowOptions(value)
        ArkUIGeneratedNativeModule._DataPanelAttribute_trackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    contentModifierAttribute(value: ContentModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(value)
        ArkUIGeneratedNativeModule._DataPanelAttribute_contentModifier(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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

export interface DataPanelConfiguration extends CommonConfiguration {
    values: Array<number>;
    maxValue: number;
}
export interface DataPanelAttribute extends CommonMethod {
    closeEffect(value: boolean): this
    valueColors(value: Array<ResourceColor | LinearGradient>): this
    trackBackgroundColor(value: ResourceColor): this
    strokeWidth(value: Length): this
    trackShadow(value: DataPanelShadowOptions): this
    contentModifier(value: ContentModifier): this
    attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIDataPanelAttribute extends UICommonMethod {
    /** @memo */
    closeEffect(value: boolean): this
    /** @memo */
    valueColors(value: Array<ResourceColor | LinearGradient>): this
    /** @memo */
    trackBackgroundColor(value: ResourceColor): this
    /** @memo */
    strokeWidth(value: Length): this
    /** @memo */
    trackShadow(value: DataPanelShadowOptions): this
    /** @memo */
    contentModifier(value: ContentModifier): this
    /** @memo */
    attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkDataPanelStyle extends ArkCommonMethodStyle implements DataPanelAttribute {
    closeEffect_value?: boolean
    valueColors_value?: Array<ResourceColor | LinearGradient>
    trackBackgroundColor_value?: ResourceColor
    strokeWidth_value?: Length
    trackShadow_value?: DataPanelShadowOptions
    contentModifier_value?: ContentModifier
    public closeEffect(value: boolean): this {
        return this
    }
    public valueColors(value: Array<ResourceColor | LinearGradient>): this {
        return this
    }
    public trackBackgroundColor(value: ResourceColor): this {
        return this
    }
    public strokeWidth(value: Length): this {
        return this
    }
    public trackShadow(value: DataPanelShadowOptions): this {
        return this
    }
    public contentModifier(value: ContentModifier): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkDataPanelComponent extends ArkCommonMethodComponent implements UIDataPanelAttribute {
    getPeer(): ArkDataPanelPeer {
        return (this.peer as ArkDataPanelPeer)
    }
    /** @memo */
    public setDataPanelOptions(options: DataPanelOptions): this {
        if (this.checkPriority("setDataPanelOptions")) {
            const options_casted = options as (DataPanelOptions)
            this.getPeer()?.setDataPanelOptionsAttribute(options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public closeEffect(value: boolean): this {
        if (this.checkPriority("closeEffect")) {
            const value_casted = value as (boolean)
            this.getPeer()?.closeEffectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public valueColors(value: Array<ResourceColor | LinearGradient>): this {
        if (this.checkPriority("valueColors")) {
            const value_casted = value as (Array<ResourceColor | LinearGradient>)
            this.getPeer()?.valueColorsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public trackBackgroundColor(value: ResourceColor): this {
        if (this.checkPriority("trackBackgroundColor")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.trackBackgroundColorAttribute(value_casted)
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
    public trackShadow(value: DataPanelShadowOptions): this {
        if (this.checkPriority("trackShadow")) {
            const value_casted = value as (DataPanelShadowOptions)
            this.getPeer()?.trackShadowAttribute(value_casted)
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
    public attributeModifier(value: AttributeModifier<DataPanelAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkDataPanel(
    /** @memo */
    style: ((attributes: UIDataPanelAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    options: DataPanelOptions,
): void {
    const receiver = remember(() => {
        return new ArkDataPanelComponent()
    })
    NodeAttach<ArkDataPanelPeer>((): ArkDataPanelPeer => ArkDataPanelPeer.create(receiver), (_: ArkDataPanelPeer) => {
        receiver.setDataPanelOptions(options)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
