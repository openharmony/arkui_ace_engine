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

import { ListDataSource } from './ListDataSource/ListDataSource';
import {NodeIdUtils} from '../grid/GetID';
@Entry
@Component
struct ListExample {
  private arr: ListDataSource = new ListDataSource([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
  @State arr2: number[] = []
  @State edgeEffectArr: number[] = [EdgeEffect.None,EdgeEffect.Spring,EdgeEffect.Fade]
  @State edgeEffectNameArr: string[] = ['None','Spring','Fade']
  @State edgeEffectArrIndex: number = 0

  scroller: Scroller = new Scroller();
  aboutToAppear() {
    for (let i = 0; i < 100; i++) {
      this.arr2.push(i)
    }
  }

  build() {
    Column() {
      Stack({ alignContent: Alignment.TopStart }) {
        List({ space: 20, initialIndex: 0,scroller: this.scroller  }) {
          ForEach(this.arr2, (item: number, index?: number) => {
            ListItem() {
              Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                Text('' + item)
                  .width(150)
                  .height(93)
                  .fontSize(30)
                  .textAlign(TextAlign.Center)
                  .borderRadius(10)
                  .backgroundColor(0xFFFFFF)
                  .flexShrink(1)
                  .focusable(true)
                  .offset({ left: 5 })
                  .id('text'+ item.toString())
              }
            }
          }, (item: string, index?: number) => item)
        }
        .id('List')
        .listDirection(Axis.Vertical) // 排列方向
        .scrollBar(BarState.Off)
        .friction(0.6)
        .divider({
          strokeWidth: 2,
          color: 0xFFFFFF,
          startMargin: 20,
          endMargin: 20
        }) // 每行之间的分界线
        .edgeEffect(this.edgeEffectArr[this.edgeEffectArrIndex])
        .onScrollIndex((firstIndex: number, lastIndex: number, centerIndex: number) => {
          console.info('first' + firstIndex);
          console.info('last' + lastIndex);
          console.info('center' + centerIndex);
        })
        .cachedCount(1000, true)
        .onScrollVisibleContentChange((start: VisibleListContentInfo, end: VisibleListContentInfo) => {
          console.info(' start index: ' + start.index +
            ' start item group area: ' + start.itemGroupArea +
            ' start index in group: ' + start.itemIndexInGroup);
          console.info(' end index: ' + end.index +
            ' end item group area: ' + end.itemGroupArea +
            ' end index in group: ' + end.itemIndexInGroup);
        })
        .onDidScroll((scrollOffset: number, scrollState: ScrollState) => {
          console.info(`onScroll scrollState = ScrollState` + scrollState + `, scrollOffset = ` + scrollOffset);
        })
        .onScrollStart(() => {
          // 开始滚动时触发
          console.info('laoxu scroll start');
        })
        .onScrollStop(() => {
          // 停止滚动时触发
          console.info('laoxu scroll stop');
        })
        .width('90%')
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
            this.scroller.scrollTo({ xOffset: 0, yOffset: yOffset + 100 , animation:true});
          })
          .margin({ top: 60, left: 20 })

        Button('scrollEdge')
          .height('5%')
          .onClick(() => { // 点击后回到顶部
            this.scroller.scrollEdge(Edge.Top);
          })
          .margin({ top: 110, left: 20 })
        Button('scrollPage')
          .height('5%')
          .onClick(() => { // 点击后滑到下一页
            this.scroller.scrollPage({ next: true ,animation: true });
          })
          .margin({ top: 160, left: 20 })
        Button('edgeEffect' + this.edgeEffectNameArr[this.edgeEffectArrIndex])
          .height('5%')
          .onClick(() => {
            this.edgeEffectArrIndex++;
            if (this.edgeEffectArrIndex >= this.edgeEffectArr.length) {
              this.edgeEffectArrIndex %= this.edgeEffectArr.length
            }
          })
          .margin({ top: 210, left: 20 })

        Button('id')
          .height('5%')
          .onClick(() => { //

            NodeIdUtils.getNodeInternalId(this.getUIContext(),'List','text',100)
          })
          .margin({ top: 360, left: 20 })
      }
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .padding({ top: 5 })
  }
}