@Entry
@Component
struct contextNoPlacement3 {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
    }
  }

  build() {
    Row() {
      Column() {
        Button('菜单宽度不设置')
          .width(64)
      }
      .bindContextMenu(this.MenuBuilder, ResponseType.RightClick )

    }.justifyContent(FlexAlign.End)
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Pink)
  }
}
