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
import swiperNextMarginTest from '../MyTest/SwiperNextMarginTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperNextMarginSample {
  @State nextMarginLength: number | string = 20

  aboutToAppear(): void {
    loadComponentTestEntry(swiperNextMarginTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperNextMarginText1')
          .backgroundColor(Color.Blue)
        Text('swiperNextMarginText2')
          .backgroundColor(Color.Brown)
        Text('swiperNextMarginText3')
          .backgroundColor(Color.Pink)
      }
      .displayMode(SwiperDisplayMode.STRETCH)
      .nextMargin(10)
      .width('100%')
      .height(100)
      .id('swiperNextMargin1')

      Swiper() {
        Text('swiperNextMarginText1')
          .backgroundColor(Color.Blue)
        Text('swiperNextMarginText2')
          .backgroundColor(Color.Brown)
        Text('swiperNextMarginText3')
          .backgroundColor(Color.Pink)
      }
      .displayMode(SwiperDisplayMode.STRETCH)
      .nextMargin($r('app.float.ListLanes_float'))
      .width('100%')
      .height(100)
      .vertical(true)
      .id('swiperNextMargin2')

      Swiper() {
        Text('swiperNextMarginText1')
          .backgroundColor(Color.Blue)
        Text('swiperNextMarginText2')
          .backgroundColor(Color.Brown)
        Text('swiperNextMarginText3')
          .backgroundColor(Color.Pink)
      }
      .displayMode(SwiperDisplayMode.STRETCH)
      .nextMargin(this.nextMarginLength)
      .width('100%')
      .height(100)
      .id('swiperNextMargin3')

      Button('SwiperNextMargin1')
        .onClick(() => {
          this.nextMarginLength = '40px'
        })
    }
  }
}