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
import router from '@ohos.router';

interface ListCategories {
  title:string,
  url:string
}

@Entry
@Component
struct Index {
  private items : ListCategories[] = [
    {title:'Navigation-title enhanced',url:'pages/titleStyle/Index'},
    {title:'Navigation removePageById',url:'pages/removePageById/Index'},
    {title:'Navigation symbol',url:'pages/hmSymbol/Index'},
    {title:'Navigation modifier',url:'pages/modifier/Index'},
    {title:'navigationPc',url:'pages/navigationPc/NavDestinationPage'},
  ]

  build() {
    Column() {
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Button(item.title)
              .fontSize(15)
              .onClick(() => {
                router.pushUrl({url:item.url})
              })
          }
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
    }.width('100%').height('100%').backgroundColor(0xE0FFFF)
  }
}