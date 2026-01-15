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

/*
 * Description: 添加元素后依旧能让Scroller保持在顶部
 * Writer: dailihuan
 */

@Observed
export class ObservedArray<T> extends Array<T> {
  constructor(args?: T[]) {
    if (args instanceof Array) {
      super(...args);
    } else {
      super();
    }
  }
}

class BasicDataSource<T> implements IDataSource {
  private listeners: DataChangeListener[] = [];

  public totalCount(): number {
    return 0;
  }

  public getData(index: number): T | undefined {
    return undefined;
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }
}

export class LazyDataSource<T> extends BasicDataSource<T> {
  dataArray: T[] = [];

  public totalCount(): number {
    return this.dataArray.length;
  }

  public getData(index: number): T {
    return this.dataArray[index];
  }

  public pushDataPositionArray(index: number, newData: ObservedArray<T>): void {
    this.dataArray.splice(index, 0, ...newData);
    this.notifyDataReload();
  }
}


@Entry
@ComponentV2
export struct Index {
  @Local isRefreshing: boolean = false;
  @Local refreshText: string = '';
  @Local lazyDataModel: LazyDataSource<string> = new LazyDataSource();
  @Local listScroller: ListScroller = new ListScroller();
  @Local timer: number = 1;
  @Local listItemHeight: number = 0;

  aboutToAppear(): void {
    let arr: string[] = [];
    for (let i = 0; i < 30; i++) {
      arr.push(`${i}Text Item`);
    }
    this.lazyDataModel.dataArray = arr;
    this.lazyDataModel.notifyDataReload();
  }

  @Builder
  getRefreshBuilder() {
    Row({ space: 8 }) {
      LoadingProgress()
        .width(20)
        .aspectRatio(1)
      Text(this.refreshText)
        .fontSize(14)
        .fontColor('#818181')
    }
  }

  async getData(timer: number) {
    let arr: string[] = [];
    for (let i = 5; i > 0; i--) {
      arr.push(`第 ${timer} 次 add HeadItem ${i}`);
    }
    setTimeout(() => {
      // 向lazyDataModel数据源头部添加一组数据，并使用scrollToIndex、scrollTo滚动到指定位置，使当前页面顶部展示数据不变。
      this.lazyDataModel.pushDataPositionArray(0, arr);
      // 使用scrollTo滚动到指定偏移量
      this.listScroller.scrollTo({ yOffset: 0, xOffset: 0 });
      this.isRefreshing = false;
    }, 500);
  }

  build() {
    Column() {
      Button(`刷新`)
        .onClick(async ()=>{
          await this.getData(this.timer);
          this.timer++;
        })

      Refresh({ refreshing: $$this.isRefreshing, builder: this.getRefreshBuilder() }) {
        List({ scroller: this.listScroller }) {
          LazyForEach(this.lazyDataModel, (item: string) => {
            ListItem() {
              Column() {
                Text(item)
                  .fontSize(18)
                  .height(52)
              }
              .height(56)
              .width('100%')
              .padding({ left: 10, right: 10 })
            }
            .onAreaChange((oldValue: Area, newValue: Area) => {
              this.listItemHeight = Number(newValue.height); // 获取item的高度
            })
          }, (item: string) => item.toString())
        }
        .width('100%')
        .height('100%')
        .scrollBar(BarState.Off)
        .edgeEffect(EdgeEffect.None)
      }
      .onStateChange(async (status) => {
        switch (status) {
          case RefreshStatus.Inactive:
            break;
          case RefreshStatus.Drag:
            this.refreshText = '继续往下拉';
            break;
          case RefreshStatus.OverDrag:
            this.refreshText = '松手加载';
            break;
          case RefreshStatus.Refresh:
            this.refreshText = '加载中';
            await this.getData(this.timer);
            this.timer++;
            break;
          case RefreshStatus.Done:
            this.refreshText = '加载成功';
        }
      })
    }
  }
}