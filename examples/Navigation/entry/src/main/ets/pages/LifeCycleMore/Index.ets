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
  @State message: string = 'Navigation页面生命周期监听能力增强'
  private items : ListCategories[] = [
    {title:'1 UIContext+未指定NavigationID',url:'pages/LifeCycleMore/1MainWindow'},
    {title:'2 UIContext+指定NavigationID',url:'pages/LifeCycleMore/2MainWindowID'},
    {title:'3 全局监听+未指定NavigationID',url:'pages/LifeCycleMore/3MainWindowObserver'},
    {title:'4 全局监听+指定NavigationID',url:'pages/LifeCycleMore/4MainWindowObserverID'},
    {title:'5 全局监听+相同NavigationID',url:'pages/LifeCycleMore/5MainWindowObserverSameID'},
    {title:'6 全局监听+不指定NavigationID+嵌套',url:'pages/LifeCycleMore/6MainWindowObserverNestedNavigation'},
  ]

  build() {
    Column() {
      Text(this.message).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').height(50).backgroundColor("#1770b9")
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