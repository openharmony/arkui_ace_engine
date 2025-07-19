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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, wrapCallback, NativeBuffer, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle, ArkCommonMethodSet } from "./common"
import { AttributeModifier, UICommonBase, AttributeUpdater } from "./../handwritten"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { NodeAttach, remember } from "@koalaui/runtime"
export class ArkRootScenePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkRootScenePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RootScene_construct(peerId, flags)
        const _peer  = new ArkRootScenePeer(_peerPtr, peerId, "RootScene", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRootSceneOptionsAttribute(session: RootSceneSession): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        RootSceneSession_serializer.write(thisSerializer, session)
        ArkUIGeneratedNativeModule._RootSceneInterface_setRootSceneOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RootSceneSession {
}
export interface RootSceneAttribute extends CommonMethod {
    attributeModifier(value: AttributeModifier<RootSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkRootSceneStyle extends ArkCommonMethodStyle implements RootSceneAttribute {
    attributeModifier_value?: AttributeModifier<RootSceneAttribute> | AttributeModifier<CommonMethod> | undefined
    public attributeModifier(value: AttributeModifier<RootSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: RootSceneAttribute): void {
        super.apply(target)
    }
}

export class ArkRootSceneComponent extends ArkCommonMethodComponent implements RootSceneAttribute {
    getPeer(): ArkRootScenePeer {
        return (this.peer as ArkRootScenePeer)
    }
    public setRootSceneOptions(session: RootSceneSession): this {
        if (this.checkPriority("setRootSceneOptions")) {
            const session_casted = session as (RootSceneSession)
            this.getPeer()?.setRootSceneOptionsAttribute(session_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<RootSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        this._modifier = value as AttributeModifier<CommonMethod>
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withRootSceneStyle(receiver: RootSceneAttribute, modifier: AttributeModifier<RootSceneAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkRootSceneStyle()
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CommonMethod>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CommonMethod>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("RootScene")
// export function RootScene(
//     session: RootSceneSession,
//     @memo
//     content_?: () => void,
// ): RootSceneAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function RootScene(
    @memo
    style: ((attributes: RootSceneAttribute) => void) | undefined,
    session: RootSceneSession,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkRootSceneComponent>((): ArkRootSceneComponent => {
        return new ArkRootSceneComponent()
    })
    NodeAttach<ArkRootScenePeer>((): ArkRootScenePeer => ArkRootScenePeer.create(receiver), (_: ArkRootScenePeer): void => {
        receiver.setRootSceneOptions(session)
        style?.(receiver)
        withRootSceneStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class ArkRootSceneSet extends ArkCommonMethodSet implements RootSceneAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyModifierPatch(component: RootSceneAttribute): void {
    }
    public attributeModifier(value: AttributeModifier<RootSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export class RootSceneSession_serializer {
    public static write(buffer: SerializerBase, value: RootSceneSession): void {
    }
    public static read(buffer: DeserializerBase): RootSceneSession {
        let value : RootSceneSession = ({} as RootSceneSession)
        return value
    }
}
