/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
//测试代码路径
import listAlignListItemTest from '../MyTest/ListAlignListItemTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ListAlignListItemSample {
  @State arr: string[] =
    ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19"]
  @State listItemAlign: ListItemAlign = ListItemAlign.Center;

  aboutToAppear(): void {
    loadComponentTestEntry(listAlignListItemTest)
  }

  build() {
    Column() {
      List({ space: 20, initialIndex: 0 }) {
        ForEach(this.arr, (item: string) => {
          ListItem() {
            Text('' + item)
              .width('100%')
              .height(70)
              .backgroundColor(0xFFFFFF)
          }
          .border({ width: 2, color: Color.Green })
        })
      }
      .height('40%')
      .width("40%")
      .border({ width: 3, color: Color.Red })
      .lanes({ minLength: 40, maxLength: 40 })
      .alignListItem(this.listItemAlign)
      .id('listAlignListItem1')

      Button('ListAlignListItem')
        .margin('5vp')
        .onClick(() => {
          this.listItemAlign = ListItemAlign.End;
        })
      List({ space: 20, initialIndex: 0 }) {
        ForEach(this.arr, (item: string) => {
          ListItem() {
            Text('' + item)
              .width('100%')
              .height(70)
              .backgroundColor(0xFFFFFF)
          }
          .border({ width: 2, color: Color.Green })
        })
      }
      .height('40%')
      .width("40%")
      .border({ width: 3, color: Color.Red })
      .lanes({ minLength: 40, maxLength: 40 })
      .alignListItem(ListItemAlign.Start)
      .id('listAlignListItem2')
    }.backgroundColor(0xDCDCDC)
  }
}