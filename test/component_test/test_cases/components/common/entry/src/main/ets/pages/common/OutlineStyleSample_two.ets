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

import outlineStyleTest_two from '../MyTest/OutlineStyleTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct OutlineStyleSample_two {
  @State any_OutlineStyle: OutlineStyle | EdgeOutlineStyles = {
    left: OutlineStyle.DOTTED,
    right: OutlineStyle.DOTTED,
    top: OutlineStyle.DOTTED,
    bottom: OutlineStyle.SOLID
  }
  @State OutlineStyle_any_1: OutlineStyle | EdgeOutlineStyles = {
    left: OutlineStyle.DASHED,
    right: OutlineStyle.SOLID,
    top: OutlineStyle.DASHED,
    bottom: OutlineStyle.DOTTED
  }
  @State OutlineStyle_any_2: OutlineStyle | EdgeOutlineStyles = {
    left: OutlineStyle.SOLID,
    right: OutlineStyle.DASHED,
    top: OutlineStyle.SOLID,
    bottom: OutlineStyle.DASHED
  }

  aboutToAppear(): void {
    loadComponentTestEntry(outlineStyleTest_two)
  }

  build() {
    Row({ space: 30 }) {
      Text()
      Column({ space: 15 }) {

        TextInput()
          .height(40)
          .width(200)
          .outlineWidth(5)
          .outlineStyle(this.any_OutlineStyle)
          .id('textInputOutlineStyle2')

        Button('ButtonOutlineStyle1')
          .onClick(() => {
            this.any_OutlineStyle = this.OutlineStyle_any_1
          })
        Button('ButtonOutlineStyle2')
          .onClick(() => {
            this.any_OutlineStyle = this.OutlineStyle_any_2
          })
      }
    }
  }
}