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
export function ToggleIndexBuilder(name: string, param: Object) {
  ToggleIndex()
}

@Component
export struct ToggleIndex {
  pathStack: NavPathStack = new NavPathStack()
  paths: NavListItem[] = [
    { name: 'toggle弹窗确认场景', path: 'ToggleWithDialog' },
    { name: 'toggle自定义场景', path: 'ToggleContentModifier' },
    { name: 'toggle场景测试合集', path: 'ToggleUnion' },
    { name: 'ToggleType', path: 'ToggleType' },
    { name: 'ToggleSwitch', path: 'ToggleSwitch' },
    { name: 'ToggleColor', path: 'ToggleColor' },
    { name: 'ToggleNormal', path: 'ToggleNormal' },
    { name: 'ToggleEnable', path: 'ToggleEnable' },
    { name: 'Toggle组合场景1', path: 'ToggleMultiTestLevel0' },
    { name: 'Toggle组合场景2', path: 'ToggleMultiTestLevel1' },
    { name: 'Toggle组合场景3', path: 'ToggleMultiTestLevel2' },
    { name: 'Toggle组合场景4', path: 'ToggleMultiTestLevel3' },
    { name: 'Toggle组合场景5', path: 'ToggleMultiTestLevel4' },
    { name: 'Toggle组合场景6', path: 'ToggleMultiTestLevel5' },
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
    .title('Toggle')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}