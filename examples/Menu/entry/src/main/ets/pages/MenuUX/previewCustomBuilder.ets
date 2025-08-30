@Entry
@Component
struct previewMenuBuilder {
  @State select: boolean = true

  @Builder MenuBuilder(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2'})
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项3'
      })
    }
  }

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ content: '菜单1'})
      MenuItem({ content: '菜单2'})
      MenuItem({ content: '菜单3'})
    }
  }

  build() {
    Column() {
      Text('LongPress preview: CustomBuilder menu').margin({ top:10,bottom:30 })
      Text('LongPress to show menu')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MyMenu, ResponseType.LongPress, {
          preview: this.MenuBuilder
        })
    }
    .width('100%')

    .height('100%')
  }
}