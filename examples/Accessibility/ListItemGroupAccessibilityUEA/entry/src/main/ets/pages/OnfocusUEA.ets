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

@Entry
@Component
struct FocusEventExample {
  @State oneButtonColor: string = '#FFC0CB'
  @State twoButtonColor: string = '#87CEFA'
  @State threeButtonColor: string = '#90EE90'
  @State fourButtonColor: string = '#E9C2A6'
  @State fiveButtonColor: string = '#EAEAAE'
  @State sixButtonColor: string = '#DB70DB'
  @State color_: string | number | Color | undefined = '#E9C2A6';

  build() {
    Column({ space: 20 }) {
      // 通过外接键盘的上下键可以让焦点在三个按钮间移动，按钮获焦时颜色变化，失焦时变回原背景色
      Row() {
        Button('First Button')
          .backgroundColor(this.oneButtonColor)
          .width(150)
          .height(70)
          .fontColor(Color.Black)
          .focusable(true)
          .onFocus(() => {
            this.oneButtonColor = '#FF0000'
          })
          .onBlur(() => {
            this.oneButtonColor = '#FFC0CB'
          })
          .onClick(() => {
            this.oneButtonColor = '#87CEFA'
          })
        Button('Second Button')
          .backgroundColor(this.twoButtonColor)
          .width(150)
          .height(70)
          .fontColor(Color.Black)
          .focusable(true)
          .onFocus(() => {
            this.twoButtonColor = '#FF0000'
          })
          .onBlur(() => {
            this.twoButtonColor = '#87CEFA'
          })
      }

      Row() {
        Button('Third Button')
          .backgroundColor(this.threeButtonColor)
          .width(150)
          .height(70)
          .fontColor(Color.Black)
          .focusable(true)
          .onFocus(() => {
            this.threeButtonColor = '#FF0000'
          })
          .onBlur(() => {
            this.threeButtonColor = '#90EE90'
          })
        Button('Four Button')
          .backgroundColor(this.fourButtonColor)
          .width(150)
          .height(70)
          .fontColor(Color.Black)
          .focusable(true)
          .onFocus(() => {
            this.fourButtonColor = '#FF0000'
          })
          .onBlur(() => {
            this.fourButtonColor = '#E9C2A6'
          })
      }

      Row() {
        Button('Five Button')
          .backgroundColor(this.fiveButtonColor)
          .width(150)
          .height(70)
          .fontColor(Color.Black)
          .focusable(true)
          .onFocus(() => {
            this.fiveButtonColor = '#FF0000'
          })
          .onBlur(() => {
            this.fiveButtonColor = '#EAEAAE'
          })
        Button('Six Button')
          .backgroundColor(this.sixButtonColor)
          .width(150)
          .height(70)
          .fontColor(Color.Black)
          .focusable(true)
          .onFocus(() => {
            this.sixButtonColor = '#FF0000'
          })
          .onBlur(() => {
            this.sixButtonColor = '#DB70DB'
          })
      }
    }.width('100%').margin({ top: 20 })
  }
}