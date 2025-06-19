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

import { pointer } from "@koalaui/interop";
import { DataOperation, DataOperationType, DataAddOperation, DataDeleteOperation, DataChangeOperation, DataMoveOperation, DataExchangeOperation, LazyForEachOps } from "./component";
import { int32 } from "@koalaui/common"
import { MutableState } from "@koalaui/runtime";
import { DataChangeListener } from "./component/lazyForEach";
import { requestFrame } from "./stateManagement";

export class InternalListener implements DataChangeListener {
    readonly parent: pointer
    private startIndex: number // Tracks the minimum item index that has changed
    private endIndex: number
    private changeCount: number // Tracks the number of items added or deleted
    private version: MutableState<int32> // reference to mark LazyForEach dirty

    constructor(parent: pointer, version: MutableState<int32>) {
        this.parent = parent
        this.startIndex = Number.POSITIVE_INFINITY
        this.endIndex = Number.NEGATIVE_INFINITY
        this.changeCount = 0
        this.version = version
    }
    /**
     * Notify the change of data to backend
     * @return the index of the first changed item
     */
    flush(offset: int32): number {
        if (this.startIndex === Number.POSITIVE_INFINITY) {
            return Number.POSITIVE_INFINITY // none affected
        }
        LazyForEachOps.NotifyChange(
            this.parent,
            this.startIndex as int32 + offset,
            this.endIndex as int32 + offset,
            this.changeCount as int32
        );
        const firstAffected = this.startIndex
        // Reset the cache after flushing
        this.startIndex = Number.POSITIVE_INFINITY;
        this.endIndex = Number.NEGATIVE_INFINITY;
        this.changeCount = 0;
        return firstAffected
    }

    onDataReloaded(): void {
        if (this.startIndex === Number.POSITIVE_INFINITY) {
            ++this.version.value
        }
        this.startIndex = 0
        this.endIndex = Number.POSITIVE_INFINITY
    }

    onDataAdd(index: number): void {
        if (index < 0) return
        if (this.startIndex === Number.POSITIVE_INFINITY) {
            ++this.version.value
        }
        this.startIndex = Math.min(this.startIndex, index)
        ++this.changeCount
    }

    onDataMove(from: number, to: number): void {
        if (from < 0 || to < 0) return
        if (this.startIndex === Number.POSITIVE_INFINITY) {
            ++this.version.value
        }
        this.startIndex = Math.min(this.startIndex, Math.min(from, to))
        this.endIndex = Math.max(this.endIndex, Math.max(from, to))
    }

    onDataDelete(index: number): void {
        if (index < 0) return
        if (this.startIndex === Number.POSITIVE_INFINITY) {
            ++this.version.value
        }
        this.startIndex = Math.min(this.startIndex, index)
        --this.changeCount
    }

    onDataChange(index: number): void {
        if (index < 0) return
        if (this.startIndex === Number.POSITIVE_INFINITY) {
            ++this.version.value
            requestFrame()
        }
        this.startIndex = Math.min(this.startIndex, index)
    }

    onDatasetChange(dataOperations: DataOperation[]): void {
        let startIndex = Number.NEGATIVE_INFINITY
        let endIndex = Number.NEGATIVE_INFINITY
        let changeCount = 0
        for (const operation of dataOperations) {
            switch (operation.type) {
                case DataOperationType.ADD: {
                    startIndex = Math.min(startIndex, (operation as DataAddOperation).index);
                    ++changeCount
                    break;
                }
                case DataOperationType.DELETE: {
                    startIndex = Math.min(startIndex, (operation as DataDeleteOperation).index);
                    --changeCount
                    break;
                }
                case DataOperationType.CHANGE: {
                    startIndex = Math.min(startIndex, (operation as DataChangeOperation).index);
                    break;
                }
                case DataOperationType.MOVE: {
                    const moveOp = operation as DataMoveOperation;
                    startIndex = Math.min(startIndex, Math.min(moveOp.index.from, moveOp.index.to));
                    endIndex = Math.max(endIndex, Math.max(moveOp.index.from, moveOp.index.to));
                    break;
                }
                case DataOperationType.EXCHANGE: {
                    const exchangeOp = operation as DataExchangeOperation;
                    startIndex = Math.min(startIndex, Math.min(exchangeOp.index.start, exchangeOp.index.end));
                    endIndex = Math.max(endIndex, Math.max(exchangeOp.index.start, exchangeOp.index.end));
                    break;
                }
                case DataOperationType.RELOAD: {
                    startIndex = 0;
                    endIndex = Number.POSITIVE_INFINITY
                    break;
                }
            }
        }
        if (this.startIndex === Number.POSITIVE_INFINITY) {
            ++this.version.value
        }
        this.startIndex = startIndex
        this.endIndex = endIndex
        this.changeCount = changeCount
    }

    /* deprecated */
    onDataAdded(index: number): void {
        this.onDataAdd(index)
    }
    onDataMoved(from: number, to: number): void {
        this.onDataMove(from, to)
    }
    onDataDeleted(index: number): void {
        this.onDataDelete(index)
    }
    onDataChanged(index: number): void {
        this.onDataChange(index)
    }
}
