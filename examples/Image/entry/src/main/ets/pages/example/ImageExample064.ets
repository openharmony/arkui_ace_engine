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
 * 图片占位图示例
 */
@Entry
@Component
struct ImageExample064 {
  @State useAlt: boolean = true
  @State imageLoaded: boolean = false

  build() {
    Column() {
      Text('图片占位图示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image(this.imageLoaded ? $r('app.media.png') : '')
        .width(200)
        .height(200)
        .alt(this.useAlt ? $r('app.media.app_icon') : undefined)
        .onComplete(() => {
          this.imageLoaded = true
        })
        .margin({ bottom: 20 })

      Row() {
        Button('显示占位图')
          .onClick(() => {
            this.useAlt = true
          })
          .margin({ right: 10 })

        Button('隐藏占位图')
          .onClick(() => {
            this.useAlt = false
          })
      }
      .margin({ bottom: 10 })

      Button('重新加载')
        .onClick(() => {
          this.imageLoaded = false
          setTimeout(() => {
            this.imageLoaded = true
          }, 500)
        })

      Text('占位图: ' + (this.useAlt ? '启用' : '禁用'))
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
