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
class BasicPrefetcher implements IPrefetcher {
  private readonly fetchingDriver: FetchingDriver;

  constructor(ds?: IDataSourcePrefetching) {
    const itemsOnScreen = new ItemsOnScreenProvider();
    const fetchedRegistry = new FetchedRegistry();
    const fetchingRegistry = new FetchingRegistry();
    const prefetchRangeRatio = new PrefetchRangeRatio(itemsOnScreen, fetchedRegistry, fetchingRegistry);
    const prefetchCount = new PrefetchCount(itemsOnScreen, prefetchRangeRatio);
    const evaluator = new FetchingRangeEvaluator(itemsOnScreen, prefetchCount, prefetchRangeRatio, fetchedRegistry);
    this.fetchingDriver = new FetchingDriver(fetchedRegistry, fetchingRegistry, evaluator, new DefaultTimeProvider());
    this.fetchingDriver.setDataSource(ds);
  }

  setDataSource(ds: IDataSourcePrefetching): void {
    this.fetchingDriver.setDataSource(ds);
  }

  visibleAreaChanged(minVisible: number, maxVisible: number): void {
    this.fetchingDriver.visibleAreaChanged(minVisible, maxVisible);
  }
}
