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

import constraintSizeTest from '../MyTest/ConstraintSizeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ConstraintSizeSample {
  constrintSizeArr: ConstraintSizeOptions[] = [
    {
      minWidth: '8px',
      maxWidth: '10px',
      minHeight: '8px',
      maxHeight: '10px'
    },
    {
      minWidth: 5,
      maxWidth: 10,
      minHeight: 5,
      maxHeight: 10
    },
    {
      maxWidth: $r('app.string.common_length'),
      minWidth: $r('app.string.common_breadth'),
      maxHeight: $r('app.string.common_length'),
      minHeight: $r('app.string.common_breadth')
    }]
  valueWidthArr: Length[] = ['8px', 11, 120]
  valueHeightArr: Length[] = ['7px', 4, 9]
  index: number = 0
  @State constrintSize: ConstraintSizeOptions = this.constrintSizeArr[this.index]
  @State valueWidth: Length = this.valueWidthArr[this.index]
  @State valueHeight: Length = this.valueHeightArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(constraintSizeTest)
  }

  build() {
    Column({ space: 10 }) {
      Row()
        .id('rowConstraintSize')
        .constraintSize(this.constrintSize)
        .size({ width: this.valueWidth, height: this.valueHeight })

      Button('ButtonConstraintSize').onClick(() => {
        this.index++
        this.valueWidth = this.valueWidthArr[this.index % 3]
        this.valueHeight = this.valueHeightArr[this.index % 3]
        this.constrintSize = this.constrintSizeArr[this.index % 3]
      })
    }
  }
}