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

import timePickerDialogAlignmentTest from '../MyTest/TimePickerDialogAlignmentTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TimePickerDialogAlignmentSample {
  @State anyDialogAlignment: DialogAlignment[] = [DialogAlignment.Top,
    DialogAlignment.Center, DialogAlignment.Bottom, DialogAlignment.Default,
    DialogAlignment.TopStart, DialogAlignment.TopEnd, DialogAlignment.CenterStart,
    DialogAlignment.CenterEnd, DialogAlignment.BottomStart, DialogAlignment.BottomEnd]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(timePickerDialogAlignmentTest)
  }

  build() {
    Column({ space: 20 }) {
      Button('TimePickerDialogAlignment').onClick(() => {
        TimePickerDialog.show({
          selected: new Date('2020-01-01T09:00:00'),
          alignment: this.anyDialogAlignment[this.index]
        })
      })
      Button('ClickToggleAlignment')
        .onClick(() => {
          this.index++
          this.index %= 10
        })
    }
  }
}