@Extend(Text)
function style() {
  .font({ size: 12 })
  .border({ width: 1 })
  .padding(12)
  .width('100%')
  .margin(5)
}
class MyTextModifier implements AttributeModifier<TextAttribute> {
  public linethickness: number = 1.0
  public linecolor: Color = Color.Black
  applyNormalAttribute(instance: TextAttribute): void {
    instance.decoration({
      type: TextDecorationType.Underline,
      color: this.linecolor,
      style: TextDecorationStyle.SOLID,
      thicknessScale: this.linethickness
    })
  }
}
class MyTextSpanModifier implements AttributeModifier<SpanAttribute> {
  public linethickness: number = 1.0
  public linecolor: Color = Color.Black
  applyNormalAttribute(instance: SpanAttribute): void {
    instance.decoration({
      type: TextDecorationType.Underline,
      color: this.linecolor,
      style: TextDecorationStyle.SOLID,
      thicknessScale: this.linethickness
    })
  }
}
@Entry
@Component
struct TextExample2 {
  @State changeDecorationIndex: number = 0;
  @State textDecorationType: TextDecorationType[] =
    [TextDecorationType.LineThrough, TextDecorationType.Overline, TextDecorationType.Underline];
  @State textDecorationTypeStr: string[] = ['LineThrough', 'Overline', 'Underline'];
  @State textDecorationStyle: TextDecorationStyle[] =
    [TextDecorationStyle.SOLID, TextDecorationStyle.DOTTED, TextDecorationStyle.WAVY];
  @State textDecorationStyleStr: string[] = ['SOLID', 'DOTTED', 'WAVY'];
  @State decorationColor:Color = Color.Black
  @State decoration:TextDecorationType = TextDecorationType.Underline
  @State decorationDynamic:TextDecorationType = TextDecorationType.Overline
  @State fontSizeDynamic:number = 20
  @State thickness:number = 1.0
  @State textmodifier: MyTextModifier = new MyTextModifier()
  @State textSpanmodifier: MyTextSpanModifier = new MyTextSpanModifier()
  translucentColor:string = 'rgba(0,0,0,0.5)'
  myDecorationStyle: DecorationStyle  = new DecorationStyle({type: TextDecorationType.Underline, thicknessScale: 4.0})
  myColor: Color = Color.Black
  myThickness: number = 1.0
  private richEditorTextStyle: RichEditorTextStyle = {}
  richController: RichEditorController = new RichEditorController()
  richOptions: RichEditorOptions = { controller: this.richController }
  mutableStr: MutableStyledString = new MutableStyledString('MutableStyledString123', [{
    start: 0,
    length: 2,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({fontColor: Color.Red})
  }, {
    start: 0,
    length: 3,
    styledKey: StyledStringKey.DECORATION,
    styledValue: new DecorationStyle({type: TextDecorationType.Underline, thicknessScale: this.thickness})
  }]);
  // 创建只读属性字符串对象styledString2
  styledString2: StyledString = new StyledString('FixedStyledString123', [{
    start: 0,
    length: 2,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({fontColor: Color.Red})
  }, {
    start: 0,
    length: 3,
    styledKey: StyledStringKey.DECORATION,
    styledValue: new DecorationStyle({type: TextDecorationType.Underline, thicknessScale: 5})
  }]);
  controller: TextController = new TextController();
  controller2: TextController = new TextController();

  build() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center}) {
      Text('decoration').fontSize(9).fontColor(0xCCCCCC)
      Text('This is the text content with the decoration set to LineThrough and the color set to Red.')
        .decoration({
          type: this.textDecorationType[this.changeDecorationIndex],
          color: Color.Red,
          style: this.TextDecorationStyle[this.changeDecorationIndex],
        })
        .style()
        .margin(5)
      Text('This is the text content with the decoration set to LineThrough and the color set to Red.')
        .decoration({
          type: this.textDecorationType[1],
          color: Color.Red,
          style: this.TextDecorationStyle[1],
        })
        .style()
        .margin(5)
      Text('This is the text content with the decoration set to LineThrough and the color set to Red.')
        .decoration({
          type: this.textDecorationType[2],
          color: Color.Red,
          style: this.TextDecorationStyle[2],
        })
        .style()
        .margin(5)
      Text('abcd123456789')
        .decoration({
          type: this.decoration,
          color: this.decorationColor,
          style: this.TextDecorationStyle[0],
          thicknessScale: 1
        })
      Text('abcd123')
        .decoration({
          type: this.decoration,
          color: this.decorationColor,
          style: this.TextDecorationStyle[0],
          thicknessScale: 2
        })
      Text('abcd123')
        .decoration({
          type: this.decoration,
          color: this.decorationColor,
          style: this.TextDecorationStyle[0],
          thicknessScale: 5
        })
      Text('dynamic123')
        .id('TextDecorationStyleText')
        .decoration({
          type: this.decoration,
          color: this.decorationColor,
          style: TextDecorationStyle.DOTTED,
          thicknessScale: this.thickness
        })
        .copyOption(CopyOptions.InApp)
        .fontSize(40)

      Text('dynamic123')
        .id('crossLineDeco')
        .decoration({
          type: TextDecorationType.LineThrough,
          color: this.decorationColor,
          style: this.TextDecorationStyle[0],
          thicknessScale: this.thickness
        })
        .backgroundColor(Color.Blue)
        .copyOption(CopyOptions.InApp)
        .fontSize(40)
      Text('translucent123我是中文这鞋子不错')
        .decoration({
          type: this.decoration,
          color: this.translucentColor,
          style: this.TextDecorationStyle[0],
          thicknessScale: this.thickness
        })
      Text('Modifier123')
        .attributeModifier(this.textmodifier)
      Text(undefined, { controller: this.controller })
        .copyOption(CopyOptions.InApp)
        .draggable(true)
        .fontSize(30)
        .onAppear(() => {
          this.controller.setStyledString(this.mutableStr)
        })
      Text(undefined, { controller: this.controller2 })
        .copyOption(CopyOptions.InApp)
        .draggable(true)
        .fontSize(30)
        .onAppear(() => {
          this.controller2.setStyledString(this.styledString2)
        })
      Text() {
        Span('span')
        Span('123')
          .id('spanDeco')
          .decoration({
            type: this.decorationDynamic,
            color: this.decorationColor,
            style: this.TextDecorationStyle[0],
            thicknessScale: this.thickness
          })
          .fontSize(this.fontSizeDynamic)
      }
      Text(){
        Span('spanModifier')
        Span('123')
          .attributeModifier(this.textSpanmodifier)
      }
      Text('dynamic123backgroundColor123')
        .id('crossLineDeco')
        .decoration({
          type: TextDecorationType.LineThrough,
          color: this.decorationColor,
          style: this.TextDecorationStyle[0],
          thicknessScale: this.thickness
        })
        .copyOption(CopyOptions.InApp)
      Text('dynamic123backgroundColor123')
        .id('crossLineDeco')
        .decoration({
          type: TextDecorationType.Underline,
          color: this.decorationColor,

          style: TextDecorationStyle.WAVY,
          thicknessScale: 0
        })
        .copyOption(CopyOptions.InApp)
      RichEditor(this.richOptions)
        .onReady(() => {
          this.richController.addTextSpan('拖拽文本到这',
            {
              style:
              {
                fontColor: Color.Orange,
                fontSize: 30,
                textShadow: { radius: 10, color: Color.Blue, offsetX: 10, offsetY: 0 }
              }
            })
        })
        .borderWidth(1)
        .borderColor(Color.Green)
        .width('100%')
        .height('30%')
      Button('default style')
        .onClick(() => {
          this.decoration = TextDecorationType.None
          this.decorationColor = Color.Black
        })
      Button('Underline style')
        .onClick(() => {
          this.decoration = TextDecorationType.Underline
          this.decorationColor = Color.Red
        })
      Button('test ++')
        .onClick(() => {
          this.decorationDynamic = TextDecorationType.LineThrough
        })
      Button('test --')
        .onClick(() => {
          this.decorationDynamic = TextDecorationType.Overline
        })
      Button('thickness ++')
        .onClick(() => {
          let thicknessUnion: number | undefined = this.myDecorationStyle.thicknessScale
          console.error(' thicknessUnion: ', thicknessUnion)
          let decorationTypeUnion: number = this.myDecorationStyle.type
          console.error(' decorationTypeUnion: ', decorationTypeUnion)
          this.thickness += 1
          this.textmodifier.linethickness += 1
          this.textSpanmodifier.linethickness += 1
          if (this.textmodifier.linethickness%2 == 1){
            this.decorationColor = Color.Red
            this.textmodifier.linecolor = Color.Red
            this.decorationDynamic = TextDecorationType.LineThrough
          } else {
            this.decorationColor = Color.Black
            this.textmodifier.linecolor = Color.Black
            this.decorationDynamic = TextDecorationType.LineThrough
          }
          this.mutableStr.replaceStyledString(0, 22, new StyledString('MutableStyledString123', [{
            start: 0,
            length: 3,
            styledKey: StyledStringKey.DECORATION,
            styledValue: new DecorationStyle({type: TextDecorationType.Underline,
              color: Color.Red, thicknessScale: this.thickness})
          }]))
          this.controller.setStyledString(this.mutableStr)
        })
      Button('thickness --')
        .onClick(() => {
          this.thickness -= 1
          this.textmodifier.linethickness -=1
          this.textSpanmodifier.linethickness -= 1
          this.mutableStr.replaceStyledString(0, 22, new StyledString('MutableStyledString123', [{
            start: 0,
            length: 3,
            styledKey: StyledStringKey.DECORATION,
            styledValue: new DecorationStyle({type: TextDecorationType.Underline, thicknessScale: this.thickness})
          }]))
          this.controller.setStyledString(this.mutableStr)
        })
      Button('getDecoration')
        .onClick(() => {
          let strJson = getInspectorByKey('TextDecorationStyleText');
          let decoration:DecorationStyleInterface = JSON.parse(JSON.parse(strJson).$attrs.decoration);
          console.error(' decoration: ', decoration.type)
          console.error(' decoration: ', decoration.color)
          console.error(' decoration: ', decoration.style)
          console.error(' decoration: ', decoration.thicknessScale)

          strJson = getInspectorByKey('spanDeco');
          decoration = JSON.parse(JSON.parse(strJson).$attrs.decoration);
          console.error(' spanDecoration: ', decoration.type)
          console.error(' spanDecoration: ', decoration.color)
          console.error(' spanDecoration: ', decoration.style)
          console.error(' spanDecoration: ', decoration.thicknessScale)

          strJson = getInspectorByKey('crossLineDeco');
          decoration = JSON.parse(JSON.parse(strJson).$attrs.decoration);
          console.error(' spanDecoration: ', decoration.type)
          console.error(' spanDecoration: ', decoration.color)
          console.error(' spanDecoration: ', decoration.style)
          console.error(' spanDecoration: ', decoration.thicknessScale)
        })
    }
  }
}