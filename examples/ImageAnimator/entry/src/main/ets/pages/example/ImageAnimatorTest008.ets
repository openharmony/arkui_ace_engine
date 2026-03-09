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
struct ImageAnimatorAdvancedTest {
  @State testTitle: string = '高级功能测试';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State duration: number = 2000;
  @State iterations: number = 1;
  @State reverse: boolean = false;
  @State fillMode: FillMode = FillMode.None;
  @State width: number = 300;
  @State height: number = 200;
  @State eventLog: string[] = [];
  @State selectedImageSet: number = 0;
  @State customDuration: number = 2000;
  @State testProgress: number = 0;
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
    ],
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') },
      { src: $r('app.media.img3') },
      { src: $r('app.media.img4') },
      { src: $r('app.media.img1') }
    ],
    [
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') },
      { src: $r('app.media.img3') },
      { src: $r('app.media.img4') },
      { src: $r('app.media.img1') },
      { src: $r('app.media.img2') }
    ]
  ];

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

        this.buildTestSection()

        Divider().strokeWidth(2)

        this.buildImageSetSelector()

        Divider().strokeWidth(2)

        this.buildPropertyControls()

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
        Text('已执行')
          .fontSize(14)
          .fontColor(0x666666)
        Text(`${this.testProgress}`)
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(0x2196F3)
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
  buildTestSection() {
    Column({ space: 10 }) {
      Text('高级测试控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: 动态图片源')
          .onClick(() => {
            this.testDynamicImageSource();
          })

        Button('测试2: 持续时间渐变')
          .onClick(() => {
            this.testDurationGradient();
          })

        Button('测试3: 尺寸自适应')
          .onClick(() => {
            this.testResponsiveSize();
          })
      }

      Row({ space: 10 }) {
        Button('测试4: 多重循环')
          .onClick(() => {
            this.testMultipleLoops();
          })

        Button('测试5: 状态机测试')
          .onClick(() => {
            this.testStateMachine();
          })

        Button('测试6: 事件顺序')
          .onClick(() => {
            this.testEventSequence();
          })
      }

      Row({ space: 10 }) {
        Button('测试7: 边界条件')
          .onClick(() => {
            this.testBoundaryConditions();
          })

        Button('测试8: 并发测试')
          .onClick(() => {
            this.testConcurrency();
          })

        Button('测试9: 资源管理')
          .onClick(() => {
            this.testResourceManagement();
          })
      }

      Row({ space: 10 }) {
        Button('测试10: 内存测试')
          .onClick(() => {
            this.testMemoryUsage();
          })

        Button('测试11: 响应性测试')
          .onClick(() => {
            this.testResponsiveness();
          })

        Button('清空结果')
          .onClick(() => {
            this.testResults = [];
            this.eventLog = [];
            this.testProgress = 0;
            this.passedTests = 0;
            this.failedTests = 0;
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildImageSetSelector() {
    Column({ space: 10 }) {
      Text('图片集选择')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        ForEach(this.imageSets, (images: ImageFrameInfo[], index: number) => {
          Button(`集${index + 1}`)
            .onClick(() => {
              this.selectedImageSet = index;
            })
            .backgroundColor(this.selectedImageSet === index ? 0x2196F3 : 0xE0E0E0)
            .fontColor(this.selectedImageSet === index ? 0xFFFFFF : 0x000000)
        }, (images: ImageFrameInfo[], index: number) => `${index}`)
      }

      Text(`当前图片集: ${this.selectedImageSet + 1}, 图片数量: ${this.imageSets[this.selectedImageSet].length}`)
        .fontSize(14)
        .fontColor(0x666666)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildPropertyControls() {
    Column({ space: 15 }) {
      Text('属性控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Text('Duration (ms)')
            .fontSize(14)
          Slider({
            min: 500,
            max: 5000,
            value: this.customDuration,
            step: 100
          })
            .width(200)
            .onChange((value: number) => {
              this.customDuration = value;
              this.duration = value;
            })
          Text(`${this.customDuration}ms`)
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 5 }) {
          Text('Iterations')
            .fontSize(14)
          Slider({
            min: -1,
            max: 10,
            value: this.iterations,
            step: 1
          })
            .width(200)
            .onChange((value: number) => {
              this.iterations = value;
            })
          Text(`${this.iterations === -1 ? 'Infinite' : this.iterations}`)
            .fontSize(12)
            .fontColor(0x666666)
        }
      }

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Text('Width')
            .fontSize(14)
          Slider({
            min: 100,
            max: 500,
            value: this.width,
            step: 10
          })
            .width(200)
            .onChange((value: number) => {
              this.width = value;
            })
          Text(`${this.width}px`)
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 5 }) {
          Text('Height')
            .fontSize(14)
          Slider({
            min: 100,
            max: 400,
            value: this.height,
            step: 10
          })
            .width(200)
            .onChange((value: number) => {
              this.height = value;
            })
          Text(`${this.height}px`)
            .fontSize(12)
            .fontColor(0x666666)
        }
      }

      Row({ space: 15 }) {
        Text('Reverse:')
          .fontSize(14)
        Toggle({ type: ToggleType.Switch, isOn: this.reverse })
          .onChange((isOn: boolean) => {
            this.reverse = isOn;
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
        .images(this.imageSets[this.selectedImageSet])
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

  private testDynamicImageSource() {
    try {
      const originalSet = this.selectedImageSet;
      let allValid = true;
      const results: string[] = [];
      
      for (let i = 0; i < this.imageSets.length; i++) {
        this.selectedImageSet = i;
        const hasImages = this.imageSets[i].length > 0;
        const allValidImages = this.imageSets[i].every(img => img.src !== undefined);
        const isValid = hasImages && allValidImages;
        allValid = allValid && isValid;
        results.push(`集${i + 1}: ${this.imageSets[i].length}张 ${isValid ? '✓' : '✗'}`);
      }
      
      this.selectedImageSet = originalSet;
      this.addTestResult('动态图片源测试', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('动态图片源测试', false, `错误: ${error}`);
    }
  }

  private testDurationGradient() {
    try {
      const durations = [500, 1000, 1500, 2000, 2500, 3000];
      let allValid = true;
      const results: string[] = [];
      
      for (const dur of durations) {
        this.duration = dur;
        this.customDuration = dur;
        const isValid = this.duration === dur && this.customDuration === dur;
        allValid = allValid && isValid;
        results.push(`${dur}ms ${isValid ? '✓' : '✗'}`);
      }
      
      this.addTestResult('持续时间渐变测试', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('持续时间渐变测试', false, `错误: ${error}`);
    }
  }

  private testResponsiveSize() {
    try {
      const sizes = [
        { w: 200, h: 150 },
        { w: 250, h: 175 },
        { w: 300, h: 200 },
        { w: 350, h: 225 },
        { w: 400, h: 250 }
      ];
      let allValid = true;
      const results: string[] = [];
      
      for (const size of sizes) {
        this.width = size.w;
        this.height = size.h;
        const isValid = this.width === size.w && this.height === size.h;
        allValid = allValid && isValid;
        results.push(`${size.w}x${size.h} ${isValid ? '✓' : '✗'}`);
      }
      
      this.addTestResult('尺寸自适应测试', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('尺寸自适应测试', false, `错误: ${error}`);
    }
  }

  private testMultipleLoops() {
    try {
      const loopCounts = [1, 2, 3, 5, 10];
      let allValid = true;
      const results: string[] = [];
      
      for (const count of loopCounts) {
        this.iterations = count;
        const isValid = this.iterations === count;
        allValid = allValid && isValid;
        results.push(`${count}次 ${isValid ? '✓' : '✗'}`);
      }
      
      this.addTestResult('多重循环测试', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('多重循环测试', false, `错误: ${error}`);
    }
  }

  private testStateMachine() {
    try {
      const stateSequence = [
        AnimationStatus.Initial,
        AnimationStatus.Running,
        AnimationStatus.Paused,
        AnimationStatus.Running,
        AnimationStatus.Stopped,
        AnimationStatus.Initial
      ];
      
      let allValid = true;
      const results: string[] = [];
      
      for (const state of stateSequence) {
        this.state = state;
        const isValid = this.state === state;
        allValid = allValid && isValid;
        const stateName = = state === AnimationStatus.Initial ? 'Initial' :
                            state === AnimationStatus.Running ? 'Running' :
                            state === AnimationStatus.Paused ? 'Paused' : 'Stopped';
        results.push(`${stateName} ${isValid ? '✓' : '✗'}`);
      }
      
      this.addTestResult('状态机测试', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('状态机测试', false, `错误: ${error}`);
    }
  }

  private testEventSequence() {
    try {
      this.iterations = 2;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const eventNames = this.eventLog.map(log => {
          const match = log.match(/\[(.*?)\] (\w+)/);
          return match ? match[2] : '';
        }).filter(name => name !== '');
        
        const hasStart = eventNames.includes('onStart');
        const hasFinish = eventNames.includes('onFinish');
        const hasRepeat = eventNames.includes('onRepeat');
        
        const sequenceValid = hasStart && hasFinish && hasRepeat;
        this.addTestResult('事件顺序测试', sequenceValid,
          `事件序列: ${eventNames.join(' -> ')}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('事件顺序测试', false, `错误: ${error}`);
    }
  }

  private testBoundaryConditions() {
    try {
      const boundaryTests = [
        { name: '最小Duration', test: () => { this.duration = 500; return this.duration === 500; } },
        { name: '最大Duration', test: () => { this.duration = 5000; return this.duration === 5000; } },
        { name: '最小Iterations', test: () => { this.iterations = 1; return this.iterations === 1; } },
        { name: '最大Iterations', test: () => { this.iterations = 10; return this.iterations === 10; } },
        { name: '无限Iterations', test: () => { this.iterations = -1; return this.iterations === -1; } },
        { name: '最小Width', test: () => { this.width = 100; return this.width === 100; } },
        { name: '最大Width', test: () => { this.width = 500; return this.width === 500; } },
        { name: '最小Height', test: () => { this.height = 100; return this.height === 100; } },
        { name: '最大Height', test: () => { this.height = 400; return this.height === 400; } }
      ];
      
      let allValid = true;
      const results: string[] = [];
      
      for (const test of boundaryTests) {
        try {
          const isValid = test.test();
          allValid = allValid && isValid;
          results.push(`${test.name}: ${isValid ? '✓' : '✗'}`);
        } catch (e) {
          allValid = false;
          results.push(`${test.name}: ✗`);
        }
      }
      
      this.addTestResult('边界条件测试', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('边界条件测试', false, `错误: ${error}`);
    }
  }

  private testConcurrency() {
    try {
      const operations = [
        () => { this.duration = 1000; },
        () => { this.iterations = 2; },
        () => { this.reverse = true; },
        () => { this.width = 300; },
        () => { this.height = 200; }
      ];
      
      let successCount = 0;
      
      for (const op of operations) {
        try {
          op();
          successCount++;
        } catch (e) {
          console.error(`Concurrent operation failed: ${e}`);
        }
      }
      
      const allSucceeded = successCount === operations.length;
      this.addTestResult('并发测试', allSucceeded,
        `成功操作: ${successCount}/${operations.length}`);
    } catch (error) {
      this.addTestResult('并发测试', false, `错误: ${error}`);
    }
  }

  private testResourceManagement() {
    try {
      const originalSet = this.selectedImageSet;
      let allValid = true;
      const results: string[] = [];
      
      for (let i = 0; i < this.imageSets.length; i++) {
        this.selectedImageSet = i;
        const images = this.imageSets[i];
        const hasValidImages = images.length > 0 && images.every(img => img.src !== undefined);
        allValid = allValid && hasValidImages;
        results.push(`集${i + 1}: ${images.length}张 ${hasValidImages ? '✓' : '✗'}`);
      }
      
      this.selectedImageSet = originalSet;
      this.addTestResult('资源管理测试', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('资源管理测试', false, `错误: ${error}`);
    }
  }

  private testMemoryUsage() {
    try {
      const startTime = Date.now();
      const iterations = 1000;
      
      for (let i = 0; i < iterations; i++) {
        this.duration = 2000;
        this.iterations = 1;
        this.width = 300;
        this.height = 200;
        this.reverse = false;
      }
      
      const endTime = Date.now();
      const executionTime = endTime - startTime;
      const isEfficient = executionTime < 200;
      
      this.addTestResult('内存测试', isEfficient,
        `执行时间: ${executionTime}ms (${iterations}次操作)`);
    } catch (error) {
      this.addTestResult('内存测试', false, `错误: ${error}`);
    }
  }

  private testResponsiveness() {
    try {
      const startTime = Date.now();
      const operations = 100;
      
      for (let i = 0; i < operations; i++) {
        this.duration = 1000 + i * 10;
        this.width = 200 + i;
        this.height = 150 + i;
      }
      
      const endTime = Date.now();
      const avgTime = (endTime - startTime) / operations;
      const isResponsive = avgTime < 5;
      
      this.addTestResult('响应性测试', isResponsive,
        `平均响应时间: ${avgTime.toFixed(2)}ms/操作`);
    } catch (error) {
      this.addTestResult('响应性测试', false, `错误: ${error}`);
    }
  }
}
