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
  word: string = "drawing";
  height: number = 10;
}
@Entry
@Component
struct Index {
  // 当前设定的字体样式
  @State fontStyleText:string = "";
  fontColor:ResourceColor = Color.Red;
  fontFamily:string = "Arial";
  fontSize:LengthMetrics = LengthMetrics.fp(16);
  fontWeight:number = FontWeight.Normal;
  fontStyle:FontStyle = FontStyle.Normal;
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
    this.fontStyleText = "Font Style: { fontColor: " + this.fontColor + " fontFamily: " + this.fontFamily
      + " fontSize: " + this.fontSize.value + " fontWeight: " + this.fontWeight + " fontStyle: " + this.fontStyle + " }";
  }

  // 当前设定的下划线样式
  @State decorationStyleText:string = "";
  decorationType:TextDecorationType = TextDecorationType.None;
  decorationColor:ResourceColor|undefined = undefined;
  decorationStyle:TextDecorationStyle = TextDecorationStyle.SOLID;
  decorationStyleAttr: DecorationStyle = new DecorationStyle({
    type: this.decorationType,
    color: this.decorationColor,
    style: this.decorationStyle
  })
  private refreshDecorationStyle() {
    this.decorationStyleAttr = new DecorationStyle({
      type: this.decorationType,
      color: this.decorationColor,
      style: this.decorationStyle
    })
    this.decorationStyleText = "Decoration Style: { type:" + this.decorationType + " color: " + this.decorationColor
      + " style: " + this.decorationStyle + " }";
  }


  // 加载图片
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

  // 文本内容变化监听
  contentChangedListener: StyledStringChangedListener = {
    onWillChange: (value:StyledStringChangeValue) => {
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

  // 初始化富文本以及初始属性字符串
  controller: RichEditorStyledStringController = new RichEditorStyledStringController();
  options: RichEditorStyledStringOptions = { controller: this.controller};
  mutableStyledString1: MutableStyledString = new MutableStyledString("初始属性字符串");
  mutableStyledString2: MutableStyledString = new MutableStyledString("插入内容");
  mutableStyledString3: MutableStyledString = new MutableStyledString("其他样式内容", [{
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
  }]);

  async aboutToAppear() {
    this.refreshFontStyle();
    this.refreshDecorationStyle();
    this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.icon'));
  }

  scroller1: Scroller = new Scroller()
  scroller2: Scroller = new Scroller()

  @State enableAutoSpace:boolean = true;

  build() {
    Column() {
      Scroll(this.scroller1){
        Column() {
          Text(this.fontStyleText)
            .fontSize(16)
            .borderWidth(1)
            .borderColor(Color.Red)
            .height("20%")
            .width("100%")
          Row() {
            Button("Red").onClick(() => {
              this.fontColor = Color.Red;
              this.refreshFontStyle();
            })
            Button("Yellow").onClick(() => {
              this.fontColor = Color.Yellow;
              this.refreshFontStyle();
            })
            Button("Blue").onClick(() => {
              this.fontColor = Color.Blue;
              this.refreshFontStyle();
            })
          }
          Row() {
            Button("HarmonyOS Sans").onClick(() => {
              this.fontFamily = "HarmonyOS Sans";
              this.refreshFontStyle();
            })
            Button("Arial").onClick(() => {
              this.fontFamily = "Arial";
              this.refreshFontStyle();
            })
          }
          Row() {
            Button("Size:16").onClick(() => {
              this.fontSize = LengthMetrics.fp(16);
              this.refreshFontStyle();
            })
            Button("Size:24").onClick(() => {
              this.fontSize = LengthMetrics.fp(24);
              this.refreshFontStyle();
            })
            Button("Size:32").onClick(() => {
              this.fontSize = LengthMetrics.fp(32);
              this.refreshFontStyle();
            })
          }
          Row() {
            Button("Normal").onClick(() => {
              this.fontWeight = FontWeight.Normal;
              this.refreshFontStyle();
            })
            Button("Bold").onClick(() => {
              this.fontWeight = FontWeight.Bold;
              this.refreshFontStyle();
            })
            Button("Lighter").onClick(() => {
              this.fontWeight = FontWeight.Lighter;
              this.refreshFontStyle();
            })
          }
          Row() {
            Button("Normal").onClick(() => {
              this.fontStyle = FontStyle.Normal;
              this.refreshFontStyle();
            })
            Button("Italic").onClick(() => {
              this.fontStyle = FontStyle.Italic;
              this.refreshFontStyle();
            })
          }
          Text(this.decorationStyleText)
            .fontSize(16)
            .borderWidth(1)
            .borderColor(Color.Red)
            .height("15%")
            .width("100%")
          Row() {
            Button("Underline").onClick(() => {
              this.decorationType = TextDecorationType.Underline;
              this.refreshDecorationStyle();
            })
            Button("LineThrough").onClick(() => {
              this.decorationType = TextDecorationType.LineThrough;
              this.refreshDecorationStyle();
            })
            Button("Overline").onClick(() => {
              this.decorationType = TextDecorationType.Overline;
              this.refreshDecorationStyle();
            })
            Button("None").onClick(() => {
              this.decorationType = TextDecorationType.None;
              this.refreshDecorationStyle();
            })
          }
          Row() {
            Button("Red").onClick(() => {
              this.decorationColor = Color.Red;
              this.refreshDecorationStyle();
            })
            Button("Yellow").onClick(() => {
              this.decorationColor = Color.Yellow;
              this.refreshDecorationStyle();
            })
            Button("Blue").onClick(() => {
              this.decorationColor = Color.Blue;
              this.refreshDecorationStyle();
            })
          }
          Row() {
            Button("SOLID").onClick(() => {
              this.decorationStyle = TextDecorationStyle.SOLID;
              this.refreshDecorationStyle();
            })
            Button("DOTTED").onClick(() => {
              this.decorationStyle = TextDecorationStyle.DOTTED;
              this.refreshDecorationStyle();
            })
            Button("WAVY").onClick(() => {
              this.decorationStyle = TextDecorationStyle.WAVY;
              this.refreshDecorationStyle();
            })
          }
        }
      }
      .width("100%")
      .height("40%")
      .borderWidth(3)
      .borderColor(Color.Orange)
      .scrollable(ScrollDirection.Vertical) // 滚动方向纵向
      .scrollBarColor(Color.Gray) // 滚动条颜色
      .scrollBarWidth(5) // 滚动条宽度
      Scroll(this.scroller2){
        Column(){
          Row(){
            Button("插入内容").onClick(() => {
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
            Button("插入其他样式内容").onClick(() => {
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
          Row(){
            Button('插入图片')
              .onClick(() => {
                if (this.imagePixelMap !== undefined) {
                  let imageStr = new MutableStyledString(new ImageAttachment({
                    value: this.imagePixelMap,
                    size: { width: 50, height: 50 },
                    layoutStyle: { borderRadius: LengthMetrics.vp(10) },
                    verticalAlign: ImageSpanAlignment.BASELINE,
                    objectFit: ImageFit.Contain
                  }))
                  let richEditorStyledString = this.controller.getStyledString();
                  richEditorStyledString.appendStyledString(imageStr);
                  this.controller.setStyledString(richEditorStyledString);
                }
              })
            Button('插入Custom')
              .onClick(() => {
                let customSpan = new MyCustomSpan("World", 80, 40);
                let customStr = new MutableStyledString(customSpan);
                let richEditorStyledString = this.controller.getStyledString();
                richEditorStyledString.appendStyledString(customStr);
                this.controller.setStyledString(richEditorStyledString);
              })
            Button('插入Url')
              .onClick(() => {
                let urlString = new UrlStyle( "https://www.example.com" );
                let urlStyledString = new MutableStyledString("Hello World", [{
                  start: 0,
                  length: "Hello".length,
                  styledKey: StyledStringKey.URL,
                  styledValue: urlString
                }]);
                let richEditorStyledString = this.controller.getStyledString();
                richEditorStyledString.appendStyledString(urlStyledString);
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
                    let range = "[ " + start + " , " + end + " ] ";
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      let fontStr = "range: " + range + " fontColor: " + fontAttr.fontColor + " fontSize: " + fontAttr.fontSize
                        + " fontWeight: " + fontAttr.fontWeight + " fontStyle: " + fontAttr.fontStyle + " fontFamily: " + fontAttr.fontFamily;
                      console.info('styledString test fontStyle: ' + fontStr);
                    }
                    if (styles[i].styledKey === 1) {
                      let decoAttr = styles[i].styledValue as DecorationStyle;
                      let decoStr = "range: " + range + " type: " + decoAttr.type + " color: " + decoAttr.color + " style: " + decoAttr.style;
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
                    let range = "[ " + start + " , " + end + " ] ";
                    console.info('styledString test style key: ' + styles[i].styledKey + " range: " + range);
                    if (styles[i].styledKey === 2) {
                      let baselineAttr = styles[i].styledValue as BaselineOffsetStyle;
                      console.info('styledString test BaselineOffsetStyle range: ' + range + ' Offset: ' + baselineAttr.baselineOffset)
                    }
                    if (styles[i].styledKey === 3) {
                      let letterAttr = styles[i].styledValue as LetterSpacingStyle;
                      console.info('styledString test LetterSpacingStyle range: ' + range + ' letterSpacing: ' + letterAttr.letterSpacing)
                    }
                    if (styles[i].styledKey === 4) {
                      let textShadowAttr = styles[i].styledValue as TextShadowStyle;
                      let shadowValues = textShadowAttr.textShadow;
                      console.info('styledString test textShadow range: ' + range )
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
                let imageArray = richEditorStyledString.getStyles(0, richEditorStyledString.length, StyledStringKey.IMAGE)
                for (let i = 0; i < imageArray.length; ++i) {
                  console.info('styledString test image start ' + imageArray[i].start + ' length ' + imageArray[i].length)
                  if (imageArray[i].styledKey === 300) {
                    let attachment = imageArray[i].styledValue as ImageAttachment
                    console.info('styledString test image value ' + JSON.stringify(attachment.value))
                    if (attachment.size !== undefined) {
                      console.info('styledString test image size width ' + attachment.size.width + ' height ' + attachment.size.height)
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
          Row() {
            Button("开启自动边距").onClick(() => {
              this.enableAutoSpace = true;
            })
            Button("关闭自动边距").onClick(() => {
              this.enableAutoSpace = false;
            })
          }
        }
      }
      .width("100%")
      .height("20%")
      .borderWidth(3)
      .borderColor(Color.Orange)
      .scrollable(ScrollDirection.Vertical) // 滚动方向纵向
      .scrollBarColor(Color.Gray) // 滚动条颜色
      .scrollBarWidth(5) // 滚动条宽度
      RichEditor(this.options)
        .onReady(() => {
          this.controller.onContentChanged(this.contentChangedListener);
          this.controller.setStyledString(this.mutableStyledString1);
        })
        .enableAutoSpacing(this.enableAutoSpace)
        .height("30%")
        .width("100%")
        .borderWidth(1)
        .borderColor(Color.Red)
    }
  }
}