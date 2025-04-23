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

@Entry
@Component
struct struct_10_06_textInput {
  @State text: string = ''
  @State Height: number = 50
  @State FontSize: number = 14
  controller: TextInputController = new TextInputController()
  @State showCounter: boolean = true
  @State count: number = 0
  @State isEditing: string = ''

  build() {
    Scroll() {
      Column() {
        Column() {
          Text('操作： 第一个TextInput输入字符')
          Text('预期： 观察第一个TextInput在输入过程中下方其它组件无抖动')
        }.borderWidth(1)
        .padding(5)

        TextInput({ text: this.text, placeholder: 'input your word...', controller: this.controller })
          .type(InputType.Normal)
          .showError('Error222')
          .placeholderColor(Color.Grey)
          .backgroundColor(Color.Blue)
          .placeholderFont({ size: 20, weight: '0', style: FontStyle.Italic })
          .caretColor(Color.Pink)
          .enterKeyType(EnterKeyType.Next)
          .textAlign(TextAlign.Start)
          .maxLength(110)
          .showUnderline(true)
          .showCounter(this.showCounter,
            { thresholdPercentage: 30, highlightBorder: true })
          .width(380)
          .height(this.Height)
          .margin({ top: 50 })
          .fontSize(this.FontSize)
          .fontColor(Color.Pink)
          .copyOption(CopyOptions.InApp)
          .onChange((value: string) => {
            this.text = value
          })
        Text('111')
        Text(this.text)
        Button('Set showCounter:' + this.showCounter)
          .margin({ bottom: 20 })
          .onClick(() => {
            this.count++
            // 将光标在第一个字符前
            if (this.count % 2 === 0) {
              this.showCounter = true
            } else {
              this.showCounter = false
            }
          })
        Column() {
          Text('操作： 长按输入框弹出菜单')
          Text('预期： 文字以及选中背板均截断显示')
        }.borderWidth(1)
        .padding(5)

        TextInput({ text: '123asdhsahdkjashdjkashdk' })
          .width(350)
          .height(50)
          .borderWidth(12)
      }.width('100%')
    }
  }
}
