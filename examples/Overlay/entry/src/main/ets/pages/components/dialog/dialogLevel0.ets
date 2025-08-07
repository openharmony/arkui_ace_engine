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

import promptAction from '@ohos.promptAction'
import { UIContext } from '@kit.ArkUI'

@Builder
export function DialogLevelOBuilder(name: string, param: Object) {
  DialogLevel0Example()
}

@CustomDialog
struct customDialogNode {
  controller?: CustomDialogController

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ content: '菜单选项' })
      MenuItem({ content: '菜单选项' })
      MenuItem({ content: '菜单选项' })
    }
  }

  @State isShown: boolean = false;

  build() {
    Column() {
      Text('Custom dialog').fontSize(10)
      TextInput()
      Row() {
        Button('确认')

          .bindMenu(this.isShown, this.MyMenu,
            {
              aboutToDisappear: () => {
                console.log('----------menu aboutToDisappear');
                this.isShown = false;
              }
            , showInSubWindow: false
            },
          )
          .onClick(() => {
            this.controller?.close()
          })
          .onClick(() => {
            this.isShown = true
          })
        Blank().width(50)
        Button('取消').onClick(() => {

          this.controller?.close()
        })
      }
    }.height(undefined).padding(5)
  }
}

let customDialogIds: number[] = [];

@Builder
function customDialogBuilder(uiContext: UIContext) {
  Column() {
    Text('Custom dialog Message').fontSize(10)
    Row() {
      Button('确认').onClick(() => {

        if (customDialogIds.length) {
          let id = customDialogIds.pop();
          uiContext.getPromptAction().closeCustomDialog(id)
          console.log('---------id:' + id);
        }
      })
      Blank().width(50)
      Button('取消').onClick(() => {
        if (customDialogIds.length) {
          uiContext.getPromptAction().closeCustomDialog(customDialogIds.pop())
        }
      })
    }
  }
  .height(1000)
  .padding(5)
}


@Entry
@Component
struct DialogLevel0Example {
  pathStack: NavPathStack = new NavPathStack()
  private alignLen: number = Object.keys(DialogAlignment).length / 2;
  @State alignment: DialogAlignment = DialogAlignment.Default;
  @State isSubwindow: boolean = true
  @State isModal: boolean = true
  @State isEnableHoverMode: boolean | undefined = false;
  @State hoverModeArea: number | undefined = 0
  @State isShown: boolean = false;
  alignmentKeys: string[] = Object.keys(DialogAlignment).slice(this.alignLen)
  alignments: DialogAlignment[] = [DialogAlignment.Default,
    DialogAlignment.Top, DialogAlignment.TopStart, DialogAlignment.TopEnd,
    DialogAlignment.Center, DialogAlignment.CenterStart, DialogAlignment.CenterEnd,
    DialogAlignment.Bottom, DialogAlignment.BottomStart, DialogAlignment.BottomEnd];
  alignIdx: number = 0;

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ content: '菜单选项' })
      MenuItem({ content: '菜单选项' })
      MenuItem({ content: '菜单选项' })
    }
  }

  @Builder
  customDialogBuilder() {
    Column() {
      Text('Custom dialog Message').fontSize(10)
      Row() {
        Button('确认').onClick(() => {

          if (customDialogIds.length) {
            let id = customDialogIds.pop();
            this.getUIContext().getPromptAction().closeCustomDialog(id)
            console.log('---------id:' + id);
          }
        })
        Blank().width(50)
        Button('取消').onClick(() => {
          if (customDialogIds.length) {
            this.getUIContext().getPromptAction().closeCustomDialog(customDialogIds.pop())
          }
        })
      }
    }.height(1000).padding(5)
  }

  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: customDialogNode(),
    showInSubWindow: this.isSubwindow,
    alignment: this.alignment,
    isModal: this.isModal,
    enableHoverMode: this.isEnableHoverMode,
    hoverModeArea: this.hoverModeArea,
    focusable:true,
  })

  updateDialog() {
    this.alignment = this.alignments[this.alignIdx % this.alignments.length]
    this.dialogController = new CustomDialogController({
      builder: customDialogNode(),
      showInSubWindow: this.isSubwindow,
      alignment: this.alignment,
      isModal: this.isModal,
      enableHoverMode: this.isEnableHoverMode,
      hoverModeArea: this.hoverModeArea
    })
  }

  build() {
    NavDestination() {
      Scroll() {
        Column() {
          Row() {
            Text(`subWindow：${this.isSubwindow}`)
            Button('true')
              .margin(5)
              .onClick(() => {
                this.isSubwindow = true;
                this.updateDialog()
              })
            Button('false')
              .margin(5)
              .onClick(() => {
                this.isSubwindow = false;
                this.updateDialog()
              })
          }.margin(5)

          Row() {
            Text(`isModal：${this.isModal}`)
            Button('true')
              .margin(5)
              .onClick(() => {
                this.isModal = true;
                this.updateDialog()
              })
            Button('false')
              .margin(5)
              .onClick(() => {
                this.isModal = false;
                this.updateDialog()
              })
          }.margin(5)


          Row() {
            Text(`hoverMode：${this.isEnableHoverMode}`)
            Button('true')
              .margin(5)
              .onClick(() => {
                this.isEnableHoverMode = true;
                this.updateDialog()
              })
            Button('false')
              .margin(5)
              .onClick(() => {
                this.isEnableHoverMode = false;
                this.updateDialog()
              })
            Button('undefined')
              .margin(5)
              .onClick(() => {
                this.isEnableHoverMode = undefined;
                this.updateDialog()
              })
          }
          .margin(5)

          Row() {
            Text(`hoverModeArea：${this.hoverModeArea}`)
            Button('Top')
              .margin(5)
              .onClick(() => {
                this.hoverModeArea = 0;
                this.updateDialog()
              })
            Button('Bottom')
              .margin(5)
              .onClick(() => {
                this.hoverModeArea = 1;
                this.updateDialog()
              })
            Button('undefined')
              .margin(5)
              .onClick(() => {
                this.hoverModeArea = undefined;
                this.updateDialog()
              })
          }
          .margin(5)

          Row() {
            Text(`对齐方式：${this.alignmentKeys[this.alignment]}`)
            Button('++1')
              .margin(5)
              .onClick(() => {
                this.alignIdx = this.alignments.indexOf(this.alignment) + 1 + this.alignments.length
                this.updateDialog()
              })
            Button('--1')
              .margin(5)
              .onClick(() => {
                this.alignIdx = this.alignments.indexOf(this.alignment) - 1 + this.alignments.length
                this.updateDialog()
              })
          }

          Column({ space: 6 }) {
            Button('AlertDialog')
              .onClick(() => {
                AlertDialog.show(
                  {
                    title: 'title',
                    subtitle: 'subtitle',
                    message: 'text',
                    buttonDirection: DialogButtonDirection.HORIZONTAL,
                    buttons: [
                      {
                        value: '按钮1', action: () => {
                        promptAction.showToast({
                          message: 'toast',
                          offset: { dx: 0, dy: 100 },
                          alignment: Alignment.Top,
                          backgroundColor: Color.Black
                        })
                      }
                      },
                      {
                        value: '按钮2', action: () => {
                      }
                      },
                    ],
                    cancel: () => {
                      console.log('----------cancel')
                    },
                    autoCancel: false,
                    showInSubWindow: this.isSubwindow,
                    alignment: this.alignment,
                    isModal: this.isModal,
                    enableHoverMode: this.isEnableHoverMode,
                    hoverModeArea: this.hoverModeArea,
                    onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
                      console.log('----------onwilldismiss');
                      dismissDialogAction.dismiss();
                    }
                  }
                )
              })
              .backgroundColor(0x317aff)

            Button('CustomDialogController')
              .bindMenu(this.MyMenu,
                {
                  aboutToDisappear: () => {
                    this.isShown = false;
                  }
                })
              .onClick(() => {
                if (this.dialogController != null) {
                  this.dialogController.open()
                  setTimeout(() => {
                  }, 1000)
                }
              })
              .backgroundColor(0x317aff)

            Button('ShowDialog')
              .onClick(() => {
                promptAction.showDialog({
                  title: 'Title Info',
                  message: 'Message Info',
                  buttons: [
                    { text: 'button1', color: '#000000' },
                    { text: 'button2', color: '#000000' },
                  ],
                  showInSubWindow: this.isSubwindow,
                  alignment: this.alignment,
                  isModal: this.isModal,
                  enableHoverMode: this.isEnableHoverMode,
                  hoverModeArea: this.hoverModeArea
                })
              })
              .backgroundColor(0x317aff)

            Button('OpenCustomDialog')
              .onClick(() => {
                this.getUIContext().getPromptAction().openCustomDialog({
                  builder: () => {
                    this.customDialogBuilder()
                  },
                  showInSubWindow: this.isSubwindow,
                  alignment: this.alignment,
                  isModal: this.isModal,
                  enableHoverMode: this.isEnableHoverMode,
                  hoverModeArea: this.hoverModeArea,
                  onWillDismiss: (dismissAction: DismissDialogAction) => {
                    dismissAction.dismiss();
                  }
                }).then((id: number) => {
                  customDialogIds.push(id)
                  setTimeout(() => {
                    this.dialogController?.open()
                    promptAction.closeCustomDialog(id)
                  }, 1000)
                  setTimeout(() => {
                    promptAction.closeCustomDialog(id)
                  }, 2000)
                })
              })
              .backgroundColor(0x317aff)
            TextInput()
            Button('bind menu')
              .bindMenu(this.isShown, this.MyMenu,
                {
                  aboutToDisappear: () => {
                    this.isShown = false;
                  }
                , showInSubWindow: this.isSubwindow
                },
              )
              .onClick(() => {
                this.isShown = true
              })
          }
        }
        .width('100%')
        .margin({ top: 5 })
      }
      .height('100%')
      .border({ width: 1, color: Color.Red })
    }
    .title('DialogLevel0')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}