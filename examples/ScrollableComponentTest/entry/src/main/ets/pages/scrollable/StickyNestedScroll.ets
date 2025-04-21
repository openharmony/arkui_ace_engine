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

@Entry
@Component
struct StickyNestedScroll {

  /*用例描述
   1、常规嵌套滚动模式中，都只能滚动手势被子组件接收，子组件产生的滚动偏移量去驱动父组件滚动。
   2、本用例则实现了一种在嵌套滚动模式下，将父组件的滑动偏移量传递给子组件的效果，可以在父组件抛滑到底部后，通过将剩余的滚动偏移量传递给子组件，
    使得子组件接力滑动下去，而不只是父组件突兀的停止。
   3、通过onScrollFrameBegin事件，在父组件滚动到底部时，调用子组件的scrollBy方法将后续的偏移量传递给子组件，驱动子组件滚动
  */
  /* 关键结构
   |-> Scroll (绑定OnScrollFrameBegin事件)
    |-> Tabs
     |-> List (设置嵌套滚动属性 { PARENT_FIRST, SELF_FIRST})
  */

  @State message: string = 'Hello World'
  @State arr: number[] = []
  private touchDown: boolean = false;
  private listTouchDown: boolean = false;
  private scrolling: boolean = false;
  private scroller: Scroller = new Scroller()
  private listScroller: Scroller = new Scroller()

  @Styles listCard() {
    .backgroundColor(Color.White)
      .height(72)
      .width('100%')
      .borderRadius(12)
  }

  build() {
    Scroll(this.scroller) {
      Column() {
        Text('Scroll Area')
          .width('100%')
          .height('400')
          .backgroundColor('#0080DC')
          .textAlign(TextAlign.Center)
        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            List({ space: 10, scroller: this.listScroller }) {
              ForEach(this.arr, (item: number) => {
                ListItem() {
                  Text('item' + item)
                    .fontSize(16)
                }.listCard()
              }, (item: number) => item.toString())
            }.width('100%')
              .edgeEffect(EdgeEffect.Spring)
              // 子组件上设置嵌套模式
              .nestedScroll({
                scrollForward: NestedScrollMode.PARENT_FIRST,
                scrollBackward: NestedScrollMode.SELF_FIRST
              })
              .onTouch((event: TouchEvent) => {
                if (event.type == TouchType.Down) {
                  this.listTouchDown = true;
                } else if (event.type == TouchType.Up) {
                  this.listTouchDown = false;
                }
              })
          }.tabBar('Tab1')
          TabContent() {
          }.tabBar('Tab2')
        }
        .vertical(false)
          .height('100%')
      }.width('100%')
    }.onTouch((event: TouchEvent) => {
      if (event.type == TouchType.Down) {
        this.touchDown = true;
      } else if (event.type == TouchType.Up) {
        this.touchDown = false;
      }
    })
      // 通过onScrollFrameBegin事件，在父组件滚动到底部时，调用子组件的scrollBy方法将后续的偏移量传递给子组件，驱动子组件滚动
      .onScrollFrameBegin((offset: number, state: ScrollState) => {
        if (this.scrolling && offset > 0) {
          let yOffset: number = this.scroller.currentOffset().yOffset
          if (yOffset >= 400) {
            this.listScroller.scrollBy(0, offset)
            return { offsetRemain: 0 }
          } else if (yOffset + offset > 400) {
            this.listScroller.scrollBy(0, yOffset + offset - 400)
            return { offsetRemain: 400 - yOffset }
          }
        }
        return { offsetRemain: offset }
      })
      .onScrollStart(() => {
        if (this.touchDown && !this.listTouchDown) {
          this.scrolling = true;
        }
      })
      .onScrollStop(() => {
        this.scrolling = false;
      })
      .edgeEffect(EdgeEffect.Spring)
      .backgroundColor('#DCDCDC')
      .scrollBar(BarState.Off)
      .width('100%')
      .height('100%')
  }
  aboutToAppear() {
    for (let i = 0; i < 30; i++) {
      this.arr.push(i)
    }
  }
}