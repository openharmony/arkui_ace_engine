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
struct workBreakPage {
  @State text: Array<string> =
    ['A simple day in my life begins with a cup of coffee and a glimpse of the sunrise. I walk to the park, enjoying the fresh air and the sounds of nature.',
      '我平凡的一天从一杯咖啡和一抹日出的光芒开始。我走到公园，享受清新的空气和自然的声音。']
  @State wordBreak: Array<WordBreak | number> = [WordBreak.NORMAL, WordBreak.BREAK_ALL, WordBreak.BREAK_WORD]
  @State wordBreakString: Array<string> = ['WordBreak.NORMAL', 'WordBreak.BREAK_ALL', 'WordBreak.BREAK_WORD']
  @State wordBreakFunction: Array<string> = ['中文文本可以在任意2个字符间断行，而英文文本只能在空白符处断行。',
    '对于英文文本，可在任意2个字符间断行。对于中文文本与NORMAL效果一致。',
    '与BREAK_ALL相同，对于英文文本可在任意2个字符间断行，一行文本中有断行破发点（如空白符）时，优先按破发点换行，保障单词优先完整显示。' +
      '若整一行文本均无断行破发点时，则在任意2个字符间断行。对于中文文本与NORMAL效果一致。']
  @State index: number = 0
  @State index1: number = 0

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start, justifyContent: FlexAlign.SpaceBetween }) {
      Scroll() {
        Column({ space: 10 }) {
          Text() {
            Span('规格: \n')
            Span('1.设置断行规则 \n')
            Span('2.WordBreak与overflow, maxLines组合使用可实现英文单词按字母截断，超出部分以省略号显示 \n')
          }.draggable(true).copyOption(CopyOptions.InApp)

          Text('规格1测试:设置断行规则').fontSize(20)
          Text('当前workBreak为： ' + this.wordBreakString[this.index]).fontSize(12)
          Text('当前workBreak规则为： ' + this.wordBreakFunction[this.index]).fontSize(12)
          TextArea({ text: this.text[this.index1] })
            .fontSize(12)
            .border({ width: 1 })
            .maxLines(2)
            .style(TextContentStyle.INLINE)
            .textOverflow(TextOverflow.Ellipsis)
            .wordBreak(this.wordBreak[this.index])
            .lineHeight(20)
          Button('改变WordBreak').onClick(() => {
            this.index = (this.index + 1) % this.wordBreakString.length;
          })
          Button('改变语言').onClick(() => {
            this.index1 = (this.index1 + 1) % this.text.length;
          })

          Text('规格2测试:WordBreak与overflow, maxLines组合使用可实现英文单词按字母截断，超出部分以省略号显示')
            .fontSize(20)
          TextArea({ text: this.text[0] + this.text[0] })
            .textOverflow(TextOverflow.Ellipsis)
            .wordBreak(WordBreak.BREAK_ALL)
            .style(TextContentStyle.INLINE)
            .fontSize(12)
            .maxLines(3)

          TextArea()
            .borderWidth(2)
            .height(500)
            .opacity(0)
        }.width(335)
      }
    }
  }
}