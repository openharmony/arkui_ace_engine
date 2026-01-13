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

import { TimeTable, ProjectsDataSource, TimeTableDataSource } from './ListDataSource';

@Entry
@Component
struct ListItemGroupExample2 {
  private arr: ArrObject[] = [
    {
      style: ListItemGroupStyle.CARD,
      itemStyles: [ListItemStyle.CARD, ListItemStyle.CARD, ListItemStyle.CARD, ListItemStyle.CARD, ListItemStyle.NONE,
        ListItemStyle.CARD]
    },
    {
      style: ListItemGroupStyle.CARD,
      itemStyles: [ListItemStyle.CARD, ListItemStyle.NONE, ListItemStyle.CARD, ListItemStyle.CARD, ListItemStyle.NONE,
        ListItemStyle.CARD]
    },
    {
      style: ListItemGroupStyle.NONE,
      itemStyles: [ListItemStyle.CARD, ListItemStyle.CARD, ListItemStyle.NONE, ListItemStyle.CARD, ListItemStyle.NONE,
        ListItemStyle.CARD]
    },
    {
      style: ListItemGroupStyle.CARD,
      itemStyles: [ListItemStyle.CARD, ListItemStyle.CARD, ListItemStyle.NONE, ListItemStyle.CARD, ListItemStyle.NONE,
        ListItemStyle.CARD]
    }
  ];

  @Builder
  itemHead(text: string) {
    Text(text)
      .fontSize(20)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .height(100)
      .padding(10)
  }

  @Builder
  itemFoot(num: number) {
    Text('共' + num + '张卡片')
      .fontSize(16)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .height(100)
      .padding(5)
  }

  build() {
    Column() {
      List({ space: 20 }) {
        ForEach(this.arr, (item: ArrObject, index?: number) => {
          ListItemGroup({ header: this.itemHead("卡片"), footer: this.itemFoot(this.arr.length) }) {
            ForEach(item.itemStyles, (itemStyle: number, itemIndex?: number) => {
              ListItem({ style: itemStyle }) {
                if (index != undefined && itemIndex != undefined) {
                  Text('第' + (index + 1) + '个Group中第' + (itemIndex + 1) + '个item')
                    .width('100%')
                    .textAlign(TextAlign.Center)
                    .height('20%')
                    // .layoutWeight(1)
                    .fontSize(20)
                    .backgroundColor(0xFFFFFF)
                }
              }
            }, (item: string) => item)
          }
        })
      }
      .sticky(StickyStyle.Header | StickyStyle.Footer)
      .width('100%')
      .multiSelectable(true)
      .backgroundColor(0xDCDCDC)
    }
    .width('100%')
    .padding({ top: 5 })
  }
}

interface ArrObject {
  style: number;
  itemStyles: number[];
}
