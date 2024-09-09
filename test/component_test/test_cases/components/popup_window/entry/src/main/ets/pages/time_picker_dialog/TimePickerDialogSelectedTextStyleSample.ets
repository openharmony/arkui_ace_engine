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

import timePickerDialogSelectedTextStyleTest from '../MyTest/TimePickerDialogSelectedTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TimePickerDialogSelectedTextStyleSample {
  @State anyColor: ResourceColor = $r("app.color.time_picker_dialog")
  @State anyFontSize: Length = $r("app.string.timePickerDialog_value_one")
  @State anyFontWeight: (FontWeight | number | string)[] = ['13vp', 13, FontWeight.Lighter,
    FontWeight.Normal, FontWeight.Regular, FontWeight.Medium, FontWeight.Bold, FontWeight.Bolder]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(timePickerDialogSelectedTextStyleTest)
  }

  build() {
    Column({ space: 20 }) {
      Button('TimePickerDialogSelectedTextStyle').onClick(() => {
        TimePickerDialog.show({
          selectedTextStyle: {
            color: this.anyColor,
            font: {
              size: this.anyFontSize,
              weight: this.anyFontWeight[this.index]
            }
          }
        })
      })

      Button('TimePickerDialog1').onClick(() => {
        this.anyFontSize = '13vp'
        this.anyColor = 'rgba(255, 183, 0, 1.00)'
      })

      Button('TimePickerDialog2').onClick(() => {
        this.anyFontSize = 13
        this.anyColor = 0xC0FF3E
      })

      Button('TimePickerDialog3').onClick(() => {
        this.anyColor = Color.Red
      })

      Button('ClickToggleWeight')
        .onClick(() => {
          this.index++
          this.index %= 8
        })
    }
  }
}