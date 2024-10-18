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

import outlineTest_two from '../MyTest/OutlineTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OutlineSample_two {
  @State any_outline: OutlineOptions =
    {
      width: $r("app.string.common_value_one"),
      style: OutlineStyle.DOTTED,
      radius: $r("app.string.common_value_one"),
      color: {
        left: Color.Brown,
        right: 0xff0000,
        top: $r("app.string.common_color"),
        bottom: 'rgba(0, 102, 255, 1.00)'
      }
    }

  aboutToAppear(): void {
    loadComponentTestEntry(outlineTest_two)
  }

  build() {
    Column({ space: 50 }) {

      TextInput()
        .outline(this.any_outline)
        .fontSize(30)
        .width(300)
        .height(80)
        .id('textInputOutline2')

      Button('ButtonOutline1')
        .onClick(() => {
          this.any_outline =
            {
              style: OutlineStyle.SOLID,
              color: 'rgba(255, 243, 12, 1.00)'
            }
        })
    }
  }
}