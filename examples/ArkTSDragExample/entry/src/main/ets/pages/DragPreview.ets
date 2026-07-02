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
function customPreviewBuilder() {
  Column() {
    Row() {
      Text('★')
        .fontSize(24)
        .fontColor('#FFD700')
      Text('自定义')
        .fontSize(16)
        .fontColor(Color.White)
        .fontWeight(FontWeight.Bold)
        .margin({ left: 8 })
    }
    Text('拖拽预览')
      .fontSize(12)
      .fontColor('#FFFFFFCC')
      .margin({ top: 4 })
  }
  .width(140)
  .height(80)
  .backgroundColor('#7C4DFF')
  .borderRadius(12)
  .justifyContent(FlexAlign.Center)
  .alignItems(HorizontalAlign.Center)
  .shadow({ radius: 10, color: '#44000000', offsetX: 0, offsetY: 4 })
}

@Builder
function badgePreviewBuilder() {
  Column() {
    Text('带角标')
      .fontSize(16)
      .fontColor(Color.White)
      .fontWeight(FontWeight.Bold)
    Text('3个待处理')
      .fontSize(12)
      .fontColor('#FFFFFFCC')
      .margin({ top: 4 })
  }
  .width(130)
  .height(70)
  .backgroundColor('#E91E63')
  .borderRadius(12)
  .justifyContent(FlexAlign.Center)
  .alignItems(HorizontalAlign.Center)
}

@Entry
@Component
struct DragPreview {
  @State eventLog: string = ''

  build() {
    Column() {
      Text('DragPreview - 拖拽预览')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Start)
        .padding({ left: 20, top: 16, bottom: 16 })

      Text('默认预览 - 使用 onDragStart 返回 CustomBuilder')
        .fontSize(13)
        .fontColor('#666666')
        .width('100%')
        .padding({ left: 20 })

      Column() {
        Text('默认样式')
          .fontSize(16)
          .fontColor(Color.White)
          .fontWeight(FontWeight.Bold)
      }
      .width(140)
      .height(80)
      .backgroundColor('#0077FF')
      .borderRadius(12)
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)
      .margin({ top: 8 })
      .draggable(true)
      .onDragStart(() => {
        this.addLog('默认预览: onDragStart')
        return customPreviewBuilder()
      })

      Divider()
        .width('90%')
        .margin({ top: 16, bottom: 8 })

      Text('自定义 Preview - 使用 dragPreview 指定预览')
        .fontSize(13)
        .fontColor('#666666')
        .width('100%')
        .padding({ left: 20 })

      Column() {
        Text('dragPreview')
          .fontSize(16)
          .fontColor(Color.White)
          .fontWeight(FontWeight.Bold)
      }
      .width(140)
      .height(80)
      .backgroundColor('#7C4DFF')
      .borderRadius(12)
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)
      .margin({ top: 8 })
      .draggable(true)
      .dragPreview(customPreviewBuilder())
      .onDragStart(() => {
        this.addLog('自定义预览: onDragStart')
      })

      Divider()
        .width('90%')
        .margin({ top: 16, bottom: 8 })

      Text('带角标 - 使用 dragPreviewOptions 的 numberBadge')
        .fontSize(13)
        .fontColor('#666666')
        .width('100%')
        .padding({ left: 20 })

      Column() {
        Text('带角标')
          .fontSize(16)
          .fontColor(Color.White)
          .fontWeight(FontWeight.Bold)
      }
      .width(140)
      .height(80)
      .backgroundColor('#E91E63')
      .borderRadius(12)
      .justifyContent(FlexAlign.Center)
      .alignItems(HorizontalAlign.Center)
      .margin({ top: 8 })
      .draggable(true)
      .dragPreview(badgePreviewBuilder(), { onlyForLifting: false })
      .dragPreviewOptions({ numberBadge: 3 })
      .onDragStart(() => {
        this.addLog('带角标预览: onDragStart')
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
