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
struct ContentTypeStruct {
  @State text: string = ''
  @State contentTypes: Array<ContentType | number> =
    [ContentType.USER_NAME, ContentType.PASSWORD, ContentType.NEW_PASSWORD,
      ContentType.FULL_STREET_ADDRESS, ContentType.HOUSE_NUMBER, ContentType.DISTRICT_ADDRESS, ContentType.CITY_ADDRESS,
      ContentType.PROVINCE_ADDRESS, ContentType.COUNTRY_ADDRESS, ContentType.PERSON_FULL_NAME,
      ContentType.PERSON_LAST_NAME,
      ContentType.PERSON_FIRST_NAME, ContentType.PHONE_NUMBER, ContentType.PHONE_COUNTRY_CODE,
      ContentType.FULL_PHONE_NUMBER,
      ContentType.EMAIL_ADDRESS, ContentType.BANK_CARD_NUMBER, ContentType.ID_CARD_NUMBER, ContentType.NICKNAME,
      ContentType.DETAIL_INFO_WITHOUT_STREET, ContentType.FORMAT_ADDRESS, -1]
  @State contentTypeString: Array<string> =
    ['USER_NAME', 'PASSWORD', 'NEW_PASSWORD', 'FULL_STREET_ADDRESS', 'HOUSE_NUMBER',
      'DISTRICT_ADDRESS', 'CITY_ADDRESS', 'PROVINCE_ADDRESS', 'COUNTRY_ADDRESS', 'PERSON_FULL_NAME', 'PERSON_LAST_NAME',
      'PERSON_FIRST_NAME', 'PHONE_NUMBER', 'PHONE_COUNTRY_CODE', 'FULL_PHONE_NUMBER', 'EMAIL_ADDRESS',
      'BANK_CARD_NUMBER',
      'ID_CARD_NUMBER', 'NICKNAME', 'DETAIL_INFO_WITHOUT_STREET', 'FORMAT_ADDRESS', '-1']
  @State index: number = 0

  build() {
    Row() {
      Column() {
        Text() {
          Span('规格:\n')
          Span('1、对输入内容进行限制 \n')
          Span('约束:\n')
          Span('1、在已启用密码保险箱情况下，用户名、密码、新密码的自动填充属性可用 \n')
          Span('2、在已启用情景化自动填充情况下，ContentType中除约束一种的其他枚举值的自动填充属性可用 \n')
        }.draggable(true).copyOption(CopyOptions.InApp)

        Text('设置自动填充类型')
        TextInput({
          placeholder: 'TextInput: set ContentType to ' + this.contentTypeString[this.index],
          text: this.text
        })
          .contentType(this.contentTypes[this.index])
          .onChange((value: string) => {
            this.text = value
          })
        TextArea({ placeholder: 'TextArea: set ContentType to ' + this.contentTypeString[this.index], text: this.text })
          .contentType(this.contentTypes[this.index])
          .onChange((value: string) => {
            this.text = value
          })
        Button('改变ContentType').onClick(() => {
          this.index = (this.index + 1) % this.contentTypes.length;
        })
      }
      .width('100%')
    }
    .height('100%')
  }
}