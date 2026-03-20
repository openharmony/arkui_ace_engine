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
struct AnimateToExample1 {
  @State widthSize: number = 250
  @State heightSize: number = 100
  @State rotateAngle: number = 0
  @State count: number = 0
  @State bg: Color = Color.Blue
  private flag: boolean = true

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
        Button('change size')
          .width(this.widthSize)
          .height(this.heightSize)
          .margin(30)
          .onClick(() => {
            if (this.flag) {
              // 建议使用this.getUIContext()?.animateTo()
              this.count++
              animateTo({
                duration: 2000,
                curve: Curve.EaseOut,
                iterations: 1,
                playMode: PlayMode.Normal,
                onFinish: () => {
                  this.count--
                  if (this.count == 0 && this.widthSize == 150 && this.heightSize == 60) {
                    this.bg = Color.Green
                  }
                }
              }, () => {
                this.widthSize = 150
                this.heightSize = 60
              })
            } else {
              // 建议使用this.getUIContext()?.animateTo()
              animateTo({}, () => {
                this.widthSize = 250
                this.heightSize = 100
              })
            }
            this.flag = !this.flag
          })
          .backgroundColor(this.bg)
      }
      .height('45%')

      Button('出现默认执行动画，点击停止')
        .margin(50)
        .rotate({ x: 0, y: 0, z: 1, angle: this.rotateAngle })
        .onAppear(() => {
          // 组件出现时开始做动画
          // 建议使用this.getUIContext()?.animateTo()
          animateTo({
            duration: 1200,
            curve: Curve.Friction,
            delay: 500,
            iterations: -1, // 设置-1表示动画无限循环
            playMode: PlayMode.Alternate,
            expectedFrameRateRange: {
              min: 10,
              max: 120,
              expected: 60,
            }
          }, () => {
            this.rotateAngle = 90
          })
        })
        .onClick(() => {
          // 建议使用this.getUIContext()?.animateTo()
          animateTo({ duration: 0 }, () => {
            // this.rotateAngle之前为90，在duration为0的动画中修改属性，可以停止该属性之前的动画，按新设置的属性显示
            this.rotateAngle = 0
          })
        })
    }.width('100%').margin({ top: 5 })
  }
}