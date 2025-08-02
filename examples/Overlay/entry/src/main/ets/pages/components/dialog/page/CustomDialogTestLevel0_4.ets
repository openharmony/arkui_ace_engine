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
 
import {MyComponent} from '../../../../common/MyComponent'
import {backgroundColorTestList} from '../params/ResourceColor'
import {blurStyleTestList} from '../params/BlurStyle'
import {CustomDialogControllerExample} from '../../../../common/CustomDialogController'

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
struct CustomDialogTestLevel0_4 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  @State textValue: string = ''
  @State inputValue: string = 'click me'
  @State showInSubWindow?: boolean = false
  @State isModal?: boolean = true

  dialogController: CustomDialogController|null = new CustomDialogController({
    builder: CustomDialogControllerExample({
      textValue: $textValue,
      inputValue: $inputValue,
      cancel: this.onCancel,
      confirm: this.onAccept,
    }),
    cornerRadius: 10,

    showInSubWindow: false,
    isModal: true,

    backgroundColor: backgroundColorTestList[this.index[0]],
  })
  // 在自定义组件即将析构销毁时将dialogController删除和置空
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
    Scroll(this.scroller){
      Column({space: 5}){
        Text(`验证自定义弹窗showInSubWindow:`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`切换showInSubWindow参数: ${this.showInSubWindow}`)
            .paramTextStyle()
          Row({space:3}){
            MyComponent({title: 'Sub: False', func: () => {
              this.showInSubWindow = false
              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                alignment: DialogAlignment.CenterEnd,
                offset: {dx: 100, dy:0},
                showInSubWindow: false,
                isModal: true,
              })
            }})
            MyComponent({title: 'Sub: True', func: () => {
              this.showInSubWindow = true
              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                alignment: DialogAlignment.CenterEnd,
                offset: {dx: 100, dy:0},
                showInSubWindow: true,
                isModal: true,
              })
            }})
            MyComponent({title: 'Sub: UN', func: () => {
              this.showInSubWindow = undefined
              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                alignment: DialogAlignment.CenterEnd,
                offset: {dx: 100, dy:0},
                showInSubWindow: undefined,
                isModal: true,
              })
            }})
          }
          Text('CustomDialog: SubWindow')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController != null) {
                this.dialogController.open()
              }
            })
        }
        .columnStyle()

        Text(`验证自定义弹窗isModal:`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`切换isModal参数: ${this.isModal}`)
            .paramTextStyle()
          Row({space:3}){
            MyComponent({title: 'Modal: False', func: () => {
              this.isModal = false
              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                maskRect: {width: '95%', height: '95%', },
                backgroundColor: '#A6C2BE',
                maskColor: '#BBB2C8',
                isModal: false,
              })
            }})
            MyComponent({title: ' Modal: True', func: () => {
              this.isModal = true
              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                maskRect: {width: '95%', height: '95%', },
                backgroundColor: '#A6C2BE',
                maskColor: '#C2B1C8',
                isModal: true,
              })
            }})
            MyComponent({title: 'Modal: UN', func: () => {
              this.isModal = undefined
              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                maskRect: {width: '95%', height: '95%', },
                backgroundColor: '#A6C2BE',
                maskColor: '#D1BFC5',
                isModal: undefined,
              })
            }})
          }
          Text('CustomDialog: IsModal')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController != null) {
                this.dialogController.open()
              }
            })

        }
        .columnStyle()

        Text(`验证自定义弹窗backgrounColor:`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`切换backgroundColor参数:`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${backgroundColorTestList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({ title: 'Test0+', func: () => {
              this.index[0]++
              if (this.index[0] == backgroundColorTestList.length) {
                this.index[0] = 0
              }

              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                backgroundColor: backgroundColorTestList[this.index[0]]
              })
            } })
            MyComponent({ title: 'Test0-', func: () => {
              this.index[0]--
              if (this.index[0] <= -1) {
                this.index[0] = backgroundColorTestList.length - 1
              }
              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                backgroundColor: backgroundColorTestList[this.index[0]]
              })
            } })
          }
          Text('CustomDialog: backgroundColor')
            .backgroundColor(Color.Orange)
            .onClick(() => {
              if (this.dialogController != null) {
                this.dialogController.open()
              }
            })
        }
        .columnStyle()
        Text(`验证自定义弹窗blurStyle:`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`切换blurStyle参数:`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[1] + 1}` + ' / ')
              .fontSize(9)
            Text(`${blurStyleTestList.length}`)
              .key('paramSets_key_1')
              .fontSize(9)
            MyComponent({ title: 'Test1+', func: () => {
              this.index[1]++
              if (this.index[1] == blurStyleTestList.length) {
                this.index[1] = 0
              }

              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                backgroundColor: '#ffc9eeea',
                backgroundBlurStyle: blurStyleTestList[this.index[1]]
              })
            } })
            MyComponent({ title: 'Test1-', func: () => {
              this.index[1]--
              if (this.index[1] <= -1) {
                this.index[1] = blurStyleTestList.length - 1
              }
              this.dialogController = new CustomDialogController({
                builder: CustomDialogControllerExample({
                  textValue: $textValue,
                  inputValue: $inputValue,
                  cancel: this.onCancel,
                  confirm: this.onAccept,
                }),
                cornerRadius: 10,

                backgroundColor: '#ffc9eeea',
                backgroundBlurStyle: blurStyleTestList[this.index[1]]
              })
            } })
          }
          Text('CustomDialog: blurStyle')
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
}