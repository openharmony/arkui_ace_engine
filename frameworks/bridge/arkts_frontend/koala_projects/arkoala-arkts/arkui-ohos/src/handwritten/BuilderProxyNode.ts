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
import { KPointer } from "@koalaui/interop"
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
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkBuilderProxyNodePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIAniModule._BuilderProxyNode_Construct(peerId)
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
}
