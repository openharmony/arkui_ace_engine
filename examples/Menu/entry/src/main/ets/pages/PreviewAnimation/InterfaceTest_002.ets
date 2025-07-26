@Entry
@Component
struct InterfaceTest_002 {
  private iconStr: ResourceStr = $r('app.media.app_icon')

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
    }
  }

  build() {
    Column({ space: 50 }) {
      Column() {
        Column() {
          Button('preview-image')
            .width(200)
            .height(100)
            .margin(100)
            .fontSize(30)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              { preview: MenuPreviewMode.IMAGE, previewAnimationOptions: {scale: [2.0, 0.5] }})
            .backgroundColor('#ff3df2f5')

        }
      }.width('100%')
    }
  }
}