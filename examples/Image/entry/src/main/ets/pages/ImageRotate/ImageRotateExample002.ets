/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This code defines a component named `ImageRotatePage2` that demonstrates various image rendering features 
 * such as rotation, auto-resizing, and circular clipping using the Image component.
 * 
 * It includes:
 * - State variables for managing different image resources, rotation orientation, auto-resize behavior, and 
 * clip dimensions.
 * - An array of orientation options used to dynamically change the image orientation when a button is clicked.
 * - Multiple `Image` components that display images with different embedded EXIF orientations.
 *   Each image applies dynamic properties including:
 *   - `autoResize`: Toggles whether the image should scale based on layout constraints.
 *   - `orientation`: Applies rotation based on the EXIF orientation enum.
 *   - `clipShape`: Clips the image into a circle with customizable width and height.
 * - Interactive buttons to:
 *   - Toggle the `autoResize` property.
 *   - Adjust the clipping shape size.
 *   - Cycle through different orientation modes.
 * 
 * Helper functions are also provided to convert enum values (e.g., orientation, repeat, fit) to human-readable strings 
 * for display purposes.
 * 
 * This component serves as a visual test case for image manipulation and styling in the UI framework.
 */

import { CircleShape } from '@kit.ArkUI'

@Entry
@Component
struct ImageRotatePage2 {
  @State res1: ResourceStr | undefined = $r('app.media.horizontal')
  @State res2: ResourceStr | undefined = $r('app.media.rotate90cw')
  @State res3: ResourceStr | undefined = $r('app.media.rotate270cw')
  @State res4: ResourceStr | undefined = $r('app.media.rotate180')
  @State orientation: ImageRotateOrientation = ImageRotateOrientation.UP
  @State autoResize: boolean = false
  @State clipWidth: number = 50
  @State clipHeight: number = 50

  idx: number = 0
  orientations: Array<ImageRotateOrientation> = [
    ImageRotateOrientation.DOWN,
    ImageRotateOrientation.LEFT,
    ImageRotateOrientation.RIGHT,
    ImageRotateOrientation.AUTO,
    ImageRotateOrientation.UP,
  ]

  build() {
    Column() {
      Image(this.res1)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay('horizontal')
        .clipShape(new CircleShape({width: this.clipWidth, height: this.clipHeight}))

      Image(this.res2)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay('rotate90cw')
        .clipShape(new CircleShape({width: this.clipWidth, height: this.clipHeight}))
      
      Image(this.res3)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay('rotate270cw')
        .clipShape(new CircleShape({width: this.clipWidth, height: this.clipHeight}))

      Image(this.res4)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay('rotate180')
        .clipShape(new CircleShape({width: this.clipWidth, height: this.clipHeight}))

      Button('切换autoResize属性 ${this.autoResize}')
        .onClick(() => {
          this.autoResize = !this.autoResize
        })

      Button('切换ClipShape的宽度和高度属性')
        .onClick(() => {
          if (this.clipWidth == 100) {
            this.clipWidth = 50
            this.clipHeight = 50
          } else {
            this.clipWidth = 100
            this.clipHeight = 100
          }
        })

      Button('点击切换不同的orientation ${convertOrientationToString(this.orientation)}')
        .onClick(() => {
          // 点击图片区域切换旋转信息
          if (this.idx == this.orientations.length) {
            this.idx = 0
          }
          this.orientation = this.orientations[this.idx]
          this.idx++;
        })
    }
    .height('100%')
    .width('100%')
  }
}

export function convertOrientationToString(orientation: ImageRotateOrientation): string | undefined {
  switch (orientation) {
    case ImageRotateOrientation.UP:
      return 'UP'
    case ImageRotateOrientation.DOWN:
      return 'DOWN'
    case ImageRotateOrientation.LEFT:
      return 'LEFT'
    case ImageRotateOrientation.RIGHT:
      return 'RIGHT'
    case ImageRotateOrientation.AUTO:
      return 'AUTO'
    default:
      return undefined
  }
}

export function convertRepeatToString(orientation: ImageRepeat): string | undefined {
  switch (orientation) {
    case ImageRepeat.NoRepeat:
      return 'NoRepeat'
    case ImageRepeat.X:
      return 'X'
    case ImageRepeat.Y:
      return 'Y'
    case ImageRepeat.XY:
      return 'XY'
    default:
      return undefined
  }
}

export function convertImageFitToString(fit: ImageFit): string | undefined {
  switch (fit) {
    case ImageFit.Contain:
      return 'Contain'
    case ImageFit.Cover:
      return 'Cover'
    case ImageFit.Auto:
      return 'Auto'
    case ImageFit.Fill:
      return 'Fill'
    case ImageFit.ScaleDown:
      return 'ScaleDown'
    case ImageFit.None:
      return 'None'
    case ImageFit.TOP_START:
      return 'TOP_START'
    case ImageFit.TOP:
      return 'TOP'
    case ImageFit.TOP_END:
      return 'TOP_END'
    case ImageFit.START:
      return 'START'
    case ImageFit.CENTER:
      return 'CENTER'
    case ImageFit.END:
      return 'END'
    case ImageFit.BOTTOM_START:
      return 'BOTTOM_START'
    case ImageFit.BOTTOM:
      return 'BOTTOM'
    case ImageFit.BOTTOM_END:
      return 'BOTTOM_END'
    default:
      return undefined
  }
}