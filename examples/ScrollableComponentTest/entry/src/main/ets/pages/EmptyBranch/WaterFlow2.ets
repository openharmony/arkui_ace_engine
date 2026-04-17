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
  @State temp: boolean = true
  @State cGap: boolean = true
  @State rGap: boolean = true

  build() {
    Column() {
      Row(undefined) {
        Button('Template').onClick((event: ClickEvent) => {
          this.temp = !this.temp
        })
        Button('rowsGap').onClick((event: ClickEvent) => {
          this.rGap = !this.rGap
        })
      }

      Row(undefined) {
        Button("true").onClick(() => {
          this.enable = true
        })
        Button("false").onClick(() => {
          this.enable = false
        })
        Button("undefined").onClick(() => {
          this.enable = undefined
        })
      }

      WaterFlow({} as WaterFlowOptions) {
        LazyForEach(this.arr, (item: number, index: number) => {
          if (index == 20 || index == 0) {

          } else {
            FlowItem() {
              Text('' + item)
                .width(100)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor(0xFFFFFF)
            }
          }
        }, (item: number) => item.toString())
      }
      .width('95%')
      .height(300)
      .borderWidth(1)
      .layoutDirection(FlexDirection.Row)
      .rowsTemplate(this.temp ? '1fr 1fr' : '1fr 1fr 1fr')
      .scrollBar(BarState.On)
      .edgeEffect(EdgeEffect.Spring)
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