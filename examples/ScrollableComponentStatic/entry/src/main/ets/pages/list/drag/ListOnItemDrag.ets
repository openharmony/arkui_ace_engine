'use static'
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
import {
  Entry,
  Builder,
  Text,
  TextAlign,
  Component,
  List,
  ListItem,
  ListItemAlign,
  ForEach,
  Button,
  Column,
  ItemDragInfo,
  CustomBuilder
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'

@Entry
@Component
struct Index {
  @State listArr: string[] = ['1'] as string[];
  @State isChange: boolean = true;

  @Builder
  pixelMapBuilder() {
    Column() {
      Text('123')
        .fontSize(16)
        .backgroundColor('#ffcc00')
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }
    .backgroundColor('#330011')
  }

  aboutToAppear(): void {
    for (let i = 0; i < 16; i++) {
      this.listArr.push(i.toString());
    }
  }

  build() {
    Column() {
      List() {
        ForEach(this.listArr, (item: string) => {
          ListItem() {
            Text(item)
          }
          .width(80)
          .height(80)
          .borderRadius(4)
          .backgroundColor('#ffcc00')
        }, (item: string) => item)
      }
      .width('100%')
      .height(500)
      .alignListItem(ListItemAlign.Center)
      .backgroundColor('#ff00')
      .onItemDragStart((event: ItemDragInfo): CustomBuilder => {
        console.log('xxx onItemDragStart')
        return this.pixelMapBuilder
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: int, insertIndex: int, isSuccess: boolean) => {
        console.log('xxx onItemDrop')
      })
      .onItemDragLeave(this.isChange ? (event: ItemDragInfo) => {
        console.log('xxx onItemDragLeave')
      } : undefined)

      Button('Change').onClick(() => {
        this.isChange = !this.isChange;
      })
    }
    .width('100%')
    .height('100%')
  }
}