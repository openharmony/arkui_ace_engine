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

import backGroundEffectTest from '../MyTest/BackGroundEffectTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BackGroundEffectSample {
  @State backgroundEffectRadius: number = 100
  @State backgroundEffectSaturation: number = 50
  @State backgroundEffectBrightness: number = 50
  @State backgroundEffectColor: Color = 0xa52a3a
  @State backgroundEffectAdaptiveColor: AdaptiveColor = AdaptiveColor.DEFAULT
  @State backgroundEffectBlurOptions: BlurOptions = { grayscale: [0, 50] }

  aboutToAppear(): void {
    loadComponentTestEntry(backGroundEffectTest)
  }

  build() {
    Column() {

      Gauge({ value: 75 })
        .backgroundEffect({
          radius: this.backgroundEffectRadius,
          saturation: this.backgroundEffectSaturation,
          brightness: this.backgroundEffectBrightness,
          color: this.backgroundEffectColor,
          adaptiveColor: this.backgroundEffectAdaptiveColor,
          blurOptions: this.backgroundEffectBlurOptions
        })
        .id('gaugeBackgroundEffect1')

      Button('ButtonBackGroundEffect1')
        .onClick(() => {
          this.backgroundEffectColor = Color.Blue
          this.backgroundEffectAdaptiveColor = AdaptiveColor.AVERAGE
        })
    }
  }
}