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
struct TextInput45_5 {
  @State enterTypes: Array<EnterKeyType> = [EnterKeyType.Go, EnterKeyType.Search, EnterKeyType.Send, EnterKeyType.Done, EnterKeyType.Next, EnterKeyType.PREVIOUS, EnterKeyType.NEW_LINE]
  @State index: number = 0
  @State enterTypesStr: string[] = ['EnterKeyType.Go' ,'EnterKeyType.Search','EnterKeyType.Send','EnterKeyType.Done','EnterKeyType.Next','EnterKeyType.PREVIOUS','EnterKeyType.NEW_LINE']
  @State value: string = ''
  @State text: string = ''
  @State text2: string = ''
  @State style: TextInputStyle = TextInputStyle.Default


  build() {
    Column({ space: 20 }) {

      Text('text:' + this.value).width('80%')

      Text('onSubmit 设置keepEditableState和text').width('80%')
      TextInput({ placeholder: '请输入用户名', text: this.text })
        .width('80%')
        .enterKeyType(this.enterTypes[this.index])
        .style(this.style)
        .onChange((value: string) => {
          this.text = value
        })
        .onSubmit((enterKey: EnterKeyType,event: SubmitEvent) => {
          event.keepEditableState();
          this.value = event.text
        })

      Text('onSubmit 只设置keepEditableState').width('80%')
      TextInput({ placeholder: '请输入用户名', text: this.text2 })
        .width('80%')
        .margin({ top: 30 })
        .enterKeyType(this.enterTypes[this.index])
        .style(this.style)
        .onChange((value: string) => {
          this.text2 = value
        })
        .onSubmit((enterKey: EnterKeyType,event: SubmitEvent) => {
          event.keepEditableState();
          // this.value = event.text
        })

      Text('onSubmit 只设置text').width('80%')
      TextInput({ placeholder: '请输入用户名', text: this.text2 })
        .width('80%')
        .margin({ top: 30 })
        .enterKeyType(this.enterTypes[this.index])
        .style(this.style)
        .onChange((value: string) => {
          this.text2 = value
        })
        .onSubmit((enterKey: EnterKeyType,event: SubmitEvent) => {
          // event.keepEditableState();
          this.value = event.text
        })

      Button('EnterKeyType:' + this.enterTypesStr[this.index]).onClick(() => {
        this.index ++
        if (this.index > (this.enterTypes.length - 1)) {
          this.index = 0
        }
      })

      Button('style DEFAULT 默认').onClick(() => {
        this.style = TextInputStyle.Default
      })
      Button('style INLINE 内联').onClick(() => {
        this.style = TextInputStyle.Inline
      })


    }.width('100%')
  }
}