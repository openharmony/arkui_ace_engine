@Entry
@Component
struct IconTextAlign_dynamicIcon {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ content: '菜单选项1', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '菜单选项2', startIcon: $r('app.media.app_icon') })
      MenuItem({ content: '菜单选项3', endIcon: $r('app.media.app_icon') })
      MenuItem({ content: '菜单选项4', endIcon: $r('app.media.app_icon') })
      MenuItem({ content: '菜单选项5', endIcon: $r('app.media.app_icon') })
    }
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