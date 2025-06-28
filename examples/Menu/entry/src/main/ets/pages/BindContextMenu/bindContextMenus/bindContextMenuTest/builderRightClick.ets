import router from '@ohos.router'
@Entry
@Component
struct BuilderRightClickBindContextMenu {

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
      })
    }
  }

  build() {
    Row(){
      Column() {
        Text('右击展示菜单')
          .fontSize(30)
          .fontWeight(FontWeight.Bold)
      }
      .bindContextMenu(this.MyMenu, ResponseType.RightClick)
    }
    .width('100%')
    .height('100%')
  }
}