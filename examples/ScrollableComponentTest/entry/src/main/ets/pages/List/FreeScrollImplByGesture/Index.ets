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

import { image } from '@kit.ImageKit';
import { curves } from '@kit.ArkUI';
import { ImageData, ImageViewModel, PreviewState, PageParams } from './ImageViewPage';
import { PreviewPageBuilder } from './PreviewBuilder';

// Create PixelMap with unique pattern, each cell has different color for observing scale and pan effects
function createPatternedPixelMap(index: number): Promise<image.PixelMap> {
  const size = 200;
  const bufferSize = size * size * 4;

  // Create buffer with unique pattern
  const buffer = new ArrayBuffer(bufferSize);
  const data = new Uint8Array(buffer);

  const checkerSize = 50;

  for (let y = 0; y < size; y++) {
    for (let x = 0; x < size; x++) {
      const idx = (y * size + x) * 4;

      // Calculate which cell current pixel is in
      const checkerX = Math.floor(x / checkerSize);
      const checkerY = Math.floor(y / checkerSize);

      // Generate unique color based on cell position and image index
      // Image 0 uses warm colors, image 1 uses cool colors
      const cellIndex = checkerY * 4 + checkerX;
      let r: number;
      let g: number;
      let b: number;

      if (index === 0) {
        r = 150 + (cellIndex * 25) % 106;
        g = 50 + (cellIndex * 15) % 150;
        b = 50 + (cellIndex * 10) % 100;
      } else {
        r = 50 + (cellIndex * 10) % 100;
        g = 50 + (cellIndex * 20) % 150;
        b = 150 + (cellIndex * 25) % 106;
      }

      // Mark edges with white
      const edge = 10;
      if (x < edge || x > size - edge || y < edge || y > size - edge) {
        r = 255;
        g = 255;
        b = 255;
      }

      data[idx] = r;
      data[idx + 1] = g;
      data[idx + 2] = b;
      data[idx + 3] = 255;
    }
  }

  // Create PixelMap
  const opts: image.InitializationOptions = {
    size: { width: size, height: size },
    pixelFormat: image.PixelMapFormat.RGBA_8888,
    alphaType: image.AlphaType.PREMUL
  };

  return image.createPixelMap(buffer, opts);
}

@Entry
@ComponentV2
struct Index {
  @Local viewModel: ImageViewModel = new ImageViewModel();
  @Local previewState: PreviewState = new PreviewState();
  @Local pageNav: NavPathStack = new NavPathStack();
  @Local isLoading: boolean = true;
  @Local errorMessage: string = '';

  aboutToAppear(): void {
    this.loadImages();
  }

  async loadImages(): Promise<void> {
    this.isLoading = true;
    this.errorMessage = '';

    const imageDataArray: ImageData[] = [];

    for (let i = 0; i < 2; i++) {
      try {
        // Create PixelMap with pattern
        const pixelMap: image.PixelMap = await createPatternedPixelMap(i);

        const imageInfo: image.ImageInfo = await pixelMap.getImageInfo();
        const imageData: ImageData = new ImageData(pixelMap);
        imageData.width = imageInfo.size.width;
        imageData.height = imageInfo.size.height;
        imageDataArray.push(imageData);

      } catch (err) {
        const errorMsg: string = `Failed to create image ${i}: ${JSON.stringify(err)}`;
        this.errorMessage = errorMsg;
      }
    }

    this.viewModel.images = imageDataArray;
    this.isLoading = false;
  }

  // Build thumbnail
  @Builder
  buildThumbnail(item: ImageData, index: number): void {
    Image(item.pixelMap)
      .width('100%')
      .height('100%')
      .objectFit(ImageFit.Cover)
      .borderRadius(8)
      .id(`thumbnail_${index}`)
      .backgroundColor('#cccccc')
      .geometryTransition(`shared_image_${index}`)
      .onClick(() => {
        this.previewState.reset();
        const params: PageParams = new PageParams();
        params.index = index;
        // Disable default transition animation, let geometryTransition handle
        this.pageNav.pushPathByName('preview', params, null, false);
      })
  }

  // Build preview page
  @Builder
  PreviewPage(name: string, param: Object): void {
    PreviewPageBuilder(name, param, this.viewModel, this.previewState, this.pageNav, this.getUIContext());
  }

  build() {
    Navigation(this.pageNav) {
      Column() {
        Text('Image Gallery')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        if (this.isLoading) {
          // Loading state
          Text('Loading images...')
            .fontSize(16)
            .fontColor(Color.Gray)
        } else if (this.errorMessage !== '') {
          // Loading failed state, show error message
          Column() {
            Text('Failed to load images')
              .fontSize(16)
              .fontColor(Color.Red)
            Text(this.errorMessage)
              .fontSize(12)
              .fontColor(Color.Red)
              .margin({ top: 8 })
          }
        } else if (this.viewModel.images.length === 0) {
          // Loading failed state
          Text('No images loaded')
            .fontSize(16)
            .fontColor(Color.Red)
        } else {
          // Thumbnail grid
          GridRow({ columns: 3, gutter: { x: 8, y: 8 } }) {
            ForEach(this.viewModel.images, (item: ImageData, index: number) => {
              GridCol() {
                this.buildThumbnail(item, index)
              }
            }, (item: ImageData, index: number) => `${index}`)
          }
          .width('100%')
          .height(200)
          .padding(10)
        }
      }
      .width('100%')
      .height('100%')
    }
    .navDestination(this.PreviewPage)
    .mode(NavigationMode.Stack)
  }
}
