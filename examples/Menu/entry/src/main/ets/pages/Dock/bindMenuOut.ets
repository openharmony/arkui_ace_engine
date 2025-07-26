@Entry
@Component
struct bindMenuOutExample {
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
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单6',
        action: () => {
          console.info('handle Menu6 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单7',
        action: () => {
          console.info('handle Menu7 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单8',
        action: () => {
          console.info('handle Menu8 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单9',
        action: () => {
          console.info('handle Menu9 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单10',
        action: () => {
          console.info('handle Menu10 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单11',
        action: () => {
          console.info('handle Menu11 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单12',
        action: () => {
          console.info('handle Menu12 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单13',
        action: () => {
          console.info('handle Menu13 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单14',
        action: () => {
          console.info('handle Menu14 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单15',
        action: () => {
          console.info('handle Menu15 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单16',
        action: () => {
          console.info('handle Menu16 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单17',
        action: () => {
          console.info('handle Menu17 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单18',
        action: () => {
          console.info('handle Menu18 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单19',
        action: () => {
          console.info('handle Menu19 select')
        }
      },
      {
        value: '菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单菜单20',
        action: () => {
          console.info('handle Menu20 select')
        }
      }
    ])
  }
}