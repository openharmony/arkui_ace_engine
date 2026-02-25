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
 * Image component multiple sources examples
 */
@Entry
@Component
struct ImageMultipleSourceExample {
  @State sourceType: number = 0
  @State currentImage: number = 0

  build() {
    Column({ space: 20 }) {
      Text('多图片源切换示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // 图片源选择
      Column({ space: 15 }) {
        Text('选择图片源:')
          .fontSize(16)
        Row({ space: 10 }) {
          ForEach([0, 1, 2, 3, 4], (index: number) => {
            Button('源 ' + index)
              .fontSize(14)
              .border({ width: 2, color: this.currentImage === index ? Color.Green : Color.Transparent })
              .onClick(() => {
                this.currentImage = index
              })
          })
        }
      }

      // 显示当前源图片
      Column({ space: 15 }) {
        Text('当前显示: 源 ' + this.currentImage)
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.Blue)

        // 根据不同源显示不同图片
      if (this.currentImage === 0) {
        // 网络图片
        Image($r('app.media.network'))
          .width(300)
          .height(300)
          .border({ width: 2, color: Color.Blue })
      } else if (this.currentImage === 1) {
        // 本地图片
        Image($r('app.media.local'))
          .width(300)
          .height(300)
          .border({ width: 2, color: Color.Green })
      } else if (this.currentImage === 2) {
        // Data URL
        Image($r('app.media.app_icon'))
          .width(300)
          .height(300)
          .border({ width: 2, color: Color.Orange })
      } else if (this.currentImage === 3) {
        // Base64
        Image($r('app.media.base64_icon'))
          .width(300)
          .height(300)
          .border({ width: 2, color: Color.Red })
      } else if (this.currentImage === 4) {
        // 多媒体
        Image($r('app.multimedia.person'))
          .width(300)
          .height(300)
          .border({ width: 2, color: Color.Pink })
      }

      Divider().strokeWidth(2)

      Text('源类型说明:')
        .fontSize(16)
        Column({ space: 10 }) {
          Text('0: 网络 ($r)')
          .fontSize(14)
          Text('1: 本地 (local)')
          .fontSize(14)
          Text('2: Data (data:)')
          .fontSize(14)
          Text('3: Base64 编码')
          .fontSize(14)
          Text('4: 多媒体 (multimedia:)')
          .fontSize(14)
          .fontColor(Color.Gray)
        }

      // 动态切换
      Column({ space: 20 }) {
        Button('动态切换到随机源')
          .fontSize(16)
          .onClick(() => {
            this.currentImage = Math.floor(Math.random() * 5)
          })
          .fontSize(14)
      }

      Divider().strokeWidth(2)

      Text('多个 src 可以通过数组或对象动态设置')
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
