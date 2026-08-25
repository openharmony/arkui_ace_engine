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

// Shared LazyForEach data source for the WaterFlow contentClip lazy-child demos.
export class LazyNumberSource implements IDataSource {
  private data: number[] = [];
  private listeners: DataChangeListener[] = [];

  constructor(count: number, base: number = 0) {
    this.fill(count, base);
  }

  private fill(count: number, base: number): void {
    this.data = [];
    for (let i = 0; i < count; i++) {
      this.data.push(base + i);
    }
  }

  public totalCount(): number {
    return this.data.length;
  }

  public getData(index: number): number {
    return this.data[index];
  }

  // Rebuild the whole data set and notify LazyForEach to reload.
  public reload(count: number, base: number): void {
    this.fill(count, base);
    this.listeners.forEach((listener: DataChangeListener) => {
      listener.onDataReloaded();
    });
  }

  public registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  public unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }
}
