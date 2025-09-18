import { LengthMetrics, LengthUnit } from '@kit.ArkUI'

let isBool: boolean = false

@Extend(Text)
function style() {
  .fontSize(12)
  .border({ width: 1 })
  .width('100%')
}

@Extend(Text)
function style1() {
  .border({ width: 1 })
  .width('100%')
}

@Entry
@Component
struct struct_02_TextSample_04_lineSpacingOnlyBetweenLines {
  @State isLineHeight: (number | null)[] = [null, 20]
  @State isLineHeightIndex: number = 0
  @State text: ResourceStr[] =
    [' \n123456789\nabcd\n ', '我是换行\n123456789\nabcd\n ', ' \n123456789\nabcd\n我是换行', $r('app.string.Long')]
  @State textIndex: number = 0
  @State isOnlyBetweenLines: (boolean | null | undefined)[] = [true, false, null, undefined]
  @State isOnlyBetweenLinesIndex: number = 0
  @State isLineSpacing: LengthMetrics[] = [LengthMetrics.px(20), LengthMetrics.px(50)]
  @State isLineSpacingIndex: number = 0
  textStyleAttrs: TextStyle =
    new TextStyle({ fontWeight: FontWeight.Bolder, fontSize: LengthMetrics.vp(24), fontStyle: FontStyle.Italic });
  titleParagraphStyleAttr: ParagraphStyle =
    new ParagraphStyle({ paragraphSpacing: LengthMetrics.px(50), textIndent: LengthMetrics.vp(15) });
  titleParagraphStyleAttr1: ParagraphStyle = new ParagraphStyle({ textIndent: LengthMetrics.vp(15) });
  @State isBool: boolean = false
  mutableStyledString: MutableStyledString =
    new MutableStyledString('属性字符串TextStyle测试\n属性字符串测试\n属性字符串TextStyle测试', [
      {
        start: 0,
        length: 3,
        styledKey: StyledStringKey.FONT,
        styledValue: this.textStyleAttrs
      },
      {
        start: 5,
        length: 9,
        styledKey: StyledStringKey.FONT,
        styledValue: new TextStyle({ fontColor: Color.Orange, fontSize: LengthMetrics.vp(12) })
      },
      {
        start: 23,
        length: 3,
        styledKey: StyledStringKey.FONT,
        styledValue: this.textStyleAttrs
      },
      {
        start: 28,
        length: 2,
        styledKey: StyledStringKey.FONT,
        styledValue: new TextStyle({ fontColor: Color.Orange, fontSize: LengthMetrics.vp(12) })
      },
      {
        start: 0,
        length: 0,
        styledKey: StyledStringKey.PARAGRAPH_STYLE,
        styledValue: this.titleParagraphStyleAttr
      },
    ]);
  mutableStyledString1: MutableStyledString =
    new MutableStyledString('属性字符串TextShadowStyle测试\n属性字符串测试\n属性字符串TextShadowStyle测试', [
      {
        start: 0,
        length: 5,
        styledKey: StyledStringKey.TEXT_SHADOW,
        styledValue: new TextShadowStyle({
          radius: 5,
          type: ShadowType.COLOR,
          color: Color.Red,
          offsetX: 10,
          offsetY: 10
        })
      },
      {
        start: 32,
        length: 5,
        styledKey: StyledStringKey.TEXT_SHADOW,
        styledValue: new TextShadowStyle({
          radius: 5,
          type: ShadowType.COLOR,
          color: Color.Red,
          offsetX: 10,
          offsetY: 10
        })
      },
      {
        start: 0,
        length: 0,
        styledKey: StyledStringKey.PARAGRAPH_STYLE,
        styledValue: this.titleParagraphStyleAttr
      },
    ]);
  mutableStyledString2: MutableStyledString =
    new MutableStyledString('属性字符串DecorationStyle测试\n属性字符串测试\n属性字符串DecorationStyle测试', [
      {
        start: 0,
        length: 5,
        styledKey: StyledStringKey.DECORATION,
        styledValue: new DecorationStyle({ type: TextDecorationType.Overline, color: Color.Red })
      },
      {
        start: 32,
        length: 5,
        styledKey: StyledStringKey.DECORATION,
        styledValue: new DecorationStyle({ type: TextDecorationType.Underline, color: Color.Red })
      },
      {
        start: 0,
        length: 0,
        styledKey: StyledStringKey.PARAGRAPH_STYLE,
        styledValue: this.titleParagraphStyleAttr
      },
    ]);
  mutableStyledString3: MutableStyledString =
    new MutableStyledString('属性字符串BaselineOffsetStyle测试\n属性字符串测试\n属性字符串BaselineOffsetStyle测试', [
      {
        start: 0,
        length: 5,
        styledKey: StyledStringKey.BASELINE_OFFSET,
        styledValue: new BaselineOffsetStyle(LengthMetrics.px(10))
      },
      {
        start: 32,
        length: 5,
        styledKey: StyledStringKey.BASELINE_OFFSET,
        styledValue: new BaselineOffsetStyle(LengthMetrics.px(10))
      },
      {
        start: 0,
        length: 0,
        styledKey: StyledStringKey.PARAGRAPH_STYLE,
        styledValue: this.titleParagraphStyleAttr
      },
    ]);
  mutableStyledString4: MutableStyledString =
    new MutableStyledString('属性字符串LineHeightStyle测试\n属性字符串测试\n属性字符串LineHeightStyle测试', [
      {
        start: 0,
        length: 22,
        styledKey: StyledStringKey.LINE_HEIGHT,
        styledValue: new LineHeightStyle(LengthMetrics.vp(50))
      },
      {
        start: 24,
        length: 7,
        styledKey: StyledStringKey.LINE_HEIGHT,
        styledValue: new LineHeightStyle(LengthMetrics.vp(50))
      },
      {
        start: 0,
        length: 0,
        styledKey: StyledStringKey.PARAGRAPH_STYLE,
        styledValue: this.titleParagraphStyleAttr
      },
    ]);
  scroller: Scroller = new Scroller()
  textController: TextController = new TextController()
  textController1: TextController = new TextController()
  textController2: TextController = new TextController()
  textController3: TextController = new TextController()
  textController4: TextController = new TextController()

  async onPageShow() {
    this.textController.setStyledString(this.mutableStyledString)
    this.textController1.setStyledString(this.mutableStyledString1)
    this.textController2.setStyledString(this.mutableStyledString2)
    this.textController3.setStyledString(this.mutableStyledString3)
    this.textController4.setStyledString(this.mutableStyledString4)
  }

  build() {
    Column() {
      Row() {
        Button('首尾空行')
          .onClick(() => {
            this.textIndex = 0
          })
        Button('尾部空行')
          .onClick(() => {
            this.textIndex = 1
          })
        Button('顶部空行')
          .onClick(() => {
            this.textIndex = 2
          })
        Button('超长文本自动换行')
          .onClick(() => {
            this.textIndex = 3
          })
      }

      Row() {
        Text('改变首尾行')
        Button('true')
          .onClick(() => {
            this.isOnlyBetweenLinesIndex = 0
          })
        Button('false')
          .onClick(() => {
            this.isOnlyBetweenLinesIndex = 1
          })
        Button('null')
          .onClick(() => {
            this.isOnlyBetweenLinesIndex = 2
          })
        Button('undefined')
          .onClick(() => {
            this.isOnlyBetweenLinesIndex = 3
          })
      }

      Row() {
        Button('不设置行高')
          .onClick(() => {
            this.isLineHeightIndex = 0
          })
        Button('文本行高20fp')
          .onClick(() => {
            this.isLineHeightIndex = 1
          })
      }.margin({ top: 10 })

      Scroll(this.scroller) {
        Column() {
          // 设置文本行间距
          Text('新接口').margin({ top: 10 }).backgroundColor('#FFE7BEEE')
          Text(this.text[this.textIndex])
            .lineSpacing(LengthMetrics.px(20),
              { onlyBetweenLines: this.isOnlyBetweenLines[this.isOnlyBetweenLinesIndex] })
            .style()
            .lineHeight(this.isLineHeight[this.isLineHeightIndex])

          Text('老接口').margin({ top: 10 }).backgroundColor('#FFE7BEEE')
          Text(this.text[this.textIndex])// .lineSpacing(LengthMetrics.px(20))
            .lineSpacing(LengthMetrics.px(20))
            .style()
            .lineHeight(this.isLineHeight[this.isLineHeightIndex])

          Text('新接口').margin({ top: 10 }).backgroundColor('#FFE7BEEE')
          Text(undefined, { controller: this.textController })
            .lineSpacing(LengthMetrics.px(30),
              { onlyBetweenLines: this.isOnlyBetweenLines[this.isOnlyBetweenLinesIndex] })
            .style1()
            .lineHeight(this.isLineHeight[this.isLineHeightIndex])

          Text(undefined, { controller: this.textController1 })
            .lineSpacing(LengthMetrics.px(30),
              { onlyBetweenLines: this.isOnlyBetweenLines[this.isOnlyBetweenLinesIndex] })
            .style1()
            .margin({ top: 10 })

          Text(undefined, { controller: this.textController2 })
            .lineSpacing(LengthMetrics.px(30),
              { onlyBetweenLines: this.isOnlyBetweenLines[this.isOnlyBetweenLinesIndex] })
            .style1()
            .margin({ top: 10 })

          Text(undefined, { controller: this.textController3 })
            .lineSpacing(LengthMetrics.px(30),
              { onlyBetweenLines: this.isOnlyBetweenLines[this.isOnlyBetweenLinesIndex] })
            .style1()
            .margin({ top: 10 })

          Text(undefined, { controller: this.textController4 })
            .lineSpacing(LengthMetrics.px(30),
              { onlyBetweenLines: this.isOnlyBetweenLines[this.isOnlyBetweenLinesIndex] })
            .style1()
            .margin({ top: 10 })

          Text('设置Span,新接口').margin({ top: 10 }).backgroundColor('#FFE7BEEE')
          Text() {
            ImageSpan($r('app.media.app_icon'))
              .width('80px')
              .baselineOffset(new LengthMetrics(50, LengthUnit.VP))
            Span('我是Span1，lineHeight 30\n')
              .fontSize(12)
              .lineHeight(30)
            Span('span font 12 Bolder Italic\n')
              .font({
                size: 12,
                weight: FontWeight.Bolder,
                style: FontStyle.Italic,
                family: 'HarmonyOS Sans'
              })
            Span('I am Overline-DASHED-span')
              .decoration({ type: TextDecorationType.Overline, color: Color.Red, style: TextDecorationStyle.DASHED })
              .fontSize(12)
              .lineHeight(30)
          }
          .lineSpacing(LengthMetrics.px(30),
            { onlyBetweenLines: this.isOnlyBetweenLines[this.isOnlyBetweenLinesIndex] })
          .style1()

          Text('设置Span,老接口').margin({ top: 10 }).backgroundColor('#FFE7BEEE')
          Text() {
            ImageSpan($r('app.media.app_icon'))
               .width('80px')
               .baselineOffset(new LengthMetrics(50, LengthUnit.VP))
            Span('我是Span1，lineHeight 30\n')
              .fontSize(12)
              .lineHeight(30)
            Span('span font 12 Bolder Italic\n')
              .font({
                size: 12,
                weight: FontWeight.Bolder,
                style: FontStyle.Italic,
                family: 'HarmonyOS Sans'
              })
            Span('I am Overline-DASHED-span')
              .decoration({ type: TextDecorationType.Overline, color: Color.Red, style: TextDecorationStyle.DASHED })
              .fontSize(12)
              .lineHeight(30)
          }
          .lineSpacing(LengthMetrics.px(30))
          .style1()
          .margin({bottom: 100})
        }
      }
    }
  }
}