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
 * 图片对齐方式示例
 */
@Entry
@Component
struct ImageExample061 {
  @State alignment: Alignment = Alignment.Center

  build() {
    Column() {
      Text('图片对齐方式示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(100)
        .height(100)
        .margin({ bottom: 20 })
        .border({ width: 1, color: Color.Gray })

      Text('在容器中的对齐方式')
        .fontSize(14)
        .margin({ bottom: 10 })

      Row({ space: 10 }) {
        Button('左上')
          .onClick(() => {
            this.alignment = Alignment.TopStart
          })
        Button('顶部')
          .onClick(() => {
            this.alignment = Alignment.Top
          })
        Button('右上')
          .onClick(() => {
            this.alignment = Alignment.TopEnd
          })
      }
      .margin({ bottom: 5 })

      Row({ space: 10 }) {
        Button('左侧')
          .onClick(() => {
            this.alignment = Alignment.Start
          })
        Button('居中')
          .onClick(() => {
            this.alignment = Alignment.Center
          })
        Button('右侧')
          .onClick(() => {
            this.alignment = Alignment.End
          })
      }
      .margin({ bottom: 5 })

      Row({ space: 10 }) {
        Button('左下')
          .onClick(() => {
            this.alignment = Alignment.BottomStart
          })
        Button('底部')
          .onClick(() => {
            this.alignment = Alignment.Bottom
          })
        Button('右下')
          .onClick(() => {
            this.alignment = Alignment.BottomEnd
          })
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
