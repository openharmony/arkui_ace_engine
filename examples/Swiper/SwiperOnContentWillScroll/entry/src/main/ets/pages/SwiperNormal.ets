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
struct SwiperNormal {
  private swiperController: SwiperController = new SwiperController()
  @State data: number[] = [0, 1, 2, 3, 4]
  @State idx: number = 0
  @State willScrollCurrentIndex: number = 0
  @State willScrollComingIndex: number = 0
  @State willScrollOffset: number = 0
  @State changeIndex: number = 0
  @State currentIndex: number = 0
  @State comingIndex: number = 0
  @State swiperWidth: Length = 300
  @State swiperHeight: Length = '30%'
  @State preMargin: number = 0
  @State nextMargin: number = 0
  @State itemSpace: number = 0
  @State swiperClip: boolean = true
  @State cachedCount: number = 1
  @State displayCount: number = 1
  @State loop: boolean = true
  @State swipeByGroup: boolean = false
  @State prevIgnoreBlank: boolean = false
  @State nextIgnoreBlank: boolean = false
  @State direct: Direction = Direction.Ltr

  build() {
    Column({ space: 5 }) {
      Swiper(this.swiperController) {
        ForEach(this.data, (item: string) => {
          MyComponent({ txt: item.toString() })
        }, (item: string) => item)
      }
      .borderWidth(1)
      .backgroundColor(Color.Pink)
      .index(this.idx)
      .loop(this.loop)
      .width(this.swiperWidth)
      .height(this.swiperHeight)
      .prevMargin(this.preMargin, this.prevIgnoreBlank)
      .nextMargin(this.nextMargin, this.nextIgnoreBlank)
      .itemSpace(this.itemSpace)
      .displayCount(this.displayCount, this.swipeByGroup)
      .direction(this.direct)
      .displayArrow({
        // 设置导航点箭头样式
        showBackground: true,
        isSidebarMiddle: true,
        backgroundSize: 24,
        backgroundColor: Color.White,
        arrowSize: 18,
        arrowColor: Color.Blue
      }, false)
      .onContentWillScroll((result: SwiperContentWillScrollResult) => {
        this.willScrollCurrentIndex = result.currentIndex
        this.willScrollComingIndex = result.comingIndex
        this.willScrollOffset = result.offset

        if (result.currentIndex == this.currentIndex && result.comingIndex == this.comingIndex) {
          return false;
        }

        return true
      })

      Scroll() {
        Column({ space: 12 }) {
          Text('will scroll currentIndex: ' + this.willScrollCurrentIndex + ', comingIndex: ' +
          this.willScrollComingIndex + ', offset: ' + this.willScrollOffset)
            .margin(5)

          Button('change loop')
            .onClick(() => {
              this.loop = !this.loop
            })
            .margin(5)
            .fontSize(15)

          Button('total count = 10')
            .onClick(() => {
              this.data = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
            })
            .margin(5)
            .fontSize(15)

          Button('total count = 5')
            .onClick(() => {
              this.data = [0, 1, 2, 3, 4]
            })
            .margin(5)
            .fontSize(15)

          Text('width: ' + this.swiperWidth.toString())
            .margin(5)
          Row() {
            Button('width = 300')
              .onClick(() => {
                this.swiperWidth = 300
              })
              .margin(5)
              .fontSize(15)

            Button('width = 90%')
              .onClick(() => {
                this.swiperWidth = '90%'
              })
              .margin(5)
              .fontSize(15)
          }

          Text('index: ' + this.idx)
            .margin(5)
          Row() {
            Button('index=1')
              .onClick(() => {
                this.idx = 1
              })
              .margin(5)
              .fontSize(15)

            Button('index++')
              .onClick(() => {
                this.idx++
              })
              .margin(5)
              .fontSize(15)

            Button('index--')
              .onClick(() => {
                this.idx--
              })
              .margin(5)
              .fontSize(15)
          }

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

          Text('itemSpace: ' + this.itemSpace + 'prevMargin: ' + this.preMargin + ', nextMargin: ' + this.nextMargin +
            ', prevIgnoreBlank: ' +
            (this.prevIgnoreBlank ? 'true' : 'false') + ', nextIgnoreBlank: ' +
            (this.nextIgnoreBlank ? 'true' : 'false'))
          Row() {
            Button('change prevIgnoreBlank')
              .onClick(() => {
                this.prevIgnoreBlank = !this.prevIgnoreBlank
              })
              .margin(5)
              .fontSize(15)

            Button('change nextIgnoreBlank')
              .onClick(() => {
                this.nextIgnoreBlank = !this.nextIgnoreBlank
              })
              .margin(5)
              .fontSize(15)

          }

          Row() {
            Button('prevMargin++')
              .onClick(() => {
                this.preMargin += 10
              })
              .margin(5)
              .fontSize(12)

            Button('nextMargin++')
              .onClick(() => {
                this.nextMargin += 10
              })
              .margin(5)
              .fontSize(12)

            Button('itemSpace++')
              .onClick(() => {
                this.itemSpace += 10
              })
              .margin(5)
              .fontSize(12)
          }

          Row() {
            Button('prevMargin--')
              .onClick(() => {
                this.preMargin -= 10
              })
              .margin(5)
              .fontSize(12)

            Button('nextMargin--')
              .onClick(() => {
                this.nextMargin -= 10
              })
              .margin(5)
              .fontSize(12)

            Button('itemSpace--')
              .onClick(() => {
                this.itemSpace -= 10
              })
              .margin(5)
              .fontSize(12)
          }


          Text('change index: ' + this.changeIndex)
            .margin(5)
          Row() {

            Button('changeIndex++')
              .onClick(() => {
                this.changeIndex++
              })
              .margin(5)
              .fontSize(15)

            Button('changeIndex--')
              .onClick(() => {
                this.changeIndex--
              })
              .margin(5)
              .fontSize(15)
          }


          Row() {
            Button('showNext')
              .onClick(() => {
                this.swiperController.showNext()
              })
              .margin(5)
              .fontSize(15)
            Button('showPrevious')
              .onClick(() => {
                this.swiperController.showPrevious()
              })
              .fontSize(15)
              .margin(5)
          }.margin(5)

          Row() {
            Button('changeIndex(' + this.changeIndex + ', false)')
              .onClick(() => {
                this.swiperController.changeIndex(this.changeIndex, false)
              })
              .fontSize(15)
              .margin(5)

            Button('changeIndex(' + this.changeIndex + ', true)')
              .onClick(() => {
                this.swiperController.changeIndex(this.changeIndex, true)
              })
              .fontSize(15)
              .margin(5)
          }

          Text('displayCount:' + this.displayCount + ', swipeByGroup:' + this.swipeByGroup)
          Button('change swipeByGroup')
            .onClick(() => {
              this.swipeByGroup = !this.swipeByGroup
            })
            .margin(5)
            .fontSize(15)
          Row() {
            Button('displayCount++')
              .onClick(() => {
                this.displayCount++
              })
              .margin(5)
              .fontSize(15)

            Button('displayCount--')
              .onClick(() => {
                this.displayCount--
              })
              .margin(5)
              .fontSize(15)
          }

          Row() {
            Button('RTL')
              .onClick(() => {
                this.direct = Direction.Rtl
              })
              .margin(5)
              .fontSize(15)

            Button('LTR')
              .onClick(() => {
                this.direct = Direction.Ltr
              })
              .margin(5)
              .fontSize(15)
          }

        }.margin(5)
      }
      .height('60%')
    }
    .width('100%')
    .margin({ top: 5 })
  }
}

@Component
struct MyComponent {
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
        .fontSize(15)
        .backgroundColor(0xAFEEEE)
        .borderWidth(1)
    }
    .width(100)
    .height(200)
  }
}
