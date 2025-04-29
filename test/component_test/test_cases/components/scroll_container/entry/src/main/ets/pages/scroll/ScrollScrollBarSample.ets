/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// 测试代码路径
import scrollScrollBarTest from '../MyTest/ScrollScrollBarTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ScrollScrollBarSample {
  @State scrollScrollBar: BarState = BarState.On
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    loadComponentTestEntry(scrollScrollBarTest)
  }

  build() {
    Column() {
      Scroll(this.scroller) {
        Column() {
          Text('ScrollScrollBar1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBar2')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBar3')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .scrollBar(BarState.Off)
      .id('scrollScrollBar1')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('30%')
      .backgroundColor(0xDCDCDC)

      Scroll(this.scroller) {
        Column() {
          Text('ScrollScrollBar1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBar2')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBar3')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .scrollBar(this.scrollScrollBar)
      .id('scrollScrollBar2')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('30%')
      .backgroundColor(0xDCDCDC)

      Button('ScrollScrollBar').onClick(() => {
        this.scrollScrollBar = BarState.Auto
      })

      Scroll(this.scroller) {
        Column() {
          Text('ScrollScrollBar1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .scrollBar(BarState.On)
      .id('scrollScrollBar3')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('20%')
      .backgroundColor(0xDCDCDC)
    }
  }
}