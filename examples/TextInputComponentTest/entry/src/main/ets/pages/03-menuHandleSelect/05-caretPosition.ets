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
struct SearchExample {
  @State numberIndex: number = 0
  @State testCaseListNumber: (number | undefined | null)[] = [
    0.5, 1, 3.5, 5, 100, -1, undefined, null
  ]
  controller: SearchController = new SearchController()

  build() {
    Column({ space: 10 }) {
      Text('onSubmit:').fontSize(18).margin(15)
      Text('').fontSize(18).margin(15)
      Search({ placeholder: 'Type to search...', controller: this.controller })
        .searchButton('SEARCH')
        .width('95%')
        .height(40)
        .backgroundColor('#F5F5F5')
        .placeholderColor(Color.Grey)
        .placeholderFont({ size: 14, weight: 400 })
        .textFont({ size: 14, weight: 400 })
        .margin(20)
      Button('Set caretPosition: ' + this.numberIndex)
        .onClick(() => {
          this.controller.caretPosition(this.testCaseListNumber[this.numberIndex])
        })
      Button('改变测试参数')
        .onClick(() => {
          this.numberIndex++
          if (this.numberIndex > this.testCaseListNumber.length - 1) {
            this.numberIndex = 0
          }
        })
    }.width('100%')
  }
}