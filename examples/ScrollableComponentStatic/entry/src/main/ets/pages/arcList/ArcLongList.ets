'use static'

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

import {
  LengthMetrics,
  Column,
  ColumnOptions,
  NavDestination,
  Entry,
  Component,
  Text,
  LazyForEach,
  ObservedV2,
  Trace,
  $r,
  Color,
  BarState,
  IDataSource,
  DataChangeListener,
  DataOperation
} from '@kit.ArkUI';
import { ArcList, ArcListItem, ArcListAttribute, ArcListItemAttribute, ArkListOptions } from '@ohos.arkui.ArcList';
import { ComponentCard } from '../../common/Card';

export class BasicDataSource implements IDataSource<StringData> {
  private listeners: DataChangeListener[] = [];
  private originDataArray: StringData[] = [];

  public totalCount(): int {
    return 0;
  }

  public getData(index: int): StringData {
    return this.originDataArray[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      console.info('add listener');
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos: int = this.listeners.indexOf(listener);
    if (pos >= 0) {
      console.info('remove listener');
      this.listeners.splice(pos, 1);
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach((listener: DataChangeListener): void => {
      listener.onDataReloaded();
    });
  }

  notifyDataAdd(index: int): void {
    this.listeners.forEach((listener: DataChangeListener): void => {
      listener.onDataAdd(index);
    });
  }

  notifyDataChange(index: int): void {
    this.listeners.forEach((listener: DataChangeListener): void => {
      listener.onDataChange(index);
    });
  }

  notifyDataDelete(index: int): void {
    this.listeners.forEach((listener: DataChangeListener): void => {
      listener.onDataDelete(index);
    });
  }

  notifyDataMove(from: int, to: int): void {
    this.listeners.forEach((listener: DataChangeListener): void => {
      listener.onDataMove(from, to);
    });
  }

  notifyDatasetChange(operations: DataOperation[]): void {
    this.listeners.forEach((listener: DataChangeListener): void => {
      listener.onDatasetChange(operations);
    });
  }
}

export class MyDataSource extends BasicDataSource {
  private dataArray: StringData[] = [];

  public totalCount(): int {
    return this.dataArray.length;
  }

  public getData(index: int): StringData {
    return this.dataArray[index];
  }

  public pushData(data: StringData): void {
    this.dataArray.push(data);
    this.notifyDataAdd(this.dataArray.length - 1);
  }
}

@ObservedV2
export class StringData {
  @Trace
  message: string;

  constructor(message: string) {
    this.message = message;
  }
}

@Entry
@Component
export struct ArcLongList {
  private data: MyDataSource = new MyDataSource();

  aboutToAppear(): void {
    for (let i: int = 0; i <= 100; i++) {
      this.data.pushData(new StringData(`Hello ${i}`));
    }
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // Replace $r('app.string.ArcLongList_title') with actual resource file.
        // In this example, the resource file's value is "Handle long lists"
        ComponentCard({ title: $r('app.string.ArcLongList_title') }) {
          ArcList() {
            LazyForEach(this.data, (item: StringData, index: int) => {
              ArcListItem() {
                Text(item.message).fontSize(30).fontColor(Color.White)
              }
              .onClick((): void => {
                item.message += '0';
              })
            }, (item: StringData, index: int) => JSON.stringify(item) + index.toString())
          }.cachedCount(3)
          .space(LengthMetrics.px(10))
          .scrollBar(BarState.Auto)
          .width('466px')
          .height('466px')
          .borderRadius('233px')
          .backgroundColor(Color.Black)
          .margin(50)
        }
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // Replace $r('app.string.ArcLongList_title') with actual resource file.
    // In this example, the resource file's value is "Handle long lists"
    .title($r('app.string.ArcLongList_title'))
  }
}
