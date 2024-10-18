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
import waterFlowItemConstraintSizeTest from '../MyTest/WaterFlowItemConstraintSizeTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct WaterFlowItemConstraintSizeSample {
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F]
  @State itemConstraintSizeType: ConstraintSizeOptions = {
    minWidth: 0,
    maxWidth: 600,
    minHeight: 0,
    maxHeight: 600
  }
  dataSource: WaterFlowDataSource = new WaterFlowDataSource()

  aboutToAppear(): void {
    loadComponentTestEntry(waterFlowItemConstraintSizeTest);
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
      .itemConstraintSize({
        minWidth: $r('app.string.length'),
        maxWidth: $r('app.string.length'),
        minHeight: $r('app.string.length'),
        maxHeight: $r('app.string.length')
      })
      .width('100%')
      .height('100')
      .margin({ bottom: "20" })
      .id('waterFlowItemConstraintSize1')

      WaterFlow() {
        FlowItem() {
          Text("1").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[0])

        FlowItem() {
          Text("2").fontSize(12)
        }.width('100%').height('40').backgroundColor(this.colors[1])
      }
      .itemConstraintSize(this.itemConstraintSizeType)
      .width('100%')
      .height('100')
      .margin({ bottom: 10 })
      .id('waterFlowItemConstraintSize2')

      Button('WaterFlowItemConstraintSize')
        .onClick(() => {
          this.itemConstraintSizeType = {
            minWidth: '0%',
            maxWidth: '100%',
            minHeight: '0%',
            maxHeight: '100%'
          }
        })
    }
  }
}