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
import sliderBlockBorderColorTest from '../MyTest/SliderBlockBorderColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SliderBlockBorderColorSample {
  @State blockBorderCol: ResourceColor = Color.Red
  @State blockBorder: ResourceColor = 'rgb(255, 100, 255)'

  aboutToAppear(): void {
    loadComponentTestEntry(sliderBlockBorderColorTest)
  }

  build() {
    Column() {
      Slider().blockStyle({ type: SliderBlockType.DEFAULT }).blockBorderColor(Color.Black).id('sliderBlockBorderColor1')
      Slider().blockStyle({ type: SliderBlockType.IMAGE }).blockBorderColor(Color.Yellow).id('sliderBlockBorderColor2')
      Slider()
        .blockStyle({ type: SliderBlockType.SHAPE })
        .blockBorderColor(this.blockBorderCol)
        .id('sliderBlockBorderColor3')
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockBorderWidth(4)
        .blockSize({ width: 40, height: 40 })
        .blockBorderColor(0xffffff)
        .id('sliderBlockBorderColor4')
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockBorderWidth(4)
        .blockSize({ width: 40, height: 40 })
        .blockBorderColor(this.blockBorder)
        .id('sliderBlockBorderColor5')
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockSize({ width: 40, height: 40 })
        .blockBorderWidth(4)
        .blockBorderColor(this.blockBorderCol)
        .id('sliderBlockBorderColor6')

      Button('SliderBlockBorderColor').onClick(() => {
        this.blockBorderCol = $r('sys.color.ohos_fa_activated')
        this.blockBorder = Color.Yellow
      })
    }
  }
}