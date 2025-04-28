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

interface TestCaseLevel131 {
  ringTotal?: number
  ringValue?: number
  ringColor?: LinearGradient
  ringStrokeWidth?: Length
  ringShadow?: boolean
  ringStatus?: ProgressStatus
  ringEnableScanEffect?: boolean
  ringEnableSmoothEffect?: boolean
}

interface TestCaseLevel132 {
  eclipseTotal?: number
  eclipseValue?: number
  eclipseEnableSmoothEffect?: boolean
}

@Entry
@Component
struct ProgressLevel1_3 {
  private index: number = 0
  @State info?: string = undefined
  @State show: boolean = false
  @State ringTotal?: number = undefined
  @State ringValue?: number = undefined
  @State ringColor?: LinearGradient = undefined
  @State ringStrokeWidth?: Length = undefined
  @State ringShadow?: boolean = undefined
  @State ringStatus?: ProgressStatus = undefined
  @State ringEnableScanEffect?: boolean = undefined
  @State ringEnableSmoothEffect?: boolean = undefined
  private index1: number = 0
  @State info1?: string = undefined
  @State show1: boolean = false
  @State eclipseTotal?: number = undefined
  @State eclipseValue?: number = undefined
  @State eclipseEnableSmoothEffect?: boolean = undefined
  private testCase: Array<TestCaseLevel131> = [
    {
      //当前进度值40。进度总长100，进度条默认宽度4vp.
      ringTotal: undefined,
      ringValue: 40,
      ringColor: new LinearGradient([{ color: 'aa', offset: 0.5 }]),
      ringStrokeWidth: undefined,
      ringShadow: undefined,
      ringStatus: undefined,
      ringEnableScanEffect: undefined,
      ringEnableSmoothEffect: undefined
    },

    {
      //当前进度值50，total使用默认值100，进度条宽度使用默认是4vp，阴影开，开启检查更新动效。无扫光动效，平滑动效开
      ringTotal: -20,
      ringValue: 50,
      ringColor: new LinearGradient([{ color: 0xFF000000, offset: 0.5 }]),
      ringStrokeWidth: -10,
      ringShadow: true,
      ringStatus: ProgressStatus.LOADING,
      ringEnableScanEffect: false,
      ringEnableSmoothEffect: true
    },
    {
      //当前进度值30，total使用默认值100，纯色-黑，进度条宽度使用默认是4vp，无扫光动效，平滑动效开
      ringTotal: 0,
      ringValue: 30,
      ringColor: new LinearGradient([{ color: 0xFF000000, offset: 0.5 }]),
      ringStrokeWidth: 0,
      ringShadow: true,
      ringStatus: ProgressStatus.PROGRESSING,
      ringEnableScanEffect: false,
      ringEnableSmoothEffect: true
    },
    {
      // 当前进度值设置为10，total设置为80，进度条宽度是10vp，有扫光动效，平滑动效开
      ringTotal: 80,
      ringValue: 10,
      ringColor: new LinearGradient([{ color: Color.Orange, offset: 0.5 }, { color: Color.Green, offset: 0.5 }, {
        color: Color.Red,
        offset: 0.8
      }]),
      ringStrokeWidth: 10,
      ringShadow: true,
      ringStatus: ProgressStatus.PROGRESSING,
      ringEnableScanEffect: true,
      ringEnableSmoothEffect: true
    },
    {
      // 当前进度值大于total的数值时置为total，total设置为100，进度条宽度是50px，有扫光动效，平滑动效关（满格的时候，扫光动效不生效）
      ringTotal: 100,
      ringValue: 120,
      ringColor: new LinearGradient([{ color: Color.Orange, offset: 0.5 }, { color: Color.Green, offset: 0.3 }, {
        color: Color.Red,
        offset: 0.8
      }]),
      ringStrokeWidth: '50px',
      ringShadow: false,
      ringStatus: ProgressStatus.PROGRESSING,
      ringEnableScanEffect: true,
      ringEnableSmoothEffect: false
    },
  ]

  private setParam(): void {
    this.ringTotal = this.testCase[this.index].ringTotal
    this.ringValue = this.testCase[this.index].ringValue
    this.ringColor = this.testCase[this.index].ringColor
    this.ringStrokeWidth = this.testCase[this.index].ringStrokeWidth
    this.ringShadow = this.testCase[this.index].ringShadow
    this.ringStatus = this.testCase[this.index].ringStatus
    this.ringEnableScanEffect = this.testCase[this.index].ringEnableScanEffect
    this.ringEnableSmoothEffect = this.testCase[this.index].ringEnableSmoothEffect

    this.info = 'Total: ' + this.testCase.length + ', CaseNumber: ' + this.index +
      '\ntotal: ' + this.testCase[this.index].ringTotal + '\nvalue: ' + this.testCase[this.index].ringValue +
      '\ncolor: ' + this.testCase[this.index].ringColor +
      '\nstrokeWidth: ' + this.testCase[this.index].ringStrokeWidth + '\nshadow: ' +
    this.testCase[this.index].ringShadow +
      '\nstatus: ' + this.testCase[this.index].ringStatus + '\nenableScanEffect: ' +
    this.testCase[this.index].ringEnableScanEffect +
      '\nenableSmoothEffect: ' + this.testCase[this.index].ringEnableSmoothEffect
  }

  private testCase1: Array<TestCaseLevel132> = [
    {
      //当前进度值0。进度总长100，进度条默认宽度4vp.总刻度数120，刻度粗细2vp，平滑动效开
      eclipseTotal: undefined,
      eclipseValue: undefined,
      eclipseEnableSmoothEffect: undefined
    },

    {
      //当前进度值50，total使用默认值100，进度条宽度使用默认是4vp，总刻度数120，刻度粗细2vp，平滑动效开
      eclipseTotal: -20,
      eclipseValue: 50,
      eclipseEnableSmoothEffect: true
    },
    {
      //当前进度值30，total使用默认值100，进度条宽度使用默认是4vp，总刻度数120，刻度粗细2vp，平滑动效关
      eclipseTotal: 0,
      eclipseValue: 30,
      eclipseEnableSmoothEffect: false
    }
  ]

  private setParam1(): void {
    this.eclipseTotal = this.testCase1[this.index1].eclipseTotal
    this.eclipseValue = this.testCase1[this.index1].eclipseValue
    this.eclipseEnableSmoothEffect = this.testCase1[this.index1].eclipseEnableSmoothEffect

    this.info1 = 'Total: ' + this.testCase1.length + ', CaseNumber: ' + this.index1 +
      '\ntotal: ' + this.testCase1[this.index1].eclipseTotal + '\nvalue: ' +
    this.testCase1[this.index1].eclipseValue +
      '\nenableSmoothEffect: ' + this.testCase1[this.index1].eclipseEnableSmoothEffect
  }

  build() {
    Scroll() {
      Column({ space: 8 }) {
        Text('Ring Progress .height(150)').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Progress({ value: this.ringValue, total: this.ringTotal, type: ProgressType.Ring }).height(150)
          .color(this.ringColor)
          .style({
            strokeWidth: this.ringStrokeWidth,
            shadow: this.ringShadow,
            status: this.ringStatus,
            enableScanEffect: this.ringEnableScanEffect,
            enableSmoothEffect: this.ringEnableSmoothEffect
          })

        Text('2.切换参数，显示参数=' + this.show).fontSize(9).fontColor(0xCCCCCC).width('100%')
          .onClick(() => {
            this.show = !this.show
          })

        Row({ space: 2 }) {
          Text(`${this.testCase.length}`).key('num')
          Text('Test++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.setParam()
              this.index++
              if (this.index == this.testCase.length) {
                this.index = 0
              }
            })

          Text('Test--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index--
              if (this.index == -1) {
                this.index = this.testCase.length - 1
              }
              this.setParam()
            })
        }

        if (this.show) {
          Text(this.info)
        }

        Divider().height(10)
        Text('Eclipse Progress .height(150)').fontSize(9).fontColor(0xCCCCCC).width('90%')
        Progress({ value: this.eclipseValue, total: this.eclipseTotal, type: ProgressType.Eclipse }).height(150)
          .style({
            enableSmoothEffect: this.eclipseEnableSmoothEffect
          })

        Text('2.切换参数，显示参数=' + this.show1).fontSize(9).fontColor(0xCCCCCC).width('100%')
          .onClick(() => {
            this.show1 = !this.show1
          })

        Row({ space: 2 }) {
          Text(`${this.testCase1.length}`).key('num1')
          Text('Test1++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.setParam1()
              this.index1++
              if (this.index1 == this.testCase1.length) {
                this.index1 = 0
              }
            })

          Text('Test1--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index1--
              if (this.index1 == -1) {
                this.index1 = this.testCase1.length - 1
              }
              this.setParam1()
            })
        }

        if (this.show1) {
          Text(this.info1)
        }

      }
      .width('100%')
    }
  }
}