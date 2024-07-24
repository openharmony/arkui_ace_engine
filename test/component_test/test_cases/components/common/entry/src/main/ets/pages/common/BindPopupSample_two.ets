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

import bindPopupTest_two from '../MyTest/BindPopupTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindPopupSample_two {
  @State any_boolean: boolean = true
  @State my_boolean_1: boolean = true
  @State any_Length: Length = 1

  aboutToAppear(): void {
    loadComponentTestEntry(bindPopupTest_two)
  }

  build() {
    Column({ space: 20 }) {
      Row() {
        Button('ButtonBindPopup')
          .onClick(() => {
            this.my_boolean_1 = !this.my_boolean_1
          })
          .bindPopup(this.my_boolean_1, {
            message: "bindPopup",
            arrowOffset: this.any_Length,
            showInSubWindow: this.any_boolean,
            mask: this.any_boolean,
            messageOptions: {
              textColor: Color.Blue,
              font: { size: 10, weight: '5' }
            }
          }).id('buttonBindPopup2')
      }
    }
  }
}