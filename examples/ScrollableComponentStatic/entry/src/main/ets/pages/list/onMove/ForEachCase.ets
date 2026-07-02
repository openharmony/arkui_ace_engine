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
  Text,
  Column,
  Component,
  Button,
  ClickEvent,
  List,
  ListOptions,
  ListItem,
  ForEach,
  Color,
  Row,
  LazyForEach,
  DynamicNode,
  OnMoveHandler,
  ItemDragEventHandler,
  IDataSource,TextAlign,
  DataChangeListener
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct ForEachSort {
  @State arr: string[] = ['start'];

  build() {
    Row() {
      List({} as ListOptions) {
        ForEach(this.arr, (item: string) => {
          ListItem() {
            Text(item.toString())
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .size({height: 100, width: '100%'})
          }.margin(10)
          .borderRadius(10)
          .backgroundColor('#FFFFFFFF')
        }, (item: string) => item)
          .onMove((from: int, to: int) => {
            let tmp = this.arr.splice(from, 1);
            this.arr.splice(to, 0, tmp[0]);
          } as OnMoveHandler,
            {
              onLongPress: (index: int) => {
                console.log('listTest onLongPress: ' + index);
              },
              onDrop: (index: int) => {
                console.log('listTest onDrop: ' + index);
              },
              onDragStart: (index: int) => {
                console.log('listTest onDragStart: ' + index);
              },
              onMoveThrough: (from: int, to: int) => {
                console.log('listTest onMoveThrough From: ' + from);
                console.log('listTest onMoveThrough To: ' + to);
              }  as OnMoveHandler
            } as ItemDragEventHandler)
      }
      .width('100%')
      .height('100%')
      .backgroundColor('#FFDCDCDC')
    }
  }
  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.arr.push(i.toString());
    }
  }
}