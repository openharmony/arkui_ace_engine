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
 * ImageAnimatorExample014 - 固定尺寸动画示例
 * 
 * 功能说明：
 * 1. fixedSize 属性 - 设置图片大小是否固定为组件大小
 * 2. true 表示图片大小与组件大小一致，此时设置图片的 width、height、top 和 left 属性无效
 * 3. false 表示每一张图片的 width、height、top 和 left 属性都要单独设置
 */

@Entry
@Component
struct ImageAnimatorExample014 {
  @State useFixedSize: boolean = true;
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State iterationCount: number = 1;
  @State fillMode: FillMode = FillMode.Forwards;
  @State reverse: boolean = false;
  @State duration: number = 2000;
  @State currentStatus: string = 'Initial';

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('ImageAnimator 固定尺寸示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildFixedSizeDemo()
        this.buildVariableSizeDemo()
        this.buildComparisonDemo()
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
      Text('fixedSize 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置图片大小是否固定为组件大小。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• true：图片大小与组件大小一致，此时设置图片的 width、height、top 和 left 属性无效')
        .fontSize(12)
        .fontColor(0x666666)

      Text('• false：每一张图片的 width、height、top 和 left 属性都要单独设置')
        .fontSize(12)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildFixedSizeDemo() {
    Column({ space: 15 }) {
      Text('固定位尺寸模式 (fixedSize = true)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
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
            .duration(this.duration)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(true)
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

          Text('所有图片自动缩放到组件大小 (300x200)')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('控制面板')
            .fontSize(14)
            .fontColor(0x333333)

          this.buildControlPanel()
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildVariableSizeDemo() {
    Column({ space: 15 }) {
      Text('可变尺寸模式 (fixedSize = false)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('动画组件')
            .fontSize(14)
            .fontColor(0x333333)

          ImageAnimator()
            .images([
              { 
                src: $r('app.media.flower'),
                width: 100,
                height: 100,
                top: 0,
                left: 0
              },
              { 
                src: $r('app.media.ic_jpg'),
                width: 150,
                height: 150,
                top: 50,
                left: 50
              },
              { 
                src: $r('app.media.mix_png'),
                width: 200,
                height: 100,
                top: 100,
                left: 0
              },
              { 
                src: $r('app.media.ic_bmp'),
                width: 100,
                height: 200,
                top: 0,
                left: 150
              }
            ])
            .duration(this.duration)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(false)
            .width(300)
            .height(300)
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

          Text('每张图片可以单独设置尺寸和位置')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('控制面板')
            .fontSize(14)
            .fontColor(0x333333)

          this.buildControlPanel()
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildComparisonDemo() {
    Column({ space: 15 }) {
      Text('模式对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('固定位尺寸')
            .fontSize(14)
            .fontColor(0x333333)

          ImageAnimator()
            .images([
              { src: $r('app.media.flower') },
              { src: $r('app.media.ic_jpg') },
              { src: $r('app.media.mix_png') },
              { src: $r('app.media.ic_bmp') }
            ])
            .duration(this.duration)
            .state(this.animationState)
            .fixedSize(true)
            .width(300)
            .height(200)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }

          Text('所有图片缩放到相同尺寸')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('可变尺寸')
            .fontSize(14)
            .fontColor(0x333333)

          ImageAnimator()
            .images([
              { 
                src: $r('app.media.flower'),
                width: 100,
                height: 100,
                top: 0,
                left: 0
              },
              { 
                src: $r('app.media.ic_jpg'),
                width: 150,
                height: 150,
                top: 50,
                left: 50
              },
              { 
                src: $r('app.media.mix_png'),
                width: 200,
                height: 100,
                top: 100,
                left: 0
              },
              { 
                src: $r('app.media.ic_bmp'),
                width: 100,
                height: 200,
                top: 0,
                left: 150
              }
            ])
            .duration(this.duration)
            .state(this.animationState)
            .fixedSize(false)
            .width(300)
            .height(300)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
        }

          Text('每张图片保持独立尺寸和位置')
            .fontSize(12)
            .fontColor(0x666666)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceAround)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
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
        Text('• 固定位尺寸：适用于所有图片尺寸相同或需要统一显示效果的场景')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 可变尺寸：适用于需要创建复杂动画效果或不同图片需要不同尺寸的场景')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 性能考虑：固定位尺寸通常性能更好，因为系统可以预先分配资源')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 内存占用：可变尺寸模式可能需要更多内存，因为需要存储每张图片的独立尺寸信息')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildControlPanel() {
    Column({ space: 15 }) {
      Text('动画状态：' + this.currentStatus)
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)

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

      Row({ space: 10 }) {
        Text('动画时长：' + this.duration + 'ms')
          .fontSize(14)
          .fontColor(0x666666)

        Slider({
          min: 500,
          max: 5000,
          value: this.duration,
          step: 100
        })
          .width('100%')
          .onChange((value: number) => {
            this.duration = value;
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xF5FEDF7)
    .borderRadius(10)
  }
}
