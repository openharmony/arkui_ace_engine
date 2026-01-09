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
    {title:"Left_100vp", url:"pages/MenuPlacement/LongPress/Top/LeftWidth"},
    {title:"Left_48vp", url:"pages/MenuPlacement/LongPress/Top/LeftWidth1"},
    {title:"Left_64vp", url:"pages/MenuPlacement/LongPress/Top/LeftWidth2"},
    {title:"Left_noWidth", url:"pages/MenuPlacement/LongPress/Top/LeftWidth3"},
    {title:"Right_100vp", url:"pages/MenuPlacement/LongPress/Top/RightWidth"},
    {title:"Right_48vp", url:"pages/MenuPlacement/LongPress/Top/RightWidth1"},
    {title:"Right_64vp", url:"pages/MenuPlacement/LongPress/Top/RightWidth2"},
    {title:"Right_noWidth", url:"pages/MenuPlacement/LongPress/Top/RightWidth3"},
    {title:"Top_100vp", url:"pages/MenuPlacement/LongPress/Top/TopWidth"},
    {title:"Top_48vp", url:"pages/MenuPlacement/LongPress/Top/TopWidth1"},
    {title:"Top_64vp", url:"pages/MenuPlacement/LongPress/Top/TopWidth2"},
    {title:"Top_noWidth", url:"pages/MenuPlacement/LongPress/Top/TopWidth3"},
    {title:"TopLeft_100vp", url:"pages/MenuPlacement/LongPress/Top/TopLeftWidth"},
    {title:"TopLeft_48vp", url:"pages/MenuPlacement/LongPress/Top/TopLeftWidth1"},
    {title:"TopLeft_64vp", url:"pages/MenuPlacement/LongPress/Top/TopLeftWidth2"},
    {title:"TopLeft_noWidth", url:"pages/MenuPlacement/LongPress/Top/TopLeftWidth3"},
    {title:"TopRight_100vp", url:"pages/MenuPlacement/LongPress/Top/TopRightWidth"},
    {title:"TopRight_48vp", url:"pages/MenuPlacement/LongPress/Top/TopRightWidth1"},
    {title:"TopRight_64vp", url:"pages/MenuPlacement/LongPress/Top/TopRightWidth2"},
    {title:"TopRight_noWidth", url:"pages/MenuPlacement/LongPress/Top/TopRightWidth3"},
    {title:"LeftTop_100vp", url:"pages/MenuPlacement/LongPress/Top/LeftTopWidth"},
    {title:"LeftTop_48vp", url:"pages/MenuPlacement/LongPress/Top/LeftTopWidth1"},
    {title:"LeftTop_64vp", url:"pages/MenuPlacement/LongPress/Top/LeftTopWidth2"},
    {title:"LeftTop_noWidth", url:"pages/MenuPlacement/LongPress/Top/LeftTopWidth3"},
    {title:"LeftBottom_100vp", url:"pages/MenuPlacement/LongPress/Top/LeftBottomWidth"},
    {title:"LeftBottom_48vp", url:"pages/MenuPlacement/LongPress/Top/LeftBottomWidth1"},
    {title:"LeftBottom_64vp", url:"pages/MenuPlacement/LongPress/Top/LeftBottomWidth2"},
    {title:"LeftBottom_noWidth", url:"pages/MenuPlacement/LongPress/Top/LeftBottomWidth3"},
    {title:"RightTop_100vp", url:"pages/MenuPlacement/LongPress/Top/RightTopWidth"},
    {title:"RightTop_48vp", url:"pages/MenuPlacement/LongPress/Top/RightTopWidth1"},
    {title:"RightTop_64vp", url:"pages/MenuPlacement/LongPress/Top/RightTopWidth2"},
    {title:"RightTop_noWidth", url:"pages/MenuPlacement/LongPress/Top/RightTopWidth3"},
    {title:"RightBottom_100vp", url:"pages/MenuPlacement/LongPress/Top/RightBottomWidth"},
    {title:"RightBottom_48vp", url:"pages/MenuPlacement/LongPress/Top/RightBottomWidth1"},
    {title:"RightBottom_64vp", url:"pages/MenuPlacement/LongPress/Top/RightBottomWidth2"},
    {title:"RightBottom_noWidth", url:"pages/MenuPlacement/LongPress/Top/RightBottomWidth3"},
    {title:"NoPlace_100vp", url:"pages/MenuPlacement/LongPress/Top/noPlacement"},
    {title:"NoPlace_48vp", url:"pages/MenuPlacement/LongPress/Top/noPlacement1"},
    {title:"NoPlace_64vp", url:"pages/MenuPlacement/LongPress/Top/noPlacement2"},
    {title:"NoPlace_noWidth", url:"pages/MenuPlacement/LongPress/Top/noPlacement3"},
  ]

  build() {
    Column() {
      Text('组件在屏幕的顶部中间').fontSize(22)
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
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('80%')
      Text(this.message).fontSize(20)
    }.width('100%').height('100%')
  }
}