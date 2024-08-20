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

interface IPrefetchRangeEvaluator {
  get rangeToPrefetch(): IndexRange;
  setTotal(totalItems: number): void;
  visibleRangeChanged(minVisible: number, maxVisible: number): void;
  itemPrefetched(index: number, fetchDuration: number): void;
}

class PrefetchRangeEvaluator implements IPrefetchRangeEvaluator {
  private readonly itemsOnScreen = new ItemsOnScreenProvider();
  private readonly prefetchCount = new PrefetchCount(this.itemsOnScreen);
  private readonly fetchedRegistry = new FetchedRegistry();
  private readonly prefetchRangeRatio = new PrefetchRangeRatio(this.itemsOnScreen, this.fetchedRegistry);
  private totalItems = 0;
  private rangeToPrefetch_ = new IndexRange(0, 0);

  get rangeToPrefetch(): IndexRange {
    return this.rangeToPrefetch_;
  }

  setTotal(totalItems: number): void {
    this.totalItems = totalItems;
  }

  visibleRangeChanged(minVisible: number, maxVisible: number): void {
    this.itemsOnScreen.update(minVisible, maxVisible);

    Logger.log(
      `visibleAreaChanged itemsOnScreen=${
        Math.abs(maxVisible - minVisible) + 1
      }, meanImagesOnScreen=${this.itemsOnScreen.meanValue}, prefetchCountCurrentLimit=${this.prefetchCount.currentLimit}, prefetchCountMaxRatio=${this.prefetchCount.maxRatio}`,
    );

    // +1 for inclusive maxVisible -> exclusive end
    this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('visible-area-changed');
    this.rangeToPrefetch_ = this.prefetchCount.getRangeToPrefetch(this.totalItems);
    this.fetchedRegistry.updateRangeToPrefetch(this.rangeToPrefetch_);
  }

  itemPrefetched(index: number, fetchDuration: number): void {
    let maxRatioChanged = false;
    if (this.prefetchRangeRatio.update(fetchDuration) === 'ratio-changed') {
      this.prefetchCount.maxRatio = this.prefetchRangeRatio.maxRatio;
      maxRatioChanged = true;
      Logger.log(
        `choosePrefetchCountLimit prefetchCountMaxRatio=${this.prefetchCount.maxRatio}, prefetchCountCurrentLimit=${this.prefetchCount.currentLimit}`,
      );
    }

    this.fetchedRegistry.addFetched(index);

    this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('resolved', maxRatioChanged);
    this.rangeToPrefetch_ = this.prefetchCount.getRangeToPrefetch(this.totalItems);
    this.fetchedRegistry.updateRangeToPrefetch(this.rangeToPrefetch_);
  }

  private evaluatePrefetchCount(event: 'resolved' | 'visible-area-changed', maxRatioChanged?: boolean): number {
    const ratio = this.prefetchRangeRatio.calculateRatio(this.prefetchCount.prefetchCountValue, this.totalItems);
    let evaluatedPrefetchCount = this.prefetchCount.getPrefetchCountByRatio(ratio);

    let nextRatio: number | undefined;

    if (maxRatioChanged) {
      nextRatio = this.prefetchRangeRatio.calculateRatio(evaluatedPrefetchCount, this.totalItems);
      evaluatedPrefetchCount = this.prefetchCount.getPrefetchCountByRatio(nextRatio);
    }

    if (
      this.prefetchRangeRatio.range.contains(ratio) ||
      (event === 'resolved' && evaluatedPrefetchCount <= this.prefetchCount.prefetchCountValue)
    ) {
      return this.prefetchCount.prefetchCountValue;
    }

    this.prefetchRangeRatio.updateRatioRange(ratio);
    Logger.log(
      `evaluatePrefetchCount prefetchCount=${evaluatedPrefetchCount}, ratio=${ratio}, nextRatio=${nextRatio}, hysteresisRange=${this.prefetchRangeRatio.range}`,
    );
    return evaluatedPrefetchCount;
  }
}
