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
 * 图片draggable拖拽功能示例
 * 演示图片的拖拽交互，包括draggable属性和drag相关事件
 */
@Entry
@Component
struct ImageExample105 {
  @State isDraggable: boolean = true
  @State dragCount: number = 0
  @State dragLog: string[] = []
  @State dropAreaActive: boolean = false
  @State droppedImageVisible: boolean = false

  private maxLogSize: number = 8

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.dragLog.unshift(`${timestamp}: ${message}`)
    if (this.dragLog.length > this.maxLogSize) {
      this.dragLog.pop()
    }
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片draggable拖拽功能示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Row({ space: 20 }) {
          Button('开启拖拽')
            .onClick(() => {
              this.isDraggable = true
              this.addLog('开启拖拽')
            })
            .backgroundColor(this.isDraggable ? 0x007DFF : 0xE0E0E0)
            .fontColor(this.isDraggable ? Color.White : 0x333333)

          Button('关闭拖拽')
            .onClick(() => {
              this.isDraggable = false
              this.addLog('关闭拖拽')
            })
            .backgroundColor(!this.isDraggable ? 0x007DFF : 0xE0E0E0)
            .fontColor(!this.isDraggable ? Color.White : 0x333333)
        }

        Text(`当前状态: ${this.isDraggable ? '可拖拽' : '不可拖拽'}`)
          .fontSize(14)
          .fontColor(0x666666)

        Row({ space: 20 }) {
          Column({ space: 10 }) {
            Text('可拖拽图片')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Image($r('app.media.startIcon'))
              .width(120)
              .height(120)
              .objectFit(ImageFit.Cover)
              .draggable(this.isDraggable)
              .border({ width: 2, color: Color.Orange })
              .borderRadius(8)
              .onDragStart(() => {
                this.dragCount++
                this.addLog(`拖拽开始 (第${this.dragCount}次)`)
                return this.getDragItem()
              })
              .onDragEnd(() => {
                this.addLog('拖拽结束')
              })
          }

          Column({ space: 10 }) {
            Text('拖放目标区域')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Column() {
              if (this.droppedImageVisible) {
                Image($r('app.media.startIcon'))
                  .width(80)
                  .height(80)
                  .objectFit(ImageFit.Cover)
                  .borderRadius(4)
              } else {
                Text('拖拽图片到此处')
                  .fontSize(14)
                  .fontColor(0x999999)
              }
            }
            .width(120)
            .height(120)
            .justifyContent(FlexAlign.Center)
            .alignItems(HorizontalAlign.Center)
            .border({
              width: 2,
              color: this.dropAreaActive ? Color.Green : 0xCCCCCC,
              style: this.dropAreaActive ? BorderStyle.Solid : BorderStyle.Dashed
            })
            .borderRadius(8)
            .backgroundColor(this.dropAreaActive ? 0xE8F5E9 : 0xF5F5F5)
            .onDrop(() => {
              this.droppedImageVisible = true
              this.dropAreaActive = false
              this.addLog('图片已放置到目标区域')
            })
            .onDragEnter(() => {
              this.dropAreaActive = true
              this.addLog('拖拽进入目标区域')
            })
            .onDragLeave(() => {
              this.dropAreaActive = false
              this.addLog('拖拽离开目标区域')
            })
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text(`拖拽次数: ${this.dragCount}`)
          .fontSize(14)
          .fontColor(0x666666)

        Column({ space: 5 }) {
          Text('事件日志:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          ForEach(this.dragLog, (log: string) => {
            Text(log)
              .fontSize(12)
              .fontColor(0x666666)
          })
        }
        .width('100%')
        .padding(10)
        .backgroundColor(0xFFFFFF)
        .borderRadius(8)
        .alignItems(HorizontalAlign.Start)
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  private getDragItem(): PixelMap | undefined {
    return undefined
  }
}
