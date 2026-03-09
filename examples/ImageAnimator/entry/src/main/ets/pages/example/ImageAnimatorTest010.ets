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
 * ImageAnimatorTest010 - duration 边界值测试
 * ========================================
 * 
 * 测试功能说明:
 * 本测试验证 ImageAnimator 组件 duration 属性的边界值行为
 * 
 * 涉及的 ImageAnimator API:
 * 1. duration(value: number) - 播放时长
 * 2. 边界值处理：0, 负数，过小值
 * 
 * ========================================
 * API 文档说明
 * ========================================
 * 根据官方文档:
 * - value 为 0 时，不播放图片
 * - value 平均分配给单张图片的播放时长小于一帧时间，将导致播放异常
 * - 设置为负数时，取默认值 (1000ms)
 * 
 * ========================================
 * 测试用例
 * ========================================
 * 1. duration = 0: 验证不播放
 * 2. duration = -100: 验证取默认值
 * 3. duration = 1: 验证过小值 (可能播放异常)
 * 4. duration = 100: 验证最小可用值
 * 5. duration = 1000: 验证正常值 (基准)
 * 6. duration = 10000: 验证大值
 */

@Entry
@Component
struct ImageAnimatorTest010 {
  @State testDuration: number = 1000;
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State currentStatus: string = 'Initial';
  @State testResult: string = '等待测试...';
  @State isPlaying: boolean = false;

  // 测试用例数据
  private testCases: Array<{
    name: string;
    value: number;
    expected: string;
  }> = [
    { name: 'duration = 0', value: 0, expected: '不播放' },
    { name: 'duration = -100', value: -100, expected: '取默认值 1000ms' },
    { name: 'duration = 1', value: 1, expected: '可能播放异常' },
    { name: 'duration = 100', value: 100, expected: '最小可用值' },
    { name: 'duration = 1000', value: 1000, expected: '正常值' },
    { name: 'duration = 10000', value: 10000, expected: '大值 (慢速)' }
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('duration 边界值测试')
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

      Text('• value 为 0 时，不播放图片')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• value 平均分配给单张图片的播放时长小于一帧时间，将导致播放异常')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 设置为负数时，取默认值 (1000ms)')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 单位：毫秒 (ms)')
        .fontSize(14)
        .fontColor(0x999999)

      Text('• 默认值：1000ms')
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
      Text('测试区域 (当前 duration: ' + this.testDuration + 'ms)')
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
        .duration(this.testDuration)
        .state(this.animationState)
        .iterations(1)
        .width(300)
        .height(200)
        .border({ width: 2, color: Color.Blue })
        .onStart(() => {
          this.currentStatus = 'Started';
          this.isPlaying = true;
          this.testResult = '播放开始 (duration=' + this.testDuration + 'ms)';
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
          this.testResult = '播放完成 (duration=' + this.testDuration + 'ms)';
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
          Text('每帧时长:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text((this.testDuration > 0 ? this.testDuration / 4 : 0).toFixed(0) + 'ms')
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Blue)
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

      ForEach(this.testCases, (testCase: { name: string; value: number; expected: string }) => {
        Row({ space: 15 }) {
          Button(testCase.name)
            .fontSize(14)
            .backgroundColor(this.testDuration === testCase.value ? Color.Blue : Color.LightGray)
            .onClick(() => {
              this.testDuration = testCase.value;
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
        .backgroundColor(this.testDuration === testCase.value ? 0xE3F2FD : 0xF5F5F5)
        .borderRadius(10)
      })
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
            this.testResult = '开始播放 (duration=' + this.testDuration + 'ms)';
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
}
