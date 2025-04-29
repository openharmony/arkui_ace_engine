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

import { NavList, NavListItem } from '../../utils/navigationList'

@Builder
export function MenuIndexBuilder(name: string, param: Object) {
  MenuIndex()
}

@Entry
@Component
export struct MenuIndex {
  pathStack: NavPathStack = new NavPathStack()
  paths: NavListItem[] = [
    { name: 'MultiMenu', path: 'MultiMenu' },
    { name: 'MultiMenuSymbol', path: 'MultiMenuSymbol' },
    { name: 'BindMenu', path: 'BindMenu' },
    { name: 'BindMenuCustomBuilder', path: 'BindMenuCustomBuilder' },
    { name: 'BindMenuSymbolIcon', path: 'BindMenuSymbolIcon' },
    { name: 'BindMenuBackgroundEffect', path: 'BindMenuBackgroundEffect' },
    { name: 'BindMenuBackgroundBlurStyle', path: 'BindMenuBackgroundBlurStyle' },
    { name: 'BindContextMenu', path: 'BindContextMenu' },
    { name: 'BindContextMenuRightClick', path: 'BindContextMenuRightClick' },
    { name: 'BindContextMenuPreviewMode', path: 'BindContextMenuPreviewMode' },
    { name: 'BindContextMenuPreviewCustomBuilder', path: 'BindContextMenuPreviewCustomBuilder' },
    { name: 'BindContextMenuIsShown', path: 'BindContextMenuIsShown' },
    { name: 'BindContextMenuTransition', path: 'BindContextMenuTransition' },
    { name: 'BindContextMenuHoverScale', path: 'BindContextMenuHoverScale' },
    { name: 'MenuDivider', path: 'MenuDivider' },
    { name: 'MenuExpand', path: 'MenuExpand' },
    { name: 'MenuPressStatus', path: 'MenuPressStatus' },
  ]

  build() {
    NavDestination() {
      Scroll() {
        NavList({
          pages: this.paths,
          onPathChange: (item: NavListItem) => {
            this.pathStack.pushPath({ name: item.path })
          }
        })
      }
    }
    .title('Menu')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}