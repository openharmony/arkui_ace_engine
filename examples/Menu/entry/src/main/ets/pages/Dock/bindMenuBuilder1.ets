@Entry
@Component
struct bindMenuBuilderExample {

  @Builder MenuBuilder() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单1' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单2' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单3' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单4' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单5' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单6' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单7' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单8' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单9' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单10' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单11' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单12' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单13' })
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