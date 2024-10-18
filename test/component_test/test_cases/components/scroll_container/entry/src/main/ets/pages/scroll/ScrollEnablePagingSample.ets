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
import scrollEnablePagingTest from '../MyTest/ScrollEnablePagingTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ScrollEnablePagingSample {
  @State scrollEnablePaging: boolean = true
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    loadComponentTestEntry(scrollEnablePagingTest)
  }

  build() {
    Column() {
      Scroll(this.scroller) {
        Column() {
          Text('ScrollEnablePaging1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollEnablePaging2')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollEnablePaging3')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .enablePaging(this.scrollEnablePaging)
      .id('scrollEnablePaging1')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('45%')
      .backgroundColor(0xDCDCDC)

      Button('ScrollEnablePaging').onClick(() => {
        this.scrollEnablePaging = !this.scrollEnablePaging
      })

      Scroll(this.scroller) {
        Column() {
          Text('ScrollEnablePaging1')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollEnablePaging2')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
          Text('ScrollEnablePaging3')
            .width('90%')
            .height(150)
            .margin({ top: 10 })
        }.width('100%')
      }
      .enablePaging(false)
      .scrollSnap({ snapAlign: ScrollSnapAlign.CENTER })
      .id('scrollEnablePaging2')
      .margin({ top: 20, left: 20 })
      .width('100%')
      .height('45%')
      .backgroundColor(0xDCDCDC)
    }
  }
}