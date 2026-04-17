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

import { curves, UIInspector } from '@kit.ArkUI';
import { NodeIdUtils } from './getID';

@Entry
@Component
struct ScrollExample {
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
      Scroll(this.scroller) {
        Column() {
          ForEach(this.arr2, (item: number) => {
            Text(item.toString())
              .width('90%')
              .height(150)
              .backgroundColor(0xFFFFFF)
              .borderRadius(15)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .margin({ top: 10 })
              .id('text' + item.toString())
          }, (item: number) => item.toString())
        }.width('100%')
      }
      .id('scroll')
      .key('my_scroll')
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

      Button('scrollBy -150')
        .height('5%')
        .onClick(() => { // 点击后下滑指定距离150.0vp
          this.scroller.scrollBy(0, -150);
        })
        .margin({ top: 10, left: 20 })
      Button('scrollTo 500')
        .height('5%')
        .onClick(() => { // 点击后滑动到指定位置，即下滑100.0vp的距离
          const yOffset: number = this.scroller.currentOffset().yOffset;
          this.scroller.scrollTo({ xOffset: 0, yOffset: yOffset + 500 });
        })
        .margin({ top: 60, left: 20 })
      Button('scrollTo 500 with animation')
        .height('5%')
        .onClick(() => { // 点击后滑动到指定位置，即下滑100.0vp的距离，滑动过程配置有动画
          let curve = curves.interpolatingSpring(10, 1, 228, 30); //创建一个弹簧曲线
          const yOffset: number = this.scroller.currentOffset().yOffset;
          this.scroller.scrollTo({ xOffset: 0, yOffset: yOffset + 500, animation: { duration: 1000, curve: curve } });
        })
        .margin({ top: 110, left: 20 })
      Button('scrollEdge to Top')
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
      Button('fling -3000')
        .height('5%')
        .onClick(() => { // 点击后触发初始速度为-3000vp/s的惯性滚动
          this.scroller.fling(-3000);
        })
        .margin({ top: 260, left: 20 })
      Button('scroll to bottom 700')
        .height('5%')
        .onClick(() => { // 点击后滑到下边缘，速度值是700vp/s
          this.scroller.scrollEdge(Edge.Bottom, { velocity: 700 });
        })
        .margin({ top: 310, left: 20 })

      Button('id')
        .height('5%')
        .onClick(() => { //

          NodeIdUtils.getNodeInternalId(this.getUIContext(), "scroll", "text", 100)
        })
        .margin({ top: 360, left: 20 })

      Button("edgeEffect" + this.edgeEffectNameArr[this.edgeEffectArrIndex])
        .height('5%')
        .onClick(() => {
          this.edgeEffectArrIndex++;
          if (this.edgeEffectArrIndex >= this.edgeEffectArr.length) {
            this.edgeEffectArrIndex %= this.edgeEffectArr.length
          }
        })
        .margin({ top: 410, left: 20 })

    }.width('100%').height('100%').backgroundColor(0xDCDCDC)
  }
}