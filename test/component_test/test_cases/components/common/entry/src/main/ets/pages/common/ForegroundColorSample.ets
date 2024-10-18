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

import foregroundColorTest from '../MyTest/ForegroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ForegroundColorSample {
  coloringStrategyArr: ColoringStrategy[] = [
    ColoringStrategy.INVERT, ColoringStrategy.AVERAGE, ColoringStrategy.PRIMARY
  ]
  resouColorArr: ResourceColor[] =
    ['rgb(72,61,139)', 0X528B8B, Color.Red, $r('sys.color.ohos_id_color_text_hyperlink')];
  index: number = 0;
  @State resouColor: ResourceColor = this.resouColorArr[this.index]
  @State coloringStrategy: ColoringStrategy = this.coloringStrategyArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(foregroundColorTest)
  }

  build() {
    Column({ space: 10 }) {
      Row() {
        Ellipse({ width: 50, height: 30 }).foregroundColor(this.resouColor)
          .id('rowForegroundColor1')
      }.backgroundColor(Color.Black)

      Row() {
        Ellipse({ width: 50, height: 30 }).foregroundColor(this.coloringStrategy)
          .id('rowForegroundColor2')
      }.backgroundColor(Color.Black)

      Button('ButtonForegroundColor')
        .onClick(() => {
          this.index++
          this.resouColor = this.resouColorArr[this.index % 4]
          this.coloringStrategy = this.coloringStrategyArr[this.index % 3]
        }).width(200).height(50).margin(20)
    }
  }
}