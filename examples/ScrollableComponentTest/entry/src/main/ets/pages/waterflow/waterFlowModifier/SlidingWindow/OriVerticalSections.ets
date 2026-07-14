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

/*
 * Description: WaterFlow组件支持基于断点自适应列数
 * Writer: renxiaowen
 */

import { WaterFlowDataSource } from '../../WaterFlowDataSource';

class waterFlowModifier implements AttributeModifier<WaterFlowAttribute> {
  public index: number = 0;
  public columnList: (string | ItemFillPolicy | undefined | null)[] = [
    '1fr 2fr 1fr',
    { fillType: PresetFillType.BREAKPOINT_DEFAULT },
    { fillType: PresetFillType.BREAKPOINT_SM2MD3LG5 },
    { fillType: PresetFillType.BREAKPOINT_SM1MD2LG3 },
    undefined,
    null
  ]

  applyNormalAttribute(instance: WaterFlowAttribute): void {
    instance.columnsTemplate(this.columnList[this.index])
  }
}

@Entry
@Component
struct WaterFlowDemo {
  @State waterFlowMod: waterFlowModifier = new waterFlowModifier()
  minSize: number = 80;
  maxSize: number = 180;
  colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  scroller: Scroller = new Scroller();
  @State contentWidth: number = -1;
  @State contentHeight: number = -1;
  dataSource: WaterFlowDataSource = new WaterFlowDataSource();
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
    // 回调函数：动态设置每个item的高度
    onGetItemMainSizeByIndex: (index: number) => {
      return this.itemHeightArray[index % 100];
    }
  };
  // 第二种分组：双列布局，适合展示列表内容
  twoColumnSection: SectionOptions = {
    itemsCount: 2, // 该分组包含2个FlowItem
    crossCount: 2, // 使用2列布局
    // 回调函数：固定高度100px
    onGetItemMainSizeByIndex: (index: number) => {
      return 100;
    }
  };
  // 最后一个分组：用于处理剩余数据
  lastSection: SectionOptions = {
    itemsCount: 20, // 该分组包含20个FlowItem
    crossCount: 2, // 使用2列布局
    // 回调函数：使用随机高度
    onGetItemMainSizeByIndex: (index: number) => {
      return this.itemHeightArray[index % 100];
    }
  };

  // 计算FlowItem高度
  getSize() {
    let ret = Math.floor(Math.random() * this.maxSize);
    return (ret > this.minSize ? ret : this.minSize);
  }

  // 设置FlowItem的高度数组
  setItemSizeArray() {
    for (let i = 0; i < 100; i++) {
      this.itemHeightArray.push(100);
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
      // 剩余数据不足20个时，使用最后一个分组处理
      if (this.dataCount - count < 20) {
        this.lastSection.itemsCount = this.dataCount - count;
        sectionOptions.push(this.lastSection);
        break;
      }

      // 交替使用单列和双列布局
      if (oneOrTwo++ % 2 == 0) {
        sectionOptions.push(this.oneColumnSection);
        count += this.oneColumnSection.itemsCount;
      } else {
        sectionOptions.push(this.twoColumnSection);
        count += this.twoColumnSection.itemsCount;
      }
    }

    // 将配置好的分组添加到WaterFlow中
    this.sections.splice(0, 0, sectionOptions);
  }

  build() {
    Column({ space: 2 }) {
      Row() {
        Button('column: ' + this.waterFlowMod.columnList[this.waterFlowMod.index]).onClick(() => {
          this.waterFlowMod.index++;
          this.waterFlowMod.index = this.waterFlowMod.index % this.waterFlowMod.columnList.length;
        })
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
      }.margin({ bottom: 20 })

      Text('Width：' + this.contentWidth + '，Height：' + this.contentHeight)
        .fontColor(Color.Red)
        .height(15)

      WaterFlow({ scroller: this.scroller, layoutMode: WaterFlowLayoutMode.SLIDING_WINDOW, sections: this.sections }) {
        ForEach(this.dataSource.dataArray, (item: number) => {
          FlowItem() {
            // 使用可复用组件，提升性能
            Column() {
              Text('F' + item).fontSize(12).height('16')
            }
            .height(item * 11)
          }
          .width('100%')
          //.aspectRatio(this.itemHeightArray[item % 100] / this.itemWidthArray[item%100])
          .backgroundColor(this.colors[item % this.colors.length])
        }, (item: string) => item)
      }
      .attributeModifier(this.waterFlowMod)
      .columnsGap(10)
      .backgroundColor(0xFAEEE0)
      .width('100%')
      .height('100%')
      .layoutWeight(1)
    }
  }
}