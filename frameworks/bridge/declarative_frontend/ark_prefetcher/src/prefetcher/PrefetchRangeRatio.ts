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
  prefetchCountMinRatioLeft: number;
  prefetchCountMaxRatioLeft: number;
  prefetchCountMinRatioRight: number;
  prefetchCountMaxRatioRight: number;
}

type PrefetchCountMaxChangedCallback = () => void;

type UpdateResult = 'ratio-changed' | 'ratio-not-changed';

// eslint-disable-next-line @typescript-eslint/no-unused-vars
class PrefetchRangeRatio {
  private readonly TOLERANCE_RANGES: ToleranceRange[] = [
    {
      leftToleranceEdge: 140,
      rightToleranceEdge: 290,
      prefetchCountMinRatioLeft: 0.5,
      prefetchCountMaxRatioLeft: 0.5,
      prefetchCountMinRatioRight: 0.25,
      prefetchCountMaxRatioRight: 1,
    },
    {
      leftToleranceEdge: 3000,
      rightToleranceEdge: 4000,
      prefetchCountMinRatioLeft: 0.25,
      prefetchCountMaxRatioLeft: 1,
      prefetchCountMinRatioRight: 0.25,
      prefetchCountMaxRatioRight: 0.25,
    },
  ];
  private readonly ACTIVE_DEGREE: number = 0;
  private readonly VISIBLE_DEGREE: number = 2.5;
  private meanPrefetchTime = 0;
  private leftToleranceEdge = Number.MIN_VALUE;
  private rightToleranceEdge = 250;

  constructor(
    private readonly itemsOnScreen: ItemsOnScreenProvider,
    private readonly fetchedRegistry: FetchedRegistry,
    private readonly fetchingRegistry: FetchingRegistry,
    private readonly logger: ILogger = dummyLogger,
  ) {}

  private callbacks: PrefetchCountMaxChangedCallback[] = [];

  register(callback: PrefetchCountMaxChangedCallback): void {
    this.callbacks.push(callback);
  }

  private rangeInternal = RatioRange.newEmpty();

  get range(): RatioRange {
    return this.rangeInternal;
  }

  setEmptyRange(): void {
    this.rangeInternal = RatioRange.newEmpty();
  }

  private minRatioInternal = 0.25 * 0.6;
  private maxRatioInternal = 0.5;

  get maxRatio(): number {
    return this.maxRatioInternal;
  }

  get minRatio(): number {
    return this.minRatioInternal;
  }

  private hysteresisEnabledInternal = false;

  get hysteresisEnabled(): boolean {
    return this.hysteresisEnabledInternal;
  }

  set hysteresisEnabled(value: boolean) {
    this.hysteresisEnabledInternal = value;
  }

  private oldRatioInternal = 0;

  set oldRatio(ratio: number) {
    this.oldRatioInternal = ratio;
  }

  get oldRatio(): number {
    return this.oldRatioInternal;
  }

  private updateTiming(index: number, prefetchDuration: number): void {
    const weight = 0.95;
    const localPrefetchDuration = 20;

    let isFetchLocal = prefetchDuration < localPrefetchDuration;
    let isFetchLatecomer = this.fetchingRegistry.isFetchLatecomer(index, this.itemsOnScreen.meanValue);

    if (!isFetchLocal && !isFetchLatecomer) {
      this.meanPrefetchTime = this.meanPrefetchTime * weight + (1 - weight) * prefetchDuration;
    }

    this.logger.debug(
      `prefetchDifference prefetchDur=${prefetchDuration}, meanPrefetchDur=${this.meanPrefetchTime}, ` +
        `isFetchLocal=${isFetchLocal}, isFetchLatecomer=${isFetchLatecomer}`,
    );
  }

  update(index: number, prefetchDuration: number): UpdateResult {
    this.updateTiming(index, prefetchDuration);

    if (this.meanPrefetchTime >= this.leftToleranceEdge && this.meanPrefetchTime <= this.rightToleranceEdge) {
      return 'ratio-not-changed';
    }

    let ratioChanged = false;

    if (this.meanPrefetchTime > this.rightToleranceEdge) {
      ratioChanged = this.updateOnGreaterThanRight();
    } else if (this.meanPrefetchTime < this.leftToleranceEdge) {
      ratioChanged = this.updateOnLessThanLeft();
    }

    if (ratioChanged) {
      this.notifyObservers();
    }

    return ratioChanged ? 'ratio-changed' : 'ratio-not-changed';
  }

  private updateOnLessThanLeft(): boolean {
    let ratioChanged = false;
    for (let i = this.TOLERANCE_RANGES.length - 1; i >= 0; i--) {
      const limit = this.TOLERANCE_RANGES[i];
      if (this.meanPrefetchTime < limit.leftToleranceEdge) {
        ratioChanged = true;
        this.maxRatioInternal = limit.prefetchCountMaxRatioLeft;
        this.minRatioInternal = limit.prefetchCountMinRatioLeft;
        this.rightToleranceEdge = limit.rightToleranceEdge;
        if (i !== 0) {
          this.leftToleranceEdge = this.TOLERANCE_RANGES[i - 1].leftToleranceEdge;
        } else {
          this.leftToleranceEdge = Number.MIN_VALUE;
        }
      }
    }
    return ratioChanged;
  }

  private updateOnGreaterThanRight(): boolean {
    let ratioChanged = false;
    for (let i = 0; i < this.TOLERANCE_RANGES.length; i++) {
      const limit = this.TOLERANCE_RANGES[i];
      if (this.meanPrefetchTime > limit.rightToleranceEdge) {
        ratioChanged = true;
        this.maxRatioInternal = limit.prefetchCountMaxRatioRight;
        this.minRatioInternal = limit.prefetchCountMinRatioRight;
        this.leftToleranceEdge = limit.leftToleranceEdge;
        if (i + 1 !== this.TOLERANCE_RANGES.length) {
          this.rightToleranceEdge = this.TOLERANCE_RANGES[i + 1].rightToleranceEdge;
        } else {
          this.rightToleranceEdge = Number.MAX_VALUE;
        }
      }
    }
    return ratioChanged;
  }

  calculateRatio(prefetchCount: number, totalCount: number): number {
    const visibleRange = this.itemsOnScreen.visibleRange;

    let start: number = 0;
    let end: number = 0;

    switch (this.itemsOnScreen.direction) {
      case 'UNKNOWN':
        start = Math.max(0, visibleRange.start - prefetchCount);
        end = Math.min(totalCount, visibleRange.end + prefetchCount);
        break;
      case 'UP':
        start = Math.max(0, visibleRange.start - prefetchCount);
        end = Math.min(totalCount, visibleRange.end + Math.round(0.5 * prefetchCount));
        break;
      case 'DOWN':
        start = Math.max(0, visibleRange.start - Math.round(0.5 * prefetchCount));
        end = Math.min(totalCount, visibleRange.end + prefetchCount);
        break;
    }

    const evaluatedPrefetchRange = new IndexRange(start, end);
    const completedActive = this.fetchedRegistry.getFetchedInRange(evaluatedPrefetchRange);
    const completedVisible = this.fetchedRegistry.getFetchedInRange(visibleRange);

    if (evaluatedPrefetchRange.length === 0 || visibleRange.length === 0) {
      return 0;
    }

    this.logger.debug(`active_degree=${this.ACTIVE_DEGREE}, visible_degree=${this.VISIBLE_DEGREE}`);
    this.logger.debug(
      `evaluatedPrefetchRange=${evaluatedPrefetchRange}, visibleRange=${visibleRange}, active_ratio=${Math.pow(completedActive / evaluatedPrefetchRange.length, this.ACTIVE_DEGREE)}, visible_ratio=${Math.pow(completedVisible / visibleRange.length, this.VISIBLE_DEGREE)}, completedActive=${completedActive}, evaluatedPrefetchRange.length=${evaluatedPrefetchRange.length}, visibleRange.length=${visibleRange.length}`,
    );

    const ratio =
      Math.pow(completedActive / evaluatedPrefetchRange.length, this.ACTIVE_DEGREE) *
      Math.pow(completedVisible / visibleRange.length, this.VISIBLE_DEGREE);

    this.logger.debug(
      `calculateRatio ratio=${ratio}, completedActive=${completedActive}, evaluatedPrefetchRange.length=${evaluatedPrefetchRange.length}, ` +
        `completedVisible=${completedVisible}, visibleRange.length=${visibleRange.length}`,
    );

    return Math.min(1, ratio);
  }

  updateRatioRange(ratio: number): void {
    if (ratio > this.oldRatioInternal) {
      this.rangeInternal = new RatioRange(new RangeEdge(this.oldRatioInternal, false), new RangeEdge(ratio, true));
    } else {
      this.rangeInternal = new RatioRange(new RangeEdge(ratio, true), new RangeEdge(this.oldRatioInternal, false));
    }
    this.oldRatioInternal = ratio;
  }

  private notifyObservers(): void {
    this.callbacks.forEach((callback) => callback());
  }
}
