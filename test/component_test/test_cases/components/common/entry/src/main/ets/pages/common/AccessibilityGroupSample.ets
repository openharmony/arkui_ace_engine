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

import accessibilityGroupTest from '../MyTest/AccessibilityGroupTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AccessibilityGroupSample {
  @State change_boolean: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(accessibilityGroupTest)
  }

  build() {
    Column({ space: 100 }) {
      Column() {
        DatePicker()
          .accessibilityGroup(this.change_boolean)
          .id('datePickerAccessibilityGroup1')
      }

      Button('DatePickerAccessibilityGroup1')
        .onClick(() => {
          this.change_boolean = !this.change_boolean
        })
    }
  }
}