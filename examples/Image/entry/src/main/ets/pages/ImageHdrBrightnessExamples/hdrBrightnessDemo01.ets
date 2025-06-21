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
 * Example: Demonstrates dynamic adjustment of image brightness using the `hdrBrightness` property.
 * 
 * The `hdrBrightness` interface is effective **only for images encoded with HDR (High Dynamic Range)**.
 * If the image is not HDR, this property will have no visible effect.
 */
import { image } from '@kit.ImageKit'

@Entry
@Component
struct hdrBrightnessDemo01 {
  // Image resource name (should exist in the app's media resources)
  @State imageUrl: string = 'img_1'

  // Current HDR brightness value (0 = no brightness boost, 1 = full boost)
  @State bright: number = 0

  aboutToAppear(): void {
    // Lifecycle hook: Called when the component is about to appear

    // Retrieve the media resource using the resource manager
    let img = getContext().resourceManager.getMediaByNameSync(this.imageUrl)

    // Create an ImageSource instance from the media buffer
    let imageSource = image.createImageSource(img.buffer.slice(0))

    // Get image metadata to determine if it is HDR
    let imageInfo = imageSource.getImageInfoSync()

    // Log whether the image supports HDR
    if (imageInfo == undefined) {
      console.error('Failed to obtain the image information')
    } else {
      console.info('imageInfo.isHdr: ' + imageInfo.isHdr)
    }
  }

  build() {
    Column() {
      // Display the image and apply dynamic HDR brightness
      Image($r('app.media.img_1'))
        .width('50%')           // Set image width to 50% of the screen
        .height('auto')         // Height adjusts automatically to maintain aspect ratio
        .margin({ top: 160 })   // Top margin spacing
        .hdrBrightness(this.bright) // Apply HDR brightness value

      // Button to toggle brightness between 0 and 1
      Button('Toggle Brightness (0 <-> 1)')
        .onClick(() => {
          // Animate the brightness transition
          animateTo({}, () => {
            this.bright = 1.0 - this.bright
          })
        })
    }
    .height('100%') // Ensure the column takes full screen height
  }
}
