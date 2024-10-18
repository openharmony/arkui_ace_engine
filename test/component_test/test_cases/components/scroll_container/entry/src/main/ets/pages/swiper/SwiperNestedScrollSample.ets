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
import swiperNestedScrollTest from '../MyTest/SwiperNestedScrollTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperNestScrollSample {
  @State nestScroll: SwiperNestedScrollMode = SwiperNestedScrollMode.SELF_ONLY

  aboutToAppear(): void {
    loadComponentTestEntry(swiperNestedScrollTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperNestScrollText1')
          .width('50%')
          .backgroundColor(Color.Blue)
        Text('swiperNestScrollText2')
          .width('50%')
          .backgroundColor(Color.Green)
      }.nestedScroll(this.nestScroll)
      .loop(true)
      .id('swiperNestedScroll1')

      Button('SwiperNestedScroll1')
        .onClick(() => {
          this.nestScroll = SwiperNestedScrollMode.SELF_FIRST
        })
      Swiper() {
        Text('swiperNestScrollText1')
          .width('50%')
          .backgroundColor(Color.Blue)
        Text('swiperNestScrollText2')
          .width('50%')
          .backgroundColor(Color.Green)
      }.nestedScroll(this.nestScroll)
      .id('swiperNestedScroll2')

      Button('SwiperNestedScroll2')
        .onClick(() => {
          this.nestScroll = SwiperNestedScrollMode.SELF_FIRST
        })
    }
  }
}