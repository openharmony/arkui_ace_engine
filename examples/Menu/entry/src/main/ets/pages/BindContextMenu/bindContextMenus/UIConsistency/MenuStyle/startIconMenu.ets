@Entry
@Component
struct MenuStyle_startIcon {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项3' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项4' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项5' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项6' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项7' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项8' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项9' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项10' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项11' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项12' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项13' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项14' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项15' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项16' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项17' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项18' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项19' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项20' })
    }
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