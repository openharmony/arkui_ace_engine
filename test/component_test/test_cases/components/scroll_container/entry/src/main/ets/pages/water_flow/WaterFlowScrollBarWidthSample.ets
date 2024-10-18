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
import waterFlowScrollBarWidthTest from '../MyTest/WaterFlowScrollBarWidthTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct WaterFlowScrollBarWidthSample {
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F]
  @State scrollBarWidthType: string | number = 20
  dataSource: WaterFlowDataSource = new WaterFlowDataSource()

  aboutToAppear(): void {
    loadComponentTestEntry(waterFlowScrollBarWidthTest);
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

        FlowItem() {
          Text("3").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[2])
      }
      .scrollBarWidth(this.scrollBarWidthType)
      .scrollBar(BarState.On)
      .backgroundColor(0xFAEEE0)
      .width('100%')
      .height('100')
      .id('waterFlowScrollBarWidth1')

      WaterFlow() {
        FlowItem() {
          Text("1").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[0])

        FlowItem() {
          Text("2").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[1])

        FlowItem() {
          Text("3").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[2])
      }
      .scrollBarWidth(10000000)
      .scrollBar(BarState.On)
      .backgroundColor(0xFAEEE0)
      .width('100%')
      .height('100')
      .id('waterFlowScrollBarWidth2')

      Button('WaterFlowScrollBarWidth')
        .onClick(() => {
          this.scrollBarWidthType = '30vp'
        })
    }
  }
}