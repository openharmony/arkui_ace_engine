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
import actionSheetConfirmTest from '../MyTest/ActionSheetConfirmTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ActionSheetConfirmSample {
  @State enabled1: boolean = true
  @State defaultFocus1: boolean = true
  @State style: DialogButtonStyle = DialogButtonStyle.DEFAULT
  @State value: Resource | string = $r('app.string.actionSheet_confirm_value')
  @State string: string = 'actionText'
  @State string1: string = 'Confirm_Button'

  aboutToAppear(): void {
    loadComponentTestEntry(actionSheetConfirmTest)
  }

  build() {
    Column() {
      Text(this.string)
      Text(this.string1)
      Button('ActionSheetConfirmTest1')
        .onClick(() => {
          ActionSheet.show({
            title: 'title1',
            message: 'message1',
            confirm: {
              enabled: this.enabled1,
              defaultFocus: this.defaultFocus1,
              style: this.style,
              value: this.value,
              action: () => {
                this.string1 = 'Confirm_Button1'
              }
            },
            sheets: [{
              title: 'sheetsTitle11', action: () => {
                this.string = 'actionText1'
              }
            },]
          })
        })
      Button('ActionSheetConfirm1')
        .onClick(() => {
          this.enabled1 = false
          this.defaultFocus1 = false
          this.style = DialogButtonStyle.HIGHLIGHT
          this.value = 'Confirm_String'
        })
    }
  }
}