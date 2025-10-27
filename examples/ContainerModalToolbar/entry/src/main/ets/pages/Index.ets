import common from '@ohos.app.ability.common';
import window from '@ohos.window';
import {
  SegmentButton,
  SegmentButtonOptions,
  SegmentButtonTextItem,
  ItemRestriction,
  SegmentButtonItemTuple
} from '@ohos.arkui.advanced.SegmentButton';
import { LengthMetrics, SymbolGlyphModifier } from '@kit.ArkUI';
import { BusinessError } from '@kit.BasicServicesKit';

@Entry
@Component
struct ToolbarExample {
  @State showSideBar: boolean = true;
  @State showNavbar: boolean = false;
  @State showNavbarItem: boolean = false;
  @State showText: boolean = false;
  @State showText30: boolean = false;
  @State showText60: boolean = false;
  @State showText90: boolean = false;
  @State mycolor: Color = Color.Blue;
  @State color: Color = Color.Blue;
  @State toolbarIsUndefine: boolean = true;
  @State toolbarIsNull: boolean = true;

  private changeOrientation(isLandscape: boolean) {
    let context = getContext(this) as common.UIAbilityContext;
    window.getLastWindow(context).then((lastWindow) => {
      lastWindow.setPreferredOrientation(isLandscape ? window.Orientation.LANDSCAPE : window.Orientation.PORTRAIT)
    });
  }

  normalIcon: Resource = $r('app.media.startIcon')
  selectedIcon: Resource = $r('app.media.startIcon')
  @State arr: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23]
  @State current: number = 1
  @Provide('navPathStack') navPathStack: NavPathStack = new NavPathStack();
  @State tabOptions: SegmentButtonOptions = SegmentButtonOptions.tab({
    buttons: [{ text: '页签1' }, { text: '页签2' }, {
      text: '页签3'
    }] as ItemRestriction<SegmentButtonTextItem>,
    backgroundBlurStyle: BlurStyle.BACKGROUND_THICK
  })
  @State tabSelectedIndexes: number[] = [1]

  @Builder
  MyToolbar() {
    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_LEADING }) {
      Row() {
        Image($r('app.media.startIcon'))
          .width('40vp')
          .height('40vp')
          .onClick(() => {
            if (this.showSideBar) {
              this.showSideBar = false
            } else {
              this.showSideBar = true
            }
          })
        if (!this.showSideBar) {
          Text('收件箱')
            .fontSize('32vp')
            .fontWeight(2)
        }
      }
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_LEADING }) {
      Button('左1')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('30vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Button('右1')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('30vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Button('右2')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('30vp')
    }

  }

  @Builder
  MyToolbarB() {
    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Button('END')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('40vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Button('END')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('40vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Button('END')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('40vp')
    }

  }

  @Builder
  MyToolbar2() {
    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_LEADING }) {
      Button('左1')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('30vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_LEADING }) {
      Button('左2')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('30vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Search()
        .width('120vp')
        .height('30vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Row({ space: 5 }) {
        Image($r('app.media.startIcon'))
          .width('40vp')
          .height('40vp')
          .onClick(() => {
          })
        Image($r('app.media.startIcon'))
          .width('40vp')
          .height('40vp')
          .onClick(() => {
          })
      }
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Slider()
        .width('120vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      SegmentButton({
        options: this.tabOptions,
        selectedIndexes: $tabSelectedIndexes
      })
        .width('200vp')
    }

    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Button('END')
        .backgroundColor(this.mycolor)
        .onClick(() => {
          this.mycolor = Color.Green;
        })
        .height('30vp')
    }

  }

  @Builder
  MyToolbar3() {
    ToolBarItem({}) {
      Button('未设置位置')
    }
  }

  @Builder
  MyToolbar30() {
    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_LEADING }) {
      Text('56VP')
        .backgroundColor(Color.Green)
        .height('30vp')
    }
  }

  @Builder
  MyToolbar60() {
    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_LEADING }) {
      Text('64VP')
        .backgroundColor(Color.Green)
        .height('60vp')
    }
  }

  @Builder
  MyToolbar90() {
    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_LEADING }) {
      Text('90VP')
        .backgroundColor(Color.Green)
        .height('90vp')
    }
  }

  @Builder
  MyToolbar4() {
    ToolBarItem({ placement: ToolBarItemPlacement.TOP_BAR_TRAILING }) {
      Column() {
        Image($r('app.media.startIcon'))
          .width('30vp')
          .height('50vp')
        Text('Action')
          .width('30vp')
          .height('10VP')
          .fontSize('10vp')
      }
    }
  }

  @Builder
  PageNavDest(name: string) {
    if (name === '1') {
      NavDestination() {
        Column() {
          Scroll() {
            Column() {
              Text('Navigation()\n' +
                '原子化服务API： 从API version 11开始，该接口支持在原子化服务中使用。\n' +
                '系统能力： SystemCapability.ArkUI.ArkUI.Full\n' +
                'Navigation10+\n' +
                'Navigation(pathInfos: NavPathStack)\n' +
                '属性\n' +
                'Navigation10+\n' +
                'Navigation(pathInfos: NavPathStack)\n' +
                '属性\n' +
                '除支持通用属性外，还支持以下属性：')
                .fontSize(30)
              if (this.showText30) {
                Text('显示56VP高的文字')
                  .toolbar(this.MyToolbar30())
              }
              Button('显示56VP高的文字')
                .onClick(() => {
                  this.showText30 = !this.showText30
                }).defaultFocus(true)

              if (this.showText60) {
                Text('显示64VP高的文字')
                  .toolbar(this.MyToolbar60())
              }
              Button('显示64VP高的文字')
                .onClick(() => {
                  this.showText60 = !this.showText60
                })
              if (this.showText90) {
                Text('显示72VP高的文字')
                  .toolbar(this.MyToolbar90())
              }
              Button('显示72VP高的文字')
                .onClick(() => {
                  this.showText90 = !this.showText90
                })
              Button('undefine 解绑')
                .onClick(() => {
                  this.toolbarIsUndefine = !this.toolbarIsUndefine
                })
                .toolbar(this.toolbarIsUndefine ? this.MyToolbar90() : undefined)
              Button('null 解绑')
                .onClick(() => {
                  this.toolbarIsNull = !this.toolbarIsNull
                })
                .toolbar(this.toolbarIsNull ? this.MyToolbar30() : null)
              if (this.toolbarIsUndefine) {
                Text('64VP')
                  .toolbar(this.MyToolbar4())
              }
              Button('显示64vp')
                .onClick(() => {
                  this.toolbarIsUndefine = !this.toolbarIsUndefine
                })
            }
          }
          .backgroundColor(Color.Grey)
        }
      }
      .hideToolBar(false)
      .title(
        {
          main: 'NavTitle',
          sub: 'subtitle'
        },
        {
          backgroundBlurStyle: BlurStyle.Thin,
          barStyle: BarStyle.STACK,
        }
      )
    } else if (name === '2') {
      NavDestination() {
        Scroll() {
          Text('toolBar(deprecated)\n' +
            'toolBar(value: object | CustomBuilder)\n' +
            '\n' +
            '设置工具栏内容。不设置时不显示工具栏。items均分底部工具栏，在每个均分内容区布局文本和图标，文本超长时，逐级缩小，缩小之后换行，最后截断。\n' +
            '\n' +
            '从API version 10开始，该接口不再维护，推荐使用toolbarConfiguration代替。\n' +
            '\n' +
            '系统能力： SystemCapability.ArkUI.ArkUI.Full\n'
          )
            .fontSize(30)
            .toolbar(this.MyToolbar2())
        }
        .backgroundColor(Color.Grey)
      }
      .hideToolBar(false)
      .title(
        {
          main: 'NavTitle',
          sub: 'subtitle'
        },
        {
          backgroundBlurStyle: BlurStyle.Thin,
          barStyle: BarStyle.STACK,
        })
    } else if (name === '3') {
      NavDestination() {
        Scroll() {
          Column() {
            Text('hideToolBar\n' +
              'hideToolBar(value: boolean)\n' +
              '参数名\t类型\t必填\t说明\n' +
              'value\tboolean\t是\t是否隐藏工具栏。\n' +
              '默认值：false\n' +
              'true: 隐藏工具栏。\n' +
              '参数名\t类型\t必填\t说明\n' +
              'value\tboolean\t是\t是否隐藏工具栏。\n' +
              '默认值：false\n' + 'true: 隐藏工具栏。\n' +
              'false: 显示工具栏。')
              .fontSize(30)
              .toolbar(this.MyToolbar3())
          }
        }
        .backgroundColor(Color.Grey)
      }
      .hideToolBar(false)
      .title(
        {
          main: 'NavTitle',
          sub: 'subtitle'
        },
        {
          backgroundBlurStyle: BlurStyle.Thin,
          barStyle: BarStyle.STACK,
        }
      )
    } else if (name === '4') {
      NavDestination() {
        Scroll() {
          Column() {
            Text('hideToolBar\n' +
              'hideToolBar(value: boolean)\n' +
              '参数名\t类型\t必填\t说明\n' +
              'value\tboolean\t是\t是否隐藏工具栏。\n' +
              '默认值：false\n' +
              'true: 隐藏工具栏。\n' +
              '参数名\t类型\t必填\t说明\n' +
              'value\tboolean\t是\t是否隐藏工具栏。\n' +
              '默认值：false\n' + 'true: 隐藏工具栏。\n' +
              'false: 显示工具栏。')
              .fontSize(30)
              .toolbar(this.MyToolbarB())
          }
        }
        .backgroundColor(Color.Grey)
      }
      .hideToolBar(false)
      .title(
        {
          main: 'NavTitle',
          sub: 'subtitle'
        },
        {
          backgroundBlurStyle: BlurStyle.Thin,
          barStyle: BarStyle.STACK,
        }
      )
    }
  }

  build() {
    SideBarContainer(SideBarContainerType.Embed) {
      Scroll() {
        Column() {
          Button('Switch Floating').onClick(() => {
            if (AppStorage.get('win')) {
              let win: window.WindowStage = AppStorage.get('win') as window.WindowStage;
              win.getMainWindowSync().maximize();
            }
          })
          Button('可见').onClick(() => {
            if (AppStorage.get('win')) {
              let win: window.WindowStage = AppStorage.get('win') as window.WindowStage;
              win.getMainWindowSync().setWindowDecorVisible(true);
            }
          })
          Button('不可见').onClick(() => {
            if (AppStorage.get('win')) {
              let win: window.WindowStage = AppStorage.get('win') as window.WindowStage;
              win.getMainWindowSync().setWindowDecorVisible(false);
            }
          })
          ForEach(this.arr, (item: number) => {
            Column({ space: 5 }) {
              Image(this.current === item ? this.selectedIcon : this.normalIcon).width(32).height(32)
              Text('Index' + item)
                .fontSize(16)
                .fontColor(this.current === item ? '#0A59F7' : '#999')
                .fontFamily('source-sans-pro,cursive,sans-serif')
            }
            .onClick(() => {
              this.showNavbar = !this.showNavbar
              this.current = item
            })
          }, (item: string) => item)

        }.width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)
      }

      Navigation(this.navPathStack) {
        Column() {
          Scroll() {
            Column({ space: 10 }) {
              Button('横屏8').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏9').onClick(() => {
                this.changeOrientation(true)
              })
              Button('竖屏1').onClick(() => {
                this.changeOrientation(false)
              })
              Button('横屏8').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏9').onClick(() => {
                this.changeOrientation(true)
              })
              Button('竖屏1').onClick(() => {
                this.changeOrientation(false)
              })

              Button('显示NavItem').onClick(() => {
                this.showNavbarItem = !this.showNavbarItem;
              })
                .backgroundColor(this.color)
              if (this.showNavbarItem) {
                Button('NavDestination1').onClick(() => {
                  this.navPathStack.pushPath({ name: '1' });
                })// .toolbar(this.MyToolbar())
                  .backgroundColor(this.color)
                Button('NavDestination2').onClick(() => {
                  this.navPathStack.pushPath({ name: '2' });
                })
                  .toolbar(this.MyToolbar())
                  .backgroundColor(this.mycolor)
              }
              Button('NavDestination1').onClick(() => {
                this.navPathStack.pushPath({ name: '1' });
              })
              Button('NavDestination2').onClick(() => {
                this.navPathStack.pushPath({ name: '2' });
              })
              Button('NavDestination3').onClick(() => {
                this.navPathStack.pushPath({ name: '3' });
              })
              Button('NavDestination1').onClick(() => {
                this.navPathStack.pushPath({ name: '1' });
              })
              Button('NavDestination2').onClick(() => {
                this.navPathStack.pushPath({ name: '2' });
              })
              Button('NavDestination3').onClick(() => {
                this.navPathStack.pushPath({ name: '3' });
              })
              Button('横屏4').onClick(() => {
                this.changeOrientation(true)
                if (this.color == Color.Blue) {
                  this.color = Color.Red
                } else {
                  this.color = Color.Blue
                }
              }).backgroundColor(Color.Brown)
              Row() {
                Button('横屏4').onClick(() => {
                  this.changeOrientation(true)
                })
              }
              .clip(true)
              .height('20vp')
              .width('40VP')

              Button('横屏5').onClick(() => {
                this.changeOrientation(true)
              })
                .backgroundColor(Color.Brown)
              // .toolbar(this.MyToolbarB)
              Button('横屏6').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏7').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏8').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏9').onClick(() => {
                this.changeOrientation(true)
              })
              Button('竖屏1').onClick(() => {
                this.changeOrientation(false)
              })
              Button('横屏2').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏3').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏4').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏5').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏6').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏7').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏8').onClick(() => {
                this.changeOrientation(true)
              })
              Button('横屏9').onClick(() => {
                this.changeOrientation(true)
              })
            }.width('100%')
          }
        }
        .backgroundColor(Color.Pink)
      }
      .navBarPosition(NavBarPosition.Start)
      .navBarWidth('50%')
      .navBarWidthRange(['25%', '70%'])
      .navBarPosition(NavBarPosition.Start)
      .hideBackButton(true)
      .hideNavBar(this.showNavbar)
      .mode(NavigationMode.Split)
      .navDestination(this.PageNavDest)
      .title(
        {
          main: 'NavTitle',
          sub: 'subtitle'
        },
        {
          backgroundBlurStyle: BlurStyle.Thin,
          barStyle: BarStyle.STACK,
          backgroundColor: Color.Orange,
          paddingEnd: new LengthMetrics(100),
        }
      )
    }
    .controlButton({
      top: 200,
      icons: {
        hidden: $r('app.media.background'),
        shown: $r('app.media.background'),
        switching: $r('app.media.background')
      }
    })
    .sideBarWidth('8%')
    .minSideBarWidth('3%')
    .maxSideBarWidth('30%')
    .showSideBar($$this.showSideBar)
    .onChange((value: boolean) => {
      console.info('status:' + value)
    })
    .backgroundColor('#FFC0CB')
    .divider({
      strokeWidth: '1%',
      color: Color.Orange,
      startMargin: '4vp',
      endMargin: '4vp'
    })
    .width('100%')

  }
}