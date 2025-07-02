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
 
class BuilderOptions {
  width?: Length = "240"
  height?: Length = "300"
}

@Extend(Text)
function paramTextStyle() {
  .fontSize(11)
  .width('100%')
}

@Extend(Text)
function subParamTextStyle() {
  .fontSize(13)
  .width('100%')
  .borderWidth(1.0)
  .backgroundColor(Color.Orange)
}

@Entry
@Component
struct MenuTestLevel0_0 {
  private scroller: Scroller = new Scroller()
  private bindMenuOptions: MenuOptions[] = [
    {},
    //title设置不同类型：结合正常宽度菜单选项验证绘制效果，是否影响菜单宽度
    {
      title: "MenuTitle"
    },
    {
      title: "MenuTitle".repeat(0)
    },
    {
      title: "MenuTitle".repeat(10)
    },
    {
      title: "MenuTitle\n".repeat(1)
    },
    {
      title: "MenuTitle\n".repeat(3)
    },
    {
      title: undefined
    },

    //菜单事件回调：菜单动效前和后的不同事件回调
    {
      title: "MenuTitle",
      onAppear: () => {
        console.info("---LCG---  MenuOptions onAppear On")
      },
      onDisappear: () => {
        console.info("---LCG---  MenuOptions disAppear On")
      },
      aboutToAppear: () => {
        console.info("---LCG---  MenuOptions aboutToAppear On")
      },
      aboutToDisappear: () => {
        console.info("---LCG---  MenuOptions aboutToDisappear On")
      },
    },


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
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //4
    {
      value: "Menu ".repeat(0),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //5
    {
      value: "Menu ".repeat(5),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //6
    {
      value: "Menu ".repeat(10),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //7
    {
      value: "Menu \n".repeat(3), //实际省略号绘制
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //8
    {
      value: "undefined", //实际不绘制
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //9 value和icon组合验证
    {
      value: "svgIcon".repeat(1),
      icon: $r('app.media.app_icon'),
      action: () => {
      }
    },
    //10
    {
      value: "gifIcon".repeat(1),
      icon: $r("app.media.app_icon"),
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
      icon: "/resource/media/money.svg",
      action: () => {
      }
    },
    //13
    {
      value: "webpIcon".repeat(1),
      icon: $r("app.media.app_icon"),
      action: () => {
      }
    },
    //14
    {
      value: "mp4Icon".repeat(1),
      icon: $r("app.media.app_icon"),
      action: () => {
      }
    },
    //15
    {
      value: "2to1Icon".repeat(1),
      icon: $r("app.media.app_icon"),
      action: () => {
      }
    },
    //16
    {
      value: "1to2Icon".repeat(1),
      icon: $r("app.media.app_icon"),
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
  private menuDifWidthArray: Array<MenuElement> = [
    {
      value: "1 ",
      action: () => {
      }
    },
    {
      value: "2 ",
      action: () => {
      }
    },
    {
      value: "3 ",
      action: () => {
      }
    },
    {
      value: "4 ",
      action: () => {
      }
    },
    {
      value: "5 ",
      action: () => {
      }
    },
    {
      value: "1 ".repeat(60),
      action: () => {
      }
    },
    {
      value: "2 ".repeat(60),
      action: () => {
      }
    },
    {
      value: "3 ".repeat(60),
      action: () => {
      }
    },
    {
      value: "4 ".repeat(60),
      action: () => {
      }
    },
    {
      value: "5 ".repeat(60),
      action: () => {
      }
    },
  ]

  //Menu菜单：设置不同的高度、宽度
  @Builder
  MenuBuilder($$: BuilderOptions) {
    Menu() {
      MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
      MenuItem({ content: "粘贴", labelInfo: "Ctrl+V" })
    }
    .borderWidth(1.0)
    .height($$.height)
    .width($$.width)
  }

  //自定义菜单：设置不同高度、宽度
  @Builder
  MenuCustomBuilder($$: BuilderOptions) {
    Scroll(this.scroller) {
      Column()
        .backgroundColor(Color.Orange)
        .height("100%")
        .width("100%")
        .borderRadius(20)
        .borderWidth(1.0)
    }
    .margin(10)
    .height($$.height)
    .width($$.width)
  }

  build() {
    Scroll(this.scroller) {
      Column({ space: 10 }) {
        Text('验证bindMenu的菜单绘制：')
          .paramTextStyle()
          .margin({ top: 5 })
        Column({ space: 5 }) {
          Text("图文菜单")
            .paramTextStyle()
          Text("正常图文列表")
            .subParamTextStyle()
            .bindMenu(this.menuArray.slice(0, 7), this.bindMenuOptions[1])
          Text("空图文列表")
            .subParamTextStyle()
            .bindMenu([], this.bindMenuOptions[1])
          Text("超长图文列表")
            .subParamTextStyle()
            .bindMenu(this.menuArray, this.bindMenuOptions[1])
          Text("窄图文列表")
            .subParamTextStyle()
            .bindMenu(this.menuDifWidthArray.slice(0, 5), this.bindMenuOptions[0])
          Text("宽图文列表")
            .subParamTextStyle()
            .bindMenu(this.menuDifWidthArray.slice(5, 10), this.bindMenuOptions[0])

          Text("自定义菜单")
            .paramTextStyle()
          Text("正常自定义菜单")
            .subParamTextStyle()
            .bindMenu(this.MenuCustomBuilder({ width: 200, height: 300 }), this.bindMenuOptions[1])
          Text("高度为0的自定义菜单")//builder父容器高度为0
            .subParamTextStyle()
            .bindMenu(this.MenuCustomBuilder({ width: 120, height: 0 }), this.bindMenuOptions[1])
          Text("窄自定义菜单")//菜单的绘制：预期正常宽度绘制
            .subParamTextStyle()
            .bindMenu(this.MenuCustomBuilder({ width: 60, height: 300 }), this.bindMenuOptions[1])
          Text("宽自定义菜单")//菜单的绘制：预期有最大宽度限制，按照最大宽度绘制，超出部分剪裁
            .subParamTextStyle()
            .bindMenu(this.MenuCustomBuilder({ width: 600, height: 300 }), this.bindMenuOptions[1])
          Text("超短自定义菜单")
            .subParamTextStyle()
            .bindMenu(this.MenuCustomBuilder({ width: 120, height: 30 }), this.bindMenuOptions[1])
          Text("超长自定义菜单")//菜单的绘制位置和方式：预期避让且高度有限制
            .subParamTextStyle()
            .bindMenu(this.MenuCustomBuilder({ width: 200, height: 1080 }), this.bindMenuOptions[1])
          Text("尺寸百分比自定义菜单")//菜单的绘制：预期有最大宽度限制，按照最大宽度绘制，超出部分剪裁
            .subParamTextStyle()
            .bindMenu(this.MenuCustomBuilder({ width: "100%", height: "100%" }), this.bindMenuOptions[1])

          Text("Menu菜单")
            .paramTextStyle()
          Text("正常Menu菜单")
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: 200, height: 300 }), this.bindMenuOptions[1])
          Text("宽度为0的Menu菜单")//builder父容器宽度为0：预期极小宽度的一个长条
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: 0, height: 300 }), this.bindMenuOptions[1])
          Text("超短Menu菜单")//builder父容器高度小于内容高度
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: 200, height: 30 }), this.bindMenuOptions[1])
          Text("超长Menu菜单")
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: 200, height: 1080 }), this.bindMenuOptions[1])
          Text("窄Menu菜单")
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: 30, height: 300 }), this.bindMenuOptions[1])
          Text("宽Menu菜单")
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: 600, height: 300 }), this.bindMenuOptions[1])
          Text("自定义尺寸Menu菜单")
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: "100%", height: "100%" }), this.bindMenuOptions[1])

        }
        .backgroundColor(Color.Pink)
        .width("100%")
        .padding(5)
        .borderWidth(1.0)

        Text(`验证菜单中滚动条效果`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`图文超长菜单滚动条`)
            .subParamTextStyle()
            .bindMenu(this.menuArray, {
              title: "MenuTitle"
            },)
          Text(`R50,图文超长菜单滚动条`)
            .subParamTextStyle()
            .bindMenu(this.menuArray, {
              title: "MenuTitle",
              borderRadius: 50
            },)

          Text(`Menu超长菜单滚动条`)
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: 200, height: 1080 }))

          Text(`R50,Menu超长菜单滚动条`)
            .subParamTextStyle()
            .bindMenu(this.MenuBuilder({ width: 200, height: 1080 }), {
              borderRadius: 50
            })
        }
        .backgroundColor(Color.Pink)
        .width("100%")
        .padding(5)
        .borderWidth(1.0)
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