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

import { SymbolGlyphModifier } from '@kit.ArkUI'

export interface MenuAttrOptions {
  submenuMode?: SubMenuExpandingMode,
  enabled?: boolean,
  subMenuExpandSymbol?:SymbolGlyphModifier | undefined | null,
  menuItemDivider?: DividerStyleOptions,
  menuItemGroupDivider?: DividerStyleOptions
  font?: Font
  fontColor?:ResourceColor
  radius?: Dimension | BorderRadiuses
  selected?: boolean
  selectIcon?: boolean | ResourceStr | SymbolGlyphModifier
  contentFont?: Font
  contentFontColor?: ResourceColor
  labelFont?: Font
  labelFontColor?: ResourceColor
}
//图标资源
let startIcon: Resource = $r('app.media.layered_image')
let endIcon: Resource = $r('app.media.foreground')
export let symbolStartIcon: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.checkmark_square_on_square_fill'))
  .fontSize('30')
  .fontColor([Color.Blue, Color.Orange])
  .fontWeight(300)
  .effectStrategy(SymbolEffectStrategy.HIERARCHICAL)
  .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR)
  .symbolEffect(SymbolEffect.prototype, 2)
export let symbolEndIcon: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.candle_light'))
  .fontSize('30')
  .fontColor([Color.Blue, Color.Orange])
  .fontWeight(300)
  .effectStrategy(SymbolEffectStrategy.HIERARCHICAL)
  .renderingStrategy(SymbolRenderingStrategy.MULTIPLE_COLOR)
  .symbolEffect(SymbolEffect.prototype, 2)

@Entry
@Preview
@Component
export struct MenuBuilder {
  @State menuAttrOptions: MenuAttrOptions = {
    submenuMode: 0,
    enabled:undefined,
    subMenuExpandSymbol:undefined,
    menuItemDivider: undefined,
    menuItemGroupDivider: undefined,
    font: undefined,
    fontColor:undefined,
    radius:undefined,
    selected:undefined,
    selectIcon:undefined,
    contentFont:undefined,
    contentFontColor:undefined,
    labelFont:undefined,
    labelFontColor:undefined,
  }

  @Builder
  SubMenuBuilder() {
    Menu(){
      MenuItem({ startIcon: startIcon, content: '菜单选项' })
        .enabled(false)
      MenuItem({
        symbolStartIcon: symbolStartIcon,
        labelInfo: 'label',
        symbolEndIcon: symbolEndIcon,
        builder:this.SubMenuBuilder()
      }).enabled(false)

      MenuItemGroup({header: '标题', footer: '脚标' }) {
        MenuItem({
          content: "菜单选项1",
          endIcon: endIcon,
        })
          .enabled(false)
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          labelInfo: 'label',
        })
      }

      MenuItem({
        content: "菜单选项2",
        labelInfo: 'label',
        symbolStartIcon: symbolStartIcon,
        symbolEndIcon: symbolEndIcon
      })
    }
  }

  build() {
    Column(){
      Menu(){
        MenuItem({startIcon: startIcon, content: '菜单选项'  })
          .enabled(false)
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          content: "次级选项",
          builder:this.SubMenuBuilder()
        }).enabled(this.menuAttrOptions.enabled)
          .selected(this.menuAttrOptions.selected)
          .selectIcon(this.menuAttrOptions.selectIcon)
          .contentFont(this.menuAttrOptions.contentFont)
          .contentFontColor(this.menuAttrOptions.contentFontColor)
          .onChange((selected: boolean)=>{
            console.log("onChange MenuItem状态改变" + selected.valueOf())
          })
        MenuItemGroup({header: '标题', footer: '脚标' }) {
          MenuItem({
            content: "菜单选项1",
            endIcon: endIcon,
          })
            .enabled(false)
          MenuItem({
            content: "次级选项1",
            symbolEndIcon: symbolEndIcon,
            builder: this.SubMenuBuilder()
          })
        }
        MenuItem({
          content: "菜单选项2",
          labelInfo: 'label',
          symbolStartIcon: symbolStartIcon,
          symbolEndIcon: symbolEndIcon
        }).labelFont(this.menuAttrOptions.labelFont)
          .labelFontColor(this.menuAttrOptions.labelFontColor)
      }
      .subMenuExpandSymbol(this.menuAttrOptions.subMenuExpandSymbol)
      .subMenuExpandingMode(this.menuAttrOptions.submenuMode)
      .menuItemDivider(this.menuAttrOptions.menuItemDivider)
      .menuItemGroupDivider(this.menuAttrOptions.menuItemGroupDivider)
      .font(this.menuAttrOptions.font)
      .fontColor(this.menuAttrOptions.fontColor)
      .radius(this.menuAttrOptions.radius)
      Text('我是一个菜单')
    }
  }
}