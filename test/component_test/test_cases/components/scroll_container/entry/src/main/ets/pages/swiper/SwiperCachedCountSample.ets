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
import swiperAutoPlayTest from '../MyTest/SwiperCachedCountTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct SwiperCachedCountSample {
  aboutToAppear(): void {
    loadComponentTestEntry(swiperAutoPlayTest)
  }

  build() {
    Column() {
      Swiper() {
        Text('swiperCachedCountText1').backgroundColor(Color.Blue)
        Text('swiperCachedCountText2').backgroundColor(Color.Brown)
        Text('swiperCachedCountText3').backgroundColor(Color.Red)
        Text('swiperCachedCountText4').backgroundColor(Color.Gray)
      }.cachedCount(2)
      .id('swiperCachedCount1')

      Swiper() {
        Text('swiperCachedCountText1').backgroundColor(Color.Blue)
        Text('swiperCachedCountText2').backgroundColor(Color.Brown)
        Text('swiperCachedCountText3').backgroundColor(Color.Red)
        Text('swiperCachedCountText4').backgroundColor(Color.Gray)
      }.cachedCount(1)
      .displayCount(2, true)
      .id('swiperCachedCount2')
    }
  }
}