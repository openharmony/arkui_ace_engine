'use static'

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

import { IDataSource, DataChangeListener } from '@kit.ArkUI';

// 实现IDataSource接口的对象，用于瀑布流组件加载数据
export class WaterFlowDataSource implements IDataSource<int> {
  private dataArray: int[] = [];
  private listeners: DataChangeListener[] = [];

  constructor(count: int) {
    for (let i: int = 0; i < count; i++) {
      this.dataArray.push(i);
    }
  }

  // 获取索引对应的数据
  public getData(index: int): int {
    return this.dataArray[index];
  }

  // 通知控制器数据重新加载
  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  // 通知控制器数据增加
  notifyDataAdd(index: int): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
    })
  }

  // 通知控制器数据变化
  notifyDataChange(index: int): void {
    this.listeners.forEach(listener => {
      listener.onDataChange(index);
    })
  }

  // 通知控制器数据删除
  notifyDataDelete(index: int): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
    })
  }

  // 通知控制器数据位置变化
  notifyDataMove(from: int, to: int): void {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to);
    })
  }

  // 获取数据总数
  public totalCount(): int {
    return this.dataArray.length;
  }

  // 注册改变数据的控制器
  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  // 注销改变数据的控制器
  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos: int = this.listeners.indexOf(listener)
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  // 增加数据
  public add1stItem(): void {
    this.dataArray.splice(0, 0, this.dataArray.length);
    this.notifyDataAdd(0);
  }

  // 在数据尾部增加一个元素
  public addLastItem(): void {
    this.dataArray.splice(this.dataArray.length, 0, this.dataArray.length);
    this.notifyDataAdd(this.dataArray.length - 1);
  }
  // [Start addNewItems_start]
  public addNewItems(count: int): void {
    for (let i: int = 0; i < count; i++) {
      this.dataArray.push(this.dataArray.length);
      this.notifyDataAdd(this.dataArray.length - 1);
    }
  }
  // [End addNewItems_start]

  // 在指定索引位置增加一个元素
  public addItem(index: int): void {
    this.dataArray.splice(index, 0, this.dataArray.length);
    this.notifyDataAdd(index);
  }

  // 删除第一个元素
  public delete1stItem(): void {
    this.dataArray.splice(0, 1);
    this.notifyDataDelete(0);
  }

  // 删除第二个元素
  public delete2ndItem(): void {
    this.dataArray.splice(1, 1);
    this.notifyDataDelete(1);
  }

  // 删除最后一个元素
  public deleteLastItem(): void {
    this.dataArray.splice(-1, 1);
    this.notifyDataDelete(this.dataArray.length);
  }

  // 在指定索引位置增加一个元素
  public deleteItem(index: int): void {
    this.dataArray.splice(index, 1);
    this.notifyDataDelete(index);
  }

  // 重新加载数据
  public reload(): void {
    this.dataArray.splice(1, 1);
    this.dataArray.splice(3, 2);
    this.notifyDataReload();
  }
}
