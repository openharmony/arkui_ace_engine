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

// xxx.ets
@Entry
@Component
struct TextArea5_5 {
  @State Text: string = ''
  @State Text1: string = ''
  @State enterTypes: Array<EnterKeyType> = [EnterKeyType.Go, EnterKeyType.Search, EnterKeyType.Send, EnterKeyType.Done, EnterKeyType.Next, EnterKeyType.PREVIOUS, EnterKeyType.NEW_LINE]
  @State index: number = 0
  @State enterTypesStr: string[] = ['EnterKeyType.Go' ,'EnterKeyType.Search','EnterKeyType.Send','EnterKeyType.Done','EnterKeyType.Next','EnterKeyType.PREVIOUS','EnterKeyType.NEW_LINE']
  @State style: TextContentStyle = TextContentStyle.DEFAULT
  build() {
    Column({ space: 20 }) {
      Text("onSubmit:" + this.Text1)
      TextArea({ placeholder: '请输入用户名', text: this.Text })
        .width(380)
        .style(this.style)
        .enterKeyType(this.enterTypes[this.index])
        .onChange((value: string) => {
          this.Text = value
        })
        .onSubmit((enterKey: EnterKeyType) => {
          this.Text1 = enterKey + ''
          // this.Text1 += EnterKeyType[enterKey]
          console.log("trigger area onsubmit" + enterKey);
        })
      Button('EnterKeyType:' + this.enterTypesStr[this.index]).onClick(() => {
        this.index ++
        if (this.index > (this.enterTypes.length - 1)) {
          this.index = 0
        }
      })
      Button('style DEFAULT 默认').onClick(() => {
        this.style = TextContentStyle.DEFAULT
      })
      Button('style INLINE 内联').onClick(() => {
        this.style = TextContentStyle.INLINE
      })


    }.width('100%')
  }
}