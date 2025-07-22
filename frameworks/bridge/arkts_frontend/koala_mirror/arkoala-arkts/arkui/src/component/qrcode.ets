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
import { ResourceColor, ResourceStr } from "./units"
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkQRCodePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkQRCodePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._QRCode_construct(peerId, flags)
        const _peer  = new ArkQRCodePeer(_peerPtr, peerId, "QRCode", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setQRCodeOptionsAttribute(value: ResourceStr): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8((0).toChar())
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8((1).toChar())
            const value_1  = value as Resource
            Resource_serializer.write(thisSerializer, value_1)
        }
        ArkUIGeneratedNativeModule._QRCodeInterface_setQRCodeOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._QRCodeAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setBackgroundColorAttribute(value: ResourceColor | undefined): void {
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
        ArkUIGeneratedNativeModule._QRCodeAttribute_setBackgroundColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setContentOpacityAttribute(value: number | Resource | undefined): void {
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
            else if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const value_value_1  = value_value as Resource
                Resource_serializer.write(thisSerializer, value_value_1)
            }
        }
        ArkUIGeneratedNativeModule._QRCodeAttribute_setContentOpacity(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface QRCodeAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method color")
    }
    backgroundColor(value: ResourceColor | undefined): this
    contentOpacity(value: number | Resource | undefined): this {
        throw new Error("Unimplemented method contentOpacity")
    }
    attributeModifier(value: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkQRCodeStyle extends ArkCommonMethodStyle implements QRCodeAttribute {
    color_value?: ResourceColor | undefined
    backgroundColor_value?: ResourceColor | undefined
    contentOpacity_value?: number | Resource | undefined
    attributeModifier_value?: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined
    public color(value: ResourceColor | undefined): this {
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        return this
    }
    public contentOpacity(value: number | Resource | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: QRCodeAttribute): void {
        super.apply(target)
        if (this.color_value !== undefined)
            target.color(this.color_value!)
        if (this.backgroundColor_value !== undefined)
            target.backgroundColor(this.backgroundColor_value!)
        if (this.contentOpacity_value !== undefined)
            target.contentOpacity(this.contentOpacity_value!)
    }
}

export class ArkQRCodeComponent extends ArkCommonMethodComponent implements QRCodeAttribute {
    getPeer(): ArkQRCodePeer {
        return (this.peer as ArkQRCodePeer)
    }
    public setQRCodeOptions(value: ResourceStr): this {
        if (this.checkPriority("setQRCodeOptions")) {
            const value_casted = value as (ResourceStr)
            this.getPeer()?.setQRCodeOptionsAttribute(value_casted)
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
    public backgroundColor(value: ResourceColor | undefined): this {
        if (this.checkPriority("backgroundColor")) {
            const value_casted = value as (ResourceColor | undefined)
            this.getPeer()?.setBackgroundColorAttribute(value_casted)
            return this
        }
        return this
    }
    public contentOpacity(value: number | Resource | undefined): this {
        if (this.checkPriority("contentOpacity")) {
            const value_casted = value as (number | Resource | undefined)
            this.getPeer()?.setContentOpacityAttribute(value_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withQRCodeStyle(receiver: QRCodeAttribute, modifier: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkQRCodeStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("QRCode")
// export function QRCode(
//     value: ResourceStr,
//     @memo
//     content_?: () => void,
// ): QRCodeAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function QRCode(
    @memo
    style: ((attributes: QRCodeAttribute) => void) | undefined,
    value: ResourceStr,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkQRCodeComponent>((): ArkQRCodeComponent => {
        return new ArkQRCodeComponent()
    })
    NodeAttach<ArkQRCodePeer>((): ArkQRCodePeer => ArkQRCodePeer.create(receiver), (_: ArkQRCodePeer): void => {
        receiver.setQRCodeOptions(value)
        style?.(receiver)
        withQRCodeStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkQRCodeSet extends ArkCommonMethodSet implements QRCodeAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _color_flag?: boolean
    _color0_value?: ResourceColor | undefined
    _backgroundColor_flag?: boolean
    _backgroundColor0_value?: ResourceColor | undefined
    _contentOpacity_flag?: boolean
    _contentOpacity0_value?: number | Resource | undefined
    applyModifierPatch(component: QRCodeAttribute): void {
        if (this._color_flag)
            component.color((this._color0_value as ResourceColor | undefined))
        if (this._backgroundColor_flag)
            component.backgroundColor((this._backgroundColor0_value as ResourceColor | undefined))
        if (this._contentOpacity_flag)
            component.contentOpacity((this._contentOpacity0_value as number | Resource | undefined))
    }
    public color(value: ResourceColor | undefined): this {
        this._color_flag = true
        this._color0_value = value
        return this
    }
    public backgroundColor(value: ResourceColor | undefined): this {
        this._backgroundColor_flag = true
        this._backgroundColor0_value = value
        return this
    }
    public contentOpacity(value: number | Resource | undefined): this {
        this._contentOpacity_flag = true
        this._contentOpacity0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<QRCodeAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
