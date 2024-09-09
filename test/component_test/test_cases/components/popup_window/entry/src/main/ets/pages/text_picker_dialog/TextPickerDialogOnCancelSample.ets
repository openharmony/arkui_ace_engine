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
import textPickerDialogOnCancelTest from '../MyTest/TextPickerDialogOnCancelTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextPickerDialogOnCancelSample {
  private select: number | number[] = 0
  private fruits: string[] = ['apple1', 'orange2', 'peach3', 'grape4', 'banana5']
  @State textPickerDialogOnCancelText: string = 'show'

  aboutToAppear(): void {
    loadComponentTestEntry(textPickerDialogOnCancelTest)
  }

  build() {
    Row() {
      Column() {
        Button("TextPickerDialogOnCancel")
          .margin(20)
          .onClick(() => {
            TextPickerDialog.show({
              range: this.fruits,
              selected: this.select,
              onCancel: () => {
                this.textPickerDialogOnCancelText = 'TextPickerDialogOnCancel'
              }
            })
          })
        Text(this.textPickerDialogOnCancelText).id('textPickerDialogOnCancelText')
      }.width('100%')
    }.height('100%')
  }
}