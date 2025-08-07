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
 1、本用例为Refresh嵌套Scroll再嵌套List场景下，滑动List时触发Refresh的下拉刷新
*/
/* 关键结构
 |-> Refresh
  |-> Scroll
   |-> Text
   |-> List
   |-> Text
*/
@Entry
@Component
struct RefreshNestedScroll {
  private headerHeight: number = 0;
  private arr: number[] = [];
  private scrollerForParent: Scroller = new Scroller();
  private scrollerForChild: Scroller = new Scroller();
  @State isRefreshing: boolean = false;

  aboutToAppear(): void {
    for (let i = 0; i < 100; i++) {
      this.arr.push(i);
    }
  }

  @Builder
  customRefreshComponent() {
    Stack() {
      Row() {
        LoadingProgress().height(32)
        Text('Refreshing...').fontSize(16).margin({ left: 20 })
      }
      .alignItems(VerticalAlign.Center)
    }
    .align(Alignment.Center)
    .clip(true)
    .constraintSize({ minHeight: 32 }) // 设置最小高度约束，保证自定义组件高度随刷新区域高度变化时，自定义组件高度不会低于minHeight
    .width('100%')
  }

  build() {
    Refresh({ refreshing: $$this.isRefreshing, builder: this.customRefreshComponent() }) {
      Scroll(this.scrollerForParent) {
        Column() {
          Text('Scroll Area')
            .width('100%')
            .height('40%')
            .backgroundColor(Color.Pink)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .onClick(() => {
              this.scrollerForChild.scrollToIndex(5);
            })
            .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
              this.headerHeight = newValue.height! as number;
            })

          List({ space: 20, scroller: this.scrollerForChild }) {
            ForEach(this.arr, (item: number) => {
              ListItem() {
                Text('ListItem' + item)
                  .width('100%')
                  .height('100%')
                  .borderRadius(15)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .backgroundColor(Color.White)
              }
              .width('100%')
              .height(100)
            }, (item: string) => item)
          }
          .width('100%')
          .height('100%')
          .edgeEffect(EdgeEffect.None)
          .scrollBar(BarState.Off)
          .enableScrollInteraction(false)

          Text('Scroll Area')
            .width('100%')
            .height('40%')
            .backgroundColor(Color.Pink)
            .fontSize(16)
            .textAlign(TextAlign.Center)
        }
      }
      .scrollBar(BarState.Off)
      .edgeEffect(EdgeEffect.Spring)
      .nestedScroll({
        scrollForward: NestedScrollMode.SELF_FIRST,
        scrollBackward: NestedScrollMode.SELF_FIRST
      })
      .onScrollFrameBegin((offset: number, state: ScrollState) => {
        let retOffset = offset;
        let currentOffset = this.scrollerForParent.currentOffset().yOffset;
        let newOffset = currentOffset + offset;
        if (offset > 0) {
          if (this.scrollerForChild.isAtEnd()) {
            return { offsetRemain: offset };
          }
          if (newOffset > this.headerHeight) {
            retOffset = this.headerHeight - currentOffset;
          }
          this.scrollerForChild.scrollBy(0, offset - retOffset);
        } else {
          if (this.scrollerForChild.currentOffset().yOffset <= 0) {
            return { offsetRemain: offset };
          }
          if (newOffset < this.headerHeight) {
            retOffset = this.headerHeight - currentOffset;
          }
          this.scrollerForChild.scrollBy(0, offset - retOffset);
        }
        return { offsetRemain: retOffset };
      })
      .width('100%')
      .height('100%')
      .backgroundColor(0xDCDCDC)
    }
    .pullToRefresh(true)
    .refreshOffset(64)
    .onStateChange((refreshStatus: RefreshStatus) => {
      console.info('Refresh onStatueChange state is ' + refreshStatus);
    })
    .onRefreshing(() => {
      setTimeout(() => {
        this.isRefreshing = false;
      }, 2000);
      console.info('onRefreshing');
    })
  }
}