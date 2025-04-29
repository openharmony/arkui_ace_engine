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

import borderWidthTest from '../MyTest/BorderWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BorderWidthSample {
  borderLengthArr: (Length | EdgeWidths)[] = ['10px', 10, $r('app.string.common_breadth'),
    {
      left: '8px',
      right: '10px',
      top: '8px',
      bottom: '10px'
    },
    {
      left: 5,
      right: 5,
      top: 5,
      bottom: 5
    },
    {
      left: $r('app.string.common_breadth'),
      right: $r('app.string.common_breadth'),
      top: $r('app.string.common_breadth'),
      bottom: $r('app.string.common_breadth')
    }
  ];
  index: number = 0
  @State borderLength: (Length | EdgeWidths) = this.borderLengthArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(borderWidthTest)
  }

  build() {
    Column() {
      Text("BorderWidthSample")
        .id('textBorderWidth')
        .borderStyle(BorderStyle.Dashed)
        .borderWidth(this.borderLength)
        .borderColor(0xAFEEEE)
        .borderRadius(10)

      Button('ButtonBorderWidth').onClick(() => {
        this.index++
        this.borderLength = this.borderLengthArr[this.index % 6]
      })
    }
  }
}