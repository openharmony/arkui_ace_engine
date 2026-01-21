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

import { MyComponent } from '../../../../common/MyComponent';
import { blurStyleTestList } from '../params/BlurStyle'
import { backgroundColorTestList } from '../params/ResourceColor'

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
struct AlertDialogTestLevel0_3 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]
  @State showInSubWindow?: boolean = false
  @State isModal?: boolean = true

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`验证警告弹窗showInSubWindow:`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`切换showInSubWindow参数: ${this.showInSubWindow}`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'Sub: False', func: () => {
                this.showInSubWindow = false
              }
            })
            MyComponent({
              title: 'Sub: True', func: () => {
                this.showInSubWindow = true
              }
            })
            MyComponent({
              title: 'Sub: UN', func: () => {
                this.showInSubWindow = undefined
              }
            })
          }

          Text('验证AlertDialog: SubWindow')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              AlertDialog.show(
                {
                  alignment: DialogAlignment.CenterEnd,
                  offset: { dx: 100, dy: 0 },

                  title: 'AlertDialog Title',
                  message: 'AlertDialog Message',
                  autoCancel: true,
                  confirm: {
                    value: 'button',
                    action: () => {
                      console.info('Button-clicking callback')
                    }
                  },
                  cancel: () => {
                    console.info('Closed callbacks')
                  }
                })
            })
        }
        .columnStyle()

        Text(`验证警告弹窗isModal:`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`切换isModal参数: ${this.isModal}`)
            .paramTextStyle()
          Row({ space: 3 }) {
            MyComponent({
              title: 'Modal: False', func: () => {
                this.isModal = false
              }
            })
            MyComponent({
              title: ' Modal: True', func: () => {
                this.isModal = true
              }
            })
            MyComponent({
              title: 'Modal: UN', func: () => {
                this.isModal = undefined
              }
            })
          }

          Text('验证AlertDialog: IsModal')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              AlertDialog.show(
                {
                  isModal: this.isModal,
                  maskRect: { width: '95%', height: '95%', },

                  title: 'AlertDialog Title',
                  message: 'AlertDialog Message',
                  autoCancel: true,
                  confirm: {
                    value: 'button',
                    action: () => {
                      console.info('Button-clicking callback')
                    }
                  },
                  cancel: () => {
                    console.info('Closed callbacks')
                  }
                })
            })

        }
        .columnStyle()

        Text(`验证警告弹窗backgrounColor和blurStyle:`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`切换backgroundColor参数:`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${backgroundColorTestList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == backgroundColorTestList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = backgroundColorTestList.length - 1
                }
              }
            })
          }

          Text(`切换backgroundBlurstyle参数:`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[1] + 1}` + ' / ')
              .fontSize(9)
            Text(`${blurStyleTestList.length}`)
              .key('paramSets_key_1')
              .fontSize(9)
            MyComponent({
              title: 'Test1+', func: () => {
                this.index[1]++
                if (this.index[1] == blurStyleTestList.length) {
                  this.index[1] = 0
                }
              }
            })
            MyComponent({
              title: 'Test1-', func: () => {
                this.index[1]--
                if (this.index[1] <= -1) {
                  this.index[1] = blurStyleTestList.length - 1
                }
              }
            })
          }

          Text('验证AlertDialog: Color_BlurStyle')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              AlertDialog.show(
                {
                  backgroundColor: backgroundColorTestList[this.index[0]],
                  backgroundBlurStyle: blurStyleTestList[this.index[1]],

                  title: 'AlertDialog Title',
                  message: 'AlertDialog Message',
                  autoCancel: true,
                  confirm: {
                    value: 'button',
                    action: () => {
                      console.info('Button-clicking callback')
                    }
                  },
                  cancel: () => {
                    console.info('Closed callbacks')
                  }
                })
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
}