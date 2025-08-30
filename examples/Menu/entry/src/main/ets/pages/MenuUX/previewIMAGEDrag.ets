import UDC from '@ohos.data.unifiedDataChannel';
import UTD from '@ohos.data.uniformTypeDescriptor';
@Entry
@Component
struct previewIMAGE3 {
  @State select: boolean = true
  @State imgState: Visibility = Visibility.Visible;

  @Builder MenuBuilder(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2'})
        .enabled(false)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项3'
      })
    }
  }

  build() {
    Column() {
      Text('MenuPreviewMode.IMAGE 拖拽').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .draggable(true)
        .onDragStart((event)=>{
          let text: UDC.PlainText = new UDC.PlainText;
          let data: UDC.UnifiedData = new UDC.UnifiedData(text);
          (event as DragEvent).setData(data);
          console.log('ets:in start')
        })
        .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
          preview: MenuPreviewMode.IMAGE
        })
    }
    .width('100%')
    .height('100%')
  }
}