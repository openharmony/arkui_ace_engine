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
import swiperPrevMarginTest from '../MyTest/SwiperPrevMarginTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperPrevMarginSample {
  @State prevMarginLength: number | string = 20

  aboutToAppear(): void {
    loadComponentTestEntry(swiperPrevMarginTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperPrevMarginText1')
          .backgroundColor(Color.Blue)
        Text('swiperPrevMarginText2')
          .backgroundColor(Color.Brown)
        Text('swiperPrevMarginText3')
          .backgroundColor(Color.Pink)
      }
      .displayMode(SwiperDisplayMode.STRETCH)
      .prevMargin(10)
      .width('100%')
      .height(100)
      .id('swiperPrevMargin1')

      Swiper() {
        Text('swiperPrevMarginText1')
          .backgroundColor(Color.Blue)
        Text('swiperPrevMarginText2')
          .backgroundColor(Color.Brown)
        Text('swiperPrevMarginText3')
          .backgroundColor(Color.Pink)
      }
      .displayMode(SwiperDisplayMode.STRETCH)
      .prevMargin($r('sys.float.ohos_id_text_size_headline9'))
      .width('100%')
      .height(100)
      .vertical(true)
      .id('swiperPrevMargin2')

      Swiper() {
        Text('swiperPrevMarginText1')
          .backgroundColor(Color.Blue)
        Text('swiperPrevMarginText2')
          .backgroundColor(Color.Brown)
        Text('swiperPrevMarginText3')
          .backgroundColor(Color.Pink)
      }
      .displayMode(SwiperDisplayMode.STRETCH)
      .prevMargin(this.prevMarginLength)
      .width('100%')
      .height(100)
      .id('swiperPrevMargin3')

      Button('SwiperPrevMargin1')
        .onClick(() => {
          this.prevMarginLength = '40px'
        })
    }
  }
}