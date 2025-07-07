/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { MyComponent } from '../base/MyComponent'

@Builder
export function MenuTestLevel011Builder(name: string, param: Object) {
  MenuTestLevel011Example()
}

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}

@Entry
@Component
struct MenuTestLevel011Example {
  pathStack: NavPathStack = new NavPathStack()
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  // 图文菜单的title测试参数
  private bindMenuOptionsList: MenuOptions[] = [
  //1
    {},
    //title设置不同类型：结合正常宽度菜单选项验证绘制效果，是否影响菜单宽度
    //2
    {
      title: 'MenuTitle'
    },
    //3
    {
      title: 'MenuTitle'.repeat(0)
    },
    //4
    {
      title: 'MenuTitle'.repeat(10)
    },
    //5
    {
      title: 'MenuTitle\n'.repeat(1)
    },
    //6
    {
      title: 'MenuTitle\n'.repeat(3)
    },
    //7
    {
      title: undefined
    }
  ]
  //图文菜单的数组：长数组、短数组、空数组
  private menuArray: Array<MenuElement> = [
  //1 action验证
    {
      value: 'Menu ',
      action: () => {
        console.info('---LCG---  Menu1 Action On')
      }
    },
    //2
    {
      value: 'Menu ',
      action: () => {
      }
    },
    //3 value和icon组合验证: 不同字符串
    {
      value: 'Menu '.repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //4
    {
      value: 'Menu '.repeat(0),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //5
    {
      value: 'Menu '.repeat(5),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //6
    {
      value: 'Menu '.repeat(10),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //7
    {
      value: 'Menu \n'.repeat(3), //实际省略号绘制
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //8
    {
      value: 'undefined', //实际不绘制
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //9 value和icon组合验证: 不同icon类型+尺寸
    {
      value: 'svgIcon'.repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //10
    {
      value: 'gifIcon'.repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //11
    {
      value: 'res异常Icon'.repeat(1),
      icon: $r('app.string.EntryAbility_label'),
      action: () => {
      }
    },
    //12
    {
      value: 'strIcon'.repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //13
    {
      value: 'webpIcon'.repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //14
    {
      value: 'mp4Icon'.repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //15
    {
      value: '2to1Icon'.repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //16
    {
      value: '1to2Icon'.repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //17
    {
      value: 'undefined'.repeat(1),
      icon: undefined,
      action: () => {
      }
    },
    //18 enabled设置菜单项是否进行交互
    {
      value: 'Menu enabled true',
      enabled: true,
      action: () => {
        console.info('---LCG---  Menu enabled true Action On')
      }
    },
    //19
    {
      value: 'Menu enabled false',
      enabled: false,
      action: () => {
        console.info('---LCG---  Menu enabled false Action On')
      }
    },
    //20
    {
      value: 'Menu enabled undefined',
      enabled: undefined,
      action: () => {
        console.info('---LCG---  Menu enabled undefined Action On')
      }
    },
  ]
  // 菜单option
  @State menuOption: MenuOptions = {
    showInSubWindow: false
  }

  //Menu菜单
  @Builder
  MenuBuilder() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  //Menu菜单验证isShow入参, 通过菜单选项hover关闭菜单
  @Builder MenuBuilder_isShow() {
    Menu() {
      MenuItem({ content: 'bindMenu的hover关闭'})
        .onHover( (isHover: boolean) => {
          if (isHover) {
            this.bindMenuShow_1 = false
          }
        })
      MenuItem({ content: 'bindContextMenu的hover关闭'})
        .onHover( (isHover: boolean) => {
          if (isHover) {
            this.bindContextMenuShow_1 = false
          }
        })
    }
  }
  // 动态切换contextMenu的responseType类型: 只有初始化的Type生效
  @State contextMenuResponseType: ResponseType = ResponseType.LongPress

  // bindMenu/ bindContextMenu的 isShow
  @State bindMenuShow_0: boolean = false
  @State bindMenuShow_1: boolean = false
  @State bindContextMenuShow_0: boolean = false
  @State bindContextMenuShow_1: boolean = false

  build() {
    NavDestination() {
      Scroll(this.scroller) {
        Column({ space: 10 }) {
          Text(`验证bindMenu和bindContextMenu的isShow参数`)
            .paramTextStyle()

          Column({ space: 5 }) {
            Text(`不设置isShow的菜单`)
              .paramTextStyle()
            Text(`bindMenu: unset_isShow`)
              .componentTextStyle()
              .bindMenu(this.MenuBuilder(), {
                aboutToAppear: () => {
                  console.info(`---1237---    bindMenu unset isShow, aboutToAppear successful`)
                },
                onAppear: () => {
                  console.info(`---1237---    bindMenu unset isShow, onAppear successful`)
                },
                aboutToDisappear: () => {
                  console.info(`---1237---    bindMenu unset isShow, aboutToDisappear successful`)
                },
                onDisappear: () => {
                  console.info(`---1237---    bindMenu unset isShow, onDisappear successful`)
                },
              })
              .onClick(() => {
                console.info(`---1237--- bindMenu unset isShow, onClick successful`)
              })
            Text(`bindContextMenu: LongPress`)
              .componentTextStyle()
              .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
                preview: MenuPreviewMode.IMAGE,
                aboutToAppear: () => {
                  console.info(`---1237---    bindContextMenu set LongPress, aboutToAppear successful`)
                },
                onAppear: () => {
                  console.info(`---1237---    bindContextMenu set LongPress, onAppear successful`)
                },
                aboutToDisappear: () => {
                  console.info(`---1237---    bindContextMenu set LongPress, aboutToDisappear successful`)
                },
                onDisappear: () => {
                  console.info(`---1237---    bindContextMenu set LongPress, onDisappear successful`)
                },
              })
            Text(`bindContextMenu: RightClick`)
              .componentTextStyle()
              .bindContextMenu(this.MenuBuilder(), ResponseType.RightClick, {
                preview: MenuPreviewMode.IMAGE,
                aboutToAppear: () => {
                  console.info(`---1237---    bindContextMenu set RightClick, aboutToAppear successful`)
                },
                onAppear: () => {
                  console.info(`---1237---    bindContextMenu set RightClick, onAppear successful`)
                },
                aboutToDisappear: () => {
                  console.info(`---1237---    bindContextMenu set RightClick, aboutToDisappear successful`)
                },
                onDisappear: () => {
                  console.info(`---1237---    bindContextMenu set RightClick, onDisappear successful`)
                },
              })

            Text(`bindContextMenu动态切换ResType(预期切换不生效): ${this.contextMenuResponseType}`)
              .paramTextStyle()
            Row({ space: 2 }) {
              MyComponent({
                title: 'longPress', func: () => {
                  this.contextMenuResponseType = ResponseType.LongPress
                }
              })
              MyComponent({
                title: 'rightClick', func: () => {
                  this.contextMenuResponseType = ResponseType.RightClick
                }
              })
            }

            Text(`bindContextMenu: 动态切换Type`)
              .componentTextStyle()
              .bindContextMenu(this.MenuBuilder(), this.contextMenuResponseType, {
                preview: MenuPreviewMode.IMAGE,
                aboutToAppear: () => {
                  console.info(`---1237---    bindContextMenu set RightClick, aboutToAppear successful`)
                },
                onAppear: () => {
                  console.info(`---1237---    bindContextMenu set RightClick, onAppear successful`)
                },
                aboutToDisappear: () => {
                  console.info(`---1237---    bindContextMenu set RightClick, aboutToDisappear successful`)
                },
                onDisappear: () => {
                  console.info(`---1237---    bindContextMenu set RightClick, onDisappear successful`)
                },
              })
          }
          .columnStyle()

          Column({ space: 5 }) {
            Text(`设置isShow的菜单`)
              .paramTextStyle()

            Text(`bindMenu: set_isShow`)
              .componentTextStyle()
              .bindMenu(this.bindMenuShow_0, this.MenuBuilder(), {
                aboutToAppear: () => {
                  console.info(`---1237---    bindMenu unset isShow, aboutToAppear successful`)
                },
                onAppear: () => {
                  console.info(`---1237---    bindMenu unset isShow, onAppear successful`)
                },
                aboutToDisappear: () => {
                  console.info(`---1237---    bindMenu unset isShow, aboutToDisappear successful`)
                },
                onDisappear: () => {
                  console.info(`---1237---    bindMenu unset isShow, onDisappear successful`)
                  if (this.bindMenuShow_0) {
                    this.bindMenuShow_0 = false
                  }
                },
              })
              .onClick(() => {
                console.info(`---1237--- bindMenu set isShow, onClick successful`)
                if (!this.bindMenuShow_0) {
                  this.bindMenuShow_0 = true
                }
              })
            Text(`bindMenu: set_isShow!!`)
              .componentTextStyle()
              .bindMenu(this.bindMenuShow_1!!, this.MenuBuilder_isShow(), {
                aboutToAppear: () => {
                  console.info(`---1237---    bindMenu unset isShow, aboutToAppear successful`)
                },
                onAppear: () => {
                  console.info(`---1237---    bindMenu unset isShow, onAppear successful`)
                },
                aboutToDisappear: () => {
                  console.info(`---1237---    bindMenu unset isShow, aboutToDisappear successful`)
                },
                onDisappear: () => {
                  console.info(`---1237---    bindMenu unset isShow, onDisappear successful`)
                },
              })
              .onClick(() => {
                console.info(`---1237--- bindMenu set isShow!!, onClick successful`)
                if (!this.bindMenuShow_1) {
                  this.bindMenuShow_1 = true
                }
              })

            Text(`bindContextMenu: set_isShow`)
              .componentTextStyle()
              .bindContextMenu(this.bindContextMenuShow_0, this.MenuBuilder(), {
                preview: MenuPreviewMode.IMAGE,
                aboutToAppear: () => {
                  console.info(`---1237---    bindContextMenu set_isShow, aboutToAppear successful`)
                },
                onAppear: () => {
                  console.info(`---1237---    bindContextMenu set_isShow, onAppear successful`)
                },
                aboutToDisappear: () => {
                  console.info(`---1237---    bindContextMenu set_isShow, aboutToDisappear successful`)
                },
                onDisappear: () => {
                  console.info(`---1237---    bindContextMenu set_isShow, onDisappear successful`)
                  if (this.bindContextMenuShow_0) {
                    this.bindContextMenuShow_0 = false
                  }
                },
              })
              .onClick(() => {
                console.info(`---1237--- bindContextMenu set isShow, onClick successful`)
                if (this.bindContextMenuShow_0 === false) {
                  this.bindContextMenuShow_0 = true
                }
              })
            Text(`bindContextMenu: set_isShow!!`)
              .componentTextStyle()
              .bindContextMenu(this.bindContextMenuShow_1!!, this.MenuBuilder_isShow(), {
                preview: MenuPreviewMode.IMAGE,
                aboutToAppear: () => {
                  console.info(`---1237---    bindContextMenu set_isShow!!, aboutToAppear successful`)
                },
                onAppear: () => {
                  console.info(`---1237---    bindContextMenu set_isShow!!, onAppear successful`)
                },
                aboutToDisappear: () => {
                  console.info(`---1237---    bindContextMenu set_isShow!!, aboutToDisappear successful`)
                },
                onDisappear: () => {
                  console.info(`---1237---    bindContextMenu set_isShow!!, onDisappear successful`)
                },
              })
              .onClick(() => {
                console.info(`---1237--- bindContextMenu set isShow!!, onClick successful`)
                if (this.bindContextMenuShow_1 === false) {
                  this.bindContextMenuShow_1 = true
                }
              })
          }
          .columnStyle()
        }
        .width('100%')
        .padding(10)
      }
      .align(Alignment.Top)
      .height('100%')
      .width('100%')
    }
    .title('MenuTestLevel011')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}