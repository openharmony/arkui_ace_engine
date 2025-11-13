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

import { int32, KoalaCallsiteKey } from "@koalaui/common"
import { Disposable, IncrementalNode, scheduleCallback, GlobalStateManager, MutableState, mutableState } from "@koalaui/runtime"
import { NativePeerNode } from "./NativePeerNode"
import { nullptr, pointer } from "@koalaui/interop"
import { ArkRootPeer, StateStylesOps } from "#generated"
import { ReusablePool } from "./ReusablePool"
import { StateUpdateLoop } from "./stateManagement"  
import { RecordData } from "@ohos.base"
import { ArkUIAniModule } from 'arkui.ani';

export const PeerNodeType = 11
export const RootPeerType = 33
export const LazyForEachType = 13
export const LazyItemNodeType = 17 // LazyItems are detached node trees that are stored privately in LazyForEach
export const BuilderRootNodeType = 19 // BuilderRootNode are detached node trees that are stored privately in BuilderNode
const INITIAL_ID = 0
const ID_CAPACITY = 10000
const UNINITIALIZE_CURSOR = -1

export class PeerNode extends IncrementalNode {
    static generateRootPeer() {
        return ArkRootPeer.create(undefined)
    }
    peer: NativePeerNode
    protected static currentId: int32 = INITIAL_ID
    protected static cursor: int32 = UNINITIALIZE_CURSOR
    private static staticLock = new Mutex()
    static nextId(): int32 {
        PeerNode.staticLock.lock();
        if (PeerNode.cursor === UNINITIALIZE_CURSOR || PeerNode.currentId >= PeerNode.cursor + ID_CAPACITY) {
            PeerNode.cursor = ArkUIAniModule._RequireArkoalaNodeId(ID_CAPACITY)
            PeerNode.currentId = PeerNode.cursor
        }
        let resId = PeerNode.currentId++;
        PeerNode.staticLock.unlock();
        return resId;
    }
    private id: int32
    private _onReuse?: (param?: RecordData) => void
    private _onRecycle?: () => void
    // Pool to store recycled child scopes, grouped by type
    private _reusePool?: Map<string, ReusablePool>
    public reusable: boolean = false
    private _uiStateStyle?: MutableState<int32>;
    private _disabledStateUpdates: MutableState<boolean> = GlobalStateManager.instance.mutableState<boolean>(false, true);

    getPeerPtr(): pointer {
        return this.peer.ptr
    }
    public getStateStyleMutable(): MutableState<int32> | undefined {
        return this._uiStateStyle;
    }
    override get disabledStateUpdates(): boolean {
        return this._disabledStateUpdates.value
    }
    set disabledStateUpdates(disabled: boolean) {
        this._disabledStateUpdates.value = disabled
    }
    setId(id: int32) {
        PeerNode.updatePeerNodeMap()
        PeerNode.peerNodeMap.delete(this.id)
        this.id = id
        PeerNode.peerNodeMap.set(this.id, this)
    }

    getId(): int32 {
        return this.id
    }

    onReuse(needRecurs: boolean, param?: RecordData): void {
        if (!this.reusable && !needRecurs) {
            return
        }
        if (this._onReuse && !needRecurs) {
            scheduleCallback(() => { this._onReuse?.(param) }) // could change states
        } else if (needRecurs) {
            this._onReuse?.(param);
            for (let child = this.firstChild; child; child = child!.nextSibling) {
                if (child?.isKind(PeerNodeType)) {
                    (child as PeerNode)!.onReuse(needRecurs, param);
                }
            }
        }
    }

    onRecycle(needRecurs?: boolean): void {
        this._onRecycle?.()
        if (needRecurs) {
            for (let child = this.firstChild; child; child = child!.nextSibling) {
                if (child?.isKind(PeerNodeType)) {
                    (child as PeerNode)!.onRecycle(needRecurs);
                }
            }
        }
    }

    private isRootNode() {
        return this instanceof ArkRootPeer
    }

    /* reuse and recycle object on RootPeers */
    override reuse(reuseKey: string, id: KoalaCallsiteKey): Disposable | undefined {
        if (!this.isKind(RootPeerType))
            return this.parent?.reuse(reuseKey, id)

        if (this._reusePool === undefined)
            return undefined
        if (this._reusePool!.has(reuseKey)) {
            const pool = this._reusePool!.get(reuseKey)!;
            return pool.get();
        }
        return undefined;
    }

    override recycle(reuseKey: string, child: Disposable, id: KoalaCallsiteKey): boolean {
        if (!this.isKind(RootPeerType)) {
            return this.parent?.recycle(reuseKey, child, id) ?? false
        }
        if (!this._reusePool)
            this._reusePool = new Map<string, ReusablePool>()
        if (!this._reusePool!.has(reuseKey)) {
            this._reusePool!.set(reuseKey, new ReusablePool());
        }
        this._reusePool!.get(reuseKey)!.put(child);
        return true
    }

    override incrementalUpdateDone(parent?: IncrementalNode) {
        super.incrementalUpdateDone(parent)
        ArkUIAniModule._UINode_OnUpdateDone(this.peer.ptr)
    }

    setReusePoolSize(size: int32, reuseKey: string): void {
        if (size < 0) {
            return
        }
        if (!this.isKind(RootPeerType)) {
            if (this.parent?.isKind(PeerNodeType)) {
                (this.parent! as PeerNode).setReusePoolSize(size, reuseKey)
            }
            return
        }
        if (!this._reusePool) {
            this._reusePool = new Map<string, ReusablePool>()
        }
        if (!this._reusePool?.has(reuseKey)) {
            this._reusePool?.set(reuseKey, new ReusablePool())
        }
        this._reusePool?.get(reuseKey)?.setMaxSize(size)
    }

    setOnRecycle(cb: () => void): void {
        this._onRecycle = cb
    }
    setOnReuse(cb: (param?: RecordData) => void): void {
        this._onReuse = cb
    }

    private static peerNodeMap = new containers.ConcurrentHashMap<number, PeerNode>()

    // peerNodeRawTail needs for perf optimizations. Insert into array much faster
    private static peerNodeRawTail = new Array<PeerNode>()

    private static updatePeerNodeMap() {
        if (PeerNode.peerNodeRawTail.length === 0)
            return

        PeerNode.peerNodeRawTail.forEach((peer: PeerNode) => {
            PeerNode.peerNodeMap.set(peer.id, peer)
        })

        PeerNode.peerNodeRawTail = []
    }

    static findPeerByNativeId(id: number): PeerNode | undefined {
        PeerNode.updatePeerNodeMap()
        return PeerNode.peerNodeMap.get(id)
    }
    readonly name: string
    private insertMark: pointer = nullptr
    private insertDirection: int32 = 0

    setInsertMark(mark: pointer, upDirection: boolean) {
        this.insertMark = mark
        this.insertDirection = upDirection ? 0 : 1
    }

    constructor(peerPtr: pointer, id: int32, name: string, flags: int32, derivedNodeType?: int32) {
        super(derivedNodeType ?? PeerNodeType)
        this.id = id
        this.peer = NativePeerNode.create(this, peerPtr, flags)
        PeerNode.staticLock.lock()
        PeerNode.peerNodeRawTail.push(this)
        PeerNode.staticLock.unlock()
        this.onChildInserted = (child: IncrementalNode) => {
            // Improve: rework to avoid search
            let peer = findPeerNode(child)
            if (peer) {
                if (peer.reusable) {
                    peer!.onReuse(false)
                } else {
                    peer.reusable = true // becomes reusable after initial mount
                }
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
                // Find the closest peer node forward.
                let sibling: PeerNode | undefined = findSiblingPeerNode(child, true)
                if (sibling === undefined) {
                    // Add to the end (common case!).
                    this.peer.addChild(peerPtr)
                } else {
                    // Insert child in the middle.
                    this.peer.insertChildBefore(peerPtr, sibling?.peer?.ptr ?? nullptr)
                }
            }
        }
        this.onChildRemoved = (child: IncrementalNode) => {
            if (child.isKind(PeerNodeType) && !child.disposed) {
                const peer = child as PeerNode
                peer.onRecycle()
                this.peer.removeChild(peer.peer.ptr)
            }
        }
        this.name = name

        this._uiStateStyle = undefined
    }
    applyAttributes(attrs: Object) { }

    override dispose(): void {
        let parent = this.parent
        if (parent != undefined && parent.isKind(PeerNodeType)) {
            const node = parent as PeerNode
            if (!node.disposed) node.peer.removeChild(this.peer.ptr)
        }
        this.peer.close()
        PeerNode.updatePeerNodeMap()
        PeerNode.peerNodeMap.delete(this.id)
        this._reusePool?.forEach((pool: ReusablePool) =>
            pool.dispose()
        )
        this._reusePool = undefined
        this._onRecycle = undefined
        this._onReuse = undefined
        super.dispose()
    }

    public getOrCreateStateStyleMutable(curState: int32 = 15): MutableState<int32> | undefined {
        if (this._uiStateStyle !== undefined) {
            return this._uiStateStyle!;
        }
        else {
            const manager = GlobalStateManager.instance
            this._uiStateStyle = manager.mutableState<int32>(0 as int32, true)
            StateStylesOps.onStateStyleChange(this.getPeerPtr(), (state: int32) => {
                this._uiStateStyle!.value = state
            }, curState)
            return this._uiStateStyle!;
        }
    }
}

export function findPeerNode(node: IncrementalNode): PeerNode | undefined {
    if (node.isKind(PeerNodeType)) return node as PeerNode
    for (let child = node.firstChild; child; child = child!.nextSibling) {
        let peer = findPeerNode(child!)
        if (peer) return peer
    }
    return undefined
}

function findSiblingPeerNode(node: IncrementalNode, forward: boolean): PeerNode | undefined {
    if (forward) {
        for (let sibling = node.nextSibling; sibling; sibling = sibling!.nextSibling) {
            if (sibling!.isKind(PeerNodeType)) {
                return sibling as PeerNode
            }
        }
    } else {
        for (let sibling = node.previousSibling; sibling; sibling = sibling!.previousSibling) {
            if (sibling!.isKind(PeerNodeType)) {
                return sibling as PeerNode
            }
        }
    }
    return undefined
}
