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

class RangeEdge {
  readonly value: number;
  readonly inclusive: boolean;
  constructor(value: number, inclusive: boolean) {
    this.value = value;
    this.inclusive = inclusive;
  }
}

class RatioRange {
  readonly start: RangeEdge;
  readonly end: RangeEdge;

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
