@Entry
@Component
struct MenuFont_FontColor_04 {
  @Builder
  MyMenu(){
    Menu() {
      // yellow
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1', endIcon: $r('app.media.app_icon') }).contentFontColor(0xffff00)
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2', endIcon: $r('app.media.app_icon') }).contentFontColor(0xffff00)
      MenuItemGroup({ header: '二级标题' }) {
        // pink
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项3', labelInfo: '标签介绍1', endIcon: $r('app.media.app_icon') }).labelFontColor(0xffc0cb)
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项4', labelInfo: '标签介绍2', endIcon: $r('app.media.app_icon') }).labelFontColor(0xffc0cb)
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项5', labelInfo: '标签介绍3', endIcon: $r('app.media.app_icon') }).labelFontColor(0xffc0cb)
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