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
 * Demo: ImageAnimatorExample007
 * Description:
 *   This demo tests ImageAnimator's behavior when the `images` list is present,
 *   while dynamically changing its state (start/pause/stop),
 *   reverse mode, loop count, fill mode, and duration.
 *   It verifies event callbacks and responsiveness to property updates.
 */

@Entry
@Component
struct ImageAnimatorExample007 {
  // Animation state: Initial, Running, Paused, Stopped
  @State state: AnimationStatus = AnimationStatus.Initial

  // Whether to play in reverse
  @State reverse: boolean = false

  // Loop count for animation
  @State iterations: number = 1

  // Animation callback flag
  @State callBackFlag: string = 'Null'

  // Fill mode: None, Forwards, Backwards, Both
  @State fillMode: FillMode = FillMode.None

  // Animation duration in milliseconds
  @State duration: number = 5000

  build() {
    Column({ space: 10 }) {
      // ImageAnimator component
      ImageAnimator()
        .images([
          { src: $r('app.media.no1') },
          { src: $r('app.media.no2') },
          { src: $r('app.media.no3') },
          { src: $r('app.media.no4') },
          { src: $r('app.media.no5') }
        ])
        .borderRadius(10)
        .duration(this.duration)
        .state(this.state)
        .reverse(this.reverse)
        .fillMode(this.fillMode)
        .iterations(this.iterations)
        .width(340)
        .height(240)
        .margin({ top: 100 })

        // Event callbacks
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

      // Animation state control
      Row() {
        Button('Start')
          .width(100).padding(5).onClick(() => {
            this.state = AnimationStatus.Running
          }).margin(5)

        Button('Pause')
          .width(100).padding(5).onClick(() => {
            this.state = AnimationStatus.Paused
          }).margin(5)

        Button('Stop')
          .width(100).padding(5).onClick(() => {
            this.state = AnimationStatus.Stopped
          }).margin(5)

        Button('Initial')
          .width(100).padding(5).onClick(() => {
            this.state = AnimationStatus.Initial
          }).margin(5)
      }

      // Playback attribute control
      Row() {
        Button('Reverse')
          .width(80).padding(5).onClick(() => {
            this.reverse = !this.reverse
          }).margin(5)

        Button('1')
          .width(40).padding(5).onClick(() => {
            this.iterations = 1
          }).margin(5)

        Button('-1')
          .width(40).padding(5).onClick(() => {
            this.iterations -= 1
          }).margin(5)

        Button('+1')
          .width(40).padding(5).onClick(() => {
            this.iterations += 1
          }).margin(5)
      }

      // FillMode selection
      Row() {
        Button('None')
          .width(50).padding(5).onClick(() => {
            this.fillMode = FillMode.None
          }).margin(5)

        Button('Forwards')
          .width(100).padding(5).onClick(() => {
            this.fillMode = FillMode.Forwards
          }).margin(5)

        Button('Backwards')
          .width(100).padding(5).onClick(() => {
            this.fillMode = FillMode.Backwards
          }).margin(5)

        Button('Both')
          .width(50).padding(5).onClick(() => {
            this.fillMode = FillMode.Both
          }).margin(5)
      }

      // Duration control
      Row() {
        Button('Dur: 0')
          .width(100).padding(5).onClick(() => {
            this.duration = 0
          }).margin(5)

        Button('Dur: 5000')
          .width(100).padding(5).onClick(() => {
            this.duration = 5000
          }).margin(5)

        Button('Dur: 2500')
          .width(100).padding(5).onClick(() => {
            this.duration = 2500
          }).margin(5)
      }

      // Display current animation state
      Text(this.callBackFlag).fontWeight(FontWeight.Bolder)
      Text('Reverse: ' + this.reverse).fontWeight(FontWeight.Bolder)
      Text('FillMode: ' + this.fillMode).fontWeight(FontWeight.Bolder)
      Text('Duration: ' + this.duration).fontWeight(FontWeight.Bolder)
      Text('Iterations: ' + this.iterations).fontWeight(FontWeight.Bolder)
    }
    .width('100%')
    .height('100%')
  }
}
