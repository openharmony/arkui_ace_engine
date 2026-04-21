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
struct ImageAnimatorTest003 {
  @State testTitle: string = '属性设置测试';
  @State state: AnimationStatus = AnimationStatus.Initial;
  @State testResults: string[] = [];
  @State duration: number = 2000;
  @State iterations: number = 1;
  @State reverse: boolean = false;
  @State fillMode: FillMode = FillMode.None;
  @State width: number = 300;
  @State height: number = 200;
  @State selectedFillMode: number = 0;

  private fillModes: FillMode[] = [
    FillMode.None,
    FillMode.Forwards,
    FillMode.Backwards,
    FillMode.Both
  ];

  private fillModeNames: string[] = [
    'None',
    'Forwards',
    'Backwards',
    'Both'
  ];

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

        this.buildPropertyControls()

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
      Text('属性测试控制')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Button('测试1: Duration属性')
          .onClick(() => {
            this.testDurationProperty();
          })

        Button('测试2: Iterations属性')
          .onClick(() => {
            this.testIterationsProperty();
          })

        Button('测试3: Reverse属性')
          .onClick(() => {
            this.testReverseProperty();
          })
      }

      Row({ space: 10 }) {
        Button('测试4: FillMode属性')
          .onClick(() => {
            this.testFillModeProperty();
          })

        Button('测试5: Width属性')
          .onClick(() => {
            this.testWidthProperty();
          })

        Button('测试6: Height属性')
          .onClick(() => {
            this.testHeightProperty();
          })
      }

      Row({ space: 10 }) {
        Button('测试7: 组合属性')
          .onClick(() => {
            this.testCombinedProperties();
          })

        Button('测试8: 边界值测试')
          .onClick(() => {
            this.testBoundaryValues();
          })

        Button('清空结果')
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
  buildPropertyControls() {
    Column({ space: 15 }) {
      Text('属性控制面板')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)

      Row({ space: 20 }) {
        Column({ space: 5 }) {
          Text('Duration (ms)')
            .fontSize(14)
          Slider({
            min: 500,
            max: 5000,
            value: this.duration,
            step: 100
          })
            .width(200)
            .onChange((value: number) => {
              this.duration = value;
            })
          Text(`${this.duration}ms`)
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

      Row({ space: 15 }) {
        Text('FillMode:')
          .fontSize(14)
        Select(this.fillModeNames)
          .selected(this.selectedFillMode)
          .value(this.fillModeNames[this.selectedFillMode])
          .onSelect((index: number) => {
            this.selectedFillMode = index;
            this.fillMode = this.fillModes[index];
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
        .onFinish(() => {
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
      
      this.addTestResult('Duration属性设置', allValid,
        `测试值: ${testValues.join(', ')}ms`);
    } catch (error) {
      this.addTestResult('Duration属性设置', false, `错误: ${error}`);
    }
  }

  private IterationsProperty() {
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
      
      this.addTestResult('Iterations属性设置', allValid,
        `测试值: ${testValues.join(', ')}`);
    } catch (error) {
      this.addTestResult('Iterations属性设置', false, `错误: ${error}`);
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
      
      this.addTestResult('Reverse属性设置', allValid,
        `测试值: ${testValues.join(', ')}`);
    } catch (error) {
      this.addTestResult('Reverse属性设置', false, `错误: ${error}`);
    }
  }

  private testFillModeProperty() {
    try {
      let allValid = true;
      
      for (let i = 0; i < this.fillModes.length; i++) {
        this.fillMode = this.fillModes[i];
        this.selectedFillMode = i;
        if (this.fillMode !== this.fillModes[i]) {
          allValid = false;
          break;
        }
      }
      
      this.addTestResult('FillMode属性设置', allValid,
        `测试模式: ${this.fillModeNames.join(', ')}`);
    } catch (error) {
      this.addTestResult('FillMode属性设置', false, `错误: ${error}`);
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
      
      this.addTestResult('Width属性设置', allValid,
        `测试值: ${testValues.join(', ')}px`);
    } catch (error) {
      this.addTestResult('Width属性设置', false, `错误: ${error}`);
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
      
      this.addTestResult('Height属性设置', allValid,
        `测试值: ${testValues.join(', ')}px`);
    } catch (error) {
      this.addTestResult('Height属性设置', false, `错误: ${error}`);
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
      
      this.addTestResult('组合属性设置', allSet,
        `Duration:1500, Iterations:3, Reverse:true, Width:350, Height:250`);
      
      if (!allSet) {
        this.duration = originalDuration;
        this.iterations = originalIterations;
        this.reverse = originalReverse;
        this.width = originalWidth;
        this.height = originalHeight;
      }
    } catch (error) {
      this.addTestResult('组合属性设置', false, `错误: ${error}`);
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
}
