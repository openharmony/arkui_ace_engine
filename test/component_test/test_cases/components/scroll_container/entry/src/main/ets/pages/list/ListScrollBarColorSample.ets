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
import listScrollBarColorTest from '../MyTest/ListScrollBarColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListScrollBarColorSample {
  private arr: number[] = [0, 1, 2, 3,]
  @State scrollBarColor: string | number | Color = Color.Blue

  aboutToAppear(): void {
    loadComponentTestEntry(listScrollBarColorTest)
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
        .height('44%')
        .width("100%")
        .border({ width: 3, color: Color.Red })
        .scrollBarColor(this.scrollBarColor)
        .scrollBar(BarState.On)
        .id('listScrollBarColor1')

        Button('ListScrollBarColor')
          .margin('5vp')
          .onClick(() => {
            this.scrollBarColor = 0xffffff
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
        .height('44%')
        .width("100%")
        .scrollBar(BarState.On)
        .border({ width: 3, color: Color.Red })
        .scrollBarColor('#FFFF64FF')
        .id('listScrollBarColor2')
      }
      .backgroundColor(0xDCDCDC)

    }
  }
}