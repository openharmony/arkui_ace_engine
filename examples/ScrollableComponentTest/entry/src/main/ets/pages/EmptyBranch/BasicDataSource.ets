/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

abstract class BasicDataSource<T> implements IDataSource {
  private listeners: DataChangeListener[] = []

  abstract totalCount(): number

  abstract getData(index: number): T

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      console.info('add listener')
      this.listeners.push(listener)
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      console.info('remove listener')
      this.listeners.splice(pos, 1)
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded()
    })
  }

  notifyDataAdd(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDatasetChange([{ type: DataOperationType.ADD, index: index } as DataAddOperation]);
    })
  }

  notifyDataChange(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDatasetChange([{ type: DataOperationType.CHANGE, index: index } as DataChangeOperation]);
    })
  }

  notifyDataDelete(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDatasetChange([{ type: DataOperationType.DELETE, index: index } as DataDeleteOperation]);
    })
  }

  notifyDataMove(from: number, to: number): void {
    this.listeners.forEach(listener => {
      listener.onDatasetChange([{ type: DataOperationType.MOVE, index: { from: from, to: to } } as DataMoveOperation]);
    })
  }

  notifyDatasetChange(operations: DataOperation[]): void {
    this.listeners.forEach(listener => {
      listener.onDatasetChange(operations);
    })
  }
}

export class MyDataSource<T> extends BasicDataSource<T> {
  public dataArray: T[] = []

  constructor() {
    super();
    for (let i = 0; i < 40; i++) {
      this.dataArray.push(i as T);
    }
  }

  public clear(): void {
    this.dataArray = [] as T[];
  }

  public totalCount(): number {
    return this.dataArray.length
  }

  public getData(index: number): T {
    return this.dataArray[index]
  }

  public addData(index: number, data: T): void {
    this.dataArray.splice(index, 0, data) // 在index位置增加data
    this.notifyDataAdd(index)
  }

  public dataReload(): void {
    this.notifyDataReload()
  }

  public pushData(data: T): void {
    this.dataArray.push(data)
    this.notifyDataAdd(this.dataArray.length - 1)
  }

  public deleteIndex(index: number): void {
    this.dataArray.splice(index, 1);
    this.notifyDataDelete(index);
  }

  public deleteData(data: T): void {
    let index = this.dataArray.indexOf(data)
    this.dataArray.splice(index, 1);
    this.notifyDataDelete(index);
  }

  public moveData(from: number, to: number) {
    this.notifyDataMove(from, to)
  }

  public changeData(index: number, data: T) {
    this.dataArray[index] = data
    this.notifyDataChange(index)
  }

  public indexOf(data: T): number {
    return this.dataArray.indexOf(data)
  }

  public addOperateData(items: T[]): void {
    this.dataArray.splice(20, 0, ...items);
    this.notifyDatasetChange([
      { type: DataOperationType.ADD, index: 20, count: 100 } as DataAddOperation]);
  }

  public DeloperateData(): void {
    this.dataArray.splice(20, 100);
    this.notifyDatasetChange([
      { type: DataOperationType.DELETE, index: 20, count: 100 } as DataDeleteOperation] as DataOperation[]);
  }

  public addLastItem(): void {
    this.dataArray.splice(this.dataArray.length, 0);
    this.notifyDataAdd(this.dataArray.length - 1);
  }

  // 在指定索引位置删除一个元素
  public deleteItem(index: number): void {
    this.dataArray.splice(index, 1);
    this.notifyDataDelete(index);
  }

  // 在指定索引位置增加一个元素
  public addItem(index: number): void {
    this.dataArray.splice(index, 0);
    this.notifyDataAdd(index);
  }
}