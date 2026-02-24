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
 * Image component animation property examples
 */
@Entry
@Component
struct ImageAnimationExample {
  @State isPlaying: boolean = false
  @State animationDuration: number = 2000
  @State iteration: number = 1

  build() {
    Column({ space: 20 }) {
      Text('Animation 属性示例')
        .fontSize(20)
        .fontColor(Color.Gray)

      // 控制动画播放
      Row({ space: 20 }) {
        Button('播放动画')
          .fontSize(16)
          .onClick(() => {
            this.isPlaying = true
          })
        Button('停止动画')
          .fontSize(16)
          .onClick(() => {
            this.isPlaying = false
          })
      }

      // 动画参数设置
      Column({ space: 15 }) {
        Text('动画时长: ' + this.animationDuration + 'ms')
          .fontSize(16)
        Slider({ value: this.animationDuration, min: 500, max: 5000, step: 100 })
          .onChange((value: number) => {
            this.animationDuration = value
          })
          .width('80%')

        Text('迭代次数: ' + this.iteration)
          .fontSize(16)
        Slider({ value: this.iteration, min: 0, max: 5, step: 1 })
          .onChange((value: number) => {
            this.iteration = value
          })
          .width('80%')
      }

      Divider().strokeWidth(2)

      // 动画展示
      Stack() {
        Image($r('app.media.animated_icon'))
          .width(300)
          .height(300)
          .animation({
            duration: this.animationDuration,
            iterations: this.iteration,
            play: this.isPlaying
          })

        if (this.isPlaying) {
          Text('动画播放中...')
            .fontSize(16)
            .fontColor(Color.Green)
        } else {
          Text('动画已停止')
            .fontSize(16)
            .fontColor(Color.Gray)
        }
      }

      Divider().strokeWidth(2)

      Text('animation 属性用于GIF等动图的播放控制')
        .fontSize(14)
        .fontColor(Color.Blue)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
    .backgroundColor(Color.White)
  }
}
