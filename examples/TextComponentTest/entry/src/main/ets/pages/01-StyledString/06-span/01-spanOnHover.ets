import { pointer } from '@kit.InputKit'

class SpanModifier implements AttributeModifier<SpanAttribute> {
  public uiContext: UIContext | undefined;
  applyNormalAttribute(instance: SpanAttribute): void {
    instance.onHover((isHover: boolean, event: HoverEvent)=>{
      if (isHover) {
        this.uiContext?.getCursorController().setCursor(pointer.PointerStyle.HAND_POINTING);
        console.log('Modifier +++ Hover')
      } else {
        this.uiContext?.getCursorController().restoreDefault();
        console.log('Modifier +++ No Hover')
      }
    })
  }
}

@Entry
@Component
struct SpanOnHoverPage {
  @State message: string = 'Hello World';
  @State color: Color | string = Color.Transparent;
  @State color2: Color | string = Color.Transparent;
  modifier: SpanModifier = new SpanModifier();

  aboutToAppear(): void {
    this.modifier.uiContext = this.getUIContext()
  }

  build() {
    Scroll() {
      Column({ space: 2 }) {
        Column() {
          Text('规格1: Span支持OnHover事件').fontColor(Color.Blue)
          Text('操作步骤：移动鼠标至蓝色"123"字符上')
          Text('Pass条件：鼠标变为小手形状').fontColor(Color.Red)

          Text('规格2: Span支持Modifier设置OnHover事件').fontColor(Color.Blue)
          Text('操作步骤：移动鼠标至红色"+++"字符上')
          Text('Pass条件：鼠标变为小手形状').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('98%')

        Text() {
          Span('ABC')
          Span('123')
            .fontColor(Color.Blue)
            .textBackgroundStyle({
              color: this.color
            })
            .onHover((isHover: boolean, event: HoverEvent)=>{
              if(isHover) {
                this.message = '123 Hover x:' + event.x;
                this.getUIContext().getCursorController().setCursor(pointer.PointerStyle.HAND_POINTING);
                this.color = '#20647985';
              } else {
                this.message = '123 No Hover x:' + event.x;
                this.getUIContext().getCursorController().restoreDefault();
                this.color = Color.Transparent;
              }
              console.log(this.message)
            })
            .onClick((event:ClickEvent)=>{
              console.log('click x:' + event.x)
            })
          Span('XXX')
            .fontColor(Color.Green)
            .textBackgroundStyle({
              color: this.color2
            })
            .onHover((isHover: boolean, event: HoverEvent)=>{
              if(isHover) {
                this.message = 'XXX Hover x:' + event.x;
                this.getUIContext().getCursorController().setCursor(pointer.PointerStyle.HAND_POINTING);
                this.color2 = '#20647985';
              } else {
                this.message = 'XXX No Hover x:' + event.x;
                this.getUIContext().getCursorController().restoreDefault();
                this.color2 = Color.Transparent;
              }
            })
          Span('+++')
            .fontColor(Color.Red)
            .attributeModifier(this.modifier)
          Span('DEF')
        }
        .fontSize(30)

        Text('普通文本')
          .fontSize(30)
          .margin(10)
          .onHover((isHover: boolean, event: HoverEvent)=>{
            if(isHover) {
              this.message = 'Normal Text Hover x:' + event.x;
              this.getUIContext().getCursorController().setCursor(pointer.PointerStyle.HAND_POINTING);
            } else {
              this.message = 'Normal Text Hover x:' + event.x;
              this.getUIContext().getCursorController().restoreDefault();
            }
          })
      }
      .height('100%')
      .width('100%')
    }
  }
}