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
 * Example: Demonstrates how to dynamically adjust image brightness using `hdrBrightness`
 * with a custom `AttributeModifier`. Includes real-time display and a fixed brightness comparison.
 *
 * ⚠️ Note: The `hdrBrightness` property only takes effect on HDR images.
 */

import { image } from '@kit.ImageKit'

// Custom modifier for dynamically applying hdrBrightness to an Image
class ImageModifier implements AttributeModifier<ImageAttribute> {
  public bright: number = 0

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.hdrBrightness(this.bright)
  }
}

@Entry
@Component
struct hdrBrightnessDemo02 {
  @State imageUrl: string = 'img_1'
  @State modifier: ImageModifier = new ImageModifier()

  aboutToAppear(): void {
    let img = getContext().resourceManager.getMediaByNameSync(this.imageUrl)
    let imageSource = image.createImageSource(img.buffer.slice(0))
    let imageInfo = imageSource.getImageInfoSync()
    if (imageInfo == undefined) {
      console.error('Failed to obtain the image information')
    } else {
      console.info('imageInfo.isHdr: ' + imageInfo.isHdr)
    }
    imageSource?.release()
  }

  build() {
    Column({ space: 20 }) {
      Text('Current Brightness: ' + this.modifier.bright.toFixed(2))
        .fontSize(18)
        .fontColor(Color.Black)

      // Image using the dynamic brightness modifier
      Text('Image with dynamic hdrBrightness')
        .fontSize(16)
      Image($r('app.media.img_1'))
        .width('60%')
        .height('auto')
        .attributeModifier(this.modifier)

      // Button to toggle brightness
      Button('Toggle Brightness (0 <-> 1)')
        .margin({ top: 10 })
        .onClick(() => {
          animateTo({}, () => {
            this.modifier.bright = 1.0 - this.modifier.bright
          })
        })

      Divider()

      // Static example: image with fixed maximum brightness
      Text('Image with fixed hdrBrightness = 1.0')
        .fontSize(16)
      Image($r('app.media.img_1'))
        .width('60%')
        .height('auto')
        .hdrBrightness(1.0)

      // Static example: image with fixed hdrBrightness = 0.0
      Text('Image with fixed hdrBrightness = 0.0')
        .fontSize(16)
      Image($r('app.media.img_1'))
        .width('60%')
        .height('auto')
        .hdrBrightness(0.0)
    }
    .height('100%')
    .align(Alignment.Top)
    .padding(20)
  }
}
