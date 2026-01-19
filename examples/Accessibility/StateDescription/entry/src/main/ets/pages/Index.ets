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
  utl:string
}

@Entry
@Component
struct InformationHomePage {
  @State message: string = 'InformationDarkMode'
  private items : ListCategories[] = [
    {title:'button',utl:'pages/button_Test'},
    {title:'toggle',utl:'pages/toggle_Test'},
    {title:'checkbox',utl:'pages/checkbox_Test'},
    {title:'radio',utl:'pages/radio_Test'},
    {title:'dongtai',utl:'pages/Dongtai'},
  ]

  build() {
    Column() {
      Text('自定义状态播报文本' ).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').height(50).borderRadius(10).backgroundColor(0x0000FF)
      List({space:'10vp'}) {
        ForEach(this.items,(item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(19).fontWeight(FontWeight.Bold)
          }.onClick(() => {
            router.pushUrl({url:item.utl})
          }).width('90%').height('55vp').backgroundColor(0x6666FF).borderRadius(10).margin({top:'10vp'})
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'}).width('100%').height('90%')
    }.width('100%').height('100%').backgroundColor(0xE0FFFF)
  }
}