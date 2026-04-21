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
export function SoftKeyboardLevel11Builder(name: string, param: Object) {
  SoftKeyboardLevel11()
}

@Entry
@Component
struct SoftKeyboardLevel11 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State longText: string = '这是一个很长的文本，用于测试输入组件在长文本情况下的表现。'
  @State showEmptyKeyboard: boolean = false
  @State showNullKeyboard: boolean = false
  controller_textInput: TextInputController = new TextInputController()
  controller_textArea: TextAreaController = new TextAreaController()
  controller_richEditor: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller_richEditor };

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach(['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'], (item: string) => {
          GridItem() {
            Button(item)
              .width(80)
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
  EmptyKeyboardBuilder() {
    Column() {
    }
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Text('边界条件和异常场景测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .key('Text_Header')

          Column({ space: 10 }) {
            Text('空文本输入测试')
              .fontSize(14)
            TextInput({ placeholder: '空文本', text: '', controller: this.controller_textInput })
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_Empty')
          }

          Column({ space: 10 }) {
            Text('超长文本输入测试')
              .fontSize(14)
            TextInput({ placeholder: '超长文本', text: this.longText, controller: this.controller_textInput })
              .borderWidth(1)
              .maxLength(100)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_LongText')
          }

          Column({ space: 10 }) {
            Text('特殊字符输入测试')
              .fontSize(14)
            TextInput({ placeholder: '特殊字符', text: '!@#$%^&*()_+-=[]{}|;:\'",.<>?/~`', controller: this.controller_textInput })
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_SpecialChars')
          }
        }
        .width('100%')
        .padding(15)
      }
    }
    .title('SoftKeyboardLevel11')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
