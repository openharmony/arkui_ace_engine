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

import borderImageTest_one from '../MyTest/BorderImageTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BorderImageSample_one {
  valueArr: RepeatMode[] = [RepeatMode.Repeat, RepeatMode.Stretch, RepeatMode.Round, RepeatMode.Space]
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
  ]
  index: number = 0
  @State value: RepeatMode = this.valueArr[this.index]
  @State bordWidth: (Length | EdgeWidths) = this.bordWidthArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(borderImageTest_one)
  }

  build() {
    Column() {
      Text('This is gradient color.')
        .textAlign(TextAlign.Center)
        .height(50)
        .width(200)
        .id('textBorderImage1')
        .borderImage({
          source: $r('app.media.app_icon'),
          width: {
            top: "10px",
            bottom: "10px",
            left: "10px",
            right: "10px"
          },
          outset: this.bordWidth,
          repeat: this.value,
          fill: true
        })

      Button('ButtonBorderImage1').onClick(() => {
        this.index++
        this.value = this.valueArr[this.index % 4]
        this.bordWidth = this.bordWidthArr[this.index % 6]
      })
    }
  }
}