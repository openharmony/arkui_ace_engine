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
 * DrawableDescriptorBoundaryTest - 边界值测试
 * ========================================
 * 
 * 测试功能说明:
 * 本测试验证 AnimatedDrawableDescriptor 的边界值行为
 * 
 * 涉及的 API:
 * 1. AnimationOptions.duration - 动画时长
 * 2. AnimationOptions.iterations - 播放次数
 * 3. 边界值处理：0, 负数，浮点数
 * 
 * ========================================
 * 测试用例
 * ========================================
 * duration 边界值:
 * 1. duration = 0: 验证不播放
 * 2. duration = -100: 验证取默认值
 * 3. duration = 1: 验证过小值
 * 4. duration = 100: 验证最小可用值
 * 5. duration = 1000: 验证正常值 (基准)
 * 
 * iterations 边界值:
 * 6. iterations = -1: 验证无限循环
 * 7. iterations = -2: 验证取默认值 1
 * 8. iterations = 0: 验证不播放
 * 9. iterations = 1: 验证播放 1 次
 * 10. iterations = 3.9: 验证向下取整
 * 11. iterations = 0.5: 验证向下取整为 0
 */

@Entry
@Component
struct DrawableDescriptorBoundaryTest {
  @State testDuration: number = 1000;
  @State testIterations: number = 1;
  @State animationStatus: AnimationStatus = AnimationStatus.Initial;
  @State testResult: string = '等待测试...';
  @State isPlaying: boolean = false;
  @State testCategory: string = 'duration';
  @State repeatCount: number = 0;

  private animatedDrawable?: AnimatedDrawableDescriptor;

  aboutToAppear() {
    if (this.getUIContext().getHostContext()?.resourceManager) {
      this.animatedDrawable = new AnimatedDrawableDescriptor(
        $r('app.media.flower'),
        { duration: this.testDuration, iterations: this.testIterations }
      );
    }
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('DrawableDescriptor 边界值测试')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildTestInfo()
        this.buildCategorySelector()
        this.buildTestArea()
        this.buildTestButtons()
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
      Text('边界值说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      if (this.testCategory === 'duration') {
        Text('duration 边界值:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x2196F3)

        Text('• duration = 0: 不播放')
          .fontSize(12)
          .fontColor(0x666666)

        Text('• duration = 负数：取默认值 (1000ms)')
          .fontSize(12)
          .fontColor(0x666666)

        Text('• duration 过小：可能导致播放卡顿')
          .fontSize(12)
          .fontColor(0x666666)
      } else {
        Text('iterations 边界值:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x2196F3)

        Text('• iterations = -1: 无限循环')
          .fontSize(12)
          .fontColor(0x666666)

        Text('• iterations < -1: 取默认值 (1)')
          .fontSize(12)
          .fontColor(0x666666)

        Text('• iterations = 浮点数：向下取整')
          .fontSize(12)
          .fontColor(0x666666)

        Text('• iterations = 0: 不播放')
          .fontSize(12)
          .fontColor(0x666666)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildCategorySelector() {
    Column({ space: 15 }) {
      Text('选择测试类别')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Row({ space: 10 }) {
        Button('duration 测试')
          .fontSize(14)
          .backgroundColor(this.testCategory === 'duration' ? Color.Blue : Color.LightGray)
          .onClick(() => {
            this.testCategory = 'duration';
            this.resetTest();
          })

        Button('iterations 测试')
          .fontSize(14)
          .backgroundColor(this.testCategory === 'iterations' ? Color.Green : Color.LightGray)
          .onClick(() => {
            this.testCategory = 'iterations';
            this.resetTest();
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.Center)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildTestArea() {
    Column({ space: 15 }) {
      Text('测试区域')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Blue)

      if (this.animatedDrawable) {
        Image(this.animatedDrawable)
          .width(150)
          .height(150)
          .borderRadius(10)
          .border({ width: 2, color: Color.Blue })
      }

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
          Text('当前值:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.testCategory === 'duration' ? 
               this.testDuration + 'ms' : 
               this.testIterations.toString())
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Blue)
        }

        Column({ space: 5 }) {
          Text('循环次数:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.repeatCount > 0 ? (this.repeatCount + 1) + ' 次' : '0 次')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Orange)
        }
      }
      .padding(10)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildTestButtons() {
    Column({ space: 15 }) {
      Text('边界值测试 (点击测试)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      if (this.testCategory === 'duration') {
        this.buildDurationTestButtons();
      } else {
        this.buildIterationsTestButtons();
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildDurationTestButtons() {
    Grid() {
      ForEach([
        { name: 'duration=0', value: 0, expected: '不播放' },
        { name: 'duration=-100', value: -100, expected: '默认值' },
        { name: 'duration=1', value: 1, expected: '可能卡顿' },
        { name: 'duration=100', value: 100, expected: '最小可用' },
        { name: 'duration=1000', value: 1000, expected: '正常值' },
        { name: 'duration=5000', value: 5000, expected: '慢速' }
      ], (testCase: { name: string; value: number; expected: string }) => {
        GridItem() {
          Column({ space: 10 }) {
            Button(testCase.name)
              .fontSize(12)
              .backgroundColor(this.testDuration === testCase.value ? Color.Blue : Color.LightGray)
              .onClick(() => {
                this.testDuration = testCase.value;
                this.testResult = '已选择：' + testCase.name + ' - 预期：' + testCase.expected;
                this.resetAnimation();
              })

            Text('预期：' + testCase.expected)
              .fontSize(10)
              .fontColor(Color.Gray)
          }
          .padding(10)
          .backgroundColor(this.testDuration === testCase.value ? 0xE3F2FD : 0xF5F5F5)
          .borderRadius(10)
          .width('100%')
        }
      })
    }
    .columnsTemplate('1fr 1fr 1fr')
    .rowsGap(10)
    .columnsGap(10)
    .width('100%')
  }

  @Builder
  buildIterationsTestButtons() {
    Grid() {
      ForEach([
        { name: 'iterations=-1', value: -1, expected: '无限循环' },
        { name: 'iterations=-2', value: -2, expected: '取默认值 1' },
        { name: 'iterations=0', value: 0, expected: '不播放' },
        { name: 'iterations=1', value: 1, expected: '播放 1 次' },
        { name: 'iterations=3', value: 3, expected: '播放 3 次' },
        { name: 'iterations=3.9', value: 3.9, expected: '取整为 3' }
      ], (testCase: { name: string; value: number; expected: string }) => {
        GridItem() {
          Column({ space: 10 }) {
            Button(testCase.name)
              .fontSize(12)
              .backgroundColor(this.testIterations === testCase.value ? Color.Green : Color.LightGray)
              .onClick(() => {
                this.testIterations = testCase.value;
                this.testResult = '已选择：' + testCase.name + ' - 预期：' + testCase.expected;
                this.resetAnimation();
              })

            Text('预期：' + testCase.expected)
              .fontSize(10)
              .fontColor(Color.Gray)
          }
          .padding(10)
          .backgroundColor(this.testIterations === testCase.value ? 0xE8F5E9 : 0xF5F5F5)
          .borderRadius(10)
          .width('100%')
        }
      })
    }
    .columnsTemplate('1fr 1fr 1fr')
    .rowsGap(10)
    .columnsGap(10)
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

        Button('重置计数')
          .fontSize(14)
          .backgroundColor(Color.Gray)
          .onClick(() => {
            this.repeatCount = 0;
            this.testResult = '循环计数已重置';
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

  resetTest() {
    this.testResult = '等待测试...';
    this.isPlaying = false;
    this.repeatCount = 0;
    this.animationStatus = AnimationStatus.Initial;
  }

  resetAnimation() {
    if (this.getUIContext().getHostContext()?.resourceManager) {
      this.animatedDrawable = new AnimatedDrawableDescriptor(
        $r('app.media.flower'),
        { 
          duration: this.testCategory === 'duration' ? this.testDuration : 1000,
          iterations: this.testCategory === 'iterations' ? this.testIterations : 1
        }
      );
      this.resetTest();
    }
  }

  startAnimation() {
    if (this.animatedDrawable instanceof AnimatedDrawableDescriptor) {
      const controller = this.animatedDrawable.getAnimationController();
      controller?.start();
      this.isPlaying = true;
      this.animationStatus = AnimationStatus.Running;
      this.testResult = '动画开始 (duration=' + this.testDuration + 'ms, iterations=' + this.testIterations + ')';
    }
  }

  pauseAnimation() {
    if (this.animatedDrawable instanceof AnimatedDrawableDescriptor) {
      const controller = this.animatedDrawable.getAnimationController();
      controller?.pause();
      this.isPlaying = false;
      this.animationStatus = AnimationStatus.Paused;
      this.testResult = '动画暂停';
    }
  }

  stopAnimation() {
    if (this.animatedDrawable instanceof AnimatedDrawableDescriptor) {
      const controller = this.animatedDrawable.getAnimationController();
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
