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
  @State message: string = 'NavigationSafeAreaPadding'
  private items : ListCategories[] = [
    {title:'Navigation工具栏和标题栏自定义',url:'pages/NavigationSafeAreaPadding/test1'},
    {title:'Navigation工具栏和标题栏非自定义',url:'pages/NavigationSafeAreaPadding/test2'},
    {title:'Navigation只设置工具栏非自定义',url:'pages/NavigationSafeAreaPadding/test3'},
    {title:'Navigation只设置标题栏非自定义',url:'pages/NavigationSafeAreaPadding/test4'},
    {title:'不设置标题栏和工具栏布局方式属性barStyle',url:'pages/NavigationSafeAreaPadding/test5'},
    {title:'Navigation滑动分割线',url:'pages/NavigationSafeAreaPadding/test6'},
    {title:'Navigation嵌套场景',url:'pages/NavigationSafeAreaPadding/test7'},

  ]

  build() {
    Column() {
      Text(this.message).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').padding(5).backgroundColor("#1770b9")
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title)
              .width('90%')
              .backgroundColor(Color.Pink)
              .padding('5vp')
              .onClick(() => {
                router.pushUrl({url:item.url})
              })
          }
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
    }.width('100%').height('100%').backgroundColor(0xE0FFFF)
  }
}