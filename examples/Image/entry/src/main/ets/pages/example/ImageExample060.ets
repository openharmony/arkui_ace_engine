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
 * 图片缩放模式示例
 */
@Entry
@Component
struct ImageExample060 {
  @State imageFit: ImageFit = ImageFit.Cover

  build() {
    Column() {
      Text('图片缩放模式示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(150)
        .objectFit(this.imageFit)
        .backgroundColor('#f0f0f0')
        .margin({ bottom: 20 })

      Row({ space: 5 }) {
        Button('Cover')
          .fontSize(12)
          .onClick(() => {
            this.imageFit = ImageFit.Cover
          })
        Button('Contain')
          .fontSize(12)
          .onClick(() => {
            this.imageFit = ImageFit.Contain
          })
        Button('Fill')
          .fontSize(12)
          .onClick(() => {
            this.imageFit = ImageFit.Fill
          })
      }
      .margin({ bottom: 5 })

      Row({ space: 5 }) {
        Button('None')
          .fontSize(12)
          .onClick(() => {
            this.imageFit = ImageFit.None
          })
        Button('ScaleDown')
          .fontSize(12)
          .onClick(() => {
            this.imageFit = ImageFit.ScaleDown
          })
      }

      Text('当前模式: ' + this.getFitName())
        .fontSize(14)
        .margin({ top: 15 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }

  getFitName(): string {
    switch (this.imageFit) {
      case ImageFit.Cover:
        return 'Cover'
      case ImageFit.Contain:
        return 'Contain'
      case ImageFit.Fill:
        return 'Fill'
      case ImageFit.None:
        return 'None'
      case ImageFit.ScaleDown:
        return 'ScaleDown'
      default:
        return '未知'
    }
  }
}
