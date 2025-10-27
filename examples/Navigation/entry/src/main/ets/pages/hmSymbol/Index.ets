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
  @State message: string = 'HM Symbol adpat'
  private items : ListCategories[] = [
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
  ]

  build() {
    Column() {
      Text(this.message).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').padding(5).backgroundColor("#1770b9")
      ForEach(this.items,(item : ListCategories) => {
        Button(item.title)
          .padding(2)
          .margin({top:5,bottom:5,left:2,right:2})
          .labelStyle({maxLines:3, font: {size:10}})
          .width('100%')
          .onClick(() => {
            router.pushUrl({url:item.url})
          })
      })
    }.width('100%').height('100%').backgroundColor(0xE0FFFF)
  }
}