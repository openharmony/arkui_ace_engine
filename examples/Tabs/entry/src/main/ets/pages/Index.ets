/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
  @State message: string = 'Search'
  private items : ListCategories[] = [

    {title:'Swiper_对照',utl:'pages/Swiper_Compare'},
    {title:'Tabs_JS',utl:'pages/Tabs_JS'},
    {title:'Tabs_Custom',utl:'pages/Tabs_Custom'},
    {title:'Tabs_ForEach',utl:'pages/Tabs_ForEach'},
    {title:'Tabs_modifier',utl:'pages/Tabs_modifier'},

  ]

  build() {
    Column() {
      Text("Tabs支持onContentDidScroll/onContentWillScroll回调")
        .width("90%")
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 15 })
        .textAlign(TextAlign.Center)

      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center)
          }.width('90%').height('50vp').backgroundColor('#ff53ecd9').borderRadius(10).onClick(() => {
            router.pushUrl({url:item.utl})
          })
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
    }.width('100%').height('100%')
  }
}
