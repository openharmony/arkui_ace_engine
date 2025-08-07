// xxx.ets
@Entry
@Component
struct BindMenuTest {
  build() {
    Column() {
      Button('点击显示菜单')
    }
    .width('100%')
    .margin({ top: 30 })
    .bindMenu(
      [
        {
          value: 'Menu1',
          action: () => {
            console.info('handle Menu1 select')
          }
        },
        {
          value: 'Menu2',
          action: () => {
            console.info('handle Menu2 select')
          }
        },
      ],
      {
        onAppear: () => {
          console.log('onAppear Trigger!')
        },
        aboutToAppear: () => {
          console.log('aboutToAppear Trigger!')
        },
        onDisappear: () => {
          console.log('onDisappear Trigger!')
        },
        aboutToDisappear: () =>{
          console.log('aboutToDisappear Trigger!')
        }
      }
    )
  }
}