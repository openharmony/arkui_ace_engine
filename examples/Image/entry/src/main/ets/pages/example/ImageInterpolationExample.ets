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
 * Image component interpolation property examples
 */
@Entry
@Component
struct ImageInterpolationExample {
  @State currentInterpolation: ImageInterpolation = ImageInterpolation.None
  @State imageWidth: number = 300
  @State imageHeight: number = 300

  build() {
    Column({ space: 20 }) {
      Text('Interpolation 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
        // None - 不插值
        Column({ space: 10 }) {
          Text('None')
            .fontSize(16)
          Image($r('app.media.app_icon'))
            .width(this.imageWidth)
            .height(this.imageHeight)
            .interpolation(ImageInterpolation.None)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: this.currentInterpolation === ImageInterpolation.None ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentInterpolation = ImageInterpolation.None
            })
        }

        // Low - 低质量
        Column({ space: 10 }) {
          Text('Low (低质量)')
            .fontSize(16)
          Image($r('app.media.app_icon'))
            .width(this.imageWidth)
            .height(this.imageHeight)
            .interpolation(ImageInterpolation.Low)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: this.currentInterpolation === ImageInterpolation.Low ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentInterpolation = ImageInterpolation.Low
            })
        }

        // Medium - 中等质量
        Column({ space: 10 }) {
          Text('Medium (中等质量)')
            .fontSize(16)
          Image($r('app.media.app_icon'))
            .width(this.imageWidth)
            .height(this.imageHeight)
            .interpolation(ImageInterpolation.Medium)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: this.currentInterpolation === ImageInterpolation.Medium ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentInterpolation = ImageInterpolation.Medium
            })
        }

        // High - 高质量
        Column({ space: 10 }) {
          Text('High (高质量)')
            .fontSize(16)
          Image($r('app.media.app_icon'))
            .width(this.imageWidth)
            .height(this.imageHeight)
            .interpolation(ImageInterpolation.High)
            .objectFit(ImageFit.Cover)
            .border({ width: 2, color: this.currentInterpolation === ImageInterpolation.High ? Color.Green : Color.Transparent })
            .onClick(() => {
              this.currentInterpolation = ImageInterpolation.High
            })
        }
      }

      Divider().strokeWidth(2)

      Text('当前插值质量: ' + this.currentInterpolation)
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .margin({ top: 10 })

      Text('interpolation 属性控制图片缩放时的插值算法')
        .fontSize(14)
        .fontColor(Color.Blue)
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
