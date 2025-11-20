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

import { TextAreaPage } from './TextArea/Index'
import { TextInputPage } from './TextInput/Index';
import { SearchPage } from './Search/Index';
import { TextPage } from './Text/Index';
import { StyledStringPage } from './StyledString/Index';

const pageMap_Stack = new NavPathStack()

interface ListCategories {
  comp: string,
  dest: string
}

@Entry
@Component
struct Index {
  private items: ListCategories[] = [
    { comp: 'Text', dest: 'TextPage' },
    { comp: 'TextInput', dest: 'TextInputPage' },
    { comp: 'TextArea', dest: 'TextAreaPage' },
    { comp: 'Search', dest: 'SearchPage' },
    { comp: 'StyledString', dest: 'StyledStringPage' }
  ]

  @Builder
  pageMap(name: string) {
    if (name === 'TextPage') {
      TextPage();
    } else if (name === 'TextInputPage') {
      TextInputPage()
    } else if (name === 'TextAreaPage') {
      TextAreaPage()
    } else if (name === 'SearchPage') {
      SearchPage()
    } else if (name === 'StyledStringPage') {
      StyledStringPage()
    }
  }

  build() {
    Column() {
      Navigation(pageMap_Stack) {
        Column({ space: 20 }) {
          List({ space: '10vp' }) {
            ForEach(this.items, (item: ListCategories) => {
              ListItem() {
                Column() {
                  Text(item.comp).fontSize(16).fontWeight(FontWeight.Bold)
                }
              }
              .width('90%')
              .height('40vp')
              .backgroundColor('#ff53ecd9')
              .borderRadius(10)
              .onClick(() => {
                pageMap_Stack.pushPathByName(item.dest, null)
              })
            })
          }.alignListItem(ListItemAlign.Center).margin({ top: '10vp' }).width('100%').height('90%')
        }
        .width('100%')
        .padding({ top: 30 })
      }
      .mode(NavigationMode.Stack)
      .titleMode(NavigationTitleMode.Mini)
      .navDestination(this.pageMap).hideBackButton(true)
    }
  }
}