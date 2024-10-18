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
import scrollScrollBarWidthTest from '../MyTest/ScrollScrollBarWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ScrollScrollBarWidthSample {
  @State scrollScrollBarWidth: number | string = 20
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    loadComponentTestEntry(scrollScrollBarWidthTest)
  }

  build() {
    Column() {
      Scroll(this.scroller) {
        Column() {
          Text('ScrollScrollBarWidth1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBarWidth2')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBarWidth3')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .scrollBarWidth(this.scrollScrollBarWidth)
      .id('scrollScrollBarWidth1')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('40%')
      .backgroundColor(0xDCDCDC)

      Button('ScrollScrollBarWidth').onClick(() => {
        this.scrollScrollBarWidth = '50vp'
      })

      Scroll(this.scroller) {
        Column() {
          Text('ScrollScrollBarWidth1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBarWidth2')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBarWidth3')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .scrollBarWidth(1000)
      .id('scrollScrollBarWidth2')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('40%')
      .backgroundColor(0xDCDCDC)
    }
  }
}