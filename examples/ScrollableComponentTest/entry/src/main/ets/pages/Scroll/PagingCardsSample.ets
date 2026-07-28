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
struct PagingCardsSample {
  private scroller: Scroller = new Scroller();
  private pages: number[] = [1, 2, 3, 4];

  build() {
    Column({ space: 16 }) {
      Text('Paging Cards')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)

      Text('滑动页面或使用按钮，Scroll 会按卡片页停靠。')
        .fontSize(16)

      Row({ space: 12 }) {
        Button('上一页')
          .onClick(() => {
            this.scroller.scrollPage({ next: false, animation: true });
          })
        Button('下一页')
          .onClick(() => {
            this.scroller.scrollPage({ next: true, animation: true });
          })
      }

      Scroll(this.scroller) {
        Column({ space: 16 }) {
          ForEach(this.pages, (page: number) => {
            Column({ space: 12 }) {
              Text('第 ' + page + ' 页')
                .fontSize(32)
                .fontWeight(FontWeight.Bold)
              Text('每张卡片的高度与滚动视口一致。')
                .fontSize(18)
            }
            .width('100%')
            .height('100%')
            .justifyContent(FlexAlign.Center)
            .alignItems(HorizontalAlign.Center)
            .borderRadius(16)
            .backgroundColor(page % 2 === 0 ? '#D6E4FF' : '#E8F3FF')
          }, (page: number) => page.toString())
        }
      }
      .layoutWeight(1)
      .width('100%')
      .scrollable(ScrollDirection.Vertical)
      .enablePaging(true)
      .scrollBar(BarState.Auto)
      .edgeEffect(EdgeEffect.Spring)
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
