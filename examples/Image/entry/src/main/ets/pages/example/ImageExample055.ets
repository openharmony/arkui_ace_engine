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
 * 图片颜色滤镜示例
 */
@Entry
@Component
struct ImageExample055 {
  @State applyFilter: boolean = false

  build() {
    Column() {
      Text('图片颜色滤镜示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .colorFilter(this.applyFilter ? [
          1.0, 0.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 0.0, 1.0, 0.0
        ] : [])
        .margin({ bottom: 20 })

      Row() {
        Button('应用滤镜')
          .onClick(() => {
            this.applyFilter = true
          })
          .margin({ right: 10 })

        Button('移除滤镜')
          .onClick(() => {
            this.applyFilter = false
          })
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
