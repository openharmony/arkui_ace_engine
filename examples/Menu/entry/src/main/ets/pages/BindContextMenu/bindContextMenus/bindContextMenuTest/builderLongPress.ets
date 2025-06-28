import router from '@ohos.router'
import web_webview from '@ohos.web.webview';

@Entry
@Component
struct BuilderLongPressBindContextMenu {

  @Builder
  SubMenu(){
    Menu() {
      MenuItem({ content: '跳转百度' })
        .onClick(() => {
          router.pushUrl({
            url: 'pages/baidu'
          })
        })
      MenuItem({ content: '跳转Index' })
        .onClick(() => {
          router.pushUrl({
            url:  'pages/Index',
          })
        })
    }
  }

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '菜单',
        builder: ():void=>this.SubMenu()
        // builder: this.SubMenu.bind(this)
      })

    }
  }

  build() {
    Row(){
      Column() {
        Text('长按显示菜单')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }
      .bindContextMenu(this.MyMenu, ResponseType.LongPress)
    }
    .width('100%')
    .height('100%')
  }
}