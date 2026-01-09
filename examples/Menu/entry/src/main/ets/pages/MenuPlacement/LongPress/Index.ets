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

interface ListCategories {
  title:string,
  url:string
}

@Entry
@Component
struct RotationIndex {
  @State message: string = 'test'

  private items : ListCategories[] = [
    {title:"Top", url:"pages/MenuPlacement/LongPress/Top/Index"},
    {title:"width20%_height50%",url:"pages/MenuPlacement/LongPress/menuWidth"},
    {title:"width30%_height70%", url:"pages/MenuPlacement/LongPress/menuWidth1"},
    {title:"width30%_Top", url:"pages/MenuPlacement/LongPress/menuWidth2"},
    {title:"width30%_Bottom", url:"pages/MenuPlacement/LongPress/menuWidth3"}
  ]

  build() {
    Column() {
      Text('长按组件，弹出菜单').fontSize(22)
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold)
          }.width('90%').height('40vp').backgroundColor('#ff53ecd9').borderRadius(10)
          .onClick(() => {
            this.message = 'Page:' + item.url
            router.pushUrl({url:item.url})
          })
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('70%')
      Text(this.message).fontSize(20)
    }.width('100%').height('100%')
  }
}