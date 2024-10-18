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
import sliderTrackColorTest from '../MyTest/SliderTrackColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SliderTrackColorSample {
  @State trackColorStatusOne: ResourceColor = Color.Red
  @State trackColorStatusTwo: ResourceColor = 0x008000

  aboutToAppear(): void {
    loadComponentTestEntry(sliderTrackColorTest)
  }

  build() {
    Column() {
      Slider()
        .trackColor(this.trackColorStatusOne)
        .id('sliderTrackColor1')
      Slider()
        .trackColor(this.trackColorStatusTwo)
        .id('sliderTrackColor2')

      Button('SliderTrackColor1')
        .onClick(() => {
          this.trackColorStatusOne = '#ffff00'
        }).margin(10)

      Button('SliderTrackColor2')
        .onClick(() => {
          this.trackColorStatusTwo = $r('sys.color.ohos_fa_palette1')
        })
    }.width('100%')
  }
}