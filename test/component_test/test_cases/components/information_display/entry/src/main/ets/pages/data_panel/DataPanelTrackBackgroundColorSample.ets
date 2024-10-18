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
import dataPanelTrackBackgroundColorTest from '../MyTest/DataPanelTrackBackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DataPanelTrackBackgroundColorSample {
  public values: number[] = [20, 20, 20, 20]
  @State trackBackgroundColorStatus: ResourceColor = Color.Yellow

  aboutToAppear(): void {
    loadComponentTestEntry(dataPanelTrackBackgroundColorTest)
  }

  build() {
    Column({ space: 5 }) {
      DataPanel({ values: this.values, max: 100, type: DataPanelType.Line })
        .width(300)
        .height(10)
        .trackBackgroundColor(this.trackBackgroundColorStatus)
        .id('dataPanelTrackBackgroundColor1')
      DataPanel({ values: this.values, max: 100, type: DataPanelType.Line })
        .width(300)
        .height(10)
        .trackBackgroundColor($r('sys.color.ohos_fa_palette1'))
        .id('dataPanelTrackBackgroundColor2')
      Button('DataPanelTrackBackgroundColor1')
        .onClick(() => {
          this.trackBackgroundColorStatus = 0xFF00FF
        })
      Button('DataPanelTrackBackgroundColor2')
        .onClick(() => {
          this.trackBackgroundColorStatus = '#FFFF00AA'
        })
    }
  }
}