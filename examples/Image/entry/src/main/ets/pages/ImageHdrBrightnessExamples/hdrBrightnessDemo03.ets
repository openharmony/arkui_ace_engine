/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/**
 * Example: `hdrBrightnessDemo03`
 * Demonstrates dynamic adjustment of HDR image brightness across multiple levels (0 → 0.3 → 0.8 → 1 → loop).
 *
 * ⚠️ Note: The `hdrBrightness` property only takes effect on HDR images.
 */

import { image } from '@kit.ImageKit'

@Entry
@Component
struct hdrBrightnessDemo03 {
  // HDR image resource name
  @State imageUrl: string = 'img_1'

  // Array of predefined brightness levels
  private brightnessLevels: number[] = [0, 0.3, 0.8, 1.0]

  // Current index in the brightness array
  @State brightnessIndex: number = 0

  // Get the current brightness value
  get currentBrightness(): number {
    return this.brightnessLevels[this.brightnessIndex]
  }

  aboutToAppear(): void {
    // Retrieve and log image HDR info
    let img = getContext().resourceManager.getMediaByNameSync(this.imageUrl)
    let imageSource = image.createImageSource(img.buffer.slice(0))
    let imageInfo = imageSource.getImageInfoSync()

    if (imageInfo == undefined) {
      console.error('Failed to obtain the image information')
    } else {
      console.info('imageInfo.isHdr: ' + imageInfo.isHdr)
    }
  }

  build() {
    Column({ space: 20 }) {
      Text('Current HDR Brightness: ' + this.currentBrightness.toFixed(1))
        .fontSize(18)
        .fontColor(Color.Black)

      // Image that uses the dynamic brightness
      Image($r('app.media.img_1'))
        .width('50%')
        .height('auto')
        .margin({ top: 20 })
        .hdrBrightness(this.currentBrightness)

      // Button to switch brightness level in sequence
      Button('Change Brightness')
        .onClick(() => {
          animateTo({}, () => {
            this.brightnessIndex = (this.brightnessIndex + 1) % this.brightnessLevels.length
          })
        })
    }
    .height('100%')
    .align(Alignment.Top)
    .padding(20)
  }
}
