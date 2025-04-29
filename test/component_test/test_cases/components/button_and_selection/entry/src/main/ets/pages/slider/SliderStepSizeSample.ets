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

// 测试代码路径
import sliderStepSizeTest from '../MyTest/SliderStepSizeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SliderStepSizeSample {
  @State stepSize: Length = '5px'

  aboutToAppear(): void {
    loadComponentTestEntry(sliderStepSizeTest)
  }

  build() {
    Column() {
      Slider({ style: SliderStyle.InSet, value: 40, step: 10 })
        .stepSize(0).stepColor(Color.Black).showSteps(true)
        .id('sliderStepSize1')
      Slider({ style: SliderStyle.InSet, value: 40, step: 10 })
        .stepSize(-1).stepColor(Color.Black).showSteps(true)
        .id('sliderStepSize2')
      Slider({ style: SliderStyle.InSet, value: 40, step: 10 })
        .stepSize(this.stepSize).stepColor(Color.Black).showSteps(true)
        .id('sliderStepSize3')

      Button('SliderStepSize')
        .onClick(() => {
          this.stepSize = $r('app.string.slider_stepSize')
        })
    }
  }
}