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

type FetchId = number;
type ItemIndex = number;

// eslint-disable-next-line @typescript-eslint/no-unused-vars
class FetchingRegistry {
  private readonly fetches = new Map<FetchId, ItemIndex>();
  private fetching = new Map<ItemIndex, FetchId>();
  private readonly fetchesBefore = new Map<ItemIndex, number>();

  private fetchCounter = 0;

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

  getItem(fetchId: FetchId): ItemIndex {
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

  incrementAllIndexesGreaterThen(value: number): void {
    this.offsetAllIndexesGreaterThen(value, 1);
  }

  getAllIndexes(): Set<number> {
    const set = new Set<number>();
    this.fetching.forEach((fetchId, itemIndex) => set.add(itemIndex));
    return set;
  }

  getFetchesCount(): number {
    return this.fetches.size;
  }

  isFetchLatecomer(index: ItemIndex, threshold: number): boolean {
    return this.fetchesBefore.get(index) > threshold;
  }

  private offsetAllIndexesGreaterThen(value: number, offset: number): void {
    const newFetching = new Map<ItemIndex, FetchId>();
    this.fetches.forEach((index, fetchId) => {
      const toSet = index > value ? index + offset : index;
      newFetching.set(toSet, fetchId);
      this.fetches.set(fetchId, toSet);
    });
    this.fetching = newFetching;
  }

  decrementAllIndexesGreaterThen(value: number): void {
    this.offsetAllIndexesGreaterThen(value, -1);
  }
}
