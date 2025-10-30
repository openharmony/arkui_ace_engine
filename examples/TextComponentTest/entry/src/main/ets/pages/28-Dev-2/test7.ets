/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@CustomDialog
struct CustomDialogExample11 {
  controller: RichEditorController = new RichEditorController()
  controller1?: CustomDialogController
  @Builder CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.controller.addTextSpan(item + '', {
                offset: this.controller.getCaretOffset(),
                style:
                {
                  fontColor: Color.Orange,
                  fontSize: 30
                }
              })
              this.controller.setCaretOffset(this.controller.getCaretOffset() + item.toString().length)
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray)
  }
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  build() {
    Column() {
      RichEditor({ controller: this.controller })
        // 绑定自定义键盘
        .onReady(() => {
          this.controller.addTextSpan('绑定自定义键盘',
            {
              style:
              {
                fontColor: Color.Orange,
                fontSize: 30
              }
            })
        })
        .customKeyboard(this.CustomKeyboardBuilder()).margin(10).border({ width: 1 })
        .height(100)
        .borderWidth(1)
        .borderColor(Color.Red)
        .width('100%')
      Button('关闭弹窗')
        .onClick(() => {
          if (this.controller1 != undefined) {
            this.controller1.close()
          }
        })
    }
  }
}
@CustomDialog
struct CustomDialogExampleTwo {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  build() {
    Column() {
      TextInput({placeholder:'系统键盘'})
      Button('关闭弹窗')
        .onClick(() => {
          if (this.controller != undefined) {
            this.controller.close()
          }
        })
    }
  }
}
@CustomDialog
struct CustomDialogExampleThree {
  @State color: Color = Color.Blue
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }
  build() {
    Column() {
      Button('获焦变红，失焦变蓝')
        .backgroundColor(this.color)
        .onFocus(() => {
          this.color = Color.Red
        })
        .onBlur(() => {
          this.color = Color.Blue
        })
      Button('关闭弹窗')
        .onClick(() => {
          if (this.controller != undefined) {
            this.controller.close()
          }
        })
    }
  }
}
@Entry
@Component
struct CustomDialogUser11 {
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample11(),
    autoCancel: true,
    onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
      console.info('reason=' + JSON.stringify(dismissDialogAction.reason))
      console.log('dialog onWillDismiss')
      if (dismissDialogAction.reason == DismissReason.PRESS_BACK) {
        dismissDialogAction.dismiss()
      }
      if (dismissDialogAction.reason == DismissReason.TOUCH_OUTSIDE) {
        dismissDialogAction.dismiss()
      }
    },
    alignment: DialogAlignment.Top,
    offset: { dx: 0, dy: -20 },
    customStyle: false,
    cornerRadius: 20,
    width: 300,
    height: 200,
    borderWidth: 1,
    borderStyle: BorderStyle.Dashed, //使用borderStyle属性，需要和borderWidth属性一起使用
    borderColor: Color.Blue, //使用borderColor属性，需要和borderWidth属性一起使用
    backgroundColor: Color.White,
    shadow: ({
      radius: 20,
      color: Color.Grey,
      offsetX: 50,
      offsetY: 0
    }),
  })
  dialogController2: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExampleTwo(),
    autoCancel: true,
    onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
      console.info('reason=' + JSON.stringify(dismissDialogAction.reason))
      console.log('dialog onWillDismiss')
      if (dismissDialogAction.reason == DismissReason.PRESS_BACK) {
        dismissDialogAction.dismiss()
      }
      if (dismissDialogAction.reason == DismissReason.TOUCH_OUTSIDE) {
        dismissDialogAction.dismiss()
      }
    },
    alignment: DialogAlignment.Top,
    offset: { dx: 0, dy: -20 },
    customStyle: false,
    cornerRadius: 20,
    width: 300,
    height: 200,
    borderWidth: 1,
    borderStyle: BorderStyle.Dashed, //使用borderStyle属性，需要和borderWidth属性一起使用
    borderColor: Color.Blue, //使用borderColor属性，需要和borderWidth属性一起使用
    backgroundColor: Color.White,
    shadow: ({
      radius: 20,
      color: Color.Grey,
      offsetX: 50,
      offsetY: 0
    }),
  })
  dialogController3: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExampleThree(),
    autoCancel: true,
    onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
      console.info('reason=' + JSON.stringify(dismissDialogAction.reason))
      console.log('dialog onWillDismiss')
      if (dismissDialogAction.reason == DismissReason.PRESS_BACK) {
        dismissDialogAction.dismiss()
      }
      if (dismissDialogAction.reason == DismissReason.TOUCH_OUTSIDE) {
        dismissDialogAction.dismiss()
      }
    },
    alignment: DialogAlignment.Top,
    offset: { dx: 0, dy: -20 },
    customStyle: false,
    cornerRadius: 20,
    width: 300,
    height: 200,
    borderWidth: 1,
    borderStyle: BorderStyle.Dashed, //使用borderStyle属性，需要和borderWidth属性一起使用
    borderColor: Color.Blue, //使用borderColor属性，需要和borderWidth属性一起使用
    backgroundColor: Color.White,
    shadow: ({
      radius: 20,
      color: Color.Grey,
      offsetX: 50,
      offsetY: 0
    }),
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

  existApp() {
    console.info('Click the callback in the blank area')
  }

  build() {
    Column() {
      Button('自定义键盘')
        .onClick(() => {
          if (this.dialogController != null) {
            this.dialogController.open()
          }
        }).backgroundColor(0x317aff)
      Button('系统键盘')
        .onClick(() => {
          if (this.dialogController2 != null) {
            this.dialogController2.open()
          }
        }).backgroundColor(0x317aff)
      Button('不使用键盘')
        .onClick(() => {
          if (this.dialogController3 != null) {
            this.dialogController3.open()
          }
        }).backgroundColor(0x317aff)
    }.width('100%').margin({ top: 5 })
  }
}