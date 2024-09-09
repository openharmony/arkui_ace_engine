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
import alertDialogButtonDirectionTest from '../MyTest/AlertDialogButtonDirectionTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AlertDialogButtonDirectionSample {
  @State buttonDirectionType: DialogButtonDirection = DialogButtonDirection.HORIZONTAL

  aboutToAppear(): void {
    loadComponentTestEntry(alertDialogButtonDirectionTest)
  }

  build() {
    Column({ space: 5 }) {
      Button('One Button Dialog')
        .onClick(() => {
          AlertDialog.show(
            {
              message: 'AlertDialogButtonDirection1',
              buttonDirection: DialogButtonDirection.AUTO,
              confirm: {
                value: 'button',
                action: () => {
                  console.info('Button-clicking callback')
                }
              },
            }
          )
        })

        .backgroundColor(0x317aff)
      Button('Two Button Dialog')
        .onClick(() => {
          AlertDialog.show(
            {
              message: 'AlertDialogButtonDirection2',
              buttonDirection: this.buttonDirectionType,
              primaryButton: {
                value: 'cancel',
                action: () => {
                  console.info('Callback when the first button is clicked')
                }
              },
              secondaryButton: {
                value: 'ok',
                action: () => {
                  console.info('Callback when the second button is clicked')
                }
              },
            }
          )
        }).backgroundColor(0x317aff)
      Button('AlertDialogButtonDirection')
        .onClick(() => {
          this.buttonDirectionType = DialogButtonDirection.VERTICAL
        })
    }.width('100%').margin({ top: 5 })
  }
}