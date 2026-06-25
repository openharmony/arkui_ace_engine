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

// [Start lazy_column_nested_lazy_layout]
import {
  IDataSource,
  DataChangeListener,
  Entry,
  Component,
  NavDestination,
  Column,
  Scroll,
  LazyColumnLayout,
  Text,
  $r,
  Color,
  LazyForEach,
  Row,
  Span,
  Blank,
  SymbolGlyph,
  LengthMetrics,
  LazyVGridLayout,
  FlexAlign,
  LazyVWaterFlowLayout,
  TextAlign,
  HorizontalAlign,
  ScrollDirection
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
export struct LazyColumnLayoutNestedLazyLayout {
  // 线性列表区域数据源
  private listData: MyDataSource = new MyDataSource();
  // 网格区域数据源
  private gridData: MyDataSource = new MyDataSource();
  // 瀑布流区域数据源
  private flowData: MyDataSource = new MyDataSource();

  private itemHeight(index: int): int {
    return 80 + (index * 37 % 121)
  }

  private itemColor(index: int): string {
    const colors: string[] = ['#FFE0B2', '#C8E6C9', '#BBDEFB', '#F8BBD0', '#D1C4E9', '#FFF9C4']
    return colors[index % colors.length]
  }

  aboutToAppear(): void {
    for (let i = 0; i < 4; i++) {
      this.listData.pushData(i);
    }
    for (let i = 0; i < 9; i++) {
      this.gridData.pushData(i);
    }
    for (let i = 0; i < 100; i++) {
      this.flowData.pushData(i);
    }
  }

  build(): void {
    NavDestination() {
      Column() {
        // [Start lazy_column_nested]
        Scroll() {
          LazyColumnLayout() {
            // [StartExclude lazy_column_nested]
            // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_following')替换为实际资源文件
            // 在本示例中该资源文件的value值为"推荐关注"
            Text($r('app.string.lazyColumnLayout_nested_lazyLayout_following'))
              .fontSize(14)
              .fontColor(Color.Gray)
              .margin({ bottom: 8 })
            // [EndExclude lazy_column_nested]

            // [Start lazy_layout_on_visible_indexes_change]
            // 区域一：线性列表
            LazyColumnLayout() {
              // [StartExclude lazy_column_nested]
              // [StartExclude lazy_layout_on_visible_indexes_change]
              LazyForEach(this.listData, (item: int) => {
                Row() {
                  Text() {
                    // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_item')替换为实际资源文件
                    // 在本示例中该资源文件的value值为"列表项"
                    Span($r('app.string.lazyColumnLayout_nested_lazyLayout_item'))
                    Span(item.toString())
                  }

                  Blank()
                  SymbolGlyph($r('sys.symbol.chevron_forward'))
                    .fontColor([Color.Gray])
                }
                .width('100%')
                .height(56)
                .padding({ left: 16, right: 16 })
                .borderRadius(8)
                .backgroundColor(Color.White)
              }, (item: int) => item.toString())
              // [EndExclude lazy_layout_on_visible_indexes_change]
              // [EndExclude lazy_column_nested]
            }
            // [StartExclude lazy_column_nested]
            .onVisibleIndexesChange((start: int, end: int) => {
              console.info('LazyColumnLayout visible indexes: start: ' + start + ', end: ' + end);
            })
            // [StartExclude lazy_layout_on_visible_indexes_change]
            .space(LengthMetrics.vp(10))

            // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_popular')替换为实际资源文件
            // 在本示例中该资源文件的value值为"热门分类"
            Text($r('app.string.lazyColumnLayout_nested_lazyLayout_popular'))
              .fontSize(14)
              .fontColor(Color.Gray)
              .margin({ top: 12, bottom: 8 })
            // [EndExclude lazy_layout_on_visible_indexes_change]
            // [EndExclude lazy_column_nested]

            // 区域二：网格布局
            LazyVGridLayout() {
              // [StartExclude lazy_column_nested]
              // [StartExclude lazy_layout_on_visible_indexes_change]
              LazyForEach(this.gridData, (item: int) => {
                Column() {
                  SymbolGlyph($r('sys.symbol.folder_fill'))
                    .fontSize(32)
                    .fontColor([Color.Orange])
                  Text() {
                    // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_category')替换为实际资源文件
                    // 在本示例中该资源文件的value值为"分类"
                    Span($r('app.string.lazyColumnLayout_nested_lazyLayout_category'))
                    Span(item.toString())
                  }
                  .fontSize(14)
                  .margin({ top: 6 })
                }
                .width('100%')
                .height(80)
                .borderRadius(8)
                .backgroundColor(Color.White)
                .justifyContent(FlexAlign.Center)
              }, (item: int) => item.toString())
              // [EndExclude lazy_layout_on_visible_indexes_change]
              // [EndExclude lazy_column_nested]
            }
            // [StartExclude lazy_column_nested]
            .onVisibleIndexesChange((start: int, end: int) => {
              console.info('LazyVGridLayout visible indexes: start: ' + start + ', end: ' + end);
            })
            // [StartExclude lazy_layout_on_visible_indexes_change]
            .columnsTemplate('1fr 1fr 1fr')
            .rowsGap(LengthMetrics.vp(10))
            .columnsGap(LengthMetrics.vp(10))

            // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_recommend')替换为实际资源文件
            // 在本示例中该资源文件的value值为"为你推荐"
            Text($r('app.string.lazyColumnLayout_nested_lazyLayout_recommend'))
              .fontSize(14)
              .fontColor(Color.Gray)
              .margin({ top: 12, bottom: 8 })
            // [EndExclude lazy_layout_on_visible_indexes_change]
            // [EndExclude lazy_column_nested]

            // 区域三：瀑布流布局
            LazyVWaterFlowLayout() {
              // [StartExclude lazy_column_nested]
              // [StartExclude lazy_layout_on_visible_indexes_change]
              LazyForEach(this.flowData, (item: int) => {
                Text() {
                  // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_recommendation')替换为实际资源文件
                  // 在本示例中该资源文件的value值为"推荐内容"
                  Span($r('app.string.lazyColumnLayout_nested_lazyLayout_recommendation'))
                  Span(item.toString())
                }
                .height(this.itemHeight(item))
                .width('100%')
                .borderRadius(8)
                .backgroundColor(this.itemColor(item))
                .textAlign(TextAlign.Center)
              }, (item: int) => item.toString())
              // [EndExclude lazy_layout_on_visible_indexes_change]
              // [EndExclude lazy_column_nested]
            }
            // [StartExclude lazy_column_nested]
            .onVisibleIndexesChange((start: int, end: int) => {
              console.info('LazyVWaterFlowLayout visible indexes: start: ' + start + ', end: ' + end);
              // [StartExclude lazy_layout_on_visible_indexes_change]
              // 即将触底时加载更多数据
              if (end + 20 >= this.flowData.totalCount()) {
                let currentCount = this.flowData.totalCount();
                for (let i = currentCount; i < currentCount + 100; i++) {
                  this.flowData.pushData(i);
                }
              }
              // [EndExclude lazy_layout_on_visible_indexes_change]
            })
            // [End lazy_layout_on_visible_indexes_change]
            .columnsTemplate('1fr 1fr')
            .rowsGap(LengthMetrics.vp(10))
            .columnsGap(LengthMetrics.vp(10))
            // [EndExclude lazy_column_nested]
          }
          // [StartExclude lazy_column_nested]
          .alignItems(HorizontalAlign.Start)
          // [EndExclude lazy_column_nested]
        }
        .scrollable(ScrollDirection.Vertical)
        // [End lazy_column_nested]
        .padding(12)
        .width('100%')
        .layoutWeight(1)
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
      .backgroundColor('#f1f2f3')
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.lazyColumnLayout_nested_lazyLayout_title')替换为实际资源文件
    // 在本示例中该资源文件的value值为"LazyColumnLayout嵌套懒加载布局容器"
    .title($r('app.string.lazyColumnLayout_nested_lazyLayout_title'))
  }
}
// [End lazy_column_nested_lazy_layout]
