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
struct minFontSizePage {
  @State minFontSize: Array<number> = [10, 15, 20]
  @State fontSize: Array<number> = [10, 20, 30]
  @State textHeightAdaptivePolicy: Array<number> =
    [TextHeightAdaptivePolicy.MAX_LINES_FIRST, TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
      TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST]
  @State minFontSizeString: Array<string> = ['0', '1', '2']
  @State index: number = 0
  @State index2: number = 0

  build() {
    Row() {
      Scroll() {
        Column() {
          Text() {
            Span('规格: \n')
            Span('1.当设置了heightAdaptivePolicy时放大字体时字体不随系统开关调整 \n')
            Span('2.minFontSize属性设置等于0，minFontSize设置不生效 \n')
            Span('3.自适应字号生效时，fontSize设置不生效 \n')
            Span('4.minFontSize小于或等于0时， 自适应字号不生效 \n')
          }.draggable(true).copyOption(CopyOptions.InApp)

          Text('规格1测试：当设置了heightAdaptivePolicy时放大字体时字体不随系统开关调整').fontSize(10)
          Text('存在heightAdaptivePolicy').fontSize(12)
          TextInput({ text: 'This is the text with the minFontSize' })
            .width('80%')
            .fontSize(this.fontSize[this.index])
            .minFontSize(10)
            .style(TextContentStyle.INLINE)
            .maxFontSize(30)
            .maxLines(3)
            .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)

          Text('不存在heightAdaptivePolicy').fontSize(12)
          TextInput({ text: 'This is the text with the minFontSize' })
            .width('80%')
            .fontSize(this.fontSize[this.index])

          Button('改变fontSize').onClick(() => {
            this.index = (this.index + 1) % this.minFontSize.length;
          })

          Text('规格2测试：minFontSize属性设置等于0，minFontSize设置不生效').fontSize(20)
          Text('minFontSize不等于0').fontSize(12)
          TextInput({ text: 'This is the text with the minFontSize' })
            .width('80%')
            .minFontSize(10)
            .style(TextContentStyle.INLINE)
            .maxFontSize(20)
            .maxLines(3)

          Text('minFontSize等于0').fontSize(12)
          TextInput({ text: 'This is the text with the minFontSize' })
            .width('80%')
            .minFontSize(0)
            .style(TextContentStyle.INLINE)
            .maxFontSize(20)
            .maxLines(3)

          Text('规格3测试：自适应字号生效时，fontSize设置不生效').fontSize(20)
          Text('自适应字号生效时').fontSize(12)
          TextInput({ text: 'This is the text with the minFontSize' })
            .width('80%')
            .minFontSize(10)
            .maxFontSize(30)
            .maxLines(3)
            .fontSize(this.fontSize[this.index2])
          Text('自适应字号不生效时').fontSize(12)
          TextInput({ text: 'This is the text with the minFontSize' })
            .width('80%')
            .fontSize(this.fontSize[this.index2])
          Button('改变文本字符间距').onClick(() => {
            this.index2 = (this.index2 + 1) % this.minFontSizeString.length;
          })

          Text('规格4测试：minFontSize小于或等于0时， 自适应字号不生效').fontSize(20)
          Text('minFontSize不等于0').fontSize(12)
          TextInput({ text: 'This is the text with the minFontSize' })
            .width('80%')
            .minFontSize(10)
            .maxFontSize(30)
            .maxLines(3)
          Text('minFontSize等于0').fontSize(12)
          TextInput({ text: 'This is the text with the minFontSize' })
            .width('80%')
            .minFontSize(0)
            .maxFontSize(30)
            .maxLines(3)

          TextArea()
            .borderWidth(2)
            .height(500)
            .opacity(0)
        }
      }
    }
  }
}