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
import textPickerDialogBackgroundColorTest from '../MyTest/TextPickerDialogBackgroundColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextPickerDialogBackgroundColorSample {
  private select: number | number[] = 0
  private fruits: string[] = ['apple1', 'orange2', 'peach3', 'grape4', 'banana5']

  aboutToAppear(): void {
    loadComponentTestEntry(textPickerDialogBackgroundColorTest)
  }

  build() {
    Row() {
      Column() {
        Button("TextPickerDialogBackgroundColor1")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              backgroundColor: Color.Green
            })
          })
        Button("TextPickerDialogBackgroundColor2")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              backgroundColor: 0x0000ff
            })
          })
        Button("TextPickerDialogBackgroundColor3")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              backgroundColor: $r('app.color.color_red')
            })
          })
        Button("TextPickerDialogBackgroundColor4")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              backgroundColor: '#ffff00'
            })
          })
      }.width('100%')
    }.height('100%')
  }
}