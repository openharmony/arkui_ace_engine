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
// 测试代码路径
import gridNestedScrollTest from '../MyTest/GridNestedScrollTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GridNestedScrollSample {
  scroll: NestedScrollMode[] = [
    NestedScrollMode.SELF_ONLY, NestedScrollMode.SELF_FIRST,
    NestedScrollMode.PARENT_FIRST, NestedScrollMode.PARALLEL]
  arr: number[] = []
  index: number = 0
  @State scrollForward: NestedScrollMode = this.scroll[this.index]
  @State scrollBackward: NestedScrollMode = this.scroll[this.index+1]

  @Styles
  gridCard() {
    .backgroundColor(Color.White)
    .height(72)
    .width("100%")
    .borderRadius(12)
  }

  aboutToAppear(): void {
    loadComponentTestEntry(gridNestedScrollTest)
    for (let i = 0; i < 20; i++) {
      this.arr.push(i)
    }
  }

  scroller: Scroller = new Scroller()

  build() {
    Scroll() {
      Column() {
        Text("Scroll Area")
          .width("100%")
          .height("40%")
          .backgroundColor('#0080DC')
        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            Grid(this.scroller) {
              ForEach(this.arr, (item: number) => {
                GridItem() {
                  Text('gridNestedScrollTest' + item)
                }.gridCard()
              }, (item: string) => item)
            }.width("100%")
            .id('gridNestedScroll')
            .columnsTemplate('1fr')
            .nestedScroll({
              scrollForward: this.scrollForward,
              scrollBackward: this.scrollBackward
            })
          }.tabBar("Tab")
        }
        .vertical(false)
        .height("80%")

        Button('GridNestedScroll')
          .onClick(() => {
            this.index++
            this.scrollForward = this.scroll[this.index % 4]
            this.scrollBackward = this.scroll[(this.index + 1) % 4]
          })
      }.width("100%")
    }
    .width('100%')
    .height('100%')
  }
}
