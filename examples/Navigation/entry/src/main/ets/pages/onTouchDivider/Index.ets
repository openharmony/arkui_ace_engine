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
struct MenuIndex {
  @State message: string = 'ssasdadsadsa【基础能力】分割线触摸直接响应'
  private items : ListCategories[] = [
    {title:'Navigation分割线测试',url:'pages/37-ssasdadsadsa/test1'},
  ]

  build() {
      Column() {
        Text(this.message).fontSize(22).fontColor(0xFFFFFF).fontWeight(FontWeight.Bold).textAlign(TextAlign.Center).width('100%').height(50).backgroundColor('#FF08528A')
        List({space:'20vp'}) {
          ForEach(this.items,(item : ListCategories) => {
            ListItem() {
              Button(){
                Row() {
                  LoadingProgress().width(40).height(40).color(0xFFFFFF)
                  Text(item.title).fontSize(16).fontColor(0xffffff).margin({ left: 5, right: 12 })
                }.alignItems(VerticalAlign.Center)

              }
              .type(ButtonType.Normal)
              .backgroundColor(0x317aff)
              .width('100%')
              .fontSize(15)
              .fontColor(0x000000)
              .labelStyle({maxLines:1, overflow: TextOverflow.MARQUEE})
              .onClick(() => {
                router.pushUrl({url:item.url})
              })
            }
          })
        }.expandSafeArea()
        .alignListItem(ListItemAlign.Center)
        .width('95%').height('90%')
      }.width('100%').height('100%').backgroundColor('#FFDDE7F6')
      .expandSafeArea()
    }
}