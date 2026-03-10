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
 * ImageAnimatorTest011 - iterations 边界值测试
 * ========================================
 * 
 * 测试功能说明:
 * 本测试验证 ImageAnimator 组件 iterations 属性的边界值行为
 * 
 * 涉及的 ImageAnimator API:
 * 1. iterations(value: number) - 播放次数
 * 2. 边界值处理：-1 (无限), 负数 (<-1), 浮点数，0
 * 
 * ========================================
 * API 文档说明
 * ========================================
 * 根据官方文档:
 * - 默认播放一次
 * - 设置为 -1 时表示无限次播放
 * - 设置为小于 -1 的负数时取默认值 (1)
 * - 设置为浮点数时，数值向下取整
 * 
 * ========================================
 * 测试用例
 * ========================================
 * 1. iterations = -1: 验证无限循环
 * 2. iterations = -2: 验证取默认值 1
 * 3. iterations = -5: 验证取默认值 1
 * 4. iterations = 0: 验证不播放
 * 5. iterations = 1: 验证播放 1 次
 * 6. iterations = 3.9: 验证向下取整为 3
 * 7. iterations = 0.5: 验证向下取整为 0
 */

@Entry
@Component
struct ImageAnimatorTest011 {
  @State testIterations: number = 1;
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State currentStatus: string = 'Initial';
  @State testResult: string = '等待测试...';
  @State repeatCount: number = 0;
  @State isPlaying: boolean = false;

  // 测试用例数据
  private testCases: Array<{
    name: string;
    value: number;
    expected: string;
  }> = [
    { name: 'iterations = -1', value: -1, expected: '无限循环' },
    { name: 'iterations = -2', value: -2, expected: '取默认值 1' },
    { name: 'iterations = -5', value: -5, expected: '取默认值 1' },
    { name: 'iterations = 0', value: 0, expected: '不播放' },
    { name: 'iterations = 1', value: 1, expected: '播放 1 次' },
    { name: 'iterations = 3', value: 3, expected: '播放 3 次' },
    { name: 'iterations = 3.9', value: 3.9, expected: '向下取整为 3' },
    { name: 'iterations = 0.5', value: 0.5, expected: '向下取整为 0' }
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('iterations 边界值测试')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildTestInfo()
        this.buildTestArea()
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

      Text('• 默认播放一次')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 设置为 -1 时表示无限次播放')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 设置为小于 -1 的负数时取默认值 (1)')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 设置为浮点数时，数值向下取整')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 默认值：1')
        .fontSize(14)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildTestArea() {
    Column({ space: 15 }) {
      Text('测试区域 (当前 iterations: ' + this.testIterations + ')')
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
        .duration(1000)
        .state(this.animationState)
        .iterations(this.testIterations)
        .width(300)
        .height(200)
        .border({ width: 2, color: Color.Blue })
        .onStart(() => {
          this.currentStatus = 'Started';
          this.isPlaying = true;
          this.testResult = '播放开始 (iterations=' + this.testIterations + ')';
        })
        .onRepeat(() => {
          this.repeatCount++;
          this.testResult = '第 ' + (this.repeatCount + 1) + ' 次循环';
        })
        .onFinish(() => {
          this.currentStatus = 'Finished';
          this.isPlaying = false;
          this.animationState = AnimationStatus.Stopped;
          this.testResult = '播放完成 (总循环：' + (this.repeatCount + 1) + ' 次)';
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
          Text('循环次数:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.repeatCount > 0 ? (this.repeatCount + 1) + ' 次' : '1 次')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Blue)
        }

        Column({ space: 5 }) {
          Text('实际值:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.getActualIterations().toString())
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(this.testIterations < -1 ? Color.Orange : Color.Blue)
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
  buildTestCases() {
    Column({ space: 15 }) {
      Text('测试用例 (点击测试)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Grid() {
        ForEach(this.testCases, (testCase: { name: string; value: number; expected: string }) => {
          GridItem() {
            Column({ space: 10 }) {
              Button(testCase.name)
                .fontSize(12)
                .backgroundColor(this.testIterations === testCase.value ? Color.Blue : Color.LightGray)
                .onClick(() => {
                  this.testIterations = testCase.value;
                  this.testResult = '已选择：' + testCase.name + ' - 预期：' + testCase.expected;
                  this.animationState = AnimationStatus.Stopped;
                  this.currentStatus = 'Initial';
                  this.isPlaying = false;
                  this.repeatCount = 0;
                })

              Text('预期：' + testCase.expected)
                .fontSize(10)
                .fontColor(Color.Gray)
            }
            .padding(10)
            .backgroundColor(this.testIterations === testCase.value ? 0xE3F2FD : 0xF5F5F5)
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
            this.testResult = '开始播放 (iterations=' + this.testIterations + ')';
            this.repeatCount = 0;
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
            this.repeatCount = 0;
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

  // 获取实际生效的 iterations 值
  getActualIterations(): number | string {
    if (this.testIterations === -1) {
      return -1; // 无限循环
    }
    if (this.testIterations < -1) {
      return 1; // 小于 -1 取默认值
    }
    if (this.testIterations === 0) {
      return 0; // 0 次
    }
    if (this.testIterations > 0 && this.testIterations < 1) {
      return 0; // 0.x 向下取整为 0
    }
    if (this.testIterations % 1 !== 0) {
      return Math.floor(this.testIterations); // 浮点数向下取整
    }
    return this.testIterations;
  }
}
