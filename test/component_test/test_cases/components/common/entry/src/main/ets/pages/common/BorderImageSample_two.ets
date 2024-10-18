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

import borderImageTest_two from '../MyTest/BorderImageTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BorderImageSample_two {
  valueArr: GradientDirection[] = [GradientDirection.Left, GradientDirection.Top, GradientDirection.Right,
    GradientDirection.Bottom, GradientDirection.LeftTop, GradientDirection.LeftBottom, GradientDirection.RightTop,
    GradientDirection.RightBottom, GradientDirection.None]
  colorArr: ResourceColor[] = ['rgb(72, 61, 139)', 0X528B8B, Color.Red, $r('sys.color.ohos_id_color_text_hyperlink')];
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
  ]
  index: number = 0
  @State value: GradientDirection = this.valueArr[this.index]
  @State color: ResourceColor = this.colorArr[this.index]
  @State borderLength: (Length | EdgeWidths) = this.borderLengthArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(borderImageTest_two)
  }

  build() {
    Column() {
      Text('This is gradient color.')
        .textAlign(TextAlign.Center)
        .height(50)
        .width(200)
        .id('textBorderImage2')
        .borderImage({
          source: {
            angle: 90,
            direction: this.value,
            colors: [[this.color, 0.0], [0xD3E0DC, 0.3], [0xFCD1D1, 1.0]]
          },
          slice: this.borderLength,
          width: {
            top: "10px",
            bottom: "10px",
            left: "10px",
            right: "10px"
          },
          fill: false
        })

      Button('ButtonBorderImage2').onClick(() => {
        this.index++
        this.value = this.valueArr[this.index % 9]
        this.color = this.colorArr[this.index % 4]
        this.borderLength = this.borderLengthArr[this.index % 6]
      })
    }
  }
}