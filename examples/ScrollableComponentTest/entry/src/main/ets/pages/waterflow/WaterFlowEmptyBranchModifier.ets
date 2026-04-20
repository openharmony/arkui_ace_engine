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
import { WaterFlowModifier } from '@ohos.arkui.modifier';

class CustomMyModifier implements AttributeModifier<WaterFlowModifier> {
  public enable: boolean | undefined = true

  applyNormalAttribute(instance: WaterFlowModifier): void {
    instance
      .supportEmptyBranchInLazyLoading(this.enable)
  }
}

@Entry
@Component
struct GridItemExample7 {
  private arr: MyDataSource<number> = new MyDataSource<number>()
  @State modifier: CustomMyModifier = new CustomMyModifier()
  scroller: Scroller = new Scroller()
  @State temp: boolean = true
  @State cGap: boolean = true
  @State rGap: boolean = true

  build() {
    Column() {
      Row(undefined) {
        Button('Template').onClick((event: ClickEvent) => {
          this.temp = !this.temp
        })
        Button('columnsGap').onClick((event: ClickEvent) => {
          this.cGap = !this.cGap
        })
        Button('rowsGap').onClick((event: ClickEvent) => {
          this.rGap = !this.rGap
        })
      }

      Row(undefined) {
        Button('true').onClick(() => {
          this.modifier.enable = true
        })
        Button('false').onClick(() => {
          this.modifier.enable = false
        })
        Button('undefined').onClick(() => {
          this.modifier.enable = undefined
        })
      }

      Row(undefined) {
        Button('isAtEnd').onClick(() => {
          this.scroller.isAtEnd()
          console.info(this.scroller.isAtEnd() + '')
        })
        Button('dataReload').onClick((event: ClickEvent) => {
          this.arr.dataReload()
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

      WaterFlow({ scroller: this.scroller } as WaterFlowOptions) {
        LazyForEach(this.arr, (item: number, index: number) => {
          if (index == 5) {

          } else {
            FlowItem() {
              Text('' + index)
                .fontSize(16)
                .height(60)
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
      .cachedCount(3, true)
      .clip(true)
      .edgeEffect(EdgeEffect.Spring)
      .attributeModifier(this.modifier as AttributeModifier<WaterFlowAttribute>)
      .columnsGap(this.cGap ? 10 : -1)
      .rowsGap(this.rGap ? 10 : -1)
      .onScrollIndex((first: number, last: number) => {
        console.info('first：' + first + ' last：' + last)
      })
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }

  aboutToAppear(): void {
    for (let i = 0; i < 30; i++) {
      this.arr.pushData(i);
    }
  }
}