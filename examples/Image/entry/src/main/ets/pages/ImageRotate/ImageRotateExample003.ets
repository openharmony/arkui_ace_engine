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
 * This code defines a component named `ImageRotatePage3` that demonstrates advanced image rendering features 
 * such as rotation, object fitting, custom resizing, and border radius styling using the Image component.
 * 
 * It includes:
 * - State variables for managing image resources, rotation orientation, auto-resize behavior, and object fit mode.
 * - Arrays of orientation and fit options for cycling through different display behaviors via buttons.
 * - Multiple `Image` components that render images with various EXIF-based orientations, each applying:
 *   - Dynamic height and width settings.
 *   - `autoResize` to control scaling behavior.
 *   - `orientation` to adjust rotation based on EXIF standards.
 *   - `objectFit` to control how the image fits within its container.
 *   - `borderRadius` for rounded corners, with customizable values for each corner.
 *   - Some images also use `resizable` to define custom scaling regions.
 * - Interactive buttons to:
 *   - Toggle the `autoResize` property.
 *   - Cycle through different orientation modes.
 *   - Switch between various `ImageFit` layout behaviors.
 */

import { CircleShape } from '@kit.ArkUI'

@Entry
@Component
struct ImageRotatePage3 {
  @State res1: ResourceStr | undefined = $r('app.media.horizontal')
  @State res2: ResourceStr | undefined = $r('app.media.rotate90cw')
  @State res3: ResourceStr | undefined = $r('app.media.rotate270cw')
  @State res4: ResourceStr | undefined = $r('app.media.rotate180')
  @State text4: string = 'Image组件引入exif规范支持的图源，设置borderRadius属性'
  @State orientation: ImageRotateOrientation = ImageRotateOrientation.UP
  @State autoResize: boolean = false
  @State fit: ImageFit = ImageFit.Cover
  idx: number = 0
  idx2: number = 0
  orientations: Array<ImageRotateOrientation> = [
    ImageRotateOrientation.DOWN,
    ImageRotateOrientation.LEFT,
    ImageRotateOrientation.RIGHT,
    ImageRotateOrientation.AUTO,
    ImageRotateOrientation.UP,
  ]
  fits: Array<ImageFit> = [
    ImageFit.Contain,
    ImageFit.Cover,
    ImageFit.Auto,
    ImageFit.Fill,
    ImageFit.ScaleDown,
    ImageFit.None,
    ImageFit.TOP_START,
    ImageFit.TOP,
    ImageFit.TOP_END,
    ImageFit.START,
    ImageFit.CENTER,
    ImageFit.END,
    ImageFit.BOTTOM_START,
    ImageFit.BOTTOM,
    ImageFit.BOTTOM_END,
  ]

  build() {
    Column() {
      Image(this.res1)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay('horizontal')
        .objectFit(this.fit)
        .borderRadius({
          topLeft: 10,
          topRight: 10,
          bottomLeft: 20,
          bottomRight: 20
        })

      Image(this.res2)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay('rotate90cw')
        .objectFit(this.fit)
        .resizable({
          slice: {
            left: 40,
            right: 10,
            top: 40,
            bottom: 5
          }
        })
        .borderRadius({
          topLeft: 10,
          topRight: 10,
          bottomLeft: 20,
          bottomRight: 20
        })

      Image(this.res3)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay('rotate270cw')
        .objectFit(this.fit)
        .borderRadius({
          topLeft: 10,
          topRight: 10,
          bottomLeft: 20,
          bottomRight: 20
        })

      Image(this.res4)
        .height(70)
        .width(80)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay('rotate180')
        .objectFit(this.fit)
        .borderRadius({
          topLeft: 10,
          topRight: 10,
          bottomLeft: 20,
          bottomRight: 20
        })

      Button(`切换autoResize属性 ${this.autoResize}`)
        .onClick(() => {
          this.autoResize = !this.autoResize
        })

      Button(`点击切换不同的orientation ${convertOrientationToString(this.orientation)}`)
        .onClick(() => {
          // 点击图片区域切换旋转信息
          if (this.idx == this.orientations.length) {
            this.idx = 0
          }
          this.orientation = this.orientations[this.idx]
          this.idx++;
        })

      Button(`切换填充模式: ${convertImageFitToString(this.fit)}`)
        .onClick(() => {
          if (this.idx2 == this.fits.length) {
            this.idx2 = 0
          }
          this.fit = this.fits[this.idx2++]
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