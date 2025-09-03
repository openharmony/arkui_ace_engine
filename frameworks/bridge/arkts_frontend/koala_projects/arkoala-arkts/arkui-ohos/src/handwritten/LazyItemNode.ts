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

import { IncrementalNode, Disposable } from "@koalaui/runtime"
import { PeerNode, LazyItemNodeType, PeerNodeType } from "../PeerNode"
import { KoalaCallsiteKey } from "@koalaui/common"
import { nullptr, pointer } from "@koalaui/interop"

/**
 * LazyItemNode is the root node of an item in LazyForEach.
 * LazyForEach items are never attached to the main tree, but stored in a separate pool in LazyForEach.
 */
export class LazyItemNode extends IncrementalNode {
    constructor(parent: PeerNode) {
        super(LazyItemNodeType)
        this._container = parent
        this.onChildInserted = (node: IncrementalNode) => {
            if (!node.isKind(PeerNodeType)) {
                return
            }
            const peer = node as PeerNode
            peer.reusable ? peer.onReuse() : peer.reusable = true
        }
        this.onChildRemoved = (node: IncrementalNode) => {
            if (!node.isKind(PeerNodeType)) {
                return
            }
            const peer = node as PeerNode
            if (!peer.disposed) {
                peer.onRecycle()
            }
        }
    }
    private _container: PeerNode

    /**
     * Supports Reusable through redirecting requests to the parent node.
     */
    reuse(reuseKey: string, id: KoalaCallsiteKey): Disposable | undefined {
        return this._container.reuse(reuseKey, id)
    }

    recycle(reuseKey: string, child: Disposable, id: KoalaCallsiteKey): boolean {
        return this._container.recycle(reuseKey, child, id)
    }

    getPeerPtr(): pointer {
        const peer = this.firstChild
        return peer?.isKind(PeerNodeType) ? (peer as PeerNode).getPeerPtr() : nullptr
    }
}
