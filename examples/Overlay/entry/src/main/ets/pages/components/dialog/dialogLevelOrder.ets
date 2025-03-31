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
  controller?: CustomDialogController

  build() {
    Column() {
      Text('我是内容')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
      TextInput()
      Button('点我关闭弹窗')
        .onClick(() => {
          let ctrl: PromptActionDialogController = this.getDialogController()
          if (ctrl !== undefined) {
            ctrl.close()
          }
        })
    }
    .height(400)
    .backgroundColor('#FFF0F0F0')
  }
}

@Builder
export function DialogLevelOrderBuilder(name: string, param: Object) {
  DialogLevelOrder()
}

@Component
export struct DialogLevelOrder {
  private message = '弹窗'
  private ctx: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.ctx.getPromptAction()

  @State customDialogIds: number[] = []
  @State dialogIdIndex: number = 0
  @Builder customDialogComponent(idIndex: number = 0) {
    Column() {
      Text('弹窗').fontSize(30)
      TextInput()
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

  @State openInterface: string = 'openCustomDialog'
  private setOpenInterface: SetParam[] = [{
    title: 'open',
    func: () => {
      this.openInterface = 'openCustomDialog'
    }
  }, {
    title: 'openCtrl',
    func: () => {
      this.openInterface = 'openCustomDialogWithController'
    }
  }, {
    title: 'present',
    func: () => {
      this.openInterface = 'presentCustomDialog'
    }
  }, {
    title: 'ctrlOpen',
    func: () => {
      this.openInterface = 'CustomDialogController'
    }
  }, {
    title: 'show',
    func: () => {
      this.openInterface = 'showDialog'
    }
  }, {
    title: 'actionSheet',
    func: () => {
      this.openInterface = 'showActionSheet'
    }
  }, {
    title: 'alertDialog',
    func: () => {
      this.openInterface = 'showAlertDialog'
    }
  }]

  @State levelOrder: LevelOrder = LevelOrder.clamp(undefined)
  private setLevelOrder: SetParam[] = [{
    title: '-100000',
    func: () => {
      this.levelOrder = LevelOrder.clamp(-100000)
    }
  }, {
    title: '-5',
    func: () => {
      this.levelOrder = LevelOrder.clamp(-5)
    }
  }, {
    title: 'undefined',
    func: () => {
      this.levelOrder = LevelOrder.clamp(undefined)
    }
  }, {
    title: '1.41',
    func: () => {
      this.levelOrder = LevelOrder.clamp(1.41)
    }
  }, {
    title: '100000',
    func: () => {
      this.levelOrder = LevelOrder.clamp(100000)
    }
  }]

  openDialog() {
    switch (this.openInterface) {
      case 'openCustomDialog': {
        this.promptAction.openCustomDialog({
          builder: () => {
            this.customDialogComponent(this.dialogIdIndex)
          },
          isModal: false,
          levelOrder: this.levelOrder
        }).then((dialogId: number) => {
          this.customDialogIds[this.dialogIdIndex] = dialogId
          this.dialogIdIndex++
        })
        break
      }
      case 'openCustomDialogWithController': {
        let dialogController: promptAction.CommonController = new promptAction.DialogController()
        let contentNode: ComponentContent<Object> = new ComponentContent(this.ctx, wrapBuilder(buildText),
          new Params(this.message, dialogController));
        this.promptAction.openCustomDialogWithController(contentNode, dialogController, {
          isModal: false,
          levelOrder: this.levelOrder,
        })
        break
      }
      case 'presentCustomDialog': {
        let dialogController: promptAction.CommonController = new promptAction.DialogController()
        this.promptAction.presentCustomDialog(() => {
          this.customDialogComponent(this.dialogIdIndex)
        }, dialogController, {
          isModal: false,
          levelOrder: this.levelOrder,
        }).then((dialogId: number) => {
          this.customDialogIds[this.dialogIdIndex] = dialogId
          this.dialogIdIndex++
        })
        break
      }
      case 'CustomDialogController': {
        let customDialogController: CustomDialogController = new CustomDialogController({
          builder: CustomDialogExample({}),
          isModal: false,
          levelOrder: this.levelOrder,
        })
        customDialogController.open()
        break
      }
      case 'showDialog': {
        this.promptAction.showDialog({
          title: '弹窗',
          message: '层级: ' + this.levelOrder.getOrder(),
          isModal: false,
          levelOrder: this.levelOrder,
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
          title: '弹窗',
          message: '层级: ' + this.levelOrder.getOrder(),
          isModal: false,
          levelOrder: this.levelOrder,
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
          title: '弹窗',
          message: '层级: ' + this.levelOrder.getOrder(),
          isModal: false,
          levelOrder: this.levelOrder,
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

  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('Interface: ' + this.openInterface)
          .fontSize(12)
        Row({ space: 5 }) {
          ForEach(this.setOpenInterface, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('LevelOrder: ' + this.levelOrder.getOrder())
          .fontSize(12)
        Row({ space: 5 }) {
          ForEach(this.setLevelOrder, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Button('弹出弹窗')
          .onClick(() => {
            this.openDialog()
          })
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