@Entry
@Component
struct previewMenuBuilder2 {
  @State select: boolean = true
  @State text: string = ''

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: 'menu1'})
      MenuItem({ content: 'menu2'})
    }
  }

  @Builder btnBuilder(){
    Button('click to show menu')
      .onKeyEvent((event: KeyEvent) => {
        this.text = 'onKeyEvent 被触发'
      })
      .bindMenu(this.SubMenu())
  }

  @Builder
  MyMenu(){
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单1'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单2'})
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单3'})
    }
  }

  build() {
    Column() {
      Text('preview: CustomBuilder 按键').margin({ top:10,bottom:30 })
      Text('LongPress to show Button' + this.text)
        .fontSize(30)
        .fontWeight(FontWeight.Bold)
        .bindContextMenu(this.MyMenu, ResponseType.LongPress, {
          preview: this.btnBuilder
        })
    }
    .width('100%')

    .height('100%')
  }
}