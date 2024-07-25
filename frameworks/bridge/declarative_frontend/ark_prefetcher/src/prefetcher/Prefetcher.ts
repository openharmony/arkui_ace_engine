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

class DefaultTimeProvider implements ITimeProvider {
  getCurrent(): number {
    return Date.now();
  }
}

class Prefetcher implements IPrefetcher {
  private datasource: IDataSourcePrefetching | null = null;
  private readonly prefetchRangeEvaluator: IPrefetchRangeEvaluator;
  private readonly timeProvider: ITimeProvider;

  constructor(prefetchRangeEvaluator: IPrefetchRangeEvaluator, timeProvider: ITimeProvider) {
    this.prefetchRangeEvaluator = prefetchRangeEvaluator;
    this.timeProvider = timeProvider;
  }

  setDataSource(ds: IDataSourcePrefetching): void {
    this.datasource = ds;
    this.prefetchRangeEvaluator.setTotal(ds.totalCount());
  }

  visibleAreaChanged(minVisible: number, maxVisible: number): void {
    if (!this.datasource) {
      throw new Error('No data source');
    }

    const oldRangeToPrefetch = this.prefetchRangeEvaluator.rangeToPrefetch;
    this.prefetchRangeEvaluator.visibleRangeChanged(minVisible, maxVisible);

    this.prefetchDifference(oldRangeToPrefetch);
    this.cancelDifference(oldRangeToPrefetch);
  }

  private prefetchDifference(oldRange: IndexRange): void {
    this.prefetchRangeEvaluator.rangeToPrefetch.subtract(oldRange).forEachIndex((index) => {
      const prefetchStart = this.timeProvider.getCurrent();

      const prefetchedCallback = (): void => {
        if (!this.prefetchRangeEvaluator.rangeToPrefetch.contains(index)) {
          return;
        }

        const oldRangeToPrefetch = this.prefetchRangeEvaluator.rangeToPrefetch;

        const prefetchDuration = this.timeProvider.getCurrent() - prefetchStart;
        this.prefetchRangeEvaluator.itemPrefetched(index, prefetchDuration);

        this.prefetchDifference(oldRangeToPrefetch);
      };

      const prefetchResponse = this.datasource!.prefetch(index);
      if (prefetchResponse instanceof Promise) {
        prefetchResponse.then(prefetchedCallback);
      } else {
        prefetchedCallback();
      }
    });
  }

  private cancelDifference(oldRangeToPrefetch: IndexRange): void {
    if (!this.datasource!.cancel || this.prefetchRangeEvaluator.rangeToPrefetch.length > oldRangeToPrefetch.length) {
      return;
    }
    oldRangeToPrefetch.subtract(this.prefetchRangeEvaluator.rangeToPrefetch).forEachIndex((index) => {
      this.datasource!.cancel!(index);
    });
  }
}
