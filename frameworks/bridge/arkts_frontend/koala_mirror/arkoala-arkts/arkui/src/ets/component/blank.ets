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
import { Color } from "./enums"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkBlankPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkBlankPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Blank_construct(peerId, flags)
        const _peer  = new ArkBlankPeer(_peerPtr, peerId, "Blank", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setBlankOptionsAttribute(min?: number | string): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let min_type : int32 = RuntimeType.UNDEFINED
        min_type = runtimeType(min)
        thisSerializer.writeInt8((min_type).toChar())
        if ((min_type) != (RuntimeType.UNDEFINED)) {
            const min_value  = min!
            let min_value_type : int32 = RuntimeType.UNDEFINED
            min_value_type = runtimeType(min_value)
            if (RuntimeType.NUMBER == min_value_type) {
                thisSerializer.writeInt8((0).toChar())
                const min_value_0  = min_value as number
                thisSerializer.writeNumber(min_value_0)
            }
            else if (RuntimeType.STRING == min_value_type) {
                thisSerializer.writeInt8((1).toChar())
                const min_value_1  = min_value as string
                thisSerializer.writeString(min_value_1)
            }
        }
        ArkUIGeneratedNativeModule._BlankInterface_setBlankOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._BlankAttribute_setColor(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface BlankAttribute extends CommonMethod {
    color(value: ResourceColor | undefined): this {
        throw new Error("Unimplemented method color")
    }
    attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkBlankStyle extends ArkCommonMethodStyle implements BlankAttribute {
    color_value?: ResourceColor | undefined
    attributeModifier_value?: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined
    public color(value: ResourceColor | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: BlankAttribute): void {
        super.apply(target)
        if (this.color_value !== undefined)
            target.color(this.color_value!)
    }
}

export class ArkBlankComponent extends ArkCommonMethodComponent implements BlankAttribute {
    getPeer(): ArkBlankPeer {
        return (this.peer as ArkBlankPeer)
    }
    public setBlankOptions(min?: number | string): this {
        if (this.checkPriority("setBlankOptions")) {
            const min_casted = min as (number | string | undefined)
            this.getPeer()?.setBlankOptionsAttribute(min_casted)
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
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withBlankStyle(receiver: BlankAttribute, modifier: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkBlankStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Blank")
// export function Blank(
//     min?: number | string,
//     @memo
//     content_?: () => void,
// ): BlankAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Blank(
    @memo
    style: ((attributes: BlankAttribute) => void) | undefined,
    min?: number | string,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkBlankComponent>((): ArkBlankComponent => {
        return new ArkBlankComponent()
    })
    NodeAttach<ArkBlankPeer>((): ArkBlankPeer => ArkBlankPeer.create(receiver), (_: ArkBlankPeer): void => {
        receiver.setBlankOptions(min)
        style?.(receiver)
        withBlankStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkBlankSet extends ArkCommonMethodSet implements BlankAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _color_flag?: boolean
    _color0_value?: ResourceColor | undefined
    applyModifierPatch(component: BlankAttribute): void {
        if (this._color_flag)
            component.color((this._color0_value as ResourceColor | undefined))
    }
    public color(value: ResourceColor | undefined): this {
        this._color_flag = true
        this._color0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
