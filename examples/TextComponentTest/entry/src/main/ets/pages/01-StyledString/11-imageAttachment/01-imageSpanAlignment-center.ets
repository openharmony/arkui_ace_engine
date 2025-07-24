// xxx.ets
import { image } from '@kit.ImageKit'
import { LengthMetrics } from '@kit.ArkUI'
import { MeasureText } from '@kit.ArkUI'
import { drawing, common2D, text } from '@kit.ArkGraphics2D';

@Entry
@Component
struct struct_01_StyledString_01_StyledStringValue_11_ImageAttachment_01_imageSpanAlignment_center {
  controller: TextController = new TextController();

  private createCustomSpan(name: string) {
    // 大小
    let fontSize = 30 // fp
    let textSize = MeasureText.measureTextSize({ textContent: name, fontSize: fontSize })
    let paddingLeft = vp2px(8)
    let paddingTop = vp2px(8)
    let width = (textSize.width as number) + paddingLeft * 2;
    let height = (textSize.height as number) + paddingTop * 2;

    // 创建pixelMap
    const color: ArrayBuffer = new ArrayBuffer(width * height * 4); //  为需要创建的像素buffer大小，取值为：height * width *4
    let opts: image.InitializationOptions = { pixelFormat: 3, size: { height: height, width: width } }
    let pixelMap: image.PixelMap = image.createPixelMapSync(color, opts);

    // 绘制背景
    const canvas = new drawing.Canvas(pixelMap);
    const brush = new drawing.Brush();
    const color2: common2D.Color = {
      alpha: 255,
      red: 88,
      green: 0,
      blue: 0
    };
    brush.setColor(color2);
    canvas.attachBrush(brush);
    let rect: common2D.Rect = {
      left: 0,
      top: 0,
      right: width,
      bottom: height
    };
    let roundRect = new drawing.RoundRect(rect, paddingTop, paddingTop); // 自定义 x/y 方向的半径
    canvas.drawRoundRect(roundRect);
    canvas.detachBrush();

    // 绘制文字
    let myTextStyle: text.TextStyle = {
      fontSize: vp2px(fontSize),
    };
    let myParagraphStyle: text.ParagraphStyle = {
      textStyle: myTextStyle,
      align: text.TextAlign.START,
    };
    let fontCollection = new text.FontCollection();
    let paragraphGraphBuilder = new text.ParagraphBuilder(myParagraphStyle, fontCollection);
    paragraphGraphBuilder.addText(name);
    let paragraph = paragraphGraphBuilder.build();
    paragraph.layoutSync(textSize.width as number);
    paragraph.paint(canvas, paddingLeft, paddingTop);

    // 创建ImageAttachment字符串
    let customSpan = new MutableStyledString(new ImageAttachment({
      value: pixelMap,
      size: { width: px2vp(width), height: px2vp(height) },
      layoutStyle: { margin: LengthMetrics.vp(2) }, // 行内margin
      verticalAlign: ImageSpanAlignment.CENTER,
      objectFit: ImageFit.None
    }))
    return customSpan
  }

  async onPageShow() {
    let customSpan = this.createCustomSpan("@小喵吃鱼")
    let message =
      new StyledString('我是只可爱的小猫咪hhh，我每天需要吃很多好吃的，睡很多觉，这是我在论坛发布的探讨问题！')
    customSpan.appendStyledString(message)
    this.controller.setStyledString(customSpan)
  }

  build() {
    Row() {
      Column({ space: 5 }) {
        Text(undefined, { controller: this.controller })
          .copyOption(CopyOptions.InApp)
          .draggable(true)
          .fontSize(30)
          .borderWidth(1)

      }
      .width('100%')
    }
    .height('100%')
  }
}