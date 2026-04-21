/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import router from '@ohos.router';

interface Categories {
  info:string,
  url:string
}

@Entry
@Component
struct Index {
  private items: Categories[] = [
    {url: "pages/Menu1_1/bindMenu/options_PlacementTest", info: "bindMenu_options_PlacementTest"},
    {url: "pages/Menu1_1/bindMenu/options_TitleTest", info: "bindMenu_options_TitleTest"},
    {url: "pages/Menu1_1/bindMenu/options_contentTest", info: "bindMenu_options_contentTest"},
    {url: "pages/Menu1_1/bindMenu/options_TransitionTest", info: "bindMenu_options_TransitionTest"},
    {url: "pages/Menu1_1/bindMenu/bindMenu_modifier", info: "bindMenu_modifier"},
    {url: "pages/Menu1_1/bindMenu/bindMenu", info: "bindMenu"},
    {url: "pages/Menu1_1/bindContextMenu/bindContextMenu_LongPress", info: "bindContextMenu_LongPress"},
    {url: "pages/Menu1_1/bindContextMenu/bindContextMenu_23", info: "bindContextMenu_23"},
    {url: "pages/Menu1_1/bindContextMenu/bindContextMenu_ContextMenuOptions", info: "bindContextMenu_ContextMenuOptions"},
    {url: "pages/Menu1_1/bindContextMenu/bindContextMenu_previewScaleMode", info: "bindContextMenu_previewScaleMode"},
    {url: "pages/Menu1_1/bindContextMenu/bindContextMenu_AvailableLayoutArea", info: "bindContextMenu_AvailableLayoutArea"},
    {url: "pages/Menu1_1/bindContextMenu/bindContextMenu", info: "bindContextMenu"}
  ]


  build() {
    Column() {
      Text('菜单控制示例代码').fontSize(22)
      List({ space: '10vp' }) {
        ForEach(this.items, (item: Categories) => {
          ListItem() {
            Text(item.info).fontSize(16).fontWeight(FontWeight.Bold)
          }
          .width('90%')
          .height('40vp')
          .backgroundColor('#ff53ecd9')
          .borderRadius(10)
          .onClick(() => {
            router.pushUrl({ url: item.url })
          })
        })
      }.alignListItem(ListItemAlign.Center).margin(({ top: '10vp' })).width('100%').height('70%')
    }.width('100%').height('100%')
  }
}