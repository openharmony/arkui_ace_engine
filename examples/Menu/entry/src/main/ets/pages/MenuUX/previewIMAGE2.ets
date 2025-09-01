@Entry
@Component
struct previewIMAGE2 {
  @State select: boolean = true

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder MenuBuilder(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项'})
        .enabled(false)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu()
      })
    }
  }

  build() {
    Column() {
      Text('MenuPreviewMode.IMAGE enableArrow为false').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
          enableArrow: false,
          preview: MenuPreviewMode.IMAGE
        })
    }
    .width('100%')
    .height('100%')
  }
}