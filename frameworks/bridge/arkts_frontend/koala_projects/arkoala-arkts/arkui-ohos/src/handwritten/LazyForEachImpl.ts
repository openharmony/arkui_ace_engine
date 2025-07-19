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

import { __id, NodeAttach, ComputableState, contextNode, GlobalStateManager, Disposable, memoEntry2, remember, rememberDisposable, rememberMutableState, StateContext, scheduleCallback } from "@koalaui/runtime"
import { InteropNativeModule, nullptr, pointer } from "@koalaui/interop"
import { PeerNode } from "../PeerNode"
import { InternalListener } from "../DataChangeListener"
import { setNeedCreate } from "../ArkComponentRoot"
import { int32 } from "@koalaui/common"
import { IDataSource } from "../component/lazyForEach"
import { LazyForEachOps } from "../component"
import { LazyItemNode } from "./LazyItemNode"
import { ArkUIAniModule } from "../ani/arkts/ArkUIAniModule"
import { CustomComponent } from "@component_handwritten/customComponent"

let globalLazyItems = new Map<ComputableState<LazyItemNode>, int32>() // V: age

export function updateLazyItems() {
    let postponed = false
    globalLazyItems.forEach((age, node, map) => {
        if (age === 0) {
            postponed = true
            map.set(node, 1)
        } else {
            node.value
        }
    })
    if (postponed) {
        // requestFrame()
    }
}

/** @memo:intrinsic */
export function LazyForEachImpl<T>(dataSource: IDataSource<T>,
    /** @memo */
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
) {
    const node = createLazyNode()

    let pool = rememberDisposable(() => new LazyItemPool(node, CustomComponent.current), (pool?: LazyItemPool) => {
        pool?.dispose()
    })
    let changeCounter = rememberMutableState(0)
    changeCounter.value //subscribe
    let listener = remember(() => {
        let res = new InternalListener(changeCounter)
        dataSource.registerDataChangeListener(res)
        return res
    })
    const changeIndex = listener.flush(node.getPeerPtr()) // first item index that's affected by DataChange
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
    LazyForEachOps.Sync(node.getPeerPtr(), dataSource.totalCount() as int32, createCallback, pool.updateActiveRange)
}

class NodeHolder {
    node?: PeerNode
}

/** @memo:intrinsic */
function createLazyNode(): PeerNode {
    /**
     *  We don't want cache behavior with LazyForEach (to support Repeat's non-memo data updates),
     *  therefore LazyForEach implementation is outside NodeAttach, and LazyForEachNode is provided through a remembered NodeHolder.
     */
    let nodeHolder = remember(() => new NodeHolder())
    NodeAttach(
        () => {
            const peerId = PeerNode.nextId()
            const _peerPtr = ArkUIAniModule._LazyForEachNode_Construct(peerId)
            if (!_peerPtr) {
                throw new Error("create LazyForEachNode failed")
            }
            const _peer = new PeerNode(_peerPtr, peerId, "LazyForEach", 0)
            return _peer
        },
        (node: PeerNode) => {
            nodeHolder.node = node
        }
    )
    return nodeHolder.node!
}

class LazyItemCompositionContext {
    private prevFrozen: boolean
    private prevNeedCreate: boolean
    private prevCurrent?: Object

    constructor(parentComponent?: Object) {
        const manager = GlobalStateManager.instance
        this.prevFrozen = manager.frozen
        manager.frozen = true
        this.prevNeedCreate = setNeedCreate(true) // ensure synchronous creation of all inner CustomComponent
        this.prevCurrent = CustomComponent.current
        CustomComponent.current = parentComponent // setup CustomComponent context to link with @Provide variables
    }

    exit(): void {
        CustomComponent.current = this.prevCurrent
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
        globalLazyItems.set(node, 0)
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
