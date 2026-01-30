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
 * 图片水印示例
 */
@Entry
@Component
struct ImageExample077 {
  @State showWatermark: boolean = true
  @State watermarkText: string = '水印'

  build() {
    Column() {
      Text('图片水印示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Stack({ alignContent: Alignment.BottomEnd }) {
        Image($r('app.media.png'))
          .width(300)
          .height(300)
          .objectFit(ImageFit.Cover)

        if (this.showWatermark) {
          Column() {
            Text(this.watermarkText)
              .fontSize(12)
              .fontColor('rgba(255, 255, 255, 0.8)')
              .padding({ left: 10, right: 10, top: 5, bottom: 5 })
              .backgroundColor('rgba(0, 0, 0, 0.3)')
              .borderRadius({ topLeft: 10, bottomRight: 10 })
          }
          .margin(10)
        }
      }
      .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('显示水印')
          .onClick(() => {
            this.showWatermark = true
          })
        Button('隐藏水印')
          .onClick(() => {
            this.showWatermark = false
          })
      }
      .margin({ bottom: 10 })

      Row() {
        Text('水印文字: ')
          .fontSize(14)
        TextInput({ text: this.watermarkText })
          .width(150)
          .height(40)
          .onChange((value) => {
            this.watermarkText = value
          })
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
