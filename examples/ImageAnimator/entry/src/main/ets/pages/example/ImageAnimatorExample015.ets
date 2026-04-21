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
 * ImageAnimatorExample015 - 自定义帧时长动画示例
 * 
 * 功能说明：
 * 1. ImageFrameInfo 的 duration 属性 - 每一帧图片的播放时长，单位毫秒
 * 2. 不支持负数，设置为负数将导致图片在当前帧长时间停留，影响正常播放
 * 3. 当 Images 中任意一帧图片设置了单独的 duration 后，duration 属性设置无效
 * 4. 支持为每一帧单独设置不同的播放时长
 */

@Entry
@Component
struct ImageAnimatorExample015 {
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State reverse: boolean = false;
  @State fillMode: FillMode = FillMode.Forwards;
  @State iterationCount: number = 1;
  @State currentFrame: number = 0;
  @State totalFrames: number = 4;
  @State currentStatus: string = 'Initial';

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('自定义帧时长动画示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildUniformDurationDemo()
        this.buildCustomDurationDemo()
        this.buildVariableDurationDemo()
        this.buildControlPanel()
        this.buildBestPractices()
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildDescription() {
    Column({ space: 10 }) {
      Text('duration 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置每一帧图片的播放时长，单位毫秒。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 不支持负数，设置为负数将导致图片在当前帧长时间停留')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 当 Images 中任意一帧图片设置了单独的 duration 后，duration 属性设置无效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 支持为每一帧单独设置不同的播放时长')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 帧时长优先级高于全局 duration 属性')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildUniformDurationDemo() {
    Column({ space: 15 }) {
      Text('统一时长模式')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('使用全局 duration 属性，所有帧使用相同时长')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('动画组件')
          .fontSize(14)
          .fontColor(0x333333)

        ImageAnimator()
          .images([
            { src: $r('app.media.flower') },
            { src: $r('app.media.ic_jpg') },
            { src: $r('app.media.mix_png') },
            { src: $r('app.media.ic_bmp') }
          ])
          .duration(2000)
          .state(this.animationState)
          .reverse(this.reverse)
          .fill fillMode)
          .iterations(this.iterationCount)
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .onStart(() => {
            this.currentStatus = 'Running';
          })
          .onPause(() => {
            this.currentStatus = 'Paused';
          })
          .onRepeat(() => {
            this.currentStatus = 'Repeat';
          })
          .onFinish(() => {
            this.currentStatus = 'Finished';
          })

        Text('每帧时长：2000ms (全局设置)')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildCustomDurationDemo() {
    Column({ space: 15 }) {
      Text('自定义帧时长模式')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('为每一帧单独设置不同的播放时长')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('动画组件')
          .fontSize(14)
          .fontColor(0x333333)

        ImageAnimator()
          .images([
            { 
              src: $r('app.media.flower'),
              duration: 500
            },
            { 
              src: $r('app.media.ic_jpg'),
              duration: 1000
            },
            { 
              src: $r('app.media.mix_png'),
              duration: 1500
            },
            { 
              src: $r('app.media.ic_bmp'),
              duration: 800
            }
          ])
          .state(this.animationState)
          .reverse(this.reverse)
          .fillMode(this.fillMode)
          .iterations(this.iterationCount)
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .onStart(() => {
            this.currentStatus = 'Running';
          })
          .onPause(() => {
            this.currentStatus = 'Paused';
          })
          .onRepeat(() => {
            this.currentStatus = 'Repeat';
          })
          .onFinish(() => {
            this.currentStatus = 'Finished';
          })

        Text('帧1: 500ms | 帧2: 1000ms | 帧3: 1500ms | 帧4: 800ms')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildVariableDurationDemo() {
    Column({ space: 15 }) {
      Text('可变时长演示')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('快速帧动画')
            .fontSize(14)
            .fontColor(0x333333)

          ImageAnimator()
            .images([
              { src: $r('app.media.flower'), duration: 200 },
              { src: $r('app.media.ic_jpg'), duration: 200 },
              { src: $r('app.media.mix_png'), duration: 200 },
              { src: $r('app.media.ic_bmp'), duration: 200 }
            ])
            .state(this.animationState)
            .iterations(this.iterationCount)
            .width(200)
            .height(150)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)

          Text('每帧 200ms')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('慢速帧动画')
            .fontSize(14)
            .fontColor(0x333333)

          ImageAnimator()
            .images([
              { src: $r('app.media.flower'), duration: 2000 },
              { src: $r('app.media.ic_jpg'), duration: 2000 },
              { src: $r('app.media.mix_png'), duration: 2000 },
              { src: $r('app.media.ic_bmp'), duration: 2000 }
            ])
            .state(this.animationState)
            .iterations(this.iterationCount)
            .width(200)
            .height(150)
            .border({ width: 2, color: Color.Orange })
            .borderRadius(8)

          Text('每帧 2000ms')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('渐变时长动画')
            .fontSize(14)
            .fontColor(0x333333)

          ImageAnimator()
            .images([
              { src: $r('app.media.flower'), duration: 300 },
              { src: $r('app.media.ic_jpg'), duration: 600 },
              { src: $r('app.media.mix_png'), duration: 900 },
              { src: $r('app.media.ic_bmp'), duration: 1200 }
            ])
            .state(this.animationState)
            .iterations(this.iterationCount)
            .width(200)
            .height(150)
            .border({ width: 2, color: Color.Purple })
            .borderRadius(8)

          Text('300ms → 600ms → 900ms → 1200ms')
            .fontSize(12)
            .fontColor(0x666666)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildControlPanel() {
    Column({ space: 15 }) {
      Text('控制面板')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 10 }) {
        Text('动画状态：' + this.currentStatus)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceBetween)

      Row({ space: 10 }) {
        Button('播放')
          .width(100)
          .onClick(() => {
            this.animationState = AnimationStatus.Running;
          })

        Button('暂停')
          .width(100)
          .onClick(() => {
            this.animationState = AnimationStatus.Paused;
          })

        Button('停止')
          .width(100)
          .onClick(() => {
            this.animationState = AnimationStatus.Stopped;
          })

        Button('重置')
          .width(100)
          .onClick(() => {
            this.animationState = AnimationStatus.Initial;
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Button('正向播放')
          .width(100)
          .onClick(() => {
            this.reverse = false;
          })

        Button('反向播放')
          .width(100)
          .onClick(() => {
            this.reverse = true;
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Button('播放一次')
          .width(100)
          .onClick(() => {
            this.iterationCount = 1;
          })

        Button('播放两次')
          .width(100)
          .onClick(() => {
            this.iterationCount = 2;
          })

        Button('无限循环')
          .width(100)
          .onClick(() => {
            this.iterationCount = -1;
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)

      Row({ space: 10 }) {
        Button('保持最后一帧')
          .width(100)
          .onClick(() => {
            this.fillMode = FillMode.Forwards;
          })

        Button('回到第一帧')
          .width(100)
          .onClick(() => {
            this.fillMode = FillMode.Backwards;
          })

        Button('保持首尾帧')
          .width(100)
          .onClick(() => {
            this.fillMode = FillMode.Both;
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xF0F0F0)
    .borderRadius(10)
  }

  @Builder
  buildBestPractices() {
    Column({ space: 15 }) {
      Text('最佳实践建议')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('• 简单动画')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用全局 duration 属性，简化代码')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 复杂动画')
          .fontSize(14)
          .fontColor(0x333333)
        Text('为每一帧单独设置 duration，实现精细控制')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 节奏动画')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用渐变时长创建节奏感')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 强调动画')
          .fontSize(14)
          .fontColor(0x333333)
        Text('为关键帧设置更长时长，突出重点')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 性能优化')
          .fontSize(14)
          .fontColor(0x333333)
        Text('避免设置过短的时长，可能导致性能问题')
          .fontSize(12)
          .fontColor(0x666666)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }
}
