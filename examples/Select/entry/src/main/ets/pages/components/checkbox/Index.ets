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
export function CheckboxIndexBuilder(name: string, param: Object) {
  CheckboxIndex()
}

@Entry
@Component
export struct CheckboxIndex {
  pathStack: NavPathStack = new NavPathStack()
  paths: NavListItem[] = [
    { name: 'CheckboxShape', path: 'CheckboxShape' },
    { name: 'CheckboxMark', path: 'CheckboxMark' },
    { name: 'CheckboxCustom', path: 'CheckboxCustom' },
    { name: 'CheckboxIndicator', path: 'CheckboxIndicator' },
    { name: 'CheckboxSize', path: 'CheckboxSize' },
    { name: 'CheckboxGroup', path: 'CheckboxGroup' },
    { name: 'CheckboxChange', path: 'CheckboxChange' },
    { name: 'CheckboxGroupIndicator', path: 'CheckboxGroupIndicator' },
    { name: 'CheckboxGroupCustom', path: 'CheckboxGroupCustom' },
    { name: 'CheckboxModifier', path: 'CheckboxModifier' },
    { name: 'CheckboxThemeControl', path: 'CheckboxThemeControl' },
    { name: 'Checkbox组合场景1', path: 'CheckboxMultiTestLevel0' },
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
    .title('Checkbox')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}