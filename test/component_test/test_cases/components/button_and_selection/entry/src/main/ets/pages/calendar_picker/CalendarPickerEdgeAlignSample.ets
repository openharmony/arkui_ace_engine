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

// 测试代码路径
import calendarPickerEdgeAlignTest from '../MyTest/CalendarPickerEdgeAlignTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct CalendarPickerEdgeAlignSample {
  private selectedDate: Date = new Date()
  @State pickerAlign: CalendarAlign = CalendarAlign.CENTER
  @State pickerOffset: number | Resource = 50

  aboutToAppear(): void {
    loadComponentTestEntry(calendarPickerEdgeAlignTest)
  }

  build() {
    Column() {
      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(CalendarAlign.START, { dx: '10px', dy: '10px' }).id('calendarPickerEdgeAlign1')
      CalendarPicker({ hintRadius: 10, selected: this.selectedDate })
        .edgeAlign(this.pickerAlign, { dx: this.pickerOffset, dy: this.pickerOffset }).id('calendarPickerEdgeAlign2')

      Button('CalendarPickerEdgeAlign').onClick(() => {
        this.pickerAlign = CalendarAlign.END
        this.pickerOffset = $r('app.string.picker_edgeOffset')
      })
    }
  }
}