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
'use static'
import { NavList, NavListItem } from '../../utils/navigationList'

@Builder
export function SelectIndexStaticBuilder(name: string, param: Object) {
  SelectIndexStatic()
}

@Entry
@Component
export struct SelectIndexStatic {
  pathStack: NavPathStack = new NavPathStack()
  paths: NavListItem[] = [
    { name: 'SelectArrowModifier', path: 'SelectArrowModifier' },
    { name: 'SelectMenuOutline', path: 'SelectMenuOutline' },
    { name: 'SelectShowInSubWindow', path: 'SelectShowInSubWindow' },
    { name: 'SelectShowDefaultSelectedIcon', path: 'SelectShowDefaultSelectedIcon' },
    { name: 'selectOptionTextModifier', path: 'selectOptionTextModifier' },
    { name: 'selectSelectedOptionTextModifier', path: 'selectSelectedOptionTextModifier' },
    { name: 'selectTextModifier', path: 'selectTextModifier' },
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
    .title('SelectStatic')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}