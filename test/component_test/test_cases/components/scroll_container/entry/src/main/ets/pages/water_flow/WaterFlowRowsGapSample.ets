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
import { WaterFlowDataSource } from '../MyTest/WaterFlowDataSource'
import waterFlowRowsGapTest from '../MyTest/WaterFlowRowsGapTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct WaterFlowRowsGapSample {
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F]
  @State rowsGapType: Length = 10
  dataSource: WaterFlowDataSource = new WaterFlowDataSource()

  aboutToAppear(): void {
    loadComponentTestEntry(waterFlowRowsGapTest);
  }

  build() {
    Column() {
      WaterFlow() {
        FlowItem() {
          Text("1").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[0])

        FlowItem() {
          Text("2").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[1])
      }
      .rowsGap($r('app.string.length'))
      .rowsTemplate('1fr 1fr 2fr')
      .width('100%')
      .height('100')
      .margin({ bottom: 20 })
      .id('waterFlowRowsGap1')

      WaterFlow() {
        FlowItem() {
          Text("1").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[0])

        FlowItem() {
          Text("2").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[1])
      }
      .rowsGap(this.rowsGapType)
      .rowsTemplate('1fr 1fr 2fr')
      .width('100%')
      .height('100')
      .margin({ bottom: 10 })
      .id('waterFlowRowsGap2')

      Button('WaterFlowRowsGap')
        .onClick(() => {
          this.rowsGapType = '80px'
        })
    }
  }
}