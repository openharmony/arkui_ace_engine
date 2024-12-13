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

interface ITimeProvider {
  getCurrent: () => number;
}

type Millisecond = number;

// eslint-disable-next-line @typescript-eslint/no-unused-vars
class DefaultTimeProvider implements ITimeProvider {
  getCurrent(): number {
    return Date.now();
  }
}

const dummyDataSource: IDataSourcePrefetching = {
  prefetch: () => {},
  totalCount: () => {
    return 0;
  },
  getData: () => {
    return undefined;
  },
  registerDataChangeListener: () => {},
  unregisterDataChangeListener: () => {},
};

const DELAY_TO_REPEAT_FETCH_AFTER_ERROR = 500;

// eslint-disable-next-line @typescript-eslint/no-unused-vars
class FetchingDriver implements DataCollectionChangeListener {
  private dataSource: IDataSourcePrefetching | null = dummyDataSource;
  private readonly dataSourceObserver = new DataSourceObserver(this);
  private isPaused: boolean;

  constructor(
    private readonly fetchedRegistry: FetchedRegistry,
    private readonly fetches: FetchingRegistry,
    private readonly prefetchRangeEvaluator: IFetchingRangeEvaluator,
    private readonly timeProvider: ITimeProvider,
    private readonly logger: ILogger = dummyLogger,
    autostart: boolean = true,
  ) {
    this.isPaused = !autostart;
    this.prefetchRangeEvaluator = prefetchRangeEvaluator;
    this.timeProvider = timeProvider;
  }

  get afterErrorDelay(): Millisecond {
    return DELAY_TO_REPEAT_FETCH_AFTER_ERROR;
  }

  batchUpdate(operations: BatchOperation[]): void {
    this.logger.info('batchUpdate called with ' + JSON.stringify(operations));
    try {
      this.batchUpdateInternal(operations);
    } catch (e) {
      reportError(this.logger, 'batchUpdate', e);
      throw e;
    }
  }

  private batchUpdateInternal(operations: BatchOperation[]): void {
    operations.forEach((operation) => {
      switch (operation.kind) {
        case 'deleted':
          this.itemsDeleted(operation.startIndex, operation.count);
          break;
        case 'added':
          this.itemsAdded(operation.startIndex, operation.count);
          break;
        case 'updated':
          this.itemUpdated(operation.index);
          break;
        case 'reloaded':
          this.collectionChanged(operation.totalCount);
          break;
        case 'swapped':
          this.itemsSwapped(operation.a, operation.b);
          break;
        case 'moved':
          this.itemMoved(operation.from, operation.to);
          break;
      }
    });

    this.prefetch(this.fetchedRegistry.getItemsToFetch());
  }

  private collectionChanged(totalCount: number): void {
    this.prefetchRangeEvaluator.updateRangeToFetch({
      kind: 'collection-changed',
      totalCount: totalCount,
    });
  }

  private itemUpdated(index: number): void {
    this.fetchedRegistry.removeFetched(index);
    this.fetches.deleteFetchByItem(index);
  }

  private itemsDeleted(index: number, count: number): void {
    for (let i = 0; i < count; i++) {
      this.fetches.decrementAllIndexesGreaterThen(index);
      this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'item-removed', itemIndex: index });
    }
  }

  private itemsAdded(index: number, count: number): void {
    for (let i = 0; i < count; i++) {
      this.fetches.incrementAllIndexesGreaterThen(index - 1);
      this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'item-added', itemIndex: index });
    }
  }

  private itemsSwapped(a: number, b: number): void {
    if (!this.fetchedRegistry.has(a) || !this.fetchedRegistry.has(b)) {
      this.fetchedRegistry.removeFetched(a);
      this.fetchedRegistry.removeFetched(b);
    }
  }

  private itemMoved(from: number, to: number): void {
    if (!this.fetchedRegistry.has(from) || !this.fetchedRegistry.has(to)) {
      const rangeToFetch = this.fetchedRegistry.rangeToFetch;

      this.itemsDeleted(from, 1);
      this.itemsAdded(to, 1);
      this.fetchedRegistry.updateRangeToFetch(rangeToFetch);
    }
  }

  setDataSource(ds: IDataSourcePrefetching = dummyDataSource): void {
    this.logger.info(`setDataSource called with ${ds !== dummyDataSource ? 'a data source' : 'null or undefined'}`);
    try {
      this.setDataSourceInternal(ds);
    } catch (e) {
      reportError(this.logger, 'setDataSource', e);
      throw e;
    }
  }

  private setDataSourceInternal(ds: IDataSourcePrefetching): void {
    this.dataSource = ds ?? dummyDataSource;
    this.dataSourceObserver.setDataSource(this.dataSource);
  }

  stop(): void {
    this.logger.info('Stop called');
    try {
      this.stopInternal();
    } catch (e) {
      reportError(this.logger, 'stop', e);
      throw e;
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
    this.logger.info('Start called');
    try {
      this.startInternal();
    } catch (e) {
      reportError(this.logger, 'start', e);
      throw e;
    }
  }

  private startInternal(): void {
    if (!this.isPaused) {
      return;
    }

    this.isPaused = false;
    this.prefetch(this.fetchedRegistry.getItemsToFetch());
  }

  visibleAreaChanged(minVisible: number, maxVisible: number): void {
    this.logger.info(`visibleAreaChanged min: ${minVisible} max: ${maxVisible}`);

    try {
      this.visibleAreaChangedInternal(minVisible, maxVisible);
    } catch (e) {
      reportError(this.logger, 'visibleAreaChanged', e);
      throw e;
    }
  }

  private visibleAreaChangedInternal(minVisible: number, maxVisible: number): void {
    if (this.dataSource === dummyDataSource) {
      throw new Error('No data source');
    }

    const oldRangeToPrefetch = this.fetchedRegistry.rangeToFetch;
    this.prefetchRangeEvaluator.updateRangeToFetch({ kind: 'visible-area-changed', minVisible, maxVisible });

    this.prefetch(this.fetchedRegistry.getItemsToFetch());

    const toCancel = oldRangeToPrefetch.subtract(this.fetchedRegistry.rangeToFetch).toSet();
    this.cancel(toCancel);
  }

  private prefetch(toPrefetch: ReadonlySet<number>): void {
    if (this.isPaused) {
      this.logger.debug('Prefetcher is paused. Do nothing.');
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

    this.logger.info('to prefetch ' + itemIndex);

    try {
      const prefetchResponse = this.dataSource!.prefetch(itemIndex);
      if (!(prefetchResponse instanceof Promise)) {
        this.fetchedCallback(fetchId, prefetchStart);
        return;
      }

      prefetchResponse
        .then(() => this.fetchedCallback(fetchId, prefetchStart))
        .catch((e) => {
          this.errorOnFetchCallback(fetchId, e);
        });
    } catch (e) {
      this.errorOnFetchCallback(fetchId, e);
    }
  };

  private fetchedCallback(fetchId: FetchId, prefetchStart: number): void {
    const itemIndex = this.fetches.getItem(fetchId);
    this.fetches.deleteFetch(fetchId);

    if (itemIndex === undefined) {
      return;
    }

    this.prefetchRangeEvaluator.updateRangeToFetch({
      kind: 'item-fetched',
      itemIndex,
      fetchDuration: this.timeProvider.getCurrent() - prefetchStart,
    });
    this.prefetch(this.fetchedRegistry.getItemsToFetch());
  }

  private errorOnFetchCallback(fetchId: FetchId, error: Error): void {
    const itemIndex = this.fetches.getItem(fetchId);
    if (itemIndex !== undefined) {
      this.logger.warn(`failed to fetch item at ${itemIndex} ${JSON.stringify(error)}`);
    }
    this.fetches.deleteFetch(fetchId);
    setTimeout(() => {
      this.prefetch(this.fetchedRegistry.getItemsToFetch());
    }, this.afterErrorDelay);
  }

  private cancel(toCancel: ReadonlySet<number>): void {
    toCancel.forEach((itemIndex) => {
      if (!this.fetches.isFetchingItem(itemIndex)) {
        return;
      }

      this.fetches.deleteFetchByItem(itemIndex);

      if (this.dataSource!.cancel) {
        this.logger.info('to cancel ' + itemIndex);
        this.dataSource.cancel(itemIndex);
      }
    });
  }
}
