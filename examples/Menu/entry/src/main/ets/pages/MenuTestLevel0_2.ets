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
 
import { MyComponent } from "../common/MyComponent"

@Extend(Text) function paramTextStyle() {
  .fontSize(9)
  .width("100%")
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width("100%")
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
struct MenuTestLevel0_2 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0, 0, 0]

  // 图文菜单的title测试参数
  private bindMenuOptionsList: MenuOptions[] = [
  //1
    {},
    //title设置不同类型：结合正常宽度菜单选项验证绘制效果，是否影响菜单宽度
    //2
    {
      title: "MenuTitle"
    },
    //3
    {
      title: "MenuTitle".repeat(0)
    },
    //4
    {
      title: "MenuTitle".repeat(10)
    },
    //5
    {
      title: "MenuTitle\n".repeat(1)
    },
    //6
    {
      title: "MenuTitle\n".repeat(3)
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
      value: "Menu ",
      action: () => {
        console.info("---LCG---  Menu1 Action On")
      }
    },
    //2
    {
      value: "Menu ",
      action: () => {
      }
    },
    //3 value和icon组合验证: 不同字符串
    {
      value: "Menu ".repeat(1),
      icon: $r('app.media.startIcon'),
      action: () => {
      }
    },
    //4
    {
      value: "Menu ".repeat(0),
      icon: $r('app.media.startIcon'),
      action: () => {
      }
    },
    //5
    {
      value: "Menu ".repeat(5),
      icon: $r('app.media.startIcon'),
      action: () => {
      }
    },
    //6
    {
      value: "Menu ".repeat(10),
      icon: $r('app.media.startIcon'),
      action: () => {
      }
    },
    //7
    {
      value: "Menu \n".repeat(3), //实际省略号绘制
      icon: $r('app.media.startIcon'),
      action: () => {
      }
    },
    //8
    {
      value: "undefined", //实际不绘制
      icon: $r('app.media.startIcon'),
      action: () => {
      }
    },
    //9 value和icon组合验证: 不同icon类型+尺寸
    {
      value: "svgIcon".repeat(1),
      icon: $r('app.media.startIcon'),
      action: () => {
      }
    },
    //10
    {
      value: "gifIcon".repeat(1),
      icon: $r("app.media.startIcon"),
      action: () => {
      }
    },
    //11
    {
      value: "res异常Icon".repeat(1),
      icon: $r("app.string.EntryAbility_label"),
      action: () => {
      }
    },
    //12
    {
      value: "strIcon".repeat(1),
      icon: "../../resources/base/media/money.svg",
      action: () => {
      }
    },
    //13
    {
      value: "webpIcon".repeat(1),
      icon: $r("app.media.startIcon"),
      action: () => {
      }
    },
    //14
    {
      value: "mp4Icon".repeat(1),
      icon: $r("app.media.startIcon"),
      action: () => {
      }
    },
    //15
    {
      value: "2to1Icon".repeat(1),
      icon: $r("app.media.startIcon"),
      action: () => {
      }
    },
    //16
    {
      value: "1to2Icon".repeat(1),
      icon: $r("app.media.startIcon"),
      action: () => {
      }
    },
    //17
    {
      value: "undefined".repeat(1),
      icon: undefined,
      action: () => {
      }
    },
    //18 enabled设置菜单项是否进行交互
    {
      value: "Menu enabled true",
      enabled: true,
      action: () => {
        console.info("---LCG---  Menu enabled true Action On")
      }
    },
    //19
    {
      value: "Menu enabled false",
      enabled: false,
      action: () => {
        console.info("---LCG---  Menu enabled false Action On")
      }
    },
    //20
    {
      value: "Menu enabled undefined",
      enabled: undefined,
      action: () => {
        console.info("---LCG---  Menu enabled undefined Action On")
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
      MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 10 }) {
        Text('验证bindMenu的Options: title')
          .paramTextStyle()
        Column({ space: 5 }) {
          Text("切换title的测试参数")
            .paramTextStyle()
          Row({ space: 2 }) {
            Text(`${this.index[0] + 1}` + " / ")
              .fontSize(9)
            Text(`${this.bindMenuOptionsList.length}`)
              .key('paramSets_key_0')
              .fontSize(9)
            MyComponent({
              title: 'Test0+', func: () => {
                this.index[0]++
                if (this.index[0] == this.bindMenuOptionsList.length) {
                  this.index[0] = 0
                }
              }
            })
            MyComponent({
              title: 'Test0-', func: () => {
                this.index[0]--
                if (this.index[0] <= -1) {
                  this.index[0] = this.bindMenuOptionsList.length - 1
                }
              }
            })
          }
          Text("图文列表菜单")
            .componentTextStyle()
            .bindMenu(this.menuArray.slice(0, 7), this.bindMenuOptionsList[this.index[0]])

          Text("bindMenu设置自定义菜单, 验证title设置")
            .paramTextStyle()
          Text("Menu自定义菜单")
            .componentTextStyle()
            .bindMenu(this.MenuBuilder(), {
              title: 'Menu Title'
            })
        }
        .columnStyle()

        Text(`验证bindMenu的showInSubWindow的节点树表现`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`切换menuOpt的subWindow(只和设备类型相关): ${this.menuOption.showInSubWindow}`)
            .paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'subWindow: T', func: () => {
              this.menuOption.showInSubWindow = true
            }})
            MyComponent({title: 'subWindow: F', func: () => {
              this.menuOption.showInSubWindow = false
            }})

          }
          Text(`bindMenu: subWindow`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder(), {
              showInSubWindow: this.menuOption.showInSubWindow
            })
        }
        .columnStyle()
      }
      .width('100%')
      .padding(10)
    }
    .align(Alignment.Top)
    .height("100%")
    .width('100%')
  }

  pageTransition() {
    //进入该界面没有跳转延迟
    PageTransitionEnter({ type: RouteType.None, duration: 0 })
  }
}