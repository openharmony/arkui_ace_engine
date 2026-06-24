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
  Stack,
  StackOptions,
  Text,
  Image,
  Grid,
  GridItem,
  WaterFlow,
  WaterFlowOptions,
  FlowItem,
  ImageFit,
  Alignment,
  Color,
  WaterFlowLayoutMode,
  WaterFlowSections,
  SectionOptions,
  LazyForEach,
  ForEach,
  NavDestination,
  $r,
  Margin
} from '@kit.ArkUI';

@Reusable
@Component
struct ReusableFlowItem {
  @State item: int = 0;

  // 从复用缓存中加入到组件树之前调用，可在此处更新组件的状态变量以展示正确的内容
  aboutToReuse(params: Record<string, int>): void {
    this.item = params.get('item') ?? 0;
  }

  build(): void {
    Stack({ alignContent: Alignment.Center } as StackOptions) {
      Text('FlowItem' + this.item).fontSize(14).height('16')
      Image('res/waterFlow (' + (this.item % 5).toString() + ').JPG')
        .objectFit(ImageFit.Fill)
        .width('100%')
        .layoutWeight(1)
    }
  }
}
// [Start waterFlowGroupingMixing_start]
@Entry
@Component
export struct WaterFlowGroupingMixing {
  minSize: int = 80;
  maxSize: int = 180;
  colors: int[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  dataSource: WaterFlowDataSource = new WaterFlowDataSource(100);
  private itemWidthArray: int[] = [];
  private itemHeightArray: int[] = [];
  private gridItems: int[] = [];
  @State sections: WaterFlowSections = new WaterFlowSections();
  sectionMargin: Margin = {
    top: 10,
    left: 5,
    bottom: 10,
    right: 5
  };
  oneColumnSection: SectionOptions = {
    itemsCount: 1,
    crossCount: 1,
    columnsGap: 5,
    rowsGap: 10,
    margin: this.sectionMargin,
  };
  twoColumnSection: SectionOptions = {
    itemsCount: 98,
    crossCount: 2,
  };
  // 使用分组瀑布流时无法通过footer设置尾部组件，可以保留一个固定的分组作为footer
  lastSection: SectionOptions = {
    itemsCount: 1,
    crossCount: 1,
  };

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
    this.setItemSizeArray();
    for (let i: int = 0; i < 15; ++i) {
      this.gridItems.push(i);
    }
    // 所有分组的itemCount之和需要和WaterFlow下数据源的子节点总数相等，否则无法正常布局
    let sectionOptions: SectionOptions[] = [this.oneColumnSection, this.twoColumnSection, this.lastSection];
    this.sections.splice(0, 0, sectionOptions);
  }

  build(): void {
    NavDestination() {
      // [StartExclude waterFlowGroupingMixing_start]
      // 请将$r('app.string.WaterFlowGroupingMixing_title')替换为实际资源文件，在本示例中该资源文件的value值为"分组混合布局"
      ComponentCard({ title: $r('app.string.WaterFlowGroupingMixing_title') }) {
        // [EndExclude waterFlowGroupingMixing_start]
        WaterFlow({ layoutMode: WaterFlowLayoutMode.SLIDING_WINDOW, sections: this.sections } as WaterFlowOptions) {
          LazyForEach(this.dataSource, (item: int) => {
            FlowItem() {
              if (item === 0) {
                Grid() {
                  ForEach(this.gridItems, (day: int) => {
                    GridItem() {
                      Text('GridItem').fontSize(14).height('16')
                    }.backgroundColor(0xFFC0CB)
                  }, (day: int) => day.toString())
                }
                .height('30%')
                .rowsGap(5)
                .columnsGap(5)
                .columnsTemplate('1fr '.repeat(5))
                .rowsTemplate('1fr '.repeat(3))
              } else {
                ReusableFlowItem({ item: item })
              }
            }
            .width('100%')
            .aspectRatio(item != 0 ? this.itemHeightArray[item % 100] / this.itemWidthArray[item % 100] : 0)
            .backgroundColor(item != 0 ? this.colors[item % 5] : Color.White)
          }, (item: int) => item.toString())
        }
        .backgroundColor(0xFAEEE0)
        .height('100%')
        // 即将触底时提前增加数据
        .onScrollIndex((first: int, last: int) => {
          if (last + 20 >= this.dataSource.totalCount()) {
            setTimeout(() => {
              this.dataSource.addNewItems(100);
              // 增加数据后同步调整对应分组的itemCount
              this.twoColumnSection.itemsCount += 100;
              this.sections.update(1, this.twoColumnSection);
            }, 1000);
          }
        })
        .margin(10)
      }
      // [StartExclude waterFlowGroupingMixing_start]
    }.backgroundColor('#f1f2f3')
    // 请将$r('app.string.WaterFlowGroupingMixing_title')替换为实际资源文件，在本示例中该资源文件的value值为"分组混合布局"
    .title($r('app.string.WaterFlowGroupingMixing_title'))
    // [EndExclude waterFlowGroupingMixing_start]
  }
}
// [End waterFlowGroupingMixing_start]
