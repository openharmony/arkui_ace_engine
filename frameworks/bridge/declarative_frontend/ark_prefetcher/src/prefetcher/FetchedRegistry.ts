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
class FetchedRegistry {
  private fetchedIndexes: Set<number> = new Set();
  private rangeToFetchInternal: IndexRange = new IndexRange(0, 0);
  private missedIndexes: Set<number> = new Set();

  get rangeToFetch(): IndexRange {
    return this.rangeToFetchInternal;
  }

  addFetched(index: number): void {
    if (this.rangeToFetch.contains(index)) {
      this.fetchedIndexes.add(index);
      this.missedIndexes.delete(index);
    }
  }

  removeFetched(index: number): void {
    if (this.rangeToFetch.contains(index)) {
      this.fetchedIndexes.delete(index);
      this.missedIndexes.add(index);
    }
  }

  has(index: number): boolean {
    return this.fetchedIndexes.has(index);
  }

  getFetchedInRange(range: IndexRange): number {
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

  getItemsToFetch(): Set<number> {
    return new Set(this.missedIndexes);
  }

  incrementFetchedGreaterThen(value: number, newFetchRange: IndexRange): void {
    this.offsetAllGreaterThen(value, 1);
    this.updateRangeToFetch(newFetchRange);
  }

  decrementFetchedGreaterThen(value: number, newFetchRange: IndexRange): void {
    this.offsetAllGreaterThen(value, -1);
    this.updateRangeToFetch(newFetchRange);
  }

  private offsetAllGreaterThen(value: number, offset: number): void {
    const updated = new Set<number>();
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
