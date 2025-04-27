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
struct struct_10_01_showUnderline {
  controller: TextInputController = new TextInputController()
  @State type: InputType[] =
    [InputType.Normal, InputType.Number, InputType.Password, InputType.Email, InputType.PhoneNumber,
      InputType.NUMBER_PASSWORD, InputType.Password, InputType.USER_NAME, InputType.NEW_PASSWORD]
  @State typeStr: string[] =
    ['Normal', 'Number', 'Password', 'Email', 'PhoneNumber', 'NUMBER_PASSWORD', 'SCREEN_LOCK_PASSWORD', 'USER_NAME',
      'NEW_PASSWORD']
  @State inputIndex: number = 0
  @State paddingTest: number = 0
  @State heightTest: number = 80
  @State widthTest: number = 250
  @State value: string = ''
  @State fontSize: number = 16

  build() {
    Column({ space: 5 }) {
      Text() {
        Span('点击type切换，查看效果，预期切换到Number类型下滑线消失，切换Password边框变红，切回Normal下划线重新显示。')
        Span('注意滑线位置。')
          .fontColor(Color.Red)
      }
      .margin(5)
      .fontSize(14)
      .fontColor(Color.Gray)
      .borderWidth(1)
      .width('90%')

      TextInput()
        .width('80%')
        .height(50)
        .style(TextInputStyle.Inline)
        .borderWidth(2)
        .maxLines(5)

      TextInput({
        text: this.value,
        placeholder: 'input your word....',
        controller: this.controller
      })
        .fontSize(this.fontSize)
        .type(this.type[this.inputIndex])
        .padding(this.paddingTest)
        .showUnderline(true)
        .width(this.widthTest)
        .height(this.heightTest)
        .showError('Error')
        .showCounter(true)

      Scroll() {
        Row() {
          Button('type:' + this.typeStr[this.inputIndex])
            .width('40%')
            .onClick(() => {
              this.inputIndex = (this.inputIndex + 1) % this.type.length
            })
        }
      }.padding({ bottom: 150 })
    }.height('40%')
  }
}