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
import { __id, ComputableState, contextNode, GlobalStateManager, Disposable, memoEntry2, remember, rememberDisposable, rememberMutableState, StateContext, IncrementalNode } from "@koalaui/runtime";
import { getOffset } from "../LazyForEach";
import { pointer } from "@koalaui/interop";
import { LazyItemNodeType, PeerNode } from "../PeerNode";
import { InternalListener } from "../DataChangeListener";
import { setNeedCreate } from "../ArkComponentRoot";
import { KoalaCallsiteKey } from "@koalaui/common";
import { IDataSource } from "../component/lazyForEach";

/**
 * LazyItemNode is the root node of an item in LazyForEach.
 * LazyForEach items are never attached to the main tree, but stored in a separate pool in LazyForEach.
 */
class LazyItemNode extends IncrementalNode {
    constructor(parent: PeerNode) {
        super(LazyItemNodeType)
        this._container = parent
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
}

class LazyItemPool implements Disposable {
    private _activeItems: Map<number, ComputableState<LazyItemNode>> = new Map()
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

    getOrCreate<T>(
        index: number,
        data: T,
        /** @memo */
        itemGenerator: (item: T, index: number) => void,
    ): pointer {
        if (this._activeItems.has(index)) {
            const node = this._activeItems.get(index)!
            if (node.recomputeNeeded) {
                console.log(`recomputeNeeded: ${index}`)
            }
            return (node.value.firstChild as PeerNode).getPeerPtr()
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
        return (node.value.firstChild as PeerNode).getPeerPtr()
    }

    /**
     * prune items outside the range [start, end]
     * @param start 
     * @param end 
     */
    prune(start: number, end: number) {
        for (let [index, node] of this._activeItems.entries()) {
            if (index < start || index > end) {
                node.dispose()
                this._activeItems.delete(index)
            }
        }
    }
}

/** @memo */
export function LazyForEach<T>(dataSource: IDataSource<T>,
    /** @memo */
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
) {
    let changeCounter = rememberMutableState(0)
    const parent = contextNode<PeerNode>()
    const offset = getOffset(parent, __id())
    let listener = remember(() => new InternalListener(parent.peer.ptr, changeCounter))
    const changeIndex = listener.flush(offset) // first item index that's affected by DataChange

    // Entering this method implies that the parameters have changed.
    let pool = rememberDisposable(() => new LazyItemPool(parent), (pool) => {
        pool?.dispose()
    })

    let createCallback = (index: number) => {
        return pool.getOrCreate(index, dataSource.getData(index), itemGenerator)
    }
    let updateRangeCallback = pool.prune
}