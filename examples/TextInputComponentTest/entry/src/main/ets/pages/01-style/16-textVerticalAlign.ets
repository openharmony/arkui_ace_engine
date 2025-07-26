import { image } from '@kit.ImageKit'
import { LengthMetrics } from '@kit.ArkUI'

class TextModifier implements AttributeModifier<TextAttribute> {
  public isActive: boolean | undefined = undefined
  applyNormalAttribute(instance: TextAttribute): void {
    instance.textVerticalAlign(TextVerticalAlign.CENTER)
  }
}

@Entry
@Component
struct DragBasePage {
  imagePixelMap: image.PixelMap | undefined = undefined
  uiContext: UIContext = this.getUIContext()

  @State vertical: TextVerticalAlign = TextVerticalAlign.CENTER
  mutableStr: MutableStyledString = new MutableStyledString('属性字符串');

  controller: TextController = new TextController();
  controller1: TextController = new TextController();

  modifier: TextModifier = new TextModifier();

  paragraphStyleAttr: ParagraphStyle = new ParagraphStyle({ textVerticalAlign: TextVerticalAlign.CENTER })

  paragraphStyleString1: StyledString =
    new StyledString('正文第一段落开始0123',[
      {
        start: 0,
        length:12,
        styledKey: StyledStringKey.PARAGRAPH_STYLE,
        styledValue: this.paragraphStyleAttr
      },
      {
        start: 0,
        length:4,
        styledKey: StyledStringKey.FONT,
        styledValue: new TextStyle({fontSize: new LengthMetrics(30)})
      },
      {
        start: 4,
        length:4,
        styledKey: StyledStringKey.FONT,
        styledValue: new TextStyle({fontSize: new LengthMetrics(20)})
      },
      {
        start: 8,
        length:4,
        styledKey: StyledStringKey.FONT,
        styledValue: new TextStyle({fontSize: new LengthMetrics(10)})
      },
    ])


  async aboutToAppear() {
    this.imagePixelMap = await this.getPixmapFromMedia($r('app.media.startIcon'))

    this.mutableStr.insertStyledString(2, new StyledString(new ImageAttachment({
      value:this.imagePixelMap!,
      size: {width: 30, height: 30},
      verticalAlign: ImageSpanAlignment.FOLLOW_PARAGRAPH
    })))

    this.mutableStr.setStyle({
      start: 0,
      length:4,
      styledKey: StyledStringKey.PARAGRAPH_STYLE,
      styledValue: new ParagraphStyle({
        textAlign: TextAlign.Center,
        textVerticalAlign: TextVerticalAlign.CENTER
      })
    });

    this.controller.setStyledString(this.mutableStr)
    this.controller1.setStyledString(this.paragraphStyleString1)
  }

  private async getPixmapFromMedia(resource: Resource) {
    let unit8Array = await this.getUIContext().getHostContext()?.resourceManager?.getMediaContent({
      bundleName: resource.bundleName,
      moduleName: resource.moduleName,
      id: resource.id
    });
    let imageSource = image.createImageSource(unit8Array?.buffer.slice(0, unit8Array.buffer.byteLength));
    let createPixelMap: image.PixelMap = await imageSource.createPixelMap({
      desiredPixelFormat: image.PixelMapFormat.RGBA_8888
    });
    await imageSource.release();
    return createPixelMap;
  }

  build() {
    Scroll() {
      Column({ space: 2 }) {
        Column() {
          Text('规格1: 文本支持内容行内垂直对齐').fontColor(Color.Blue)
          Text('操作步骤：检查第一个字符串')
          Text('Pass条件：文本居中对齐').fontColor(Color.Red)

          Text('规格2: 文本支持图文混排行内垂直对齐').fontColor(Color.Blue)
          Text('操作步骤：检查包含图片的字符串')
          Text('Pass条件：图文居中对齐').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('98%')

        Text(undefined, { controller : this.controller1 })
          .width(300)
          .borderWidth(1)
          .copyOption(CopyOptions.InApp)
          .draggable(true)
          .fontSize(40)

        Text(undefined, { controller : this.controller })
          .width(300)
          .borderWidth(1)
          .copyOption(CopyOptions.InApp)
          .draggable(true)
          .fontSize(40)

        Text(){
          Span('123')
            .fontSize(50)
          ImageSpan($r('app.media.startIcon'))
            .height(30)
            .width(30)
            .verticalAlign(ImageSpanAlignment.FOLLOW_PARAGRAPH)
          Span('使用Text的textVerticalAlign')
        }
          .textVerticalAlign(this.vertical)
          .borderWidth(1)

        Text(){
          Span('123')
            .fontSize(50)
          ImageSpan($r('app.media.startIcon'))
            .height(30)
            .width(30)
            .verticalAlign(ImageSpanAlignment.FOLLOW_PARAGRAPH)
          Span('使用modifier的textVerticalAlign')
        }
        .attributeModifier(this.modifier)
        .borderWidth(1)

        Button('baseline')
          .onClick(()=>{
            this.vertical = TextVerticalAlign.BASELINE
          })

        Button('center')
          .onClick(()=>{
            this.vertical = TextVerticalAlign.CENTER
          })

        Button('bottom')
          .onClick(()=>{
            this.vertical = TextVerticalAlign.BOTTOM
          })

        Button('top')
          .onClick(()=>{
            this.vertical = TextVerticalAlign.TOP
          })
      }
      .height('100%')
      .width('100%')
    }
  }
}