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

import { BusinessError } from '@ohos.base';
import window from '@ohos.window';
import promptAction from '@ohos.promptAction'

@CustomDialog
struct CustomDialogInput {
  controller?: CustomDialogController
  controller_richEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller_richEditor };
  controller_richEditor2: RichEditorController = new RichEditorController();
  options2: RichEditorOptions = { controller: this.controller_richEditor2 };
  controller_textArea: TextAreaController = new TextAreaController()
  controller_textInput: TextInputController = new TextInputController()

  build() {
    Column({ space: 5 }) {
      Row() {
        TextInput({ placeholder: '普通TextInput' }).enterKeyType(EnterKeyType.Send).key('TextInput_01').borderWidth(1)
        Search({ placeholder: '普通Search' }).key('Search_01').borderWidth(1)
      }

      Row() {
        TextArea({ placeholder: '普通TextArea' })
          .borderWidth(1)
          .key('TextArea_01')
          .defaultFocus(false)
        RichEditor(this.options)
          .placeholder('普通RichEditor')
          .borderWidth(1)
          .key('RichEditor_01')
      }

      Row() {
        TextInput({ placeholder: '绑定自定义键盘的TextInput', controller: this.controller_textInput })
          .borderWidth(1)
          .customKeyboard(CustomKeyboardBuilderG(), { supportAvoidance: true })
          .key('TextInput_02')
        Search({ placeholder: '绑定自定义键盘的Search' })
          .borderWidth(1)
          .customKeyboard(CustomKeyboardBuilderG(), { supportAvoidance: true })
          .key('Search_02')
      }

      Row() {
        TextArea({ placeholder: '绑定自定义键盘的TextArea', controller: this.controller_textArea })
          .borderWidth(1)
          .customKeyboard(CustomKeyboardBuilderG(), { supportAvoidance: true })
          .key('TextArea_02')
        RichEditor(this.options2)
          .borderWidth(1)
          .placeholder('绑定自定义键盘的RichEditor')
          .customKeyboard(CustomKeyboardBuilderG(), { supportAvoidance: true })
          .key('RichEditor_02')
      }

      Button('点我关闭弹框').fontSize(10).onClick(() => {
        this.controller!.close()
      })
        .focusOnTouch(true)
    }.width('50%').padding(10)
  }
}

//构造自定义弹窗默认获焦
@CustomDialog
struct CustomDialogInputSec {
  controller?: CustomDialogController
  controller_richEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller_richEditor };
  controller_richEditor2: RichEditorController = new RichEditorController();
  options2: RichEditorOptions = { controller: this.controller_richEditor2 };
  controller_textArea: TextAreaController = new TextAreaController()
  controller_textInput: TextInputController = new TextInputController()

  build() {
    Column({ space: 5 }) {
      Row() {
        TextInput({ placeholder: '普通TextInput' }).enterKeyType(EnterKeyType.Send).key('TextInput_01').borderWidth(1)
        Search({ placeholder: '普通Search' }).key('Search_01').borderWidth(1)
      }

      Row() {
        TextArea({ placeholder: '普通TextArea' }).defaultFocus(true)
          .borderWidth(1)
          .key('TextArea_01')
        RichEditor(this.options)
          .placeholder('普通RichEditor')
          .borderWidth(1)
          .key('RichEditor_01')
      }

      Button('点我关闭弹框').fontSize(10).onClick(() => {
        this.controller!.close()
      })
        .focusOnTouch(true)
    }.width('50%').padding(10)
  }
}

// 自定义键盘组件
@Builder
function CustomKeyboardBuilderG() {
  Column() {
    Grid() {
      ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
        GridItem() {
          Button(item + '')
            .width(110)
        }
      })
    }.maxCount(3).columnsGap(20).rowsGap(30).padding(15)
  }.backgroundColor(Color.Gray)
}

@Builder
export function SoftKeyboardLevel01Builder(name: string, param: Object) {
  SoftKeyboardLevel01()
}

@Entry
@Component
struct SoftKeyboardLevel01 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State supportAvoidance: boolean | undefined = undefined
  controller_textArea: TextAreaController = new TextAreaController()
  controller_textInput: TextInputController = new TextInputController()
  controller_richEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller_richEditor };
  controller_richEditor2: RichEditorController = new RichEditorController();
  options2: RichEditorOptions = { controller: this.controller_richEditor2 };
  dialog_subWindow: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogInput(),
    autoCancel: true,
    alignment: DialogAlignment.Center,
    offset: { dx: 0, dy: -20 },
    gridCount: 4,
    showInSubWindow: true,
    maskColor: '#33000000',
    isModal: false,
    customStyle: false,
    cornerRadius: 10,
    backgroundColor: Color.Orange
  })
  dialog_curWindow: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogInputSec(),
    autoCancel: true,
    alignment: DialogAlignment.Center,
    offset: { dx: 0, dy: -20 },
    gridCount: 4,
    showInSubWindow: false,
    maskColor: '#33000000',
    isModal: false,
    customStyle: false,
    cornerRadius: 10,
    backgroundColor: Color.Orange
  })
  @State showPopupInCurWindow: boolean = false
  @State showPopupInSubWindow: boolean = false
  @State showSheet: boolean = false
  @State column_h: number = 100
  @State can_focus: boolean = true

  //空的自定义键盘
  @Builder
  CustomKeyboardBuilderNull() {
  }

  // 自定义键盘组件1
  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Row({ space: 2 }) {
        Button('x_textInput').onClick(() => {
          // 关闭自定义键盘
          this.controller_textInput.stopEditing()
        })
          .key('Button_01')
        Button('x_textArea').onClick(() => {
          // 关闭自定义键盘
          this.controller_textArea.stopEditing()
        })
          .key('Button_02')
      }

      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.inputValue += item
            })
              .key('Button_03' + item)
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray)
  }
  // 自定义键盘组件2
  @Builder
  CustomKeyboardBuilder2() {
    Column() {
      Row({ space: 2 }) {
        Button('x_textInput').onClick(() => {
          // 关闭自定义键盘
          this.controller_textInput.stopEditing()
        })
          .key('Button_04')
        Button('x_textArea').onClick(() => {
          // 关闭自定义键盘
          this.controller_textArea.stopEditing()
        })
          .key('Button_05')
      }

      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.inputValue += item
            })
              .key('Button_06' + item)
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }
    .backgroundColor(Color.Blue)
    .position({ x: 0, y: 540 })
    .focusable(true)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Text('窗口焦点切换基本功能验证(点击可获焦)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .focusable(true)
            .focusOnTouch(true)
            .key('Text_05')
          Column() {
            Text('点击关闭自定义输入法').fontSize(9).fontColor(0xCCCCCC).width('100%')
            Row({ space: 2 }) {
              Button('stopEditing_textInput').fontSize(12).onClick(() => {
                this.controller_textInput.stopEditing()
              })
                .key('Button_07')
              Button('stopEditing_textArea').fontSize(12).onClick(() => {
                this.controller_textArea.stopEditing()
              })
                .key('Button_08')
            }
          }

          Column() {
            Text('点击弹出窗口后触发输入法弹出').fontSize(9).fontColor(0xCCCCCC).width('100%')
            Flex({ justifyContent: FlexAlign.SpaceBetween }) {
              Button('系统子窗true')
                .layoutWeight(1)
                .fontSize(10)
                .key('Button_09')
                .onClick(() => {
                  let windowClass: window.Window | undefined = undefined;
                  let config: window.Configuration = {
                    name: 'WindowT',
                    windowType: window.WindowType.TYPE_FLOAT,
                    ctx: getContext(this)
                  };
                  try {
                    window.createWindow(config, (err: BusinessError, data) => {
                      const errCode: number = err.code;
                      if (errCode) {
                        console.error('Failed to create the window. Cause: ' + JSON.stringify(err));
                        return;
                      }
                      windowClass = data;
                      console.info('Succeeded in creating the window.');
                      // windowClass.setNeedKeepKeyboard(true)
                      windowClass.moveWindowTo(200, 200)
                      windowClass.keepKeyboardOnFocus(true) // 子窗true，保留其他窗口创建的软键盘
                      windowClass.resize(1000, 1500).then(() => {
                        console.log('AppSubWindow resetSize Done');
                        try {
                          windowClass!.setUIContent('pages/normalKeyboard/SoftKeyboardLevel0_2').then(() => {
                            windowClass!.setWindowBackgroundColor('#00FF00');
                            console.log('subWindow loadContent Done');
                            windowClass!.showWindow().then(() => {
                              console.log('subWindow show Done');
                            })
                          })
                        } catch (exception) {
                          console.error('Failed to load the content. Cause:' + JSON.stringify(exception));
                        }
                        ;
                      });
                    });
                  } catch (exception) {
                    console.error('Failed to create the window. Cause: ' + JSON.stringify(exception));
                  }
                })
                .padding(0)
                .width('15%')

              Button('系统子窗false')
                .layoutWeight(1)
                .fontSize(10)
                .key('Button_10')
                .onClick(() => {
                  let windowClass2: window.Window | undefined = undefined;
                  let config: window.Configuration = {
                    name: 'WindowF',
                    windowType: window.WindowType.TYPE_FLOAT,
                    // ctx: (GlobalContext.getContext().getObject('app_context') as Context)
                    ctx: getContext(this)
                  };
                  try {
                    window.createWindow(config, (err: BusinessError, data) => {
                      const errCode: number = err.code;
                      if (errCode) {
                        console.error('Failed to create the window. Cause: ' + JSON.stringify(err));
                        return;
                      }
                      windowClass2 = data;
                      windowClass2.keepKeyboardOnFocus(false) // 子窗false，不保留其他窗口创建的软键盘
                      console.info('Succeeded in creating the window.');
                      // windowClass.setNeedKeepKeyboard(true)
                      windowClass2.moveWindowTo(400, 200)
                      windowClass2.resize(1000, 1500).then(() => {
                        console.log('AppSubWindow2 resetSize Done');
                        try {
                          windowClass2!.setUIContent('pages/normalKeyboard/SoftKeyboardLevel0_2').then(() => {
                            windowClass2!.setWindowBackgroundColor('#00FF00');
                            console.log('subWindow loadContent Done');
                            windowClass2!.showWindow().then(() => {
                              console.log('subWindow show Done');
                            })
                          })
                        } catch (exception) {
                          console.error('Failed to load the content. Cause:' + JSON.stringify(exception));
                        }
                        ;
                      });
                    });
                  } catch (exception) {
                    console.error('Failed to create the window. Cause: ' + JSON.stringify(exception));
                  }
                })
                .padding(0)
                .width('15%')

              Button('自定义弹窗')
                .layoutWeight(1)
                .fontSize(10)
                .key('Button_11')
                .onClick(() => {
                  if (this.dialog_curWindow != null) {
                    this.dialog_curWindow.open()
                  }
                })
                .padding(0)
                .width('15%')

              Button('自定义弹窗_子窗')
                .layoutWeight(1)
                .fontSize(10)
                .key('Button_12')
                .onClick(() => {
                  if (this.dialog_subWindow != null) {
                    this.dialog_subWindow.open()
                  }
                })
                .padding(0)
                .width('15%')
            }
          }.padding(0)

          Column() {
            Text('点击控制自定义键盘避让，默认不避让')
              .fontSize(9)
              .width('100%')
            Row() {
              Button('true')
                .onClick(() => {
                  this.supportAvoidance = true
                })
                .key('Button_13')

              Button('false')
                .onClick(() => {
                  this.supportAvoidance = false
                })
                .key('Button_14')

              Button('undefined')
                .onClick(() => {
                  this.supportAvoidance = undefined
                })
                .key('Button_15')

            }.height('40%')

            Text('点击按钮控制Column的高度,用来构造输入组件被输入法挡住的场景')
              .fontSize(9)
              .width('100%')
            Row() {
              Button('点我height+100').fontSize(10).onClick(() => {
                this.column_h += 100
              })
                .key('Button_16')

              Button('点我height-100').fontSize(10).onClick(() => {
                this.column_h -= 100
              })
                .key('Button_17')

            }.height('40%')
          }.backgroundColor(Color.Pink).padding(10).height(this.column_h)

          Text('绑定普通软键盘的输入组件，点击弹出toast，持续十秒，软键盘会避让toast')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .key('Text_06')
            .onClick(() => {
              try {
                promptAction.showToast({
                  message: 'Message Info',
                  duration: 10000
                });
              } catch (error) {
                let message = (error as BusinessError).message
                let code = (error as BusinessError).code
                console.error(`showToast args error code is ${code}, message is ${message}`);
              }
              ;
            })
          Row({ space: 5 }) {
            Column() {
              TextInput({ placeholder: '普通TextInput', controller: this.controller_textInput })
                .focusable(this.can_focus)
                .enableKeyboardOnFocus(false)
                .defaultFocus(false)
                .border({ width: 1, color: Color.Red })
                .enterKeyType(EnterKeyType.Go)
                .onSubmit((enterKey) => {
                  console.info('zzz TextInput1 onSubmit=' + EnterKeyType[enterKey])
                })
                .onEditChange((isEditing) => {
                  console.info('zzz TextInput1 onEditChange=' + isEditing)
                })
                .key('TextInput_03')
              Search({ placeholder: '普通Search' }).borderWidth(1).key('Search_03')
            }.layoutWeight(2)

            TextArea({ placeholder: '普通TextArea', controller: this.controller_textArea })
              .layoutWeight(1)
              .borderWidth(1)
              .enableKeyboardOnFocus(false)
              .key('TextArea_03')
            RichEditor(this.options)
              .layoutWeight(1)
              .borderWidth(1)
              .key('RichEditor_03')
              .onReady(() => {
                this.controller_richEditor.addTextSpan('012',
                  {
                    style:
                    {
                      fontColor: Color.Orange,
                      fontSize: 30
                    }
                  })
                this.controller_richEditor.addImageSpan($r('app.media.startIcon'),
                  {
                    imageStyle:
                    {
                      size: ['57px', '57px']
                    }
                  })
                this.controller_richEditor.addTextSpan('45',
                  {
                    style:
                    {
                      fontColor: Color.Black,
                      fontSize: 30
                    }
                  })
                this.controller_richEditor.addTextSpan('wfe',
                  {
                    style:
                    {
                      fontColor: Color.Black,
                      fontSize: 30
                    }
                  })
              })
              .aboutToIMEInput((value: RichEditorInsertValue) => {
                console.info('zzz RichEditor1 aboutToIMEInput=' + JSON.stringify(value))
                return true;
              })
              .onIMEInputComplete((value: RichEditorTextSpanResult) => {
                console.info('zzz RichEditor1 onIMEInputComplete=' + JSON.stringify(value))
              })
              .aboutToDelete((value: RichEditorDeleteValue) => {
                console.info('zzz RichEditor1 aboutToDelete=' + JSON.stringify(value))
                return true;
              })
              .onDeleteComplete(() => {
                console.log('zzz RichEditor1 onDeleteComplete')
              })

          }

          Text('绑定了自定义键盘的输入组件').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 5 }) {
            Column() {
              TextInput({
                text: this.inputValue,
                placeholder: '自定义键盘TextInput',
                controller: this.controller_textInput
              })
                .borderWidth(1)
                .defaultFocus(true)
                .enableKeyboardOnFocus(true)
                .enterKeyType(EnterKeyType.Send)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
                .margin(5)
                .border({ width: 1 })
                .onSubmit((enterKey) => {
                  console.info('TextInput2 onSubmit=' + EnterKeyType[enterKey])
                })
                .onEditChange((isEditing) => {
                  console.info('TextInput2 onEditChange=' + isEditing)
                })
                .key('TextInput_04')
              Search({ placeholder: '自定义键盘Search', value: this.inputValue })
                .customKeyboard(this.CustomKeyboardBuilder2(), { supportAvoidance: this.supportAvoidance })
                .borderWidth(1)
                .margin(5)
                .key('Search_04')
            }
            .layoutWeight(2)

            TextArea({
              placeholder: '绑定自定义键盘的TextArea',
              text: this.inputValue,
              controller: this.controller_textArea
            })
              .layoutWeight(1)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
              .margin(5)
              .border({ width: 1 })
              .enableKeyboardOnFocus(true)
              .key('TextArea_04')

            RichEditor(this.options2)
              .layoutWeight(1)
              .borderWidth(1)
              .key('RichEditor_04')
              .onReady(() => {
                this.controller_richEditor2.addTextSpan('012',
                  {
                    style:
                    {
                      fontColor: Color.Orange,
                      fontSize: 30
                    }
                  })
                this.controller_richEditor2.addImageSpan($r('app.media.startIcon'),
                  {
                    imageStyle:
                    {
                      size: ['57px', '57px']
                    }
                  })
                this.controller_richEditor2.addTextSpan('45',
                  {
                    style:
                    {
                      fontColor: Color.Black,
                      fontSize: 30
                    }
                  })
              })
              .aboutToIMEInput((value: RichEditorInsertValue) => {
                console.info('zzz RichEditor2 aboutToIMEInput=' + JSON.stringify(value))
                return true;
              })
              .onIMEInputComplete((value: RichEditorTextSpanResult) => {
                console.info('zzz RichEditor2 onIMEInputComplete=' + JSON.stringify(value))
              })
              .aboutToDelete((value: RichEditorDeleteValue) => {
                console.info('zzz RichEditor2 aboutToDelete=' + JSON.stringify(value))
                return true;
              })
              .onDeleteComplete(() => {
                console.log('zzz RichEditor2 onDeleteComplete')
              })
              .customKeyboard(this.CustomKeyboardBuilder2(), { supportAvoidance: this.supportAvoidance })
          }

          Text('其他场景').fontSize(9).fontColor(0xCCCCCC).width('100%')
          Row({ space: 5 }) {
            Search({ placeholder: 'enableKeyboardOnFocus为false的Search' })
              .borderWidth(1)
              .layoutWeight(1)
              .borderWidth(1)
              .enableKeyboardOnFocus(false)
              .key('Search_05')
            Search({ placeholder: '禁用focus的Search' })
              .borderWidth(1)
              .layoutWeight(1)
              .borderWidth(1)
              .focusable(false)
              .key('Search_06')
            TextInput({ placeholder: '空自定义', controller: this.controller_textInput })
              .layoutWeight(1)
              .borderWidth(1)
              .type(InputType.Number)
              .enterKeyType(EnterKeyType.Send)
              .customKeyboard(this.CustomKeyboardBuilderNull())//空的自定义键盘，不崩溃即可
              .key('TextInput_05')
          }

        }
        .width('100%').padding(5)
      }
    }
    .title('SoftKeyboardLevel01')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
