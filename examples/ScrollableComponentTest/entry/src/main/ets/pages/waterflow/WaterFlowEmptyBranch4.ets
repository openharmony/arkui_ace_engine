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
  @State dir: FlexDirection = FlexDirection.Column

  build() {
    Column() {
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
        Button('Column').onClick((event: ClickEvent) => {
          this.dir = FlexDirection.Column
        })
        Button('Row').onClick((event: ClickEvent) => {
          this.dir = FlexDirection.Row
        })
        Button('ColumnRe').onClick((event: ClickEvent) => {
          this.dir = FlexDirection.ColumnReverse
        })
        Button('RowRe').onClick((event: ClickEvent) => {
          this.dir = FlexDirection.RowReverse
        })
      }

      WaterFlow({} as WaterFlowOptions) {
        LazyForEach(this.arr, (item: number, index: number) => {
          if (index == 5) {

          } else {
            FlowItem() {
              Text('' + item)
                .width('100%')
                .height(100)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor(0xFFFFFF)
            }
            .width(100)
            .height(100)
          }
        }, (item: number) => item.toString())
      }
      .width('90%')
      .height('60%')
      .scrollBar(BarState.On)
      .borderWidth(2)
      .layoutDirection(this.dir)
      .edgeEffect(EdgeEffect.Spring)
      .columnsGap(10)
      .rowsGap(10)
      .supportEmptyBranchInLazyLoading(this.enable)
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }

  aboutToAppear(): void {
    this.arr.clear();
    for (let i = 0; i < 100; i++) {
      this.arr.pushData(i);
    }
  }
}