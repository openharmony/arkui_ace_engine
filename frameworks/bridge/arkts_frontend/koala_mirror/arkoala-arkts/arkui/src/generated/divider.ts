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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { ResourceColor } from "./units"
import { LineCapStyle, Color } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkDividerPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkDividerPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Divider_construct(peerId, flags)
        const _peer  = new ArkDividerPeer(_peerPtr, peerId, "Divider", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setDividerOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._DividerInterface_setDividerOptions(this.peer.ptr)
    }
    verticalAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._DividerAttribute_vertical(this.peer.ptr, value ? 1 : 0)
    }
    colorAttribute(value: ResourceColor): void {
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
        ArkUIGeneratedNativeModule._DividerAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    strokeWidthAttribute(value: number | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        ArkUIGeneratedNativeModule._DividerAttribute_strokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    lineCapAttribute(value: LineCapStyle): void {
        ArkUIGeneratedNativeModule._DividerAttribute_lineCap(this.peer.ptr, TypeChecker.LineCapStyle_ToNumeric(value))
    }
}

export interface DividerAttribute extends CommonMethod {
    vertical(value: boolean): this
    color(value: ResourceColor): this
    strokeWidth(value: number | string): this
    lineCap(value: LineCapStyle): this
    attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIDividerAttribute extends UICommonMethod {
    /** @memo */
    vertical(value: boolean): this
    /** @memo */
    color(value: ResourceColor): this
    /** @memo */
    strokeWidth(value: number | string): this
    /** @memo */
    lineCap(value: LineCapStyle): this
    /** @memo */
    attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkDividerStyle extends ArkCommonMethodStyle implements DividerAttribute {
    vertical_value?: boolean
    color_value?: ResourceColor
    strokeWidth_value?: number | string
    lineCap_value?: LineCapStyle
    public vertical(value: boolean): this {
        return this
    }
    public color(value: ResourceColor): this {
        return this
    }
    public strokeWidth(value: number | string): this {
        return this
    }
    public lineCap(value: LineCapStyle): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkDividerComponent extends ArkCommonMethodComponent implements UIDividerAttribute {
    getPeer(): ArkDividerPeer {
        return (this.peer as ArkDividerPeer)
    }
    /** @memo */
    public setDividerOptions(): this {
        if (this.checkPriority("setDividerOptions")) {
            this.getPeer()?.setDividerOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public vertical(value: boolean): this {
        if (this.checkPriority("vertical")) {
            const value_casted = value as (boolean)
            this.getPeer()?.verticalAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public color(value: ResourceColor): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.colorAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public strokeWidth(value: number | string): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (number | string)
            this.getPeer()?.strokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public lineCap(value: LineCapStyle): this {
        if (this.checkPriority("lineCap")) {
            const value_casted = value as (LineCapStyle)
            this.getPeer()?.lineCapAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkDivider(
    /** @memo */
    style: ((attributes: UIDividerAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    
): void {
    const receiver = remember(() => {
        return new ArkDividerComponent()
    })
    NodeAttach<ArkDividerPeer>((): ArkDividerPeer => ArkDividerPeer.create(receiver), (_: ArkDividerPeer) => {
        receiver.setDividerOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
