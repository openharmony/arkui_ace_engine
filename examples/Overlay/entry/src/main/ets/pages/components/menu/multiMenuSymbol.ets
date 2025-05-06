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

import { SymbolGlyphModifier } from '@kit.ArkUI';

@Builder
export function MultiMenuSymbolBuilder(name: string, param: Object) {
  MultiMenuSymbolExample()
}

@Entry
@Component
struct MultiMenuSymbolExample {
  @State startIconModifier: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_mic')).fontSize('24vp');
  @State endIconModifier: SymbolGlyphModifier = new SymbolGlyphModifier($r('sys.symbol.ohos_trash')).fontSize('24vp');
  @State selectIconModifier: SymbolGlyphModifier =
    new SymbolGlyphModifier($r('sys.symbol.checkmark')).fontSize('24vp');
  @State select: boolean = true;
  pathStack: NavPathStack = new NavPathStack()

  @Builder
  SubMenu() {
    Menu() {
      MenuItem({ content: '复制', labelInfo: 'Ctrl+C' })
      MenuItem({ content: '粘贴', labelInfo: 'Ctrl+V' })
    }
  }

  @Builder
  MyMenu() {
    Menu() {
      MenuItem({ symbolStartIcon: this.startIconModifier, content: '菜单选项' })
      MenuItem({ symbolStartIcon: this.startIconModifier, content: '菜单选项' })
        .enabled(false)
      MenuItem({
        symbolStartIcon: this.startIconModifier,
        content: '菜单选项',
        symbolEndIcon: this.endIconModifier,
        builder: (): void => this.SubMenu()
      })
      MenuItemGroup({ header: '小标题' }) {
        MenuItem({
          symbolStartIcon: this.startIconModifier,
          content: '菜单选项',
          symbolEndIcon: this.endIconModifier,
          builder: (): void => this.SubMenu()
        })
        MenuItem({
          symbolStartIcon: this.startIconModifier,
          content: '菜单选项',
          symbolEndIcon: this.endIconModifier,
          builder: (): void => this.SubMenu()
        })
      }

      MenuItem({
        content: '菜单选项',
      })
        .selected(this.select)
        .selectIcon(this.selectIconModifier)
    }
  }

  build() {
    NavDestination() {
      Row() {
        Column() {
          Text('click to show menu')
            .fontSize(50)
            .fontWeight(FontWeight.Bold)
        }
        .bindMenu(this.MyMenu)
        .width('100%')
      }
      .height('100%')
    }
    .title('MultiMenuSymbol')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}