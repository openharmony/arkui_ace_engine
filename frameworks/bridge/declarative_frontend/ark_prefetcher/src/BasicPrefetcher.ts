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

class BasicPrefetcher implements IPrefetcher {
  private readonly prefetcher = new Prefetcher(new PrefetchRangeEvaluator(), new DefaultTimeProvider());

  constructor(ds?: IDataSourcePrefetching) {
    if (ds) {
      this.prefetcher.setDataSource(ds);
    }
  }

  setDataSource(ds: IDataSourcePrefetching): void {
    this.prefetcher.setDataSource(ds);
  }

  visibleAreaChanged(minVisible: number, maxVisible: number): void {
    this.prefetcher.visibleAreaChanged(minVisible, maxVisible);
  }
}
