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
import swiperDisplayModeTest from '../MyTest/SwiperDisplayModeTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperDisplayModeSample {
  @State displayMode: SwiperDisplayMode = SwiperDisplayMode.AUTO_LINEAR

  aboutToAppear(): void {
    loadComponentTestEntry(swiperDisplayModeTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperDisplayModeText1')
          .width('10%')
          .backgroundColor(Color.Blue)
        Text('swiperDisplayModeText2')
          .width('30%')
          .backgroundColor(Color.Orange)
        Text('swiperDisplayModeText3')
          .width('30%')
          .backgroundColor(Color.Pink)
      }.displayMode(this.displayMode)
      .displayCount(2)
      .id('swiperDisplayMode1')

      Swiper() {
        Text('swiperDisplayModeText1')
          .width('30%')
          .backgroundColor(Color.Blue)
        Text('swiperDisplayModeText2')
          .width('30%')
          .backgroundColor(Color.Orange)
        Text('swiperDisplayModeText3')
          .width('30%')
          .backgroundColor(Color.Pink)
      }.displayMode(this.displayMode)
      .id('swiperDisplayMode2')

      Button('SwiperDisplayMode1')
        .onClick(() => {
          this.displayMode = SwiperDisplayMode.STRETCH
        })
    }
  }
}