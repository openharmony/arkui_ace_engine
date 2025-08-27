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

@Builder
export function MenuLevel0Builder(name: string, param: Object) {
  MenuLevel0Example()
}

export interface MenuAttrOptions1 {
  submenuMode?: SubMenuExpandingMode,
  menuItemDivider?: DividerStyleOptions,
  menuItemGroupDivider?: DividerStyleOptions
}
//图标资源
let startIcon: Resource = $r('app.media.app_icon')
let endIcon: Resource = $r('app.media.app_icon')
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
          content: '菜单选项1',
          endIcon: endIcon,
        })
          .enabled(false)
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          labelInfo: 'label',
        })
      }

      MenuItem({
        content: '菜单选项2',
        labelInfo: 'label',
        symbolStartIcon: symbolStartIcon,
        symbolEndIcon: symbolEndIcon
      })
    }
  }
}

@Entry
@Preview
@Component
export struct MenuLevel0Example {
  pathStack: NavPathStack = new NavPathStack()
  @State menuAttrOptions: MenuAttrOptions1 = {
    submenuMode: 0,
    menuItemDivider: undefined,
    menuItemGroupDivider: undefined
  }

  @Builder
  SubMenuBuilder() {
    SubMenuBuilder()
  }

  build() {
    NavDestination() {
      Menu() {
        MenuItem({ startIcon: startIcon, content: '菜单选项' })
          .enabled(false)
        MenuItem({
          symbolStartIcon: symbolStartIcon,
          content: '次级选项',
          builder: this.SubMenuBuilder()
        })

        MenuItemGroup({ header: '标题', footer: '脚标' }) {
          MenuItem({
            content: '菜单选项1',
            endIcon: endIcon,
          })
            .enabled(false)
          MenuItem({
            content: '次级选项1',
            symbolEndIcon: symbolEndIcon,
            builder: this.SubMenuBuilder()
          })
        }

        MenuItem({
          content: '菜单选项2',
          labelInfo: 'label',
          symbolStartIcon: symbolStartIcon,
          symbolEndIcon: symbolEndIcon
        })
      }
      .subMenuExpandingMode(this.menuAttrOptions.submenuMode)
      .menuItemDivider(this.menuAttrOptions.menuItemDivider)
      .menuItemGroupDivider(this.menuAttrOptions.menuItemGroupDivider)
    }
    .title('MenuLevel0')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}