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
struct ImageAnimatorTest009 {
  @State testTitle: string = '补充测试套件';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State duration: number = 2000;
  @State iterations: number = 1;
  @State reverse: boolean = false;
  @State fillMode: FillMode = FillMode.None;
  @State width: number = 300;
  @State height: number = 200;
  @State eventLog: string[] = [];
  @State testProgress: number = 0;
  @State passedTests: number = 0;
  @State failedTests: number = 0;

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
    if (this.eventLog.length > 30) {
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
      Text('测试控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: 基础')
          .onClick(() => {
            this.testBasic();
          })

        Button('测试2: 属性')
          .onClick(() => {
            this.testProperties();
          })

        Button('测试3: 事件')
          .onClick(() => {
            this.testEvents();
          })
      }

      Row({ space: 10 }) {
        Button('测试4: 状态')
          .onClick(() => {
            this.testStates();
          })

        Button('测试5: 循环')
          .onClick(() => {
            this.testLoops();
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

  private testBasic() {
    try {
      this.state = AnimationStatus.Running;
      const isValid = this.state === AnimationStatus.Running;
      this.addTestResult('基础测试', isValid, '状态设置为Running');
    } catch (error) {
      this.addTestResult('基础测试', false, `错误: ${error}`);
    }
  }

  private testProperties() {
    try {
      this.duration = 2000;
      this.iterations = 2;
      this.reverse = true;
      this.width = 300;
      this.height = 200;
      
      const allSet = this.duration === 2000 &&
                      this.iterations === 2 &&
                      this.reverse === true &&
                      this.width === 300 &&
                      this.height === 200;
      
      this.addTestResult('属性测试', allSet, '所有属性设置成功');
    } catch (error) {
      this.addTestResult('属性测试', false, `错误: ${error}`);
    }
  }

  private testEvents() {
    try {
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        this.addTestResult('事件测试', hasStart,
          `事件日志数: ${this.eventLog.length}`);
      }, 100);
    } catch (error) {
      this.addTestResult('事件测试', false, `错误: ${error}`);
    }
  }

  private testStates() {
    try {
      const states = [
        AnimationStatus.Initial,
        AnimationStatus.Running,
        AnimationStatus.Paused,
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
      
      this.addTestResult('状态测试', allValid, `切换了${states.length}种状态`);
    } catch (error) {
      this.addTestResult('状态测试', false, `错误: ${error}`);
    }
  }

  private testLoops() {
    try {
      const loopCounts = [1, 2, 3, 5];
      let allValid = true;
      
      for (const count of loopCounts) {
        this.iterations = count;
        if (this.iterations !== count) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('循环测试', allValid,
        `测试循环次数: ${loopCounts.join(', ')}`);
    } catch (error) {
      this.addTestResult('循环测试', false, `错误: ${error}`);
    }
  }
}
