@Entry
@Component
struct ContextMenuHeiExample {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单1' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单2' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单3' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单4' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单5' })
    }
  }

  build() {
    Column() {
      Text('RightClick for menu').fontSize(25)
    }
    .bindContextMenu(this.MenuBuilder, ResponseType.RightClick)
    .width('100%')
    .height('100%')
  }
}