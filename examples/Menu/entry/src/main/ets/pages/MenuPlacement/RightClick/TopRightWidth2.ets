@Entry
@Component
struct contextMenuTopRight2 {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
    }.width(64)
  }

  build() {
    Row() {
      Column() {
        Button('菜单宽度为64vp').id('topRight_Context_2')
          .width(64)
      }
      .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
        placement: Placement.TopRight
      })
    }.justifyContent(FlexAlign.End)
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Pink)
  }
}
