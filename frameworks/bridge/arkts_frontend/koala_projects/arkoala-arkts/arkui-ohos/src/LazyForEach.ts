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

import { __context, __id, contextNode, DataNode, IncrementalNode, memoEntry2, remember, rememberMutableState, scheduleCallback } from "@koalaui/runtime"
import { hashCodeFromString, int32, KoalaCallsiteKey } from "@koalaui/common"
import { nullptr, pointer } from "@koalaui/interop";
import { LazyForEachType, PeerNode, PeerNodeType } from "./PeerNode";
import { LazyForEachOps } from "./generated/ArkLazyForEachOpsMaterialized"
import { InternalListener } from "./DataChangeListener";
import { IDataSource } from "./component/lazyForEach";
import { setNeedCreate } from "./ArkComponentRoot";

class LazyForEachManager {
    static isDummy: boolean = false
     // Special pointer to mark that more elements needed.
    static specialPointer: pointer = 1
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

    /**
     * @param parent
     * @param itemCount
     * @param offset of LazyForEach in parent's children
     */
    static Prepare(parent: PeerNode, itemCount: int32, offset: int32): void {
        if (!LazyForEachManager.isDummy)
            LazyForEachOps.Prepare(parent.peer.ptr, itemCount, offset)
    }
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

    get activeCount(): int32 {
        return this.indexDown >= 0 ? this.indexDown - this.indexUp + 1 : 0
    }
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
        // corresponding DataNode is attached after the generated items
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

/** @memo */
export function LazyForEachImpl<T>(dataSource: IDataSource<T>,
    /** @memo */
    itemGenerator: (item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
) {
    let current = rememberMutableState<int32>(-1)
    let mark = rememberMutableState<pointer>(nullptr)
	let version = rememberMutableState<int32>(0)
	// console.log(`LazyForEach current=${current.value} version=${version.value} mark=${mark.value}`)

    let parent = contextNode<PeerNode>()
    const offset = getOffset(parent, __id())

    let listener = remember(() => new InternalListener(parent.peer.ptr, version))
    const changeIndex = listener.flush(offset) // first item index that's affected by DataChange

    const currentLocal = current.value >= 0 ? Math.max(current.value - offset, 0) as int32 : -1; // translated to local index
    const visibleRange = new VisibleRange(parent, currentLocal, currentLocal)
    remember(() => {
        dataSource.registerDataChangeListener(listener)
        LazyForEachManager.OnRangeUpdate(visibleRange.parent, dataSource.totalCount() as int32, (currentIndex: int32, currentMark: pointer, end: int32) => {
            // console.log(`LazyForEach[${parent}]: current updated to ${currentIndex} ${currentMark} end=${end}`)
            current.value = currentIndex
            mark.value = currentMark
            version.value++
        })
    })
    // Subscribe to version changes.
    version.value

    let generator = (element: T, index: number): int32 => keyGenerator ? hashCodeFromString(keyGenerator!(element, index)) : index as int32
    let index: number = visibleRange.indexUp as number

    LazyForEachManager.Prepare(parent, dataSource.totalCount() as int32, offset)
    LazyForEachManager.SetInsertMark(parent, mark.value, false)
    const prevVal = setNeedCreate(true) // force synchronous create of inner CustomComponents in order to layout them correctly
	while (true) {
        // console.log(`LazyForEach[${parent}]: index=${index}`)
        if (index < 0 || index >= dataSource.totalCount()) break
        const element: T = dataSource.getData(index as number)
        memoEntry2<T, number, void>(
            __context(),
            generator(element, index),
            (element: T, index: number): void => { itemGenerator(element, index) },
	        element,
            index
	    )
        let moreUp = visibleRange.needFillUp()
        if (moreUp && visibleRange.indexUp > 0) {
            index = --visibleRange.indexUp
        } else if (visibleRange.needFillDown()) {
            index = ++visibleRange.indexDown
        } else {
            // console.log("No more needed")
            index = -1
        }
        LazyForEachManager.SetInsertMark(parent, moreUp ? visibleRange.markUp : visibleRange.markDown, moreUp)
	}
    setNeedCreate(prevVal)
	parent.setInsertMark(nullptr, false)

    // create DataNode to provide count information to parent
    const identifier = new LazyForEachIdentifier(__id(), dataSource.totalCount() as int32, visibleRange.activeCount)
    DataNode.attach(LazyForEachType, identifier)
}
