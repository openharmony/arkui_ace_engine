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
export function ButtonIndexBuilder(name: string, param: Object) {
  ButtonIndex()
}

@Entry
@Component
export struct ButtonIndex {
  pathStack: NavPathStack = new NavPathStack()
  paths: NavListItem[] = [
    { name: 'ButtonStyle', path: 'ButtonStyle' },
    { name: 'ButtonJudgment', path: 'ButtonJudgment' },
    { name: 'ButtonLabelStyle', path: 'ButtonLabelStyle' },
    { name: 'ButtonControlSize', path: 'ButtonControlSize' },
    { name: 'ButtonRole', path: 'ButtonRole' },
    { name: 'ButtonCustom', path: 'ButtonCustom' },
    { name: 'ButtonType', path: 'ButtonType' },
    { name: 'ButtonModifier', path: 'ButtonModifier' },
    { name: 'Button组合场景1', path: 'ButtonLevel1' },
    { name: 'Button组合场景2', path: 'ButtonLevel2' },
    { name: 'Button组合场景3', path: 'ButtonLevel3' },
    { name: 'Button组合场景4', path: 'ButtonLevel4' },
    { name: 'Button组合场景5', path: 'ButtonLevel5' },
    { name: 'Button组合场景6', path: 'ButtonLevel6' },
    { name: 'Button组合场景7', path: 'ButtonLevel7' },
    { name: 'Button组合场景8', path: 'ButtonLevel8' },
    { name: 'Button组合场景9', path: 'ButtonLevel9' },
    { name: 'Button组合场景10', path: 'ButtonLevel10' },
    { name: 'Button组合场景11', path: 'ButtonLevel11' }
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
    .title('Button')
    .onBackPressed(() => {
      this.pathStack.pop()
      return true
    })
    .onReady((context: NavDestinationContext) => {
      this.pathStack = context.pathStack;
    })
  }
}