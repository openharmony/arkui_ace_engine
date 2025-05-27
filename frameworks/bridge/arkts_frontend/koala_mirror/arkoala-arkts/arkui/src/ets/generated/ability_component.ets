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
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkAbilityComponentPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkAbilityComponentPeer {
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
    onConnectAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AbilityComponentAttribute_onConnect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onDisconnectAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._AbilityComponentAttribute_onDisconnect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface Literal__want {
    want: Want;
}

export type Callback_Void = () => void;
export interface AbilityComponentAttribute extends CommonMethod {
    onConnect(value: (() => void)): this
    onDisconnect(value: (() => void)): this
    attributeModifier(value: AttributeModifier<AbilityComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIAbilityComponentAttribute extends UICommonMethod {
    @memo
    onConnect(value: (() => void)): this
    @memo
    onDisconnect(value: (() => void)): this
    @memo
    attributeModifier(value: AttributeModifier<AbilityComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkAbilityComponentStyle extends ArkCommonMethodStyle implements AbilityComponentAttribute {
    onConnect_value?: (() => void)
    onDisconnect_value?: (() => void)
    public onConnect(value: (() => void)): this {
        return this
    }
    public onDisconnect(value: (() => void)): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<AbilityComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkAbilityComponentComponent extends ArkCommonMethodComponent implements UIAbilityComponentAttribute {
    getPeer(): ArkAbilityComponentPeer {
        return (this.peer as ArkAbilityComponentPeer)
    }
    @memo
    public setAbilityComponentOptions(value: Literal__want): this {
        if (this.checkPriority("setAbilityComponentOptions")) {
            const value_casted = value as (Literal__want)
            this.getPeer()?.setAbilityComponentOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onConnect(value: (() => void)): this {
        if (this.checkPriority("onConnect")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onConnectAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public onDisconnect(value: (() => void)): this {
        if (this.checkPriority("onDisconnect")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onDisconnectAttribute(value_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<AbilityComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("AbilityComponent")
export function AbilityComponent(
    value: Literal__want,
    @memo
    content_?: () => void,
): AbilityComponentAttribute {
    throw new Error("Not implemented")
}

@memo
export function AbilityComponent(
    @memo
    style: ((attributes: UIAbilityComponentAttribute) => void) | undefined,
    value: Literal__want,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkAbilityComponentComponent>((): ArkAbilityComponentComponent => {
        return new ArkAbilityComponentComponent()
    })
    NodeAttach<ArkAbilityComponentPeer>((): ArkAbilityComponentPeer => ArkAbilityComponentPeer.create(receiver), (_: ArkAbilityComponentPeer): void => {
        receiver.setAbilityComponentOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
