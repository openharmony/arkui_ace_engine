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
import shadowTest_one from '../MyTest/ShadowTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ShadowSample_one {
  @State radiusNumber: Resource | number = 20
  @State colorColor: Color | string | Resource | ColoringStrategy = 0x0000ff
  @State offsetXNumber: number | Resource = 50
  @State offsetYNumber: number | Resource = 50
  @State fillBoolean: boolean = false
  @State shadowStyle: ShadowStyle = ShadowStyle.OUTER_DEFAULT_XS
  private selectedDate: Date = new Date()

  aboutToAppear(): void {
    loadComponentTestEntry(shadowTest_one)
  }

  build() {
    Column() {
      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .id('calendarPicker1')
        .shadow({
          radius: this.radiusNumber,
          type: ShadowType.COLOR,
          color: this.colorColor,
          offsetX: this.offsetXNumber,
          offsetY: this.offsetYNumber,
          fill: this.fillBoolean
        })

      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .id('calendarPicker2')
        .shadow({
          radius: 50,
          type: ShadowType.BLUR,
          color: ("#FFF12525"),
          offsetX: $r("app.string.any_offset"),
          offsetY: $r("app.string.any_offset"),
          fill: true
        })

      Button('ButtonShadow1').onClick(() => {
        this.colorColor = $r('app.color.start_window_background');
        this.radiusNumber = $r('app.string.any_offset')
        this.offsetXNumber = $r("app.string.any_offset")
        this.offsetYNumber = $r("app.string.any_offset")
        this.fillBoolean = true
      })

      Button('ButtonShadow2').onClick(() => {
        this.colorColor = ColoringStrategy.INVERT;
      })
      Button('ButtonShadow3').onClick(() => {
        this.colorColor = ColoringStrategy.AVERAGE;
      })
      Button('ButtonShadow4').onClick(() => {
        this.colorColor = ColoringStrategy.PRIMARY;
      })
      Button('ButtonShadow5').onClick(() => {
        this.colorColor = 0x0000ff;
      })
    }
  }
}