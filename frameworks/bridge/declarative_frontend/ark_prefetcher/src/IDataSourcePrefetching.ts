/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

declare interface IDataSource {
  totalCount(): number;
  getData(index: number): any;
  registerDataChangeListener(listener: DataChangeListener): void;
  unregisterDataChangeListener(listener: DataChangeListener): void;
}

declare interface DataChangeListener {
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

declare enum DataOperationType {
  ADD = 'add',
  DELETE = 'delete',
  EXCHANGE = 'exchange',
  MOVE = 'move',
  CHANGE = 'change',
  RELOAD = 'reload',
}

declare interface DataAddOperation {
  type: DataOperationType.ADD;
  index: number;
  count?: number;
  key?: string | Array<string>;
}

declare interface DataDeleteOperation {
  type: DataOperationType.DELETE;
  index: number;
  count?: number;
}

declare interface DataChangeOperation {
  type: DataOperationType.CHANGE;
  index: number;
  key?: string;
}

declare interface DataMoveOperation {
  type: DataOperationType.MOVE;
  index: MoveIndex;
  key?: string;
}

declare interface DataExchangeOperation {
  type: DataOperationType.EXCHANGE;
  index: ExchangeIndex;
  key?: ExchangeKey;
}

declare interface DataReloadOperation {
  type: DataOperationType.RELOAD;
}

declare interface MoveIndex {
  from: number;
  to: number;
}

declare interface ExchangeIndex {
  start: number;
  end: number;
}

declare interface ExchangeKey {
  start: string;
  end: string;
}

declare type DataOperation =
  | DataAddOperation
  | DataDeleteOperation
  | DataChangeOperation
  | DataMoveOperation
  | DataExchangeOperation
  | DataReloadOperation;

interface IDataSourcePrefetching extends IDataSource {
  prefetch(index: number): Promise<void> | void;
  cancel?(index: number): Promise<void> | void;
}
