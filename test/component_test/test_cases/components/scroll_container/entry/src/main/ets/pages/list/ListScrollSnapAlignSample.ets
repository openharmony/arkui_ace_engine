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
import listScrollSnapAlignTest from '../MyTest/ListScrollSnapAlignTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListScrollSnapAlignSample {
  private arr: number[] = []
  private scrollerForList: Scroller = new Scroller()
  @State scrollSnapAlign: ScrollSnapAlign = ScrollSnapAlign.CENTER
  @State scrollSnapAlign1: ScrollSnapAlign = ScrollSnapAlign.NONE

  aboutToAppear(): void {
    loadComponentTestEntry(listScrollSnapAlignTest)
  }

  build() {
    Scroll() {
      Column() {
        List({ space: 20, initialIndex: 3, scroller: this.scrollerForList }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('100%').height(100).fontSize(16)
                .textAlign(TextAlign.Center)
            }
            .border({ width: 2, color: Color.Green })
            .borderRadius(10)
            .backgroundColor(0xFFFFFF)
            .width('60%')
            .height('80%')
          })
        }
        .listDirection(Axis.Horizontal)
        .width('100%')
        .height('30%')
        .border({ width: 3, color: Color.Red })
        .scrollSnapAlign(this.scrollSnapAlign)
        .id('listScrollSnapAlign1')

        Button('ListScrollSnapAlign1')
          .margin('5vp')
          .onClick(() => {
            this.scrollSnapAlign = ScrollSnapAlign.END;
          })

        List({ space: 20, initialIndex: 3, scroller: this.scrollerForList }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('100%').height(100).fontSize(16)
                .textAlign(TextAlign.Center)
            }
            .border({ width: 2, color: Color.Green })
            .borderRadius(10)
            .backgroundColor(0xFFFFFF)
            .width('60%')
            .height('80%')
          })
        }
        .listDirection(Axis.Horizontal)
        .width('100%')
        .height('30%')
        .border({ width: 3, color: Color.Red })
        .scrollSnapAlign(this.scrollSnapAlign1)
        .id('listScrollSnapAlign2')

        Button('ListScrollSnapAlign2')
          .margin('5vp')
          .onClick(() => {
            this.scrollSnapAlign1 = ScrollSnapAlign.CENTER
          })

        List({ space: 20, initialIndex: 3, scroller: this.scrollerForList }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('100%').height(100).fontSize(16)
                .textAlign(TextAlign.Center)
            }
            .border({ width: 2, color: Color.Green })
            .borderRadius(10)
            .backgroundColor(0xFFFFFF)
            .width('60%')
            .height('150')
          })
        }
        .listDirection(Axis.Horizontal)
        .width('100%')
        .height('30%')
        .border({ width: 3, color: Color.Red })
        .scrollSnapAlign(ScrollSnapAlign.CENTER)
        .id('listScrollSnapAlign3')
      }
      .backgroundColor(0xDCDCDC)
    }
  }
}