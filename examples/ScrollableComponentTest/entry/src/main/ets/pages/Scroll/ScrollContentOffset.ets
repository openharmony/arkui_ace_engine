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
struct ScrollContentOffsetTest {
  private arr: number[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18];
  @State edgeE: EdgeEffect = EdgeEffect.Spring
  @State alwaysEnable: boolean = false;
  @State currentOffset: number = 0
  @State startOffset: number = 20
  @State endOffset: number = 30
  @State isAtEnd: boolean = false
  @State fadingEdge: boolean = false
  @State backToTop: boolean = false
  scroller: Scroller = new Scroller();

  build() {
    Column({ space: 5 }) {
      Scroll() {
        Column({ space: 5 }) {
          Row() {
            Button('currentOffset: ' + this.currentOffset)
              .onClick(() => {
                this.currentOffset = this.scroller.currentOffset()?.yOffset
              })
            Button('isAtEnd:' + this.isAtEnd)
              .onClick(() => {
                this.isAtEnd = this.scroller.isAtEnd()
              })
          }

          Row() {
            Button('EdgeEffect')
              .onClick(() => {
                if (this.edgeE === EdgeEffect.Spring) {
                  this.edgeE = EdgeEffect.None
                } else {
                  this.edgeE = EdgeEffect.Spring
                }
              })
            Button('alwaysEnable:' + this.alwaysEnable)
              .onClick(() => {
                this.alwaysEnable = !this.alwaysEnable
              })
          }

          Row({ space: 5 }) {
            Button('fadingEdge:' + this.fadingEdge)
              .onClick(() => {
                this.fadingEdge = !this.fadingEdge
              })
            Button('backToTop:' + this.backToTop)
              .onClick(() => {
                this.backToTop = !this.backToTop
              })
          }

          Row() {
            Button('下滚一页')
              .onClick(() => {
                this.scroller.scrollPage({ next: true })
              })
            Button('上滚一页')
              .onClick(() => {
                this.scroller.scrollPage({ next: false })
              })
          }

          Row() {
            Button('Scroll by 200')
              .onClick(() => {
                this.scroller.scrollBy(0, 200)
              })
            Button('scroll by -200')
              .onClick(() => {
                this.scroller.scrollBy(0, -200)
              })
          }

          Row() {
            Button('start++')
              .onClick(() => {
                this.startOffset += 10
              })
            Button('start--')
              .onClick(() => {
                if (this.startOffset > 0) {
                  this.startOffset -= 10
                }
              })
          }

          Row() {
            Button('end++')
              .onClick(() => {
                this.endOffset += 10
              })
            Button('end--')
              .onClick(() => {
                if (this.endOffset > 0) {
                  this.endOffset -= 10
                }
              })
          }
        }
      }.height('40%')

      Scroll(this.scroller) {
        Column() {
          ForEach(this.arr, (item: string, index: number) => {
            Column() {
              Text(item)
                .width('30%')
                .height(100)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .focusable(true)
                .borderRadius(10)
                .backgroundColor(Color.Orange)
            }
          }, (item: string) => item)
        }
      }
      .edgeEffect(this.edgeE, { alwaysEnabled: this.alwaysEnable })
      .width('90%')
      .height(300)
      .borderWidth(1)
      .backgroundColor(Color.Green)
      .scrollBar(BarState.On)
      .contentStartOffset(this.startOffset)
      .contentEndOffset(this.endOffset)
      .scrollBarWidth(20)
      .onScrollStart(() => {
        console.log('scroll on scroll start')
      })
      .onScrollStop(() => {
        console.log('scroll on scroll stop')
      })
      .onReachStart(() => {
        console.log('scroll on reach start')
      })
      .onReachEnd(() => {
        console.log('scroll on reach end')
      })
      .onDidScroll((offset: number, state: ScrollState) => {
        console.log('scroll on did scroll offset:' + offset + ', state:' + state)
      })
      .onWillScroll((xOffset: number, yOffset: number, state: ScrollState, source: ScrollSource) => {
        console.log('scroll on did scroll xOffset:' + xOffset + ', yOffset:' + yOffset + ', state:' + state +
          ', source:' + source)
      })
      .fadingEdge(this.fadingEdge)
      .backToTop(this.backToTop)
    }
  }
}