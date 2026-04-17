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

import { Router, UIContext } from '@ohos.arkui.UIContext'
import router from '@ohos.router'


interface ListCategories {
  title: string,
  url: string,
}

@Entry
@Component
struct Catalogue {
  @State message: string = 'TextAreaTest'
  private items: ListCategories[] = [
    { title: 'WaterFlow_Column_Lazy', url: "pages/EmptyBranch/WaterFlow1" },
    { title: 'WaterFlow_Row_Lazy', url: "pages/EmptyBranch/WaterFlow2" },
    { title: 'layoutDirection', url: "pages/EmptyBranch/WaterFlow4" },
    { title: 'WaterFlow_Repeat', url: "pages/EmptyBranch/WaterFlow6" },
    { title: 'WaterFlow_Modifier', url: "pages/EmptyBranch/WaterFlow_Modifier" },
    { title: 'WaterFlow_Session', url: "pages/EmptyBranch/WaterFlowSessionEmpty" },
    { title: 'grid', url: "pages/EmptyBranch/gridtest" },
    { title: 'list', url: "pages/EmptyBranch/EmptyListPage" }
  ]

  build() {
    Column() {
      Text('WaterFlow组件支持懒加载空分支')
        .fontSize(22)
        .fontColor(0xFFFFFF)
        .textAlign(TextAlign.Center)
        .width('100%')
        .height(50)
        .borderRadius(10)
        .backgroundColor('#ff0bd0b2')
      List({ space: 10 } as ListOptions) {
        ForEach(this.items, (item: ListCategories) => {
          ListItem() {
            Text(item.title).fontSize(16)
          }
          .width('90%')
          .height('40vp')
          .backgroundColor('#ff53ecd9')
          .borderRadius(10)
          .onClick(() => {
            this.getUIContext().getRouter().pushUrl({ url: item.url } as router.RouterOptions)
          })
        })
      }
      .alignListItem(ListItemAlign.Center)
      .margin({ top: '10vp' })
      .width('100%')
      .height('90%')
      .scrollBarColor("#87F787")
    }.width('100%').height('100%')
  }
}
