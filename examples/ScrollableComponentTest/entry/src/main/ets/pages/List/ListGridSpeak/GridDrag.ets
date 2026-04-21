/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

import { GridDataSource } from '../../grid/GridDataSource';

@Entry
@Component
struct GridDragExample {
  numbers: GridDataSource = new GridDataSource([]);
  scroller: Scroller = new Scroller();
  @State text: string = 'drag';

  @Builder
  pixelMapBuilder() { //拖拽过程样式
    Column() {
      Text(this.text)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width('80vp')
        .height('80vp')
        .textAlign(TextAlign.Center)
    }
  }

  aboutToAppear() {
    let list: string[] = [];
    for (let i = 1; i <= 15; i++) {
      list.push(i + '');
    }
    this.numbers = new GridDataSource(list);
  }

  changeIndex(index1: number, index2: number) { //交换数组位置
    this.numbers.swapItem(index1, index2);
  }

  build() {
    Column({ space: 5 }) {
      Grid(this.scroller) {
        LazyForEach(this.numbers, (day: string) => {
          GridItem() {
            Text(day)
              .fontSize(16)
              .backgroundColor(0xF9CF93)
              .width('80vp')
              .height('80vp')
              .textAlign(TextAlign.Center)
          }
        }, (day: string) => day)
      }
      .columnsTemplate('1fr 1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .width('90%')
      .backgroundColor(0xFAEEE0)
      .height(300)
      .editMode(true) //设置Grid是否进入编辑模式，进入编辑模式可以拖拽Grid组件内部GridItem
      .supportAnimation(true) // 设置支持动画
      .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
        this.text = this.numbers.getData(itemIndex);
        return this.pixelMapBuilder(); //设置拖拽过程中显示的图片。
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number,
        isSuccess: boolean) => { //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
        // isSuccess=false时，说明drop的位置在grid外部；insertIndex > length时，说明有新增元素的事件发生
        if (!isSuccess || insertIndex >= this.numbers.totalCount()) {
          return;
        }
        console.info('itemIndex:' + itemIndex + ', insertIndex:' + insertIndex); //itemIndex拖拽起始位置，insertIndex拖拽插入位置
        this.changeIndex(itemIndex, insertIndex);
      })
    }.width('100%').margin({ top: 5 })
  }
}