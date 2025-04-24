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
import { Want } from "./ohos.app.ability"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { AttributeModifier, UICommonBase } from "./../handwritten"
export class ArkAbilityComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkAbilityComponentPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._AbilityComponent_construct(peerId, flags)
        const _peer  = new ArkAbilityComponentPeer(_peerPtr, peerId, "AbilityComponent", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setAbilityComponentOptionsAttribute(value: Literal__want): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_want  = value.want
        thisSerializer.writeWant(value_want)
        ArkUIGeneratedNativeModule._AbilityComponentInterface_setAbilityComponentOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onConnectAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AbilityComponentAttribute_onConnect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDisconnectAttribute(value: (() => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._AbilityComponentAttribute_onDisconnect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface Literal__want {
    want: Want;
}
export type AbilityComponentInterface = (value: Literal__want) => AbilityComponentAttribute;
export type Callback_Void = () => void;
export interface AbilityComponentAttribute extends CommonMethod {
    onConnect(value: (() => void) | undefined): this
    onDisconnect(value: (() => void) | undefined): this
    attributeModifier(value: AttributeModifier<AbilityComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIAbilityComponentAttribute extends UICommonMethod {
    /** @memo */
    onConnect(value: (() => void) | undefined): this
    /** @memo */
    onDisconnect(value: (() => void) | undefined): this
    /** @memo */
    attributeModifier(value: AttributeModifier<AbilityComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkAbilityComponentStyle extends ArkCommonMethodStyle implements AbilityComponentAttribute {
    onConnect_value?: (() => void) | undefined
    onDisconnect_value?: (() => void) | undefined
    public onConnect(value: (() => void) | undefined): this {
        return this
    }
    public onDisconnect(value: (() => void) | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<AbilityComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkAbilityComponentComponent extends ArkCommonMethodComponent implements UIAbilityComponentAttribute {
    getPeer(): ArkAbilityComponentPeer {
        return (this.peer as ArkAbilityComponentPeer)
    }
    /** @memo */
    public setAbilityComponentOptions(value: Literal__want): this {
        if (this.checkPriority("setAbilityComponentOptions")) {
            const value_casted = value as (Literal__want)
            this.getPeer()?.setAbilityComponentOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onConnect(value: (() => void) | undefined): this {
        if (this.checkPriority("onConnect")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onConnectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onDisconnect(value: (() => void) | undefined): this {
        if (this.checkPriority("onDisconnect")) {
            const value_casted = value as ((() => void) | undefined)
            this.getPeer()?.onDisconnectAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<AbilityComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function AbilityComponent(
    /** @memo */
    style: ((attributes: UIAbilityComponentAttribute) => void) | undefined,
    value: Literal__want,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkAbilityComponentComponent()
    })
    NodeAttach<ArkAbilityComponentPeer>((): ArkAbilityComponentPeer => ArkAbilityComponentPeer.create(receiver), (_: ArkAbilityComponentPeer) => {
        receiver.setAbilityComponentOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
