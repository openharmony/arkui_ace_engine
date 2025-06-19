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
export function SelectIndexBuilder(name: string, param: Object) {
  SelectIndex()
}

@Entry
@Component
export struct SelectIndex {
  pathStack: NavPathStack = new NavPathStack()
  paths: NavListItem[] = [
    { name: 'SelectDivider', path: 'SelectDivider' },
    { name: 'SelectOption', path: 'SelectOption' },
    { name: 'SelectSymbolModifier', path: 'SelectSymbolModifier' },
    { name: 'SelectLanguagePadding', path: 'SelectLanguagePadding' },
    { name: 'SelectLanguageChange', path: 'SelectLanguageChange' },
    { name: 'SelectOnSelect', path: 'SelectOnSelect' },
    { name: 'SelectNormal', path: 'SelectOptionMenu' },
    { name: 'SelectSymbol', path: 'SelectSymbol' },
    { name: 'SelectCustom', path: 'SelectCustom' },
    { name: 'SelectDividerNormal', path: 'SelectDividerOptions' },
    { name: 'SelectDividerNull', path: 'SelectDividerNull' },
    { name: 'SelectArrow', path: 'SelectArrow' },
    { name: 'SelectModifier', path: 'SelectOptionTextModifier' },
    { name: 'SelectLevel00', path: 'SelectLevel00' },
    { name: 'SelectLevel11', path: 'SelectLevel11' },
    { name: 'SelectLevel2', path: 'SelectLevel2' },
    { name: 'SelectLevel3', path: 'SelectLevel3' },
    { name: 'SelectLevel4', path: 'SelectLevel4' }
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
    .title('Select')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}