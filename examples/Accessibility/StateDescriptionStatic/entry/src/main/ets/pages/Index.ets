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

'use static'

import { Entry, Component, Column, Row, SliderStyle, Slider, Text, List, ForEach, ListItemAlign, FontWeight, TextAlign,
  Margin, ListItem, Promise
} from '@ohos.arkui.component';
import { State } from '@ohos.arkui.stateManagement'
import router from '@ohos.router';
import { BusinessError } from '@ohos.base'

interface ListCategories {
  title: string,
  url: string
}

@Entry
@Component
struct InformationDarkMode {
  @State message: string = 'InformationDarkMode'
  private items : ListCategories[] = [
    { title: 'button', url: 'pages/button_Test' },
    { title: 'toggle', url: 'pages/toggle_Test'},
    { title: 'checkbox', url: 'pages/checkbox_Test'},
    { title: 'radio', url: 'pages/radio_Test'},
    { title: 'dongTai', url: 'pages/dongTai'},
  ]

  async routePage(demoUrl: string) {
    this.getUIContext().getRouter().pushUrl({
      url: demoUrl,
    })
  }

  build() {
    Column() {
      Text('自定义状态播报文本' ).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').height(50).borderRadius(10).backgroundColor(0x0000FF)
      List({space:'10vp'}) {
        ForEach(this.items, (item : ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(19).fontWeight(FontWeight.Bold)
          }.onClick(() => {
            this.routePage(item.url);
            // router.pushUrl({url: item.url} as RouterOptions)
          }).width('90%').height('55vp').backgroundColor(0x6666FF).borderRadius(10).margin({top:'10vp'} as Margin)
        })
      }.alignListItem(ListItemAlign.Center).margin({top:'10vp'} as Margin).width('100%').height('90%')
    }.width('100%').height('100%').backgroundColor(0xE0FFFF)
  }
}