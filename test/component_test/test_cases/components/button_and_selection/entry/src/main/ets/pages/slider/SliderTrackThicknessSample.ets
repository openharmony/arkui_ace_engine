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
import sliderTrackThicknessTest from '../MyTest/SliderTrackThicknessTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct SliderTrackThicknessSample {
  @State trackNess: Length = 35

  aboutToAppear(): void {
    loadComponentTestEntry(sliderTrackThicknessTest)
  }

  build() {
    Column() {
      Slider({ style: SliderStyle.InSet, value: 40 }).trackThickness(0).id('sliderTrackThickness1')
      Slider({ style: SliderStyle.InSet, value: 40 }).trackThickness('15px').id('sliderTrackThickness2')
      Slider({ style: SliderStyle.InSet, value: 40 }).trackThickness(this.trackNess).id('sliderTrackThickness3')

      Button('SliderTrackThickness').onClick(() => {
        this.trackNess = $r('app.string.track_thickness')
      })
    }
  }
}