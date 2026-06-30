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
function dragPreviewBuilder() {
  Column() {
    Text('拖拽预览')
      .fontSize(16)
      .fontColor(Color.White)
      .fontWeight(FontWeight.Bold)
  }
  .width(120)
  .height(80)
  .backgroundColor('#0077FF')
  .borderRadius(8)
  .justifyContent(FlexAlign.Center)
  .alignItems(HorizontalAlign.Center)
  .shadow({ radius: 8, color: '#33000000', offsetX: 2, offsetY: 4 })
}

@Entry
@Component
struct BasicDrag {
  @State draggableEnabled: boolean = true
  @State eventLog: string = ''
  @State preDragStatusText: string = '等待拖拽...'

  private preDragStatusMap: string[] = [
    'ACTION_DETECTING_STATUS',
    'READY_TO_TRIGGER_DRAG_ACTION',
    'PREVIEW_LIFT_STARTED',
    'PREVIEW_LIFT_FINISHED',
    'PREVIEW_LANDING_STARTED',
    'PREVIEW_LANDING_FINISHED',
    'ACTION_CANCELED_BEFORE_DRAG',
    'PREPARING_FOR_DRAG_DETECTION'
  ]

  build() {
    Column() {
      Text('BasicDrag - 基本拖拽')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Start)
        .padding({ left: 20, top: 16, bottom: 8 })

      Row() {
        Text('启用拖拽')
          .fontSize(16)
        Toggle({ type: ToggleType.Switch, isOn: this.draggableEnabled })
          .onChange((val: boolean) => {
            this.draggableEnabled = val
            this.addLog('draggable: ' + val)
          })
      }
      .width('100%')
      .padding({ left: 20, right: 20, top: 8, bottom: 8 })
      .justifyContent(FlexAlign.SpaceBetween)

      Text('PreDrag状态: ' + this.preDragStatusText)
        .fontSize(14)
        .fontColor('#666666')
        .width('100%')
        .padding({ left: 20, top: 4, bottom: 4 })

      Column() {
        Text('长按拖拽我')
          .fontSize(18)
          .fontColor(Color.White)
          .fontWeight(FontWeight.Bold)
        Text('↓ 拖到下方区域')
          .fontSize(12)
          .fontColor('#FFFFFFCC')
          .margin({ top: 8 })
      }
      .width(160)
      .height(160)
      .backgroundColor(this.draggableEnabled ? '#0077FF' : '#999999')
      .borderRadius(16)
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)
      .margin({ top: 20 })
      .draggable(this.draggableEnabled)
      .onPreDrag((status: PreDragStatus) => {
        let statusStr = this.preDragStatusMap[status as number] ?? 'UNKNOWN'
        this.preDragStatusText = statusStr
        this.addLog('onPreDrag: ' + statusStr)
      })
      .onDragStart(() => {
        this.addLog('onDragStart: 拖拽开始')
        return dragPreviewBuilder()
      })
      .onDragEnd((event: DragEvent, extraParams?: string) => {
        let result = event.getResult()
        this.addLog('onDragEnd: result=' + result)
        this.preDragStatusText = '等待拖拽...'
      })

      Divider()
        .width('90%')
        .margin({ top: 20, bottom: 8 })

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
