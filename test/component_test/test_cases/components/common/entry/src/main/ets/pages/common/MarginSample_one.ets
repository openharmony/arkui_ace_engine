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

import marginTest_one from '../MyTest/MarginTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MarginSample_one {
  marginWidthArr: (Length | EdgeWidths)[] = ['10px', 10, $r('app.string.common_breadth')]
  index: number = 0
  @State marginWidth: (Length | EdgeWidths) = this.marginWidthArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(marginTest_one)
  }

  build() {
    Column() {
      Text('Margin sample').margin(this.marginWidth)
        .id('textMargin1')
      Button('ButtonTextMargin').onClick(() => {
        this.index++
        this.marginWidth = this.marginWidthArr[this.index % 3]
      })
    }
  }
}
