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

import { WaterFlowDataSource } from './WaterFlowDataSource';
import {NodeIdUtils} from  '../grid/GetID';

enum FooterState {
  Loading = 0,
  End = 1
}

@Entry
@Component
struct WaterFlowDemo {
  @State minSize: number = 80;
  @State maxSize: number = 180;
  @State colors: number[] = [0xFFC0CB, 0xDA70D6, 0x6B8E23, 0x6A5ACD, 0x00FFFF, 0x00FF7F];
  @State footerState: FooterState = FooterState.Loading;
  scroller: Scroller = new Scroller();
  dataSource: WaterFlowDataSource = new WaterFlowDataSource();
  private itemWidthArray: number[] = [];
  private itemHeightArray: number[] = [];
  @State arr2: number[] = []

  // 计算FlowItem宽/高
  getSize() {
    let ret = Math.floor(Math.random() * this.maxSize);
    return (ret > this.minSize ? ret : this.minSize);
  }

  // 设置FlowItem的宽/高数组
  setItemSizeArray() {
    for (let i = 0; i < 100; i++) {
      this.itemWidthArray.push(this.getSize());
      this.itemHeightArray.push(this.getSize());
    }
  }

  // 组件生命周期：在组件即将出现时初始化尺寸数组
  aboutToAppear() {
    this.setItemSizeArray();
    for (let i = 0; i < 100; i++) {
      this.arr2.push(i)
    }
  }

  @Builder
  itemFoot() {
    // 注意：不要直接用IfElse节点作为footer的根节点
    // 必须在外面使用(Column/Row/Stack等)容器包裹，确保布局正确
    Column() {
      if (this.footerState == FooterState.Loading) {
        Text(`加载中...`)
          .fontSize(10)
          .backgroundColor(Color.Red)
          .width(50)
          .height(50)
          .align(Alignment.Center)
          .margin({ top: 2 })
      } else if (this.footerState == FooterState.End) {
        Text(`到底啦...`)
          .fontSize(10)
          .backgroundColor(Color.Red)
          .width(50)
          .height(50)
          .align(Alignment.Center)
          .margin({ top: 2 })
      } else {
        Text(`Footer`)
          .fontSize(10)
          .backgroundColor(Color.Red)
          .width(50)
          .height(50)
          .align(Alignment.Center)
          .margin({ top: 2 })
      }
    }
  }

  build() {
    Column({ space: 2 }) {
      Stack({ alignContent: Alignment.TopStart }) {
        WaterFlow({ scroller: this.scroller, footer: this.itemFoot() }) {
          ForEach(this.arr2, (item: number, index?: number) => {
            FlowItem() {
              Column() {
                Text('N' + item).fontSize(12).height('16')
                  .id('text' + item.toString())

                // 注意：需要确保对应的jpg文件存在才会正常显示
                Image('res/waterFlowTest(' + item % 5 + ').jpg')
                  .objectFit(ImageFit.Fill)
                  .width('100%')
                  .layoutWeight(1)
              }
            }
          }, (item: string, index?: number) => item)

        }
        .id('WaterFlow')
        .rowsTemplate('1fr ')
        .cachedCount(1000, true)
        .columnsTemplate('1fr') // 设置2列等宽布局
        .columnsGap(10)
        .rowsGap(5)
        .backgroundColor(0xFAEEE0)
        .width('100%')
        .height('100%')
        .itemConstraintSize({
          minWidth: 80,
          maxWidth: 180,
          minHeight: 80,
          maxHeight: 180
        })
        // 触底加载数据：滚动到底部时触发分页加载
        .onReachEnd(() => {
          console.info('onReachEnd')

          // 模拟分页加载：当数据超过200条时停止加载
          if (this.dataSource.totalCount() > 200) {
            this.footerState = FooterState.End;
            return;
          }
          setTimeout(() => {
            for (let i = 0; i < 100; i++) {
              this.dataSource.addLastItem();
            }
          }, 1000)
        })
        .onReachStart(() => {
          // 滚动到顶部时触发
          console.info('waterFlow reach start');
        })
        .onScrollStart(() => {
          // 开始滚动时触发
          console.info('laoxu waterFlow scroll start');
        })
        .onScrollStop(() => {
          // 停止滚动时触发
          console.info('laoxu waterFlow scroll stop');
        })
        .onScrollFrameBegin((offset: number, state: ScrollState) => {
          // 滚动帧开始时触发：可以控制滚动行为
          // offset：滚动偏移量，state：滚动状态
          console.info('waterFlow scrollFrameBegin offset: ' + offset + ' state: ' + state.toString());
          return { offsetRemain: offset }; // 返回开发者期望的实际滚动偏移量
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
          .onClick(() => { //

            NodeIdUtils.getNodeInternalId(this.getUIContext(), 'WaterFlow', 'text', 100)
          })
          .margin({ top: 360, left: 20 })
      }
    }
  }
}