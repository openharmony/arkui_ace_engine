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
 * ========================================
 * AnimationOptionsAdvancedTest - AnimationOptions 高级测试
 * ========================================
 * 
 * 测试功能说明:
 * 本测试验证 AnimatedDrawableDescriptor 的 AnimationOptions 高级功能
 * 
 * 涉及的 API:
 * 1. AnimationOptions.duration - 动画时长
 * 2. AnimationOptions.iterations - 播放次数
 * 3. AnimationOptions.autoPlay - 自动播放
 * 4. AnimationOptions.frameDurations - 每帧时长数组 (高级功能)
 * 
 * ========================================
 * AnimationOptions 完整接口
 * ========================================
 * interface AnimationOptions {
 *   duration?: number;        // 动画总时长 (ms)
 *   iterations?: number;      // 播放次数 (-1 无限)
 *   autoPlay?: boolean;       // 自动播放
 *   frameDurations?: number[]; // 每帧时长数组 (高级)
 * }
 * 
 * ========================================
 * 测试用例
 * ========================================
 * 1. 基础配置 (duration + iterations)
 * 2. autoPlay 自动播放
 * 3. frameDurations 每帧单独控制
 * 4. 组合配置 (所有选项)
 */

@Entry
@Component
struct AnimationOptionsAdvancedTest {
  @State testMode: number = 1;
  @State animationStatus: AnimationStatus = AnimationStatus.Initial;
  @State testResult: string = '等待测试...';
  @State isPlaying: boolean = false;
  @State currentFrame: number = 0;
  @State frameCount: number = 0;

  private animatedDrawable1?: AnimatedDrawableDescriptor; // 基础配置
  private animatedDrawable2?: AnimatedDrawableDescriptor; // autoPlay
  private animatedDrawable3?: AnimatedDrawableDescriptor; // frameDurations
  private animatedDrawable4?: AnimatedDrawableDescriptor; // 组合配置

  aboutToAppear() {
    if (this.getUIContext().getHostContext()?.resourceManager) {
      this.createTestDrawables();
    }
  }

  createTestDrawables() {
    const resManager = this.getUIContext().getHostContext()?.resourceManager;
    if (!resManager) return;

    // 测试 1: 基础配置
    this.animatedDrawable1 = new AnimatedDrawableDescriptor(
      $r('app.media.flower'),
      { duration: 2000, iterations: -1 }
    );

    // 测试 2: autoPlay
    this.animatedDrawable2 = new AnimatedDrawableDescriptor(
      $r('app.media.img2'),
      { duration: 3000, iterations: 1, autoPlay: true }
    );

    // 测试 3: frameDurations (每帧单独控制)
    this.animatedDrawable3 = new AnimatedDrawableDescriptor(
      $r('app.media.cat2'),
      { 
        frameDurations: [500, 1000, 200, 1500, 300] // 每帧不同时长
      }
    );

    // 测试 4: 组合配置
    this.animatedDrawable4 = new AnimatedDrawableDescriptor(
      $r('app.media.mouse'),
      { 
        duration: 4000,
        iterations: 3,
        autoPlay: false,
        frameDurations: [800, 1200, 1000, 1000]
      }
    );
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('AnimationOptions 高级测试')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildTestInfo()
        this.buildModeSelector()
        this.buildTestArea()
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
  buildTestInfo() {
    Column({ space: 10 }) {
      Text('AnimationOptions 接口')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('interface AnimationOptions {')
        .fontSize(12)
        .fontColor(0x999999)
        .backgroundColor(0xF5F5F5)
        .padding(10)
        .borderRadius(5)

      Text('  duration?: number;        // 动画总时长 (ms)')
        .fontSize(12)
        .fontColor(0x666666)

      Text('  iterations?: number;      // 播放次数 (-1 无限)')
        .fontSize(12)
        .fontColor(0x666666)

      Text('  autoPlay?: boolean;       // 自动播放')
        .fontSize(12)
        .fontColor(0x666666)

      Text('  frameDurations?: number[]; // 每帧时长数组 (高级)')
        .fontSize(12)
        .fontColor(0x2196F3)
        .backgroundColor(0xE3F2FD)
        .padding(5)
        .borderRadius(5)

      Text('}')
        .fontSize(12)
        .fontColor(0x999999)

      Text('提示：frameDurations 优先级高于 duration')
        .fontSize(12)
        .fontColor(Color.Orange)
        .backgroundColor(0xFFF3E0)
        .padding(10)
        .borderRadius(10)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildModeSelector() {
    Column({ space: 15 }) {
      Text('选择测试模式')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Grid() {
        GridItem() {
          this.buildModeCard(1, '基础配置', 'duration + iterations', Color.Blue);
        }
        GridItem() {
          this.buildModeCard(2, 'autoPlay', '自动播放', Color.Green);
        }
        GridItem() {
          this.buildModeCard(3, 'frameDurations', '每帧单独控制', Color.Orange);
        }
        GridItem() {
          this.buildModeCard(4, '组合配置', '所有选项', Color.Purple);
        }
      }
      .columnsTemplate('1fr 1fr')
      .rowsGap(10)
      .columnsGap(10)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildModeCard(mode: number, title: string, desc: string, color: number) {
    Column({ space: 10 }) {
      Text(title)
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.White)
        .padding(5)
        .backgroundColor(color)
        .borderRadius(5)
        .width('100%')
        .textAlign(TextAlign.Center)

      Text(desc)
        .fontSize(12)
        .fontColor(Color.Gray)

      Button('选择')
        .fontSize(12)
        .backgroundColor(this.testMode === mode ? color : Color.LightGray)
        .onClick(() => {
          this.testMode = mode;
          this.testResult = '已选择模式 ' + mode + ': ' + title;
          this.updateStatus();
        })
    }
    .padding(10)
    .backgroundColor(this.testMode === mode ? 0xF0F0F0 : 0xFFFFFF)
    .borderRadius(10)
    .width('100%')
  }

  @Builder
  buildTestArea() {
    Column({ space: 15 }) {
      Text('测试区域 (模式 ' + this.testMode + ')')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Blue)

      this.buildTestContent()

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Text('状态:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.getAnimationStatusName(animationStatus))
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(this.isPlaying ? Color.Green : Color.Gray)
        }

        Column({ space: 5 }) {
          Text('当前帧:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text((this.currentFrame + 1) + ' / ' + (this.frameCount > 0 ? this.frameCount : 4))
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Blue)
        }
      }
      .padding(10)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      this.buildConfigDisplay()
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildTestContent() {
    if (this.testMode === 1) {
      // 基础配置
      if (this.animatedDrawable1) {
        Image(this.animatedDrawable1)
          .width(150)
          .height(150)
          .borderRadius(10)
          .border({ width: 2, color: Color.Blue })
      }
    } else if (this.testMode === 2) {
      // autoPlay
      if (this.animatedDrawable2) {
        Image(this.animatedDrawable2)
          .width(150)
          .height(150)
          .borderRadius(10)
          .border({ width: 2, color: Color.Green })
      }
    } else if (this.testMode === 3) {
      // frameDurations
      if (this.animatedDrawable3) {
        Image(this.animatedDrawable3)
          .width(150)
          .height(150)
          .borderRadius(10)
          .border({ width: 2, color: Color.Orange })
      }
    } else if (this.testMode === 4) {
      // 组合配置
      if (this.animatedDrawable4) {
        Image(this.animatedDrawable4)
          .width(150)
          .height(150)
          .borderRadius(10)
          .border({ width: 2, color: Color.Purple })
      }
    }
  }

  @Builder
  buildConfigDisplay() {
    Column({ space: 10 }) {
      Text('当前配置:')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Gray)

      if (this.testMode === 1) {
        Text('{ duration: 2000, iterations: -1 }')
          .fontSize(12)
          .fontColor(Color.Blue)
          .backgroundColor(0xE3F2FD)
          .padding(10)
          .borderRadius(5)
      } else if (this.testMode === 2) {
        Text('{ duration: 3000, iterations: 1, autoPlay: true }')
          .fontSize(12)
          .fontColor(Color.Green)
          .backgroundColor(0xE8F5E9)
          .padding(10)
          .borderRadius(5)
      } else if (this.testMode === 3) {
        Text('{ frameDurations: [500, 1000, 200, 1500, 300] }')
          .fontSize(12)
          .fontColor(Color.Orange)
          .backgroundColor(0xFFF3E0)
          .padding(10)
          .borderRadius(5)
        Text('每帧时长不同，实现变速效果')
          .fontSize(12)
          .fontColor(Color.Gray)
      } else if (this.testMode === 4) {
        Text('{ duration: 4000, iterations: 3, autoPlay: false, frameDurations: [...] }')
          .fontSize(12)
          .fontColor(Color.Purple)
          .backgroundColor(0xF3E5F5)
          .padding(10)
          .borderRadius(5)
        Text('组合配置，frameDurations 优先级更高')
          .fontSize(12)
          .fontColor(Color.Gray)
      }
    }
    .width('100%')
  }

  @Builder
  buildControlPanel() {
    Column({ space: 15 }) {
      Text('控制面板')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Row({ space: 10 }) {
        Button('开始')
          .fontSize(14)
          .backgroundColor(Color.Green)
          .onClick(() => {
            this.startAnimation();
          })

        Button('暂停')
          .fontSize(14)
          .backgroundColor(Color.Orange)
          .onClick(() => {
            this.pauseAnimation();
          })

        Button('停止')
          .fontSize(14)
          .backgroundColor(Color.Red)
          .onClick(() => {
            this.stopAnimation();
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)

      Text('测试结果：' + this.testResult)
        .fontSize(14)
        .fontColor(Color.Blue)
        .padding(10)
        .backgroundColor(0xE8F5E9)
        .borderRadius(10)
        .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xE8F5E9)
    .borderRadius(15)
  }

  updateStatus() {
    const drawable = this.getCurrentDrawable();
    if (drawable instanceof AnimatedDrawableDescriptor) {
      const controller = drawable.getAnimationController();
      const status = controller?.getStatus();
      if (status !== undefined) {
        this.animationStatus = status;
      }
    }
  }

  getCurrentDrawable(): AnimatedDrawableDescriptor | undefined {
    if (this.testMode === 1) return this.animatedDrawable1;
    if (this.testMode === 2) return this.animatedDrawable2;
    if (this.testMode === 3) return this.animatedDrawable3;
    if (this.testMode === 4) return this.animatedDrawable4;
    return undefined;
  }

  startAnimation() {
    const drawable = this.getCurrentDrawable();
    if (drawable instanceof AnimatedDrawableDescriptor) {
      const controller = drawable.getAnimationController();
      controller?.start();
      this.isPlaying = true;
      this.animationStatus = AnimationStatus.Running;
      this.testResult = '动画开始 (模式 ' + this.testMode + ')';
    }
  }

  pauseAnimation() {
    const drawable = this.getCurrentDrawable();
    if (drawable instanceof AnimatedDrawableDescriptor) {
      const controller = drawable.getAnimationController();
      controller?.pause();
      this.isPlaying = false;
      this.animationStatus = AnimationStatus.Paused;
      this.testResult = '动画暂停';
    }
  }

  stopAnimation() {
    const drawable = this.getCurrentDrawable();
    if (drawable instanceof AnimatedDrawableDescriptor) {
      const controller = drawable.getAnimationController();
      controller?.stop();
      this.isPlaying = false;
      this.animationStatus = AnimationStatus.Stopped;
      this.testResult = '动画停止';
    }
  }

  getAnimationStatusName(status: AnimationStatus): string {
    switch (status) {
      case AnimationStatus.Initial: return 'Initial';
      case AnimationStatus.Running: return 'Running';
      case AnimationStatus.Paused: return 'Paused';
      case AnimationStatus.Stopped: return 'Stopped';
      default: return 'Unknown';
    }
  }
}
