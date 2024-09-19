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
import timePickerUseMilitaryTimeTest from '../MyTest/TimePickerUseMilitaryTimeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TimePickerUseMilitaryTimeSample {
  @State useMilTime: boolean = true
  private selectedTime: Date = new Date('2022-07-22T08:00:00')

  aboutToAppear(): void {
    loadComponentTestEntry(timePickerUseMilitaryTimeTest)
  }

  build() {
    Column() {
      TimePicker({ selected: this.selectedTime }).useMilitaryTime(this.useMilTime).id('timePickerUseMilitaryTime');

      Button('TimePickerUseMilitaryTime').onClick(() => {
        this.useMilTime = false
      })
    }.width('100%')
  }
}