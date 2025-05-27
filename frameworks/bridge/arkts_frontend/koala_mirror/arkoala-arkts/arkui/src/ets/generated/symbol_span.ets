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
import { Resource } from "./resource"
import { ResourceColor } from "./units"
import { FontWeight, Color } from "./enums"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./symbolglyph"
import { AttributeModifier, UICommonBase } from "./../handwritten"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkSymbolSpanPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkSymbolSpanPeer {
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
    fontSizeAttribute(value: number | string | Resource): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as string
            thisSerializer.writeString(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_fontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontColorAttribute(value: Array<ResourceColor>): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(value.length as int32)
        for (let i = 0; i < value.length; i++) {
            const value_element : ResourceColor = value[i]
            let value_element_type : int32 = RuntimeType.UNDEFINED
            value_element_type = runtimeType(value_element)
            if (TypeChecker.isColor(value_element)) {
                thisSerializer.writeInt8(0)
                const value_element_0  = value_element as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_element_0))
            }
            else if (RuntimeType.NUMBER == value_element_type) {
                thisSerializer.writeInt8(1)
                const value_element_1  = value_element as number
                thisSerializer.writeNumber(value_element_1)
            }
            else if (RuntimeType.STRING == value_element_type) {
                thisSerializer.writeInt8(2)
                const value_element_2  = value_element as string
                thisSerializer.writeString(value_element_2)
            }
            else if (RuntimeType.OBJECT == value_element_type) {
                thisSerializer.writeInt8(3)
                const value_element_3  = value_element as Resource
                thisSerializer.writeResource(value_element_3)
            }
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_fontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    fontWeightAttribute(value: number | FontWeight | string): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(0)
            const value_0  = value as number
            thisSerializer.writeNumber(value_0)
        }
        else if (TypeChecker.isFontWeight(value)) {
            thisSerializer.writeInt8(1)
            const value_1  = value as FontWeight
            thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_1))
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_fontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    effectStrategyAttribute(value: SymbolEffectStrategy): void {
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_effectStrategy(this.peer.ptr, TypeChecker.SymbolEffectStrategy_ToNumeric(value))
    }
    renderingStrategyAttribute(value: SymbolRenderingStrategy): void {
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_renderingStrategy(this.peer.ptr, TypeChecker.SymbolRenderingStrategy_ToNumeric(value))
    }
}

export interface SymbolSpanAttribute extends CommonMethod {
    fontSize(value: number | string | Resource): this
    fontColor(value: Array<ResourceColor>): this
    fontWeight(value: number | FontWeight | string): this
    effectStrategy(value: SymbolEffectStrategy): this
    renderingStrategy(value: SymbolRenderingStrategy): this
    attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UISymbolSpanAttribute extends UICommonMethod {
    @memo
    fontSize(value: number | string | Resource): this
    @memo
    fontColor(value: Array<ResourceColor>): this
    @memo
    fontWeight(value: number | FontWeight | string): this
    @memo
    effectStrategy(value: SymbolEffectStrategy): this
    @memo
    renderingStrategy(value: SymbolRenderingStrategy): this
    @memo
    attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkSymbolSpanStyle extends ArkCommonMethodStyle implements SymbolSpanAttribute {
    fontSize_value?: number | string | Resource
    fontColor_value?: Array<ResourceColor>
    fontWeight_value?: number | FontWeight | string
    effectStrategy_value?: SymbolEffectStrategy
    renderingStrategy_value?: SymbolRenderingStrategy
    attributeModifier_value?: AttributeModifier<SymbolSpanAttribute>
    public fontSize(value: number | string | Resource): this {
        return this
    }
    public fontColor(value: Array<ResourceColor>): this {
        return this
    }
    public fontWeight(value: number | FontWeight | string): this {
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy): this {
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkSymbolSpanComponent extends ArkCommonMethodComponent implements UISymbolSpanAttribute {
    getPeer(): ArkSymbolSpanPeer {
        return (this.peer as ArkSymbolSpanPeer)
    }
    @memo
    public setSymbolSpanOptions(value: Resource): this {
        if (this.checkPriority("setSymbolSpanOptions")) {
            const value_casted = value as (Resource)
            this.getPeer()?.setSymbolSpanOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontSize(value: number | string | Resource): this {
        if (this.checkPriority("fontSize")) {
            const value_casted = value as (number | string | Resource)
            this.getPeer()?.fontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontColor(value: Array<ResourceColor>): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (Array<ResourceColor>)
            this.getPeer()?.fontColorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public fontWeight(value: number | FontWeight | string): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string)
            this.getPeer()?.fontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public effectStrategy(value: SymbolEffectStrategy): this {
        if (this.checkPriority("effectStrategy")) {
            const value_casted = value as (SymbolEffectStrategy)
            this.getPeer()?.effectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public renderingStrategy(value: SymbolRenderingStrategy): this {
        if (this.checkPriority("renderingStrategy")) {
            const value_casted = value as (SymbolRenderingStrategy)
            this.getPeer()?.renderingStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("SymbolSpan")
export function SymbolSpan(
    value: Resource,
    @memo
    content_?: () => void,
): SymbolSpanAttribute {
    throw new Error("Not implemented")
}

@memo
export function SymbolSpan(
    @memo
    style: ((attributes: UISymbolSpanAttribute) => void) | undefined,
    value: Resource,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkSymbolSpanComponent>((): ArkSymbolSpanComponent => {
        return new ArkSymbolSpanComponent()
    })
    NodeAttach<ArkSymbolSpanPeer>((): ArkSymbolSpanPeer => ArkSymbolSpanPeer.create(receiver), (_: ArkSymbolSpanPeer): void => {
        receiver.setSymbolSpanOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
