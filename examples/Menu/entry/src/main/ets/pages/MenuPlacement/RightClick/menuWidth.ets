@Entry
@Component
struct RightClickWidth {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
    }.width('20%').height('50%')
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
