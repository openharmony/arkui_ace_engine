@Entry
@Component
struct previewIMAGESelected {
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
      Text('MenuPreviewMode.IMAGE Text文本选中').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .copyOption(CopyOptions.LocalDevice)
        .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
          preview: MenuPreviewMode.IMAGE
        })
    }
    .width('100%')
    .height('100%')
  }
}