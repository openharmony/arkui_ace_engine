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
import { Color } from "./enums"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
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
        const thisSerializer : Serializer = Serializer.hold()
        let min_type : int32 = RuntimeType.UNDEFINED
        min_type = runtimeType(min)
        thisSerializer.writeInt8(min_type)
        if ((RuntimeType.UNDEFINED) != (min_type)) {
            const min_value  = min!
            let min_value_type : int32 = RuntimeType.UNDEFINED
            min_value_type = runtimeType(min_value)
            if (RuntimeType.NUMBER == min_value_type) {
                thisSerializer.writeInt8(0)
                const min_value_0  = min_value as number
                thisSerializer.writeNumber(min_value_0)
            }
            else if (RuntimeType.STRING == min_value_type) {
                thisSerializer.writeInt8(1)
                const min_value_1  = min_value as string
                thisSerializer.writeString(min_value_1)
            }
        }
        ArkUIGeneratedNativeModule._BlankInterface_setBlankOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    colorAttribute(value: ResourceColor): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (TypeChecker.isColor(value)) {
            thisSerializer.writeInt8(0)
            const value_0  = value as Color
            thisSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_0))
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(2)
            const value_2  = value as string
            thisSerializer.writeString(value_2)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(3)
            const value_3  = value as Resource
            thisSerializer.writeResource(value_3)
        }
        ArkUIGeneratedNativeModule._BlankAttribute_color(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}

export interface BlankAttribute extends CommonMethod {
    color(value: ResourceColor): this
    attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIBlankAttribute extends UICommonMethod {
    @memo
    color(value: ResourceColor): this
    @memo
    attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkBlankStyle extends ArkCommonMethodStyle implements BlankAttribute {
    color_value?: ResourceColor
    public color(value: ResourceColor): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkBlankComponent extends ArkCommonMethodComponent implements UIBlankAttribute {
    getPeer(): ArkBlankPeer {
        return (this.peer as ArkBlankPeer)
    }
    @memo
    public setBlankOptions(min?: number | string): this {
        if (this.checkPriority("setBlankOptions")) {
            const min_casted = min as (number | string | undefined)
            this.getPeer()?.setBlankOptionsAttribute(min_casted)
            return this
        }
        return this
    }
    @memo
    public color(value: ResourceColor): this {
        if (this.checkPriority("color")) {
            const value_casted = value as (ResourceColor)
            this.getPeer()?.colorAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<BlankAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("Blank")
export function Blank(
    min?: number | string,
    @memo
    content_?: () => void,
): BlankAttribute {
    throw new Error("Not implemented")
}

@memo
export function Blank(
    @memo
    style: ((attributes: UIBlankAttribute) => void) | undefined,
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
        content_?.()
        receiver.applyAttributesFinish()
    })
}
