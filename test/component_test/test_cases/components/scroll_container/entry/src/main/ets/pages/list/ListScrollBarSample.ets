/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import listScrollBarTest from '../MyTest/ListScrollBarTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListScrollBarSample {
  @State arr: string[] = ['0', '1', '2', '3', '4', '5']
  @State scrollBar: BarState = BarState.Off

  aboutToAppear(): void {
    loadComponentTestEntry(listScrollBarTest)
  }

  build() {
    Scroll() {
      Column() {
        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr, (item: string) => {
            ListItem() {
              Text('' + item)
                .width('100%')
                .height(70)
                .backgroundColor(0xFFFFFF)
            }
            .border({ width: 2, color: Color.Green })
          })
        }
        .height("40%")
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .scrollBar(this.scrollBar)
        .id('listScrollBar1')

        Button('ListScrollBar')
          .margin('5vp')
          .onClick(() => {
            this.scrollBar = BarState.Auto
          })

        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr, (item: string) => {
            ListItem() {
              Text('' + item)
                .width('100%')
                .height(70)
                .backgroundColor(0xFFFFFF)
            }
            .border({ width: 2, color: Color.Green })
          })
        }
        .height("40%")
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .scrollBar(BarState.On)
        .id('listScrollBar2')

        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr, (item: string) => {
            ListItem() {
              Text('' + item)
                .width('100%')
                .height(70)
                .backgroundColor(0xFFFFFF)
            }
            .border({ width: 2, color: Color.Green })
          })
        }
        .height("40%")
        .width("100%")
        .border({ width: 3, color: Color.Red })
      }.backgroundColor(0xDCDCDC)
    }
    .scrollBar(BarState.On)
    .id('listScrollBar3')
  }
}