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

import { __id, ComputableState, contextNode, GlobalStateManager, Disposable, memoEntry2, remember, rememberDisposable, rememberMutableState, StateContext, DataNode } from "@koalaui/runtime";
import { pointer } from "@koalaui/interop";
import { LazyForEachType, PeerNode, PeerNodeType } from "../PeerNode";
import { InternalListener } from "../DataChangeListener";
import { setNeedCreate } from "../ArkComponentRoot";
import { int32, KoalaCallsiteKey } from "@koalaui/common";
import { IDataSource } from "../component/lazyForEach";
import { LazyForEachOps } from "../component";
import { LazyItemNode } from "./LazyItemNode";

/** @memo */
export function LazyForEachImpl<T>(dataSource: IDataSource<T>,
    /** @memo */
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
) {
    let changeCounter = rememberMutableState(0)
    const parent = contextNode<PeerNode>()
    const offset = getOffset(parent, __id())
    let listener = remember(() => {
        let res = new InternalListener(parent.peer.ptr, changeCounter)
        dataSource.registerDataChangeListener(res)
        return res
    })
    const changeIndex = listener.flush(offset) // first item index that's affected by DataChange

    // Entering this method implies that the parameters have changed.
    let pool = rememberDisposable(() => new LazyItemPool(parent), (pool?: LazyItemPool) => {
        pool?.dispose()
    })

    /**
     * provide totalCount and callbacks to the backend
     */
    let createCallback = (index: int32) => {
        return pool.getOrCreate(index, dataSource.getData(index), itemGenerator)
    }
    LazyForEachOps.Sync(parent.getPeerPtr(), dataSource.totalCount() as int32, createCallback, pool.prune)

    // create DataNode to provide count information to parent
    const identifier = new LazyForEachIdentifier(__id(), dataSource.totalCount() as int32, pool.activeCount)
    DataNode.attach(LazyForEachType, identifier)
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
        for (let node of this._activeItems.values()) {
            node.dispose()
        }
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
                    0,
                    itemGenerator,
                    data,
                    index
                )
                setNeedCreate(false)
                manager.frozen = frozen
            }
        )

        this._activeItems.set(index, node)
        return node.value.getPeerPtr()
    }

    /**
     * prune items outside the range [start, end]
     * @param start 
     * @param end 
     */
    prune(start: int32, end: int32) {
        for (let entry of this._activeItems.entries()) {
            if (entry[0] < start || entry[0] > end) {
                entry[1].dispose()
                this._activeItems.delete(entry[0])
            }
        }
    }
}
