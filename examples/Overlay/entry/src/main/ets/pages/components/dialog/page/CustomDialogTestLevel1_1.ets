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

import promptAction from '@ohos.promptAction';
import { BusinessError } from '@ohos.base';
import { MyComponent } from '../../../../common/MyComponent'
import { CustomDialogControllerExample } from '../../../../common/CustomDialogController'


@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct CustomDialogTestLevel1_1 {
  scroller: Scroller = new Scroller()
  @State textValue: string = ''
  @State inputValue: string = 'click me'
  @State index: number[] = [0, 0, 0]
  @State dialogDismissParam: string = 'func'
  dialogController_withOtherAttr: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogControllerExample({
      textValue: $textValue,
      inputValue: $inputValue,
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),

    onWillDismiss: (dismissDialog: DismissDialogAction) => {
      if (this.dialogDismissParam == 'NA') {
      }
      if (this.dialogDismissParam == 'func') {
        dismissDialog.dismiss()
        console.log(`dialog close via onWillDismiss`)
      }
    },

    maskRect: {
      x: '0',
      y: '50%',
      width: '100%',
      height: '100%'
    },
    autoCancel: true,
    isModal: true,
    showInSubWindow: false,
    backgroundColor: '#B6C5D1'
  })
  dialogController_withToast: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogControllerExample({
      textValue: $textValue,
      inputValue: $inputValue,
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),

    onWillDismiss: (dismissDialog: DismissDialogAction) => {
      dismissDialog.dismiss()
    },

    maskRect: {
      x: '0',
      y: '50%',
      width: '100%',
      height: '100%'
    },
    backgroundColor: '#B6C5D1'
  })
  dialogController_withOptions: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogControllerExample({
      textValue: $textValue,
      inputValue: $inputValue,
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),

    width: 320,
    height: 240,

    cornerRadius: '20%',
    borderWidth: '1%',
    borderColor: Color.Blue,
    shadow: {
      radius: 10,
      color: '#392F49',
      offsetX: 20,
      offsetY: 20
    },
    backgroundColor: '#B6C5D1'
  })

  // 在自定义组件即将析构销毁时将dialogController删除和置空
  aboutToDisappear() {
    // 将dialogController置空
    this.dialogController_withOtherAttr = null
    this.dialogController_withToast = null
    this.dialogController_withOptions = null
  }

  onCancel() {
    console.info('Callback when the first button is clicked')
  }

  onAccept() {
    console.info('Callback when the second button is clicked')
  }

  existApp() {
    console.info('Click the callback in the blank area')
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证自定义弹窗onWillDismiss:`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`onWillDismiss和其他入参属性的组合测试:`)
            .paramTextStyle()
          Row({ space: 2 }) {
            MyComponent({
              title: 'Miss:func', func: () => {
                this.dialogDismissParam = 'func'
                this.dialogController_withOtherAttr = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  onWillDismiss: (dismissDialog: DismissDialogAction) => {
                    if (this.dialogDismissParam == 'NA') {
                    }
                    if (this.dialogDismissParam == 'func') {
                      dismissDialog.dismiss()
                      console.log(`dialog close via onWillDismiss`)
                    }
                  },
                  maskRect: {
                    x: '0',
                    y: '50%',
                    width: '100%',
                    height: '100%'
                  },
                  autoCancel: true,
                  isModal: true,
                  showInSubWindow: false,
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'Miss: NA', func: () => {
                this.dialogDismissParam = 'NA'
                this.dialogController_withOtherAttr = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  onWillDismiss: (dismissDialog: DismissDialogAction) => {
                    if (this.dialogDismissParam == 'NA') {
                    }
                    if (this.dialogDismissParam == 'func') {
                      dismissDialog.dismiss()
                      console.log(`dialog close via onWillDismiss`)
                    }
                  },
                  maskRect: {
                    x: '0',
                    y: '50%',
                    width: '100%',
                    height: '100%'
                  },
                  autoCancel: true,
                  isModal: true,
                  showInSubWindow: false,
                  backgroundColor: '#B6C5D1'
                })
              }
            })

            MyComponent({
              title: 'Modal: true', func: () => {
                this.dialogDismissParam = 'func'
                this.dialogController_withOtherAttr = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  onWillDismiss: (dismissDialog: DismissDialogAction) => {
                    if (this.dialogDismissParam == 'NA') {
                    }
                    if (this.dialogDismissParam == 'func') {
                      dismissDialog.dismiss()
                      console.log(`dialog close via onWillDismiss`)
                    }
                  },
                  maskRect: {
                    x: '0',
                    y: '50%',
                    width: '100%',
                    height: '100%'
                  },
                  autoCancel: true,
                  isModal: true,
                  showInSubWindow: false,
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'Modal: false', func: () => {
                this.dialogDismissParam = 'func'
                this.dialogController_withOtherAttr = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  onWillDismiss: (dismissDialog: DismissDialogAction) => {
                    if (this.dialogDismissParam == 'NA') {
                    }
                    if (this.dialogDismissParam == 'func') {
                      dismissDialog.dismiss()
                      console.log(`dialog close via onWillDismiss`)
                    }
                  },
                  maskRect: {
                    x: '0',
                    y: '50%',
                    width: '100%',
                    height: '100%'
                  },
                  autoCancel: true,
                  isModal: false,
                  showInSubWindow: false,
                  backgroundColor: '#B6C5D1'
                })
              }
            })
          }

          Row({ space: 3 }) {
            MyComponent({
              title: 'Auto: true', func: () => {
                this.dialogDismissParam = 'func'
                this.dialogController_withOtherAttr = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  onWillDismiss: (dismissDialog: DismissDialogAction) => {
                    if (this.dialogDismissParam == 'NA') {
                    }
                    if (this.dialogDismissParam == 'func') {
                      dismissDialog.dismiss()
                      console.log(`dialog close via onWillDismiss`)
                    }
                  },
                  maskRect: {
                    x: '0',
                    y: '50%',
                    width: '100%',
                    height: '100%'
                  },
                  autoCancel: true,
                  isModal: true,
                  showInSubWindow: false,
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'Auto: false', func: () => {
                this.dialogDismissParam = 'func'
                this.dialogController_withOtherAttr = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  onWillDismiss: (dismissDialog: DismissDialogAction) => {
                    if (this.dialogDismissParam == 'NA') {
                    }
                    if (this.dialogDismissParam == 'func') {
                      dismissDialog.dismiss()
                      console.log(`dialog close via onWillDismiss`)
                    }
                  },
                  maskRect: {
                    x: '0',
                    y: '50%',
                    width: '100%',
                    height: '100%'
                  },
                  autoCancel: false,
                  isModal: true,
                  showInSubWindow: false,
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'SubWindow: true', func: () => {
                this.dialogDismissParam = 'func'
                this.dialogController_withOtherAttr = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  onWillDismiss: (dismissDialog: DismissDialogAction) => {
                    if (this.dialogDismissParam == 'NA') {
                    }
                    if (this.dialogDismissParam == 'func') {
                      dismissDialog.dismiss()
                      console.log(`dialog close via onWillDismiss`)
                    }
                  },
                  maskRect: {
                    x: '0',
                    y: '50%',
                    width: '100%',
                    height: '100%'
                  },
                  autoCancel: true,
                  isModal: true,
                  showInSubWindow: true,
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'SubWindow: false', func: () => {
                this.dialogDismissParam = 'func'
                this.dialogController_withOtherAttr = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  onWillDismiss: (dismissDialog: DismissDialogAction) => {
                    if (this.dialogDismissParam == 'NA') {
                    }
                    if (this.dialogDismissParam == 'func') {
                      dismissDialog.dismiss()
                      console.log(`dialog close via onWillDismiss`)
                    }
                  },
                  maskRect: {
                    x: '0',
                    y: '50%',
                    width: '100%',
                    height: '100%'
                  },
                  autoCancel: true,
                  isModal: true,
                  showInSubWindow: false,
                  backgroundColor: '#B6C5D1'
                })
              }
            })
          }

          Text('CustomDialog: withOtherAttr')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController_withOtherAttr != null) {
                this.dialogController_withOtherAttr.open()
              }
            })
        }
        .columnStyle()

        Column({ space: 5 }) {
          Text(`onWillDismiss和Toast组合测试:`)
            .paramTextStyle()
          Text('showToast')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: 'Message Info',
                  duration: 4000
                });
              } catch (error) {
                let message = (error as BusinessError).message
                let code = (error as BusinessError).code
                console.error(`showToast args error code is ${code}, message is ${message}`);
              }
              ;
            })
          Text('CustomDialog: withToast')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController_withToast != null) {
                this.dialogController_withToast.open()
              }
            })
        }
        .columnStyle()

        //
        Text(`验证自定义弹窗radius/border/size/shadow:`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`自定义弹窗size和radius/border/shadow的组合测试:`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'width: 240', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  width: 240,
                  height: 240,

                  cornerRadius: '20%',
                  borderWidth: '1%',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    color: '#392F49',
                    offsetX: 20,
                    offsetY: 20
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'width: 320', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  width: 320,
                  height: 240,

                  cornerRadius: '20%',
                  borderWidth: '1%',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    color: '#392F49',
                    offsetX: 20,
                    offsetY: 20
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'width: 400', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  width: 400,
                  height: 240,

                  cornerRadius: '20%',
                  borderWidth: '1%',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    color: '#392F49',
                    offsetX: 20,
                    offsetY: 20
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'height: 300', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  width: 320,
                  height: 300,

                  cornerRadius: '20%',
                  borderWidth: '1%',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    color: '#392F49',
                    offsetX: 20,
                    offsetY: 20
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'height: 480', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  width: 320,
                  height: 480,

                  cornerRadius: '20%',
                  borderWidth: '1%',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    color: '#392F49',
                    offsetX: 20,
                    offsetY: 20
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
          }

          Text(`dialogSize: withRadius_Border_Shadow`)
            .key(`dialogSize: withRadius_Border_Shadow`)
            .fontSize(13)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController_withOptions != null) {
                this.dialogController_withOptions.open()
              }
            })
          Text(`自定义弹窗customStyle和radius/border/shadow/size的组合测试:`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'customStyle: F', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),
                  customStyle: false,

                  width: 320,
                  height: 400,

                  cornerRadius: '24vp',
                  borderWidth: '2vp',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    color: '#392F49',
                    offsetX: 20,
                    offsetY: 20
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'customStyle: T', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),
                  customStyle: true,

                  width: 320,
                  height: 400,

                  cornerRadius: '24vp',
                  borderWidth: '2vp',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    color: '#392F49',
                    offsetX: 20,
                    offsetY: 20
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
          }

          Text(`customStyle: withRadius_Border_Size_Shadow`)
            .key(`customStyle: withRadius_Border_Size_Shadow`)
            .fontSize(13)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController_withOptions != null) {
                this.dialogController_withOptions.open()
              }
            })

          Text(`自定义弹窗模式和阴影绘制:`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'isModal: F', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  isModal: false,
                  borderWidth: '2vp',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    type: 7,
                    color: Color.Orange,
                    offsetX: 30,
                    offsetY: 30,
                    fill: true
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'isModal: T', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  isModal: true,
                  borderWidth: '2vp',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    type: 7,
                    color: Color.Orange,
                    offsetX: 30,
                    offsetY: 30,
                    fill: true
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'subWindow: F', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  showInSubWindow: false,
                  borderWidth: '2vp',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    type: 7,
                    color: Color.Orange,
                    offsetX: 30,
                    offsetY: 30,
                    fill: true
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
            MyComponent({
              title: 'subWindow: T', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  showInSubWindow: true,
                  borderWidth: '2vp',
                  borderColor: Color.Blue,
                  shadow: {
                    radius: 10,
                    type: 7,
                    color: Color.Orange,
                    offsetX: 30,
                    offsetY: 30,
                    fill: true
                  },
                  backgroundColor: '#B6C5D1'
                })
              }
            })
          }

          Text(`dialogShadow: withModal_subWindow`)
            .key(`dialogShadow: withModal_subWindow`)
            .fontSize(13)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController_withOptions != null) {
                this.dialogController_withOptions.open()
              }
            })
        }
        .columnStyle()

        Text(`验证自定义弹窗subWindow和bgColor/blurStyle组合测试:`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Row({ space: 3 }) {
            MyComponent({
              title: 'subWindow: 0', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  showInSubWindow: false,
                  backgroundColor: '#B6C5D1',
                  backgroundBlurStyle: BlurStyle.BACKGROUND_THIN
                })
              }
            })
            MyComponent({
              title: 'subWindow: 1', func: () => {
                this.dialogController_withOptions = new CustomDialogController({
                  builder: CustomDialogControllerExample({
                    textValue: $textValue,
                    inputValue: $inputValue,
                    cancel: this.onCancel,
                    confirm: this.onAccept,
                  }),

                  showInSubWindow: true,
                  backgroundColor: '#B6C5D1',
                  backgroundBlurStyle: BlurStyle.BACKGROUND_THIN
                })
              }
            })
          }

          Text(`dialogSubWindow: bgColor_blurStyle`)
            .key(`dialogSubWindow: bgColor_blurStyle`)
            .fontSize(13)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController_withOptions != null) {
                this.dialogController_withOptions.open()
              }
            })

        }
        .columnStyle()
      }
      .width('100%')

    }
    .padding(10)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}