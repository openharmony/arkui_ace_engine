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

const canvasWidth = 1000
const canvasHeight = 100

class LeadingMarginCreator {
  private settings: RenderingContextSettings = new RenderingContextSettings(true)
  private offscreenCanvas: OffscreenCanvas = new OffscreenCanvas(canvasWidth, canvasHeight)
  private offContext: OffscreenCanvasRenderingContext2D = this.offscreenCanvas.getContext('2d', this.settings)
  public static instance: LeadingMarginCreator = new LeadingMarginCreator()

  public genSquareMark(fontSize: number): PixelMap {
    this.offContext = this.offscreenCanvas.getContext('2d', this.settings)
    this.clearCanvas()
    const coordinate = fontSize * (1 - 1 / 1.5) / 2
    const sideLength = fontSize / 1.5
    this.offContext.fillRect(coordinate, coordinate, sideLength, sideLength)
    return this.offContext.getPixelMap(0, 0, fontSize, fontSize)
  }

  private clearCanvas() {
    this.offContext.clearRect(0, 0, canvasWidth, canvasHeight)
  }
}

@Entry
@Component
struct struct_01_StyledString_01_StyledStringValue_10_ParagraphStyle_06_leadingMargin_02_LeadingMarginPlaceholder {
  @State message: string = '运动45分钟';
  @State start: number = 0
  @State end: number = 5
  private leadingMarkCreatorInstance = LeadingMarginCreator.instance
  @State showValue1: string = ''
  controller1: TextController = new TextController()
  leadingMarginPlaceholder1: LeadingMarginPlaceholder = {
    pixelMap: this.leadingMarkCreatorInstance.genSquareMark(24),
    size: ['200px', '200px']
  }
  mutableStyledString1: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.PARAGRAPH_STYLE,
    styledValue: new ParagraphStyle({ leadingMargin: this.leadingMarginPlaceholder1 })
  }]);
  @State showValue2: string = ''
  controller2: TextController = new TextController()
  leadingMarginPlaceholder2: LeadingMarginPlaceholder = {
    pixelMap: this.leadingMarkCreatorInstance.genSquareMark(24),
    size: ['200vp', '200vp']
  }
  mutableStyledString2: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.PARAGRAPH_STYLE,
    styledValue: new ParagraphStyle({ leadingMargin: this.leadingMarginPlaceholder2 })
  }]);
  @State showValue3: string = ''
  controller3: TextController = new TextController()
  leadingMarginPlaceholder3: LeadingMarginPlaceholder = {
    pixelMap: this.leadingMarkCreatorInstance.genSquareMark(24),
    size: ['200fp', '200fp']
  }
  mutableStyledString3: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.PARAGRAPH_STYLE,
    styledValue: new ParagraphStyle({ leadingMargin: this.leadingMarginPlaceholder3 })
  }]);
  @State showValue4: string = ''
  controller4: TextController = new TextController()
  leadingMarginPlaceholder4: LeadingMarginPlaceholder = {
    pixelMap: this.leadingMarkCreatorInstance.genSquareMark(24),
    size: ['200lpx', '200lpx']
  }
  mutableStyledString4: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.PARAGRAPH_STYLE,
    styledValue: new ParagraphStyle({ leadingMargin: this.leadingMarginPlaceholder4 })
  }]);
  @State showValue5: string = ''
  controller5: TextController = new TextController()
  leadingMarginPlaceholder5: LeadingMarginPlaceholder = {
    pixelMap: this.leadingMarkCreatorInstance.genSquareMark(24),
    size: ['200%', '200%']
  }
  mutableStyledString5: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.PARAGRAPH_STYLE,
    styledValue: new ParagraphStyle({ leadingMargin: this.leadingMarginPlaceholder5 })
  }]);
  @State showValue6: string = ''
  controller6: TextController = new TextController()
  leadingMarginPlaceholder6: LeadingMarginPlaceholder = {
    pixelMap: this.leadingMarkCreatorInstance.genSquareMark(24),
    size: [200, 200]
  }
  mutableStyledString6: MutableStyledString = new MutableStyledString(this.message, [{
    start: this.start,
    length: this.end,
    styledKey: StyledStringKey.PARAGRAPH_STYLE,
    styledValue: new ParagraphStyle({ leadingMargin: this.leadingMarginPlaceholder6 })
  }]);

  aboutToAppear(): void {
    setTimeout(() => {
      let styles1 = this.mutableStyledString1.getStyles(this.start, this.end)
      let attribute1 = styles1[0].styledValue as ParagraphStyle;
      let margin1 = attribute1.leadingMargin as LeadingMarginPlaceholder
      console.info('StyledString leadingMargin:' + margin1.size[0] + ',' + margin1.size[1])
      this.showValue1 = 'getStyles 的值是 ' + margin1.size[0] + ',' + margin1.size[1]

      let styles2 = this.mutableStyledString2.getStyles(this.start, this.end)
      let attribute2 = styles2[0].styledValue as ParagraphStyle;
      let margin2 = attribute2.leadingMargin as LeadingMarginPlaceholder
      console.info('StyledString leadingMargin:' + margin2.size[0] + ',' + margin2.size[1])
      this.showValue2 = 'getStyles 的值是 ' + margin2.size[0] + ',' + margin2.size[1]

      let styles3 = this.mutableStyledString3.getStyles(this.start, this.end)
      let attribute3 = styles3[0].styledValue as ParagraphStyle;
      let margin3 = attribute3.leadingMargin as LeadingMarginPlaceholder
      console.info('StyledString leadingMargin:' + margin3.size[0] + ',' + margin3.size[1])
      this.showValue3 = 'getStyles 的值是 ' + margin3.size[0] + ',' + margin3.size[1]

      let styles4 = this.mutableStyledString4.getStyles(this.start, this.end)
      let attribute4 = styles4[0].styledValue as ParagraphStyle;
      let margin4 = attribute4.leadingMargin as LeadingMarginPlaceholder
      console.info('StyledString leadingMargin:' + margin4.size[0] + ',' + margin4.size[1])
      this.showValue4 = 'getStyles 的值是 ' + margin4.size[0] + ',' + margin4.size[1]

      let styles5 = this.mutableStyledString5.getStyles(this.start, this.end)
      let attribute5 = styles5[0].styledValue as ParagraphStyle;
      let margin5 = attribute5.leadingMargin as LeadingMarginPlaceholder
      console.info('StyledString leadingMargin:' + margin5.size[0] + ',' + margin5.size[1])
      this.showValue6 = 'getStyles 的值是 ' + margin5.size[0] + ',' + margin5.size[1]

      let styles6 = this.mutableStyledString6.getStyles(this.start, this.end)
      let attribute6 = styles6[0].styledValue as ParagraphStyle;
      let margin6 = attribute6.leadingMargin as LeadingMarginPlaceholder
      console.info('StyledString leadingMargin:' + margin6.toString())
      this.showValue6 = 'getStyles 的值是 ' + margin6.size[0] + ',' + margin6.size[1]

    }, 100)
  }

  build() {
    Column() {
      Column() {
        Text('测试 TextStyle leadingMargin LeadingMarginPlaceholder size unit px 类型')
        Text('pass条件：size 的值是 133.33333333333334 ')
        Text(undefined, { controller: this.controller1 })
        Text(this.showValue1)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle leadingMargin LeadingMarginPlaceholder size unit vp 类型')
        Text('pass条件：size 的值是 200 ')
        Text(undefined, { controller: this.controller2 })
        Text(this.showValue2)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle leadingMargin LeadingMarginPlaceholder size unit fp 类型')
        Text('pass条件：size 的值是 200 ')
        Text(undefined, { controller: this.controller3 })
        Text(this.showValue3)
      }.borderWidth(1)

      Column() {
        Text('测试 TTextStyle leadingMargin LeadingMarginPlaceholder size unit lpx 类型')
        Text('pass条件：size 的值是 133.33333333333334 ')
        Text(undefined, { controller: this.controller4 })
        Text(this.showValue4)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle leadingMargin LeadingMarginPlaceholder size unit percent 类型')
        Text('pass条件：size 的值是 0 ')
        Text(undefined, { controller: this.controller5 })
        Text(this.showValue5)
      }.borderWidth(1)

      Column() {
        Text('测试 TextStyle leadingMargin LeadingMarginPlaceholder size unit 无单位 类型')
        Text('pass条件：size 的值是 200 ')
        Text(undefined, { controller: this.controller6 })
        Text(this.showValue6)
      }.borderWidth(1)

    }
    .height('100%')
    .width('100%')
  }
}