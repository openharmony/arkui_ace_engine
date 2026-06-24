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

// [Start list_nested_lazy_layout]
import {
  IDataSource,
  DataChangeListener,
  Entry,
  Component,
  NavDestination,
  Column,
  List,
  ListOptions,
  ListItem,
  Text,
  $r,
  Color,
  LazyVGridLayout,
  LazyForEach,
  TextAlign,
  LengthMetrics,
  LazyVWaterFlowLayout,
  Axis
} from '@kit.ArkUI';

export class BasicDataSource implements IDataSource<int> {
  private listeners: DataChangeListener[] = [];
  protected dataArray: Array<int> = new Array<int>();

  public totalCount(): int {
    return this.dataArray.length;
  }

  public getData(index: int): int {
    return this.dataArray[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos: int = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  notifyDataAdd(index: int): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
    })
  }

  notifyDataDelete(index: int): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
    })
  }
}

export class MyDataSource extends BasicDataSource {
  public pushData(data: int): void {
    this.dataArray.push(data);
    this.notifyDataAdd(this.dataArray.length - 1);
  }
}

@Entry
@Component
export struct ListNestedLazyLayout {
  // 网格区域数据源
  private gridData: MyDataSource = new MyDataSource();
  // 瀑布流区域数据源
  private flowData: MyDataSource = new MyDataSource();

  private itemHeight(index: int): int {
    return 80 + (index * 37 % 121)
  }

  aboutToAppear(): void {
    for (let i = 0; i < 6; i++) {
      this.gridData.pushData(i);
    }
    for (let i = 0; i < 100; i++) {
      this.flowData.pushData(i);
    }
  }

  build(): void {
    NavDestination() {
      Column() {
        // [Start lazy_water_flow_load_data]
        List({ space: 10 } as ListOptions) {
          // [StartExclude lazy_water_flow_load_data]
          ListItem() {
            // 请将$r('app.string.list_nested_lazyLayout_grid')替换为实际资源文件
            // 在本示例中该资源文件的value值为"网格布局"
            Text($r('app.string.list_nested_lazyLayout_grid'))
              .fontSize(14)
              .fontColor(Color.Gray)
          }

          LazyVGridLayout() {
            LazyForEach(this.gridData, (item: int) => {
              Text('item' + item.toString())
                .height(96)
                .width('100%')
                .borderRadius(5)
                .backgroundColor('#ffe0e2e4')
                .textAlign(TextAlign.Center)
            }, (item: int) => item.toString())
          }
          .columnsTemplate('1fr 1fr 1fr')
          .rowsGap(LengthMetrics.vp(10))
          .columnsGap(LengthMetrics.vp(10))
          .onVisibleIndexesChange((start: int, end: int) => {
            console.info('LazyVGridLayout visible indexes: start: ' + start + ', end: ' + end);
          })

          LazyVGridLayout() {
            LazyForEach(this.gridData, (item: int) => {
              Text('item' + (this.gridData.totalCount() + item).toString())
                .height(96)
                .width('100%')
                .borderRadius(5)
                .backgroundColor('#ffe0e2e4')
                .textAlign(TextAlign.Center)
            }, (item: int) => item.toString())
          }
          .columnsTemplate('1fr 2fr')
          .rowsGap(LengthMetrics.vp(10))
          .columnsGap(LengthMetrics.vp(10))
          .margin({ bottom: 16 })
          .onVisibleIndexesChange((start: int, end: int) => {
            console.info('LazyVGridLayout visible indexes: start: ' + (this.gridData.totalCount() + start) + ', end: ' +
              (this.gridData.totalCount() + end));
          })

          ListItem() {
            // 请将$r('app.string.list_nested_lazyLayout_waterFlow')替换为实际资源文件
            // 在本示例中该资源文件的value值为"瀑布流布局"
            Text($r('app.string.list_nested_lazyLayout_waterFlow'))
              .fontSize(14)
              .fontColor(Color.Gray)
          }

          // [EndExclude lazy_water_flow_load_data]
          LazyVWaterFlowLayout() {
            LazyForEach(this.flowData, (item: int) => {
              // [StartExclude lazy_water_flow_load_data]
              Text('item' + item.toString())
                .height(this.itemHeight(item))
                .width('100%')
                .borderRadius(5)
                .backgroundColor('#ffe0e2e4')
                .textAlign(TextAlign.Center)
              // [EndExclude lazy_water_flow_load_data]
            }, (item: int) => item.toString())
          }
          .columnsTemplate('1fr 1fr')
          .rowsGap(LengthMetrics.vp(10))
          .columnsGap(LengthMetrics.vp(10))
          .onVisibleIndexesChange((start: int, end: int) => {
            console.info('LazyVWaterFlowLayout visible indexes: start: ' + start + ', end: ' + end);
            // 滚动监听：即将触底时提前加载更多数据
            if (end + 20 >= this.flowData.totalCount()) {
              let currentCount = this.flowData.totalCount();
              for (let i = currentCount; i < currentCount + 100; i++) {
                this.flowData.pushData(i);
              }
            }
          })
        }
        .listDirection(Axis.Vertical)
        // [End lazy_water_flow_load_data]
        .backgroundColor(Color.White)
        .borderRadius(12)
        .padding(12)
        .width('100%')
        .layoutWeight(1)
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.list_nested_lazyLayout_title')替换为实际资源文件
    // 在本示例中该资源文件的value值为"List嵌套懒加载布局容器"
    .title($r('app.string.list_nested_lazyLayout_title'))
  }
}
// [End list_nested_lazy_layout]
