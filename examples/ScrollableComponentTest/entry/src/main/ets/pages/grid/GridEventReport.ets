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

import { GridDataSource } from './GridDataSource';
import { NodeIdUtils } from './GetID';

@Entry
@Component
struct GridExample {
  numbers: GridDataSource = new GridDataSource([]);
  scroller: Scroller = new Scroller();
  @State gridPosition: number = 0; // 0代表滚动到grid顶部，1代表中间值，2代表滚动到grid底部。
  @State arr2: number[] = []

  aboutToAppear() {
    let list: string[] = [];
    for (let i = 0; i < 5; i++) {
      for (let j = 0; j < 5; j++) {
        list.push(j.toString());
      }
    }
    this.numbers = new GridDataSource(list);

    for (let i = 0; i < 100; i++) {
      this.arr2.push(i)
    }
  }

  build() {
    Column({ space: 5 }) {
      Stack({ alignContent: Alignment.TopStart }) {

        Grid(this.scroller) {
          ForEach(this.arr2, (item: number, index?: number) => {
            GridItem() {
              Text('' + item)
                .fontSize(16)
                .backgroundColor(0xF9CF93)
                .width('100%')
                .height('100%')
                .textAlign(TextAlign.Center)
                .id('text' + item.toString())
            }
            .width('100%')
            .height(40)
            .shadow({
              radius: 10,
              color: '#909399',
              offsetX: 1,
              offsetY: 1
            })
            .borderRadius(10)
            .translate({ x: 0, y: 0 })
          }, (item: string) => item)
        }
        .id('Grid')
        .columnsTemplate('1fr ')
        .friction(0.3)
        .columnsGap(15)
        .rowsGap(10)
        .scrollBar(BarState.Off)
        .width('100%')
        .height('100%')
        .layoutDirection(GridDirection.Column)
        .cachedCount(1000, true)
        .onScrollStart(() => {
          // 开始滚动时触发
          console.info('laoxu scroll start');
        })
        .onScrollStop(() => {
          // 停止滚动时触发
          console.info('laoxu scroll stop');
        })

        Button('scrollBy 150')
          .height('5%')
          .onClick(() => { // 点击后下滑指定距离150.0vp
            this.scroller.scrollBy(0, 150);
          })
          .margin({ top: 10, left: 20 })
        Button('scrollToIndex 25')
          .height('5%')
          .onClick(() => { // 点击后下滑指定距离150.0vp
            this.scroller.scrollToIndex(25, true, ScrollAlign.START);
          })
          .margin({ top: 10, left: 20 })
        Button('scrollTo 100')
          .height('5%')
          .onClick(() => { // 点击后滑动到指定位置，即下滑100.0vp的距离
            const yOffset: number = this.scroller.currentOffset().yOffset;
            this.scroller.scrollTo({ xOffset: 0, yOffset: yOffset + 100, animation: true });
          })
          .margin({ top: 60, left: 20 })

        Button('scrollEdge')
          .height('5%')
          .onClick(() => { // 点击后回到顶部
            this.scroller.scrollEdge(Edge.Top);
          })
          .margin({ top: 160, left: 20 })
        Button('scrollPage')
          .height('5%')
          .onClick(() => { // 点击后滑到下一页
            this.scroller.scrollPage({ next: true, animation: true });
          })
          .margin({ top: 210, left: 20 })

        Button('id')
          .height('5%')
          .onClick(() => {

            NodeIdUtils.getNodeInternalId(this.getUIContext(), 'Grid', 'text', 100)
          })
          .margin({ top: 360, left: 20 })
      }
    }.width('100%').margin({ top: 5 })
  }
}