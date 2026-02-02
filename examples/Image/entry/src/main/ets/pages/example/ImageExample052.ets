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
 * 图片渲染模式示例
 */
@Entry
@Component
struct ImageExample052 {
  @State renderMode: ImageRenderMode = ImageRenderMode.Original

  build() {
    Column() {
      Text('图片渲染模式示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .renderMode(this.renderMode)
        .margin({ bottom: 20 })

      Row() {
        Button('原图模式')
          .onClick(() => {
            this.renderMode = ImageRenderMode.Original
          })
          .margin({ right: 10 })

        Button('模板模式')
          .onClick(() => {
            this.renderMode = ImageRenderMode.Template
          })
      }

      Text('当前模式: ' + (this.renderMode === ImageRenderMode.Original ? '原图' : '模板'))
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
