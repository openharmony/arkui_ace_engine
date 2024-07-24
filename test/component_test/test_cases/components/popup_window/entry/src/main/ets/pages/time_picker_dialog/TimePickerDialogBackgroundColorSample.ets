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

import timePickerDialogBackgroundColorTest from '../MyTest/TimePickerDialogBackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TimePickerDialogBackgroundColorSample {
  @State anyColor: ResourceColor[] =
    [$r("app.color.time_picker_dialog"), Color.Pink, 'rgba(255, 228, 91, 1.00)', 0x80FFAA]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(timePickerDialogBackgroundColorTest)
  }

  build() {
    Column({ space: 20 }) {
      Button('TimePickerDialogBackgroundColor').onClick(() => {
        TimePickerDialog.show({ backgroundColor: this.anyColor[this.index] })
      })
      Button('ClickToggleBackgroundColor')
        .onClick(() => {
          this.index++
          this.index %= 4
        })
    }
  }
}