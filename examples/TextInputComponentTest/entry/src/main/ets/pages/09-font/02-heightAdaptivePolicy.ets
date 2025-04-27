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
struct heightAdaptivePolicyPage {
  @State maxLines: Array<number> = [1, 2, 3]
  @State minFontSize: Array<number> = [10, 15, 20]
  @State maxFontSize: Array<number> = [25, 30, 35]
  @State heightAdaptivePolicy: Array<number> =
    [TextHeightAdaptivePolicy.MAX_LINES_FIRST, TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST,
      TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST]
  @State ratio: Array<number> = [3, 4, 5]
  @State maxLinesString: Array<String> = ['1', '2', '3']
  @State minFontSizeString: Array<String> = ['10', '15', '20']
  @State maxFontSizeString: Array<String> = ['25', '30', '35']
  @State heightAdaptivePolicyString: Array<String> =
    ['TextHeightAdaptivePolicy.MAX_LINES_FIRST', ' TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST',
      'TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST']
  @State testStyle: Array<String> = ['测试MAX_LINES_FIRST', '测试MIN_FONT_SIZE_FIRST', '测试LAYOUT_CONSTRAINT_FIRST']
  @State aspectRatioSting: Array<String> = ['3', '4', '5']
  @State index1: number = 0
  @State index2: number = 0
  @State index3: number = 0
  @State index4: number = 0
  @State index5: number = 0

  build() {
    Column() {
      Text() {
        Span('规格: \n')
        Span('1.当设置为MAX_LINES_FIRST，优先使用maxLines。如果超过约束布局 则根据minFontSize和maxFontSize来调整 \n')
        Span('2.当设置为MIN_FONT_SIZE_FIRST，优先使用maxLines。如果超过约束布局 则根据minFontSize和maxFontSize来调整 \n')
        Span('3.当设置为LAYOUT_CONSTRAINT_FIRST，优先使用maxLines。如果超过约束布局 则根据minFontSize和maxFontSize来调整 \n')
      }.draggable(true).copyOption(CopyOptions.InApp)

      Text('当前为测试规格 ' + (this.index4 + 1) + ' ' + this.testStyle[this.index4]).fontSize(20).width('80%')
      Text('当前maxLines = ' + this.maxLinesString[this.index3]).fontSize(20).width('80%')
      Text('当前minFontSize = ' + this.minFontSizeString[this.index1]).fontSize(20).width('80%')
      Text('当前maxFontSize = ' + this.maxFontSizeString[this.index2]).fontSize(20).width('80%')
      Text('当前aspectRatio = ' + this.aspectRatioSting[this.index5]).fontSize(20).width('80%')
      TextInput({ text: 'This is the text with the height adaptive policy set' })
        .width('80%')
        .height(90)
        .minFontSize(this.minFontSize[this.index1])
        .maxFontSize(this.maxFontSize[this.index2])
        .maxLines(this.maxLines[this.index3])
        .heightAdaptivePolicy(this.heightAdaptivePolicy[this.index4])
        .aspectRatio(this.ratio[this.index5])

      Button('更改minFontSize').onClick(() => {
        this.index1 = (this.index1 + 1) % this.minFontSize.length;
      })
      Button('更改maxFontSize').onClick(() => {
        this.index2 = (this.index2 + 1) % this.maxFontSize.length;
      })
      Button('更改maxLines').onClick(() => {
        this.index3 = (this.index3 + 1) % this.maxLines.length;
      })
      Button('Ratio').onClick(() => {
        this.index5 = (this.index5 + 1) % this.ratio.length;
      })
      Button('next test').onClick(() => {
        this.index4 = (this.index4 + 1) % this.maxLines.length;
      }).height(100)
    }
  }
}