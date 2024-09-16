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
import gaugeTrackShadowTest from '../MyTest/GaugeTrackShadowTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GaugeTrackShadowSample {
  @State trackShadowStatus: GaugeShadowOptions | null = { radius: 100, offsetX: 30, offsetY: 30 }

  aboutToAppear(): void {
    loadComponentTestEntry(gaugeTrackShadowTest)
  }

  build() {
    Column() {
      Row() {
        Stack() {
          Column() {
            Gauge({ value: 50, min: 1, max: 100 })
              .trackShadow(this.trackShadowStatus)
              .width(150)
              .height(150)
              .id('gaugeTrackShadow')
            Button('GaugeTrackShadow1')
              .onClick(() => {
                this.trackShadowStatus = {
                  radius: $r("app.string.data_panel_number"),
                  offsetX: $r("app.string.data_panel_number"),
                  offsetY: $r("app.string.data_panel_number")
                }
              })
            Button('GaugeTrackShadow2')
              .onClick(() => {
                this.trackShadowStatus = null
              })
          }
        }
      }
    }
  }
}