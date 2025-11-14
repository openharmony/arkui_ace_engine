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

import { SerializerBase, DeserializerBase, nullptr, KPointer, KInt, KBoolean, KStringPtr, runtimeType, RuntimeType, MaterializedBase, toPeerPtr, NativeBuffer } from "@koalaui/interop"
import { Position_serializer, Position, Length } from "./units"
import { int32, int64, float32 } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { AttributeModifier, hookWindowSceneAttributeModifier, AttributeUpdater } from "#handwritten"
import { Resource } from "global.resource"
import { CallbackKind } from "./../framework/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { WindowSceneModifier } from "./../WindowSceneModifier"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ModifierStateManager } from '../CommonModifier';
export class ArkWindowScenePeer extends ArkCommonMethodPeer {
    attributeSet?: WindowSceneModifier;
    public constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkWindowScenePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WindowScene_construct(peerId, flags)
        const _peer  = new ArkWindowScenePeer(_peerPtr, peerId, 'WindowScene', flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWindowSceneOptionsAttribute(persistentId: number): void {
        ArkUIGeneratedNativeModule._WindowSceneInterface_setWindowSceneOptions(this.peer.ptr, persistentId)
    }
    setAttractionEffectAttribute(destination: Position | undefined, fraction: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        if (destination !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const destinationTmpValue  = destination!
            Position_serializer.write(thisSerializer, destinationTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        if (fraction !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const fractionTmpValue  = fraction!
            thisSerializer.writeNumber(fractionTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._WindowSceneAttribute_setAttractionEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface WindowSceneAttribute extends CommonMethod {
    setWindowSceneOptions(persistentId: number): this {
        throw new Error("Unimplemented method setWindowSceneOptions")
    }
    attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        throw new Error("Unimplemented method attractionEffect")
    }
    attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
}
export class ArkWindowSceneStyle extends ArkCommonMethodStyle implements WindowSceneAttribute {
    attributeModifier_value?: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined
    setWindowSceneOptions(persistentId: number): this {
        return this
    }
    attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

export class ArkWindowSceneComponent extends ArkCommonMethodComponent implements WindowSceneAttribute {
    getPeer(): ArkWindowScenePeer {
        if (!this.peer) {
            throw new Error("Attribute function should be called in memo context")
        }
        return (this.peer as ArkWindowScenePeer)
    }
    public setWindowSceneOptions(persistentId: number): this {
        if (this.checkPriority("setWindowSceneOptions")) {
            const persistentId_casted = persistentId as (number)
            this.getPeer()?.setWindowSceneOptionsAttribute(persistentId_casted)
            this.applyOptionsFinish('WindowSceneAttribute');
            return this
        }
        return this
    }
    public attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        if (this.checkPriority("attractionEffect")) {
            const destination_casted = destination as (Position | undefined)
            const fraction_casted = fraction as (number | undefined)
            this.getPeer()?.setAttractionEffectAttribute(destination_casted, fraction_casted)
            return this
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<WindowSceneAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookWindowSceneAttributeModifier(this, value);
        })
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
    public applyOptionsFinish(traceName: string): void {
        super.applyOptionsFinish(traceName)
    }
}

@memo
export function WindowSceneImpl(
    @memo
    style: ((attributes: WindowSceneAttribute) => void) | undefined,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkWindowSceneComponent>((): ArkWindowSceneComponent => {
        return new ArkWindowSceneComponent()
    })
    NodeAttach<ArkWindowScenePeer>((): ArkWindowScenePeer => ArkWindowScenePeer.create(receiver), (peer: ArkWindowScenePeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

