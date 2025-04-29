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
import sliderBlockSizeTest from '../MyTest/SliderBlockSizeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SliderBlockSizeSample {
  @State sliderSize: SizeOptions = { width: '60px', height: '60px' }

  aboutToAppear(): void {
    loadComponentTestEntry(sliderBlockSizeTest)
  }

  build() {
    Column() {
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockSize({ width: 40, height: 40 })
        .id('sliderBlockSize1')
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockSize({ width: 0, height: 0 })
        .id('sliderBlockSize2')
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockSize(this.sliderSize)
        .id('sliderBlockSize3')

      Button('SliderBlockSize').onClick(() => {
        this.sliderSize = {
          width: $r('app.string.slider_blockSize'),
          height: $r('app.string.slider_blockSize')
        }
      })
    }
  }
}