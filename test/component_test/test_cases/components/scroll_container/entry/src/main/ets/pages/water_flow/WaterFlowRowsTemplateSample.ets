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
import waterFlowRowsTemplateTest from '../MyTest/WaterFlowRowsTemplateTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct WaterFlowRowsTemplateSample {
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23]
  dataSource: WaterFlowDataSource = new WaterFlowDataSource()

  aboutToAppear(): void {
    loadComponentTestEntry(waterFlowRowsTemplateTest);
  }

  build() {
    WaterFlow() {
      FlowItem() {
        Text("1").fontSize(12)
      }.width('10%').backgroundColor(this.colors[0])

      FlowItem() {
        Text("2").fontSize(12)
      }.width('10%').backgroundColor(this.colors[1])

      FlowItem() {
        Text("3").fontSize(12)
      }.width('10%').backgroundColor(this.colors[2])
    }
    .rowsTemplate('1fr 1fr 2fr')
    .layoutDirection(FlexDirection.Row)
    .id('waterFlowRowsTemplate')
  }
}