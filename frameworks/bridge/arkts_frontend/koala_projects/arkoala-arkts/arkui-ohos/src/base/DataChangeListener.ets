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

import { pointer } from '@koalaui/interop'
import { int32 } from '@koalaui/common'
import { LazyForEachOps } from '#generated'
import { DataOperation, DataOperationType, DataAddOperation, DataDeleteOperation, DataChangeOperation,
    DataMoveOperation, DataExchangeOperation, DataChangeListener } from '../component/lazyForEach'
import { ILocalDecoratedVariable } from '../stateManagement/decorator'

export class InternalListener implements DataChangeListener {
    private startIndex: int32 // Tracks the minimum item index that has changed
    private endIndex: int32
    private changeCount: int32 // Tracks the number of items added or deleted
    public version: ILocalDecoratedVariable<int32> // reference to mark LazyForEach dirty

    constructor(version: ILocalDecoratedVariable<int32>) {
        this.startIndex = Number.POSITIVE_INFINITY.toInt()
        this.endIndex = Number.NEGATIVE_INFINITY.toInt()
        this.changeCount = 0
        this.version = version
    }

    /**
     * Notify the change of data to backend
     * @return the index of the first changed item
     */
    flush(nodePtr: pointer): int32 {
        if (this.startIndex === Number.POSITIVE_INFINITY.toInt()) {
            return Number.POSITIVE_INFINITY.toInt() // none affected
        }
        LazyForEachOps.NotifyChange(
            nodePtr,
            this.startIndex,
            this.endIndex,
            this.changeCount
        )
        const firstAffected = this.startIndex
        // Reset the cache after flushing
        this.startIndex = Number.POSITIVE_INFINITY.toInt()
        this.endIndex = Number.NEGATIVE_INFINITY.toInt()
        this.changeCount = 0
        return firstAffected
    }

    onDataReloaded(): void {
        if (this.startIndex === Number.POSITIVE_INFINITY.toInt()) {
            this.version.set(this.version.get() + 1)
        }
        this.startIndex = 0
        this.endIndex = Number.POSITIVE_INFINITY.toInt()
    }

    onDataAdd(index: int32): void {
        if (index < 0) {
            return
        }
        if (this.startIndex === Number.POSITIVE_INFINITY.toInt()) {
            this.version.set(this.version.get() + 1)
        }
        this.startIndex = Math.min(this.startIndex, index).toInt()
        ++this.changeCount
    }

    onDataMove(from: int32, to: int32): void {
        if (from < 0 || to < 0) {
            return
        }
        if (this.startIndex === Number.POSITIVE_INFINITY.toInt()) {
            this.version.set(this.version.get() + 1)
        }
        this.startIndex = Math.min(this.startIndex, Math.min(from, to)).toInt()
        this.endIndex = Math.max(this.endIndex, Math.max(from, to)).toInt()
    }

    onDataDelete(index: int32): void {
        if (index < 0) {
            return
        }
        if (this.startIndex === Number.POSITIVE_INFINITY.toInt()) {
            this.version.set(this.version.get() + 1)
        }
        this.startIndex = Math.min(this.startIndex, index).toInt()
        --this.changeCount
    }

    onDataChange(index: int32): void {
        if (index < 0) {
            return
        }
        if (this.startIndex === Number.POSITIVE_INFINITY.toInt()) {
            this.version.set(this.version.get() + 1)
        }
        this.startIndex = Math.min(this.startIndex, index).toInt()
    }

    onDatasetChange(dataOperations: DataOperation[]): void {
        let startIndex = Number.NEGATIVE_INFINITY.toInt()
        let endIndex = Number.NEGATIVE_INFINITY.toInt()
        let changeCount = 0
        for (const operation of dataOperations) {
            switch (operation.type) {
                case DataOperationType.ADD: {
                    startIndex = Math.min(startIndex, (operation as DataAddOperation).index).toInt()
                    ++changeCount
                    break
                }
                case DataOperationType.DELETE: {
                    startIndex = Math.min(startIndex, (operation as DataDeleteOperation).index).toInt()
                    --changeCount
                    break
                }
                case DataOperationType.CHANGE: {
                    startIndex = Math.min(startIndex, (operation as DataChangeOperation).index).toInt()
                    break
                }
                case DataOperationType.MOVE: {
                    const moveOp = operation as DataMoveOperation
                    startIndex = Math.min(startIndex, Math.min(moveOp.index.from, moveOp.index.to)).toInt()
                    endIndex = Math.max(endIndex, Math.max(moveOp.index.from, moveOp.index.to)).toInt()
                    break
                }
                case DataOperationType.EXCHANGE: {
                    const exchangeOp = operation as DataExchangeOperation
                    startIndex = Math.min(startIndex, Math.min(exchangeOp.index.start, exchangeOp.index.end)).toInt()
                    endIndex = Math.max(endIndex, Math.max(exchangeOp.index.start, exchangeOp.index.end)).toInt()
                    break
                }
                case DataOperationType.RELOAD: {
                    startIndex = 0
                    endIndex = Number.POSITIVE_INFINITY.toInt()
                    break
                }
            }
        }
        if (this.startIndex === Number.POSITIVE_INFINITY.toInt()) {
            this.version.set(this.version.get() + 1)
        }
        this.startIndex = startIndex
        this.endIndex = endIndex
        this.changeCount = changeCount
    }

    /**
     * @internal
     * Notify data change without updating MutableState. Safe to call during composition.
     */
    update(start: int32, end: int32, countDiff: int32): void {
        this.startIndex = Math.min(start, this.startIndex).toInt()
        this.endIndex = Math.max(end, this.endIndex).toInt()
        this.changeCount += countDiff
    }
}
