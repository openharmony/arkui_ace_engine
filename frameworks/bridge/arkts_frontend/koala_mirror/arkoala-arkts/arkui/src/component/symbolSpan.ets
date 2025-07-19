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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { Resource_serializer, Resource } from "./../generated/resource"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { ResourceColor } from "./units"
import { Color, FontWeight } from "./enums"
import { SymbolEffectStrategy, SymbolRenderingStrategy } from "./symbolglyph"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
        const thisSerializer : SerializerBase = SerializerBase.hold()
        Resource_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._SymbolSpanInterface_setSymbolSpanOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontSizeAttribute(value: number | string | Resource | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as string
                thisSerializer.writeString(value_value_1)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setFontSize(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontColorAttribute(value: Array<ResourceColor> | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeInt32((value_value.length).toInt())
            for (let value_value_counter_i = 0; value_value_counter_i < value_value.length; value_value_counter_i++) {
                const value_value_element : ResourceColor = value_value[value_value_counter_i]
                let value_value_element_type : int32 = RuntimeType.UNDEFINED
                value_value_element_type = runtimeType(value_value_element)
                if (TypeChecker.isColor(value_value_element)) {
                    thisSerializer.writeInt8((0).toChar())
                    const value_value_element_0  = value_value_element as Color
                    thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_element_0))
                }
                else if (RuntimeType.NUMBER == value_value_element_type) {
                    thisSerializer.writeInt8((1).toChar())
                    const value_value_element_1  = value_value_element as number
                    thisSerializer.writeNumber(value_value_element_1)
                }
                else if (RuntimeType.STRING == value_value_element_type) {
                    thisSerializer.writeInt8((2).toChar())
                    const value_value_element_2  = value_value_element as string
                    thisSerializer.writeString(value_value_element_2)
                }
                else if (RuntimeType.OBJECT == value_value_element_type) {
                    thisSerializer.writeInt8((3).toChar())
                    const value_value_element_3  = value_value_element as Resource
                    Resource_serializer.write(thisSerializer, value_value_element_3)
                }
            }
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setFontColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setFontWeightAttribute(value: number | FontWeight | string | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as number
                thisSerializer.writeNumber(value_value_0)
            }
            else if (TypeChecker.isFontWeight(value_value)) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as FontWeight
                thisSerializer.writeInt32(TypeChecker.FontWeight_ToNumeric(value_value_1))
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setFontWeight(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setEffectStrategyAttribute(value: SymbolEffectStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SymbolEffectStrategy)
            thisSerializer.writeInt32(TypeChecker.SymbolEffectStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setEffectStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setRenderingStrategyAttribute(value: SymbolRenderingStrategy | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as SymbolRenderingStrategy)
            thisSerializer.writeInt32(TypeChecker.SymbolRenderingStrategy_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._SymbolSpanAttribute_setRenderingStrategy(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface SymbolSpanAttribute extends CommonMethod {
    fontSize(value: number | string | Resource | undefined): this {
        throw new Error("Unimplemented method fontSize")
    }
    fontColor(value: Array<ResourceColor> | undefined): this {
        throw new Error("Unimplemented method fontColor")
    }
    fontWeight(value: number | FontWeight | string | undefined): this {
        throw new Error("Unimplemented method fontWeight")
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        throw new Error("Unimplemented method effectStrategy")
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        throw new Error("Unimplemented method renderingStrategy")
    }
    attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkSymbolSpanStyle extends ArkCommonMethodStyle implements SymbolSpanAttribute {
    fontSize_value?: number | string | Resource | undefined
    fontColor_value?: Array<ResourceColor> | undefined
    fontWeight_value?: number | FontWeight | string | undefined
    effectStrategy_value?: SymbolEffectStrategy | undefined
    renderingStrategy_value?: SymbolRenderingStrategy | undefined
    attributeModifier_value?: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined
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
    public attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: SymbolSpanAttribute): void {
        super.apply(target)
        if (this.fontSize_value !== undefined)
            target.fontSize(this.fontSize_value!)
        if (this.fontColor_value !== undefined)
            target.fontColor(this.fontColor_value!)
        if (this.fontWeight_value !== undefined)
            target.fontWeight(this.fontWeight_value!)
        if (this.effectStrategy_value !== undefined)
            target.effectStrategy(this.effectStrategy_value!)
        if (this.renderingStrategy_value !== undefined)
            target.renderingStrategy(this.renderingStrategy_value!)
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
            this.getPeer()?.setFontSizeAttribute(value_casted)
            return this
        }
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        if (this.checkPriority("fontColor")) {
            const value_casted = value as (Array<ResourceColor> | undefined)
            this.getPeer()?.setFontColorAttribute(value_casted)
            return this
        }
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        if (this.checkPriority("fontWeight")) {
            const value_casted = value as (number | FontWeight | string | undefined)
            this.getPeer()?.setFontWeightAttribute(value_casted)
            return this
        }
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (this.checkPriority("effectStrategy")) {
            const value_casted = value as (SymbolEffectStrategy | undefined)
            this.getPeer()?.setEffectStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (this.checkPriority("renderingStrategy")) {
            const value_casted = value as (SymbolRenderingStrategy | undefined)
            this.getPeer()?.setRenderingStrategyAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withSymbolSpanStyle(receiver: SymbolSpanAttribute, modifier: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkSymbolSpanStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("SymbolSpan")
// export function SymbolSpan(
//     value: Resource,
//     @memo
//     content_?: () => void,
// ): SymbolSpanAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function SymbolSpan(
    @memo
    style: ((attributes: SymbolSpanAttribute) => void) | undefined,
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
        withSymbolSpanStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkSymbolSpanSet extends ArkCommonMethodSet implements SymbolSpanAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _fontSize_flag?: boolean
    _fontSize0_value?: number | string | Resource | undefined
    _fontColor_flag?: boolean
    _fontColor0_value?: Array<ResourceColor> | undefined
    _fontWeight_flag?: boolean
    _fontWeight0_value?: number | FontWeight | string | undefined
    _effectStrategy_flag?: boolean
    _effectStrategy0_value?: SymbolEffectStrategy | undefined
    _renderingStrategy_flag?: boolean
    _renderingStrategy0_value?: SymbolRenderingStrategy | undefined
    applyModifierPatch(component: SymbolSpanAttribute): void {
        if (this._fontSize_flag)
            component.fontSize((this._fontSize0_value as number | string | Resource | undefined))
        if (this._fontColor_flag)
            component.fontColor((this._fontColor0_value as Array<ResourceColor> | undefined))
        if (this._fontWeight_flag)
            component.fontWeight((this._fontWeight0_value as number | FontWeight | string | undefined))
        if (this._effectStrategy_flag)
            component.effectStrategy((this._effectStrategy0_value as SymbolEffectStrategy | undefined))
        if (this._renderingStrategy_flag)
            component.renderingStrategy((this._renderingStrategy0_value as SymbolRenderingStrategy | undefined))
    }
    public fontSize(value: number | string | Resource | undefined): this {
        this._fontSize_flag = true
        this._fontSize0_value = value
        return this
    }
    public fontColor(value: Array<ResourceColor> | undefined): this {
        this._fontColor_flag = true
        this._fontColor0_value = value
        return this
    }
    public fontWeight(value: number | FontWeight | string | undefined): this {
        this._fontWeight_flag = true
        this._fontWeight0_value = value
        return this
    }
    public effectStrategy(value: SymbolEffectStrategy | undefined): this {
        this._effectStrategy_flag = true
        this._effectStrategy0_value = value
        return this
    }
    public renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        this._renderingStrategy_flag = true
        this._renderingStrategy0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
