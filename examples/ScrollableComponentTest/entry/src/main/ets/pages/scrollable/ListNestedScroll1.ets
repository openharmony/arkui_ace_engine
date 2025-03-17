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


// 使用onScrollFrameBegin实现List和多个Scroll子组件的嵌套滚动
@Entry
@Component
struct ListNestedScroll1 {
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
  /* 关键结构
   |-> List (100%高度, scrollerForList)
    |-> Scroll (100%高度, scroller2)
     |-> List (横向)
     |-> Scroll (100%高度, scroller1)
    |-> Scroll (100%高度, scroller3)
  */

  private scrollerForList: Scroller = new Scroller()
  private scroller1: Scroller = new Scroller()
  private scroller2: Scroller = new Scroller()
  private scroller3: Scroller = new Scroller()
  build() {
    Column() {
      List({ space: 20, initialIndex: 0, scroller: this.scrollerForList }) {
        ListItem() {
          Scroll(this.scroller2) {
            Column() {
              Row() {
                List({ space: 20, initialIndex: 3 }) {
                  ForEach(this.arr, (item: number) => {
                    ListItem() {
                      Text('' + item)
                        .width('100%').height('100%').fontSize(16)
                        .textAlign(TextAlign.Center)
                    }
                    .borderRadius(10).backgroundColor(0xFFFFFF)
                      .width('60%')
                  }, (item: number) => JSON.stringify(item))
                }
                .edgeEffect(EdgeEffect.None)
                  .listDirection(Axis.Horizontal)
                  .height('100vp')
                  .width('100%')
                  .borderRadius(10)
                  .backgroundColor(0xDCDCDC)
                  .scrollBar(BarState.Off)
              }
              .width('100%')
                .backgroundColor(0xDCDCDC)

              Scroll(this.scroller1) {
                Column() {
                  ForEach(this.arr, (item: number) => {
                    Text(item.toString())
                      .width('90%')
                      .height(150)
                      .backgroundColor(0xFFFFFF)
                      .borderRadius(15)
                      .fontSize(16)
                      .textAlign(TextAlign.Center)
                      .margin({ top: 10 })
                  }, (item: string) => item)
                }.width('100%')
              }
              .enableScrollInteraction(false) //禁用该组件手势滑动
                .backgroundColor(Color.Red)
                .height('100%')
                .scrollable(ScrollDirection.Vertical)
                .scrollBar(BarState.Off)
                .edgeEffect(EdgeEffect.None)
            }
          }
          .enableScrollInteraction(false) //禁用该组件手势滑动
            .scrollBar(BarState.Off)
            .edgeEffect(EdgeEffect.None)
            .height('100%')
        }

        ListItem() {
          Scroll(this.scroller3) {
            Column() {
              ForEach(this.arr, (item: number) => {
                Text(item.toString())
                  .width('90%')
                  .height(150)
                  .backgroundColor(0xFFFFFF)
                  .borderRadius(15)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .margin({ top: 10 })
              }, (item: string) => item)
            }.width('100%')
          }
          .enableScrollInteraction(false) //禁用该组件手势滑动
            .backgroundColor(Color.Yellow)
            .height('100%')
            .scrollable(ScrollDirection.Vertical)
            .scrollBar(BarState.Off)
            .edgeEffect(EdgeEffect.None)
        }
      }

      // 禁用了所有子组件的手势滑动后，所有子组件的滑动交由最外面的父组件通过onScrollFrameBegin来统一调度分配
      // 滚动到上边界：scroller.currentOffset().yOffset 小于等于0
      // 滚动到下边界：scroller.isAtEnd() 为true
      .onScrollFrameBegin((offset: number, state: ScrollState) => {
        console.log('ZRJ onScrollFrameBegin offset:' + offset + ' scrollerForList.isAtEnd:' + this.scrollerForList.isAtEnd())
        if (offset > 0) {
          if (!this.scrollerForList.isAtEnd()) {
            if (!this.scroller2.isAtEnd()) {
              this.scroller2.scrollBy(0, offset)
              return { offsetRemain: 0 };
            } else if (!this.scroller1.isAtEnd()) {
              this.scroller1.scrollBy(0, offset)
              return { offsetRemain: 0 };
            }
          } else {
            this.scroller3.scrollBy(0, offset)
            return { offsetRemain: 0 };
          }
        }

        if (offset < 0) {
          if (this.scroller3.currentOffset().yOffset > 0) {
            this.scroller3.scrollBy(0, offset)
            return { offsetRemain: 0 };
          } else if (this.scrollerForList.currentOffset().yOffset <= 0) {
            if (this.scroller1.currentOffset().yOffset > 0) {
              this.scroller1.scrollBy(0, offset)
              return { offsetRemain: 0 };
            } else {
              this.scroller2.scrollBy(0, offset)
              return { offsetRemain: 0 };
            }
          }
        }
        return { offsetRemain: offset };
      })
        .listDirection(Axis.Vertical)
        .scrollBar(BarState.Off)
        .friction(0.6)
        .edgeEffect(EdgeEffect.Spring)
        .width('90%')
        .height('100%')
    }
    .width('100%')
      .height('100%')
      .backgroundColor(0xDCDCDC)
  }
}