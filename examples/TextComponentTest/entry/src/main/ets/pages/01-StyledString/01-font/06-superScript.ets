import { LengthMetrics, LengthUnit } from '@kit.ArkUI'
import common from '@ohos.app.ability.common';
import window from '@ohos.window';

@Entry
@Component
struct struct_01_StyledString_01_StyledStringValue_01_TextStyle_superScript {
  fontStyleAttr1: TextStyle = new TextStyle({ fontColor: Color.Blue });
  fontStyleAttr2: StyledStringValue = new TextStyle({
    fontColor: Color.Orange,
    fontSize: LengthMetrics.vp(20),
    fontWeight: FontWeight.Bolder,
    fontStyle: FontStyle.Italic,
    fontFamily: 'Arial'
  });

  fontStyleAttr3: StyledStringValue = new TextStyle({
    fontColor: Color.Red,
    fontSize: LengthMetrics.vp(35),
    fontWeight: FontWeight.Bolder,
    fontStyle: FontStyle.Italic,
    fontFamily: 'Arial',
  });
  // 创建多重TextStyle样式的对象mutableStyledString
  urlString: StyledStringValue = new UrlStyle( 'www.********.com' );

  mutableStyledString: MutableStyledString = new MutableStyledString(
    '干活干活干活🎄AAAAA🎄88888$$$$$%%%%%@@@@@=====+++++&&&&&00000GASDF\nJJ,S🎄CBJ\nMGMM(3)',
    [
      {
        start: 0,
        length: 4,
        styledKey: StyledStringKey.FONT,
        styledValue: this.fontStyleAttr3
      }, {
      start: 4,
      length: 5,
      styledKey: StyledStringKey.FONT,
      styledValue: this.fontStyleAttr2
    },
      {
        start: 0,
        length: "按住显示器的菜单".length,
        styledKey: StyledStringKey.URL,
        styledValue: this.urlString
      },
      {
        start:5,
        length: 25,
        styledKey: StyledStringKey.FONT,
        styledValue: new TextStyle({
          superscript:SuperscriptStyle.SUPERSCRIPT,
          fontStyle:FontStyle.Italic, fontColor: Color.Green,
          fontSize:LengthMetrics.px(30)
        })
      },
      {
        start: 10,
        length: 20,
        styledKey: StyledStringKey.FONT,
        styledValue: new TextStyle({
          superscript:SuperscriptStyle.SUBSCRIPT,
          fontStyle:FontStyle.Italic,fontColor: Color.Red,
          fontSize:LengthMetrics.px(30)
        })
      }
    ]);

  @State fontColor1: ResourceColor = Color.Red;
  controller3: RichEditorController = new RichEditorController()
  controller4: RichEditorStyledStringController = new RichEditorStyledStringController();

  controller: TextController = new TextController();
  controller1: TextAreaController = new TextAreaController();
  options: TextOptions = { controller: this.controller };
  controller2: TextController = new TextController();
  // @State SpanStyle: string[] = ["spanStyle1","spanStyle2"]
  // @State SpanStyleIndex: number = 0

  spanStyle0: SpanStyle = {
    start: 3,
    length: 25,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      superscript:SuperscriptStyle.NORMAL,
      fontStyle:FontStyle.Italic, fontColor: Color.Black,fontSize:LengthMetrics.vp(25)  })
  };

  spanStyle1: SpanStyle = {
    start:8,
    length: 25,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      superscript:SuperscriptStyle.SUPERSCRIPT,
      fontStyle:FontStyle.Italic, fontColor: Color.Green,
      fontSize:LengthMetrics.vp(30)
    })
  };

  spanStyle2: SpanStyle = {
    start: 10,
    length: 20,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      superscript:SuperscriptStyle.SUBSCRIPT,
      fontStyle:FontStyle.Normal,fontColor: Color.Yellow,
      fontSize:LengthMetrics.vp(25)
    })
  };

  spanStyle3: SpanStyle = {
    start: 0,
    length: 30,
    styledKey: StyledStringKey.LETTER_SPACING,
    styledValue: new LetterSpacingStyle(new LengthMetrics(20, LengthUnit.VP))
  };

  spanStyle4: SpanStyle = {
    start: 0,
    length: 30,
    styledKey: StyledStringKey.LETTER_SPACING,
    styledValue: new LetterSpacingStyle(new LengthMetrics(40, LengthUnit.PX))
  };
  spanStyle5: SpanStyle = {
    start: 0,
    length: 30,
    styledKey: StyledStringKey.LETTER_SPACING,
    styledValue: new LetterSpacingStyle(new LengthMetrics(30, LengthUnit.FP))
  };
  // spanStyle6: SpanStyle = {
  // start: 0,
  // length: 30,
  // styledKey: StyledStringKey.LETTER_SPACING,
  // styledValue: new LetterSpacingStyle(new LengthMetrics(30, LengthUnit.PERCENT))
  //  };

  async onPageShow() {
    this.controller.setStyledString(this.mutableStyledString)
  }
  @State text: string =' '
  @State textShadow:(ShadowOptions|Array<ShadowOptions>) []= [
    {radius: 5, type: ShadowType.COLOR, color: Color.Green, offsetX: -5, offsetY: -5},
    {radius: 10, type: ShadowType.COLOR, color: Color.Red, offsetX: 5, offsetY: -10},
    {radius: 15, type: ShadowType.COLOR, color: Color.Orange, offsetX: -10, offsetY: 5},
    {radius: 0, type: ShadowType.COLOR, color: Color.Pink, offsetX: 5, offsetY: 5},
    {radius: 0, color: undefined, offsetX: 0, offsetY: 0},

  ]
  @State textShadowIndex: number = 0
  @State decoration:DecorationStyleInterface[] = [
    {type: TextDecorationType.LineThrough, color: Color.Black },
    {type: TextDecorationType.Underline, color: Color.Blue },
    {type: TextDecorationType.Overline, color: Color.Green },
    {type: TextDecorationType.None, color: Color.Black }
  ]
  @State decorationIndex: number = 0
  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }
  scroll: Scroller = new Scroller();
  private arr: number[] = [0]
  @State overflow:TextOverflowOptions[]=[{overflow: TextOverflow.None }, {overflow: TextOverflow.Clip },
    {overflow: TextOverflow.Ellipsis }, {overflow: TextOverflow.MARQUEE }]
  @State overflowIndex:number = 0
  @State overflowList:string []= ['None', 'Clip', 'Ellipsis', 'MARQUEE']
  @State lineSpacing: (LengthMetrics | undefined) [] =
    [undefined, LengthMetrics.prototype, LengthMetrics.px(20), LengthMetrics.px(100), LengthMetrics.vp(50),]
  @State lineSpacingIndex:number = 0
  @State TextAlign:(TextAlign|undefined) []=[undefined,TextAlign.Center, TextAlign.Start, TextAlign.End, TextAlign.JUSTIFY]
  @State TextAlignIndex:number =0
  @State html : string | undefined = undefined

  build() {
    Column({space:5}) {
      Row() {
        Button('竖屏').onClick(() => {
          this.changeOrientation(false)
        })
        Button('横屏').onClick(() => {
          this.changeOrientation(true)
        })
      }
      Column( ) {
        // 显示配了字体各种样式的属性字符串，Text组件亦配置冲突部分生效属性字符串配置，未冲突区间生效Text组件属性设置值
        Text(undefined,{ controller: this.controller })
          .fontColor(this.fontColor1)
          .decoration(this.decoration[this.decorationIndex])
          .textShadow(this.textShadow[this.textShadowIndex])
          .font({ size: 20, weight: 500, style: FontStyle.Normal })
          .copyOption(CopyOptions.LocalDevice)
          .draggable(true)
          .textOverflow(this.overflow[this.overflowIndex])
          // .fontFeature("\"sups\" on")
          .height('20%')
          .lineSpacing(this.lineSpacing[this.lineSpacingIndex])
          .textAlign(this.TextAlign[this.TextAlignIndex])
        // .textIndent(10)
        // TextArea({ controller: this.controller1 })
        //   .height('20%')
        //   .borderWidth(2)
        //   .width("100%")
        //   .draggable(true)

        RichEditor({ controller: this.controller4 })
          .onReady(() => {
            this.controller.setStyledString(this.mutableStyledString);
          })
          .height("15%")
          .width("100%")
          .borderWidth(2)
          .draggable(true)
        // .copyOption(CopyOptions.LocalDevice)


      }

      Scroll(this.scroll) {
        Column({space:10}) {
          ForEach(this.arr, (item: number) => {
            Text(undefined, { controller: this.controller2 })
            // .copyOption(CopyOptions.InApp)
              .draggable(true)
              .fontSize(30)
              .copyOption(CopyOptions.LocalDevice)
              .margin(10)

            Text(undefined, { controller: this.controller2 })
            Text(this.html)
            Row({space:10}) {

              Button('NORMAL')
                .onClick(() => {
                  this.mutableStyledString.setStyle(this.spanStyle0)
                  this.controller.setStyledString(this.mutableStyledString)
                  let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      if (styles[i].styledKey === 0) {
                        let fontAttr = styles[i].styledValue as TextStyle;
                        console.info('superscript:' + fontAttr.superscript)
                        this.text = '\n' + 'superscript:' + fontAttr.superscript + '\n'
                      }
                    }
                  }
                })
              Button('SUPERSCRIPT')
                .onClick(() => {
                  this.mutableStyledString.setStyle(this.spanStyle1)
                  this.controller.setStyledString(this.mutableStyledString)
                  let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      if (styles[i].styledKey === 0) {
                        let fontAttr = styles[i].styledValue as TextStyle;
                        console.info('superscript:' + fontAttr.superscript)
                        this.text = '\n' + 'superscript:' + fontAttr.superscript + '\n'
                      }
                    }
                  }
                })
              Button('SUBSCRIPT')
                .onClick(() => {
                  this.mutableStyledString.setStyle(this.spanStyle2)
                  this.controller.setStyledString(this.mutableStyledString)
                  let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      if (styles[i].styledKey === 0) {
                        let fontAttr = styles[i].styledValue as TextStyle;
                        console.info('superscript:' + fontAttr.superscript)
                        this.text = '\n' + 'superscript:' + fontAttr.superscript + '\n'
                      }
                    }
                  }
                })

            }
            Row({ space: 10 }) {
              Button('lineSpacing')
                .onClick(() => {
                  this.lineSpacingIndex++
                  if (this.lineSpacingIndex > this.lineSpacing.length - 1) {
                    this.lineSpacingIndex = 0
                  }
                })

              Button('TextAlign')
                .onClick(()=>{
                  this.TextAlignIndex++
                  if (this.TextAlignIndex > this.TextAlign.length -1) {
                    this.TextAlignIndex = 0

                  }
                })
              Button('toHtml').onClick(() => {
                this.html = StyledString.toHtml(this.mutableStyledString)
              }).margin(5)

              Button('fromHtml').onClick(async () => {
                let styledString = await StyledString.fromHtml(this.html)
                this.controller2.setStyledString(styledString)
              }).margin(5)
            }
            Row(){
              Button('间距_20vp')
                .onClick(() => {
                  this.mutableStyledString.setStyle(this.spanStyle3)
                  this.controller.setStyledString(this.mutableStyledString)
                  let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      if (styles[i].styledKey === 0) {
                        let fontAttr = styles[i].styledValue as TextStyle;
                        console.info('superscript:' + fontAttr.superscript)
                        this.text = '\n' + 'superscript:' + fontAttr.superscript + '\n'
                      }
                    }
                  }
                })
              Button('间距_40px')
                .onClick(() => {
                  this.mutableStyledString.setStyle(this.spanStyle4)
                  this.controller.setStyledString(this.mutableStyledString)
                  let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      if (styles[i].styledKey === 0) {
                        let fontAttr = styles[i].styledValue as TextStyle;
                        console.info('superscript:' + fontAttr.superscript)
                        this.text = '\n' + 'superscript:' + fontAttr.superscript + '\n'
                      }
                    }
                  }
                })
              Button('间距_30fp')
                .onClick(() => {
                  this.mutableStyledString.setStyle(this.spanStyle5)
                  this.controller.setStyledString(this.mutableStyledString)
                  let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      if (styles[i].styledKey === 0) {
                        let fontAttr = styles[i].styledValue as TextStyle;
                        console.info('superscript:' + fontAttr.superscript)
                        this.text = '\n' + 'superscript:' + fontAttr.superscript + '\n'
                      }
                    }
                  }
                })
            }

            Row({space:10}) {
              Button('清除所有样式').onClick(() => {
                this.mutableStyledString.clearStyles()
                this.controller.setStyledString(this.mutableStyledString)
              })
              Button('替换新字符串_1[3,1]').onClick(() => {
                this.mutableStyledString.replaceStyledString(3, 1, new StyledString('符A🎄$', [{
                  start: 2,
                  length: 3,
                  styledKey: StyledStringKey.FONT,
                  styledValue: new TextStyle({
                    superscript: SuperscriptStyle.SUPERSCRIPT,
                    fontColor: Color.Yellow,
                    fontSize: LengthMetrics.px(55)
                  })
                }]))
                this.controller.setStyledString(this.mutableStyledString)
                let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
                if (styles.length !== 0) {
                  for (let i = 0; i < styles.length; i++) {
                    if (styles[i].styledKey === 0) {
                      let fontAttr = styles[i].styledValue as TextStyle;
                      console.info('replace superscript:' + fontAttr.superscript)
                      this.text = '\n' + 'replace superscript:' + fontAttr.superscript + '\n'
                    }
                  }
                }
              })
              Button('replaceStyle')
                .onClick(() => {
                  this.mutableStyledString.replaceStyle({
                    start: 2,
                    length: 6,
                    styledKey: StyledStringKey.FONT,
                    styledValue: new TextStyle({
                      superscript: SuperscriptStyle.SUPERSCRIPT,
                      fontStyle: FontStyle.Italic,
                      fontColor: Color.Orange,
                      fontSize: LengthMetrics.px(30)
                    })
                  })

                  this.controller.setStyledString(this.mutableStyledString)
                })
                .margin({ top: 10 })

            }
            Row({space:10}) {
              Button('RemoveString (5,1)').onClick(() => {
                this.mutableStyledString.removeString(5, 1)
                this.controller.setStyledString(this.mutableStyledString)
              })
              Button('RemoveString (3,5)').onClick(() => {
                this.mutableStyledString.removeString(3, 5)
                this.controller.setStyledString(this.mutableStyledString)
              })
              Button('清除指定范围[2,3]')
                .onClick(() => {
                  this.mutableStyledString.removeStyles(2, 3);
                  this.controller.setStyledString(this.mutableStyledString);
                })
            }

            Row({space:10}) {
              Button('获取属性字符串 (4,4)').onClick(() => {
                this.controller2.setStyledString(this.mutableStyledString.subStyledString(4, 4))
              })

              Button('替换指定范围replace[2,5]')
                .onClick(() => {
                  this.mutableStyledString.replaceString(2, 5, "替换ss7🎄AAAAA9SS替换")
                  this.controller.setStyledString(this.mutableStyledString)
                })

            }
            Row({space:10}) {
              Button('插入字符串[3,')
                .onClick(() => {
                  this.mutableStyledString.insertString(3, '1符AFFFSD')
                  this.controller.setStyledString(this.mutableStyledString)
                })

              Button('指定位置插入新[4,').onClick(() => {
                this.mutableStyledString.insertStyledString(4, new StyledString("SS🎄SDS🎄DDFA34🎄定34定34定dd义", [
                  {
                    start: 2,
                    length: 3,
                    styledKey: StyledStringKey.FONT,
                    styledValue: new TextStyle({
                      superscript: SuperscriptStyle.SUPERSCRIPT,
                      fontColor: Color.Blue,fontStyle:FontStyle.Italic, fontSize: LengthMetrics.vp(15) })
                  },
                  {
                    start: 5,
                    length: 3,
                    styledKey: StyledStringKey.FONT,
                    styledValue: new TextStyle({
                      superscript: SuperscriptStyle.SUBSCRIPT,
                      fontColor: Color.Blue,fontStyle:FontStyle.Italic, fontSize: LengthMetrics.vp(20) })
                  },
                  {
                    start: 8,
                    length: 3,
                    styledKey: StyledStringKey.FONT,
                    styledValue: new TextStyle({
                      superscript: SuperscriptStyle.NORMAL,
                      fontColor: Color.Blue,fontStyle:FontStyle.Italic, fontSize: LengthMetrics.vp(25) })
                  },

                ]))
                this.controller.setStyledString(this.mutableStyledString)
              })

              Button('末尾追加新字符串')
                .onClick(()=> {
                  this.mutableStyledString.appendStyledString(new StyledString("🎄🎄A34定34定34定义", [
                    {
                      start: 2,
                      length: 3,
                      styledKey: StyledStringKey.FONT,
                      styledValue: new TextStyle({
                        superscript: SuperscriptStyle.SUPERSCRIPT,
                        fontColor: Color.Blue,fontStyle:FontStyle.Italic, fontSize: LengthMetrics.vp(25) })
                    },
                    {
                      start: 5,
                      length: 3,
                      styledKey: StyledStringKey.FONT,
                      styledValue: new TextStyle({
                        superscript: SuperscriptStyle.SUBSCRIPT,
                        fontColor: Color.Blue,fontStyle:FontStyle.Italic, fontSize: LengthMetrics.px(80) })
                    },
                    {
                      start: 8,
                      length: 3,
                      styledKey: StyledStringKey.FONT,
                      styledValue: new TextStyle({
                        superscript: SuperscriptStyle.NORMAL,
                        fontColor: Color.Blue,fontStyle:FontStyle.Italic, fontSize: LengthMetrics.vp(25) })
                    },

                  ]))
                  this.controller.setStyledString(this.mutableStyledString)
                  let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
                  if (styles.length !== 0) {
                    for (let i = 0; i < styles.length; i++) {
                      if (styles[i].styledKey === 0) {
                        let fontAttr = styles[i].styledValue as TextStyle;
                        console.info('append superscript:' + fontAttr.superscript)
                        this.text = '\n' + 'append superscript:' + fontAttr.superscript + '\n'
                      }
                    }
                  }
                })
            }
            Row({space:10}) {
              Button('背景色')
                .onClick(() => {
                  this.textShadowIndex++
                  if (this.textShadowIndex > this.textShadow.length - 1) {
                    this.textShadowIndex = 0
                  }
                })

              Button('装饰线')
                .onClick(() => {
                  this.decorationIndex++
                  if (this.decorationIndex > this.decoration.length - 1) {
                    this.decorationIndex = 0
                  }
                })
              Button('textOverflow: '+ this.overflowList[this.overflowIndex])
                .onClick(()=>{
                  this.overflowIndex
                  this.overflowIndex++
                  if(this.overflowIndex>this.overflowList.length - 1){
                    this.overflowIndex = 0
                  }
                })

            }
            Column(){

            }.height('100%')
          }, (item: string) => item)
        }
      }

    }.width('100%')
    .expandSafeArea([200])

  }
}