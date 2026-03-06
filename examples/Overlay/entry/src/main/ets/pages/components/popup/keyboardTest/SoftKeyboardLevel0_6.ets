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
export function SoftKeyboardLevel06Builder(name: string, param: Object) {
  SoftKeyboardLevel06()
}

@Entry
@Component
struct SoftKeyboardLevel06 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State canFocus: boolean = true
  @State enableKeyboardOnFocus: boolean = true
  @State defaultFocus1: boolean = false
  controller_textInput: TextInputController = new TextInputController()
  controller_textArea: TextAreaController = new TextAreaController()
  controller_richEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller_richEditor };

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'], (item: string) => {
          GridItem() {
            Button(item)
              .width(80)
              .onClick(() => {
                this.inputValue += item
              })
          }
        })
      }
      .maxCount(4)
      .columnsGap(5)
      .rowsGap(5)
      .padding(5)

      Button('关闭键盘')
        .onClick(() => {
          this.controller_textInput.stopEditing()
          this.controller_textArea.stopEditing()
        })
    }
    .backgroundColor(Color.Gray)
    .padding(10)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Text('焦点属性组合测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .key('Text_Header')

          Column({ space: 10 }) {
            Text('控制按钮')
              .fontSize(14)
              .fontColor(0xCCCCCC)

            Row({ space: 10 }) {
              Button('canFocus: true')
                .onClick(() => {
                  this.canFocus = true
                })
                .key('Button_CanFocusTrue')

              Button('canFocus: false')
                .onClick(() => {
                  this.canFocus = false
                })
                .key('Button_CanFocusFalse')

              Button('enableKeyboardOnFocus: true')
                .onClick(() => {
                  this.enableKeyboardOnFocus = true
                })
                .key('Button_EnableKeyboardTrue')

              Button('enableKeyboardOnFocus: false')
                .onClick(() => {
                  this.enableKeyboardOnFocus = false
                })
                .key('Button_EnableKeyboardFalse')
            }

            Row({ space: 10 }) {
              Button('defaultFocus: true')
                .onClick(() => {
                  this.defaultFocus1 = true
                })
                .key('Button_DefaultFocusTrue')

              Button('defaultFocus: false')
                .onClick(() => {
                  this.defaultFocus1 = false
                })
                .key('Button_DefaultFocusFalse')
            }
          }
          .backgroundColor(Color.Pink)
          .padding(10)

          Divider().color(Color.Gray)

          Column({ space: 10 }) {
            Text('TextInput - 动态焦点属性')
              .fontSize(14)
            TextInput({ placeholder: 'TextInput测试', text: this.inputValue, controller: this.controller_textInput })
              .focusable(this.canFocus)
              .enableKeyboardOnFocus(this.enableKeyboardOnFocus)
              .defaultFocus(this.defaultFocus1)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_Dynamic')
          }

          Column({ space: 10 }) {
            Text('TextArea - 动态焦点属性')
              .fontSize(14)
            TextArea({ placeholder: 'TextArea测试', text: this.inputValue, controller: this.controller_textArea })
              .focusable(this.canFocus)
              .enableKeyboardOnFocus(this.enableKeyboardOnFocus)
              .defaultFocus(this.defaultFocus1)
              .borderWidth(1)
              .height(80)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextArea_Dynamic')
          }

          Column({ space: 10 }) {
            Text('RichEditor - 动态焦点属性')
              .fontSize(14)
            RichEditor(this.options)
              .placeholder('RichEditor测试')
              .focusable(this.canFocus)
              .enableKeyboardOnFocus(this.enableKeyboardOnFocus)
              .defaultFocus(this.defaultFocus1)
              .borderWidth(1)
              .height(80)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('RichEditor_Dynamic')
          }

          Divider().color(Color.Gray)

          Column({ space: 10 }) {
            Text('固定属性测试')
              .fontSize(14)

            Row({ space: 10 }) {
              Column({ space: 5 }) {
                Text('focusable: true')
                  .fontSize(12)
                TextInput({ placeholder: '可获焦' })
                  .focusable(true)
                  .borderWidth(1)
                  .key('TextInput_FocusableTrue')
              }

              Column({ space: 5 }) {
                Text('focusable: false')
                  .fontSize(12)
                TextInput({ placeholder: '不可获焦' })
                  .focusable(false)
                  .borderWidth(1)
                  .key('TextInput_FocusableFalse')
              }
            }

            Row({ space: 10 }) {
              Column({ space: 5 }) {
                Text('enableKeyboardOnFocus: true')
                  .fontSize(12)
                TextInput({ placeholder: '自动弹出' })
                  .enableKeyboardOnFocus(true)
                  .borderWidth(1)
                  .key('TextInput_EnableKeyboardTrue')
              }

              Column({ space: 5 }) {
                Text('enableKeyboardOnFocus: false')
                  .fontSize(12)
                TextInput({ placeholder: '不自动弹出' })
                  .enableKeyboardOnFocus(false)
                  .borderWidth(1)
                  .key('TextInput_EnableKeyboardFalse')
              }
            }
          }

        }
        .width('100%')
        .padding(15)
      }
    }
    .title('SoftKeyboardLevel06')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
