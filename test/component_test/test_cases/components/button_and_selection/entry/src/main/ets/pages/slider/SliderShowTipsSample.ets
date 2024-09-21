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
import sliderShowTipsTest from '../MyTest/SliderShowTipsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SliderShowTipsSample {
  @State showTipsStatus: boolean = false

  aboutToAppear(): void {
    loadComponentTestEntry(sliderShowTipsTest)
  }

  build() {
    Column() {
      Slider()
        .showTips(this.showTipsStatus)
        .id('sliderShowTips1')
      Slider({ direction: Axis.Horizontal })
        .showTips(true, 'hello')
        .id('sliderShowTips2')
      Slider({ direction: Axis.Vertical })
        .showTips(true, $r('app.string.app_name'))
        .height(200)
        .id('sliderShowTips3')

      Button('SliderShowTips1')
        .onClick(() => {
          this.showTipsStatus = true
        })
    }.width('100%')
  }
}