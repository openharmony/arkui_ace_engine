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
 * Example: Demonstrates displaying a local animated GIF image.
 *
 * The `Image` component automatically plays GIF animation in a loop.
 * This example also provides buttons to simulate loading failure and recovery.
 */
@Entry
@Component
struct gifDemo01 {
  // Image source path (app resource)
  @State gifSrc: Resource = $r('app.media.loading_gif')

  // Whether to simulate a failed load
  @State loadFail: boolean = false

  build() {
    Column() {
      // Display GIF or an error placeholder if load failed
      if (!this.loadFail) {
        Image(this.gifSrc)
          .width(200)
          .height(200)
          .margin({ top: 80 })
          .alt('GIF loading failed') // Alternative text if rendering fails
      } else {
        Text('GIF load failed')
          .fontSize(18)
          .fontColor('#FF3B30')
          .margin({ top: 120 })
      }

      // Buttons for control
      Row() {
        Button('Simulate Fail')
          .margin({ right: 10 })
          .onClick(() => {
            this.loadFail = true
          })
        Button('Reload GIF')
          .onClick(() => {
            this.loadFail = false
          })
      }
      .margin({ top: 20 })
    }
    .alignItems(HorizontalAlign.Center)
    .height('100%')
  }
}
