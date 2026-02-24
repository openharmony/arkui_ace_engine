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
 * Image component draggable property examples
 */
@Entry
@Component
struct ImageDraggableExample {
  @State dragOffsetX: number = 0
  @State dragOffsetY: number = 0
  @State isDragging: boolean = false
  @State imageWidth: number = 200
  @State imageHeight: number = 200

  build() {
    Column({ space: 20 }) {
      Text('Draggable 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // 可拖拽区域
      Stack({ alignContent: Alignment.Center }) {
        Column() {
          Text('拖拽下面的图片')
            .fontSize(16)
            .margin({ bottom: 10 })

          // 可拖拽图片
          Image($r('app.media.app_icon'))
            .width(this.imageWidth)
            .height(this.imageHeight)
            .draggable(true)
            .border({ width: 2, color: Color.Blue })
            .offset({ x: this.dragOffsetX, y: this.dragOffsetY })
            .onDragStart((event: DragEvent) => {
              this.isDragging = true
            })
            .onDragUpdate((event: DragEvent) => {
              this.dragOffsetX = event.getOffsetX()
              this.dragOffsetY = event.getOffsetY()
            })
            .onDragEnd((event: DragEvent) => {
              this.isDragging = false
            })
        }

        // 拖拽状态指示器
        Text(this.isDragging ? '正在拖拽...' : '拖拽图片')
          .fontSize(18)
          .fontColor(this.isDragging ? Color.Red : Color.Green)
          .margin({ top: 20 })
      }

      Divider().strokeWidth(2)

      Text('draggable 属性使图片可以响应用户拖拽操作')
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
