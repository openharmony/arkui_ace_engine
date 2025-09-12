@Entry
@Component
struct MenuFont_ContentFontSize_10 {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1', endIcon: $r('app.media.app_icon') }).contentFont({ size: 10 })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2', endIcon: $r('app.media.app_icon') }).contentFont({ size: 10 })
      MenuItemGroup() {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项3', endIcon: $r('app.media.app_icon') }).contentFont({ size: 10 })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项4', endIcon: $r('app.media.app_icon') }).contentFont({ size: 10 })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项5', endIcon: $r('app.media.app_icon') }).contentFont({ size: 10 })
      }
    }.width('100%')
  }
  build() {
    Row() {
      Text('点击展示菜单')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
    }
    .bindMenu(this.MyMenu)
  }
}