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

import {
  DynamicLayout, DynamicLayoutAttribute, GridLayoutAlgorithm, LengthMetrics
} from '@kit.ArkUI'

@Entry
@ComponentV2
struct GridLayoutExample {
  @Local flag1: boolean = false
  @Local flag2: boolean = false
  @Local gridLayoutAlgorithm1: GridLayoutAlgorithm = new GridLayoutAlgorithm({
    columnsTemplate: '1fr 1fr 1fr',
    columnsGap: LengthMetrics.vp(10),
    rowsGap: LengthMetrics.vp(10)
  })
  @Local gridLayoutAlgorithm2: GridLayoutAlgorithm = new GridLayoutAlgorithm({
    columnsTemplate: '1fr 1fr 1fr',
    columnsGap: LengthMetrics.vp(10),
    rowsGap: LengthMetrics.vp(10)
  })
  @Local alignV1: Alignment = Alignment.TopStart
  @Local localAlign2: LocalizedAlignment = LocalizedAlignment.TOP_START
  @Local directionV1: Direction = Direction.Ltr
  @Local directionV2: Direction = Direction.Ltr

  build() {
    WaterFlow() {
      FlowItem() {
        DynamicLayout(this.gridLayoutAlgorithm1) {
          ForEach([1, 2, 3, 4, 5, 6], (item: number, index: number) => {
            Text('S' + item)
              .fontSize(20)
              .width(30)
              .height(50 + index * 10)
              .borderWidth(2)
          })
        }.width('100%')
        .align(this.alignV1)
        .direction(this.directionV1)
      }
      FlowItem() {
        Button('change gridLayoutAlgorithm1 rowsGap').onClick(() => {
          this.flag1 = !this.flag1
          if (this.flag1) {
            this.gridLayoutAlgorithm1.rowsGap = LengthMetrics.vp(30)
          } else {
            this.gridLayoutAlgorithm1.rowsGap = LengthMetrics.vp(10)
          }
        })
      }
      // align
      FlowItem() {
        Button('Alignment TopStart ltr').onClick(() => {
          this.alignV1 = Alignment.TopStart
          this.directionV1 = Direction.Ltr
        })
      }
      FlowItem() {
        Button('Alignment TopStart rtl').onClick(() => {
          this.alignV1 = Alignment.TopStart
          this.directionV1 = Direction.Rtl
        })
      }

      FlowItem() {
        DynamicLayout(this.gridLayoutAlgorithm2) {
          ForEach([1, 2, 3, 4, 5, 6], (item: number, index: number) => {
            Text('S' + item)
              .fontSize(20)
              .width(30)
              .height(50 + index * 10)
              .borderWidth(2)
          })
        }.width('100%')
        .align(this.localAlign2)
        .direction(this.directionV2)
      }
      FlowItem() {
        Button('change gridLayoutAlgorithm2 rowsGap').onClick(() => {
          this.flag2 = !this.flag2
          if (this.flag2) {
            this.gridLayoutAlgorithm2.rowsGap = LengthMetrics.vp(30)
          } else {
            this.gridLayoutAlgorithm2.rowsGap = LengthMetrics.vp(10)
          }
        })
      }
      // LocalizedAlignment
      FlowItem() {
        Button('LocalizedAlignment TopStart ltr').onClick(() => {
          this.localAlign2 = LocalizedAlignment.TOP_START
          this.directionV2 = Direction.Ltr
        })
      }
      FlowItem() {
        Button('LocalizedAlignment TopStart rtl').onClick(() => {
          this.localAlign2 = LocalizedAlignment.TOP_START
          this.directionV2 = Direction.Rtl
        })
      }
    }
  }
}