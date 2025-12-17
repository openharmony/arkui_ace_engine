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
'use static'
import { Entry, Text, Column, Component, Button, ClickEvent, ColumnOptions, ResourceStr, $r, Rating } from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Builder
export function RatingStarStyleStaticBuilder(name: string, param: Object) {
  RatingStarStyleStaticExample()
}

@Entry
@Component
struct RatingStarStyleStaticExample {
  @State rating: Double = 3.5;

  build() {
    Column() {
      Text(`设置undefined:`)
        .fontSize(16)
        .width('100%')
      Rating({ rating:3.5 })
        .stars(5)
        .stepSize(0.5)
        .starStyle(undefined)
        .margin(10)
      Text(`设置Resource:`)
        .fontSize(16)
        .width('100%')
      Rating({ rating: this.rating, indicator: false })
        .stars(5)
        .stepSize(0.5)
        .starStyle({
          backgroundUri: $r('app.media.image1'),
          foregroundUri: $r('app.media.image2'),
          secondaryUri: $r('app.media.image3')
        })
        .margin(10)
        .onChange((value: number) => {
          this.rating = value;
        })
      Text('current score is ' + this.rating)
        .fontSize(16)
        .fontColor('rgba(24,36,49,0.60)')
        .margin(10)
    }.width('100%').height('100%').backgroundColor('#F1F3F5')
  }
}