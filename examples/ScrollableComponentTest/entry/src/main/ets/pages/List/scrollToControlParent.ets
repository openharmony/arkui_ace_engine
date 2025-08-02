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
  private scroller: Scroller = new Scroller()
  private listScroller: Scroller = new Scroller();
  private scrollOffset: number = 0
  @State arr: number[] = []

  @Styles
  listCard() {
    .backgroundColor(Color.White)
    .height(72)
    .width('100%')
    .borderRadius(12)
  }

  scrollerBy(offset: number):void {
    if (this.scroller.isAtEnd()) {
      this.listScroller.scrollBy(0, offset)
      return;
    }
    this.scrollOffset = 0;
    this.getUIContext()?.animateTo({duration:0}, ()=>{
      this.scroller.scrollBy(0, offset)
    })
    this.listScroller.scrollBy(0, offset - this.scrollOffset)
  }

  build() {
    Scroll(this.scroller) {
      Column() {
        Text('Scroll Area')
          .width('100%')
          .height('40%')
          .backgroundColor('#0080DC')
          .textAlign(TextAlign.Center)
          .onClick(()=>{
            this.scrollerBy(100)
          })
        Tabs({ barPosition: BarPosition.Start }) {
          TabContent() {
            List({ space: 10, scroller:this.listScroller }) {
              ForEach(this.arr, (item: number) => {
                ListItem() {
                  Text('item' + item)
                    .fontSize(16)
                }.listCard()
              }, (item: string) => item)
            }.width('100%')
            .edgeEffect(EdgeEffect.Spring)
            .nestedScroll({
              scrollForward: NestedScrollMode.PARENT_FIRST,
              scrollBackward: NestedScrollMode.SELF_FIRST
            })
            .onClick(()=>{
              this.scrollerBy(100)
            })
          }.tabBar('Tab1')

          TabContent() {
          }.tabBar('Tab2')
        }
        .vertical(false)
        .height('100%')
      }.width('100%')
    }
    .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState)=>{
      this.scrollOffset = yOffset
    })
    .edgeEffect(EdgeEffect.Spring)
    .friction(0.6)
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