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

import offsetTest from '../MyTest/OffsetTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OffsetSample {
  @State any_position: Position = { x: $r("app.string.common_value_two"), y: $r("app.string.common_value_two") }

  aboutToAppear(): void {
    loadComponentTestEntry(offsetTest)
  }

  build() {
    Column() {

      Slider()
        .offset(this.any_position)
        .id('sliderOffset1')

      Button('ButtonOffset1')
        .onClick(() => {
          this.any_position = { x: 10, y: 10 }
        })

      Button('ButtonOffset2')
        .onClick(() => {
          this.any_position = { x: '30', y: '30' }
        })
    }
  }
}
