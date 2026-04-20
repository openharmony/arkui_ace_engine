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

import { MyDataSource } from './BasicDataSource'
import { WaterFlowModifier } from '@ohos.arkui.modifier';

@Entry
@Component
struct WaterFlowDemo {
  minSize: number = 80;
  maxSize: number = 180;
  colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  scroller: Scroller = new Scroller();
  dataSource: MyDataSource<number> = new MyDataSource<number>();
  dataCount: number = this.dataSource.totalCount();
  private itemWidthArray: number[] = [];
  private itemHeightArray: number[] = [];
  // 分组管理：WaterFlow的核心特性，支持不同区域使用不同列数
  @State sections: WaterFlowSections = new WaterFlowSections();
  // 分组边距配置：统一的外边距设置
  sectionMargin: Margin = {
    top: 10,
    left: 5,
    bottom: 10,
    right: 5
  };
  oneColumnSection: SectionOptions = {
    itemsCount: 4, // 该分组包含4个FlowItem
    crossCount: 1, // 使用1列布局
    columnsGap: '5vp',
    rowsGap: 10,
    margin: this.sectionMargin,
    // 回调函数：动态设置每个item的高度
    onGetItemMainSizeByIndex: (index: number) => {
      return this.itemHeightArray[index % 100];
    }
  };

  // 设置FlowItem的高度数组
  setItemSizeArray() {
    for (let i = 0; i < 100; i++) {
      this.itemHeightArray.push(80 as number);
    }
  }

  // 组件生命周期：初始化数据和恢复上次的列数设置
  aboutToAppear() {
    this.setItemSizeArray();

    // 初始化瀑布流分组信息：交替使用单列和双列布局
    let sectionOptions: SectionOptions[] = [];
    let count = 0; // 已分配的FlowItem数量计数
    let oneOrTwo = 0; // 用于交替选择分组类型

    while (count < this.dataCount) {
      sectionOptions.push(this.oneColumnSection);
      count += this.oneColumnSection.itemsCount;
    }

    // 将配置好的分组添加到WaterFlow中
    this.sections.splice(0, 0, sectionOptions);
  }

  build() {
    Column() {
      Row() {
        Button('splice')
          .height('5%')
          .onClick(() => {
            // 重要：必须保证LazyForEach中数据数量和新分组itemsCount累计总数保持一致
            let totalCount: number = this.dataSource.totalCount();
            let newSection: SectionOptions = {
              itemsCount: totalCount,
              crossCount: 2,
              onGetItemMainSizeByIndex: (index: number) => {
                return this.itemHeightArray[index % 100];
              }
            };
            let oldLength: number = this.sections.length();
            this.sections.splice(0, oldLength, [newSection]); // 替换所有分组
          })
          .margin({ top: 10, left: 20 })

        Button('update')
          .height('5%')
          .onClick(() => {
            // 在第一个分组中增加4个FlowItem
            // 重要：必须保证数据源和分组itemsCount同步更新
            const sections: SectionOptions[] = this.sections.values();
            let newSection: SectionOptions = sections[0];

            // 先在数据源中添加4个新数据
            this.dataSource.addLastItem();
            this.dataSource.addLastItem();
            this.dataSource.addLastItem();
            this.dataSource.addLastItem();

            // 然后更新分组的itemsCount
            newSection.itemsCount += 4;
            const result: boolean = this.sections.update(0, newSection);
            console.info('update:' + result);
          })
          .margin({ top: 10, left: 20 })

        Button('delete')
          .height('5%')
          .onClick(() => {
            // 在第一个分组中减少4个FlowItem
            // 重要：必须保证数据源和分组itemsCount同步更新
            const sections: SectionOptions[] = this.sections.values();
            let newSection: SectionOptions = sections[0];

            // 检查是否有足够的item可以删除
            if (newSection.itemsCount < 4) {
              return;
            }

            // 先从数据源中删除4条数据
            this.dataSource.deleteItem(this.oneColumnSection.itemsCount - 1);
            this.dataSource.deleteItem(this.oneColumnSection.itemsCount - 2);
            this.dataSource.deleteItem(this.oneColumnSection.itemsCount - 3);
            this.dataSource.deleteItem(this.oneColumnSection.itemsCount - 4);

            // 更新分组的itemsCount
            newSection.itemsCount -= 4;
            this.sections.update(0, newSection);
          })
          .margin({ top: 10, left: 20 })

        Button('values')
          .height('5%')
          .onClick(() => {
            const sections: SectionOptions[] = this.sections.values();
            for (const value of sections) {
              console.info('values:' + JSON.stringify(value));
            }
            console.info('count:' + this.sections.length());
          })
          .margin({ top: 10, left: 20 })
      }.margin({ bottom: 20 })

      WaterFlow({ scroller: this.scroller, sections: this.sections }) {
        LazyForEach(this.dataSource, (item: number) => {
          if (item == 4 || item == 12) {

          } else {
            FlowItem() {
              Text(item + '')
            }
            .width('100%')
            .backgroundColor(this.colors[item % this.colors.length])
          }
        }, (item: number) => item + '')
      }
      .columnsTemplate('1fr 1fr')
      .columnsGap(10)
      .rowsGap(5)
      .backgroundColor(0xFAEEE0)
      .width('100%')
      .height('100%')
      .layoutWeight(1)
    }
  }
}