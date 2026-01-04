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

 {title:'Navigation use symbol set fontSize、fontColor、fontWeight、effectStrategy',url:'pages/hmSymbol/test1'},
    {title:'Navigation use symbol set fontSize、fontColor、fontWeight、renderingStrategy',url:'pages/hmSymbol/test2'},
    {title:'Navigation use symbol set symbolEffect（isActive）',url:'pages/hmSymbol/test4'},
    {title:'test5',url:'pages/hmSymbol/test5'},
    {title:'test6',url:'pages/hmSymbol/test6'},
    {title:'test7',url:'pages/hmSymbol/test7'},
    {title:'test8',url:'pages/hmSymbol/test8'},
    {title:'Ntest9',url:'pages/hmSymbol/test9'},
    {title:'test10',url:'pages/hmSymbol/test10'},
    {title:'test11',url:'pages/hmSymbol/test11'},
    {title:'test12',url:'pages/hmSymbol/test12'},
    {title:'test13',url:'pages/hmSymbol/test13'}

@Entry
@Component
struct Index {
  @State message: string = 'Navigation titleStyle enhanced'
  private items : ListCategories[] = [
    {title:'Navigation use symbol set fontSize、fontColor、fontWeight、effectStrategy',url:'pages/titleStyle/Test1'},
    {title:'Navigation use symbol set fontSize、fontColor、fontWeight、renderingStrategy',url:'pages/titleStyle/Test2'},
    {title:'Navigation-title set backgroundColor',url:'pages/titleStyle/Test3'},
    {title:'Navigation-title set blur',url:'pages/titleStyle/Test4'},
    {title:'Navigation-title set blur&backgroundColor',url:'pages/titleStyle/Test5'},
    {title:'test6',url:'pages/titleStyle/Test6'},
    {title:'test7',url:'pages/titleStyle/Test7'},
    {title:'test8',url:'pages/titleStyle/Test8'},
    {title:'test9',url:'pages/titleStyle/Test9'},
    {title:'test10',url:'pages/titleStyle/Test10'}
  ]

  build() {
    Column() {
      Text(this.message)
        .fontSize(22).fontColor(0xFFFFFF)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .width('100%').padding(5)
        .backgroundColor('#1770b9')
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