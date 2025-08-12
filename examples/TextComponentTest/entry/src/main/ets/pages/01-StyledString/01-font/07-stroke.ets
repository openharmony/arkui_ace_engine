import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct struct_01_StyledString_01_StyledStringValue_01_TextStyle_stroke {
  controller2: RichEditorController = new RichEditorController();
  options: RichEditorOptions = { controller: this.controller2 }
  @State string1: string = ''
  @State html: string | undefined = undefined
  //-60vp Color.blue
  spanStyle0: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Pink,
      strokeWidth: LengthMetrics.vp(-60),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //60vp #FF125AD6
  spanStyle1: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.vp(60),
      strokeColor: '#FF125AD6',
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //20vp $r('app.color.green')
  spanStyle2: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.vp(20),
      strokeColor: $r('app.color.green'),
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //-20vp undefined
  spanStyle3: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.vp(-20),
      strokeColor: undefined,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //20px
  spanStyle4: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.px(20),
      strokeColor: Color.Pink,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //-20px
  spanStyle5: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.px(-20),
      strokeColor: Color.Pink,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //20lpx
  spanStyle6: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.lpx(20),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //-20lpx
  spanStyle7: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.lpx(-20),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //20fp
  spanStyle8: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.fp(20),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //-20fp
  spanStyle9: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.fp(-20),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //10%
  spanStyle10: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.percent(10),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //-10%
  spanStyle11: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.percent(-10),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //resource
  spanStyle12: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.resource($r('app.string.20vp')),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //不同颜色
  spanStyle13: SpanStyle = {
    start: 0,
    length: 2,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.vp(20),
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  spanStyle14: SpanStyle = {
    start: 2,
    length: 3,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: LengthMetrics.vp(20),
      strokeColor: Color.Green,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //undefined
  spanStyle15: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({
      fontColor: Color.Red,
      strokeWidth: undefined,
      strokeColor: Color.Blue,
      fontWeight: FontWeight.Bolder,
      fontSize: LengthMetrics.px(100)
    })
  };
  //装饰线
  spanStyle16: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.DECORATION,
    styledValue: new DecorationStyle({
      type: TextDecorationType.LineThrough,
      color: Color.Green,
      style: TextDecorationStyle.DOUBLE
    })
  };
  //阴影
  spanStyle17: SpanStyle = {
    start: 0,
    length: 5,
    styledKey: StyledStringKey.TEXT_SHADOW,
    styledValue: new TextShadowStyle({
      radius: 5,
      type: ShadowType.COLOR,
      color: Color.Yellow,
      offsetX: 10,
      offsetY: -10
    })
  };
  //字体偏移量
  spanStyle18: SpanStyle = {
    start: 0,
    length: 2,
    styledKey: StyledStringKey.BASELINE_OFFSET,
    styledValue: new BaselineOffsetStyle(LengthMetrics.px(20))
  };
  //段落样式
  spanStyle19: SpanStyle = {
    start: 0,
    length: 25,
    styledKey: StyledStringKey.PARAGRAPH_STYLE,
    styledValue: new ParagraphStyle({
      textAlign: TextAlign.End,
      maxLines: 1,
      wordBreak: WordBreak.BREAK_ALL,
      overflow: TextOverflow.Ellipsis
    })
  };
  mutableStyledString: MutableStyledString = new MutableStyledString('label', []);
  controller: TextController = new TextController();
  controller1: TextController = new TextController();

  async onPageShow() {
    this.controller.setStyledString(this.mutableStyledString);
  }

  build() {
    Scroll() {
      Column() {
        // 显示属性字符串
        Text(undefined, { controller: this.controller })
          .copyOption(CopyOptions. LocalDevice)
          .margin({ top: 10, bottom: 50 })
          .draggable(true)
          .onDragStart(() => {
          })

        Row() {
          Button('-60vp')
            .onClick(() => {
              this.mutableStyledString.setStyle(this.spanStyle0)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('60vp')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle1)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('20vp')
            .onClick(() => {
              this.mutableStyledString.setStyle(this.spanStyle2)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('-20vp')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle3)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('20px')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle4)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('-20px')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle5)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        Row() {
          Button('20lpx')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle6)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('-20lpx')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle7)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('20fp')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle8)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('-20fp')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle9)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('10%')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle10)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('-10%')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle11)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        Row() {
          Button('resource20vp')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle12)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('undefined')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle15)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        //设置删除装饰线
        Row() {
          Button('设置装饰线')
            .onClick(() => {
              this.mutableStyledString.setStyle(this.spanStyle16)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('删除装饰线')
            .onClick(() => {
              this.mutableStyledString.removeStyle(0, 5, StyledStringKey.DECORATION)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        //设置删除阴影
        Row() {
          Button('设置阴影')
            .onClick(() => {
              this.mutableStyledString.setStyle(this.spanStyle17)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('删除阴影')
            .onClick(() => {
              this.mutableStyledString.removeStyle(0, 5, StyledStringKey.TEXT_SHADOW)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        //设置删除字体偏移量
        Row() {
          Button('设置偏移量')
            .onClick(() => {
              this.mutableStyledString.setStyle(this.spanStyle18)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('删除偏移量')
            .onClick(() => {
              this.mutableStyledString.removeStyle(0, 5, StyledStringKey.BASELINE_OFFSET)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        //设置删除段落样式
        Row() {
          Button('设置段落样式')
            .onClick(() => {
              this.mutableStyledString.setStyle(this.spanStyle19)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('删除段落样式')
            .onClick(() => {
              this.mutableStyledString.removeStyle(0, 25, StyledStringKey.PARAGRAPH_STYLE)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        //不同字母设置不同描边效果
        Row() {
          Button('La描边蓝色')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle13)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('bel描边绿色')
            .onClick(() => {
              this.mutableStyledString.replaceStyle(this.spanStyle14)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        //删除样式
        Row() {
          Button('removeStyle')
            .onClick(() => {
              this.mutableStyledString.removeStyle(0, 5, StyledStringKey.FONT)
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('removeStyles')
            .onClick(() => {
              this.mutableStyledString.removeStyles(0, 5)
              this.controller.setStyledString(this.mutableStyledString)
            })
        }

        //clear和获取字体样式
        Row() {
          Button('clearStyles')
            .onClick(() => {
              this.mutableStyledString.clearStyles()
              this.controller.setStyledString(this.mutableStyledString)
            })
          Button('getStyles')
            .onClick(() => {
              let styles = this.mutableStyledString.getStyles(0, this.mutableStyledString.length)
              if (styles.length !== 0) {
                for (let i = 0; i < styles.length; i++) {
                  console.info('mutableStyledString style object start:' + styles[i].start)
                  console.info('mutableStyledString style object length:' + styles[i].length)
                  console.info('mutableStyledString style object key:' + styles[i].styledKey)
                  if (styles[i].styledKey === 0) {
                    let fontAttr = styles[i].styledValue as TextStyle;
                    console.info('mutableStyledString fontColor:' + fontAttr.fontColor)
                    console.info('mutableStyledString fontSize:' + fontAttr.fontSize)
                    console.info('mutableStyledString fontWeight:' + fontAttr.fontWeight)
                    console.info('mutableStyledString strokeWidth:' + fontAttr.strokeWidth)
                    console.info('mutableStyledString strokeColor:' + fontAttr.strokeColor)
                  }
                }
              }
            })
        }

        Row() {
          Button('增加字符串长度')
            .onClick(() => {
              this.mutableStyledString.insertString(0, 'label'.repeat(4))
              this.controller.setStyledString(this.mutableStyledString)
            })

          Button('toHtml')
            .onClick(() => {
              this.html = StyledString.toHtml(this.mutableStyledString)
            })

          Button('fromHtml').onClick(async () => {
            let styledString = await StyledString.fromHtml(this.html)
            this.controller1.setStyledString(styledString)
          })
        }
        TextInput({placeholder: '文本接收'})

        TextArea({ placeholder: '请输入' })
          .strokeWidth(LengthMetrics.vp(-20))
          .strokeColor(undefined)

        Text(undefined, { controller: this.controller1 }).height(100)
        Text(this.html)
      }
      .height('100%')
      .width('100%')
    }
  }
}