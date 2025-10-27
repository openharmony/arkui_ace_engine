/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import { convertImageFitToString, convertOrientationToString, convertRepeatToString } from "./utils"
import { CircleShape } from '@kit.ArkUI'


class OrientationModifier implements AttributeModifier<ImageAttribute> {
  private idx = 3
  private orientation: ImageRotateOrientation = ImageRotateOrientation.UP
  private orientations: Array<ImageRotateOrientation> = [
    ImageRotateOrientation.DOWN,
    ImageRotateOrientation.LEFT,
    ImageRotateOrientation.RIGHT,
    ImageRotateOrientation.AUTO,
    ImageRotateOrientation.UP,
  ]

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.orientation(this.orientation)
  }

  updateOrientation() {
    if (this.idx == 5) {
      this.idx = 0
    }
    this.orientation = this.orientations[this.idx]
    this.idx++
  }

  getOrientation() {
    return this.orientation
  }
}


@Entry
@Component
struct Test01 {
  @State res1: ResourceStr | undefined = $r('app.media.horizontal')
  @State res2: ResourceStr | undefined = $r('app.media.rotate90cw')
  @State res3: ResourceStr | undefined = $r('app.media.rotate270cw')
  @State res4: ResourceStr | undefined = $r('app.media.rotate180')
  @State res5: ResourceStr | undefined = $r('app.media.leaf')
  @State res6: ResourceStr | undefined = $r('app.media.huawei_200')
  @State text4: string = "Image组件引入exif规范支持的图源，设置borderRadius属性"
  @State orientation: ImageRotateOrientation = ImageRotateOrientation.AUTO
  @State fit: ImageFit = ImageFit.Cover
  @State repeat: ImageRepeat = ImageRepeat.NoRepeat
  @State autoResize: boolean = false
  @State modifier: OrientationModifier = new OrientationModifier()
  @State deleteOnTree: boolean = true
  @State left: number = 10
  @State right: number = 10
  @State top: number = 20
  @State bottom: number = 20


  idx: number = 0
  idx2: number = 0
  orientations: Array<ImageRotateOrientation> = [
    ImageRotateOrientation.DOWN,
    ImageRotateOrientation.LEFT,
    ImageRotateOrientation.RIGHT,
    ImageRotateOrientation.AUTO,
    ImageRotateOrientation.UP,
  ]
  repeats: Array<ImageRepeat> = [
    ImageRepeat.NoRepeat,
    ImageRepeat.X,
    ImageRepeat.Y,
    ImageRepeat.XY,
  ]

  build() {
    Column() {
      if (this.deleteOnTree) {
        Image(this.res6)
          .width(150)
          .height(150)
          .autoResize(this.autoResize)
          .orientation(this.orientation)
          .overlay("horizontal")
          .objectRepeat(this.repeat)
          .matchTextDirection(true)

        Image(this.res2)
          .width(150)
          .height(150)
          .autoResize(this.autoResize)
          .orientation(this.orientation)
          .overlay("rotate90cw")
          .objectRepeat(this.repeat)
          .matchTextDirection(true)

        Image(this.res3)
          .width(150)
          .height(150)
          .autoResize(this.autoResize)
          .orientation(this.orientation)
          .overlay("rotate270cw")
          .objectRepeat(this.repeat)
          .matchTextDirection(true)

        Image(this.res5)
          .width(150)
          .height(150)
          .autoResize(this.autoResize)
          .orientation(this.orientation)
          .overlay("rotate180")
          .objectRepeat(this.repeat)
          .matchTextDirection(true)
      }

      Button(`切换autoResize属性 ${this.autoResize}`)
        .onClick(() => {
          this.autoResize = !this.autoResize
        })

      Button(`点击切换不同的orientation ${convertOrientationToString(this.orientation)}`)
        .onClick(() => {
          if (this.idx == this.orientations.length) {
            this.idx = 0
          }
          this.orientation = this.orientations[this.idx]
          this.idx++;
        })

      Button(`点击切换不同的repeat ${convertRepeatToString(this.repeat)}`)
        .onClick(() => {
          if (this.idx2 == this.repeats.length) {
            this.idx2 = 0
          }
          this.repeat = this.repeats[this.idx2]
          this.idx2++;
        })
    }
    .height('100%')
    .width('100%')
  }
}
