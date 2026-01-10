/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

class PageClass {
  title: string
  url: string
  key: string

  constructor(title: string, url: string, key: string) {
    this.title = title;
    this.url = url;
    this.key = key;
  }
}

const testList1: PageClass[] = [
  new PageClass('菜单基础场景', 'pages/MenuUX/MenuKeyboardAvoid/baseMenu', 'bindMenu'),
  new PageClass('selet基础场景', 'pages/MenuUX/MenuKeyboardAvoid/baseSelect', 'select'),
  new PageClass('bindMenu', 'pages/MenuUX/MenuKeyboardAvoid/bindMenu', 'bindMenu'),
  new PageClass('select', 'pages/MenuUX/MenuKeyboardAvoid/select', 'select'),
  new PageClass('bindContextMenu', 'pages/MenuUX/MenuKeyboardAvoid/bindContextMenu', 'bindContextMenu'),
  new PageClass('openMenu', 'pages/MenuUX/MenuKeyboardAvoid/openMenu', 'openMenu'),
  new PageClass('openMenu', 'pages/MenuUX/MenuKeyboardAvoid/updateMenu', 'updateMenu'),
  new PageClass('selectAttribute', 'pages/MenuUX/MenuKeyboardAvoid/selectAttribute', 'selectAttribute'),
  new PageClass('previewLayoutRegionMargin', 'pages/MenuUX/MenuKeyboardAvoid/previewLayoutRegionMargin', 'previewLayoutRegionMargin'),
]

@Entry
@Component
struct MenuKeyboardAvoid {
  build() {
    Scroll() {
      Column({ space: 10 }) {
        List({ space: 8 }) {
          ForEach(testList1, (item: PageClass) => {
            ListItem() {
              Button(item.title)
                .width('85%')
                .fontSize(20)
                .onClick(() => {
                  this.getUIContext().getRouter().pushUrl({
                    url: item.url
                  }).catch(() => {
                  })
                })
                .key(item.key)
            }.align(Alignment.Center).margin({
              bottom: 10
            })
          }, (item: PageClass) => item.title)
        }.padding(5).alignListItem(ListItemAlign.Center)
      }.width('100%').height('100%').align(Alignment.Top)
    }.width('100%').height('100%').align(Alignment.Top)
  }
}