@Entry
@Component
struct MenuStyle_titleIcon {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1', endIcon: $r('app.media.app_icon') })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2', endIcon: $r('app.media.app_icon') })
      MenuItemGroup({ header: '标题头', footer: '标题尾' }) {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项3', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项4', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项5', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项6', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项7', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项8', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项9', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项10', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项11', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项12', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项13', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项14', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项15', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项16', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项17', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项18', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项19', endIcon: $r('app.media.app_icon') })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项20', endIcon: $r('app.media.app_icon') })
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