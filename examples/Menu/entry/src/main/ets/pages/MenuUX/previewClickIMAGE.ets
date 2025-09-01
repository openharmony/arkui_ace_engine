@Entry
@Component
struct previewClickIMAGE {
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
        builder: ():void=>this.SubMenu()
      })
    }
  }

  build() {
    Column() {
      Text('RightClick MenuPreviewMode.IMAGE').margin({ top:10,bottom:30 })
      Text('click to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
          preview: MenuPreviewMode.IMAGE
        })
    }
    .width('100%')
    .height('100%')
  }
}