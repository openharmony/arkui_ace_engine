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
import datePickerDialogOffsetTest from '../MyTest/DatePickerDialogOffsetTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DatePickerDialogOffsetSample {
  @State offsetNum: number | Resource = 60

  aboutToAppear(): void {
    loadComponentTestEntry(datePickerDialogOffsetTest)
  }

  build() {
    Column() {
      Button("DatePickerDialogOffset1").onClick(() => {
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          offset: { dx: this.offsetNum, dy: this.offsetNum }
        })
      })
      Button("DatePickerDialogOffset2").onClick(() => {
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          offset: { dx: '300px', dy: '100px' }
        })
      })

      Button("DatePickerDialogOffset3").onClick(() => {
        this.offsetNum = $r('app.string.offset_num');
      })
    }.width('100%')
  }
}