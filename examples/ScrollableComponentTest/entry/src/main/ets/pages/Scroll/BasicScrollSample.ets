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

@Entry
@Component
struct BasicScrollSample {
  private scroller: Scroller = new Scroller();
  private items: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
  @State scrollOffset: number = 0;

  private syncScrollOffset(): void {
    let currentOffset = this.scroller.currentOffset();
    if (currentOffset !== undefined) {
      this.scrollOffset = currentOffset.yOffset;
    }
  }

  build() {
    Column({ space: 12 }) {
      Text('Scroll Sample')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)

      Text('当前滚动偏移：' + this.scrollOffset.toFixed(0) + ' vp')
        .fontSize(16)

      Row({ space: 12 }) {
        Button('回到顶部')
          .onClick(() => {
            this.scroller.scrollTo({ xOffset: 0, yOffset: 0, animation: { duration: 300 } });
            this.syncScrollOffset();
            setTimeout(() => {
              this.syncScrollOffset();
            }, 350);
          })
        Button('向下滚动')
          .onClick(() => {
            this.scroller.scrollBy(0, 200);
            this.syncScrollOffset();
            setTimeout(() => {
              this.syncScrollOffset();
            }, 350);
          })
      }

      Scroll(this.scroller) {
        Column({ space: 12 }) {
          ForEach(this.items, (item: number) => {
            Text('滚动内容 ' + item)
              .width('100%')
              .height(100)
              .padding(16)
              .fontSize(18)
              .borderRadius(12)
              .backgroundColor(item % 2 === 0 ? '#D6E4FF' : '#E8F3FF')
          }, (item: number) => item.toString())
        }
        .width('100%')
      }
      .layoutWeight(1)
      .width('100%')
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(BarState.Auto)
      .edgeEffect(EdgeEffect.Spring)
      .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        this.scrollOffset += yOffset;
        if (this.scrollOffset < 0) {
          this.scrollOffset = 0;
        }
      })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
