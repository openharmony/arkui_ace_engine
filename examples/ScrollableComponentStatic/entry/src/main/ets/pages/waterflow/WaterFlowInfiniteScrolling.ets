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

import { ComponentCard } from '../../common/Card';
import { WaterFlowDataSource } from './WaterFlowDataSource';
import { image } from '@kit.ImageKit';
import {
  Entry,
  Component,
  Builder,
  Reusable,
  State,
  Column,
  ColumnOptions,
  Text,
  Image,
  Row,
  WaterFlow,
  WaterFlowOptions,
  FlowItem,
  ImageFit,
  Alignment,
  WaterFlowLayoutMode,
  Color,
  FlexAlign,
  LazyForEach,
  LoadingProgress,
  NavDestination,
  $r,
  AppStorage
} from '@kit.ArkUI';

@Reusable
@Component
struct ReusableFlowItem {
  @State item: int = 0;

  // 从复用缓存中加入到组件树之前调用，可在此处更新组件的状态变量以展示正确的内容
  aboutToReuse(params: Record<string, int>): void {
    this.item = params['item'] ?? 0;
  }

  build(): void {
    Column() {
      Text('FlowItem' + this.item).fontSize(16).height('16')
      Image('res/waterFlow(' + (this.item % 5).toString() + ').JPG')
        .objectFit(ImageFit.Fill)
        .width('100%')
        .layoutWeight(1)
    }
  }
}

@Entry
@Component
export struct WaterFlowInfiniteScrolling {
  minSize: int = 80;
  maxSize: int = 180;
  colors: int[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  dataSource: WaterFlowDataSource = new WaterFlowDataSource(100);
  private itemWidthArray: int[] = [];
  private itemHeightArray: int[] = [];
  @State columns: int = 2;
  @State waterflowScale: float = 1;
  @State imageScale: float = 1;
  @State waterFlowOpacity: float = 1;
  @State waterflowSnapshot: image.PixelMap | undefined = undefined;
  private columnChanged: boolean = false;
  private oldColumn: int = this.columns;
  private pinchTime: int = 0;
  private gridItems: int[] = [];

  // 计算FlowItem宽/高
  getSize(): int {
    let ret: double = Math.floor(Math.random() * this.maxSize);
    let result: int = Double.toInt(ret > this.minSize ? ret : this.minSize);
    return result;
  }

  // 设置FlowItem的宽/高数组
  setItemSizeArray(): void {
    for (let i: int = 0; i < 100; i++) {
      this.itemWidthArray.push(this.getSize());
      this.itemHeightArray.push(this.getSize());
    }
  }

  aboutToAppear(): void {
    // 读取上次最后切换到到列数
    let lastCount: int | undefined = AppStorage.get<int>('columnsCount');
    if (typeof lastCount != 'undefined' && lastCount != null) {
      this.columns = lastCount;
    }
    this.setItemSizeArray();
    for (let i: int = 0; i < 15; ++i) {
      this.gridItems.push(i);
    }
  }

  // 根据缩放阈值改变列数，触发WaterFlow重新布局
  changeColumns(scale: float): void {
    if (scale > (this.columns / (this.columns - 0.5)) && this.columns > 1) {
      this.columns--;
      this.columnChanged = true;
    } else if (scale < 1 && this.columns < 4) {
      this.columns++;
      this.columnChanged = true;
    }
  }
  // [Start WaterFlowInfiniteScrolling_start]
  @Builder
  itemFoot(): void {
    Row() {
      LoadingProgress()
        .color(Color.Blue).height(50).aspectRatio(1).width('20%')
      // 请将$r('app.string.waterFlow_text1')替换为实际资源文件，在本示例中该资源文件的value值为"正在加载 "
      Text($r('app.string.waterFlow_text1'))
        .fontSize(20)
        .width('30%')
        .height(50)
        .align(Alignment.Center)
        .margin({ top: 2 })
    }.width('100%').justifyContent(FlexAlign.Center)
  }

  build(): void {
    NavDestination() {
      Column({ space: 12 } as ColumnOptions) {
        // [StartExclude WaterFlowInfiniteScrolling_start]
        // 请将$r('app.string.WaterFlowInfiniteScrolling_title')替换为实际资源文件，在本示例中该资源文件的value值为"无限滚动（到达末尾时新增数据）"
        ComponentCard({ title: $r('app.string.WaterFlowInfiniteScrolling_title') }) {
          // [EndExclude WaterFlowInfiniteScrolling_start]
          WaterFlow({ footer: this.itemFoot, layoutMode: WaterFlowLayoutMode.SLIDING_WINDOW } as WaterFlowOptions) {
            LazyForEach(this.dataSource, (item: int) => {
              FlowItem() {
                ReusableFlowItem({ item: item })
              }
              .width('100%')
              .aspectRatio(this.itemHeightArray[item % 100] / this.itemWidthArray[item % 100])
              .backgroundColor(this.colors[item % 5])
            }, (item: int) => item.toString())
          }
          .columnsTemplate('1fr '.repeat(this.columns))
          .backgroundColor(0xFAEEE0)
          .width('100%')
          .height('100%')
          .layoutWeight(1)
          // 触底加载数据
          .onReachEnd(() => {
            setTimeout(() => {
              this.dataSource.addNewItems(100);
            }, 1000)
          })
        }
        // [StartExclude WaterFlowInfiniteScrolling_start]
      }
      .width('100%')
      .height('100%')
      .padding({ left: 12, right: 12 })
      // [EndExclude WaterFlowInfiniteScrolling_start]
    }
    .backgroundColor('#f1f2f3')
    // 请将$r('app.string.WaterFlowInfiniteScrolling_title')替换为实际资源文件，在本示例中该资源文件的value值为"无限滚动（到达末尾时新增数据）"
    .title($r('app.string.WaterFlowInfiniteScrolling_title'))
  }
  // [End WaterFlowInfiniteScrolling_start]
}
