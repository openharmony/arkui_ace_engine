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
import { Color, LineCapStyle } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
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
    setVerticalAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._DividerAttribute_setVertical(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setColorAttribute(value: ResourceColor | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (TypeChecker.isColor(value_value)) {
                thisSerializer.writeInt8((0).toChar())
                const value_value_0  = value_value as Color
                thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_value_0))
            }
            else if (RuntimeType.NUMBER == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as number
                thisSerializer.writeNumber(value_value_1)
            }
            else if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8((2).toChar())
                const value_value_2  = value_value as string
                thisSerializer.writeString(value_value_2)
            }
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((3).toChar())
                const value_value_3  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._DividerAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStrokeWidthAttribute(value: number | string | undefined): void {
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
        }
        ArkUIGeneratedNativeModule._DividerAttribute_setStrokeWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setLineCapAttribute(value: LineCapStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as LineCapStyle)
            thisSerializer.writeInt32(TypeChecker.LineCapStyle_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._DividerAttribute_setLineCap(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface DividerAttribute extends CommonMethod {
    vertical(value: boolean | undefined): this {
        throw new Error("Unimplemented method vertical")
    }
    color(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method color")
    }
    strokeWidth(value: number | string | undefined): this {
        throw new Error("Unimplemented method strokeWidth")
    }
    lineCap(value: LineCapStyle | undefined): this {
        throw new Error("Unimplemented method lineCap")
    }
    attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkDividerStyle extends ArkCommonMethodStyle implements DividerAttribute {
    vertical_value?: boolean | undefined
    color_value?: ResourceColor | undefined
    strokeWidth_value?: number | string | undefined
    lineCap_value?: LineCapStyle | undefined
    attributeModifier_value?: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined
    public vertical(value: boolean | undefined): this {
        return this
    }
    public color(value: ResourceColor | undefined): this {
        return this
    }
    public strokeWidth(value: number | string | undefined): this {
        return this
    }
    public lineCap(value: LineCapStyle | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: DividerAttribute): void {
        super.apply(target)
        if (this.vertical_value !== undefined)
            target.vertical(this.vertical_value!)
        if (this.color_value !== undefined)
            target.color(this.color_value!)
        if (this.strokeWidth_value !== undefined)
            target.strokeWidth(this.strokeWidth_value!)
        if (this.lineCap_value !== undefined)
            target.lineCap(this.lineCap_value!)
    }
}

export class ArkDividerComponent extends ArkCommonMethodComponent implements DividerAttribute {
    getPeer(): ArkDividerPeer {
        return (this.peer as ArkDividerPeer)
    }
    public setDividerOptions(): this {
        if (this.checkPriority("setDividerOptions")) {
            this.getPeer()?.setDividerOptionsAttribute()
            return this
        }
        return this
    }
    public vertical(value: boolean | undefined): this {
        if (this.checkPriority("vertical")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setVerticalAttribute(value_casted)
            return this
        }
        return this
    }
    public color(value: ResourceColor | undefined): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setColorAttribute(value_casted)
            return this
        }
        return this
    }
    public strokeWidth(value: number | string | undefined): this {
        if (this.checkPriority("strokeWidth")) {
            const value_casted = value as (number | string | undefined)
            this.getPeer()?.setStrokeWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public lineCap(value: LineCapStyle | undefined): this {
        if (this.checkPriority("lineCap")) {
            const value_casted = value as (LineCapStyle | undefined)
            this.getPeer()?.setLineCapAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withDividerStyle(receiver: DividerAttribute, modifier: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkDividerStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Divider")
// export function Divider(
//     
//     @memo
//     content_?: () => void,
// ): DividerAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Divider(
    @memo
    style: ((attributes: DividerAttribute) => void) | undefined,
    
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkDividerComponent>((): ArkDividerComponent => {
        return new ArkDividerComponent()
    })
    NodeAttach<ArkDividerPeer>((): ArkDividerPeer => ArkDividerPeer.create(receiver), (_: ArkDividerPeer): void => {
        receiver.setDividerOptions()
        style?.(receiver)
        withDividerStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkDividerSet extends ArkCommonMethodSet implements DividerAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _vertical_flag?: boolean
    _vertical0_value?: boolean | undefined
    _color_flag?: boolean
    _color0_value?: ResourceColor | undefined
    _strokeWidth_flag?: boolean
    _strokeWidth0_value?: number | string | undefined
    _lineCap_flag?: boolean
    _lineCap0_value?: LineCapStyle | undefined
    applyModifierPatch(component: DividerAttribute): void {
        if (this._vertical_flag)
            component.vertical((this._vertical0_value as boolean | undefined))
        if (this._color_flag)
            component.color((this._color0_value as ResourceColor | undefined))
        if (this._strokeWidth_flag)
            component.strokeWidth((this._strokeWidth0_value as number | string | undefined))
        if (this._lineCap_flag)
            component.lineCap((this._lineCap0_value as LineCapStyle | undefined))
    }
    public vertical(value: boolean | undefined): this {
        this._vertical_flag = true
        this._vertical0_value = value
        return this
    }
    public color(value: ResourceColor | undefined): this {
        this._color_flag = true
        this._color0_value = value
        return this
    }
    public strokeWidth(value: number | string | undefined): this {
        this._strokeWidth_flag = true
        this._strokeWidth0_value = value
        return this
    }
    public lineCap(value: LineCapStyle | undefined): this {
        this._lineCap_flag = true
        this._lineCap0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<DividerAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
