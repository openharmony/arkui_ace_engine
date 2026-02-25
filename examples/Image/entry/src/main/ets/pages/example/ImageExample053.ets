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
 * 图片插值方式示例
 */
@Entry
@Component
struct ImageExample053 {
  @State interpolation: ImageInterpolation = ImageInterpolation.None

  build() {
    Column() {
      Text('图片插值方式示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(300)
        .height(300)
        .interpolation(this.interpolation)
        .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('无')
          .onClick(() => {
            this.interpolation = ImageInterpolation.None
          })
        Button('低')
          .onClick(() => {
            this.interpolation = ImageInterpolation.Low
          })
        Button('中')
          .onClick(() => {
            this.interpolation = ImageInterpolation.Medium
          })
        Button('高')
          .onClick(() => {
            this.interpolation = ImageInterpolation.High
          })
      }
      .margin({ bottom: 10 })

      Text('当前插值: ' + this.getInterpolationName())
        .fontSize(14)
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }

  getInterpolationName(): string {
    switch (this.interpolation) {
      case ImageInterpolation.None:
        return '无'
      case ImageInterpolation.Low:
        return '低'
      case ImageInterpolation.Medium:
        return '中'
      case ImageInterpolation.High:
        return '高'
      default:
        return '未知'
    }
  }
}
