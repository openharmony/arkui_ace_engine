@Entry
@Component
struct SettingIcons_startDynamicIcon {
  @State select: boolean = true
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ content: '菜单选项1', startIcon: $r('app.media.app_icon') }).selectIcon(true).selected(this.select)
      MenuItem({ content: '菜单选项2', startIcon: $r('app.media.app_icon') }).selectIcon(true).selected(this.select)
      MenuItem({ content: '菜单选项3', startIcon: $r('app.media.app_icon') }).selectIcon(true).selected(this.select)
      MenuItem({ content: '菜单选项4', startIcon: $r('app.media.app_icon') }).selectIcon(true).selected(this.select)
      MenuItem({ content: '菜单选项5', startIcon: $r('app.media.app_icon') }).selectIcon(true).selected(this.select)
    }.width('100%')
  }
  build() {
    Row() {
      Text('点击展示菜单')
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
      Text('查看动态图标是否显示')
        .fontSize(14)
        .fontColor('blue')
    }
    .bindMenu(this.MyMenu)
  }
}