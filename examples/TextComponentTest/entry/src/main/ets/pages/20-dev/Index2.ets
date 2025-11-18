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
struct Marquee4269 {
  @State enterKeyType: EnterKeyType[] = [ EnterKeyType.Go, EnterKeyType.Search, EnterKeyType.Send, EnterKeyType.Next, EnterKeyType.Done, EnterKeyType.PREVIOUS, EnterKeyType.NEW_LINE ]
  @State enterKeyTypeIndex: number = 0
  @State submitValue: string = ''
  @State changeValue: string = ''
  controller: SearchController = new SearchController()

  build() {
    Column({ space:10 }) {
      Text('onSubmit:' + this.submitValue).fontSize(18).margin(15)
      Search({ value: this.changeValue, placeholder: 'Type to search...', controller: this.controller })
        .enterKeyType(this.enterKeyType[this.enterKeyTypeIndex])
        .onSubmit((value: string) => {
          this.submitValue = value
        })
        .onChange((value: string) => {
          this.changeValue = value
        })

      Row() {
        Button('enterKeyType: ' + EnterKeyType[this.enterKeyTypeIndex])
          .width('100%')
          .onClick(() => {
            this.enterKeyTypeIndex = (this.enterKeyTypeIndex + 1) % this.enterKeyType.length
          })
      }.width('80%')
    }
    .width('100%')
    .height('100%')
  }
}