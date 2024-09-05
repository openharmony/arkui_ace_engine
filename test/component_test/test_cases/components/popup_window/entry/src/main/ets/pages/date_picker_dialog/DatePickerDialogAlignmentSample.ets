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
import datePickerDialogAlignmentTest from '../MyTest/DatePickerDialogAlignmentTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DatePickerDialogAlignmentSample {
  @State alignChange: DialogAlignment[] = [DialogAlignment.Top, DialogAlignment.Center, DialogAlignment.Bottom,
    DialogAlignment.Default, DialogAlignment.TopStart, DialogAlignment.TopEnd, DialogAlignment.CenterStart,
    DialogAlignment.CenterEnd, DialogAlignment.BottomStart, DialogAlignment.BottomEnd]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(datePickerDialogAlignmentTest)
  }

  build() {
    Column() {
      Button("DatePickerDialogAlignment1").onClick(() => {
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          alignment: this.alignChange[this.index]
        })
      })

      Button("DatePickerDialogAlignment2").onClick(() => {
        this.index++;
        this.index %= 10;
      })
    }.width('100%')
  }
}