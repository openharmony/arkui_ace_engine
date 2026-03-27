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
 * SVG Animation Advanced Example - Demonstrates advanced SVG animation effects
 * 
 */
@Entry
@Component
struct svgExample015 {
  @State rotationAngle: number = 0
  @State scaleValue: number = 1.0
  @State translateX: number = 0
  @State translateY: number = 0
  @State opacityValue: number = 1.0
  @State skewX: number = 0
  @State isPlaying: boolean = false
  @State animationDuration: number = 2000

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Advanced Animation Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Combined transform animation
        Text('Combined Transform Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.testSvg'))
          .width(100)
          .height(100)
          .rotate({ angle: this.rotationAngle })
          .scale({ x: this.scaleValue, y: this.scaleValue })
          .translate({ x: this.translateX, y: this.translateY })
          .opacity(this.opacityValue)
          .border({ width: 1, color: Color.Gray })
          .animation({
            duration: this.animationDuration,
            curve: Curve.EaseInOut,
            iterations: -1,
            playMode: PlayMode.Alternate
          })

        Row({ space: 10 }) {
          Button('Play')
            .onClick(() => {
              this.isPlaying = true
              this.rotationAngle = 360
              this.scaleValue = 1.5
              this.translateX = 50
              this.opacityValue = 0.5
            })

          Button('Stop')
            .onClick(() => {
              this.isPlaying = false
              this.rotationAngle = 0
              this.scaleValue = 1.0
              this.translateX = 0
              this.opacityValue = 1.0
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Divider()

        // Spring animation
        Text('Spring Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State springScale: number = 1.0

        Image($r('app.media.svg'))
          .width(100)
          .height(100)
          .scale({ x: this.springScale, y: this.springScale })
          .border({ width: 1, color: Color.Gray })
          .animation({
            duration: 500,
            curve: Curve.SpringMotion,
          })

        Button('Spring Effect')
          .onClick(() => {
            this.springScale = this.springScale === 1.0 ? 1.8 : 1.0
          })

        Divider()

        // Sequential animation
        Text('Sequential Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          @State seqAngle1: number = 0
          @State seqAngle2: number = 0
          @State seqAngle3: number = 0

          Image($r('app.media.icon'))
            .width(60)
            .height(60)
            .rotate({ angle: seqAngle1 })
            .animation({
              duration: 1000,
              delay: 0,
              curve: Curve.EaseInOut,
              iterations: -1
            })

          Image($r('app.media.star'))
            .width(60)
            .height(60)
            .rotate({ angle: seqAngle2 })
            .animation({
              duration: 1000,
              delay: 300,
              curve: Curve.EaseInOut,
              iterations: -1
            })

          Image($r('app.media.heart'))
            .width(60)
            .height(60)
            .rotate({ angle: seqAngle3 })
            .animation({
              duration: 1000,
              delay: 600,
              curve: Curve.EaseInOut,
              iterations: -1
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Button('Start Sequential')
          .onClick(() => {
            seqAngle1 = 360
            seqAngle2 = 360
            seqAngle3 = 360
          })

        Divider()

        // Pulse animation
        Text('Pulse Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State pulseScale: number = 1.0
        @State pulseOpacity: number = 1.0

        Stack({ alignContent: Alignment.Center }) {
          Image($r('app.media.testSvg'))
            .width(120)
            .height(120)
            .scale({ x: this.pulseScale, y: this.pulseScale })
            .opacity(this.pulseOpacity)
            .fillColor(Color.Blue)
            .animation({
              duration: 800,
              curve: Curve.EaseInOut,
              iterations: -1,
              playMode: PlayMode.Alternate
            })
        }
        .width(150)
        .height(150)

        Button('Toggle Pulse')
          .onClick(() => {
            this.pulseScale = this.pulseScale === 1.0 ? 1.3 : 1.0
            this.pulseOpacity = this.pulseOpacity === 1.0 ? 0.6 : 1.0
          })

        Divider()

        // Path animation (simulation)
        Text('Path Animation Simulation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State pathProgress: number = 0

        Image($r('app.media.svg'))
          .width(80)
          .height(80)
          .translate({
            x: Math.sin(this.pathProgress * 2 * Math.PI) * 80,
            y: Math.cos(this.pathProgress * 2 * Math.PI) * 80
          })
          .animation({
            duration: 3000,
            curve: Curve.Linear,
            iterations: -1
          })

        Button('Start Path Animation')
          .onClick(() => {
            this.pathProgress = this.pathProgress + 1
          })

        Divider()

        // Color animation
        Text('Color Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State colorIndex: number = 0
        private colors: Color[] = [
          Color.Red, Color.Orange, Color.Yellow, Color.Green,
          Color.Cyan, Color.Blue, Color.Purple, Color.Pink
        ]

        Image($r('app.media.testSvg'))
          .width(120)
          .height(120)
          .fillColor(this.colors[this.colorIndex])
          .animation({
            duration: 500,
            curve: Curve.EaseInOut
          })
          .border({ width: 1, color: Color.Gray })

        Button('Animate Color')
          .onClick(() => {
            this.colorIndex = (this.colorIndex + 1) % this.colors.length
          })

        Divider()

        // Flip animation
        Text('Flip Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State flipScaleX: number = 1.0
        @State flipScaleY: number = 1.0

        Image($r('app.media.icon'))
          .width(120)
          .height(120)
          .scale({ x: this.flipScaleX, y: 1.0 })
          .border({ width: 1, color: Color.Gray })
          .animation({
            duration: 600,
            curve: Curve.EaseInOut
          })

        Row({ space: 10 }) {
          Button('Flip H')
            .onClick(() => {
              this.flipScaleX = this.flipScaleX * -1
            })

          Button('Flip V')
            .onClick(() => {
              this.flipScaleY = this.flipScaleY * -1
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Divider()

        // Custom easing functions
        Text('Custom Easing Functions')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          @State easeAngle1: number = 0
          @State easeAngle2: number = 0
          @State easeAngle3: number = 0

          Column({ space: 5 }) {
            Image($r('app.media.star'))
              .width(60)
              .height(60)
              .rotate({ angle: easeAngle1 })
              .animation({
                duration: 1500,
                curve: Curve.EaseIn,
                iterations: -1,
                playMode: PlayMode.Alternate
              })
            Text('EaseIn').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.heart'))
              .width(60)
              .height(60)
              .rotate({ angle: easeAngle2 })
              .animation({
                duration: 1500,
                curve: Curve.EaseOut,
                iterations: -1,
                playMode: PlayMode.Alternate
              })
            Text('EaseOut').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(60)
              .height(60)
              .rotate({ angle: easeAngle3 })
              .animation({
                duration: 1500,
                curve: Curve.EaseInOut,
                iterations: -1,
                playMode: PlayMode.Alternate
              })
            Text('EaseInOut').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)
        .margin({ bottom: 20 })

        Button('Start All')
          .onClick(() => {
            easeAngle1 = 360
            easeAngle2 = 360
            easeAngle3 = 360
          })
      }
      .width('100%')
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}
