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
import scrollNestedScrollTest from '../MyTest/ScrollNestedScrollTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ScrollNestedScrollSample {
  @State scrollNestedScroll: NestedScrollMode = NestedScrollMode.SELF_FIRST
  @State
  arr: number[] = []
  index: number = 0
  @State scroll: NestedScrollMode[] = [
    NestedScrollMode.PARALLEL, NestedScrollMode.PARENT_FIRST,
    NestedScrollMode.SELF_FIRST, NestedScrollMode.SELF_ONLY]
  @State scrollForward: NestedScrollMode = this.scroll[this.index]
  @State scrollBackward: NestedScrollMode = this.scroll[this.index+1]

  @Styles
  listCard() {
    .height(72)
  }

  onPageShow(): void {
    loadComponentTestEntry(scrollNestedScrollTest)
  }

  build() {
    Column() {
      Scroll() {
        Column() {
          Text("Scroll Area")
            .width("100%")
            .height("30%")
            .backgroundColor('#0080DC')
          Tabs({ barPosition: BarPosition.Start }) {
            TabContent() {
              List({ space: 10 }) {
                ForEach(this.arr, (item: number) => {
                  ListItem() {
                    Text("ScrollNestedScroll" + item)
                  }.listCard()
                }, (item: string) => item)
              }.width("100%")
              .nestedScroll({
                scrollForward: this.scrollForward,
                scrollBackward: this.scrollBackward
              })
              .id('scrollNestedScroll')
            }.tabBar("Tab1")
          }
        }
      }
      .width('100%')
      .height('25%')

      Button('ScrollNestedScroll')
        .onClick(() => {
          this.index++
          this.scrollForward = this.scroll[this.index % 4]
          this.scrollBackward = this.scroll[(this.index + 1) % 4]
        })
    }
  }

  aboutToAppear() {
    for (let i = 0; i < 20; i++) {
      this.arr.push(i)
    }
  }
}