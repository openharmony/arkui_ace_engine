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

import timePickerDialogMaskRectTest from '../MyTest/TimePickerDialogMaskRectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TimePickerDialogMaskRectSample {
  @State anyLength: Length = 0
  @State maskRectLength: Length = '100%'

  aboutToAppear(): void {
    loadComponentTestEntry(timePickerDialogMaskRectTest)
  }

  build() {
    Column({ space: 20 }) {
      Button('TimePickerDialogMaskRect').onClick(() => {
        TimePickerDialog.show({
          maskRect: {
            x: this.anyLength,
            y: this.anyLength,
            width: this.maskRectLength,
            height: this.maskRectLength
          }
        })
      })

      Button('TimePickerDialog1').onClick(() => {
        this.anyLength = '10px'
        this.maskRectLength = 8000
      })

      Button('TimePickerDialog2').onClick(() => {
        this.anyLength = $r("app.string.timePickerDialog_value_one")
      })
    }
  }
}