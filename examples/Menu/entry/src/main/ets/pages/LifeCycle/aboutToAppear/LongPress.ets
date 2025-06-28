// xxx.ets
@Entry
@Component
struct LongPressTest {
  @Builder MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Text('Test menu item 1')
        .fontSize(20)
        .width(200)
        .height(50)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 2')
        .fontSize(20)
        .width(200)
        .height(50)
        .textAlign(TextAlign.Center)
    }.width(200)
  }

  build() {
    Column() {
      Button('长按显示菜单')
    }
    .width('100%')
    .margin({ top: 30 })
    .bindContextMenu(
      this.MenuBuilder,
      ResponseType.LongPress,
      {
        aboutToDisappear: () => {
          console.log('aboutToDisappear Trigger!')
        },
        aboutToAppear: () => {
          console.log('aboutToAppear Trigger!')
        },
        onAppear: () => {
          console.log('onAppear Trigger!')
        },
        onDisappear: () => {
          console.log('onDisappear Trigger!')
        }
      }
    )
  }
}