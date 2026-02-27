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
struct ImageAnimatorTest002 {
  @State testTitle: string = '事件回调测试';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State eventLog: string[] = [];
  @State iterations: number = 2;
  @State reverse: boolean = false;

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

  private logEvent(eventName: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.eventLog.unshift(`[${timestamp}] ${eventName}`);
    if (this.eventLog.length > 20) {
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
      Text('事件测试控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: onStart事件')
          .onClick(() => {
            this.testOnStartEvent();
          })

        Button('测试2: onPause事件')
          .onClick(() => {
            this.testOnPauseEvent();
          })

        Button('测试3: onRepeat事件')
          .onClick(() => {
            this.testOnRepeatEvent();
          })
      }

      Row({ space: 10 }) {
        Button('测试4: onCancel事件')
          .onClick(() => {
            this.testOnCancelEvent();
          })

        Button('测试5: onFinish事件')
          .onClick(() => {
            this.testOnFinishEvent();
          })

        Button('测试6: 完整事件流')
          .onClick(() => {
            this.testCompleteEventFlow();
          })
      }

      Row({ space: 10 }) {
        Button('测试7: 重复播放事件')
          .onClick(() => {
            this.testRepeatEvents();
          })

        Button('测试8: 反向播放事件')
          .onClick(() => {
            this.testReverseEvents();
          })

        Button('清空日志')
          .onClick(() => {
            this.eventLog = [];
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
      Text('ImageAnimator (事件监听中)')
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
                .fontColor(result.includes('PASS') ? 0x4CAF50 : 0xF44336)
            }
            .width('100%')
          }, (result: string, index: number) => `${index}_${result}`)
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

  private testOnStartEvent() {
    try {
      const initialLogLength = this.eventLog.length;
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStartEvent = this.eventLog.some(log => log.includes('onStart'));
        this.addTestResult('onStart事件触发', hasStartEvent,
          `事件日志数: ${this.eventLog.length - initialLogLength}`);
      }, 100);
    } catch (error) {
      this.addTestResult('onStart事件触发', false, `错误: ${error}`);
    }
  }

  private testOnPauseEvent() {
    try {
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const initialLogLength = this.eventLog.length;
        this.state = AnimationStatus.Paused;
        
        setTimeout(() => {
          const hasPauseEvent = this.eventLog.some(log => log.includes('onPause'));
          this.addTestResult('onPause事件触发', hasPauseEvent,
            `事件日志数: ${this.eventLog.length - initialLogLength}`);
        }, 100);
      }, 500);
    } catch (error) {
      this.addTestResult('onPause事件触发', false, `错误: ${error}`);
    }
  }

  private testOnRepeatEvent() {
    try {
      this.iterations = 3;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const repeatCount = this.eventLog.filter(log => log.includes('onRepeat')).length;
        this.addTestResult('onRepeat事件触发', repeatCount >= 2,
          `重复次数: ${repeatCount}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('onRepeat事件触发', false, `错误: ${error}`);
    }
  }

  private testOnCancelEvent() {
    try {
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const initialLogLength = this.eventLog.length;
        this.state = AnimationStatus.Stopped;
        
        setTimeout(() => {
          const hasCancelEvent = this.eventLog.some(log => log.includes('onCancel'));
          this.addTestResult('onCancel事件触发', hasCancelEvent,
            `事件日志数: ${this.eventLog.length - initialLogLength}`);
        }, 100);
      }, 500);
    } catch (error) {
      this.addTestResult('onCancel事件触发', false, `错误: ${error}`);
    }
  }

  private testOnFinishEvent() {
    try {
      this.iterations = 1;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasFinishEvent = this.eventLog.some(log => log.includes('onFinish'));
        this.addTestResult('onFinish事件触发', hasFinishEvent,
          `总事件数: ${this.eventLog.length}`);
      }, 3000);
    } catch (error) {
      this.addTestResult('onFinish事件触发', false, `错误: ${error}`);
    }
  }

  private testCompleteEventFlow() {
    try {
      this.iterations = 1;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        const flowCorrect = hasStart && hasFinish;
        
        this.addTestResult('完整事件流', flowCorrect,
          `事件序列: ${this.eventLog.join(' -> ')}`);
      }, 3000);
    } catch (error) {
      this.addTestResult('完整事件流', false, `错误: ${error}`);
    }
  }

  private testRepeatEvents() {
    try {
      this.iterations = 3;
      this.reverse = false;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const repeatCount = this.eventLog.filter(log => log.includes('onRepeat')).length;
        this.addTestResult('重复播放事件', repeatCount >= 2,
          `onRepeat触发次数: ${repeatCount}`);
      }, 6000);
    } catch (error) {
      this.addTestResult('重复播放事件', false, `错误: ${error}`);
    }
  }

  private testReverseEvents() {
    try {
      this.iterations = 2;
      this.reverse = true;
      this.eventLog = [];
      this.state = AnimationStatus.Running;
      
      setTimeout(() => {
        const hasStart = this.eventLog.some(log => log.includes('onStart'));
        const hasRepeat = this.eventLog.some(log => log.includes('onRepeat'));
        const hasFinish = this.eventLog.some(log => log.includes('onFinish'));
        
        this.addTestResult('反向播放事件', hasStart && hasRepeat && hasFinish,
          `反向模式事件数: ${this.eventLog.length}`);
      }, 5000);
    } catch (error) {
      this.addTestResult('反向播放事件', false, `错误: ${error}`);
    }
  }
}
