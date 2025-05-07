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

import { LengthMetrics } from '@ohos.arkui.node';

@Extend(Text)
function lineSpacingValue(lineSpacing: LengthMetrics | undefined) {
  .lineSpacing(lineSpacing)
  .fontSize(12)
  .border({ width: 1 })
}

@Entry
@Component
struct TextExample8 {
  @State message1: string =
    'They can be classified as built-in components–those directly provided by the ArkUI framework and custom components – those defined by developers' +
      'The built-in components include buttons radio buttonsprogress indicators and text You can set the rendering effectof thesecomponents in method chaining mode,' +
      'page components are divided into independent UI units to implementindependent creation development and reuse of different units on pages making pages more engineering-oriented.';
  @State lineBreakStrategyIndex: number = 0;
  @State lineBreakStrategy: LineBreakStrategy[] =
    [LineBreakStrategy.GREEDY, LineBreakStrategy.HIGH_QUALITY, LineBreakStrategy.BALANCED]
  @State lineBreakStrategyStr: string[] = ['GREEDY', 'HIGH_QUALITY', 'BALANCED']

  build() {
    Row() {
      Column() {
        Text() {
          Span('规格: \n')
          Span('1.Inline生效 \n')
          Span('2.GREEDY:使每一行尽量显示多的字符，直到这一行不能显示更多字符再进行折行。 \n')
          Span('3.HIGH_QUALITY:在BALANCED的基础上，尽可能填满行，在最后一行的权重上比较低，可能会出现最后一行留白比较多。 \n')
          Span('4.BALANCED:尽可能保证在不拆词的情况下，使一个段落中每一行的宽度相同。 \n')
        }.draggable(true).copyOption(CopyOptions.InApp)

        Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Start, justifyContent: FlexAlign.SpaceBetween }) {
          Text('规格测试 ' + (this.lineBreakStrategyIndex + 2) + ' 测试' +
          this.lineBreakStrategyStr[this.lineBreakStrategyIndex]).fontSize(10)
          TextArea({
            text: 'A simple day in my life begins with a cup of coffee and a glimpse of the sunrise. I walk to the park, enjoying the fresh air and the sounds of nature. School or work follows, filled with challenges and learning opportunities. Afterwards, I spend time with family, sharing meals and stories. Before bed, I read a book or journal my thoughts. This routine brings me peace and happiness in the simplicity of daily life.'
          })
            .fontSize(12)
            .padding(10)
            .width('100%')
            .lineBreakStrategy(this.lineBreakStrategy[this.lineBreakStrategyIndex])
          Button('nextTest').onClick(() => {
            this.lineBreakStrategyIndex = (this.lineBreakStrategyIndex + 1) % this.lineBreakStrategy.length;
          })
        }.height(600).width(350).padding({ left: 35, right: 35, top: 35 })
      }
    }
  }
}