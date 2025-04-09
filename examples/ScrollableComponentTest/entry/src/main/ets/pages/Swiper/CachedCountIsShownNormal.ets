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

class CachedCountIsShownNormalDataSource implements IDataSource {
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
struct CachedCountIsShownNormal {
  private swiperController: SwiperController = new SwiperController()
  private data: CachedCountIsShownNormalDataSource = new CachedCountIsShownNormalDataSource([])
  @State private arr: string[] = ['0', '1', '2', '3', '4']
  @State index: number = 0
  @State displayCount: number = 1
  @State cachedCount: number = 1
  @State show: boolean = true
  @State swiperClip: boolean = true
  @State loop: boolean = false
  @State swipeByGroup: boolean = false
  @State prevMargin: number = 0
  @State nextMargin: number = 0
  @State itemSpace: number = 0
  @State changeIndex: number = 0
  @State preloadIndex: number = 0
  @State dirc: Direction = Direction.Ltr
  @State swiperWidth: Length = '20%'
  @State swiperHeight: Length = '20%'
  @State nextIgnoreBlank: boolean = false
  @State prevIgnoreBlank: boolean = false
  @State flag: boolean = false
  @State vertical: boolean = false
  @State preloadIndexArr: Array<Array<number>> =
    [[3, 4, 5], [4, 5], [3, 5], [7, 8], [1, 2], [4, 6], [4, 1], [10, 6], [10, 7], [10, 9], [10, 1]]
  @State arrIndex: number = 0
  @State createFlag: number = 0
  @State createText: string = '非控制节点'

  aboutToAppear(): void {
    let list: number[] = []
    for (let i = 0; i <= 9; i++) {
      list.push(i);
    }
    this.data = new CachedCountIsShownNormalDataSource(list)
  }

  build() {
    Column({ space: 5 }) {
      Column().height('10%')
      Swiper(this.swiperController) {
        if (this.createFlag == 0) {
          Text('0')
            .width('100%')
            .height('80%')
            .textAlign(TextAlign.Center)
            .fontSize(30)
            .borderWidth(1)

          Text('1')
            .width('100%')
            .height('80%')
            .textAlign(TextAlign.Center)
            .fontSize(30)
            .borderWidth(1)

          Text('2')
            .width('100%')
            .height('80%')
            .textAlign(TextAlign.Center)
            .fontSize(30)
            .borderWidth(1)

          Text('3')
            .width('100%')
            .height('80%')
            .textAlign(TextAlign.Center)
            .fontSize(30)
            .borderWidth(1)

          Text('4')
            .width('100%')
            .height('80%')
            .textAlign(TextAlign.Center)
            .fontSize(30)
            .borderWidth(1)
        } else if (this.createFlag == 1) {
          ForEach(this.arr, (item: string) => {
            CachedCountComponent({ txt: item.toString() })
          })
        } else if (this.createFlag == 2) {
          LazyForEach(this.data, (item: number) => {
            CachedCountComponent({ txt: item.toString() })
          })
        } else if (this.createFlag == 3) {
          Repeat(this.arr)
            .virtualScroll({
              totalCount: this.arr.length
            })
            .each((ri) => {
              CachedCountComponent({ txt: ri.item })
            })
        }
      }
      .indicator(new DotIndicator().mask(true))
      .backgroundColor(Color.Blue)
      .width(this.swiperWidth)
      .height(this.swiperHeight)
      .index(this.index)
      .displayCount(this.displayCount, this.swipeByGroup)
      .cachedCount(this.cachedCount, this.show)
      .loop(this.loop)
      .prevMargin(this.prevMargin, this.prevIgnoreBlank)
      .nextMargin(this.nextMargin, this.nextIgnoreBlank)
      .itemSpace(this.itemSpace)
      .clip(this.swiperClip)
      .direction(this.dirc)
      .borderWidth(1)
      .vertical(this.vertical)

      Text('index:' + this.index + ', displayCount:' + this.displayCount + ', cachedCount:' + this.cachedCount +
        ', show:' + (this.show ? 'true' : 'false') + ', loop:' + (this.loop ? 'true' : 'false') + ', prevMargin' +
      this.prevMargin + ', nextMargin:' + this.nextMargin + ', itemSpace:' +
      this.itemSpace + ', changeIndex:' + this.changeIndex + ', swipeByGroup:' + this.swipeByGroup +
        ', nextIgnoreBlank:' + (this.nextIgnoreBlank ? 'true' : 'false') + ', prevIgnoreBlank:' +
        (this.prevIgnoreBlank ? 'true' : 'false') + ', preloadIndex:' + this.preloadIndex + ', 创建方式：' +
      this.createFlag + ', vertical:' + this.vertical)

      Scroll() {
        Column() {
          Button('change vertical')
            .onClick(() => {
              this.vertical = !this.vertical
            })
            .margin(5)

          Button('非控制节点')
            .onClick(() => {
              this.createFlag = 0
            })
            .margin(5)

          Button('使用ForEach')
            .onClick(() => {
              this.createFlag = 1
            })
            .margin(5)

          Button('使用LazyForEach')
            .onClick(() => {
              this.createFlag = 2
            })
            .margin(5)

          Button('Repeat')
            .onClick(() => {
              this.createFlag = 3
            })
            .margin(5)

          Button('add preloadItems index')
            .onClick(() => {
              this.preloadIndex++
            })
            .margin(5)

          Button('minus preloadItems index')
            .onClick(() => {
              this.preloadIndex--
            })
            .margin(5)

          Button('add preloadItems array index')
            .onClick(() => {
              this.arrIndex++
            })
            .margin(5)

          Button('minus preloadItems array index')
            .onClick(() => {
              this.arrIndex--
            })
            .margin(5)

          Row() {
            Button('swiper width=10%')
              .onClick(() => {
                this.swiperWidth = '10%'
              })
              .margin(5)

            Button('swiper width=20%')
              .onClick(() => {
                this.swiperWidth = '20%'
              })
              .margin(5)

          }

          Row() {
            Button('swiper height=10%')
              .onClick(() => {
                this.swiperHeight = '10%'
              })
              .margin(5)

            Button('swiper height=5%')
              .onClick(() => {
                this.swiperHeight = '5%'
              })
              .margin(5)

          }

          Row() {
            Button('show next')
              .onClick(() => {
                this.swiperController.showNext()
              })
              .margin(5)

            Button('show previous')
              .onClick(() => {
                this.swiperController.showPrevious()
              })
              .margin(5)
          }

          Row() {
            Button('changeIndex(' + this.changeIndex + ', false)')
              .onClick(() => {
                this.swiperController.changeIndex(this.changeIndex, false)
              })
              .margin(5)

            Button('changeIndex(' + this.changeIndex + ', true)')
              .onClick(() => {
                this.swiperController.changeIndex(this.changeIndex, true)
              })
              .margin(5)
          }

          Row() {
            Button('add index')
              .onClick(() => {
                this.index++
              })
              .margin(5)

            Button('minus index')
              .onClick(() => {
                this.index--
              })
              .margin(5)
          }

          Row() {
            Button('add changeIndex')
              .onClick(() => {
                this.changeIndex++
              })
              .margin(5)

            Button('minus changeIndex')
              .onClick(() => {
                this.changeIndex--
              })
              .margin(5)
          }

          Row() {
            Button('add displayCount')
              .onClick(() => {
                this.displayCount++
              })
              .margin(5)

            Button('minus displayCount')
              .onClick(() => {
                this.displayCount--
              })
              .margin(5)
          }

          Row() {
            Button('add cachedCount')
              .onClick(() => {
                this.cachedCount++
              })
              .margin(5)

            Button('minus cachedCount')
              .onClick(() => {
                this.cachedCount--
              })
              .margin(5)
          }

          Row() {
            Button('change isShown')
              .onClick(() => {
                this.show = !this.show
              })
              .margin(5)

            Button('change swipeByGroup')
              .onClick(() => {
                this.swipeByGroup = !this.swipeByGroup
              })
              .margin(5)
          }


          Row() {
            Button('change loop')
              .onClick(() => {
                this.loop = !this.loop
              })
              .margin(5)

            Button('change clip')
              .onClick(() => {
                this.swiperClip = !this.swiperClip
              })
              .margin(5)
          }

          Button('change prevIgnoreBlank')
            .onClick(() => {
              this.prevIgnoreBlank = !this.prevIgnoreBlank
            })
            .margin(5)

          Button('change nextIgnoreBlank')
            .onClick(() => {
              this.nextIgnoreBlank = !this.nextIgnoreBlank
            })
            .margin(5)

          Button('add foreach child')
            .onClick(() => {
              this.arr.push('5')
              this.arr.push('6')
              this.arr.push('7')
              this.arr.push('8')
              this.arr.push('9')
            })
            .margin(5)

          Row() {
            Button('add prevMargin')
              .onClick(() => {
                this.prevMargin += 10
              })
              .margin(5)

            Button('minus prevMargin')
              .onClick(() => {
                this.prevMargin -= 10
              })
              .margin(5)
          }

          Row() {
            Button('add nextMargin')
              .onClick(() => {
                this.nextMargin += 10
              })
              .margin(5)

            Button('minus nextMargin')
              .onClick(() => {
                this.nextMargin -= 10
              })
              .margin(5)
          }

          Row() {
            Button('add itemSpace')
              .onClick(() => {
                this.itemSpace += 10
              })
              .margin(5)

            Button('minus itemSpace')
              .onClick(() => {
                this.itemSpace -= 10
              })
              .margin(5)
          }

          Row() {
            Button('set LTR')
              .onClick(() => {
                this.dirc = Direction.Ltr
              })
              .margin(5)

            Button('set RTL')
              .onClick(() => {
                this.dirc = Direction.Rtl
              })
              .margin(5)
          }

        }
      }
      .height('60%')

    }
    .width('100%')

  }
}


@Component
struct CachedCountComponent {
  txt: string = ''

  aboutToAppear(): void {
    console.info('aboutToAppear index:' + this.txt)
  }

  aboutToDisappear(): void {
    console.info('aboutToDisappear index:' + this.txt)
  }

  build() {
    Column() {
      Text(this.txt)
        .width('100%')
        .height('100%')
        .textAlign(TextAlign.Center)
        .fontSize(30)
        .backgroundColor(Color.Yellow)
        .borderWidth(1)
    }
    .width('100%')
    .height('100%')
  }
}
