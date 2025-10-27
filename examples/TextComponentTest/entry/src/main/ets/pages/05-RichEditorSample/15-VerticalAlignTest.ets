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

import { LengthMetrics, LengthUnit } from '@ohos.arkui.node'
import { image } from '@kit.ImageKit'
import { drawing } from '@kit.ArkGraphics2D'

class MyCustomSpan extends CustomSpan {
  constructor(word: string, width: number, height: number) {
    super();
    this.word = word;
    this.width = width;
    this.height = height;
  }

  onMeasure(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics {
    return { width: this.width, height: this.height };
  }

  onDraw(context: DrawContext, options: CustomSpanDrawInfo) {
    let canvas = context.canvas;

    const brush = new drawing.Brush();
    brush.setColor({
      alpha: 255,
      red: 0,
      green: 74,
      blue: 175
    });
    const font = new drawing.Font();
    font.setSize(25);
    const textBlob = drawing.TextBlob.makeFromString(this.word, font, drawing.TextEncoding.TEXT_ENCODING_UTF8);
    canvas.attachBrush(brush);
    canvas.drawRect({
      left: options.x + 10,
      right: options.x + vp2px(this.width) - 10,
      top: options.lineTop + 10,
      bottom: options.lineBottom - 10
    });

    brush.setColor({
      alpha: 255,
      red: 23,
      green: 169,
      blue: 141
    });
    canvas.attachBrush(brush);
    canvas.drawTextBlob(textBlob, options.x + 20, options.lineBottom - 15);
    canvas.detachBrush();
  }

  setWord(word: string) {
    this.word = word;
  }

  width: number = 160;
  word: string = 'drawing';
  height: number = 10;
}

@Entry
@Component
struct VerticalAlign {
  private my_builder: CustomBuilder = undefined

  @Builder
  MyBuilder() {
    Text('hello').padding('20').borderWidth(1).width('20%')
  }

  @State selection: string = '';
  @State content: string = '';
  @State range: string = '';
  @State replaceString: string = '';
  @State rangeBefore: string = '';
  @State rangeAfter: string = '';
  @State text5: string = 'onwillchange'
  @State text6: string = 'ondidchange'
  @State start: number = -1;
  @State end: number = -1;
  @State message: string = '[-1, -1]'
  @State w: number = 400
  @State H: number = 500
  @State radius: number = 0
  @State clipType: boolean = false
  private leftMargin: Dimension = 0;
  @State S: number = 30
  @State DS: number = 1
  @State emojisOption: string[] = ['😀', '😃', '😄', '😁', '😆', '😀'];
  @State randomEmoji: string = ''
  @State log: string = ''
  @State onDoubleClick: string = ''
  @State sss: string = '!!!'
  @State text1: string = ''
  @State onSelectionChangeValue: string = ''
  @State private enableDataDetector: boolean = false
  @State copyOption: CopyOptions[] =
    [CopyOptions.None, CopyOptions.InApp, CopyOptions.LocalDevice, CopyOptions.CROSS_DEVICE]
  @State copyOptionStr: string[] = ['None', 'InApp', 'LocalDevice', 'CROSS_DEVICE']
  @State index: number = 2
  @State textVerticalAlign: TextVerticalAlign[] =
    [TextVerticalAlign.BASELINE, TextVerticalAlign.BOTTOM, TextVerticalAlign.CENTER, TextVerticalAlign.TOP]
  @State textVerticalAlignStr: string[] = ['BASELINE', 'BOTTOM', 'CENTER', 'TOP']
  @State index1: number = 2
  @State imageSpanAlignment: ImageSpanAlignment[] =
    [ImageSpanAlignment.BASELINE, ImageSpanAlignment.BOTTOM, ImageSpanAlignment.CENTER, ImageSpanAlignment.TOP,
      ImageSpanAlignment.FOLLOW_PARAGRAPH]
  @State imageSpanAlignmentStr: string[] = ['BASELINE', 'BOTTOM', 'CENTER', 'TOP', 'FOLLOW_PARAGRAPH']
  @State index2: number = 2
  @State fontStyleText: string = '';
  fontColor: ResourceColor = Color.Red;
  fontFamily: string = 'Arial';
  fontSize: LengthMetrics = LengthMetrics.fp(16);
  fontWeight: number = FontWeight.Normal;
  fontStyle: FontStyle = FontStyle.Normal;
  fontStyleAttr: TextStyle = new TextStyle({
    fontColor: this.fontColor,
    fontFamily: this.fontFamily,
    fontSize: this.fontSize,
    fontWeight: this.fontWeight,
    fontStyle: this.fontStyle
  })

  private refreshFontStyle() {
    this.fontStyleAttr = new TextStyle({
      fontColor: this.fontColor,
      fontFamily: this.fontFamily,
      fontSize: this.fontSize,
      fontWeight: this.fontWeight,
      fontStyle: this.fontStyle
    })
    this.fontStyleText = 'Font Style: { fontColor: ' + this.fontColor + ' fontFamily: ' + this.fontFamily
      + ' fontSize: ' + this.fontSize.value + ' fontWeight: ' + this.fontWeight + ' fontStyle: ' + this.fontStyle +
      ' }';
  }

  @State decorationStyleText: string = '';
  decorationType: TextDecorationType = TextDecorationType.None;
  decorationColor: ResourceColor = Color.Orange;
  decorationStyle: TextDecorationStyle = TextDecorationStyle.SOLID;
  decorationThicknessScale: number = 5
  decorationStyleAttr: DecorationStyle = new DecorationStyle({
    type: this.decorationType,
    color: this.decorationColor,
    style: this.decorationStyle,
    thicknessScale: this.decorationThicknessScale
  })

  private refreshDecorationStyle() {
    this.decorationStyleAttr = new DecorationStyle({
      type: this.decorationType,
      color: this.decorationColor,
      style: this.decorationStyle,
      thicknessScale: this.decorationThicknessScale
    })
    this.decorationStyleText = 'Decoration Style: { type:' + this.decorationType + ' color: ' + this.decorationColor
      + ' style: ' + this.decorationStyle + ' }';
  }

  imagePixelMap: image.PixelMap | undefined = undefined;

  private async getPixmapFromMedia(resource: Resource) {
    let unit8Array = await getContext(this)?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    })
    let imageSource = image.createImageSource(unit8Array.buffer.slice(0, unit8Array.buffer.byteLength))
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    })
    await imageSource.release()
    return createPixelMap
  }

  contentChangedListener: StyledStringChangedListener = {
    onWillChange: (value: StyledStringChangeValue) => {
      console.log('styledString test onWillChange: ' + JSON.stringify(value));
      console.log('styledString test onWillChange range: [ ' + value.range.start + ' , ' + value.range.end + ' ]');
      console.log('styledString test onWillChange: replacementString: ' + value.replacementString.getString());
      return true;
    },
    onDidChange: (rangeBefore, rangeAfter) => {
      console.log('styledString test onDidChange rangeBefore start: ' + rangeBefore.start + ' end: ' + rangeBefore.end);
      console.log('styledString test onDidChange rangeAfter start: ' + rangeAfter.start + ' end: ' + rangeAfter.end);
    }
  }
  controller: RichEditorStyledStringController = new RichEditorStyledStringController();
  options: RichEditorStyledStringOptions = { controller: this.controller };
  styledString: MutableStyledString = new MutableStyledString('');
  mutableStyledString1: MutableStyledString = new MutableStyledString('初始属性字符串');
  mutableStyledString2: MutableStyledString = new MutableStyledString('插入内容');
  mutableStyledString3: MutableStyledString = new MutableStyledString('其他样式内容', [{
    start: 0,
    length: 6,
    styledKey: StyledStringKey.TEXT_SHADOW,
    styledValue: new TextShadowStyle({
      radius: 5,
      type: ShadowType.COLOR,
      color: Color.Yellow,
      offsetX: 10,
      offsetY: -10
    })
  }, {
    start: 0,
    length: 6,
    styledKey: StyledStringKey.BASELINE_OFFSET,
    styledValue: new BaselineOffsetStyle(LengthMetrics.px(20))
  }, {
    start: 0,
    length: 6,
    styledKey: StyledStringKey.LETTER_SPACING,
    styledValue: new LetterSpacingStyle(new LengthMetrics(10, LengthUnit.VP))
  }, {
    start: 0,
    length: 6,
    styledKey: StyledStringKey.BASELINE_OFFSET,
    styledValue: new BaselineOffsetStyle(LengthMetrics.fp(10))
  }, {
    start: 0,
    length: 6,
    styledKey: StyledStringKey.PARAGRAPH_STYLE,
    styledValue: new ParagraphStyle({ textVerticalAlign: TextVerticalAlign.CENTER })
  }]);

  async aboutToAppear() {
    this.refreshFontStyle();
    this.refreshDecorationStyle();
    this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.icon'));
  }

  scroller1: Scroller = new Scroller()
  scroller2: Scroller = new Scroller()
  scroller3: Scroller = new Scroller()
  @State enablePreviewText: boolean = true
  controller1: RichEditorController = new RichEditorController();

  build() {
    Scroll() {
      Column() {
        Scroll(this.scroller1) {
          Column() {
            Text(this.fontStyleText)
              .fontSize(16)
              .borderWidth(1)
              .borderColor(Color.Red)
              .height('20%')
              .width('100%')
            Row() {
              Button('Red').onClick(() => {
                this.fontColor = Color.Red;
                this.refreshFontStyle();
              })
              Button('Yellow').onClick(() => {
                this.fontColor = Color.Yellow;
                this.refreshFontStyle();
              })
              Button('Blue').onClick(() => {
                this.fontColor = Color.Blue;
                this.refreshFontStyle();
              })
            }

            Row() {
              Button('HarmonyOS Sans').onClick(() => {
                this.fontFamily = 'HarmonyOS Sans';
                this.refreshFontStyle();
              })
              Button('Arial').onClick(() => {
                this.fontFamily = 'Arial';
                this.refreshFontStyle();
              })
            }

            Row() {
              Button('Size:16').onClick(() => {
                this.fontSize = LengthMetrics.fp(16);
                this.refreshFontStyle();
              })
              Button('Size:24').onClick(() => {
                this.fontSize = LengthMetrics.fp(24);
                this.refreshFontStyle();
              })
              Button('Size:32').onClick(() => {
                this.fontSize = LengthMetrics.fp(32);
                this.refreshFontStyle();
              })
            }

            Row() {
              Button('Normal').onClick(() => {
                this.fontWeight = FontWeight.Normal;
                this.refreshFontStyle();
              })
              Button('Bold').onClick(() => {
                this.fontWeight = FontWeight.Bold;
                this.refreshFontStyle();
              })
              Button('Lighter').onClick(() => {
                this.fontWeight = FontWeight.Lighter;
                this.refreshFontStyle();
              })
            }

            Row() {
              Button('Normal').onClick(() => {
                this.fontStyle = FontStyle.Normal;
                this.refreshFontStyle();
              })
              Button('Italic').onClick(() => {
                this.fontStyle = FontStyle.Italic;
                this.refreshFontStyle();
              })
            }

            Text(this.decorationStyleText)
              .fontSize(16)
              .borderWidth(1)
              .borderColor(Color.Red)
              .height('15%')
              .width('100%')
            Row() {
              Button('Underline').onClick(() => {
                this.decorationType = TextDecorationType.Underline;
                this.refreshDecorationStyle();
              })
              Button('LineThrough').onClick(() => {
                this.decorationType = TextDecorationType.LineThrough;
                this.refreshDecorationStyle();
              })
              Button('Overline').onClick(() => {
                this.decorationType = TextDecorationType.Overline;
                this.refreshDecorationStyle();
              })
              Button('None').onClick(() => {
                this.decorationType = TextDecorationType.None;
                this.refreshDecorationStyle();
              })
            }

            Row() {
              Button('Red').onClick(() => {
                this.decorationColor = Color.Red;
                this.refreshDecorationStyle();
              })
              Button('Yellow').onClick(() => {
                this.decorationColor = Color.Yellow;
                this.refreshDecorationStyle();
              })
              Button('Blue').onClick(() => {
                this.decorationColor = Color.Blue;
                this.refreshDecorationStyle();
              })
            }

            Row() {
              Button('SOLID').onClick(() => {
                this.decorationStyle = TextDecorationStyle.SOLID;
                this.refreshDecorationStyle();
              })
              Button('DOTTED').onClick(() => {
                this.decorationStyle = TextDecorationStyle.DOTTED;
                this.refreshDecorationStyle();
              })
              Button('WAVY').onClick(() => {
                this.decorationStyle = TextDecorationStyle.WAVY;
                this.refreshDecorationStyle();
              })
              Button('切换AI').onClick(() => {
                this.enableDataDetector = !this.enableDataDetector
              })
            }
          }
        }
        .width('100%')
        .height('40%')
        .borderWidth(3)
        .borderColor(Color.Orange)
        .scrollable(ScrollDirection.Vertical)
        .scrollBarColor(Color.Gray)
        .scrollBarWidth(5)

        Scroll(this.scroller2) {
          Column() {
            Text('预上屏功能:').fontSize(10).width('100%')
            Flex({ direction: FlexDirection.Row, justifyContent: FlexAlign.SpaceAround }) {
              Button('开启/关闭预上屏' + this.enablePreviewText).fontSize(10).height(25)
                .onClick(() => {
                  this.enablePreviewText = !this.enablePreviewText
                })
            }.backgroundColor('#F0F0F0').padding(10)

            Row() {
              Button('插入内容').onClick(() => {
                this.mutableStyledString2.clearStyles();
                this.mutableStyledString2.setStyle({
                  start: 0,
                  length: 4,
                  styledKey: StyledStringKey.FONT,
                  styledValue: this.fontStyleAttr
                })
                this.mutableStyledString2.setStyle({
                  start: 0,
                  length: 4,
                  styledKey: StyledStringKey.DECORATION,
                  styledValue: this.decorationStyleAttr
                })
                let richEditorStyledString = this.controller.getStyledString();
                richEditorStyledString.appendStyledString(this.mutableStyledString2);
                this.controller.setStyledString(richEditorStyledString);
              })
              Button('插入其他样式内容').onClick(() => {
                this.mutableStyledString3.setStyle({
                  start: 0,
                  length: 6,
                  styledKey: StyledStringKey.FONT,
                  styledValue: this.fontStyleAttr
                })
                this.mutableStyledString3.setStyle({
                  start: 0,
                  length: 6,
                  styledKey: StyledStringKey.DECORATION,
                  styledValue: this.decorationStyleAttr
                })
                let richEditorStyledString = this.controller.getStyledString();
                richEditorStyledString.appendStyledString(this.mutableStyledString3);
                this.controller.setStyledString(richEditorStyledString);
              })
            }

            Row() {
              Button('插入图片')
                .onClick(() => {
                  if (this.imagePixelMap !== undefined) {
                    let imageStr = new MutableStyledString(new ImageAttachment({
                      value: this.imagePixelMap,
                      size: { width: 50, height: 50 },
                      layoutStyle: { borderRadius: LengthMetrics.vp(10) },
                      verticalAlign: ImageSpanAlignment.FOLLOW_PARAGRAPH,
                      objectFit: ImageFit.Contain
                    }))
                    let richEditorStyledString = this.controller.getStyledString();
                    richEditorStyledString.appendStyledString(imageStr);
                    this.controller.setStyledString(richEditorStyledString);
                  }
                })
              Button('插入Custom')
                .onClick(() => {
                  let customSpan = new MyCustomSpan('World', 80, 40);
                  let customStr = new MutableStyledString(customSpan);
                  let richEditorStyledString = this.controller.getStyledString();
                  richEditorStyledString.appendStyledString(customStr);
                  this.controller.setStyledString(richEditorStyledString);
                })
            }

            Row() {
              Button('查询字体及下划线样式')
                .onClick(() => {
                  let richEditorStyledString = this.controller.getStyledString();
                  if (richEditorStyledString.length <= 0) {
                    return;
                  }
                  let styles = richEditorStyledString.getStyles(0, richEditorStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      let start = styles[i].start;
                      let end = styles[i].start + styles[i].length;
                      let range = '[ ' + start + ' , ' + end + ' ] ';
                      if (styles[i].styledKey === 0) {
                        let fontAttr = styles[i].styledValue as TextStyle;
                        let fontStr =
                          'range: ' + range + ' fontColor: ' + fontAttr.fontColor + ' fontSize: ' + fontAttr.fontSize
                            + ' fontWeight: ' + fontAttr.fontWeight + ' fontStyle: ' + fontAttr.fontStyle +
                            ' fontFamily: ' + fontAttr.fontFamily;
                        console.info('styledString test fontStyle: ' + fontStr);
                      }
                      if (styles[i].styledKey === 1) {
                        let decoAttr = styles[i].styledValue as DecorationStyle;
                        let decoStr =
                          'range: ' + range + ' type: ' + decoAttr.type + ' color: ' + decoAttr.color + ' style: ' +
                          decoAttr.style;
                        console.info('styledString test decorationStyle: ' + decoStr);
                      }
                    }
                  }
                })
              Button('查询其他文本样式')
                .onClick(() => {
                  let richEditorStyledString = this.controller.getStyledString();
                  if (richEditorStyledString.length <= 0) {
                    return;
                  }
                  let styles = richEditorStyledString.getStyles(0, richEditorStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      let start = styles[i].start;
                      let end = styles[i].start + styles[i].length;
                      let range = '[ ' + start + ' , ' + end + ' ] ';
                      console.info('styledString test style key: ' + styles[i].styledKey + ' range: ' + range);
                      if (styles[i].styledKey === 2) {
                        let baselineAttr = styles[i].styledValue as BaselineOffsetStyle;
                        console.info('styledString test BaselineOffsetStyle range: ' + range + ' Offset: ' +
                        baselineAttr.baselineOffset)
                      }
                      if (styles[i].styledKey === 3) {
                        let letterAttr = styles[i].styledValue as LetterSpacingStyle;
                        console.info('styledString test LetterSpacingStyle range: ' + range + ' letterSpacing: ' +
                        letterAttr.letterSpacing)
                      }
                      if (styles[i].styledKey === 4) {
                        let textShadowAttr = styles[i].styledValue as TextShadowStyle;
                        let shadowValues = textShadowAttr.textShadow;
                        console.info('styledString test textShadow range: ' + range)
                        if (shadowValues.length > 0) {
                          for (let j = 0; j < shadowValues.length; j++) {
                            console.info('styledString test textShadow type:' + shadowValues[j].type);
                            console.info('styledString test textShadow radius:' + shadowValues[j].radius);
                            console.info('styledString test textShadow color:' + shadowValues[j].color);
                            console.info('styledString test textShadow offsetX:' + shadowValues[j].offsetX);
                            console.info('styledString test textShadow offsetY:' + shadowValues[j].offsetY);
                          }
                        }
                      }
                    }
                  }
                })
            }

            Row() {
              Button('查询图片样式')
                .onClick(() => {
                  let richEditorStyledString = this.controller.getStyledString();
                  if (richEditorStyledString.length <= 0) {
                    return;
                  }
                  let imageArray =
                    richEditorStyledString.getStyles(0, richEditorStyledString.length, StyledStringKey.IMAGE)
                  for (let i = 0; i < imageArray.length; ++i) {
                    console.info('styledString test image start ' + imageArray[i].start + ' length ' +
                    imageArray[i].length)
                    if (imageArray[i].styledKey === 300) {
                      let attachment = imageArray[i].styledValue as ImageAttachment
                      console.info('styledString test image value ' + JSON.stringify(attachment.value))
                      if (attachment.size !== undefined) {
                        console.info('styledString test image size width ' + attachment.size.width + ' height ' +
                        attachment.size.height)
                      }
                      console.info('styledString test image vertical ' + attachment.verticalAlign)
                      console.info('styledString test image fit ' + attachment.objectFit)
                      if (attachment.layoutStyle !== undefined) {
                        let radius = attachment.layoutStyle.borderRadius as BorderRadiuses
                        console.info('styledString test image radius ' + JSON.stringify(radius))
                      }
                    }
                  }
                })
            }
          }
        }
        .width('100%')
        .height('20%')
        .borderWidth(3)
        .borderColor(Color.Orange)
        .scrollable(ScrollDirection.Vertical)
        .scrollBarColor(Color.Gray)
        .scrollBarWidth(5)

        Text('属性字符串:').fontSize(10).width('100%')
        RichEditor(this.options)
          .onReady(() => {
            this.styledString.appendStyledString(new StyledString('属性字符串继续文字', [{
              start: 0,
              length: 5,
              styledKey: StyledStringKey.FONT,
              styledValue: new UrlStyle('https://www.example.com')
            },
              {
                start: 3,
                length: 5,
                styledKey: StyledStringKey.FONT,
                styledValue: new TextStyle({
                  fontColor: '#8F00F1',
                  fontSize: LengthMetrics.px(80),
                  fontStyle: FontStyle.Italic,
                }),
              },
              {
                start: 0,
                length: 7,
                styledKey: StyledStringKey.PARAGRAPH_STYLE,
                styledValue: new ParagraphStyle({
                  textVerticalAlign: TextVerticalAlign.TOP,
                })
              },
              {
                start: 3,
                length: 6,
                styledKey: StyledStringKey.DECORATION,
                styledValue: new DecorationStyle({
                  type: TextDecorationType.LineThrough,
                  color: Color.Blue,
                  thicknessScale: 6,
                  style: TextDecorationStyle.DASHED
                },
                  {
                    enableMultiType: true
                  }
                )
              },
              {
                start: 4,
                length: 5,
                styledKey: StyledStringKey.DECORATION,
                styledValue: new DecorationStyle({
                  type: TextDecorationType.Overline,
                  color: Color.Red,
                  thicknessScale: 2,
                  style: TextDecorationStyle.WAVY
                },
                  {
                    enableMultiType: true
                  })
              },
              {
                start: 6,
                length: 3,
                styledKey: StyledStringKey.DECORATION,
                styledValue: new DecorationStyle({
                  type: TextDecorationType.Underline,
                  color: Color.Pink,
                  thicknessScale: 4,
                  style: TextDecorationStyle.WAVY
                },
                  {
                    enableMultiType: true
                  })
              }

            ]))
            this.styledString.appendStyledString(new MutableStyledString(new ImageAttachment({
              value: this.imagePixelMap,
              resourceValue: $r('app.media.cat'),
              size: { width: 50, height: 90 },
              layoutStyle: { borderRadius: LengthMetrics.vp(10) },
              verticalAlign: ImageSpanAlignment.FOLLOW_PARAGRAPH,
              objectFit: ImageFit.Contain
            })));
            this.controller.setStyledString(this.styledString);
            this.controller.onContentChanged(this.contentChangedListener);
          })
          .height('30%')
          .width('100%')
          .borderWidth(1)
          .borderColor(Color.Red)
          .enablePreviewText(this.enablePreviewText)
          .enableDataDetector(this.enableDataDetector)
          .copyOptions(this.copyOption[this.index])
          .aboutToDelete((value) => {
            console.log('aboutToDelete回调' +
            JSON.stringify(value))
            console.log(JSON.stringify(this.controller.getCaretOffset()))
            return true
          })
          .aboutToIMEInput((value) => {
            console.log('aboutToIMEInput回调:' +
            JSON.stringify(value))
            console.log(JSON.stringify(this.controller.getCaretOffset()))
            return true
          })
          .onDeleteComplete((value) => {
            console.log('onDeleteComplete回调:' + JSON.stringify(value))
          })
          .onIMEInputComplete((value) => {
            console.log('onIMEInputComplete回调: ' +
            JSON.stringify(value))
            console.log(JSON.stringify(this.controller.getCaretOffset()))
          })
          .onPaste(() => {
            this.text5 = '测试log：onPaste';
            console.log('测试log：onPaste')
            console.log('onPaste:' + JSON.stringify(this.controller.getCaretOffset()))
          })
          .onCut(() => {
            console.log('onCut:' + JSON.stringify(this.controller.getCaretOffset()))
          })
          .onDidChange((value) => {
            console.log('onDidChange:' + JSON.stringify(value))
          })
          .onWillChange((value) => {
            console.log('onWillChange:' + JSON.stringify(value))
            console.log('onWillChange:' + JSON.stringify(this.controller.getCaretOffset()))
            return true;
          })
          .onWillChange((value) => {
            console.log('onWillChange:' + JSON.stringify(value))
            return true
          })
          .onSelect(() => {
            console.log('触发onSelect回调')
          })
          .onSelect((value) => {
            console.log('onSelect回调：' + JSON.stringify(value))
          })
          .onSelectionChange((value: RichEditorRange) => {
            console.log('onSelectionChange回调：' + JSON.stringify(value))
          })
        Scroll(this.scroller3) {
          Column() {
            Row() {
              Button('getSPans').onClick(() => {
                console.log('getspans:' +
                JSON.stringify(this.controller1.getSpans({ start: this.start, end: this.end })))

              }).controlSize(ControlSize.SMALL)
              Button('add').onClick(() => {
                this.controller1.addTextSpan('emjio链接：https://www.emojiall.com/zh-hans/sub-categories/B11 \n\n测试emoji\n😀😀😃😄😁😆🏁🚩🇨🇳🇯🇵👭🍇🏧🐸🎼🛋️✉️🎭⚽🦰🦰💪🤛🥰👻😸🙈❤️‍🔥💯🧑⚠️⬆️🛐♈⏭️♀️✖️ ️💱#️⃣🅾️🔷🏁🇦🇨🇨🇬⚕️🧑‍🎓🧑‍🎨🧑‍🍼🧑‍🎄🏇🍄🍱🦞🌍🏖️🎡🚂🛳️✈️🛎️⏳🎇🔮🎭🩰📟🖱️🏮📗💰📧✏️📁🏧󠁢󠁥󠁮󠁧󠁿󠁧󠁢󠁳󠁣󠁴󠁿🏽‍♀️‍➡️🧑🏽‍🦱👩⚖',
                  {
                    gesture: {
                      onDoubleClick: () => {
                        console.info('onHover_onDoubleClick TextSpan_emoji onDoubleClick ')
                      }
                    }
                  })
              })
              Button('get').onClick(() => {
                this.controller1.setSelection(this.start, this.end)
              })
              Button('setTypingStyle')
                .fontSize(12)
                .onClick(() => {

                  this.controller1.setTypingStyle(
                    {
                      fontSize: 20,
                      fontWeight: 400,
                      fontStyle: FontStyle.Normal,
                      fontColor: Color.Red
                    })
                })
              Button('设置光标位置').onClick(() => {
                this.controller1.setCaretOffset(20)
              })
            }

            Row() {
              Button('copyOption:' + this.copyOptionStr[this.index], { controlSize: ControlSize.SMALL }).onClick(() => {
                this.index++
                if (this.index > (this.copyOptionStr.length - 1)) {
                  this.index = 0
                }
              })
              Button('全选').onClick(() => {
                this.controller1.setSelection(-1, -1)
              })
              Button('切换AI').onClick(() => {
                this.enableDataDetector = !this.enableDataDetector
              })
              Button('增加多个表情').onClick(() => {
                this.controller1.addTextSpan('👨‍👩‍👧‍👦👩‍👧‍👦\uD83D\uDC68\u200D\uD83D\uDC69\u200D\uD83D\uDC67\u200D\uD83D\uDC66\uD83D\uDC69\u200D\uD83D\uDC69\u200D\uD83D\uDC66',
                  {
                    style:
                    {
                      fontColor: Color.Orange,
                      fontSize: 20
                    },
                    urlStyle: { url: '1' },

                    gesture: {
                      onDoubleClick: () => {
                        console.info('onHover_onDoubleClick TextSpan_emoji1 onDoubleClick ')
                      },
                    },
                  })
              })
            }

            Row() {
              Button('增加数字1').onClick(() => {
                this.controller1.addTextSpan('013',
                  {
                    style:
                    {
                      fontColor: Color.Orange,
                      fontSize: 50,
                      decoration: {
                        type: TextDecorationType.Underline,
                        thicknessScale: 2
                      },
                    },
                    gesture: {
                      onDoubleClick: () => {
                        console.info('onHover_onDoubleClick TextSpan_number onDoubleClick')
                      },
                    },
                  })
              }).fontSize(8).height(20)

              Button('增加图片').onClick(() => {
                this.controller1.addImageSpan($r('app.media.icon'),
                  {
                    imageStyle:
                    {
                      size: [80, 80],
                      verticalAlign: ImageSpanAlignment.FOLLOW_PARAGRAPH
                    },
                  })
              }).fontSize(8).height(20)
              Button('增加图片1').onClick(() => {
                this.controller1.addImageSpan($r('app.media.cat'),
                  {
                    imageStyle:
                    {
                      size: [80, 200]
                    },
                    gesture: {
                      onDoubleClick: () => {
                        console.info('onHover_onDoubleClick TextSpan_Image1 onDoubleClick')
                      },
                      onLongPress: () => {
                        console.info('onHover_onDoubleClick TextSpan_Image1 onLongPress')
                      },
                      onClick: () => {
                        console.info('onHover_onDoubleClick TextSpan_Image1 onClick')
                      }
                    },
                    onHover: (status: boolean, event: HoverEvent) => {
                      console.info('onHover_onDoubleClick ImageSpan1 onHover status : ' + status)
                      console.info('onHover_onDoubleClick ImageSpan1 onHover HoverEvent :' + JSON.stringify(event))
                    }
                  })
              }).fontSize(8).height(20)
              Button('增加文字').onClick(() => {
                this.controller1.addTextSpan('文字文字文字文字',
                  {
                    style:
                    {
                      fontColor: $r('app.color.color_2'),
                      fontSize: this.S,
                      decoration: {
                        type: TextDecorationType.LineThrough,
                        thicknessScale: 5
                      },
                    },
                    paragraphStyle: {
                      textVerticalAlign: TextVerticalAlign.TOP,
                    },
                    gesture: {
                      onDoubleClick: () => {
                        console.info('onHover_onDoubleClick TextSpan_text onDoubleClick ')
                      },
                    },
                  })
              }).fontSize(8).height(20)
              Button('增加英文').onClick(() => {
                this.controller1.addTextSpan('This is set wordBreak to WordBreak text',
                  {
                    style:
                    {
                      fontColor: Color.Orange,
                      fontSize: 20
                    },
                  })
              }).fontSize(8).height(20)
            }

            Row() {
              Button('增加symbol').onClick(() => {
                this.controller1.addSymbolSpan($r('sys.symbol.ohos_trash'),
                  {
                    style:
                    {
                      fontSize: 50
                    }
                  })
              }
              ).fontSize(8).height(20)
              Button('addBuilderSpan').onClick(() => {
                this.my_builder = () => {
                  this.MyBuilder()
                }
                this.controller1.addBuilderSpan(this.my_builder)
              }).fontSize(8).height(20)
              Button('预设段落样式')
                .fontSize(10)
                .height(25)
                .onClick(() => {
                  let style: RichEditorParagraphStyle = {
                    textAlign: TextAlign.Center,
                    leadingMargin: 100,
                    wordBreak: WordBreak.NORMAL
                  }
                  this.controller1.setTypingParagraphStyle(style)
                })
                .fontSize(8)
                .height(20)
            }

            Row() {
              Button('增加高度').onClick(() => {
                this.H = this.H + 5
              })
              Button('减少高度').onClick(() => {
                this.H = this.H - 5
              })

              Button('增加宽度').onClick(() => {
                this.w = this.w + 5
              })
              Button('减少宽度').onClick(() => {
                this.w = this.w - 5
              })

            }

            Row() {
              Button('字体变大').onClick(() => {
                this.S = this.S + 1
                this.controller1.updateSpanStyle({
                  start: -1,
                  end: -1,
                  textStyle:
                  {
                    fontSize: this.S
                  }
                })
              }).fontSize(8).height(20)
              Button('字体变小').onClick(() => {
                this.S = this.S - 1
                this.controller1.updateSpanStyle({
                  start: -1,
                  end: -1,
                  textStyle:
                  {
                    fontSize: this.S
                  }
                })
              }).fontSize(8).height(20)
              Button('线大').onClick(() => {
                this.DS = this.DS + 1
                this.controller1.updateSpanStyle({
                  start: this.start,
                  end: this.end,
                  textStyle: {
                    decoration: {
                      type: TextDecorationType.LineThrough,
                      thicknessScale: this.DS
                    }
                  }
                })
              }).fontSize(8).height(20)
              Button('线小').onClick(() => {
                this.DS = this.DS - 1
                console.info(`=-= DS: ${this.DS}, start: ${this.start}, end: ${this.end}`);
                let deco = new DecorationStyle({
                  type: TextDecorationType.LineThrough,
                  thicknessScale: this.DS
                });
                this.controller1.updateSpanStyle({
                  start: this.start,
                  end: this.end,
                  textStyle: {
                    decoration: deco
                  }
                })
              }).fontSize(8).height(20)
              Button('更新文本').onClick(() => {
                this.controller1.updateSpanStyle(
                  {
                    start: this.start,
                    end: this.end,
                    textStyle: {
                      textBackgroundStyle: { color: Color.Green },
                    },
                    imageStyle: {
                      size: ['150px', '150px'],
                      verticalAlign: ImageSpanAlignment.BASELINE
                    },
                  })
              }).fontSize(8).height(20)
            }

            Row() {
              Button('textVerticalAlign:' + this.textVerticalAlignStr[this.index1], { controlSize: ControlSize.SMALL })
                .onClick(() => {
                  this.index1++
                  if (this.index1 > (this.textVerticalAlignStr.length - 1)) {
                    this.index1 = 0
                  }
                })
                .fontSize(8)
                .height(20)
              Button('更新文本对齐').onClick(() => {
                this.controller1.updateParagraphStyle(
                  {
                    start: this.start,
                    end: this.end,
                    style: {
                      textVerticalAlign: this.textVerticalAlign[this.index1]
                    }
                  })
              }).fontSize(8).height(20)
              Button('获取段落样式').onClick(() => {
                console.log('getParagraphs&&:' +
                JSON.stringify(this.controller1.getParagraphs({ start: this.start, end: this.end })))
              }).fontSize(8).height(20)
            }

            Row() {
              Button('imageSpanAlignment:' + this.imageSpanAlignmentStr[this.index2],
                { controlSize: ControlSize.SMALL }).onClick(() => {
                this.index2++
                if (this.index2 > (this.imageSpanAlignmentStr.length - 1)) {
                  this.index2 = 0
                }
              }).fontSize(8).height(20)
              Button('更新图片对齐').onClick(() => {
                this.controller1.updateSpanStyle(
                  {
                    start: this.start,
                    end: this.end,
                    textStyle: {
                      fontSize: 20,
                      fontStyle: FontStyle.Italic,
                      fontColor: $r('app.color.color_1'),
                      textShadow: {
                        radius: 10,
                        color: Color.Blue,
                        offsetX: 10,
                        offsetY: 0
                      },
                      lineHeight: 200,
                      letterSpacing: 10,
                      decoration: {
                        type: TextDecorationType.Underline,
                        thicknessScale: 5,
                        color: Color.Blue,
                        style: TextDecorationStyle.WAVY
                      },
                      textBackgroundStyle: { color: Color.Green },
                      halfLeading: true,
                    },
                    imageStyle: {
                      size: ['150px', '150px'],
                      verticalAlign: this.imageSpanAlignment[this.index2]
                    },
                  })
              }).fontSize(8).height(20)
              Button('更新段落对齐').onClick(() => {
                this.controller1.updateParagraphStyle(
                  {
                    start: this.start,
                    end: this.end,
                    style: {
                      textAlign: TextAlign.End,
                    }
                  })
              }).fontSize(8).height(20)
            }

            Row() {
              Text('索引起始位置:')
              Counter() {
                Text(this.start.toString())
              }.margin({ right: 20 })
              .onInc(() => {
                this.start++
              })
              .onDec(() => {
                this.start--
              })
            }.height(50)

            Row() {
              Text('索引结束位置:')
              Counter() {
                Text(this.end.toString())
              }.margin({ right: 20 })
              .onInc(() => {
                this.end++
              })
              .onDec(() => {
                this.end--
              })
            }.height(50)
          }
        }
        .width('100%')
        .height('20%')
        .borderWidth(3)
        .borderColor(Color.Orange)
        .scrollable(ScrollDirection.Vertical)
        .scrollBarColor(Color.Gray)
        .scrollBarWidth(5)

        Text('老框架:').fontSize(10).width('100%')
        RichEditor({ controller: this.controller1 })
          .clip(true)
          .draggable(true)
          .padding(10)
          .enableDataDetector(this.enableDataDetector)
          .undoStyle(1)
          .maxLength(3)
          .onReady(() => {
            this.controller1.addTextSpan('012345',
              {
                gesture:
                {
                  onDoubleClick: () => {
                    console.info('onHover_onDoubleClick TextSpan_text1 onDoubleClick')
                  },
                  onClick: () => {
                    console.info('onHover_onDoubleClick TextSpan_text1 onClick')
                  },
                  onLongPress: () => {
                    console.info('onHover_onDoubleClick TextSpan_text1 onLongpress')
                  }
                },
              })
            this.controller1.addSymbolSpan($r('sys.symbol.ohos_trash'),

              {
                style:
                {
                  fontSize: 30
                }
              })
            this.controller1.addImageSpan($r('app.media.icon'),
              {
                imageStyle:
                {
                  size: ['57px', '57px']
                },
                onHover: (status: boolean, event: HoverEvent) => {
                  console.info('onHover_onDoubleClick ImageSpan onHover status : ' + status)
                  console.info('onHover_onDoubleClick ImageSpan onHover HoverEvent :' + JSON.stringify(event))
                }

              })
            this.controller1.addTextSpan('56789',
              {
                style:
                {
                  fontColor: Color.Green,
                  fontSize: 30,
                  decoration: {
                    type: TextDecorationType.Underline,
                    style: TextDecorationStyle.WAVY,
                    thicknessScale: 5
                  },

                },
                gesture:
                {
                  onDoubleClick: () => {
                    console.info('onHover_onDoubleClick TextSpan_text2 onDoubleClick')
                  },
                  onClick: () => {
                    console.info('onHover_onDoubleClick TextSpan_text2 Click')
                  },
                  onLongPress: () => {
                    console.info('onHover_onDoubleClick TextSpan_text2 Longpress')
                  }
                },
              })
          })
          .onSelect((value: RichEditorSelection) => {
            this.start = value.selection[0];
            this.end = value.selection[1];
            this.message = '[' + this.start + ', ' + this.end + ']'
          })
          .onWillChange((value: RichEditorChangeValue) => {
            console.log('onWillChange-------' + JSON.stringify(value))
            return true
          })
          .aboutToIMEInput((value: RichEditorInsertValue) => {
            console.log('aboutToIMEInput value=' + JSON.stringify(value))
            return true
          })
          .onSelectionChange((value: RichEditorRange) => {
            console.log('onSelectionChange回调：' + JSON.stringify(value))
            this.onSelectionChangeValue = JSON.stringify(value)
          })
          .onIMEInputComplete((value: RichEditorTextSpanResult) => {
            console.log('onIMEInputComplete value=' + JSON.stringify(value))
          })
          .aboutToDelete((value: RichEditorDeleteValue) => {
            console.info('aboutToDelete value=' + JSON.stringify(value))
            return true
          })
          .onDeleteComplete(() => {
            console.log('---------------------- onDeleteComplete ------------------------')
          })
          .borderWidth(1)
          .copyOptions(this.copyOption[this.index])
          .borderColor(Color.Green)
          .width(this.w)
          .height(this.H)
          .borderRadius(this.radius)
      }
    }
  }
}