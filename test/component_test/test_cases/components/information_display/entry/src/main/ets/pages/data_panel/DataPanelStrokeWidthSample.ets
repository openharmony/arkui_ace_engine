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
import dataPanelStrokeWidthTest from '../MyTest/DataPanelStrokeWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DataPanelStrokeWidthSample {
  public values: number[] = [20, 20, 20, 20]
  @State strokeWidthStatus: Length = 30

  aboutToAppear(): void {
    loadComponentTestEntry(dataPanelStrokeWidthTest)
  }

  build() {
    Column({ space: 5 }) {
      DataPanel({ values: this.values, max: 100, type: DataPanelType.Circle })
        .width(150)
        .height(150)
        .strokeWidth(this.strokeWidthStatus)
        .id('dataPanelStrokeWidth1')
      DataPanel({ values: this.values, max: 100, type: DataPanelType.Circle })
        .width(150)
        .height(150)
        .strokeWidth($r('app.string.data_panel_strokeWidth'))
        .id('dataPanelStrokeWidth2')
      DataPanel({ values: this.values, max: 100, type: DataPanelType.Line })
        .width(150)
        .height(150)
        .strokeWidth(20)
        .id('dataPanelStrokeWidth3')
      Button('DataPanelStrokeWidth1')
        .onClick(() => {
          this.strokeWidthStatus = '20%'
        })
      Button('DataPanelStrokeWidth2')
        .onClick(() => {
          this.strokeWidthStatus = -10
        })
    }
  }
}