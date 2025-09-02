import UDC from '@ohos.data.unifiedDataChannel';
import UTD from '@ohos.data.uniformTypeDescriptor';

@Entry
@Component
struct buttonMenuExample {
  @State select: boolean = true
  @State imgState: Visibility = Visibility.Visible;
  @State dropText:string | null = null;
  @State textContext :string = 'Text文本132131321321321321231321231231';

  @Builder
  CounterBuilder() {
    Column() {
      Button('menu')
        .bindContextMenu(this.MenuBuilder,ResponseType.LongPress,)
      Text(this.textContext)
        .copyOption(CopyOptions.InApp)
        .textAlign(TextAlign.Center)
        .onDragStart((event)=>{
          let text: UDC.PlainText = new UDC.PlainText;
          text.textContent = this.textContext;
          let data: UDC.UnifiedData = new UDC.UnifiedData(text);
          (event as DragEvent).setData(data);
          console.log('ets:in start')
        })
        .border({ width: 1 })
        .padding(10)
        .bindContextMenu(this.MenuBuilder,ResponseType.LongPress,)

    }
    .height(300)
    .draggable(true)
    .borderWidth(2)
    .onDragStart((event) => {
    })
    .margin(20)
    .border({ width: 1 })
  }

  @Builder
  MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
        .enabled(false)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        builder: (): void => this.CounterBuilder()
      })
    }
  }

  build() {
    Column() {
      Text('button绑定menu 自定义组件、text文本可拖拽').margin({ top: 10, bottom: 30 })
      Button('LongPress for menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .draggable(true)
        .onDragStart((event) => {
          let text: UDC.PlainText = new UDC.PlainText;
          text.textContent = 'hello world'
          let data: UDC.UnifiedData = new UDC.UnifiedData(text);
          (event as DragEvent).setData(data);
        })
        .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
          preview: this.CounterBuilder
        })
      Text('文本释放区域')
        .fontSize('15dp')
        .height('30%')
      Column() {
        if (this.dropText == null) {
          Text('Text drop').fontSize(20)
        } else {
          Text(this.dropText).fontSize(20)
        }
      }
      .border({width: 1})
      .height('90%')
      .width('100%')
      .allowDrop([UTD.UniformDataType.PLAIN_TEXT])
      .onDrop((event) => {
        console.log('ets:in drop')
        let records: Array<UDC.UnifiedRecord> = event.getData().getRecords();
        let text: UDC.PlainText =  records[0] as UDC.PlainText;
        this.dropText = text.textContent
      })
    }
    .draggable(true)
    .width('100%')
    .height('100%')
  }
}