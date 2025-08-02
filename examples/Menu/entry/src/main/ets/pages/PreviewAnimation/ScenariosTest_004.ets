@Entry
@Component
struct ScenariosTest_004 {
  private iconStr: ResourceStr = $r('app.media.app_icon')

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '横竖屏切换' })
      MenuItem({ startIcon: this.iconStr, content: '横竖屏切换' })
      MenuItem({ startIcon: this.iconStr, content: '横竖屏切换' })
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
              { preview: MenuPreviewMode.IMAGE, previewAnimationOptions: {scale: [1.0, 2.0] }})
            .backgroundColor('#ff3df2f5')

        }
      }.width('100%')
    }
  }
}