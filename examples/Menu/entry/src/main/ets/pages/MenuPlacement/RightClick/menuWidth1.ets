@Entry
@Component
struct RightClickWidth1 {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
    }.width('30%').height('70%')
  }

  build() {
    Column() {
      Row().width('100%').height('60%')
      Button('弹出菜单')
        .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
          placement: Placement.RightTop
        })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Pink)
  }
}
