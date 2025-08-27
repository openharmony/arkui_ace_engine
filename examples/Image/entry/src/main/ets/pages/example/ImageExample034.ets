/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

/**
 * Demonstrates various Image component modifiers including copyOption, interpolation,
 * fillColor, autoResize, syncLoad, and dynamicRangeMode.
 */
@Entry
@Component
struct Index {
  build() {
    Column({ space: 15 }) {
      // --- copyOption ---
      Row() {
        Text('copyOption')
          .fontSize(16)
          .width(120)

        // None
        Image($r('app.media.sky'))
          .copyOption(CopyOptions.None)
          .height(200)
          .width(200)

        // InApp
        Image($r('app.media.sky'))
          .copyOption(CopyOptions.InApp)
          .height(200)
          .width(200)

        // LocalDevice
        Image($r('app.media.sky'))
          .copyOption(CopyOptions.LocalDevice)
          .height(200)
          .width(200)
      }

      // --- interpolation ---
      Row() {
        Text('interpolation')
          .fontSize(16)
          .width(120)

        // Low
        Image($r('app.media.sky'))
          .interpolation(ImageInterpolation.Low)
          .height(200)
          .width(200)

        // High
        Image($r('app.media.sky'))
          .interpolation(ImageInterpolation.High)
          .height(200)
          .width(200)

        // Medium
        Image($r('app.media.sky'))
          .interpolation(ImageInterpolation.Medium)
          .height(200)
          .width(200)
      }

      // --- fillColor ---
      Row() {
        Text('fillColor')
          .fontSize(16)
          .width(120)

        // Red
        Image($r('app.media.heart'))
          .fillColor(Color.Red)
          .height(100)
          .width(100)

        // 0xffff0000
        Image($r('app.media.heart'))
          .fillColor(0xffff0000)
          .height(100)
          .width(100)

        // RGB string
        Image($r('app.media.heart'))
          .fillColor('rgb(255, 100, 255)')
          .height(100)
          .width(100)
      }

      // --- autoResize ---
      Row() {
        Text('autoResize')
          .fontSize(16)
          .width(120)

        // true
        Image($r('app.media.sky'))
          .autoResize(true)
          .height(100)
          .width(100)

        // false
        Image($r('app.media.sky'))
          .autoResize(false)
          .height(100)
          .width(100)
      }

      // --- syncLoad ---
      Row() {
        Text('syncLoad')
          .fontSize(16)
          .width(120)

        // true
        Image($r('app.media.sky'))
          .syncLoad(true)
          .height(100)
          .width(100)

        // false
        Image($r('app.media.sky'))
          .syncLoad(false)
          .height(100)
          .width(100)
      }

      // --- dynamicRangeMode ---
      Row() {
        Text('dynamicRangeMode')
          .fontSize(16)
          .width(120)

        // STANDARD
        Image($r('app.media.sky'))
          .dynamicRangeMode(DynamicRangeMode.STANDARD)
          .height(100)
          .width(100)

        // HIGH
        Image($r('app.media.sky'))
          .dynamicRangeMode(DynamicRangeMode.HIGH)
          .height(100)
          .width(100)

        // CONSTRAINT
        Image($r('app.media.sky'))
          .dynamicRangeMode(DynamicRangeMode.CONSTRAINT)
          .height(100)
          .width(100)
      }
    }
    .padding(10)
    .height('100%')
    .width('100%')
  }
}