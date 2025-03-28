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
import { BusinessError } from '@kit.BasicServicesKit'

class Params {
  public text: string = ''
  public dialogController: promptAction.CommonController = new promptAction.DialogController()
  constructor(text: string, dialogController: promptAction.CommonController) {
    this.text = text
    this.dialogController = dialogController
  }
}

@Component
struct MyComponent {
  build() {
    Column() {
      Button('点我关闭弹窗：通过自定义组件自带的DialogController')
        .onClick(() => {
          let dialogController: promptAction.DialogController = this.getDialogController()
          if (dialogController !== undefined) {
            dialogController.close()
          }
        })
    }
  }
}

@Builder
function buildText(params: Params) {
  Column({ space: 5 }) {
    Text(params.text)
      .fontSize(30)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
    if (params.dialogController !== undefined) {
      Button('点我关闭弹窗：通过外部传递的DialogController')
        .onClick(() => {
          params.dialogController.close()
        })
    }
    MyComponent()
  }
  .width(300)
  .height(200)
  .backgroundColor('#FFF0F0F0')
}

@Builder
function buildTextNoParams() {
  Column({ space: 5 }) {
    Text('弹窗：无外部传递的DialogController')
      .fontSize(30)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
    MyComponent()
  }.backgroundColor('#FFF0F0F0')
}

class FuncParams {
  public text: string = ''
  public dialogController: promptAction.CommonController = new promptAction.DialogController()
  public func: Function
  constructor(text: string, dialogController: promptAction.CommonController, func: Function) {
    this.text = text
    this.dialogController = dialogController
    this.func = func
  }
}

@Builder
function buildTextWithFunc(func: Function, dialogController: promptAction.DialogController) {
  Text(func())
    .fontSize(50)
    .fontWeight(FontWeight.Bold)
    .margin({ bottom: 36 })
  if (dialogController !== undefined) {
    Button('点我关闭弹窗：嵌套传递的DialogController')
      .onClick(() => {
        dialogController.close()
      })
  }
}

@Builder
function buildTextFull(params: FuncParams) {
  Column({ space: 5 }) {
    Text(params.text)
      .fontSize(30)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 })
    if (params.dialogController !== undefined) {
      Button('点我关闭弹窗：通过外部传递的DialogController')
        .onClick(() => {
          params.dialogController.close()
        })
    }
    MyComponent()
    buildTextWithFunc(params.func, params.dialogController)
  }.backgroundColor('#FFF0F0F0')
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
      Button('点我关闭弹窗：通过自定义组件自带的DialogController')
        .onClick(() => {
          let dialogController: PromptActionDialogController = this.getDialogController()
          if (dialogController !== undefined) {
            dialogController.close()
          }
        })
    }
    .height(400)
    .backgroundColor('#FFF0F0F0')
  }
}

@Builder
export function DialogControllerBuilder(name: string, param: Object) {
  DialogController()
}

@Component
export struct DialogController {
  private message = '弹窗'
  private ctx: UIContext = this.getUIContext()
  private promptAction: PromptAction = this.ctx.getPromptAction()

  @State customDialogIds: number[] = []
  @State dialogIdIndex: number = 0
  @Builder customDialogComponent(idIndex: number, controller: promptAction.DialogController) {
    Column() {
      Text(this.message)
        .fontSize(30)
      TextInput()
      Row({ space: 5 }) {
        if (idIndex !== undefined) {
          Button('点击关闭弹窗：通过ID')
            .onClick(() => {
              this.promptAction.closeCustomDialog(this.customDialogIds[idIndex])
              this.customDialogIds[idIndex] = null!
            })
        }
        if (controller !== undefined) {
          Button('点击关闭弹窗：通过外部传递的DialogController')
            .onClick(() => {
              controller.close()
            })
        }
      }
    }
    .height(200)
    .padding(5)
    .justifyContent(FlexAlign.SpaceBetween)
    .backgroundColor('#FFF0F0F0')
  }

  @Builder customDialogComponentWithId(dialogId: number, controller: promptAction.DialogController) {
    Column() {
      Text(this.message)
        .fontSize(30)
      TextInput()
      Row({ space: 5 }) {
        if (dialogId !== undefined) {
          Button('点击关闭弹窗：通过ID')
            .onClick(() => {
              this.promptAction.closeCustomDialog(dialogId)
            })
        }
        if (controller !== undefined) {
          Button('点击关闭弹窗：通过外部传递的DialogController')
            .onClick(() => {
              controller.close()
            })
        }
      }
    }
  }

  private baseDialogOptions: promptAction.BaseDialogOptions = {
    isModal: false,
    autoCancel: false
  }

  private dialogOptions: promptAction.DialogOptions = {
    isModal: false,
    autoCancel: false
  }

  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Button('openCustomDialog+CustomBuilder弹窗')
          .onClick(() => {
            this.promptAction.openCustomDialog({
              builder: () => {
                this.customDialogComponent(this.dialogIdIndex, undefined!)
              }
            }).then((dialogId: number) => {
              this.customDialogIds[this.dialogIdIndex] = dialogId
              this.dialogIdIndex++
            }).catch((err: BusinessError) => {
              console.error('openCustomDialog error: ' + err.code + ' ' + err.message)
            })
          })
        Button('openCustomDialog+ParamsNode弹窗')
          .onClick(() => {
            let contentNode: ComponentContent<Object> =
              new ComponentContent(this.ctx, wrapBuilder(buildText), new Params(this.message, undefined!))
            this.promptAction.openCustomDialog(contentNode, this.baseDialogOptions)
              .catch((err: BusinessError) => {
                console.error('openCustomDialog error: ' + err.code + ' ' + err.message)
              })
          })
        Button('openCustomDialogWithController+全部参数+NoParamsNode弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            let contentNodeNoParams: ComponentContent<Object> =
              new ComponentContent(this.ctx, wrapBuilder(buildTextNoParams))
            this.promptAction.openCustomDialogWithController(
              contentNodeNoParams, dialogController, this.baseDialogOptions
            ).catch((err: BusinessError) => {
              console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
            })
          })
        Button('openCustomDialogWithController+必填参数+NoParamsNode弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            let contentNodeNoParams: ComponentContent<Object> =
              new ComponentContent(this.ctx, wrapBuilder(buildTextNoParams))
            this.promptAction.openCustomDialogWithController(contentNodeNoParams, dialogController)
              .catch((err: BusinessError) => {
                console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
              })
          })
        Button('openCustomDialogWithController+全部参数+ParamsNode弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            let contentNode: ComponentContent<Object> =
              new ComponentContent(this.ctx, wrapBuilder(buildText), new Params(this.message, dialogController))
            this.promptAction.openCustomDialogWithController(contentNode, dialogController, this.baseDialogOptions)
              .catch((err: BusinessError) => {
                console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
              })
          })
        Button('openCustomDialogWithController+必填参数+ParamsNode弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            let contentNode: ComponentContent<Object> =
              new ComponentContent(this.ctx, wrapBuilder(buildText), new Params(this.message, dialogController))
            this.promptAction.openCustomDialogWithController(contentNode, dialogController)
              .catch((err: BusinessError) => {
                console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
              })
          })
        Button('openCustomDialogWithController+全部参数+FullNode弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            let contentNodeFull: ComponentContent<Object> = new ComponentContent(this.ctx, wrapBuilder(buildTextFull),
              new FuncParams(this.message, dialogController, () => { return 'FUNCTION' }),
              { nestingBuilderSupported: true })
            this.promptAction.openCustomDialogWithController(contentNodeFull, dialogController, this.baseDialogOptions)
              .catch((err: BusinessError) => {
                console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
              })
          })
        Button('openCustomDialogWithController+必填参数+FullNode弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            let contentNodeFull: ComponentContent<Object> = new ComponentContent(this.ctx, wrapBuilder(buildTextFull),
              new FuncParams(this.message, dialogController, () => { return 'FUNCTION' }),
              { nestingBuilderSupported: true })
            this.promptAction.openCustomDialogWithController(contentNodeFull, dialogController)
              .catch((err: BusinessError) => {
                console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
              })
          })
        Button('presentCustomDialog+CustomBuilderWithId全部参数弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            this.promptAction.presentCustomDialog((dialogId: number) => {
              this.customDialogComponentWithId(dialogId, dialogController)
            }, dialogController, this.dialogOptions).catch((err: BusinessError) => {
              console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
            })
          })
        Button('presentCustomDialog+CustomBuilderWithId必填参数+Controller弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            this.promptAction.presentCustomDialog((dialogId: number) => {
              this.customDialogComponentWithId(dialogId, dialogController)
            }, dialogController).catch((err: BusinessError) => {
              console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
            })
          })
        Button('presentCustomDialog+CustomBuilderWithId必填参数弹窗')
          .onClick(() => {
            this.promptAction.presentCustomDialog((dialogId: number) => {
              this.customDialogComponentWithId(dialogId, undefined!)
            }).catch((err: BusinessError) => {
                console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
              })
          })
        Button('presentCustomDialog+CustomBuilder全部参数弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            this.promptAction.presentCustomDialog(() => {
              this.customDialogComponent(this.dialogIdIndex, dialogController)
            }, dialogController, this.dialogOptions).then((dialogId: number) => {
              this.customDialogIds[this.dialogIdIndex] = dialogId
              this.dialogIdIndex++
            }).catch((err: BusinessError) => {
              console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
            })
          })
        Button('presentCustomDialog+CustomBuilder必填参数+Controller弹窗')
          .onClick(() => {
            let dialogController: promptAction.CommonController = new promptAction.DialogController()
            this.promptAction.presentCustomDialog(() => {
              this.customDialogComponent(this.dialogIdIndex, dialogController)
            }, dialogController).then((dialogId: number) => {
              this.customDialogIds[this.dialogIdIndex] = dialogId
              this.dialogIdIndex++
            }).catch((err: BusinessError) => {
              console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
            })
          })
        Button('presentCustomDialog+CustomBuilder必填参数弹窗')
          .onClick(() => {
            this.promptAction.presentCustomDialog(() => {
              this.customDialogComponent(this.dialogIdIndex, undefined!)
            }).then((dialogId: number) => {
              this.customDialogIds[this.dialogIdIndex] = dialogId
              this.dialogIdIndex++
            }).catch((err: BusinessError) => {
              console.error('openCustomDialogWithController error: ' + err.code + ' ' + err.message)
            })
          })
        Button('CustomDialogController弹窗')
          .onClick(() => {
            let customDialogController: CustomDialogController = new CustomDialogController({
              builder: CustomDialogExample(),
            })
            customDialogController.open()
          })
      }
    }
    .title('DialogController')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack
    })
  }
}