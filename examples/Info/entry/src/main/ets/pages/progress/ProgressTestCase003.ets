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

interface setsObject {
  linearTotal?: number
  linearVotal?: number
  linearStrokeWidth?: Length
  linearStrokeRadius?: PX | VP | LPX | Resource
  linearEnableScanEffect?: boolean
  linearEnableSmoothEffect?: boolean
}

interface setsObject1 {
  scaleRingTotal?: number
  scaleRingValue?: number
  scaleRingStrokeWidth?: Length
  scaleRingScaleCount?: number
  scaleRingScaleWidth?: Length
  scaleRingEnableSmoothEffect?: boolean
}

interface setsObject2 {
  capsuleTotal?: number
  capsuleValue?: number
  capsuleBorderColor?: ResourceColor
  capsuleBorderWidth?: Length
  capsuleContent?: string
  capsuleFont?: Font
  capsuleFontColor?: ResourceColor
  capsuleEnableScanEffect?: boolean
  capsuleShowDefaultPercentage?: boolean
  capsuleEnableSmoothEffect?: boolean
}

@Entry
@Component
struct ProgressLevel1_2 {
  private index: number = 0
  @State info?: string = undefined
  @State show: boolean = false
  @State linearTotal?: number = undefined
  @State linearVotal?: number = undefined
  @State linearStrokeWidth?: Length = undefined
  @State linearStrokeRadius?: PX | VP | LPX | Resource = undefined
  @State linearEnableScanEffect?: boolean = undefined
  @State linearEnableSmoothEffect?: boolean = undefined
  private index1: number = 0
  @State info1?: string = undefined
  @State show1: boolean = false
  @State scaleRingTotal?: number = undefined
  @State scaleRingValue?: number = undefined
  @State scaleRingStrokeWidth?: Length = undefined
  @State scaleRingScaleCount?: number = undefined
  @State scaleRingScaleWidth?: Length = undefined
  @State scaleRingEnableSmoothEffect?: boolean = undefined
  private index2: number = 0
  @State info2?: string = undefined
  @State show2: boolean = false
  @State capsuleTotal?: number = undefined
  @State capsuleValue?: number = undefined
  @State capsuleBorderColor?: ResourceColor = undefined
  @State capsuleBorderWidth?: Length = undefined
  @State capsuleContent?: string = undefined
  @State capsuleFont?: Font = undefined
  @State capsuleFontColor?: ResourceColor = undefined
  @State capsuleEnableScanEffect?: boolean = undefined
  @State capsuleShowDefaultPercentage?: boolean = undefined
  @State capsuleEnableSmoothEffect?: boolean = undefined
  private testCase: Array<setsObject> = [
    {
      linearTotal: undefined,
      linearVotal: undefined,
      linearStrokeWidth: undefined,
      linearStrokeRadius: undefined,
      linearEnableScanEffect: undefined,
      linearEnableSmoothEffect: undefined
    },
    {
      linearTotal: -20,
      linearVotal: 50,
      linearStrokeWidth: -10,
      linearStrokeRadius: '2px',
      linearEnableScanEffect: false,
      linearEnableSmoothEffect: true
    },
    {
      linearTotal: 0,
      linearVotal: 30,
      linearStrokeWidth: 0,
      linearStrokeRadius: '1vp',
      linearEnableScanEffect: false,
      linearEnableSmoothEffect: true
    },
    {
      linearTotal: 80,
      linearVotal: 10,
      linearStrokeWidth: 10,
      linearStrokeRadius: '6lpx',
      linearEnableScanEffect: true,
      linearEnableSmoothEffect: true
    },
    {
      linearTotal: 100,
      linearVotal: 120,
      linearStrokeWidth: '50px',
      linearStrokeRadius: $r('app.string.number1'),
      linearEnableScanEffect: true,
      linearEnableSmoothEffect: true
    },
    {
      linearTotal: 100,
      linearVotal: 30,
      linearStrokeWidth: '30%',
      linearStrokeRadius: '10vp',
      linearEnableScanEffect: false,
      linearEnableSmoothEffect: true
    },
    {
      linearTotal: 100,
      linearVotal: 90,
      linearStrokeWidth: $r('app.string.number120'),
      linearStrokeRadius: -10,
      linearEnableScanEffect: false,
      linearEnableSmoothEffect: false
    },
  ]

  private setParam(): void {
    this.linearTotal = this.testCase[this.index].linearTotal
    this.linearVotal = this.testCase[this.index].linearVotal
    this.linearStrokeWidth = this.testCase[this.index].linearStrokeWidth
    this.linearStrokeRadius = this.testCase[this.index].linearStrokeRadius
    this.linearEnableScanEffect = this.testCase[this.index].linearEnableScanEffect
    this.linearEnableSmoothEffect = this.testCase[this.index].linearEnableSmoothEffect

    this.info = 'Total: ' + this.testCase.length + ', CaseNumber: ' + this.index +
      '\ntotal: ' + this.testCase[this.index].linearTotal + '\nvalue: ' + this.testCase[this.index].linearVotal +
      '\nstrokeWidth: ' + this.testCase[this.index].linearStrokeWidth + '\nstrokeRadius : ' +
    this.testCase[this.index].linearStrokeRadius +
      '\nenableScanEffect: ' + this.testCase[this.index].linearEnableScanEffect + '\nenableSmoothEffect: ' +
    this.testCase[this.index].linearEnableSmoothEffect
  }

  private testCase1: Array<setsObject1> = [
    {
      scaleRingTotal: undefined,
      scaleRingValue: undefined,
      scaleRingStrokeWidth: undefined,
      scaleRingScaleCount: undefined,
      scaleRingScaleWidth: undefined,
      scaleRingEnableSmoothEffect: undefined
    },
    {
      scaleRingTotal: -20,
      scaleRingValue: 50,
      scaleRingStrokeWidth: -10,
      scaleRingScaleCount: -10,
      scaleRingScaleWidth: -10,
      scaleRingEnableSmoothEffect: true
    },
    {
      scaleRingTotal: 0,
      scaleRingValue: 30,
      scaleRingStrokeWidth: 0,
      scaleRingScaleCount: 0,
      scaleRingScaleWidth: 0,
      scaleRingEnableSmoothEffect: true
    },
    {
      scaleRingTotal: 80,
      scaleRingValue: 10,
      scaleRingStrokeWidth: 30,
      scaleRingScaleCount: 1,
      scaleRingScaleWidth: 5,
      scaleRingEnableSmoothEffect: true
    },
    {
      scaleRingTotal: 100,
      scaleRingValue: 20,
      scaleRingStrokeWidth: '100px',
      scaleRingScaleCount: 2,
      scaleRingScaleWidth: '20px',
      scaleRingEnableSmoothEffect: true
    },
    {
      scaleRingTotal: 100,
      scaleRingValue: 30,
      scaleRingStrokeWidth: '30%',
      scaleRingScaleCount: 50,
      scaleRingScaleWidth: '30%',
      scaleRingEnableSmoothEffect: false
    },
    {
      scaleRingTotal: 100,
      scaleRingValue: 90,
      scaleRingStrokeWidth: $r('app.string.number1'),
      scaleRingScaleCount: 200,
      scaleRingScaleWidth: $r('app.string.number120'),
      scaleRingEnableSmoothEffect: true
    },
  ]

  private setParam1(): void {
    this.scaleRingTotal = this.testCase1[this.index1].scaleRingTotal
    this.scaleRingValue = this.testCase1[this.index1].scaleRingValue
    this.scaleRingStrokeWidth = this.testCase1[this.index1].scaleRingStrokeWidth
    this.scaleRingScaleCount = this.testCase1[this.index1].scaleRingScaleCount
    this.scaleRingScaleWidth = this.testCase1[this.index1].scaleRingScaleWidth
    this.scaleRingEnableSmoothEffect = this.testCase1[this.index1].scaleRingEnableSmoothEffect

    this.info1 = 'Total: ' + this.testCase1.length + ', CaseNumber: ' + this.index1 +
      '\ntotal: ' + this.testCase1[this.index1].scaleRingTotal + '\nvalue: ' +
    this.testCase1[this.index1].scaleRingValue +
      '\nstrokeWidth: ' + this.testCase1[this.index1].scaleRingStrokeWidth + '\nscaleCount: ' +
    this.testCase1[this.index1].scaleRingScaleCount +
      '\nscaleWidth: ' + this.testCase1[this.index1].scaleRingScaleWidth + '\nenableSmoothEffect: ' +
    this.testCase1[this.index1].scaleRingEnableSmoothEffect
  }

  private testCase2: Array<setsObject2> = [
    {
      capsuleTotal: undefined,
      capsuleValue: 30,
      capsuleBorderColor: undefined,
      capsuleBorderWidth: undefined,
      capsuleContent: '下载',
      capsuleFont: undefined,
      capsuleFontColor: undefined,
      capsuleEnableScanEffect: undefined,
      capsuleShowDefaultPercentage: true,
      capsuleEnableSmoothEffect: undefined,
    },
    {
      capsuleTotal: -20,
      capsuleValue: 90,
      capsuleBorderColor: Color.Red,
      capsuleBorderWidth: -5,
      capsuleContent: undefined,
      capsuleFont: {
        size: 20,
        weight: 550,
        family: 'Arial',
        style: FontStyle.Normal
      },
      capsuleFontColor: $r('app.string.Color_green'),
      capsuleEnableScanEffect: false,
      capsuleShowDefaultPercentage: true,
      capsuleEnableSmoothEffect: true,
    },
    {
      capsuleTotal: 0,
      capsuleValue: 50,
      capsuleBorderColor: 0xffa500,
      capsuleBorderWidth: 0,
      capsuleContent: '@￥#@快￥&……#%*',
      capsuleFont: {
        size: -10,
        weight: 200,
        family: 'Arial',
        style: FontStyle.Italic
      },
      capsuleFontColor: Color.Green,
      capsuleEnableScanEffect: false,
      capsuleShowDefaultPercentage: true,
      capsuleEnableSmoothEffect: true,
    },
    {
      capsuleTotal: 80,
      capsuleValue: 10,
      capsuleBorderColor: '#32cd32',
      capsuleBorderWidth: 5,
      capsuleContent: 'rgb(255, 100, 100)rfehbuqjil3quo3y4钱他！#￥#@……%￥@@￥&',
      capsuleFont: {
        size: 15,
        weight: '800',
        family: 'Arial',
        style: FontStyle.Normal
      },
      capsuleFontColor: Color.Red,
      capsuleEnableScanEffect: false,
      capsuleShowDefaultPercentage: true,
      capsuleEnableSmoothEffect: false,
    },
    {
      capsuleTotal: 80,
      capsuleValue: 10,
      capsuleBorderColor: 'rgb(255, 100, 100)',
      capsuleBorderWidth: '20',
      capsuleContent: '',
      capsuleFont: {
        size: '100px',
        weight: 50,
        family: 'Arial',
        style: FontStyle.Normal
      },
      capsuleFontColor: Color.Blue,
      capsuleEnableScanEffect: true,
      capsuleShowDefaultPercentage: false,
      capsuleEnableSmoothEffect: true,
    },
    {
      capsuleTotal: 100,
      capsuleValue: 120,
      capsuleBorderColor: 0xffa500,
      capsuleBorderWidth: '20px',
      capsuleContent: '暂停',
      capsuleFont: {
        size: '100%',
        weight: 300,
        family: 'Arial',
        style: FontStyle.Normal
      },
      capsuleFontColor: 0x800080,
      capsuleEnableScanEffect: false,
      capsuleShowDefaultPercentage: false,
      capsuleEnableSmoothEffect: true,
    },
    {
      capsuleTotal: 100,
      capsuleValue: 80,
      capsuleBorderColor: '#FFFF00',
      capsuleBorderWidth: '20%',
      capsuleContent: undefined,
      capsuleFont: {
        size: $r('app.float.float_30_6'),
        weight: 900,
        family: 'Arial',
        style: FontStyle.Italic
      },
      capsuleFontColor: 0xFF4D00,
      capsuleEnableScanEffect: false,
      capsuleShowDefaultPercentage: true,
      capsuleEnableSmoothEffect: true,
    },
    {
      capsuleTotal: 80,
      capsuleValue: 10,
      capsuleBorderColor: 0x800080,
      capsuleBorderWidth: 'aa',
      capsuleContent: undefined,
      capsuleFont: {
        size: 'aa',
        weight: FontWeight.Bolder,
        family: 'Arial',
        style: FontStyle.Normal
      },
      capsuleFontColor: '#FFFF00',
      capsuleEnableScanEffect: false,
      capsuleShowDefaultPercentage: true,
      capsuleEnableSmoothEffect: true,
    },
    {
      capsuleTotal: 90,
      capsuleValue: 40,
      capsuleBorderColor: Color.Blue,
      capsuleBorderWidth: $r('app.float.float_10'),
      capsuleContent: undefined,
      capsuleFont: {
        size: '100px',
        weight: FontWeight.Normal,
        family: 'Arial',
        style: FontStyle.Normal
      },
      capsuleFontColor: 'rgb(255, 100, 100)',
      capsuleEnableScanEffect: false,
      capsuleShowDefaultPercentage: true,
      capsuleEnableSmoothEffect: true,
    },
  ]

  private setParam2(): void {
    this.capsuleTotal = this.testCase2[this.index2].capsuleTotal
    this.capsuleValue = this.testCase2[this.index2].capsuleValue
    this.capsuleBorderColor = this.testCase2[this.index2].capsuleBorderColor
    this.capsuleBorderWidth = this.testCase2[this.index2].capsuleBorderWidth
    this.capsuleContent = this.testCase2[this.index2].capsuleContent
    this.capsuleFont = this.testCase2[this.index2].capsuleFont
    this.capsuleFontColor = this.testCase2[this.index2].capsuleFontColor
    this.capsuleEnableScanEffect = this.testCase2[this.index2].capsuleEnableScanEffect
    this.capsuleShowDefaultPercentage = this.testCase2[this.index2].capsuleShowDefaultPercentage
    this.capsuleEnableSmoothEffect = this.testCase2[this.index2].capsuleEnableSmoothEffect

    this.info2 = 'Total: ' + this.testCase2.length + ', CaseNumber: ' + this.index2 +
      '\nvalue: ' + this.testCase2[this.index2].capsuleValue + '\ntotal: ' +
    this.testCase2[this.index2].capsuleTotal + '\nborderColor: ' + this.testCase2[this.index2].capsuleBorderColor +
      '\nborderWidth: ' + this.testCase2[this.index2].capsuleBorderWidth + '\ncontent: ' +
    this.testCase2[this.index2].capsuleContent +
      '\nfont: ' + this.testCase2[this.index2].capsuleFont + '\nfontColor: ' +
    this.testCase2[this.index2].capsuleFontColor +
      '\nenableScanEffect: ' + this.testCase2[this.index2].capsuleEnableScanEffect + '\nshowDefaultPercentage: ' +
    this.testCase2[this.index2].capsuleShowDefaultPercentage +
      '\nenableSmoothEffect: ' + this.testCase2[this.index2].capsuleEnableSmoothEffect
  }
  build() {
    Scroll() {
      Column({ space: 8 }) {
        Column({ space: 8 }) {
          Text('No type Progress .width(200).height(50)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.linearVotal, total: this.linearTotal }).width(200).height(50)
            .style({
              strokeWidth: this.linearStrokeWidth,
              strokeRadius: this.linearStrokeRadius,
              enableScanEffect: this.linearEnableScanEffect,
              enableSmoothEffect: this.linearEnableSmoothEffect
            })
          Text('undefined Progress .width(200)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('100%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.linearVotal, total: this.linearTotal, type: undefined }).width(200)
            .style({
              strokeWidth: this.linearStrokeWidth,
              strokeRadius: this.linearStrokeRadius,
              enableScanEffect: this.linearEnableScanEffect,
              enableSmoothEffect: this.linearEnableSmoothEffect
            })
          Text('Linear Progress .height(50)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('90%')
            .height(this.show ? 'auto' : 0)
          Progress({ value: this.linearVotal, total: this.linearTotal, type: ProgressType.Linear }).height(50)
            .style({
              strokeWidth: this.linearStrokeWidth,
              strokeRadius: this.linearStrokeRadius,
              enableScanEffect: this.linearEnableScanEffect,
              enableSmoothEffect: this.linearEnableSmoothEffect
            })
          Divider().height(10)
          Text('ScaleRing Progress .height(150)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('90%')
            .height(this.show1 ? 'auto' : 0)
          Progress({ value: this.scaleRingValue, total: this.scaleRingTotal, type: ProgressType.ScaleRing })
            .height(150)
            .style({
              strokeWidth: this.scaleRingStrokeWidth,
              scaleCount: this.scaleRingScaleCount,
              scaleWidth: this.scaleRingScaleWidth,
              enableSmoothEffect: this.scaleRingEnableSmoothEffect
            })
          Divider().height(10)
          Text('Capsule Progress .height(50)')
            .fontSize(9)
            .fontColor(0xCCCCCC)
            .width('90%')
            .height(this.show2 ? 'auto' : 0)
          Progress({ value: this.capsuleValue, total: this.capsuleTotal, type: ProgressType.Capsule }).height(50)
            .style({
              borderColor: this.capsuleBorderColor,
              borderWidth: this.capsuleBorderWidth,
              content: this.capsuleContent,
              font: this.capsuleFont,
              fontColor: this.capsuleFontColor,
              enableScanEffect: this.capsuleEnableScanEffect,
              showDefaultPercentage: this.capsuleShowDefaultPercentage,
              enableSmoothEffect: this.capsuleEnableSmoothEffect,
            })
        }
        .key('testArea')
        .height('75%')
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

        Text('2.切换参数，显示参数=' + this.show2).fontSize(9).fontColor(0xCCCCCC).width('100%')
          .onClick(() => {
            this.show2 = !this.show2
          })
        Row({ space: 2 }) {
          Text(`${this.testCase2.length}`).key('num2')
          Text('Test2++')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.setParam2()
              this.index2++
              if (this.index2 == this.testCase2.length) {
                this.index2 = 0
              }
            })
          Text('Test2--')
            .fontSize(10)
            .backgroundColor(0x0000ff)
            .fontColor(0xffffff)
            .padding(5)
            .onClick(() => {
              this.index2--
              if (this.index2 == -1) {
                this.index2 = this.testCase2.length - 1
              }
              this.setParam2()
            })
        }
        if (this.show2) {
          Text(this.info2)
        }
      }
      .width('100%')
    }
  }
}