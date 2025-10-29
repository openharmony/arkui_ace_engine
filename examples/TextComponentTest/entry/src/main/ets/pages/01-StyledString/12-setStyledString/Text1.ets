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
struct TextFontScale {
  @State fontSize: number = 16
  @State fontWeight1: number = 400
  @State colorAll: Color[] = [Color.Black, Color.Blue, Color.Pink, Color.Yellow, Color.Brown]
  @State color: number = 0
  @State text: string = ''
  @State decorationType: TextDecorationType[] =
    [TextDecorationType.None, TextDecorationType.Underline, TextDecorationType.LineThrough, TextDecorationType.Overline]
  @State typeIndex: number = 0
  @State decorationColor: number = 0
  @State enableDataDetector: boolean = false
  @State copyOption: CopyOptions[] =
    [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 2
  @State width1: number = 200
  @State height1: number = 50
  @State ellipsisMode: EllipsisMode[] = [EllipsisMode.START, EllipsisMode.CENTER, EllipsisMode.END]
  @State ellipsisModeStr: string[] = ['START', 'CENTER', 'END']
  @State ellipsisModeIndex: number = 2
  @State textOverflow: TextOverflow[] =
    [TextOverflow.Clip, TextOverflow.None, TextOverflow.Ellipsis, TextOverflow.MARQUEE]
  @State textOverflowStr: string[] = ['Clip', 'None', 'Ellipsis', 'MARQUEE']
  @State textOverflowIndex: number = 0
  @State obscured1: ObscuredReasons[] = []
  @State obscured2: ObscuredReasons[] = [ObscuredReasons.PLACEHOLDER]
  @State maxLines: number = 1
  @State selectionStart: number = -1
  @State selectionEnd: number = -1
  @State wordBreak: WordBreak[] = [WordBreak.NORMAL, WordBreak.BREAK_ALL, WordBreak.BREAK_WORD]
  @State wordBreakStr: string[] = ['NORMAL', 'BREAK_ALL', 'BREAK_WORD']
  @State wordBreakIndex: number = 2
  @State clip1: boolean = true
  scroll: Scroller = new Scroller()
  fontStyleAttr1: TextStyle = new TextStyle({ fontColor: Color.Blue })
  fontStyleAttr2: StyledStringValue = new TextStyle({ fontColor: Color.Orange })
  //创建构造入参只有字符串的对象styledString1
  styledString1: StyledString = new StyledString("电话号码：15544889988", [{
    start: 0,
    length: 8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString3: StyledString = new StyledString("这是一段测试文字", [
    {
      start: 0,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Blue })
    },
    {
      start: 4,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Red })
    }
  ])
  styledString4: StyledString = new StyledString("这是测试字符：Abc123！@#￥%…&*（）", [
    {
      start: 0,
      length: 7,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Blue })
    },
    {
      start: 7,
      length: 30,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Red })
    }
  ])
  styledString5: StyledString = new StyledString("这是一段测试文字", [
    {
      start: 0,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Blue })
    },
    {
      start: 2,
      length: 4,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Red })
    }
  ])
  styledString6: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 3,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString7: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 10,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString8: StyledString = new StyledString("这是一段测试文字")
  styledString9: StyledString = new StyledString("这是一段测试文字",
    [{ styledKey: StyledStringKey.FONT, styledValue: new TextStyle({ fontColor: Color.Blue }) }])
  styledString10: StyledString = new StyledString("这是一段测试文字", [{
    start: 15,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString11: StyledString = new StyledString("这是一段测试文字", [{
    start: -5,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString12: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: -8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString13: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString24: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString25: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString26: StyledString = new StyledString("这是一段测试字符", [{
    start: 0,
    length: 8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString27: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: 0x0000ff })
  }])
  styledString28: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Red })
  }])
  styledString37: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 4,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString44: StyledString = new StyledString("这是一段测试文字", [{
    start: 0,
    length: 4,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }])
  styledString45: StyledString = new StyledString("这是一段测试文字", [
    {
      start: 0,
      length: 2,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Blue })
    },
    {
      start: 2,
      length: 2,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Red })
    },
    {
      start: 4,
      length: 2,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Pink })
    },
    {
      start: 6,
      length: 2,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Yellow })
    }
  ])
  spanStyle38: SpanStyle = {
    start: 0,
    length: 4,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Pink })
  }
  spanStyle39: SpanStyle = {
    start: -1,
    length: 4,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Pink })
  }
  spanStyle40: SpanStyle = {
    start: 20,
    length: 4,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Pink })
  }
  spanStyle41: SpanStyle = {
    start: 0,
    length: -1,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Pink })
  }
  spanStyle42: SpanStyle = {
    start: 0,
    length: 20,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Pink })
  }
  spanStyle43: SpanStyle = {
    start: 6,
    length: 3,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Pink })
  }
  //创建构造入参只有字符串的对象mutableStyledString1
  mutableStyledString2: MutableStyledString = new MutableStyledString("email：1056602211@huawei.com", [{
    start: 0,
    length: 8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }]);
  mutableStyledString3: MutableStyledString = new MutableStyledString("这是一段测试文字", [{
    start: 0,
    length: 8,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({ fontColor: Color.Blue })
  }]);
  controller1: TextController = new TextController();
  controller2: TextController = new TextController();
  controller3: TextController = new TextController();
  controller4: TextController = new TextController();
  controller5: TextController = new TextController();
  controller6: TextController = new TextController();
  controller7: TextController = new TextController();
  controller8: TextController = new TextController();
  controller9: TextController = new TextController();
  controller10: TextController = new TextController();
  controller11: TextController = new TextController();
  controller12: TextController = new TextController();
  controller37: TextController = new TextController();
  controller33: TextController = new TextController();
  controller44: TextController = new TextController();
  controller45: TextController = new TextController();

  async onPageShow() {
    this.controller1.setStyledString(this.styledString1)
    this.controller2.setStyledString(this.mutableStyledString2)
    this.controller3.setStyledString(this.styledString3)
    this.controller4.setStyledString(this.styledString4)
    this.controller5.setStyledString(this.styledString5)
    this.controller6.setStyledString(this.styledString6)
    this.controller7.setStyledString(this.styledString7)
    this.controller8.setStyledString(this.styledString8)
    this.controller9.setStyledString(this.styledString9)
    this.controller10.setStyledString(this.styledString10)
    this.controller11.setStyledString(this.styledString11)
    this.controller12.setStyledString(this.styledString12)
    this.controller37.setStyledString(this.styledString37)
    this.controller33.setStyledString(this.mutableStyledString3)
    this.controller44.setStyledString(this.styledString44)
    this.controller45.setStyledString(this.styledString45)
  }

  build() {
    Column() {
      TextInput().height(60)
      Divider()
      Scroll() {
        Column() {
          Text(undefined, { controller: this.controller1 })
            .key('styledString1')
            .margin({ top: 50 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller2 })
            .key('mutableStyledString1')
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller3 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller4 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller5 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller6 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller7 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller8 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller9 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller10 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller11 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text(undefined, { controller: this.controller12 })
            .margin({ top: 10 })
            .borderWidth(1)
            .height(this.height1)
            .width(this.width1)
            .fontSize(this.fontSize)
            .fontColor(this.colorAll[this.color])
            .decoration({
              type: this.decorationType[this.typeIndex],
              color: this.colorAll[this.decorationColor]
            })
            .enableDataDetector(this.enableDataDetector)
            .copyOption(this.copyOption[this.index])

            .ellipsisMode(this.ellipsisMode[this.ellipsisModeIndex])
            .textOverflow({
              overflow: this.textOverflow[this.textOverflowIndex]
            })
            .obscured(this.obscured1)
            .maxLines(this.maxLines)
            .selection(this.selectionStart, this.selectionEnd)
            .wordBreak(this.wordBreak[this.wordBreakIndex])
            .clip(this.clip1)

          Text('0370:').margin({ top: 10 })
          Text(undefined, { controller: this.controller37 }).margin({ top: 10 }).fontColor(Color.Red)

          Divider()

          Text(this.text).borderWidth(1).margin({ top: 10 })
        }
      }.height('50%')


      Scroll(this.scroll) {
        Column() {

          Row() {
            Button('fontSize+,' + this.fontSize)
              .width('40%')
              .onClick(() => {
                this.fontSize += 5
              })

            Button('fontSize-,' + this.fontSize)
              .width('40%')
              .onClick(() => {
                this.fontSize -= 5
              })
          }

          Row() {
            Button('width+,' + this.width1)
              .width('40%')
              .onClick(() => {
                this.width1 += 10
              })

            Button('width-,' + this.width1)
              .width('40%')
              .onClick(() => {
                this.width1 -= 10
              })
          }

          Row() {
            Button('height+,' + this.height1)
              .width('40%')
              .onClick(() => {
                this.height1 += 10
              })

            Button('height-,' + this.height1)
              .width('40%')
              .onClick(() => {
                this.height1 -= 10
              })
          }

          Row() {
            Button('fontColor:' + this.colorAll[this.color])
              .width('80%')
              .onClick(() => {
                this.color = (this.color + 1) % this.colorAll.length
              })
          }

          Row() {
            Button('decorationType')
              .width('40%')
              .onClick(() => {
                this.typeIndex = (this.typeIndex + 1) % this.decorationType.length
              })

            Button('decorationColor')
              .width('40%')
              .onClick(() => {
                this.decorationColor = (this.decorationColor + 1) % this.colorAll.length
              })
          }

          Row() {
            Button('enableDataDetector:' + this.enableDataDetector)
              .width('80%')
              .onClick(() => {
                this.enableDataDetector = !this.enableDataDetector
              })
          }

          Row() {
            Button('copyOption:' + this.copyOptionStr[this.index])
              .width('80%')
              .onClick(() => {
                this.index++
                if (this.index > (this.copyOptionStr.length - 1)) {
                  this.index = 0
                }
              })
          }

          Row() {
            Button('ellipsisMode:' + this.ellipsisModeStr[this.ellipsisModeIndex])
              .width('40%')
              .onClick(() => {
                this.ellipsisModeIndex = (this.ellipsisModeIndex + 1) % this.ellipsisMode.length
              })

            Button('clip:' + this.clip1)
              .width('40%')
              .onClick(() => {
                this.clip1 = !this.clip1
              })
          }

          Row() {
            Button('textOverflow:' + this.textOverflowStr[this.textOverflowIndex])
              .width('80%')
              .onClick(() => {
                this.textOverflowIndex = (this.textOverflowIndex + 1) % this.textOverflow.length
              })
          }

          Row() {
            Button('文本遮罩')
              .width('40%')
              .onClick(() => {
                this.obscured1 = [ObscuredReasons.PLACEHOLDER]
              })

            Button('不遮罩')
              .width('40%')
              .onClick(() => {
                this.obscured1 = []
              })
          }

          Row() {
            Button('maxLines+,' + this.maxLines)
              .width('40%')
              .onClick(() => {
                this.maxLines += 1
              })

            Button('maxLines-,' + this.maxLines)
              .width('40%')
              .onClick(() => {
                this.maxLines -= 1
              })
          }

          Row() {
            Button('selectionStart+,' + this.selectionStart)
              .width('40%')
              .onClick(() => {
                this.selectionStart += 1
              })

            Button('selectionStart-,' + this.selectionStart)
              .width('40%')
              .onClick(() => {
                this.selectionStart -= 1
              })
          }

          Row() {
            Button('selectionEnd+,' + this.selectionEnd)
              .width('40%')
              .onClick(() => {
                this.selectionEnd += 1
              })

            Button('selectionEnd-,' + this.selectionEnd)
              .width('40%')
              .onClick(() => {
                this.selectionEnd -= 1
              })
          }

          Row() {
            Button('wordBreak:' + this.wordBreakStr[this.wordBreakIndex])
              .width('80%')
              .onClick(() => {
                this.wordBreakIndex = (this.wordBreakIndex + 1) % this.wordBreakStr.length
              })
          }

          Row() {
            Button('1 getString')

              .width('40%')
              .onClick(() => {
                this.text = this.styledString1.getString()
              })

            Button('4 getString')

              .width('40%')
              .onClick(() => {
                this.text = this.styledString4.getString()
              })
          }

          Row() {
            Button('1 getString(0,4)')

              .width('30%')
              .onClick(() => {
                this.text = JSON.stringify(this.styledString1.getStyles(0, 4, StyledStringKey.FONT))
                let styles = this.styledString1.getStyles(0, 4)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })

            Button('0160')
              .width('30%')
              .onClick(() => {
                this.text = JSON.stringify(this.styledString1.getStyles(0, 4))
                let styles = this.styledString1.getStyles(0, 4)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })

            Button('0170')
              .width('30%')
              .onClick(() => {
                this.text = JSON.stringify(this.styledString3.getStyles(0, 8, StyledStringKey.FONT))
                let styles = this.styledString1.getStyles(0, 8)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })
          }

          Row() {
            Button('0180')
              .width('30%')
              .onClick(() => {
                this.text = JSON.stringify(this.styledString1.getStyles(-5, 8, StyledStringKey.FONT))
                let styles = this.styledString1.getStyles(-5, 8)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })

            Button('0190')
              .width('30%')
              .onClick(() => {
                this.text = JSON.stringify(this.styledString1.getStyles(20, 8, StyledStringKey.FONT))
                let styles = this.styledString1.getStyles(20, 8)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })

            Button('0200')
              .width('30%')
              .onClick(() => {
                this.text = JSON.stringify(this.styledString1.getStyles(0, -8, StyledStringKey.FONT))
                let styles = this.styledString1.getStyles(0, -8)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })
          }

          Row() {
            Button('0210')
              .width('30%')
              .onClick(() => {
                this.text = JSON.stringify(this.styledString1.getStyles(0, 10, StyledStringKey.FONT))
                let styles = this.styledString1.getStyles(0, 10)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })

            Button('0220')
              .width('30%')
              .onClick(() => {
                this.text = JSON.stringify(this.styledString1.getStyles(4, 6, StyledStringKey.FONT))
                let styles = this.styledString1.getStyles(4, 6)
                if (styles) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      this.text += '\n' + `fontColor${i}:` + fontAttr.fontColor
                    }
                  }
                }
              })

            Button('0230')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.length + ''
              })
          }

          Row() {
            Button('0240')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.equals(this.styledString24) + ''
              })

            Button('0250')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.equals(this.styledString25) + ''
              })

            Button('0260')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.equals(this.styledString26) + ''
              })
          }

          Row() {
            Button('0270')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.equals(this.styledString27) + ''
              })

            Button('0280')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.equals(this.styledString28) + ''
              })

            Button('0290')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.subStyledString(0, 3).getString()
              })
          }

          Row() {
            Button('0300')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.subStyledString(0).getString()
              })

            Button('0310')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.subStyledString(5).getString()
              })

            Button('0320')
              .width('30%')
              .onClick(() => {
                this.text = this.styledString1.subStyledString(-1, 3).getString()
              })
          }

          Row() {
            Button('0330')
              .onClick(() => {
                this.text = this.styledString1.subStyledString(20, 3).getString()
              })

            Button('0340')
              .onClick(() => {
                this.text = this.styledString1.subStyledString(0, -3).getString()
              })

            Button('0350')
              .onClick(() => {
                this.text = this.styledString1.subStyledString(0, 10).getString()
              })

            Button('0360')
              .onClick(() => {
                this.text = this.styledString1.subStyledString(6, 4).getString()
              })
          }

          Text(undefined, { controller: this.controller33 }).margin({ top: 10 })

          Row() {
            Button('0380')
              .onClick(() => {
                this.mutableStyledString3.replaceStyle(this.spanStyle38)
                this.controller33.setStyledString(this.mutableStyledString3)
              })

            Button('0390')
              .onClick(() => {
                this.mutableStyledString3.replaceStyle(this.spanStyle39)
                this.controller33.setStyledString(this.mutableStyledString3)
              })

            Button('0400')
              .onClick(() => {
                this.mutableStyledString3.replaceStyle(this.spanStyle40)
                this.controller33.setStyledString(this.mutableStyledString3)
              })

            Button('0410')
              .onClick(() => {
                this.mutableStyledString3.replaceStyle(this.spanStyle41)
                this.controller33.setStyledString(this.mutableStyledString3)
              })
          }

          Row() {
            Button('0420')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString3.replaceStyle(this.spanStyle42)
                this.controller33.setStyledString(this.mutableStyledString3)
              })

            Button('0430')
              .width('40%')
              .onClick(() => {
                this.mutableStyledString3.replaceStyle(this.spanStyle43)
                this.controller33.setStyledString(this.mutableStyledString3)
              })
          }

          Text(undefined, { controller: this.controller44 }) {
            Span('Span测试')
          }
          .margin({ top: 10 })

          Text(undefined, { controller: this.controller45 }).margin({ top: 10 })
        }

      }
      .expandSafeArea([SafeAreaType.KEYBOARD])
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(BarState.On)
      .scrollBarColor(Color.Gray)
      .scrollBarWidth(10)
      .height('50%')
      .edgeEffect(EdgeEffect.None)
      .backgroundColor('#f9eff6')
      .padding({ bottom: 50 })
    }
    .width('100%')
  }
}