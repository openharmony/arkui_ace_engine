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


const TAG = 'entry_index2'

@Entry
@Component
export struct Index {
  @State message: string = 'Hello World';
  private arr: number[] = []
  private scrollerForList: Scroller = new Scroller()
  @State currentIndex: number = 0
  @State maxPageIndex: number = 0
  @State minPageIndex: number = 0

  aboutToAppear() {
    for (let i = 0; i < 20; i++) {
      this.arr.push(i)
    }
    this.maxPageIndex = this.arr.length - 1
    this.minPageIndex = 0
    this.scrollerForList.scrollToIndex(this.minPageIndex)
  }

  build() {
    Column() {
      Row() {
        List({ space: 20, initialIndex: 3, scroller: this.scrollerForList }) {
          ForEach(this.arr, (item: number) => {
            ListItem() {
              Text('' + item)
                .width('100%').height('100%').fontSize(16)
                .textAlign(TextAlign.Center)

            }
            .borderRadius(10).backgroundColor(Color.Pink)
            .width('100%')
            .height('100%')
          }, (item: number) => JSON.stringify(item))
        }
        .gesture(

          SwipeGesture({ direction: SwipeDirection.Vertical })
            .onAction((event: GestureEvent | undefined) => {
              if (event) {
                if (event.angle < 0) {
                  let aimPage = (this.currentIndex + 1) >= this.maxPageIndex ? this.maxPageIndex : this.currentIndex + 1
                  this.currentIndex = aimPage
                  animateTo({ duration: 200, }, () => {
                    this.scrollerForList.scrollToIndex(aimPage)
                  })
                } else {
                  let aimPage = this.currentIndex - 1 > 0 ? this.currentIndex - 1 : 0
                  this.currentIndex = aimPage
                  animateTo({ duration: 200, }, () => {
                    this.scrollerForList.scrollToIndex(aimPage)
                  })
                }
              }
            })
        )
        .flingSpeedLimit(1000)
        .chainAnimation(true)
        .edgeEffect(EdgeEffect.Spring)
        .height('100%')
        .width('100%')
        .scrollSnapAlign(ScrollSnapAlign.CENTER)
        .borderRadius(10)
        .backgroundColor(0xDCDCDC)
      }
      .width('100%')
      .height('100%')
      .backgroundColor(0xDCDCDC)
      .padding({ top: 10 })
    }
  }
}