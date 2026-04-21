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
@Entry
@Component
struct ImageRotateOrientationIndex {
  @State message: string = 'Hello World';
  @State text: string = "Image组件引入exif规范不支持的图源，设置autoResize属性"
  @State orientation: ImageRotateOrientation = ImageRotateOrientation.UP
  @State autoResize: boolean = false
  @State resource: Resource = $r('app.media.startIcon')
  @State onTree: boolean = true
  @State rotateDegree: number = 0
  @State fit: ImageFit = ImageFit.None
  res: Resource = $r('app.media.startIcon')
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
      Scroll() {

        Column() {
          Row() {
            Text('IMG_H_MIRROR_CCW')
            Image($r('app.media.startIcon'))
              .width(100)
              .height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
              .objectFit(ImageFit.Fill)
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
              .objectFit(ImageFit.Fill)
          }

          Row() {
            Text('IMG_V_MIRROR')
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('IMG_H_MIRROR')
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('IMG_H_MIRROR_CW')
            Image($r('app.media.foreground'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5).objectFit(ImageFit.Cover)
            Image($r('app.media.foreground'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5).objectFit(ImageFit.Cover)
          }

          Row() {
            Text('IMG_CCW')
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('IMG_CW')
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('IMG_DOWN')
            Image($r('app.media.foreground'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.foreground'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }

          Row() {
            Text('UP')
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
          Row() {
            Text('app.media.H_MIRROR_CW1')
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
          Row() {
            Text('app.media.H_MIRROR_CW2')
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
          Row() {
            Text('app.media.H_MIRROR_CCW1')
            Image($r('app.media.foreground'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.foreground'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
          Row() {
            Text('app.media.H_MIRROR_CCW2')
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
          Row() {
            Text('app.media.UP1')
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
              .privacySensitive(true)
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
          Row() {
            Text('app.media.V_MIRROR')
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
          Row() {
            Text('app.media.CCW1')
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.startIcon'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
          Row() {
            Text('app.media.CW1')
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.AUTO)
              .margin(5)
            Image($r('app.media.background'))
              .width(100).height(100)
              .orientation(ImageRotateOrientation.UP)
              .margin(5)
          }
        }
      }

    }
    .height('100%')
    .width('100%')
  }
}
