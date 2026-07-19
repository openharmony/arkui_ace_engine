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

/**
 * 测试Image组件事件回调
 * 验证onComplete/onError/onFinish/onAppear/onDisappear回调
 */

@Entry
@Component
struct ImageEventCallbackTestCase029 {
  @State completeCount: number = 0
  @State errorCount: number = 0
  @State finishCount: number = 0
  @State appearCount: number = 0
  @State disappearCount: number = 0
  @State lastEvent: string = 'None'
  @State currentSource: ResourceStr = $r('app.media.startIcon')

  build() {
    Column() {
      Text('Image事件回调测试')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 16 })

      Row() {
        Image(this.currentSource)
          .width(120)
          .height(120)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .onComplete(() => {
            this.completeCount++
            this.lastEvent = 'onComplete'
          })
          .onError((err: ImageError) => {
            this.errorCount++
            this.lastEvent = 'onError: ' + (err.message ?? '')
          })
          .onFinish(() => {
            this.finishCount++
            this.lastEvent = 'onFinish'
          })
          .onAppear(() => {
            this.appearCount++
            this.lastEvent = 'onAppear'
          })
          .onDisAppear(() => {
            this.disappearCount++
            this.lastEvent = 'onDisAppear'
          })
      }
      .margin({ bottom: 16 })

      Text(`最近事件: ${this.lastEvent}`)
        .fontSize(14)
        .fontColor(Color.Orange)
        .margin({ bottom: 8 })

      Grid() {
        GridItem() {
          Column() {
            Text('onComplete')
              .fontSize(12)
              .fontColor(Color.Green)
            Text(`${this.completeCount}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .padding(12)
          .backgroundColor('#E8F5E8')
          .borderRadius(6)
        }

        GridItem() {
          Column() {
            Text('onError')
              .fontSize(12)
              .fontColor(Color.Red)
            Text(`${this.errorCount}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .padding(12)
          .backgroundColor('#FFEBEE')
          .borderRadius(6)
        }

        GridItem() {
          Column() {
            Text('onFinish')
              .fontSize(12)
              .fontColor(Color.Blue)
            Text(`${this.finishCount}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .padding(12)
          .backgroundColor('#E3F2FD')
          .borderRadius(6)
        }

        GridItem() {
          Column() {
            Text('onAppear')
              .fontSize(12)
              .fontColor(Color.Orange)
            Text(`${this.appearCount}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .padding(12)
          .backgroundColor('#FFF3E0')
          .borderRadius(6)
        }

        GridItem() {
          Column() {
            Text('onDisAppear')
              .fontSize(12)
              .fontColor(Color.Gray)
            Text(`${this.disappearCount}`)
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
          }
          .padding(12)
          .backgroundColor('#F5F5F5')
          .borderRadius(6)
        }
      }
      .columnsTemplate('repeat(5, 1fr)')
      .columnsGap(8)
      .margin({ bottom: 16 })

      Row({ space: 12 }) {
        Button('正常图片')
          .onClick(() => {
            this.currentSource = $r('app.media.startIcon')
          })
        Button('错误图片')
          .onClick(() => {
            this.currentSource = 'invalid://nonexistent.jpg'
          })
        Button('重置计数')
          .onClick(() => {
            this.completeCount = 0
            this.errorCount = 0
            this.finishCount = 0
            this.appearCount = 0
            this.disappearCount = 0
            this.lastEvent = 'None'
          })
          .backgroundColor('#FF6666')
      }
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
