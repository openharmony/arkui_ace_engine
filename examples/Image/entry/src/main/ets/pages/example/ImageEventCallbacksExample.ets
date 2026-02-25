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
 * Image component event callbacks examples
 */
@Entry
@Component
struct ImageEventCallbacksExample {
  @State loadStatus: string = '未加载'
  @State progress: number = 0

  build() {
    Column({ space: 20 }) {
      Text('事件回调示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // onComplete - 加载完成
      Column({ space: 15 }) {
        Text('onComplete (加载完成)')
          .fontSize(16)
        Image($r('app.media.app_icon'))
            .width(200)
            .height(200)
            .onComplete(() => {
              this.loadStatus = '加载成功'
            })
          .border({ width: 2, color: Color.Green })
        Text('状态: ' + this.loadStatus)
          .fontSize(14)
          .fontColor(this.loadStatus === '加载成功' ? Color.Green : Color.Gray)
      }

      // onError - 加载失败
      Column({ space: 15 }) {
        Text('onError (加载失败)')
          .fontSize(16)
        Image($r('app.media.invalid_icon'))
            .width(200)
            .height(200)
            .onError(() => {
              this.loadStatus = '加载失败'
            })
          .border({ width: 2, color: Color.Red })
        Text('状态: ' + this.loadStatus)
          .fontSize(14)
          .fontColor(this.loadStatus === '加载失败' ? Color.Red : Color.Gray)
      }

      Divider().strokeWidth(2)

      // 进度回调
      Column({ space: 15 }) {
        Text('onProgress (加载进度)')
          .fontSize(16)
        Text('进度: ' + this.progress + '%')
          .fontSize(14)
        Image($r('app.media.large_image'))
            .width(300)
            .height(100)
            .onProgress((dlNow: number, dlTotal: number) => {
              this.progress = Math.floor(dlNow / dlTotal * 100)
            })
          .border({ width: 2, color: Color.Blue })

        // 模拟进度更新
        Button('模拟进度更新')
          .fontSize(14)
          .onClick(() => {
            this.progress = Math.min(100, this.progress + 10)
          })
      }

      Divider().strokeWidth(2)

      Text('事件回调用于处理图片加载的生命周期')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
