class MySwitchStyle implements ContentModifier<ToggleConfiguration> {
  constructor() {
  }
  applyContent(): WrappedBuilder<[ToggleConfiguration]> {
    return wrapBuilder(buildSwitch);
  }
}


@Builder
function buildSwitch(config: ToggleConfiguration) {
  Column({ space: 50 }) {
    Stack() {
      if (config.isOn) {
        // 开启状态 (正面)
        Column() {
          Text('Sun raise')
            .fontSize(16)
            .fontColor('#FF2D55')
        }
        .justifyContent(FlexAlign.Center)
        .width(120)
        .height(120)
        .backgroundColor('#ffffff')
        .border({
          width: 2,
          color: '#FF2D55'
        })
        .borderRadius(60)
      } else {
        // 关闭状态 (背面)
        Column() {
          Text('Moon raise')
            .fontSize(16)
            .fontColor('#00F0FF')
        }
        .justifyContent(FlexAlign.Center)
        .width(120)
        .height(120)
        .backgroundColor('#1A1A1A')
        .border({
          width: 2,
          color: '#00F0FF'
        })
        .borderRadius(60)

      }
    }
    .width(120)
    .height(120)
    .margin({ top: 30 })

    Row() {
      Button('Sun raise')
        .onClick(() => {
          config.triggerChange(true);
        })

      Button('Moon raise')
        .onClick(() => {
          config.triggerChange(false);
        })
    }
  }
}

@Builder
export function ToggleContentModifierBuilder(name: string, param: Object) {
  toggleContentModifier()
}

@Component
struct toggleContentModifier {
  pathStack: NavPathStack = new NavPathStack()

  build() {
    NavDestination() {
      Column({ space: 50 }) {
        Toggle({ type: ToggleType.Switch })
          .enabled(true)
          .contentModifier(new MySwitchStyle())
          .onChange((isOn: boolean) => {
            console.info('Switch Log:' + isOn);
          })
      }.height('100%').width('100%')
    }
    .title('toggle弹窗确认场景')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}