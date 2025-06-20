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
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, MultiShadowOptions, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { ResourceColor, Length } from "./units"
import { ContentModifier, CommonConfiguration } from "./arkui-wrapper-builder"
import { Color } from "./enums"
import { Resource } from "global/resource"
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkDataPanelPeer {
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
    closeEffectAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_closeEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    valueColorsAttribute(value: Array<ResourceColor | LinearGradient> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ResourceColor | LinearGradient = value_value[i]
                let value_value_element_type : int32 = RuntimeType.UNDEFINED
                value_value_element_type = runtimeType(value_value_element)
                if ((TypeChecker.isColor(value_value_element)) || (RuntimeType.NUMBER == value_value_element_type) || (RuntimeType.STRING == value_value_element_type) || (RuntimeType.OBJECT == value_value_element_type)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_element_0  = value_value_element as ResourceColor
                    let value_value_element_0_type : int32 = RuntimeType.UNDEFINED
                    value_value_element_0_type = runtimeType(value_value_element_0)
                    if (TypeChecker.isColor(value_value_element_0)) {
                        thisSerializer.writeInt8(0 as int32)
                        const value_value_element_0_0  = value_value_element_0 as Color
                        thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_element_0_0))
                    }
                    else if (RuntimeType.NUMBER == value_value_element_0_type) {
                        thisSerializer.writeInt8(1 as int32)
                        const value_value_element_0_1  = value_value_element_0 as number
                        thisSerializer.writeNumber(value_value_element_0_1)
                    }
                    else if (RuntimeType.STRING == value_value_element_0_type) {
                        thisSerializer.writeInt8(2 as int32)
                        const value_value_element_0_2  = value_value_element_0 as string
                        thisSerializer.writeString(value_value_element_0_2)
                    }
                    else if (RuntimeType.OBJECT == value_value_element_0_type) {
                        thisSerializer.writeInt8(3 as int32)
                        const value_value_element_0_3  = value_value_element_0 as Resource
                        thisSerializer.writeResource(value_value_element_0_3)
                    }
                }
                else if (TypeChecker.isLinearGradient(value_value_element)) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_element_1  = value_value_element as LinearGradient
                    thisSerializer.writeLinearGradient(value_value_element_1)
                }
            }
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_valueColors(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackBackgroundColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as Resource
                thisSerializer.writeResource(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_trackBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._DataPanelAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    trackShadowAttribute(value: DataPanelShadowOptions | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeDataPanelShadowOptions(value_value)
        }
        ArkUIGeneratedNativeModule._DataPanelAttribute_trackShadow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
export type DataPanelInterface = (options: DataPanelOptions) => DataPanelAttribute;
export interface DataPanelConfiguration extends CommonConfiguration {
    values: Array<number>;
    maxValue: number;
}
export interface DataPanelAttribute extends CommonMethod {
    closeEffect(value: boolean | undefined): this
    valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this
    trackBackgroundColor(value: ResourceColor | undefined): this
    strokeWidth(value: Length | undefined): this
    trackShadow(value: DataPanelShadowOptions | undefined): this
    contentModifier(value: ContentModifier | undefined): this
}
export class ArkDataPanelStyle extends ArkCommonMethodStyle implements DataPanelAttribute {
    closeEffect_value?: boolean | undefined
    valueColors_value?: Array<ResourceColor | LinearGradient> | undefined
    trackBackgroundColor_value?: ResourceColor | undefined
    strokeWidth_value?: Length | undefined
    trackShadow_value?: DataPanelShadowOptions | undefined
    contentModifier_value?: ContentModifier | undefined
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
    public contentModifier(value: ContentModifier | undefined): this {
        return this
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
            this.getPeer()?.closeEffectAttribute(value_casted)
            return this
        }
        return this
    }
    public valueColors(value: Array<ResourceColor | LinearGradient> | undefined): this {
        if (this.checkPriority("valueColors")) {
            const value_casted = value as (Array<ResourceColor | LinearGradient> | undefined)
            this.getPeer()?.valueColorsAttribute(value_casted)
            return this
        }
        return this
    }
    public trackBackgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("trackBackgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.trackBackgroundColorAttribute(value_casted)
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
    public trackShadow(value: DataPanelShadowOptions | undefined): this {
        if (this.checkPriority("trackShadow")) {
            const value_casted = value as (DataPanelShadowOptions | undefined)
            this.getPeer()?.trackShadowAttribute(value_casted)
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
export function DataPanel(
    /** @memo */
    style: ((attributes: DataPanelAttribute) => void) | undefined,
    options: DataPanelOptions,
    /** @memo */
    content_?: (() => void) | undefined,
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
