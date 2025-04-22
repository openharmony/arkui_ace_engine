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

import { ComponentContent, LevelOrder, PromptAction, promptAction } from '@kit.ArkUI'
import { ParamOption, SetParam } from '../base/ParamOption'

class Params {
  public text: string = ''
  public dialogController: promptAction.CommonController = new promptAction.DialogController()
  constructor(text: string, dialogController: promptAction.CommonController) {
    this.text = text
    this.dialogController = dialogController
  }
}

@Builder
function buildText(params: Params) {
  Column({ space: 5 }) {
    Text(params.text)
      .fontSize(30)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
    Button('点我关闭弹窗')
      .onClick(() => {
        if (params.dialogController !== undefined) {
          params.dialogController.close()
        }
      })
  }
  .width(300)
  .height(200)
  .backgroundColor('#FFF0F0F0')
}

@CustomDialog
@Component
struct CustomDialogExample {
  title: string = '弹窗'
  controller?: CustomDialogController
  private ctx: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.ctx.getPromptAction()

  textInputCtrl: TextInputController = new TextInputController()
  @State inputValue: string = ''
  @Builder CustomKeyboardBuilder() {
    Column() {
      Button('X')
        .onClick(() => {
          this.textInputCtrl.stopEditing()
        })
      Grid() {
        ForEach([ 1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#' ], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.inputValue += item
            })
          }
        })
      }
      .maxCount(3)
      .columnsGap(10)
      .rowsGap(10)
      .padding(5)
    }
    .backgroundColor(Color.Gray)
    .height(400)
  }

  build() {
    Column() {
      Text(this.title)
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
      TextInput({ controller: this.textInputCtrl, text: this.inputValue })
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .margin(10)
        .border({ width: 1 })
        .height('48vp')
        .onChange(() => {
          let topOrder: LevelOrder = this.promptAction.getTopOrder();
          if (topOrder === undefined) {
            console.error('topOrder: ' + topOrder);
          } else {
            console.error('topOrder: ' + topOrder.getOrder());
          }

          let bottomOrder: LevelOrder = this.promptAction.getBottomOrder();
          if (bottomOrder === undefined) {
            console.error('bottomOrder: ' + bottomOrder);
          } else {
            console.error('bottomOrder: ' + bottomOrder.getOrder());
          }
        })
      Button('点我关闭弹窗')
        .onClick(() => {
          let ctrl: PromptActionDialogController = this.getDialogController()
          if (ctrl !== undefined) {
            ctrl.close()
          }
        })
    }
    .height(200)
    .backgroundColor('#FFF0F0F0')
  }
}

@Builder
export function DialogLevelOrderBuilder(name: string, param: Object) {
  DialogLevelOrder()
}

@Component
export struct DialogLevelOrder {
  private message1 = '弹窗1'
  private message2 = '弹窗2'
  private ctx: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.ctx.getPromptAction()

  textInputCtrl: TextInputController = new TextInputController()
  @State inputValue: string = ''
  @Builder CustomKeyboardBuilder() {
    Column() {
      Button('X')
        .onClick(() => {
          this.textInputCtrl.stopEditing()
        })
      Grid() {
        ForEach([ 1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#' ], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.inputValue += item
            })
          }
        })
      }
      .maxCount(3)
      .columnsGap(10)
      .rowsGap(10)
      .padding(5)
    }
    .backgroundColor(Color.Gray)
    .height(400)
  }

  @State customDialogIds: number[] = []
  @State dialogIdIndex: number = 0
  @Builder customDialogComponent(title: string, idIndex: number = 0) {
    Column() {
      Text(title).fontSize(30)
      TextInput({ controller: this.textInputCtrl, text: this.inputValue })
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .margin(10)
        .border({ width: 1 })
        .height('48vp')
        .onChange(() => {
          let topOrder: LevelOrder = this.promptAction.getTopOrder();
          if (topOrder === undefined) {
            console.error('topOrder: ' + topOrder);
          } else {
            console.error('topOrder: ' + topOrder.getOrder());
          }

          let bottomOrder: LevelOrder = this.promptAction.getBottomOrder();
          if (bottomOrder === undefined) {
            console.error('bottomOrder: ' + bottomOrder);
          } else {
            console.error('bottomOrder: ' + bottomOrder.getOrder());
          }
        })
      Button('点击关闭弹窗')
        .onClick(() => {
          this.promptAction.closeCustomDialog(this.customDialogIds[idIndex])
          this.customDialogIds[idIndex] = null!
        })
    }
    .height(200)
    .padding(5)
    .justifyContent(FlexAlign.SpaceBetween)
    .backgroundColor('#FFF0F0F0')
  }

  @State openInterface1: string = 'openCustomDialog'
  private setOpenInterface1: SetParam[] = [{
    title: 'open',
    func: () => {
      this.openInterface1 = 'openCustomDialog'
    }
  }, {
    title: 'openCtrl',
    func: () => {
      this.openInterface1 = 'openCustomDialogWithController'
    }
  }, {
    title: 'present',
    func: () => {
      this.openInterface1 = 'presentCustomDialog'
    }
  }, {
    title: 'ctrlOpen',
    func: () => {
      this.openInterface1 = 'CustomDialogController'
    }
  }, {
    title: 'show',
    func: () => {
      this.openInterface1 = 'showDialog'
    }
  }, {
    title: 'actionSheet',
    func: () => {
      this.openInterface1 = 'showActionSheet'
    }
  }, {
    title: 'alertDialog',
    func: () => {
      this.openInterface1 = 'showAlertDialog'
    }
  }]

  @State levelOrder1: LevelOrder = LevelOrder.clamp(undefined)
  private setLevelOrder1: SetParam[] = [{
    title: '-100000',
    func: () => {
      this.levelOrder1 = LevelOrder.clamp(-100000)
    }
  }, {
    title: '-5',
    func: () => {
      this.levelOrder1 = LevelOrder.clamp(-5)
    }
  }, {
    title: 'undefined',
    func: () => {
      this.levelOrder1 = LevelOrder.clamp(undefined)
    }
  }, {
    title: '1.41',
    func: () => {
      this.levelOrder1 = LevelOrder.clamp(1.41)
    }
  }, {
    title: '100000',
    func: () => {
      this.levelOrder1 = LevelOrder.clamp(100000)
    }
  }]

  @State openInterface2: string = 'openCustomDialog'
  private setOpenInterface2: SetParam[] = [{
    title: 'open',
    func: () => {
      this.openInterface2 = 'openCustomDialog'
    }
  }, {
    title: 'openCtrl',
    func: () => {
      this.openInterface2 = 'openCustomDialogWithController'
    }
  }, {
    title: 'present',
    func: () => {
      this.openInterface2 = 'presentCustomDialog'
    }
  }, {
    title: 'ctrlOpen',
    func: () => {
      this.openInterface2 = 'CustomDialogController'
    }
  }, {
    title: 'show',
    func: () => {
      this.openInterface2 = 'showDialog'
    }
  }, {
    title: 'actionSheet',
    func: () => {
      this.openInterface2 = 'showActionSheet'
    }
  }, {
    title: 'alertDialog',
    func: () => {
      this.openInterface2 = 'showAlertDialog'
    }
  }]

  @State levelOrder2: LevelOrder = LevelOrder.clamp(undefined)
  private setLevelOrder2: SetParam[] = [{
    title: '-100000',
    func: () => {
      this.levelOrder2 = LevelOrder.clamp(-100000)
    }
  }, {
    title: '-5',
    func: () => {
      this.levelOrder2 = LevelOrder.clamp(-5)
    }
  }, {
    title: 'undefined',
    func: () => {
      this.levelOrder2 = LevelOrder.clamp(undefined)
    }
  }, {
    title: '1.41',
    func: () => {
      this.levelOrder2 = LevelOrder.clamp(1.41)
    }
  }, {
    title: '100000',
    func: () => {
      this.levelOrder2 = LevelOrder.clamp(100000)
    }
  }]

  openDialog(title: string, openInterface: string, options: promptAction.BaseDialogOptions) {
    switch (openInterface) {
      case 'openCustomDialog': {
        this.promptAction.openCustomDialog({
          builder: () => {
            this.customDialogComponent(title, this.dialogIdIndex)
          },
          isModal: options.isModal,
          levelOrder: options.levelOrder,
          focusable: options.focusable,
          showInSubWindow: options.showInSubWindow,
        }).then((dialogId: number) => {
          this.customDialogIds[this.dialogIdIndex] = dialogId
          this.dialogIdIndex++
        })
        break
      }
      case 'openCustomDialogWithController': {
        let dialogController: promptAction.CommonController = new promptAction.DialogController()
        let contentNode: ComponentContent<Object> = new ComponentContent(this.ctx, wrapBuilder(buildText),
          new Params(title, dialogController));
        this.promptAction.openCustomDialogWithController(contentNode, dialogController, options)
        break
      }
      case 'presentCustomDialog': {
        let dialogController: promptAction.CommonController = new promptAction.DialogController()
        this.promptAction.presentCustomDialog(() => {
          this.customDialogComponent(title, this.dialogIdIndex)
        }, dialogController, options).then((dialogId: number) => {
          this.customDialogIds[this.dialogIdIndex] = dialogId
          this.dialogIdIndex++
        })
        break
      }
      case 'CustomDialogController': {
        let customDialogController: CustomDialogController = new CustomDialogController({
          builder: CustomDialogExample({ title: title }),
          isModal: options.isModal,
          levelOrder: options.levelOrder,
          focusable: options.focusable,
          showInSubWindow: options.showInSubWindow,
        })
        customDialogController.open()
        break
      }
      case 'showDialog': {
        this.promptAction.showDialog({
          title: title,
          message: '层级: ' + options.levelOrder?.getOrder(),
          isModal: options.isModal,
          levelOrder: options.levelOrder,
          showInSubWindow: options.showInSubWindow,
          backgroundColor: '#FFF0F0F0',
          buttons: [{
            text: 'button1',
            color: '#000000'
          }, {
            text: 'button2',
            color: '#000000'
          }]
        })
        break
      }
      case 'showActionSheet': {
        this.ctx.showActionSheet({
          title: title,
          message: '层级: ' + options.levelOrder?.getOrder(),
          isModal: options.isModal,
          levelOrder: options.levelOrder,
          showInSubWindow: options.showInSubWindow,
          backgroundColor: '#FFF0F0F0',
          confirm: {
            defaultFocus: true,
            value: 'Confirm button',
            action: () => {
              console.info('ActionSheet action')
            }
          },
          cancel: () => {
            console.info('ActionSheet cancel')
          },
          sheets: [{
            title: 'apples',
            action: () => {
              console.info('apples')
            }
          }, {
            title: 'bananas',
            action: () => {
              console.info('bananas')
            }
          }]
        })
        break
      }
      case 'showAlertDialog': {
        this.ctx.showAlertDialog({
          title: title,
          message: '层级: ' + options.levelOrder?.getOrder(),
          isModal: options.isModal,
          levelOrder: options.levelOrder,
          showInSubWindow: options.showInSubWindow,
          backgroundColor: '#FFF0F0F0',
          confirm: {
            defaultFocus: true,
            value: 'Confirm button',
            action: () => {
              console.info('AlertDialog action')
            }
          },
          cancel: () => {
            console.info('AlertDialog cancel')
          }
        })
        break
      }
    }
  }

  @State isShowMenu1: boolean = false
  @State isShowMenu2: boolean = false
  @State isShowMenu3: boolean = false
  private iconStr: ResourceStr = $r('app.media.app_icon')
  private iconStr2: ResourceStr = $r('app.media.app_icon')
  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项',
        endIcon: this.iconStr2,
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: '菜单选项',
          endIcon: this.iconStr2,
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '菜单选项',
          endIcon: this.iconStr2,
        })
      }
      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项',
      })
    }
    .onDisAppear(() => {
      this.isShowMenu1 = false
      this.isShowMenu2 = false
      this.isShowMenu3 = false
    })
  }

  @State isShowPopup1: boolean = false
  @State isShowPopup2: boolean = false
  @State isShowPopup3: boolean = false
  private popupOptions: PopupOptions = {
    message: 'This is a popup with PopupOptions',
    placementOnTop: true,
    showInSubWindow: false,
    primaryButton: {
      value: 'confirm',
      action: () => {
        console.info('confirm Button click')
        this.isShowPopup1 = false
        this.isShowPopup2 = false
        this.isShowPopup3 = false
      }
    },
    // 第二个按钮
    secondaryButton: {
      value: 'cancel',
      action: () => {
        console.info('cancel Button click')
        this.isShowPopup1 = false
        this.isShowPopup2 = false
        this.isShowPopup3 = false
      }
    },
    onStateChange: (e) => {
      if (!e.isVisible) {
        this.isShowPopup1 = false
        this.isShowPopup2 = false
        this.isShowPopup3 = false
      }
    }
  }

  @State isShowSheet1: boolean = false
  @State isShowSheet2: boolean = false
  @State isShowSheet3: boolean = false
  private items: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  @Builder SheetBuilder() {
    Column() {
      // 第一步：自定义滚动容器
      List({ space: '10vp' }) {
        ForEach(this.items, (item: number) => {
          ListItem() {
            Text(String(item)).fontSize(16).fontWeight(FontWeight.Bold)
          }.width('90%').height('80vp').backgroundColor('#ff53ecd9').borderRadius(10)
        })
      }
      .alignListItem(ListItemAlign.Center)
      .margin({ top: '10vp' })
      .width('100%')
      .height('900px')
      // 第二步：设置滚动组件的嵌套滚动属性
      .nestedScroll({
        scrollForward: NestedScrollMode.PARENT_FIRST,
        scrollBackward: NestedScrollMode.SELF_FIRST,
      })

      Text('非滚动区域')
        .width('100%')
        .backgroundColor(Color.Gray)
        .layoutWeight(1)
        .textAlign(TextAlign.Center)
        .align(Alignment.Top)
    }.width('100%').height('100%')
  }

  @State isShowSheetCover1: boolean = false
  @State isShowSheetCover2: boolean = false
  @State isShowSheetCover3: boolean = false
  @Builder SheetCoverBuilder() {
    Column() {
      Text('Custom SheetCover').fontSize(16)
      Button('点击关闭弹窗')
        .onClick(() => {
          this.isShowSheetCover1 = false
          this.isShowSheetCover2 = false
          this.isShowSheetCover3 = false
        })
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  toastId: number = 0;

  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('1st Interface: ' + this.openInterface1)
          .fontSize(12)
        Row({ space: 5 }) {
          ForEach(this.setOpenInterface1, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('1st LevelOrder: ' + this.levelOrder1.getOrder())
          .fontSize(12)
        Row({ space: 5 }) {
          ForEach(this.setLevelOrder1, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('2nd Interface: ' + this.openInterface2)
          .fontSize(12)
        Row({ space: 5 }) {
          ForEach(this.setOpenInterface2, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('2nd LevelOrder: ' + this.levelOrder2.getOrder())
          .fontSize(12)
        Row({ space: 5 }) {
          ForEach(this.setLevelOrder2, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Row() {
          Button('弹出弹窗1')
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1,
                isModal: false,
              })
            })
          Button('获取层级')
            .onClick(() => {
              let topOrder: LevelOrder = this.promptAction.getTopOrder();
              if (topOrder === undefined) {
                console.error('topOrder: ' + topOrder);
              } else {
                console.error('topOrder: ' + topOrder.getOrder());
              }

              let bottomOrder: LevelOrder = this.promptAction.getBottomOrder();
              if (bottomOrder === undefined) {
                console.error('bottomOrder: ' + bottomOrder);
              } else {
                console.error('bottomOrder: ' + bottomOrder.getOrder());
              }
            })
          Button('弹出弹窗2')
            .onClick(() => {
              this.openDialog(this.message2, this.openInterface2, {
                levelOrder: this.levelOrder2,
                isModal: true,
              })
            })
        }

        Row() {
          Button('Menu+弹窗1+弹窗2')
            .fontSize(10)
            .bindMenu(this.isShowMenu1, this.MenuBuilder())
            .onClick(() => {
              this.isShowMenu1 = !this.isShowMenu1
              setTimeout(() => {
                this.openDialog(this.message1, this.openInterface1, {
                  levelOrder: this.levelOrder1
                })
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+Menu+弹窗2')
            .fontSize(10)
            .bindMenu(this.isShowMenu2, this.MenuBuilder())
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.isShowMenu2 = !this.isShowMenu2
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+弹窗2+Menu')
            .fontSize(10)
            .bindMenu(this.isShowMenu3, this.MenuBuilder())
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 3000)
              setTimeout(() => {
                this.isShowMenu3 = !this.isShowMenu3
              }, 6000)
            })
        }

        Row() {
          Button('Popup+弹窗1+弹窗2')
            .fontSize(10)
            .bindPopup(this.isShowPopup1, this.popupOptions)
            .onClick(() => {
              this.isShowPopup1 = !this.isShowPopup1
              setTimeout(() => {
                this.openDialog(this.message1, this.openInterface1, {
                  levelOrder: this.levelOrder1
                })
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+Popup+弹窗2')
            .fontSize(10)
            .bindPopup(this.isShowPopup2, this.popupOptions)
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.isShowPopup2 = !this.isShowPopup2
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+弹窗2+Popup')
            .fontSize(10)
            .bindPopup(this.isShowPopup3, this.popupOptions)
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 3000)
              setTimeout(() => {
                this.isShowPopup3 = !this.isShowPopup3
              }, 6000)
            })
        }

        Row() {
          Button('Toast+弹窗1+弹窗2')
            .fontSize(10)
            .onClick(() => {
              this.promptAction.showToast({
                message: 'ok，我是DEFAULT toast',
                duration: 10000,
                showMode: promptAction.ToastShowMode.DEFAULT,
                bottom: 80
              })
              setTimeout(() => {
                this.openDialog(this.message1, this.openInterface1, {
                  levelOrder: this.levelOrder1
                })
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+Toast+弹窗2')
            .fontSize(10)
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.promptAction.showToast({
                  message: 'ok，我是DEFAULT toast',
                  duration: 10000,
                  showMode: promptAction.ToastShowMode.DEFAULT,
                  bottom: 80
                })
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+弹窗2+Toast')
            .fontSize(10)
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 3000)
              setTimeout(() => {
                this.promptAction.showToast({
                  message: 'ok，我是DEFAULT toast',
                  duration: 10000,
                  showMode: promptAction.ToastShowMode.DEFAULT,
                  bottom: 80
                })
              }, 6000)
            })
        }

        Row() {
          Button('Sheet+弹窗1+弹窗2')
            .fontSize(10)
            .bindSheet(this.isShowSheet1, this.SheetBuilder(), {
              detents: [SheetSize.MEDIUM, SheetSize.LARGE, 600],
              preferType: SheetType.BOTTOM,
              title: { title: '嵌套滚动场景' },
              onDisappear: () => {
                this.isShowSheet1 = false
              }
            })
            .onClick(() => {
              this.isShowSheet1 = !this.isShowSheet1
              setTimeout(() => {
                this.openDialog(this.message1, this.openInterface1, {
                  levelOrder: this.levelOrder1
                })
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+Sheet+弹窗2')
            .fontSize(10)
            .bindSheet(this.isShowSheet2, this.SheetBuilder(), {
              detents: [SheetSize.MEDIUM, SheetSize.LARGE, 600],
              preferType: SheetType.BOTTOM,
              title: { title: '嵌套滚动场景' },
              onDisappear: () => {
                this.isShowSheet2 = false
              }
            })
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.isShowSheet2 = !this.isShowSheet2
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+弹窗2+Sheet' +
            '')
            .fontSize(10)
            .bindSheet(this.isShowSheet3, this.SheetBuilder(), {
              detents: [SheetSize.MEDIUM, SheetSize.LARGE, 600],
              preferType: SheetType.BOTTOM,
              title: { title: '嵌套滚动场景' },
              onDisappear: () => {
                this.isShowSheet3 = false
              }
            })
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 3000)
              setTimeout(() => {
                this.isShowSheet3 = !this.isShowSheet3
              }, 6000)
            })
        }

        Row() {
          Button('SheetCover+弹窗1+弹窗2')
            .fontSize(8)
            .bindContentCover(this.isShowSheetCover1, this.SheetCoverBuilder(), {
              modalTransition: ModalTransition.DEFAULT,
              backgroundColor: Color.Pink,
              onDisappear: () => {
                this.isShowSheetCover1 = false
              }
            })
            .onClick(() => {
              this.isShowSheetCover1 = !this.isShowSheetCover1;
              setTimeout(() => {
                this.openDialog(this.message1, this.openInterface1, {
                  levelOrder: this.levelOrder1
                })
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+SheetCover+弹窗2')
            .fontSize(8)
            .bindContentCover(this.isShowSheetCover2, this.SheetCoverBuilder(), {
              modalTransition: ModalTransition.DEFAULT,
              backgroundColor: Color.Pink,
              onDisappear: () => {
                this.isShowSheetCover2 = false
              }
            })
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.isShowSheetCover2 = !this.isShowSheetCover2;
              }, 3000)
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 6000)
            })
          Button('弹窗1+弹窗2+SheetCover')
            .fontSize(8)
            .bindContentCover(this.isShowSheetCover3, this.SheetCoverBuilder(), {
              modalTransition: ModalTransition.DEFAULT,
              backgroundColor: Color.Pink,
              onDisappear: () => {
                this.isShowSheetCover3 = false
              }
            })
            .onClick(() => {
              this.openDialog(this.message1, this.openInterface1, {
                levelOrder: this.levelOrder1
              })
              setTimeout(() => {
                this.openDialog(this.message2, this.openInterface2, {
                  levelOrder: this.levelOrder2
                })
              }, 3000)
              setTimeout(() => {
                this.isShowSheetCover3 = !this.isShowSheetCover3;
              }, 6000)
            })
        }
      }
    }
    .title('DialogLevelOrder')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}