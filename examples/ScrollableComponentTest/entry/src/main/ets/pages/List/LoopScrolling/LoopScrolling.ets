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

/**
 * This demo demonstrates how to achieve the effect of List cyclic scrolling
 * through the onScrollFrameBegin callback event.
 */

class BasicDataSource implements IDataSource {
  private listeners: DataChangeListener[] = [];
  private originDataArray: string[] = [];

  public totalCount(): number {
    return 0;
  }

  public getData(index: number): string {
    return this.originDataArray[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      console.info('add listener');
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      console.info('remove listener');
      this.listeners.splice(pos, 1);
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  notifyDataAdd(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
    })
  }

  notifyDataChange(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataChange(index);
    })
  }

  notifyDataDelete(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
    })
  }

  notifyDataMove(from: number, to: number): void {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to);
    })
  }
}

class MyDataSource extends BasicDataSource {
  private dataArray: string[] = [];

  public totalCount(): number {
    return this.dataArray.length * 3;
  }

  public getData(index: number): string {
    return this.dataArray[index % this.dataArray.length];
  }

  public addData(index: number, data: string): void {
    this.dataArray.splice(index, 0, data);
    this.notifyDataAdd(index);
  }

  public moveDataWithoutNotify(from: number, to: number): void {
    let tmp = this.dataArray.splice(from, 1);
    this.dataArray.splice(to, 0, tmp[0])
  }

  public pushData(data: string): void {
    this.dataArray.push(data);
    this.notifyDataAdd(this.dataArray.length - 1);
  }

  public deleteData(index: number): void {
    this.dataArray.splice(index, 1);
    this.notifyDataDelete(index);
  }
}

@Entry
@Component
struct Parent {
  private data: MyDataSource = new MyDataSource();
  private scroller: Scroller = new Scroller();

  build() {
    Row() {
      List({initialIndex: 10, scroller: this.scroller}) {
        LazyForEach(this.data, (item: string) => {
          ListItem() {
            Text(item.toString())
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .size({height: 200, width: 200})
          }
          .borderRadius(10)
          .margin(10)
          .backgroundColor('#FFFFFFFF')
        }, (item: string) => item)
      }
      .scrollBar(BarState.Off)
      .width('100%')
      .height('300')
      .backgroundColor('#FFDCDCDC')
      .listDirection(Axis.Horizontal)
      .scrollSnapAlign(ScrollSnapAlign.START)
      .friction(2)
      .onScrollFrameBegin((offset: number, state: ScrollState)=>{
        let currOffset = this.scroller.currentOffset().xOffset;
        let newOffset = currOffset + offset;
        let totalHeight = 220 * 10;
        if (newOffset < totalHeight * 0.5) {
          newOffset += totalHeight;
        } else if (newOffset > totalHeight * 2.5) {
          newOffset -= totalHeight;
        }
        return {offsetRemain: newOffset - currOffset }
      })
    }
  }
  aboutToAppear(): void {
    for (let i = 0; i < 10; i++) {
      this.data.pushData(i.toString())
    }
  }
}