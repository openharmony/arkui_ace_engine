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
 * limitations under theater License.
 */

@Builder
export function SoftKeyboardLevel08Builder(name: string, param: Object) {
  SoftKeyboardLevel08()
}

@Entry
@Component
struct SoftKeyboardLevel08 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State nestedLevel: number = 1
  controller_textInput: TextInputController = new TextInputController()
  controller_textArea: TextAreaController = new TextAreaController()

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
    .    padding(10)
  }

  @Builder
  NestedColumn(level: number) {
    Column({ space: 10 }) {
      Text(`嵌套层级 ${level}`)
        .fontSize(14)
        .fontWeight(FontWeight.Bold)

      TextInput({ placeholder: `层级${level} TextInput`, text: this.inputValue, controller: this.controller_textInput })
        .borderWidth(1)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key(`TextInput_Level${level}`)

      TextArea({ placeholder: `层级${level} TextArea`, text: this.inputValue, controller: this.controller_textArea })
        .borderWidth(1)
        .height(60)
        .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
        .key(`TextArea_Level${level}`)

      if (level < 3) {
        Row({ space: 10 }) {
          Column({ space: 10 }) {
            Text(`Row嵌套 ${level + 1}`)
              .fontSize(12)
            TextInput({ placeholder: `Row${level + 1} TextInput` })
              .borderWidth(1)
              .key(`TextInput_Row${level + 1}`)
          }
          .layoutWeight(1)

          Column({ space: 10 }) {
            Text(`Column嵌套 ${level + 1}`)
              .fontSize(12)
            TextInput({ placeholder: `Col${level + 1} TextInput` })
              .borderWidth(1)
              .key(`TextInput_Col${level + 1}`)
          }
          .layoutWeight(1)
        }
        .backgroundColor(Color.Pink)
        .padding(10)
      }
    }
    .width('100%')
    .padding(10)
    .backgroundColor(level % 2 === 0 ? Color.White : Color.Grey)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Text('嵌套布局中的输入组件测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .key('Text_Header')

          Column({ space: 10 }) {
            Text('控制嵌套层级')
              .fontSize(14)
              .fontColor(0xCCCCCC)

            Row({ space: 10 }) {
              Button('1层')
                .onClick(() => {
                  this.nestedLevel = 1
                })
                .key('Button_Level1')

              Button('2层')
                .onClick(() => {
                  this.nestedLevel = 2
                })
                .key('Button_Level2')

              Button('3层')
                .onClick(() => {
                  this.nestedLevel = 3
                })
                .key('Button_Level3')
            }
          }
          .backgroundColor(Color.Pink)
          .padding(10)

          Divider().color(Color.Gray)

          Column({ space: 10 }) {
            Text('Column嵌套测试')
              .fontSize(14)

            this.NestedColumn(1)

            if (this.nestedLevel >= 2) {
              Column({ space: 10 }) {
                this.NestedColumn(2)
              }
              .backgroundColor(Color.Yellow)
              .padding(10)
            }

            if (this.nestedLevel >= 3) {
              Column({ space: 10 }) {
                this.NestedColumn(3)
              }
              .backgroundColor(Color.Green)
              .padding(10)
            }
          }

          Divider().color(Color.Gray)

          Column({ space: 10 }) {
            Text('Stack嵌套测试')
              .fontSize(14)

            Stack({ alignContent: Alignment.BottomStart }) {
              Text('底层')
                .width('100%')
                .height(100)
                .backgroundColor(Color.Blue)
                .fontSize(20)
                .fontColor(Color.White)

              Column({ space: 5 }) {
                TextInput({ placeholder: 'Stack TextInput', text: this.inputValue, controller: this.controller_textInput })
                  .borderWidth(1)
                  .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
                  .key('TextInput_Stack')
              }
              .padding(10)
              .backgroundColor(Color.White)
            }
            .width('100%')
            .height(120)
          }

          Column({ space: 10 }) {
            Text('RelativeContainer嵌套测试')
              .fontSize(14)

            RelativeContainer() {
              TextInput({ placeholder: 'Relative TextInput', text: this.inputValue })
                .borderWidth(1)
                .id('input1')
                .alignRules({
                  top: { anchor: '__container__', align: VerticalAlign.Top },
                  left: { anchor: '__container__', align: HorizontalAlign.Start }
                })
                .key('TextInput_Relative')

              TextArea({ placeholder: 'Relative TextArea' })
                .borderWidth(1)
                .height(60)
                .id('area1')
                .alignRules({
                  top: { anchor: 'input1', align: VerticalAlign.Top },
                  left: { anchor: '__container__', align: HorizontalAlign.Start }
                })
                .key('TextArea_Relative')
            }
            .width('100%')
            .height(150)
          }

        }
        .width('100%')
        .padding(15)
      }
    }
    .title('SoftKeyboardLevel08')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
