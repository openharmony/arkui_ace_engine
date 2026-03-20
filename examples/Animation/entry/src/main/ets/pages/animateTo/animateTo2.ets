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
struct AnimateToExample2 {
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
      Button('change size')
        .width(this.widthSize)
        .height(this.heightSize)
        .margin(30)
        .onClick(() => {
          // 建议使用this.getUIContext()?.animateTo()
          this.getUIContext()?.animateTo({
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
          }, () => {
            this.count++
            if (this.flag) {
              this.widthSize = 150
              this.heightSize = 60
            } else {
              this.widthSize = 250
              this.heightSize = 100
            }
            this.flag = !this.flag
          })
        })
        .backgroundColor(this.bg)
    }.width('100%').margin({ top: 5 })
  }
}