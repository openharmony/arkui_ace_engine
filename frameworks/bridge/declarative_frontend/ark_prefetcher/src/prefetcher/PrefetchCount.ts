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

// eslint-disable-next-line @typescript-eslint/no-unused-vars
class PrefetchCount {
  private readonly MAX_SCREENS: number = 4;
  private readonly speedCoef: number = 2.5;
  private maxItems = 0;
  private prefetchCountValueInternal = 0;
  private currentMaxItemsInternal = 0;
  private currentMinItemsInternal = 0;

  constructor(
    private readonly itemsOnScreen: IItemsOnScreenProvider,
    private readonly prefetchRangeRatio: PrefetchRangeRatio,
    private readonly logger: ILogger = dummyLogger,
  ) {
    this.itemsOnScreen = itemsOnScreen;
    this.itemsOnScreen.register(() => {
      this.updateLimits();
    });
    this.prefetchRangeRatio.register(() => {
      this.updateLimits();
    });
  }

  get prefetchCountValue(): number {
    return this.prefetchCountValueInternal;
  }

  set prefetchCountValue(v: number) {
    this.prefetchCountValueInternal = v;
    this.logger.debug(`{"tm":${Date.now()},"prefetch_count":${v}}`);
  }

  get currentMaxItems(): number {
    return this.currentMaxItemsInternal;
  }

  get currentMinItems(): number {
    return this.currentMinItemsInternal;
  }

  getPrefetchCountByRatio(ratio: number): number {
    this.itemsOnScreen.updateSpeed(this.itemsOnScreen.visibleRange.start, this.itemsOnScreen.visibleRange.end - 1);
    const minItems = Math.min(
      this.currentMaxItems,
      Math.ceil(this.speedCoef * this.itemsOnScreen.speed * this.currentMaxItems),
    );
    const prefetchCount = minItems + Math.ceil(ratio * (this.currentMaxItems - minItems));
    this.logger.debug(
      `speed: ${this.itemsOnScreen.speed}, minItems: ${minItems}, ratio: ${ratio}, prefetchCount: ${prefetchCount}`,
    );
    return prefetchCount;
  }

  getRangeToFetch(totalCount: number): IndexRange {
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
    if (start > end) {
      start = end;
    }
    return new IndexRange(start, end);
  }

  private updateLimits(): void {
    this.maxItems = Math.max(this.currentMinItems, Math.ceil(this.MAX_SCREENS * this.itemsOnScreen.meanValue));
    this.updateCurrentLimit();
  }

  private updateCurrentLimit(): void {
    this.currentMaxItemsInternal = Math.max(
      this.currentMinItems,
      Math.ceil(this.maxItems * this.prefetchRangeRatio.maxRatio),
    );
    this.currentMinItemsInternal = Math.ceil(this.maxItems * this.prefetchRangeRatio.minRatio);
  }
}
