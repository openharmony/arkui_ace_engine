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

//测试代码路径
import sliderSelectedColorTest from '../MyTest/SliderSelectedColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SliderSelectedColorSample {
  @State selectedColorStatusOne: ResourceColor = Color.Red
  @State selectedColorStatusTwo: ResourceColor = 0x008000

  aboutToAppear(): void {
    loadComponentTestEntry(sliderSelectedColorTest)
  }

  build() {
    Column() {
      Slider()
        .id('sliderSelectedColor1')
        .selectedColor(this.selectedColorStatusOne)
      Slider()
        .id('sliderSelectedColor2')
        .selectedColor(this.selectedColorStatusTwo)
      Button('SliderSelectedColor1')
        .onClick(() => {
          this.selectedColorStatusOne = '#ffff00'
        }).margin(10)
      Button('SliderSelectedColor2')
        .onClick(() => {
          this.selectedColorStatusTwo = $r('sys.color.ohos_fa_palette1')
        })
    }.width('100%')
  }
}