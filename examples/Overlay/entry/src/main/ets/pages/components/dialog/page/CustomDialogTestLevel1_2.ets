/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { MyComponent } from '../../../../common/MyComponent'
import { LevelOrder } from '@kit.ArkUI'

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3)
  .padding(3)
  .borderWidth(1.0)
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Extend(Select)
function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

// customDialog demo
@CustomDialog
@Component
struct CustomDialogExample {
  @Link textValue: string
  @Link inputValue: string
  controller?: CustomDialogController
  // 若尝试在CustomDialog中传入多个其他的Controller，以实现在CustomDialog中打开另一个或另一些CustomDialog，那么此处需要将指向自己的controller放在所有controller的后面
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }

  build() {
    Column() {
      Text('Change text').fontSize(20).margin({ top: 10, bottom: 10 })
      TextInput({ placeholder: '', text: this.textValue }).height(60).width('90%')
        .onChange((value: string) => {
          this.textValue = value
        })
        .id('textInput_in_dialog')
      Text('Whether to change a text?').fontSize(16).margin({ bottom: 10 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('cancel')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('confirm')
          .onClick(() => {
            if (this.controller != undefined) {
              this.inputValue = this.textValue
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 10 })
    }.borderRadius(10)

    // 如果需要使用border属性或cornerRadius属性，请和borderRadius属性一起使用。
  }
}

// 验证自定义弹窗内走焦切换
@CustomDialog
@Component
struct CustomDialog_Focus {
  controller?: CustomDialogController
  // 若尝试在CustomDialog中传入多个其他的Controller，以实现在CustomDialog中打开另一个或另一些CustomDialog，那么此处需要将指向自己的controller放在所有controller的后面
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }

  build() {
    Column() {
      Text('是否删除此文件夹').fontSize(20).margin({ top: 10, bottom: 10 })
        .fontWeight(FontWeight.Bold)
      Text('删除后, 可在最近删除中保留30天').fontSize(16).margin({ bottom: 10 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('cancel')
          .fontColor(Color.Red)
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor('#F1F3F5')
        Button('confirm')
          .fontColor(Color.Blue)
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor('#F1F3F5')
      }.margin({ bottom: 10 })
    }
    .margin(10)
    .borderRadius(10)

    // 如果需要使用border属性或cornerRadius属性，请和borderRadius属性一起使用。
  }
}

// 作参考的自定义弹窗
@CustomDialog
@Component
struct CustomDialog_Test {
  @Link textValue: string
  @Link inputValue: string
  controller?: CustomDialogController
  // 若尝试在CustomDialog中传入多个其他的Controller，以实现在CustomDialog中打开另一个或另一些CustomDialog，那么此处需要将指向自己的controller放在所有controller的后面
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }

  build() {
    Column() {
      Text('作为参考的自定义弹窗').fontSize(20).margin({ top: 10, bottom: 10 })
      TextInput({ placeholder: '', text: this.textValue }).height(60).width('90%')
        .onChange((value: string) => {
          this.textValue = value
        })
        .id('textInput_in_testDialog')
      Text('Whether to change a text?').fontSize(16).margin({ bottom: 10 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('cancel')
          .onClick(() => {
            if (this.controller != undefined) {
              this.controller.close()
              this.cancel()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('confirm')
          .onClick(() => {
            if (this.controller != undefined) {
              this.inputValue = this.textValue
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 10 })
    }.borderRadius(10)

    // 如果需要使用border属性或cornerRadius属性，请和borderRadius属性一起使用。
  }
}


@Entry
@Component
struct CustomDialogTestLevel1_2 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]
  TestCaseList: number[] = []
  @State textValue: string = ''
  @State inputValue: string = 'click me'
  @State cancelInfo: string = ''
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      cancel: () => {
        this.onCancel()
      },
      confirm: () => {
        this.onAccept()
      },
      textValue: $textValue,
      inputValue: $inputValue
    }),
    cancel: this.exitDialog,
    autoCancel: true,
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: -20 },
    gridCount: 4,
    cornerRadius: 10,
  })
  dialogController_focus: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialog_Focus({
      cancel: () => {
        this.onCancelAction()
      },
      confirm: () => {
        this.onConfirmAction()
      },
    }),
    cancel: this.onAutoCancel,
    autoCancel: true,
    alignment: DialogAlignment.Bottom,
    gridCount: 4,
    cornerRadius: 16,
  })
  dialogController_comp: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialog_Test({
      cancel: () => {
        this.onCancelAction()
      },
      confirm: () => {
        this.onConfirmAction()
      },
      textValue: $textValue,
      inputValue: $inputValue
    }),
    cancel: this.onAutoCancel,
    autoCancel: true,
    alignment: DialogAlignment.Center,
    gridCount: 4,
    cornerRadius: 16,
  })

  // 在自定义组件即将析构销毁时将dialogController置空
  aboutToDisappear() {
    this.dialogController = null // 将dialogController置空
  }

  onCancel() {
    console.info('Callback when the first button is clicked')
  }

  onAccept() {
    console.info('Callback when the second button is clicked')
  }

  exitDialog() {
    console.info('Click the callback in the blank area')
  }

  onCancelAction() {
    this.cancelInfo = 'CustomDialog_Focus Close Via Cancel Button'
  }

  onConfirmAction() {
    this.cancelInfo = 'CustomDialog_Focus Close Via Confirm Button'
  }

  onAutoCancel() {
    this.cancelInfo = 'CustomDialog_Focus Close Via autoCancel'
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证自定义弹窗和textInput组合测试`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`自定义弹窗的输入法避让`)
            .paramTextStyle()
          TextInput()
            .id(`keyboard`)
          Row({ space: 3 }) {
            MyComponent({
              title: 'placement: Top,sub_F', func: () => {
                this.dialogController = new CustomDialogController({
                  builder: CustomDialogExample({
                    cancel: () => {
                      this.onCancel()
                    },
                    confirm: () => {
                      this.onAccept()
                    },
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                  cancel: this.exitDialog,
                  autoCancel: true,
                  alignment: DialogAlignment.Top,
                  gridCount: 4,
                  cornerRadius: 10,
                })
              }
            })
            MyComponent({
              title: 'placement: Bottom,sub_F', func: () => {
                this.dialogController = new CustomDialogController({
                  builder: CustomDialogExample({
                    cancel: () => {
                      this.onCancel()
                    },
                    confirm: () => {
                      this.onAccept()
                    },
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                  cancel: this.exitDialog,
                  autoCancel: true,
                  alignment: DialogAlignment.Bottom,
                  gridCount: 4,
                  cornerRadius: 10,
                })
              }
            })
          }

          Row({ space: 3 }) {
            MyComponent({
              title: 'placement: Top,sub_T', func: () => {
                this.dialogController = new CustomDialogController({
                  showInSubWindow: true,
                  builder: CustomDialogExample({
                    cancel: () => {
                      this.onCancel()
                    },
                    confirm: () => {
                      this.onAccept()
                    },
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                  cancel: this.exitDialog,
                  autoCancel: true,
                  alignment: DialogAlignment.Top,
                  gridCount: 4,
                  cornerRadius: 10,
                })
              }
            })
            MyComponent({
              title: 'placement: Bottom,sub_T', func: () => {
                this.dialogController = new CustomDialogController({
                  showInSubWindow: true,
                  builder: CustomDialogExample({
                    cancel: () => {
                      this.onCancel()
                    },
                    confirm: () => {
                      this.onAccept()
                    },
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                  cancel: this.exitDialog,
                  autoCancel: true,
                  alignment: DialogAlignment.Bottom,
                  gridCount: 4,
                  cornerRadius: 10,
                })
              }
            })
          }

          Text(`customDialog: withTextInput`)
            .componentTextStyle()
            .onClick(() => {
              if (this.dialogController != null) {
                this.dialogController.open()
              }
            })
        }
        .columnStyle()

        Text(`验证自定义弹窗走焦测试`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`tab切换弹窗内焦点,enter点击: 点击信息: ${this.cancelInfo}`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'focus_subWindow: T', func: () => {
                this.dialogController_focus = new CustomDialogController({
                  showInSubWindow: true,
                  builder: CustomDialog_Focus({
                    cancel: () => {
                      this.onCancelAction()
                    },
                    confirm: () => {
                      this.onConfirmAction()
                    },
                  }),
                  cancel: this.onAutoCancel,
                  autoCancel: true,
                  alignment: DialogAlignment.Bottom,
                  gridCount: 4,
                  cornerRadius: 16,
                })
              }
            })
            MyComponent({
              title: 'focus_subWindow: F', func: () => {
                this.dialogController_focus = new CustomDialogController({
                  showInSubWindow: true,
                  builder: CustomDialog_Focus({
                    cancel: () => {
                      this.onCancelAction()
                    },
                    confirm: () => {
                      this.onConfirmAction()
                    },
                  }),
                  cancel: this.onAutoCancel,
                  autoCancel: true,
                  alignment: DialogAlignment.Bottom,
                  gridCount: 4,
                  cornerRadius: 16,
                })
              }
            })
          }

          Text(`customDialog: withFocus`)
            .componentTextStyle()
            .onClick(() => {
              if (this.dialogController_focus != null) {
                this.dialogController_focus.open()
              }
            })
        }
        .columnStyle()

        Text(`验证自定义弹窗获取焦点功能`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`切换自定义弹窗的获取焦点属性`)
            .paramTextStyle()
          Select([
            { value: '非子窗弹窗,焦点设置True' },
            { value: '非子窗弹窗,焦点设置False' },
            { value: '子窗弹窗,焦点设置True' },
            { value: '子窗弹窗,焦点设置False' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '非子窗弹窗,焦点设置True':
                  this.dialogController = new CustomDialogController({
                    showInSubWindow: false,
                    focusable: true,

                    builder: CustomDialogExample({
                      cancel: () => {
                        this.onCancel()
                      },
                      confirm: () => {
                        this.onAccept()
                      },
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                    cancel: this.exitDialog,
                    autoCancel: true,
                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -20 },
                    gridCount: 4,
                    cornerRadius: 10,
                  })
                  break

                case '非子窗弹窗,焦点设置False':
                  this.dialogController = new CustomDialogController({
                    showInSubWindow: false,
                    focusable: false,

                    builder: CustomDialogExample({
                      cancel: () => {
                        this.onCancel()
                      },
                      confirm: () => {
                        this.onAccept()
                      },
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                    cancel: this.exitDialog,
                    autoCancel: true,
                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -20 },
                    gridCount: 4,
                    cornerRadius: 10,
                  })
                  break

                case '子窗弹窗,焦点设置True':
                  this.dialogController = new CustomDialogController({
                    showInSubWindow: true,
                    focusable: true,

                    builder: CustomDialogExample({
                      cancel: () => {
                        this.onCancel()
                      },
                      confirm: () => {
                        this.onAccept()
                      },
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                    cancel: this.exitDialog,
                    autoCancel: true,
                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -20 },
                    gridCount: 4,
                    cornerRadius: 10,
                  })
                  break

                case '子窗弹窗,焦点设置False':
                  this.dialogController = new CustomDialogController({
                    showInSubWindow: true,
                    focusable: false,

                    builder: CustomDialogExample({
                      cancel: () => {
                        this.onCancel()
                      },
                      confirm: () => {
                        this.onAccept()
                      },
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                    cancel: this.exitDialog,
                    autoCancel: true,
                    alignment: DialogAlignment.Bottom,
                    offset: { dx: 0, dy: -20 },
                    gridCount: 4,
                    cornerRadius: 10,
                  })
                  break
              }
            })
            .key('select_dialogFocus')
          Divider()


          Text(`切换自定义弹窗获取焦点能力: 先弹软键盘再弹弹窗`)
            .paramTextStyle()
          TextInput({ placeholder: 'click for inputting ur comments' })
            .id(`textInput_keyboard`)
            .onClick(() => {
              setTimeout(() => {
                this.dialogController?.open()
              }, 1500)
            })

          Text(`切换自定义弹窗获取焦点能力: 组合参考弹窗不同层级, 自定义弹窗不同获焦`)
            .paramTextStyle()
          Select([
            { value: '非子窗弹窗,order设置-1' },
            { value: '非子窗弹窗,order设置1' },
            { value: '子窗弹窗' },
          ])
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case '非子窗弹窗,order设置-1':
                  this.dialogController_comp = new CustomDialogController({
                    showInSubWindow: false,
                    levelOrder: LevelOrder.clamp(-1),

                    builder: CustomDialog_Test({
                      cancel: () => {
                        this.onCancel()
                      },
                      confirm: () => {
                        this.onAccept()
                      },
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                    cancel: this.exitDialog,
                    autoCancel: true,
                    alignment: DialogAlignment.Center,
                    offset: { dx: 0, dy: 120 },
                    gridCount: 4,
                    cornerRadius: 10,
                  })
                  break

                case '非子窗弹窗,order设置1':
                  this.dialogController_comp = new CustomDialogController({
                    showInSubWindow: false,
                    levelOrder: LevelOrder.clamp(1),

                    builder: CustomDialog_Test({
                      cancel: () => {
                        this.onCancel()
                      },
                      confirm: () => {
                        this.onAccept()
                      },
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                    cancel: this.exitDialog,
                    autoCancel: true,
                    alignment: DialogAlignment.Center,
                    offset: { dx: 0, dy: 120 },
                    gridCount: 4,
                    cornerRadius: 10,
                  })
                  break

                case '子窗弹窗':
                  this.dialogController_comp = new CustomDialogController({
                    showInSubWindow: true,
                    builder: CustomDialog_Test({
                      cancel: () => {
                        this.onCancel()
                      },
                      confirm: () => {
                        this.onAccept()
                      },
                      textValue: $textValue,
                      inputValue: $inputValue
                    }),
                    cancel: this.exitDialog,
                    autoCancel: true,
                    alignment: DialogAlignment.Center,
                    offset: { dx: 0, dy: 120 },

                    gridCount: 4,
                    cornerRadius: 10,
                  })
                  break
              }
            })
            .key('select_testDialogLevelOrder')

          Text(`customDialog: focus_otherOrder`)
            .componentTextStyle()
            .onClick(() => {
              // 先弹出不同levelOrder的参考弹窗
              setTimeout(() => {
                this.dialogController_comp?.open()
              }, 500)

              // 再弹出不同获取焦点能力的自定义弹窗
              setTimeout(() => {
                this.dialogController?.open()
              }, 2000)
            })
        }
        .columnStyle()
      }
      .width('100%')
    }
    .scrollBar(BarState.Off)
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%')
    .height('100%')
  }
}