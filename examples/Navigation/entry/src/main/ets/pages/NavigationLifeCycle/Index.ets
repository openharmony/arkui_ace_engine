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
struct Index {
  @State message: string = '【基础能力】新增Navigation页面生命周期回调'
  private items : ListCategories[] = [
    {title:'1 未指定id监听',url:'pages/NavigationLifeCycle/MainWindow'},
    {title:'2 指定id监听',url:'pages/NavigationLifeCycle/MainWindowID'},
    {title:'3 willshow和didshow执行过程中，跳出弹窗',url:'pages/NavigationLifeCycle/Test1'},
    {title:'4 自定义动画',url:'pages/NavigationLifeCycle/customNavContentTransition'},
  ]

  build() {
    Column() {
      Text(this.message).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').padding(5).backgroundColor("#1770b9")
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