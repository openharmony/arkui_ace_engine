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

import bindPopupTest_three from '../MyTest/BindPopupTest_three'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindPopupSample_three {
  @State my_boolean_1: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(bindPopupTest_three)
  }

  build() {
    Column({ space: 20 }) {
      Column() {

        Button('ButtonBindPopup')
          .onClick(() => {
            this.my_boolean_1 = !this.my_boolean_1
          })
          .bindPopup(this.my_boolean_1, {
            message: "bindPopup",
            targetSpace: $r("app.string.common_value_one"),
            offset: { x: 1, y: 1 },
            width: '100px',
            arrowWidth: '10px'
          }).id('buttonBindPopup3')
      }
    }
  }
}