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
export function RadioIndexBuilder(name: string, param: Object) {
  RadioIndex()
}

@Entry
@Component
export struct RadioIndex {
  pathStack: NavPathStack = new NavPathStack()
  paths: NavListItem[] = [
    { name: 'RadioCheckedBackgroundColor', path: 'RadioCheckedBackgroundColor' },
    { name: 'RadioSelected', path: 'RadioSelected' },
    { name: 'RadioCustom', path: 'RadioCustom' },
    { name: 'RadioResponse', path: 'RadioResponse' },
    { name: 'RadioBuild', path: 'RadioBuild' },
    { name: 'Radio组合场景1', path: 'RadioLevel1' },
    { name: 'Radio组合场景2', path: 'RadioLevel2' },
    { name: 'Radio组合场景3', path: 'RadioLevel3' },
    { name: 'Radio组合场景4', path: 'RadioLevel4' },
    { name: 'Radio组合场景5', path: 'RadioLevel5' },
    { name: 'RadioWithTheme1 基础主题切换', path: 'RadioWithTheme1' },
    { name: 'RadioWithTheme2 深浅色模式', path: 'RadioWithTheme2' },
    { name: 'RadioWithTheme3 主题+自定义颜色', path: 'RadioWithTheme3' },
    { name: 'RadioWithTheme4 嵌套主题深浅色', path: 'RadioWithTheme4' },
    { name: 'RadioWithTheme5 Token颜色随深浅色切换', path: 'RadioWithTheme5' }
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
    .title('Radio')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}