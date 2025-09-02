@Entry
@Component
struct previewNONE {
  @State select: boolean = true

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制'})
      MenuItem({ content: '粘贴'})
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
      Text('LongPress MenuPreviewMode.NONE').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MenuBuilder, ResponseType.LongPress, {
          enableArrow: true,
          preview: MenuPreviewMode.NONE
        })
    }
    .width('100%')

    .height('100%')
  }
}