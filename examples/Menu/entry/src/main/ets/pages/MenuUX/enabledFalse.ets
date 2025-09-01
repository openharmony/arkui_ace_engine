@Entry
@Component
struct falseEnabled {
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder MenuBuilder(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项',
        builder: ():void=>this.SubMenu()})
        .enabled(false)
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项',
        builder: ():void=>this.SubMenu()})
        .enabled(false)
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单选项',
        builder: ():void=>this.SubMenu()})
        .enabled(false)
    }
  }
  build() {
    Column(){
      Text('enabled 设置为false')

      Column() {
        Text('click for bindMenu')
          .fontSize(25).margin(30)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
      .margin({ top: 5 })
      .bindMenu([
        {
          value: 'Menu1',
          enabled: false,
          action: () => {
            console.info('handle Menu1 select')
          }
        },
        {
          value: 'Menu2',
          enabled:false,
          action: () => {
            console.info('handle Menu2 select')
          }
        },
      ])

      Column() {
        Text('click for Menu')
          .fontSize(25).margin(30)
          .fontWeight(FontWeight.Bold)
      }
      .width('100%')
      .margin({ top: 5 })
      .bindMenu(this.MenuBuilder())
    }

  }
}