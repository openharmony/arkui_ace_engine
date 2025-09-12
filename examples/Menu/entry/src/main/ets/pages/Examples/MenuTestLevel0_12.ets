/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * bindMenu和bindContextMenu验证菜单的边框圆角半径
 */

import { MyComponent } from '../../common/MyComponent'

@Extend(Text)
function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}

@Extend(Text)
function componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3)
  .padding(3)
  .borderWidth(1.0)
}

@Extend(Column)
function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct MenuTestLevel0_12 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0,]
  @State menuShow: boolean[] = [false, false, false, false, false]
  @State extremeMenuRadius: number = 60
  private iconStr: ResourceStr = $r('app.media.app_icon')
  private iconStr2: ResourceStr = $r('app.media.app_icon')

  // 次级菜单
  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
    .backgroundColor('#C2B1C8')
    .borderWidth(1.0)
    .borderRadius(10)
  }

  @Builder
  MenuBuilder_Radius() {
    Menu() {
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
      MenuItem({ startIcon: $r('app.media.app_icon'), content: '菜单选项' })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: '次级菜单',
        endIcon: this.iconStr2,
        builder: (): void => this.SubMenu()
      })
    }
    .backgroundColor('#C2B1C8')
    .borderWidth(1.0)
    .borderRadius(10)
  }

  // BorderRadius bindMenu/bindContextMenu CustomBuilder
  @Builder
  CustomMenuBuilder_Radius() {
    Flex({ direction: FlexDirection.Column, alignItems: ItemAlign.Center, justifyContent: FlexAlign.Center }) {
      Text('Options')
      Divider().strokeWidth(1).margin(5).color('#ff414141')
      Text('Hide')
      Divider().strokeWidth(1).margin(5).color('#ff414141')
      Text('Exit')
    }
    .width('70%')
    .backgroundColor('#C2B1C8')
    .borderWidth(1.0)
    .borderRadius(10)
  }

  // menu preview
  @Builder
  MenuPreviewBuilder() {
    Column() {
      Image($r('app.media.app_icon'))
        .width(160)
        .height(120)
        .margin(10)
    }
    .borderWidth(1.0)
    .borderRadius(10)
  }

  // borderRadius TestList
  @State menuBorderRadiusTestList: (ContextMenuOptions | undefined)[] = [
  //1
    ,
    //2
    {
      borderRadius: undefined
    },
    //3
    {
      borderRadius: {
        topLeft: '20vp',
        topRight: '20px',
        bottomLeft: '20fp',
        bottomRight: '20lpx'
      },
    },
    //4
    {
      borderRadius: {
        topLeft: '-20',
        topRight: '0',
        bottomLeft: '20',
        bottomRight: '36'
      },
    },
    //5
    {
      borderRadius: {
        topLeft: 20,
        topRight: $r('app.float.float_10'),
        bottomLeft: '20',
        bottomRight: '20%'
      }, //百分比不生效.
    },
    //6
    {
      borderRadius: {
        topLeft: '60aa',
        topRight: $r('app.string.EntryAbility_label'),
        bottomLeft: undefined,
        bottomRight: '30%'
      }, //预期都为默认值.
    },
    //7
    {
      borderRadius: 32,
    },
    //8
    {
      borderRadius: '32px',
    },
    //9
    {
      borderRadius: '32lpx',
    },
    //10
    {
      borderRadius: '32fp',
    },
    //11
    {
      borderRadius: '32vp',
    },
    //12
    {
      borderRadius: -32,
    },
    //13
    {
      borderRadius: 0,
    },
    //14
    {
      borderRadius: $r('app.float.float_60'),
    },
    //15
    {
      borderRadius: $r('app.string.EntryAbility_label'),
    },
    //16
    {
      borderRadius: '90px',
    },
  ]

  build() {
    Scroll(this.scroller) {
      Column({ space: 5 }) {
        Text(`bindMenu和bindContextMenu验证菜单的边框圆角半径`)
          .paramTextStyle()
        Column({ space: 5 }) {
          Text(`bindMenu/bindContextMenu不设置边框圆角半径`)
            .paramTextStyle()
          Text(`bindMenu_Array: unset_borderRadius`)
            .componentTextStyle()
            .bindMenu([
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
            ])
          Text(`bindMenu_Menu: unset_borderRadius`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder_Radius())
          Text(`bindContextMenu_Custom: unset_borderRadius`)
            .componentTextStyle()
            .fontSize(13)
            .bindContextMenu(this.CustomMenuBuilder_Radius(), ResponseType.LongPress)
        }
        .columnStyle()

        Column({ space: 5 }) {
          Text(`bindMenu/bindContextMenu设置边框圆角半径`)
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + ' / ')
              .fontSize(9)
            Text(`${this.menuBorderRadiusTestList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == this.menuBorderRadiusTestList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.menuBorderRadiusTestList.length - 1
                }
              }
            })
          }

          Text(`bindMenu_Array: set_borderRadius`)
            .componentTextStyle()
            .bindMenu([
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
            ], {
              borderRadius: this.menuBorderRadiusTestList[this.index[0]]?.borderRadius,
              //bindMenu： borderRadius和Arrow组合测试
              enableArrow: true,
              arrowOffset: '25%',
              backgroundColor: '#fffdd986',
              backgroundBlurStyle: BlurStyle.NONE,
            })
          Text(`bindMenu_Custom: set_borderRadius`)
            .componentTextStyle()
            .bindMenu(this.CustomMenuBuilder_Radius(), {
              borderRadius: this.menuBorderRadiusTestList[this.index[0]]?.borderRadius,
              backgroundColor: '#4A4333',
              backgroundBlurStyle: BlurStyle.NONE,
            })
          Text(`bindContextMenu_Menu: set_borderRadius`)
            .componentTextStyle()
            .fontSize(13)
            .bindContextMenu(this.MenuBuilder_Radius(), ResponseType.LongPress, {
              borderRadius: this.menuBorderRadiusTestList[this.index[0]]?.borderRadius,
              backgroundColor: '#4A4333',
              backgroundBlurStyle: BlurStyle.NONE,
              preview: this.MenuPreviewBuilder(),
            })
        }
        .columnStyle()
      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width('100%').height('100%')
  }
}