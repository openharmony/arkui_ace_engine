import font from '@ohos.font';
import { LengthMetrics, LengthUnit } from '@ohos.arkui.node'

class MyTextModifier implements AttributeModifier<TextAttribute> {
  trasition: NumericTextTransition | undefined | null = { flipDirection: FlipDirection.UP, enableBlur: false }

  applyNormalAttribute(instance: TextAttribute): void {
    instance
      .contentTransition(this.trasition)
  }
}

@Entry
@Component
struct struct_02_TextSample_02_textNumericTextTransition {
  @State testText: string = "Test";
  @State testAccessibilityText: string | undefined | null = 'MyTest.accessibilityText';
  @State testAccessibilityDescription: string | undefined | null = 'MyTest.accessibilityDescription';
  @State testAccessibilityLevel: string | undefined | null = 'MyTest.auto';
  @State backgroundColor1: ResourceColor | undefined = undefined;
  controller3: TextController = new TextController();
  clickGestureAttr: GestureStyle = new GestureStyle({
    onClick: () => {
      console.log('click GestureAttr');
    },
  })
  mutableStyledString3: MutableStyledString = new MutableStyledString("hello world", [
    {
      start: 0,
      length: 5,
      styledKey: StyledStringKey.GESTURE,
      styledValue: this.clickGestureAttr
    },
    {
      start: 6,
      length: 5,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Pink })
    }
  ]);

  async onPageShow() {
    this.controller3.setStyledString(this.mutableStyledString3)
  }

  // 自定义字体
  // async aboutToAppear() {
  //   getContext(this)
  //     .resourceManager
  //   font.registerFont({
  //     familyName: 'medium',
  //     familySrc: $rawfile('font/cartoon.ttf')
  //   })
  // }

  @State message: number = 17858867166
  @State message2: number = 88
  @State trasition: NumericTextTransition | undefined | null =
    new NumericTextTransition({ flipDirection: FlipDirection.UP, enableBlur: true })
  @State trasition1: NumericTextTransition =
    new NumericTextTransition({ flipDirection: FlipDirection.DOWN, enableBlur: true })
  @State trasition2: NumericTextTransition = { flipDirection: undefined, enableBlur: true }
  @State trasition3: NumericTextTransition = { enableBlur: true }
  @State trasition4: NumericTextTransition = {}
  @State trasition5: NumericTextTransition = { flipDirection: FlipDirection.UP, enableBlur: undefined }
  @State color1: Color = Color.Red
  @State fontsize1: string = "120px"
  @State textAlign1: TextAlign = TextAlign.Start
  @State lineHeight: number = 50
  @State ellipsisMode: EllipsisMode = EllipsisMode.CENTER
  @State fontWeight: Array<FontWeight> = [FontWeight.Normal, FontWeight.Lighter, FontWeight.Bolder]
  @State fontWeightindex: number = 0
  private decorationStyleInterface1: DecorationStyleInterface = {
    color: Color.Gray,
    type: TextDecorationType.Underline,
    style: TextDecorationStyle.WAVY
  }
  private decorationStyleInterface2: DecorationStyleInterface = {
    type: TextDecorationType.None,
    color: Color.Green,
    style: TextDecorationStyle.DOUBLE
  }
  private decorationStyleInterface3: DecorationStyleInterface = {
    type: TextDecorationType.LineThrough,
    style: TextDecorationStyle.DASHED,
    color: Color.Pink
  }
  @State decorationStyleInterface: DecorationStyleInterface = {
    type: TextDecorationType.Underline
  }
  @State fontfamily: string = ""
  @State copyoption: CopyOptions = CopyOptions.InApp
  @State fontArray: Array<Font> =
    [{ size: 30, style: FontStyle.Normal }, { size: 10, style: FontStyle.Italic },
      { size: 60, weight: FontWeight.Bold, style: FontStyle.Normal }]
  @State fontindex: number = 0
  @State fontStyle: FontStyle = FontStyle.Normal
  private textshadow1: ShadowOptions = {
    radius: 10,
    color: Color.Black,
    offsetX: 0,
    offsetY: 0
  }
  private textshadow2: ShadowOptions = {
    radius: 0,
    color: Color.Pink,
    offsetX: 100,
    offsetY: 100
  }
  @State textshadow: ShadowOptions = this.textshadow1
  @State fontFeatureIndex: number = 0;
  @State fontFeature: string[] =
    ["\"sups\" -1", "\"sups\" 1", "\"sinf\" on"];
  @State indent1: number = 20
  @State onlyBetweenLinesvalue: boolean = false
  @State modifierText: MyTextModifier = new MyTextModifier()
  @State baselineOffset: number = 20
  @State lineBreakStrategyIndex: number = 0;
  @State lineBreakStrategy: LineBreakStrategy[] =
    [LineBreakStrategy.HIGH_QUALITY, LineBreakStrategy.GREEDY, LineBreakStrategy.BALANCED];
  @State halfLeading: boolean = false;
  @State fontwenable: number = 120
  @State autospacing: boolean = false;
  @State linearGradientOptions1: LinearGradientOptions =
    {
      angle: 45,
      colors: [[Color.Red, 0.0], [Color.Blue, 0.3], [Color.Green, 0.5]]
    };
  @State linearGradientOptions2: LinearGradientOptions =
    {
      direction: GradientDirection.LeftTop,
      colors: [[Color.Red, 0.0], [Color.Blue, 0.3], [Color.Green, 0.5]],
      repeating: true,
    };
  @State radialGradientOptions: RadialGradientOptions =
    {
      center: [50, 50],
      radius: 20,
      colors: [[Color.Red, 0.0], [Color.Blue, 0.3], [Color.Green, 0.5]],
      repeating: true,
    };
  @State textOverflowIndex: number = 0;
  @State textOverflow: TextOverflow[] =
    [TextOverflow.None, TextOverflow.MARQUEE, TextOverflow.Ellipsis];
  @State wordBreakIndex: number = 0;
  @State wordBreakOptions: WordBreak[] =
    [WordBreak.NORMAL, WordBreak.BREAK_ALL, WordBreak.BREAK_WORD, WordBreak.HYPHENATION]
  @State clip1: boolean = true;
  @State start: number = 0;
  @State end: number = 1;
  @State caretColor: Color = Color.Blue
  @State padding1: number = 10
  @State enableDataDetector: boolean = true
  @State enableprevieew: boolean | undefined | null = true
  scrollerForList: Scroller = new Scroller();
  @State visi: Visibility = Visibility.Visible

  @Builder
  MyMenu() {
    Column() {
      Text("hhh")
    }
  }

  build() {
    Row() {
      Column() {
        Scroll() {
          Column() {
            Text("测试自适应字号翻牌" + "😅")
              .fontSize(8)
              .padding(this.padding1)
              .borderWidth(1)
              .shaderStyle(this.linearGradientOptions1)
            Text("" + this.message)
              .attributeModifier(this.modifierText)
              .fontSize(this.fontsize1)
              .borderWidth(1)
              .wordBreak(this.wordBreakOptions[this.wordBreakIndex])
              .width(110)
              .textOverflow({ overflow: this.textOverflow[this.textOverflowIndex] })
              // .maxLines(1)
              .textAlign(this.textAlign1)
              .decoration(this.decorationStyleInterface)
              .ellipsisMode(this.ellipsisMode)
              .fontColor(this.color1)
              .fontWeight(this.fontWeight[this.fontWeightindex])
              .fontFamily(this.fontfamily)
              .copyOption(this.copyoption)
              .font(this.fontArray[this.fontindex])
              .fontStyle(this.fontStyle)
              .textShadow(this.textshadow)
              .minFontSize(10)
              .maxFontSize(60)
              .textIndent(this.indent1)
              .baselineOffset(this.baselineOffset)
              .lineBreakStrategy(this.lineBreakStrategy[this.lineBreakStrategyIndex])
              .halfLeading(this.halfLeading)
              .fontWeight(this.fontwenable, { enableVariableFontWeight: true })
              .enableAutoSpacing(this.autospacing)
              .shaderStyle(this.linearGradientOptions1)
              .clip(this.clip1)
              .selection(this.start, this.end)
              .caretColor(this.caretColor)
              .padding(this.padding1)
              .fontFeature(this.fontFeature[this.fontFeatureIndex])
              .enableDataDetector(this.enableDataDetector)
              .dataDetectorConfig({
                types: [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL, TextDataDetectorType.EMAIL,
                  TextDataDetectorType.ADDRESS, TextDataDetectorType.DATE_TIME],
                color: $r('app.color.start_window_background'),
                decoration: {
                  type: TextDecorationType.Overline
                },
                enablePreviewMenu: this.enableprevieew
              })

            Text("测试截断数字")
              .fontSize(8)
              .shaderStyle(this.linearGradientOptions2)
            Text(this.message + "")
              .contentTransition(this.trasition)
              .fontSize(this.fontsize1)
              .borderWidth(1)
              .width(110)
              // .wordBreak(WordBreak.BREAK_ALL)
              .textOverflow({ overflow: this.textOverflow[this.textOverflowIndex] })
              .maxLines(1)
              .textAlign(this.textAlign1)
              .lineHeight(this.lineHeight)
              .decoration(this.decorationStyleInterface)
              .ellipsisMode(this.ellipsisMode)
              // .fontColor(this.color1)
              .fontWeight(this.fontWeight[this.fontWeightindex])
              .fontFamily(this.fontfamily)
              .copyOption(this.copyoption)
              .maxLines(1)
              .font(this.fontArray[this.fontindex])
              .fontStyle(this.fontStyle)
              .textShadow(this.textshadow)
              .fontFeature(this.fontFeature[this.fontFeatureIndex])
              .textIndent(this.indent1)
              .baselineOffset(this.baselineOffset)
              .lineBreakStrategy(this.lineBreakStrategy[this.lineBreakStrategyIndex])
              .halfLeading(this.halfLeading)
              .fontWeight(this.fontwenable, { enableVariableFontWeight: true })
              .enableAutoSpacing(this.autospacing)
              .lineSpacing(LengthMetrics.vp(30), { onlyBetweenLines: this.onlyBetweenLinesvalue })
              .shaderStyle(this.linearGradientOptions2)
              .wordBreak(this.wordBreakOptions[this.wordBreakIndex])
              .clip(this.clip1)
              .selection(this.start, this.end)
              .caretColor(this.caretColor)
              .padding(this.padding1)
              .align(Alignment.BottomEnd)
              .enableDataDetector(true)
              .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
            Text("测试属性切换88")
              .fontSize(8)
              .shaderStyle(this.radialGradientOptions)
            Row() {


              Text(this.message2 + "")
                .contentTransition(this.trasition)// .attributeModifier(this.modifierText)
                .fontSize(this.fontsize1)
                .borderWidth(1)
                .width(110)// .wordBreak(WordBreak.BREAK_ALL)
                .textOverflow({ overflow: TextOverflow.Ellipsis })// .maxLines(1)
                .textAlign(this.textAlign1)
                .lineHeight(this.lineHeight)
                .decoration(this.decorationStyleInterface)//删除ellipsisMode、fontColor可以测试relayout效果
                .ellipsisMode(this.ellipsisMode)
                // .fontColor(this.color1)
                .fontFamily(this.fontfamily)
                .fontWeight(this.fontWeight[this.fontWeightindex])
                .copyOption(this.copyoption)// .font(this.fontArray[this.fontindex])
                .fontStyle(this.fontStyle)// .textShadow(this.textshadow)
                .margin({ bottom: 20 })
                .fontFeature(this.fontFeature[this.fontFeatureIndex])
                .textIndent(this.indent1)
                .baselineOffset(this.baselineOffset)
                .lineBreakStrategy(this.lineBreakStrategy[this.lineBreakStrategyIndex])
                .halfLeading(this.halfLeading)
                .fontWeight(this.fontwenable, { enableVariableFontWeight: true })
                .enableAutoSpacing(this.autospacing)
                .shaderStyle(this.radialGradientOptions)
                .wordBreak(this.wordBreakOptions[this.wordBreakIndex])
                .clip(this.clip1)
                .selection(this.start, this.end)
                .caretColor(this.caretColor)
                .padding(this.padding1)
                .backgroundColor(Color.Orange)
                .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)

              Text(this.message2 + "")
                .contentTransition(this.trasition)
                .attributeModifier(this.modifierText)
                .fontSize(this.fontsize1)
                .borderWidth(1)
                .width(110)
                .wordBreak(WordBreak.BREAK_ALL)
                .textOverflow({ overflow: TextOverflow.Ellipsis })// .maxLines(1)
                .textAlign(this.textAlign1)
                .lineHeight(this.lineHeight)
                .decoration(this.decorationStyleInterface)//删除ellipsisMode、fontColor可以测试relayout效果
                .ellipsisMode(this.ellipsisMode)
                .fontColor(this.color1)
                .fontFamily(this.fontfamily)
                .fontWeight(this.fontWeight[this.fontWeightindex])
                .copyOption(this.copyoption)
                .font(this.fontArray[this.fontindex])
                .fontStyle(this.fontStyle)
                .textShadow(this.textshadow)
                .margin({ bottom: 20 })
                .fontFeature(this.fontFeature[this.fontFeatureIndex])
                .textIndent(this.indent1)
                .baselineOffset(this.baselineOffset)
                .lineBreakStrategy(this.lineBreakStrategy[this.lineBreakStrategyIndex])
                .halfLeading(this.halfLeading)
                .fontWeight(this.fontwenable, { enableVariableFontWeight: true })
                .enableAutoSpacing(this.autospacing)
                .shaderStyle(this.radialGradientOptions)
                .wordBreak(this.wordBreakOptions[this.wordBreakIndex])
                .clip(this.clip1)
                .selection(this.start, this.end)
                .caretColor(this.caretColor)
                .padding(this.padding1)
                .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
            }

            Text("测试span不生效")
              .fontSize(8)
            Text() {
              Span(this.message2 + "")
            }
            .contentTransition(this.trasition) // .attributeModifier(this.modifierText)
            .fontSize(this.fontsize1)
            .borderWidth(1)
            // .wordBreak(WordBreak.BREAK_ALL)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            // .maxLines(1)
            .textAlign(this.textAlign1)
            .lineHeight(this.lineHeight)
            .decoration(this.decorationStyleInterface) //删除ellipsisMode、fontColor可以测试relayout效果
            .ellipsisMode(this.ellipsisMode)
            .fontColor(this.color1)
            .fontFamily(this.fontfamily)
            .fontWeight(this.fontWeight[this.fontWeightindex])
            .copyOption(this.copyoption)
            .font(this.fontArray[this.fontindex])
            .fontStyle(this.fontStyle)
            .textShadow(this.textshadow)
            .margin({ bottom: 20 })
            .fontFeature(this.fontFeature[this.fontFeatureIndex])
            .textIndent(this.indent1)
            .baselineOffset(this.baselineOffset)
            .lineBreakStrategy(this.lineBreakStrategy[this.lineBreakStrategyIndex])
            .halfLeading(this.halfLeading)
            .fontWeight(this.fontwenable, { enableVariableFontWeight: true })
            .enableAutoSpacing(this.autospacing)
            .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)

            .lineSpacing(LengthMetrics.vp(30), { onlyBetweenLines: this.onlyBetweenLinesvalue })


            Text(this.message + "hh")
              .contentTransition(this.trasition1)
              .fontSize(this.fontsize1)
              .fontColor(this.color1)
              .borderWidth(1)

            Text(this.message + "哈")
              .contentTransition(this.trasition3)
              .fontSize("120px")
              .borderWidth(1)

          }
        }
        .height(300)

        Scroll() {
          Column() {
            Button('switch decorationStyle1 ').onClick(() => {
              this.decorationStyleInterface =
                this.decorationStyleInterface1
              this.message2++
            })
            Button('switch decorationStyle2 ').onClick(() => {
              this.decorationStyleInterface =
                this.decorationStyleInterface2
              this.message2++
            })
            Button('switch decorationStyle3 ').onClick(() => {
              this.decorationStyleInterface =
                this.decorationStyleInterface3
              this.message2++
            })
            Button("change textAlign")
              .onClick(() => {
                this.textAlign1 = this.textAlign1 == TextAlign.Start ? TextAlign.End : TextAlign.Start
                this.message2++
              })
            Button("change number++")
              .onClick(() => {
                this.message++
                this.message2++
              })

            Button("change number--")
              .onClick(() => {
                this.message--
                this.message2--
              })

            Button("change number 100000")
              .onClick(() => {
                this.message += 100000
                this.message2 += 100000
              })
            Button("change undefined")
              .onClick(() => {
                // this.message2++
                this.trasition = null
                this.modifierText.trasition = null
              })

            Button("change trasition1")
              .onClick(() => {
                // this.message++
                this.trasition = this.trasition1
                this.modifierText.trasition = this.trasition1
              })

            Button("change trasition2")
              .onClick(() => {
                // this.message++
                this.trasition = this.trasition2
                this.modifierText.trasition = this.trasition2
              })
            Button("change trasition3")
              .onClick(() => {
                // this.message++
                this.trasition = this.trasition3
                this.modifierText.trasition = this.trasition3
              })
            Button("change trasition4")
              .onClick(() => {
                // this.message++
                this.trasition = this.trasition4
                this.modifierText.trasition = this.trasition4
              })

            Button("change trasition5")
              .onClick(() => {
                // this.message++
                this.trasition = this.trasition5
                // this.modifierText.trasition = this.trasition5
              })

            Button("change fontWeight")
              .onClick(() => {
                this.fontWeightindex++
                if (this.fontWeightindex >= this.fontWeight.length) {
                  this.fontWeightindex = 0;
                }
              })
            Button("change color")
              .onClick(() => {
                this.color1 = this.color1 == Color.Red ? Color.Black : Color.Red
              })
            Button("change color animateTo")
              .onClick(() => {
                animateTo({ duration: 2000 }, () => {
                  this.color1 = this.color1 == Color.Red ? Color.Black : Color.Red
                })
              })
            Button("change fontsize")
              .onClick(() => {
                // this.color1 = this.color1 == Color.Red ? Color.Black : Color.Red
                this.fontsize1 = this.fontsize1 == "120px" ? "80px" : "120px"
                this.message2++
              })
            Button("change fontsize animateTo")
              .onClick(() => {
                animateTo({ duration: 2000 }, () => {
                  // this.color1 = this.color1 == Color.Red ? Color.Black : Color.Red
                  this.fontsize1 = this.fontsize1 == "120px" ? "80px" : "120px"
                  // this.message++
                })
              })
            Button("change ellipsisMode")
              .onClick(() => {
                this.ellipsisMode = this.ellipsisMode == EllipsisMode.CENTER ? EllipsisMode.START : EllipsisMode.CENTER
              })
            Button("change lineHeight")
              .onClick(() => {
                this.lineHeight = this.lineHeight == 50 ? 100 : 50
                this.message2++
              })
            Button("change fontfamiy")
              .onClick(() => {
                this.fontfamily = this.fontfamily == "" ? "medium" : ""
              })

            Button("change copyOption")
              .onClick(() => {
                this.copyoption = this.copyoption == CopyOptions.None ? CopyOptions.InApp : CopyOptions.None
              })

            Button("change font")
              .onClick(() => {
                this.fontindex++
                if (this.fontindex >= this.fontArray.length) {
                  this.fontindex = 0;
                }
              })

            Button("change fontStyle")
              .onClick(() => {
                this.fontStyle = this.fontStyle == FontStyle.Normal ? FontStyle.Italic : FontStyle.Normal
              })

            Button('switch animation textshadow1').onClick(() => {
              animateTo({ duration: 2000 }, () => {
                this.textshadow = this.textshadow1
              })
            })

            Button('switch animation textshadow2').onClick(() => {
              animateTo({ duration: 2000 }, () => {
                this.textshadow = this.textshadow2
              })
            })

            Button('switch textshadow1 static').onClick(() => {
              this.textshadow = this.textshadow1
            })
            Button('switch textshadow2 static').onClick(() => {
              this.textshadow = this.textshadow2
            })

            Button('当前fontFeature模式：' + this.fontFeature[this.fontFeatureIndex])
              .onClick(() => {
                this.fontFeatureIndex++;
                if (this.fontFeatureIndex > (this.fontFeature.length - 1)) {
                  this.fontFeatureIndex = 0;
                }
              })
            Button("change textIndent")
              .onClick(() => {
                this.indent1 = this.indent1 == 20 ? 0 : 20
              })

            Button("change onlyBetweenLines")
              .onClick(() => {
                this.onlyBetweenLinesvalue = !this.onlyBetweenLinesvalue
              })

            Button("change baselineOffset")
              .onClick(() => {
                this.baselineOffset = this.baselineOffset == 20 ? 0 : 20
              })
            Button('当前lineBreakStrategy模式：' + this.lineBreakStrategy[this.lineBreakStrategyIndex])
              .onClick(() => {
                this.lineBreakStrategyIndex++;
                if (this.lineBreakStrategyIndex > (this.lineBreakStrategy.length - 1)) {
                  this.lineBreakStrategyIndex = 0;
                }
              })

            Button("change halfLeading")
              .onClick(() => {
                this.halfLeading = !this.halfLeading
                this.message2++
              })

            Button("change enableVariableFontWeight")
              .onClick(() => {
                this.fontwenable += 20
              })

            Button("change enableAutoSpacing")
              .onClick(() => {
                this.autospacing = !this.autospacing
              })

            Button('当前textoverflow模式：' + this.textOverflowIndex)
              .onClick(() => {
                this.textOverflowIndex++;
                if (this.textOverflowIndex > (this.textOverflow.length - 1)) {
                  this.textOverflowIndex = 0;
                }
              })

            Button('当前wordbreak模式：' + this.wordBreakIndex)
              .onClick(() => {
                this.wordBreakIndex++;
                if (this.wordBreakIndex > (this.wordBreakOptions.length - 1)) {
                  this.wordBreakIndex = 0;
                }
              })

            Button("change clip")
              .onClick(() => {
                this.clip1 = !this.clip1
              })

            Button("change select")
              .onClick(() => {
                this.start = this.start == -1 ? 1 : -1;
                this.end = this.end == -1 ? 2 : -1
              })

            Button("change color")
              .onClick(() => {
                this.caretColor = this.caretColor == Color.Blue ? Color.Orange : Color.Blue
              })

            Button("change padding")
              .onClick(() => {
                this.padding1 == 10 ? 1 : 10
              })

            Button("change enableprevieew")
              .onClick(() => {
                this.enableprevieew == !this.enableprevieew
              })

          }
        }
        .height(200)

        TextInput()

        Text('' + this.message2)
          .copyOption(CopyOptions.InApp)
          .contentTransition(this.trasition)
          .width('100%')
          .height(100)
          .fontSize(30)
          .backgroundColor(0x00FFFF)
          .visibility(this.visi)
          .textAlign(TextAlign.Center)
          // .overlay(this.MyMenu())
          .baselineOffset(20)
        Button("change Visibility")
          .onClick(() => {
            this.visi = this.visi == Visibility.Visible ? Visibility.None : Visibility.Visible
          })

        Button("change visi")
          .onClick(() => {
            this.visi = this.visi == Visibility.Visible ? Visibility.Hidden : Visibility.Visible
          })

        Text("change 无崩溃")
          .margin(10)
          .onClick(() => {
            this.message2++
          })

      }
      .width('100%')
    }
    .height('100%')
  }
}