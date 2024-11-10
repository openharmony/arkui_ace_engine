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

interface DataCollectionChangeListener {
  batchUpdate(operations: BatchOperation[]): void;
}

interface ItemsDeleted {
  kind: 'deleted';
  startIndex: number;
  count: number;
}

interface ItemsAdded {
  kind: 'added';
  startIndex: number;
  count: number;
}

interface ItemUpdated {
  kind: 'updated';
  index: number;
}

interface CollectionReloaded {
  kind: 'reloaded';
  totalCount: number;
}

interface ItemsSwapped {
  kind: 'swapped';
  a: number;
  b: number;
}

interface ItemMoved {
  kind: 'moved';
  from: number;
  to: number;
}

type BatchOperation = ItemsDeleted | ItemsAdded | ItemUpdated | CollectionReloaded | ItemsSwapped | ItemMoved;

// eslint-disable-next-line @typescript-eslint/no-unused-vars
class DataSourceObserver implements DataChangeListener {
  private dataSource: IDataSource;

  constructor(private readonly simpleChangeListener: DataCollectionChangeListener) {}

  onDataReloaded(): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'reloaded',
        totalCount: this.dataSource.totalCount(),
      },
    ]);
  }

  onDataAdded(index: number): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'added',
        startIndex: index,
        count: 1,
      },
    ]);
  }

  onDataAdd(index: number): void {
    this.onDataAdded(index);
  }

  onDataMoved(from: number, to: number): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'swapped',
        a: from,
        b: to,
      },
    ]);
  }

  onDataMove(from: number, to: number): void {
    this.onDataMoved(from, to);
  }

  onDataDeleted(index: number): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'deleted',
        startIndex: index,
        count: 1,
      },
    ]);
  }

  onDataDelete(index: number): void {
    this.onDataDeleted(index);
  }

  onDataChanged(index: number): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'updated',
        index,
      },
    ]);
  }

  onDataChange(index: number): void {
    this.onDataChanged(index);
  }

  onDatasetChange(dataOperations: DataOperation[]): void {
    const operations: BatchOperation[] = [];
    dataOperations.forEach((operation) => {
      switch (operation.type) {
        case 'add':
        case 'delete':
          if (operation.count === undefined || operation.count > 0) {
            operations.push({
              kind: operation.type === 'add' ? 'added' : 'deleted',
              startIndex: operation.index,
              count: operation.count ?? 1,
            });
          }
          break;
        case 'change':
          operations.push({
            kind: 'updated',
            index: operation.index,
          });
          break;
        case 'reload':
          operations.push({
            kind: 'reloaded',
            totalCount: this.dataSource.totalCount(),
          });
          break;
        case 'exchange':
          operations.push({
            kind: 'swapped',
            a: operation.index.start,
            b: operation.index.end,
          });
          break;
        case 'move':
          operations.push({
            kind: 'moved',
            from: operation.index.from,
            to: operation.index.to,
          });
          break;
        default:
          assertNever(operation);
      }
    });
    this.simpleChangeListener.batchUpdate(operations);
  }

  setDataSource(dataSource: IDataSource): void {
    if (this.dataSource) {
      this.dataSource.unregisterDataChangeListener(this);
    }
    this.dataSource = dataSource;
    this.dataSource.registerDataChangeListener(this);
    this.onDataReloaded();
  }
}
