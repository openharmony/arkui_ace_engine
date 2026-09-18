/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { int32 } from "@koalaui/common"
import { KPointer } from "@koalaui/interop"
import { ArkUIAniModule } from "arkui.ani"
import { PeerNode } from "../PeerNode"

export class ArkInteropProxyNodePeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    public static create(id: int32, flags: int32 = 0): ArkInteropProxyNodePeer {
        const peerPtr = ArkUIAniModule._InteropProxyNode_Construct(id)
        return new ArkInteropProxyNodePeer(peerPtr, id, 'InteropProxyNode', flags)
    }

    public registerDestroyEvent(event: (nodeId: int) => void): void {
        ArkUIAniModule._SetOnNodeDestroyEvent(this.getPeerPtr(), event)
    }
}
