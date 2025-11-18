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
import { convertImageFitToString, convertOrientationToString } from "./utils"
import { CircleShape } from '@kit.ArkUI'

@Entry
@Component
struct Test01 {
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
        .overlay("horizontal")
        .clipShape(new CircleShape({width: this.clipWidth, height: this.clipHeight}))


      Image(this.res2)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay("rotate90cw")
        .clipShape(new CircleShape({width: this.clipWidth, height: this.clipHeight}))


      Image(this.res3)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay("rotate270cw")
        .clipShape(new CircleShape({width: this.clipWidth, height: this.clipHeight}))

      Image(this.res4)
        .height(100)
        .width(100)
        .autoResize(this.autoResize)
        .orientation(this.orientation)
        .overlay("rotate180")
        .clipShape(new CircleShape({width: this.clipWidth, height: this.clipHeight}))

      Button(`切换autoResize属性 ${this.autoResize}`)
        .onClick(() => {
          this.autoResize = !this.autoResize
        })

      Button(`切换ClipShape的宽度和高度属性`)
        .onClick(() => {
          if (this.clipWidth == 100) {
            this.clipWidth = 50
            this.clipHeight = 50
          } else {
            this.clipWidth = 100
            this.clipHeight = 100
          }
        })

      Button(`点击切换不同的orientation ${convertOrientationToString(this.orientation)}`)
        .onClick(() => {
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
