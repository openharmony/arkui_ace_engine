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

type VisibleRangeChangedCallback = () => void;

interface IItemsOnScreenProvider {
  register(callback: VisibleRangeChangedCallback): void;
  get visibleRange(): IndexRange;
  get meanValue(): number;
  get direction(): ScrollDirection;
  update(minVisible: number, maxVisible: number): void;
}

class ItemsOnScreenProvider implements IItemsOnScreenProvider {
  private firstScreen = true;
  private meanImagesOnScreen = 0;
  private minVisible = 0;
  private maxVisible = 0;
  private _direction: ScrollDirection = 'UNKNOWN';
  private _visibleRange: IndexRange = new IndexRange(0, 0);

  private callbacks: VisibleRangeChangedCallback[] = [];

  register(callback: VisibleRangeChangedCallback): void {
    this.callbacks.push(callback);
  }

  get visibleRange(): IndexRange {
    return this._visibleRange;
  }

  get meanValue(): number {
    return this.meanImagesOnScreen;
  }

  get direction(): ScrollDirection {
    return this._direction;
  }

  update(minVisible: number, maxVisible: number): void {
    if (minVisible === this.minVisible && maxVisible === this.maxVisible) {
      // Direction not changed
    } else if (
      Math.max(minVisible, this.minVisible) === minVisible &&
      Math.max(maxVisible, this.maxVisible) === maxVisible
    ) {
      this._direction = 'DOWN';
    } else if (
      Math.min(minVisible, this.minVisible) === minVisible &&
      Math.min(maxVisible, this.maxVisible) === maxVisible
    ) {
      this._direction = 'UP';
    }
    this.minVisible = minVisible;
    this.maxVisible = maxVisible;

    let imagesOnScreen = maxVisible - minVisible + 1;
    if (this.firstScreen) {
      this.meanImagesOnScreen = imagesOnScreen;
      this.firstScreen = false;
    } else {
      const weight = 0.95;
      this.meanImagesOnScreen = this.meanImagesOnScreen * weight + (1 - weight) * imagesOnScreen;
      imagesOnScreen = Math.ceil(this.meanImagesOnScreen);
    }

    const visibleRangeSizeChanged = this.visibleRange.length !== imagesOnScreen;
    this._visibleRange = new IndexRange(minVisible, maxVisible + 1);

    if (visibleRangeSizeChanged) {
      this.notifyObservers();
    }
  }

  private notifyObservers(): void {
    this.callbacks.forEach((callback) => callback());
  }
}
