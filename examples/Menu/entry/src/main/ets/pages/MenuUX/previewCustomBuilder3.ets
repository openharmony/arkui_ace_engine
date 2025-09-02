import UDC from '@ohos.data.unifiedDataChannel';
import UTD from '@ohos.data.uniformTypeDescriptor';

@Entry
@Component
struct previewMenuBuilder3 {
  @State select: boolean = true
  @State imgState: Visibility = Visibility.Visible;
  @State dropText:string | null = null;
  @State textContext :string = 'Text文本132131321321321321231321231231';

  @Builder
  CounterBuilder() {
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
      Text('LongPress preview: CustomBuilder Text文本').margin({ top: 10, bottom: 30 })
      Text('LongPress to show Text').margin(20)
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
      .width('90%')
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