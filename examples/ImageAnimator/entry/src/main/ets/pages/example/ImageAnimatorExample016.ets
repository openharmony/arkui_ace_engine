/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with License.
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
 * ImageAnimatorExample016 - 自定义帧尺寸和位置动画示例
 * 
 * 功能说明：
 * 1. ImageFrameInfo 的 width/height/top/left 属性 - 每一帧图片的尺寸和位置信息
 * 2. 只有在 fixedSize 设置为 false 时，这些属性才会生效
 * 3. 支持为每一帧单独设置不同的尺寸和位置，实现复杂动画效果
 * 4. string 类型支持 number 和 string，string 可以附带单位（如 "100vp"）
 */

@Entry
@Component
struct ImageAnimatorExample016 {
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State reverse: boolean = false;
  @State iterationCount: number = 1;
  @State fillMode: FillMode = FillMode.Forwards;
  @State currentStatus: string = 'Initial';
  @State showAdvanced: boolean = false;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('自定义帧尺寸和位置动画示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildBasicDemo()
        this.buildComplexDemo()
        this.buildAdvancedDemo()
        this.buildBestPractices()
        this.buildControlPanel()
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
      Text('ImageFrameInfo 尺寸和位置属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('每一帧图片可以单独设置尺寸和位置信息：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• width - 图片宽度')
        .fontSize(12)
        .fontColor(0x666666)

      Text('• height - 图片高度')
        .fontSize(12)
        .fontColor(0x666666)

      Text('• top - 图片相对于组件左上角的纵向坐标')
        .fontSize(12)
        .fontColor(0x666666)

      Text('• left - 图片相对于组件左上角的横向坐标')
        .fontSize(12)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 只有在 fixedSize 设置为 false 时，这些属性才会生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 支持 number 和 string 类型，string 可以附带单位（如 "100vp"）')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 可以创建复杂的动画效果，如：')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 图片在不同位置之间移动')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 图片大小渐变动画')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 路径缩放动画')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildBasicDemo() {
    Column({ space: 15 }) {
      Text('基础演示')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('固定尺寸模式')
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
                top: 100,
                left: 100
              }
            ])
            .duration(2000)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(false)
            .width(300)
            .height(300)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)

          Text('所有图片保持独立尺寸和位置')
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
  buildComplexDemo() {
    Column({ space: 15 }) {
      Text('复杂动画演示')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Column({ space: 10 }) {
          Text('旋转缩放动画')
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
                top: 100,
                left: 100
              }
            ])
            .duration(2000)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(false)
            .width(300)
            .height(300)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)

          Text('图片在不同位置旋转缩放')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('路径动画')
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
                top: 100,
                left: 100
              }
            ])
            .duration(2000)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(false)
            .width(300)
            .height(300)
            .border({ width: 2, color: Color.Orange })
            .borderRadius(8)

          Text('图片沿路径移动')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('大小渐变动画')
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
                top: 100,
                left: 100
              }
            ])
            .duration(2000)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(false)
            .width(300)
            .height(300)
            .border({ width: 2, color: Color.Purple })
            .borderRadius(8)

          Text('图片大小渐变')
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
  buildAdvancedDemo() {
    Column({ space: 15 }) {
      Text('高级功能演示')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('可变尺寸动画')
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
                top: 100,
                left: 100
              }
            ])
            .duration(2000)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(false)
            .width(300)
            .height(300)
            .border({ width: 2, color: Color.Pink })
            .borderRadius(8)

          Text('动态改变每帧的尺寸和位置')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('重叠动画')
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
                top: 100,
                left: 100
              }
            ])
            .duration(2000)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(false)
            .width(300)
            .height(300)
            .border({ width: 2, color: Color.Gray })
            .borderRadius(8)

          Text('图片重叠在一起显示')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('径向缩放动画')
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
                top: 100,
                left: 100
              }
            ])
            .duration(2000)
            .state(this.animationState)
            .reverse(this.reverse)
            .fillMode(this.fillMode)
            .iterations(this.iterationCount)
            .fixedSize(false)
            .width(300)
            .height(300)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)

          Text('图片径向缩放')
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
        Text('使用不同的帧尺寸和位置创建逐帧动画效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 路径向动画')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用径向缩放实现图片放大镜效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 性能优化')
          .fontSize(14)
          .fontColor(0x333333)
        Text('• 固定位尺寸通常性能更好，因为系统可以预先分配资源')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 内存占用')
          .fontSize(14)
          .fontColor(0x333333)
        Text('• 可变尺寸模式可能需要更多内存，因为需要存储每张图片的独立尺寸信息')
          .fontSize(12)
          .fontColor(0x666666)
      }
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
        Button('显示高级功能')
          .width(100)
          .onClick(() => {
            this.showAdvanced = !this.showAdvanced;
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
}
