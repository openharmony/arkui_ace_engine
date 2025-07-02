import router from '@ohos.router'
import web_webview from '@ohos.web.webview';
@Entry
@Component
struct menuLongPressBindContextMenu {
  @State text: string = ''

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '跳转百度'
      })
        .onClick(() => {
          router.pushUrl({
            url: 'pages/baidu'
          })
        })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '跳转Index'
      })
        .onClick(() => {
          router.pushUrl({ url: 'pages/Index' })
        })
    }
  }

  build() {
    Row(){
      Text(this.text)
      Column() {
        Text('长按展示菜单')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }
      .bindContextMenu(this.MyMenu, ResponseType.LongPress)
    }
    .width('100%')
    .height('100%')
  }
}