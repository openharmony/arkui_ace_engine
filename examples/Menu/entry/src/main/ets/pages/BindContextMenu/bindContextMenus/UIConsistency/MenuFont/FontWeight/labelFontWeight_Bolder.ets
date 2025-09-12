@Entry
@Component
struct MenuFont_LabelFontWeight_Bolder {
  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签介绍1', endIcon: $r('app.media.app_icon') }).labelFont({ weight: FontWeight.Bolder })
      MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签介绍2', endIcon: $r('app.media.app_icon') }).labelFont({ weight: FontWeight.Bolder })
      MenuItemGroup() {
        MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签介绍3', endIcon: $r('app.media.app_icon') }).labelFont({ weight: FontWeight.Bolder })
        MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签介绍4', endIcon: $r('app.media.app_icon') }).labelFont({ weight: FontWeight.Bolder })
        MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签介绍5', endIcon: $r('app.media.app_icon') }).labelFont({ weight: FontWeight.Bolder })
        MenuItem({ startIcon: $r('app.media.app_icon'), labelInfo: '标签介绍6', endIcon: $r('app.media.app_icon') }).labelFont({ weight: FontWeight.Bolder })
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