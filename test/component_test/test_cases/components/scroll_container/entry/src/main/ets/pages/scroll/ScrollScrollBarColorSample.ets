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
import scrollScrollBarColorTest from '../MyTest/ScrollScrollBarColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ScrollScrollBarColorSample {
  @State scrollScrollBarColor: number | string = 0x000000
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    loadComponentTestEntry(scrollScrollBarColorTest)
  }

  build() {
    Column() {
      Scroll(this.scroller) {
        Column() {
          Text('ScrollScrollBarColor1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBarColor2')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBarColor3')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .scrollBar(BarState.On)
      .scrollBarColor(Color.Blue)
      .id('scrollScrollBarColor1')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('30%')
      .backgroundColor(0xDCDCDC)

      Scroll(this.scroller) {
        Column() {
          Text('ScrollScrollBarColor1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBarColor2')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollScrollBarColor3')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .scrollBar(BarState.On)
      .scrollBarColor(this.scrollScrollBarColor)
      .id('scrollScrollBarColor2')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('30%')
      .backgroundColor(0xDCDCDC)

      Button('ScrollScrollBarColor').onClick(() => {
        this.scrollScrollBarColor = 'rgb(255, 100, 255)'
      })
    }
  }
}