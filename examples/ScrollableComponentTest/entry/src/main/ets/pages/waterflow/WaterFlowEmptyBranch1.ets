/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { MyDataSource } from './BasicDataSource'

@Entry
@Component
struct GridItemExample {
  private arr: MyDataSource<number> = new MyDataSource<number>()
  @State enable: boolean | undefined = true
  scroller: Scroller = new Scroller()
  @State temp: boolean = true
  @State cGap: boolean = true
  @State rGap: boolean = true
  @State clips: boolean = true
  @State iShow: boolean = true
  @State isAtEnd: boolean = true
  @State dexNum: number = 0
  @State dateInfo: number[] = [0, 5, 29, -1, 18]

  build() {
    Column() {
      Row(undefined) {
        Button('index:' + `${this.dateInfo[this.dexNum%5]}`).onClick((p1: ClickEvent) => {
          this.dexNum++
        })
      }

      Row(undefined) {
        Button('Template').onClick((p1: ClickEvent) => {
          this.temp = !this.temp
        })
        Button('columnsGap').onClick((p1: ClickEvent) => {
          this.cGap = !this.cGap
        })
        Button('rowsGap').onClick((p1: ClickEvent) => {
          this.rGap = !this.rGap
        })
      }

      Row(undefined) {
        Button('true').onClick(() => {
          this.enable = true
        })
        Button('false').onClick(() => {
          this.enable = false
        })
        Button('undefined').onClick(() => {
          this.enable = undefined
        })
      }

      Row(undefined) {
        Button('isAtEnd' + this.isAtEnd).onClick(() => {
          this.isAtEnd = this.scroller.isAtEnd()
          console.info(this.scroller.isAtEnd() + '')
        })
        Button('pushData').onClick((event: ClickEvent) => {
          this.arr.pushData(this.arr.totalCount() + 1)
        })
      }

      Row(undefined) {
        Button('delete 5').onClick((event: ClickEvent) => {
          this.arr.deleteIndex(5)
        })
        Button('deleteData').onClick((event: ClickEvent) => {
          this.arr.deleteData(this.arr.totalCount())
        })
        Button('ToIndex5').onClick((event: ClickEvent) => {
          this.scroller.scrollToIndex(5)
        })
      }

      Row(undefined) {
        Button('clip:' + this.clips).onClick((p1: ClickEvent) => {
          this.clips = !this.clips
        })
        Button('show:' + this.iShow).onClick((p1: ClickEvent) => {
          this.iShow = !this.iShow
        })
      }

      WaterFlow({ scroller: this.scroller } as WaterFlowOptions) {
        LazyForEach(this.arr, (item: number, index: number) => {
          if (index == this.dateInfo[this.dexNum%5]) {

          } else {
            FlowItem() {
              Text('' + item)
                .height(60)
                .fontSize(16)
                .focusable(true)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
            }
          }
        }, (item: number) => item.toString())
      }
      .width('90%')
      .height('50%')
      .columnsTemplate(this.temp ? '1fr' : '1fr 1fr 1fr')
      .scrollBar(BarState.On)
      .borderWidth(1)
      .cachedCount(3, this.iShow)
      .clip(this.clips)
      .edgeEffect(EdgeEffect.Spring)
      .columnsGap(this.cGap ? 10 : -1)
      .rowsGap(this.rGap ? 10 : -1)
      .supportEmptyBranchInLazyLoading(this.enable)
      .onScrollIndex((first: number, last: number) => {
        console.info('first：' + first + ' last：' + last)
      })
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }

  aboutToAppear(): void {
    this.arr.clear();
    for (let i = 0; i < 30; i++) {
      this.arr.pushData(i);
    }
  }
}