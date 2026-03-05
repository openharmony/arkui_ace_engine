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

@Builder
export function SoftKeyboardLevel07Builder(name: string, param: Object) {
  SoftKeyboardLevel07()
}

@Entry
@Component
struct SoftKeyboardLevel07 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State eventLog: string[] = []
  @State showPopup: boolean = false
  controller_textInput: TextInputController = new TextInputController()
  controller_textArea: TextAreaController = new TextAreaController()
  controller_richEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller_richEditor };

  logEvent(eventName: string, data: string = '') {
    const timestamp = new Date().toLocaleTimeString()
    this.eventLog.unshift(`${timestamp}: ${eventName} ${data}`)
    if (this.eventLog.length > 20) {
      this.eventLog.pop()
    }
  }

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach(['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'], (item: string) => {
          GridItem() {
            Button(item)
              .width(70)
              .onClick(() => {
                this.inputValue += item
              })
          }
        })
      }
      .maxCount(3)
      .columnsGap(5)
      .rowsGap(5)
      .padding(5)

      Button('关闭')
        .onClick(() => {
          this.controller_textInput.stopEditing()
          this.controller_textArea.stopEditing()
        })
    }
    .backgroundColor(Color.Gray)
    .padding(10)
  }

  @Builder
  popupBuilder() {
    Column({ space: 10 }) {
      Text('Popup中的事件测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      TextInput({ placeholder: 'Popup TextInput', text: this.inputValue, controller: this.controller_textInput })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .onFocus(() => {
          this.logEvent('Popup TextInput onFocus')
        })
        .onBlur(() => {
          this.logEvent('Popup TextInput onBlur')
        })
        .onEditChange((isEditing) => {
          this.logEvent('Popup TextInput onEditChange', isEditing.toString())
        })
        .onChange((value) => {
          this.logEvent('Popup TextInput onChange', value)
        })
        .key('TextInput_Popup')

      Button('关闭')
        .onClick(() => {
          this.showPopup = false
        })
    }
    .width('70%')
    .padding(15)
    .backgroundColor(Color.White)
  }

  build() {
    NavDestination() {
      Column({ space: 10 }) {
        Text('输入组件事件回调测试')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .width('100%')
          .key('Text_Header')

        Scroll() {
          Column({ space: 15 }) {
            Column({ space: 10 }) {
              Text('TextInput事件测试')
                .fontSize(14)
              TextInput({ placeholder: 'TextInput', text: this.inputValue, controller: this.controller_textInput })
                .borderWidth(1)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .onFocus(() => {
                  this.logEvent('TextInput onFocus')
                })
                .onBlur(() => {
                  this.logEvent('TextInput onBlur')
                })
                .onEditChange((isEditing) => {
                  this.logEvent('TextInput onEditChange', isEditing.toString())
                })
                .onChange((value) => {
                  this.logEvent('TextInput onChange', value)
                })
                .onSubmit((enterKey) => {
                  this.logEvent('TextInput onSubmit', EnterKeyType[enterKey])
                })
                .onTextSelectionChange((selectionStart, selectionEnd) => {
                  this.logEvent('TextInput onTextSelectionChange', `${selectionStart}-${selectionEnd}`)
                })
                .key('TextInput_Main')
            }

            Column({ space: 10 }) {
              Text('TextArea事件测试')
                .fontSize(14)
              TextArea({ placeholder: 'TextArea', text: this.inputValue, controller: this.controller_textArea })
                .borderWidth(1)
                .height(80)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .onFocus(() => {
                  this.logEvent('TextArea onFocus')
                })
                .onBlur(() => {
                  this.logEvent('TextArea onBlur')
                })
                .onEditChange((isEditing) => {
                  this.logEvent('TextArea onEditChange', isEditing.toString())
                })
                .onChange((value) => {
                  this.logEvent('TextArea onChange', value)
                })
                .onTextSelectionChange((selectionStart, selectionEnd) => {
                  this.logEvent('TextArea onTextSelectionChange', `${selectionStart}-${selectionEnd}`)
                })
                .key('TextArea_Main')
            }

            Column({ space: 10 }) {
              Text('RichEditor事件测试')
                .fontSize(14)
              RichEditor(this.options)
                .placeholder('RichEditor')
                .borderWidth(1)
                .height(80)
                .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                .onFocus(() => {
                  this.logEvent('RichEditor onFocus')
                })
                .onBlur(() => {
                  this.logEvent('RichEditor onBlur')
                })
                .aboutToIMEInput((value) => {
                  this.logEvent('RichEditor aboutToIMEInput', JSON.stringify(value))
                  return true
                })
                .onIMEInputComplete((value) => {
                  this.logEvent('RichEditor onIMEInputComplete', JSON.stringify(value))
                })
                .aboutToDelete((value) => {
                  this.logEvent('RichEditor aboutToDelete', JSON.stringify(value))
                  return true
                })
                .onDeleteComplete(() => {
                  this.logEvent('RichEditor onDeleteComplete')
                })
                .onSelectionChange((value) => {
                  this.logEvent('RichEditor onSelectionChange', `${value.start}-${value.end}`)
                })
                .key('RichEditor_Main')
            }

            Button('打开Popup测试事件')
              .onClick(() => {
                this.showPopup = true
              })
              .bindPopup(this.showPopup, {
                builder: this.popupBuilder,
                onStateChange: (e) => {
                  this.logEvent('Popup onStateChange', e.isVisible.toString())
                  if (!e.isVisible) {
                    this.showPopup = false
                  }
                }
              })
              .key('Button_OpenPopup')

          }
          .width('100%')
          .padding(15)
        }
        .layoutWeight(1)

        Divider().color(Color.Gray)

        Column({ space: 5 }) {
          Text('事件日志')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)

          List({ space: 5 }) {
            ForEach(this.eventLog, (log: string) => {
              ListItem() {
                Text(log)
                  .fontSize(10)
                  .fontColor(0x666666)
              }
            })
          }
          .height(200)
          .width('100%')
          .backgroundColor(Color.Pink)
          .padding(10)

          Button('清除日志')
            .onClick(() => {
              this.eventLog = []
            })
        }
        .padding(10)

      }
      .width('100%')
      .height('100%')
    }
    .title('SoftKeyboardLevel07')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
