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
struct textOverflowPage {
  @State textOverflow: Array<number> = [TextOverflow.Clip, TextOverflow.Ellipsis]
  @State textOverflowString: Array<string> = ['TextOverflow.Clip', 'TextOverflow.Ellipsis']
  @State index: number = 0

  build() {
    Row() {
      Scroll() {
        Column() {
          Text() {
            Span('规格: \n')
            Span('1.仅在编辑态和非编辑态生效 placeHolder以及编辑文本会生效 maxlines默认为3 \n')
            Span('2.英文截断默认按词 按字截断配置WorkBreak.Break_ALL \n')
          }.draggable(true).copyOption(CopyOptions.InApp)

          Text('规格1测试 仅在编辑态和非编辑态生效 placeHolder以及编辑文本会生效 maxlines默认为3').fontSize(15)
          Text('当前为编辑文本 且textOverflow为' + this.textOverflowString[this.index]).fontSize(15).height(20)
          TextArea({
            text: 'A simple day in my life begins with a cup of coffee and a glimpse of the sunrise. I walk to the park, enjoying the fresh air and the sounds of nature. School or work follows, filled with challenges and learning opportunities. Afterwards, I spend time with family, sharing meals and stories. Before bed, I read a book or journal my thoughts. This routine brings me peace and happiness in the simplicity of daily life.'
          })
            .fontSize(25)
            .maxLines(2)
            .textOverflow(this.textOverflow[this.index])
            .style(TextContentStyle.INLINE)

          Text('当前为placeHolder 且textOverflow为' + this.textOverflowString[this.index]).fontSize(15)
          TextArea({
            text: 'A simple day in my life begins with a cup of coffee and a glimpse of the sunrise. I walk to the park, enjoying the fresh air and the sounds of nature. School or work follows, filled with challenges and learning opportunities. Afterwards, I spend time with family, sharing meals and stories. Before bed, I read a book or journal my thoughts. This routine brings me peace and happiness in the simplicity of daily life.'
          })
            .fontSize(25)
            .maxLines(2)
            .textOverflow(this.textOverflow[this.index])
            .style(TextContentStyle.INLINE)

          Button('改变textOverflow').onClick(() => {
            this.index = (this.index + 1) % this.textOverflow.length;
          })

          Text('规格2测试 英文截断默认按词 按字截断配置WorkBreak.Break_ALL').fontSize(15).height(30)
          Text('当前为英文').fontSize(15)
          Text('预期结果：英文按词截断').fontSize(15)
          TextArea({
            text: 'A simple day in my life begins with a cup of coffee and a glimpse of the sunrise. I walk to the park, enjoying the fresh air and the sounds of nature.'
          })
            .fontSize(20)
            .maxLines(5)
            .textOverflow(TextOverflow.Clip)
            .style(TextContentStyle.INLINE)

          Text('预期结果：中文按字截断').fontSize(15)
          Text('当前为中文').fontSize(15)
          TextArea({ text: '我平凡的一天从一杯咖啡和一抹日出的光芒开始。我走到公园，享受清新的空气和自然的声音。' })
            .fontSize(20)
            .maxLines(5)
            .textOverflow(TextOverflow.Clip)
            .wordBreak(WordBreak.BREAK_ALL)
            .style(TextContentStyle.INLINE)

          TextArea()
            .borderWidth(2)
            .height(500)
            .opacity(0)
        }.width('100%')
      }
    }
  }
}