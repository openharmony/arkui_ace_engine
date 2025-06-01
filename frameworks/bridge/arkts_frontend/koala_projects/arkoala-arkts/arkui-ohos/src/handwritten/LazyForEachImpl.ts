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

import { __id, ComputableState, contextNode, GlobalStateManager, Disposable, memoEntry2, remember, rememberDisposable, rememberMutableState, StateContext, DataNode, memo, scheduleCallback } from "@koalaui/runtime";
import { pointer } from "@koalaui/interop";
import { LazyForEachType, PeerNode, PeerNodeType } from "../PeerNode";
import { InternalListener } from "../DataChangeListener";
import { setNeedCreate } from "../ArkComponentRoot";
import { int32, KoalaCallsiteKey } from "@koalaui/common";
import { IDataSource } from "../component/lazyForEach";
import { LazyForEachOps } from "../component";
import { LazyItemNode } from "./LazyItemNode";

let globalLazyItems: Set<ComputableState<LazyItemNode>> = new Set<ComputableState<LazyItemNode>>()
export function updateLazyItems() {
    for (let node of globalLazyItems) {
        node.value
    }
}

/** @memo */
export function LazyForEachImpl<T>(dataSource: IDataSource<T>,
    /** @memo */
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
) {
    const parent = contextNode<PeerNode>()
    let pool = rememberDisposable(() => new LazyItemPool(parent), (pool?: LazyItemPool) => {
        pool?.dispose()
    })
    let changeCounter = rememberMutableState(0)
    let listener = remember(() => {
        let res = new InternalListener(parent.peer.ptr, changeCounter)
        dataSource.registerDataChangeListener(res)
        return res
    })
    changeCounter.value // subscribe
    const changeIndex = listener.flush(0) // first item index that's affected by DataChange
    if (changeIndex < Number.POSITIVE_INFINITY) {
        scheduleCallback(() => {
            pool.pruneBy((index: int32) => index >= changeIndex)
        })
    }

    /**
     * provide totalCount and callbacks to the backend
     */
    let createCallback = (index: int32) => {
        return pool.getOrCreate(index, dataSource.getData(index), itemGenerator)
    }
    LazyForEachOps.Sync(parent.getPeerPtr(), dataSource.totalCount() as int32, createCallback, pool.updateActiveRange)
}

class LazyForEachIdentifier {
    constructor(id: KoalaCallsiteKey, totalCnt: int32, activeCnt: int32) {
        this.id = id
        this.totalCnt = totalCnt
        this.activeCnt = activeCnt
    }
    readonly id: KoalaCallsiteKey
    readonly totalCnt: int32
    readonly activeCnt: int32
}

/**
 * @param id unique identifier of LazyForEach
 * @returns item offset of LazyForEach in parent's children
 */
/** @memo */
function getOffset(parent: PeerNode, id: KoalaCallsiteKey): int32 {
    let offset = 0
    for (let child = parent.firstChild; child; child = child!.nextSibling) {
        // corresponding DataNode is attached after the component items
        let info = DataNode.extract<LazyForEachIdentifier>(LazyForEachType, child!!)
        if (info?.id === id) {
            offset -= info!.activeCnt
            // console.log(`offset = ${offset}`)
            return offset
        } else if (info) {
            offset += info!.totalCnt - info!.activeCnt // active nodes are already counted
        } else if (child!.isKind(PeerNodeType)) {
            ++offset
        }
    }
    return offset // DataNode not found, maybe throw error?
}

class LazyItemPool implements Disposable {
    private _activeItems = new Map<int32, ComputableState<LazyItemNode>>()
    private _parent: PeerNode
    disposed: boolean = false

    constructor(parent: PeerNode) {
        this._parent = parent
    }

    dispose(): void {
        if (this.disposed) return

        this.pruneBy(() => true)
        this.disposed = true
    }

    get activeCount(): int32 {
        return this._activeItems.size as int32
    }

    getOrCreate<T>(
        index: int32,
        data: T,
        /** @memo */
        itemGenerator: (item: T, index: number) => void,
    ): pointer {
        if (this._activeItems.has(index)) {
            const node = this._activeItems.get(index)!
            if (node.recomputeNeeded) {
                console.log(`recomputeNeeded: ${index}`)
            }
            return node.value.getPeerPtr()
        }

        const manager = GlobalStateManager.instance
        const node = manager.updatableNode<LazyItemNode>(new LazyItemNode(this._parent),
            (context: StateContext) => {
                const frozen = manager.frozen
                manager.frozen = true
                setNeedCreate(true) // ensure synchronous creation of CustomComponent
                memoEntry2<T, number, void>(
                    context,
                    index, // using index to simplify reuse process
                    itemGenerator,
                    data,
                    index
                )
                setNeedCreate(false)
                manager.frozen = frozen
            }
        )

        this._activeItems.set(index, node)
        globalLazyItems.add(node)
        return node.value.getPeerPtr()
    }

    /**
     *
     * @param criteria predicate to determine if the item needs to be removed
     */
    pruneBy(criteria: (index: int32) => boolean) {
        this._activeItems.forEach((node, index) => {
            if (criteria(index)) {
                node.dispose()
                this._activeItems.delete(index)
                globalLazyItems.delete(node)
            }
        })
    }

    /**
     * prune items outside the range [start, end]
     * @param start 
     * @param end 
     */
    updateActiveRange(start: int32, end: int32) {
        if (start > end) return
        this.pruneBy(index => index < start || index > end)
    }
}
