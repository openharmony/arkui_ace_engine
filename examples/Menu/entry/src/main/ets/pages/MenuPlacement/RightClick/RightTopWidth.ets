@Entry
@Component
struct contextMenuRightTop {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
    }.width(100)
  }

  build() {
    Row() {
      Column() {
        Button('菜单宽度为100vp').id('rightTop_Context')
          .width(64)
      }
      .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
        placement: Placement.RightTop
      })
    }.justifyContent(FlexAlign.End)
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Pink)
  }
}
