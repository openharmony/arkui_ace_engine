/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { ArkUIGeneratedNativeModule } from "#components"
import { KPointer, SerializerBase, RuntimeType } from "@koalaui/interop"
import { int32 } from "@koalaui/common"
import { PeerNode } from "../PeerNode"
import { ComponentBase } from "../ComponentBase"
import { ArkUIAniModule } from "arkui.ani"

export interface UIContentSlotAttribute {
}
export class ArkBuilderProxyNodePeer extends PeerNode {
    private _hasChild:boolean;
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(
        component: ComponentBase | undefined,
        isWeak: boolean = true,
        flags: int32 = 0
    ): ArkBuilderProxyNodePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = isWeak
            ? ArkUIAniModule._BuilderProxyNode_Mock_Construct(peerId)
            : ArkUIAniModule._BuilderProxyNode_Construct(peerId)
        const _peer = new ArkBuilderProxyNodePeer(_peerPtr, peerId, "BuilderProxyNode", flags)
        component?.setPeer(_peer)
        return _peer
    }
    set hasChild(hasChild:boolean){
        this._hasChild = hasChild;
    }
    get hasChild():boolean{
        return this._hasChild;
    }
    getParentViewId(): double {
        return Int.toDouble(ArkUIAniModule.__BuilderNode_GetParentViewId(this.getPeerPtr()));
    }
    setOnAttach(value: () => void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CommonMethod_setOnAttach(
            this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnDetach(value: () => void): void {
        const thisSerializer: SerializerBase = SerializerBase.hold()
        if (value !== undefined) {
            thisSerializer.writeInt8(RuntimeType.OBJECT)
            const valueTmpValue = value!
            thisSerializer.holdAndWriteCallback(valueTmpValue)
        } else {
            thisSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        ArkUIGeneratedNativeModule._CommonMethod_setOnDetach(
            this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    public registerDestroyEvent(event: (nodeId: int) => void) {
        ArkUIAniModule._SetOnNodeDestroyEvent(this.getPeerPtr(), event);
    }
}