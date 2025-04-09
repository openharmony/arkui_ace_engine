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

@Entry
@Component
struct BadgeExample002 {
  @State badgeCount: number = 1
  @State maxCount: number = 15
  @State badgeSize: number = 20
  @State fontSize: number = 10

  build() {
    Column({ space: 40 }) {
      Badge({
        count: this.badgeCount,
        maxCount: this.maxCount,
        style: {
          fontSize: this.fontSize,
          badgeSize: this.badgeSize
        },
        position: BadgePosition.RightTop,
      }) {
        Image($r('app.media.startIcon'))
          .width(50)
          .height(50)
      }
      .width(55)

      Button('count+1')
        .onClick(() => {
          this.badgeCount += 1
        })
        .width(250)
        .height(40)
        .fontSize(9)
      Button('count-1')
        .onClick(() => {
          this.badgeCount -= 1
        })
        .width(250)
        .height(40)
        .fontSize(9)
      Button('count+10')
        .onClick(() => {
          this.badgeCount += 10
        })
        .width(250)
        .height(40)
        .fontSize(9)
      Button('count-10')
        .onClick(() => {
          this.badgeCount -= 10
        })
        .width(250)
        .height(40)
        .fontSize(9)

      Button('max+1')
        .onClick(() => {
          this.maxCount += 1
        })
        .width(250)
        .height(40)
        .fontSize(9)
      Button('max-1')
        .onClick(() => {
          this.maxCount -= 1
        })
        .width(250)
        .height(40)
        .fontSize(9)
      Button('max+10')
        .onClick(() => {
          this.maxCount += 10
        })
        .width(250)
        .height(40)
        .fontSize(9)
      Button('max-10')
        .onClick(() => {
          this.maxCount -= 10
        })
        .width(250)
        .height(40)
        .fontSize(9)
    }
    .margin({ top: 20 })
  }
}