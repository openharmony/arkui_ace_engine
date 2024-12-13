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
  get speed(): number;
  updateSpeed(minVisible: number, maxVisible: number): void;
  update(minVisible: number, maxVisible: number): void;
}

// eslint-disable-next-line @typescript-eslint/no-unused-vars
class ItemsOnScreenProvider implements IItemsOnScreenProvider {
  private firstScreen = true;
  private meanImagesOnScreen = 0;
  private minVisible = 0;
  private maxVisible = 0;
  private directionInternal: ScrollDirection = 'UNKNOWN';
  private speedInternal = 0;
  private lastUpdateTimestamp = 0;
  private visibleRangeInternal: IndexRange = new IndexRange(0, 0);

  private callbacks: VisibleRangeChangedCallback[] = [];

  register(callback: VisibleRangeChangedCallback): void {
    this.callbacks.push(callback);
  }

  get visibleRange(): IndexRange {
    return this.visibleRangeInternal;
  }

  get meanValue(): number {
    return this.meanImagesOnScreen;
  }

  get direction(): ScrollDirection {
    return this.directionInternal;
  }

  get speed(): number {
    return this.speedInternal;
  }

  updateSpeed(minVisible: number, maxVisible: number): void {
    const timeDifference = Date.now() - this.lastUpdateTimestamp;
    if (timeDifference > 0) {
      const speedTau = 100;
      const speedWeight = 1 - Math.exp(-timeDifference / speedTau);
      const distance =
        minVisible + (maxVisible - minVisible) / 2 - (this.minVisible + (this.maxVisible - this.minVisible) / 2);
      const rawSpeed = Math.abs(distance / timeDifference) * 1000;
      this.speedInternal = speedWeight * rawSpeed + (1 - speedWeight) * this.speedInternal;
    }
  }

  update(minVisible: number, maxVisible: number): void {
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

    let imagesOnScreen = maxVisible - minVisible + 1;
    let oldMeanImagesOnScreen = this.meanImagesOnScreen;
    if (this.firstScreen) {
      this.meanImagesOnScreen = imagesOnScreen;
      this.firstScreen = false;
      this.lastUpdateTimestamp = Date.now();
    } else {
      {
        const imagesWeight = 0.95;
        this.meanImagesOnScreen = this.meanImagesOnScreen * imagesWeight + (1 - imagesWeight) * imagesOnScreen;
      }
      this.updateSpeed(minVisible, maxVisible);
    }

    this.minVisible = minVisible;
    this.maxVisible = maxVisible;

    const visibleRangeSizeChanged = Math.ceil(oldMeanImagesOnScreen) !== Math.ceil(this.meanImagesOnScreen);
    this.visibleRangeInternal = new IndexRange(minVisible, maxVisible + 1);

    if (visibleRangeSizeChanged) {
      this.notifyObservers();
    }
    this.lastUpdateTimestamp = Date.now();
  }

  private notifyObservers(): void {
    this.callbacks.forEach((callback) => callback());
  }
}
