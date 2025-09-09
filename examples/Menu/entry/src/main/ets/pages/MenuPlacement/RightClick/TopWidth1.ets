@Entry
@Component
struct contextMenuTop1 {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单' })
    }.width(48)
  }

  build() {
    Row() {
      Column() {
        Button('菜单宽度为48vp').id('top_Context_1')
          .width(64)
      }
      .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
        placement: Placement.Top
      })
    }.justifyContent(FlexAlign.End)
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Pink)
  }
}
