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
import sliderBlockStyleTest from '../MyTest/SliderBlockStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SliderBlockStyleSample {
  @State sliderStyle: SliderBlockStyle = {
    type: SliderBlockType.IMAGE,
    image: "/pages/slider/StarYellow.png", shape: new Path({ commands: 'M60 60 M30 30 L15 56 L45 56 Z' })
  }

  aboutToAppear(): void {
    loadComponentTestEntry(sliderBlockStyleTest)
  }

  build() {
    Column() {
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockStyle({ type: SliderBlockType.DEFAULT, shape: new Circle({ width: 150, height: 150 }) })
        .id('sliderBlockStyle1')
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockStyle({ type: SliderBlockType.DEFAULT, shape: new Ellipse({ width: 150, height: 100 }) })
        .id('sliderBlockStyle2')
      Slider({ style: SliderStyle.OutSet, value: 40 })
        .blockStyle(this.sliderStyle)
        .id('sliderBlockStyle3')

      Button('SliderBlockStyle').onClick(() => {
        this.sliderStyle = {
          type: SliderBlockType.SHAPE,
          image: $r('app.media.startIcon'), shape: new Rect({ width: 150, height: 150 })
        }
      })

    }.backgroundColor(Color.Gray).width('100%').height('100%')
  }
}