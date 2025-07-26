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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32 } from "@koalaui/common"
import { NodeAttach, remember } from "@koalaui/runtime"
import { PeerNode } from "../PeerNode"
import { ComponentBase } from "./../ComponentBase"
import { Serializer } from "./peers/Serializer"
import { Content } from "../Content"
import { NodeContent } from "../NodeContent"
import { ArkUIAniModule } from "arkui.ani"

export interface UIContentSlotAttribute {
}
export class ArkContentSlotPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkContentSlotPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIAniModule._ContentSlot_construct(peerId)
        const _peer = new ArkContentSlotPeer(_peerPtr, peerId, "ContentSlot", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setContentSlotOptionsAttribute(content?: Content): void {
        let content_type: int32 = RuntimeType.UNDEFINED
        content_type = runtimeType(content)
        if ((RuntimeType.UNDEFINED) != (content_type)) {
            const content_value = content as NodeContent
            ArkUIAniModule._ContentSlotInterface_setContentSlotOptions(this.peer.ptr, toPeerPtr(content_value))
        } else {
            ArkUIAniModule._ContentSlotInterface_setContentSlotOptions(this.peer.ptr, nullptr)
        }
    }
}
/** @memo:stable */
export class ArkContentSlotComponent extends ComponentBase implements UIContentSlotAttribute {
    getPeer(): ArkContentSlotPeer {
        return (this.peer as ArkContentSlotPeer)
    }
    /** @memo */
    public setContentSlotOptions(content?: Content): this {
        if (this.checkPriority("setContentSlotOptions")) {
            const content_type = runtimeType(content)
            if ((RuntimeType.OBJECT == content_type) || (RuntimeType.UNDEFINED == content_type)) {
                const content_casted = content as (Content | undefined)
                this.getPeer()?.setContentSlotOptionsAttribute(content_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
}
/** @memo */
export function ContentSlot(
    /** @memo */
    style: ((attributes: UIContentSlotAttribute) => void) | undefined,
    content?: Content,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkContentSlotComponent()
    })
    NodeAttach<ArkContentSlotPeer>((): ArkContentSlotPeer => ArkContentSlotPeer.create(receiver), (_: ArkContentSlotPeer) => {
        receiver.setContentSlotOptions(content)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
