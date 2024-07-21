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

interface ToleranceRange {
  leftToleranceEdge: number;
  rightToleranceEdge: number;
  prefetchCountMaxRatioLeft: number;
  prefetchCountMaxRatioRight: number;
}

type UpdateResult = 'ratio-changed' | 'ratio-not-changed';

class PrefetchRangeRatio {
  private readonly itemsOnScreen: ItemsOnScreenProvider;
  private readonly fetchedRegistry: FetchedRegistry;
  private readonly TOLERANCE_RANGES: [ToleranceRange, ToleranceRange] = [
    {
      leftToleranceEdge: 180,
      rightToleranceEdge: 250,
      prefetchCountMaxRatioLeft: 0.5,
      prefetchCountMaxRatioRight: 1,
    },
    {
      leftToleranceEdge: 3000,
      rightToleranceEdge: 4000,
      prefetchCountMaxRatioLeft: 1,
      prefetchCountMaxRatioRight: 0.25,
    },
  ];
  private readonly ACTIVE_DEGREE = 0.5;
  private readonly VISIBLE_DEGREE = 2.5;
  private meanPrefetchTime = 0;
  private leftToleranceEdge = Number.MIN_VALUE;
  private rightToleranceEdge = 250;
  private oldRatio = 0;

  constructor(itemsOnScreen: ItemsOnScreenProvider, fetchedRegistry: FetchedRegistry) {
    this.itemsOnScreen = itemsOnScreen;
    this.fetchedRegistry = fetchedRegistry;
  }

  private _range = RatioRange.newEmpty();

  get range(): RatioRange {
    return this._range;
  }

  private _maxRatio = 0.5;

  get maxRatio(): number {
    return this._maxRatio;
  }

  private updateTiming(prefetchDuration: number): void {
    // Check if not from file storage
    if (prefetchDuration > 20) {
      const weight = 0.95;
      this.meanPrefetchTime = this.meanPrefetchTime * weight + (1 - weight) * prefetchDuration;
    }
    Logger.log(`prefetchDifference prefetchDur=${prefetchDuration}, meanPrefetchDur=${this.meanPrefetchTime}`);
  }

  update(prefetchDuration: number): UpdateResult {
    this.updateTiming(prefetchDuration);

    if (this.meanPrefetchTime >= this.leftToleranceEdge && this.meanPrefetchTime <= this.rightToleranceEdge) {
      return 'ratio-not-changed';
    }

    let ratioChanged = false;

    if (this.meanPrefetchTime > this.rightToleranceEdge) {
      for (let i = 0; i < this.TOLERANCE_RANGES.length; i++) {
        const limit = this.TOLERANCE_RANGES[i];
        if (this.meanPrefetchTime > limit.rightToleranceEdge) {
          ratioChanged = true;
          this._maxRatio = limit.prefetchCountMaxRatioRight;
          this.leftToleranceEdge = limit.leftToleranceEdge;
          if (i + 1 !== this.TOLERANCE_RANGES.length) {
            this.rightToleranceEdge = this.TOLERANCE_RANGES[i + 1].rightToleranceEdge;
          } else {
            this.rightToleranceEdge = Number.MAX_VALUE;
          }
        }
      }
    } else if (this.meanPrefetchTime < this.leftToleranceEdge) {
      for (let i = this.TOLERANCE_RANGES.length - 1; i >= 0; i--) {
        const limit = this.TOLERANCE_RANGES[i];
        if (this.meanPrefetchTime < limit.leftToleranceEdge) {
          ratioChanged = true;
          this._maxRatio = limit.prefetchCountMaxRatioLeft;
          this.rightToleranceEdge = limit.rightToleranceEdge;
          if (i !== 0) {
            this.leftToleranceEdge = this.TOLERANCE_RANGES[i - 1].leftToleranceEdge;
          } else {
            this.leftToleranceEdge = Number.MIN_VALUE;
          }
        }
      }
    }
    return ratioChanged ? 'ratio-changed' : 'ratio-not-changed';
  }

  calculateRatio(prefetchCount: number, totalCount: number): number {
    const visibleRange = this.itemsOnScreen.visibleRange;

    const start = Math.max(0, visibleRange.start - prefetchCount);
    const end = Math.min(totalCount, visibleRange.end + prefetchCount);
    const evaluatedPrefetchRange = new IndexRange(start, end);

    const completedActive = this.fetchedRegistry.getFetchedInRange(evaluatedPrefetchRange);
    const completedVisible = this.fetchedRegistry.getFetchedInRange(visibleRange);

    return Math.min(
      1,
      Math.pow(completedActive / evaluatedPrefetchRange.length, this.ACTIVE_DEGREE) *
        Math.pow(completedVisible / visibleRange.length, this.VISIBLE_DEGREE),
    );
  }

  updateRatioRange(ratio: number): void {
    if (ratio > this.oldRatio) {
      this._range = new RatioRange(new RangeEdge(this.oldRatio, false), new RangeEdge(ratio, true));
    } else {
      this._range = new RatioRange(new RangeEdge(ratio, true), new RangeEdge(this.oldRatio, false));
    }
    this.oldRatio = ratio;
  }
}
