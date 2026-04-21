/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { curves } from '@kit.ArkUI';
import { image } from '@kit.ImageKit';

// Image data model with state management V2
@ObservedV2
export class ImageData {
  @Trace pixelMap: image.PixelMap | null = null;
  @Trace width: number = 0;
  @Trace height: number = 0;

  constructor(pixelMap: image.PixelMap | null = null) {
    this.pixelMap = pixelMap;
  }
}

// Image view model with state management V2
@ObservedV2
export class ImageViewModel {
  @Trace images: ImageData[] = [];
  @Trace selectedIndex: number = 0;
  @Trace currentPixelMap: image.PixelMap | null = null;
  @Trace imageWidth: number = 0;
  @Trace imageHeight: number = 0;
  @Trace containerWidth: number = 360;
  @Trace containerHeight: number = 640;
  @Trace baseImageWidth: number = 0;
  @Trace baseImageHeight: number = 0;

  setSelectedIndex(index: number) {
    this.selectedIndex = index;
    const imageData = this.images[index];
    this.currentPixelMap = imageData.pixelMap;
    this.imageWidth = imageData.width;
    this.imageHeight = imageData.height;

    // Calculate base display size at 100% scale, fill screen while maintaining aspect ratio
    const imageAspect = this.imageWidth / this.imageHeight;
    const containerAspect = this.containerWidth / this.containerHeight;

    if (imageAspect > containerAspect) {
      // Image is wider, use width as reference
      this.baseImageWidth = this.containerWidth;
      this.baseImageHeight = this.containerWidth / imageAspect;
    } else {
      // Image is taller, use height as reference
      this.baseImageHeight = this.containerHeight;
      this.baseImageWidth = this.containerHeight * imageAspect;
    }
  }

  setContainerSize(width: number, height: number) {
    this.containerWidth = width;
    this.containerHeight = height;
    // Recalculate base dimensions
    if (this.imageWidth > 0 && this.imageHeight > 0) {
      this.setSelectedIndex(this.selectedIndex);
    }
  }
}

// Preview page state management
@ObservedV2
export class PreviewState {
  @Trace scale: number = 1.0;
  @Trace offsetX: number = 0;
  @Trace offsetY: number = 0;
  @Trace isAnimating: boolean = false;
  @Trace showTitleBar: boolean = true;
  @Trace isPinching: boolean = false;
  @Trace isDragging: boolean = false;
  @Trace containerWidth: number = 360;
  @Trace containerHeight: number = 640;
  // More granular animation state: distinguish between pinch rebound and pan rebound
  @Trace isPinchRebounding: boolean = false;
  @Trace isPanRebounding: boolean = false;
  // Page enter/exit animation state
  @Trace pageTransitionProgress: number = 0;
  @Trace isPageTransitioning: boolean = false;

  reset() {
    this.scale = 1.0;
    this.offsetX = 0;
    this.offsetY = 0;
    this.showTitleBar = true;
    this.isAnimating = false;
    this.isPinching = false;
    this.isDragging = false;
    this.isPinchRebounding = false;
    this.isPanRebounding = false;
    this.pageTransitionProgress = 0;
    this.isPageTransitioning = false;
  }

  setContainerSize(width: number, height: number) {
    this.containerWidth = width;
    this.containerHeight = height;
  }
}

// Page navigation parameter type
export class PageParams {
  index: number = 0;
}
