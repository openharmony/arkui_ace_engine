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
import { ArkCommonMethodPeer, CommonMethod, ArkCommonMethodComponent, ArkCommonMethodStyle } from "./common"
import { Position } from "./units"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkWindowScenePeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkWindowScenePeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._WindowScene_construct(peerId, flags)
        const _peer  = new ArkWindowScenePeer(_peerPtr, peerId, "WindowScene", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setWindowSceneOptionsAttribute(persistentId: number): void {
        ArkUIGeneratedNativeModule._WindowSceneInterface_setWindowSceneOptions(this.peer.ptr, persistentId)
    }
    attractionEffectAttribute(destination: Position | undefined, fraction: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let destination_type : int32 = RuntimeType.UNDEFINED
        destination_type = runtimeType(destination)
        thisSerializer.writeInt8(destination_type as int32)
        if ((RuntimeType.UNDEFINED) != (destination_type)) {
            const destination_value  = destination!
            thisSerializer.writePosition(destination_value)
        }
        let fraction_type : int32 = RuntimeType.UNDEFINED
        fraction_type = runtimeType(fraction)
        thisSerializer.writeInt8(fraction_type as int32)
        if ((RuntimeType.UNDEFINED) != (fraction_type)) {
            const fraction_value  = fraction!
            thisSerializer.writeNumber(fraction_value)
        }
        ArkUIGeneratedNativeModule._WindowSceneAttribute_attractionEffect(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type WindowSceneInterface = (persistentId: number) => WindowSceneAttribute;
export interface WindowSceneAttribute extends CommonMethod {
    attractionEffect(destination: Position | undefined, fraction: number | undefined): this
}
export class ArkWindowSceneStyle extends ArkCommonMethodStyle implements WindowSceneAttribute {
    public attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        return this
        }
}
export class ArkWindowSceneComponent extends ArkCommonMethodComponent implements WindowSceneAttribute {
    getPeer(): ArkWindowScenePeer {
        return (this.peer as ArkWindowScenePeer)
    }
    public setWindowSceneOptions(persistentId: number): this {
        if (this.checkPriority("setWindowSceneOptions")) {
            const persistentId_casted = persistentId as (number)
            this.getPeer()?.setWindowSceneOptionsAttribute(persistentId_casted)
            return this
        }
        return this
    }
    public attractionEffect(destination: Position | undefined, fraction: number | undefined): this {
        if (this.checkPriority("attractionEffect")) {
            const destination_casted = destination as (Position | undefined)
            const fraction_casted = fraction as (number | undefined)
            this.getPeer()?.attractionEffectAttribute(destination_casted, fraction_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function WindowScene(
    /** @memo */
    style: ((attributes: WindowSceneAttribute) => void) | undefined,
    persistentId: number,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkWindowSceneComponent()
    })
    NodeAttach<ArkWindowScenePeer>((): ArkWindowScenePeer => ArkWindowScenePeer.create(receiver), (_: ArkWindowScenePeer) => {
        receiver.setWindowSceneOptions(persistentId)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
