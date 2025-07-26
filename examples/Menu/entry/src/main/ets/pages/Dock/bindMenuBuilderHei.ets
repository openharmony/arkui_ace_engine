@Entry
@Component
struct bindMenuBuilderHeiExample {

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
      Text('click for Menu').fontSize(25)
    }
    .bindMenu(this.MenuBuilder)
    .width('100%')
    .height('100%')
  }
}