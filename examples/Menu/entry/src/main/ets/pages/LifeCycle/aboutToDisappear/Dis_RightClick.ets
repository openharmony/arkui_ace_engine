// xxx.ets
@Entry
@Component
struct Dis_RightClickTest {
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
      Button('右击显示菜单')
    }
    .width('100%')
    .margin({ top: 30 })
    .bindContextMenu(
      this.MenuBuilder,
      ResponseType.RightClick,
      {
        aboutToAppear: () => {
          console.log('aboutToAppear Trigger!')
        },
        aboutToDisappear: () => {
          console.log('aboutToDisappear Trigger!')
        }
      }
    )
  }
}