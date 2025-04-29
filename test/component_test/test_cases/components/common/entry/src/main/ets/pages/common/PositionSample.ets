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

import positionTest from '../MyTest/PositionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct PositionSample {
  @State any_Position: Position = { x: '1', y: "1" }

  aboutToAppear(): void {
    loadComponentTestEntry(positionTest)
  }

  build() {
    Column() {
      Slider().position(this.any_Position)
      RelativeContainer().position(this.any_Position)
        .height(100).width(100)
        .id('relativeContainerPosition1')

      Button('ButtonPosition1')
        .onClick(() => {
          this.any_Position = { x: 2, y: 2 }
        })
      Button('ButtonPosition2')
        .onClick(() => {
          this.any_Position = { x: $r("app.string.common_value_one"), y: $r("app.string.common_value_one") }
        })
    }
  }
}