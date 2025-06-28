/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@Builder
export function AlertDialogAvoidBuilder(name: string, param: Object) {
  AlertDialogAvoidExample()
}

@Entry
@Component
struct AlertDialogAvoidExample {
  pathStack: NavPathStack = new NavPathStack()
  @State isShowInSubwindow: boolean = false
  @State placement:DialogAlignment = DialogAlignment.Default

  @Builder
  testComponent() {
    Column({ space: 20 }) {
      Row() {
        Text('placement: ')
        TextPicker({
          range: [
            'Default',
            'Center',
            'Bottom',
            'Top',
          ],
          selected: 0
        })
          .width(100)
          .height(60)
          .selectedTextStyle({ font: { size: 14 } })
          .disappearTextStyle({ font: { size: 14 } })
          .canLoop(false)
          .textStyle({ font: { size: 14 } })
          .defaultPickerItemHeight(20)
          .onChange((value: string | string[], index: number | number[]) => {
            switch (value) {
              case 'Default':
                this.placement = DialogAlignment.Default
                break
              case 'Center':
                this.placement = DialogAlignment.Center
                break
              case 'Bottom':
                this.placement = DialogAlignment.Bottom
                break
              case 'Top':
                this.placement = DialogAlignment.Top
            }
          })
      }

      Button('showAlertDialog_showInSubwindow_false')
        .width('100%')
        .onClick(() => {
          this.getUIContext().showAlertDialog({
            title: 'title',
            subtitle: 'subtitle',
            message: 'text',
            autoCancel: true,
            showInSubWindow: false,
            alignment: this.placement,
            offset: { dx: 0, dy: -20 },
            gridCount: 3,
            buttonDirection: DialogButtonDirection.HORIZONTAL,
            buttons: [
              {
                value: '按钮',
                action: () => {
                  console.info('Callback when button1 is clicked')
                }
              },
              {
                value: '按钮',
                action: () => {
                  console.info('Callback when button2 is clicked')
                }
              },
              {
                value: '按钮',
                enabled: true,
                defaultFocus: true,
                style: DialogButtonStyle.HIGHLIGHT,
                action: () => {
                  console.info('Callback when button3 is clicked')
                }
              },
            ],
            cancel: () => {
              console.info('Closed callbacks')
            }
          })
        })

      Button('showAlertDialog_showInSubwindow_true')
        .width('100%')
        .onClick(() => {
          this.getUIContext().showAlertDialog({
            title: 'title',
            subtitle: 'subtitle',
            message: 'text',
            autoCancel: true,
            showInSubWindow: true,
            alignment: this.placement,
            offset: { dx: 0, dy: -20 },
            gridCount: 3,
            buttonDirection: DialogButtonDirection.HORIZONTAL,
            buttons: [
              {
                value: '按钮',
                action: () => {
                  console.info('Callback when button1 is clicked')
                }
              },
              {
                value: '按钮',
                action: () => {
                  console.info('Callback when button2 is clicked')
                }
              },
              {
                value: '按钮',
                enabled: true,
                defaultFocus: true,
                style: DialogButtonStyle.HIGHLIGHT,
                action: () => {
                  console.info('Callback when button3 is clicked')
                }
              },
            ],
            cancel: () => {
              console.info('Closed callbacks')
            }
          })
        })
    }
  }

  @Builder
  operateButton() {
    Column({ space: 10 }) {
      Button(`showInSubwindow=${!this.isShowInSubwindow}`)
        .width('100%')
        .onClick(() => {
          this.isShowInSubwindow = !this.isShowInSubwindow
        })
    }
    .margin({
      top: 36
    })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column() {
          this.testComponent()
        }
        .padding({
          left: 8,
          right: 8
        })
        .margin({
          bottom: 8
        })
      }
    }
    .title('AlertDialog')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}