/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { __context, contextNode, memoEntry2, remember, rememberMutableState, scheduleCallback } from "@koalaui/runtime"
import { hashCodeFromString, int32 } from "@koalaui/common"
import { nullptr, pointer } from "@koalaui/interop";
import { PeerNode } from "./PeerNode";
import { LazyForEachOps } from "./generated/ArkLazyForEachOpsMaterialized"

// TODO: proper import [DataChangeListener] from lazy_for_each.d.ts
export interface DataChangeListener {
    onDataReloaded(): void;
    onDataAdded(index: number): void;
    onDataAdd(index: number): void;
    onDataMoved(from: number, to: number): void;
    onDataMove(from: number, to: number): void;
    onDataDeleted(index: number): void;
    onDataDelete(index: number): void;
    onDataChanged(index: number): void;
    onDataChange(index: number): void;
    onDatasetChange(dataOperations: DataOperation[]): void;
}
/**
 * Developers need to implement this interface to provide data to LazyForEach component.
 * @since 7
 */
export interface IDataSource {
    /**
     * Total data count.
     * @since 7
     */
    totalCount(): number;
    /**
     * Return the data of index.
     * @since 7
     */
    getData(index: number): any;
    /**
     * Register data change listener.
     * @since 7
     */
    registerDataChangeListener(listener: DataChangeListener): void;
    /**
     * Unregister data change listener.
     * @since 7
     */
    unregisterDataChangeListener(listener: DataChangeListener): void;
}

class LazyForEachManager {
    static isDummy: boolean = false
    // Special pointer to mark that more elements needed.
    static specialPointer: pointer = BigInt(1)

    static OnRangeUpdate(parent: pointer, totalCount: int32, updater: (currentIndex: int32, currentMark: pointer, end: int32) => void) {
        if (LazyForEachManager.isDummy)
            scheduleCallback(() =>  updater(0, LazyForEachManager.specialPointer, 100))
        else
            LazyForEachOps.OnRangeUpdate(parent, totalCount, updater)
    }

    static NeedMoreElements(parent: pointer, mark: pointer, direction: int32): pointer {
        if (LazyForEachManager.isDummy)
            return LazyForEachManager.specialPointer
        else
            return LazyForEachOps.NeedMoreElements(parent, mark, direction)
    }

    static SetCurrentIndex(node: pointer, index: int32): void {
        if (!LazyForEachManager.isDummy)
            LazyForEachOps.SetCurrentIndex(node, index)
    }

    static SetInsertMark(parent: PeerNode, mark: pointer, moreUp: boolean): void {
        if (!LazyForEachManager.isDummy)
            parent.setInsertMark(mark, moreUp)
    }

    static Prepare(parent: PeerNode): void {}
}

class VisibleRange {
    parent: pointer = nullptr
    markUp: pointer = nullptr
    markDown: pointer = nullptr
    indexUp: int32
    indexDown: int32

    constructor(parent: PeerNode, indexUp: int32, indexDown: int32) {
        this.parent = parent.peer.ptr
        this.indexUp = indexUp
        this.indexDown = indexDown
    }
    needFillUp(): boolean {
        let more = LazyForEachManager.NeedMoreElements(this.parent, this.markUp, 0)
        if (more == nullptr) return false
        this.markUp = more
        return true
    }

    needFillDown(): boolean {
        let more = LazyForEachManager.NeedMoreElements(this.parent, this.markDown, 1)
        if (more == nullptr) return false
        this.markDown = more
        return true
    }
}


/** @memo */
export function LazyForEach(dataSource: IDataSource,
    /** @memo */
    itemGenerator: (item: any, index?: number) => void,
    keyGenerator?: (item: any, index?: number) => string,
) { let current = rememberMutableState<int32>(-1)
    let mark = rememberMutableState<pointer>(nullptr)
	let version = rememberMutableState<int32>(0)
	console.log(`LazyForEach current=${current.value} version=${version.value} mark=${mark.value}`)

    let parent = contextNode<PeerNode>()
    const visibleRange = new VisibleRange(parent, current.value, current.value)
    remember(() => {
        LazyForEachManager.OnRangeUpdate(visibleRange.parent, dataSource.totalCount() as int32, (currentIndex: int32, currentMark: pointer, end: int32) => {
            console.log(`LazyForEach[${parent}]: current updated to ${currentIndex} ${currentMark} end=${end}`)
            current.value = currentIndex
            mark.value = currentMark
            version.value++
        })
    })
    // Subscribe to version changes.
    version.value

    let generator = (element: any, index: number): int32 => keyGenerator ? hashCodeFromString(keyGenerator!(element, index)) : index as int32
    let index: number = visibleRange.indexUp as number

    LazyForEachManager.Prepare(parent)
    LazyForEachManager.SetInsertMark(parent, mark.value, false)
	while (true) {
        console.log(`LazyForEach[${parent}]: index=${index}`)
	    if (index < 0 || index >= dataSource.totalCount()) break
	    const element = dataSource.getData(index as number)
	    memoEntry2<any, number, void>(
	        __context(),
            generator(element, index),
            (element: any, index: number): void => { itemGenerator(element, index) },
	        element,
            index
	    )
        let moreUp = visibleRange.needFillUp()
        if (moreUp && visibleRange.indexUp > 0) {
            index = --visibleRange.indexUp
        } else if (visibleRange.needFillDown()) {
            index = ++visibleRange.indexDown
        } else {
            console.log("No more needed")
            index = -1
        }
        LazyForEachManager.SetInsertMark(parent, moreUp ? visibleRange.markUp : visibleRange.markDown, moreUp)
	}
	parent.setInsertMark(nullptr, false)
}
