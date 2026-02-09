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
    {title:'Left_100vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftWidth'},
    {title:'Left_48vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftWidth1'},
    {title:'Left_64vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftWidth2'},
    {title:'Left_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/LeftWidth3'},
    {title:'Right_100vp', url:'pages/MenuPlacement/LongPress/Bottom/RightWidth'},
    {title:'Right_48vp', url:'pages/MenuPlacement/LongPress/Bottom/RightWidth1'},
    {title:'Right_64vp', url:'pages/MenuPlacement/LongPress/Bottom/RightWidth2'},
    {title:'Right_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/RightWidth3'},
    {title:'Bottom_100vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomWidth'},
    {title:'Bottom_48vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomWidth1'},
    {title:'Bottom_64vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomWidth2'},
    {title:'Bottom_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/BottomWidth3'},
    {title:'BottomLeft_100vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomLeftWidth'},
    {title:'BottomLeft_48vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomLeftWidth1'},
    {title:'BottomLeft_64vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomLeftWidth2'},
    {title:'BottomLeft_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/BottomLeftWidth3'},
    {title:'BottomRight_100vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomRightWidth'},
    {title:'BottomRight_48vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomRightWidth1'},
    {title:'BottomRight_64vp', url:'pages/MenuPlacement/LongPress/Bottom/BottomRightWidth2'},
    {title:'BottomRight_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/BottomRightWidth3'},
    {title:'LeftTop_100vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftTopWidth'},
    {title:'LeftTop_48vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftTopWidth1'},
    {title:'LeftTop_64vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftTopWidth2'},
    {title:'LeftTop_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/LeftTopWidth3'},
    {title:'LeftBottom_100vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftBottomWidth'},
    {title:'LeftBottom_48vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftBottomWidth1'},
    {title:'LeftBottom_64vp', url:'pages/MenuPlacement/LongPress/Bottom/LeftBottomWidth2'},
    {title:'LeftBottom_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/LeftBottomWidth3'},
    {title:'RightTop_100vp', url:'pages/MenuPlacement/LongPress/Bottom/RightTopWidth'},
    {title:'RightTop_48vp', url:'pages/MenuPlacement/LongPress/Bottom/RightTopWidth1'},
    {title:'RightTop_64vp', url:'pages/MenuPlacement/LongPress/Bottom/RightTopWidth2'},
    {title:'RightTop_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/RightTopWidth3'},
    {title:'RightBottom_100vp', url:'pages/MenuPlacement/LongPress/Bottom/RightBottomWidth'},
    {title:'RightBottom_48vp', url:'pages/MenuPlacement/LongPress/Bottom/RightBottomWidth1'},
    {title:'RightBottom_64vp', url:'pages/MenuPlacement/LongPress/Bottom/RightBottomWidth2'},
    {title:'RightBottom_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/RightBottomWidth3'},
    {title:'NoPlace_100vp', url:'pages/MenuPlacement/LongPress/Bottom/noPlacement'},
    {title:'NoPlace_48vp', url:'pages/MenuPlacement/LongPress/Bottom/noPlacement1'},
    {title:'NoPlace_64vp', url:'pages/MenuPlacement/LongPress/Bottom/noPlacement2'},
    {title:'NoPlace_noWidth', url:'pages/MenuPlacement/LongPress/Bottom/noPlacement3'},
  ]

  build() {
    Column() {
      Text('组件在屏幕的底部中间').fontSize(22)
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