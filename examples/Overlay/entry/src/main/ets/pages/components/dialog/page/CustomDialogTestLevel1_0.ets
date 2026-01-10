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

import {
  UpgradeDialog1,
  UpgradeDialog2,
  CustomDialogExample,
  MainCustomDialog,
  Scroll_CustomDialog
} from '../../../../common/CustomDialog'

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
struct CustomDialogTestLevel1_0 {
  scroller: Scroller = new Scroller()
  //button: click for two dialogs
  private customDialog: CustomDialogController = new CustomDialogController({
    builder: UpgradeDialog1(),
    customStyle: true, //问题：字会溢出去
    alignment: DialogAlignment.Bottom,
  })
  private uncustomDialog: CustomDialogController = new CustomDialogController({
    builder: UpgradeDialog2(),
    customStyle: false, //宽度根据栅格系统自适应，高度自适应子节点，最大为窗口高度的90%
    alignment: DialogAlignment.Top,
  })
  //button: click for subDialog
  @State textValue: string = ''
  @State inputValue: string = 'click me'
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      cancel: this.onCancel,
      confirm: this.onAccept,
      textValue: $textValue,
      inputValue: $inputValue
    }),
    cancel: this.exitApp,
    autoCancel: true,
    alignment: DialogAlignment.Default,
    gridCount: 4,
    customStyle: false,
    cornerRadius: 10,
  })
  //button: click for Subs
  @State inputValue_subs: string = 'click for Subs'
  controller_subs: CustomDialogController | null = new CustomDialogController({
    builder: MainCustomDialog({}),
    cancel: this.exitApp,
    autoCancel: true,
    alignment: DialogAlignment.Top,
    offset: { dx: 0, dy: 20 },
    gridCount: 4,
    customStyle: false,
    backgroundColor: 0xd9ffffff,
    cornerRadius: 10,
    showInSubWindow: false
  })
  //button: click for textInput and keyboard
  controller_textInput: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      cancel: this.onCancel,
      confirm: this.onAccept,
      textValue: $textValue,
      inputValue: $inputValue
    }),
    cancel: this.exitApp,
    autoCancel: true,
    alignment: DialogAlignment.Default,
    offset: { dx: 0, dy: 0 },
  })
  //button: click for scroll component
  controller_scroll: CustomDialogController | null = new CustomDialogController({
    builder: Scroll_CustomDialog({
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),
    cancel: this.exitApp,
    autoCancel: true,
    alignment: DialogAlignment.Default,
    backgroundColor: Color.Pink,
    cornerRadius: 10,
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

  exitApp() {
    console.info('Click the callback in the blank area')
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text('自定义弹窗:一个组件绑定多个弹窗')
          .paramTextStyle()
        Column({ space: 2 }) {
          Button('click for two dialogs')
            .onClick(() => {
              this.customDialog.open()
              this.uncustomDialog.open()
            }).backgroundColor(0x317aff)
        }.columnStyle()

        Text('自定义弹窗:自定义弹窗弹出子自定义弹窗')
          .paramTextStyle()
        Column({ space: 2 }) {
          Button('click for subDialog')
            .backgroundColor(0x317aff)
            .onClick(() => {
              if (this.dialogController != null) {
                this.dialogController.open()
              }
            })
        }.columnStyle()

        Text('自定义弹窗:自定义弹窗builder弹出其他弹窗类组件')
          .paramTextStyle()
        Column() {
          Button(this.inputValue_subs)
            .onClick(() => {
              if (this.controller_subs != null) {
                this.controller_subs.open()
              }
            }).backgroundColor(0x317aff)
        }
        .columnStyle()

        Text('自定义弹窗:Builder设置滚动容器')
          .paramTextStyle()
        Column() {
          Button('click for scroll')
            .onClick(() => {
              if (this.controller_scroll != null) {
                this.controller_scroll.open()
              }
            }).backgroundColor(0x317aff)
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(10)
    .align(Alignment.TopStart)
    .width('100%').height('100%')

  }
}