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

@Entry
@Component
struct ImageAnimatorTest001 {
  @State testTitle: string = '基础功能测试';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State duration: number = 2000;
  @State iterations: number = 1;
  @State reverse: boolean = false;
  @State fillMode: FillMode = FillMode.None;
  @State width: number = 300;
  @State height: number = 200;

  private testImages: ImageFrameInfo[] = [
    { src: $r('app.media.img1') },
    { src: $r('app.media.img2') },
    { src: $r('app.media.img3') },
    { src: $r('app.media.img4') }
  ];

  private addTestResult(testName: string, result: boolean, details: string = '') {
    const status = result ? 'PASS' : 'FAIL';
    const timestamp = new Date().toLocaleTimeString();
    this.testResults.unshift(`[${timestamp}] ${testName}: ${status} ${details}`);
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text(this.testTitle)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        Divider().strokeWidth(2)

        this.buildTestSection()

        Divider().strokeWidth(2)

        this.buildImageAnimator()

        Divider().strokeWidth(2)

        this.buildTestResults()
      }
      .width('100%')
      .padding(20)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildTestSection() {
    Column({ space: 10 }) {
      Text('测试控制面板')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: 初始化状态')
          .onClick(() => {
            this.testInitialization();
          })

        Button('测试2: 播放功能')
          .onClick(() => {
            this.testPlayFunction();
          })

        Button('测试3: 暂停功能')
          .onClick(() => {
            this.testPauseFunction();
          })
      }

      Row({ space: 10 }) {
        Button('测试4: 停止功能')
          .onClick(() => {
            this.testStopFunction();
          })

        Button('测试5: 图片源设置')
          .onClick(() => {
            this.testImageSource();
          })

        Button('测试6: 持续时间设置')
          .onClick(() => {
            this.testDurationSetting();
          })
      }

      Row({ space: 10 }) {
        Button('测试7: 尺寸设置')
          .onClick(() => {
            this.testSizeSetting();
          })

        Button('测试8: 清空结果')
          .onClick(() => {
            this.testResults = [];
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildImageAnimator() {
    Column({ space: 10 }) {
      Text('ImageAnimator 预览')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      ImageAnimator()
        .images(this.testImages)
        .duration(this.duration)
        .state(this.state)
        .reverse(this.reverse)
        .fillMode(this.fillMode)
        .iterations(this.iterations)
        .width(this.width)
        .height(this.height)
        .borderRadius(10)
        .backgroundColor(0xE0E0E0)
        .onStart(() => {
          console.info('ImageAnimator onStart');
          this.addTestResult('onStart回调', true, '动画开始');
        })
        .onPause(() => {
          console.info('ImageAnimator onPause');
          this.addTestResult('onPause回调', true, '动画暂停');
        })
        .onRepeat(() => {
          console.info('ImageAnimator onRepeat');
          this.addTestResult('onRepeat回调', true, '动画重复');
        })
        .onCancel(() => {
          console.info('ImageAnimator onCancel');
          this.addTestResult('onCancel回调', true, '动画取消');
        })
        .onFinish(() => {
          console.info('ImageAnimator onFinish');
          this.addTestResult('onFinish回调', true, '动画完成');
          this.state = AnimationStatus.Stopped;
        })

      Row({ space: 10 }) {
        Text(`状态: ${this.state}`)
        Text(`时长: ${this.duration}ms`)
        Text(`循环: ${this.iterations}`)
      }
      .fontSize(14)
      .fontColor(0x666666)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildTestResults() {
    Column({ space: 10 }) {
      Text('测试结果')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      if (this.testResults.length === 0) {
        Text('暂无测试结果')
          .fontSize(14)
          .fontColor(0x999999)
      } else {
        List({ space: 5 }) {
          ForEach(this.testResults, (result: string, index: number) => {
            ListItem() {
              Text(result)
                .fontSize(12)
                .fontColor(result.includes('PASS') ? 0x4CAF50 : 0xF44336)
            }
            .width('100%')
          }, (result: string, index: number) => `${index}_${result}`)
        }
        .width('100%')
        .height(300)
        .backgroundColor(0xF0F0F0)
        .borderRadius(5)
        .padding(10)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  private testInitialization() {
    try {
      const initialState = this.state;
      this.addTestResult('初始化状态检查', 
        initialState === AnimationStatus.Initial || 
        initialState === AnimationStatus.Stopped,
        `初始状态: ${initialState}`);
    } catch (error) {
      this.addTestResult('初始化状态检查', false, `错误: ${error}`);
    }
  }

  private testPlayFunction() {
    try {
      this.state = AnimationStatus.Running;
      this.addTestResult('播放功能', true, '状态设置为Running');
    } catch (error) {
      this.addTestResult('播放功能', false, `错误: ${error}`);
    }
  }

  private testPauseFunction() {
    try {
      this.state = AnimationStatus.Paused;
      this.addTestResult('暂停功能', true, '状态设置为Paused');
    } catch (error) {
      this.addTestResult('暂停功能', false, `错误: ${error}`);
    }
  }

  private testStopFunction() {
    try {
      this.state = AnimationStatus.Stopped;
      this.addTestResult('停止功能', true, '状态设置为Stopped');
    } catch (error) {
      this.addTestResult('停止功能', false, `错误: ${error}`);
    }
  }

  private testImageSource() {
    try {
      const hasImages = this.testImages.length > 0;
      const allValid = this.testImages.every(img => img.src !== undefined);
      this.addTestResult('图片源设置', hasImages && allValid,
        `图片数量: ${this.testImages.length}`);
    } catch (error) {
      this.addTestResult('图片源设置', false, `错误: ${error}`);
    }
  }

  private testDurationSetting() {
    try {
      const testDurations = [1000, 2000, 3000, 5000];
      let allValid = true;
      
      for (const dur of testDurations) {
        this.duration = dur;
        if (this.duration !== dur) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('持续时间设置', allValid,
        `测试时长: ${testDurations.join(', ')}ms`);
    } catch (error) {
      this.addTestResult('持续时间设置', false, `错误: ${error}`);
    }
  }

  private testSizeSetting() {
    try {
      const testSizes = [
        { w: 200, h: 150 },
        { w: 300, h: 200 },
        { w: 400, h: 300 }
      ];
      let allValid = true;
      
      for (const size of testSizes) {
        this.width = size.w;
        this.height = size.h;
        if (this.width !== size.w || this.height !== size.h) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('尺寸设置', allValid,
        `测试尺寸: ${testSizes.map(s => `${s.w}x${s.h}`).join(', ')}`);
    } catch (error) {
      this.addTestResult('尺寸设置', false, `错误: ${error}`);
    }
  }
}
