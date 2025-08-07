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
 * This code snippet defines a component named 'Test01' which is designed to demonstrate the functionality of 
 * image manipulation and display using various properties and methods. The component includes:
 * - State variables for managing text, orientation, auto-resize settings, pixel maps, resources, GIFs, tree state,
 *   rotation degrees, and image fitting modes.
 * - An asynchronous 'aboutToAppear' lifecycle method that loads an image resource and converts it into a pixel map 
 *   when the component is about to be displayed.
 * - A 'build' method constructing the UI layout with interactive elements such as:
 *   - An Image component that dynamically applies properties like auto-resize, object fit, orientation, padding, 
 *     rotation, and repeat based on the component's state.
 *   - Buttons for interacting with the component, allowing users to change the rotation angle, toggle the visibility 
 *     of the image (on/off tree), switch auto-resize settings, cycle through different orientation modes, and alter 
 *     the image fitting mode.
 * - Helper functions ('convertOrientationToString', 'convertRepeatToString', 'convertImageFitToString') for converting 
 *   enum values to their string representations, aiding in UI updates and logging.
 * 
 * This example showcases dynamic image handling, including transformations and adjustments, within a user interface.
 */

import { image } from '@kit.ImageKit'

@Entry
@Component
struct Test01 {
  @State text: string = 'Image组件引入exif规范不支持的图源，设置autoResize属性'
  @State orientation: ImageRotateOrientation = ImageRotateOrientation.UP
  @State autoResize: boolean = false
  @State pixmap: image.PixelMap | undefined = undefined
  @State resource: Resource = $r('app.media.UP')
  @State gif: Resource = $r('app.media.leaf')
  @State onTree: boolean = true
  @State rotateDegree: number = 0
  @State fit: ImageFit = ImageFit.Cover
  res: Resource = $r('app.media.UP')
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

  async aboutToAppear() {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: this.res.bundleName,
      moduleName: this.res.moduleName,
      id: this.res.id
    })
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    })
    this.pixmap = createPixelMap
    await imageSource.release()
  }

  build() {
    Column() {
      if (this.onTree) {
        Image($r('app.media.bmp'))
          .autoResize(this.autoResize)
          .height(150)
          .width(150)
          .border({
            width: 1,
            color: Color.Red
          })
          .objectFit(this.fit)
          .orientation(this.orientation)
          .padding({
            left: 10,
            right: 10,
            top: 20,
            bottom: 20
          })
          .overlay(convertOrientationToString(this.orientation))
          .matchTextDirection(true)
          .rotate({ angle: this.rotateDegree })
          .objectRepeat(ImageRepeat.XY)
      }

      ImageAnimator()

      Button('改变rotate角度 ${this.rotateDegree}')
        .onClick(() => {
          this.rotateDegree += 30
        })

      Button('切换上下树 ${this.onTree}')
        .onClick(() => {
          this.onTree = !this.onTree
        })

      Button('点击切换auto resize ${this.autoResize}')
        .onClick(() => {
          this.autoResize = !this.autoResize
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

      Button('切换填充模式: ${convertImageFitToString(this.fit)}')
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