/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

@Builder
function dragSourceBuilder() {
  Column() {
    Text('预览')
      .fontSize(16)
      .fontColor(Color.White)
      .fontWeight(FontWeight.Bold)
  }
  .width(100)
  .height(60)
  .backgroundColor('#FF6B00')
  .borderRadius(8)
  .justifyContent(FlexAlign.Center)
  .alignItems(HorizontalAlign.Center)
}

@Entry
@Component
struct DragInteraction {
  @State eventLog: string = ''
  @State targetState: string = '等待拖拽进入...'
  @State targetBgColor: ResourceColor = '#E8E8E8'
  @State targetBorderColor: ResourceColor = '#CCCCCC'

  build() {
    Column() {
      Text('DragInteraction - 拖拽交互')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Start)
        .padding({ left: 20, top: 16, bottom: 8 })

      Text('拖拽源')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .padding({ left: 20 })

      Column() {
        Text('长按拖拽我')
          .fontSize(18)
          .fontColor(Color.White)
          .fontWeight(FontWeight.Bold)
      }
      .width(140)
      .height(100)
      .backgroundColor('#FF6B00')
      .borderRadius(12)
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)
      .margin({ top: 8 })
      .draggable(true)
      .onDragStart(() => {
        this.addLog('onDragStart: 拖拽开始')
        return dragSourceBuilder()
      })
      .onDragEnd(() => {
        this.addLog('onDragEnd: 拖拽结束')
      })

      Divider()
        .width('90%')
        .margin({ top: 16, bottom: 16 })

      Text('拖放目标')
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .padding({ left: 20 })

      Text(this.targetState)
        .fontSize(14)
        .fontColor('#333333')
        .width('100%')
        .padding({ left: 20, top: 4, bottom: 4 })

      Column() {
        Text('放置在此区域')
          .fontSize(18)
          .fontColor('#333333')
          .fontWeight(FontWeight.Bold)
        Text('allowDrop 已启用')
          .fontSize(12)
          .fontColor('#999999')
          .margin({ top: 6 })
      }
      .width('80%')
      .height(160)
      .backgroundColor(this.targetBgColor)
      .borderRadius(16)
      .border({
        width: 2,
        color: this.targetBorderColor,
        style: BorderStyle.Dashed
      })
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)
      .margin({ top: 8 })
      .allowDrop(['general.text'])
      .onDragEnter(() => {
        this.targetState = '拖拽进入目标区域'
        this.targetBgColor = '#E3F2FD'
        this.targetBorderColor = '#2196F3'
        this.addLog('onDragEnter: 拖拽进入目标区域')
      })
      .onDragMove(() => {
        this.targetState = '拖拽在目标区域移动'
        this.addLog('onDragMove: 拖拽在目标区域移动')
      })
      .onDragLeave(() => {
        this.targetState = '拖拽离开目标区域'
        this.targetBgColor = '#E8E8E8'
        this.targetBorderColor = '#CCCCCC'
        this.addLog('onDragLeave: 拖拽离开目标区域')
      })
      .onDrop(() => {
        this.targetState = '已放置! 拖拽成功'
        this.targetBgColor = '#C8E6C9'
        this.targetBorderColor = '#4CAF50'
        this.addLog('onDrop: 拖拽放置成功')
      })

      Divider()
        .width('90%')
        .margin({ top: 16, bottom: 8 })

      Text('事件日志')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .padding({ left: 20 })

      Scroll() {
        Text(this.eventLog)
          .fontSize(12)
          .fontColor('#333333')
          .width('100%')
          .padding(10)
      }
      .width('100%')
      .layoutWeight(1)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)
      .margin({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F1F3F5')
  }

  addLog(msg: string): void {
    let now = new Date()
    let time = now.getHours().toString().padStart(2, '0') + ':' +
      now.getMinutes().toString().padStart(2, '0') + ':' +
      now.getSeconds().toString().padStart(2, '0') + '.' +
      now.getMilliseconds().toString().padStart(3, '0')
    this.eventLog = '[' + time + '] ' + msg + '\n' + this.eventLog
    if (this.eventLog.length > 1000) {
      this.eventLog = this.eventLog.substring(0, 1000)
    }
  }
}
