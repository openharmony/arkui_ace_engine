/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// HANDWRITTEN, DO NOT REGENERATE
import { __memo_context_type , __memo_id_type  } from "arkui.stateManagement.runtime";

import { __context, __id } from "@koalaui/runtime"
import { DynamicNode } from "./common"
import { LazyForEachImpl } from "../handwritten/LazyForEachImpl"

export enum DataOperationType {
    ADD = "add",
    DELETE = "delete",
    EXCHANGE = "exchange",
    MOVE = "move",
    CHANGE = "change",
    RELOAD = "reload"
}
export interface DataAddOperation {
    type: DataOperationType;
    index: number;
    count?: number;
    key?: string | Array<string>;
}
export interface DataDeleteOperation {
    type: DataOperationType;
    index: number;
    count?: number;
}
export interface DataChangeOperation {
    type: DataOperationType;
    index: number;
    key?: string;
}
export interface MoveIndex {
    from: number;
    to: number;
}
export interface ExchangeIndex {
    start: number;
    end: number;
}
export interface ExchangeKey {
    start: string;
    end: string;
}
export interface DataMoveOperation {
    type: DataOperationType;
    index: MoveIndex;
    key?: string;
}
export interface DataExchangeOperation {
    type: DataOperationType;
    index: ExchangeIndex;
    key?: ExchangeKey;
}
export interface DataReloadOperation {
    type: DataOperationType;
}
export type DataOperation = DataAddOperation | DataDeleteOperation | DataChangeOperation | DataMoveOperation | DataExchangeOperation | DataReloadOperation;

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
export interface IDataSource<T> {
    /**
     * Total data count.
     * @since 7
     */
    totalCount(): number;
    /**
     * Return the data of index.
     * @since 7
     */
    getData(index: number): T;
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

/** @memo */
export function LazyForEach<T>(
    /** @memo */
    style: ((attributes: DynamicNode<T>) => void) | undefined,
    dataSource: IDataSource<T>,
    itemGenerator: (__memo_context: __memo_context_type, __memo_id: __memo_id_type,item: T, index: number) => void,
    keyGenerator?: (item: T, index: number) => string,
) {
    LazyForEachImpl(dataSource, itemGenerator, keyGenerator)
}
