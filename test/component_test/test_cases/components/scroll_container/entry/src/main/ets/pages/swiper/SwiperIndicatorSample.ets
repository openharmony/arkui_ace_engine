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
import swiperIndicatorTest from '../MyTest/SwiperIndicatorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperIndicatorSample {
  @State dotIndicatorLength1: number | string = 3
  @State dotIndicatorLength2: number | string = 4
  @State dotIndicatorColor1: ResourceColor = 0x5d5d6c
  @State dotIndicatorColor2: ResourceColor = 0x5d6d3c
  @State digitIndicatorLength1: number | string = 5
  @State digitIndicatorLength2: number | string = 6
  @State digitIndicatorColor1: ResourceColor = 0x5d5d6c
  @State digitIndicatorColor2: ResourceColor = 0x5d6d3c

  aboutToAppear(): void {
    loadComponentTestEntry(swiperIndicatorTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperIndicatorText1')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
        Text('swiperIndicatorText2')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
      }.indicator(
        new DotIndicator()
          .itemWidth('30px')
          .itemHeight('40px')
          .selectedItemWidth($r('sys.float.ohos_id_text_size_headline9'))
          .selectedItemHeight($r('sys.float.ohos_id_text_size_headline9'))
          .mask(false)
          .color(Color.Blue)
          .selectedColor(Color.Pink))
      .id('swiperIndicator1')

      Swiper() {
        Text('swiperIndicatorText1')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
        Text('swiperIndicatorText2')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
      }.indicator(Indicator.dot()
        .itemWidth($r('sys.float.ohos_id_text_size_headline9'))
        .itemHeight($r('sys.float.ohos_id_text_size_headline9'))
        .selectedItemWidth($r('sys.float.ohos_id_text_size_headline9'))
        .selectedItemHeight($r('sys.float.ohos_id_text_size_headline9'))
        .mask(false)
        .color($r('sys.color.ohos_id_icon_color_active_secondary'))
        .selectedColor($r('app.color.start_window_background')))
      .id('swiperIndicator2')

      Swiper() {
        Text('swiperIndicatorText1')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
        Text('swiperIndicatorText2')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
      }.indicator(Indicator.dot()
        .itemWidth(this.dotIndicatorLength1)
        .itemHeight(this.dotIndicatorLength1)
        .selectedItemWidth(this.dotIndicatorLength2)
        .selectedItemHeight(this.dotIndicatorLength2)
        .mask(true)
        .color(this.dotIndicatorColor1)
        .selectedColor(this.dotIndicatorColor2))
      .id('swiperIndicator3')

      Button('SwiperIndicator1')
        .onClick(() => {
          this.dotIndicatorLength1 = '23px'
          this.dotIndicatorLength2 = '30px'
          this.dotIndicatorColor1 = '#125432'
          this.dotIndicatorColor2 = '#ff373dc3'
        })
      Swiper() {
        Text('swiperIndicatorText1')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
        Text('swiperIndicatorText2')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
      }.indicator(Indicator.digit()
        .fontColor($r('sys.color.ohos_id_navigation_group_color'))
        .selectedFontColor('sys.color.ohos_id_icon_color_active_secondary')
        .digitFont({ size: $r('sys.float.ohos_id_text_size_headline9'), weight: 10 })
        .selectedDigitFont({ size: $r('sys.float.ohos_id_text_size_headline9'), weight: 10 }))
      .id('swiperIndicator4')

      Swiper() {
        Text('swiperIndicatorText1')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
        Text('swiperIndicatorText2')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
      }.indicator(Indicator.digit()
        .fontColor(Color.Gray)
        .selectedFontColor(Color.Gray)
        .digitFont({ size: 10, weight: FontWeight.Bold })
        .selectedDigitFont({ size: 10, weight: FontWeight.Bold }))
      .id('swiperIndicator5')

      Swiper() {
        Text('swiperIndicatorText1')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
        Text('swiperIndicatorText2')
          .width('50%')
          .height(60)
          .textAlign(TextAlign.Center)
      }.indicator(Indicator.digit()
        .fontColor(this.digitIndicatorColor1)
        .selectedFontColor(this.digitIndicatorColor2)
        .digitFont({ size: this.digitIndicatorLength1, weight: this.digitIndicatorLength1 })
        .selectedDigitFont({ size: this.digitIndicatorLength2, weight: this.digitIndicatorLength2 }))
      .id('swiperIndicator6')

      Button('SwiperIndicator2')
        .onClick(() => {
          this.digitIndicatorLength1 = '15px'
          this.digitIndicatorLength2 = '20px'
          this.digitIndicatorColor1 = '#ff26868f'
          this.digitIndicatorColor2 = '#ff9417a2'
        })
    }
  }
}