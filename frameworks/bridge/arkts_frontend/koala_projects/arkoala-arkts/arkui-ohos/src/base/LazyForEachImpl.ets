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

import { __id, NodeAttach, Disposable, remember, rememberDisposable, rememberMutableState,
    scheduleCallback } from '@koalaui/runtime'
import { InteropNativeModule, nullptr, pointer } from '@koalaui/interop'
import { int32 } from '@koalaui/common'
import { PeerNode } from '../PeerNode'
import { InternalListener } from './DataChangeListener'
import { IDataSource } from '../component/lazyForEach'
import { OnMoveHandler, ItemDragEventHandler, LazyForEachOps } from '#generated'
import { SyntaxItemPeer, LazyNodePeer, NodeHolder } from './SyntaxNodeBase'
import { createUiDetachedRoot } from 'arkui/ArkUIEntry'
import { ObserveSingleton } from '../stateManagement/base/observeSingleton'
import { ExtendableComponent } from '../component/extendableComponent'

/** @memo:intrinsic */
export function LazyForEachImplForOptions<T>(dataSource: IDataSource<T>,
    /** @memo */
    itemGenerator: (item: T, index: int32) => void,
    keyGenerator?: (item: T, index: int32) => string,
    onMove?: OnMoveHandler,
    itemDragEvent?: ItemDragEventHandler,
    isRepeat: boolean = false,
) {
    const node = createLazyNode(isRepeat)

    let pool = rememberDisposable(() => new LazyItemPool(), (pool?: LazyItemPool) => pool?.dispose())
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

    const currentRenderingComponent = ObserveSingleton.instance.renderingComponent;
    const currentExtendableComponent = ExtendableComponent.current;
    /**
     * provide totalCount and callbacks to the backend
     */
    let createCallback = (index: int32) => {
        const lastRenderingComponent = ObserveSingleton.instance.renderingComponent;
        const lastExtendableComponent = ExtendableComponent.current;
        ObserveSingleton.instance.renderingComponent = currentRenderingComponent;
        ExtendableComponent.current = currentExtendableComponent;
        try {
            return pool.getOrCreate(index, dataSource.getData(index), itemGenerator,
                currentRenderingComponent, currentExtendableComponent)
        } catch (error) {
            InteropNativeModule._NativeLog(`error during createLazyItem: ${error}`)
            return nullptr
        } finally {
            ObserveSingleton.instance.renderingComponent = lastRenderingComponent;
            ExtendableComponent.current = lastExtendableComponent;
        }
    }
    LazyForEachOps.Sync(node.getPeerPtr(), dataSource.totalCount() as int32, createCallback, pool.updateActiveRange)

    /**
     * provide onMove callbacks to the backend if onMove is set，and reset callbacks if onMove is unset
     */
    LazyForEachOps.SyncOnMoveOps(node.getPeerPtr(), pool.onMoveFromTo, onMove, itemDragEvent)
}

/** @memo:intrinsic */
function createLazyNode(isRepeat: boolean): PeerNode {
    /**
     * We don't want cache behavior with LazyForEach (to support Repeat's non-memo data updates),
     *   therefore LazyForEach implementation is outside NodeAttach,
     *   and LazyNode is provided through a remembered NodeHolder.
     */
    let nodeHolder = remember(() => new NodeHolder())
    NodeAttach(() => LazyNodePeer.create(isRepeat), (node: PeerNode) => {
        nodeHolder.node = node
    })
    return nodeHolder.node!
}

class LazyItemPool implements Disposable {
    private _activeItems = new Map<int32, SyntaxItemPeer>()
    private _moveFromTo?: [int32, int32] = undefined // used to track moveFromTo in onMove event
    disposed: boolean = false

    dispose(): void {
        if (this.disposed) {
            return
        }

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
        itemGenerator: (item: T, index: int32) => void,
        currentRenderingComponent: int32,
        currentExtendableComponent: object | undefined,
    ): pointer {
        if (this._activeItems.has(index)) {
            const node = this._activeItems.get(index)!
            return node.getPeerPtr()
        }

        const node = createUiDetachedRoot((): PeerNode => SyntaxItemPeer.create(), (): void => {
            const lastRenderingComponent = ObserveSingleton.instance.renderingComponent;
            const lastExtendableComponent = ExtendableComponent.current;
            ObserveSingleton.instance.renderingComponent = currentRenderingComponent;
            ExtendableComponent.current = currentExtendableComponent;
            itemGenerator(data, index);
            ObserveSingleton.instance.renderingComponent = lastRenderingComponent;
            ExtendableComponent.current = lastExtendableComponent;
        })

        this._activeItems.set(index, node as SyntaxItemPeer)
        return node.peer.ptr
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
            }
        })
    }

    /**
     * prune items outside the range [start, end]
     * @param start 
     * @param end 
     */
    updateActiveRange(start: int32, end: int32) {
        if (start > end) {
            return
        }
        try {
            this.pruneBy(index => {
                index = this.convertFromToIndexRevert(index)
                return index < start || index > end
            })
        } catch (error) {
            InteropNativeModule._NativeLog(`error during LazyItem pruning: ${error}`)
        }
    }

    /**
     * set onMoveFromTo value used for functions convertFromToIndex and convertFromToIndexRevert
     * @param moveFrom
     * @param moveTo
     */
    onMoveFromTo(moveFrom: int32, moveTo: int32): void {
        if (moveFrom < 0 || moveTo < 0) {
            this.updateActiveItemsForOnMove();
            this._moveFromTo = undefined;
            InteropNativeModule._NativeLog(`onMoveFromTo param invalid, reset moveFromTo`);
            return;
        }
        if (this._moveFromTo != undefined) {
            this._moveFromTo![1] = moveTo;
            if (this._moveFromTo![1] === this._moveFromTo![0]) {
                this._moveFromTo = undefined;
            }
        } else {
            this._moveFromTo = [moveFrom, moveTo];
        }
        if (this._moveFromTo != undefined) {
            InteropNativeModule._NativeLog(`onMoveFromTo updated (${this._moveFromTo![0]}, ${this._moveFromTo![1]})`);
        } else {
            InteropNativeModule._NativeLog(`onMoveFromTo data moved to original pos, reset moveFromTo.`);
        }
    }

    // before onMove called, update _activeItems according to the _moveFromTo
    private updateActiveItemsForOnMove(): void {
        if (this._moveFromTo == undefined) {
            return;
        }
        const fromIndex = Math.min(this._moveFromTo![0], this._moveFromTo![1]);
        const toIndex = Math.max(this._moveFromTo![0], this._moveFromTo![1]);
        if (fromIndex === toIndex) {
            return;
        }
        let tempActiveItems = new Map<int32, SyntaxItemPeer>();
        this._activeItems.forEach((node, index) => {
            if (index < fromIndex || index > toIndex) {
                tempActiveItems.set(index, node);
            } else {
                const newIndex = this.convertFromToIndexRevert(index);
                tempActiveItems.set(newIndex, node);
            }
        })
        this._activeItems = tempActiveItems;
    }

    // currently unused, but may be useful in the future.
    private convertFromToIndex(index: int32): int32 {
        if (this._moveFromTo == undefined) {
            return index;
        }
        if (this._moveFromTo![1] === index) {
            return this._moveFromTo![0];
        }
        if (this._moveFromTo![0] <= index && index < this._moveFromTo![1]) {
            return index + 1;
        }
        if (this._moveFromTo![1] < index && index <= this._moveFromTo![0]) {
            return index - 1;
        }
        return index;
    }

    // used for updateActiveRange.
    private convertFromToIndexRevert(index: int32): int32 {
        if (this._moveFromTo == undefined) {
            return index;
        }
        if (this._moveFromTo![0] === index) {
            return this._moveFromTo![1];
        }
        if (this._moveFromTo![0] < index && index <= this._moveFromTo![1]) {
            return index - 1;
        }
        if (this._moveFromTo![1] <= index && index < this._moveFromTo![0]) {
            return index + 1;
        }
        return index;
    }
}
