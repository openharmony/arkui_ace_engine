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
import { image } from '@kit.ImageKit'


@Entry
@Component
struct Test01 {
  @State text: string = "Image组件引入exif规范不支持的图源，设置autoResize属性"
  @State orientation: ImageRotateOrientation = ImageRotateOrientation.UP
  @State autoResize: boolean = false
  @State resource: Resource = $r('app.media.huawei_200')
  @State onTree: boolean = true
  @State rotateDegree: number = 0
  @State fit: ImageFit = ImageFit.None
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

  @State repeat: ImageRepeat = ImageRepeat.NoRepeat
  repeats: Array<ImageRepeat> = [
    ImageRepeat.NoRepeat,
    ImageRepeat.X,
    ImageRepeat.Y,
    ImageRepeat.XY,
  ]

  build() {
    Column() {
      if (this.onTree) {
        Image(this.resource)
          .autoResize(this.autoResize)
          .height(400)
          .width(200)
          .border({
            width: 1,
            color: Color.Red
          })
          .objectFit(this.fit)
          .orientation(this.orientation)
          .overlay(convertOrientationToString(this.orientation))
          .matchTextDirection(true)
          .rotate({ angle: this.rotateDegree })
          .objectRepeat(this.repeat)
      }

      Row(){
        Button(`huwei`)
          .onClick(() => {
            this.resource=$r('app.media.huawei_200')
          })
        Button(`gif`)
          .onClick(() => {
            this.resource=$r('app.media.leaf')
          })
        Button(`UP`)
          .onClick(() => {
            this.resource=$r('app.media.UP')
          })
      }


      Button(`改变rotate角度 ${this.rotateDegree}`)
        .onClick(() => {
          this.rotateDegree+=30
        })

      Button(`切换上下树 ${this.onTree}`)
        .onClick(() => {
          this.onTree = !this.onTree
        })

      Button(`点击切换auto resize ${this.autoResize}`)
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
