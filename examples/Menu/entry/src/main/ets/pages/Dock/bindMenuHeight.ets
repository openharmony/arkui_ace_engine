@Entry
@Component
struct bindMenuHeight {
  build() {
    Column() {
      Text('click for Menu').fontSize(25)
    }
    .width('100%')
    .height('100%')
    .bindMenu([
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单1',
        action: () => {
          console.info('handle Menu1 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单2',
        action: () => {
          console.info('handle Menu2 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单3',
        action: () => {
          console.info('handle Menu3 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单4',
        action: () => {
          console.info('handle Menu4 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单5',
        action: () => {
          console.info('handle Menu5 select')
        }
      }
    ])
  }
}