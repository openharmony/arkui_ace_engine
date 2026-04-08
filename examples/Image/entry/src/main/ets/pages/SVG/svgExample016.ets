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

/**
 * SVG Gesture Example - Demonstrates SVG gesture interactions
 * 
 */
@Entry
@Component
struct svgExample016 {
  @State scale: number = 1.0
  @State offsetX: number = 0
  @State offsetY: number = 0
  @State angle: number = 0
  @State pinchCenter: { x: number, y: number } = { x: 0, y: 0 }
  @State gestureInfo: string = 'Try gestures on the SVG'

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Gesture Interaction Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        Text(this.gestureInfo)
          .fontSize(14)
          .fontColor(Color.Gray)

        // Combined gestures
        Text('Pan, Pinch, Rotation Gesture')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Stack({ alignContent: Alignment.Center }) {
          // Background grid
          Grid() {
            ForEach(Array.from({ length: 25 }, (_, i) => i), (index: number) => {
              GridItem() {
                Rectangle()
                  .fill(Color.LightGray)
                  .border({ width: 0.5, color: Color.Gray })
              }
            })
          }
          .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
          .width('100%')
          .height(300)

          // Interactive SVG
          Image($r('app.media.testSvg'))
            .width(150)
            .height(150)
            .scale({ x: this.scale, y: this.scale })
            .rotate({ angle: this.angle })
            .translate({ x: this.offsetX, y: this.offsetY })
            .gesture(
              GestureGroup(GestureMode.Exclusive) {
                // Pinch to zoom gesture
                PinchGesture({ fingers: 2 })
                  .onActionStart(() => {
                    this.gestureInfo = 'Pinch started'
                  })
                  .onActionUpdate((event: GestureEvent) => {
                    if (event.scale) {
                      this.scale = event.scale
                    }
                    this.gestureInfo = 'Scale: ' + this.scale.toFixed(2)
                  })
                  .onActionEnd(() => {
                    this.gestureInfo = 'Pinch ended - Scale: ' + this.scale.toFixed(2)
                  })

                // Pan gesture
                PanGesture({ direction: PanDirection.All })
                  .onActionStart(() => {
                    this.gestureInfo = 'Pan started'
                  })
                  .onActionUpdate((event: GestureEvent) => {
                    if (event.offsetX) {
                      this.offsetX = event.offsetX
                    }
                    if (event.offsetY) {
                      this.offsetY = event.offsetY
                    }
                    this.gestureInfo = 'X: ' + this.offsetX.toFixed(0) + ', Y: ' + this.offsetY.toFixed(0)
                  })
                  .onActionEnd(() => {
                    this.gestureInfo = 'Pan ended'
                  })

                // Rotation gesture
                RotationGesture()
                  .onActionStart(() => {
                    this.gestureInfo = 'Rotation started'
                  })
                  .onActionUpdate((event: GestureEvent) => {
                    if (event.angle) {
                      this.angle = event.angle
                    }
                    this.gestureInfo = 'Angle: ' + this.angle.toFixed(0) + '°'
                  })
                  .onActionEnd(() => {
                    this.gestureInfo = 'Rotation ended - Angle: ' + this.angle.toFixed(0) + '°'
                  })
              }
            )
        }
        .width(300)
        .height(300)
        .border({ width: 2, color: Color.Blue })

        Button('Reset')
          .onClick(() => {
            this.scale = 1.0
            this.offsetX = 0
            this.offsetY = 0
            this.angle = 0
            this.gestureInfo = 'Reset complete'
          })

        Divider()

        // Tap gestures
        Text('Tap Gestures')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          @State tapCount: number = 0
          @State doubleTapCount: number = 0
          @State tripleTapCount: number = 0

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(80)
              .height(80)
              .fillColor(Color.Red)
              .gesture(
                TapGesture({ count: 1 })
                  .onAction(() => {
                    this.tapCount++
                  })
              )
            Text('Single: ' + tapCount).fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.icon'))
              .width(80)
              .height(80)
              .fillColor(Color.Green)
              .gesture(
                TapGesture({ count: 2 })
                  .onAction(() => {
                    this.doubleTapCount++
                  })
              )
            Text('Double: ' + doubleTapCount).fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.star'))
              .width(80)
              .height(80)
              .fillColor(Color.Blue)
              .gesture(
                TapGesture({ count: 3 })
                  .onAction(() => {
                    this.tripleTapCount++
                  })
              )
            Text('Triple: ' + tripleTapCount).fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Long press gesture
        Text('Long Press Gesture')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State longPressProgress: number = 0

        Image($r('app.media.heart'))
          .width(120)
          .height(120)
          .fillColor(Color.Pink)
          .gesture(
            LongPressGesture({ repeat: true, duration: 1000 })
              .onActionStart(() => {
                this.gestureInfo = 'Long press started...'
              })
              .onActionUpdate((event: GestureEvent) => {
                if (event.repeat) {
                  this.longPressProgress = event.repeat
                }
                this.gestureInfo = 'Long press: ' + this.longPressProgress
              })
              .onActionEnd(() => {
                this.gestureInfo = 'Long press completed'
              })
          )

        Text('Long press count: ' + this.longPressProgress)
          .fontSize(14)
          .fontColor(Color.Gray)

        Divider()

        // Swipe gesture
        Text('Swipe Gestures')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State swipeDirection: string = 'None'

        Image($r('app.media.testSvg'))
          .width(150)
          .height(150)
          .gesture(
            SwipeGesture({ direction: SwipeDirection.All })
              .onAction((event: GestureEvent) => {
                if (event swipeDirection === SwipeDirection.Left) {
                  this.swipeDirection = 'Left'
                } else if (event swipeDirection === SwipeDirection.Right) {
                  this.swipeDirection = 'Right'
                } else if (event swipeDirection === SwipeDirection.Up) {
                  this.swipeDirection = 'Up'
                } else if (event swipeDirection === SwipeDirection.Down) {
                  this.swipeDirection = 'Down'
                }
                this.gestureInfo = 'Swiped ' + this.swipeDirection
              })
          )

        Text('Last swipe: ' + this.swipeDirection)
          .fontSize(14)
          .fontColor(Color.Gray)

        Divider()

        // Scroll/EdgeSwipe gesture
        Text('Scroll/EdgeSwipe Gesture')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State edgeSwipeDistance: number = 0

        Image($r('app.media.svg'))
          .width(150)
          .height(150)
          .gesture(
            EdgeSwipeGesture({ edge: EdgeSwipeEdge.Right })
              .onAction((event: GestureEvent) => {
                if (event.offsetX) {
                  this.edgeSwipeDistance = event.offsetX
                }
                this.gestureInfo = 'Edge swipe distance: ' + this.edgeSwipeDistance.toFixed(0)
              })
          )

        Text('Edge swipe: ' + edgeSwipeDistance.toFixed(0) + 'px')
          .fontSize(14)
          .fontColor(Color.Gray)

        Divider()

        // Gesture priority
        Text('Gesture Priority')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State priorityInfo: string = 'Tap or LongPress'

        Image($r('app.media.icon'))
          .width(120)
          .height(120)
          .gesture(
            GestureGroup(GestureMode.Sequence) {
              LongPressGesture()
                .onAction(() => {
                  this.priorityInfo = 'Long press triggered'
                })

              TapGesture()
                .onAction(() => {
                  this.priorityInfo = 'Tap triggered'
                })
            }
          )

        Text(this.priorityInfo)
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ bottom: 20 })
      }
      .width('100%')
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}
