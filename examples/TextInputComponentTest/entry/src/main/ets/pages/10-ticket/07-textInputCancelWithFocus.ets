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
struct textInputCancelWithFocus {
  @State type: CancelButtonStyle = CancelButtonStyle.INVISIBLE
  @State text1: string = '123456789test001'

  build() {
    Scroll() {
      Column({ space: 20 }) {

        Column() {
          Text('操作：两个输入框间点击切换').fontColor(Color.Blue)
          Text('Pass条件：点击第二个输入框时，获焦显示cancelButton，无闪烁异常').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

        TextInput();

        TextInput({ text: this.text1 })
          .maxLength(100)
          .showCounter(true)
          .cancelButton({ style: this.type })
          .width('80%')
          .margin(10)
          .textAlign(TextAlign.End)
          .onFocus(() => {
            this.type = CancelButtonStyle.CONSTANT
          })
          .onBlur(() => {
            this.type = CancelButtonStyle.INVISIBLE
          })

      }.width('100%')
    }
  }
}