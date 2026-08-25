/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

import { IncrementalNode, Disposable, scheduleCallback, callScheduledCallbacks, GetReusableScopeNode } from '@koalaui/runtime'
import { int32, KoalaCallsiteKey } from '@koalaui/common'
import { nullptr, pointer, KPointer } from '@koalaui/interop'
import { PeerNode, LazyItemNodeType, PeerNodeType, findPeerNode } from '../PeerNode'
import { ReusablePool } from '../ReusablePool'
import { ArkUIAniModule } from '../ani/arkts/ArkUIAniModule'
import { IExtendableComponent } from '../component/extendableComponent'

export class NodeHolder {
    node?: PeerNode
}

export class SyntaxItemPeer extends PeerNode {
    public static create(): SyntaxItemPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIAniModule._SyntaxItem_Construct(peerId)
        if (!_peerPtr) {
            throw new Error(`Failed to create SyntaxItemPeer with id: ${peerId}`)
        }
        return new SyntaxItemPeer(_peerPtr, peerId, 'SyntaxItem')
    }

    public component?: IExtendableComponent;
    public isCustomComponent: boolean = false;
    getParentNodeWhenRecycle(nodeRef?: IncrementalNode): IncrementalNode | undefined {
        if (this.isCustomComponent) {
            const node = this.component?.__getParentNode__Internal();
            return node;
        } else {
            return nodeRef;
        }
    }

    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    getRid(): int32 {
        // Repeat rid reuses the existing peer/node id so frontend and backend stay naturally aligned.
        return this.getId()
    }
}

export class ForEachNodePeer extends PeerNode {
    public static create(isRepeat: boolean = false): ForEachNodePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIAniModule._ForEachNode_Construct(peerId, isRepeat)
        if (!_peerPtr) {
            throw new Error(`Failed to create ForEachNodePeer with id: ${peerId}`)
        }
        return new ForEachNodePeer(_peerPtr, peerId, isRepeat ? 'Repeat' : 'ForEach', 0, isRepeat)
    }

    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0,
        allowSiblingReorder: boolean = false) {
        super(peerPtr, id, name, flags, PeerNodeType, allowSiblingReorder)
    }
}

export class LazyNodePeer extends PeerNode {
    private _reusePool?: Map<string, ReusablePool> = undefined
    private _repeatTemplatePoolSize?: Map<string, int32> = undefined
    private _repeatReusePlan?: Map<string, Array<string | undefined>> = undefined
    private _repeatActiveRangeReuseKeys?: Map<int32, string> = undefined

    public static create(isRepeat: boolean = false): LazyNodePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ArkUIAniModule._LazyForEachNode_Construct(peerId, isRepeat)
        if (!_peerPtr) {
            throw new Error(`Failed to create LazyNodePeer with id: ${peerId}`)
        }
        return new LazyNodePeer(_peerPtr, peerId, isRepeat ? 'Repeat' : 'LazyForEach')
    }

    protected constructor(peerPtr: KPointer, id: int32, name: string = '', flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    override reuse(reuseKey: string, id: KoalaCallsiteKey): Disposable | undefined {
        const plannedReuseKeys = this._repeatReusePlan?.get(reuseKey)
        if (plannedReuseKeys) {
            while (plannedReuseKeys.length > 0) {
                const plannedReuseKey = plannedReuseKeys.shift()
                const candidate = plannedReuseKey ? this.tryReuseFromPool(plannedReuseKey, reuseKey) : undefined
                if (candidate) {
                    if (plannedReuseKeys.length === 0) {
                        this._repeatReusePlan?.delete(reuseKey)
                    }
                    return candidate
                }
            }
            this._repeatReusePlan?.delete(reuseKey)
        }
        if (!this._reusePool) {
            return undefined
        }
        return this.tryReuseFromPool(reuseKey, reuseKey)
    }

    override recycle(reuseKey: string, child: Disposable, id: KoalaCallsiteKey): boolean {
        console.log(`GlobalReuse: SyntaxNodeBase.recycle disposing=${this.disposing} hasParent=${this.parent !== undefined}`);
        if (this.disposing) { // do not recycle if repeat is disposed
            // When this container is disposing, try to delegate to the parent
            // so that reusable children can still be recycled to an ancestor's
            // GlobalReusePool instead of being destroyed.
            if (this.parent !== undefined) {
                return this.parent!.recycle(reuseKey, child, id);
            }
            return false
        }
        const templateKey = this.extractRepeatTemplateKey(reuseKey)
        if (templateKey && this._repeatTemplatePoolSize) {
            const maxSize = this._repeatTemplatePoolSize!.get(templateKey)
            if (maxSize !== undefined) {
                let templateSize = 0
                this._reusePool?.forEach((pool, candidateReuseKey) => {
                    if (this.extractRepeatTemplateKey(candidateReuseKey) === templateKey) {
                        templateSize += pool.size
                    }
                })
                if (templateSize >= maxSize) {
                    return false
                }
            }
        }
        if (!this._reusePool) {
            this._reusePool = new Map<string, ReusablePool>()
        }
        if (!this._reusePool!.has(reuseKey)) {
            this._reusePool!.set(reuseKey, new ReusablePool())
        }
        this._reusePool!.get(reuseKey)!.put(child)
        return true
    }

    public override clearReusePool(): void {
        if (!this._reusePool) {
            return
        }

        this._reusePool!.forEach((pool: ReusablePool) => {
            scheduleCallback(() => {
                pool!.dispose()
            })
        })
        this._reusePool!.clear()
        this._reusePool = undefined
        callScheduledCallbacks()
    }

    setRepeatTemplatePoolSize(size: int32, templateKey: string): void {
        if (size < 0) {
            return
        }
        if (!this._repeatTemplatePoolSize) {
            this._repeatTemplatePoolSize = new Map<string, int32>()
        }
        this._repeatTemplatePoolSize!.set(templateKey, size)
    }

    setRepeatActiveRangeReuseKeys(activeRangeReuseKeys: Map<int32, string>): void {
        this._repeatActiveRangeReuseKeys = new Map<int32, string>(activeRangeReuseKeys)
    }

    getRepeatActiveRangeReuseKeys(): Map<int32, string> {
        return this._repeatActiveRangeReuseKeys ? new Map<int32, string>(this._repeatActiveRangeReuseKeys) :
            new Map<int32, string>()
    }

    isRepeatNodeChildInAnimation(rid: int32): boolean {
        return ArkUIAniModule._Repeat_IsChildInAnimation(this.getPeerPtr(), rid) !== 0
    }

    isRepeatNodeChildOnMainTree(rid: int32): boolean {
        return ArkUIAniModule._Repeat_IsChildOnMainTree(this.getPeerPtr(), rid) !== 0
    }

    isRepeatNodeAllowAnimation(): boolean {
        return ArkUIAniModule._Repeat_IsAllowAnimation(this.getPeerPtr()) !== 0
    }

    isRepeatNodeImplicitAnimationOpen(): boolean {
        return ArkUIAniModule._Repeat_IsImplicitAnimationOpen(this.getPeerPtr()) !== 0
    }

    prepareRepeatReusePlan(targetReuseKeys: string[]): void {
        // Record how many reusable nodes are currently available for each reuseKey.
        // Only pools with at least one node are considered for reuse planning.
        const available = new Map<string, int32>()
        this._reusePool?.forEach((pool, reuseKey) => {
            if (pool.size > 0) {
                available.set(reuseKey, pool.size)
            }
        })
        // The final plan maps each target reuseKey to the source reuseKey(s) it should take from.
        const plan = new Map<string, Array<string | undefined>>()
        // Keep target keys that cannot be satisfied by exact-key matching for the fallback pass.
        const unmatchedTargets: string[] = []

        // First pass: consume exact-key matches first so the best reuse is always used before fallback.
        targetReuseKeys.forEach((targetReuseKey) => {
            const count = available.get(targetReuseKey) ?? 0
            if (count > 0) {
                if (!plan.has(targetReuseKey)) {
                    plan.set(targetReuseKey, [])
                }
                plan.get(targetReuseKey)!.push(targetReuseKey)
                available.set(targetReuseKey, count - 1)
            } else {
                unmatchedTargets.push(targetReuseKey)
            }
        })

        // Second pass: if no exact match exists, try to reuse any node from the same Repeat template.
        unmatchedTargets.forEach((targetReuseKey) => {
            const templateKey = this.extractRepeatTemplateKey(targetReuseKey)
            if (!templateKey) {
                // No template key means this target cannot be reused from another key.
                if (!plan.has(targetReuseKey)) {
                    plan.set(targetReuseKey, [])
                }
                plan.get(targetReuseKey)!.push(undefined)
                return
            }
            let matchedReuseKey: string | undefined = undefined
            for (const entry of available) {
                const candidateReuseKey = entry[0]
                const count = entry[1]
                if (count <= 0 || candidateReuseKey === targetReuseKey) {
                    continue
                }
                if (this.extractRepeatTemplateKey(candidateReuseKey) === templateKey) {
                    // Found a compatible source key in the same template; consume one slot from it.
                    matchedReuseKey = candidateReuseKey
                    available.set(candidateReuseKey, count - 1)
                    break
                }
            }
            if (!plan.has(targetReuseKey)) {
                plan.set(targetReuseKey, [])
            }
            // undefined means this target still has no reusable source after fallback search.
            plan.get(targetReuseKey)!.push(matchedReuseKey)
        })

        this._repeatReusePlan = plan
    }

    private extractRepeatTemplateKey(reuseKey: string): string | undefined {
        const marker = '@Repeat@'
        const markerIndex = reuseKey.indexOf(marker)
        if (markerIndex < 0) {
            return undefined
        }
        return reuseKey.substring(0, markerIndex)
    }

    private tryReuseFromPool(sourceReuseKey: string, targetReuseKey: string): Disposable | undefined {
        const pool = this._reusePool?.get(sourceReuseKey)
        if (!pool) {
            return undefined
        }
        const skipped: Disposable[] = []
        while (pool.size > 0) {
            const candidate = pool.getLastNode()
            if (!candidate) {
                skipped.forEach((item) => pool.put(item))
                return undefined
            }
            if (this.canReuseCandidate(candidate, sourceReuseKey, targetReuseKey)) {
                skipped.forEach((item) => pool.put(item))
                return candidate
            }
            skipped.push(candidate)
        }
        skipped.forEach((item) => pool.put(item))
        return undefined
    }

    private canReuseCandidate(candidate: Disposable, sourceReuseKey: string, targetReuseKey: string): boolean {
        const candidateNode = GetReusableScopeNode(candidate)
        if (!(candidateNode instanceof SyntaxItemPeer)) {
            return false
        }
        const rid = candidateNode.getRid()
        const sameKey = sourceReuseKey === targetReuseKey
        const isOnMainTree = this.isRepeatNodeChildOnMainTree(rid)
        const isInAnimation = this.isRepeatNodeChildInAnimation(rid)
        if (this.isRepeatNodeImplicitAnimationOpen()) {
            return sameKey ? isOnMainTree : false;
        }
        if (sameKey) {
            return !(!isOnMainTree && isInAnimation)
        }
        return !isInAnimation
    }

    hasReusableCandidate(key: string): boolean {
        const plannedReuseKeys = this._repeatReusePlan?.get(key)
        if (!plannedReuseKeys || plannedReuseKeys.length === 0 || plannedReuseKeys[0] !== key) {
            return false
        }
        const pool = this._reusePool?.get(key)
        if (!pool || pool.size === 0) {
            return false
        }
        const candidate = pool.getLastNode()
        if (!candidate) {
            return false
        }
        const candidateNode = GetReusableScopeNode(candidate)
        if (!(candidateNode instanceof SyntaxItemPeer)) {
            return false
        }
        const rid = candidateNode.getRid()
        const isOnMainTree = this.isRepeatNodeChildOnMainTree(rid)
        pool.put(candidate)
        return isOnMainTree
    }

    override dispose(): void {
        this._repeatTemplatePoolSize = undefined
        this._repeatReusePlan = undefined
        this._repeatActiveRangeReuseKeys = undefined
        super.dispose()
    }
}

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
            if (peer.reusable) {
                peer.onReuse(false)
            } else {
                peer.reusable = true
            } 
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
        if (!this.firstChild) {
            return nullptr
        }
        const peer = findPeerNode(this.firstChild!)
        return peer?.isKind(PeerNodeType) ? (peer as PeerNode).getPeerPtr() : nullptr
    }
}
