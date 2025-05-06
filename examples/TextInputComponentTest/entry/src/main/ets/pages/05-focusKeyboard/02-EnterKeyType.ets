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

class EnterKeyTypeClass {
  public typeValue?: number = 0
  public typeString?: string = ''
}

@Entry
@Component
struct EnterKeyTypeStruct {
  @State text: string = ''
  @State typeArray: EnterKeyTypeClass[] = [
    { typeValue: EnterKeyType.Go, typeString: 'GO' },
    { typeValue: EnterKeyType.Search, typeString: 'SEARCH' },
    { typeValue: EnterKeyType.Send, typeString: 'SEND' },
    { typeValue: EnterKeyType.Next, typeString: 'NEXT' },
    { typeValue: EnterKeyType.Done, typeString: 'DONE' },
    { typeValue: EnterKeyType.PREVIOUS, typeString: 'PREVIOUS' },
    { typeValue: EnterKeyType.NEW_LINE, typeString: 'NEW_LINE' },
    { typeValue: 0, typeString: 'DEFAULT_ZERO' },
    { typeValue: -1, typeString: 'INVALID_NEGATIVE' },]
  @State textInputIndex: number = 0
  @State textAreaIndex: number = 0

  build() {
    Column({ space: 20 }) {
      Text() {
        Span('规格:\n')
        Span('1、对输入内容进行限制 \n')
        Span('2、TextArea组件默认值：EnterKeyType.NEW_LINE \n')
        Span('3、TextInput组件默认值：EnterKeyType.Done \n')
        Span('4、输入参数分有效值（EnterKeyType枚举值）和无效值（0， -1） \n')
      }.draggable(true).copyOption(CopyOptions.InApp)

      Row() {
        Column() {
          Text('设置TextInput参数: ' + this.typeArray[this.textInputIndex].typeString)
          TextInput({ placeholder: 'TextInput', text: this.text })
            .enterKeyType(this.typeArray[this.textInputIndex].typeValue)
            .onChange((value: string) => {
              this.text = value
            })
          Button('改变TextInput EnterKeyType').onClick(() => {
            this.textInputIndex = (this.textInputIndex + 1) % this.typeArray.length;
          })
        }.width('100%')
      }.height('20%')

      Row() {
        Column() {
          Text('设置TextArea参数: ' + this.typeArray[this.textAreaIndex].typeString)
          TextArea({ placeholder: 'TextArea', text: this.text })
            .enterKeyType(this.typeArray[this.textAreaIndex].typeValue)
            .onChange((value: string) => {
              this.text = value
            })
          Button('改变TextArea EnterKeyType').onClick(() => {
            this.textAreaIndex = (this.textAreaIndex + 1) % this.typeArray.length;
          })
        }.width('100%')
      }.height('20%')
    }.width('100%')
  }
}