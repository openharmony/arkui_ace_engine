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

import { curves } from '@kit.ArkUI';
import { NodeIdUtils } from './getID';

@Entry
@Component
struct ScrollExample_nestedScroll2 {
  scroller: Scroller = new Scroller();
  @State arr2: number[] = []
  @State edgeEffectArr: number[] = [EdgeEffect.None, EdgeEffect.Spring, EdgeEffect.Fade]
  @State edgeEffectNameArr: string[] = ["None", "Spring", "Fade"]
  @State edgeEffectArrIndex: number = 0
  @State scrollDirectionArr: number[] =
    [ScrollDirection.Vertical, ScrollDirection.Horizontal, ScrollDirection.None, ScrollDirection.FREE]
  @State scrollDirectionNameArr: string[] = ["Vertical", "Horizontal", "None", "FREE"]
  @State scrollDirectionArrIndex: number = 0
  @State zoomScaleArr: number[] = [1, 0.5, 2]
  @State zoomScaleArrIndex: number = 0

  aboutToAppear() {
    for (let i = 0; i < 100; i++) {
      this.arr2.push(i)
    }
  }

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      Scroll() {
        Column() {
          Text('Scroll Area')
            .width('100%')
            .height('40%')
            .backgroundColor('#0080DC')
            .textAlign(TextAlign.Center)
          Tabs({ barPosition: BarPosition.Start }) {
            TabContent() {
              List({ space: 10, scroller: this.scroller }) {
                ForEach(this.arr2, (item: number) => {
                  ListItem() {
                    Text('item' + item)
                      .fontSize(16)
                      .margin({ left: 200 })
                      .id('text' + item.toString())
                  }
                }, (item: number) => item.toString())
              }
              .width('100%')
              .id("List")
              .cachedCount(1000, true)
              .edgeEffect(EdgeEffect.Spring)
              .nestedScroll({
                scrollForward: NestedScrollMode.PARENT_FIRST,
                scrollBackward: NestedScrollMode.SELF_FIRST
              })
              .onScrollStart(() => {
                // 开始滚动时触发
                console.info('laoxu list scroll start');
              })
              .onScrollStop(() => {
                // 停止滚动时触发
                console.info('laoxu list scroll stop');
              })
            }.tabBar('Tab1')

          }
          .vertical(false)
          .height('100%')
        }.width('100%')
      }
      .scrollable(ScrollDirection.Vertical) // 滚动方向纵向
      .scrollable(this.scrollDirectionArr[this.scrollDirectionArrIndex])
      .edgeEffect(this.edgeEffectArr[this.edgeEffectArrIndex])
      .zoomScale(this.zoomScaleArr[this.zoomScaleArrIndex])
      .scrollBar(BarState.On) // 滚动条常驻显示
      .scrollBarColor(Color.Gray) // 滚动条颜色
      .scrollBarWidth(10) // 滚动条宽度
      .friction(0.6)
      .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        console.info(xOffset + ' ' + yOffset);
      })
      .onScrollEdge((side: Edge) => {
        console.info('To the edge');
      })
      .onScrollStart(() => {
        // 开始滚动时触发
        console.info('laoxu scroll start');
      })
      .onScrollStop(() => {
        // 停止滚动时触发
        console.info('laoxu scroll stop');
      })

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
        .onClick(() => { //

          NodeIdUtils.getNodeInternalId(this.getUIContext(), "List", "text", 100)
        })
        .margin({ top: 360, left: 20 })
    }.width('100%').height('100%').backgroundColor(0xDCDCDC)
  }
}