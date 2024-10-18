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
import listNestedScrollTest from '../MyTest/ListNestedScrollTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListNestedScrollSample {
  @State arr: number[] = []
  @State nestedScroll: NestedScrollOptions = {
    scrollForward: NestedScrollMode.SELF_ONLY,
    scrollBackward: NestedScrollMode.SELF_ONLY
  }
  @State nestedScroll1: NestedScrollOptions = {
    scrollForward: NestedScrollMode.SELF_FIRST,
    scrollBackward: NestedScrollMode.SELF_FIRST
  }

  aboutToAppear(): void {
    loadComponentTestEntry(listNestedScrollTest)
  }

  @Styles
  listCard() {
  }

  build() {
    Scroll() {
      Column() {
        Text("Scroll Area")
          .width("100%")
          .height("40%")
          .backgroundColor('#0080DC')
        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            List({ space: 10 }) {
              ForEach(this.arr, (item: number) => {
                ListItem() {
                  Text("item" + item)
                }.listCard()
              }, (item: string) => item)
            }
            .border({ width: 3, color: Color.Red })
            .edgeEffect(EdgeEffect.Spring)
            .nestedScroll(this.nestedScroll)
            .id('listNestedScroll1')
          }.tabBar("Tab1")

          TabContent() {
          }.tabBar("Tab2")
        }

        Button('ListNestedScroll1')
          .margin('5vp')
          .onClick(() => {
            this.nestedScroll = {
              scrollForward: NestedScrollMode.PARENT_FIRST,
              scrollBackward: NestedScrollMode.PARENT_FIRST
            };
          })

        Text("Scroll Area")
          .width("100%")
          .height("40%")
          .backgroundColor('#0080DC')
        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            List({ space: 10 }) {
              ForEach(this.arr, (item: number) => {
                ListItem() {
                  Text("item" + item)
                }.listCard()
              }, (item: string) => item)
            }
            .border({ width: 3, color: Color.Red })
            .edgeEffect(EdgeEffect.Spring)
            .nestedScroll(this.nestedScroll1)
            .id('listNestedScroll2')
          }.tabBar("Tab1")

          TabContent() {
          }.tabBar("Tab2")
        }

        Button('ListNestedScroll2')
          .margin('5vp')
          .onClick(() => {
            this.nestedScroll1 = {
              scrollForward: NestedScrollMode.PARALLEL,
              scrollBackward: NestedScrollMode.PARALLEL
            };
          })
      }
    }
  }
}