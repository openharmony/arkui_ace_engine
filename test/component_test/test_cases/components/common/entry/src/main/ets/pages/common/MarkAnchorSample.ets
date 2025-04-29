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

import markAnchorTest from '../MyTest/MarkAnchorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MarkAnchorSample {
  @State any_markAnchor: Position = { x: $r("app.string.common_value_one"), y: $r("app.string.common_value_one") }

  aboutToAppear(): void {
    loadComponentTestEntry(markAnchorTest)
  }

  build() {
    Column() {

      Slider()
        .markAnchor(this.any_markAnchor)
        .id('sliderMarkAnchor1')

      Button('ButtonMarkAnchor1')
        .onClick(() => {
          this.any_markAnchor = { x: '2', y: '2' }
        })
      Button('ButtonMarkAnchor2')
        .onClick(() => {
          this.any_markAnchor = { x: 1, y: 1 }
        })
    }
  }
}
