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
 * 通过slice拉伸图片
 */
@Entry
@Component
struct Index {
  @State top: number = 10
  @State bottom: number = 10
  @State left: number = 10
  @State right: number = 10

  build() {
    Column({ space: 5 }) {
      // 原图效果
      Image($r('app.media.landscape'))
        .width(200).height(200)
        .border({ width: 2, color: Color.Pink })
        .objectFit(ImageFit.Contain)

      // 图像拉伸效果，设置resizable属性，对图片不同方向进行拉伸
      Image($r('app.media.landscape'))
        .resizable({
          slice: {
            left: this.left,
            right: this.right,
            top: this.top,
            bottom: this.bottom
          }
        })
        .width(200)
        .height(200)
        .border({ width: 2, color: Color.Pink })
        .objectFit(ImageFit.Contain)

      Row() {
        Button('add top to ' + this.top).fontSize(10)
          .onClick(() => {
            this.top += 10
          })
        Button('add bottom to ' + this.bottom).fontSize(10)
          .onClick(() => {
            this.bottom += 10
          })
      }

      Row() {
        Button('add left to ' + this.left).fontSize(10)
          .onClick(() => {
            this.left += 10
          })
        Button('add right to ' + this.right).fontSize(10)
          .onClick(() => {
            this.right += 10
          })
      }

    }
    .justifyContent(FlexAlign.Start).width('100%').height('100%')
  }
}