/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
* 用例调整：分隔线组合测试场景划分为L1用例
*
* 验证Menu的divider分割线样式: 空Item, 一个Item和ItemGroup, ForEach的超多Item, 设置Menu有padding, 设置if语句
 */
import { LengthUnit } from '@ohos.arkui.node';
import { MyComponent } from '../../common/MyComponent'
import { SymbolGlyphModifier } from '@kit.ArkUI'

@Extend(Text) function  paramTextStyle() {
  .fontSize(9)
  .width('100%')
}
@Extend(Text) function  componentTextStyle() {
  .fontSize(15)
  .backgroundColor(Color.Orange)
  .margin(3).padding(3)
  .borderWidth(1.0)
}
@Extend(Column) function columnStyle() {
  .borderWidth(1.0)
  .padding(5)
  .width('100%')
  .backgroundColor(Color.Pink)
}

@Entry
@Component
struct MenuTestLevel0_14 {
  scroller: Scroller = new Scroller()
  @State index: number[] = [0,]
  @State menuShow: boolean[] = [false, false, false]

  @State select: boolean = true
  private iconStr: ResourceStr = $r('app.media.app_icon')
  private iconStr2: ResourceStr = $r('app.media.app_icon')

  //菜单控制-builder-Column-Menu(subMenuMode)
  @Builder
  X_SubMenuModeBuilder() {
    Column({space: 3}){
      Menu(){
        MenuItem({ 
            content: 'side子菜单', 
            labelInfo: 'Ctrl+C', 
            builder: this.GrandSubMenu() 
        })
        MenuItem({ 
            content: '子菜单', 
            labelInfo: 'Ctrl+V', 
            builder: this.GrandSubMenu() 
        })
          .enabled(false)
      }
      .width(280)
      .subMenuExpandingMode(0)
      Menu(){
        MenuItem({ 
            content: 'embedded子菜单',
            labelInfo: 'Ctrl+C', 
            builder: this.GrandSubMenu() 
        })
      }
      .width(280)
      .subMenuExpandingMode(1)
      Menu(){
        MenuItem({ 
            content: 'stack子菜单', 
            labelInfo: 'Ctrl+C', 
            builder: this.GrandSubMenu() 
        })
      }
      .width(280)
      .subMenuExpandingMode(2)
    }
    .padding(3)
  }
  //
  @Builder
  GrandSubMenu() {
    Menu() {
      MenuItem({ 
        content: '复制', 
        labelInfo: 'Ctrl+C' 
      })
      MenuItem({ 
        content: '粘贴', 
        labelInfo: 'Ctrl+V' 
      })
    }
  }

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ 
        content: '复制',
        labelInfo: 'Ctrl+C' 
      })
      MenuItem({ 
        content: '粘贴', 
        labelInfo: 'Ctrl+V' 
      })
      MenuItem({
        startIcon: this.iconStr,
        content: '子菜单',
        endIcon: this.iconStr2,
        builder: (): void => this.GrandSubMenu()
      })
    }
    .subMenuExpandingMode(this.menuSubMenuExpandingMode)
  }
  // sized subMenu builder
  @State subMenuWidth: number = 160
  @State subMenuHeight: number = 160
  @Builder
  SubMenu_sized() {
    Menu() {
      MenuItem({ 
        content: '复制', 
        labelInfo: 'Ctrl+C'
      })
      MenuItem({ 
        content: '粘贴', 
        labelInfo: 'Ctrl+V' 
      })
      MenuItem({
        startIcon: this.iconStr,
        content: '子菜单',
        endIcon: this.iconStr2,
        builder: (): void => this.GrandSubMenu()
      })
    }
    .width(this.subMenuWidth)
    .height(this.subMenuHeight)
    .subMenuExpandingMode(this.menuSubMenuExpandingMode)
  }

  //subMenu mode
  @State menuSubMenuExpandingMode: SubMenuExpandingMode | undefined = SubMenuExpandingMode.SIDE_EXPAND
  // subMenu expandSymbol
  @State subMenuExpandSymbol: SymbolGlyphModifier | undefined = undefined

  //subMenu builder
  @Builder
  MenuBuilder(){
    Menu() {
      MenuItem({ 
        startIcon: $r('app.media.app_icon'), 
        content: '菜单选项' 
      })
        .selectIcon(true)
        .selected(this.select)
        .onChange( () => {
          this.select = !this.select
        })
      MenuItem({ 
        startIcon: $r('app.media.app_icon'), 
        content: '菜单选项' 
      })
        .enabled(false)
      MenuItem({
        startIcon: this.iconStr,
        content: '子菜单1.0',
        endIcon: this.iconStr2,
        builder: (): void => this.SubMenu()
      })
      MenuItemGroup({ header: '标题' }) {
        MenuItem({
          startIcon: this.iconStr,
          content: 'sized子菜单',
          endIcon: this.iconStr2,
          builder: () => this.SubMenu_sized()
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '子菜单2.0',
          endIcon: this.iconStr2,
          builder: this.SubMenu()
        })
      }
      MenuItem({
        startIcon: this.iconStr,
        content: '菜单选项',
      })
    }
    .subMenuExpandingMode(this.menuSubMenuExpandingMode)
    .subMenuExpandSymbol(this.subMenuExpandSymbol)
  }

  build() {
    Scroll(this.scroller){
      Column({space : 5}) {
        Text('验证Menu子菜单展开样式')
          .paramTextStyle()
        Column({space : 5}){
          Text('切换子菜单弹出样式')
            .paramTextStyle()
          Row({space: 3}) {
            MyComponent({title: `SIDE`, func: () => {
              this.menuSubMenuExpandingMode = SubMenuExpandingMode.SIDE_EXPAND  //UX默认值
            }})
            MyComponent({title: `EMBEDDED`, func: () => {
              this.menuSubMenuExpandingMode = SubMenuExpandingMode.EMBEDDED_EXPAND
            }})
            MyComponent({title: `STACK`, func: () => {
              this.menuSubMenuExpandingMode = SubMenuExpandingMode.STACK_EXPAND
            }})
            MyComponent({title: `UN`, func: () => {
              this.menuSubMenuExpandingMode = undefined
            }})
            MyComponent({title: `枚举异常`, func: () => {
              this.menuSubMenuExpandingMode = 7
            }})
          }
          Text('切换子菜单展开符号样式')
            .paramTextStyle()
          Row({space: 3}){
            MyComponent({title: 'expandSymbol: UN', func: () => {
              this.subMenuExpandSymbol = undefined
            }})
            MyComponent({title: 'expandSymbol: 正常', func: () => {
              this.subMenuExpandSymbol = new SymbolGlyphModifier($r('sys.symbol.candle_light'))
                .fontSize('30')
                .fontColor([Color.Blue, Color.Orange])
                .fontWeight(300)
                .effectStrategy(SymbolEffectStrategy.HIERARCHICAL)
                .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR)
                .symbolEffect(SymbolEffect.prototype, 2)
            }})
            MyComponent({title: 'expandSymbol: 较大值', func: () => {
              this.subMenuExpandSymbol = new SymbolGlyphModifier($r('sys.symbol.candle_light'))
                .fontSize('60')
                .fontColor([Color.Blue, Color.Orange])
                .fontWeight(300)
                .effectStrategy(SymbolEffectStrategy.HIERARCHICAL)
                .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR)
                .symbolEffect(SymbolEffect.prototype, 2)
            }})
          }

          Text(`bindMenu: subMenuMode`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder(), {
            })
          Text(`bindContextMenu: subMenuMode`)
            .componentTextStyle()
            .bindContextMenu(this.MenuBuilder(), ResponseType.LongPress, {
              placement: Placement.BottomLeft,
            })

          Text(`一个菜单包含多种子菜单类型`)
            .paramTextStyle()
          Text(`bindContextMenu: X-subMenuMode`)
            .componentTextStyle()
            .bindContextMenu(this.X_SubMenuModeBuilder(), ResponseType.LongPress, {
              preview: MenuPreviewMode.IMAGE,
              backgroundColor: '#B6C5D1',
              backgroundBlurStyle: BlurStyle.NONE
            })

          Text(`切换子菜单尺寸: width-${this.subMenuWidth}, height-${this.subMenuHeight}`)
            .paramTextStyle()
          Row({space: 3}) {
            MyComponent({title: `W: 120`, func: () => {
              this.subMenuWidth = 120
            }})
            MyComponent({title: `W: 160`, func: () => {
              this.subMenuWidth = 160
            }})
            MyComponent({title: `W: 200`, func: () => {
              this.subMenuWidth = 200
            }})
            MyComponent({title: `W: 240`, func: () => {
              this.subMenuWidth = 240
            }})
          }
          Row({space: 3}) {
            MyComponent({title: `H: 120`, func: () => {
              this.subMenuHeight = 120
            }})
            MyComponent({title: `H: 240`, func: () => {
              this.subMenuHeight = 240
            }})
            MyComponent({title: `H: 480`, func: () => {
              this.subMenuHeight = 480
            }})
            MyComponent({title: `H: 600`, func: () => {
              this.subMenuHeight = 600
            }})
          }
          Text(`bindMenu: subMenuMode_difSize`)
            .componentTextStyle()
            .bindMenu(this.MenuBuilder(), {
              placement: Placement.Top,
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