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

export class ArkScreenPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkScreenPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Screen_construct(peerId, flags)
        const _peer  = new ArkScreenPeer(_peerPtr, peerId, "Screen", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setScreenOptionsAttribute(screenId: number): void {
        ArkUIGeneratedNativeModule._ScreenInterface_setScreenOptions(this.peer.ptr, screenId)
    }
}
export type ScreenInterface = (screenId: number) => ScreenAttribute;
export interface ScreenAttribute extends CommonMethod {
}
export class ArkScreenStyle extends ArkCommonMethodStyle implements ScreenAttribute {
}
export class ArkScreenComponent extends ArkCommonMethodComponent implements ScreenAttribute {
    getPeer(): ArkScreenPeer {
        return (this.peer as ArkScreenPeer)
    }
    public setScreenOptions(screenId: number): this {
        if (this.checkPriority("setScreenOptions")) {
            const screenId_casted = screenId as (number)
            this.getPeer()?.setScreenOptionsAttribute(screenId_casted)
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
export function Screen(
    /** @memo */
    style: ((attributes: ScreenAttribute) => void) | undefined,
    screenId: number,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkScreenComponent()
    })
    NodeAttach<ArkScreenPeer>((): ArkScreenPeer => ArkScreenPeer.create(receiver), (_: ArkScreenPeer) => {
        receiver.setScreenOptions(screenId)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
