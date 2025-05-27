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
import { Position, Length } from "./units"
import { Resource } from "./resource"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkWindowScenePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWindowScenePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WindowScene_construct(peerId, flags)
        const _peer  = new ArkWindowScenePeer(_peerPtr, peerId, "WindowScene", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWindowSceneOptionsAttribute(persistentId: number): void {
        ArkUIGeneratedNativeModule._WindowSceneInterface_setWindowSceneOptions(this.peer.ptr, persistentId)
    }
    attractionEffectAttribute(destination: Position, fraction: number): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writePosition(destination)
        ArkUIGeneratedNativeModule._WindowSceneAttribute_attractionEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length(), fraction)
        thisSerializer.release()
    }
}

export interface WindowSceneAttribute extends CommonMethod {
    attractionEffect(destination: Position, fraction: number): this
    attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UIWindowSceneAttribute extends UICommonMethod {
    @memo
    attractionEffect(destination: Position, fraction: number): this
    @memo
    attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkWindowSceneStyle extends ArkCommonMethodStyle implements WindowSceneAttribute {
    public attractionEffect(destination: Position, fraction: number): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
@memo_stable
export class ArkWindowSceneComponent extends ArkCommonMethodComponent implements UIWindowSceneAttribute {
    getPeer(): ArkWindowScenePeer {
        return (this.peer as ArkWindowScenePeer)
    }
    @memo
    public setWindowSceneOptions(persistentId: number): this {
        if (this.checkPriority("setWindowSceneOptions")) {
            const persistentId_casted = persistentId as (number)
            this.getPeer()?.setWindowSceneOptionsAttribute(persistentId_casted)
            return this
        }
        return this
    }
    @memo
    public attractionEffect(destination: Position, fraction: number): this {
        if (this.checkPriority("attractionEffect")) {
            const destination_casted = destination as (Position)
            const fraction_casted = fraction as (number)
            this.getPeer()?.attractionEffectAttribute(destination_casted, fraction_casted)
            return this
        }
        return this
    }
    @memo
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
@BuilderLambda("WindowScene")
export function WindowScene(
    persistentId: number,
    @memo
    content_?: () => void,
): WindowSceneAttribute {
    throw new Error("Not implemented")
}

@memo
export function WindowScene(
    @memo
    style: ((attributes: UIWindowSceneAttribute) => void) | undefined,
    persistentId: number,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkWindowSceneComponent>((): ArkWindowSceneComponent => {
        return new ArkWindowSceneComponent()
    })
    NodeAttach<ArkWindowScenePeer>((): ArkWindowScenePeer => ArkWindowScenePeer.create(receiver), (_: ArkWindowScenePeer): void => {
        receiver.setWindowSceneOptions(persistentId)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
