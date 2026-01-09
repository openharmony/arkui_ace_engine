/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import {MyComponent} from "../../common/MyComponent"
import { SymbolGlyphModifier } from '@kit.ArkUI'

@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width("100%")
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width("100%")
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct MenuAccessibilityTestLevel0_0 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]

  // MenuElement/Title的文本内容
  @State menuElement: MenuElement[] =
    [
      {
        value: "图文菜单选项 ".repeat(1),
        enabled: true,
        icon: $r("sys.media.ohos_app_icon"),
        action: () => {},
        symbolIcon: new SymbolGlyphModifier($r('sys.symbol.menu_TV'))
      },
      {
        value: "图文菜单选项 ".repeat(3),
        enabled: true,
        icon: $r("sys.media.ohos_app_icon"),
        action: () => {},
      },
      {
        value: "图文菜单选项 ".repeat(10),
        enabled: false,
        icon: $r("sys.media.ohos_app_icon"),
        action: () => {},
        symbolIcon: new SymbolGlyphModifier($r('sys.symbol.menu_TV'))
      },
    ]

  //图文菜单的option
  @State menuOptions: MenuOptions = {
    showInSubWindow: false
  }

  build() {
    Scroll(this.scroller){
      Column({ space: 5 }) {
        Text(`验证bindMenu图文菜单无障碍功能`)
          .paramTextStyle()
        Column({space: 5}){
          Button('bindMenu: 图文菜单')
            .backgroundColor(Color.Orange)
            .borderRadius(0)
            .bindMenu(this.menuElement, {
              title: '图文菜单',
            })
        }
        .columnStyle()

      }
      .width('100%')
    }
    .padding(12)
    .align(Alignment.TopStart)
    .width("100%").height("100%")
    .scrollBar(BarState.Off)
  }
}