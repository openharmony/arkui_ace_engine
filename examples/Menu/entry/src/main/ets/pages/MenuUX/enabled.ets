@Entry
@Component
struct bindMenuEnabled {
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder MenuBuilder(){
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        builder: ():void=>this.SubMenu()})
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        builder: ():void=>this.SubMenu()})
        .enabled(true)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        builder: ():void=>this.SubMenu()})
        .enabled(false)
    }
  }
  build() {
    Column(){
      Text('enabled 不设置 true false').margin({ top:10,bottom:30 })
      Column() {
        Text('click for Menu')
          .fontSize(25).margin(30)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
      .bindMenu(this.MenuBuilder())
    }
  }
}