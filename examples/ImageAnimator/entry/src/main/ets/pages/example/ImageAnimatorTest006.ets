/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
struct ImageAnimatorTest006 {
  @State testTitle: string = '循环与反向播放测试';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State iterations: number = 1;
  @State reverse: boolean = false;
  @State eventLog: string[] = [];
  @State repeatCount: number = 0;

  private: ImageFrameInfo[] = [
    { src: $r('app.media.img1') },
    { src: $r('app.media.img2') },
    { src: $r('app.media.img3') },
    { src: $r('app.media.img4') }
  ];

  private: (testName: string, result: boolean, details: string = '') {
    const status = result ? 'PASS' : 'FAIL';
    const timestamp = new Date().toLocaleTimeString();
    this.testResults.unshift(`[${timestamp}] ${testName}: ${status} ${details}`);
  }

  private: (eventName: string) {
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

        Divider().strokeWidth(2)

        this.buildTestSection()

        Divider().strokeWidth(2)

        this.buildControls()

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
  buildTestSection() {
    Column({ space: 10 }) {
      Text('循环与反向测试控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: 单次播放')
          .onClick(() => {
            this.testSinglePlay();
          })

        Button('测试2: 两次循环')
          .onClick(() => {
            this.testDoubleLoop();
          })

        Button('测试3: 多次循环')
          .onClick(() => {
            this.testMultipleLoop();
          })
      }

      Row({ space: 10 }) {
        Button('测试4: 无限循环')
          .onClick(() => {
            this.testInfiniteLoop();
          })

        Button('测试5: 正向播放')
          .onClick(() => {
            this.testForwardPlay();
          })

        Button('测试6: 反向播放')
          .onClick(() => {
            this.testReversePlay();
          })
      }

      Row({ space: 10 }) {
        Button('测试7: 循环+反向')
          .onClick(() => {
            this.testLoopWithReverse();
          })

        Button('测试8: 循环事件验证')
          .onClick(() => {
            this.testLoopEventValidation();
          })

        Button('清空结果')
          .onClick(() => {
            this.testResults = [];
            this.eventLog = [];
            this.repeatCount = 0;
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildControls() {
    Column({ space: 15 }) {
      Text('播放控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 20 }) {
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

        Column({ space: 5 }) {
          Text('Reverse')
            .fontSize(14)
          Toggle({ type: ToggleType.Switch, isOn: this.reverse })
            .onChange((isOn: boolean) => {
              this.reverse = isOn;
            })
          Text(`${this.reverse ? 'On' : 'Off'}`)
            .fontSize(12)
            .fontColor(0x666666)
        }
      }

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

      Text(`重复次数: ${this.repeatCount}`)
        .fontSize(14)
        .fontColor(0x666666)
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
        .duration(2000)
        .state(this.state)
        .reverse(this.reverse)
        .fillMode(FillMode.Forwards)
        .iterations(this.iterations)
        .width(300)
        .height(200)
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
          this.repeatCount++;
          this.logEvent(`onRepeat (${this.repeatCount})`);
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
        .height(200)
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
                .fontColor(result.includes('PASS') ? 0x4CAF50 : 0xF44322)
            }
            .width('100%')
          }, (result: string, index: number) => `${index}_${result}`)
        }
        .width('100%')
        .height(250)
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

  private testSinglePlay() {
    try {
      this.iterations = 1;
      this.reverse = false;
      this.repeatCount = 0;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const noRepeat = !this.eventLog.some(log => log.includes('onRepeat'));
        
        const success = hasStart && hasFinish && noRepeat;
        this.addTestResult('单次播放测试', success,
          `事件数: ${this.eventLog.length}, 重复次数: ${this.repeatCount}`);
      }, 3000);
    } catch (error) {
      this.addTestResult('单次播放测试', false, `错误: ${error}`);
    }
  }

  private testDoubleLoop() {
    try {
      this.iterations = 2;
      this.reverse = false;
      this.repeatCount = 0;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        
        const success = hasStart && hasFinish && hasRepeat && this.repeatCount >= 1;
        this.addTestResult('两次循环测试', success,
          `事件数: ${this.eventLog.length}, 重复次数: ${this.repeatCount}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('两次循环测试', false, ``错误: ${error}`);
    }
  }

  private testMultipleLoop() {
    try {
      this.iterations = 5;
      this.reverse = false;
      this.repeatCount = 0;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        
        const success = hasStart && hasFinish && hasRepeat && this.repeatCount >= 4;
        this.addTestResult('多次循环测试', success,
          `事件数: ${this.eventLog.length}, 重复次数: ${this.repeatCount}`);
      }, 12000);
    } catch (error) {
      this.addTestResult('多次循环测试', false, `错误: ${error}`);
    }
  }

  private testInfiniteLoop() {
    try {
      this.iterations = -1;
      this.reverse = false;
      this.repeatCount = 0;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        const noFinish = !this.eventLog.some(log => log.includes('onFinish'));
        
        const success = hasStart && hasRepeat && noFinish && this.repeatCount >= 2;
        this.addTestResult('无限循环测试', success,
          `事件数: ${this.eventLog.length}, 重复次数: ${this.repeatCount}`);
        
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
      this.repeatCount = 0;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        
        const success = hasStart && hasFinish;
        this.addTestResult('正向播放测试', success,
          `事件数: ${this.eventLog.length}, 重复次数: ${this.repeatCount}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('正向播放测试', false, `错误: ${error}`);
    }
  }

  private testReversePlay() {
    try {
      this.iterations = 2;
      this.reverse = true;
      this.repeatCount = 0;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        
        const success = hasStart && hasFinish;
        this.addTestResult('反向播放测试', success,
          `事件数: ${this.eventLog.length}, 重复次数: ${this.repeatCount}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('反向播放测试', false, `错误: ${error}`);
    }
  }

  private testLoopWithReverse() {
    try {
      this.iterations = 3;
      this.reverse = true;
      this.repeatCount = 0;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        
        const success = hasStart && hasFinish && hasRepeat && this.repeatCount >= 2;
        this.addTestResult('循环+反向测试', success,
          `事件数: ${this.eventLog.length}, 重复次数: ${this.repeatCount}`);
      }, 7000);
    } catch (error) {
      this.addTestResult('循环+反向测试', false, `错误: ${error}`);
    }
  }

  private testLoopEventValidation() {
    try {
      this.iterations = 3;
      this.reverse = false;
      this.repeatCount = 0;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const startCount = this.eventLog.filter(log => log.includes('onStart')).length;
        const repeatCount = this.eventLog.filter(log => log.includes('onRepeat')).length;
        const finishCount = this.eventLog.filter(log => log.includes('onFinish')).length;
        
        const validSequence = startCount === 1 && repeatCount >= 2 && finishCount === 1;
        this.addTestResult('循环事件验证', validSequence,
          `onStart: ${startCount}, onRepeat: ${repeatCount}, onFinish: ${finishCount}`);
      }, 7000);
    } catch (error) {
      this.addTestResult('循环事件验证', false, `错误: ${error}`);
    }
  }
}
