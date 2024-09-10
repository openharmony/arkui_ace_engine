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
import alertDialogButtonsTest from '../MyTest/AlertDialogButtonsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AlertDialogButtonsSample {
  @State textType: string = 'button end'

  aboutToAppear(): void {
    loadComponentTestEntry(alertDialogButtonsTest)
  }

  build() {
    Column({ space: 5 }) {
      Button('One Button Dialog')
        .onClick(() => {
          AlertDialog.show(
            {
              message: 'text',
              buttons: [
                {
                  value: '按钮1',
                  style: DialogButtonStyle.DEFAULT,
                  fontColor: Color.Green,
                  backgroundColor: Color.Gray,
                  action: () => {
                    this.textType = 'button1 ending'
                  }
                },
                {
                  value: $r('app.string.alert_dialog_buttons_value'),
                  fontColor: 0x8B008B,
                  backgroundColor: 0xFFE4C4,
                  action: () => {
                    this.textType = 'button2 ending'
                  }
                },
                {
                  value: '按钮3',
                  enabled: true,
                  defaultFocus: true,
                  style: DialogButtonStyle.HIGHLIGHT,
                  fontColor: 'rgb(255,105,180)',
                  backgroundColor: $r('sys.color.ohos_id_color_text_hyperlink'),
                  action: () => {
                    this.textType = 'button3 ending'
                  }
                },
                {
                  value: '按钮4',
                  fontColor: $r('sys.color.ohos_id_color_text_hyperlink'),
                  backgroundColor: 'rgb(255,240,245)',
                  action: () => {
                    this.textType = 'button4 ending'
                  }
                },
              ],
              cancel: () => {
                console.info('Closed callbacks')
              }
            }
          )
        }).backgroundColor(0x317aff)
      Text(this.textType)
    }.width('100%').margin({ top: 5 })
  }
}