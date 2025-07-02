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
import { ComponentContent, PromptAction, promptAction } from '@kit.ArkUI'
import { BusinessError} from '@kit.BasicServicesKit'

@Builder
export function CustomDialogAvoidBuilder(name: string, param: Object) {
  CustomDialogAvoidExample()
}

class Params {
  public text: string = ''
  public dialogController?: promptAction.DialogController = new promptAction.DialogController();
  constructor(text: string, dialogController?: promptAction.DialogController) {
    this.text = text
    this.dialogController = dialogController
  }
}

@Builder
function builderText(params: Params) {
  Column() {
    Text('弹窗')
      .fontSize(50)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
    if (params.dialogController != undefined) {
      Button('关闭弹窗')
        .onClick(() => {
          if (params.dialogController != undefined) {
            params.dialogController.close()
          }
        })
    }
  }
}

@CustomDialog
struct CustomDialogExample {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  build() {
    Column() {
      Text('弹窗')
        .fontSize(30)
    }
    .borderRadius(10)
    .height('40%')
    .width('40%')
  }
}

@Entry
@Component
struct CustomDialogAvoidExample {
  pathStack: NavPathStack = new NavPathStack()
  @State isShowInSubwindow: boolean = false
  @State message: string = 'hello'
  @State placement: DialogAlignment = DialogAlignment.Default
  private ctx: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.ctx.getPromptAction()
  private dialogController: promptAction.DialogController = new promptAction.DialogController()
  private customDialogComponentId: number = 0

  onCancel() {
    console.info('Callback when the first button is clicked')
  }

  onAccept() {
    console.info('Callback when the second button is clicked')
  }

  exitApp() {
    console.info('Click the callback in the blank area')
  }

  @Builder
  customDialogComponent() {
    Column () {
      Text('弹窗')
        .fontSize(30)
      Row({ space: 10 }) {
        Button('关闭弹窗')
          .onClick(() => {
            this.promptAction.closeCustomDialog(this.customDialogComponentId)
          })
      }
      .padding(5)
      .justifyContent(FlexAlign.SpaceBetween)
      .borderRadius(10)
      .height('40%')
      .width('40%')
    }
  }

  @Builder
  testComponent() {
    Column() {
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

      Button('promptAction.openCustomDialog')
        .width('100%')
        .onClick(() => {
          let contentNode = new ComponentContent(this.ctx, wrapBuilder(builderText),
            new Params(this.message))
          this.promptAction.openCustomDialog(contentNode, {
            showInSubWindow: this.isShowInSubwindow,
            alignment: this.placement,
            autoCancel: true
          })
            .then(() => {
              console.log('succeed')
            })
            .catch((error: BusinessError) => {
              console.error('OpenCustomDialog error')
            })
          setTimeout(() => {
            this.promptAction.closeCustomDialog(contentNode)
              .then(() => {
                console.log('succeed')
              })
              .catch((error: BusinessError) => {
                console.error('closeCustomDialog error')
              })
          }, 5000)
        })

      Button('openCustomDialogWithController')
        .width('100%')
        .onClick(() => {
          let contentNode = new ComponentContent(this.ctx, wrapBuilder(builderText),
            new Params(this.message, this.dialogController))
          this.promptAction.openCustomDialogWithController(contentNode, this.dialogController, {
            showInSubWindow: this.isShowInSubwindow,
            alignment: this.placement,
            autoCancel: true
          })
            .then(() => {
              console.log('succeed')
            })
            .catch((error: BusinessError) => {
              console.error('openCustomDialogWithController error')
            })
        })

      Button('presentCustomDialog')
        .width('100%')
        .onClick(() => {
          this.promptAction.presentCustomDialog(() => {
            this.customDialogComponent()
          }, this.dialogController, {
            showInSubWindow: this.isShowInSubwindow,
            alignment: this.placement,
            autoCancel: true
          })
            .then((dialogId: number) => {
              this.customDialogComponentId = dialogId
              console.log('succeed')
            })
            .catch((error: BusinessError) => {
              console.error('openCustomDialogWithController error')
            })
        })

      Button('dialogController')
        .width('100%')
        .onClick(() => {
          new CustomDialogController({
            builder: CustomDialogExample({
              cancel: () => {
                this.onCancel()
              },
              confirm: () => {
                this.onAccept()
              }
            }),
            showInSubWindow: this.isShowInSubwindow,
            alignment: this.placement,
            onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
              if (dismissDialogAction.reason == DismissReason.PRESS_BACK) {
                dismissDialogAction.dismiss()
              }
              if (dismissDialogAction.reason == DismissReason.TOUCH_OUTSIDE) {
                dismissDialogAction.dismiss()
              }
            }
          })
          ?.open()
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
    .margin({ top: 36 })
  }

  build() {
    NavDestination() {
      Column() {
        Scroll() {
          Column() {
            this.testComponent()
            Divider()
            this.operateButton()
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
    }
    .title('CustomDialog')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}