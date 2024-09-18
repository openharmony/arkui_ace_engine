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

import outlineTest_one from '../MyTest/OutlineTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OutlineSample {
  @State any_outline: OutlineOptions =
    {
      width: $r("app.string.common_value_one"),
      color: 0xff0000,
      style: {
        left: OutlineStyle.DASHED,
        right: OutlineStyle.DASHED,
        top: OutlineStyle.SOLID,
        bottom: OutlineStyle.DOTTED
      },
      radius: {
        topLeft: '5px',
        topRight: '6px',
        bottomLeft: '7vp',
        bottomRight: $r("app.string.common_value_one")
      }
    }

  aboutToAppear(): void {
    loadComponentTestEntry(outlineTest_one)
  }

  build() {
    Column({ space: 50 }) {

      TextInput()
        .outline(this.any_outline)
        .fontSize(30)
        .width(300)
        .height(80)
        .id('textInputOutline1')

      Button('ButtonOutline1')
        .onClick(() => {
          this.any_outline =
            {
              width: '5px',
              style: OutlineStyle.DOTTED,
              radius: 5,
              color: $r("app.string.common_color")
            }
        })
    }
  }
}