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
 
import { SymbolGlyphModifier } from '@kit.ArkUI'

export interface MenuAttrOptions {
  font?: Font,
  fontColor?: ResourceColor,
  radius?: Dimension | BorderRadiuses,

  submenuMode?: SubMenuExpandingMode,
  menuItemDivider?: DividerStyleOptions,
  menuItemGroupDivider?: DividerStyleOptions,

  border?: BorderOptions,
}
//图标资源
export let startIcon: Resource = $r('app.media.app_icon')
export let endIcon: Resource = $r('app.media.app_icon')
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

@Preview
@Component
export struct SubMenuBuilder {
  build() {
    Menu(){
      MenuItem({ startIcon: startIcon, content: '菜单选项' })
        .enabled(false)
      MenuItem({
        symbolStartIcon: symbolStartIcon,
        labelInfo: 'label',
        symbolEndIcon: symbolEndIcon
      })

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
}

@Preview
@Component
export struct MenuBuilder {
  @State menuAttrOptions: MenuAttrOptions = {
    submenuMode: 0,
    menuItemDivider: undefined,
    menuItemGroupDivider: undefined
  }

  @Builder
  SubMenuBuilder() {
    SubMenuBuilder()
  }

  build() {
    Menu(){
      MenuItem({startIcon: startIcon, content: '菜单选项'  })
        .enabled(false)
      MenuItem({
        symbolStartIcon: symbolStartIcon,
        content: "次级选项",
        builder:this.SubMenuBuilder()
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
      })
    }
    .font(this.menuAttrOptions.font)
    .fontColor(this.menuAttrOptions.fontColor)
    .radius(this.menuAttrOptions.radius)

    .subMenuExpandingMode(this.menuAttrOptions.submenuMode)
    .menuItemDivider(this.menuAttrOptions.menuItemDivider)
    .menuItemGroupDivider(this.menuAttrOptions.menuItemGroupDivider)
  }
}

@Preview
@Component
export struct CustomMenuBuilder {
  @Builder
  SubMenuBuilder() {
    SubMenuBuilder()
  }

  build() {
    Column({space: 10}) {
      Menu() {
        MenuItem({startIcon: startIcon, content: '菜单选项'  })
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          content: "次级选项-0",
          builder:this.SubMenuBuilder()
        })
      }
      .width(200)
      .subMenuExpandingMode(0)

      Menu() {
        MenuItem({startIcon: startIcon, content: '菜单选项'  })
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          content: "次级选项-1",
          builder:this.SubMenuBuilder()
        })
      }
      .width(200)
      .subMenuExpandingMode(1)

      Menu() {
        MenuItem({startIcon: startIcon, content: '菜单选项'  })
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          content: "次级选项-2",
          builder:this.SubMenuBuilder()
        })
      }
      .width(200)
      .subMenuExpandingMode(2)
    }
    .padding(10)
    .borderWidth(1.0)
    .borderRadius(16)
    .borderColor(Color.Blue)
  }
}