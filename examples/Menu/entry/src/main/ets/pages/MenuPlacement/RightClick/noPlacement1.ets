@Entry
@Component
struct contextNoPlacement1 {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
    }.width(48)
  }

  build() {
    Row() {
      Column() {
        Button('菜单宽度为48vp')
          .width(64)
      }
      .bindContextMenu(this.MenuBuilder, ResponseType.RightClick )

    }.justifyContent(FlexAlign.End)
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Pink)
  }
}
