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
struct ImageAnimatorTest005 {
  @State testTitle: string = '状态转换测试';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State stateHistory: string[] = [];
  @State iterations: number = 1;

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

  private logStateChange(newState: AnimationStatus) {
    const timestamp = new Date().toLocaleTimeString();
    const stateName = this.getStateName(newState);
    this.stateHistory.unshift(`[${timestamp}] ${stateName}`);
    if (this.stateHistory.length > 20) {
      this.stateHistory.pop();
    }
  }

  private getStateName(state: AnimationStatus): string {
    switch (state) {
      case AnimationStatus.Initial:
        return 'Initial';
      case AnimationStatus.Running:
        return 'Running';
      case AnimationStatus.Paused:
        return 'Paused';
      case AnimationStatus.Stopped:
        return 'Stopped';
      default:
        return 'Unknown';
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

        this.buildStateControls()

        Divider().strokeWidth(2)

        this.buildImageAnimator()

        Divider().strokeWidth(2)

        this.buildStateHistory()

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
      Text('状态转换测试控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: Initial->Running')
          .onClick(() => {
            this.testInitialToRunning();
          })

        Button('测试2: Running->Paused')
          .onClick(() => {
            this.testRunningToPaused();
          })

        Button('测试3: Paused->Running')
          .onClick(() => {
            this.testPausedToRunning();
          })
      }

      Row({ space: 10 }) {
        Button('测试4: Running->Stopped')
          .onClick(() => {
            this.testRunningToStopped();
          })

        Button('测试5: Paused->Stopped')
          .onClick(() => {
            this.testPausedToStopped();
          })

        Button('测试6: 完整状态循环')
          .onClick(() => {
            this.testCompleteStateCycle();
          })
      }

      Row({ space: 10 }) {
        Button('测试7: 快速状态切换')
          .onClick(() => {
            this.testRapidStateSwitch();
          })

        Button('测试8: 状态验证')
          .onClick(() => {
            this.testStateValidation();
          })

        Button('清空结果')
          .onClick(() => {
            this.testResults = [];
            this.stateHistory = [];
          })
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildStateControls() {
    Column({ space: 10 }) {
      Text('状态控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 15 }) {
        Button('Initial')
          .onClick(() => {
            this.state = AnimationStatus.Initial;
            this.logStateChange(this.state);
          })
          .backgroundColor(this.state === AnimationStatus.Initial ? 0x2196F3 : 0xE0E0E0)
          .fontColor(this.state === AnimationStatus.Initial ? 0xFFFFFF : 0x000000)

        Button('Running')
          .onClick(() => {
            this.state = AnimationStatus.Running;
            this.logStateChange(this.state);
          })
          .backgroundColor(this.state === AnimationStatus.Running ? 0x4CAF50 : 0xE0E0E0)
          .fontColor(this.state === AnimationStatus.Running ? 0xFFFFFF : 0x000000)

        Button('Paused')
          .onClick(() => {
            this.state = AnimationStatus.Paused;
            this.logStateChange(this.state);
          })
          .backgroundColor(this.state === AnimationStatus.Paused ? 0xFF9800 : 0xE0E0E0)
          .fontColor(this.state === AnimationStatus.Paused ? 0xFFFFFF : 0x000000)

        Button('Stopped')
          .onClick(() => {
            this.state = AnimationStatus.Stopped;
            this.logStateChange(this.state);
          })
          .backgroundColor(this.state === AnimationStatus.Stopped ? 0xF44336 : 0xE0E0E0)
          .fontColor(this.state === AnimationStatus.Stopped ? 0xFFFFFF : 0x000000)
      }

      Text(`当前状态: ${this.getStateName(this.state)}`)
        .fontSize(16)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x333333)
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
        .fillMode(FillMode.Forwards)
        .iterations(this.iterations)
        .width(300)
        .height(200)
        .borderRadius(10)
        .backgroundColor(0xE0E0E0)
        .onFinish(() => {
          this.state = AnimationStatus.Stopped;
          this.logStateChange(this.state);
        })
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildStateHistory() {
    Column({ space: 10 }) {
      Text('状态历史')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      if (this.stateHistory.length === 0) {
        Text('暂无状态历史')
          .fontSize(14)
          .fontColor(0x999999)
      } else {
        List({ space: 5 }) {
          ForEach(this.stateHistory, (log: string, index: number) => {
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

  private testInitialToRunning() {
    try {
      this.state = AnimationStatus.Initial;
      this.logStateChange(this.state);
      
      setTimeout(() => {
        this.state = AnimationStatus.Running;
        this.logStateChange(this.state);
        
        const success = this.state === AnimationStatus.Running;
        this.addTestResult('Initial->Running转换', success,
          `当前状态: ${this.getStateName(this.state)}`);
      }, 100);
    } catch (error) {
      this.addTestResult('Initial->Running转换', false, `错误: ${error}`);
    }
  }

  private testRunningToPaused() {
    try {
      this.state = AnimationStatus.Running;
      this.logStateChange(this.state);
      
      setTimeout(() => {
        this.state = AnimationStatus.Paused;
        this.logStateChange(this.state);
        
        const success = this.state === AnimationStatus.Paused;
        this.addTestResult('Running->Paused转换', success,
          `当前状态: ${this.getStateName(this.state)}`);
      }, 500);
    } catch (error) {
      this.addTestResult('Running->Paused转换', false, `错误: ${error}`);
    }
  }

  private testPausedToRunning() {
    try {
      this.state = AnimationStatus.Running;
      this.logStateChange(this.state);
      
      setTimeout(() => {
        this.state = AnimationStatus.Paused;
        this.logStateChange(this.state);
        
        setTimeout(() => {
          this.state = AnimationStatus.Running;
          this.logStateChange(this.state);
          
          const success = this.state === AnimationStatus.Running;
          this.addTestResult('Paused->Running转换', success,
            `当前状态: ${this.getStateName(this.state)}`);
        }, 500);
      }, 500);
    } catch (error) {
      this.addTestResult('Paused->Running转换', false, `错误: ${error}`);
    }
  }

  private testRunningToStopped() {
    try {
      this.state = AnimationStatus.Running;
      this.logStateChange(this.state);
      
      setTimeout(() => {
        this.state = AnimationStatus.Stopped;
        this.logStateChange(this.state);
        
        const success = this.state === AnimationStatus.Stopped;
        this.addTestResult('Running->Stopped转换', success,
          `当前状态: ${this.getStateName(this.state)}`);
      }, 500);
    } catch (error) {
      this.addTestResult('Running->Stopped转换', false, `错误: ${error}`);
    }
  }

  private testPausedToStopped() {
    try {
      this.state = AnimationStatus.Running;
      this.logStateChange(this.state);
      
      setTimeout(() => {
        this.state = AnimationStatus.Paused;
        this.logStateChange(this.state);
        
        setTimeout(() => {
          this.state = AnimationStatus.Stopped;
          this.logStateChange(this.state);
          
          const success = this.state === AnimationStatus.Stopped;
          this.addTestResult('Paused->Stopped转换', success,
            `当前状态: ${this.getStateName(this.state)}`);
        }, 500);
      }, 500);
    } catch (error) {
      this.addTestResult('Paused->Stopped转换', false, `错误: ${error}`);
    }
  }

  private testCompleteStateCycle() {
    try {
      this.stateHistory = [];
      const expectedStates = ['Initial', 'Running', 'Paused', 'Running', 'Stopped'];
      
      this.state = AnimationStatus.Initial;
      this.logStateChange(this.state);
      
      setTimeout(() => {
        this.state = AnimationStatus.Running;
        this.logStateChange(this.state);
        
        setTimeout(() => {
          this.state = AnimationStatus.Paused;
          this.logStateChange(this.state);
          
          setTimeout(() => {
            this.state = AnimationStatus.Running;
            this.logStateChange(this.state);
            
            setTimeout(() => {
              this.state = AnimationStatus.Stopped;
              this.logStateChange(this.state);
              
              const actualStates = this.stateHistory.map(log => {
                const match = log.match(/\[(.*?)\] (\w+)/);
                return match ? match[2] : '';
              }).filter(s => s !== '');
              
              const success = actualStates.length >= expectedStates.length;
              this.addTestResult('完整状态循环', success,
                `状态序列: ${actualStates.join(' -> ')}`);
            }, 500);
          }, 500);
        }, 500);
      }, 500);
    } catch (error) {
      this.addTestResult('完整状态循环', false, `错误: ${error}`);
    }
  }

  private testRapidStateSwitch() {
    try {
      this.stateHistory = [];
      const states = [
        AnimationStatus.Initial,
        AnimationStatus.Running,
        AnimationStatus.Paused,
        AnimationStatus.Running,
        AnimationStatus.Stopped,
        AnimationStatus.Initial,
        AnimationStatus.Running
      ];
      
      let index = 0;
      const switchState = () => {
        if (index < states.length) {
          this.state = states[index];
          this.logStateChange(this.state);
          index++;
          setTimeout(switchState, 200);
        } else {
          const success = this.stateHistory.length >= states.length;
          this.addTestResult('快速状态切换', success,
            `切换次数: ${this.stateHistory.length}`);
        }
      };
      
      switchState();
    } catch (error) {
      this.addTestResult('快速状态切换', false, `错误: ${error}`);
    }
  }

  private testStateValidation() {
    try {
      const allStates = [
        AnimationStatus.Initial,
        AnimationStatus.Running,
        AnimationStatus.Paused,
        AnimationStatus.Stopped
      ];
      
      let allValid = true;
      const results: string[] = [];
      
      for (const state of allStates) {
        this.state = state;
        const isValid = this.state === state;
        allValid = allValid && isValid;
        results.push(`${this.getStateName(state)}: ${isValid ? '✓' : '✗'}`);
      }
      
      this.addTestResult('状态验证', allValid, results.join(', '));
    } catch (error) {
      this.addTestResult('状态验证', false, `错误: ${error}`);
    }
  }
}
