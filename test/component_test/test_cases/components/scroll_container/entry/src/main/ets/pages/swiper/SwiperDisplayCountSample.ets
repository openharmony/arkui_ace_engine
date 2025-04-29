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
import swiperDisplayCountTest from '../MyTest/SwiperDisplayCountTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperDisplayCountSample {
  @State displayCount: number | string = 'auto'

  aboutToAppear(): void {
    loadComponentTestEntry(swiperDisplayCountTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperDisplayCountText1')
          .width('50%')
          .backgroundColor(Color.Yellow)
        Text('swiperDisplayCountText2')
          .width('50%')
          .backgroundColor(Color.Gray)
        Text('swiperDisplayCountText3')
          .width('50%')
          .backgroundColor(Color.Pink)
        Text('swiperDisplayCountText4')
          .width('50%')
          .backgroundColor(Color.Red)
      }.displayCount({ minSize: '60vp' }, false)
      .width(200)
      .id('swiperDisplayCount1')

      Swiper() {
        Text('swiperDisplayCountText1')
          .width('50%')
          .backgroundColor(Color.Yellow)
        Text('swiperDisplayCountText2')
          .width('50%')
          .backgroundColor(Color.Gray)
        Text('swiperDisplayCountText3')
          .width('50%')
          .backgroundColor(Color.Pink)
        Text('swiperDisplayCountText4')
          .width('50%')
          .backgroundColor(Color.Red)
      }.displayCount({ minSize: 40 }, true)
      .width(200)
      .id('swiperDisplayCount2')

      Swiper() {
        Text('swiperDisplayCountText1')
          .width('50%')
          .backgroundColor(Color.Yellow)
        Text('swiperDisplayCountText2')
          .width('50%')
          .backgroundColor(Color.Gray)
        Text('swiperDisplayCountText3')
          .width('50%')
          .backgroundColor(Color.Pink)
        Text('swiperDisplayCountText4')
          .width('50%')
          .backgroundColor(Color.Red)
      }.displayCount(this.displayCount, true)
      .id('swiperDisplayCount3')

      Button('SwiperDisplayCount1')
        .onClick(() => {
          this.displayCount = 2
        })
    }
  }
}