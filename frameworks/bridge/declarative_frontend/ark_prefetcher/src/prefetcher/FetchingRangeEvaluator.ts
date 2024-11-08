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

interface IFetchingRangeEvaluator {
  updateRangeToFetch(whatHappened: RangeUpdateEvent): void;
}

type RangeUpdateEvent =
  | {
      kind: 'visible-area-changed';
      minVisible: number;
      maxVisible: number;
    }
  | {
      kind: 'item-fetched';
      itemIndex: number;
      fetchDuration: number;
    }
  | {
      kind: 'collection-changed';
      totalCount: number;
    }
  | {
      kind: 'item-added';
      itemIndex: number;
    }
  | {
      kind: 'item-removed';
      itemIndex: number;
    };

// eslint-disable-next-line @typescript-eslint/no-unused-vars
class FetchingRangeEvaluator implements IFetchingRangeEvaluator {
  protected totalItems = 0;

  constructor(
    private readonly itemsOnScreen: ItemsOnScreenProvider,
    private readonly prefetchCount: PrefetchCount,
    private readonly prefetchRangeRatio: PrefetchRangeRatio,
    protected readonly fetchedRegistry: FetchedRegistry,
    private readonly logger: ILogger = dummyLogger,
  ) {}

  updateRangeToFetch(whatHappened: RangeUpdateEvent): void {
    switch (whatHappened.kind) {
      case 'visible-area-changed':
        this.onVisibleAreaChange(whatHappened.minVisible, whatHappened.maxVisible);
        break;
      case 'item-fetched':
        this.onItemFetched(whatHappened.itemIndex, whatHappened.fetchDuration);
        break;
      case 'collection-changed':
        this.onCollectionChanged(whatHappened.totalCount);
        break;
      case 'item-added':
        this.onItemAdded(whatHappened.itemIndex);
        break;
      case 'item-removed':
        this.onItemDeleted(whatHappened.itemIndex);
        break;
      default:
        assertNever(whatHappened);
    }
  }

  protected onVisibleAreaChange(minVisible: number, maxVisible: number): void {
    const oldVisibleRange = this.itemsOnScreen.visibleRange;
    this.itemsOnScreen.update(minVisible, maxVisible);

    this.logger.debug(
      `visibleAreaChanged itemsOnScreen=${this.itemsOnScreen.visibleRange.length}, meanImagesOnScreen=${this.itemsOnScreen.meanValue}, prefetchCountCurrentLimit=${this.prefetchCount.currentMaxItems}, prefetchCountMaxRatio=${this.prefetchRangeRatio.maxRatio}`,
    );

    if (!oldVisibleRange.equals(this.itemsOnScreen.visibleRange)) {
      this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('visible-area-changed');
      const rangeToFetch = this.prefetchCount.getRangeToFetch(this.totalItems);
      this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
    }
  }

  protected onItemFetched(index: number, fetchDuration: number): void {
    if (!this.fetchedRegistry.rangeToFetch.contains(index)) {
      return;
    }

    this.logger.debug(`onItemFetched`);
    let maxRatioChanged = false;
    if (this.prefetchRangeRatio.update(index, fetchDuration) === 'ratio-changed') {
      maxRatioChanged = true;
      this.logger.debug(
        `choosePrefetchCountLimit prefetchCountMaxRatio=${this.prefetchRangeRatio.maxRatio}, prefetchCountMinRatio=${this.prefetchRangeRatio.minRatio}, prefetchCountCurrentLimit=${this.prefetchCount.currentMaxItems}`,
      );
    }

    this.fetchedRegistry.addFetched(index);

    this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('resolved', maxRatioChanged);
    const rangeToFetch = this.prefetchCount.getRangeToFetch(this.totalItems);
    this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
  }

  private evaluatePrefetchCount(event: 'resolved' | 'visible-area-changed', maxRatioChanged?: boolean): number {
    let ratio = this.prefetchRangeRatio.calculateRatio(this.prefetchCount.prefetchCountValue, this.totalItems);
    let evaluatedPrefetchCount = this.prefetchCount.getPrefetchCountByRatio(ratio);

    if (maxRatioChanged) {
      ratio = this.prefetchRangeRatio.calculateRatio(evaluatedPrefetchCount, this.totalItems);
      evaluatedPrefetchCount = this.prefetchCount.getPrefetchCountByRatio(ratio);
    }

    if (!this.prefetchRangeRatio.hysteresisEnabled) {
      if (event === 'resolved') {
        this.prefetchRangeRatio.updateRatioRange(ratio);
        this.prefetchRangeRatio.hysteresisEnabled = true;
      } else if (event === 'visible-area-changed') {
        this.prefetchRangeRatio.oldRatio = ratio;
      }
    } else if (this.prefetchRangeRatio.range.contains(ratio)) {
      return this.prefetchCount.prefetchCountValue;
    } else {
      if (event === 'resolved') {
        this.prefetchRangeRatio.updateRatioRange(ratio);
      } else if (event === 'visible-area-changed') {
        this.prefetchRangeRatio.setEmptyRange();
        this.prefetchRangeRatio.oldRatio = ratio;
        this.prefetchRangeRatio.hysteresisEnabled = false;
      }
    }

    this.logger.debug(
      `evaluatePrefetchCount event=${event}, ${this.prefetchRangeRatio.hysteresisEnabled ? 'inHysteresis' : 'setHysteresis'} prefetchCount=${evaluatedPrefetchCount}, ratio=${ratio}, hysteresisRange=${this.prefetchRangeRatio.range}`,
    );

    return evaluatedPrefetchCount;
  }

  protected onCollectionChanged(totalCount: number): void {
    this.totalItems = Math.max(0, totalCount);
    let newRangeToFetch: IndexRange;
    if (this.fetchedRegistry.rangeToFetch.length > 0) {
      newRangeToFetch = this.itemsOnScreen.visibleRange;
    } else {
      newRangeToFetch = this.fetchedRegistry.rangeToFetch;
    }
    if (newRangeToFetch.end > this.totalItems) {
      const end = this.totalItems;
      const start = newRangeToFetch.start < end ? newRangeToFetch.start : end;
      newRangeToFetch = new IndexRange(start, end);
    }

    this.fetchedRegistry.clearFetched(newRangeToFetch);
  }

  private onItemDeleted(itemIndex: number): void {
    if (this.totalItems === 0) {
      return;
    }
    this.totalItems--;
    this.fetchedRegistry.removeFetched(itemIndex);

    const end =
      this.fetchedRegistry.rangeToFetch.end < this.totalItems ? this.fetchedRegistry.rangeToFetch.end : this.totalItems;
    const rangeToFetch = new IndexRange(this.fetchedRegistry.rangeToFetch.start, end);

    this.fetchedRegistry.decrementFetchedGreaterThen(itemIndex, rangeToFetch);
  }

  private onItemAdded(itemIndex: number): void {
    this.totalItems++;
    if (itemIndex > this.fetchedRegistry.rangeToFetch.end) {
      return;
    }

    const end = this.fetchedRegistry.rangeToFetch.end + 1;
    const rangeToFetch = new IndexRange(this.fetchedRegistry.rangeToFetch.start, end);
    this.fetchedRegistry.incrementFetchedGreaterThen(itemIndex - 1, rangeToFetch);
  }
}
