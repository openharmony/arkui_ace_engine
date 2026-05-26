/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

// 实现IDataSource接口的对象，用于瀑布流组件加载数据
export class BasicDataSource<T> implements IDataSource {
  private originDataArray: T[] = [];
  private listeners: DataChangeListener[] = [];

  public totalCount(): number {
    return 0;
  }

  public getData(index: number): T {
    return this.originDataArray[index];
  }

  // 注册改变数据的控制器
  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  // 注销改变数据的控制器
  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  // 通知控制器数据重新加载
  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  //通知控制器数据批量修改
  notifyDatasetChange(operations: DataOperation[]): void {
    this.listeners.forEach(listener => {
      listener.onDatasetChange(operations);
    })
  }
}

export class ObservedArray<T> extends Array<T> {
  constructor(args: T[]) {
    if (args instanceof Array) {
      super(...args);
    } else {
      super(args);
    }
  }
}

@Observed
export class BaseDataSource<T> extends BasicDataSource<T> {
  private dataArray: ObservedArray<T> = [];

  public totalCount(): number {
    return this.dataArray.length;
  }

  /**
   * 获取数据
   * @param index
   * @returns
   */
  public getData(index: number): T {
    return this.dataArray[index];
  }
  /**
   * 在末尾添加一个数组
   * @param data
   */
  public addAllData(data: Array<T>): void {
    const totalCount = this.dataArray.length;
    this.dataArray.push(...data);
    this.notifyDatasetChange([{
      type: DataOperationType.ADD, index: totalCount, count: data.length
    }])
  }
}