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
 * 图片同步加载示例
 */
@Entry
@Component
struct ImageExample050 {
  @State syncLoad: boolean = false

  build() {
    Column() {
      Text('图片同步加载示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .syncLoad(this.syncLoad)
        .margin({ bottom: 20 })

      Row() {
        Button('同步加载')
          .onClick(() => {
            this.syncLoad = true
          })
          .margin({ right: 10 })

        Button('异步加载')
          .onClick(() => {
            this.syncLoad = false
          })
      }

      Text('当前模式: ' + (this.syncLoad ? '同步' : '异步'))
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
