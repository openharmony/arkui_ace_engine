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
struct textIndentPage {
  @State textIndent: Array<number> = [-1, 0, 10, 20, 50]
  @State textIndentString: Array<string> = ['-1', '0', '10', '20', '50']
  @State index: number = 0
  @State index1: number = 0

  build() {
    Row() {
      Scroll() {
        Column() {
          Text() {
            Span('规格: \n')
            Span('1.设置首行文本缩进，默认值：0 ，小于0时 缩进效果为0 \n')
            Span('2.对placeholder不生效 \n')
          }.draggable(true).copyOption(CopyOptions.InApp)

          Text('规格1测试 设置首行文本缩进').fontSize(15)
          TextInput({ text: 'set textIndent to ' + this.textIndentString[this.index] })
            .fontSize(25)
            .textIndent(this.textIndent[this.index])
          TextArea({ text: 'set textIndent to ' + this.textIndentString[this.index] })
            .fontSize(25)
            .textIndent(this.textIndent[this.index])

          Button('改变首行文本缩进').onClick(() => {
            this.index = (this.index + 1) % this.textIndent.length;
          })

          Text('规格2测试 改变textIndent对placeholder不生效').fontSize(15)
          Text('当前为placeholder').fontSize(20)
          TextArea({ placeholder: 'set textIndent to ' + this.textIndentString[this.index1] })
            .fontSize(25)
            .letterSpacing(this.textIndent[this.index1])
          Text('当前为text').fontSize(20)
          TextArea({ text: 'pan letter spacing' + ' ' + this.textIndentString[this.index1] })
            .fontSize(25)
            .letterSpacing(this.textIndent[this.index1])
          Button('改变首行文本缩进').onClick(() => {
            this.index1 = (this.index1 + 1) % this.textIndent.length;
          })
          TextArea()
            .borderWidth(2)
            .height(500)
            .opacity(0)
        }.width('100%')
      }
    }
  }
}