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

import borderColorTest_two from '../MyTest/BorderColorTest_two';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BorderColorSample_two {
  bordColorArr: EdgeColors[] = [{
    left: Color.Red,
    right: Color.Blue,
    top: Color.Red,
    bottom: Color.Green
  },
    {
      left: 0xe3bbbb,
      right: 0xFFE4E1,
      top: 0x00FF00,
      bottom: 0xB658BB
    },
    {
      left: $r('sys.color.ohos_id_color_text_hyperlink'),
      right: $r('sys.color.ohos_id_color_text_hyperlink'),
      top: $r('sys.color.ohos_id_color_text_hyperlink'),
      bottom: $r('sys.color.ohos_id_color_text_hyperlink')
    },
    {
      left: 'rgb(72 61 139)',
      right: 'rgb(72 61 139)',
      top: 'rgb(72 61 139)',
      bottom: 'rgb(72 61 139)'
    }
  ]
  index: number = 0
  @State bordColor: EdgeColors = this.bordColorArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(borderColorTest_two)
  }

  build() {
    Column() {
      Grid() {
        GridItem() {
          Text('22')
        }
        .width(100)
        .height(100)
        .borderWidth(5)
        .borderColor(this.bordColor)
        .id('gridItemBorderColor2')
      }

      Button('ButtonItemBorderColor2')
        .onClick(() => {
          this.index++
          this.bordColor = this.bordColorArr[this.index % 4]
        }).width(200).height(50).margin(20)
    }
  }
}