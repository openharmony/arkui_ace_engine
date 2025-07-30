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
import router from '@ohos.router';

@Builder
export function PopupKeyboardBuilder(name: string, param: Object) {
  PopupKeyboardExample()
}

@Entry
@Component
struct PopupKeyboardExample {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State supportAvoidance: boolean | undefined = undefined
  controllerTextArea: TextAreaController = new TextAreaController()
  controllerTextInput: TextInputController = new TextInputController()
  controllerTextArea1: TextAreaController = new TextAreaController()
  controllerTextInput1: TextInputController = new TextInputController()
  controllerTextArea2: TextAreaController = new TextAreaController()
  controllerTextInput2: TextInputController = new TextInputController()
  controllerTextArea3: TextAreaController = new TextAreaController()
  controllerTextInput3: TextInputController = new TextInputController()
  controllerRichEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controllerRichEditor };
  controllerRichEditor2: RichEditorController = new RichEditorController();
  options2: RichEditorOptions = { controller: this.controllerRichEditor2 };
  @State showPopupInCurWindow: boolean = false
  @State showPopupInSubWindow: boolean = false
  @State showSheet1: boolean = false
  @State showSheet2: boolean = false
  @State showSheet3: boolean = false
  @State showBindContentCover: boolean = false
  @State columnH: number = 100
  @State canFocus: boolean = true
  @State keyHeight: number = 250
  @State showKeyboard: boolean = true;
  @State inputType: InputType = InputType.Normal;

  //空的自定义键盘
  @Builder
  CustomKeyboardBuilderNull() {
  }

  // 自定义键盘组件1
  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Row({ space: 2 }) {
        Button('高度+').onClick(() => {
          this.keyHeight += 10
        }).key('keyHeight1+')
        Button('x_textInput').onClick(() => {
          // 关闭自定义键盘
          this.controllerTextInput.stopEditing()
          this.controllerTextInput1.stopEditing()
          this.controllerTextInput2.stopEditing()
        })
          .key('Button_01')
        Button('x_textArea').onClick(() => {
          // 关闭自定义键盘
          this.controllerTextArea.stopEditing()
          this.controllerTextArea1.stopEditing()
          this.controllerTextArea2.stopEditing()
        })
          .key('Button_02')
        Button('高度-').onClick(() => {
          this.keyHeight -= 10
        }).key('keyHeight1-')
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
    .height(this.keyHeight)
  }

  // 自定义键盘组件2-设置了.position({x:0,y:540})
  @Builder
  CustomKeyboardBuilder2() {
    Column() {
      Row({ space: 2 }) {
        Button('x_textInput').onClick(() => {
          // 关闭自定义键盘
          this.controllerTextInput.stopEditing()
          this.controllerTextInput1.stopEditing()
          this.controllerTextInput2.stopEditing()
        })
          .key('Button_04')
        Button('x_textArea').onClick(() => {
          // 关闭自定义键盘
          this.controllerTextArea.stopEditing()
          this.controllerTextArea1.stopEditing()
          this.controllerTextArea2.stopEditing()
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

  // 自定义键盘组件-设置给底部RicheEditor使用
  @Builder
  CustomKeyboardBuilderRicheEditor() {
    Column() {
      Row() {
        Button('按钮高度+').onClick(() => {
          this.keyHeight += 10
        }).key('keyHeight2+')
        Button('按钮高度-').onClick(() => {
          this.keyHeight -= 10
        }).key('keyHeight2-')
      }

      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.controllerRichEditor2.addTextSpan(item + '', {
                offset: this.controllerRichEditor2.getCaretOffset(),
                style:
                {
                  fontColor: Color.Orange,
                  fontSize: 30
                }
              })
              this.controllerRichEditor2.setCaretOffset(this.controllerRichEditor2.getCaretOffset() +
              item.toString().length)
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray)
    .height(this.keyHeight)
  }

  // popup构造器定义弹框内容
  @Builder
  popupBuilder() {
    Column({ space: 5 }) {
      Text('点击跳转首页')
        .focusable(true)
        .onClick(() => {
          router.pushUrl({
            url: '/'
          })
        })
        .borderWidth(1)
        .backgroundColor(Color.Blue)
        .fontColor(Color.White)
        .key('Text_01')
      TextInput({ placeholder: '普通TextInput' }).enterKeyType(EnterKeyType.Send).key('TextInput_01').borderWidth(1)
      Search({ placeholder: '普通Search' }).key('Search_01').borderWidth(1)
      TextArea({ placeholder: '普通TextArea' })
        .borderWidth(1)
        .key('TextArea_01')
      RichEditor(this.options)
        .placeholder('普通RichEditor')
        .borderWidth(1)
        .key('RichEditor_01')
      TextInput({ placeholder: '绑定自定义键盘的TextInput', controller: this.controllerTextInput })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
        .key('TextInput_02')
      Search({ placeholder: '绑定自定义键盘的Search' })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
        .key('Search_02')
      TextArea({ placeholder: '绑定自定义键盘的TextArea', controller: this.controllerTextArea })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder2(), { supportAvoidance: this.supportAvoidance })
        .key('TextArea_02')
      RichEditor(this.options2)
        .borderWidth(1)
        .placeholder('绑定自定义键盘的RichEditor')
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('RichEditor_02')
    }.width('50%')
    .padding(10)
  }

  // popup构造器定义弹框内容默认获焦
  @Builder
  popupBuilderSec() {
    Column({ space: 5 }) {
      Text('点击跳转首页')
        .focusable(true)
        .key('index')
        .onClick(() => {
          router.pushUrl({
            url: '/'
          })
        })
        .borderWidth(1)
        .backgroundColor(Color.Blue)
        .fontColor(Color.White)
        .key('Text_01')
      TextInput({ placeholder: '普通TextInput' })
        .enterKeyType(EnterKeyType.Send)
        .key('TextInput_01')
        .borderWidth(1)
      Search({ placeholder: '普通Search' })
        .key('Search_01')
        .borderWidth(1)
      TextArea({ placeholder: '普通TextArea' })
        .defaultFocus(true)
        .focusable(true)
        .enableKeyboardOnFocus(true)
        .borderWidth(1)
        .key('TextArea_01')
      RichEditor(this.options)
        .placeholder('普通RichEditor')
        .borderWidth(1)
        .key('RichEditor_01')
    }
    .width('50%')
    .padding(10)
  }

  // 半模态绑定窗口
  @Builder
  myBuilderSheet(defaultFocus: boolean) {
    Column({ space: 5 }) {
      Text('点击跳转首页')
        .focusable(true)
        .onClick(() => {
          router.pushUrl({
            url: '/'
          })
        })
        .borderWidth(1)
        .backgroundColor(Color.Blue)
        .fontColor(Color.White)
        .key('Text_02')
      TextInput({ placeholder: '普通TextInput' })
        .enterKeyType(EnterKeyType.Send)
        .key('TextInput_03')
      Search({ placeholder: '普通Search' })
        .key('Search_03')
        .borderWidth(1)
      TextArea({ placeholder: '普通TextArea' })
        .borderWidth(1)
        .defaultFocus(defaultFocus)
        .key('TextArea_03')
      RichEditor(this.options)
        .placeholder('普通RichEditor')
        .borderWidth(1)
        .key('RichEditor_03')
      TextInput({ placeholder: '绑定自定义键盘的TextInput', controller: this.controllerTextInput })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
        .key('TextInput_04')
      Search({ placeholder: '绑定自定义键盘的Search' })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
        .key('Search_04')
      TextArea({ placeholder: '绑定自定义键盘的TextArea', controller: this.controllerTextArea })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder2(), { supportAvoidance: this.supportAvoidance })
        .key('TextArea_04')
      RichEditor(this.options2)
        .borderWidth(1)
        .placeholder('绑定自定义键盘的RichEditor')
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('RichEditor_04')
    }.width('50%').padding(10)
  }

  // 全模态绑定窗口
  @Builder
  myBuilder() {
    Column({ space: 5 }) {
      Button('close')
        .margin(10)
        .fontSize(20)
        .onClick(() => {
          this.showBindContentCover = false;
        })
        .key('Button_07')
      Text('点击跳转首页')
        .focusable(true)
        .onClick(() => {
          router.pushUrl({
            url: '/'
          })
        })
        .borderWidth(1)
        .backgroundColor(Color.Blue)
        .fontColor(Color.White)
        .key('Text_03')
      TextInput({ placeholder: '普通TextInput' })
        .enterKeyType(EnterKeyType.Send)
        .key('TextInput_05')
      Search({ placeholder: '普通Search' })
        .key('Search_05').borderWidth(1)
      TextArea({ placeholder: '普通TextArea' })
        .borderWidth(1)
        .defaultFocus(true)
        .key('TextArea_05')
      RichEditor(this.options)
        .placeholder('普通RichEditor')
        .borderWidth(1)
        .key('RichEditor_05')
      TextInput({ placeholder: '绑定自定义键盘的TextInput', controller: this.controllerTextInput })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
        .key('TextInput_06')
      Search({ placeholder: '绑定自定义键盘的Search' })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: this.supportAvoidance })
        .key('Search_06')
      TextArea({ placeholder: '绑定自定义键盘的TextArea', controller: this.controllerTextArea })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder2(), { supportAvoidance: this.supportAvoidance })
        .key('TextArea_06')
      RichEditor(this.options2)
        .borderWidth(1)
        .placeholder('绑定自定义键盘的RichEditor')
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key('RichEditor_06')
    }
    .width('100%')
    .height('100%')
    .justifyContent(FlexAlign.Center)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 5 }) {
          Row({ space: 5 }) {
            Text('点击可跳系统键盘')
              .focusable(true)
              .onClick(() => {
                router.pushUrl({
                  url: 'pages/normalKeyboard/SoftKeyboardLevel0_4'
                })
              })
              .borderWidth(1)
              .key('Text_04')
            Text('点击可跳自定义键盘')
              .focusable(true)
              .onClick(() => {
                router.pushUrl({
                  url: 'pages/normalKeyboard/SoftKeyboardLevel0_1'
                })
              })
              .borderWidth(1)
              .key('Text_05')
            Text('点击跳转首页')
              .focusable(true)
              .onClick(() => {
                router.pushUrl({
                  url: '/'
                })
              })
              .borderWidth(1)
              .key('Text_06')
          }

          Text('窗口焦点切换基本功能验证(点击可获焦)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .focusable(true)
            .focusOnTouch(true)
            .key('Text_07')
          Column() {
            Text('点击关闭自定义输入法').fontSize(9).fontColor(0xCCCCCC).width('100%')
            Row({ space: 2 }) {
              Button('stopEditing_textInput').fontSize(12).onClick(() => {
                this.controllerTextInput1.stopEditing()
                this.controllerTextInput2.stopEditing()
              })
                .key('Button_9')
              Button('stopEditing_textArea').fontSize(12).onClick(() => {
                this.controllerTextArea1.stopEditing()
                this.controllerTextArea2.stopEditing()

              })
                .key('Button_10')
            }
          }

          Column({ space: 5 }) {
            Text('点击弹出窗口测试输入法').fontSize(9).fontColor(0xCCCCCC).width('100%')
            Flex({ justifyContent: FlexAlign.SpaceBetween }) {
              Button('Popup_当前窗口')
                .layoutWeight(1)
                .fontSize(10)
                .onClick(() => {
                  this.showPopupInCurWindow = !this.showPopupInCurWindow
                })
                .bindPopup(this.showPopupInCurWindow, {
                  builder: this.popupBuilderSec,
                  showInSubWindow: false,
                  mask: false,
                  onStateChange: (e) => {
                    console.info('zzz onStateChange1=' + e.isVisible)
                    if (!e.isVisible) {
                      this.showPopupInCurWindow = false
                    }
                  }
                })
                .padding(0)
                .width('15%')
                .key('Button_11')
              Button('Popup_子窗口')
                .layoutWeight(1)
                .fontSize(10)
                .onClick(() => {
                  this.showPopupInSubWindow = !this.showPopupInSubWindow
                })
                .bindPopup(this.showPopupInSubWindow, {
                  builder: this.popupBuilder,
                  showInSubWindow: true,
                  mask: false,
                  onStateChange: (e) => {
                    console.info('zlTest onStateChange2=' + e.isVisible);
                    if (!e.isVisible) {
                      this.showPopupInSubWindow = false
                    }
                  }
                })
                .padding(0)
                .width('15%')
                .key('Button_12')
              Button('全模态')
                .layoutWeight(1)
                .fontSize(10)
                .onClick(() => {
                  this.showBindContentCover = true
                })
                .bindContentCover($$this.showBindContentCover, this.myBuilder(), {
                  modalTransition: ModalTransition.DEFAULT,
                  backgroundColor: Color.Pink,
                })
                .padding(0)
                .width('15%')
                .key('Button_13')
            }.padding(0)

            Flex({ justifyContent: FlexAlign.SpaceBetween }) {
              Button('半模态_底部OVERLAY')
                .layoutWeight(1)
                .fontSize(10)
                .onClick(() => {
                  this.showSheet1 = true
                })
                .bindSheet($$this.showSheet1, this.myBuilderSheet(true), {
                  height: 300,
                  backgroundColor: Color.Green,
                  enableOutsideInteractive: true,
                  mode: SheetMode.OVERLAY,
                  preferType: SheetType.BOTTOM
                })
                .padding(0)
                .width('15%')
                .key('Button_14')
              Button('半模态_居中EMBEDDED')
                .layoutWeight(1)
                .fontSize(10)
                .onClick(() => {
                  this.showSheet2 = true
                })
                .bindSheet($$this.showSheet2, this.myBuilderSheet(false), {
                  height: 300,
                  backgroundColor: Color.Green,
                  enableOutsideInteractive: false,
                  mode: SheetMode.EMBEDDED,
                  preferType: SheetType.CENTER
                })
                .padding(0)
                .width('15%')
                .key('Button_15')
              Button('半模态_跟手OVERLAY')
                .layoutWeight(1)
                .fontSize(10)
                .onClick(() => {
                  this.showSheet3 = true
                })
                .bindSheet($$this.showSheet3, this.myBuilderSheet(true), {
                  height: 300,
                  backgroundColor: Color.Green,
                  enableOutsideInteractive: true,
                  mode: SheetMode.OVERLAY,
                  preferType: SheetType.POPUP
                })
                .padding(0)
                .width('15%')
                .key('Button_16')
            }.padding(0)

            Column() {
              Text('点击控制自定义键盘避让，默认不避让')
                .fontSize(9)
                .width('100%')
              Row() {
                Button('true').fontSize(10)
                  .onClick(() => {
                    this.supportAvoidance = true
                  })
                  .key('Button_17')
                Button('false').fontSize(10)
                  .onClick(() => {
                    this.supportAvoidance = false
                  })
                  .key('Button_18')
                Button('undefined').fontSize(10)
                  .onClick(() => {
                    this.supportAvoidance = undefined
                  })
                  .key('Button_19')
                Button('切换系统键盘与自定义键盘').fontSize(10).onClick((event: ClickEvent) => {
                  this.showKeyboard = !this.showKeyboard
                })
              }.height('40%')

              Text('点击按钮控制Column的高度,用来构造输入组件被输入法挡住的场景;控制TextInput类型')
                .fontSize(9)
                .width('100%')
              Row() {
                Button('点我height+50').fontSize(10).onClick(() => {
                  this.columnH += 50
                })
                  .key('Button_20')
                Button('点我height-50').fontSize(10).onClick(() => {
                  this.columnH -= 50
                })
                  .key('Button_21')
                Button('密码模式').fontSize(10).onClick(() => {
                  this.inputType = InputType.Password
                }).key('Button_Password')
                Button('正常模式').fontSize(10).onClick(() => {
                  this.inputType = InputType.Normal
                }).key('Button_Normal')
              }.height('40%')
            }.backgroundColor(Color.Pink).padding(10).height(this.columnH)

            Text('绑定普通软键盘的输入组件').fontSize(9).fontColor(0xCCCCCC).width('100%')
            Row({ space: 5 }) {
              Column() {
                TextInput({ placeholder: '普通TextInput', controller: this.controllerTextInput1 })
                  .placeholderFont({ size: 20, weight: 400 })// .height(40)
                  .showUnderline(true)
                  .lineHeight(-10)
                  .focusable(this.canFocus)
                  .type(this.inputType)
                  .enableKeyboardOnFocus(false)
                  .defaultFocus(true)
                  .border({ width: 1, color: Color.Red })
                  .enterKeyType(EnterKeyType.Go)
                  .onSubmit((enterKey) => {
                    console.info('zzz TextInput1 onSubmit=' + EnterKeyType[enterKey])
                  })
                  .onEditChange((isEditing) => {
                    console.info('zzz TextInput1 onEditChange=' + isEditing)
                  })
                  .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
                    console.info('zzz TextInput1 onTextSelectionChange, selectionStart: ' + selectionStart +
                      'selectionEnd: ' + selectionEnd)
                  })
                  .key('TextInput_7')
                  .showError('输入错啦！请重新输入。。。。')
                Search({ placeholder: '普通Search' }).borderWidth(1)
                  .searchButton('搜1', { fontSize: '10fp', fontColor: '#ff3f97e9' })
                  .key('Search_7')
              }.layoutWeight(2)

              TextArea({ placeholder: '普通TextArea', controller: this.controllerTextArea1 })
                .layoutWeight(1)
                .borderWidth(1)
                .enableKeyboardOnFocus(false)
                .key('TextArea_7')
              RichEditor(this.options)
                .layoutWeight(1)
                .borderWidth(1)
                .key('RichEditor_7')
                .onReady(() => {
                  this.controllerRichEditor.addTextSpan('012',
                    {
                      style:
                      {
                        fontColor: Color.Orange,
                        fontSize: 30
                      }
                    })
                  this.controllerRichEditor.addImageSpan($r('app.media.app_icon'),
                    {
                      imageStyle:
                      {
                        size: ['57px', '57px']
                      }
                    })
                  this.controllerRichEditor.addTextSpan('45',
                    {
                      style:
                      {
                        fontColor: Color.Black,
                        fontSize: 30
                      }
                    })
                  this.controllerRichEditor.addTextSpan('wfe',
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
                .onSelectionChange((value: RichEditorRange) => {
                  console.log('zzz RichEditor1 onSelectionChange start: ' + value.start + 'end: ' + value.end)
                })

            }

            Text('绑定了自定义键盘的输入组件').fontSize(9).fontColor(0xCCCCCC).width('100%')
            Row({ space: 5 }) {
              Column() {
                TextInput({
                  text: this.inputValue,
                  placeholder: '自定义键盘TextInput',
                  controller: this.controllerTextInput2
                })
                  .type(this.inputType)
                  .borderWidth(1)
                  .enterKeyType(EnterKeyType.Send)
                  .customKeyboard(this.showKeyboard ? this.CustomKeyboardBuilder() : undefined,
                    { supportAvoidance: this.supportAvoidance })
                  .margin(5)
                  .border({ width: 1 })
                  .onSubmit((enterKey) => {
                    console.info('TextInput2 onSubmit=' + EnterKeyType[enterKey])
                  })
                  .onEditChange((isEditing) => {
                    console.info('TextInput2 onEditChange=' + isEditing)
                  })
                  .key('TextInput_08')
                Search({ placeholder: '自定义键盘Search', value: this.inputValue })
                  .customKeyboard(this.showKeyboard ? this.CustomKeyboardBuilder2() : undefined,
                    { supportAvoidance: this.supportAvoidance })
                  .searchButton('搜2', { fontSize: '10fp', fontColor: '#ff3f97e9' })
                  .borderWidth(1)
                  .margin(5)
                  .key('Search_08')
              }
              .layoutWeight(2)

              TextArea({
                placeholder: '绑定自定义键盘的TextArea',
                text: this.inputValue,
                controller: this.controllerTextArea2
              })
                .layoutWeight(1)
                .borderWidth(1)
                .customKeyboard(this.showKeyboard ? this.CustomKeyboardBuilder() : undefined,
                  { supportAvoidance: this.supportAvoidance })
                .margin(5)
                .border({ width: 1 })
                .enableKeyboardOnFocus(true)
                .key('TextArea_08')


              RichEditor(this.options2)
                .layoutWeight(1)
                .borderWidth(1)
                .key('RichEditor_08')
                .onReady(() => {
                  this.controllerRichEditor2.addTextSpan('012',
                    {
                      style:
                      {
                        fontColor: Color.Orange,
                        fontSize: 30
                      }
                    })
                  this.controllerRichEditor2.addImageSpan($r('app.media.app_icon'),
                    {
                      imageStyle:
                      {
                        size: ['57px', '57px']
                      }
                    })
                  this.controllerRichEditor2.addTextSpan('45',
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
                .customKeyboard(this.showKeyboard ? this.CustomKeyboardBuilderRicheEditor() : undefined,
                  { supportAvoidance: this.supportAvoidance })
            }

            Text('其他场景').fontSize(9).fontColor(0xCCCCCC).width('100%')
            Row({ space: 5 }) {
              Search({ placeholder: 'enableKeyboardOnFocus为false的Search' })
                .borderWidth(1)
                .layoutWeight(1)
                .borderWidth(1)
                .enableKeyboardOnFocus(false)
                .key('Search_09')
              Search({ placeholder: '禁用focus的Search' })
                .borderWidth(1)
                .layoutWeight(1)
                .borderWidth(1)
                .focusable(false)
                .key('Search_10')
              TextInput({ placeholder: '空自定义', controller: this.controllerTextInput3 })
                .layoutWeight(1)
                .borderWidth(1)
                .type(InputType.Number)
                .enterKeyType(EnterKeyType.Send)
                .customKeyboard(this.CustomKeyboardBuilderNull())//空的自定义键盘，不崩溃即可
                .key('TextInput_09')
            }

          }
          .width('100%').padding(5)
        }
      }
    }
    .title('PopupKeyboardTest')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}