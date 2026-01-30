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
 * 图片加载状态示例
 */
@Entry
@Component
struct ImageExample062 {
  @State loadingState: string = '加载中'
  @State imageLoaded: boolean = false

  build() {
    Column() {
      Text('图片加载状态示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Stack() {
        if (this.imageLoaded) {
          Image($r('app.media.png'))
            .width(200)
            .height(200)
        } else {
          Column() {
            LoadingProgress()
              .width(50)
              .height(50)
            Text('加载中...')
              .fontSize(14)
              .margin({ top: 10 })
          }
          .width(200)
          .height(200)
          .justifyContent(FlexAlign.Center)
          .backgroundColor('#f0f0f0')
        }
      }
      .margin({ bottom: 20 })

      Row() {
        Button('加载图片')
          .onClick(() => {
            this.loadingState = '加载中'
            this.imageLoaded = false
            setTimeout(() => {
              this.imageLoaded = true
              this.loadingState = '加载完成'
            }, 1000)
          })
          .margin({ right: 10 })

        Button('重置')
          .onClick(() => {
            this.imageLoaded = false
            this.loadingState = '加载中'
          })
      }

      Text('状态: ' + this.loadingState)
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
