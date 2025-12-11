/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { SearchEnableAutoSpacing } from './enableAutoSpacing';

const childPageMap_Stack = new NavPathStack()

interface ListCategories {
  title: string,
  dest: string
}

@Entry
@Component
export struct SearchPage {
  private items: ListCategories[] = [
    { title: 'SearchEnableAutoSpacing', dest: 'SearchEnableAutoSpacing' },
  ]

  @Builder
  pageMap(name: string) {
    if (name === 'SearchEnableAutoSpacing') {
      SearchEnableAutoSpacing()
    }
  }

  build() {
    Column() {
      NavDestination() {
        Navigation(childPageMap_Stack) {
          Column({ space: 20 }) {
            List({ space: '10vp' }) {
              ForEach(this.items, (item: ListCategories) => {
                ListItem() {
                  Column() {
                    Text(item.title).fontSize(16).fontWeight(FontWeight.Bold)
                  }
                }
                .width('90%')
                .height('40vp')
                .backgroundColor('#ff4dc0ef')
                .borderRadius(10)
                .onClick(() => {
                  childPageMap_Stack.pushPathByName(item.dest, null)
                })
              })
            }.alignListItem(ListItemAlign.Center).margin({ top: '10vp' }).width('100%').height('90%')
          }
          .width('100%')
          .padding({ top: 30 })
        }
        .hideTitleBar(true)
        .mode(NavigationMode.Stack)
        .titleMode(NavigationTitleMode.Mini)
        .navDestination(this.pageMap)
      }.hideBackButton(true)
    }
  }
}