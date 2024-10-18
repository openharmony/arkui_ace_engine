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

import marginTest_two from '../MyTest/MarginTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MarginSample_two {
  marginWidthArr: (Length | EdgeWidths)[] = [
    {
      left: '8px',
      right: '10px',
      top: '8px',
      bottom: '10px'
    },
    {
      left: 10,
      right: 10,
      top: 10,
      bottom: 10
    },
    {
      left: $r('app.string.common_breadth'),
      right: $r('app.string.common_breadth'),
      top: $r('app.string.common_breadth'),
      bottom: $r('app.string.common_breadth')
    }
  ]
  index: number = 0
  @State marginWidth: (Length | EdgeWidths) = this.marginWidthArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(marginTest_two)
  }

  build() {
    Column() {
      Text('Margin sample')
        .margin({
          left: '8px',
          right: '10px',
          top: '8px',
          bottom: '10px'
        })
        .id('textMargin2')
      Text('Margin sample')
        .margin({
          left: 5,
          right: 5,
          top: 5,
          bottom: 5
        })
        .id('textMargin3')
      Text('Margin sample')
        .margin({
          left: $r('app.string.common_breadth'),
          right: $r('app.string.common_breadth'),
          top: $r('app.string.common_breadth'),
          bottom: $r('app.string.common_breadth')
        })
        .id('textMargin4')
    }
  }
}
