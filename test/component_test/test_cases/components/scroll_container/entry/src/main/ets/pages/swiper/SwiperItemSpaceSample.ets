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
import swiperItemSpaceTest from '../MyTest/SwiperItemSpaceTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperItemSpaceSample {
  @State itemSpace: string | number = 2

  aboutToAppear(): void {
    loadComponentTestEntry(swiperItemSpaceTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperItemSpaceText1')
          .width('30%')
          .backgroundColor(Color.Blue)
        Text('swiperItemSpaceText2')
          .width('30%')
          .backgroundColor(Color.Pink)
      }.itemSpace("20%")
      .id('swiperItemSpace1')

      Swiper() {
        Text('swiperItemSpaceText1')
          .width('30%')
          .backgroundColor(Color.Blue)
        Text('swiperItemSpaceText2')
          .width('30%')
          .backgroundColor(Color.Pink)
      }.itemSpace(this.itemSpace)
      .id('swiperItemSpace2')

      Button('SwiperItemSpace1')
        .onClick(() => {
          this.itemSpace = '15px'
        })
    }.width('100%')
  }
}