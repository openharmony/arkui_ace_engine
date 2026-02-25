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
 * Image component margin and padding examples
 */
@Entry
@Component
struct ImageMarginPaddingExample {
  @State marginValue: number = 20
  @State paddingValue: number = 20

  build() {
    Column({ space: 20 }) {
      Text('Margin 和 Padding 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // Margin 调整
      Column({ space: 15 }) {
        Text('外边距 (margin):')
          .fontSize(16)
        Slider({ value: this.marginValue, min: 0, max: 100, step: 5 })
          .onChange((value: number) => {
            this.marginValue = value
          })
        Image($r('app.media.app_icon'))
            .width(300)
            .height(200)
            .margin({ top: this.marginValue, bottom: this.marginValue, left: this.marginValue, right: this.marginValue })
            .border({ width: 2, color: Color.Green })
      }

      Divider().strokeWidth(2)

      // Padding 调整
      Column({ space: 15 }) {
        Text('内边距 (padding):')
          .fontSize(16)
        Slider({ value: this.paddingValue, min: 0, max: 50, step: 5 })
          .onChange((value: number) => {
            this.paddingValue = value
          })
        Image($r('app.media.app_icon'))
            .width(300)
            .height(200)
            .padding({ top: this.paddingValue, bottom: this.paddingValue, left: this.paddingValue, right: this.paddingValue })
            .border({ width: 2, color: Color.Blue })
      }

      Divider().strokeWidth(2)

      // 单独边距
      Column({ space: 15 }) {
        Text('单独设置各边距:')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(300)
            .height(200)
            .margin({ top: 10, right: 20, bottom: 30, left: 40 })
            .padding({ top: 15, right: 25, bottom: 35, left: 45 })
            .border({ width: 2, color: Color.Purple })
      }

      Divider().strokeWidth(2)

      // 百分比
      Column({ space: 15 }) {
        Text('百分比边距和内边距:')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width('80%')
            .height('80%')
            .margin({ top: '5%', right: '10%', bottom: '15%', left: '20%' })
            .padding({ top: '8%', right: '5%', bottom: '12%', left: '10%' })
            .border({ width: 2, color: Color.Orange })
      }

      Divider().strokeWidth(2)

      Text('margin/padding 属性控制图片与容器的间距')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
