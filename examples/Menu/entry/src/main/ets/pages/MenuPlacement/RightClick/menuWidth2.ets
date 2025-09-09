@Entry
@Component
struct RightClickWidth2 {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
    }.width('30%')
  }

  build() {
    Row() {
      Column() {
        Button('弹出菜单')
          .width(64)
      }
      .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
        placement: Placement.Right
      })
    }.justifyContent(FlexAlign.End)
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Pink)
  }
}
