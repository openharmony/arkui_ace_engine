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

class SwiperNestListMyDataSource implements IDataSource {
  private list: number[] = []

  constructor(list: number[]) {
    this.list = list
  }

  totalCount(): number {
    return this.list.length
  }

  getData(index: number): number {
    return this.list[index]
  }

  registerDataChangeListener(listener: DataChangeListener): void {
  }

  unregisterDataChangeListener() {
  }
}

@Entry
@Component
struct OnContentWillScrollNestList {
  private swiperController: SwiperController = new SwiperController()
  private data: SwiperNestListMyDataSource = new SwiperNestListMyDataSource([])
  @State text: number = 0
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
  @State currentIndex: number = 0
  @State comingIndex: number = 0
  @State swiperWidth: Length = 300
  @State swiperHeight: Length = '30%'
  @State willScrollCurrentIndex: number = 0
  @State willScrollComingIndex: number = 0
  @State willScrollOffset: number = 0

  aboutToAppear(): void {
    let list: number[] = []
    for (let i = 0; i <= 4; i++) {
      list.push(i);
    }
    this.data = new SwiperNestListMyDataSource(list)
  }

  build() {
    Column({ space: 5 }) {
      Swiper(this.swiperController) {
        LazyForEach(this.data, (item: string) => {
          List({ space: 5, initialIndex: 0 }) {
            ForEach(this.arr, (item: number) => {
              ListItem() {
                Flex({ direction: FlexDirection.Row, alignItems: ItemAlign.Center }) {
                  Text('' + item)
                    .width('100%')
                    .height(20)
                    .fontSize(16)
                    .textAlign(TextAlign.Center)
                    .borderRadius(10)
                    .backgroundColor(0xFFFFFF)
                }

              }
            }, (item: string) => item)
          }
          .borderWidth(1)
          .nestedScroll({ scrollForward: NestedScrollMode.SELF_FIRST, scrollBackward: NestedScrollMode.SELF_FIRST })
          .edgeEffect(EdgeEffect.None)
          .width('30%')
          .height('30%')
          .alignRules({
            bottom: { anchor: '__container__', align: VerticalAlign.Bottom },
            left: { anchor: '__container__', align: HorizontalAlign.Start }
          })

        }, (item: string) => item)

      }
      .backgroundColor(Color.Pink)
      .vertical(true)
      .width(this.swiperWidth)
      .height(this.swiperHeight)
      .onContentWillScroll((info: SwiperContentWillScrollResult) => {
        this.willScrollCurrentIndex = info.currentIndex
        this.willScrollComingIndex = info.comingIndex
        this.willScrollOffset = info.offset

        if (info.currentIndex == this.currentIndex && info.comingIndex == this.comingIndex) {
          return false;
        }

        return true
      })

      Scroll() {
        Column({ space: 12 }) {
          Text('will scroll currentIndex: ' + this.willScrollCurrentIndex + ', comingIndex: ' +
          this.willScrollComingIndex + ', offset: ' + this.willScrollOffset)
            .margin(5)

          Text('拦截条件: ' + this.currentIndex + ' 到 ' + this.comingIndex)
            .margin(5)

          Row() {
            Button('currentIndex++')
              .onClick(() => {
                this.currentIndex++
              })
              .margin(5)
              .fontSize(15)

            Button('currentIndex--')
              .onClick(() => {
                this.currentIndex--
              })
              .margin(5)
              .fontSize(15)
          }

          Row() {
            Button('comingIndex++')
              .onClick(() => {
                this.comingIndex++
              })
              .margin(5)
              .fontSize(15)

            Button('comingIndex--')
              .onClick(() => {
                this.comingIndex--
              })
              .margin(5)
              .fontSize(15)
          }
        }.margin(5)
      }
      .height('60%')
    }
  }
}

