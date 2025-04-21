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

import { ComponentContent, LengthMetrics, PromptAction, promptAction } from '@kit.ArkUI'
import { ParamOption, SetParam } from '../base/ParamOption'

class Params {
  public dialogController: promptAction.CommonController = new promptAction.DialogController()
  public secondInterface: string = 'openCustomDialog'
  public secondShowInSubWindow: boolean = false
  public secondFocusable: boolean = false
  constructor(dialogController: promptAction.CommonController, secondInterface: string, secondShowInSubWindow: boolean,
    secondFocusable: boolean) {
    this.dialogController = dialogController
    this.secondInterface = secondInterface
    this.secondShowInSubWindow = secondShowInSubWindow
    this.secondFocusable = secondFocusable
  }
}

@Builder
function buildText(params: Params) {
  Column({ space: 5 }) {
    Text('弹窗')
      .fontSize(30)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
    SecondDialogComponent({
      secondInterface: params.secondInterface,
      secondShowInSubWindow: params.secondShowInSubWindow,
      secondFocusable: params.secondFocusable
    })
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
  secondInterface: string = 'openCustomDialog'
  secondShowInSubWindow: boolean = false
  secondFocusable: boolean = false
  controller?: CustomDialogController

  private ctx: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.ctx.getPromptAction()

  @State customDialogIds: number[] = []
  @State dialogIdIndex: number = 0
  @Builder customDialogComponent(idIndex: number = 0) {
    Column() {
      Text('弹窗').fontSize(30)
      Button('点击关闭弹窗')
        .onClick(() => {
          this.promptAction.closeCustomDialog(this.customDialogIds[idIndex])
          this.customDialogIds[idIndex] = null!
        })
    }
    .height(200)
    .padding(5)
    .justifyContent(FlexAlign.SpaceBetween)
  }

  build() {
    Column() {
      Text('我是内容')
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
      TextInput()
        .onChange(() => {
          switch (this.secondInterface) {
            case 'openCustomDialog': {
              this.promptAction.openCustomDialog({
                builder: () => {
                  this.customDialogComponent(this.dialogIdIndex)
                },
                showInSubWindow: this.secondShowInSubWindow,
                focusable: this.secondFocusable
              }).then((dialogId: number) => {
                this.customDialogIds[this.dialogIdIndex] = dialogId
                this.dialogIdIndex++
              })
              break
            }
            case 'openCustomDialogWithController': {
              let dialogController: promptAction.CommonController = new promptAction.DialogController()
              let contentNode: ComponentContent<Object> = new ComponentContent(this.ctx, wrapBuilder(buildText),
                new Params(dialogController, this.secondInterface, this.secondShowInSubWindow, this.secondFocusable));
              this.promptAction.openCustomDialogWithController(contentNode, dialogController, {
                showInSubWindow: this.secondShowInSubWindow,
                focusable: this.secondFocusable,
              })
              break
            }
            case 'presentCustomDialog': {
              let dialogController: promptAction.CommonController = new promptAction.DialogController()
              this.promptAction.presentCustomDialog(() => {
                this.customDialogComponent(this.dialogIdIndex)
              }, dialogController, {
                showInSubWindow: this.secondShowInSubWindow,
                focusable: this.secondFocusable,
              }).then((dialogId: number) => {
                this.customDialogIds[this.dialogIdIndex] = dialogId
              })
            }
            case 'CustomDialogController': {
              let customDialogController: CustomDialogController = new CustomDialogController({
                builder: CustomDialogExample({
                  secondInterface: this.secondInterface,
                  secondShowInSubWindow: this.secondShowInSubWindow,
                  secondFocusable: this.secondFocusable
                }),
                showInSubWindow: this.secondShowInSubWindow,
                focusable: this.secondFocusable,
              })
              customDialogController.open()
            }
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
    .height(400)
  }
}

@Component
struct SecondDialogComponent {
  secondInterface: string = 'openCustomDialog'
  secondShowInSubWindow: boolean = false
  secondFocusable: boolean = false

  private ctx: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.ctx.getPromptAction()

  @State customDialogIds: number[] = []
  @State dialogIdIndex: number = 0
  @Builder customDialogComponent(idIndex: number = 0) {
    Column() {
      Text('弹窗').fontSize(30)
      Button('点击关闭弹窗')
        .onClick(() => {
          this.promptAction.closeCustomDialog(this.customDialogIds[idIndex])
          this.customDialogIds[idIndex] = null!
        })
    }
    .height(200)
    .padding(5)
    .justifyContent(FlexAlign.SpaceBetween)
  }

  build() {
    Column() {
      TextInput()
        .onChange(() => {
          switch (this.secondInterface) {
            case 'openCustomDialog': {
              this.promptAction.openCustomDialog({
                builder: () => {
                  this.customDialogComponent(this.dialogIdIndex)
                },
                showInSubWindow: this.secondShowInSubWindow,
                focusable: this.secondFocusable
              }).then((dialogId: number) => {
                this.customDialogIds[this.dialogIdIndex] = dialogId
                this.dialogIdIndex++
              })
              break
            }
            case 'openCustomDialogWithController': {
              let dialogController: promptAction.CommonController = new promptAction.DialogController()
              let contentNode: ComponentContent<Object> = new ComponentContent(this.ctx, wrapBuilder(buildText),
                new Params(dialogController, this.secondInterface, this.secondShowInSubWindow, this.secondFocusable));
              this.promptAction.openCustomDialogWithController(contentNode, dialogController, {
                showInSubWindow: this.secondShowInSubWindow,
                focusable: this.secondFocusable,
              })
              break
            }
            case 'presentCustomDialog': {
              let dialogController: promptAction.CommonController = new promptAction.DialogController()
              this.promptAction.presentCustomDialog(() => {
                this.customDialogComponent(this.dialogIdIndex)
              }, dialogController, {
                showInSubWindow: this.secondShowInSubWindow,
                focusable: this.secondFocusable,
              }).then((dialogId: number) => {
                this.customDialogIds[this.dialogIdIndex] = dialogId
              })
              break
            }
            case 'CustomDialogController': {
              let customDialogController: CustomDialogController = new CustomDialogController({
                builder: CustomDialogExample({
                  secondInterface: this.secondInterface,
                  secondShowInSubWindow: this.secondShowInSubWindow,
                  secondFocusable: this.secondFocusable
                }),
                showInSubWindow: this.secondShowInSubWindow,
                focusable: this.secondFocusable,
              })
              customDialogController.open()
              break
            }
          }
        })
    }
  }
}

@Builder
export function DialogFocusableBuilder(name: string, param: Object) {
  DialogFocusable()
}

@Component
export struct DialogFocusable {
  private ctx: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.ctx.getPromptAction()

  @State customDialogIds: number[] = []
  @State dialogIdIndex: number = 0
  @Builder customDialogComponent(idIndex: number = 0) {
    Column() {
      Text('弹窗').fontSize(30)
      TextInput()
        .onChange(() => {
          this.openSecondDialog()
        })
      Button('点击关闭弹窗')
        .onClick(() => {
          this.promptAction.closeCustomDialog(this.customDialogIds[idIndex])
          this.customDialogIds[this.dialogIdIndex] = null!
        })
    }
    .height(200)
    .padding(5)
    .justifyContent(FlexAlign.SpaceBetween)
  }

  @State firstInterface: string = 'openCustomDialog'
  private setFirstInterface: SetParam[] = [{
    title: 'open',
    func: () => {
      this.firstInterface = 'openCustomDialog'
    }
  }, {
    title: 'openWithController',
    func: () => {
      this.firstInterface = 'openCustomDialogWithController'
    }
  }, {
    title: 'present',
    func: () => {
      this.firstInterface = 'presentCustomDialog'
    }
  }, {
    title: 'Controller',
    func: () => {
      this.firstInterface = 'CustomDialogController'
    }
  }]

  @State firstShowInSubWindow: boolean = false
  private setFirstShowInSubWindow: SetParam[] = [{
    title: 'false',
    func: () => {
      this.firstShowInSubWindow = false
    }
  }, {
    title: 'true',
    func: () => {
      this.firstShowInSubWindow = true
    }
  }]

  @State firstFocusable: boolean = false
  private setFirstFocusable: SetParam[] = [{
    title: 'false',
    func: () => {
      this.firstFocusable = false
    }
  }, {
    title: 'true',
    func: () => {
      this.firstFocusable = true
    }
  }]

  @State secondInterface: string = 'openCustomDialog'
  private setSecondInterface: SetParam[] = [{
    title: 'open',
    func: () => {
      this.secondInterface = 'openCustomDialog'
    }
  }, {
    title: 'openWithController',
    func: () => {
      this.secondInterface = 'openCustomDialogWithController'
    }
  }, {
    title: 'present',
    func: () => {
      this.secondInterface = 'presentCustomDialog'
    }
  }, {
    title: 'Controller',
    func: () => {
      this.secondInterface = 'CustomDialogController'
    }
  }]

  @State secondShowInSubWindow: boolean = false
  private setSecondShowInSubWindow: SetParam[] = [{
    title: 'false',
    func: () => {
      this.secondShowInSubWindow = false
    }
  }, {
    title: 'true',
    func: () => {
      this.secondShowInSubWindow = true
    }
  }]

  @State secondFocusable: boolean = false
  private setSecondFocusable: SetParam[] = [{
    title: 'false',
    func: () => {
      this.secondFocusable = false
    }
  }, {
    title: 'true',
    func: () => {
      this.secondFocusable = true
    }
  }]

  openFirstDialog(enableAsync: boolean = false) {
    switch (this.firstInterface) {
      case 'openCustomDialog': {
        this.promptAction.openCustomDialog({
          builder: () => {
            this.customDialogComponent(this.dialogIdIndex)
          },
          showInSubWindow: this.firstShowInSubWindow,
          focusable: this.firstFocusable
        }).then((dialogId: number) => {
          this.customDialogIds[this.dialogIdIndex] = dialogId
          this.dialogIdIndex++
          if (!enableAsync) {
            return
          }
          setTimeout(() => {
            this.openSecondDialog()
          }, 5000)
        })
        break
      }
      case 'openCustomDialogWithController': {
        let dialogController: promptAction.CommonController = new promptAction.DialogController()
        let contentNode: ComponentContent<Object> = new ComponentContent(this.ctx, wrapBuilder(buildText),
          new Params(dialogController, this.secondInterface, this.secondShowInSubWindow, this.secondFocusable));
        this.promptAction.openCustomDialogWithController(contentNode, dialogController, {
          showInSubWindow: this.secondShowInSubWindow,
          focusable: this.secondFocusable,
        }).then(() => {
          if (!enableAsync) {
            return
          }
          setTimeout(() => {
            this.openSecondDialog()
          }, 5000)
        })
        break
      }
      case 'presentCustomDialog': {
        let dialogController: promptAction.CommonController = new promptAction.DialogController()
        this.promptAction.presentCustomDialog(() => {
          this.customDialogComponent(this.dialogIdIndex)
        }, dialogController, {
          showInSubWindow: this.secondShowInSubWindow,
          focusable: this.secondFocusable,
        }).then((dialogId: number) => {
          this.customDialogIds[this.dialogIdIndex] = dialogId
          this.dialogIdIndex++
          if (!enableAsync) {
            return
          }
          setTimeout(() => {
            this.openSecondDialog()
          }, 5000)
        })
        break
      }
      case 'CustomDialogController': {
        let customDialogController: CustomDialogController = new CustomDialogController({
          builder: CustomDialogExample({
            secondInterface: this.secondInterface,
            secondShowInSubWindow: this.secondShowInSubWindow,
            secondFocusable: this.secondFocusable
          }),
          showInSubWindow: this.secondShowInSubWindow,
          focusable: this.secondFocusable,
          keyboardAvoidDistance: LengthMetrics.vp(0)
        })
        customDialogController.open()
        if (!enableAsync) {
          return
        }
        setTimeout(() => {
          this.openSecondDialog()
        }, 5000)
        break
      }
    }
  }

  openSecondDialog() {
    switch (this.secondInterface) {
      case 'openCustomDialog': {
        this.promptAction.openCustomDialog({
          builder: () => {
            this.customDialogComponent(this.dialogIdIndex)
          },
          showInSubWindow: this.firstShowInSubWindow,
          focusable: this.firstFocusable
        }).then((dialogId: number) => {
          this.customDialogIds[this.dialogIdIndex] = dialogId
          this.dialogIdIndex++
        })
        break
      }
      case 'openCustomDialogWithController': {
        let dialogController: promptAction.CommonController = new promptAction.DialogController()
        let contentNode: ComponentContent<Object> = new ComponentContent(this.ctx, wrapBuilder(buildText),
          new Params(dialogController, this.secondInterface, this.secondShowInSubWindow, this.secondFocusable));
        this.promptAction.openCustomDialogWithController(contentNode, dialogController, {
          showInSubWindow: this.secondShowInSubWindow,
          focusable: this.secondFocusable,
        })
        break
      }
      case 'presentCustomDialog': {
        let dialogController: promptAction.CommonController = new promptAction.DialogController()
        this.promptAction.presentCustomDialog(() => {
          this.customDialogComponent(this.dialogIdIndex)
        }, dialogController, {
          showInSubWindow: this.secondShowInSubWindow,
          focusable: this.secondFocusable,
        }).then((dialogId: number) => {
          this.customDialogIds[this.dialogIdIndex] = dialogId
          this.dialogIdIndex++
        })
        break
      }
      case 'CustomDialogController': {
        let customDialogController: CustomDialogController = new CustomDialogController({
          builder: CustomDialogExample({
            secondInterface: this.secondInterface,
            secondShowInSubWindow: this.secondShowInSubWindow,
            secondFocusable: this.secondFocusable
          }),
          showInSubWindow: this.secondShowInSubWindow,
          focusable: this.secondFocusable,
        })
        customDialogController.open()
        break
      }
    }
  }

  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('1st Interface: ' + this.firstInterface)
          .fontSize(12)
        Row({ space: 2 }) {
          ForEach(this.setFirstInterface, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('1st ShowInSubWindow: ' + this.firstShowInSubWindow)
          .fontSize(12)
        Row({ space: 2 }) {
          ForEach(this.setFirstShowInSubWindow, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('1st Focusable: ' + this.firstFocusable)
          .fontSize(12)
        Row({ space: 2 }) {
          ForEach(this.setFirstFocusable, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        TextInput({ placeholder: '输入任意字符弹出弹窗' })
          .onChange(() => {
            this.openFirstDialog()
          })

        Text('2nd Interface: ' + this.secondInterface)
          .fontSize(12)
        Row({ space: 2 }) {
          ForEach(this.setSecondInterface, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('2nd ShowInSubWindow: ' + this.secondShowInSubWindow)
          .fontSize(12)
        Row({ space: 2 }) {
          ForEach(this.setSecondShowInSubWindow, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Text('2nd Focusable: ' + this.secondFocusable)
          .fontSize(12)
        Row({ space: 2 }) {
          ForEach(this.setSecondFocusable, (item: SetParam) => {
            ParamOption({ title: item.title, func: item.func })
          }, (item: SetParam) => item.title)
        }

        Button('弹出多级弹窗')
          .onClick(() => {
            this.openFirstDialog()
          })

        Button('弹出异步弹窗')
          .onClick(() => {
            this.openFirstDialog()
          })
      }
    }
    .title('DialogFocusable')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}