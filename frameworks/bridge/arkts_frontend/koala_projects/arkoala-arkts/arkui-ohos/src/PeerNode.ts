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

import { int32 } from "@koalaui/common"
import { Disposable, IncrementalNode, scheduleCallback } from "@koalaui/runtime"
import { NativePeerNode } from "./NativePeerNode"
import { nullptr, pointer } from "@koalaui/interop"
import { ArkRootPeer } from "./generated/peers/ArkStaticComponentsPeer"

export const PeerNodeType = 11
export const LazyForEachType = 13
const INITIAL_ID = 1000

export class PeerNode extends IncrementalNode {
    static generateRootPeer() {
        return ArkRootPeer.create()
    }
    peer: NativePeerNode
    protected static currentId: int32 = INITIAL_ID
    static nextId(): int32 { return PeerNode.currentId++ }
    private id: int32
    private _onReuse?: () => void
    private _onRecycle?: () => void
    // Pool to store recycled child scopes, grouped by type
    private _reusePool?: Map<string, Array<Disposable>>
    private _reusable: boolean = false

    setId(id: int32) {
        PeerNode.peerNodeMap.delete(this.id)
        this.id = id
        PeerNode.peerNodeMap.set(this.id, this)
    }

    getId(): int32 {
        return this.id
    }

    onReuse(): void {
        if (!this._reusable) {
            this._reusable = true // becomes reusable after initial mount
        } else {
            this._onReuse?.() // could change states
        }
        // traverse subtree to notify all children
        for (let child = this.firstChild; child; child = child!.nextSibling) {
            if (child instanceof PeerNode)
                (child as PeerNode)!.onReuse()
        }
    }

    onRecycle(): void {
        this._onRecycle?.()
        // traverse subtree to notify all children
        for (let child = this.firstChild; child; child = child!.nextSibling) {
            if (child instanceof PeerNode)
                (child as PeerNode)!.onRecycle()
        }
    }

    override reuse(reuseKey: string): Disposable | undefined {
        if (this._reusePool === undefined)
            return undefined
        if (this._reusePool!.has(reuseKey)) {
            const scopes = this._reusePool!.get(reuseKey)!;
            return scopes.pop();
        }
        return undefined;
    }

    override recycle(reuseKey: string, child: Disposable): boolean {
        if (!this._reusePool)
            this._reusePool = new Map<string, Array<Disposable>>()
        if (!this._reusePool!.has(reuseKey)) {
            this._reusePool!.set(reuseKey, new Array<Disposable>());
        }
        this._reusePool!.get(reuseKey)!.push(child);
        return true
    }

    setOnRecycle(cb: () => void): void {
        this._onRecycle = cb
    }
    setOnReuse(cb: () => void): void {
        this._onReuse = cb
    }

    private static peerNodeMap = new Map<number, PeerNode>()

    static findPeerByNativeId(id: number): PeerNode | undefined {
        return PeerNode.peerNodeMap.get(id)
    }
    readonly name: string
    private insertMark: pointer = nullptr
    private insertDirection: int32 = 0

    setInsertMark(mark: pointer, upDirection: boolean) {
        this.insertMark = mark
        this.insertDirection = upDirection ? 0 : 1
    }

    constructor(peerPtr: pointer, id: int32, name: string, flags: int32) {
        super(PeerNodeType)
        this.id = id
        this.peer = NativePeerNode.create(this, peerPtr, flags)
        PeerNode.peerNodeMap.set(this.id, this)
        this.onChildInserted = (child: IncrementalNode) => {
            // TODO: rework to avoid search
            let peer = findPeerNode(child)
            if (peer) {
                let peerPtr = peer.peer.ptr
                if (this.insertMark != nullptr) {
                    if (this.insertDirection == 0) {
                        this.peer.insertChildBefore(peerPtr, this.insertMark)
                    } else {
                        this.peer.insertChildAfter(peerPtr, this.insertMark)
                    }
                    this.insertMark = peerPtr
                    return
                }
                // Find the closest peer node backward.
                let sibling: PeerNode | undefined = undefined
                for (let node = child.previousSibling; node; node = node!.previousSibling) {
                    if (node!.isKind(PeerNodeType)) {
                        sibling = node as PeerNode
                        break
                    }
                }
                this.peer.insertChildAfter(peerPtr, sibling?.peer?.ptr ?? nullptr)
                scheduleCallback(() => peer!.onReuse())
            }
        }
        this.onChildRemoved = (child: IncrementalNode) => {
            if (child.isKind(PeerNodeType) && !child.disposed) {
                const peer = child as PeerNode
                peer.onRecycle()
            }
        }
        this.name = name
    }
    applyAttributes(attrs: Object) { }

    override dispose(): void {
        let parent = this.parent
        if (parent != undefined && parent.isKind(PeerNodeType)) {
            (parent as PeerNode).peer.removeChild(this.peer.ptr)
        }
        this.peer.close()
        PeerNode.peerNodeMap.delete(this.id)
        this._reusePool?.forEach((value: Array<Disposable>) =>
            value.forEach((disposable: Disposable) => disposable.dispose())
        )
        this._reusePool = undefined
        this._onRecycle = undefined
        this._onReuse = undefined
        super.dispose()
    }
}

function findPeerNode(node: IncrementalNode): PeerNode | undefined {
    if (node.isKind(PeerNodeType)) return node as PeerNode
    for (let child = node.firstChild; child; child = child!.nextSibling) {
        let peer = findPeerNode(child!)
        if (peer) return peer
    }
    return undefined
}
