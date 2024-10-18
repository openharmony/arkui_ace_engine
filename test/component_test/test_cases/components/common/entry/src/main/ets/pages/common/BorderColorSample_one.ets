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

import borderColorTest_one from '../MyTest/BorderColorTest_one';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BorderColorSample_one {
  borderColorArr: ResourceColor[] = ['rgba(27, 0, 255, 1.00)', 0X528B8B, Color.Red,
    $r('sys.color.ohos_id_color_text_hyperlink'),]
  index: number = 0
  @State bordColor: ResourceColor = this.borderColorArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(borderColorTest_one)
  }

  build() {
    Column() {
      Grid() {
        GridItem() {
          Text('GridItemText')
        }
        .width(100)
        .height(100)
        .borderWidth(5)
        .borderColor(this.bordColor)
        .id('gridItemBorderColor1')
      }

      Button('ButtonItemBorderColor1')
        .onClick(() => {
          this.index++
          this.bordColor = this.borderColorArr[this.index % 4]
        }).width(200).height(50).margin(20)
    }
  }
}