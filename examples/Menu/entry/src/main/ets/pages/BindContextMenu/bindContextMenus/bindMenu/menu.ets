import router from '@ohos.router'
@Entry
@Component
struct menuBindMenu {

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '跳转百度'
      })
        .onClick(() => {
          router.pushUrl({
            url: 'pages/baidu',
          })
        })

      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '跳转Index'
      })
        .onClick(() => {
          router.pushUrl({
            url: 'pages/Index',
          })
        })
    }
  }

  build() {
    Row(){
      Column() {
        Text('单击展示菜单')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }
      .bindMenu(this.MyMenu)
    }
    .width('100%')
    .height('100%')
  }
}