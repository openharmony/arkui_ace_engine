/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// HANDWRITTEN, DO NOT REGENERATE

import { DataOperationType, DataAddOperation, DataDeleteOperation, DataChangeOperation, DataMoveOperation,
  DataExchangeOperation, DataOperation, DataChangeListener, IDataSource } from '@ohos.arkui.component'

export interface IDataSourcePrefetching<T> extends IDataSource<T> {
  prefetch(index: int): Promise<void> | undefined;
  cancel(index: int): Promise<void> | undefined { return undefined; };
}

export interface IPrefetcher<T> {
  setDataSource(dataSource: IDataSourcePrefetching<T>): void;
  visibleAreaChanged(minVisible: int, maxVisible: int): void;
}

export class BasicPrefetcher<T> implements IPrefetcher<T> {
  private readonly fetchingDriver: FetchingDriver<T>;

  constructor(dataSource?: IDataSourcePrefetching<T>) {
    const itemsOnScreen = new ItemsOnScreenProvider();
    const fetchedRegistry = new FetchedRegistry();
    const fetchingRegistry = new FetchingRegistry();
    const prefetchRangeRatio = new PrefetchRangeRatio(itemsOnScreen, fetchedRegistry, fetchingRegistry);
    const prefetchCount = new PrefetchCount(itemsOnScreen, prefetchRangeRatio);
    const evaluator = new FetchingRangeEvaluator(itemsOnScreen, prefetchCount, prefetchRangeRatio, fetchedRegistry);
    this.fetchingDriver = new FetchingDriver<T>(fetchedRegistry, fetchingRegistry, evaluator, new DefaultTimeProvider(),
      dataSource);
    if (dataSource) {
      this.fetchingDriver.setDataSource(dataSource);
    }
  }

  setDataSource(dataSource: IDataSourcePrefetching<T>): void {
    this.fetchingDriver.setDataSource(dataSource);
  }

  visibleAreaChanged(minVisible: int, maxVisible: int): void {
    this.fetchingDriver.visibleAreaChanged(minVisible, maxVisible);
  }
}

interface ITimeProvider {
  getCurrent(): long;
}

type Millisecond = int;

class DefaultTimeProvider implements ITimeProvider {
  getCurrent(): long {
    return Date.now() as long;
  }
}

interface DataCollectionChangeListener<T> {
  batchUpdate(operations: BatchOperation[]): void;
}

interface ItemsDeletedOrAdded {
  kind: BatchOperationKind;
  startIndex: int;
  count: int;
}

interface ItemUpdated {
  kind: BatchOperationKind;
  index: int;
}

interface CollectionReloaded {
  kind: BatchOperationKind;
  totalCount: int;
}

interface ItemsSwapped {
  kind: BatchOperationKind;
  a: int;
  b: int;
}

interface ItemMoved {
  kind: BatchOperationKind;
  from: int;
  to: int;
}

type BatchOperation = ItemsDeletedOrAdded | ItemUpdated | CollectionReloaded | ItemsSwapped | ItemMoved;

type BatchOperationKind = 'deleted' | 'added' | 'updated' | 'reloaded' | 'swapped' | 'moved';

const DELAY_TO_REPEAT_FETCH_AFTER_ERROR = 500;

class FetchingDriver<T> implements DataCollectionChangeListener<T> {
  private dataSource: IDataSourcePrefetching<T> | undefined;
  private readonly dataSourceObserver: DataSourceObserver<T>;
  private readonly fetchedRegistry: FetchedRegistry;
  private readonly fetches: FetchingRegistry;
  private readonly prefetchRangeEvaluator: IFetchingRangeEvaluator;
  private readonly timeProvider: ITimeProvider;
  private isPaused: boolean;

  constructor(
    fetchedRegistry: FetchedRegistry,
    fetches: FetchingRegistry,
    prefetchRangeEvaluator: IFetchingRangeEvaluator,
    timeProvider: ITimeProvider,
    dataSource: IDataSourcePrefetching<T> | undefined,
    autostart: boolean = true,
  ) {
    this.fetchedRegistry = fetchedRegistry;
    this.fetches = fetches;
    this.prefetchRangeEvaluator = prefetchRangeEvaluator;
    this.timeProvider = timeProvider;
    this.dataSource = dataSource;
    this.dataSourceObserver = new DataSourceObserver<T>(this, this.dataSource);
    this.isPaused = !autostart;
  }

  get afterErrorDelay(): Millisecond {
    return DELAY_TO_REPEAT_FETCH_AFTER_ERROR;
  }

  batchUpdate(operations: BatchOperation[]): void {
    try {
      this.batchUpdateInternal(operations);
    } catch (error) {
      throw error;
    }
  }

  private batchUpdateInternal(operations: BatchOperation[]): void {
    operations.forEach((operation) => {
      switch (operation.kind) {
        case 'deleted':
          this.itemsDeleted((operation as ItemsDeletedOrAdded).startIndex, (operation as ItemsDeletedOrAdded).count);
          break;
        case 'added':
          this.itemsAdded((operation as ItemsDeletedOrAdded).startIndex, (operation as ItemsDeletedOrAdded).count);
          break;
        case 'updated':
          this.itemUpdated((operation as ItemUpdated).index);
          break;
        case 'reloaded':
          this.collectionChanged((operation as CollectionReloaded).totalCount);
          break;
        case 'swapped':
          this.itemsSwapped((operation as ItemsSwapped).a, (operation as ItemsSwapped).b);
          break;
        case 'moved':
          this.itemMoved((operation as ItemMoved).from, (operation as ItemMoved).to);
          break;
      }
    });

    this.prefetch(this.fetchedRegistry.getItemsToFetch());
  }

  private collectionChanged(totalCount: int): void {
    this.prefetchRangeEvaluator.updateRangeToFetch({
      kind: 'collection-changed',
      totalCount: totalCount,
    } as RangeUpdateEvent);
  }

  private itemUpdated(index: int): void {
    this.fetchedRegistry.removeFetched(index);
    this.fetches.deleteFetchByItem(index);
  }

  private itemsDeleted(index: int, count: int): void {
    for (let i = 0; i < count; i++) {
      this.fetches.decrementAllIndexesGreaterThen(index);
      this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'item-removed', itemIndex: index } as RangeUpdateEvent);
    }
  }

  private itemsAdded(index: int, count: int): void {
    for (let i = 0; i < count; i++) {
      this.fetches.incrementAllIndexesGreaterThen(index - 1);
      this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'item-added', itemIndex: index } as RangeUpdateEvent);
    }
  }

  private itemsSwapped(a: int, b: int): void {
    if (!this.fetchedRegistry.has(a) || !this.fetchedRegistry.has(b)) {
      this.fetchedRegistry.removeFetched(a);
      this.fetchedRegistry.removeFetched(b);
    }
  }

  private itemMoved(from: int, to: int): void {
    if (!this.fetchedRegistry.has(from) || !this.fetchedRegistry.has(to)) {
      const rangeToFetch = this.fetchedRegistry.rangeToFetch;

      this.itemsDeleted(from, 1);
      this.itemsAdded(to, 1);
      this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
    }
  }

  setDataSource(dataSource: IDataSourcePrefetching<T>): void {
    try {
      this.setDataSourceInternal(dataSource);
    } catch (error) {
      throw error;
    }
  }

  private setDataSourceInternal(dataSource: IDataSourcePrefetching<T>): void {
    this.dataSource = dataSource;
    this.dataSourceObserver.setDataSource(dataSource);
  }

  stop(): void {
    try {
      this.stopInternal();
    } catch (error) {
      throw error;
    }
  }

  private stopInternal(): void {
    if (this.isPaused) {
      return;
    }

    this.isPaused = true;
    this.cancel(this.fetches.getAllIndexes());
  }

  start(): void {
    try {
      this.startInternal();
    } catch (error) {
      throw error;
    }
  }

  private startInternal(): void {
    if (!this.isPaused) {
      return;
    }

    this.isPaused = false;
    this.prefetch(this.fetchedRegistry.getItemsToFetch());
  }

  visibleAreaChanged(minVisible: int, maxVisible: int): void {
    try {
      this.visibleAreaChangedInternal(minVisible, maxVisible);
    } catch (error) {
      throw error;
    }
  }

  private visibleAreaChangedInternal(minVisible: int, maxVisible: int): void {
    if (!this.dataSource) {
      throw new Error('No data source');
    }

    const oldRangeToPrefetch = this.fetchedRegistry.rangeToFetch;
    this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'visible-area-changed', minVisible, maxVisible }
      as RangeUpdateEvent);

    this.prefetch(this.fetchedRegistry.getItemsToFetch());

    const toCancel = oldRangeToPrefetch.subtract(this.fetchedRegistry.rangeToFetch).toSet();
    this.cancel(toCancel);
  }

  private prefetch(toPrefetch: ReadonlySet<int>): void {
    if (!this.dataSource || this.isPaused) {
      return;
    }
    toPrefetch.forEach(this.singleFetch);
  }

  private singleFetch = (itemIndex: ItemIndex): void => {
    if (this.fetches.isFetchingItem(itemIndex) || this.fetchedRegistry.has(itemIndex)) {
      return;
    }

    const prefetchStart = this.timeProvider.getCurrent();
    const fetchId = this.fetches.registerFetch(itemIndex);

    try {
      const prefetchResponse = this.dataSource!.prefetch(itemIndex);
      if (!(prefetchResponse instanceof Promise)) {
        this.fetchedCallback(fetchId, prefetchStart);
        return;
      }

      prefetchResponse
        .then(() => this.fetchedCallback(fetchId, prefetchStart))
        .catch((error) => {
          this.errorOnFetchCallback(fetchId, error);
        });
    } catch (error) {
      this.errorOnFetchCallback(fetchId, error);
    }
  };

  private fetchedCallback(fetchId: FetchId, prefetchStart: long): void {
    const itemIndex = this.fetches.getItem(fetchId);
    this.fetches.deleteFetch(fetchId);

    if (itemIndex === undefined) {
      return;
    }

    this.prefetchRangeEvaluator.updateRangeToFetch({
      kind: 'item-fetched',
      itemIndex: itemIndex,
      fetchDuration: this.timeProvider.getCurrent() - prefetchStart,
    } as RangeUpdateEvent);
    this.prefetch(this.fetchedRegistry.getItemsToFetch());
  }

  private errorOnFetchCallback(fetchId: FetchId, error: Object): void {
    const itemIndex = this.fetches.getItem(fetchId);
    this.fetches.deleteFetch(fetchId);
    setTimeout(() => {
      this.prefetch(this.fetchedRegistry.getItemsToFetch());
    }, this.afterErrorDelay);
  }

  private cancel(toCancel: ReadonlySet<int>): void {
    if (!this.dataSource) {
      return;
    }
    toCancel.forEach((itemIndex) => {
      if (!this.fetches.isFetchingItem(itemIndex)) {
        return;
      }

      this.fetches.deleteFetchByItem(itemIndex);

      if (this.dataSource!.cancel) {
        this.dataSource!.cancel!(itemIndex);
      }
    });
  }
}

class IndexRange {
  public readonly start: int; // inclusive
  public readonly end: int; // exclusive

  constructor(start: int, end: int) {
    this.start = start;
    this.end = end;
    if (this.start > this.end) {
      throw new Error('Invalid range');
    }
  }

  get length(): int {
    return this.end - this.start;
  }

  toSet(target?: Set<int>): Set<int> {
    const set = target ?? new Set<int>();
    for (let i = this.start; i < this.end; ++i) {
      set.add(i);
    }
    return set;
  }

  contains(value: IndexRange | int): boolean {
    if (typeof value === 'object') {
      return this.start <= (value as IndexRange).start && (value as IndexRange).end <= this.end;
    } else {
      return this.start <= (value as int) && (value as int) < this.end;
    }
  }

  subtract(other: IndexRange): IndexRangeArray {
    const result = new IndexRangeArray();
    if (other.start > this.start) {
      result.push(new IndexRange(this.start, Math.min(this.end, other.start) as int));
    }
    if (other.end < this.end) {
      result.push(new IndexRange(Math.max(other.end, this.start) as int, this.end));
    }
    return result;
  }

  // Expand the range to contain another.
  // When `this` and `other` intersect, this is a union.
  expandedWith(other: IndexRange): IndexRange {
    return new IndexRange(Math.min(this.start, other.start) as int, Math.max(this.end, other.end) as int);
  }

  forEachIndex(callback: (index: int) => void): void {
    for (let i = this.start; i < this.end; ++i) {
      callback(i);
    }
  }

  equals(other: IndexRange): boolean {
    return this.start === other.start && this.end === other.end;
  }

  toString(): string {
    return `[${this.start}, ${this.end})`;
  }
}

class IndexRangeArray extends Array<IndexRange> {
  forEachIndex(callback: (index: int) => void): void {
    this.forEach((range) => {
      range.forEachIndex(callback);
    });
  }

  toSet(): Set<int> {
    const set = new Set<int>();
    this.forEach((range) => {
      range.toSet(set);
    });
    return set;
  }
}

class FetchedRegistry {
  private fetchedIndexes: Set<int> = new  Set<int>();
  private rangeToFetchInternal: IndexRange = new IndexRange(0, 0);
  private missedIndexes:  Set<int> = new  Set<int>();

  get rangeToFetch(): IndexRange {
    return this.rangeToFetchInternal;
  }

  addFetched(index: int): void {
    if (this.rangeToFetch.contains(index)) {
      this.fetchedIndexes.add(index);
      this.missedIndexes.delete(index);
    }
  }

  removeFetched(index: int): void {
    if (this.rangeToFetch.contains(index)) {
      this.fetchedIndexes.delete(index);
      this.missedIndexes.add(index);
    }
  }

  has(index: int): boolean {
    return this.fetchedIndexes.has(index);
  }

  getFetchedInRange(range: IndexRange): int {
    let fetched = 0;
    range.forEachIndex((index) => {
      fetched += this.fetchedIndexes.has(index) ? 1 : 0;
    });
    return fetched;
  }

  updateRangeToFetch(fetchRange: IndexRange): void {
    this.rangeToFetch.subtract(fetchRange).forEachIndex((index) => {
      this.fetchedIndexes.delete(index);
    });
    this.rangeToFetchInternal = fetchRange;
    this.missedIndexes.clear();
    this.rangeToFetch.forEachIndex((index) => {
      if (!this.fetchedIndexes.has(index)) {
        this.missedIndexes.add(index);
      }
    });
  }

  getItemsToFetch(): Set<int> {
    return new Set<int>(this.missedIndexes);
  }

  incrementFetchedGreaterThen(value: int, newFetchRange: IndexRange): void {
    this.offsetAllGreaterThen(value, 1);
    this.updateRangeToFetch(newFetchRange);
  }

  decrementFetchedGreaterThen(value: int, newFetchRange: IndexRange): void {
    this.offsetAllGreaterThen(value, -1);
    this.updateRangeToFetch(newFetchRange);
  }

  private offsetAllGreaterThen(value: int, offset: int): void {
    const updated = new Set<int>();
    this.fetchedIndexes.forEach((index) => {
      updated.add(index > value ? index + offset : index);
    });
    this.fetchedIndexes = updated;
  }

  clearFetched(newFetchRange: IndexRange): void {
    this.fetchedIndexes.clear();
    this.updateRangeToFetch(newFetchRange);
  }
}

type FetchId = int;
type ItemIndex = int;

class FetchingRegistry {
  private readonly fetches = new Map<FetchId, ItemIndex>();
  private fetching = new Map<ItemIndex, FetchId>();
  private readonly fetchesBefore = new Map<ItemIndex, int>();

  private fetchCounter: int = 0;

  registerFetch(index: ItemIndex): FetchId {
    let fetchId = this.fetching.get(index);
    if (fetchId !== undefined) {
      return fetchId;
    }

    fetchId = ++this.fetchCounter;
    this.fetching.set(index, fetchId);
    this.fetches.set(fetchId, index);
    this.fetchesBefore.set(index, this.fetches.size);

    return fetchId;
  }

  getItem(fetchId: FetchId): ItemIndex | undefined {
    return this.fetches.get(fetchId);
  }

  deleteFetch(fetchId: FetchId): void {
    const index = this.fetches.get(fetchId);
    if (index !== undefined) {
      this.fetching.delete(index);
      this.fetches.delete(fetchId);
    }
  }

  deleteFetchByItem(index: ItemIndex): void {
    const fetchId = this.fetching.get(index);
    if (fetchId !== undefined) {
      this.fetching.delete(index);
      this.fetches.delete(fetchId);
    }
  }

  isFetchingItem(index: ItemIndex): boolean {
    return this.fetching.has(index);
  }

  incrementAllIndexesGreaterThen(value: int): void {
    this.offsetAllIndexesGreaterThen(value, 1);
  }

  getAllIndexes(): Set<int> {
    const set: Set<int> = new Set<int>();
    this.fetching.forEach((fetchId, itemIndex) => { set.add(itemIndex); });
    return set;
  }

  getFetchesCount(): int {
    return this.fetches.size;
  }

  isFetchLatecomer(index: ItemIndex, threshold: number): boolean {
    const size = this.fetchesBefore.get(index);
    if (size !== undefined) {
      return size > threshold;
    }
    return false;
  }

  private offsetAllIndexesGreaterThen(value: int, offset: int): void {
    const newFetching = new Map<ItemIndex, FetchId>();
    this.fetches.forEach((index, fetchId) => {
      const toSet = index > value ? index + offset : index;
      newFetching.set(toSet, fetchId);
      this.fetches.set(fetchId, toSet);
    });
    this.fetching = newFetching;
  }

  decrementAllIndexesGreaterThen(value: int): void {
    this.offsetAllIndexesGreaterThen(value, -1);
  }
}

type VisibleRangeChangedCallback = () => void;

type ScrollDirection = 'UP' | 'DOWN' | 'UNKNOWN';

interface IItemsOnScreenProvider {
  register(callback: VisibleRangeChangedCallback): void;
  get visibleRange(): IndexRange;
  get meanValue(): float;
  get direction(): ScrollDirection;
  get speed(): float;
  updateSpeed(minVisible: int, maxVisible: int): void;
  update(minVisible: int, maxVisible: int): void;
}

class ItemsOnScreenProvider implements IItemsOnScreenProvider {
  private firstScreen: boolean = true;
  private meanImagesOnScreen: float = 0;
  private minVisible: int = 0;
  private maxVisible: int = 0;
  private directionInternal: ScrollDirection = 'UNKNOWN';
  private speedInternal: float = 0;
  private lastUpdateTimestamp: long = 0;
  private visibleRangeInternal: IndexRange = new IndexRange(0, 0);

  private callbacks: Array<VisibleRangeChangedCallback> = [];

  register(callback: VisibleRangeChangedCallback): void {
    this.callbacks.push(callback);
  }

  get visibleRange(): IndexRange {
    return this.visibleRangeInternal;
  }

  get meanValue(): float {
    return this.meanImagesOnScreen;
  }

  get direction(): ScrollDirection {
    return this.directionInternal;
  }

  get speed(): float {
    return this.speedInternal;
  }

  updateSpeed(minVisible: int, maxVisible: int): void {
    const timeDifference: long = Date.now() as long - this.lastUpdateTimestamp;
    if (timeDifference > 0) {
      const speedTau = 100.0;
      const speedWeight = 1 - Math.exp(-timeDifference / speedTau);
      const distance =
        minVisible + (maxVisible - minVisible) / 2.0 - (this.minVisible + (this.maxVisible - this.minVisible) / 2.0);
      const rawSpeed = Math.abs(distance / timeDifference) * 1000.0;
      this.speedInternal = (speedWeight * rawSpeed + (1 - speedWeight) * this.speedInternal) as float;
    }
  }

  update(minVisible: int, maxVisible: int): void {
    if (minVisible !== this.minVisible || maxVisible !== this.maxVisible) {
      if (
        Math.max(minVisible, this.minVisible) === minVisible &&
          Math.max(maxVisible, this.maxVisible) === maxVisible
      ) {
        this.directionInternal = 'DOWN';
      } else if (
        Math.min(minVisible, this.minVisible) === minVisible &&
          Math.min(maxVisible, this.maxVisible) === maxVisible
      ) {
        this.directionInternal = 'UP';
      }
    }

    let imagesOnScreen: int = maxVisible - minVisible + 1;
    let oldMeanImagesOnScreen: float = this.meanImagesOnScreen;
    if (this.firstScreen) {
      this.meanImagesOnScreen = imagesOnScreen;
      this.firstScreen = false;
      this.lastUpdateTimestamp = Date.now() as long;
    } else {
      const imagesWeight = 0.95;
      this.meanImagesOnScreen = (this.meanImagesOnScreen * imagesWeight + (1 - imagesWeight) * imagesOnScreen)
        as float;
      this.updateSpeed(minVisible, maxVisible);
    }

    this.minVisible = minVisible;
    this.maxVisible = maxVisible;

    const visibleRangeSizeChanged: boolean = Math.ceil(oldMeanImagesOnScreen) !== Math.ceil(this.meanImagesOnScreen);
    this.visibleRangeInternal = new IndexRange(minVisible, maxVisible + 1);

    if (visibleRangeSizeChanged) {
      this.notifyObservers();
    }
    this.lastUpdateTimestamp = Date.now() as long;
  }

  private notifyObservers(): void {
    this.callbacks.forEach((callback) => callback());
  }
}

class RangeEdge {
  public readonly value: float;
  public readonly inclusive: boolean;
  constructor(value: float, inclusive: boolean) {
    this.value = value;
    this.inclusive = inclusive;
  }
}

class RatioRange {
  public readonly start: RangeEdge;
  public readonly end: RangeEdge;

  constructor(start: RangeEdge, end: RangeEdge) {
    this.start = start;
    this.end = end;
    if (this.start.value > this.end.value) {
      throw new Error(`RatioRange: ${this.start.value} > ${this.end.value}`);
    }
  }

  static newEmpty(): RatioRange {
    return new RatioRange(new RangeEdge(0, false), new RangeEdge(0, false));
  }

  contains(point: number): boolean {
    if (point === this.start.value) {
      return this.start.inclusive;
    }
    if (point === this.end.value) {
      return this.end.inclusive;
    }
    return this.start.value < point && point < this.end.value;
  }

  toString(): string {
    return `${this.start.inclusive ? '[' : '('}${this.start.value}, ${this.end.value}${this.end.inclusive ? ']' : ')'}`;
  }
}

interface ToleranceRange {
  leftToleranceEdge: float;
  rightToleranceEdge: float;
  prefetchCountMinRatioLeft: float;
  prefetchCountMaxRatioLeft: float;
  prefetchCountMinRatioRight: float;
  prefetchCountMaxRatioRight: float;
}

type PrefetchCountMaxChangedCallback = () => void;

type UpdateResult = 'ratio-changed' | 'ratio-not-changed';

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
  private readonly ACTIVE_DEGREE: float = 0;
  private readonly VISIBLE_DEGREE: float = 2.5;
  private meanPrefetchTime: float = 0;
  private leftToleranceEdge: float = Number.MIN_VALUE as float;
  private rightToleranceEdge: float = 250;

  private readonly itemsOnScreen: ItemsOnScreenProvider;
  private readonly fetchedRegistry: FetchedRegistry;
  private readonly fetchingRegistry: FetchingRegistry;

  constructor(
    itemsOnScreen: ItemsOnScreenProvider,
    fetchedRegistry: FetchedRegistry,
    fetchingRegistry: FetchingRegistry,
  ) {
    this.itemsOnScreen = itemsOnScreen;
    this.fetchedRegistry = fetchedRegistry;
    this.fetchingRegistry = fetchingRegistry;
  }

  private callbacks: Array<PrefetchCountMaxChangedCallback> = [];

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

  private minRatioInternal: float = (0.25 * 0.6) as float;
  private maxRatioInternal: float = 0.5 as float;

  get maxRatio(): float {
    return this.maxRatioInternal;
  }

  get minRatio(): float {
    return this.minRatioInternal;
  }

  private hysteresisEnabledInternal: boolean = false;

  get hysteresisEnabled(): boolean {
    return this.hysteresisEnabledInternal;
  }

  set hysteresisEnabled(value: boolean) {
    this.hysteresisEnabledInternal = value;
  }

  private oldRatioInternal: float = 0;

  set oldRatio(ratio: float) {
    this.oldRatioInternal = ratio;
  }

  get oldRatio(): float {
    return this.oldRatioInternal;
  }

  private updateTiming(index: int, prefetchDuration: float): void {
    const weight = 0.95;
    const localPrefetchDuration = 20;

    let isFetchLocal: boolean = prefetchDuration < localPrefetchDuration;
    let isFetchLatecomer: boolean = this.fetchingRegistry.isFetchLatecomer(index, this.itemsOnScreen.meanValue);

    if (!isFetchLocal && !isFetchLatecomer) {
      this.meanPrefetchTime = (this.meanPrefetchTime * weight + (1 - weight) * prefetchDuration) as float;
    }
  }

  update(index: int, prefetchDuration: float): UpdateResult {
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
          this.leftToleranceEdge = Number.MIN_VALUE as float;
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
          this.rightToleranceEdge = Number.MAX_VALUE as float;
        }
      }
    }
    return ratioChanged;
  }

  calculateRatio(prefetchCount: int, totalCount: int): float {
    const visibleRange = this.itemsOnScreen.visibleRange;

    let start: int = 0;
    let end: int = 0;

    switch (this.itemsOnScreen.direction) {
      case 'UNKNOWN':
        start = Math.max(0, visibleRange.start - prefetchCount) as int;
        end = Math.min(totalCount, visibleRange.end + prefetchCount) as int;
        break;
      case 'UP':
        start = Math.max(0, visibleRange.start - prefetchCount) as int;
        end = Math.min(totalCount, visibleRange.end + Math.round(0.5 * prefetchCount)) as int;
        break;
      case 'DOWN':
        start = Math.max(0, visibleRange.start - Math.round(0.5 * prefetchCount)) as int;
        end = Math.min(totalCount, visibleRange.end + prefetchCount) as int;
        break;
    }

    const evaluatedPrefetchRange = new IndexRange(start, end);
    const completedActive = this.fetchedRegistry.getFetchedInRange(evaluatedPrefetchRange);
    const completedVisible = this.fetchedRegistry.getFetchedInRange(visibleRange);

    if (evaluatedPrefetchRange.length === 0 || visibleRange.length === 0) {
      return 0;
    }

    const ratio =
      Math.pow(1.0 * completedActive / evaluatedPrefetchRange.length, this.ACTIVE_DEGREE) *
      Math.pow(1.0 * completedVisible / visibleRange.length, this.VISIBLE_DEGREE);

    return Math.min(1, ratio) as float;
  }

  updateRatioRange(ratio: float): void {
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

class PrefetchCount {
  private readonly MAX_SCREENS: float = 4;
  private readonly speedCoef: float = 2.5;
  private maxItems: int = 0;
  private prefetchCountValueInternal: int = 0;
  private currentMaxItemsInternal: int = 0;
  private currentMinItemsInternal: int = 0;
  private readonly itemsOnScreen: IItemsOnScreenProvider;
  private readonly prefetchRangeRatio: PrefetchRangeRatio;

  constructor(
    itemsOnScreen: IItemsOnScreenProvider,
    prefetchRangeRatio: PrefetchRangeRatio,
  ) {
    this.itemsOnScreen = itemsOnScreen;
    this.itemsOnScreen.register(() => {
      this.updateLimits();
    });
    this.prefetchRangeRatio = prefetchRangeRatio;
    this.prefetchRangeRatio.register(() => {
      this.updateLimits();
    });
  }

  get prefetchCountValue(): int {
    return this.prefetchCountValueInternal;
  }

  set prefetchCountValue(value: int) {
    this.prefetchCountValueInternal = value;
  }

  get currentMaxItems(): int {
    return this.currentMaxItemsInternal;
  }

  get currentMinItems(): int {
    return this.currentMinItemsInternal;
  }

  getPrefetchCountByRatio(ratio: float): int {
    this.itemsOnScreen.updateSpeed(this.itemsOnScreen.visibleRange.start, this.itemsOnScreen.visibleRange.end - 1);
    const minItems = Math.min(
      this.currentMaxItems,
      Math.ceil(this.speedCoef * this.itemsOnScreen.speed * this.currentMaxItems),
    ) as int;
    const prefetchCount: int = minItems + Math.ceil(ratio * (this.currentMaxItems - minItems)) as int;
    return prefetchCount;
  }

  getRangeToFetch(totalCount: int): IndexRange {
    const visibleRange = this.itemsOnScreen.visibleRange;
    let start: int = 0;
    let end: int = 0;
    switch (this.itemsOnScreen.direction) {
      case 'UNKNOWN':
        start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue)) as int;
        end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue)) as int;
        break;
      case 'UP':
        start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue)) as int;
        end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue * 0.5)) as int;
        break;
      case 'DOWN':
        start = Math.max(0, visibleRange.start - Math.round(this.prefetchCountValue * 0.5)) as int;
        end = Math.min(totalCount, visibleRange.end + Math.round(this.prefetchCountValue)) as int;
        break;
    }
    if (start > end) {
      start = end;
    }
    return new IndexRange(start, end);
  }

  private updateLimits(): void {
    this.maxItems = Math.max(this.currentMinItems, Math.ceil(this.MAX_SCREENS * this.itemsOnScreen.meanValue)) as int;
    this.updateCurrentLimit();
  }

  private updateCurrentLimit(): void {
    this.currentMaxItemsInternal = Math.max(
      this.currentMinItems,
      Math.ceil(this.maxItems * this.prefetchRangeRatio.maxRatio),
    ) as int;
    this.currentMinItemsInternal = Math.ceil(this.maxItems * this.prefetchRangeRatio.minRatio) as int;
  }
}

interface IFetchingRangeEvaluator {
  updateRangeToFetch(whatHappened: RangeUpdateEvent): void;
}

interface RangeUpdateVisibleAreaChanged {
  kind: RangeUpdateEventKind;
  minVisible: int;
  maxVisible: int;
}

interface RangeUpdateFetched {
  kind: RangeUpdateEventKind;
  itemIndex: int;
  fetchDuration: float;
}

interface RangeUpdateCollectionChanged {
  kind: RangeUpdateEventKind;
  totalCount: int;
}

interface RangeUpdateRemovedOrAdded {
  kind: RangeUpdateEventKind;
  itemIndex: int;
}

type RangeUpdateEvent = RangeUpdateVisibleAreaChanged | RangeUpdateFetched | RangeUpdateCollectionChanged |
  RangeUpdateRemovedOrAdded;

type RangeUpdateEventKind = 'visible-area-changed' | 'item-fetched' | 'collection-changed' | 'item-added' |
  'item-removed';

class FetchingRangeEvaluator implements IFetchingRangeEvaluator {
  private readonly itemsOnScreen: ItemsOnScreenProvider;
  private readonly prefetchCount: PrefetchCount;
  private readonly prefetchRangeRatio: PrefetchRangeRatio;
  protected readonly fetchedRegistry: FetchedRegistry;
  protected totalItems: int = 0;

  constructor(
    itemsOnScreen: ItemsOnScreenProvider,
    prefetchCount: PrefetchCount,
    prefetchRangeRatio: PrefetchRangeRatio,
    fetchedRegistry: FetchedRegistry,
  ) {
    this.itemsOnScreen = itemsOnScreen;
    this.prefetchCount = prefetchCount;
    this.prefetchRangeRatio = prefetchRangeRatio;
    this.fetchedRegistry = fetchedRegistry;
  }

  updateRangeToFetch(whatHappened: RangeUpdateEvent): void {
    if (whatHappened.kind === 'visible-area-changed') {
      this.onVisibleAreaChange((whatHappened as RangeUpdateVisibleAreaChanged).minVisible,
        (whatHappened as RangeUpdateVisibleAreaChanged).maxVisible);
    } else if (whatHappened.kind === 'item-fetched') {
      this.onItemFetched((whatHappened as RangeUpdateFetched).itemIndex,
        (whatHappened as RangeUpdateFetched).fetchDuration);
    } else if (whatHappened.kind === 'collection-changed') {
      this.onCollectionChanged((whatHappened as RangeUpdateCollectionChanged).totalCount);
    } else if (whatHappened.kind === 'item-added') {
      this.onItemAdded((whatHappened as RangeUpdateRemovedOrAdded).itemIndex);
    } else if (whatHappened.kind === 'item-removed') {
      this.onItemDeleted((whatHappened as RangeUpdateRemovedOrAdded).itemIndex);
    } else {
      throw new Error(`updateRangeToFetch error`);
    }
  }

  protected onVisibleAreaChange(minVisible: int, maxVisible: int): void {
    const oldVisibleRange = this.itemsOnScreen.visibleRange;
    this.itemsOnScreen.update(minVisible, maxVisible);

    if (!oldVisibleRange.equals(this.itemsOnScreen.visibleRange)) {
      this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('visible-area-changed');
      const rangeToFetch = this.prefetchCount.getRangeToFetch(this.totalItems);
      this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
    }
  }

  protected onItemFetched(index: int, fetchDuration: float): void {
    if (!this.fetchedRegistry.rangeToFetch.contains(index)) {
      return;
    }

    let maxRatioChanged = false;
    if (this.prefetchRangeRatio.update(index, fetchDuration) === 'ratio-changed') {
      maxRatioChanged = true;
    }

    this.fetchedRegistry.addFetched(index);

    this.prefetchCount.prefetchCountValue = this.evaluatePrefetchCount('resolved', maxRatioChanged);
    const rangeToFetch = this.prefetchCount.getRangeToFetch(this.totalItems);
    this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
  }

  private evaluatePrefetchCount(event: 'resolved' | 'visible-area-changed', maxRatioChanged?: boolean): int {
    let ratio: float = this.prefetchRangeRatio.calculateRatio(this.prefetchCount.prefetchCountValue, this.totalItems);
    let evaluatedPrefetchCount: int = this.prefetchCount.getPrefetchCountByRatio(ratio);

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

    return evaluatedPrefetchCount;
  }

  protected onCollectionChanged(totalCount: int): void {
    this.totalItems = Math.max(0, totalCount) as int;
    let newRangeToFetch = this.itemsOnScreen.visibleRange;
    if (newRangeToFetch.end > this.totalItems) {
      const end = this.totalItems;
      const start = newRangeToFetch.start < end ? newRangeToFetch.start : end;
      newRangeToFetch = new IndexRange(start, end);
    }

    this.fetchedRegistry.clearFetched(newRangeToFetch);
  }

  private onItemDeleted(itemIndex: int): void {
    if (this.totalItems === 0) {
      return;
    }
    this.totalItems--;
    this.fetchedRegistry.removeFetched(itemIndex);

    const rangeToFetch = this.prefetchCount.getRangeToFetch(this.totalItems);
    this.fetchedRegistry.decrementFetchedGreaterThen(itemIndex, rangeToFetch);
  }

  private onItemAdded(itemIndex: int): void {
    this.totalItems++;
    if (itemIndex > this.fetchedRegistry.rangeToFetch.end) {
      return;
    }

    const rangeToFetch = this.prefetchCount.getRangeToFetch(this.totalItems);
    this.fetchedRegistry.incrementFetchedGreaterThen(itemIndex - 1, rangeToFetch);
  }
}

class DataSourceObserver<T> implements DataChangeListener {
  private dataSource: IDataSource<T> | undefined;
  private readonly simpleChangeListener: DataCollectionChangeListener<T>;

  constructor(simpleChangeListener: DataCollectionChangeListener<T>, dataSource: IDataSource<T> | undefined) {
    this.simpleChangeListener = simpleChangeListener;
    this.dataSource = dataSource;
  }

  onDataReloaded(): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'reloaded',
        totalCount: this.dataSource!.totalCount(),
      },
    ]);
  }

  onDataAdded(index: int): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'added',
        startIndex: index,
        count: 1,
      },
    ]);
  }

  onDataAdd(index: int): void {
    this.onDataAdded(index);
  }

  onDataMoved(from: int, to: int): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'swapped',
        a: from,
        b: to,
      },
    ]);
  }

  onDataMove(from: int, to: int): void {
    this.onDataMoved(from, to);
  }

  onDataDeleted(index: int): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'deleted',
        startIndex: index,
        count: 1,
      },
    ]);
  }

  onDataDelete(index: int): void {
    this.onDataDeleted(index);
  }

  onDataChanged(index: int): void {
    this.simpleChangeListener.batchUpdate([
      {
        kind: 'updated',
        index: index,
      },
    ]);
  }

  onDataChange(index: int): void {
    this.onDataChanged(index);
  }

  onDatasetChange(dataOperations: DataOperation[]): void {
    const operations: BatchOperation[] = [];
    dataOperations.forEach((operation) => {
      switch (operation.type) {
        case DataOperationType.ADD:
          const addCount = (operation as DataAddOperation).count;
          if (addCount === undefined || addCount > 0) {
            operations.push({
              kind: 'added',
              startIndex: (operation as DataAddOperation).index,
              count: (addCount ?? 1),
            });
          }
          break;
        case DataOperationType.DELETE:
          const deleteCount = (operation as DataDeleteOperation).count;
          if (deleteCount === undefined || deleteCount > 0) {
            operations.push({
              kind: 'deleted',
              startIndex: (operation as DataDeleteOperation).index,
              count: (deleteCount ?? 1),
            });
          }
          break;
        case DataOperationType.CHANGE:
          operations.push({
            kind: 'updated',
            index: (operation as DataChangeOperation).index,
          });
          break;
        case DataOperationType.RELOAD:
          operations.push({
            kind: 'reloaded',
            totalCount: this.dataSource!.totalCount(),
          });
          break;
        case DataOperationType.EXCHANGE:
          operations.push({
            kind: 'swapped',
            a: (operation as DataExchangeOperation).index.start,
            b: (operation as DataExchangeOperation).index.end,
          });
          break;
        case DataOperationType.MOVE:
          operations.push({
            kind: 'moved',
            from: (operation as DataMoveOperation).index.from,
            to: (operation as DataMoveOperation).index.to,
          });
          break;
        default:
          throw new Error(`onDatasetChange error`);
      }
    });
    this.simpleChangeListener.batchUpdate(operations);
  }

  setDataSource(dataSource: IDataSource<T>): void {
    if (this.dataSource) {
      this.dataSource!.unregisterDataChangeListener(this);
    }
    this.dataSource = dataSource;
    this.dataSource!.registerDataChangeListener(this);
    this.onDataReloaded();
  }
}