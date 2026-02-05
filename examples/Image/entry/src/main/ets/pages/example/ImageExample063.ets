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
 * 图片错误处理示例
 */
@Entry
@Component
struct ImageExample063 {
  @State showError: boolean = false
  @State errorMessage: string = ''

  build() {
    Column() {
      Text('图片错误处理示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      if (this.showError) {
        Column() {
          Text('图片加载失败')
            .fontSize(16)
            .fontColor(Color.Red)
            .margin({ bottom: 10 })
          Text(this.errorMessage)
            .fontSize(14)
            .fontColor(Color.Gray)
          Image($r('app.media.app_icon'))
            .width(100)
            .height(100)
            .margin({ top: 10 })
        }
        .width(200)
        .height(200)
        .justifyContent(FlexAlign.Center)
        .backgroundColor('#ffe0e0')
        .borderRadius(10)
      } else {
        Image($r('app.media.png'))
          .width(200)
          .height(200)
          .onError((error) => {
            this.showError = true
            this.errorMessage = error?.message ?? '未知错误'
          })
      }
      .margin({ bottom: 20 })

      Button('模拟错误')
        .onClick(() => {
          this.showError = true
          this.errorMessage = '模拟的错误信息'
        })

      Button('重试')
        .margin({ left: 10 })
        .onClick(() => {
          this.showError = false
          this.errorMessage = ''
        })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
