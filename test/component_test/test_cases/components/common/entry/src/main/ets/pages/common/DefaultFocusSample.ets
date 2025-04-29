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

import defaultFocusTest from '../MyTest/DefaultFocusTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DefaultFocusSample {
  @State isDefaultFocus: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(defaultFocusTest)
  }

  build() {
    Column({ space: 5 }) {
      Checkbox()
        .id('checkboxDefaultFocus')
        .focusable(true)
        .defaultFocus(this.isDefaultFocus)
      Button('ButtonDefaultFocus')
        .onClick(() => {
          this.isDefaultFocus = !this.isDefaultFocus
        })
    }
  }
}

