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
import {MyComponent} from "../../common/MyComponent"
import {MenuBuilder, MenuAttrOptions } from "../../customBuilder/MenuBuilder"

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
struct MenuAccessibilityTestLevel0_1 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]

  //图文菜单的option
  @State menuOptions: MenuOptions = {
    showInSubWindow: false
  }

  //Menu的builder option
  @State menuAttrOption: MenuAttrOptions = {
    submenuMode: 0
  }

  @Builder
  MenuBuilder() {
    MenuBuilder({
        menuAttrOptions: {
            submenuMode: this.menuAttrOption.submenuMode
        }
    })
  }

  build() {
    Scroll(this.scroller){
      Column({ space: 5 }) {
        Text(`验证bindMenu菜单无障碍功能`)
          .paramTextStyle()
        Column({space: 5}){
          Text(`设置菜单次级菜单类型: ${this.menuAttrOption.submenuMode}`)
            .paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'SIDE', func: () => {
              this.menuAttrOption.submenuMode = 0
            }})
            MyComponent({title: 'EMBEDDED', func: () => {
              this.menuAttrOption.submenuMode = 1
            }})
            MyComponent({title: 'STACK', func: () => {
              this.menuAttrOption.submenuMode = 2
            }})
          }
          Button('bindMenu: 菜单')
            .backgroundColor(Color.Orange)
            .borderRadius(0)
            .bindMenu(this.MenuBuilder(), {
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