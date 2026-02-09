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

/**
 * SVG Event Handling Example - Demonstrates SVG event handling and interaction
 * 
 */
@Entry
@Component
struct svgExample009 {
  @State clickCount: number = 0
  @State touchText: string = 'Touch the SVG image'
  @State isPressed: boolean = false
  @State hoverText: string = 'Hover over the images'
  @State lastSwipe: string = ''

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Event Handling Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Click event
        Text('Click Event')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text('Click count: ' + this.clickCount)
          .fontSize(14)
          .fontColor(Color.Gray)

        Image($r('app.media.testSvg'))
          .width(120)
          .height(120)
          .fillColor(this.clickCount % 2 === 0 ? Color.Blue : Color.Red)
          .border({ width: 2, color: this.isPressed ? Color.Green : Color.Gray })
          .onClick(() => {
            this.clickCount++
          })

        Divider()

        // Touch event
        Text('Touch Event')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text(this.touchText)
          .fontSize(14)
          .fontColor(Color.Gray)

        Image($r('app.media.svg'))
          .width(120)
          .height(120)
          .border({ width: 1, color: Color.Gray })
          .onTouch((event: TouchEvent) => {
            if (event.type === TouchType.Down) {
              this.touchText = 'Touch Down'
            } else if (event.type === TouchType.Up) {
              this.touchText = 'Touch Up'
            } else if (event.type === TouchType.Move) {
              this.touchText = 'Touch Move - X: ' + event.touches[0].x.toFixed(0) + ', Y: ' + event.touches[0].y.toFixed(0)
            }
          })

        Divider()

        // Pressed state
        Text('State Style')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.icon'))
          .width(120)
          .height(120)
          .fillColor(this.isPressed ? Color.Green : Color.Gray)
          .border({ width: 2, color: this.isPressed ? Color.Green : Color.Gray })
          .stateStyles({
            normal: {
              .opacity(1.0)
              .scale({ x: 1.0, y: 1.0 })
            },
            pressed: {
              .opacity(0.8)
              .scale({ x: 0.95, y: 0.95 })
            }
          })
          .onClick(() => {
            this.isPressed = !this.isPressed
          })

        Divider()

        // Hover effect
        Text('Hover Effect')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text(this.hoverText)
          .fontSize(14)
          .fontColor(Color.Gray)

        Row({ space: 15 }) {
          Image($r('app.media.star'))
            .width(100)
            .height(100)
            .border({ width: 2, color: Color.Gray })
            .onHover((isHover: boolean) => {
              this.hoverText = isHover ? 'Hovering over star' : 'Hover over the images'
            })
            .animation({
              duration: 200,
              curve: Curve.EaseInOut
            })

          Image($r('app.media.heart'))
            .width(100)
            .height(100)
            .border({ width: 2, color: Color.Gray })
            .onHover((isHover: boolean) => {
              this.hoverText = isHover ? 'Hovering over heart' : 'Hover over the images'
            })
            .animation({
              duration: 200,
              curve: Curve.EaseInOut
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Divider()

        // Swipe gesture
        Text('Swipe Gesture')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text(this.lastSwipe)
          .fontSize(14)
          .fontColor(Color.Gray)

        Image($r('app.media.testSvg'))
          .width(120)
          .height(120)
          .border({ width: 1, color: Color.Gray })
          .gesture(
            SwipeGesture({ direction: SwipeDirection.All })
              .onAction((event: GestureEvent) => {
                if (event swipeDirection === SwipeDirection.Left) {
                  this.lastSwipe = 'Swiped Left'
                } else if (event swipeDirection === SwipeDirection.Right) {
                  this.lastSwipe = 'Swiped Right'
                } else if (event swipeDirection === SwipeDirection.Up) {
                  this.lastSwipe = 'Swiped Up'
                } else if (event swipeDirection === SwipeDirection.Down) {
                  this.lastSwipe = 'Swiped Down'
                }
              })
          )

        Divider()

        // Long press event
        Text('Long Press Event')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State longPressText: string = 'Long press the image'

        Text(this.longPressText)
          .fontSize(14)
          .fontColor(Color.Gray)

        Image($r('app.media.svg'))
          .width(120)
          .height(120)
          .border({ width: 1, color: Color.Gray })
          .gesture(
            LongPressGesture({ repeat: false })
              .onAction(() => {
                this.longPressText = 'Long pressed at ' + new Date().toLocaleTimeString()
              })
          )

        Divider()

        // Double tap event
        Text('Double Tap Event')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State doubleTapCount: number = 0
        @State doubleTapText: string = 'Double tap the image'

        Text(this.doubleTapText)
          .fontSize(14)
          .fontColor(Color.Gray)

        Image($r('app.media.icon'))
          .width(120)
          .height(120)
          .border({ width: 1, color: Color.Gray })
          .gesture(
            TapGesture({ count: 2 })
              .onAction(() => {
                this.doubleTapCount++
                this.doubleTapText = 'Double tapped ' + this.doubleTapCount + ' times'
              })
          )
          .margin({ bottom: 20 })
      }
      .width('100%')
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}
