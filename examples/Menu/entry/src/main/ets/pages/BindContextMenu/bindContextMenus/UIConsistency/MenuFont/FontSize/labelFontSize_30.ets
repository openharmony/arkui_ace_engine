@Entry
@Component
struct MenuFont_LabelFontSize_30 {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签选项1', endIcon: $r('app.media.app_icon') }).labelFont({ size: 30 })
      MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签选项2', endIcon: $r('app.media.app_icon') }).labelFont({ size: 30 })
      MenuItemGroup() {
        MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签选项3', endIcon: $r('app.media.app_icon') }).labelFont({ size: 30 })
        MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签选项4', endIcon: $r('app.media.app_icon') }).labelFont({ size: 30 })
        MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签选项5', endIcon: $r('app.media.app_icon') }).labelFont({ size: 30 })
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