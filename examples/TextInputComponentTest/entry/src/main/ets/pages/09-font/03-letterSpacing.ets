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
struct letterSpacingPage {
  @State letterSpacing: Array<number | string> = [-20, -5, 0, 3, 20, '50%']
  @State letterSpacingString: Array<string> = ['-20', '-5', '0', '3', '20', '50%']
  @State index: number = 0

  build() {
    Row() {
      Column() {
        Text() {
          Span('规格: \n')
          Span('1.设置文本字符间距。为百分比或0时为默认值 为负数时会压缩 \n')
          Span('2.设置为15vp，此时手柄和选中态无偏差 \n')
          Span('3.设置为-1，计算得到的左手柄的位置超出最左侧 \n')
        }.draggable(true).copyOption(CopyOptions.InApp)

        Text('规格1测试 设置文本字符间距的值为' + this.letterSpacingString[this.index]).fontSize(15)
        TextInput({ text: '测试1 pan letter spacing' })
          .fontSize(20)
          .wordBreak(WordBreak.NORMAL)
          .letterSpacing(this.letterSpacing[this.index])
        TextArea({ text: '测试1 pan letter spacing' })
          .fontSize(20)
          .wordBreak(WordBreak.NORMAL)
          .letterSpacing(this.letterSpacing[this.index])

        Button('改变文本字符间距').onClick(() => {
          this.index = (this.index + 1) % this.letterSpacingString.length;
        })

        Text('规格2测试 设置为15vp，此时手柄和选中态无偏差').fontSize(15)
        TextInput({ text: '测试2 ：pan letter spacing' })
          .fontSize(20)
          .letterSpacing('15vp')
        TextArea({ text: '测试2 ：pan letter spacing' })
          .fontSize(20)
          .letterSpacing('15vp')

        Text('规格3测试 设置为-1，计算得到的左手柄的位置超出最左侧').fontSize(15)
        TextInput({ text: '测试3 ：pan letter spacing' })
          .fontSize(20)
          .letterSpacing(-1)
        TextArea({ text: '测试3 ：pan letter spacing' })
          .fontSize(20)
          .letterSpacing(-1)

      }.width('100%')
    }
    .height('100%')
  }
}