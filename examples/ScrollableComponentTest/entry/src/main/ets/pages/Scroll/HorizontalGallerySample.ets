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
struct HorizontalGallerySample {
  private scroller: Scroller = new Scroller();
  private cards: string[] = ['海洋', '森林', '日落', '星空', '雪山'];
  @State xOffset: number = 0;

  build() {
    Column({ space: 16 }) {
      Text('Horizontal Gallery')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)

      Text('水平偏移：' + this.xOffset.toFixed(0) + ' vp')
        .fontSize(16)

      Row({ space: 12 }) {
        Button('向左滚动')
          .onClick(() => {
            this.scroller.scrollBy(-240, 0);
          })
        Button('向右滚动')
          .onClick(() => {
            this.scroller.scrollBy(240, 0);
          })
      }

      Scroll(this.scroller) {
        Row({ space: 12 }) {
          ForEach(this.cards, (card: string, index: number) => {
            Column({ space: 12 }) {
              Text(card)
                .fontSize(24)
                .fontWeight(FontWeight.Bold)
              Text('卡片 ' + (index + 1))
                .fontSize(16)
            }
            .width(220)
            .height(280)
            .justifyContent(FlexAlign.Center)
            .alignItems(HorizontalAlign.Center)
            .borderRadius(16)
            .backgroundColor(index % 2 === 0 ? '#D6E4FF' : '#E8F3FF')
          }, (card: string) => card)
        }
        .padding({ left: 16, right: 16 })
      }
      .layoutWeight(1)
      .width('100%')
      .scrollable(ScrollDirection.Horizontal)
      .scrollBar(BarState.Auto)
      .edgeEffect(EdgeEffect.Spring)
      .onDidScroll((xOffset: number, yOffset: number) => {
        this.xOffset = xOffset;
      })
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
