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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Demo: ImageAnimatorExample006
 * Description:
 *   This demo tests the integration of ImageAnimator in a scrollable page,
 *   verifying its behavior when dynamically modifying state (play, pause, reverse),
 *   auto-monitoring invisible areas, handling long list rendering,
 *   and ensuring correct event callbacks during scroll interactions.
 */

@Entry
@Component
struct ImageAnimatorExample006 {
  // Scroll controller
  scroller: Scroller = new Scroller()

  // Animation state: Running, Paused, Stopped, Initial
  @State state: AnimationStatus = AnimationStatus.Running

  // Whether to play in reverse
  @State reverse: boolean = false

  // Loop count: -1 = infinite
  @State iterations: number = 100

  // Whether to auto-monitor visibility
  @State autoMonitorInvisibleArea: boolean = false

  // Current callback message
  @State callBackFlag: string = 'Null'

  // List data for scroll test
  private arr: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      // Scrollable area
      Scroll(this.scroller) {
        Column() {
          // ImageAnimator component with scroll visibility support
          ImageAnimator()
            .images([
              { src: $r('app.media.no0') },
              { src: $r('app.media.no1') },
              { src: $r('app.media.no2') },
              { src: $r('app.media.no3') },
              { src: $r('app.media.no4') },
              { src: $r('app.media.no5') },
              { src: $r('app.media.no6') }
            ])
            .borderRadius(10)
            .monitorInvisibleArea(this.autoMonitorInvisibleArea)
            .clip(true)
            .duration(4000)
            .state(this.state)
            .reverse(this.reverse)
            .fillMode(FillMode.Forwards)
            .iterations(this.iterations)
            .width(340)
            .height(240)
            .margin({ top: 100 })
            .onStart(() => {
              this.callBackFlag = 'ImageAnimator Start'
              console.info('ImageAnimator Start')
            })
            .onPause(() => {
              this.callBackFlag = 'ImageAnimator Pause'
              console.info('ImageAnimator Pause')
            })
            .onRepeat(() => {
              this.callBackFlag = 'ImageAnimator Repeat'
              console.info('ImageAnimator Repeat')
            })
            .onCancel(() => {
              this.callBackFlag = 'ImageAnimator Cancel'
              console.info('ImageAnimator Cancel')
            })
            .onFinish(() => {
              this.callBackFlag = 'ImageAnimator Finish'
              console.info('ImageAnimator Finish')
            })

          // Render list items
          ForEach(this.arr, (item: number) => {
            Text(item.toString())
              .width('90%')
              .height(150)
              .backgroundColor(0xFFFFFF)
              .borderRadius(15)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .margin({ top: 10 })
          }, (item: number) => item.toString())
        }
        .width('100%')
      }
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(BarState.On)
      .scrollBarColor(Color.Gray)
      .scrollBarWidth(10)
      .friction(0.6)
      .edgeEffect(EdgeEffect.None)
      .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        console.info(`Scroll offset: x=${xOffset}, y=${yOffset}`)
      })
      .onScrollEdge((side: Edge) => {
        console.info('Scroll to the edge')
      })
      .onScrollStop(() => {
        console.info('Scroll stopped')
      })

      // Animation control buttons
      Button('Start')
        .width(100)
        .padding(5)
        .onClick(() => {
          this.state = AnimationStatus.Running
        })
        .margin({ top: 60, left: 20 })

      Button('Pause')
        .width(100)
        .padding(5)
        .onClick(() => {
          this.state = AnimationStatus.Paused
        })
        .margin({ top: 110, left: 20 })

      Button('Stop')
        .width(100)
        .padding(5)
        .onClick(() => {
          this.state = AnimationStatus.Stopped
        })
        .margin({ top: 160, left: 20 })

      Button('Reset')
        .width(100)
        .padding(5)
        .onClick(() => {
          this.state = AnimationStatus.Initial
        })
        .margin({ top: 210, left: 20 })

      Button('Reverse')
        .width(100)
        .padding(5)
        .onClick(() => {
          this.reverse = !this.reverse
        })
        .margin({ top: 260, left: 20 })

      Button('Once')
        .width(100)
        .padding(5)
        .onClick(() => {
          this.iterations = 1
        })
        .margin({ top: 310, left: 20 })

      Button('Infinite')
        .width(100)
        .padding(5)
        .onClick(() => {
          this.iterations = -1
        })
        .margin({ top: 360, left: 20 })

      Button(`Monitor Invisible: ${this.autoMonitorInvisibleArea}`)
        .width(200)
        .padding(5)
        .onClick(() => {
          this.autoMonitorInvisibleArea = !this.autoMonitorInvisibleArea
        })
        .margin({ top: 410, left: 20 })

      // Callback status display
      Text(this.callBackFlag)
        .width(200)
        .padding(5)
        .margin({ top: 460, left: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
  }
}
