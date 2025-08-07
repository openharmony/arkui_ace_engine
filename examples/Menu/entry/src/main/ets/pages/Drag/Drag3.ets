// xxx.ets
@Entry
@Component
struct Drag3 {
  private iconStr: ResourceStr = $r('app.media.app_icon')

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
      MenuItem({ startIcon: this.iconStr, content: '菜单选项' })
    }
  }
  @Builder
  PreviewImage() {
    Text('CustomBuilderText')
      .width(200)
      .height(100)
      .backgroundColor('#e23c2f')
  }

  build() {
    Column({ space: 50 }) {
      Column() {
        Column() {
          Button('preview-image')
            .draggable(true)
            .onDragStart((event)=>{
            })
            .width(200)
            .height(100)
            .margin(100)
            .fontSize(30)
            .bindContextMenu(this.MyMenu, ResponseType.LongPress,
              { preview: this.PreviewImage(),
                previewAnimationOptions: {scale: [0.8, 1.0]},
              })
            .backgroundColor('#ff3df2f5')
        }
      }.width('100%')
    }
  }
}