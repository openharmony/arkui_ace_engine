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
function springDragPreview() {
  Column() {
    Text('拖拽中')
      .fontSize(16)
      .fontColor(Color.White)
      .fontWeight(FontWeight.Bold)
  }
  .width(120)
  .height(60)
  .backgroundColor('#FF9800')
  .borderRadius(8)
  .justifyContent(FlexAlign.Center)
  .alignItems(HorizontalAlign.Center)
}

@Builder
function listItemBuilder(text: string) {
  Text(text)
    .fontSize(16)
    .fontColor(Color.White)
    .fontWeight(FontWeight.Medium)
}

@Entry
@Component
struct DragSpringLoading {
  @State eventLog: string = ''
  @State springLoadingState: string = '等待拖拽...'
  @State springActive: boolean = false

  private stateNames: string[] = ['BEGIN', 'UPDATE', 'END', 'CANCEL']

  build() {
    Column() {
      Text('DragSpringLoading - 弹性加载')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .textAlign(TextAlign.Start)
        .padding({ left: 20, top: 16, bottom: 8 })

      Text('下方列表项可拖拽到弹性加载区域触发回调')
        .fontSize(13)
        .fontColor('#666666')
        .width('100%')
        .padding({ left: 20, bottom: 8 })

      Text('弹性加载状态: ' + this.springLoadingState)
        .fontSize(14)
        .fontColor(this.springActive ? '#FF9800' : '#666666')
        .fontWeight(this.springActive ? FontWeight.Bold : FontWeight.Normal)
        .width('100%')
        .padding({ left: 20, top: 4, bottom: 4 })

      Scroll() {
        Column({ space: 8 }) {
          ForEach([1, 2, 3, 4, 5], (index: number) => {
            Column() {
              Text('列表项 ' + index + ' - 长按拖拽')
                .fontSize(16)
                .fontColor(Color.White)
                .fontWeight(FontWeight.Medium)
            }
            .width('85%')
            .height(60)
            .backgroundColor('#009688')
            .borderRadius(10)
            .justifyContent(FlexAlign.Center)
            .alignItems(HorizontalAlign.Center)
            .draggable(true)
            .onDragStart(() => {
              this.addLog('列表项' + index + ': onDragStart')
              return springDragPreview()
            })
          }, (index: number) => index.toString())
        }
        .width('100%')
        .alignItems(HorizontalAlign.Center)
        .margin({ top: 8 })
      }
      .width('100%')
      .layoutWeight(1)
      .onDragSpringLoading((context: SpringLoadingContext) => {
        let stateVal = context.state
        let stateNum: number = stateVal as number ?? 0
        let stateName = this.stateNames[stateNum] ?? 'UNKNOWN'
        this.springLoadingState = stateName
        this.springActive = (stateNum === 0 || stateNum === 1)
        this.addLog('onDragSpringLoading: ' + stateName)
      }, {
        stillTimeLimit: 500,
        updateInterval: 100,
        updateNotifyCount: 3
      })

      Divider()
        .width('90%')
        .margin({ top: 8, bottom: 8 })

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
      .height(150)
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
