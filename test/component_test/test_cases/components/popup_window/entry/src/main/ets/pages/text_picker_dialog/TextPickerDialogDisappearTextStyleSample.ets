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
import textPickerDialogDisappearTextStyleTest from '../MyTest/TextPickerDialogDisappearTextStyleTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextPickerDialogDisappearTextStyleSample {
  @State index: number = -1
  private select: number | number[] = 0
  private fruits: string[] = ['apple1', 'orange2', 'peach3', 'grape4', 'banana5']
  private fontWeightType: FontWeight[] =
    [FontWeight.Lighter, FontWeight.Normal, FontWeight.Regular, FontWeight.Medium, FontWeight.Bold, FontWeight.Bolder]

  aboutToAppear(): void {
    loadComponentTestEntry(textPickerDialogDisappearTextStyleTest)
  }

  build() {
    Row() {
      Column() {
        Button("TextPickerDialogDisappearTextStyle1")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              disappearTextStyle: { color: Color.Red, font: { size: 30, weight: 100 } }
            })
          })
        Button("TextPickerDialogDisappearTextStyle2")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              disappearTextStyle: { color: 0x0000ff, font: { size: '30', weight: this.fontWeightType[this.index] } }
            })
          })
        Button("TextPickerDialogDisappearTextStyle3")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              disappearTextStyle: {
                color: $r('app.color.color_red'),
                font: { size: $r('app.integer.font_size'), weight: '800' }
              }
            })
          })
        Button('ClickToggleWeight')
          .onClick(() => {
            this.index++
            this.index %= 6
          })
      }.width('100%')
    }.height('100%')
  }
}