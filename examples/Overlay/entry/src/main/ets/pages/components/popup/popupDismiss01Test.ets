/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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



import promptAction from '@ohos.promptAction';
import { BusinessError } from '@ohos.base';
import { MyComponent } from './MyComponenet'

@Builder
export function PopupDismiss01Builder(name: string, param: Object) {
  PopupDismiss01Example()
}

export const DismissTestList: string[] = [
  // 1. 回调事件为空
  'NA',
  // 2. 回调事件undefined
  'undefined',
  // 3. 回调事件设置func
  'dismissPopupAction.dismiss()',

  // 4.reason设置undefined, 回调事件禁止
  'reason_undefined_0',
  // 5.reason设置undefined, 回调事件允许
  'reason_undefined_1',

  // 6.reason判断index, 回调事件禁止
  'reason_index_0',
  // 7.reason判断index, 回调事件允许
  'reason_index_1',

  // 8.reason判断枚举值, 回调事件禁止
  'reason_enum_0',
  // 9.reason判断枚举值, 回调事件允许
  'reason_enum_1',
]

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Column)
function columnStyle() {
  .borderWidth(0.5)
  .padding(10)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct PopupDismiss01Example {
  pathStack: NavPathStack = new NavPathStack()
  @State popupShowList: boolean[] = [false, false, false, false,]
  @State customPopupShowList: boolean[] = [false, false, false, false,]
  @State index: number[] = [0,]

  // popup构造器定义弹框内容
  @Builder
  PopupBuilder(index: number) {
    Column({ space: 2 }) {
      Text('Custom Popup')
      Text(`Close Popup`)
        .fontSize(13)
        .backgroundColor(Color.Orange)
        .onClick(() => {
          this.customPopupShowList[index] = false
        })
    }
    .padding(10)
  }

  //onWillDismiss
  @State popupDismiss: string = 'func'
  @State popupMask: boolean = true
  @State popupAutoCancel: boolean = true
  @State popupShowInSubWindow: boolean = false

  build() {
    NavDestination() {
      Column({ space: 5 }) {
        Text('验证Popup的onWillDismiss属性')
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`bindPopup不设置onWillDismiss:`)
            .paramTextStyle()
          //标准popup
          Text('bindPopup: unset onWillDismiss')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.popupShowList[0] = !this.popupShowList[0]
            })
            .bindPopup(this.popupShowList[0], {
              message: 'This is a popup with PopupOptions',
              primaryButton: {
                value: 'confirm',
                action: () => {
                  this.popupShowList[0] = !this.popupShowList[0]
                  console.info('confirm Button click')
                }
              },
              // 第二个按钮
              secondaryButton: {
                value: 'cancel',
                action: () => {
                  this.popupShowList[0] = !this.popupShowList[0]
                  console.info('cancel Button click')
                }
              },
              onStateChange: (e) => {
                console.info(JSON.stringify(e.isVisible))
                if (!e.isVisible) {
                  this.popupShowList[0] = false
                }
              }
            })
          //自定义popup
          Text('bindCustomPopup: unset onWillDismiss')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.customPopupShowList[0] = !this.customPopupShowList[0]
            })
            .bindPopup(this.customPopupShowList[0], {
              builder: this.PopupBuilder(0),
              mask: { color: '#33000000' },
              popupColor: Color.Orange,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.customPopupShowList[0] = false
                }
              }
            })
        }
        .columnStyle()

        Column({ space: 5 }) {
          Text(`bindPopup设置onWillDismiss:`)
            .paramTextStyle()
          Text(`切换dismiss参数:`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${DismissTestList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == DismissTestList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = DismissTestList.length - 1
                }
              }
            })
          }

          //标准popup
          Text('bindPopup: onWillDismiss')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.popupShowList[1] = !this.popupShowList[1]
            })
            .bindPopup(this.popupShowList[1], {
              onWillDismiss: (dismissPopupAction: DismissPopupAction) => {
                //不设置
                if (DismissTestList[this.index[0]] == 'NA') {
                }
                //设置undefined
                if (DismissTestList[this.index[0]] == 'undefined') {
                  undefined
                }
                //设置关闭dismiss()函数
                if (DismissTestList[this.index[0]] == 'dismissPopupAction.dismiss()') {
                  dismissPopupAction.dismiss()
                  console.log(`---LCG---  popup close via onWillDismiss`)
                }

                //验证reason为undefined的情况
                if (DismissTestList[this.index[0]] == 'reason_undefined_0') {
                  if (dismissPopupAction.reason == undefined) {
                  }
                }
                if (DismissTestList[this.index[0]] == 'reason_undefined_1') {
                  if (dismissPopupAction.reason == undefined) {
                    dismissPopupAction.dismiss()
                    console.log(`---LCG---  popup close via onWillDismiss`)
                  }
                }

                //验证reason不同索引值，验证调用和不调用dismiss()
                if (DismissTestList[this.index[0]] == 'reason_index_0') {
                  if (dismissPopupAction.reason == 0) {
                  }
                  if (dismissPopupAction.reason == 1) {
                  }
                  if (dismissPopupAction.reason == 2) {
                  }
                }
                if (DismissTestList[this.index[0]] == 'reason_index_1') {
                  if (dismissPopupAction.reason == 0) {
                    dismissPopupAction.dismiss()
                  }
                  if (dismissPopupAction.reason == 1) {
                    dismissPopupAction.dismiss()
                  }
                  if (dismissPopupAction.reason == 2) {
                    dismissPopupAction.dismiss()
                    console.log(`---LCG---  popup close via onWillDismiss`)
                  }
                }

                //验证reason不同枚举值，验证调用和不调用dismiss()
                if (DismissTestList[this.index[0]] == 'reason_enum_0') {
                  if (dismissPopupAction.reason == DismissReason.PRESS_BACK) {
                  }
                  if (dismissPopupAction.reason == DismissReason.TOUCH_OUTSIDE) {
                  }
                  if (dismissPopupAction.reason == DismissReason.CLOSE_BUTTON) {
                  }
                  /*                    if (dismissPopupAction.reason == 7) {
                                      }*/
                }
                if (DismissTestList[this.index[0]] == 'reason_enum_1') {
                  if (dismissPopupAction.reason == DismissReason.PRESS_BACK) {
                    dismissPopupAction.dismiss()
                  }
                  if (dismissPopupAction.reason == DismissReason.TOUCH_OUTSIDE) {
                    dismissPopupAction.dismiss()
                  }
                  if (dismissPopupAction.reason == DismissReason.CLOSE_BUTTON) {
                    dismissPopupAction.dismiss()
                    console.log(`---LCG---  popup close via onWillDismiss`)
                  }
                }
              },

              message: 'This is a popup with PopupOptions',
              primaryButton: {
                value: 'confirm',
                action: () => {
                  this.popupShowList[1] = !this.popupShowList[1]
                  console.info('confirm Button click')
                }
              },
              // 第二个按钮
              secondaryButton: {
                value: 'cancel',
                action: () => {
                  this.popupShowList[1] = !this.popupShowList[1]
                  console.info('cancel Button click')
                }
              },
              onStateChange: (e) => {
                console.info(JSON.stringify(e.isVisible))
                if (!e.isVisible) {
                  this.popupShowList[1] = false
                }
              }
            })
          //自定义popup
          Text('bindCustomPopup: onWillDismiss')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.customPopupShowList[1] = !this.customPopupShowList[1]
            })
            .bindPopup(this.customPopupShowList[1], {
              onWillDismiss: (dismissPopupAction: DismissPopupAction) => {
                //不设置
                if (DismissTestList[this.index[0]] == 'NA') {
                }
                //设置undefined
                if (DismissTestList[this.index[0]] == 'undefined') {
                  undefined
                }
                //设置关闭dismiss()函数
                if (DismissTestList[this.index[0]] == 'dismissPopupAction.dismiss()') {
                  dismissPopupAction.dismiss()
                  console.log(`---LCG---  popup close via onWillDismiss`)
                }

                //验证reason为undefined的情况
                if (DismissTestList[this.index[0]] == 'reason_undefined_0') {
                  if (dismissPopupAction.reason == undefined) {
                  }
                }
                if (DismissTestList[this.index[0]] == 'reason_undefined_1') {
                  if (dismissPopupAction.reason == undefined) {
                    dismissPopupAction.dismiss()
                    console.log(`---LCG---  popup close via onWillDismiss`)
                  }
                }

                //验证reason不同索引值，验证调用和不调用dismiss()
                if (DismissTestList[this.index[0]] == 'reason_index_0') {
                  if (dismissPopupAction.reason == 0) {
                  }
                  if (dismissPopupAction.reason == 1) {
                  }
                  if (dismissPopupAction.reason == 2) {
                  }
                }
                if (DismissTestList[this.index[0]] == 'reason_index_1') {
                  if (dismissPopupAction.reason == 0) {
                    dismissPopupAction.dismiss()
                  }
                  if (dismissPopupAction.reason == 1) {
                    dismissPopupAction.dismiss()
                  }
                  if (dismissPopupAction.reason == 2) {
                    dismissPopupAction.dismiss()
                    console.log(`---LCG---  popup close via onWillDismiss`)
                  }
                }

                //验证reason不同枚举值，验证调用和不调用dismiss()
                if (DismissTestList[this.index[0]] == 'reason_enum_0') {
                  if (dismissPopupAction.reason == DismissReason.PRESS_BACK) {
                  }
                  if (dismissPopupAction.reason == DismissReason.TOUCH_OUTSIDE) {
                  }
                  if (dismissPopupAction.reason == DismissReason.CLOSE_BUTTON) {
                  }
                }
                if (DismissTestList[this.index[0]] == 'reason_enum_1') {
                  if (dismissPopupAction.reason == DismissReason.PRESS_BACK) {
                    dismissPopupAction.dismiss()
                  }
                  if (dismissPopupAction.reason == DismissReason.TOUCH_OUTSIDE) {
                    dismissPopupAction.dismiss()
                  }
                  if (dismissPopupAction.reason == DismissReason.CLOSE_BUTTON) {
                    dismissPopupAction.dismiss()
                    console.log(`---LCG---  popup close via onWillDismiss`)
                  }
                }
              },

              builder: this.PopupBuilder(1),
              mask: { color: '#33000000' },
              popupColor: Color.Orange,
              onStateChange: (e) => {
                if (!e.isVisible) {
                  this.customPopupShowList[1] = false
                }
              }
            })
        }
        .columnStyle()

        //组合测试
        Column({ space: 5 }) {
          Text(`bindPopup设置onWillDismiss和其他属性的组合测试:`)
            .paramTextStyle()
          Text(`bindPopup设置showInSubWindow: ${this.popupShowInSubWindow}`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'subWindow: T', func: () => {
                this.popupShowInSubWindow = true
              }
            })
            MyComponent({
              title: 'subWindow: F', func: () => {
                this.popupShowInSubWindow = false
              }
            })
          }
          Text(`bindPopup设置mask: ${this.popupMask}`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'mask: T', func: () => {
                this.popupMask = true
              }
            })
            MyComponent({
              title: 'mask: F', func: () => {
                this.popupMask = false
              }
            })
          }

          Text(`bindPopup设置autoCancel: ${this.popupAutoCancel}`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'autoCancel: T', func: () => {
                this.popupAutoCancel = true
              }
            })
            MyComponent({
              title: 'autoCancel: F', func: () => {
                this.popupAutoCancel = false
              }
            })
          }

          Text(`bindPopup: withOtherAttr`)
            .key(`bindPopup: withOtherAttr`)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.popupShowList[2] = !this.popupShowList[2]
            })
            .bindPopup(this.popupShowList[2], {
              showInSubWindow: this.popupShowInSubWindow,
              mask: this.popupMask,
              autoCancel: this.popupAutoCancel,

              onWillDismiss: (dismissPopupAction: DismissPopupAction) => {
                if (this.popupDismiss == 'NA') {

                } else if (this.popupDismiss == 'func') {
                  dismissPopupAction.dismiss()
                  console.log(`---LCG---  dialog close via onWillDismiss`)
                } else {
                  console.log('---LCG---  dismissDialog error')
                }
              },

              message: 'This is a popup with PopupOptions',
              primaryButton: {
                value: 'confirm',
                action: () => {
                  this.popupShowList[2] = !this.popupShowList[2]
                  console.info('confirm Button click')
                }
              },
              // 第二个按钮
              secondaryButton: {
                value: 'cancel',
                action: () => {
                  this.popupShowList[2] = !this.popupShowList[2]
                  console.info('cancel Button click')
                }
              },
              onStateChange: (e) => {
                console.info(JSON.stringify(e.isVisible))
                if (!e.isVisible) {
                  this.popupShowList[2] = false
                }
              }
            })
          Text(`bindCustomPopup: withOtherAttr`)
            .key(`bindCustomPopup: withOtherAttr`)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.customPopupShowList[2] = !this.customPopupShowList[2]
            })
            .bindPopup(this.customPopupShowList[2], {
              showInSubWindow: this.popupShowInSubWindow,
              mask: this.popupMask,
              autoCancel: this.popupAutoCancel,

              onWillDismiss: (dismissPopupAction: DismissPopupAction) => {
                if (this.popupDismiss == 'NA') {

                } else if (this.popupDismiss == 'func') {
                  dismissPopupAction.dismiss()
                  console.log(`---LCG---  dialog close via onWillDismiss`)
                } else {
                  console.log('---LCG---  dismissDialog error')
                }
              },
              builder: this.PopupBuilder(2),
              popupColor: Color.Orange,
              onStateChange: (e) => {
                console.info(JSON.stringify(e.isVisible))
                if (!e.isVisible) {
                  this.customPopupShowList[2] = false
                }
              }
            })
        }
        .columnStyle()

        Column({ space: 5 }) {
          Text(`bindPopup设置onWillDismiss和showToast的组合测试:`)
            .paramTextStyle()
          Text(`bindCustomPopup: withShowToast`)
            .key(`bindCustomPopup: withShowToast`)
            .backgroundColor(Color.Orange)
            .onClick(() => {
              this.customPopupShowList[3] = !this.customPopupShowList[3]
              setTimeout(() => {
                try {
                  promptAction.showToast({
                    message: 'Message Info',
                    bottom: 220,
                    duration: 6000
                  });
                } catch (error) {
                  let message = (error as BusinessError).message
                  let code = (error as BusinessError).code
                  console.error(`showToast args error code is ${code}, message is ${message}`);
                }
                ;
              }, 500)
            })
            .bindPopup(this.customPopupShowList[3], {

              onWillDismiss: (dismissPopupAction: DismissPopupAction) => {
                dismissPopupAction.dismiss()
              },
              builder: this.PopupBuilder(3),
              popupColor: Color.Pink,
              backgroundBlurStyle: BlurStyle.NONE,
              onStateChange: (e) => {
                console.info(JSON.stringify(e.isVisible))
                if (!e.isVisible) {
                  this.customPopupShowList[3] = false
                }
              }
            })
        }
        .columnStyle()
      }.width('100%').margin({ top: 5 })
    }
    .title('PopupDismiss01Test')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
