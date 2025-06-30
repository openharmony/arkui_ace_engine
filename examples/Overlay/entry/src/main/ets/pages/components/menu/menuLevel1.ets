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
export function MenuLevel1Builder(name: string, param: Object) {
  MenuLevel1Example()
}

export interface MenuAttrOptions {
  submenuMode?: SubMenuExpandingMode,
  enabled?: boolean,
  subMenuExpandSymbol?: SymbolGlyphModifier | undefined | null,
}

export let symbolStartIcon: SymbolGlyphModifier =
  new SymbolGlyphModifier($r('sys.symbol.checkmark_square_on_square_fill'))
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
export struct MenuLevel1Example {
  pathStack: NavPathStack = new NavPathStack()
  @State menuAttrOptions: MenuAttrOptions = {
    submenuMode: 0,
    enabled: undefined,
    subMenuExpandSymbol: undefined,
  }

  @Builder
  SubMenu56() {
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '三级菜单1',
        endIcon: $r('app.media.app_icon'),

      })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '三级菜单2',
        endIcon: $r('app.media.app_icon'),

      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '三级菜单3',
          endIcon: $r('app.media.app_icon'),

        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '三级菜单4',
          endIcon: $r('app.media.app_icon'),

        })
      }
    }
  }

  @Builder
  SubMenu55() {
    Menu() {
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '二级菜单1',
        endIcon: $r('app.media.app_icon'),
        builder: (): void => this.SubMenu56()
      })
      MenuItem({
        startIcon: $r('app.media.app_icon'),
        content: '二级菜单2',
        endIcon: $r('app.media.app_icon'),
        builder: (): void => this.SubMenu56()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '二级菜单3',
          endIcon: $r('app.media.app_icon'),
          builder: (): void => this.SubMenu56()
        })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '二级菜单4',
          endIcon: $r('app.media.app_icon'),
          builder: (): void => this.SubMenu56()
        })
      }
    }
  }

  build() {
    NavDestination() {
      Menu() {
        MenuItem({ startIcon: $r('app.media.app_icon'), content: '一级菜单1', builder: (): void => this.SubMenu55() })
        MenuItem({
          startIcon: $r('app.media.app_icon'),
          content: '一级菜单2',
          endIcon: $r('app.media.app_icon'),
          builder: (): void => this.SubMenu55()
        })
        MenuItemGroup({ header: '小标题' }) {
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: '一级菜单3',
            endIcon: $r('app.media.app_icon'),
            builder: (): void => this.SubMenu55()
          })
          MenuItem({
            startIcon: $r('app.media.app_icon'),
            content: '一级菜单4',
            endIcon: $r('app.media.app_icon'),
            builder: (): void => this.SubMenu55()
          })
        }
      }
      .subMenuExpandingMode(this.menuAttrOptions.submenuMode)
    }
    .title('MenuLevel1')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}