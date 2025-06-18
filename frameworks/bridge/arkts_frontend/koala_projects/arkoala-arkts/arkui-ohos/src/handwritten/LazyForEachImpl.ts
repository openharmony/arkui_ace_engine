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

import { __id, ComputableState, contextNode, GlobalStateManager, Disposable, memoEntry2, remember, rememberDisposable, rememberMutableState, StateContext, scheduleCallback } from "@koalaui/runtime";
import { InteropNativeModule, nullptr, pointer } from "@koalaui/interop";
import { PeerNode } from "../PeerNode";
import { InternalListener } from "../DataChangeListener";
import { setNeedCreate } from "../ArkComponentRoot";
import { int32 } from "@koalaui/common";
import { IDataSource } from "../component/lazyForEach";
import { LazyItemNode } from "./LazyItemNode";
import { CustomComponent } from "../component/customComponent";
import { LazyForEachOps } from "../generated/ArkLazyForEachOpsMaterialized"

let globalLazyItems: Set<ComputableState<LazyItemNode>> = new Set<ComputableState<LazyItemNode>>()
export function updateLazyItems() {
    for (let node of globalLazyItems) {
        node.value
    }
}

/** @memo:intrinsic */
export function LazyForEachImpl<T>(dataSource: IDataSource<T>,
    /** @memo */
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
) {
    const parent = contextNode<PeerNode>()
    let pool = rememberDisposable(() => new LazyItemPool(parent, CustomComponent.current), (pool?: LazyItemPool) => {
        pool?.dispose()
    })
    let changeCounter = rememberMutableState(0)
    changeCounter.value //subscribe
    let listener = remember(() => {
        let res = new InternalListener(parent.peer.ptr, changeCounter)
        dataSource.registerDataChangeListener(res)
        return res
    })
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
        try {
            return pool.getOrCreate(index, dataSource.getData(index), itemGenerator)
        } catch (error) {
            InteropNativeModule._NativeLog(`error during createLazyItem: ${error}`)
            return nullptr
        }
    }
    LazyForEachOps.Sync(parent.getPeerPtr(), dataSource.totalCount() as int32, createCallback, pool.updateActiveRange)
}

class LazyItemCompositionContext {
    private prevFrozen: boolean
    private prevNeedCreate: boolean

    constructor(parentComponent?: Object) {
        const manager = GlobalStateManager.instance
        this.prevFrozen = manager.frozen
        manager.frozen = true
        this.prevNeedCreate = setNeedCreate(true) // ensure synchronous creation of all inner CustomComponent
    }

    exit(): void {
        setNeedCreate(this.prevNeedCreate)
        GlobalStateManager.instance.frozen = this.prevFrozen
    }
}

class LazyItemPool implements Disposable {
    private _activeItems = new Map<int32, ComputableState<LazyItemNode>>()
    private _parent: PeerNode
    private _componentRoot?: Object
    disposed: boolean = false

    /**
     * 
     * @param parent direct parent node (should be the scroll container node)
     * @param root root object of the current CustomComponent
     */
    constructor(parent: PeerNode, root?: Object) {
        this._parent = parent
        this._componentRoot = root
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
            return node.value.getPeerPtr()
        }

        const manager = GlobalStateManager.instance
        const node = manager.updatableNode<LazyItemNode>(new LazyItemNode(this._parent),
            (context: StateContext) => {
                let scope = new LazyItemCompositionContext(this._componentRoot)
                memoEntry2<T, number, void>(
                    context,
                    0,
                    itemGenerator,
                    data,
                    index
                )
                scope.exit()
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
        try {
            this.pruneBy(index => index < start || index > end)
        } catch (error) {
            InteropNativeModule._NativeLog(`error during LazyItem pruning: ${error}`)
        }
    }
}
