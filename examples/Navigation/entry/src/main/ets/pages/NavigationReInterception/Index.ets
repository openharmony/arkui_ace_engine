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
import display from '@ohos.display';

import router from '@ohos.router';
interface ListCategories {
  title:string,
  url:string
}
@Entry
@Component

struct ScreenTestComponents {
  @State message: string = 'Navigation测试'
  private items : ListCategories[] = [
    {title:'test1',url:'pages/NavigationReInterception/test1'},
    {title:'willshow中对页面栈进行操作',url:'pages/NavigationReInterception/A'},
    {title:'didshow中对页面栈进行操作',url:'pages/NavigationReInterception/A1'},
    {title:'willshow和didshow对页面栈进行操作',url:'pages/NavigationReInterception/A2'},
    {title:'modeChange',url:'pages/NavigationReInterception/test2'},
    {title:'willshow和didshow过程中跳出弹窗',url:'pages/NavigationReInterception/test3'},
  ]

  build() {
    Column() {
      Text(this.message).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').height(50).backgroundColor("#FF08528A")
      List({space:'20vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Button(item.title)
              .fontSize(15)
              .labelStyle({maxLines:10})
              .onClick(() => {
                router.pushUrl({url:item.url})
              })
              .type(ButtonType.Normal)
              .backgroundColor(0x317aff)
              .width('100%')
              .fontSize(15)
              .fontColor(0x000000)
              .labelStyle({maxLines:1, overflow: TextOverflow.MARQUEE})
          }
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('90%').height('90%')
    }.width('100%').height('100%').backgroundColor('#FFDDE7F6')
  }
}