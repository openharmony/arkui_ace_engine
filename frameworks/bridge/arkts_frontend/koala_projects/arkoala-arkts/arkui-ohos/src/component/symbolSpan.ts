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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Resource } from "global/resource"
import { ResourceColor } from "./units"
import { FontWeight, Color } from "./enums"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./symbolglyph"

import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSymbolSpanPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkSymbolSpanPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._SymbolSpan_construct(peerId, flags)
        const _peer  = new ArkSymbolSpanPeer(_peerPtr, peerId, "SymbolSpan", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setSymbolSpanOptionsAttribute(value: Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeResource(value)
        ArkUIGeneratedNativeModule._SymbolSpanInterface_setSymbolSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: Array<ResourceColor> | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeInt32(value_value.length as int32)
            for (let i = 0; i < value_value.length; i++) {
                const value_value_element : ResourceColor = value_value[i]
                let value_value_element_type : int32 = RuntimeType.UNDEFINED
                value_value_element_type = runtimeType(value_value_element)
                if (TypeChecker.isColor(value_value_element)) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_element_0  = value_value_element as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_element_0))
                }
                else if (RuntimeType.NUMBER == value_value_element_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_element_1  = value_value_element as number
                    thisSerializer.writeNumber(value_value_element_1)
                }
                else if (RuntimeType.STRING == value_value_element_type) {
                    thisSerializer.writeInt8(2 as int32)
                    const value_value_element_2  = value_value_element as string
                    thisSerializer.writeString(value_value_element_2)
                }
                else if (RuntimeType.OBJECT == value_value_element_type) {
                    thisSerializer.writeInt8(3 as int32)
                    const value_value_element_3  = value_value_element as Resource
                    thisSerializer.writeResource(value_value_element_3)
                }
            }
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    effectStrategyAttribute(value: SymbolEffectStrategy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SymbolEffectStrategy)
            thisSerializer.writeInt32(TypeChecker.SymbolEffectStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_effectStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    renderingStrategyAttribute(value: SymbolRenderingStrategy | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as SymbolRenderingStrategy)
            thisSerializer.writeInt32(TypeChecker.SymbolRenderingStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_renderingStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type SymbolSpanInterface = (value: Resource) => SymbolSpanAttribute;
export interface SymbolSpanAttribute extends CommonMethod {
    fontSize(value: number | string | Resource | undefined): this
    fontColor(value: Array<ResourceColor> | undefined): this
    fontWeight(value: number | FontWeight | string | undefined): this
    effectStrategy(value: SymbolEffectStrategy | undefined): this
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this
}
export class ArkSymbolSpanStyle extends ArkCommonMethodStyle implements SymbolSpanAttribute {
    fontSize_value?: number | string | Resource | undefined
    fontColor_value?: Array<ResourceColor> | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    effectStrategy_value?: SymbolEffectStrategy | undefined
    renderingStrategy_value?: SymbolRenderingStrategy | undefined
    public fontSize(value: number | string | Resource | undefined): this {
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        return this
        }
}
export class ArkSymbolSpanComponent extends ArkCommonMethodComponent implements SymbolSpanAttribute {
    getPeer(): ArkSymbolSpanPeer {
        return (this.peer as ArkSymbolSpanPeer)
    }
    public setSymbolSpanOptions(value: Resource): this {
        if (this.checkPriority("setSymbolSpanOptions")) {
            const value_casted = value as (Resource)
            this.getPeer()?.setSymbolSpanOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public fontSize(value: number | string | Resource | undefined): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource | undefined)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (Array<ResourceColor> | undefined)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (this.checkPriority("effectStrategy")) {
            const value_casted = value as (SymbolEffectStrategy | undefined)
            this.getPeer()?.effectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (this.checkPriority("renderingStrategy")) {
            const value_casted = value as (SymbolRenderingStrategy | undefined)
            this.getPeer()?.renderingStrategyAttribute(value_casted)
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
export function SymbolSpan(
    /** @memo */
    style: ((attributes: SymbolSpanAttribute) => void) | undefined,
    value: Resource,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkSymbolSpanComponent()
    })
    NodeAttach<ArkSymbolSpanPeer>((): ArkSymbolSpanPeer => ArkSymbolSpanPeer.create(receiver), (_: ArkSymbolSpanPeer) => {
        receiver.setSymbolSpanOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
