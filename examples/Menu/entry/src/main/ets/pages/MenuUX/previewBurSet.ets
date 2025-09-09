@Entry
@Component
struct previewBuilderSelected {
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
      Text('preview为CustomBuilder Text文本选中').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .copyOption(CopyOptions.InApp)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MyMenu, ResponseType.LongPress, {
          preview: this.MenuBuilder
        })
    }
    .width('100%')
    .height('100%')
  }
}