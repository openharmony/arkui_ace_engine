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
 * 图片点击放大示例
 */
@Entry
@Component
struct ImageExample076 {
  @State scale: number = 1
  @State offsetX: number = 0
  @State offsetY: number = 0
  @State isExpanded: boolean = false

  build() {
    Column() {
      Text('图片点击放大示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Stack() {
        Image($r('app.media.png'))
          .width(this.isExpanded ? 300 : 200)
          .height(this.isExpanded ? 300 : 200)
          .scale({ x: this.scale, y: this.scale })
          .offset({ x: this.offsetX, y: this.offsetY })
          .objectFit(ImageFit.Cover)
          .borderRadius(15)
          .shadow({ radius: 10, color: Color.Gray, offsetX: 5, offsetY: 5 })
          .onClick(() => {
            this.isExpanded = !this.isExpanded
            if (!this.isExpanded) {
              this.scale = 1
              this.offsetX = 0
              this.offsetY = 0
            }
          })
          .gesture(
            PinchGesture({ fingers: 2 })
              .onActionUpdate((event: GestureEvent) => {
                if (this.isExpanded) {
                  this.scale = event.scale
                }
              })
          )

        if (!this.isExpanded) {
          Text('点击放大')
            .fontSize(14)
            .fontColor(Color.White)
            .padding(8)
            .backgroundColor('rgba(0, 0, 0, 0.5)')
            .borderRadius(5)
        }
      }
      .margin({ bottom: 20 })

      if (this.isExpanded) {
        Column() {
          Text('双指缩放图片')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text('再次点击关闭')
            .fontSize(14)
            .fontColor(Color.Gray)
        }
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
