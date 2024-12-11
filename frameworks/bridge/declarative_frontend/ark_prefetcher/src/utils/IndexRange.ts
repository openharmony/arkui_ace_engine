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

class IndexRange {
  readonly start: number; // inclusive
  readonly end: number; // exclusive

  constructor(start: number, end: number) {
    this.start = start;
    this.end = end;
    if (this.start > this.end) {
      throw new Error('Invalid range');
    }
  }

  get length(): number {
    return this.end - this.start;
  }

  toSet(target?: Set<number>): Set<number> {
    const set = target ?? new Set<number>();
    for (let i = this.start; i < this.end; ++i) {
      set.add(i);
    }
    return set;
  }

  contains(value: IndexRange | number): boolean {
    if (typeof value === 'object') {
      return this.start <= value.start && value.end <= this.end;
    } else {
      return this.start <= value && value < this.end;
    }
  }

  subtract(other: IndexRange): IndexRangeArray {
    const result = new IndexRangeArray();
    if (other.start > this.start) {
      result.push(new IndexRange(this.start, Math.min(this.end, other.start)));
    }
    if (other.end < this.end) {
      result.push(new IndexRange(Math.max(other.end, this.start), this.end));
    }
    return result;
  }

  // Expand the range to contain another.
  // When `this` and `other` intersect, this is a union.
  expandedWith(other: IndexRange): IndexRange {
    return new IndexRange(Math.min(this.start, other.start), Math.max(this.end, other.end));
  }

  forEachIndex(callback: (index: number) => void): void {
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
  forEachIndex(callback: (index: number) => void): void {
    this.forEach((range) => {
      range.forEachIndex(callback);
    });
  }

  toSet(): Set<number> {
    const set = new Set<number>();
    this.forEach((range) => {
      range.toSet(set);
    });
    return set;
  }
}
