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

import { pointer, nullptr } from "@koalaui/interop";
import { DataOperation, DataOperationType, DataAddOperation, DataDeleteOperation, DataChangeOperation, DataMoveOperation, DataExchangeOperation, LazyForEachOps } from "./generated";
import { int32 } from "@koalaui/common"

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

export class InternalListener implements DataChangeListener {
    parent: pointer = nullptr
    startIndex = Number.NEGATIVE_INFINITY // Tracks the minimum item index that has changed
    endIndex = Number.NEGATIVE_INFINITY
    changeCount = 0 // Tracks the number of items added or deleted

    constructor(parent: pointer) {
        this.parent = parent;
    }
    /**
     * Notify the change of data to backend
     */
    flush(offset: int32): void {
        if (this.startIndex === Number.NEGATIVE_INFINITY) {
            return
        }
        // Notify the change with the cached index and count
        LazyForEachOps.NotifyChange(
            this.parent,
            this.startIndex as int32 + offset,
            this.endIndex as int32 + offset,
            this.changeCount as int32
        );
        // Reset the cache after flushing
        this.startIndex = Number.NEGATIVE_INFINITY;
        this.endIndex = Number.NEGATIVE_INFINITY;
        this.changeCount = 0;
    }

    onDataReloaded(): void {
        this.startIndex = 0;
        this.endIndex = Number.POSITIVE_INFINITY
    }

    onDataAdd(index: number): void {
        this.startIndex = Math.min(this.startIndex, index);
        ++this.changeCount
    }

    onDataMove(from: number, to: number): void {
        this.startIndex = Math.min(this.startIndex, Math.min(from, to));
        this.endIndex = Math.max(this.endIndex, Math.max(from, to));
    }

    onDataDelete(index: number): void {
        this.startIndex = Math.min(this.startIndex, index);
        --this.changeCount
    }

    onDataChange(index: number): void {
        this.startIndex = Math.min(this.startIndex, index);
    }

    onDatasetChange(dataOperations: DataOperation[]): void {
        // Iterate through each operation and update the cache
        for (const operation of dataOperations) {
            switch (operation.type) {
                case DataOperationType.ADD: {
                    const addOp = operation as DataAddOperation;
                    this.onDataAdd(addOp.index)
                    break;
                }
                case DataOperationType.DELETE: {
                    const deleteOp = operation as DataDeleteOperation;
                    this.onDataDelete(deleteOp.index)
                    break;
                }
                case DataOperationType.CHANGE: {
                    const changeOp = operation as DataChangeOperation;
                    this.onDataChange(changeOp.index)
                    break;
                }
                case DataOperationType.MOVE: {
                    const moveOp = operation as DataMoveOperation;
                    this.onDataMove(moveOp.index.from, moveOp.index.to)
                    break;
                }
                case DataOperationType.EXCHANGE: {
                    const exchangeOp = operation as DataExchangeOperation;
                    this.onDataMove(exchangeOp.index.start, exchangeOp.index.end)
                    break;
                }
                case DataOperationType.RELOAD: {
                    this.onDataReloaded()
                    break;
                }
            }
        }
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