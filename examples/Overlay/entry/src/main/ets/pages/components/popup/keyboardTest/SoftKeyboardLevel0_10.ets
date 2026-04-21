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
export function SoftKeyboardLevel10Builder(name: string, param: Object) {
  SoftKeyboardLevel10()
}

@Entry
@Component
struct SoftKeyboardLevel10 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue1: string = ''
  @State inputValue2: string = ''
  @State inputValue3: string = ''
  @State currentKeyboard: number = 1
  controller_textInput1: TextInputController = new TextInputController()
  controller_textInput2: TextInputController = new TextInputController()
  controller_textInput3: TextInputController = new TextInputController()

  @Builder
  CustomKeyboardBuilder1() {
    Column() {
      Text('数字键盘')
        .fontSize(14)
        .fontWeight(FontWeight.Bold)

      Grid() {
        ForEach(['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'], (item: string) => {
          GridItem() {
            Button(item)
              .width(70)
              .onClick(() => {
                this.inputValue1 += item
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
          this.controller_textInput1.stopEditing()
        })
    }
    .backgroundColor(Color.Blue)
    .padding(10)
  }

  @Builder
  CustomKeyboardBuilder2() {
    Column() {
      Text('字母键盘')
        .fontSize(14)
        .fontWeight(FontWeight.Bold)

      Grid() {
        ForEach(['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L'], (item: string) => {
          GridItem() {
            Button(item)
              .width(70)
              .onClick(() => {
                this.inputValue2 += item
              })
          }
        })
      }
      .maxCount(4)
      .columnsGap(5)
      .rowsGap(5)
      .padding(5)

      Button('关闭')
        .onClick(() => {
          this.controller_textInput2.stopEditing()
        })
    }
    .backgroundColor(Color.Green)
    .padding(10)
  }

  @Builder
  CustomKeyboardBuilder3() {
    Column() {
      Text('符号键盘')
        .fontSize(14)
        .fontWeight(FontWeight.Bold)

      Grid() {
        ForEach(['!', '@', '#', '$', '%', '^', '&', '*', '(', ')'], (item: string) => {
          GridItem() {
            Button(item)
              .width(70)
              .onClick(() => {
                this.inputValue3 += item
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
          this.controller_textInput3.stopEditing()
        })
    }
    .backgroundColor(Color.Orange)
    .padding(10)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Text('多个自定义键盘切换测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .key('Text_Header')

          Column({ space: 10 }) {
            Text('数字键盘输入')
              .fontSize(14)
            TextInput({ placeholder: '数字键盘输入', text: this.inputValue1, controller: this.controller_textInput1 })
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder1(), { supportAvoidance: true })
              .key('TextInput_Number')
            Text(`输入值: ${this.inputValue1}`)
              .fontSize(12)
              .fontColor(0x666666)
          }

          Column({ space: 10 }) {
            Text('字母键盘输入')
              .fontSize(14)
            TextInput({ placeholder: '字母键盘输入', text: this.inputValue2, controller: this.controller_textInput2 })
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder2(), { supportAvoidance: true })
              .key('TextInput_Letter')
            Text(`输入值: ${this.inputValue2}`)
              .fontSize(12)
              .fontColor(0x666666)
          }

          Column({ space: 10 }) {
            Text('符号键盘输入')
              .fontSize(14)
            TextInput({ placeholder: '符号键盘输入', text: this.inputValue3, controller: this.controller_textInput3 })
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder3(), { supportAvoidance: true })
              .key('TextInput_Symbol')
            Text(`输入值: ${this.inputValue3}`)
              .fontSize(12)
              .fontColor(0x666666)
          }

          Divider().color(Color.Gray)

          Column({ space: 10 }) {
            Text('切换键盘类型')
              .fontSize(14)
              .fontColor(0xCCCCCC)

            Row({ space: 10 }) {
              Button('数字键盘')
                .onClick(() => {
                  this.currentKeyboard = 1
                })
                .backgroundColor(this.currentKeyboard === 1 ? Color.Blue : Color.White)
                .key('Button_NumberKeyboard')

              Button('字母键盘')
                .onClick(() => {
                  this.currentKeyboard = 2
                })
                .backgroundColor(this.currentKeyboard === 2 ? Color.Green : Color.White)
                .key('Button_LetterKeyboard')

              Button('符号键盘')
                .onClick(() => {
                  this.currentKeyboard = 3
                })
                .backgroundColor(this.currentKeyboard === 3 ? Color.Orange : Color.White)
                .key('Button_SymbolKeyboard')
            }
          }
          .backgroundColor(Color.Pink)
          .padding(10)

          Divider().color(Color.Gray)

          Column({ space: 10 }) {
            Text('动态切换键盘')
              .fontSize(14)

            TextInput({ placeholder: '动态切换键盘', text: this.inputValue1, controller: this.controller_textInput1 })
              .borderWidth(1)
              .customKeyboard(
                this.currentKeyboard === 1 ? this.CustomKeyboardBuilder1() :
                this.currentKeyboard === 2 ? this.CustomKeyboardBuilder2() :
                this.CustomKeyboardBuilder3(),
                { supportAvoidance: true }
              )
              .key('TextInput_Dynamic')
          }

          Divider().color(Color.Gray)

          Column({ space: 10 }) {
            Text('清除所有输入')
              .fontSize(14)

            Row({ space: 10 }) {
              Button('清除数字')
                .onClick(() => {
                  this.inputValue1 = ''
                })
                .key('Button_ClearNumber')

              Button('清除字母')
                .onClick(() => {
                  this.inputValue2 = ''
                })
                .key('Button_ClearLetter')

              Button('清除符号')
                .onClick(() => {
                  this.inputValue3 = ''
                })
                .key('Button_ClearSymbol')

              Button('清除全部')
                .onClick(() => {
                  this.inputValue1 = ''
                  this.inputValue2 = ''
                  this.inputValue3 = ''
                })
                .key('Button_ClearAll')
            }
          }

        }
        .width('100%')
        .padding(15)
      }
    }
    .title('SoftKeyboardLevel10')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
