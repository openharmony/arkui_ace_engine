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
  DataChangeListener
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

// BasicDataSource implements the IDataSource interface, used for managing listener monitoring and
// notifying LazyForEach of data updates
class BasicDataSource<string> implements IDataSource<string> {
  private listeners: Array<DataChangeListener> = Array<DataChangeListener>();
  private originDataArray: Array<string> = [];

  public totalCount(): number {
    return this.originDataArray.length;
  }

  public getData(index: number): string {
    return this.originDataArray[index.toInt()];
  }

  // This method is called by the framework to add listener monitoring to the data source for the
  // LazyForEach component
  registerDataChangeListener(listener: DataChangeListener) {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  // This method is called by the framework to remove listener monitoring from the data source for
  // the corresponding LazyForEach component
  unregisterDataChangeListener(listener: DataChangeListener) {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  // Notify the LazyForEach component that all child components need to be reloaded
  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    });
  }

  // Notify the LazyForEach component that a child component needs to be added at the corresponding
  // index
  notifyDataAdd(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
    });
  }

  // Notify the LazyForEach component that data has changed at the corresponding index and the child
  // component needs to be rebuilt
  notifyDataChange(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataChange(index);
    });
  }

  // Notify the LazyForEach component that the child component at the corresponding index needs to be
  // deleted
  notifyDataDelete(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
    });
  }

  // Notify the LazyForEach component to swap child components at the from and to indices
  notifyDataMove(from: number, to: number): void {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to);
    });
  }
}

class MyDataSource extends BasicDataSource<string> {
  private dataArray: string[] = [];

  public totalCount(): number {
    return this.dataArray.length;
  }

  public getData(index: number): string {
    return this.dataArray[index.toInt()];
  }

  public moveDataWithoutNotify(from: number, to: number): void {
    let tmp = this.dataArray.splice(from as int, 1);
    this.dataArray.splice(to as int, 0, tmp[0]);
  }

  public pushData(data: string): void {
    this.dataArray.push(data);
    this.notifyDataAdd(this.dataArray.length - 1);
  }
}

@Entry
@Component
struct MyStateSample {
  @State data: MyDataSource = new MyDataSource();
  @State onMoveValid: boolean = true;

  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.data.pushData(i.toString());
    }
  }

  build() {
    Row() {
      List() {
        LazyForEach(this.data, (item: string) => {
          ListItem() {
            Text(item.toString())
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .size({ height: 100, width: '100%' })
          }.margin(10)
          .borderRadius(10)
          .backgroundColor('#FFFFFFFF')
        }, (item: string) => item)
          .onMove(!this.onMoveValid ? undefined :
            (from: number, to: number) => {
              this.data.moveDataWithoutNotify(from, to);
              console.log('listTest onMove From: ' + from);
              console.log('listTest onMove To: ' + to);
            } as OnMoveHandler,
            {
              onLongPress: (index: number) => {
                console.log('listTest onLongPress: ' + index);
              },
              onDrop: (index: number) => {
                console.log('listTest onDrop: ' + index);
              },
              onDragStart: (index: number) => {
                console.log('listTest onDragStart: ' + index);
              },
              onMoveThrough: (from: number, to: number) => {
                console.log('listTest onMoveThrough From: ' + from);
                console.log('listTest onMoveThrough To: ' + to);
              }  as OnMoveHandler
            } as ItemDragEventHandler
          )
      }
      .onClick((e: ClickEvent) => {
        this.onMoveValid = !this.onMoveValid;
      })
      .width('100%')
      .height('100%')
      .backgroundColor('#FFDCDCDC')
    }
  }
}