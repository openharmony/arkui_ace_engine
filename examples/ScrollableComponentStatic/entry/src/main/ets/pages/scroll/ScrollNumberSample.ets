'use static'
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

import {
  Entry,
  Column,
  Component,
  Color,
  Text,
  LoadingProgress,
  Margin,
  Scroller,
  Scroll,
  ColumnOptions,
  Stack,
  Edge,
  Alignment,
  ForEach,
  ScrollDirection,
  BarState,
  EdgeEffect,
  TextAlign,
  ICurve,
  Flex,
  FlexDirection,
  ItemAlign,
  FlexAlign,
  FontWeight,
  Button,
  ButtonType,
  ClickEvent,
  ScrollState,
  ScrollSource
} from '@ohos.arkui.component'
import Curves from '@ohos.curves'
import hilog from '@ohos.hilog';

@Entry
@Component
struct ScrollExample {
  scroller: Scroller = new Scroller();
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      Scroll(this.scroller) {
        Column() {
          ForEach(this.arr, (item: number) => {
            Text(item.toString())
              .width('90%')
              .height(150)
              .backgroundColor('#FFFFFF')
              .borderRadius(15)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .margin({ top: 10 } as Margin)
          }, (item: number) => item.toString())
        }.width('100%')
      }
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(BarState.On)
      .scrollBarColor(Color.Gray)
      .scrollBarWidth(10)
      .friction(0.6)
      .edgeEffect(EdgeEffect.None)
      .onWillScroll((xOffset: double, yOffset: double, scrollState: ScrollState) => {
        console.info(xOffset + ' ' + yOffset);
      })
      .onScrollEdge((side: Edge) => {
        console.info('To the edge');
      })
      .onScrollStop(() => {
        console.info('Scroll Stop');
      })

      Button('scroll 150')
        .height('5%')
        .onClick(() => {
          this.scroller.scrollBy(0, 150);
        })
        .margin({ top: 10, left: 20 } as Margin)
      Button('scroll 100')
        .height('5%')
        .onClick(() => {
          const yOffset: number = this.scroller.currentOffset()!.yOffset;
          this.scroller.scrollTo({ xOffset: 0, yOffset: yOffset + 100 });
        })
        .margin({ top: 60, left: 20 } as Margin)
      Button('scroll 100')
        .height('5%')
        .onClick(() => {
          let curve = Curves.interpolatingSpring(10, 1, 228, 30);
          const yOffset: number = this.scroller.currentOffset()!.yOffset;
          this.scroller.scrollTo({
            xOffset: 0,
            yOffset: yOffset + 100,
            animation: { duration: 1000, curve: curve }
          });
        })
        .margin({ top: 110, left: 20 } as Margin)
      Button('back top')
        .height('5%')
        .onClick(() => {
          this.scroller.scrollEdge(Edge.Top);
        })
        .margin({ top: 160, left: 20 } as Margin)
      Button('next page')
        .height('5%')
        .onClick(() => {
          this.scroller.scrollPage({ next: true, animation: true });
        })
        .margin({ top: 210, left: 20 } as Margin)
      Button('fling -3000')
        .height('5%')
        .onClick(() => {
          this.scroller.fling(-3000);
        })
        .margin({ top: 260, left: 20 } as Margin)
      Button('scroll to bottom 700')
        .height('5%')
        .onClick(() => {
          this.scroller.scrollEdge(Edge.Bottom, { velocity: 700 });
        })
        .margin({ top: 310, left: 20 } as Margin)
    }.width('100%').height('100%').backgroundColor('#DCDCDC')
  }
}