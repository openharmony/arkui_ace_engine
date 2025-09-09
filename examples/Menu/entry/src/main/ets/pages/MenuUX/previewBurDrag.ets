import UDC from '@ohos.data.unifiedDataChannel';
import UTD from '@ohos.data.uniformTypeDescriptor';
@Entry
@Component
struct previewBuilderDrag {
  @State select: boolean = true

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ content: '菜单1'})
      MenuItem({ content: '菜单2'})
      MenuItem({ content: '菜单3'})
    }
  }

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
      Text('preview为CustomBuilder 拖拽').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .draggable(true)
        .visibility(Visibility.Visible)
        .onDragStart((event)=>{
          let text: UDC.PlainText = new UDC.PlainText;
          let data: UDC.UnifiedData = new UDC.UnifiedData(text);
          (event as DragEvent).setData(data);
        })
        .bindContextMenu(this.MyMenu, ResponseType.LongPress, {
          preview: this.MenuBuilder
        })
    }
    .width('100%')
    .height('100%')
  }
}