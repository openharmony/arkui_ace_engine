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

import foregroundBlurStyleTest from '../MyTest/ForegroundBlurStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ForegroundBlurStyleSample {
  ForegroundBlurStyle: BlurStyle[] = [BlurStyle.Thin, BlurStyle.Regular, BlurStyle.Thick, BlurStyle.BACKGROUND_THIN
    , BlurStyle.BACKGROUND_REGULAR, BlurStyle.BACKGROUND_THICK, BlurStyle.BACKGROUND_ULTRA_THICK
    , BlurStyle.NONE, BlurStyle.COMPONENT_ULTRA_THIN, BlurStyle.COMPONENT_THIN, BlurStyle.COMPONENT_REGULAR
    , BlurStyle.COMPONENT_THICK, BlurStyle.COMPONENT_ULTRA_THICK]
  index: number = 0
  @State value: BlurStyle = this.ForegroundBlurStyle[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(foregroundBlurStyleTest)
  }

  build() {
    Column() {

      Image($r('app.media.app_icon'))
        .width(300)
        .height(350)
        .foregroundBlurStyle(this.value, {
          colorMode: ThemeColorMode.SYSTEM,
          adaptiveColor: AdaptiveColor.DEFAULT,
          blurOptions: { grayscale: [12, 103] }
        })
        .id('imageForegroundBlurStyle1')


      Button('ButtonForegroundBlurStyle')
        .onClick(() => {
          this.index++
          this.value = this.ForegroundBlurStyle[this.index % 13]
        })

    }
  }
}

