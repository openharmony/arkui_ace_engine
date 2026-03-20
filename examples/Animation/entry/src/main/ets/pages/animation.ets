/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import router from '@ohos.router';
@Entry
@Component
struct AnimationExample {
  @State widthSize: number = 250
  @State heightSize: number = 100
  @State rotateAngle: number = 0
  @State count: number = 0
  @State flag: boolean = true
  @State bg: Color = Color.Blue

  build() {
    Column() {
      Column() {
        Button("返回")
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .height('10%')
      .backgroundColor(Color.Orange)
      .justifyContent(FlexAlign.Center)
      Column() {
        Column() {
          Button()
            .margin(30)
            .height(this.heightSize)
            .animation({
              duration: 2000,
              curve: Curve.EaseOut,
              iterations: 1,
              playMode: PlayMode.Normal,
              onFinish: () => {
                this.count--
                if (this.count == 0) {
                  this.bg = Color.Green
                }
              }
            })
            .width(this.widthSize)
            .backgroundColor(this.bg)
          Row() {
            Button('改变高度有动效')
              .onClick(() => {
                this.count++
                if (this.flag) {
                  this.heightSize = 60
                } else {
                  this.heightSize = 100
                }
                this.flag = !this.flag
              })
            Button('改变宽度无动效')
              .onClick(() => {
                if (this.flag) {
                  this.widthSize = 150
                } else {
                  this.widthSize = 250
                }
                this.flag = !this.flag
              })
          }
        }
        .height('45%')
        Column() {
          Button('change rotate angle')
            .onClick(() => {
              this.rotateAngle = 90
            })
            .margin(50)
            .rotate({ angle: this.rotateAngle })
            .animation({
              duration: 1200,
              curve: Curve.Friction,
              delay: 500,
              iterations: -1, // 设置-1表示动画无限循环
              playMode: PlayMode.Alternate,
              expectedFrameRateRange: {
                min: 20,
                max: 120,
                expected: 90,
              }
            })
        }
        .height('45%')
      }
    }.width('100%').margin({ top: 20 })
  }
}