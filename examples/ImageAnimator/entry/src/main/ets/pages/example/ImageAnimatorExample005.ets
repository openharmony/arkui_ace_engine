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
 * Demo: ImageAnimatorExample005
 * Description: This demo comprehensively tests the behavior of the ImageAnimator component
 * when dynamically modifying state parameters, playback attributes, and verifying callbacks.
 */

@Entry
@Component
struct ImageAnimatorExample005 {
  // Animation state: Initial, Running, Paused, Stopped
  @State state: AnimationStatus = AnimationStatus.Initial

  // Whether to play the animation in reverse
  @State reverse: boolean = true

  // Number of iterations to loop (-1 = infinite)
  @State iterations: number = 1

  // Current callback status text
  @State callBackFlag: string = 'Null'

  // Fill mode after animation ends
  @State fillMode: FillMode = FillMode.None

  build() {
    Column({ space: 10 }) {
      // Main ImageAnimator with callbacks
      ImageAnimator()
        .images([
          { src: $r('app.media.no1') },
          { src: $r('app.media.no2') },
          { src: $r('app.media.no3') },
          { src: $r('app.media.no4') },
          { src: $r('app.media.no5') }
        ])
        .borderRadius(10)
        .duration(5000)
        .state(this.state)
        .reverse(this.reverse)
        .fillMode(this.fillMode)
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

      // Animation control buttons row
      Row() {
        Button('Start')
          .width(100)
          .padding(5)
          .onClick(() => {
            this.state = AnimationStatus.Running
          })
          .margin(5)

        Button('Pause')
          .width(100)
          .padding(5)
          .onClick(() => {
            this.state = AnimationStatus.Paused
          })
          .margin(5)

        Button('Stop')
          .width(100)
          .padding(5)
          .onClick(() => {
            this.state = AnimationStatus.Stopped
          })
          .margin(5)

        Button('Reset')
          .width(100)
          .padding(5)
          .onClick(() => {
            this.state = AnimationStatus.Initial
          })
          .margin(5)
      }

      // Playback mode buttons row
      Row() {
        Button('Reverse: ' + this.reverse)
          .width(100)
          .padding(5)
          .onClick(() => {
            this.reverse = !this.reverse
          })
          .margin(5)

        Button('Once')
          .width(100)
          .padding(5)
          .onClick(() => {
            this.iterations = 1
          })
          .margin(5)

        Button('Infinite')
          .width(100)
          .padding(5)
          .onClick(() => {
            this.iterations = -1
          })
          .margin(5)
      }

      // Animation status display
      Text(this.callBackFlag).fontWeight(FontWeight.Bolder)
      Text('Reverse: ' + this.reverse).fontWeight(FontWeight.Bolder)
      Text('FillMode: ' + this.fillMode).fontWeight(FontWeight.Bolder)
      Text('Iterations: ' + this.iterations).fontWeight(FontWeight.Bolder)
    }
    .width('100%')
    .height('100%')
  }
}
