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
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"

export class ArkRemoteWindowPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkRemoteWindowPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._RemoteWindow_construct(peerId, flags)
        const _peer  = new ArkRemoteWindowPeer(_peerPtr, peerId, "RemoteWindow", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setRemoteWindowOptionsAttribute(target: WindowAnimationTarget): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeWindowAnimationTarget(target)
        ArkUIGeneratedNativeModule._RemoteWindowInterface_setRemoteWindowOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface RRect {
    left: number;
    top: number;
    width: number;
    height: number;
    radius: number;
}
export interface WindowAnimationTarget {
    bundleName: string;
    abilityName: string;
    windowBounds: RRect;
    missionId: number;
}
export type RemoteWindowInterface = (target: WindowAnimationTarget) => RemoteWindowAttribute;
export interface RemoteWindowAttribute extends CommonMethod {
}
export class ArkRemoteWindowStyle extends ArkCommonMethodStyle implements RemoteWindowAttribute {
    
}
export class ArkRemoteWindowComponent extends ArkCommonMethodComponent implements RemoteWindowAttribute {
    getPeer(): ArkRemoteWindowPeer {
        return (this.peer as ArkRemoteWindowPeer)
    }
    public setRemoteWindowOptions(target: WindowAnimationTarget): this {
        if (this.checkPriority("setRemoteWindowOptions")) {
            const target_casted = target as (WindowAnimationTarget)
            this.getPeer()?.setRemoteWindowOptionsAttribute(target_casted)
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
export function RemoteWindow(
    /** @memo */
    style: ((attributes: RemoteWindowAttribute) => void) | undefined,
    target: WindowAnimationTarget,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkRemoteWindowComponent()
    })
    NodeAttach<ArkRemoteWindowPeer>((): ArkRemoteWindowPeer => ArkRemoteWindowPeer.create(receiver), (_: ArkRemoteWindowPeer) => {
        receiver.setRemoteWindowOptions(target)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
