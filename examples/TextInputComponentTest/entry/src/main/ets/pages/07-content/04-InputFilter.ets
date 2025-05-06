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
struct InputFilterStruct {
  @State defaultTestText: Array<string> = ['', '12.3ah_jdk@jha\ud83c\udf0dhkdsa']
  @State index: number = 0
  @State textAreaString: string = ''
  @State typeValue: number = 0
  @State filterString: ResourceStr = ''
  @State textInputString: string = ''

  build() {
    Column() {
      Column() {
        Text() {
          Span('规格:\n')
          Span('1、默认空字符串，不进行过滤操作 \n')
          Span('2、与type互斥，正则表达式设置为非空值时，type过滤设置不生效 \n')
        }.draggable(true)
      }.height('10%')

      Column() {
        Text('默认空字符串，不进行过滤操作')
        Row() {
          TextInput({ placeholder: 'TextInput: not set inputFilter', text: this.defaultTestText[this.index] })
            .onChange((value: string) => {
              this.defaultTestText[this.index] = value
            })
            .width('50%')
          TextInput({ placeholder: 'set inputFilter to \'\'', text: this.defaultTestText[this.index] })
            .inputFilter('')
            .onChange((value: string) => {
              this.defaultTestText[this.index] = value
            })
            .width('50%')
        }

        Row() {
          TextArea({ placeholder: 'TextArea: not set inputFilter', text: this.defaultTestText[this.index] })
            .onChange((value: string) => {
              this.defaultTestText[this.index] = value
            })
            .width('50%')
          TextArea({ placeholder: 'set inputFilter to \'\'', text: this.defaultTestText[this.index] })
            .inputFilter('')
            .onChange((value: string) => {
              this.defaultTestText[this.index] = value
            })
            .width('50%')
        }

        Button('Verify the default')
          .width('90%')
          .margin(2)
          .onClick(() => {
            this.index = (this.index + 1) % this.defaultTestText.length
          })
      }.height('20%')

      Column() {
        Text('与type互斥')
        TextInput({ placeholder: 'TextInput', text: this.textInputString })
          .inputFilter(this.filterString)
          .type(this.typeValue)
          .onChange((value: string) => {
            this.textInputString = value
          })
        Button('type: Normal, filter: \'\', input: \'12.3_ab c@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = ''
            this.typeValue = InputType.Normal
            this.textInputString = '12.3_ab c@'
          })
        Button('type: Number, filter: \'[a-z]\', input: \'12.3_ab c@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = '[a-z]'
            this.typeValue = InputType.Number
            this.textInputString = '12.3_ab c@'
          })
        Button('type: Phone number, filter: \'[a-z]\', input: \'12.3_ab c@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = '[a-z]'
            this.typeValue = InputType.PhoneNumber
            this.textInputString = '12.3_ab c@'
          })
        Button('type: Email, filter: \'[@]\', input: \'12.3,#$@@@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = '[@]'
            this.typeValue = InputType.Email
            this.textInputString = '12.3,#$@@@'
          })
        Button('type: Number decimal, filter: \'[a-z]\', input: \'12.3_ab c@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = '[a-z]'
            this.typeValue = InputType.NUMBER_DECIMAL
            this.textInputString = '12.3_ab c@'
          })

        TextArea({ placeholder: 'TextArea', text: this.textAreaString })
          .inputFilter(this.filterString)
          .type(this.typeValue)
          .onChange((value: string) => {
            this.textAreaString = value
          })
        Button('type: Normal, filter: \'\', input: \'12.3_ab c@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = ''
            this.typeValue = TextAreaType.NORMAL
            this.textAreaString = '12.3_ab c@'
          })
        Button('type: Number, filter: \'[a-z]\', input: \'12.3_ab c@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = '[a-z]'
            this.typeValue = TextAreaType.NUMBER
            this.textAreaString = '12.3_ab c@'
          })
        Button('type: Phone number, filter: \'[a-z]\', input: \'12.3_ab c@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = '[a-z]'
            this.typeValue = TextAreaType.PHONE_NUMBER
            this.textAreaString = '12.3_ab c@'
          })
        Button('type: Email, filter: \'[@]\', input: \'12.3,#$@@@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = '[@]'
            this.typeValue = TextAreaType.NORMAL
            this.textAreaString = '12.3,#$@@@'
          })
        Button('type: Number decimal, filter: \'[a-z]\', input: \'12.3_ab c@\'')
          .width('100%')
          .margin(2)
          .onClick(() => {
            this.filterString = '[a-z]'
            this.typeValue = TextAreaType.NORMAL
            this.textAreaString = '12.3_ab c@'
          })
      }.height('70%')
    }.width('100%').height('100%')
  }
}