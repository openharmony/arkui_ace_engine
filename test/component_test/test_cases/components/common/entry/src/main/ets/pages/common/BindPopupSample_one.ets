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

import bindPopupTest_one from '../MyTest/BindPopupTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindPopupSample_one {
  @State any_boolean: boolean = true
  @State my_boolean_1: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(bindPopupTest_one)
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
            placementOnTop: this.any_boolean,
            primaryButton: {
              value: 'confirm', action: () => {
                this.any_boolean = !this.any_boolean
                console.info('confirm Button click')
              }
            },
            secondaryButton: {
              value: 'cancel', action: () => {
                this.any_boolean = !this.any_boolean
                console.info('cancel Button click')
              }
            },
            onStateChange: (e) => {
              if (!e.isVisible) {
                this.any_boolean = !this.any_boolean
              }
            }
          }).id('buttonBindPopup1')
        Button('enabled').enabled(this.any_boolean).id('ButtonEnabled')
      }
    }
  }
}