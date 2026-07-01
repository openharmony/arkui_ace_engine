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
import {
  IDataSource,
  DataChangeListener,
} from '@ohos.arkui.component'

export class BasicDataSource<T> implements IDataSource<T> {
  private listeners: Array<DataChangeListener> = []
  protected dataArray: Array<T> = []

  public totalCount(): int {
    return this.dataArray.length
  }

  public getData(index: int): T {
    return this.dataArray[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener)
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos: int = this.listeners.indexOf(listener)
    if (pos >= 0) {
      this.listeners.splice(pos, 1)
    }
  }

  notifyDataReload(): void {
    for (let i: int = 0; i < this.listeners.length; i++) {
      this.listeners[i].onDataReloaded()
    }
  }

  notifyDataAdd(index: int): void {
    for (let i: int = 0; i < this.listeners.length; i++) {
      this.listeners[i].onDataAdd(index)
    }
  }

  notifyDataChange(index: int): void {
    for (let i: int = 0; i < this.listeners.length; i++) {
      this.listeners[i].onDataChange(index)
    }
  }

  notifyDataDelete(index: int): void {
    for (let i: int = 0; i < this.listeners.length; i++) {
      this.listeners[i].onDataDelete(index)
    }
  }

  notifyDataMove(from: int, to: int): void {
    for (let i: int = 0; i < this.listeners.length; i++) {
      this.listeners[i].onDataMove(from, to)
    }
  }
}

export class LazyDataSource extends BasicDataSource<string> {
  public pushData(data: string): void {
    this.dataArray.push(data)
    this.notifyDataAdd(this.dataArray.length - 1)
  }

  public unshiftData(data: string): void {
    this.dataArray.splice(0, 0, data)
    this.notifyDataAdd(0)
  }

  public shiftData(): void {
    if (this.dataArray.length === 0) {
      return
    }
    this.dataArray.splice(0, 1)
    this.notifyDataDelete(0)
  }

  public popData(): void {
    if (this.dataArray.length === 0) {
      return
    }
    this.dataArray.pop()
    this.notifyDataDelete(this.dataArray.length)
  }

  public clearData(): void {
    this.dataArray = []
    this.notifyDataReload()
  }
}
