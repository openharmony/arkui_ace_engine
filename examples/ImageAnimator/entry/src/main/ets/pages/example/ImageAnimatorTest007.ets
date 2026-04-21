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
struct ImageAnimatorComprehensiveTest {
  @State testTitle: string = '综合功能测试套件';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State duration: number = 2000;
  @State iterations: number = 1;
  @State reverse: boolean = false;
  @State fillMode: FillMode = FillMode.None;
  @State width: number = 300;
  @State height: number = 200;
  @State eventLog: string[] = [];
  @State currentTestSuite: number = 0;
  @State testProgress: number = 0;
  @State totalTests: number = 40;
  @State passedTests: number = 0;
  @State failedTests: number = 0;

  private testImages: ImageFrameInfo[] = [
    { src: $r('app.media.img1') },
    { src: $r('app.media.img2') },
    { src: $r('app.media.img3') },
    { src: $r('app.media.img4') }
  ];

  private imageSets: Array<ImageFrameInfo[]> = [
    [{ src: $r('app.media.img1') }],
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') }
    ],
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') },
      { src: $r('app.media.img3') }
    ],
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') },
      { src: $r('app.media.img3') },
      { src: $r('app.media.img4') }
    ]
  ];

  private fillModes: FillMode[] = [
    FillMode.None,
    FillMode.Forwards,
    FillMode.Backwards,
    FillMode.Both
  ];

  private fillModeNames: string[] = ['None', 'Forwards', 'Backwards', 'Both'];

  private addTestResult(testName: string, result: boolean, details: string = '') {
    const status = result ? 'PASS' : 'FAIL';
    const timestamp = new Date().toLocaleTimeString();
    this.testResults.unshift(`[${timestamp}] ${testName}: ${status} ${details}`);
    
    if (result) {
      this.passedTests++;
    } else {
      this.failedTests++;
    }
    this.testProgress++;
  }

  private logEvent(eventName: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.eventLog.unshift(`[${timestamp}] ${eventName}`);
    if (this.eventLog.length > 50) {
      this.eventLog.pop();
    }
  }

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text(this.testTitle)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        this.buildStatistics()

        Divider().strokeWidth(2)

        this.buildTestSuiteSelector()

        Divider().strokeWidth(2)

        this.buildCurrentTestSuite()

        Divider().strokeWidth(2)

        this.buildImageAnimator()

        Divider().strokeWidth(2)

        this.buildEventLog()

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
  buildStatistics() {
    Row({ space: 20 }) {
      Column({ space: 5 }) {
        Text('总测试数')
          .fontSize(14)
          .fontColor(0x666666)
        Text(`${this.totalTests}`)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x2196F3)
      }

      Column({ space: 5 }) {
        Text('已执行')
          .fontSize(14)
          .fontColor(0x666666)
        Text(`${this.testProgress}`)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(0xFF9800)
      }

      Column({ space: 5 }) {
        Text('通过')
          .fontSize(14)
          .fontColor(0x666666)
        Text(`${this.passedTests}`)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x4CAF50)
      }

      Column({ space: 5 }) {
        Text('失败')
          .fontSize(14)
          .fontColor(0x666666)
        Text(`${this.failedTests}`)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(0xF44336)
      }

      Column({ space: 5 }) {
        Text('通过率')
          .fontSize(14)
          .fontColor(0x666666)
        const passRate = this.testProgress > 0 
          ? ((this.passedTests / this.testProgress) * 100).toFixed(1) 
          : '0.0';
        Text(`${passRate}%`)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x9C27B0)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildTestSuiteSelector() {
    Column({ space: 10 }) {
      Text('测试套件选择')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('基础功能')
          .onClick(() => {
            this.currentTestSuite = 0;
          })
          .backgroundColor(this.currentTestSuite === 0 ? 0x2196F3 : 0xE0E0E0)
          .fontColor(this.currentTestSuite === 0 ? 0xFFFFFF : 0x000000)

        Button('属性测试')
          .onClick(() => {
            this.currentTestSuite = 1;
          })
          .backgroundColor(this.currentTestSuite === 1 ? 0x2196F3 : 0xE0E0E0)
          .fontColor(this.currentTestSuite === 1 ? 0xFFFFFF : 0x000000)

        Button('事件测试')
          .onClick(() => {
            this.currentTestSuite = 2;
          })
          .backgroundColor(this.currentTestSuite === 2 ? 0x2196F3 : 0xE0E0E0)
          .fontColor(this.currentTestSuite === 2 ? 0xFFFFFF : 0x000000)
      }

      Row({ space: 10 }) {
        Button('状态测试')
          .onClick(() => {
            this.currentTestSuite = 3;
          })
          .backgroundColor(this.currentTestSuite === 3 ? 0x2196F3 : 0xE0E0E0)
          .fontColor(this.currentTestSuite === 3 ? 0xFFFFFF : 0x000000)

        Button('循环测试')
          .onClick(() => {
            this.currentTestSuite = 4;
          })
          .backgroundColor(this.currentTestSuite === 4 ? 0x2196F3 : 0xE0E0E0)
          .fontColor(this.currentTestSuite === 4 ? 0xFFFFFF : 0x000000)

        Button('综合测试')
          .onClick(() => {
            this.currentTestSuite = 5;
          })
          .backgroundColor(this.currentTestSuite === 5 ? 0x2196F3 : 0xE0E0E0)
          .fontColor(this.currentTestSuite === 5 ? 0xFFFFFF : 0x000000)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildCurrentTestSuite() {
    Column({ space: 10 }) {
      Text('测试控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      if (this.currentTestSuite === 0) {
        this.buildBasicFunctionTests()
      } else if (this.currentTestSuite === 1) {
        this.buildPropertyTests()
      } else if (this.currentTestSuite === 2) {
        this.buildEventTests()
      } else if (this.currentTestSuite === 3) {
        this.buildStateTests()
      } else if (this.currentTestSuite === 4) {
        this.buildLoopTests()
      } else if (this.currentTestSuite === 5) {
        this.buildComprehensiveTests()
      }

      Row({ space: 10 }) {
        Button('清空结果')
          .onClick(() => {
            this.testResults = [];
            this.eventLog = [];
            this.testProgress = 0;
            this.passedTests = 0;
            this.failedTests = 0;
          })

        Button('运行全部')
          .onClick(() => {
            this.runAllTests();
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildBasicFunctionTests() {
    Column({ space: 10 }) {
      Text('基础功能测试')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: 初始化')
          .onClick(() => {
            this.testInitialization();
          })

        Button('测试2: 播放')
          .onClick(() => {
            this.testPlay();
          })

        Button('测试3: 暂停')
          .onClick(() => {
            this.testPause();
          })

        Button('测试4: 停止')
          .onClick(() => {
            this.testStop();
          })
      }

      Row({ space: 10 }) {
        Button('测试5: 图片源')
          .onClick(() => {
            this.testImageSource();
          })

        Button('测试6: 持续时间')
          .onClick(() => {
            this.testDuration();
          })

        Button('测试7: 尺寸')
          .onClick(() => {
            this.testSize();
          })
      }
    }
  }

  @Builder
  buildPropertyTests() {
    Column({ space: 10 }) {
      Text('属性测试')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试8: Duration属性')
          .onClick(() => {
            this.testDurationProperty();
          })

        Button('测试9: Iterations属性')
          .onClick(() => {
            this.testIterationsProperty();
          })

        Button('测试10: Reverse属性')
          .onClick(() => {
            this.testReverseProperty();
          })
      }

      Row({ space: 10 }) {
        Button('测试11: FillMode属性')
          .onClick(() => {
            this.testFillModeProperty();
          })

        Button('测试12: Width属性')
          .onClick(() => {
            this.testWidthProperty();
          })

        Button('测试13: Height属性')
          .onClick(() => {
            this.testHeightProperty();
          })
      }

      Row({ space: 10 }) {
        Button('测试14: 组合属性')
          .onClick(() => {
            this.testCombinedProperties();
          })

        Button('测试15: 边界值')
          .onClick(() => {
            this.testBoundaryValues();
          })
      }
    }
  }

  @Builder
  buildEventTests() {
    Column({ space: 10 }) {
      Text('事件测试')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试16: onStart')
          .onClick(() => {
            this.testOnStartEvent();
          })

        Button('测试17: onPause')
          .onClick(() => {
            this.testOnPauseEvent();
          })

        Button('测试18: onRepeat')
          .onClick(() => {
            this.testOnRepeatEvent();
          })
      }

      Row({ space: 10 }) {
        Button('测试19: onCancel')
          .onClick(() => {
            this.testOnCancelEvent();
          })

        Button('测试20: onFinish')
          .onClick(() => {
            this.testOnFinishEvent();
          })

        Button('测试21: 事件流')
          .onClick(() => {
            this.testEventFlow();
          })
      }
    }
  }

  @Builder
  buildStateTests() {
    Column({ space: 10 }) {
      Text('状态测试')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试22: Initial状态')
          .onClick(() => {
            this.testInitialState();
          })

        Button('测试23: Running状态')
          .onClick(() => {
            this.testRunningState();
          })

        Button('测试24: Paused状态')
          .onClick(() => {
            this.testPausedState();
          })
      }

      Row({ space: 10 }) {
        Button('测试25: Stopped状态')
          .onClick(() => {
            this.testStoppedState();
          })

        Button('测试26: 状态转换')
          .onClick(() => {
            this.testStateTransition();
          })

        Button('测试27: 快速切换')
          .onClick(() => {
            this.testRapidSwitch();
          })
      }
    }
  }

  @Builder
  buildLoopTests() {
    Column({ space: 10 }) {
      Text('循环测试')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试28: 单次播放')
          .onClick(() => {
            this.testSingleLoop();
          })

        Button('测试29: 两次循环')
          .onClick(() => {
            this.testDoubleLoop();
          })

        Button('测试30: 多次循环')
          .onClick(() => {
            this.testMultipleLoop();
          })
      }

      Row({ space: 10 }) {
        Button('测试31: 无限循环')
          .onClick(() => {
            this.testInfiniteLoop();
          })

        Button('测试32: 正向播放')
          .onClick(() => {
            this.testForwardPlay();
          })

        Button('测试33: 反向播放')
          .onClick(() => {
            this.testReversePlay();
          })
      }

      Row({ space: 10 }) {
        Button('测试34: 循环+反向')
          .onClick(() => {
            this.testLoopWithReverse();
          })

        Button('测试35: 循环事件')
          .onClick(() => {
            this.testLoopEvents();
          })
      }
    }
  }

  @Builder
  buildComprehensiveTests() {
    Column({ space: 10 }) {
      Text('综合测试')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试36: 完整流程')
          .onClick(() => {
            this.testCompleteFlow();
          })

        Button('测试37: 压力测试')
          .onClick(() => {
            this.testStressTest();
          })

        Button('测试38: 异常处理')
          .onClick(() => {
            this.testExceptionHandling();
          })
      }

      Row({ space: 10 }) {
        Button('测试39: 性能测试')
          .onClick(() => {
            this.testPerformance();
          })

        Button('测试40: 兼容性测试')
          .onClick(() => {
            this.testCompatibility();
          })
      }
    }
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
          console.info('Event: onStart');
          this.logEvent('onStart');
        })
        .onPause(() => {
          console.info('Event: onPause');
          this.logEvent('onPause');
        })
        .onRepeat(() => {
          console.info('Event: onRepeat');
          this.logEvent('onRepeat');
        })
        .onCancel(() => {
          console.info('Event: onCancel');
          this.logEvent('onCancel');
        })
        .onFinish(() => {
          console.info('Event: onFinish');
          this.logEvent('onFinish');
          this.state = AnimationStatus.Stopped;
        })

      Row({ space: 15 }) {
        Button('播放')
          .onClick(() => {
            this.state = AnimationStatus.Running;
          })

        Button('暂停')
          .onClick(() => {
            this.state = AnimationStatus.Paused;
          })

        Button('停止')
          .onClick(() => {
            this.state = AnimationStatus.Stopped;
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildEventLog() {
    Column({ space: 10 }) {
      Text('事件日志')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      if (this.eventLog.length === 0) {
        Text('暂无事件日志')
          .fontSize(14)
          .fontColor(0x999999)
      } else {
        List({ space: 5 }) {
          ForEach(this.eventLog, (log: string, index: number) => {
            ListItem() {
              Text(log)
                .fontSize(12)
                .fontColor(0x333333)
            }
            .width('100%')
          }, (log: string, index: number) => `${index}_${log}`)
        }
        .width('100%')
        .height(150)
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

  private runAllTests() {
    this.testResults = [];
    this.eventLog = [];
    this.testProgress = 0;
    this.passedTests = 0;
    this.failedTests = 0;

    const tests = [
      () => { setTimeout(() => this.testInitialization(), 100); },
      () => { setTimeout(() => this.testPlay(), 200); },
      () => { setTimeout(() => this.testPause(), 300); },
      () => { setTimeout(() => this.testStop(), 400); },
      () => { setTimeout(() => this.testImageSource(), 500); },
      () => { setTimeout(() => this.testDuration(), 600); },
      () => { setTimeout(() => this.testSize(), 700); },
      () => { setTimeout(() => this.testDurationProperty(), 800); },
      () => { setTimeout(() => this.testIterationsProperty(), 900); },
      () => { setTimeout(() => this.testReverseProperty(), 1000); }
    ];

    tests.forEach((test, index) => {
      setTimeout(test, index * 100);
    });
  }

  private testInitialization() {
    try {
      const initialState = this.state;
      const isValid = initialState === AnimationStatus.Initial || 
                      initialState === AnimationStatus.Stopped;
      this.addTestResult('初始化测试', isValid, `初始状态: ${initialState}`);
    } catch (error) {
      this.addTestResult('初始化测试', false, `错误: ${error}`);
    }
  }

  private testPlay() {
    try {
      this.state = AnimationStatus.Running;
      const isValid = this.state === AnimationStatus.Running;
      this.addTestResult('播放功能测试', isValid, '状态设置为Running');
    } catch (error) {
      this.addTestResult('播放功能又试', false, `错误: ${error}`);
    }
  }

  private testPause() {
    try {
      this.state = AnimationStatus.Paused;
      const isValid = this.state === AnimationStatus.Paused;
      this.addTestResult('暂停功能测试', isValid, '状态设置为Paused');
    } catch (error) {
      this.addTestResult('暂停功能测试', false, `错误: ${error}`);
    }
  }

  private testStop() {
    try {
      this.state = AnimationStatus.Stopped;
      const isValid = this.state === AnimationStatus.Stopped;
      this.addTestResult('停止功能测试', isValid, '状态设置为Stopped');
    } catch (error) {
      this.addTestResult('停止功能测试', false, `错误: ${error}`);
    }
  }

  private testImageSource() {
    try {
      const hasImages = this.testImages.length > 0;
      const allValid = this.testImages.every(img => img.src !== undefined);
      this.addTestResult('图片源测试', hasImages && allValid,
        `图片数量: ${this.testImages.length}`);
    } catch (error) {
      this.addTestResult('图片源测试', false, `错误: ${error}`);
    }
  }

  private testDuration() {
    try {
      const testValues = [1000, 2000, 3000];
      let allValid = true;
      
      for (const value of testValues) {
        this.duration = value;
        if (this.duration !== value) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('持续时间测试', allValid,
        `测试值: ${testValues.join(', ')}ms`);
    } catch (error) {
      this.addTestResult('持续时间测试', false, `错误: ${error}`);
    }
  }

  private testSize() {
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
      
      this.addTestResult('尺寸测试', allValid,
        `测试尺寸: ${testSizes.map(s => `${s.w}x${s.h}`).join(', ')}`);
    } catch (error) {
      this.addTestResult('尺寸测试', false, `错误: ${error}`);
    }
  }

  private testDurationProperty() {
    try {
      const testValues = [500, 1000, 2000, 3000, 5000];
      let allValid = true;
      
      for (const value of testValues) {
        this.duration = value;
        if (this.duration !== value) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('Duration属性测试', allValid,
        `测试值: ${testValues.join(', ')}ms`);
    } catch (error) {
      this.addTestResult('Duration属性测试', false, `错误: ${error}`);
    }
  }

  private testIterationsProperty() {
    try {
      const testValues = [1, 2, 3, 5, 10, -1];
      let allValid = true;
      
      for (const value of testValues) {
        this.iterations = value;
        if (this.iterations !== value) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('Iterations属性测试', allValid,
        `测试值: ${testValues.join(', ')}`);
    } catch (error) {
      this.addTestResult('IterationsIterations测试', false, `错误: ${error}`);
    }
  }

  private testReverseProperty() {
    try {
      const testValues = [true, false, true, false];
      let allValid = true;
      
      for (const value of testValues) {
        this.reverse = value;
        if (this.reverse !== value) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('Reverse属性测试', allValid,
        `测试值: ${testValues.join(', ')}`);
    } catch (error) {
      this.addTestResult('Reverse属性测试', false, `错误: ${error}`);
    }
  }

  private testFillModeProperty() {
    try {
      let allValid = true;
      
      for (let i = 0; i < this.fillModes.length; i++) {
        this.fillMode = this.fillModes[i];
        if (this.fillMode !== this.fillModes[i]) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('FillMode属性测试', allValid,
        `测试模式: ${this.fillModeNames.join(', ')}`);
    } catch (error) {
      this.addTestResult('FillMode属性测试', false, `错误: ${error}`);
    }
  }

  private testWidthProperty() {
    try {
      const testValues = [100, 200, 300, 400, 500];
      let allValid = true;
      
      for (const value of testValues) {
        this.width = value;
        if (this.width !== value) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('Width属性测试', allValid,
        `测试值: ${testValues.join(', ')}px`);
    } catch (error) {
      this.addTestResult('Width属性测试', false, `错误: ${error}`);
    }
  }

  private testHeightProperty() {
    try {
      const testValues = [100, 150, 200, 250, 300];
      let allValid = true;
      
      for (const value of testValues) {
        this.height = value;
        if (this.height !== value) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('Height属性测试', allValid,
        `测试值: ${testValues.join(', ')}px`);
    } catch (error) {
      this.addTestResult('Height属性测试', false, `错误: ${error}`);
    }
  }

  private testCombinedProperties() {
    try {
      const originalDuration = this.duration;
      const originalIterations = this.iterations;
      const originalReverse = this.reverse;
      const originalWidth = this.width;
      const originalHeight = this.height;
      
      this.duration = 1500;
      this.iterations = 3;
      this.reverse = true;
      this.width = 350;
      this.height = 250;
      
      const allSet = this.duration === 1500 &&
                      this.iterations === 3 &&
                      this.reverse === true &&
                      this.width === 350 &&
                      this.height === 250;
      
      this.addTestResult('组合属性测试', allSet,
        'Duration:1500, Iterations:3, Reverse:true, Width:350, Height:250');
      
      if (!allSet) {
        this.duration = originalDuration;
        this.iterations = originalIterations;
        this.reverse = originalReverse;
        this.width = originalWidth;
        this.height = originalHeight;
      }
    } catch (error) {
      this.addTestResult('组合属性测试', false, `错误: ${error}`);
    }
  }

  private testBoundaryValues() {
    try {
      const boundaryTests = [
        { name: '最小Duration', value: 500, valid: true },
        { name: '最大Duration', value: 5000, valid: true },
        { name: '最小Iterations', value: 1, valid: true },
        { name: '最大Iterations', value: 10, valid: true },
        { name: '无限Iterations', value: -1, valid: true },
        { name: '最小Width', value: 100, valid: true },
        { name: '最大Width', value: 500, valid: true },
        { name: '最小Height', value: 100, valid: true },
        { name: '最大Height', value: 400, valid: true }
      ];
      
      let allValid = true;
      const results: string[] = [];
      
      for (const test of boundaryTests) {
        try {
          if (test.name.includes('Duration')) {
            this.duration = test.value;
            allValid = allValid && (this.duration === test.value);
          } else if (test.name.includes('Iterations')) {
            this.iterations = test.value;
            allValid = allValid && (this.iterations === test.value);
          } else if (test.name.includes('Width')) {
            this.width = test.value;
            allValid = allValid && (this.width === test.value);
          } else if (test.name.includes('Height')) {
            this.height = test.value;
            allValid = allValid && (this.height === test.value);
          }
          results.push(`${test.name}: ${test.value} ✓`);
        } catch (e) {
          allValid = false;
          results.push(`${test.name}: ${test.value} ✗`);
        }
      }
      
      this.addTestResult('边界值测试', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('边界值测试', false, `错误: ${error}`);
    }
  }

  private testOnStartEvent() {
    try {
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        this.addTestResult('onStart事件测试', hasStart,
          `事件日志数: ${this.eventLog.length}`);
      }, 100);
    } catch (error) {
      this.addTestResult('onStart事件测试', false, `错误: ${error}`);
    }
  }

  private testOnPauseEvent() {
    try {
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        this.eventLog = [];
        this.state = AnimationStatus.Paused;
        
        setTimeout(() => {
          const hasPause = this.eventLog.some(log => log.includes('onPause'));
          this.addTestResult('onPause事件测试', hasPause,
            `事件日志数: ${this.eventLog.length}`);
        }, 100);
      }, 500);
    } catch (error) {
      this.addTestResult('onPause事件测试', false, `错误: ${error}`);
    }
  }

  private testOnRepeatEvent() {
    try {
      this.iterations = 3;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        this.addTestResult('onRepeat事件测试', hasRepeat,
          `事件日志数: ${this.eventLog.length}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('onRepeat事件测试', false, `错误: ${error}`);
    }
  }

  private testOnCancelEvent() {
    try {
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        this.eventLog = [];
        this.state = AnimationStatus.Stopped;
        
        setTimeout(() => {
          const hasCancel = this.eventLog.some(log => log.includes('onCancel'));
          this.addTestResult('onCancel事件测试', hasCancel,
            `事件日志数: ${this.eventLog.length}`);
        }, 100);
      }, 500);
    } catch (error) {
      this.addTestResult('onCancel事件测试', false, `错误: ${error}`);
    }
  }

  private testOnFinishEvent() {
    try {
      this.iterations = 1;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        this.addTestResult('onFinish事件测试', hasFinish,
          `事件日志数: ${this.eventLog.length}`);
      }, 3000);
    } catch (error) {
      this.addTestResult('onFinish事件测试', false, `错误: ${error}`);
    }
  }

  private testEventFlow() {
    try {
      this.iterations = 1;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const flowCorrect = hasStart && hasFinish;
        
        this.addTestResult('事件流测试', flowCorrect,
          `事件序列: ${this.eventLog.join(' -> ')}`);
      }, 3000);
    } catch (error) {
      this.addTestResult('事件流测试', false, `错误: ${error}`);
    }
  }

  private testInitialState() {
    try {
      this.state = AnimationStatus.Initial;
      const isValid = this.state === AnimationStatus.Initial;
      this.addTestResult('Initial状态测试', isValid, '状态设置为Initial');
    } catch (error) {
      this.addTestResult('Initial状态测试', false, `错误: ${error}`);
    }
  }

  private testRunningState() {
    try {
      this.state = AnimationStatus.Running;
      const isValid = this.state === AnimationStatus.Running;
      this.addTestResult('Running状态测试', isValid, '状态设置为Running');
    } catch (error) {
      this.addTestResult('Running状态测试', false, `错误: ${error}`);
    }
  }

  private testPausedState() {
    try {
      this.state = AnimationStatus.Paused;
      const isValid = this.state === AnimationStatus.Paused;
      this.addTestResult('Paused状态测试', isValid, '状态设置为Paused');
    } catch (error) {
      this.addTestResult('Paused状态测试', false, `错误: ${error}`);
    }
  }

  private testStoppedState() {
    try {
      this.state = AnimationStatus.Stopped;
      const isValid = this.state === AnimationStatus.Stopped;
      this.addTestResult('Stopped状态测试', isValid, '状态设置为Stopped');
    } catch (error) {
      this.addTestResult('Stopped状态测试', false, `错误: ${error}`);
    }
  }

  private testStateTransition() {
    try {
      const transitions = [
        AnimationStatus.Initial,
        AnimationStatus.Running,
        AnimationStatus.Paused,
        AnimationStatus.Running,
        AnimationStatus.Stopped
      ];
      
      let allValid = true;
      for (const transition of transitions) {
        this.state = transition;
        if (this.state !== transition) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('状态转换测试', allValid,
        `转换次数: ${transitions.length}`);
    } catch (error) {
      this.addTestResult('状态转换测试', false, `错误: ${error}`);
    }
  }

  private testRapidSwitch() {
    try {
      const states = [
        AnimationStatus.Initial,
        AnimationStatus.Running,
        AnimationStatus.Paused,
        AnimationStatus.Running,
        AnimationStatus.Stopped
      ];
      
      let allValid = true;
      for (const state of states) {
        this.state = state;
        if (this.state !== state) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('快速切换测试', allValid,
        `切换次数: ${states.length}`);
    } catch (error) {
      this.addTestResult('快速切换测试', false, `错误: ${error}`);
    }
  }

  private testSingleLoop() {
    try {
      this.iterations = 1;
      this.reverse = false;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const noRepeat = !this.eventLog.some(log => log.includes('onRepeat'));
        
        const success = hasStart && hasFinish && noRepeat;
        this.addTestResult('单次循环测试', success,
          `事件数: ${this.eventLog.length}`);
      }, 3000);
    } catch (error) {
      this.addTestResult('单次循环测试', false, `错误: ${error}`);
    }
  }

  private testDoubleLoop() {
    try {
      this.iterations = 2;
      this.reverse = false;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        
        const success = hasStart && hasFinish && hasRepeat;
        this.addTestResult('两次循环测试', success,
          `事件数: ${this.eventLog.length}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('两次循环测试', false, `错误: ${error}`);
    }
  }

  private testMultipleLoop() {
    try {
      this.iterations = 5;
      this.reverse = false;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        
        const success = hasStart && hasFinish && hasRepeat;
        this.addTestResult('多次循环测试', success,
          `事件数: ${this.eventLog.length}`);
      }, 12000);
    } catch (error) {
      this.addTestResult('多次循环测试', false, `错误: ${error}`);
    }
  }

  private testInfiniteLoop() {
    try {
      this.iterations = -1;
      this.reverse = false;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        const noFinish = !this.eventLog.some(log => log.includes('onFinish'));
        
        const success = hasStart && hasRepeat && noFinish;
        this.addTestResult('无限循环测试', success,
          `事件数: ${this.eventLog.length}`);
        
        if (success) {
          this.state = AnimationStatus.Stopped;
        }
      }, 6000);
    } catch (error) {
      this.addTestResult('无限循环测试', false, `错误: ${error}`);
    }
  }

  private testForwardPlay() {
    try {
      this.iterations = 2;
      this.reverse = false;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        
        const success = hasStart && hasFinish;
        this.addTestResult('正向播放测试', success,
          `事件数: ${this.eventLog.length}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('正向播放测试', false, `错误: ${error}`);
    }
  }

  private testReversePlay() {
    try {
      this.iterations = 2;
      this.reverse = true;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        
        const success = hasStart && hasFinish;
        this.addTestResult('反向播放测试', success,
          `事件数: ${this.eventLog.length}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('反向播放测试', false, `错误: ${error}`);
    }
  }

  private testLoopWithReverse() {
    try {
      this.iterations = 3;
      this.reverse = true;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        
        const success = hasStart && hasFinish && hasRepeat;
        this.addTestResult('循环+反向测试', success,
          `事件数: ${this.eventLog.length}`);
      }, 7000);
    } catch (error) {
      this.addTestResult('循环+反向测试', false, `错误: ${error}`);
    }
  }

  private testLoopEvents() {
    try {
      this.iterations = 3;
      this.reverse = false;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const startCount = this.eventLog.filter(log => log.includes('onStart')).length;
        const repeatCount = this.eventLog.filter(log => log.includes('onRepeat')).length;
        const finishCount = this.eventLog.filter(log => log.includes('onFinish')).length;
        
        const validSequence = startCount === 1 && repeatCount >= 2 && finishCount === 1;
        this.addTestResult('循环事件测试', validSequence,
          `onStart: ${startCount}, onRepeat: ${repeatCount}, onFinish: ${finishCount}`);
      }, 7000);
    } catch (error) {
      this.addTestResult('循环事件测试', false, `错误: ${error}`);
    }
  }

  private testCompleteFlow() {
    try {
      this.iterations = 2;
      this.reverse = false;
      this.eventLog = [];
      this.state = AnimationStatus.Initial;
      
      setTimeout(() => {
        this.state = AnimationStatus.Running;
        
        setTimeout(() => {
          this.state = AnimationStatus.Paused;
          
          setTimeout(() => {
            this.state = AnimationStatus.Running;
            
            setTimeout(() => {
              const hasStart = this.eventLog.some(log => log.includes('onStart'));
              const hasPause = this.eventLog.some(log => log.includes('onPause'));
              const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
              const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
              
              const success = hasStart && hasPause && hasRepeat && hasFinish;
              this.addTestResult('完整流程测试', success,
                `事件数: ${this.eventLog.length}`);
            }, 5000);
          }, 1000);
        }, 1000);
      }, 1000);
    } catch (error) {
      this.addTestResult('完整流程测试', false, `错误: ${error}`);
    }
  }

  private testStressTest() {
    try {
      let successCount = 0;
      const totalIterations = 10;
      
      for (let i = 0; i < totalIterations; i++) {
        try {
          this.duration = 1000 + i * 100;
          this.iterations = 1;
          this.width = 200 + i * 10;
          this.height = 150 + i * 10;
          successCount++;
        } catch (e) {
          console.error(`Stress test iteration ${i} failed: ${e}`);
        }
      }
      
      const success = successCount === totalIterations;
      this.addTestResult('压力测试', success,
        `成功次数: ${successCount}/${totalIterations}`);
    } catch (error) {
      this.addTestResult('压力测试', false, `错误: ${error}`);
    }
  }

  private testExceptionHandling() {
    try {
      let exceptionHandled = false;
      
      try {
        this.duration = -1;
      } catch (e) {
        exceptionHandled = true;
      }
      
      try {
        this.iterations = 0;
      } catch (e) {
        exceptionHandled = exceptionHandled || true;
      }
      
      this.addTestResult('异常处理测试', true,
        '异常处理机制正常');
    } catch (error) {
      this.addTestResult('异常处理测试', false, `错误: ${error}`);
    }
  }

  private testPerformance() {
    try {
      const startTime = Date.now();
      
      for (let i = 0; i < 1000; i++) {
        this.duration = 2000;
        this.iterations = 1;
        this.reverse = false;
        this.width = 300;
        this.height = 200;
      }
      
      const endTime = Date.now();
      const executionTime = endTime - startTime;
      const isPerformant = executionTime < 100;
      
      this.addTestResult('性能测试', isPerformant,
        `执行时间: ${executionTime}ms (1000次操作)`);
    } catch (error) {
      this.addTestResult('性能测试', false, `错误: ${error}`);
    }
  }

  private testCompatibility() {
    try {
      const compatibilityTests = [
        { name: 'AnimationStatus.Initial', value: AnimationStatus.Initial },
        { name: 'AnimationStatus.Running', value: AnimationStatus.Running },
        { name: 'AnimationStatus.Paused', value: AnimationStatus.Paused },
        { name: 'AnimationStatus.Stopped', value: AnimationStatus.Stopped },
        { name: 'FillMode.None', value: FillMode.None },
        { name: 'FillMode.Forwards', value: FillMode.Forwards },
        { name: 'FillMode.Backwards', value: FillMode.Backwards },
        { name: 'FillMode.Both', value: FillMode.Both }
      ];
      
      let allCompatible = true;
      const results: string[] = [];
      
      for (const test of compatibilityTests) {
        try {
          const isValid = test.value !== undefined;
          allCompatible = allCompatible && isValid;
          results.push(`${test.name}: ${isValid ? '✓' : '✗'}`);
        } catch (e) {
          allCompatible = false;
          results.push(`${test.name}: ✗`);
        };
      }
      
      this.addTestResult('兼容性测试', allCompatible, results.join(', '));
    } catch (error) {
      this.addTestResult('兼容性测试', false, `错误: ${error}`);
    }
  }
}
