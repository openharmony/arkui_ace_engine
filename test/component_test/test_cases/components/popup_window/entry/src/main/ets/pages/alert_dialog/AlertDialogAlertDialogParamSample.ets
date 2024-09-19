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
import alertDialogAlertDialogParamTest from '../MyTest/AlertDialogAlertDialogParamTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct AlertDialogAlertDialogParamSample {
  aboutToAppear(): void {
    loadComponentTestEntry(alertDialogAlertDialogParamTest)
  }

  @State dialog: AlertDialogParam = {
    title: 'title',
    subtitle: 'fax',
    message: 'text',
    autoCancel: true,
    cancel: () => {
      this.textList = 'free'
    },
    alignment: DialogAlignment.Center,
    offset: { dx: 0, dy: -20 },
    gridCount: 5,
    maskRect: {
      x: 0,
      y: 0,
      width: '100%',
      height: '100%'
    },
    showInSubWindow: false,
    isModal: true,
    backgroundColor: Color.Yellow,
    backgroundBlurStyle: BlurStyle.Thick
  }
  @State textList: string = 'list'

  build() {
    Column() {
      Text(this.textList)
      Button('AlertDialogAlertDialogParam')
        .onClick(() => {
          AlertDialog.show(this.dialog)
        })
      Button('AlertDialogAlertDialogParam1')
        .onClick(() => {
          this.dialog = {
            title: $r('app.string.dialog_show_title'),
            subtitle: $r('app.string.dialog_show_subtitle'),
            message: $r('app.string.dialog_show_message'),
            autoCancel: true,
            cancel: () => {
              this.textList = 'world'
            },
            alignment: DialogAlignment.CenterStart,
            offset: { dx: '1px', dy: '20px' },
            gridCount: 3,
            maskRect: {
              x: $r('app.integer.dialog_show_mask_rect_x'),
              y: $r('app.integer.dialog_show_mask_rect_y'),
              width: $r('app.string.dialog_show_mask_rect_width'),
              height: $r('app.string.dialog_show_mask_rect_height')
            },
            showInSubWindow: false,
            isModal: true,
            backgroundColor: '#0000ff',
            backgroundBlurStyle: BlurStyle.Regular
          }
        })
      Button('AlertDialogAlertDialogParam2')
        .onClick(() => {
          AlertDialog.show(
            {
              title: 'animator',
              subtitle: 'cat',
              message: 'dog pag pag',
              autoCancel: true,
              confirm: {
                value: 'confirm1',
                action: () => {
                  this.textList = 'tiger'
                }
              },
              alignment: DialogAlignment.Top,
              offset: { dx: $r('app.integer.dialog_show_offset_dx'), dy: $r('app.integer.dialog_show_offset_dy') },
              gridCount: 4,
              showInSubWindow: false,
              isModal: false,
              backgroundColor: 0xFFB6C1,
              backgroundBlurStyle: BlurStyle.Thin
            })
        })
      Button('AlertDialogAlertDialogParam3 ')
        .onClick(() => {
          AlertDialog.show(
            {
              title: 'plant',
              subtitle: 'ferns',
              confirm: {
                value: 'confirm2',
                action: () => {
                  this.textList = 'arg'
                }
              },
              message: 'beautiful',
              autoCancel: false,
              alignment: DialogAlignment.CenterStart,
              offset: { dx: 0, dy: -20 },
              gridCount: 3,
              maskRect: {
                x: 0,
                y: 0,
                width: '100%',
                height: '100%'
              },
              showInSubWindow: false,
              isModal: true,
              backgroundColor: $r('app.color.dialog_show_background_color'),
              backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK
            }
          )
        })
    }
  }
}