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
import ratingStarStyleTest from '../MyTest/RatingStarStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct RatingStarStyleSample {
  @State starStyleTest: string = '/pages/slider/StarYellow.png'

  aboutToAppear(): void {
    loadComponentTestEntry(ratingStarStyleTest)
  }

  build() {
    Column() {
      Rating().starStyle({
        backgroundUri: undefined,
        foregroundUri: undefined,
        secondaryUri: undefined
      }).id('ratingStarStyle1')

      Rating().starStyle({
        backgroundUri: this.starStyleTest,
        foregroundUri: undefined,
        secondaryUri: undefined
      }).id('ratingStarStyle2')

      Rating().starStyle({
        backgroundUri: '/pages/rating/StarBlue.png',
        foregroundUri: '/pages/slider/StarYellow.png',
        secondaryUri: '/pages/rating/StarOrange.png'
      }).id('ratingStarStyle3')

      Button('RatingStarStyle').onClick(() => {
        this.starStyleTest = '/pages/slider/StarYellow.png'
      })
    }.width('100%').height('100%').backgroundColor('#F1F3F5')
  }
}