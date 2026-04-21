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
 * ImageAnimatorTest012 - fillMode 完整测试
 * ========================================
 * 
 * 测试功能说明:
 * 本测试验证 ImageAnimator 组件 fillMode 属性的所有枚举值
 * 
 * 涉及的 ImageAnimator API:
 * 1. fillMode(value: FillMode) - 动画前后状态
 * 2. FillMode 枚举：None, Forwards, Backwards, Both
 * 3. 与 reverse 属性的配合
 * 
 * ========================================
 * API 文档说明
 * ========================================
 * fillMode 设置当前播放方向下，动画开始前和结束后的状态。
 * 
 * 动画结束后的状态由 fillMode 和 reverse 属性共同决定。
 * 例如，fillMode 为 Forwards 表示停止时维持动画最后一个关键帧的状态：
 * - 若 reverse 为 false 则维持正播的最后一帧 (最后一张图)
 * - 若 reverse 为 true 则维持逆播的最后一帧 (第一张图)
 * 
 * ========================================
 * FillMode 枚举值
 * ========================================
 * 1. FillMode.None: 动画前后都不保持状态
 * 2. FillMode.Forwards: 动画结束后保持最终状态 (默认)
 * 3. FillMode.Backwards: 动画开始前保持初始状态
 * 4. FillMode.Both: 同时应用 Backwards 和 Forwards
 * 
 * ========================================
 * 测试用例
 * ========================================
 * 1. FillMode.None: 验证不保持状态
 * 2. FillMode.Forwards: 验证保持最终状态
 * 3. FillMode.Backwards: 验证保持初始状态
 * 4. FillMode.Both: 验证同时保持
 * 5. 配合 reverse=true 测试
 */

@Entry
@Component
struct ImageAnimatorTest012 {
  @State testFillMode: FillMode = FillMode.Forwards;
  @State testReverse: boolean = false;
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State currentStatus: string = 'Initial';
  @State testResult: string = '等待测试...';
  @State isPlaying: boolean = false;

  // 测试用例数据
  private testCases: Array<{
    name: string;
    fillMode: FillMode;
    expected: string;
  }> = [
    { name: 'FillMode.None', fillMode: FillMode.None, expected: '前后都不保持' },
    { name: 'FillMode.Forwards', fillMode: FillMode.Forwards, expected: '保持最终状态 (默认)' },
    { name: 'FillMode.Backwards', fillMode: FillMode.Backwards, expected: '保持初始状态' },
    { name: 'FillMode.Both', fillMode: FillMode.Both, expected: '同时保持前后' }
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('fillMode 完整测试')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildTestInfo()
        this.buildTestArea()
        this.buildFillModeComparison()
        this.buildTestCases()
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
      Text('API 文档说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('fillMode 设置当前播放方向下，动画开始前和结束后的状态。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('动画结束后的状态由 fillMode 和 reverse 属性共同决定。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('例如，fillMode 为 Forwards 表示停止时维持动画最后一个关键帧的状态：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 若 reverse 为 false 则维持正播的最后一帧 (最后一张图)')
        .fontSize(14)
        .fontColor(0x2196F3)

      Text('• 若 reverse 为 true 则维持逆播的最后一帧 (第一张图)')
        .fontSize(14)
        .fontColor(0x2196F3)

      Row({ space: 20 }) {
        Text('FillMode 枚举值:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x666666)
      }
      .width('100%')

      Grid() {
        GridItem() {
          Text('None')
            .fontSize(12)
            .fontColor(Color.White)
            .padding(5)
            .backgroundColor(Color.Gray)
            .borderRadius(5)
        }
        GridItem() {
          Text('Forwards (默认)')
            .fontSize(12)
            .fontColor(Color.White)
            .padding(5)
            .backgroundColor(Color.Blue)
            .borderRadius(5)
        }
        GridItem() {
          Text('Backwards')
            .fontSize(12)
            .fontColor(Color.White)
            .padding(5)
            .backgroundColor(Color.Green)
            .borderRadius(5)
        }
        GridItem() {
          Text('Both')
            .fontSize(12)
            .fontColor(Color.White)
            .padding(5)
            .backgroundColor(Color.Purple)
            .borderRadius(5)
        }
      }
      .columnsTemplate('1fr 1fr')
      .rowsGap(5)
      .columnsGap(5)
      .width('100%')
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildTestArea() {
    Column({ space: 15 }) {
      Text('测试区域 (fillMode: ' + this.getFillModeName(this.testFillMode) + ', reverse: ' + this.testReverse + ')')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Blue)

      ImageAnimator()
        .images([
          { src: $r('app.media.img1') },
          { src: $r('app.media.img2') },
          { src: $r('app.media.img3') },
          { src: $r('app.media.img4') }
        ])
        .duration(2000)
        .state(this.animationState)
        .fillMode(this.testFillMode)
        .reverse(this.testReverse)
        .iterations(1)
        .width(300)
        .height(200)
        .border({ width: 2, color: Color.Blue })
        .onStart(() => {
          this.currentStatus = 'Started';
          this.isPlaying = true;
          this.testResult = '播放开始';
        })
        .onPause(() => {
          this.currentStatus = 'Paused';
          this.isPlaying = false;
          this.testResult = '播放暂停';
        })
        .onFinish(() => {
          this.currentStatus = 'Finished';
          this.isPlaying = false;
          this.animationState = AnimationStatus.Stopped;
          this.testResult = '播放完成 (fillMode=' + this.getFillModeName(this.testFillMode) + ')';
        })

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Text('状态:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.currentStatus)
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(this.isPlaying ? Color.Green : Color.Gray)
        }

        Column({ space: 5 }) {
          Text('播放方向:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.testReverse ? '反向 (4→1)' : '正向 (1→4)')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Blue)
        }
      }
      .padding(10)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Text('提示：播放完成后观察保持的帧')
        .fontSize(12)
        .fontColor(Color.Orange)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildFillModeComparison() {
    Column({ space: 15 }) {
      Text('FillMode 对比 (正向播放)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Grid() {
        ForEach([FillMode.None, FillMode.Forwards, FillMode.Backwards, FillMode.Both], (fillMode: FillMode) => {
          GridItem() {
            Column({ space: 10 }) {
              Text(this.getFillModeName(fillMode))
                .fontSize(12)
                .fontWeight(FontWeight.Medium)
                .fontColor(Color.White)
                .padding(5)
                .backgroundColor(this.getFillModeColor(fillMode))
                .borderRadius(5)
                .width('100%')
                .textAlign(TextAlign.Center)

              ImageAnimator()
                .images([
                  { src: $r('app.media.img1') },
                  { src: $r('app.media.img4') }
                ])
                .duration(1000)
                .fillMode(fillMode)
                .iterations(1)
                .width(120)
                .height(80)

              Text(this.getFillModeDesc(fillMode))
                .fontSize(10)
                .fontColor(Color.Gray)
                .textAlign(TextAlign.Center)
            }
            .padding(10)
            .backgroundColor(0xF5F5F5)
            .borderRadius(10)
            .width('100%')
          }
        })
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
  buildTestCases() {
    Column({ space: 15 }) {
      Text('测试用例 (点击测试)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      ForEach(this.testCases, (testCase: { name: string; fillMode: FillMode; expected: string }) => {
        Row({ space: 15 }) {
          Button(testCase.name)
            .fontSize(14)
            .backgroundColor(this.testFillMode === testCase.fillMode ? Color.Blue : Color.LightGray)
            .onClick(() => {
              this.testFillMode = testCase.fillMode;
              this.testResult = '已选择：' + testCase.name + ' - 预期：' + testCase.expected;
              this.animationState = AnimationStatus.Stopped;
              this.currentStatus = 'Initial';
              this.isPlaying = false;
            })

          Text('预期：' + testCase.expected)
            .fontSize(12)
            .fontColor(Color.Gray)
            .layoutWeight(1)
        }
        .width('100%')
        .padding(10)
        .backgroundColor(this.testFillMode === testCase.fillMode ? 0xE3F2FD : 0xF5F5F5)
        .borderRadius(10)
      })

      Toggle({ type: ToggleType.Switch, isOn: this.testReverse })
        .onChange((isOn: boolean) => {
          this.testReverse = isOn;
          this.testResult = 'reverse 切换为：' + (isOn ? 'true (反向)' : 'false (正向)');
        })
        .padding({ top: 10 })

      Text('reverse: ' + (this.testReverse ? 'true (反向播放)' : 'false (正向播放)'))
        .fontSize(14)
        .fontColor(Color.Gray)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildControlPanel() {
    Column({ space: 15 }) {
      Text('控制面板')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Row({ space: 10 }) {
        Button('开始播放')
          .fontSize(14)
          .backgroundColor(Color.Green)
          .onClick(() => {
            this.animationState = AnimationStatus.Running;
            this.testResult = '开始播放 (fillMode=' + this.getFillModeName(this.testFillMode) + ')';
          })

        Button('暂停')
          .fontSize(14)
          .backgroundColor(Color.Orange)
          .onClick(() => {
            this.animationState = AnimationStatus.Paused;
            this.testResult = '播放暂停';
          })

        Button('停止')
          .fontSize(14)
          .backgroundColor(Color.Red)
          .onClick(() => {
            this.animationState = AnimationStatus.Stopped;
            this.testResult = '播放停止';
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

  getFillModeName(fillMode: FillMode): string {
    switch (fillMode) {
      case FillMode.None: return 'None';
      case FillMode.Forwards: return 'Forwards';
      case FillMode.Backwards: return 'Backwards';
      case FillMode.Both: return 'Both';
      default: return 'Unknown';
    }
  }

  getFillModeColor(fillMode: FillMode): number {
    switch (fillMode) {
      case FillMode.None: return 0x9E9E9E;
      case FillMode.Forwards: return 0x2196F3;
      case FillMode.Backwards: return 0x4CAF50;
      case FillMode.Both: return 0x9C27B0;
      default: return 0x9E9E9E;
    }
  }

  getFillModeDesc(fillMode: FillMode): string {
    switch (fillMode) {
      case FillMode.None: return '前后都不保持';
      case FillMode.Forwards: return '保持最终帧';
      case FillMode.Backwards: return '保持初始帧';
      case FillMode.Both: return '前后都保持';
      default: return '';
    }
  }
}
