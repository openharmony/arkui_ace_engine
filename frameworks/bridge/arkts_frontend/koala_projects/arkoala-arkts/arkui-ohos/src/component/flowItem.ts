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

export class ArkFlowItemPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkFlowItemPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._FlowItem_construct(peerId, flags)
        const _peer  = new ArkFlowItemPeer(_peerPtr, peerId, "FlowItem", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setFlowItemOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._FlowItemInterface_setFlowItemOptions(this.peer.ptr)
    }
}
export type FlowItemInterface = () => FlowItemAttribute;
export interface FlowItemAttribute extends CommonMethod {
}
export class ArkFlowItemStyle extends ArkCommonMethodStyle implements FlowItemAttribute {
}
export class ArkFlowItemComponent extends ArkCommonMethodComponent implements FlowItemAttribute {
    getPeer(): ArkFlowItemPeer {
        return (this.peer as ArkFlowItemPeer)
    }
    public setFlowItemOptions(): this {
        if (this.checkPriority("setFlowItemOptions")) {
            this.getPeer()?.setFlowItemOptionsAttribute()
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
export function FlowItem(
    /** @memo */
    style: ((attributes: FlowItemAttribute) => void) | undefined,
    
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkFlowItemComponent()
    })
    NodeAttach<ArkFlowItemPeer>((): ArkFlowItemPeer => ArkFlowItemPeer.create(receiver), (_: ArkFlowItemPeer) => {
        receiver.setFlowItemOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
