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

import outlineWidthTest from '../MyTest/OutlineWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OutlineWidthSample {
  @State any: Dimension | EdgeOutlineWidths = {
    left: '5vp',
    right: $r("app.string.common_value_one"),
    top: '15px',
    bottom: 20
  }

  aboutToAppear(): void {
    loadComponentTestEntry(outlineWidthTest)
  }

  build() {
    Row({ space: 50 }) {
      Text()
      Column({ space: 50 }) {
        Text()
        TimePicker().width(300).height(100)
          .outlineWidth(this.any).id('timePickerOutlineWidth1')
      }

      Button('ButtonOutlineWidth1')
        .onClick(() => {
          this.any = '15px'
        })
      Button('ButtonOutlineWidth2')
        .onClick(() => {
          this.any = $r("app.string.common_value_one")
        })
      Button('ButtonOutlineWidth3')
        .onClick(() => {
          this.any = 20
        })
    }
  }
}