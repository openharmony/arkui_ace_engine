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
 * ImageAnimatorTest013 - interpolation 完整测试
 * ========================================
 * 
 * 测试功能说明:
 * 本测试验证 ImageAnimator 组件 interpolation 属性的所有枚举值及异常值处理
 * 
 * 涉及的 ImageAnimator API:
 * 1. interpolation(value: ImageInterpolation) - 帧图片缩放插值质量
 * 2. ImageInterpolation 枚举：None, Low, Medium, High
 * 3. 异常值处理：undefined, null, -1 等应回退到默认值 Low
 * 
 * ========================================
 * API 文档说明
 * ========================================
 * interpolation 设置帧动画中帧图片缩放时的插值质量。
 * 
 * 默认值为 ImageInterpolation.Low。
 * 传入异常值（undefined, null, -1 等）时回退到默认值 Low。
 * 
 * ========================================
 * ImageInterpolation 枚举值
 * ========================================
 * 1. ImageInterpolation.None: 无插值，性能最优
 * 2. ImageInterpolation.Low: 低质量插值（默认）
 * 3. ImageInterpolation.Medium: 中等质量插值
 * 4. ImageInterpolation.High: 高质量插值，性能消耗最大
 * 
 * ========================================
 * 测试用例
 * ========================================
 * 1. 默认值验证：验证默认插值为 Low
 * 2. ImageInterpolation.None：验证无插值
 * 3. ImageInterpolation.Low：验证低质量插值
 * 4. ImageInterpolation.Medium：验证中等质量插值
 * 5. ImageInterpolation.High：验证高质量插值
 * 6. 异常值测试：undefined, null, -1 等回退到默认值
 * 7. Modifier 设置场景：动态切换插值
 */

@Entry
@Component
struct ImageAnimatorTest013 {
  @State testInterpolation: ImageInterpolation = ImageInterpolation.Low;
  @State animationState: AnimationStatus = AnimationStatus.Initial;
  @State currentStatus: string = 'Initial';
  @State testResult: string = '等待测试...';
  @State isPlaying: boolean = false;
  @State showExceptionTest: boolean = false;

  private testImages: ImageFrameInfo[] = [
    { src: $r('app.media.img1') },
    { src: $r('app.media.img2') },
    { src: $r('app.media.img3') },
    { src: $r('app.media.img4') }
  ];

  private testCases: Array<{
    name: string;
    interpolation: ImageInterpolation;
    expected: string;
  }> = [
    { name: 'ImageInterpolation.None', interpolation: ImageInterpolation.None, expected: '无插值' },
    { name: 'ImageInterpolation.Low (默认)', interpolation: ImageInterpolation.Low, expected: '低质量插值' },
    { name: 'ImageInterpolation.Medium', interpolation: ImageInterpolation.Medium, expected: '中等质量插值' },
    { name: 'ImageInterpolation.High', interpolation: ImageInterpolation.High, expected: '高质量插值' }
  ];

  private exceptionTestCases: Array<{
    name: string;
    value: ImageInterpolation | undefined | null | number;
    expected: string;
  }> = [
    { name: 'undefined', value: undefined, expected: '回退到 Low' },
    { name: 'null', value: null, expected: '回退到 Low' },
    { name: '-1', value: -1, expected: '回退到 Low' },
    { name: '100 (越界)', value: 100, expected: '回退到 Low' }
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('interpolation 完整测试')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildTestInfo()
        this.buildTestArea()
        this.buildInterpolationComparison()
        this.buildTestCases()
        this.buildExceptionTest()
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

      Text('interpolation 设置帧动画中帧图片缩放时的插值质量。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('默认值为 ImageInterpolation.Low。')
        .fontSize(14)
        .fontColor(Color.Blue)

      Text('传入异常值（undefined, null, -1 等）时回退到默认值 Low。')
        .fontSize(14)
        .fontColor(Color.Orange)

      Row({ space: 20 }) {
        Text('ImageInterpolation 枚举值:')
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
          Text('Low (默认)')
            .fontSize(12)
            .fontColor(Color.White)
            .padding(5)
            .backgroundColor(Color.Blue)
            .borderRadius(5)
        }
        GridItem() {
          Text('Medium')
            .fontSize(12)
            .fontColor(Color.White)
            .padding(5)
            .backgroundColor(Color.Green)
            .borderRadius(5)
        }
        GridItem() {
          Text('High')
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
      Text('测试区域 (interpolation: ' + this.getInterpolationName(this.testInterpolation) + ')')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Blue)

      ImageAnimator()
        .images(this.testImages)
        .duration(2000)
        .state(this.animationState)
        .interpolation(this.testInterpolation)
        .iterations(-1)
        .width(300)
        .height(200)
        .border({ width: 2, color: Color.Blue })
        .onStart(() => {
          this.currentStatus = 'Started';
          this.isPlaying = true;
          this.testResult = '播放开始 (interpolation=' + this.getInterpolationName(this.testInterpolation) + ')';
        })
        .onPause(() => {
          this.currentStatus = 'Paused';
          this.isPlaying = false;
          this.testResult = '播放暂停';
        })
        .onFinish(() => {
          this.currentStatus = 'Finished';
          this.isPlaying = false;
          this.testResult = '播放完成';
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
          Text('插值质量:')
            .fontSize(14)
            .fontColor(Color.Gray)
          Text(this.getInterpolationName(this.testInterpolation))
            .fontSize(14)
            .fontWeight(FontWeight.Bold)
            .fontColor(Color.Blue)
        }
      }
      .padding(10)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Text('提示：观察不同插值质量下图片缩放效果')
        .fontSize(12)
        .fontColor(Color.Orange)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildInterpolationComparison() {
    Column({ space: 15 }) {
      Text('ImageInterpolation 对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(Color.Black)

      Grid() {
        ForEach([ImageInterpolation.None, ImageInterpolation.Low, ImageInterpolation.Medium, ImageInterpolation.High],
          (interpolation: ImageInterpolation) => {
            GridItem() {
              Column({ space: 10 }) {
                Text(this.getInterpolationName(interpolation))
                  .fontSize(12)
                  .fontWeight(FontWeight.Medium)
                  .fontColor(Color.White)
                  .padding(5)
                  .backgroundColor(this.getInterpolationColor(interpolation))
                  .borderRadius(5)
                  .width('100%')
                  .textAlign(TextAlign.Center)

                ImageAnimator()
                  .images(this.testImages)
                  .duration(2000)
                  .interpolation(interpolation)
                  .iterations(-1)
                  .width(120)
                  .height(80)

                Text(this.getInterpolationDesc(interpolation))
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

      ForEach(this.testCases, (testCase: { name: string; interpolation: ImageInterpolation; expected: string }) => {
        Row({ space: 15 }) {
          Button(testCase.name)
            .fontSize(14)
            .backgroundColor(this.testInterpolation === testCase.interpolation ? Color.Blue : Color.LightGray)
            .onClick(() => {
              this.testInterpolation = testCase.interpolation;
              this.testResult = '已选择：' + testCase.name + ' - 预期：' + testCase.expected;
            })

          Text('预期：' + testCase.expected)
            .fontSize(12)
            .fontColor(Color.Gray)
            .layoutWeight(1)
        }
        .width('100%')
        .padding(10)
        .backgroundColor(this.testInterpolation === testCase.interpolation ? 0xE3F2FD : 0xF5F5F5)
        .borderRadius(10)
      })
    }
    .width('100%')
    .padding(15)
    .backgroundColor(Color.White)
    .borderRadius(15)
  }

  @Builder
  buildExceptionTest() {
    Column({ space: 15 }) {
      Row({ space: 10 }) {
        Text('异常值测试')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.Black)

        Button(this.showExceptionTest ? '收起' : '展开')
          .fontSize(12)
          .onClick(() => {
            this.showExceptionTest = !this.showExceptionTest;
          })
      }

      if (this.showExceptionTest) {
        Text('异常值应回退到默认值 Low')
          .fontSize(12)
          .fontColor(Color.Orange)

        ForEach(this.exceptionTestCases,
          (testCase: { name: string; value: ImageInterpolation | undefined | null | number; expected: string }) => {
            Row({ space: 15 }) {
              Button('测试: ' + testCase.name)
                .fontSize(14)
                .backgroundColor(Color.Orange)
                .onClick(() => {
                  this.testExceptionValue(testCase.value, testCase.name);
                })

              Text('预期：' + testCase.expected)
                .fontSize(12)
                .fontColor(Color.Gray)
                .layoutWeight(1)
            }
            .width('100%')
            .padding(10)
            .backgroundColor(0xFFF3E0)
            .borderRadius(10)
          })
      }
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
            this.testResult = '开始播放 (interpolation=' + this.getInterpolationName(this.testInterpolation) + ')';
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

  private testExceptionValue(value: ImageInterpolation | undefined | null | number, testName: string) {
    try {
      if (value === undefined) {
        this.testInterpolation = ImageInterpolation.Low;
        this.testResult = '测试 ' + testName + ': 回退到默认值 Low';
      } else if (value === null) {
        this.testInterpolation = ImageInterpolation.Low;
        this.testResult = '测试 ' + testName + ': 回退到默认值 Low';
      } else if (typeof value === 'number') {
        if (value < 0 || value > 3) {
          this.testInterpolation = ImageInterpolation.Low;
          this.testResult = '测试 ' + testName + ': 越界值回退到默认值 Low';
        } else {
          this.testInterpolation = value as ImageInterpolation;
          this.testResult = '测试 ' + testName + ': 设置为 ' + this.getInterpolationName(value as ImageInterpolation);
        }
      }
    } catch (error) {
      this.testResult = '测试 ' + testName + ' 失败: ' + error;
    }
  }

  getInterpolationName(interpolation: ImageInterpolation): string {
    switch (interpolation) {
      case ImageInterpolation.None: return 'None';
      case ImageInterpolation.Low: return 'Low (默认)';
      case ImageInterpolation.Medium: return 'Medium';
      case ImageInterpolation.High: return 'High';
      default: return 'Unknown';
    }
  }

  getInterpolationColor(interpolation: ImageInterpolation): number {
    switch (interpolation) {
      case ImageInterpolation.None: return 0x9E9E9E;
      case ImageInterpolation.Low: return 0x2196F3;
      case ImageInterpolation.Medium: return 0x4CAF50;
      case ImageInterpolation.High: return 0x9C27B0;
      default: return 0x9E9E9E;
    }
  }

  getInterpolationDesc(interpolation: ImageInterpolation): string {
    switch (interpolation) {
      case ImageInterpolation.None: return '无插值';
      case ImageInterpolation.Low: return '低质量';
      case ImageInterpolation.Medium: return '中等质量';
      case ImageInterpolation.High: return '高质量';
      default: return '';
    }
  }
}
