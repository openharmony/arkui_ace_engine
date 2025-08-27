@Entry
@Component
struct bindMenuBuilderSubExample {

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '子菜单1' })
      MenuItem({ content: '子菜单2' })
      MenuItem({ content: '子菜单3' })
      MenuItem({ content: '子菜单4' })
      MenuItem({ content: '子菜单5' })
      MenuItem({ content: '子菜单6' })
      MenuItem({ content: '子菜单7' })
      MenuItem({ content: '子菜单8' })
      MenuItem({ content: '子菜单9' })
      MenuItem({ content: '子菜单10' })
      MenuItem({ content: '子菜单11' })
      MenuItem({ content: '子菜单12' })
      MenuItem({ content: '子菜单13' })
      MenuItem({ content: '子菜单14' })
      MenuItem({ content: '子菜单15' })
      MenuItem({ content: '子菜单16' })
      MenuItem({ content: '子菜单17' })
      MenuItem({ content: '子菜单18' })
      MenuItem({ content: '子菜单19' })
      MenuItem({ content: '子菜单20' })
    }
  }

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu1',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu2',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu3',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu4',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu5' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu6' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu7',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu8' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu9' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu10',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu11' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu12' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu13',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu14' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu15' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu16',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu17' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu18' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu19' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: 'Menu20',
        endIcon: $r('app.media.app_icon'),
        builder: ():void=>this.SubMenu() })
    }
  }

  build() {
    Column() {
      Text('click for Menu').fontSize(25)
    }
    .bindMenu(this.MyMenu)
    .width('100%')
    .height('100%')
  }
}