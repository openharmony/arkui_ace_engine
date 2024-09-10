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
import sliderStepColorTest from '../MyTest/SliderStepColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SliderStepColorSample {
  @State stepColorText: ResourceColor = Color.Red

  aboutToAppear(): void {
    loadComponentTestEntry(sliderStepColorTest)
  }

  build() {
    Column() {
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .showSteps(true)
        .stepColor('rgba(255, 100, 255, 0.5)')
        .id('sliderStepColor1')
      Slider({ style: SliderStyle.OutSet, value: 40 }).showSteps(true).stepColor(0xffffee).id('sliderStepColor2')
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .showSteps(true)
        .stepColor(this.stepColorText)
        .id('sliderStepColor3')

      Button('SliderStepColor').onClick(() => {
        this.stepColorText = $r('sys.color.ohos_fa_activated')
      })
    }
  }
}