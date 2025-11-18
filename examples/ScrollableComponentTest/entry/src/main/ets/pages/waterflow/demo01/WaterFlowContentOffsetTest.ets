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

import { WaterFlowDataSource } from './WaterFlowDataSource';
import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct WaterFlowContentOffsetTest {
  arr: WaterFlowDataSource = new WaterFlowDataSource([])
  @State edgeE: EdgeEffect = EdgeEffect.Spring
  @State alwaysEnable: boolean = false;
  @State columnCount: number = 2
  @State columnTemplate: string = '1fr '.repeat(this.columnCount)
  @State currentOffset: number = 0
  @State startOffset: number = 20
  @State endOffset: number = 30
  @State ani: boolean = false
  @State scrollAlign: ScrollAlign = ScrollAlign.START
  @State extraOffset: number = 0
  @State isAtEnd: boolean = false
  @State cachedCount: number = 3
  @State showCache: boolean = false
  @State fadingEdge: boolean = false
  @State backToTop: boolean = false
  scroller: Scroller = new Scroller();
  irregular: boolean = false;

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
            Text('cachedCount:' + this.cachedCount)
            Button('++cache')
              .onClick(() => {
                this.cachedCount++
              })
            Button('--cache')
              .onClick(() => {
                this.cachedCount--
              })
          }

          Row({ space: 5 }) {
            Button('showCache:' + this.showCache)
              .onClick(() => {
                this.showCache = !this.showCache
              })
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
            Button('AUTO')
              .onClick(() => {
                this.scrollAlign = ScrollAlign.AUTO
              })
            Button('START')
              .onClick(() => {
                this.scrollAlign = ScrollAlign.START
              })
            Button('CENTER')
              .onClick(() => {
                this.scrollAlign = ScrollAlign.CENTER
              })
            Button('END')
              .onClick(() => {
                this.scrollAlign = ScrollAlign.END
              })
          }

          Row() {
            Button('开动画')
              .onClick(() => {
                this.ani = true
              })
            Button('关动画')
              .onClick(() => {
                this.ani = false
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

          Row({ space: 5 }) {
            Text('extraOffset:' + this.extraOffset)
            Button('++extra')
              .onClick(() => {
                this.extraOffset++
              })
            Button('--extra')
              .onClick(() => {
                this.extraOffset--
              })
          }

          Row() {
            Button('列数++')
              .onClick(() => {
                this.columnCount++
              })
            Button('列数--')
              .onClick(() => {
                if (this.columnCount > 1) {
                  this.columnCount--
                }
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
                if (this.columnCount > 0) {
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
                if (this.columnCount > 0) {
                  this.endOffset -= 10
                }
              })
          }

          Row({ space: 5 }) {
            Text('Scroll to index')
            Button('0')
              .onClick(() => {
                this.scroller.scrollToIndex(0, this.ani, this.scrollAlign,
                  { extraOffset: LengthMetrics.px(this.extraOffset) })
              })
            Button('10')
              .onClick(() => {
                this.scroller.scrollToIndex(0, this.ani, this.scrollAlign,
                  { extraOffset: LengthMetrics.px(this.extraOffset) })
              })
            Button('24')
              .onClick(() => {
                this.scroller.scrollToIndex(0, this.ani, this.scrollAlign,
                  { extraOffset: LengthMetrics.px(this.extraOffset) })
              })
            Button('22')
              .onClick(() => {
                this.scroller.scrollToIndex(0, this.ani, this.scrollAlign,
                  { extraOffset: LengthMetrics.px(this.extraOffset) })
              })
          }
        }
      }.height('40%')

      WaterFlow({scroller:this.scroller}) {
        LazyForEach(this.arr, (item: string, index: number) => {
          FlowItem() {
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
      .columnsTemplate(this.columnTemplate)
      .columnsGap(10)
      .rowsGap(10)
      .edgeEffect(this.edgeE, { alwaysEnabled: this.alwaysEnable })
      .width('90%')
      .height(300)
      .borderWidth(1)
      .backgroundColor(Color.Green)
      .cachedCount(this.cachedCount, this.showCache)
      .scrollBar(BarState.On)
      .contentStartOffset(this.startOffset)
      .contentEndOffset(this.endOffset)
      .scrollBarWidth(20)
      .onScrollStart(() => {
        console.log('grid on scroll start')
      })
      .onScrollStop(() => {
        console.log('grid on scroll stop')
      })
      .onReachStart(() => {
        console.log('grid on reach start')
      })
      .onReachEnd(() => {
        console.log('grid on reach end')
      })
      .onScrollIndex((start: number, end: number) => {
        console.log('grid on scroll index start' + start + ', end:' + end)
      })
      .onDidScroll((offset: number, state: ScrollState) => {
        console.log('grid on did scroll offset:' + offset + ', state:' + state)
      })
      .onWillScroll((offset: number, state: ScrollState, source: ScrollSource) => {
        console.log('grid on did scroll offset:' + offset + ', state:' + state + ', source:' + source)
      })
      .fadingEdge(this.fadingEdge)
      .backToTop(this.backToTop)
    }
  }
}