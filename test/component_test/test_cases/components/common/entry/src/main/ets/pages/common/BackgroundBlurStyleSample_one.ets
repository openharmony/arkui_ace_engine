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

import backgroundBlurStyleTest from '../MyTest/BackgroundBlurStyleTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BackgroundBlurStyleSample {
  blurStyle: BlurStyle = BlurStyle.BACKGROUND_THICK

  aboutToAppear(): void {
    loadComponentTestEntry(backgroundBlurStyleTest)
  }

  build() {
    Column() {
      Scroll() {
        Text('backgroundBlurStyleTest1')
      }.backgroundImage($r('app.media.app_icon'))
      .backgroundBlurStyle(BlurStyle.Thin, {
        colorMode: ThemeColorMode.SYSTEM,
        adaptiveColor: AdaptiveColor.DEFAULT,
        blurOptions: { grayscale: [12, 103] }
      })
      .id('scrollBackgroundBlurStyle1')

      Scroll() {
        Text('backgroundBlurStyleTest2')
      }.backgroundImage($r('app.media.app_icon'))
      .backgroundBlurStyle(BlurStyle.Regular, { colorMode: ThemeColorMode.LIGHT, adaptiveColor: AdaptiveColor.AVERAGE })
      .id('scrollBackgroundBlurStyle2')

      Scroll() {
        Text('backgroundBlurStyleTest3')
      }.backgroundImage($r('app.media.app_icon'))
      .backgroundBlurStyle(BlurStyle.Thick, { colorMode: ThemeColorMode.DARK })
      .id('scrollBackgroundBlurStyle3')

      Scroll() {
        Text('backgroundBlurStyleTest4')
      }.backgroundImage($r('app.media.app_icon'))
      .backgroundBlurStyle(BlurStyle.BACKGROUND_THIN)
      .id('scrollBackgroundBlurStyle4')

      Scroll() {
        Text('backgroundBlurStyleTest5')
      }.backgroundImage($r('app.media.app_icon'))
      .backgroundBlurStyle(BlurStyle.BACKGROUND_REGULAR)
      .id('scrollBackgroundBlurStyle5')

      Scroll() {
        Text('backgroundBlurStyleTest6')
      }.backgroundImage($r('app.media.app_icon'))
      .backgroundBlurStyle(BlurStyle.BACKGROUND_THICK)
      .id('scrollBackgroundBlurStyle6')

      Scroll() {
        Text('backgroundBlurStyleTest7')
      }.backgroundImage($r('app.media.app_icon'))
      .backgroundBlurStyle(BlurStyle.BACKGROUND_ULTRA_THICK)
      .id('scrollBackgroundBlurStyle7')

      Scroll() {
        Text('backgroundBlurStyleTest8')
      }.backgroundImage($r('app.media.app_icon'))
      .backgroundBlurStyle(BlurStyle.NONE)
      .id('scrollBackgroundBlurStyle8')
    }
  }
}

