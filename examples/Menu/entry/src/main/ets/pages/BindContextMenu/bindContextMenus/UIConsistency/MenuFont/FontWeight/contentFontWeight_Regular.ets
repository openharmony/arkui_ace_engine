import { Size } from '@ohos/hypium'
@Entry
@Component
struct MenuFont_ContentFontWeight_Regular {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项1', endIcon: $r('app.media.app_icon') }).contentFont({ weight: FontWeight.Regular })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项2', endIcon: $r('app.media.app_icon') }).contentFont({ weight: FontWeight.Regular })
      MenuItemGroup() {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项3', endIcon: $r('app.media.app_icon') }).contentFont({ weight: FontWeight.Regular })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项4', endIcon: $r('app.media.app_icon') }).contentFont({ weight: FontWeight.Regular })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项5', endIcon: $r('app.media.app_icon') }).contentFont({ weight: FontWeight.Regular })
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项6', endIcon: $r('app.media.app_icon') }).contentFont({ weight: FontWeight.Regular })
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