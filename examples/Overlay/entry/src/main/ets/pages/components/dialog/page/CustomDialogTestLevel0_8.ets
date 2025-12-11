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

import {CustomDialogExample, CustomDialog_Blur} from '../../../../common/CustomDialogController'
import { LengthMetrics } from '@kit.ArkUI'


@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Select) function selectStyle() {
  .width('50%')
  .controlSize(ControlSize.SMALL)
  .selected(0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct CustomDialogTestLevel0_8 {
  scroller: Scroller = new Scroller()

  // 自定义键盘组件
  @State text: string = ''
  controller: TextInputController = new TextInputController()
  @State inputValue_custom: string = '';
  @Builder
  CustomKeyboardBuilder() {
    Column() {
      // Button('X').onClick(() => {
      //   // 关闭自定义键盘
      //   this.controller.stopEditing();
      // })
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#', '', '↓', '←'], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .key(item.toString())
              .width(110).onClick(() => {
              if (item === '↓') {
                this.controller.stopEditing();
              }
              else if (item === '←') {
                this.inputValue_custom = this.inputValue_custom.slice(0, -1);
              }
              else {
                this.inputValue_custom += item
              }
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }
    .backgroundColor('#19000000')
    .padding({top: 5, left: 10, right: 10, bottom: 30})
  }

  // 系统软键盘
  @State textValue: string = ''
  @State inputValue: string = 'click me'
  @State dialogControllerInfo: string = '不设置distance'
  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      textValue: $textValue,
      inputValue: $inputValue
    }),
  })


  build() {
    Scroll(this.scroller){
      Column({space: 5}) {
        Text(`验证CustomDialog的避让键盘属性`)
          .paramTextStyle()
        Column({space: 5}){
          TextInput()
            .key('system_keyboard')
            .backgroundColor('#80889292')

          TextInput({ controller: this.controller, text: this.inputValue_custom })// 绑定自定义键盘
            .customKeyboard(this.CustomKeyboardBuilder(), {supportAvoidance: true})
            .margin(10).border({ width: 1 })
            .key('custom_keyboard')
        }
        .columnStyle()


        Column({space: 5}){
          Text('CustomDialog的keyboardAvoidMode属性')
            .paramTextStyle()
          Text(`CustomDialog: AvoidMode_Default`)
            .componentTextStyle()
            .onClick( () => {
              this.dialogController = new CustomDialogController({
                keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                height: '50%',
                borderWidth: 1,
                cornerRadius: 10,
                alignment: DialogAlignment.Bottom,
                offset: {dx: 0, dy: -40},
                showInSubWindow: false,
                isModal: false,
                builder: CustomDialogExample({
                  textValue: $textValue,
                  inputValue: $inputValue
                }),
              })
              this.dialogController?.open()
            })
          Text(`CustomDialog: AvoidMode_None`)
            .componentTextStyle()
            .onClick( () => {
              this.dialogController = new CustomDialogController({
                keyboardAvoidMode: KeyboardAvoidMode.NONE,
                keyboardAvoidDistance:  LengthMetrics.vp(60),

                height: '50%',
                borderWidth: 1,
                cornerRadius: 10,
                alignment: DialogAlignment.Bottom,
                offset: {dx: 0, dy: -40},
                showInSubWindow: false,
                isModal: false,
                builder: CustomDialogExample({
                  textValue: $textValue,
                  inputValue: $inputValue
                }),
              })
              this.dialogController?.open()
            })

          Text(`子窗CustomDialog: AvoidMode_Default`)
            .componentTextStyle()
            .onClick( () => {
              this.dialogController = new CustomDialogController({
                keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                height: '50%',
                borderWidth: 1,
                cornerRadius: 10,
                alignment: DialogAlignment.Bottom,
                offset: {dx: 0, dy: -40},
                showInSubWindow: true,
                isModal: false,
                builder: CustomDialogExample({
                  textValue: $textValue,
                  inputValue: $inputValue
                }),
              })
              this.dialogController?.open()
            })
        }
        .columnStyle()

        Column({space: 5}){
          Text(`CustomDialog设置避让,验证avoidDistance属性`)
            .paramTextStyle()
          Select(([
            {value: '不设置distance'},
            {value: '设置undefined'},
            {value: '设置16vp'},
            {value: '设置16px'},
            {value: '设置16fp'},
            {value: '设置16lpx'},
            {value: '设置50%'},
            {value: '设置-16vp'},
            {value: '设置0vp'},
            {value: '设置400px'},
          ]))
            .selectStyle()
            .onSelect((idx, value: string) => {
              switch (value) {
                case value:
                  console.info(`onSelect value ${value}`)
                  this.dialogControllerInfo = value
                  break;
              }
            })
            .key('select_avoidDistance')

          Text(`子窗CustomDialog: AvoidDistance`)
            .componentTextStyle()
            .onClick( () => {
              if (this.dialogControllerInfo === '不设置distance') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置undefined') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance: undefined,
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置16vp') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance:  LengthMetrics.vp(16),
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置16px') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance:  LengthMetrics.px(16),
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置16lpx') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance:  LengthMetrics.lpx(16),
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置16fp') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance:  LengthMetrics.fp(16),
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置50%') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance:  LengthMetrics.percent(50),
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置-16vp') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance:  LengthMetrics.vp(-16),
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置0vp') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance:  LengthMetrics.vp(0),
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }
              if (this.dialogControllerInfo === '设置400px') {
                this.dialogController = new CustomDialogController({
                  keyboardAvoidDistance:  LengthMetrics.px(400),
                  keyboardAvoidMode: KeyboardAvoidMode.DEFAULT,

                  height: '50%',
                  borderWidth: 1,
                  cornerRadius: 10,
                  alignment: DialogAlignment.Bottom,
                  offset: {dx: 0, dy: -40},
                  showInSubWindow: true,
                  isModal: false,
                  builder: CustomDialogExample({
                    textValue: $textValue,
                    inputValue: $inputValue
                  }),
                })
              }

              this.dialogController?.open()
            })

        }
        .columnStyle()

      }
      .width('100%')
    }
    .scrollBar(BarState.Off)
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }
}