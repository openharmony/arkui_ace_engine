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

import backgroundImagePositionTest from '../MyTest/BackgroundImagePositionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BackgroundImagePositionSample {
  alignmentArr: Alignment[] = [Alignment.TopStart, Alignment.Top, Alignment.TopEnd, Alignment.Start,
    Alignment.Center, Alignment.End, Alignment.BottomStart, Alignment.Bottom, Alignment.BottomEnd]
  index: number = 0
  @State alignment: Alignment = this.alignmentArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(backgroundImagePositionTest)
  }

  build() {
    Column() {
      Menu()
        .width('50%')
        .height('10%')
        .backgroundImage($r('app.media.app_icon'))
        .backgroundImageSize({ width: '50%', height: '50%' })
        .backgroundImagePosition({ x: 10, y: 15 })
        .id('menuBackgroundImagePosition1')
      Menu()
        .width('50%')
        .height('10%')
        .backgroundImage($r('app.media.app_icon'))
        .backgroundImageSize({ width: '50%', height: '50%' })
        .backgroundImagePosition({ x: '10px', y: '15px' })
        .id('menuBackgroundImagePosition2')
      Marquee({ start: false, src: "1" })
        .width('50%')
        .height('10%')
        .backgroundImage($r('app.media.app_icon'))
        .backgroundImageSize({ width: '50%', height: '50%' })
        .backgroundImagePosition({
          x: $r('app.string.commonPosition_length'),
          y: $r('app.string.commonPosition_length')
        })
        .id('marqueeBackgroundImagePosition')
      Menu()
        .width('50%')
        .height('10%')
        .backgroundImage($r('app.media.app_icon'))
        .backgroundImageSize({ width: '50%', height: '50%' })
        .backgroundImagePosition(this.alignment)
        .id('menuBackgroundImagePosition3')
      Button('BackgroundImagePosition')
        .onClick(() => {
          this.index++
          this.alignment = this.alignmentArr[this.index % 9]
        })
    }.height('100%').width('100%')
  }
}

