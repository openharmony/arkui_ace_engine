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

/*用例描述
 1、本用例使用Scroll组件的内置滚动条，实现了滚动条支持嵌套滚动的效果
*/
/* 关键结构
 |-> Scroll
  |-> List
 | -> Scroll
*/

import { LengthMetrics } from '@ohos.arkui.node';

@Entry
@Component
struct StickyNestedScroll {
  @State arr: number[] = []
  scroller: Scroller = new Scroller()
  listScroller: Scroller = new Scroller();
  scrollBarScroller: Scroller = new Scroller();
  @State contentHeight: number = 400 + (72 + 10) * 30 - 10;
  listScrollOffset: number = 0;
  scrollOffset: number = 0;

  @Styles
  listCard() {
    .backgroundColor(Color.White)
    .height(72)
    .width('100%')
    .borderRadius(12)
  }

  build() {
    Stack() {
      Scroll(this.scroller) {
        Column() {
          Text('Scroll Area')
            .width('100%')
            .height('400')
            .backgroundColor('#0080DC')
            .textAlign(TextAlign.Center)
          List({ space: 10, scroller: this.listScroller }) {
            ForEach(this.arr, (item: number) => {
              ListItem() {
                Text('item' + item)
                  .fontSize(16)
              }.listCard()
            }, (item: string) => item)
          }
          .width('100%')
          .edgeEffect(EdgeEffect.Spring)
          .nestedScroll({
            scrollForward: NestedScrollMode.PARENT_FIRST,
            scrollBackward: NestedScrollMode.SELF_FIRST
          })
          .height('100%')
          .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
            // 通过onWillScroll获取List组件的滚动偏移量，调用scrollBarScroller的scrollTo方法触发滚动条对应的scroll2组件滚动
            this.listScrollOffset = this.listScroller.currentOffset().yOffset + scrollOffset;
            this.scrollBarScroller.scrollTo({ xOffset: 0, yOffset: (this.listScrollOffset + this.scrollOffset) })
          })
          .scrollBar(BarState.Off)
        }.width('100%')
      }
      .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
        // 通过onWillScroll获取scroll1组件的滚动偏移量，调用scrollBarScroller的scrollTo方法触发滚动条对应的scroll2组件滚动
        this.scrollOffset = this.scroller.currentOffset().yOffset + yOffset;
        this.scrollBarScroller.scrollTo({ xOffset: 0, yOffset: (this.listScrollOffset + this.scrollOffset) })
      })
      .edgeEffect(EdgeEffect.Spring)
      .friction(0.6)
      .backgroundColor('#DCDCDC')
      .scrollBar(BarState.Off)
      .width('100%')
      .height('100%')
      .id('scroll1')

      Scroll(this.scrollBarScroller) {
        // 设置内容高度为scroll1内容高度和list内容高度之和
        Stack().height(this.contentHeight)
      }
      .height('100%')
      .width(12)
      .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
        // 拖动滚动条时，触发scroll1和list组件的滚动
        if (scrollSource == ScrollSource.SCROLL_BAR || scrollSource == ScrollSource.SCROLL_BAR_FLING) {
          if (yOffset > 0) {
            if (!this.scroller.isAtEnd()) {
              this.scroller.scrollBy(0, yOffset)
            } else {
              this.listScroller.scrollBy(0, yOffset)
            }
          } else {
            if (this.listScroller.currentOffset().yOffset > 0) {
              this.listScroller.scrollBy(0, yOffset)
            } else {
              this.scroller.scrollBy(0, yOffset)
            }
          }
        }
      })
      .margin({
        end: new LengthMetrics(12)
      })
      .id('scroll2')
    }.alignContent(Alignment.End)
  }

  aboutToAppear() {
    for (let i = 0; i < 30; i++) {
      this.arr.push(i)
    }
  }
}