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

class PrefetchCount {
  private readonly itemsOnScreen: IItemsOnScreenProvider;
  private readonly MAX_SCREENS = 4;
  private readonly MIN_SCREENS = 0.6;
  private min = 0;
  private max = 0;

  constructor(itemsOnScreen: IItemsOnScreenProvider) {
    this.itemsOnScreen = itemsOnScreen;
    this.itemsOnScreen.register(() => {
      this.updateLimits();
    });
  }

  private _prefetchCountValue = 0;

  get prefetchCountValue(): number {
    return this._prefetchCountValue;
  }

  set prefetchCountValue(v: number) {
    this._prefetchCountValue = v;
    Logger.log(`{"tm":${Date.now()},"prefetch_count":${v}}`);
  }

  private _currentLimit = 0;

  get currentLimit(): number {
    return this._currentLimit;
  }

  private _maxRatio = 0.5;

  get maxRatio(): number {
    return this._maxRatio;
  }

  set maxRatio(value: number) {
    this._maxRatio = value;
    this.updateCurrentLimit();
  }

  getPrefetchCountByRatio(ratio: number): number {
    return this.min + Math.ceil(ratio * (this.currentLimit - this.min));
  }

  getRangeToPrefetch(totalCount: number): IndexRange {
    const visibleRange = this.itemsOnScreen.visibleRange;
    let start = 0;
    let end = 0;
    switch (this.itemsOnScreen.direction) {
      case 'UNKNOWN':
        start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue));
        end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue));
        break;
      case 'UP':
        start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue));
        end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue * 0.5));
        break;
      case 'DOWN':
        start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue * 0.5));
        end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue));
        break;
    }
    return new IndexRange(start, end);
  }

  private updateLimits(): void {
    this.min = Math.ceil(this.itemsOnScreen.meanValue * this.MIN_SCREENS);
    this.max = Math.max(this.min, Math.ceil(this.MAX_SCREENS * this.itemsOnScreen.meanValue));
    this.updateCurrentLimit();
  }

  private updateCurrentLimit(): void {
    this._currentLimit = Math.max(this.min, Math.ceil(this.max * this._maxRatio));
  }
}
