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
import datePickerDialogUseMilitaryTimeTest from '../MyTest/DatePickerDialogUseMilitaryTimeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DatePickerDialogUseMilitaryTimeSample {
  @State useMilitaryTimeChange: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(datePickerDialogUseMilitaryTimeTest)
  }

  build() {
    Column() {
      Button("DatePickerDialogUseMilitaryTime1").onClick(() => {
        DatePickerDialog.show({
          start: new Date("2000-1-1"),
          end: new Date("2100-12-31"),
          useMilitaryTime: this.useMilitaryTimeChange
        })
      })
      Button("DatePickerDialogUseMilitaryTime2").onClick(() => {
        this.useMilitaryTimeChange = false
      })
    }.width('100%')
  }
}