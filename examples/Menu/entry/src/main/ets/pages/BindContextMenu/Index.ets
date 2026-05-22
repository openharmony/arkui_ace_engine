/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

interface ListCategories {
  title:string,
  utl:string
}

@Entry
@Component
struct Index {
  scroller: Scroller = new Scroller()
  @State items : ListCategories[] = [
    {title:'labelInfoTest',utl:'pages/BindContextMenu/bindContextMenus/LabelInfoAnimation/labelInfoTest'},
    {title:'ContentTest',utl:'pages/BindContextMenu/bindContextMenus/ContentAnimation/Content'},
    {title:'UIConsistency',utl:'pages/BindContextMenu/UIConsistency'},
    {title:'bindMenu',utl:'pages/BindContextMenu/bindMenu'},
    {title:'bindContextMenuTest',utl:'pages/BindContextMenu/bindContextMenuTest'},
    {title:'bindContextMenuTestTwo',utl:'pages/BindContextMenu/bindContextMenus/bindContextMenu'},
    {title:'AvoidMenu',utl:'pages/BindContextMenu/AvoidMenu'}
  ]

  build() {
    Scroll(this.scroller) {
      Column() {
        List({space:'10vp'}) {
          ForEach(this.items,(item : ListCategories) => {
            ListItem() {
              Text(item.title).fontSize(20).fontWeight(FontWeight.Bold).onClick(() => {
                router.pushUrl({url:item.utl})
              })
            }.width('80%').height('50vp').backgroundColor('#ff53ecd9').borderRadius(10)
          })
        }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
      }.width('100%').height('100%')
    }.height('100%')
  }
}