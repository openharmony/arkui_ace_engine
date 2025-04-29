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

import borderImageTest_three from '../MyTest/BorderImageTest_three'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BorderImageSample_three {
  valueArr: (string | Resource)[] = ['../../../resources/base/media/2.png', $r('app.media.app_icon')]
  bordWidthArr: (Length | EdgeWidths)[] = ['10px', 10, $r('app.string.common_breadth'),
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
  @State value: (string | Resource) = this.valueArr[this.index]
  @State bordWidth: (Length | EdgeWidths) = this.bordWidthArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(borderImageTest_three)
  }

  build() {
    Column() {
      Text('bordimageSample')
        .id('textBorderImage3')
        .borderImage({
          source: this.value,
          width: this.bordWidth,
        })

      Button('ButtonBorderImage3').onClick(() => {
        this.index++
        this.value = this.valueArr[this.index % 2]
        this.bordWidth = this.bordWidthArr[this.index % 6]
      })
    }
  }
}