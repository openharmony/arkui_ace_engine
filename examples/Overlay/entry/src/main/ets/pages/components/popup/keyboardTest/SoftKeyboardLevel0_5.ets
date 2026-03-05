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
export function SoftKeyboardLevel05Builder(name: string, param: Object) {
  SoftKeyboardLevel05()
}

@Entry
@Component
struct SoftKeyboardLevel05 {
  pathStack: NavPathStack = new NavPathStack()
  @State inputValue: string = ''
  @State inputType: InputType = InputType.Normal
  @State showPopup: boolean = false
  controller_textInput: TextInputController = new TextInputController()

  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Row({ space: 5 }) {
        ForEach(['1', '2', '3', '4', '5', '6', '7', '8', '9', '0'], (item: string) => {
          Button(item)
            .width(60)
            .height(50)
            .onClick(() => {
              this.inputValue += item
            })
        })
      }

      Row({ space: 5 }) {
        Button('清除').onClick(() => {
          this.inputValue = ''
        })
        Button('确认').onClick(() => {
          this.controller_textInput.stopEditing()
        })
      }
    }
    .backgroundColor(Color.Gray)
    .padding(10)
  }

  @Builder
  popupBuilder() {
    Column({ space: 10 }) {
      Text('不同InputType测试')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)

      TextInput({ placeholder: 'Normal', controller: this.controller_textInput })
        .type(InputType.Normal)
        .borderWidth(1)
        .key('TextInput_Normal')

      TextInput({ placeholder: 'Number', controller: this.controller_textInput })
        .type(InputType.Number)
        .borderWidth(1)
        .key('TextInput_Number')

      TextInput({ placeholder: 'PhoneNumber', controller: this.controller_textInput })
        .type(InputType.PhoneNumber)
        .borderWidth(1)
        .key('TextInput_PhoneNumber')

      TextInput({ placeholder: 'Email', controller: this.controller_textInput })
        .type(InputType.Email)
        .borderWidth(1)
        .key('TextInput_Email')

      TextInput({ placeholder: 'Password', controller: this.controller_textInput })
        .type(InputType.Password)
        .borderWidth(1)
        .key('TextInput_Password')

      TextInput({ placeholder: 'URL', controller: this.controller_textInput })
        .type(InputType.URL)
        .borderWidth(1)
        .key('TextInput_URL')

      Button('关闭')
        .onClick(() => {
          this.showPopup = false
        })
    }
    .width('80%')
    .padding(15)
    .backgroundColor(Color.White)
  }

  build() {
    NavDestination() {
      Scroll() {
        Column({ space: 15 }) {
          Text('不同InputType与自定义键盘组合测试')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .width('100%')
            .key('Text_Header')

          Column({ space: 10 }) {
            Text('Normal类型')
              .fontSize(14)
            TextInput({ placeholder: 'Normal类型输入', text: this.inputValue, controller: this.controller_textInput })
              .type(InputType.Normal)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_Main_Normal')
          }

          Column({ space: 10 }) {
            Text('Number类型')
              .fontSize(14)
            TextInput({ placeholder: 'Number类型输入', text: this.inputValue, controller: this.controller_textInput })
              .type(InputType.Number)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_Main_Number')
          }

          Column({ space: 10 }) {
            Text('PhoneNumber类型')
              .fontSize(14)
            TextInput({ placeholder: 'PhoneNumber类型输入', text: this.inputValue, controller: this.controller_textInput })
              .type(InputType.PhoneNumber)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_Main_PhoneNumber')
          }

          Column({ space: 10 }) {
            Text('EmailAddress类型')
              .fontSize(14)
            TextInput({ placeholder: 'EmailAddress类型输入', text: this.inputValue, controller: this.controller_textInput })
              .type(InputType.Email)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_Main_Email')
          }

          Column({ space: 10 }) {
            Text('Password类型')
              .fontSize(14)
            TextInput({ placeholder: 'Password类型输入', text: this.inputValue, controller: this.controller_textInput })
              .type(InputType.Password)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_Main_Password')
          }

          Column({ space: 10 }) {
            Text('URL类型')
              .fontSize(14)
            TextInput({ placeholder: 'URL类型输入', text: this.inputValue, controller: this.controller_textInput })
              .type(InputType.URL)
              .borderWidth(1)
              .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
              .key('TextInput_Main_URL')
          }

          Divider().color(Color.Gray)

          Button('打开Popup查看更多InputType')
            .onClick(() => {
              this.showPopup = true
            })
            .bindPopup(this.showPopup, {
              builder: this.popupBuilder,
              onStateChange: (e) => {
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
    }
    .title('SoftKeyboardLevel05')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}
