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
 * 图片网格布局示例
 */
@Entry
@Component
struct ImageExample073 {
  @State imageCount: number = 4

  build() {
    Column() {
      Text('图片网格布局示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceBetween }) {
        ForEach(Array.from({ length: this.imageCount }), (_, index) => {
          Image($r('app.media.png'))
            .width('45%')
            .aspectRatio(1)
            .objectFit(ImageFit.Cover)
            .borderRadius(10)
            .margin({ bottom: 10 })
        })
      }
      .width('100%')

      Row({ space: 10 }) {
        Button('2张')
          .onClick(() => {
            this.imageCount = 2
          })
        Button('4张')
          .onClick(() => {
            this.imageCount = 4
          })
        Button('6张')
          .onClick(() => {
            this.imageCount = 6
          })
        Button('8张')
          .onClick(() => {
            this.imageCount = 8
          })
      }
      .margin({ top: 20 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
