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

import {MyComponent} from '../../../../common/MyComponent'
import {CustomDialogControllerExample} from '../../../../common/CustomDialogController'
import {dismissTestList} from  '../params/WillDismiss'

@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct CustomDialogTestLevel0_5 {
  scroller: Scroller = new Scroller()
  @State textValue: string = ''
  @State inputValue: string = 'click me'

  @State index: number[] = [0, 0, 0]
  @State dialogDismissParam: string = 'func'

  dialogControllerUnsetDismiss: CustomDialogController|null = new CustomDialogController({
    builder: CustomDialogControllerExample({
      textValue: $textValue,
      inputValue: $inputValue,
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),

    backgroundColor: '#A6C2BE'
  })
  dialogController: CustomDialogController|null = new CustomDialogController({
    builder: CustomDialogControllerExample({
      textValue: $textValue,
      inputValue: $inputValue,
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),

    onWillDismiss: (dismissDialog: DismissDialogAction) => {
      // 1
      if (dismissTestList[this.index[0]] == 'NA') {
      }
      // 2
      if (dismissTestList[this.index[0]] == 'undefined') {
        undefined
      }
      // 3
      if (dismissTestList[this.index[0]] == 'DismissDialog.dismiss()') {
        dismissDialog.dismiss()
        console.log(`dialog close via onWillDismiss`)
      }
      // 4
      if (dismissTestList[this.index[0]] == 'reason_undefined_0') {
        if (dismissDialog.reason == undefined) {
        }
      }
      // 5
      if (dismissTestList[this.index[0]] == 'reason_undefined_1') {
        if (dismissDialog.reason == undefined) {
          dismissDialog.dismiss()
          console.log(`dialog close via onWillDismiss`)
        }
      }
      // 6
      if (dismissTestList[this.index[0]] == 'reason_index_0') {
        if (dismissDialog.reason == 0) {
        }
        if (dismissDialog.reason == 1) {
        }
        if (dismissDialog.reason == 2) {
        }
      }
      // 7
      if (dismissTestList[this.index[0]] == 'reason_index_1') {
        if (dismissDialog.reason == 0) {
          console.info('customDialog closed via onWillDismiss of reason 0')
          dismissDialog.dismiss()
        }
        if (dismissDialog.reason == 1) {
          console.info('customDialog closed via onWillDismiss of reason 1')
          dismissDialog.dismiss()
        }
        if (dismissDialog.reason == 2) {
          dismissDialog.dismiss()
          console.info('customDialog closed via onWillDismiss of reason 2')
        }
      }
      // 8
      if (dismissTestList[this.index[0]] == 'reason_enum_0') {
        if (dismissDialog.reason == DismissReason.PRESS_BACK) {
        }
        if (dismissDialog.reason == DismissReason.TOUCH_OUTSIDE) {
        }
        if (dismissDialog.reason == DismissReason.CLOSE_BUTTON) {
        }
      }
      // 9
      if (dismissTestList[this.index[0]] == 'reason_enum_1') {
        if (dismissDialog.reason == DismissReason.PRESS_BACK) {
          dismissDialog.dismiss()
        }
        if (dismissDialog.reason == DismissReason.TOUCH_OUTSIDE) {
          dismissDialog.dismiss()
        }
        if (dismissDialog.reason == DismissReason.CLOSE_BUTTON) {
          dismissDialog.dismiss()
          console.log(`dialog close via onWillDismiss`)
        }
      }
    },

    maskRect: {x: '0', y: '0', width: '100%', height: '100%'},
    autoCancel: true,
    isModal: true,
    showInSubWindow: false,
  })

  // 在自定义组件即将析构销毁时将dialogController删除和置空
  aboutToDisappear() {
    // 将dialogController置空
    this.dialogControllerUnsetDismiss = null
    this.dialogController = null
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
    Scroll(this.scroller){
      Column({space: 5}){
        Text(`验证自定义弹窗onWillDismiss:`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`验证自定义弹窗不设置onWillDismiss:`)
            .paramTextStyle()
          Text('CustomDialog: unset onWillDismiss')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogControllerUnsetDismiss != null) {
                this.dialogControllerUnsetDismiss.open()
              }
            })
        }
        .columnStyle()
        Column({space: 5}){
          Text(`自定义弹窗设置onWillDismiss: \n切换测试参数: ${dismissTestList[this.index[0]]}`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${dismissTestList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({ title: 'Test0+', func: () => {
              this.index[0]++
              if (this.index[0] == dismissTestList.length) {
                this.index[0] = 0
              }
            } })
            MyComponent({ title: 'Test0-', func: () => {
              this.index[0]--
              if (this.index[0] <= -1) {
                this.index[0] = dismissTestList.length - 1
              }
            }})
          }
          Text('CustomDialog: onWillDismiss')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController != null) {
                this.dialogController.open()
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