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
 * either express or implied. See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Example: ImageAnimatorExample004
 * Purpose: Comprehensive test of ImageAnimator component's behavior when dynamically modifying
 *          animation state, playback attributes, and verifying callback logic.
 */

@Entry
@Component
struct ImageAnimatorExample004 {
  // Animation state: Initial, Running, Paused, Stopped
  @State state: AnimationStatus = AnimationStatus.Initial

  // Whether to play the animation in reverse
  @State reverse: boolean = false

  // Number of iterations to loop (-1 means infinite)
  @State iterations: number = 1

  // Indicator for triggered callback status
  @State callBackFlag: string = 'Null'

  // Fill mode: what the animation displays after finishing
  @State fillMode: FillMode = FillMode.Forwards

  build() {
    Column({ space: 10 }) {
      // ImageAnimator component
      ImageAnimator()
        .images([
          { src: $r('app.media.ic_gif') },
          { src: $r('app.media.no2') },
          { src: $r('app.media.no3') },
          { src: $r('app.media.no4') },
          { src: $r('app.media.no5') }
        ])
        .borderRadius(10)
        .duration(5000) // Animation duration in milliseconds
        .state(this.state)
        .reverse(this.reverse)
        .fillMode(this.fillMode)
        .iterations(this.iterations)
        .width(340)
        .height(240)
        .margin({ top: 100 })
        // Callbacks for different animation stages
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

      // Animation control buttons
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
            this.state = AnimationStatus.Paused // Show current frame
          })
          .margin(5)

        Button('Stop')
          .width(100)
          .padding(5)
          .onClick(() => {
            this.state = AnimationStatus.Stopped // Show first frame
          })
          .margin(5)

        Button('Reset')
          .width(100)
          .padding(5)
          .onClick(() => {
            this.state = AnimationStatus.Initial // Reset to initial frame
          })
          .margin(5)
      }

      // Animation setting buttons
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
            this.iterations = -1 // Infinite loop
          })
          .margin(5)
      }

      // Status display
      Text(this.callBackFlag).fontWeight(FontWeight.Bolder)
      Text('Reverse: ' + this.reverse).fontWeight(FontWeight.Bolder)
      Text('FillMode: ' + this.fillMode).fontWeight(FontWeight.Bolder)
      Text('Iterations: ' + this.iterations).fontWeight(FontWeight.Bolder)
    }
    .width('100%')
    .height('100%')
  }
}
