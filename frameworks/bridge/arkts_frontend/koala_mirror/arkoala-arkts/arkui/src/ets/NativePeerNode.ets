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

import { int32 } from "@koalaui/common"
import { pointer } from "@koalaui/interop"
import { Finalizable } from "@koalaui/interop"
import { ArkUINativeModule } from "#components"
import { PeerNode } from "./PeerNode"

export class NativePeerNode extends Finalizable {
    constructor(peer: PeerNode, ptr: pointer) {
        super(ptr, ArkUINativeModule._GetNodeFinalizer())
    }

    static create(peer: PeerNode, peerPtr: pointer, flags: int32): NativePeerNode {
        return new NativePeerNode(peer, peerPtr)
    }

    addChild(node: pointer) {
        ArkUINativeModule._AddChild(this.ptr, node)
    }
    removeChild(node: pointer) {
        ArkUINativeModule._RemoveChild(this.ptr, node)
    }
    insertChildBefore(node: pointer, sibling: pointer) {
        ArkUINativeModule._InsertChildBefore(this.ptr, node, sibling)
    }
    insertChildAfter(node: pointer, sibling: pointer) {
        ArkUINativeModule._InsertChildAfter(this.ptr, node, sibling)
    }
    insertChildAt(node: pointer, position: int32) {
        ArkUINativeModule._InsertChildAt(this.ptr, node, position)
    }
    dumpTree() {
        ArkUINativeModule._DumpTreeNode(this.ptr)
    }
}
