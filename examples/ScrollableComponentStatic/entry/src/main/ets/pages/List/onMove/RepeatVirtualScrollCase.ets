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
'use static'

import {
  Entry,
  Text,
  Column,
  Component,
  Button,
  ClickEvent,
  List,
  ListItem,
  ForEach,
  Color,
  Row,
  ClickEvent,
  LazyForEach,
  DynamicNode,
  OnMoveHandler,
  ItemDragEventHandler,
  IDataSource,TextAlign,
  DataChangeListener,
  RepeatItem,
  Repeat
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct ForEachSort {
  @State arr: Array<string> = new Array<string>();

  build() {
    Row() {
      List() {
        Repeat<string>(this.arr)
        // 通过设置onMove，使能拖拽排序。
          .onMove((from: number, to: number) => {
            let temp = this.arr.splice(from as int, 1);
            this.arr.splice(to as int, 0, temp[0]);
          } as OnMoveHandler,
            {
              onLongPress: (index: number) => {
                console.log('ljn onLongPress: ' + index);
              },
              onDrop: (index: number) => {
                console.log('ljn onDrop: ' + index);
              },
              onDragStart: (index: number) => {
                console.log('ljn onDragStart: ' + index);
              },
              onMoveThrough: (from: number, to: number) => {
                console.log('ljn onMoveThrough From: ' + from);
                console.log('ljn onMoveThrough To: ' + to);
              }  as OnMoveHandler
            } as ItemDragEventHandler)
          .each((obj: RepeatItem<string>) => {
            ListItem() {
              Text(obj.item)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .size({height: 100, width: "100%"})
            }.margin(10)
            .borderRadius(10)
            .backgroundColor("#FFFFFFFF")
          })
          .key((item: string, index: number) => {
            return item;
          })
          .virtualScroll({ totalCount: this.arr.length })
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