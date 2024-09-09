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
import alertDialogPrimaryButtonTest from '../MyTest/AlertDialogPrimaryButtonTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AlertDialogPrimaryButtonSample {
  @State fontColor: ResourceColor = Color.Green
  @State backGroundColor: ResourceColor = Color.Brown
  @State style: DialogButtonStyle = DialogButtonStyle.HIGHLIGHT
  @State value: ResourceStr = 'button'
  @State test: string = 'dialog1'
  @State isTrue: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(alertDialogPrimaryButtonTest)
  }

  build() {
    Column({ space: 5 }) {
      Text(this.test).id('alertDialogPrimary')
      Button('AlertDialogPrimaryButton1')
        .onClick(() => {
          this.fontColor = $r('app.color.alert_color1')
          this.backGroundColor = $r('app.color.alert_color2')
        })
      Button('AlertDialogPrimaryButton2')
        .onClick(() => {
          this.fontColor = '#1A94C2'
          this.backGroundColor = '#C025BE'
        })
      Button('AlertDialogPrimaryButton3')
        .onClick(() => {
          this.style = DialogButtonStyle.DEFAULT
          this.fontColor = 0xff8207
          this.backGroundColor = 0xff1234
          this.value = $r('app.string.alert_string')
          this.isTrue = !this.isTrue
        })
      Button('AlertDialog')
        .onClick(() => {
          AlertDialog.show(
            {
              title: 'title',
              message: 'alertDialogPrimaryButton',
              primaryButton: {
                enabled: this.isTrue,
                defaultFocus: !this.isTrue,
                style: this.style,
                value: this.value,
                fontColor: this.fontColor,
                backgroundColor: this.backGroundColor,
                action: () => {
                  this.test = 'dialogOne'
                }
              }
            }
          )
        })
        .backgroundColor(0x317aff)
    }.width('100%').margin({ top: 5 })
  }
}